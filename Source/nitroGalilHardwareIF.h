/*=========================================================================

  Program:   NeedlePusher
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

  =========================================================================*/

#ifndef  __nitroGalilHardwareIF_h
#define  __nitroGalilHardwareIF_h

// STD include
#include <sys/types.h>   /* for type definitions */
#include <sys/socket.h>  /* for socket API function calls */
#include <netinet/in.h>  /* for address structs */
#include <arpa/inet.h>   /* for sockaddr_in */
#include <stdio.h>       /* for printf() */
#include <stdlib.h>      /* for atoi() */
#include <string.h>      /* for strlen() */
#include <unistd.h>      /* for close() */

#include <iostream>
#include <sstream>
#include <vector>

// NITRO includes
#include "nitroHardwareIF.h"


// Communication information
#define MAX_LEN 1024
#define DISCOVERY_PORT 18888
#define COMMUNICATION_PORT 18889
#define MULTICAST_IP "239.255.19.56"

class  GalilHardwareIF : public nitro::HardwareIF
{
 public:
  typedef GalilHardwareIF          Self;
  typedef HardwareIF              Superclass;
  typedef nitro::SmartPointer<Self>  Pointer;
  typedef nitro::SmartPointer<const Self>  ConstPointer;

  nitroNewMacro(Self);
  nitroTypeMacro(GalilHardwareIF, HardwareIF);


//--------------------------------------------------
// Galil methods

  void Connect();
  void Command(const char* command);
  void Disconnect();

  int GetNumberOfDevices();
  std::string GetNthIPAsString(int i);

 protected:

// Description:
// Constructor/Destructor
  GalilHardwareIF();
  ~GalilHardwareIF();

 private:
  void DiscoverGalilBoards();
  void DisplayBoardsAvailable();
  void InitiateCommunication(int board);
  void RequestGalilBoardToConnect();

 private:
  std::vector<std::string> GalilList;
  int CommunicationSocket;

};

#endif
