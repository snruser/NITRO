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

// NITRO Base class
#include "nitroBase.h"
#include "nitroJoint.h"

namespace nitro {


  class NITROCommon_EXPORT HardwareIF : public nitroBase
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
    virtual void Initialize();

// Description:
// Move actuator to target
    virtual void Move(int actuator, double target) {};

// Description:
// Move actuator to target
    virtual void InitiateCommunication() {};

// Description:
// Move actuator to target
    virtual void DefaultConfiguration() {};

// Description:
// Close connections, delete classes
    virtual void Exit() {};


  protected:

// Description:
// Constructor/Destructor
    HardwareIF();
    ~HardwareIF();

  protected:

  };

} // end namespace nitro

#endif
