/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

  =========================================================================*/

#ifndef  __nitroJoint_h
#define  __nitroJoint_h

#include "nitroConfigure.h"
#include "nitroObject.h"
#include "nitroObjectFactory.h"

#include "nitroJointTypes.h"

namespace nitro {

  class NITROCommon_EXPORT Joint : public Object
  {
  public:
    typedef Joint                    Self;
    typedef Object                   Superclass;
    typedef SmartPointer<Self>       Pointer;
    typedef SmartPointer<const Self> ConstPointer;

    nitroNewMacro(Self);
    nitroTypeMacro(Joint, Object);

  public:

    // Getters / Setters
    void SetName(const char* name) { this->m_Name.assign(name); };
    const char* GetName() { return this->m_Name.c_str(); };
    void SetDescription(const char* description) { this->m_Description = description; };
    const char* GetDescription() { return this->m_Description.c_str(); };
    void SetGroup(int group) { this->m_Group = group; };
    int GetGroup() { return this->m_Group; };
    void SetMotionType(MotionTypes type) { this->m_MotionType = type;};
    MotionTypes GetMotionType() { return this->m_MotionType; };
    void SetDrive(Drive drive) { this->m_Drive = drive; };
    Drive GetDrive() { return this->m_Drive; };
    void SetMotionRange(MinMax motionRange) { this->m_MotionRange = motionRange; };
    MinMax GetMotionRange() { return this->m_MotionRange; };
    void SetSpeed(MinMaxFixed speed) { this->m_Speed = speed; };
    MinMaxFixed GetSpeed() { return this->m_Speed; };
    void SetAcceleration(MinMaxFixed acceleration) { this->m_Acceleration = acceleration; };
    MinMaxFixed GetAcceleration() { return this->m_Acceleration; };
    void SetTorque(MinMaxFixed torque) { this->m_Torque = torque; };
    MinMaxFixed GetTorque() { return this->m_Torque; };
    void SetActuator(Actuator actuator) { this->m_Actuator = actuator; };
    Actuator GetActuator() { return this->m_Actuator; };
    void SetSensor(Sensor sensor) { this->m_Sensor = sensor; };
    Sensor GetSensor() { return this->m_Sensor; };
    void SetLandmark(Landmark landmark) { this->m_Landmark = landmark; };
    Landmark GetLandmark() { return this->m_Landmark; };

  protected:

    // Description:
    // Constructor/Destructor
    Joint();
    ~Joint();

  protected:

    Text        m_Name;         // Name of the joint
    Text        m_Description;  // Description of the joint
    int         m_Group;        // Group belonging for priority motion
    MotionTypes m_MotionType;   // Rotational or linear motion
    Drive	m_Drive;        // Active or passive joint
    MinMax      m_MotionRange;  // Range of motion
    MinMaxFixed m_Speed;        // Range of speed, or fixed
    MinMaxFixed m_Acceleration; // Range of acceleration, or fixed
    MinMaxFixed m_Torque;       // Range of torque, or fixed
    Actuator    m_Actuator;     // Actuator informations
    Sensor      m_Sensor;       // Sensor informations
    Landmark    m_Landmark;     // Landmark informations
  };

} // end namespace nitro

#endif
