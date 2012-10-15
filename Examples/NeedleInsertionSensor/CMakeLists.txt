PROJECT(NeedleInsertionSensor)

cmake_minimum_required(VERSION 2.8)
if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

find_package(NITRO REQUIRED)

include(${NITRO_USE_FILE})

SET(HEADERS
    )

SET(SOURCES
    nitroNeedleInsertionSensorServer.cxx
    )

ADD_EXECUTABLE(NeedleInsertionSensorServer ${SOURCES})
TARGET_LINK_LIBRARIES(NeedleInsertionSensorServer NITRO)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
