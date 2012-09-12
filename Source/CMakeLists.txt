# list of libraries
# Note: this part should be moved to NITROConfigPlatform.cmake

IF(NITRO_PLATFORM_WIN32) # for Windows
  SET(LINK_LIBS
    ws2_32
    wsock32
  )
ELSE(NITRO_PLATFORM_WIN32) # for POSIX-compatible OSs
  SET(LINK_LIBS
    m
    pthread
  )
  IF(NITRO_PLATFORM_QNX)
    SET(LINK_LIBS
      ${LINK_LIBS}
      c
      socket
    )
  ENDIF(NITRO_PLATFORM_QNX)
  IF(NITRO_PLATFORM_SUNOS)
    SET(LINK_LIBS
      ${LINK_LIBS}
      ${NITRO_STD_LINK_LIBRARIES}
    )
  ENDIF(NITRO_PLATFORM_SUNOS)
ENDIF(NITRO_PLATFORM_WIN32)

SET(NITRO_BASE_SOURCES
  nitroConditionVariable.cxx
  nitroFastMutexLock.cxx
  nitroLightObject.cxx
  nitroMultiThreader.cxx
  nitroMutexLock.cxx
  nitroObject.cxx
  nitroObjectFactoryBase.cxx
  nitroSimpleFastMutexLock.cxx
  nitroJoint.cxx
  nitroXMLParser.cxx
  nitroOSUtil.cxx
  )

SET(NITRO_WORKFLOW_SOURCES
  nitroController.cxx
  nitroKinematics.cxx
  nitroHardwareIF.cxx
  nitroNetworkIF.cxx
  nitroUserIF.cxx
  nitroGalilHardwareIF.cxx
  nitroOpenIGTLinkNetworkIF.cxx
  )	

SET(NITRO_BASE_INCLUDES
  nitroConditionVariable.h
  nitroCreateObjectFunction.h
  nitroFastMutexLock.h
  nitroLightObject.h
  nitroMacro.h
  nitroMultiThreader.h
  nitroMutexLock.h
  nitroObject.h
  nitroObjectFactory.h
  nitroObjectFactoryBase.h
  nitroSimpleFastMutexLock.h
  nitroSmartPointer.h
  nitroTypes.h
  nitroWin32Header.h
  nitroWindows.h
  nitroJoint.h
  nitroXMLParser.h
  nitroOSUtil.h
  nitroMath.h
)

SET(NITRO_WORKFLOW_INCLUDES
  nitroController.h
  nitroKinematics.h
  nitroHardwareIF.h
  nitroNetworkIF.h
  nitroUserIF.h
  nitroGalilHardwareIF.h
  nitroOpenIGTLinkNetworkIF.cxx
  )

SET(RAPIDXML_INCLUDE_FILES
  RapidXML/rapidxml_iterators.hpp
  RapidXML/rapidxml_print.hpp
  RapidXML/rapidxml_utils.hpp
  RapidXML/rapidxml.hpp
  )

ADD_LIBRARY(NITRO
  ${NITRO_BASE_SOURCES}
  ${NITRO_WORKFLOW_SOURCES}
  )

 # add imported target
ADD_LIBRARY(OpenIGTLinkLib STATIC IMPORTED)
 
 # point the imported target at the real file
SET_PROPERTY(TARGET OpenIGTLinkLib PROPERTY
                IMPORTED_LOCATION "${OpenIGTLink_INSTALL_DIR}/lib/igtl/libOpenIGTLink.a")

INCLUDE_DIRECTORIES(${OpenIGTLink_INSTALL_DIR}/include/igtl)

TARGET_LINK_LIBRARIES(NITRO
  ${LINK_LIBS}
  OpenIGTLinkLib
  )

SET_TARGET_PROPERTIES(NITRO PROPERTIES
  VERSION ${NITRO_VERSION_MAJOR}.${NITRO_VERSION_MINOR}.${NITRO_VERSION_PATCH}
  SOVERSION ${NITRO_VERSION_MAJOR}
)

INSTALL(FILES ${NITRO_BASE_INCLUDES} ${NITRO_WORKFLOW_INCLUDES} ${RAPIDXML_INCLUDE_FILES}
  DESTINATION ${NITRO_INSTALL_INCLUDE_DIR}
  COMPONENT Development)

INSTALL(TARGETS NITRO
  RUNTIME DESTINATION ${NITRO_INSTALL_BIN_DIR} COMPONENT RuntimeLibraries
  LIBRARY DESTINATION ${NITRO_INSTALL_LIB_DIR} COMPONENT RuntimeLibraries
  ARCHIVE DESTINATION ${NITRO_INSTALL_LIB_DIR} COMPONENT Development)
