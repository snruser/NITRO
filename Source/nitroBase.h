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

// Shared Memory
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_CONTROLLER_AREA	(key_t)84560
#define SHM_HARDWARE_AREA	(key_t)84561
#define SHM_NETWORK_AREA	(key_t)84562
#define SHM_KINEMATICS_AREA	(key_t)84563
#define SHM_UI_AREA		(key_t)84564

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

    int AllocateSharedMemory(key_t shmKey ,int size, int permflag);
    //void SetShmID(int shid) { this->shm_id = shid; }
    //int GetShmID() { return this->shm_id; }
    //void SetSharedMemoryArea(void* shmem) { this->SharedMemoryArea = shmem; }
    void* GetSharedMemoryArea() { return this->SharedMemoryArea; }
    int DeallocateSharedMemory();

  protected:

    // Description:
    // Constructor/Destructor
    nitroBase();
    ~nitroBase();

  protected:

    int shm_id;
    void* SharedMemoryArea;

  };

} // end namespace nitro

#endif
