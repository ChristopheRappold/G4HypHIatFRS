# $Id: CMakeLists.txt 760 2014-08-27 13:43:29Z ihrivnac $

#----------------------------------------------------------------------------
# Setup the project
#
cmake_minimum_required(VERSION 2.8.3 FATAL_ERROR)
project(HYPHIFRS_MC)

include(CheckCXXCompilerFlag)
#SET(CPP_STANDARD c++14)

SET(Geant4VMC_DIR $ENV{G4VMC}/lib/Geant4VMC-3.1.1)
SET(MTRoot_DIR $ENV{G4VMC}/lib/MTRoot-3.1.1)
SET(VGM_DIR $ENV{VGM_INSTALL}/lib/VGM-4.2.0)


#----------------------------------------------------------------------------
# Set path to Find modules in VGM
#
set(CMAKE_MODULE_PATH 
  ${Geant4VMC_DIR}/Modules
  ${VGM_DIR}/Modules
  ${CMAKE_MODULE_PATH}) 

message(STATUS ${CMAKE_MODULE_PATH})
#----------------------------------------------------------------------------
# Find VGM package
if (NOT VGM_FOUND)
  find_package(VGM REQUIRED)
endif()


include(UseVMC)

#----------------------------------------------------------------------------
# Find ROOT package
find_package(ROOT REQUIRED)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include
                    ${PROJECT_SOURCE_DIR}/FairBase  
                    ${Geant4_INCLUDE_DIR}
                    ${ROOT_INCLUDE_DIRS}
                    ${VGM_INCLUDE_DIRS})

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#

set(library_name vmc_${PROJECT_NAME})

add_executable(HypHIFRS_MC HypHIFRS_MC.cc ${sources} ${headers})
target_link_libraries(HypHIFRS_MC -L${PROJECT_SOURCE_DIR}/FairBase -lHyphiFairBase ${library_name} ${VGM_LIBRARIES} ${ROOT_LIBRARIES} ${Geant4_LIBRARIES})


ROOT_GENERATE_DICTIONARY(
  ${CMAKE_SHARED_LIBRARY_PREFIX}${library_name}
  no_rootmap
  ${CMAKE_CURRENT_SOURCE_DIR}/include/THypHi_Par.hh
  ${CMAKE_CURRENT_SOURCE_DIR}/include/THypHi_UTrackerHit.hh
  ${CMAKE_CURRENT_SOURCE_DIR}/include/THypHi_Event.hh
  LINKDEF ${CMAKE_CURRENT_SOURCE_DIR}/include/THypHi_linkdef.h)

set(SourceLib ${PROJECT_SOURCE_DIR}/src/THypHi_Par.cc ${PROJECT_SOURCE_DIR}/src/THypHi_Event.cc ${PROJECT_SOURCE_DIR}/src/THypHi_UTrackerHit.cc)

add_library(${library_name} ${SourceLib} ${CMAKE_SHARED_LIBRARY_PREFIX}${library_name}_dict.cxx ${headers})
target_link_libraries(${library_name} ${VMC_LIBRARIES})


#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build B4a. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(B4a_SCRIPTS
  exampleB4a.out
  exampleB4.in
  icons.mac
  gui.mac
  run.png
  init.mac
  init_vis.mac
  run1.mac
  run2.mac
  vis.mac
  )

foreach(_script ${B4a_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS HypHIFRS_MC DESTINATION bin)
