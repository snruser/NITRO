/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

  =========================================================================*/

#ifndef  __nitroOpenIGTLinkNetworkIF_h
#define  __nitroOpenIGTLinkNetworkIF_h

#include <cstring>

#include "nitroConfigure.h"
#include "nitroObject.h"
#include "nitroObjectFactory.h"
#include "nitroNetworkIF.h"

#include "igtlSessionManager.h"

namespace nitro {

  class NITROCommon_EXPORT OpenIGTLinkNetworkIF : public NetworkIF
  {
  public:
    typedef OpenIGTLinkNetworkIF          Self;
    typedef Object                      Superclass;
    typedef SmartPointer<Self>          Pointer;
    typedef SmartPointer<const Self>    ConstPointer;

    nitroNewMacro(Self);
    nitroTypeMacro(OpenIGTLinkNetworkIF, NetworkIF);

  public:

    // Description:
    // Configure the connector as a server and
    // set remote host information
    void ConfigureAsServer(int port);

    // Description:
    // Configure the connector as a client and
    // set remote host information
    void ConfigureAsClient(const char* hostname, int port);

    // Description:
    // Connect to the OpenIGTLink remote host.
    virtual int Connect();

    // Description:
    // Disconnect from the remote host.
    virtual int Disconnect();

    // Description:
    // Check if the connection is alive.
    virtual int IsConnected();

    // Description:
    // Get target coordinates receviced from the remote host. GetTargets()
    // creates a list of coordinates in image coordinate system and
    // set them in 'vectors'.
    // Because GetTargets() checkes the connection status before fetching
    // target data, thus the caller does not need to call IsConnected() before
    // calling GetTargets().
    virtual int GetTargets(std::list< Vector >& vectors);

    // Description:
    // Initialization function. Could be overloaded.
    virtual void Initialize();

    // Description:
    // Close connections, delete classes
    virtual void Exit();

  protected:

    // Description:
    // Constructor/Destructor
    OpenIGTLinkNetworkIF();
    ~OpenIGTLinkNetworkIF();

  protected:
    igtl::SessionManager::Pointer m_Session;

  };

} // end namespace nitro

#endif
