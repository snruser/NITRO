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

  //----------------------------------------------------------------------------------------------------

  nitroBase::nitroBase()
  {
    this->shm_id = -1;
    this->SharedMemoryArea = NULL;
    this->NumOfFields = 0;
  }

  //----------------------------------------------------------------------------------------------------

  nitroBase::~nitroBase()
  {
    if(this->SharedMemoryArea)
      {
      this->DeallocateSharedMemory();
      }
  }

  //----------------------------------------------------------------------------------------------------

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
    memset(this->SharedMemoryArea,0x00, MEMORY_SIZE);
    return 1;
  }

  //----------------------------------------------------------------------------------------------------

  int nitroBase::DeallocateSharedMemory()
  {
    if(this->SharedMemoryArea && (shm_id >= 0))
      {
      // Detach and remove memory
      if(shmdt(this->SharedMemoryArea) >= 0)
        {
        // IPC_RMID set the segment ready for destruction. As soon as number of processes attaches become 0, the segment is destroy
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

  //----------------------------------------------------------------------------------------------------
  // TODO: Implement update flag

  // Memory organization:
  //
  // FIELD_LENGTH = 256
  // MAX_FIELD = 500
  //
  // SharedMemoryArea                                                                       SharedMemoryArea + MEMORY_SIZE
  // |                                                                                                    |
  // V                                                                                                    V
  //
  // 0              256               512              768              1024                        MEMORY_SIZE
  // --------------------------------------------------------------------------   -------------------------
  // |      Key1     |      Value1     |      Key2      |     Value2     |  ...           |   Value 500   |
  // --------------------------------------------------------------------------   -------------------------
  //
  // ^                                 ^                                 ^                                ^
  // |_________________________________|_________________________________|_____   ________________________|
  //               Field 1                           Field 2                            Field 500


  //----------------------------------------------------------------------------------------------------

  int nitroBase::AddField(const char* key, const char* value)
  {
    if(this->SharedMemoryArea)
      {
      if(strcasecmp(key,""))
        {
        char* foundKey = this->GetField(key);
        if(foundKey)
          {
          // Key already exists. Overwrite value if different (case insensitive)
          if(strcasecmp(foundKey, value) != 0)
            {
            std::cerr << "Replace value by " << value <<  std::endl;
            strncpy(foundKey, value, FIELD_LENGTH*sizeof(char));
            }
          }
        else
          {
          // New key. Add key and value in shared memory
          int memoffset = this->NumOfFields*FIELD_LENGTH*sizeof(char)*2;
          if(memoffset <= MEMORY_SIZE)
            {
            char* dptr = (char*)(this->SharedMemoryArea) + memoffset;
            strncpy(dptr, key, FIELD_LENGTH*sizeof(char));
            strncpy(dptr + FIELD_LENGTH*sizeof(char), value, FIELD_LENGTH*sizeof(char));
            this->NumOfFields++;
            }
          }
        }
      }
    return 1;
  }

  //----------------------------------------------------------------------------------------------------
  // NULL can't be printed directly. Need to be converted in void* or check return of function before displaying

  char* nitroBase::GetField(const char* key)
  {
    if(this->SharedMemoryArea)
      {
      if(strcasecmp(key,""))
        {
        // Set start pointer, end pointer, and iterator pointer
        char* sptr = (char*)(this->SharedMemoryArea);
        char* eptr = sptr + this->NumOfFields*2*FIELD_LENGTH*sizeof(char);
        char* ptr = sptr;

        // Look for required key in array (limited to number of fields). Return value if found, NULL otherwise
        while(ptr < eptr)
          {
          char* curKey = ptr;
          char* curVal = ptr + FIELD_LENGTH*sizeof(char);

          // Case insensitive
          if(strcasecmp(key,curKey) == 0)
            {
            return curVal;
            }
          ptr+=FIELD_LENGTH*sizeof(char)*2;
          }
        }
      }
    return NULL;
  }

  //----------------------------------------------------------------------------------------------------

 int nitroBase::RemoveField(const char* key)
  {
    if(this->SharedMemoryArea)
      {
      if(strcasecmp(key,""))
        {
        // Set start pointer, end pointer, and iterator pointer
        char* sptr = (char*)(this->SharedMemoryArea);
        char* eptr = sptr + this->NumOfFields*2*FIELD_LENGTH*sizeof(char);
        char* ptr = sptr;

        // Look for required key in array (limited to number of fields). Return value if found, NULL otherwise
        while(ptr < eptr)
          {
          char* curKey = ptr;
          char* curVal = ptr + FIELD_LENGTH*sizeof(char);

          // Move array to erase key and value
          if(strcasecmp(key,curKey) == 0)
            {
            // Move memory
            // Memory before moving: key1, val1, key2, val2, key3, val3. 
            memmove(curKey, curVal + FIELD_LENGTH*sizeof(char), eptr - (curVal + FIELD_LENGTH*sizeof(char)));
            
            // Memory after moving: key1, val1, key3, val3, key3, val3 .Need to erase last one.
            memset(eptr - 2*FIELD_LENGTH*sizeof(char), 0x00, 2*FIELD_LENGTH);
            this->NumOfFields--;
            return 1;
            }
          ptr+=FIELD_LENGTH*sizeof(char)*2;
          }
        }
      }
    return 0;
  }

  //----------------------------------------------------------------------------------------------------

} // end namespace nitro
