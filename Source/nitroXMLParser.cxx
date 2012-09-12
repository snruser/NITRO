/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

  =========================================================================*/

#include "nitroXMLParser.h"

#include <fstream>
#include <iostream>

namespace nitro {

//---------------------------------------------------------------------------

  XMLParser::XMLParser()
  {
    this->ActuatorNode = NULL;
  }

//---------------------------------------------------------------------------

  XMLParser::~XMLParser()
  {
  }

//---------------------------------------------------------------------------

  void XMLParser::Parse(const char* xmlFile)
  {
    // Check if file exists
    std::ifstream fin(xmlFile);
    if(fin.fail()) { std::cerr << "Fail to open XML file" << std::endl; }

    // Read buffer and add \0 at the end
    fin.seekg(0, std::ios::end);
    size_t length = fin.tellg();
    fin.seekg(0, std::ios::beg);
    char* buffer = new char[length + 1];
    fin.read(buffer, length);
    buffer[length] = '\0';
    fin.close();

    // Parse XML File with RapidXML
    this->XMLDoc.parse<0>(buffer);

    delete[] buffer;
  }

//---------------------------------------------------------------------------

  void* XMLParser::GoToNextActuator()
  {
    if(!this->ActuatorNode)
      {
      if(this->XMLDoc.first_node("Actuator"))
        {
        this->ActuatorNode = this->XMLDoc.first_node("Actuator");
        }
      else
        {
        return NULL;
        }
      }
    else
      {
      if(this->ActuatorNode->next_sibling("Actuator"))
        {
        this->ActuatorNode = this->ActuatorNode->next_sibling("Actuator");
        }
      else
        {
        return NULL;
        }
      }
    return this->ActuatorNode;
  }

//---------------------------------------------------------------------------

  int XMLParser::GetNumberOfActuators()
  {
    int numberOfNodes = 0;

    for(rapidxml::xml_node<>* i = this->XMLDoc.first_node("Actuator"); i; i = i->next_sibling("Actuator"))
      {
      numberOfNodes++;
      }
    return numberOfNodes;
  }

//---------------------------------------------------------------------------

  std::string XMLParser::GetTagValue(const char* tag)
  {
    std::stringstream errorMsg;

    if(this->ActuatorNode)
      {
      if(this->ActuatorNode->first_node(tag))
        {
        return this->ActuatorNode->first_node(tag)->value();
        }

      errorMsg << "No \"" << tag << "\" tag in this node" << std::endl;
      return errorMsg.str();
      }

    errorMsg << "No actuator selected" << std::endl;
    return errorMsg.str();
  }

//---------------------------------------------------------------------------


} // end namespace nitro
