#include "nitroHardwareNeedlePusher.h"
#include "nitroXMLParser.h"

int main()
{

  // ------------------------------------------------------------
  // Step 1: Create instances for device I/O, network I/O, control
  // logic, and user interface

  // Device I/O (Galil)
  HardwareNeedlePusher::Pointer hwnp;
  hwnp = HardwareNeedlePusher::New();

  // Test XML Parser
  nitro::XMLParser::Pointer xmlp;
  xmlp = nitro::XMLParser::New();

  xmlp->Parse("/Users/SNR/Desktop/test2.xml");
  for(int i = 0; i < xmlp->GetNumberOfActuators(); i++)
    {
    xmlp->GoToNextActuator();
    int testvalue = xmlp->ConvertFromString<int>(xmlp->GetTagValue("test"));
    std::cerr << "Test: " << testvalue << std::endl;
    }
  return 0;
}
