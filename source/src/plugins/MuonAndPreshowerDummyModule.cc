/// \file MuonAndPreshowerDummyModule.cc
/*
 *
 * MuonAndPreshowerDummyModule.cc source template automatically generated by a class generator
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
#include <dqm4hep/OnlineElement.h>
#include "dqm4hep/ModuleApi.h"


namespace dqm4hep {

  namespace dream {
    
    class MuonAndPreshowerDummyModule : public dqm4hep::online::AnalysisModule {
    public:
      MuonAndPreshowerDummyModule() = default;
      MuonAndPreshowerDummyModule(const MuonAndPreshowerDummyModule&) = delete;
      MuonAndPreshowerDummyModule& operator=(const MuonAndPreshowerDummyModule&) = delete;
      
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
      online::OnlineElementPtr m_px1 = {nullptr};
      online::OnlineElementPtr m_pqx1 = {nullptr};
      online::OnlineElementPtr m_pnHitx1 = {nullptr};
      online::OnlineElementPtr m_px2 = {nullptr};
      online::OnlineElementPtr m_pqx2 = {nullptr};
      online::OnlineElementPtr m_pnHitx2 = {nullptr};
      online::OnlineElementPtr m_px3 = {nullptr};
      online::OnlineElementPtr m_pqx3 = {nullptr};
      online::OnlineElementPtr m_pnHitx3 = {nullptr};
      online::OnlineElementPtr m_px4 = {nullptr};
      online::OnlineElementPtr m_pqx4 = {nullptr};
      online::OnlineElementPtr m_pnHitx4 = {nullptr};
      online::OnlineElementPtr m_py1 = {nullptr};
      online::OnlineElementPtr m_pqy1 = {nullptr};
      online::OnlineElementPtr m_pnHity1 = {nullptr};
      online::OnlineElementPtr m_py2 = {nullptr};
      online::OnlineElementPtr m_pqy2 = {nullptr};
      online::OnlineElementPtr m_pnHity2 = {nullptr};
      online::OnlineElementPtr m_py3 = {nullptr};
      online::OnlineElementPtr m_pqy3 = {nullptr};
      online::OnlineElementPtr m_pnHity3 = {nullptr};
      online::OnlineElementPtr m_py4 = {nullptr};
      online::OnlineElementPtr m_pqy4 = {nullptr};
      online::OnlineElementPtr m_pnHity4 = {nullptr};

    };
    
    //-------------------------------------------------------------------------------------------------
    
    void MuonAndPreshowerDummyModule::readSettings(const core::TiXmlHandle &/*handle*/) {

    }
    
    //-------------------------------------------------------------------------------------------------
    
    void MuonAndPreshowerDummyModule::initModule() {

      m_px1 = online::ModuleApi::getMonitorElement(this, "/", "x1");
      m_pqx1 = online::ModuleApi::getMonitorElement(this, "/", "qx1");
      m_pnHitx1 = online::ModuleApi::getMonitorElement(this, "/", "nHitx1");
      m_px2 = online::ModuleApi::getMonitorElement(this, "/", "x2");
      m_pqx2 = online::ModuleApi::getMonitorElement(this, "/", "qx1");
      m_pnHitx2 = online::ModuleApi::getMonitorElement(this, "/", "nHitx2");
      m_px3 = online::ModuleApi::getMonitorElement(this, "/", "x3");
      m_pqx3 = online::ModuleApi::getMonitorElement(this, "/", "qx3");
      m_pnHitx3 = online::ModuleApi::getMonitorElement(this, "/", "nHitx3");
      m_px4 = online::ModuleApi::getMonitorElement(this, "/", "x4");
      m_pqx4 = online::ModuleApi::getMonitorElement(this, "/", "qx4");
      m_pnHitx4 = online::ModuleApi::getMonitorElement(this, "/", "nHitx4");
      m_py1 = online::ModuleApi::getMonitorElement(this, "/", "y1");
      m_pqy1 = online::ModuleApi::getMonitorElement(this, "/", "qy1");
      m_pnHity1 = online::ModuleApi::getMonitorElement(this, "/", "nHity1");
      m_py2 = online::ModuleApi::getMonitorElement(this, "/", "y2");
      m_pqy2 = online::ModuleApi::getMonitorElement(this, "/", "qy2");
      m_pnHity2 = online::ModuleApi::getMonitorElement(this, "/", "nHity2");
      m_py3 = online::ModuleApi::getMonitorElement(this, "/", "y3");
      m_pqy3 = online::ModuleApi::getMonitorElement(this, "/", "qy3");
      m_pnHity3 = online::ModuleApi::getMonitorElement(this, "/", "nHity3");
      m_py4 = online::ModuleApi::getMonitorElement(this, "/", "y4");
      m_pqy4 = online::ModuleApi::getMonitorElement(this, "/", "qy4");
      m_pnHity4 = online::ModuleApi::getMonitorElement(this, "/", "nHity4");

    }
    
    //-------------------------------------------------------------------------------------------------
    
    void MuonAndPreshowerDummyModule::startOfRun(core::Run &/*run*/) {

    }
    
    //-------------------------------------------------------------------------------------------------
    
    void MuonAndPreshowerDummyModule::startOfCycle() {

    }
    
    //-------------------------------------------------------------------------------------------------
    
    void MuonAndPreshowerDummyModule::endOfCycle(const online::EOCCondition &/*condition*/) {

    }
    
    //-------------------------------------------------------------------------------------------------
    
    void MuonAndPreshowerDummyModule::endOfRun(const core::Run &/*run*/) {

    }
    
    //-------------------------------------------------------------------------------------------------
    
    void MuonAndPreshowerDummyModule::endModule() {

    }
    
    //-------------------------------------------------------------------------------------------------

    void MuonAndPreshowerDummyModule::process(core::EventPtr pEvent) {

      if(nullptr == pEvent) {
        dqm_warning("Event pointer is invalid - skipping this event");
        return;
      }
      
      core::GenericEvent *pGenericEvent = pEvent->getEvent<core::GenericEvent>();

      std::vector<double> vGemCluster1d_x_cc;
      std::vector<int> vGemCluster1d_q;
      std::vector<int> vGemCluster1d_nHit;

      std::vector<int> vGemCluster1d_view;
      std::vector<int> vGemCluster1d_plane;

      pGenericEvent->getValues("GemCluster1d_x_cc", vGemCluster1d_x_cc);
      pGenericEvent->getValues("GemCluster1d_q", vGemCluster1d_q);
      pGenericEvent->getValues("GemCluster1d_nHit", vGemCluster1d_nHit);
      pGenericEvent->getValues("GemCluster1d_view", vGemCluster1d_view);
      pGenericEvent->getValues("GemCluster1d_plane", vGemCluster1d_plane);

      if (vGemCluster1d_q[0] > 400) {

	if (vGemCluster1d_view[0] == 0) {
	  if (vGemCluster1d_plane[0] == 0) {
	    m_px1->objectTo<TH1D>()->Fill(vGemCluster1d_x_cc[0]);
	    m_pqx1->objectTo<TH1D>()->Fill(vGemCluster1d_q[0]);
	    m_pnHitx1->objectTo<TH1D>()->Fill(vGemCluster1d_nHit[0]);
	  }
	  if (vGemCluster1d_plane[0] == 1) {
	    m_px2->objectTo<TH1D>()->Fill(vGemCluster1d_x_cc[0]);
	    m_pqx2->objectTo<TH1D>()->Fill(vGemCluster1d_q[0]);
	    m_pnHitx2->objectTo<TH1D>()->Fill(vGemCluster1d_nHit[0]);
	  }
	  if (vGemCluster1d_plane[0] == 2) {
	    m_px3->objectTo<TH1D>()->Fill(vGemCluster1d_x_cc[0]);
	    m_pqx3->objectTo<TH1D>()->Fill(vGemCluster1d_q[0]);
	    m_pnHitx3->objectTo<TH1D>()->Fill(vGemCluster1d_nHit[0]);
	  }
	  if (vGemCluster1d_plane[0] == 3) {
	    m_px4->objectTo<TH1D>()->Fill(vGemCluster1d_x_cc[0]);
	    m_pqx4->objectTo<TH1D>()->Fill(vGemCluster1d_q[0]);
	    m_pnHitx4->objectTo<TH1D>()->Fill(vGemCluster1d_nHit[0]);
	  }
	}

	if (vGemCluster1d_view[0] == 1) {
	  if (vGemCluster1d_plane[0] == 0) {
	    m_py1->objectTo<TH1D>()->Fill(vGemCluster1d_x_cc[0]);
	    m_pqy1->objectTo<TH1D>()->Fill(vGemCluster1d_q[0]);
	    m_pnHity1->objectTo<TH1D>()->Fill(vGemCluster1d_nHit[0]);
	  }
	  if (vGemCluster1d_plane[0] == 1) {
	    m_py2->objectTo<TH1D>()->Fill(vGemCluster1d_x_cc[0]);
	    m_pqy2->objectTo<TH1D>()->Fill(vGemCluster1d_q[0]);
	    m_pnHity2->objectTo<TH1D>()->Fill(vGemCluster1d_nHit[0]);
	  }
	  if (vGemCluster1d_plane[0] == 2) {
	    m_py3->objectTo<TH1D>()->Fill(vGemCluster1d_x_cc[0]);
	    m_pqy3->objectTo<TH1D>()->Fill(vGemCluster1d_q[0]);
	    m_pnHity3->objectTo<TH1D>()->Fill(vGemCluster1d_nHit[0]);
	  }
	  if (vGemCluster1d_plane[0] == 3) {
	    m_py4->objectTo<TH1D>()->Fill(vGemCluster1d_x_cc[0]);
	    m_pqy4->objectTo<TH1D>()->Fill(vGemCluster1d_q[0]);
	    m_pnHity4->objectTo<TH1D>()->Fill(vGemCluster1d_nHit[0]);
	  }
	}


      }


    }
    
    DQM_PLUGIN_DECL(MuonAndPreshowerDummyModule, "MuonAndPreshowerDummyModule");
    
  }
  
}
