# Install script for directory: C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/OpenSteer")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenSteer" TYPE FILE FILES
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/AbstractVehicle.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/Annotation.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/Camera.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/Clock.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/Color.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/Draw.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/LocalSpace.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/lq.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/Obstacle.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/OldPathway.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/OpenSteerDemo.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/Path.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/Pathway.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/PlugIn.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/PolylineSegmentedPath.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/PolylineSegmentedPathwaySegmentRadii.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/PolylineSegmentedPathwaySingleRadius.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/Proximity.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/QueryPathAlike.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/QueryPathAlikeBaseDataExtractionPolicies.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/QueryPathAlikeMappings.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/QueryPathAlikeUtilities.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/SegmentedPath.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/SegmentedPathAlikeUtilities.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/SegmentedPathway.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/SharedPointer.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/SimpleVehicle.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/StandardTypes.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/SteerLibrary.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/UnusedParameter.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/Utilities.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/Vec3.h"
    "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/src/include/OpenSteer/Vec3Utilities.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/Build/third-party/glfw/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Users/Javier/Desktop/MasMierdas/UniTwT/Grupo6/Juego/Juego_de_autos/Motor/Dependecies/OpenSteer/Build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
