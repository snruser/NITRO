/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef  __nitroHardwareIF_h
#define  __nitroHardwareIF_h

#include "nitroConfigure.h"
#include "nitroObject.h"
#include "nitroObjectFactory.h"

namespace nitro {

class NITROCommon_EXPORT HardwareIF : public Object
{
 public:
  typedef HardwareIF          Self;
  typedef Object              Superclass;
  typedef SmartPointer<Self>  Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  nitroNewMacro(Self);
  nitroTypeMacro(HardwareIF, Object);

 public:


 protected:

  // Description:
  // Constructor/Destructor
  HardwareIF();
  ~HardwareIF();

 protected:
    
};

} // end namespace nitro

#endif


