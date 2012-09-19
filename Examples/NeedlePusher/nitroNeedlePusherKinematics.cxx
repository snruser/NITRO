/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

  =========================================================================*/

#include "nitroNeedlePusherKinematics.h"

namespace nitro {

  NeedlePusherKinematics::NeedlePusherKinematics()
  {
  }

  NeedlePusherKinematics::~NeedlePusherKinematics()
  {
  }

  double NeedlePusherKinematics::Convert(double target)
  {
    // TODO: Get max value, min value from XML and current position
    if(target > -200.0 && target < 200.0)
      {
      return target*300;
      }
    return 0.0;
  }


} // end namespace nitro
