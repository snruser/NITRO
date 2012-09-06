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

SET(NITRO_SOURCES
  nitroConditionVariable.cxx
  nitroFastMutexLock.cxx
  nitroLightObject.cxx
  nitroMultiThreader.cxx
  nitroMutexLock.cxx
  nitroObject.cxx
  nitroObjectFactoryBase.cxx
  nitroSimpleFastMutexLock.cxx
  )

SET(NITRO_INCLUDE_FILES
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
)

ADD_LIBRARY(NITRO
  ${NITRO_SOURCES}
  )

TARGET_LINK_LIBRARIES(NITRO
  ${LINK_LIBS}
  )

SET_TARGET_PROPERTIES(NITRO PROPERTIES
  VERSION ${NITRO_VERSION_MAJOR}.${NITRO_VERSION_MINOR}.${NITRO_VERSION_PATCH}
  SOVERSION ${NITRO_VERSION_MAJOR}
)

INSTALL(FILES ${NITRO_INCLUDE_FILES}
  DESTINATION ${NITRO_INSTALL_INCLUDE_DIR}
  COMPONENT Development)

INSTALL(TARGETS NITRO
  RUNTIME DESTINATION ${NITRO_INSTALL_BIN_DIR} COMPONENT RuntimeLibraries
  LIBRARY DESTINATION ${NITRO_INSTALL_LIB_DIR} COMPONENT RuntimeLibraries
  ARCHIVE DESTINATION ${NITRO_INSTALL_LIB_DIR} COMPONENT Development)
