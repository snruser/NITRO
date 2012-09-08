/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef  __nitroOpenIGTLinkNetworkIF_h
#define  __nitroOpenIGTLinkNetworkIF_h

#include "nitroConfigure.h"
#include "nitroObject.h"
#include "nitroObjectFactory.h"

namespace nitro {

class NITROCommon_EXPORT OpenIGTLinkNetworkIF : public Object
{
 public:
  typedef OpenIGTLinkNetworkIF           Self;
  typedef Object              Superclass;
  typedef SmartPointer<Self>  Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  nitroNewMacro(Self);
  nitroTypeMacro(OpenIGTLinkNetworkIF, Object);

 public:


 protected:

  // Description:
  // Constructor/Destructor
  OpenIGTLinkNetworkIF();
  ~OpenIGTLinkNetworkIF();

 protected:
    
};

} // end namespace nitro

#endif


