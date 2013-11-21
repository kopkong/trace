# Install script for directory: /home/devtools/data/rel-16/external/apitrace

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/home/devtools/data/android-ndk-r8e/toolchains/arm-linux-androideabi-4.7/prebuilt/linux-x86_64/user")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/apitrace/scripts" TYPE PROGRAM FILES
    "/home/devtools/data/rel-16/external/apitrace/scripts/highlight.py"
    "/home/devtools/data/rel-16/external/apitrace/scripts/jsondiff.py"
    "/home/devtools/data/rel-16/external/apitrace/scripts/profileshader.py"
    "/home/devtools/data/rel-16/external/apitrace/scripts/retracediff.py"
    "/home/devtools/data/rel-16/external/apitrace/scripts/snapdiff.py"
    "/home/devtools/data/rel-16/external/apitrace/scripts/tracecheck.py"
    "/home/devtools/data/rel-16/external/apitrace/scripts/tracediff.py"
    "/home/devtools/data/rel-16/external/apitrace/scripts/unpickle.py"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/apitrace" TYPE FILE FILES
    "/home/devtools/data/rel-16/external/apitrace/BUGS.markdown"
    "/home/devtools/data/rel-16/external/apitrace/NEWS.markdown"
    "/home/devtools/data/rel-16/external/apitrace/README.markdown"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/apitrace" TYPE FILE RENAME "LICENSE.txt" FILES "/home/devtools/data/rel-16/external/apitrace/LICENSE")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/devtools/data/rel-16/external/apitrace/build/thirdparty/zlib/cmake_install.cmake")
  INCLUDE("/home/devtools/data/rel-16/external/apitrace/build/thirdparty/snappy/cmake_install.cmake")
  INCLUDE("/home/devtools/data/rel-16/external/apitrace/build/thirdparty/libpng/cmake_install.cmake")
  INCLUDE("/home/devtools/data/rel-16/external/apitrace/build/dispatch/cmake_install.cmake")
  INCLUDE("/home/devtools/data/rel-16/external/apitrace/build/helpers/cmake_install.cmake")
  INCLUDE("/home/devtools/data/rel-16/external/apitrace/build/wrappers/cmake_install.cmake")
  INCLUDE("/home/devtools/data/rel-16/external/apitrace/build/image/cmake_install.cmake")
  INCLUDE("/home/devtools/data/rel-16/external/apitrace/build/retrace/cmake_install.cmake")
  INCLUDE("/home/devtools/data/rel-16/external/apitrace/build/cli/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/home/devtools/data/rel-16/external/apitrace/build/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/home/devtools/data/rel-16/external/apitrace/build/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
