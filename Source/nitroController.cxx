/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

  =========================================================================*/

#include "nitroController.h"

#include "nitroMath.h"
#include "nitroOSUtil.h"

#define MEMORY_SIZE 500*256*sizeof(char)

namespace nitro {

  Controller::Controller()
  {
    this->m_LoopCycle = 1000; // 1000 microsecond

    this->m_Kinematics = NULL;
    this->m_NetworkIF  = NULL;
    this->m_HardwareIF = NULL;
    this->m_UserIF     = NULL;
    this->m_XMLParser  = NULL;
  }

  Controller::~Controller()
  {
  }

  int Controller::Execute()
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

  void Controller::Initialize()
  {
    // Controller Shared Memory
    this->AllocateSharedMemory(SHM_CONTROLLER_AREA, MEMORY_SIZE, IPC_CREAT | 0644);

    if(this->m_Kinematics)
      {
      // Kinematics Shared Memory
      this->m_Kinematics->AllocateSharedMemory(SHM_KINEMATICS_AREA, MEMORY_SIZE, IPC_CREAT | 0644);

      // Initialization
      this->m_Kinematics->Initialize();
      }

    if(this->m_NetworkIF)
      {
      // Network Shared Memory
      this->m_NetworkIF->AllocateSharedMemory(SHM_NETWORK_AREA, MEMORY_SIZE, IPC_CREAT | 0644);

      // Initialization
      this->m_NetworkIF->Initialize();
      }

    if(this->m_HardwareIF)
      {
      // Hardware Shared Memory
      this->m_HardwareIF->AllocateSharedMemory(SHM_HARDWARE_AREA, MEMORY_SIZE, IPC_CREAT | 0644);
      
      // Initialization
      this->m_HardwareIF->Initialize();
      }

    if(this->m_UserIF)
      {
      // User Interface Shared Memory
      this->m_UserIF->AllocateSharedMemory(SHM_UI_AREA, MEMORY_SIZE, IPC_CREAT | 0644);

      // Initialization
      this->m_UserIF->Initialize();
      }

    if(this->m_XMLParser)
      {
      // XML Path should be set before calling Initialize
      if(!strcmp(this->m_XMLParser->GetXMLPath(),""))
        {
        this->m_XMLParser->Initialize();
        }
      }

    if(this->m_LogRecorder)
      {
      // File path should be set before calling Initialize
      if(!strcmp(this->m_LogRecorder->GetLogFile(),""))
        {
        this->m_LogRecorder->Initialize();
        }
      }
  }

  void Controller::Loop()
  {
    // TODO: Get targets
    // Get targets from NetworkIF of UserIF ?
    double target = 30.0;  // mm

    // Convert target in lists of target of each actuators
    double convertedTarget = this->m_Kinematics->Convert(target);

    // Send targets to HardwareIF
    this->m_HardwareIF->Move(0, convertedTarget);

    // Inverse kinematics

    // Send feedback position to NetworkIF

  }


  void Controller::Exit()
  {
    // TODO: delete classes ?

    if(this->m_Kinematics)
      {
      this->m_Kinematics->Exit();
      }

    if(this->m_NetworkIF)
      {
      this->m_NetworkIF->Exit();
      }

    if(this->m_HardwareIF)
      {
      this->m_HardwareIF->Exit();
      }

    if(this->m_UserIF)
      {
      this->m_UserIF->Exit();
      }

    if(this->m_XMLParser)
      {
      this->m_XMLParser->Exit();
      }

    if(this->m_LogRecorder)
      {
      this->m_LogRecorder->Exit();
      }
  }


} // end namespace nitro
