#include "nitroHardwareNeedlePusher.h"

int main()
{

  // ------------------------------------------------------------
  // Step 1: Create instances for device I/O, network I/O, control
  // logic, and user interface

  // Device I/O (Galil)
  HardwareNeedlePusher::Pointer hwnp;
  hwnp = HardwareNeedlePusher::New();



  return 0;
}
