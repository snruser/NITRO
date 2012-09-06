#include <nitro.h>
#include <nitroHardwareGalil.h>
#include <nitroNetworkInterfaceOpenIGTLink.h>
#include <nitroControlLogicNeedlePusher.h>
#include <introUserInterfaceConsole.h>
 
int main()
{
 
 // ------------------------------------------------------------
 // Step 1: Create instances for device I/O, network I/O, control
 // logic, and user interface 

 // Device I/O (Galil)
 nitroSmartPointer<nitro::HardwareGalil> hwio;
 hwio = nitro::HardwareGalil::New();
  
 // Network IO (OpenIGTLink)
 nitroSmartPointer<nitro::NetworkInterfaceOpenIGTLink> nwio;
 nwio = nitro::InterfaceOpenIGTLink::New();

 // Controller (Kinematics)
 nitroSmartPointer<nitro::ControlLogicNeedlePusher> cl;
 cl = nitro::ControlLogicNeedlePusher::New();

 // User Interface
 nitroSmartPointer<nitro::UserInterfaceConsole> ui;
 ui = nitro::UserInterfaceConsole::New();

 // ------------------------------------------------------------
 // Step 2: Create controller and set the instances

 nitroSmartPointer<nitro::Controller> controller;
 controller = nitro::Controller::New();
 controller->SetHardware(hwio);
 controller->SetInterface(nwio);
 controller->SetControlLogic(cl);
 controller->SetUserInterface(ui);

 // ------------------------------------------------------------
 // Step 3: Initialize the controller
 controller->Initialize();

 // ------------------------------------------------------------
 // Step 4: Main loop
 controller->Loop();

 // ------------------------------------------------------------
 // Step 5: Exit
 controller->Finialize();

}
