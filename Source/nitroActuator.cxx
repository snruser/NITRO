/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

  =========================================================================*/

#include "nitroActuator.h"

namespace nitro {

//---------------------------------------------------------------------------

  Actuator::Actuator()
  {
    this->MotorType = ROTARY;
    this->FeedbackDevice = NONE;
  }

//---------------------------------------------------------------------------

  Actuator::~Actuator()
  {
  }

//---------------------------------------------------------------------------

  int Actuator::GetMotorType()
  {
    return MotorType;

  }
//---------------------------------------------------------------------------

  std::string Actuator::GetMotorTypeAsString()
  {
    switch(MotorType)
      {
      case ROTARY: { return "Rotary"; break; }
      case LINEAR: { return "Linear"; break; }
      default: { return "Not recognized"; break; }
      }
  }

//---------------------------------------------------------------------------

  void Actuator::SetMotorType(Motor type)
  {
    this->MotorType = type;
  }

//---------------------------------------------------------------------------

  int Actuator::GetFeedbackDevice()
  {
    return FeedbackDevice;
  }

//---------------------------------------------------------------------------

  std::string Actuator::GetFeedbackDeviceAsString()
  {
    switch(FeedbackDevice)
      {
      case NONE: { return "None"; break; }
      case ENCODER: { return "Encoder"; break; }
      default: { return "Not recognized"; break; }
      }
  }

//---------------------------------------------------------------------------

  void Actuator::SetFeedbackDevice(Feedback device)
  {
    this->FeedbackDevice = device;
  }


} // end namespace nitro
