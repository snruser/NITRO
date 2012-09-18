/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

  =========================================================================*/

#include "nitroLink.h"

namespace nitro {

  Link::Link()
  {
    this->Name="Default link";
    this->Length = 0.0;
  }

  Link::~Link()
  {
  }

} // end namespace nitro
