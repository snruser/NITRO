/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef  __nitroController_h
#define  __nitroController_h

#include "nitroConfigure.h"
#include "nitroObject.h"
#include "nitroObjectFactory.h"

// NITRO Classes
#include "nitroKinematics.h"
#include "nitroNetworkIF.h"
#include "nitroHardwareIF.h"
#include "nitroUserIF.h"

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
  void        SetKinematics(Kinematics* k) { this->m_Kinematics = k; }
  Kinematics* GetKinematics(Kinematics* k) { return this->m_Kinematics; }

  // Description:
  // Set/get pointer to NetworkIF class
  void        SetNetworkIF(NetworkIF* n)   { this->m_NetworkIF = n; }
  NetworkIF*  GetNetworkIF(NetworkIF* n)   { return this->m_NetworkIF; }

  // Description:
  // Set/get pointer to HardwareIF class
  void        SetHardwareIF(HardwareIF* h) { this->m_HardwareIF = h; }
  HardwareIF* GetHardwareIF(HardwareIF* h) { return this->m_HardwareIF; }

  // Description:
  // Set/get pointer to UserIF class
  void        SetUserIF(UserIF* u)         { this->m_UserIF = u; }
  UserIF*     GetUserIF(UserIF* u)         { return this->m_UserIF; }

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


