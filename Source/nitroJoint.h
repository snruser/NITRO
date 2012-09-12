/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

  =========================================================================*/

#ifndef  __nitroJoint_h
#define  __nitroJoint_h

#include "nitroConfigure.h"
#include "nitroObject.h"
#include "nitroObjectFactory.h"

#include "nitroJointTypes.h"

namespace nitro {

  class NITROCommon_EXPORT Joint : public Object
  {
  public:
    typedef Joint                    Self;
    typedef Object                   Superclass;
    typedef SmartPointer<Self>       Pointer;
    typedef SmartPointer<const Self> ConstPointer;

    nitroNewMacro(Self);
    nitroTypeMacro(Joint, Object);

  public:

  protected:

    // Description:
    // Constructor/Destructor
    Joint();
    ~Joint();

  protected:

    Text j_Name;
    Text j_Description;
    MotionType j_MotionType;
    Drive j_Drive;
    MinMax j_MotionRange;
    MinMaxFixed j_Speed;
    MinMaxFixed j_Acceleration;
    MinMaxFixed j_Torque;
    Actuator j_Actuator;
    Sensor j_Sensor;
    Landmark j_Landmark;
  };

} // end namespace nitro

#endif
