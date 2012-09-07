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

  XMLParser::XMLParser()
  {
  }

  XMLParser::~XMLParser()
  {
  }

  void XMLParser::Parse(const char* xmlFile)
  {
    std::ifstream fin(xmlFile);
    if(fin.fail()) { std::cerr << "Fail to open XML file" << std::endl; }
    else { std::cerr << "File open" << std::endl; }

    fin.seekg(0, std::ios::end);
    size_t length = fin.tellg();
    fin.seekg(0, std::ios::beg);
    char* buffer = new char[length + 1];
    fin.read(buffer, length);
    buffer[length] = '\0';

    fin.close();

    rapidxml::xml_document<> doc;
    doc.parse<0>(buffer);

    delete[] buffer;


    //----------------------------------------------------------------------------------------------------
    // TODO: Need to change this part (should match with NITRO xml file structure)

    int cd = 0;
    for(rapidxml::xml_node<>*n = doc.first_node()->first_node(); n; n = n->next_sibling())
      {
      std::cerr << "----------------------------------------------------------" << std::endl;
      std::cerr << "CD" << cd << std::endl;
      for(rapidxml::xml_node<>*z = n->first_node(); z; z = z->next_sibling())
        {
        std::cerr << z->name() << ":\t" << z->value() << std::endl; 
        }
      cd++;
      }

    //----------------------------------------------------------------------------------------------------
  }

} // end namespace nitro
