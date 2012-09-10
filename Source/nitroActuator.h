/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

  =========================================================================*/

#ifndef  __nitroActuator_h
#define  __nitroActuator_h

#include "nitroConfigure.h"
#include "nitroObject.h"
#include "nitroObjectFactory.h"

namespace nitro {

  class NITROCommon_EXPORT Actuator : public Object
  {
  public:
    typedef Actuator            Self;
    typedef Object              Superclass;
    typedef SmartPointer<Self>  Pointer;
    typedef SmartPointer<const Self>  ConstPointer;

    nitroNewMacro(Self);
    nitroTypeMacro(Actuator, Object);

  public:

    enum Motor{
      ROTARY,
      LINEAR
    };

    enum Feedback{
      NONE,
      ENCODER
    };

    // Motor Type (Linear, Rotary, ...)
    int GetMotorType();
    std::string GetMotorTypeAsString();
    void SetMotorType(Motor type);

    // Feedback Device (Encoder, None, ...)
    int GetFeedbackDevice();
    std::string GetFeedbackDeviceAsString();
    void SetFeedbackDevice(Feedback device);

  protected:

    // Description:
    // Constructor/Destructor
    Actuator();
    ~Actuator();

  protected:

    Motor MotorType;
    Feedback FeedbackDevice;

  };

} // end namespace nitro

#endif
