/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkWin32Header.h,v $
  Language:  C++
  Date:      $Date: 2010-01-17 13:38:05 -0500 (Sun, 17 Jan 2010) $
  Version:   $Revision: 5577 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

  Portions of this code are covered under the VTK copyright.
  See VTKCopyright.txt or http://www.kitware.com/VTKCopyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __nitroWin32Header_h
#define __nitroWin32Header_h

#include "nitroConfigure.h"

// add in the Windows variants

#if defined(__CYGWIN__)
#ifndef WIN32
#define WIN32 1
#endif
#ifndef _WIN32
#define _WIN32 1
#endif
#endif

#if defined(_WIN32)
  // Include the windows header here only if requested by user code.
# if defined(NITRO_INCLUDE_WINDOWS_H)
#  include <windows.h>
   // Define types from the windows header file.
   typedef DWORD nitroWindowsDWORD;
   typedef PVOID nitroWindowsPVOID;
   typedef LPVOID nitroWindowsLPVOID;
   typedef HANDLE nitroWindowsHANDLE;
   typedef LPTHREAD_START_ROUTINE nitroWindowsLPTHREAD_START_ROUTINE;
# else
   // Define types from the windows header file.
   typedef unsigned long nitroWindowsDWORD;
   typedef void* nitroWindowsPVOID;
   typedef nitroWindowsPVOID nitroWindowsLPVOID;
   typedef nitroWindowsPVOID nitroWindowsHANDLE;
   typedef nitroWindowsDWORD (__stdcall *nitroWindowsLPTHREAD_START_ROUTINE)(nitroWindowsLPVOID);
# endif

#if ( _MSC_VER >= 1300 ) // Visual studio .NET
#pragma warning ( disable : 4311 )
#pragma warning ( disable : 4312 )
#  define nitroGetWindowLong GetWindowLongPtr
#  define nitroSetWindowLong SetWindowLongPtr
#  define nitroLONG LONG_PTR
#  define nitroGWL_WNDPROC GWLP_WNDPROC
#  define nitroGWL_HINSTANCE GWLP_HINSTANCE
#  define nitroGWL_USERDATA GWLP_USERDATA
#else // older or non-Visual studio
#  define nitroGetWindowLong GetWindowLong
#  define nitroSetWindowLong SetWindowLong
#  define nitroLONG LONG
#  define nitroGWL_WNDPROC GWL_WNDPROC
#  define nitroGWL_HINSTANCE GWL_HINSTANCE
#  define nitroGWL_USERDATA GWL_USERDATA
#endif //
#endif


#if defined(_MSC_VER)
  // Enable MSVC compiler warning messages that are useful but off by default.
# pragma warning ( default : 4263 ) /* no override, call convention differs */
  // Disable MSVC compiler warning messages that often occur in valid code.
# if !defined(NITRO_DISPLAY_WIN32_WARNINGS)
#  pragma warning ( disable : 4003 ) /* not enough actual parameters for macro */
#  pragma warning ( disable : 4097 ) /* typedef is synonym for class */
#  pragma warning ( disable : 4127 ) /* conditional expression is constant */
#  pragma warning ( disable : 4244 ) /* possible loss in conversion */
#  pragma warning ( disable : 4251 ) /* missing DLL-interface */
#  pragma warning ( disable : 4305 ) /* truncation from type1 to type2 */
#  pragma warning ( disable : 4309 ) /* truncation of constant value */
#  pragma warning ( disable : 4514 ) /* unreferenced inline function */
#  pragma warning ( disable : 4706 ) /* assignment in conditional expression */
#  pragma warning ( disable : 4710 ) /* function not inlined */
#  pragma warning ( disable : 4786 ) /* identifier truncated in debug info */
#  pragma warning ( disable : 4996 ) /* 'strncpy': This function or variable may be unsafe. */
# endif

// typename keyword in default template arguments is not accepted by
// MSVC.  This macro should only be used in such places.
# if !defined(CABLE_CONFIGURATION) && (_MSC_VER < 1310)
#  define NITRO_TYPENAME
# else
#  define NITRO_TYPENAME typename
# endif
#else
# define NITRO_TYPENAME typename
#endif

// MSVC 6.0 in release mode will warn about code it produces with its
// optimizer.  Disable the warnings specifically for this
// configuration.  Real warnings will be revealed by a debug build or
// by other compilers.
#if defined(_MSC_VER) && (_MSC_VER < 1300) && defined(NDEBUG)
# pragma warning ( disable : 4701 ) /* Variable may be used uninitialized.  */
# pragma warning ( disable : 4702 ) /* Unreachable code.  */
#endif

#if defined(__BORLANDC__)
  // Disable Borland compiler warning messages that often occur in valid code.
# if !defined(NITRO_DISPLAY_WIN32_WARNINGS)
#  pragma warn -8004 /* assigned a value that is never used */
#  pragma warn -8008 /* condition is always false */
#  pragma warn -8026 /* funcs w/class-by-value args not expanded inline */
#  pragma warn -8027 /* functions w/ do/for/while not expanded inline */
#  pragma warn -8060 /* possibly incorrect assignment */
#  pragma warn -8066 /* unreachable code */
#  pragma warn -8072 /* suspicious pointer arithmetic */
# endif
#endif

// NITRO_EXPORT can not be used
#define NITRO_EXPORT

#if (defined(_WIN32) || defined(WIN32)) && !defined(NITROSTATIC) 
# ifdef NITROCommon_EXPORTS
#  define NITROCommon_EXPORT __declspec(dllexport)
# else
#  define NITROCommon_EXPORT __declspec(dllimport)
# endif  /* NITROCommon_EXPORT */
#else
/* unix needs nothing */
#define NITROCommon_EXPORT 
#endif




#endif
