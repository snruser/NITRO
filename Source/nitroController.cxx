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
  this->LoopCycle = 1000; // 1000 microsecond

  this->Kinematics;
  this->NetworkIF;
  this->HardwareIF;
}

Controller::~Controller()
{
}

virtual void Controller::Execute()
{
}
  
} // end namespace nitro
