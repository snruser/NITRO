/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

  =========================================================================*/

#include "nitroJoint.h"

namespace nitro {

//---------------------------------------------------------------------------

  Joint::Joint()
  {
    this->j_Name = "Default";
    this->j_Description = "(None)";
    this->j_MotionType = ROTATIONAL;
    this->j_Drive = ACTIVE;
    this->j_MotionRange;
    this->j_Speed;
    this->j_Acceleration;
    this->j_Torque;
    this->j_Actuator;
    this->j_Sensor;
    this->j_Landmark;
  }

//---------------------------------------------------------------------------

  Joint::~Joint()
  {
  }

} // end namespace nitro
