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
  Module:    $RCSfile: itkMutexLock.h,v $
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
#ifndef __nitroMutexLock_h
#define __nitroMutexLock_h

#include "nitroObject.h"
#include "nitroObjectFactory.h"

#ifdef NITRO_USE_SPROC
#include <abi_mutex.h>
#endif

#ifdef NITRO_USE_PTHREADS
#include <pthread.h>
#endif

#ifdef NITRO_USE_WIN32_THREADS
#include "nitroWindows.h"
#endif

namespace nitro
{

#ifdef NITRO_USE_SPROC
  typedef abilock_t MutexType;
#endif

#ifdef NITRO_USE_PTHREADS
  typedef pthread_mutex_t MutexType;
#endif

#ifdef NITRO_USE_WIN32_THREADS
  typedef HANDLE MutexType;
#endif

#ifndef NITRO_USE_SPROC
#ifndef NITRO_USE_PTHREADS
#ifndef NITRO_USE_WIN32_THREADS
  typedef int MutexType;
#endif
#endif
#endif

/** \class SimpleMutexLock
 * \brief Simple mutual exclusion locking class.

 * SimpleMutexLock allows the locking of variables which are accessed
 * through different threads.  This header file also defines
 * SimpleMutexLock which is not a subclass of Object.
 *
 * \ingroup OSSystemObjects
 */
  class NITROCommon_EXPORT SimpleMutexLock
  {
  public:
    /** Standard class typedefs.  */
    typedef SimpleMutexLock       Self;

    /** Constructor and destructor left public purposely. */
    SimpleMutexLock();
    virtual ~SimpleMutexLock();

    /** Methods for creation and destruction through the object factory. */
    static SimpleMutexLock *New();
    //void Delete() {delete this;}

    /** Used for debugging and other run-time purposes. */
    virtual const char *GetNameOfClass() {return "nitroSimpleMutexLock";};

    /** Lock the MutexLock. */
    void Lock( void );

    /** Unlock the MutexLock. */
    void Unlock( void );

    /** Access the MutexType member variable from outside this class */
    MutexType& GetMutexLock()
      {
      return m_MutexLock;
      }
    const MutexType GetMutexLock() const
    {
      return m_MutexLock;
    }

  protected:
    MutexType   m_MutexLock;
  };

/** \class MutexLock
 * \brief Mutual exclusion locking class.
 *
 * MutexLock allows the locking of variables which are accessed
 * through different threads.  This header file also defines
 * SimpleMutexLock which is not a subclass of nitroObject.
 *
 * \ingroup OSSystemObjects
 */
  class NITROCommon_EXPORT MutexLock : public Object
  {
  public:
    /** Standard class typedefs. */
    typedef MutexLock       Self;
    typedef Object  Superclass;
    typedef SmartPointer<Self>  Pointer;
    typedef SmartPointer<const Self>  ConstPointer;

    /** Method for creation. */
    nitroNewMacro(Self);

    /** Run-time information. */
    nitroTypeMacro(MutexLock,Object);

    /** Lock the nitroMutexLock. */
    void Lock( void );

    /** Unlock the MutexLock. */
    void Unlock( void );

  protected:
    MutexLock() {}
    ~MutexLock() {}

    SimpleMutexLock   m_SimpleMutexLock;
    void PrintSelf(std::ostream& os) const;

  private:
    MutexLock(const Self&); //purposely not implemented
    void operator=(const Self&); //purposely not implemented
  };


  inline void MutexLock::Lock( void )
  {
    m_SimpleMutexLock.Lock();
  }

  inline void MutexLock::Unlock( void )
  {
    m_SimpleMutexLock.Unlock();
  }


}//end nitro namespace
#endif
