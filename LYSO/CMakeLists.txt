#(1)
#----------------------------------------------------------------------------
# Setup the project
#
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(LYSO)

#(2)
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

#(2.5)
#----------------------------------------------------------------------------
#Link ROOT libraries to be used with GEANT4
# 
find_package(ROOT REQUIRED)
include_directories(/usr/local/include/root)

#(3)
#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

#(4)
#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#(5)
#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(LYSO LYSO.cc ${sources} ${headers})
target_link_libraries(LYSO ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

#(6)
#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build Bcal01. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(LYSO_SCRIPTS
    vis.mac
  )

foreach(_script ${LYSO_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#(7)
#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
#install(TARGETS LYSO DESTINATION bin)
