/// \file RD52MainModule.cc
/*
 *
 * RD52MainModule.cc source template automatically generated by a class generator
 * Creation date : 13 june 2018
 *
 * This file is part of dqm4hep-dream libraries.
 *
 * dqm4hep-dream is free software: you can redistribute it and/or modify
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
 * along with dqm4hep-dream.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @author Remi Ete
 * @author Tom Coates
 * @copyright 2018
 */

// -- dqm4hep headers
#include <dqm4hep/Internal.h>
#include <dqm4hep/StatusCodes.h>
#include <dqm4hep/GenericEvent.h>
#include <dqm4hep/RootHeaders.h>
#include <dqm4hep/Module.h>
#include "dqm4hep/PluginManager.h"
#include "dqm4hep/OnlineElement.h"
#include "dqm4hep/ModuleApi.h"

namespace dqm4hep {

  namespace dream {
    
    class RD52MainModule : public dqm4hep::online::AnalysisModule {
    public:
      RD52MainModule() = default;
      RD52MainModule(const RD52MainModule&) = delete;
      RD52MainModule& operator=(const RD52MainModule&) = delete;
      
    private:
      void readSettings(const core::TiXmlHandle &handle) override;
      void initModule() override;
      void startOfRun(core::Run &run) override;
      void startOfCycle() override;
      void endOfCycle(const online::EOCCondition &condition) override;
      void endOfRun(const core::Run &run) override;
      void endModule() override;
      void process(core::EventPtr event) override;
      
    private:

      std::vector<online::OnlineElementPtr> m_pChannelSpectra;
      std::vector<online::OnlineElementPtr> m_pLeakage;

      std::vector<online::OnlineElementPtr> m_pIT;
      std::vector<online::OnlineElementPtr> m_pT3_PSD;
      std::vector<online::OnlineElementPtr> m_pTC;
      std::vector<online::OnlineElementPtr> m_pMu;

    };
    
    //-------------------------------------------------------------------------------------------------
    
    void RD52MainModule::readSettings(const core::TiXmlHandle &xmlHandle) {

    }
    
    //-------------------------------------------------------------------------------------------------
    
    void RD52MainModule::initModule() {
      
      for (int i=0; i<72; i++) {
        std::string meName = "SpectrumCh" + std::to_string(i);
        m_pChannelSpectra.push_back(online::ModuleApi::getMonitorElement(this, "/", meName));
      }

      for (int i=0; i<16; i++) {
        std::string meName = "Leakage" + std::to_string(i);
        m_pLeakage.push_back(online::ModuleApi::getMonitorElement(this, "/", meName));
      }
      

      /*
      m_pIT.push_back(online::ModuleApi::getMonitorElement(this, "/", "IT"));
      m_pT3_PSD.push_back(online::ModuleApi::getMonitorElement(this, "/", "T3-PSD"));
      m_pTC.push_back(online::ModuleApi::getMonitorElement(this, "/", "TC"));
      m_pMu.push_back(online::ModuleApi::getMonitorElement(this, "/", "mu"));
      */
    }
    
    //-------------------------------------------------------------------------------------------------
    
    void RD52MainModule::startOfRun(core::Run &/*run*/) {

    }
    
    //-------------------------------------------------------------------------------------------------
    
    void RD52MainModule::startOfCycle() {

    }
    
    //-------------------------------------------------------------------------------------------------
    
    void RD52MainModule::endOfCycle(const online::EOCCondition &/*condition*/) {

    }
    
    //-------------------------------------------------------------------------------------------------
    
    void RD52MainModule::endOfRun(const core::Run &/*run*/) {

    }
    
    //-------------------------------------------------------------------------------------------------
    
    void RD52MainModule::endModule() {

    }
    
    //-------------------------------------------------------------------------------------------------

    void RD52MainModule::process(core::EventPtr pEvent) {
      //dqm_debug("Inside module process");

      if (nullptr == pEvent) {
	dqm_warning("Event pointer is invalid - skipping this event");
	return;
      }

      std::vector<int> eventADC0;
      std::vector<int> eventADC1;
      std::vector<int> eventADC2;
      std::vector<int> eventADC3;
      std::vector<int> eventAncl;
      std::vector<int> eventTDC;
      
      core::GenericEvent *pGenericEvent = pEvent->getEvent<core::GenericEvent>();
      
      pGenericEvent->getValues("ADC0", eventADC0);
      pGenericEvent->getValues("ADC1", eventADC1);
      pGenericEvent->getValues("ADC2", eventADC2);
      pGenericEvent->getValues("ADC3", eventADC3);
      pGenericEvent->getValues("Ancl", eventAncl);
      pGenericEvent->getValues("TDC",  eventTDC);

      dqm_debug("0th element in vector: {0}", eventADC2[0]);
      //dqm_debug("0th element in vector: {0}", eventADC3[0]);
      //dqm_debug("0th element in vector: {0}", eventAncl[0]);


      for (int i=0; i<32; i++) {
	m_pChannelSpectra[i]->objectTo<TH1I>()->Fill(eventADC0[i]);
      }

      for (int i=0; i<32; i++) {
	m_pChannelSpectra[32+i]->objectTo<TH1I>()->Fill(eventADC1[i]);
      }
      /*
      for (int i=0; i<9; i++) {
	m_pChannelSpectra[64+i]->objectTo<TH1I>()->Fill(eventADC2[i]);
      }
      */
      /*
      for (int i=0; i<9; i++) {
	m_pSpectraADC2[i]->objectTo<TH1I>()->Fill(eventADC2[i]);
      }
      */

      /*
      int k = 0;
      for (int i=16; i<32; i++) {
	m_pLeakage[k]->objectTo<TH1I>()->Fill(eventADC3[i]);
	k++;
      }
      */
      /*
      m_pLeakage[17]->objectTo<TH1I>()->Fill(eventADC4[0]);
      m_pLeakage[18]->objectTo<TH1I>()->Fill(eventADC4[1]);
      m_pLeakage[19]->objectTo<TH1I>()->Fill(eventADC4[2]);
      m_pLeakage[20]->objectTo<TH1I>()->Fill(eventADC4[3]);

      m_pIT[0]->objectTo<TH1I>()->Fill(eventADC4[8]);
      m_pT3_PSD[0]->objectTo<TH1I>()->Fill(eventADC4[9]);
      m_pTC[0]->objectTo<TH1I>()->Fill(eventADC4[10]);
      m_pMu[0]->objectTo<TH1I>()->Fill(eventADC4[11]);
      */
      
      //dqm_debug("Completed module");

    }
    
    DQM_PLUGIN_DECL(RD52MainModule, "RD52MainModule");
    
  }
  

}
