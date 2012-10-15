/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

  =========================================================================*/

#include "nitroOpenIGTLinkNetworkIF.h"

namespace nitro {

  OpenIGTLinkNetworkIF::OpenIGTLinkNetworkIF()
  {
    this->m_Session = igtl::SessionManager::New();

    // Set Handler
    //TransformHandler::Pointer tmh = TransformHandler::New();
    //PositionHandler::Pointer pmh  = PositionHandler::New();
    //ImageHandler::Pointer imh     = ImageHandler::New();

    //this->m_Session->ClearMessageHandler();
    //this->m_Session->AddMessageHandler(tmh);
    //this->m_Session->AddMessageHandler(pmh);
    //this->m_Session->AddMessageHandler(imh);

  }

  OpenIGTLinkNetworkIF::~OpenIGTLinkNetworkIF()
  {
  }

  void OpenIGTLinkNetworkIF::ConfigureAsServer(int port)
  {
    if (this->m_Session.IsNotNull())
      {
      this->m_Session->SetMode(igtl::SessionManager::MODE_SERVER);
      this->m_Session->SetPort(port);
      }
  }

  void OpenIGTLinkNetworkIF::ConfigureAsClient(const char* hostname, int port)
  {
    if (this->m_Session.IsNotNull())
      {
      this->m_Session->SetMode(igtl::SessionManager::MODE_CLIENT);
      this->m_Session->SetHostname(hostname);
      this->m_Session->SetPort(port);
      }
  }

  int OpenIGTLinkNetworkIF::Connect()
  {
    // Check if the session manager is available
    if (!this->m_Session.IsNotNull())
      {
      return 0;
      }
    std::cerr << "Connecting..." << std::endl;

    if(!this->m_Session->Connect())
      {
      std::cerr << "Connection timeout" << std::endl;
      return 0;
      }
    return 1;
  }

  int OpenIGTLinkNetworkIF::Disconnect()
  {
    return this->m_Session->Disconnect();
  }

  int OpenIGTLinkNetworkIF::IsConnected()
  {
    return 1;
    // this->m_Session->IsConnected();
  }

  int OpenIGTLinkNetworkIF::GetTargets(std::list< Vector >& vectors)
  {
    if (!this->m_Session.IsNotNull())
      {
      return 0;
      }

    int r = this->m_Session->ProcessMessage();
    if (r == 0) // Disconnected
      {
      this->m_Session->Disconnect();
      return 0;
      }

    // message received
    return 1;
  }

  void OpenIGTLinkNetworkIF::Initialize()
  {
    std::cerr << "OpenIGTLinkNetworkIF initialization" << std::endl;
    
    // 10/15/2012 ayamada: !!You have to decide the variable i!! 
    int i = 0;
    switch(this->m_Session->GetMode(i))
      {
      // Server
      case igtl::SessionManager::MODE_SERVER:
        {
        if(this->m_Session->GetPort())
          {
          this->Connect();
          }
        else
          {
          std::cerr << "ERROR: As server, port should be set" << std::endl;
          }
        break;
        }

        // Client
      case igtl::SessionManager::MODE_CLIENT:
        {
        if(this->m_Session->GetPort() && !strcmp(this->m_Session->GetHostname(),""))
          {
          this->Connect();
          }
        else
          {
          std::cerr << "ERROR: As client, port and hostname should be set" << std::endl;
          }
        break;
        }

        // Default
      default:
        {
        break;
        }
      }
  }

  void OpenIGTLinkNetworkIF::Exit()
  {
    if(this->m_Session)
      {
      this->Disconnect();
      }
  }

} // end namespace nitro
