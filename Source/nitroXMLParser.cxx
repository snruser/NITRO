/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

  =========================================================================*/

#include "nitroJointTypes.h"
#include "nitroXMLParser.h"

#include <fstream>
#include <iostream>

namespace nitro {

//---------------------------------------------------------------------------

  XMLParser::XMLParser()
  {
    this->TagNode = NULL;

    this->HardwareName = "";
    this->DegreesOfFreedom = 0;
    this->NumberOfJoints = 0;
  }

//---------------------------------------------------------------------------

  XMLParser::~XMLParser()
  {
  }

//---------------------------------------------------------------------------

  int XMLParser::SetXMLPath(const char* path)
  {
    std::fstream xmlFile;
    xmlFile.open(path);
    if(xmlFile.is_open())
      {
      // Path is correct
      xmlFile.close();

      // Remove previous path if already set
      this->XMLPath.clear();

      // Set new path
      this->XMLPath.assign(path);

      return 1;
      }
    return 0;
  }

//---------------------------------------------------------------------------

  const char* XMLParser::GetXMLPath()
  {
    if(this->XMLPath.empty())
      {
      return NULL;
      }
    return this->XMLPath.c_str();
  }

//---------------------------------------------------------------------------

  void XMLParser::Parse()
  {
    if(!this->XMLPath.empty())
      {
      std::ifstream xmlFile;
      xmlFile.open(this->XMLPath.c_str());

      // Read buffer and add \0 at the end
      xmlFile.seekg(0, std::ios::end);
      size_t length = xmlFile.tellg();
      xmlFile.seekg(0, std::ios::beg);
      char* buffer = new char[length + 1];
      xmlFile.read(buffer, length);
      buffer[length] = '\0';
      xmlFile.close();

      // Parse XML File with RapidXML
      this->XMLDoc.parse<0>(buffer);

      delete[] buffer;
      }

    this->GetHardwareName();
    this->GetDegreesOfFreedom();
    this->GetJointList();
  }

//---------------------------------------------------------------------------

  void XMLParser::GetHardwareName()
  {
    if(this->XMLDoc.first_node("RobotName"))
      {
      rapidxml::xml_node<>* hn = this->XMLDoc.first_node("RobotName");
      if(hn)
        {
        this->HardwareName.assign(hn->value());
        }
      }
  }

//---------------------------------------------------------------------------

  void XMLParser::GetDegreesOfFreedom()
  {
    if(this->XMLDoc.first_node("DegreesOfFreedom"))
      {
      rapidxml::xml_node<>* dof = this->XMLDoc.first_node("DegreesOfFreedom");
      if(dof)
        {
        this->DegreesOfFreedom = this->ConvertFromString<int>(dof->value());
        }
      }
  }

//---------------------------------------------------------------------------

  // TODO: Check required fields and optional
  void XMLParser::GetJointList()
  {
    if(this->XMLDoc.first_node("Joint"))
      {
      for(rapidxml::xml_node<>* n = this->XMLDoc.first_node("Joint"); n; n = n->next_sibling("Joint"))
        {
        Joint::Pointer newJoint = Joint::New();
        
        // Joint Name
        if(rapidxml::xml_node<>* tmpNode = n->first_node("Name"))
          {
          if(strcmp(tmpNode->value(), ""))
            {
            newJoint->SetName(tmpNode->value());
            }
          }
        
        // Joint Description
        if(rapidxml::xml_node<>* tmpNode = n->first_node("Description"))
          {
          if(strcmp(tmpNode->value(), ""))
            {
            newJoint->SetDescription(tmpNode->value());
            }
          }

        // Joint Group
        if(rapidxml::xml_node<>* tmpNode = n->first_node("Group"))
          {
          if(strcmp(tmpNode->value(), ""))
            {
            newJoint->SetGroup(this->ConvertFromString<int>(tmpNode->value()));
            }
          }
        
        // Joint MotionType
        if(rapidxml::xml_node<>* tmpNode = n->first_node("MotionType"))
          {
          if(strcmp(tmpNode->value(), ""))
            {
            if(!strcasecmp(tmpNode->value(), "rotational"))
              {
              newJoint->SetMotionType(ROTATIONAL);
              }
            else if(!strcasecmp(tmpNode->value(), "linear"))
              {
              newJoint->SetMotionType(LINEAR);
              }
            }
          }

        // Joint Drive
        if(rapidxml::xml_node<>* tmpNode = n->first_node("Drive"))
          {
          if(strcmp(tmpNode->value(), ""))
            {
            if(!strcasecmp(tmpNode->value(), "Active"))
              {
              newJoint->SetDrive(ACTIVE);
              }
            else if(!strcasecmp(tmpNode->value(), "Passive"))
              {
              newJoint->SetDrive(PASSIVE);
              }
            }
          }
        
        // TODO: Check variables not empty
        // Joint MotionRange
        if(rapidxml::xml_node<>* tmpNode = n->first_node("MotionRange"))
          {
          struct MinMax temp;
          if(rapidxml::xml_node<>* tmpNode2 = tmpNode->first_node("Min"))
            {
            temp.Min = this->ConvertFromString<double>(tmpNode2->value());
            }
         if(rapidxml::xml_node<>* tmpNode3 = tmpNode->first_node("Max"))
            {
            temp.Max = this->ConvertFromString<double>(tmpNode3->value());
            } 
         newJoint->SetMotionRange(temp);
         }
        
        // Joint Speed
        if(rapidxml::xml_node<>* tmpNode = n->first_node("Speed"))
          {
          struct MinMaxFixed temp;
          if(rapidxml::xml_node<>* tmpNode2 = tmpNode->first_node("Min"))
            {
            temp.Min = this->ConvertFromString<double>(tmpNode2->value());
            }
         if(rapidxml::xml_node<>* tmpNode3 = tmpNode->first_node("Max"))
            {
            temp.Max = this->ConvertFromString<double>(tmpNode3->value());
            } 
         if(rapidxml::xml_node<>* tmpNode4 = tmpNode->first_node("Fixed"))
            {
            temp.Fixed = this->ConvertFromString<double>(tmpNode4->value());
            } 
         newJoint->SetSpeed(temp);
         }
        
        // Joint Acceleration
        if(rapidxml::xml_node<>* tmpNode = n->first_node("Acceleration"))
          {
          struct MinMaxFixed temp;
          if(rapidxml::xml_node<>* tmpNode2 = tmpNode->first_node("Min"))
            {
            temp.Min = this->ConvertFromString<double>(tmpNode2->value());
            }
         if(rapidxml::xml_node<>* tmpNode3 = tmpNode->first_node("Max"))
            {
            temp.Max = this->ConvertFromString<double>(tmpNode3->value());
            } 
         if(rapidxml::xml_node<>* tmpNode4 = tmpNode->first_node("Fixed"))
            {
            temp.Fixed = this->ConvertFromString<double>(tmpNode4->value());
            } 
         newJoint->SetAcceleration(temp);
         }
        
        // Joint Torque
        if(rapidxml::xml_node<>* tmpNode = n->first_node("Torque"))
          {
          struct MinMaxFixed temp;
          if(rapidxml::xml_node<>* tmpNode2 = tmpNode->first_node("Min"))
            {
            temp.Min = this->ConvertFromString<double>(tmpNode2->value());
            }
         if(rapidxml::xml_node<>* tmpNode3 = tmpNode->first_node("Max"))
            {
            temp.Max = this->ConvertFromString<double>(tmpNode3->value());
            } 
         if(rapidxml::xml_node<>* tmpNode4 = tmpNode->first_node("Fixed"))
            {
            temp.Fixed = this->ConvertFromString<double>(tmpNode4->value());
            } 
         newJoint->SetTorque(temp);
         } 

        // Joint Actuator
        if(rapidxml::xml_node<>* tmpNode = n->first_node("Actuator"))
          {
          struct Actuator temp;
          if(rapidxml::xml_node<>* tmpNode2 = tmpNode->first_node("Type"))
            {
            if(!strcasecmp(tmpNode2->value(), "DC"))
              {
              temp.Type = DC;
              }
            else if(!strcasecmp(tmpNode2->value(), "Stepping"))
              {
              temp.Type = STEPPING;
              }
            }
         if(rapidxml::xml_node<>* tmpNode3 = tmpNode->first_node("MotionType"))
            {
            if(!strcasecmp(tmpNode3->value(), "rotational"))
              {
              temp.MotionType = ROTATIONAL;
              }
            else if(!strcasecmp(tmpNode3->value(), "linear"))
              {
              temp.MotionType = LINEAR;
              }
            } 
         if(rapidxml::xml_node<>* tmpNode4 = tmpNode->first_node("Input"))
            {
            if(!strcasecmp(tmpNode4->value(), "position"))
              {
              temp.Input = POSITION;
              }
            else if(!strcasecmp(tmpNode4->value(), "speed"))
              {
              temp.Input = SPEED;
              }
            else if(!strcasecmp(tmpNode4->value(), "torque"))
              {
              temp.Input = TORQUE;
              }
            }
         if(rapidxml::xml_node<>* tmpNode5 = tmpNode->first_node("PPU"))
            {
            temp.PulsePerUnit = this->ConvertFromString<int>(tmpNode5->value());
            }
         if(rapidxml::xml_node<>* tmpNode6 = tmpNode->first_node("GearRatio"))
            {
            temp.GearRatio = this->ConvertFromString<double>(tmpNode6->value());
            }         
         newJoint->SetActuator(temp);
         }
        
        // Joint Sensor
        if(rapidxml::xml_node<>* tmpNode = n->first_node("Sensor"))
          {
          struct Sensor temp;
          if(rapidxml::xml_node<>* tmpNode2 = tmpNode->first_node("Type"))
            {
            if(!strcasecmp(tmpNode2->value(), "Encoder"))
              {
              temp.Type = ENCODER;
              }
            else if(!strcasecmp(tmpNode2->value(), "None"))
              {
              temp.Type = NONE;
              }
            }
          if(rapidxml::xml_node<>* tmpNode3 = tmpNode->first_node("MotionType"))
            {
            if(!strcasecmp(tmpNode3->value(), "rotational"))
              {
              temp.MotionType = ROTATIONAL;
              }
            else if(!strcasecmp(tmpNode3->value(), "linear"))
              {
              temp.MotionType = LINEAR;
              }
            }
          if(rapidxml::xml_node<>* tmpNode4 = tmpNode->first_node("CountsPerUnit"))
            {
            temp.CountsPerUnit = this->ConvertFromString<double>(tmpNode4->value());
            }
          newJoint->SetSensor(temp);
          }

        // Joint Landmark
        if(rapidxml::xml_node<>* tmpNode = n->first_node("Landmark"))
          {
          struct Landmark temp;
          if(rapidxml::xml_node<>* tmpNode2 = tmpNode->first_node("Home"))
            {
            temp.Home = this->ConvertFromString<double>(tmpNode2->value());
            }
          if(rapidxml::xml_node<>* tmpNode3 = tmpNode->first_node("Min"))
            {
            temp.Limits.Min = this->ConvertFromString<double>(tmpNode3->value());
            }
          if(rapidxml::xml_node<>* tmpNode4 = tmpNode->first_node("Max"))
            {
            temp.Limits.Max = this->ConvertFromString<double>(tmpNode4->value());
            }
          newJoint->SetLandmark(temp);
          }


        // Add new joints to the list
        this->JointList.push_back(newJoint);
        this->NumberOfJoints++;
        }
      }
  }

} // end namespace nitro
