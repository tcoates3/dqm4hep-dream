#################################################
# cmake file for building DQMDream package
# @author Ete Remi, DESY
# Copyright (c)
cmake_minimum_required( VERSION 2.6 FATAL_ERROR )
#################################################

# -------------------------------------------------
# project name
project( DQMDream )

# -------------------------------------------------
# Find DQM4hep package
find_package( DQM4hep REQUIRED )
dqm4hep_set_cxx_flags()

# -------------------------------------------------
# DQMDream as a DQM4hep package
dqm4hep_package( DQMDream
  MAJOR 0 MINOR 1 PATCH 0
  USES 
    [ROOT COMPONENTS Core Hist Rint HistPainter Graf Graf3d MathCore Net RIO Tree REQUIRED]
    [DQM4hep COMPONENTS DQMCore DQMNet DQMOnline REQUIRED]
    MySQL
)

# -------------------------------------------------
# build the DQMDream library
dqm4hep_add_package_library( DQMDream
  SOURCES source/src/plugins/*.cc
)

# -------------------------------------------------
# display some variables and write them to cache
dqm4hep_display_std_variables()
