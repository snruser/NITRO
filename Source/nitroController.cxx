/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "nitroController.h"

namespace nitro {

Controller::Controller()
{
  this->m_LoopCycle = 1000; // 1000 microsecond

  this->m_Kinematics = NULL;
  this->m_NetworkIF  = NULL;
  this->m_HardwareIF = NULL;
  this->m_UserIF     = NULL;
}

Controller::~Controller()
{
}

void Controller::Execute()
{
}
  
} // end namespace nitro
