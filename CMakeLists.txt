#################################################
# cmake file for building DQMDream package
# @author Ete Remi, DESY
# Copyright (c)
cmake_minimum_required( VERSION 2.6 FATAL_ERROR )
#################################################

###############################
# project name
project( DQMDream )

set( ${PROJECT_NAME}_VERSION_MAJOR 1 )
set( ${PROJECT_NAME}_VERSION_MINOR 0 )
set( ${PROJECT_NAME}_VERSION_PATCH 0 )

###############################
# Central settings
include( dqm4hep_settings )

# ----- Find DQM4hep package -----
dqm4hep_find_package( 
  PACKAGE DQM4hep 
  COMPONENTS DQMCore DQMNet DQMOnline 
  REQUIRED 
)

###############################
# Add source directory
add_subdirectory( source )

###############################
# display some variables and write them to cache
display_std_variables()
