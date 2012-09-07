/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef  __nitroNetworkIF_h
#define  __nitroNetworkIF_h

#include "nitroConfigure.h"
#include "nitroObject.h"
#include "nitroObjectFactory.h"

namespace nitro {

class NITROCommon_EXPORT NetworkIF : public Object
{
 public:
  typedef NetworkIF          Self;
  typedef Object              Superclass;
  typedef SmartPointer<Self>  Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  nitroNewMacro(Self);
  nitroTypeMacro(NetworkIF, Object);

 public:


 protected:

  // Description:
  // Constructor/Destructor
  NetworkIF();
  ~NetworkIF();

 protected:
    
};

} // end namespace nitro

#endif


