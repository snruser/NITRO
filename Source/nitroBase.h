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

#include <string.h>
#include <stdio.h>

#define SHM_CONTROLLER_AREA     (key_t)84560
#define SHM_HARDWARE_AREA       (key_t)84561
#define SHM_NETWORK_AREA        (key_t)84562
#define SHM_KINEMATICS_AREA     (key_t)84563
#define SHM_UI_AREA             (key_t)84564

// Attribute = Timestamp (unsigned int) + Key (256 char) + Value (256 char)

#define FIELD_LENGTH 256
#define FIELDS_PER_ATTRIBUTE 2
#define TIMESTAMP_SIZE sizeof(unsigned int)
#define ATTRIBUTE_SIZE (TIMESTAMP_SIZE + FIELDS_PER_ATTRIBUTE*FIELD_LENGTH*sizeof(char))
#define MAX_ATTRIBUTES 100
#define MEMORY_SIZE MAX_ATTRIBUTES*ATTRIBUTE_SIZE

#define KEY_OFFSET TIMESTAMP_SIZE
#define VALUE_OFFSET (TIMESTAMP_SIZE + FIELD_LENGTH*sizeof(char))

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
    void* GetSharedMemoryArea() { return this->SharedMemoryArea; }
    int DeallocateSharedMemory();
    int AddAttribute(const char* key, const char* value);
    int RemoveAttribute(const char* key);
    int ModifyAttribute(const char* key, const char* value);
    char* GetKeyValue(const char* key);
    unsigned int GetKeyTimestamp(const char* key);

  protected:

    // Description:
    // Constructor/Destructor
    nitroBase();
    ~nitroBase();

  protected:

    int shm_id;
    void* SharedMemoryArea;
    int NumOfAttributes;
    unsigned int AccessCounter;

  };

} // end namespace nitro

#endif
