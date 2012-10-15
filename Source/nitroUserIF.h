/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

  =========================================================================*/

#ifndef  __nitroUserIF_h
#define  __nitroUserIF_h

// NITRO Base class
#include "nitroBase.h"

namespace nitro {

  class NITROCommon_EXPORT UserIF : public nitroBase
  {
  public:
    typedef UserIF                      Self;
    typedef Object                      Superclass;
    typedef SmartPointer<Self>          Pointer;
    typedef SmartPointer<const Self>    ConstPointer;

    nitroNewMacro(Self);
    nitroTypeMacro(UserIF, Object);

  public:

    virtual void Print(const char *format, ...);
    virtual void PrintError(const char *format, ...);

    // Description:
    // Initialization function. Could be overloaded.
    virtual void Initialize() {};

    // Description:
    // Close connections, delete classes
    virtual void Exit() {};

    // Description:
    // Check which shared memory has been allocated
    void CheckSharedMemories();

    // Access shared memories area
    void* GetControllerMemory() { return this->shmController; }
    void* GetNetworkMemory() { return this->shmNetwork; }
    void* GetKinematicsMemory() { return this->shmKinematics; }
    void* GetHardwareMemory() { return this->shmHardware; }

  protected:

    // Description:
    // Constructor/Destructor
    UserIF();
    ~UserIF();

    void CheckSharedMemory(key_t shmKey, int* shmID, void** shmPtr);

  protected:

    void* shmController;
    void* shmNetwork;
    void* shmKinematics;
    void* shmHardware;

    int shmControllerID;
    int shmNetworkID;
    int shmKinematicsID;
    int shmHardwareID;

  };

} // end namespace nitro

#endif
