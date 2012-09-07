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


 protected:

  // Description:
  // Constructor/Destructor
  Actuator();
  ~Actuator();

 protected:
    
};

} // end namespace nitro

#endif


