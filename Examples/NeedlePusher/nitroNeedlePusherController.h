/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

  =========================================================================*/

#ifndef  __nitroNeedlePusherController_h
#define  __nitroNeedlePusherController_h

#include "nitroConfigure.h"
#include "nitroObject.h"
#include "nitroObjectFactory.h"

// NITRO Classes
#include "nitroController.h"
#include "nitroGalilHardwareIF.h"

namespace nitro {

  class NITROCommon_EXPORT NeedlePusherController : public Controller
  {
  public:
    typedef NeedlePusherController          Self;
    typedef Object              Superclass;
    typedef SmartPointer<Self>  Pointer;
    typedef SmartPointer<const Self>  ConstPointer;

    nitroNewMacro(Self);
    nitroTypeMacro(NeedlePusherController, Object);

  public:

    // Description:
    // Initialize all classes and parse xml file (if exists) to fill them
    virtual void Initialize();

    // Description:
    // Main loop 
    // TODO: Rename it
    //virtual void Loop();
    
    // Description:
    // Close connections, delete classes 
    virtual void Exit();
    
    // Description:
    // Run main loop. Note that this base class is implemented for
    // non-real-time OS. If you consider using real-time OS API for
    // hard real-time control of the loop, you may create a child
    // class and override this function.
    virtual int Execute();

  protected:

    // Description:
    // Constructor/Destructor
    NeedlePusherController();
    ~NeedlePusherController();
  };

} // end namespace nitro

#endif
