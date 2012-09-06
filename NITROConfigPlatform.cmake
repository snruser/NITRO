#-----------------------------------------------------------------------------
# Check platform and generate igtlConfigure.h
#-----------------------------------------------------------------------------

#
# The platform is determined by CMAKE_SYSTEM_NAME variable.
# CMake set CMAKE_SYSTEM_NAME based on "uname -s" on unix or just set "Windows"
# on windows.
# The list of "uname -s" is available in CMake/Modules/CMakeDetermineSystem.cmake
#

# Thread parameters
# Use pthread in default except Windows
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  SET(NITRO_USE_WIN32_THREADS 1)
else(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  SET(NITRO_USE_PTHREADS 1)  
endif(CMAKE_SYSTEM_NAME STREQUAL "Windows")


# Windows
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  SET(NITRO_PLATFORM_WIN32 1)
endif(CMAKE_SYSTEM_NAME STREQUAL "Windows")

# Mac OS X
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  SET(NITRO_PLATFORM_MACOSX 1)
endif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")

# Linux
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
  SET(NITRO_PLATFORM_LINUX 1)
endif(CMAKE_SYSTEM_NAME MATCHES "Linux")

# Sun OS
if(CMAKE_SYSTEM_NAME MATCHES "SunOS")
#  SET(OpenIGTLink_USE_SPROC 1)
  SET(OpenIGTLink_PLATFORM_SUNOS 1)
  # Set OpenIGTLink_STD_LINK_LIBRARIES 

  SET(OpenIGTLink_STD_LINK_LIBRARIES
    ${OpenIGTLink_STD_LINK_LIBRARIES}
    rt
    nsl
  )
  IF(CMAKE_COMPILER_IS_GNUCXX)
     SET(OpenIGTLink_STD_LINK_LIBRARIES
       ${OpenIGTLink_STD_LINK_LIBRARIES}
       stdc++
     )
  ELSE(CMAKE_COMPILER_IS_GNUCXX)
  ENDIF(CMAKE_COMPILER_IS_GNUCXX)
endif(CMAKE_SYSTEM_NAME MATCHES "SunOS")

# QNX
if(CMAKE_SYSTEM_NAME STREQUAL "QNX")
  SET(NITRO_PLATFORM_QNX 1)
endif(CMAKE_SYSTEM_NAME STREQUAL "QNX")

#-----------------------------------------------------------------------------
# Type Check 
# 

include(CheckTypeSize)
check_type_size(int         CMAKE_SIZEOF_INT)
check_type_size(long        CMAKE_SIZEOF_LONG)
check_type_size("void*"     CMAKE_SIZEOF_VOID_P)
check_type_size(char        CMAKE_SIZEOF_CHAR)
check_type_size(short       CMAKE_SIZEOF_SHORT)
check_type_size(float       CMAKE_SIZEOF_FLOAT)
check_type_size(double      CMAKE_SIZEOF_DOUBLE)
check_type_size("long long" CMAKE_SIZEOF_LONG_LONG)
check_type_size("__int64"   CMAKE_SIZEOF___INT64)
check_type_size("int64_t"   CMAKE_SIZEOF_INT64_T)

#ADD_DEFINITIONS(-DIGTL_SIZEOF_CHAR=${CMAKE_SIZEOF_CHAR})
#ADD_DEFINITIONS(-DIGTL_SIZEOF_DOUBLE=${CMAKE_SIZEOF_DOUBLE})
#ADD_DEFINITIONS(-DIGTL_SIZEOF_FLOAT=${CMAKE_SIZEOF_FLOAT})
#ADD_DEFINITIONS(-DIGTL_SIZEOF_INT=${CMAKE_SIZEOF_INT})
#ADD_DEFINITIONS(-DIGTL_SIZEOF_LONG=${CMAKE_SIZEOF_LONG})
#ADD_DEFINITIONS(-DIGTL_SIZEOF_SHORT=${CMAKE_SIZEOF_SHORT})
#ADD_DEFINITIONS(-DIGTL_SIZEOF_FLOAT=${CMAKE_SIZEOF_FLOAT})
#ADD_DEFINITIONS(-DIGTL_SIZEOF_DOUBLE=${CMAKE_SIZEOF_DOUBLE})

