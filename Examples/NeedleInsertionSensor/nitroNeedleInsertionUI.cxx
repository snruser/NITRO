#include <iostream>

#include "nitroUserIF.h"

using namespace nitro;

int main()
{
  std::cerr << " > Checking shared memories" << std::endl;

  UserIF::Pointer NeedleInsertionUI;
  NeedleInsertionUI = UserIF::New();

  if(NeedleInsertionUI->GetControllerMemory())
    {
      std::cerr << "\tController detected" << std::endl;
    }
  if(NeedleInsertionUI->GetNetworkMemory())
    {
      std::cerr << "\tNetwork detected" << std::endl;
    }
  if(NeedleInsertionUI->GetKinematicsMemory())
    {
      std::cerr << "\tKinematics detected" << std::endl;
    }
  if(NeedleInsertionUI->GetHardwareMemory())
    {
      std::cerr << "\tHardware detected" << std::endl;
    }

  getchar();
  return 0;
}
