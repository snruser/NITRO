#include "nitroGalilHardwareIF.h"
#include "nitroXMLParser.h"

int main()
{

  // ------------------------------------------------------------
  // Step 1: Create instances for device I/O, network I/O, control
  // logic, and user interface

  // Device I/O (Galil)
  GalilHardwareIF::Pointer hwnp;
  hwnp = GalilHardwareIF::New();

  // Test XML Parser
  nitro::XMLParser::Pointer xmlp;
  xmlp = nitro::XMLParser::New();

  if(xmlp->SetXMLPath("/Users/SNR/Desktop/NITRO/Examples/NeedlePusher/NeedlePusher.xml"))
    {
    xmlp->Parse();    
    }
  else
    {
    std::cerr << "Couldn't open file" << std::endl;
    }
  return 0;
}
