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

  //----------------------------------------------------------------------------------------------------

  Joint::Joint()
  {
    this->m_Name = "Default";
    this->m_Description = "(None)";
    this->m_Group = 0;
    this->m_MotionType = ROTATIONAL;
    this->m_Drive = ACTIVE;
    this->m_MotionRange;
    this->m_Speed;
    this->m_Acceleration;
    this->m_Torque;
    this->m_Actuator;
    this->m_Sensor;
    this->m_Landmark;
  }

  //----------------------------------------------------------------------------------------------------

  Joint::~Joint()
  {
  }

  //----------------------------------------------------------------------------------------------------

} // end namespace nitro
