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

namespace nitro {

  Controller::Controller()
  {
    this->m_LoopCycle = 1000; // 1000 microsecond

    this->m_Kinematics = NULL;
    this->m_NetworkIF  = NULL;
    this->m_HardwareIF = NULL;
    this->m_XMLParser  = NULL;

    this->m_InitializationStatus = 1;
  }

  Controller::~Controller()
  {
  }

  int Controller::Execute()
  {
    if (this->m_Kinematics)
      {
      return 0;
      }

    if (this->m_NetworkIF)
      {
      return 0;
      }

    if (this->m_HardwareIF)
      {
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
      // TODO: Add flag for initialization status. Check the flag before starting loop.
      //this->m_InitializationStatus = this->m_InitializationStatus & this->m_Kinematics->Initialize();
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
    double convertedTarget = 0.0;

    // Convert target in lists of target of each actuators
    if(this->m_Kinematics)
      {
      convertedTarget = this->m_Kinematics->Convert(target);
      }

    // Send targets to HardwareIF
    if(this->m_HardwareIF)
      {
      this->m_HardwareIF->Move(0, convertedTarget);
      }

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
