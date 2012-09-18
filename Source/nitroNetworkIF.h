/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

  =========================================================================*/

#ifndef  __nitroNetworkIF_h
#define  __nitroNetworkIF_h

#include "nitroConfigure.h"
#include "nitroObject.h"
#include "nitroObjectFactory.h"
#include "nitroMath.h"

namespace nitro {

  class NITROCommon_EXPORT NetworkIF : public Object
  {
  public:
    typedef NetworkIF                   Self;
    typedef Object                      Superclass;
    typedef SmartPointer<Self>          Pointer;
    typedef SmartPointer<const Self>    ConstPointer;

    nitroNewMacro(Self);
    nitroTypeMacro(NetworkIF, Object);

  public:

    // Description:
    // Connect to the remote host.
    virtual int Connect() { return 0; };

    // Description:
    // Disconnect from the remote host.
    virtual int Disconnect() { return 0; };

    // Description:
    // Check if the connection is alive.
    virtual int IsConnected() { return 0; };

    // Description:
    // Get target coordinates receviced from the remote host. GetTargets()
    // creates a list of coordinates in image coordinate system and
    // set them in 'vectors'.
    // Because GetTargets() checkes the connection status before fetching
    // target data, thus the caller does not need to call IsConnected() before
    // calling GetTargets().
    virtual int GetTargets(std::list< Vector >& vectors) { return 0; };

  protected:

    // Description:
    // Constructor/Destructor
    NetworkIF();
    ~NetworkIF();

  protected:

  };

} // end namespace nitro

#endif
