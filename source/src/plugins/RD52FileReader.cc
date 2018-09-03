/// \file RD52FileReader.cc
/*
 *
 * RD52FileReader.cc source template automatically generated by a class generator
 * Creation date : lun. mars 7 2016
 *
 * This file is part of DQM4HEP libraries.
 *
 * DQM4HEP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * based upon these libraries are permitted. Any copy of these libraries
 * must include this copyright notice.
 *
 * DQM4HEP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DQM4HEP.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @author Tom Coates
 * @copyright CNRS , IPNL
 */


// -- std headers 
#include <sstream>

// -- dqm4hep headers
#include <dqm4hep/Event.h>
#include <dqm4hep/EventReader.h>
#include <dqm4hep/StatusCodes.h>
#include <dqm4hep/GenericEvent.h>
#include <dqm4hep/PluginManager.h>
#include <dqm4hep/XmlHelper.h>

namespace dqm4hep {

  namespace core {

    /**
     *  @brief  RD52FileReader class
     *          Read a DREAM RD52 calorimeter .dat datafile and read GenericEvent events from it
     */
    class RD52FileReader : public EventReader {
    public:
      RD52FileReader() = default;
      ~RD52FileReader() override;
      RD52FileReader(const RD52FileReader&) = delete;
      RD52FileReader& operator=(const RD52FileReader&) = delete;

      core::StatusCode open(const std::string &fname) override;
      core::StatusCode skipNEvents(int nEvents) override;
      core::StatusCode runInfo(core::Run &run) override;
      core::StatusCode readNextEvent() override;
      core::StatusCode close() override;
      
      typedef struct {
	uint32_t magicWord;        // Magic word - 0xaabbccdd
	uint32_t headerSize;       // Size in bytes
	uint32_t runNumber;
	uint32_t numberOfEvents;
	uint32_t startTime;
	uint32_t endTime;
      } RunHeader;

      typedef struct {
	uint32_t eventMarker;      // Beginning of event marker - 0xcafecafe
	uint32_t headerSize;       // In bytes
	uint32_t eventSize;        // In bytes (including header)
	uint32_t eventNumber;
	uint32_t spillNumber;
	uint32_t tsec;             // Seconds in the day from gettimeofday
	uint32_t tusec;            // Microseconds in the day from gettimeofday
      } EventHeader;

      typedef struct {
	uint32_t subeventMarker;   // Beginning of subevent marker - 0xacabacab
	uint32_t headerSize;       // In bytes
	uint32_t moduleID;
	uint32_t subeventSize;
      } SubeventHeader;

    protected:
      FILE* inputFile = 0;

    private:
      uint32_t hexEventMarker = 0xCAFECAFE;
      uint32_t hexSubeventMarker = 0xACABACAB;

    };
    
    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    RD52FileReader::~RD52FileReader() {
      //
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode RD52FileReader::open(const std::string &fname) {
      
      inputFile = fopen(fname.c_str(), "r");

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode RD52FileReader::skipNEvents(int nEvents) {

      for (int e=0; e<nEvents; e++) {
	EventHeader myEventHeader;
	fread(&myEventHeader, sizeof(myEventHeader), 1, inputFile);
	int32_t eventDataSize = (myEventHeader.eventSize-myEventHeader.headerSize)/4;
	uint32_t* myEventContainer = new uint32_t[eventDataSize];
	fread(myEventContainer, sizeof(uint32_t), eventDataSize, inputFile);
	delete[] myEventContainer;
      }

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode RD52FileReader::runInfo(core::Run &run) {

      RunHeader myRunHeader;
      fread(&myRunHeader, sizeof(RunHeader), 1, inputFile);

      run.setRunNumber(myRunHeader.runNumber);
      //run.setStartTime(core::time::asPoint(myRunHeader.startTime)); // Compiler says "ambiguous"
      //run.setEndTime(core::time::asPoint(myRunHeader.endTime)); // Compiler says "ambiguous" 
      run.setParameter("Number of events", myRunHeader.numberOfEvents);
      run.setParameter("Magic word", myRunHeader.magicWord);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode RD52FileReader::readNextEvent() {
      EventPtr pEvent = GenericEvent::make_shared();
      GenericEvent *pGenericEvent = pEvent->getEvent<GenericEvent>();

      EventHeader myEventHeader;
      fread(&myEventHeader, sizeof(EventHeader), 1, inputFile);

      if (myEventHeader.eventMarker != hexEventMarker) {
	dqm_error("Could not locate the correct event marker. The read event marker was: {0}",myEventHeader.eventMarker);
	return STATUS_CODE_FAILURE;
      }

      int32_t eventDataSize = (myEventHeader.eventSize-myEventHeader.headerSize)/4;
      uint32_t* myEventContainer = new uint32_t[eventDataSize];
      fread(myEventContainer, sizeof(uint32_t), eventDataSize, inputFile);
 
      SubeventHeader mySubeventHeader;
      uint32_t subeventLoopCounter = 0;

      std::string valueType;
      std::vector<int> dataValue;
      std::vector<int> dataChannel;

      bool isV775 = false;
      bool isV792AC = false;
      bool isV862 = false;
      bool isADC = false;
      bool isTDC = false;

      while (true) {
	if (subeventLoopCounter > eventDataSize) {
	  break;
	}

 	memcpy(&mySubeventHeader, &myEventContainer[0], sizeof(mySubeventHeader));
	if (mySubeventHeader.subeventMarker != hexSubeventMarker) {
	  dqm_error("Could not locate the correct subevent marker. The read subevent marker was: {0}",mySubeventHeader.subeventMarker);
	  return STATUS_CODE_FAILURE;
	}
	
	// We should also check the validity bit here (bit 14) but previously the validity bit was always 0. Wonder if this is a feature of the module? 
	// We also need to decode the trigger number, but the process for this in the original code is arcane and makes no sense.

	if ( ((myEventContainer[subeventLoopCounter] >> 24) & 0x7) == 0) {

	  //
	  // So now we need to know what the different module IDs are
	  // Options so far in dec: 134217764, 50331685
	  // Options so far in hex: 0x8000024, 0x3000025
	  // Although the DreamDaq says "MARKER_V775" should be 0x20000024
	  //

	  if (mySubeventHeader.moduleID == 0x8000024) { //Placeholder
	    isV775 = true;
	  }
	  if (mySubeventHeader.moduleID == 0x3000025) { //Placeholder
	    isV792AC = true;
	  }
	  if (mySubeventHeader.moduleID == 0x3000025) { //Placeholder
	    isV862 = true;
	  }

	  if (!isV775 and !isV792AC and !isV862) {
	    dqm_error("The Module ID could not be classified. The read module Id was: {0}", mySubeventHeader.moduleID);
	    return STATUS_CODE_FAILURE;
	  }
	  if (isV775) {
	    isTDC = true;
	    bool tdcValidity = ((myEventContainer[subeventLoopCounter] >> 14) & 0x1);
	    dataValue.push_back(myEventContainer[subeventLoopCounter] & 0xFFF);
	    dataChannel.push_back((myEventContainer[subeventLoopCounter] >> 17) & 0xF);	   
	  }
	  if (isV792AC or isV862) {
	    isADC = true;
	    //adcValidity ?
	    dataValue.push_back(myEventContainer[subeventLoopCounter] & 0xFFF);
	    dataChannel.push_back((myEventContainer[subeventLoopCounter] >> 16) & 0x1F);
	  }

	/*
	  Global [?]	 
	    [Type]			= (buf[i] >> 24) & 0x7	  
	  DecodeV775 (TDC)
	    data			= (buf[i] & 0xFFF)
	    channel			= (buf[i] >> 17) 0xF
	    valid			= (buf[i] >> 14) & 0x1 
	  DecodeV792AC (ADCN)
	    data			= (buf[i] & 0xFFF);
	    channel			= (buf[i] >> 16) & 0x1F;
	    ov				= (buf[i] >> 12) & 0x1;
	    un				= (buf[i] >> 13) & 0x1;	 
	  DecodeV862
	    (same as V792AC)
	*/
	}
	subeventLoopCounter += mySubeventHeader.subeventSize/4;
      }

      pEvent->setEventNumber(myEventHeader.eventNumber);
      //pEvent->setTimeStamp(core::time::asPoint(myEventHeader.tsec)); // Compiler says "ambiguous"


      if (isADC) {
	pGenericEvent->setValues("EventType", "ADC");
	pGenericEvent->setValues("ADC", dataValue);
      }
      if (isTDC) {
	pGenericEvent->setValues("EventType", "TDC");
	pGenericEvent->setValues("TDC", dataValue);
      }
      if (!isADC and !isTDC) {
	
      }

      pGenericEvent->setValues(valueType, dataValue);
      pGenericEvent->setValues("Channels", dataChannel);

      onEventRead().emit(pEvent);
      delete[] myEventContainer;
      return STATUS_CODE_SUCCESS;
    }

    StatusCode RD52FileReader::close() {
      
      fclose(inputFile);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------
    
    DQM_PLUGIN_DECL(RD52FileReader, "RD52FileReader");
  }
}
