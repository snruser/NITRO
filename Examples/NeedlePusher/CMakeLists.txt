PROJECT(NeedlePusher)

cmake_minimum_required(VERSION 2.8)
if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

find_package(NITRO REQUIRED)

include(${NITRO_USE_FILE})

SET(HEADERS
   nitroHardwareNeedlePusher.h)

SET(SOURCES
    nitroNeedlePusherServer.cxx
    nitroHardwareNeedlePusher.cxx)

ADD_EXECUTABLE(NeedlePusherServer ${SOURCES})
TARGET_LINK_LIBRARIES(NeedlePusherServer NITRO)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
