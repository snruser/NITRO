typedef std::string Text;

enum MotionType
{
  ROTATIONAL,
  LINEAR
};

enum Drive
{
  ACTIVE,
  PASSIVE
};

enum ActuatorType
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

enum SensorType
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
  ActuatorType a_ActuatorType;
  MotionType a_MotionType;
  ActuatorInput a_ActuatorInput;
  int a_PulsePerUnit;
  double a_GearRatio;
Actuator():a_ActuatorType(DC),a_MotionType(ROTATIONAL),a_ActuatorInput(POSITION),a_PulsePerUnit(0.0),a_GearRatio(1.0){}
};

struct Sensor{
  SensorType s_SensorType;
  MotionType s_MotionType;
  double s_CountsPerUnit;
Sensor():s_SensorType(NONE),s_MotionType(ROTATIONAL),s_CountsPerUnit(0.0){}
};

struct Landmark{
  double l_Home;
  MinMax l_Limits;
Landmark():l_Home(0),l_Limits(){}
};
