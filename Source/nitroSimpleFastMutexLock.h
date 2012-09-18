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
  Module:    $RCSfile: itkSimpleFastMutexLock.h,v $
  Language:  C++
  Date:      $Date: 2008-12-22 19:05:42 -0500 (Mon, 22 Dec 2008) $
  Version:   $Revision: 3460 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

  Portions of this code are covered under the VTK copyright.
  See VTKCopyright.txt or http://www.kitware.com/VTKCopyright.htm for details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

  =========================================================================*/
#ifndef __nitroSimpleFastMutexLock_h
#define __nitroSimpleFastMutexLock_h

#include "nitroMacro.h"

#ifdef NITRO_USE_SPROC
#include <abi_mutex.h>
#endif

#ifdef NITRO_USE_PTHREADS
#include <pthread.h>
#endif

#if defined(_WIN32) && !defined(NITRO_USE_PTHREADS)
#include "nitroWindows.h"
#endif

namespace nitro
{

#ifdef NITRO_USE_SPROC
#include <abi_mutex.h>
  typedef abilock_t FastMutexType;
#endif

#ifdef NITRO_USE_PTHREADS
#include <pthread.h>
  typedef pthread_mutex_t FastMutexType;
#endif

#if defined(_WIN32) && !defined(NITRO_USE_PTHREADS)
#include <winbase.h>
  typedef CRITICAL_SECTION FastMutexType;
#endif

#ifndef NITRO_USE_SPROC
#ifndef NITRO_USE_PTHREADS
#ifndef _WIN32
  typedef int FastMutexType;
#endif
#endif
#endif

/** \class SimpleFastMutexLock
 * \brief Critical section locking class that can be allocated on the stack.
 *
 * SimpleFastMutexLock is used by FastMutexLock to perform mutex locking.
 * SimpleFastMutexLock is not a subclass of Object and is designed to be
 * allocated on the stack.
 *
 * \ingroup OSSystemObjects
 */

// Critical Section object that is not a nitroObject.
  class NITROCommon_EXPORT SimpleFastMutexLock
  {
  public:
    /** Standard class typedefs.  */
    typedef SimpleFastMutexLock       Self;

    /** Constructor and destructor left public purposely because of stack allocation. */
    SimpleFastMutexLock();
    ~SimpleFastMutexLock();

    /** Lock access. */
    void Lock() const;

    /** Unlock access. */
    void Unlock() const;

  protected:
    mutable FastMutexType   m_FastMutexLock;
  };

}//end nitro namespace
#endif
