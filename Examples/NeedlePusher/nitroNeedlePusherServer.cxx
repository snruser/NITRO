#include "nitroGalilHardwareIF.h"
#include "nitroOpenIGTLinkNetworkIF.h"
#include "nitroNeedlePusherKinematics.h"
#include "nitroUserIF.h"
#include "nitroNeedlePusherController.h"

#include "nitroXMLParser.h"

const int COM_PORT = 18944;
const char* IP_ADDR = "";

using namespace nitro;

int main()
{

  // ------------------------------------------------------------
  // Step 1: Create instances for device I/O, network I/O, control
  // logic, and user interface

  // Device I/O (Galil)
  GalilHardwareIF::Pointer hwnp;
  hwnp = GalilHardwareIF::New();

  // Network IO (OpenIGTLink)
  OpenIGTLinkNetworkIF::Pointer nwio;
  nwio = OpenIGTLinkNetworkIF::New();
  nwio->ConfigureAsServer(18944);
  
  // Controller (Kinematics)
  NeedlePusherKinematics::Pointer km;
  km = NeedlePusherKinematics::New();

  // User Interface (Required ?)
  //UserIF::Pointer ui;
  //ui = UserIF::New();

  // XML Parser
  XMLParser::Pointer xmlp;
  xmlp = XMLParser::New();
  xmlp->SetXMLPath("/Users/SNR/Desktop/NITRO/Examples/NeedlePusher/NeedlePusher.xml");
    
  // ------------------------------------------------------------
  // Step 2: Create controller and set the instances

  NeedlePusherController::Pointer ctl;
  ctl = NeedlePusherController::New();
  ctl->SetHardwareIF(hwnp);
  ctl->SetNetworkIF(nwio);
  ctl->SetKinematics(km);
  //ctl->SetUserIF(ui);
  ctl->SetXMLParser(xmlp);

  // ------------------------------------------------------------
  // Step 3: Initialize the controller

  ctl->Initialize();

  // ------------------------------------------------------------
  // Step 4: Main loop
  // TODO: Change the name

  ctl->Loop();

  // ------------------------------------------------------------
  // Step 5: Exit

  ctl->Exit();

  return 0;
}
