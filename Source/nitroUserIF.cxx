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
}

UserIF::~UserIF()
{
}

void UserIF::Print(const char *format, ...)
{
  std::cout << format;
}

void UserIF::PrintError(const char *format, ...)
{
  std::cerr << "ERROR: " << format;
}

  
} // end namespace nitro
