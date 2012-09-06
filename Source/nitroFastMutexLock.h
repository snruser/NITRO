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
  Module:    $RCSfile: itkFastMutexLock.h,v $
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
#ifndef __nitroFastMutexLock_h
#define __nitroFastMutexLock_h

#include "nitroObject.h"
#include "nitroSimpleFastMutexLock.h"
#include "nitroObjectFactory.h"

namespace nitro
{

/** \class FastMutexLock
 * \brief Critical section locking class.
 * 
 * FastMutexLock allows the locking of variables which are accessed 
 * through different threads.  This header file also defines 
 * SimpleFastMutexLock which is not a subclass of Object.
 * The API is identical to that of MutexLock, and the behavior is
 * identical as well, except on Windows 9x/NT platforms. The only difference
 * on these platforms is that MutexLock is more flexible, in that
 * it works across processes as well as across threads, but also costs
 * more, in that it evokes a 600-cycle x86 ring transition. The 
 * FastMutexLock provides a higher-performance equivalent (on 
 * Windows) but won't work across processes. Since it is unclear how,
 * in nitro, an object at the nitro level can be shared across processes
 * in the first place, one should use FastMutexLock unless one has
 * a very good reason to use MutexLock. If higher-performance equivalents
 * for non-Windows platforms (Irix, SunOS, etc) are discovered, they
 * should replace the implementations in this class
 *
 * \ingroup OSSystemObjects
 */
class NITROCommon_EXPORT FastMutexLock : public Object
{
public:
  /** Standard class typedefs. */
  typedef FastMutexLock       Self;
  typedef Object  Superclass;
  typedef SmartPointer<Self>  Pointer;
  typedef SmartPointer<const Self>  ConstPointer;
  
  /** Method for creation. */
  nitroNewMacro(Self);

  /** Run-time type information. */
  nitroTypeMacro(FastMutexLock,Object);

  /** Lock the nitroFastMutexLock. */
  void Lock();

  /** Unlock the FastMutexLock. */
  void Unlock();

protected:
  FastMutexLock() {}
  ~FastMutexLock() {}
  
  SimpleFastMutexLock   m_SimpleFastMutexLock;
  void PrintSelf(std::ostream& os) const;
  
private:
  FastMutexLock(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented
};


inline void FastMutexLock::Lock( void )
{
  m_SimpleFastMutexLock.Lock();
}

inline void FastMutexLock::Unlock( void )
{
  m_SimpleFastMutexLock.Unlock();
}


}//end nitro namespace
#endif

