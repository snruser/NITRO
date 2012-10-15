/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

  =========================================================================*/

#ifndef  __nitroKinematics_h
#define  __nitroKinematics_h

// NITRO Base class
#include "nitroBase.h"

namespace nitro {

  class NITROCommon_EXPORT Kinematics : public nitroBase
  {
  public:
    typedef Kinematics                  Self;
    typedef Object                      Superclass;
    typedef SmartPointer<Self>          Pointer;
    typedef SmartPointer<const Self>    ConstPointer;

    nitroNewMacro(Self);
    nitroTypeMacro(Kinematics, Object);

  public:

    // Description:
    // Initialization function. Could be overloaded.
    virtual void Initialize() {};

    // Description:
    // Convert target position to motor motion
    virtual double Convert(double target) { return 0.0; };

    // Description:
    // Close connections, delete classes
    virtual void Exit() {};

  protected:

    // Description:
    // Constructor/Destructor
    Kinematics();
    ~Kinematics();

  protected:

  };

} // end namespace nitro

#endif
