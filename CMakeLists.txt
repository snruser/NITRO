PROJECT( NITRO )

cmake_minimum_required(VERSION 2.8)

if(COMMAND cmake_policy)
     cmake_policy(SET CMP0003 NEW)
     endif(COMMAND cmake_policy)

#-----------------------------------------------------------------------------
# NITRO version number.
SET(NITRO_VERSION_MAJOR "0")
SET(NITRO_VERSION_MINOR "5")
SET(NITRO_VERSION_PATCH "0")

#-----------------------------------------------------------------------------
# NITRO build configuration options.

OPTION(BUILD_SHARED_LIBS "Build NITRO with shared libraries." OFF)
SET(NITRO_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})

if(NOT NITRO_BUILD_SHARED_LIBS)
  OPTION(BUILD_GENERATE_PIC "Generate position independent code (for static)." ON)
  SET(NITRO_BUILD_GENERATE_PIC ${BUILD_GENERATE_PIC})
endif(NOT NITRO_BUILD_SHARED_LIBS)

OPTION(BUILD_EXAMPLES "Build NITRO example programs." OFF)
SET(NITRO_BUILD_EXAMPLES ${BUILD_EXAMPLES})

OPTION(BUILD_TESTING "Build the testing tree." ON)
SET(NITRO_BUILD_TESTING ${BUILD_TESTING})
IF(NITRO_BUILD_TESTING)
  ENABLE_TESTING()
  INCLUDE (${CMAKE_ROOT}/Modules/Dart.cmake)
ENDIF()

#-----------------------------------------------------------------------------
# OpenIGTLink

include(ExternalProject)

set(OpenIGTLink_PREFIX "${CMAKE_BINARY_DIR}/OpenIGTLink")
set(OpenIGTLink_GIT_REPO_URL   https://github.com/openigtlink/OpenIGTLink)
set(OpenIGTLink_INSTALL_DIR "${CMAKE_BINARY_DIR}/OpenIGTLink-build")
set(OpenIGTLink_CMAKE_ARGS     "-DCMAKE_INSTALL_PREFIX=${OpenIGTLink_INSTALL_DIR}")

ExternalProject_Add(OpenIGTLink
   PREFIX ${OpenIGTLink_PREFIX}
   GIT_REPOSITORY ${OpenIGTLink_GIT_REPO_URL}
   GIT_TAG "origin/development"
   CMAKE_ARGS ${OpenIGTLink_CMAKE_ARGS}
   INSTALL_DIR ${OpenIGTLink_INSTALL_DIR}
)


#-----------------------------------------------------------------------------
# Output directories.

IF(NOT LIBRARY_OUTPUT_PATH)
  SET (LIBRARY_OUTPUT_PATH ${NITRO_BINARY_DIR}/bin CACHE INTERNAL "Single output directory for building all libraries.")
ENDIF(NOT LIBRARY_OUTPUT_PATH)
IF(NOT EXECUTABLE_OUTPUT_PATH)
  SET (EXECUTABLE_OUTPUT_PATH ${NITRO_BINARY_DIR}/bin CACHE INTERNAL "Single output directory for building all executables.")
ENDIF(NOT EXECUTABLE_OUTPUT_PATH)
MARK_AS_ADVANCED(LIBRARY_OUTPUT_PATH EXECUTABLE_OUTPUT_PATH)

SET(NITRO_LIBRARY_PATH "${LIBRARY_OUTPUT_PATH}")
SET(NITRO_EXECUTABLE_PATH "${EXECUTABLE_OUTPUT_PATH}")

SET(NITRO_CMAKE_DIR "${NITRO_SOURCE_DIR}/CMake")
SET(CMAKE_MODULE_PATH "${NITRO_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})


#-----------------------------------------------------------------------------
# Installation vars.
# NITRO_INSTALL_BIN_DIR          - binary dir (executables)
# NITRO_INSTALL_LIB_DIR          - library dir (libs)
# NITRO_INSTALL_DATA_DIR         - share dir (say, examples, data, etc)
# NITRO_INSTALL_INCLUDE_DIR      - include dir (headers)
# NITRO_INSTALL_PACKAGE_DIR      - package/export configuration files
# NITRO_INSTALL_NO_DEVELOPMENT   - do not install development files
# NITRO_INSTALL_NO_RUNTIME       - do not install runtime files
# NITRO_INSTALL_NO_DOCUMENTATION - do not install documentation files

IF(NOT NITRO_INSTALL_BIN_DIR)
  SET(NITRO_INSTALL_BIN_DIR "bin")
ENDIF(NOT NITRO_INSTALL_BIN_DIR)

IF(NOT NITRO_INSTALL_LIB_DIR)
  SET(NITRO_INSTALL_LIB_DIR "lib/nitro")
ENDIF(NOT NITRO_INSTALL_LIB_DIR)

IF(NOT NITRO_INSTALL_DATA_DIR)
  SET(NITRO_INSTALL_DATA_DIR "share/nitro")
ENDIF(NOT NITRO_INSTALL_DATA_DIR)

IF(NOT NITRO_INSTALL_INCLUDE_DIR)
  SET(NITRO_INSTALL_INCLUDE_DIR "include/nitro")
ENDIF(NOT NITRO_INSTALL_INCLUDE_DIR)

IF(NOT NITRO_INSTALL_PACKAGE_DIR)
  SET(NITRO_INSTALL_PACKAGE_DIR ${NITRO_INSTALL_LIB_DIR}
    CACHE INTERNAL "")
ENDIF(NOT NITRO_INSTALL_PACKAGE_DIR)

IF(NOT NITRO_INSTALL_NO_DOCUMENTATION)
  SET(NITRO_INSTALL_NO_DOCUMENTATION 0)
ENDIF(NOT NITRO_INSTALL_NO_DOCUMENTATION)

SET(NITRO_DIR "${CMAKE_BINARY_DIR}" CACHE INTERNAL "NITRO dir to be used by subprojects")

#-----------------------------------------------------------------------------
# Include directories

SET(NITRO_INCLUDE_DIRS_BUILD_TREE ${NITRO_INCLUDE_DIRS_BUILD_TREE}
  ${NITRO_BINARY_DIR}
  ${NITRO_SOURCE_DIR}/Source
)

INCLUDE_DIRECTORIES(
  ${NITRO_INCLUDE_DIRS_BUILD_TREE}
  )

#-----------------------------------------------------------------------------
# NITRO requires special compiler flags on some platforms.


INCLUDE (FindThreads)

IF(CMAKE_COMPILER_IS_GNUCXX)

  # If the library is built as a static library, pass -fPIC option to the compiler
  IF(NITRO_BUILD_GENERATE_PIC)
    SET(NITRO_REQUIRED_C_FLAGS "${NITRO_REQUIRED_C_FLAGS} -fPIC")
    SET(NITRO_REQUIRED_CXX_FLAGS "${NITRO_REQUIRED_CXX_FLAGS} -fPIC")
  ENDIF(NITRO_BUILD_GENERATE_PIC)

  # pthread
  IF(CMAKE_HAVE_THREADS_LIBRARY)
    SET(NITRO_REQUIRED_LINK_FLAGS "${NITRO_REQUIRED_LINK_FLAGS} ${CMAKE_THREAD_LIBS_INIT}")
  ENDIF(CMAKE_HAVE_THREADS_LIBRARY)

ENDIF(CMAKE_COMPILER_IS_GNUCXX)


# for the gnu compiler a -D_PTHREADS is needed on sun
# for the native compiler a -mt flag is needed on the sun
IF(CMAKE_USE_PTHREADS)
  IF(CMAKE_SYSTEM MATCHES "SunOS.*")
    IF(CMAKE_COMPILER_IS_GNUCXX)
      SET(NITRO_REQUIRED_CXX_FLAGS "${NITRO_REQUIRED_CXX_FLAGS} -D_PTHREADS")
    ELSE(CMAKE_COMPILER_IS_GNUCXX)
      SET(NITRO_REQUIRED_CXX_FLAGS "${NITRO_REQUIRED_CXX_FLAGS} -mt")
      SET(NITRO_REQUIRED_C_FLAGS "${NITRO_REQUIRED_C_FLAGS} -mt")
    ENDIF(CMAKE_COMPILER_IS_GNUCXX)
  ENDIF(CMAKE_SYSTEM MATCHES "SunOS.*")
ENDIF(CMAKE_USE_PTHREADS)


#-----------------------------------------------------------------------------
# Platform configuration tests.

# Socket tests etc.
#INCLUDE(${NITRO_CMAKE_DIR}/NITROCMakeTests.cmake)



#-----------------------------------------------------------------------------
# Generate Configuration Header files.

include (${NITRO_SOURCE_DIR}/NITROConfigPlatform.cmake)

CONFIGURE_FILE(${NITRO_SOURCE_DIR}/nitroConfigure.h.in 
  ${NITRO_BINARY_DIR}/nitroConfigure.h)

CONFIGURE_FILE(${NITRO_SOURCE_DIR}/nitroTypeConfig.h.in 
  ${NITRO_BINARY_DIR}/nitroTypeConfig.h)


#-----------------------------------------------------------------------------
# Help other projects use NITRO.

# Copy the UseNITRO.cmake file to the binary tree for backward compatability.
CONFIGURE_FILE(${NITRO_SOURCE_DIR}/UseNITRO.cmake.in
${NITRO_BINARY_DIR}/UseNITRO.cmake COPYONLY IMMEDIATE)

# Create the NITROConfig.cmake file containing the NITRO configuration.
INCLUDE (${NITRO_SOURCE_DIR}/GenerateNITROConfig.cmake)

# Save the compiler settings so another project can import them.
INCLUDE(${CMAKE_ROOT}/Modules/CMakeExportBuildSettings.cmake)
CMAKE_EXPORT_BUILD_SETTINGS(${NITRO_BINARY_DIR}/NITROBuildSettings.cmake)

# Save library dependencies.
#EXPORT_LIBRARY_DEPENDENCIES(${NITRO_BINARY_DIR}/NITROLibraryDepends.cmake)

INSTALL(FILES
  ${NITRO_BINARY_DIR}/NITROBuildSettings.cmake
  ${NITRO_BINARY_DIR}/UseNITRO.cmake
#  ${NITRO_BINARY_DIR}/Utilities/NITROConfig.cmake
  DESTINATION ${NITRO_INSTALL_PACKAGE_DIR}
  COMPONENT Development
  )

INSTALL(FILES
  ${NITRO_BINARY_DIR}/nitroConfigure.h
  DESTINATION ${NITRO_INSTALL_INCLUDE_DIR}
  COMPONENT Development
  )

INSTALL(FILES
  ${NITRO_BINARY_DIR}/nitroTypeConfig.h
  DESTINATION ${NITRO_INSTALL_INCLUDE_DIR}
  COMPONENT Development
  )

#-----------------------------------------------------------------------------
# Add compiler flags NITRO needs to work on this platform.  This must be
# done AFTER the call to CMAKE_EXPORT_BUILD_SETTINGS.

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${NITRO_REQUIRED_C_FLAGS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${NITRO_REQUIRED_CXX_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${NITRO_REQUIRED_LINK_FLAGS}")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${NITRO_REQUIRED_LINK_FLAGS}")
SET(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${NITRO_REQUIRED_LINK_FLAGS}")


#-----------------------------------------------------------------------------
# Configure Subdirectories

ADD_SUBDIRECTORY( Source    )
#ADD_SUBDIRECTORY( Tools     )
#ADD_SUBDIRECTORY( Documents )

#IF(NITRO_BUILD_TESTING)
#  ADD_SUBDIRECTORY( Testing )
#ENDIF(NITRO_BUILD_TESTING)

IF(NITRO_BUILD_EXAMPLES)
 ADD_SUBDIRECTORY( Examples )
ENDIF(NITRO_BUILD_EXAMPLES)



##-----------------------------------------------------------------------------
## Doxygen 
#
#OPTION(BUILD_DOCUMENTATION "Build NITRO Documentation" OFF)
#
#IF(BUILD_DOCUMENTATION)
#  #SUBDIRS(Utilities/Doxygen)
#  ADD_SUBDIRECTORY( Documents/Doxygen )
#  CONFIGURE_FILE(${NITRO_SOURCE_DIR}/Utilities/Doxygen/doxygen.config.in
#               ${NITRO_BINARY_DIR}/doxygen.config)
#
#  CONFIGURE_FILE(${NITRO_SOURCE_DIR}/Utilities/Doxygen/nitrodoxygen.pl.in
#               ${NITRO_BINARY_DIR}/nitrodoxygen.pl)
#ENDIF(BUILD_DOCUMENTATION)


