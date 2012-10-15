/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

  =========================================================================*/

#include "nitroBase.h"

namespace nitro {

  nitroBase::nitroBase()
  {
    this->shm_id = -1;
    this->SharedMemoryArea = NULL;
  }

  nitroBase::~nitroBase()
  {
    if(this->SharedMemoryArea)
      {
      this->DeallocateSharedMemory();
      }
  }

  int nitroBase::AllocateSharedMemory(key_t shmKey, int size, int permflag)
  {
    // Check if memory not already allocated
    if(this->SharedMemoryArea == NULL)
      {
      // Allocate new shared memory and attach it to the process
      this->shm_id = shmget(shmKey, size, permflag);
      if(this->shm_id >= 0)
        {
        this->SharedMemoryArea = shmat(this->shm_id, NULL, 0);
        if(this->SharedMemoryArea <= 0)
          {
          std::cerr << "Shared Memory not allocated for key: " << shmKey << std::endl;
          return 0;
          }
        }
      else
        {
        std::cerr << "shmget failed" << std::endl;
        return 0;
        }
      }
    return 1;
  }

  int nitroBase::DeallocateSharedMemory()
  {
    if(this->SharedMemoryArea && (shm_id >= 0))
      {
      // Detach and remove memory
      // TODO: Add counter of mutex to be sure no one else is accessing memory
      if(shmdt(this->SharedMemoryArea) >= 0)
        {
        if(shmctl(this->shm_id, IPC_RMID, NULL) >= 0)
          {
          std::cerr << "Shared Memory deallocation succeed" << std::endl;
          }
        else
          {
          return 0;
          }
        }
      else
        {
        return 0;
        }
      }
    return 1;
  }

} // end namespace nitro
