#######################################################
# cmake file for building DQMDream package
# @author Ete Remi, DESY
# Copyright (c)
#######################################################

# -------------------------------------------------
# include directories
include_directories( BEFORE include )

# -------------------------------------------------
# Set CXX_FLAGS
dqm4hep_set_cxx_flags()

# -------------------------------------------------
# build the project library
aux_source_directory( src SRC_FILES )
aux_source_directory( src/plugins SRC_FILES )
add_shared_library( ${PROJECT_NAME} ${SRC_FILES} )
install( TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib )

install_directory( include DESTINATION . FILES_MATCHING PATTERN "*.h" PATTERN "*.cc" )


