#ifndef __nitroJointTypes_h
#define __nitroJointTypes_h

#include <string>

namespace nitro {

  typedef std::string Text;

  enum MotionTypes
  {
    ROTATIONAL,
    LINEAR
  };

  enum Drive
  {
    ACTIVE,
    PASSIVE
  };

  enum ActuatorTypes
  {
    DC,
    STEPPING
  };

  enum ActuatorInput
  {
    POSITION,
    SPEED,
    TORQUE
  };

  enum SensorTypes
  {
    NONE,
    ENCODER
  };

  struct MinMax
  {
    double Min;
    double Max;
  MinMax():Min(0.0),Max(0.0){}
  };

  struct MinMaxFixed
  {
    double Min;
    double Max;
    double Fixed;
  MinMaxFixed():Min(0.0),Max(0.0),Fixed(0.0){}
  };

  struct Actuator{
    ActuatorTypes Type;
    MotionTypes MotionType;
    ActuatorInput Input;
    int PulsePerUnit;
    double GearRatio;
  Actuator():Type(DC),MotionType(ROTATIONAL),Input(POSITION),PulsePerUnit(0.0),GearRatio(1.0){}
  };

  struct Sensor{
    SensorTypes Type;
    MotionTypes MotionType;
    double CountsPerUnit;
  Sensor():Type(NONE),MotionType(ROTATIONAL),CountsPerUnit(0.0){}
  };

  struct Landmark{
    double Home;
    MinMax Limits;
  Landmark():Home(0),Limits(){}
  };

} // end namespace nitro
#endif
