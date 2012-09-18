/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

  =========================================================================*/

#include "nitroNeedlePusherController.h"

#include "nitroMath.h"
#include "nitroOSUtil.h"

namespace nitro {

  NeedlePusherController::NeedlePusherController()
  {
    this->m_LoopCycle = 1000; // 1000 microsecond

    this->m_Kinematics = NULL;
    this->m_NetworkIF  = NULL;
    this->m_HardwareIF = NULL;
    this->m_UserIF     = NULL;
    this->m_XMLParser  = NULL;
  }

  NeedlePusherController::~NeedlePusherController()
  {
  }

  int NeedlePusherController::Execute()
  {

    // Before start using this->m_UserIF->Print() and this->m_UserIF->PrintError(),
    // make sure that UserIF is set.
    if (this->m_UserIF)
      {
      std::cerr << "ERROR: NO user interface has found." << std::endl;
      return 0;
      }

    if (this->m_Kinematics)
      {
      this->m_UserIF->PrintError("No Kinematic class has been set.\n");
      return 0;
      }

    if (this->m_NetworkIF)
      {
      this->m_UserIF->PrintError("No NetworkIF class has been set.\n");
      return 0;
      }

    if (this->m_HardwareIF)
      {
      this->m_UserIF->PrintError("No HardwareIF class has been set.\n");
      return 0;
      }

    // ------------------------------
    // Check number of end effectors
    //int nEffectors = this->m_HardwareIF->GetNumberOfEndEffectors();
    int nEffectors = 1;
    //this->NetworkIF->SetNEffectors(nEffectors);

    std::list< Matrix > targets;
    targets.resize(nEffectors);

    // ------------------------------
    // Initialize
    this->m_UserIF->Print("Initializing.\n");

    while (1)
      {
      //this->NetworkIF->GetTarget(targets);

      // The following code is tentative.
      Sleep(10);
      }
  }

  void NeedlePusherController::Initialize()
  {
    // Parse XML File and create Joints list and Links list
    if(this->m_XMLParser)
      {
      std::cerr << "Parse XML" << std::endl;
      this->m_XMLParser->Parse();
      }

    if(this->m_NetworkIF)
      {
      std::cerr << "Connect OpenIGTLink" << std::endl;
      if(this->m_NetworkIF->Connect())
        {
        std::cerr << "Client connected" << std::endl;
        }
      else
        {
        std::cerr << "Timeout" << std::endl;
        }
      }

    if(this->m_HardwareIF)
      {
      GalilHardwareIF* GalilIF = dynamic_cast<GalilHardwareIF*>(this->m_HardwareIF.GetPointer());
      GalilIF->Connect();
      }

  }

  void NeedlePusherController::Exit()
  {
    if(this->m_NetworkIF)
      {
      std::cerr << "Disconnect" << std::endl;
      // TODO: Check if connected
      this->m_NetworkIF->Disconnect();
      }
  }


} // end namespace nitro