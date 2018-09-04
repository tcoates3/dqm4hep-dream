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
#include <dqm4hep/RootHeaders.h>
#include <dqm4hep/Module.h>
#include "dqm4hep/PluginManager.h"

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
      // your monitor elements here !
    };
    
    //-------------------------------------------------------------------------------------------------
    
    void MuonAndPreshowerDummyModule::readSettings(const core::TiXmlHandle &/*handle*/) {

    }
    
    //-------------------------------------------------------------------------------------------------
    
    void MuonAndPreshowerDummyModule::initModule() {

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

    void MuonAndPreshowerDummyModule::process(core::EventPtr /*event*/) {

    }
    
    DQM_PLUGIN_DECL(MuonAndPreshowerDummyModule, "MuonAndPreshowerDummyModule");
    
  }
  
}
