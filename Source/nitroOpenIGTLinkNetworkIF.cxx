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

  return this->m_Session->Connect();
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
}
  
} // end namespace nitro
