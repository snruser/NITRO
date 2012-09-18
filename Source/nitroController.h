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
#include "nitroXMLParser.h"

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
    Kinematics::Pointer GetKinematics() { return this->m_Kinematics; }
    //template<typename smPointer> void SetKinematics(SmartPointer<smPointer> k) { this->m_Kinematics = k; };
    

    // Description:
    // Set/get pointer to NetworkIF class
    void        SetNetworkIF(NetworkIF* n)   { this->m_NetworkIF = n; }
    NetworkIF::Pointer  GetNetworkIF()   { return this->m_NetworkIF; }
    //template<typename smPointer> void SetNetworkIF(SmartPointer<smPointer> n) { this->m_NetworkIF = n; }


    // Description:
    // Set/get pointer to HardwareIF class
    void        SetHardwareIF(HardwareIF* h) { this->m_HardwareIF = h; }
    HardwareIF::Pointer GetHardwareIF() { return this->m_HardwareIF; }
    //template<typename smPointer> void SetHardwareIF(SmartPointer<smPointer> h) { this->m_HardwareIF = h; };

    // Description:
    // Set/get pointer to UserIF class
    void        SetUserIF(UserIF* u)         { this->m_UserIF = u; }
    UserIF::Pointer     GetUserIF()         { return this->m_UserIF; }
    //template<typename smPointer> void SetUserIF(SmartPointer<smPointer> u) { this->m_UserIF = u; };

    // Description:
    // Set/get pointer to UserIF class
    void        SetXMLParser(XMLParser* x)         { this->m_XMLParser = x; }
    XMLParser::Pointer     GetXMLParser()         { return this->m_XMLParser; }
    //template<typename smPointer> void SetXMLParser(SmartPointer<smPointer> x) { this->m_XMLParser = x; };

    // Description:
    // Specify main loop cylcle (microsecond)
    void SetLoopCycle(int c)  { this->m_LoopCycle = c; }
    int  GetLoopCycle()       { return this->m_LoopCycle; }

    // Description:
    // Initialize all classes and parse xml file (if exists) to fill them
    void Initialize();

    // Description:
    // Main loop 
    // TODO: Rename it
    void Loop() {};
    
    // Description:
    // Close connections, delete classes 
    void Exit();
    
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
    Kinematics::Pointer m_Kinematics;
    NetworkIF::Pointer  m_NetworkIF;
    HardwareIF::Pointer m_HardwareIF;
    UserIF::Pointer     m_UserIF;
    XMLParser::Pointer  m_XMLParser;
  };

} // end namespace nitro

#endif
