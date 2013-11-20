# Install script for directory: G:/trace

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/apitrace")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
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

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/scripts" TYPE PROGRAM FILES
    "G:/trace/scripts/highlight.py"
    "G:/trace/scripts/jsondiff.py"
    "G:/trace/scripts/profileshader.py"
    "G:/trace/scripts/retracediff.py"
    "G:/trace/scripts/snapdiff.py"
    "G:/trace/scripts/tracecheck.py"
    "G:/trace/scripts/tracediff.py"
    "G:/trace/scripts/unpickle.py"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/scripts" TYPE PROGRAM FILES "G:/trace/scripts/convert.py")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/doc" TYPE FILE FILES
    "G:/trace/BUGS.markdown"
    "G:/trace/NEWS.markdown"
    "G:/trace/README.markdown"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/doc" TYPE FILE RENAME "LICENSE.txt" FILES "G:/trace/LICENSE")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/doc" TYPE FILE RENAME "LICENSE-msinttypes.txt" FILES "G:/trace/thirdparty/msinttypes/LICENSE")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("G:/trace/msbuild/thirdparty/zlib/cmake_install.cmake")
  INCLUDE("G:/trace/msbuild/thirdparty/snappy/cmake_install.cmake")
  INCLUDE("G:/trace/msbuild/thirdparty/libpng/cmake_install.cmake")
  INCLUDE("G:/trace/msbuild/thirdparty/getopt/cmake_install.cmake")
  INCLUDE("G:/trace/msbuild/thirdparty/less/cmake_install.cmake")
  INCLUDE("G:/trace/msbuild/thirdparty/directxtex/cmake_install.cmake")
  INCLUDE("G:/trace/msbuild/dispatch/cmake_install.cmake")
  INCLUDE("G:/trace/msbuild/helpers/cmake_install.cmake")
  INCLUDE("G:/trace/msbuild/wrappers/cmake_install.cmake")
  INCLUDE("G:/trace/msbuild/image/cmake_install.cmake")
  INCLUDE("G:/trace/msbuild/retrace/cmake_install.cmake")
  INCLUDE("G:/trace/msbuild/inject/cmake_install.cmake")
  INCLUDE("G:/trace/msbuild/cli/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "G:/trace/msbuild/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "G:/trace/msbuild/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
