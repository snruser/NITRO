/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

  =========================================================================*/

#ifndef  __nitroXMLParser_h
#define  __nitroXMLParser_h

#include <fstream>
#include <iostream>
#include <cstring>

// NITRO Base class
#include "nitroBase.h"
#include "nitroJointTypes.h"
#include "nitroJoint.h"
#include "nitroLink.h"

// Rapid XML
#include "RapidXML/rapidxml.hpp"

namespace nitro {

  class NITROCommon_EXPORT XMLParser : public nitroBase
  {
  public:
    typedef XMLParser                   Self;
    typedef Object                      Superclass;
    typedef SmartPointer<Self>          Pointer;
    typedef SmartPointer<const Self>    ConstPointer;

    nitroNewMacro(Self);
    nitroTypeMacro(XMLParser, Object);

  public:

    int SetXMLPath(const char *path);
    const char* GetXMLPath();
    void Parse();

    // Templated method to help conversion from string to different type (int, double, float, ...)
    template <class T> T ConvertFromStringTo(const std::string& s)
      {
      if(!s.empty())
        {
        std::istringstream ss(s);
        T t;
        ss >> t;
        return t;
        }
      return (T)NULL;
      }

    const char* GetHardwareName() { return this->HardwareName.c_str(); };
    int GetDegreesOfFreedom() { return this->DegreesOfFreedom; };
    std::vector<Joint::Pointer> GetJointList() { return this->JointList; };

    int GetNumberOfJoints() { return this->NumberOfJoints; };
    int GetNumberOfLinks() { return this->NumberOfLinks; };

    // Description:
    // Initialization function. Could be overloaded.
    virtual void Initialize() {};

    // Description:
    // Close connections, delete classes
    virtual void Exit() {};


  protected:

    // Description:
    // Constructor/Destructor
    XMLParser();
    ~XMLParser();

    void ParseHardwareName();
    void ParseDegreesOfFreedom();
    void ParseLinks();
    void ParseJoints();

  protected:

    rapidxml::xml_document<> XMLDoc;
    rapidxml::xml_node<>* TagNode;
    std::string XMLPath;

    std::string HardwareName;
    int DegreesOfFreedom;
    std::vector<Link::Pointer> LinkList;
    std::vector<Joint::Pointer> JointList;
    int NumberOfJoints;
    int NumberOfLinks;
  };

} // end namespace nitro

#endif
