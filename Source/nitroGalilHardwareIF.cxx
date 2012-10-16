/*=========================================================================

  Program:   NeedlePusher
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

  =========================================================================*/

#include "nitroGalilHardwareIF.h"

namespace nitro {

  //----------------------------------------------------------------------------------------------------

  GalilHardwareIF::GalilHardwareIF()
  {
  }

  //----------------------------------------------------------------------------------------------------

  GalilHardwareIF::~GalilHardwareIF()
  {
  }

  //----------------------------------------------------------------------------------------------------

  void GalilHardwareIF::Connect()
  {
    this->DiscoverGalilBoards();

    /* Display all boards available */
    this->DisplayBoardsAvailable();

    /* Autoconnection if only 1 board detected */
    if(this->GalilList.size() == 1)
      {
      this->InitiateCommunication(0);
      }
    else
      {
      this->RequestGalilBoardToConnect();
      }
  }

  //----------------------------------------------------------------------------------------------------

  void GalilHardwareIF::DiscoverGalilBoards()
  {
    int sock;                     /* socket descriptor */
    int flag_on = 1;              /* socket option flag */
    char send_str[MAX_LEN];       /* string to send */
    struct sockaddr_in mc_addr;   /* socket address structure */
    unsigned int send_len;        /* length of string to send */
    struct ip_mreq mc_req;        /* multicast request structure */
    char recv_str[MAX_LEN+1];     /* buffer to receive string */
    int recv_len;                 /* length of string received */
    struct sockaddr_in from_addr; /* packet source */
    unsigned int from_len;        /* source addr length */

    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

    /* create a socket for sending to the multicast address */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
    perror("UDP socket() failed");
    exit(1);
    }

    /* receive replies from anyone */
    memset(&mc_addr, 0, sizeof(mc_addr));
    mc_addr.sin_family      = AF_INET;
    mc_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    mc_addr.sin_port        = htons(DISCOVERY_PORT);

    /* set reuse port to on to allow multiple binds per host */
    if ((setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &flag_on,
                    sizeof(flag_on))) < 0) {
    perror("setsockopt() failed");
    exit(1);
    }

    /* bind to multicast address to socket */
    if ((bind(sock, (struct sockaddr *) &mc_addr,
              sizeof(mc_addr))) < 0) {
    perror("bind() failed");
    exit(1);
    }

    /* construct a multicast address structure */
    mc_addr.sin_addr.s_addr = inet_addr(MULTICAST_IP);

    /* clear send buffer */
    memset(send_str, 0, sizeof(send_str));

    /* set command 0x0D = \r */
    send_str[0] = 0x0D;
    send_len = strlen(send_str);

    /* send string to multicast address */
    if ((sendto(sock, send_str, send_len, 0,
                (struct sockaddr *) &mc_addr,
                sizeof(mc_addr))) != send_len) {
    perror("sendto() sent incorrect number of bytes");
    exit(1);
    }

    /* clear send buffer */
    memset(send_str, 0, sizeof(send_str));

    /* construct an IGMP join request structure */
    mc_req.imr_multiaddr.s_addr = inet_addr(MULTICAST_IP);
    mc_req.imr_interface.s_addr = htonl(INADDR_ANY);

    /* send an ADD MEMBERSHIP message via setsockopt */
    if ((setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP,
                    (void*) &mc_req, sizeof(mc_req))) < 0) {
    perror("setsockopt() failed");
    exit(1);
    }

    /* clear the receive buffers & structs */
    memset(recv_str, 0, sizeof(recv_str));
    from_len = sizeof(from_addr);
    memset(&from_addr, 0, from_len);

    /* Receive data */
    fd_set socks;
    FD_ZERO(&socks);
    FD_SET(sock, &socks);
    while(select(sock + 1, &socks, NULL, NULL, &timeout) > 0)
      {
      recvfrom(sock, recv_str, MAX_LEN, 0, (struct sockaddr*)&from_addr, &from_len);
      std::string IPAddress(inet_ntoa(from_addr.sin_addr));
      this->GalilList.push_back(IPAddress);
      }

    /* send a DROP MEMBERSHIP message via setsockopt */
    if ((setsockopt(sock, IPPROTO_IP, IP_DROP_MEMBERSHIP,
                    (void*) &mc_req, sizeof(mc_req))) < 0) {
    perror("setsockopt() failed");
    exit(1);
    }

    /* Close connection */
    std::string clear_cmd("IHS=>-1\r");
    send_len = strlen(clear_cmd.c_str());

    /* send string to multicast address */
    if ((sendto(sock, clear_cmd.c_str(), send_len, 0,
                (struct sockaddr *) &mc_addr,
                sizeof(mc_addr))) != send_len) {
    perror("close connection failed");
    exit(1);
    }

    close(sock);
  }

  //----------------------------------------------------------------------------------------------------

  void GalilHardwareIF::DisplayBoardsAvailable()
  {
    std::cerr << "Galil boards detected" << std::endl;
    std::cerr << "---------------------------" << std::endl;

    for(int i=0; i < this->GalilList.size(); i++)
      {
      std::cerr << "  #" << i << "\t " << this->GalilList[i].c_str() << std::endl;
      std::cerr << "---------------------------" << std::endl;
      }
  }

  //----------------------------------------------------------------------------------------------------

  void GalilHardwareIF::RequestGalilBoardToConnect()
  {
    int selectedBoard = 0;

    std::cerr << std::endl;
    std::cerr << "Connect to board: ";
    std::cin >> selectedBoard;

    if(selectedBoard == -1)
      {
      this->Exit();
      return;
      }

    if(selectedBoard >= 0   && selectedBoard < this->GalilList.size())
      {
      this->InitiateCommunication(selectedBoard);
      }
    else
      {
      std::cerr << "Invalid board number" << std::endl;
      this->RequestGalilBoardToConnect();
      }
  }

  //----------------------------------------------------------------------------------------------------

  void GalilHardwareIF::InitiateCommunication(int board)
  {
    int flag_on = 1;               /* socket option flag */
    struct sockaddr_in com_addr;   /* socket address structure */

    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

    std::cerr << "Connecting to " << this->GalilList[board].c_str() << "..." << std::endl;
    if((this->CommunicationSocket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
      {
      perror("TCP socket() failed");
      exit(1);
      }

    memset(&com_addr, 0, sizeof(com_addr));
    com_addr.sin_family = AF_INET;
    com_addr.sin_addr.s_addr = inet_addr(this->GalilList[board].c_str());
    com_addr.sin_port = htons(COMMUNICATION_PORT);

    if(connect(this->CommunicationSocket, (const struct sockaddr*)&com_addr, sizeof(com_addr)) < 0)
      {
      perror("connect() failed");
      exit(1);
      }

    std::cerr << "Connected" << std::endl;
  }

  //----------------------------------------------------------------------------------------------------

  void GalilHardwareIF::Command(const char *command)
  {
    if(this->CommunicationSocket < 0)
      {
      perror("Socket not connected");
      exit(1);
      }

    /* Add cariage return at the end of command */
    std::stringstream completedCommand;
    completedCommand << command << "\r";
    int commandLength = strlen(completedCommand.str().c_str());

    /* Send command */
    if(send(this->CommunicationSocket,completedCommand.str().c_str(), commandLength, 0) < commandLength)
      {
      perror("Cannot send data");
      exit(1);
      }

    /* Wait for reply and read it */
    char reply[MAX_LEN];
    memset(&reply, 0, MAX_LEN);

    if(recv(this->CommunicationSocket, reply, MAX_LEN, 0) < 0)
      {
      perror("Couldn't receive data");
      exit(1);
      }
  }

  //----------------------------------------------------------------------------------------------------

  void GalilHardwareIF::Disconnect()
  {
    if(this->CommunicationSocket > 0)
      {
      // TODO: Send MO command to turn off motor on every axis
      close(this->CommunicationSocket);
      }
  }

  //----------------------------------------------------------------------------------------------------

  int GalilHardwareIF::GetNumberOfDevices()
  {
    return GalilList.size();
  }

  //----------------------------------------------------------------------------------------------------

  std::string GalilHardwareIF::GetNthIPAsString(int i)
  {
    if(i < GalilList.size())
      {
      return GalilList[i];
      }
    return "(empty)";
  }

  //----------------------------------------------------------------------------------------------------

  void GalilHardwareIF::InitiateCommunication()
  {
    std::cerr << "Galil communication initiation" << std::endl;
    this->Connect();
  }

  //----------------------------------------------------------------------------------------------------

  void GalilHardwareIF::Move(int actuator, double target)
  {
    std::cerr << "Moving..." << std::endl;

    // TODO: Should check if connected
    std::stringstream command;
    command << "PR";

    switch(actuator){
    case 0: { command << "A"; break; }
    case 1: { command << "B"; break; }
    case 2: { command << "C"; break; }
    case 3: { command << "D"; break; }
    default: { command << "A"; break; }
    }

    command << "=" << target;
    this->Command(command.str().c_str());
    this->Command("BGA");
  }

  //----------------------------------------------------------------------------------------------------

  void GalilHardwareIF::DefaultConfiguration()
  {
    if(this->CommunicationSocket > 0)
      {
      std::cerr << "Configuring..." << std::endl;
      this->Command("BAA");
      this->Command("BMA=4096");
      this->Command("BXA=-3");
      this->Command("KIA=0.17");
      this->Command("SPA=2000");
      this->Command("PRA=8192");
      }
  }

  //----------------------------------------------------------------------------------------------------

  void GalilHardwareIF::Exit()
  {
    std::cerr << "Disconnect..." << std::endl;
    this->Disconnect();
  }

  //----------------------------------------------------------------------------------------------------

}
