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
      uint32_t hexMarkerEvent = 0xCAFECAFE;
      uint32_t hexMarkerSubevent = 0xACABACAB;

      uint32_t hexMarkerTDC  = 0x08000024;
      uint32_t hexMarkerAncl = 0x03000025;
      uint32_t hexMarkerADC0 = 0x04000005;
      uint32_t hexMarkerADC1 = 0x05000005;
      uint32_t hexMarkerADC2 = 0x06000005;
      uint32_t hexMarkerADC3 = 0x07000005;

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

      if (feof(inputFile)) {
	dqm_warning("Reached end of file");
	return STATUS_CODE_OUT_OF_RANGE;
      }

      EventPtr pEvent = GenericEvent::make_shared();
      GenericEvent *pGenericEvent = pEvent->getEvent<GenericEvent>();

      EventHeader myEventHeader;
      fread(&myEventHeader, sizeof(EventHeader), 1, inputFile);

      if (myEventHeader.eventMarker != hexMarkerEvent) {
	dqm_error("Could not locate the correct event marker. The read event marker was: {0}", myEventHeader.eventMarker);
	return STATUS_CODE_FAILURE;
      }

      int32_t eventDataSize = (myEventHeader.eventSize-myEventHeader.headerSize)/4;
      uint32_t* myEventContainer = new uint32_t[eventDataSize];
      fread(myEventContainer, sizeof(uint32_t), eventDataSize, inputFile);
 
      SubeventHeader mySubeventHeader;
      uint32_t subeventLoopCounter = 0;

      // These are default values to avoid passing an array full of null values
      int dataTDC[32]  = {999999};
      int dataAncl[32] = {999999};
      int dataADC0[32] = {999999};
      int dataADC1[32] = {999999};
      int dataADC2[32] = {999999};
      int dataADC3[32] = {999999};

      while (true) {

	if (subeventLoopCounter > eventDataSize-1) {
	  break;
	}

 	memcpy(&mySubeventHeader, &myEventContainer[subeventLoopCounter], sizeof(mySubeventHeader));

	
	if (mySubeventHeader.subeventMarker != hexMarkerSubevent) {
	  dqm_warning("Could not locate the correct subevent marker. The read subevent marker was: {0}",mySubeventHeader.subeventMarker);
	  break;
	}
	
	//dqm_debug("Before event type detection");

	if ( ((myEventContainer[subeventLoopCounter] >> 24) & 0x7) == 4) {
	  
	  for (int subeventChunk = 5; subeventChunk < (mySubeventHeader.subeventSize/4); subeventChunk++) {
	    if (mySubeventHeader.moduleID != 0x32026) {
	    }

	    //dqm_debug("Inside for loop over subevent");
	    if (mySubeventHeader.moduleID == hexMarkerTDC)  {
	      int thisChannel = (myEventContainer[subeventLoopCounter+subeventChunk] >> 17) & 0xF;
	      //dataTDC[thisChannel] = static_cast<int>(myEventContainer[subeventLoopCounter+subeventChunk] & 0xFFF);	    
	    }
	    if (mySubeventHeader.moduleID == hexMarkerAncl) {
	      int thisChannel = (myEventContainer[subeventLoopCounter+subeventChunk] >> 16) & 0x1F;
	      dataAncl[thisChannel] = static_cast<int>(myEventContainer[subeventLoopCounter+subeventChunk] & 0xFFF);	    
	    }
	    if (mySubeventHeader.moduleID == hexMarkerADC0) {
	      int thisChannel = (myEventContainer[subeventLoopCounter+subeventChunk] >> 16) & 0x1F;
	      dataADC0[thisChannel] = static_cast<int>(myEventContainer[subeventLoopCounter+subeventChunk] & 0xFFF);
	    }
	    if (mySubeventHeader.moduleID == hexMarkerADC1) {
	      int thisChannel = (myEventContainer[subeventLoopCounter+subeventChunk] >> 16) & 0x1F;
	      dataADC1[thisChannel] = static_cast<int>(myEventContainer[subeventLoopCounter+subeventChunk] & 0xFFF);
	    }
	    if (mySubeventHeader.moduleID == hexMarkerADC2) {
	      int thisChannel = (myEventContainer[subeventLoopCounter+subeventChunk] >> 16) & 0x1F;
	      dataADC2[thisChannel] = static_cast<int>(myEventContainer[subeventLoopCounter+subeventChunk] & 0xFFF);
	      //dqm_debug("Value of ADC2 here: {0}", myEventContainer[subeventLoopCounter+subeventChunk] & 0xFFF);
	    }
	    if (mySubeventHeader.moduleID == hexMarkerADC3) {
	      int thisChannel = (myEventContainer[subeventLoopCounter+subeventChunk] >> 16) & 0x1F;
	      dataADC3[thisChannel] = static_cast<int>(myEventContainer[subeventLoopCounter+subeventChunk] & 0xFFF);	    
	    }

	  }
 
	  /*
	  Global [?]	 
	    [Type]			= (buf[i] >> 24) & 0x7	  
	  DecodeV775 (TDC)
	    data			= (buf[i] & 0xFFF)
	    channel			= (buf[i] >> 17) & 0xF
	    valid			= (buf[i] >> 14) & 0x1 
	    overflow			= (buf[i] >> 12) & 0x1;
	    under threshold		= (buf[i] >> 13) & 0x1;	
	  DecodeV792AC (ADC)
	    data			= (buf[i] & 0xFFF);
	    channel			= (buf[i] >> 16) & 0x1F;
	    overflow			= (buf[i] >> 12) & 0x1;
	    under threshold		= (buf[i] >> 13) & 0x1;	 
	  DecodeV862
	    (same as V792AC)
	  */
	  
	}
	subeventLoopCounter += mySubeventHeader.subeventSize/4;
	
      }
      
      pEvent->setEventNumber(myEventHeader.eventNumber);

      //pEvent->setTimeStamp(core::time::asPoint(myEventHeader.tsec)); // Compiler says "ambiguous"

      std::vector<int> dataVecADC0;
      std::vector<int> dataVecADC1;
      std::vector<int> dataVecADC2;
      std::vector<int> dataVecADC3;
      std::vector<int> dataVecAncl;
      std::vector<int> dataVecTDC;

      dataVecADC0.assign(std::begin(dataADC0), std::end(dataADC0));
      dataVecADC1.assign(std::begin(dataADC1), std::end(dataADC1));
      dataVecADC2.assign(std::begin(dataADC2), std::end(dataADC2));
      dataVecADC3.assign(std::begin(dataADC3), std::end(dataADC3));
      dataVecAncl.assign(std::begin(dataAncl), std::end(dataAncl));
      dataVecTDC.assign( std::begin(dataTDC ), std::end(dataTDC ));

      /*for (int i = 0; i < 32; i++) {
	dqm_debug("Element {0} of the array is: {1}", i, dataADC2[i]);
	}*/

      pGenericEvent->setValues("ADC0", dataVecADC0);
      pGenericEvent->setValues("ADC1", dataVecADC1);
      pGenericEvent->setValues("ADC2", dataVecADC2);
      pGenericEvent->setValues("ADC3", dataVecADC3);
      pGenericEvent->setValues("Ancl", dataVecAncl);
      pGenericEvent->setValues("TDC",  dataVecTDC );

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
