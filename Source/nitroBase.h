/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

  =========================================================================*/

#ifndef  __nitroBase_h
#define  __nitroBase_h

#include "nitroConfigure.h"
#include "nitroObject.h"
#include "nitroObjectFactory.h"

namespace nitro {

  class NITROCommon_EXPORT nitroBase : public Object
  {
  public:
    typedef nitroBase                Self;
    typedef Object                   Superclass;
    typedef SmartPointer<Self>       Pointer;
    typedef SmartPointer<const Self> ConstPointer;

    nitroNewMacro(Self);
    nitroTypeMacro(nitroBase, Object);

  public:


  protected:

    // Description:
    // Constructor/Destructor
    nitroBase();
    ~nitroBase();

  protected:

  };

} // end namespace nitro

#endif
