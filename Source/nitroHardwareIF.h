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

// STD include
#include <vector>

#include "nitroConfigure.h"
#include "nitroObject.h"
#include "nitroObjectFactory.h"

// NITRO includes
#include "nitroJoint.h"

namespace nitro {

  class NITROCommon_EXPORT HardwareIF : public Object
  {
  public:
    typedef HardwareIF                  Self;
    typedef Object                      Superclass;
    typedef SmartPointer<Self>          Pointer;
    typedef SmartPointer<const Self>    ConstPointer;

    nitroNewMacro(Self);
    nitroTypeMacro(HardwareIF, Object);

  public:

    // Description:
    // Initialization function. Could be overloaded.
    virtual void Initialize() {};


  protected:

    // Description:
    // Constructor/Destructor
    HardwareIF();
    ~HardwareIF();

    // Description:
    // Variables
    int DegreesOfFreedom;

    // Description:
    // Vector of actuators
    std::vector<Joint*> JointsList;

  protected:

  };

} // end namespace nitro

#endif
