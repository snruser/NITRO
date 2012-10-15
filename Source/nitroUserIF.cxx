/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

  =========================================================================*/

#include "nitroUserIF.h"

namespace nitro {

  UserIF::UserIF()
  {
    this->shmController = NULL;
    this->shmNetwork    = NULL;
    this->shmKinematics = NULL;
    this->shmHardware   = NULL;

    this->shmControllerID = -1;
    this->shmNetworkID    = -1;
    this->shmKinematicsID = -1;
    this->shmHardwareID   = -1;

    this->CheckSharedMemories();
  }

  UserIF::~UserIF()
  {
  }

  void UserIF::Print(const char *format, ...)
  {
  }

  void UserIF::PrintError(const char *format, ...)
  {
  }

  void UserIF::CheckSharedMemories()
  {
    // Check Controller Shared Memory
    this->CheckSharedMemory(SHM_CONTROLLER_AREA,&(this->shmControllerID), &shmController);
    this->CheckSharedMemory(SHM_NETWORK_AREA, &(this->shmNetworkID), &shmNetwork);
    this->CheckSharedMemory(SHM_KINEMATICS_AREA, &(this->shmKinematicsID), &shmKinematics);
    this->CheckSharedMemory(SHM_HARDWARE_AREA, &(this->shmHardwareID), &shmHardware);
  }

  void UserIF::CheckSharedMemory(key_t shmKey, int* shmID, void** shmPtr)
  {
    // Get ID
    int newShmID = shmget(shmKey, MEMORY_SIZE, 0644);
    *shmID = (newShmID >= 0) ? newShmID : -1;

    // Get Pointer
    if(*shmID >= 0)
      {
      void* newShmPtr = shmat(*shmID, NULL, 0);
      *shmPtr = (newShmPtr >= 0) ? newShmPtr : NULL;
      }
  }

} // end namespace nitro
