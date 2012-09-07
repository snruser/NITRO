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
  typedef Controller          Self;
  typedef Object              Superclass;
  typedef SmartPointer<Self>  Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  nitroNewMacro(Self);
  nitroTypeMacro(Controller, Object);

 public:
  // Description:
  // Set/get pointer to Kinematics class
  void        SetKinematics(Kinematics* k) { this->m_Kinematics; }
  Kinematics* GetKinematics(Kinematics* k) { return this->m_Kinematics; }

  // Description:
  // Set/get pointer to NetworkIF class
  void        SetNetworkIF(NetworkIF* k)   { this->m_NetworkIF; }
  NetworkIF*  GetNetworkIF(NetworkIF* k)   { return this->m_NetworkIF; }

  // Description:
  // Set/get pointer to HardwareIF class
  void        SetHardwareIF(HardwareIF* k) { this->m_HardwareIF; }
  HardwareIF* GetHardwareIF(HardwareIF* k) { return this->m_HardwareIF; }

  // Description:
  // Set/get pointer to UserIF class
  void        SetUserIF(UserIF* k)         { this->m_UserIF; }
  UserIF*     GetUserIF(UserIF* k)         { return this->m_UserIF; }

  // Description:
  // Specify main loop cylcle (microsecond)
  void SetLoopCycle(int c)  { this->m_LoopCycle = c; }
  int  GetLoopCycle()       { return this->m_LoopCycle; }
  
  // Description:
  // Run main loop. Note that this base class is implemented for
  // non-real-time OS. If you consider using real-time OS API for
  // hard real-time control of the loop, you may create a child
  // class and override this function.
  virtual void Execute();

 protected:

  // Description:
  // Constructor/Destructor
  Controller();
  ~Controller();

 protected:
  
  int m_LoopCycle;
  
  // Pointer to a kinmatics class
  Kinematics* m_Kinematics;
  NetworkIF*  m_NetworkIF;
  HardwareIF* m_HardwareIF;
  UserIF*     m_UserIF;

};

} // end namespace nitro

#endif


