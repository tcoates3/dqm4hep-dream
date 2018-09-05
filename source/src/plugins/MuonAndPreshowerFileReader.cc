/// \file MuonAndPreshowerFileReader.cc
/*
 ***
 *
 * MuonAndPreshowerFileReader.cc source template automatically generated by a class generator
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

// -- root headers
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TLeaf.h"

namespace dqm4hep {

  namespace core {

    /**
     *  @brief  MuonAndPreshowerFileReader class
     *          An example plugin for creating file readers
     */
    class MuonAndPreshowerFileReader : public EventReader {
    public:
      MuonAndPreshowerFileReader() = default;
      ~MuonAndPreshowerFileReader() override;
      MuonAndPreshowerFileReader(const MuonAndPreshowerFileReader&) = delete;
      MuonAndPreshowerFileReader& operator=(const MuonAndPreshowerFileReader&) = delete;

      core::StatusCode open(const std::string &fname) override;
      core::StatusCode skipNEvents(int nEvents) override;
      core::StatusCode runInfo(core::Run &run) override;
      core::StatusCode readNextEvent() override;
      core::StatusCode close() override;

      int nEntries = -1;
      int currentEventNum = -1;
      TFile *rootFile = new TFile;
      TTree *mainTree = new TTree;
      
    };
    
    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    MuonAndPreshowerFileReader::~MuonAndPreshowerFileReader() {
      dqm_debug("Inside destructor");

    }

    //-------------------------------------------------------------------------------------------------

    StatusCode MuonAndPreshowerFileReader::open(const std::string &fname) {
      dqm_debug("Inside open()");
      
      rootFile = new TFile(fname.c_str());
      mainTree = (TTree*)rootFile->Get("t1");

      nEntries = mainTree->GetEntries();
      if (nEntries == -1) {
	dqm_error("Could not determine the number of events in file {0}", fname);
	return STATUS_CODE_FAILURE;
      }
      currentEventNum = 0;
      mainTree->GetEvent(0);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode MuonAndPreshowerFileReader::skipNEvents(int nEvents) {
      dqm_debug("Inside skipNEvents()");

      currentEventNum += nEvents;

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode MuonAndPreshowerFileReader::runInfo(core::Run &run) {
      dqm_debug("Inside runInfo()");

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode MuonAndPreshowerFileReader::readNextEvent() {
      dqm_debug("Inside readNextEvent()");

      if (currentEventNum == nEntries-1) {
	dqm_info("Reached end of file");
	return STATUS_CODE_OUT_OF_RANGE;
      }

      EventPtr pEvent = GenericEvent::make_shared();
      GenericEvent *pGenericEvent = pEvent->getEvent<GenericEvent>();

      // Seeking to the correct event
      mainTree->GetEvent(currentEventNum);
      if (mainTree->GetBranch("Event")->GetLeaf("Event")->GetValue() != currentEventNum) {
	dqm_error("Event number mismatch");
	return STATUS_CODE_FAILURE;
      }

      int i_eventNum = mainTree->GetBranch("Event")->GetLeaf("Event")->GetValue();
      pEvent->setEventNumber(i_eventNum);

      int i_triggerTime = mainTree->GetBranch("trigger_time")->GetLeaf("trigger_time")->GetValue();
      pEvent->setTimeStamp(core::time::asPoint(i_triggerTime));

      std::vector<int> i_triggerOn;
      i_triggerOn.push_back(mainTree->GetBranch("trigger_is_on")->GetLeaf("trigger_is_on")->GetValue());
      pGenericEvent->setValues("triggerOn", i_triggerOn);
      std::vector<int> i_triggerEvent;
      i_triggerEvent.push_back(mainTree->GetBranch("trigger_event")->GetLeaf("trigger_event")->GetValue());
      pGenericEvent->setValues("triggerEvent", i_triggerEvent);
      
      std::vector<int> i_nGemHit;
      i_nGemHit.push_back(mainTree->GetBranch("nGemHit")->GetLeaf("nGemHit")->GetValue());
      pGenericEvent->setValues("nGemHit", i_nGemHit);

      std::vector<int> i_GemHit_nHit;
      i_GemHit_nHit.push_back(mainTree->GetBranch("GemHit_nHit")->GetLeaf("GemHit_nHit")->GetValue());
      pGenericEvent->setValues("GemHit_nHit", i_GemHit_nHit);

      std::vector<int> i_GemHit_apv;
      i_GemHit_apv.push_back(mainTree->GetBranch("GemHit_apv")->GetLeaf("GemHit_apv")->GetValue());
      pGenericEvent->setValues("GemHit_apv", i_GemHit_apv);

      std::vector<int> i_GemHit_plane;
      i_GemHit_plane.push_back(mainTree->GetBranch("GemHit_plane")->GetLeaf("GemHit_plane")->GetValue());
      pGenericEvent->setValues("GemHit_plane", i_GemHit_plane);

      std::vector<int> i_GemHit_view;
      i_GemHit_view.push_back(mainTree->GetBranch("GemHit_view")->GetLeaf("GemHit_view")->GetValue());
      pGenericEvent->setValues("GemHit_view", i_GemHit_view);

      std::vector<int> i_GemHit_sample;
      i_GemHit_sample.push_back(mainTree->GetBranch("GemHit_sample")->GetLeaf("GemHit_sample")->GetValue());
      pGenericEvent->setValues("GemHit_sample", i_GemHit_sample);

      std::vector<int> i_GemHit_strip;
      i_GemHit_strip.push_back(mainTree->GetBranch("GemHit_strip")->GetLeaf("GemHit_strip")->GetValue());
      pGenericEvent->setValues("GemHit_strip", i_GemHit_strip);

      std::vector<int> i_GemHit_q;
      i_GemHit_q.push_back(mainTree->GetBranch("GemHit_q")->GetLeaf("GemHit_q")->GetValue());
      pGenericEvent->setValues("GemHit_q", i_GemHit_q);

      std::vector<int> i_GemHit_qtot;
      i_GemHit_qtot.push_back(mainTree->GetBranch("GemHit_qtot")->GetLeaf("GemHit_qtot")->GetValue());
      pGenericEvent->setValues("GemHit_qtot", i_GemHit_qtot);

      std::vector<int> i_GemHit_qraw;
      i_GemHit_qraw.push_back(mainTree->GetBranch("GemHit_qraw")->GetLeaf("GemHit_qraw")->GetValue());
      pGenericEvent->setValues("GemHit_qraw", i_GemHit_qraw);

      std::vector<double> d_GemHit_x;
      d_GemHit_x.push_back(mainTree->GetBranch("GemHit_x")->GetLeaf("GemHit_x")->GetValue());
      pGenericEvent->setValues("GemHit_x", d_GemHit_x);

      std::vector<double> d_GemHit_pos;
      d_GemHit_pos.push_back(mainTree->GetBranch("GemHit_pos")->GetLeaf("GemHit_pos")->GetValue());
      pGenericEvent->setValues("GemHit_pos", d_GemHit_pos);

      std::vector<double> d_GemHit_z;
      d_GemHit_z.push_back(mainTree->GetBranch("GemHit_z")->GetLeaf("GemHit_z")->GetValue());
      pGenericEvent->setValues("GemHit_z", d_GemHit_z);

      std::vector<double> d_GemHit_tFD;
      d_GemHit_tFD.push_back(mainTree->GetBranch("GemHit_tFD")->GetLeaf("GemHit_tFD")->GetValue());
      pGenericEvent->setValues("GemHit_tFD", d_GemHit_tFD);

      std::vector<double> d_GemHit_tFD_trigger;
      d_GemHit_tFD_trigger.push_back(mainTree->GetBranch("GemHit_tFD_trigger")->GetLeaf("GemHit_tFD_trigger")->GetValue());
      pGenericEvent->setValues("GemHit_tFD_trigger", d_GemHit_tFD_trigger);

      std::vector<double> d_GemHit_tTHR;
      d_GemHit_tTHR.push_back(mainTree->GetBranch("GemHit_tTHR")->GetLeaf("GemHit_tTHR")->GetValue());
      pGenericEvent->setValues("GemHit_tTHR", d_GemHit_tTHR);

      std::vector<double> d_GemHit_dtFD;
      d_GemHit_dtFD.push_back(mainTree->GetBranch("GemHit_dtFD")->GetLeaf("GemHit_dtFD")->GetValue());
      pGenericEvent->setValues("GemHit_dtFD", d_GemHit_dtFD);

      std::vector<double> d_GemHit_x_tpc;
      d_GemHit_x_tpc.push_back(mainTree->GetBranch("GemHit_x_tpc")->GetLeaf("GemHit_x_tpc")->GetValue());
      pGenericEvent->setValues("GemHit_x_tpc", d_GemHit_x_tpc);

      std::vector<double> d_GemHit_z_tpc;
      d_GemHit_z_tpc.push_back(mainTree->GetBranch("GemHit_z_tpc")->GetLeaf("GemHit_z_tpc")->GetValue());
      pGenericEvent->setValues("GemHit_z_tpc", d_GemHit_z_tpc);

      std::vector<double> d_GemHit_dx_tpc;
      d_GemHit_dx_tpc.push_back(mainTree->GetBranch("GemHit_dx_tpc")->GetLeaf("GemHit_dx_tpc")->GetValue());
      pGenericEvent->setValues("GemHit_dx_tpc", d_GemHit_dx_tpc);

      std::vector<double> d_GemHit_dz_tpc;
      d_GemHit_dz_tpc.push_back(mainTree->GetBranch("GemHit_dz_tpc")->GetLeaf("GemHit_dz_tpc")->GetValue());
      pGenericEvent->setValues("GemHit_dz_tpc", d_GemHit_dz_tpc);

      std::vector<double> d_GemHit_fd_fit0;
      d_GemHit_fd_fit0.push_back(mainTree->GetBranch("GemHit_fd_fit0")->GetLeaf("GemHit_fd_fit0")->GetValue());
      pGenericEvent->setValues("GemHit_fd_fit0", d_GemHit_fd_fit0);

      std::vector<double> d_GemHit_fd_fit1;
      d_GemHit_fd_fit1.push_back(mainTree->GetBranch("GemHit_fd_fit1")->GetLeaf("GemHit_fd_fit1")->GetValue());
      pGenericEvent->setValues("GemHit_fd_fit1", d_GemHit_fd_fit1);

      std::vector<double> d_GemHit_fd_fit2;
      d_GemHit_fd_fit2.push_back(mainTree->GetBranch("GemHit_fd_fit2")->GetLeaf("GemHit_fd_fit2")->GetValue());
      pGenericEvent->setValues("GemHit_fd_fit2", d_GemHit_fd_fit2);

      std::vector<double> d_GemHit_fd_fit3;
      d_GemHit_fd_fit3.push_back(mainTree->GetBranch("GemHit_fd_fit3")->GetLeaf("GemHit_fd_fit3")->GetValue());
      pGenericEvent->setValues("GemHit_fd_fit3", d_GemHit_fd_fit3);

      std::vector<double> d_GemHit_fd_fitlimlow0;
      d_GemHit_fd_fitlimlow0.push_back(mainTree->GetBranch("GemHit_fd_fitlimlow0")->GetLeaf("GemHit_fd_fitlimlow0")->GetValue());
      pGenericEvent->setValues("GemHit_fd_fitlimlow0", d_GemHit_fd_fitlimlow0);

      std::vector<double> d_GemHit_fd_fitlimlow1;
      d_GemHit_fd_fitlimlow1.push_back(mainTree->GetBranch("GemHit_fd_fitlimlow1")->GetLeaf("GemHit_fd_fitlimlow1")->GetValue());
      pGenericEvent->setValues("GemHit_fd_fitlimlow1", d_GemHit_fd_fitlimlow1);

      std::vector<double> d_GemHit_fd_fitlimlow2;
      d_GemHit_fd_fitlimlow2.push_back(mainTree->GetBranch("GemHit_fd_fitlimlow2")->GetLeaf("GemHit_fd_fitlimlow2")->GetValue());
      pGenericEvent->setValues("GemHit_fd_fitlimlow2", d_GemHit_fd_fitlimlow2);

      std::vector<double> d_GemHit_fd_fitlimlow3;
      d_GemHit_fd_fitlimlow3.push_back(mainTree->GetBranch("GemHit_fd_fitlimlow3")->GetLeaf("GemHit_fd_fitlimlow3")->GetValue());
      pGenericEvent->setValues("GemHit_fd_fitlimlow3", d_GemHit_fd_fitlimlow3);

      std::vector<double> d_GemHit_fd_fitlimup0;
      d_GemHit_fd_fitlimup0.push_back(mainTree->GetBranch("GemHit_fd_fitlimup0")->GetLeaf("GemHit_fd_fitlimup0")->GetValue());
      pGenericEvent->setValues("GemHit_fd_fitlimup0", d_GemHit_fd_fitlimup0);

      std::vector<double> d_GemHit_fd_fitlimup1;
      d_GemHit_fd_fitlimup1.push_back(mainTree->GetBranch("GemHit_fd_fitlimup1")->GetLeaf("GemHit_fd_fitlimup1")->GetValue());
      pGenericEvent->setValues("GemHit_fd_fitlimup1", d_GemHit_fd_fitlimup1);

      std::vector<double> d_GemHit_fd_fitlimup2;
      d_GemHit_fd_fitlimup2.push_back(mainTree->GetBranch("GemHit_fd_fitlimup2")->GetLeaf("GemHit_fd_fitlimup2")->GetValue());
      pGenericEvent->setValues("GemHit_fd_fitlimup2", d_GemHit_fd_fitlimup2);

      std::vector<double> d_GemHit_fd_fitlimup3;
      d_GemHit_fd_fitlimup3.push_back(mainTree->GetBranch("GemHit_fd_fitlimup3")->GetLeaf("GemHit_fd_fitlimup3")->GetValue());
      pGenericEvent->setValues("GemHit_fd_fitlimup3", d_GemHit_fd_fitlimup3);

      std::vector<double> d_GemHit_lin_m;
      d_GemHit_lin_m.push_back(mainTree->GetBranch("GemHit_lin_m")->GetLeaf("GemHit_lin_m")->GetValue());
      pGenericEvent->setValues("GemHit_lin_m", d_GemHit_lin_m);

      std::vector<double> d_GemHit_lin_q;
      d_GemHit_lin_q.push_back(mainTree->GetBranch("GemHit_lin_q")->GetLeaf("GemHit_lin_q")->GetValue());
      pGenericEvent->setValues("GemHit_lin_q", d_GemHit_lin_q);

      std::vector<double> d_GemHit_lin_chi2;
      d_GemHit_lin_chi2.push_back(mainTree->GetBranch("GemHit_lin_chi2")->GetLeaf("GemHit_lin_chi2")->GetValue());
      pGenericEvent->setValues("GemHit_lin_chi2", d_GemHit_lin_chi2);

      std::vector<int> i_GemHit_lin_nHit;
      i_GemHit_lin_nHit.push_back(mainTree->GetBranch("GemHit_lin_nHit")->GetLeaf("GemHit_lin_nHit")->GetValue());
      pGenericEvent->setValues("GemHit_lin_nHit", i_GemHit_lin_nHit);

      std::vector<int> i_GemHit_linear_fit; // Should be a boolean, but no booleans are allowed in GenericEvents
      i_GemHit_linear_fit.push_back(mainTree->GetBranch("GemHit_linear_fit")->GetLeaf("GemHit_linear_fit")->GetValue());
      pGenericEvent->setValues("GemHit_linear_fit", i_GemHit_linear_fit);

      std::vector<double> d_GemHit_deltaX;
      d_GemHit_deltaX.push_back(mainTree->GetBranch("GemHit_deltaX")->GetLeaf("GemHit_deltaX")->GetValue());
      pGenericEvent->setValues("GemHit_deltaX", d_GemHit_deltaX);

      std::vector<double> d_GemHit_deltaZ;
      d_GemHit_deltaZ.push_back(mainTree->GetBranch("GemHit_deltaZ")->GetLeaf("GemHit_deltaZ")->GetValue());
      pGenericEvent->setValues("GemHit_deltaZ", d_GemHit_deltaZ);

      std::vector<int> i_GemHit_is_tpc; // Should be a boolean, but no booleans are allowed in GenericEvents
      i_GemHit_is_tpc.push_back(mainTree->GetBranch("GemHit_is_tpc")->GetLeaf("GemHit_is_tpc")->GetValue());
      pGenericEvent->setValues("GemHit_is_tpc", i_GemHit_is_tpc);

      std::vector<int> i_GemHit_utpc_goodHit; // Should be a boolean, but no booleans are allowed in GenericEvents
      i_GemHit_utpc_goodHit.push_back(mainTree->GetBranch("GemHit_utpc_goodHit")->GetLeaf("GemHit_utpc_goodHit")->GetValue());
      pGenericEvent->setValues("GemHit_utpc_goodHit", i_GemHit_utpc_goodHit);

      std::vector<int> i_nGemCluster;
      i_nGemCluster.push_back(mainTree->GetBranch("nGemCluster")->GetLeaf("nGemCluster")->GetValue());
      pGenericEvent->setValues("nGemCluster", i_nGemCluster);

      std::vector<int> i_GemCluster1d_nCluster;
      i_GemCluster1d_nCluster.push_back(mainTree->GetBranch("GemCluster1d_nCluster")->GetLeaf("GemCluster1d_nCluster")->GetValue());
      pGenericEvent->setValues("GemCluster1d_nCluster", i_GemCluster1d_nCluster);

      std::vector<int> i_GemCluster1d_plane;
      i_GemCluster1d_plane.push_back(mainTree->GetBranch("GemCluster1d_plane")->GetLeaf("GemCluster1d_plane")->GetValue());
      pGenericEvent->setValues("GemCluster1d_plane", i_GemCluster1d_plane);

      std::vector<int> i_GemCluster1d_view;
      i_GemCluster1d_view.push_back(mainTree->GetBranch("GemCluster1d_view")->GetLeaf("GemCluster1d_view")->GetValue());
      pGenericEvent->setValues("GemCluster1d_view", i_GemCluster1d_view);

      std::vector<int> i_GemCluster1d_q;
      i_GemCluster1d_q.push_back(mainTree->GetBranch("GemCluster1d_q")->GetLeaf("GemCluster1d_q")->GetValue());
      pGenericEvent->setValues("GemCluster1d_q", i_GemCluster1d_q);

      std::vector<double> d_GemCluster1d_x;
      d_GemCluster1d_x.push_back(mainTree->GetBranch("GemCluster1d_x")->GetLeaf("GemCluster1d_x")->GetValue());
      pGenericEvent->setValues("GemCluster1d_x", d_GemCluster1d_x);

      std::vector<double> d_GemCluster1d_z;
      d_GemCluster1d_z.push_back(mainTree->GetBranch("GemCluster1d_z")->GetLeaf("GemCluster1d_z")->GetValue());
      pGenericEvent->setValues("GemCluster1d_z", d_GemCluster1d_z);

      std::vector<double> d_GemCluster1d_pos;
      d_GemCluster1d_pos.push_back(mainTree->GetBranch("GemCluster1d_pos")->GetLeaf("GemCluster1d_pos")->GetValue());
      pGenericEvent->setValues("GemCluster1d_pos", d_GemCluster1d_pos);

      std::vector<double> d_GemCluster1d_dx;
      d_GemCluster1d_dx.push_back(mainTree->GetBranch("GemCluster1d_dx")->GetLeaf("GemCluster1d_dx")->GetValue());
      pGenericEvent->setValues("GemCluster1d_dx", d_GemCluster1d_dx);

      std::vector<double> d_GemCluster1d_dz;
      d_GemCluster1d_dz.push_back(mainTree->GetBranch("GemCluster1d_dz")->GetLeaf("GemCluster1d_dz")->GetValue());
      pGenericEvent->setValues("GemCluster1d_dz", d_GemCluster1d_dz);

      std::vector<double> d_GemCluster1d_x_cc;
      d_GemCluster1d_x_cc.push_back(mainTree->GetBranch("GemCluster1d_x_cc")->GetLeaf("GemCluster1d_x_cc")->GetValue());
      pGenericEvent->setValues("GemCluster1d_x_cc", d_GemCluster1d_x_cc);

      std::vector<double> d_GemCluster1d_z_cc;
      d_GemCluster1d_z_cc.push_back(mainTree->GetBranch("GemCluster1d_z_cc")->GetLeaf("GemCluster1d_z_cc")->GetValue());
      pGenericEvent->setValues("GemCluster1d_z_cc", d_GemCluster1d_z_cc);

      std::vector<double> d_GemCluster1d_dx_cc;
      d_GemCluster1d_dx_cc.push_back(mainTree->GetBranch("GemCluster1d_dx_cc")->GetLeaf("GemCluster1d_dx_cc")->GetValue());
      pGenericEvent->setValues("GemCluster1d_dx_cc", d_GemCluster1d_dx_cc);

      std::vector<double> d_GemCluster1d_dz_cc;
      d_GemCluster1d_dz_cc.push_back(mainTree->GetBranch("GemCluster1d_dz_cc")->GetLeaf("GemCluster1d_dz_cc")->GetValue());
      pGenericEvent->setValues("GemCluster1d_dz_cc", d_GemCluster1d_dz_cc);

      std::vector<double> d_GemCluster1d_t0_tpc;
      d_GemCluster1d_t0_tpc.push_back(mainTree->GetBranch("GemCluster1d_t0_tpc")->GetLeaf("GemCluster1d_t0_tpc")->GetValue());
      pGenericEvent->setValues("GemCluster1d_t0_tpc", d_GemCluster1d_t0_tpc);

      std::vector<double> d_GemCluster1d_tF_tpc;
      d_GemCluster1d_tF_tpc.push_back(mainTree->GetBranch("GemCluster1d_tF_tpc")->GetLeaf("GemCluster1d_tF_tpc")->GetValue());
      pGenericEvent->setValues("GemCluster1d_tF_tpc", d_GemCluster1d_tF_tpc);

      std::vector<double> d_GemCluster1d_t0_tpc_THR;
      d_GemCluster1d_t0_tpc_THR.push_back(mainTree->GetBranch("GemCluster1d_t0_tpc_THR")->GetLeaf("GemCluster1d_t0_tpc_THR")->GetValue());
      pGenericEvent->setValues("GemCluster1d_t0_tpc_THR", d_GemCluster1d_t0_tpc_THR);

      std::vector<double> d_GemCluster1d_x_tpc;
      d_GemCluster1d_x_tpc.push_back(mainTree->GetBranch("GemCluster1d_x_tpc")->GetLeaf("GemCluster1d_x_tpc")->GetValue());
      pGenericEvent->setValues("GemCluster1d_x_tpc", d_GemCluster1d_x_tpc);

      std::vector<double> d_GemCluster1d_x_tpc_trigger;
      d_GemCluster1d_x_tpc_trigger.push_back(mainTree->GetBranch("GemCluster1d_x_tpc_trigger")->GetLeaf("GemCluster1d_x_tpc_trigger")->GetValue());
      pGenericEvent->setValues("GemCluster1d_x_tpc_trigger", d_GemCluster1d_x_tpc_trigger);

      std::vector<double> d_GemCluster1d_z_tpc;
      d_GemCluster1d_z_tpc.push_back(mainTree->GetBranch("GemCluster1d_z_tpc")->GetLeaf("GemCluster1d_z_tpc")->GetValue());
      pGenericEvent->setValues("GemCluster1d_z_tpc", d_GemCluster1d_z_tpc);

      std::vector<double> d_GemCluster1d_z_tpc_trigger;
      d_GemCluster1d_z_tpc_trigger.push_back(mainTree->GetBranch("GemCluster1d_z_tpc_trigger")->GetLeaf("GemCluster1d_z_tpc_trigger")->GetValue());
      pGenericEvent->setValues("GemCluster1d_z_tpc_trigger", d_GemCluster1d_z_tpc_trigger);

      std::vector<double> d_GemCluster1d_dx_tpc;
      d_GemCluster1d_dx_tpc.push_back(mainTree->GetBranch("GemCluster1d_dx_tpc")->GetLeaf("GemCluster1d_dx_tpc")->GetValue());
      pGenericEvent->setValues("GemCluster1d_dx_tpc", d_GemCluster1d_dx_tpc);

      std::vector<double> d_GemCluster1d_dz_tpc;
      d_GemCluster1d_dz_tpc.push_back(mainTree->GetBranch("GemCluster1d_dz_tpc")->GetLeaf("GemCluster1d_dz_tpc")->GetValue());
      pGenericEvent->setValues("GemCluster1d_dz_tpc", d_GemCluster1d_dz_tpc);

      std::vector<double> d_GemCluster1d_q_tpc;
      d_GemCluster1d_q_tpc.push_back(mainTree->GetBranch("GemCluster1d_q_tpc")->GetLeaf("GemCluster1d_q_tpc")->GetValue());
      pGenericEvent->setValues("GemCluster1d_q_tpc", d_GemCluster1d_q_tpc);

      std::vector<double> d_GemCluster1d_m_tpc;
      d_GemCluster1d_m_tpc.push_back(mainTree->GetBranch("GemCluster1d_m_tpc")->GetLeaf("GemCluster1d_m_tpc")->GetValue());
      pGenericEvent->setValues("GemCluster1d_m_tpc", d_GemCluster1d_m_tpc);

      std::vector<double> d_GemCluster1d_dq_tpc;
      d_GemCluster1d_dq_tpc.push_back(mainTree->GetBranch("GemCluster1d_dq_tpc")->GetLeaf("GemCluster1d_dq_tpc")->GetValue());
      pGenericEvent->setValues("GemCluster1d_dq_tpc", d_GemCluster1d_dq_tpc);

      std::vector<double> d_GemCluster1d_dm_tpc;
      d_GemCluster1d_dm_tpc.push_back(mainTree->GetBranch("GemCluster1d_dm_tpc")->GetLeaf("GemCluster1d_dm_tpc")->GetValue());
      pGenericEvent->setValues("GemCluster1d_dm_tpc", d_GemCluster1d_dm_tpc);

      std::vector<double> d_GemCluster1d_q0_tpc;
      d_GemCluster1d_q0_tpc.push_back(mainTree->GetBranch("GemCluster1d_q0_tpc")->GetLeaf("GemCluster1d_q0_tpc")->GetValue());
      pGenericEvent->setValues("GemCluster1d_q0_tpc", d_GemCluster1d_q0_tpc);

      std::vector<double> d_GemCluster1d_m0_tpc;
      d_GemCluster1d_m0_tpc.push_back(mainTree->GetBranch("GemCluster1d_m0_tpc")->GetLeaf("GemCluster1d_m0_tpc")->GetValue());
      pGenericEvent->setValues("GemCluster1d_m0_tpc", d_GemCluster1d_m0_tpc);

      std::vector<double> d_GemCluster1d_chi2_tpc;
      d_GemCluster1d_chi2_tpc.push_back(mainTree->GetBranch("GemCluster1d_chi2_tpc")->GetLeaf("GemCluster1d_chi2_tpc")->GetValue());
      pGenericEvent->setValues("GemCluster1d_chi2_tpc", d_GemCluster1d_chi2_tpc);

      std::vector<double> d_GemCluster1d_qt_tpc;
      d_GemCluster1d_qt_tpc.push_back(mainTree->GetBranch("GemCluster1d_qt_tpc")->GetLeaf("GemCluster1d_qt_tpc")->GetValue());
      pGenericEvent->setValues("GemCluster1d_qt_tpc", d_GemCluster1d_qt_tpc);

      std::vector<double> d_GemCluster1d_mt_tpc;
      d_GemCluster1d_mt_tpc.push_back(mainTree->GetBranch("GemCluster1d_mt_tpc")->GetLeaf("GemCluster1d_mt_tpc")->GetValue());
      pGenericEvent->setValues("GemCluster1d_mt_tpc", d_GemCluster1d_mt_tpc);

      std::vector<double> d_GemCluster1d_dqt_tpc;
      d_GemCluster1d_dqt_tpc.push_back(mainTree->GetBranch("GemCluster1d_dqt_tpc")->GetLeaf("GemCluster1d_dqt_tpc")->GetValue());
      pGenericEvent->setValues("GemCluster1d_dqt_tpc", d_GemCluster1d_dqt_tpc);

      std::vector<double> d_GemCluster1d_dmt_tpc;
      d_GemCluster1d_dmt_tpc.push_back(mainTree->GetBranch("GemCluster1d_dmt_tpc")->GetLeaf("GemCluster1d_dmt_tpc")->GetValue());
      pGenericEvent->setValues("GemCluster1d_dmt_tpc", d_GemCluster1d_dmt_tpc);

      std::vector<double> d_GemCluster1d_q0t_tpc;
      d_GemCluster1d_q0t_tpc.push_back(mainTree->GetBranch("GemCluster1d_q0t_tpc")->GetLeaf("GemCluster1d_q0t_tpc")->GetValue());
      pGenericEvent->setValues("GemCluster1d_q0t_tpc", d_GemCluster1d_q0t_tpc);

      std::vector<double> d_GemCluster1d_m0t_tpc;
      d_GemCluster1d_m0t_tpc.push_back(mainTree->GetBranch("GemCluster1d_m0t_tpc")->GetLeaf("GemCluster1d_m0t_tpc")->GetValue());
      pGenericEvent->setValues("GemCluster1d_m0t_tpc", d_GemCluster1d_m0t_tpc);

      std::vector<double> d_GemCluster1d_chi2t_tpc;
      d_GemCluster1d_chi2t_tpc.push_back(mainTree->GetBranch("GemCluster1d_chi2t_tpc")->GetLeaf("GemCluster1d_chi2t_tpc")->GetValue());
      pGenericEvent->setValues("GemCluster1d_chi2t_tpc", d_GemCluster1d_chi2t_tpc);

      std::vector<int> i_GemCluster1d_HitIndex; 
      i_GemCluster1d_HitIndex.push_back(mainTree->GetBranch("GemCluster1d_HitIndex")->GetLeaf("GemCluster1d_HitIndex")->GetValue());
      pGenericEvent->setValues("GemCluster1d_HitIndex", i_GemCluster1d_HitIndex);

      std::vector<int> i_GemCluster1d_HitIndex_tpc;
      i_GemCluster1d_HitIndex_tpc.push_back(mainTree->GetBranch("GemCluster1d_HitIndex_tpc")->GetLeaf("GemCluster1d_HitIndex_tpc")->GetValue());
      pGenericEvent->setValues("GemCluster1d_HitIndex_tpc", i_GemCluster1d_HitIndex_tpc);

      std::vector<int> i_GemCluster1d_nHit;
      i_GemCluster1d_nHit.push_back(mainTree->GetBranch("GemCluster1d_nHit")->GetLeaf("GemCluster1d_nHit")->GetValue());
      pGenericEvent->setValues("GemCluster1d_nHit", i_GemCluster1d_nHit);

      std::vector<int> i_GemCluster1d_nHit_tpc;
      i_GemCluster1d_nHit_tpc.push_back(mainTree->GetBranch("GemCluster1d_nHit_tpc")->GetLeaf("GemCluster1d_nHit_tpc")->GetValue());
      pGenericEvent->setValues("GemCluster1d_nHit_tpc", i_GemCluster1d_nHit_tpc);

      std::vector<int> i_GemCluster1d_is_tpc; // Should be a boolean, but no booleans are allowed in GenericEvents
      i_GemCluster1d_is_tpc.push_back(mainTree->GetBranch("GemCluster1d_is_tpc")->GetLeaf("GemCluster1d_is_tpc")->GetValue());
      pGenericEvent->setValues("GemCluster1d_is_tpc", i_GemCluster1d_is_tpc);

      std::vector<double> d_GemCluster1d_real_angle;
      d_GemCluster1d_real_angle.push_back(mainTree->GetBranch("GemCluster1d_real_angle")->GetLeaf("GemCluster1d_real_angle")->GetValue());
      pGenericEvent->setValues("GemCluster1d_real_angle", d_GemCluster1d_real_angle);

      onEventRead().emit(pEvent);
      currentEventNum++;

      return STATUS_CODE_SUCCESS;
    }
  

    StatusCode MuonAndPreshowerFileReader::close() {
      dqm_debug("Inside close()");
     
      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------
    
    DQM_PLUGIN_DECL(MuonAndPreshowerFileReader, "MuonAndPreshowerFileReader");
  }
}
