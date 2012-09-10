/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef __igltOSUtil_h
#define __igltOSUtil_h

#include "nitroWin32Header.h"
namespace nitro
{

  /** Stop the program for the duration specified in millisecond
   *  The maximum dulation is 
   * */
  void NITROCommon_EXPORT Sleep(int millisecond);

}

#endif // __igltOSUtil_h


