/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

  =========================================================================*/

#include "nitroOSUtil.h"

#if defined(_WIN32) && !defined(__CYGWIN__)
#include <windows.h>
#else
#include <time.h>
#endif

namespace nitro
{

  void Sleep(int milliseconds)
  {
#if defined(_WIN32) && !defined(__CYGWIN__)

    // Call Windows Native Sleep() function
    ::Sleep(milliseconds);

#else

    struct timespec req;
    req.tv_sec  = (int) milliseconds / 1000;
    req.tv_nsec = (milliseconds % 1000) * 1000000;

    nanosleep(&req, NULL);

#endif

  }

}
