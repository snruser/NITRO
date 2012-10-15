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

// Shared Memory
#include <sys/types.h>
#include <sys/ipc.h>

// Nitro Base class
#include "nitroBase.h"

// NITRO Classes
#include "nitroKinematics.h"
#include "nitroNetworkIF.h"
#include "nitroHardwareIF.h"
#include "nitroUserIF.h"
#include "nitroXMLParser.h"
#include "nitroLogRecorder.h"

namespace nitro {

class NITROCommon_EXPORT Controller : public nitroBase
{
public:
typedef Controller               Self;
typedef Object                   Superclass;
typedef SmartPointer<Self>       Pointer;
typedef SmartPointer<const Self> ConstPointer;

nitroNewMacro(Self);
nitroTypeMacro(Controller, Object);

public:
// Description:
// Set/get pointer to Kinematics class
void        SetKinematics(Kinematics* k) { this->m_Kinematics = k; }
Kinematics::Pointer GetKinematics() { return this->m_Kinematics; }

// Description:
// Set/get pointer to NetworkIF class
void        SetNetworkIF(NetworkIF* n)   { this->m_NetworkIF = n; }
NetworkIF::Pointer  GetNetworkIF()   { return this->m_NetworkIF; }

// Description:
// Set/get pointer to HardwareIF class
void        SetHardwareIF(HardwareIF* h){ this->m_HardwareIF = h; }
HardwareIF::Pointer GetHardwareIF() { return this->m_HardwareIF; }

// Description:
// Set/get pointer to UserIF class
void        SetUserIF(UserIF* u)         { this->m_UserIF = u; }
UserIF::Pointer     GetUserIF()         { return this->m_UserIF; }

// Description:
// Set/get pointer to XMLParser class
void        SetXMLParser(XMLParser* x)         { this->m_XMLParser = x; }
XMLParser::Pointer     GetXMLParser()         { return this->m_XMLParser; }

// Description:
// Set/get pointer to XMLParser class
void        SetLogRecorder(LogRecorder* l)         { this->m_LogRecorder = l; }
LogRecorder::Pointer     GetLogRecorder()         { return this->m_LogRecorder; }

// Description:
// Specify main loop cylcle (microsecond)
void SetLoopCycle(int c)  { this->m_LoopCycle = c; }
int  GetLoopCycle()       { return this->m_LoopCycle; }

// Description:
// Initialize all classes and parse xml file (if exists) to fill them
virtual void Initialize();

// Description:
// Main loop
// TODO: Rename it
virtual void Loop();

// Description:
// Close connections, delete classes
virtual void Exit();

// Description:
// Run main loop. Note that this base class is implemented for
// non-real-time OS. If you consider using real-time OS API for
// hard real-time control of the loop, you may create a child
// class and override this function.
virtual int Execute();

protected:

// Description:
// Constructor/Destructor
Controller();
~Controller();

protected:

int m_LoopCycle;

// Pointer to a classes
Kinematics::Pointer  m_Kinematics;
NetworkIF::Pointer   m_NetworkIF;
HardwareIF::Pointer  m_HardwareIF;
UserIF::Pointer      m_UserIF;
XMLParser::Pointer   m_XMLParser;
LogRecorder::Pointer m_LogRecorder;
};

} // end namespace nitro

#endif
