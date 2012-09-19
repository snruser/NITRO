/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef  __nitroNeedlePusherKinematics_h
#define  __nitroNeedlePusherKinematics_h

#include "nitroConfigure.h"
#include "nitroObject.h"
#include "nitroObjectFactory.h"
#include "nitroKinematics.h"

namespace nitro {

class NITROCommon_EXPORT NeedlePusherKinematics : public Kinematics
{
 public:
  typedef NeedlePusherKinematics          Self;
  typedef Object              Superclass;
  typedef SmartPointer<Self>  Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  nitroNewMacro(Self);
  nitroTypeMacro(NeedlePusherKinematics, Object);

 public:

  // Description:
  // Convert target position to motor motion
  virtual double Convert(double target);

 protected:

  // Description:
  // Constructor/Destructor
  NeedlePusherKinematics();
  ~NeedlePusherKinematics();

 protected:
    
};

} // end namespace nitro

#endif


