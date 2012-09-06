/*=========================================================================

  Program:   NITRO
  Language:  C

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef __nitroTypes_H
#define __nitroTypes_H

#include "nitroTypeConfig.h"

/* 8-bit integer type */
#if NITRO_SIZEOF_CHAR == 1
  typedef unsigned char nitroUint8;
  typedef char          nitroInt8;
#else
  # error "No native data type can represent an 8-bit integer."
#endif

/* 16-bit integer type */
#if NITRO_SIZEOF_SHORT == 2
  typedef unsigned short nitroUint16;
  typedef signed short   nitroInt16;
#elif NITRO_SIZEOF_INT == 2
  typedef unsigned int   nitroUint16;
  typedef signed int     nitroInt16;
#else
  # error "No native data type can represent a 16-bit integer."
#endif

/* 32-bit integer type */
#if NITRO_SIZEOF_INT == 4
  typedef unsigned int   nitroUint32;
  typedef signed int     nitroInt32;
#elif NITRO_SIZEOF_LONG == 4
  typedef unsigned long  nitroUint32;
  typedef signed long    nitroInt32;
#else
  # error "No native data type can represent a 32-bit integer."
#endif

/* 64-bit integer type */
#if defined(NITRO_TYPE_USE_LONG_LONG) && NITRO_SIZEOF_LONG_LONG == 8
  typedef unsigned long long nitroUint64;
  typedef signed long long   nitroInt64;
#elif NITRO_SIZEOF_INT == 8
  typedef unsigned int       nitroUint64;
  typedef signed int         nitroInt64;
#elif NITRO_SIZEOF_LONG == 8
  typedef unsigned long      nitroUint64;
  typedef signed long        nitroInt64;
#elif defined(NITRO_TYPE_USE___INT64) && NITRO_SIZEOF___INT64 == 8
  typedef unsigned __int64   nitroUint64;
  typedef signed __int64     nitroInt64;
#elif defined(NITRO_TYPE_USE_INT64_T) && NITRO_SIZEOF_INT64_T == 8
  typedef unsigned int64_t   nitroUint64;
  typedef signed int64_t     nitroInt64;
#else
  # error "No native data type can represent a 64-bit integer."
#endif

/* 32-bit floating point type */
#if NITRO_SIZEOF_FLOAT == 4
  typedef float              nitroFloat32;
#else
# error "No native data type can represent a 32-bit floating point value."
#endif

/* 64-bit floating point type */
#if NITRO_SIZEOF_DOUBLE == 8
  typedef double             nitroFloat64;
#else
# error "No native data type can represent a 64-bit floating point value."
#endif

/* 128-bit complex type */
typedef double nitroComplex[2];


#endif /* __nitroTypes_H */
