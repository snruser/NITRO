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

  double NeedlePusherKinematics::Convert(double distance_mm)
  {
    // TODO: Get max value, min value from XML and current position
    if(distance_mm > -200.0 && distance_mm < 200.0)
      {
      return distance_mm*300;
      }
    return 0.0;
  }


} // end namespace nitro
