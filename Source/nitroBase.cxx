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
    this->NumOfAttributes = 0;
    this->AccessCounter = 0;
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
          return 1;
          }
        }
      }
    return 0;
  }

  //----------------------------------------------------------------------------------------------------

  // Memory organization:
  //
  // FIELD_LENGTH = 256
  // FIELD_PER_ATTRIBUTE = 3
  // MAX_ATTRIBUTES = 100
  //
  // SharedMemoryArea                                                                       SharedMemoryArea + MEMORY_SIZE
  // |                                                                                                    |
  // V                                                                                                    V
  //
  // 0              4              516            772            776                                 MEMORY_SIZE
  // --------------------------------------------------------------------------   -------------------------
  // |  Timestamp1  |      Key1     |    Value1    |  Timestamp2  |    ...         Key100  |   Value100   |
  // --------------------------------------------------------------------------   -------------------------
  //
  // ^   4 bytes        256 bytes       256 bytes  ^                                                      ^
  // |_____________________________________________|___________________________   ________________________|
  //                    Attribute 1                          Attribute 2                Attribute 100


  //----------------------------------------------------------------------------------------------------

  int nitroBase::AddAttribute(const char* key, const char* value)
  {
    if(this->SharedMemoryArea)
      {
      if(strcasecmp(key,""))
        {
        char* valueKey = this->GetKeyValue(key);
        if(valueKey)
          {
          this->ModifyAttribute(key, value);
          }
        else
          {
          // New key. Add key and value in shared memory
          int memoffset = this->NumOfAttributes*ATTRIBUTE_SIZE;

          if(memoffset <= MEMORY_SIZE)
            {
            this->AccessCounter++;

            // Get Atribute pointer
            char* dptr = (char*)(this->SharedMemoryArea) + memoffset;

            // Set Timestamp
            unsigned int* tsptr = (unsigned int*)dptr;
            *tsptr = this->AccessCounter;

            // Set Key and Value
            strncpy(dptr + KEY_OFFSET, key, FIELD_LENGTH*sizeof(char));
            strncpy(dptr + VALUE_OFFSET, value, FIELD_LENGTH*sizeof(char));
            this->NumOfAttributes++;
            return 1;
            }
          }
        }
      }
    return 0;
  }

//----------------------------------------------------------------------------------------------------

  int nitroBase::ModifyAttribute(const char* key, const char* value)
  {
    if(this->SharedMemoryArea)
      {
      if(strcasecmp(key,""))
        {
        char* valueKey = this->GetKeyValue(key);
        if(valueKey)
          {
          // Key already exists. Overwrite value if different (case insensitive)
          if(strcasecmp(valueKey, value) != 0)
            {
            this->AccessCounter++;

            // Set new Timestamp
            unsigned int* tsptr = (unsigned int*)(valueKey - VALUE_OFFSET);
            *tsptr = this->AccessCounter;

            // Set new Value
            strncpy(valueKey, value, FIELD_LENGTH*sizeof(char));
            return 1;
            }
          }
        }
      }
    return 0;
  }

//----------------------------------------------------------------------------------------------------
// NULL can't be printed directly. Need to be converted in void* or check return of function before displaying

  char* nitroBase::GetKeyValue(const char* key)
  {
    if(this->SharedMemoryArea)
      {
      if(strcasecmp(key,""))
        {
        // Set start pointer, end pointer, and iterator pointer
        char* sptr = (char*)(this->SharedMemoryArea);
        char* eptr = sptr + this->NumOfAttributes*ATTRIBUTE_SIZE;
        char* ptr = sptr;

        // Look for required key in array (limited to number of fields). Return value if found, NULL otherwise
        while(ptr < eptr)
          {
          char* curKey = ptr + KEY_OFFSET;
          char* curVal = ptr + VALUE_OFFSET;

          // Case insensitive
          if(strcasecmp(key,curKey) == 0)
            {
            return curVal;
            }
          ptr+=ATTRIBUTE_SIZE;
          }
        }
      }
    return NULL;
  }

//----------------------------------------------------------------------------------------------------

  unsigned int nitroBase::GetKeyTimestamp(const char* key)
  {
    if(this->SharedMemoryArea)
      {
      if(strcasecmp(key,""))
        {
        // Set start pointer, end pointer, and iterator pointer
        char* sptr = (char*)(this->SharedMemoryArea);
        char* eptr = sptr + this->NumOfAttributes*ATTRIBUTE_SIZE;
        char* ptr = sptr;

        // Look for required key in array (limited to number of fields). Return value if found, NULL otherwise
        while(ptr < eptr)
          {

          char* curKey = ptr + KEY_OFFSET;
          unsigned int* curTs = (unsigned int*)ptr;

          // Case insensitive
          if(strcasecmp(key,curKey) == 0)
            {
            return *curTs;
            }
          ptr+=ATTRIBUTE_SIZE;
          }
        }
      }
    return 0;
  }

//----------------------------------------------------------------------------------------------------

  int nitroBase::RemoveAttribute(const char* key)
  {
    if(this->SharedMemoryArea)
      {
      if(strcasecmp(key,""))
        {
        // Set start pointer, end pointer, and iterator pointer
        char* sptr = (char*)(this->SharedMemoryArea);
        char* eptr = sptr + this->NumOfAttributes*ATTRIBUTE_SIZE;
        char* ptr = sptr;

        // Look for required key in array (limited to number of fields). Return value if found, NULL otherwise
        while(ptr < eptr)
          {
          char* curTs = ptr;
          char* curKey = ptr + KEY_OFFSET;
          char* curVal = ptr + VALUE_OFFSET;

          // Move array to erase key and value
          if(strcasecmp(key,curKey) == 0)
            {
            // Move memory
            // Memory before moving: key1, val1, key2, val2, key3, val3.
            memmove(curTs, curVal + FIELD_LENGTH*sizeof(char), eptr - (curVal + FIELD_LENGTH*sizeof(char)));

            // Memory after moving: key1, val1, key3, val3, key3, val3 .Need to erase last one.
            memset(eptr - ATTRIBUTE_SIZE, 0x00, ATTRIBUTE_SIZE);
            this->NumOfAttributes--;
            return 1;
            }
          ptr+=ATTRIBUTE_SIZE;
          }
        }
      }
    return 0;
  }

//----------------------------------------------------------------------------------------------------

} // end namespace nitro
