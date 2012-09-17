/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef  __nitroLink_h
#define  __nitroLink_h

#include "nitroConfigure.h"
#include "nitroObject.h"
#include "nitroObjectFactory.h"

namespace nitro {

class NITROCommon_EXPORT Link : public Object
{
 public:
  typedef Link          Self;
  typedef Object              Superclass;
  typedef SmartPointer<Self>  Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  nitroNewMacro(Self);
  nitroTypeMacro(Link, Object);

 public:

  void SetName(const char* name) { this->Name.assign(name); };
  const char* GetName() { return this->Name.c_str(); };
  void SetLength(double l) { this->Length = l; };
  double GetLength() { return this->Length; };

 protected:

  // Description:
  // Constructor/Destructor
  Link();
  ~Link();

 protected:
    
  std::string Name;
  double Length;

};

} // end namespace nitro

#endif


