/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef  __nitroConditionVariable_h
#define  __nitroConditionVariable_h

#include "nitroConfigure.h"
#include "nitroObject.h"


namespace nitro {

class NITROCommon_EXPORT Controller : public Object
{
public:
  /** Standard class typedefs. */
  typedef Controller          Self;
  typedef Object              Superclass;
  typedef SmartPointer<Self>  Pointer;
  typedef SmartPointer<const Self>  ConstPointer;
  
  /** Method for creation through the object factory. */
  nitroNewMacro(Self);
  
  /** Run-time type information (and related methods). */
  nitroTypeMacro(ConditionVariable, LightObject);

  /** Suspend execution of this thread until the condition is signaled. The
   *  argument is a SimpleMutex object that must be locked prior to calling
   *  this method.  */
  void Wait(SimpleMutexLock * mutex);

  /** Signal that the condition is true and release one waiting thread */
  void Signal();

  /** Signal that the condition is true and release all waiting threads */
  void Broadcast();

protected:
  ConditionVariable();
  ~ConditionVariable();

private:
  ConditionVariable(const Self & other);
  const Self & operator=( const Self & );
#ifdef NITRO_USE_PTHREADS
  pthread_cond_t m_ConditionVariable;
  MutexType      m_Mutex;
#else
  int m_NumberOfWaiters;                   // number of waiting threads
#ifdef WIN32
  CRITICAL_SECTION m_NumberOfWaitersLock;  // Serialize access to 
                                           // m_NumberOfWaiters

  HANDLE m_Semaphore;                      // Semaphore to queue threads 
  HANDLE m_WaitersAreDone;                 // Auto-reset event used by the
                                           // broadcast/signal thread to
                                           // wait for all the waiting
                                           // threads to wake up and
                                           // release the semaphore

  size_t m_WasBroadcast;                   // Keeps track of whether we
                                           // were broadcasting or signaling
#endif
#endif
};

} // end namespace nitro

#endif


