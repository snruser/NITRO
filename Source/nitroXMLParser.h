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

#include "nitroConfigure.h"
#include "nitroObject.h"
#include "nitroObjectFactory.h"
#include "nitroJoint.h"

// Rapid XML
#include "RapidXML/rapidxml.hpp"

namespace nitro {

  class NITROCommon_EXPORT XMLParser : public Object
  {
  public:
    typedef XMLParser           Self;
    typedef Object              Superclass;
    typedef SmartPointer<Self>  Pointer;
    typedef SmartPointer<const Self>  ConstPointer;

    nitroNewMacro(Self);
    nitroTypeMacro(XMLParser, Object);

  public:

    int SetXMLPath(const char *path);
    const char* GetXMLPath();
    void Parse();

    // Templated method to help conversion from string to different type (int, double, float, ...)
    template <class T> T ConvertFromString(const std::string& s)
      {
	if(!s.empty())
	  {
	    std::istringstream ss(s);
	    T t;
	    ss >> t;
	    return t;
	  }
	return NULL;
      }


  protected:

    // Description:
    // Constructor/Destructor
    XMLParser();
    ~XMLParser();

    void GetHardwareName();
    void GetDegreesOfFreedom();
    void GetJointList();

  protected:

    rapidxml::xml_document<> XMLDoc;
    rapidxml::xml_node<>* TagNode;
    std::string XMLPath;


    std::string HardwareName;
    int DegreesOfFreedom;
    //std::vector<Link*> LinkList;
    std::vector<Joint::Pointer> JointList;
    int NumberOfJoints;
  };

} // end namespace nitro

#endif
