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

  protected:

    // Description:
    // Constructor/Destructor
    Joint();
    ~Joint();

  protected:

/* (REQUIRED) */   Text		j_Name;	        // Name of the joint                         
                   Text		j_Description;	// Description of the joint                  
/* (REQUIRED) */   int		j_Group;	// Group belonging for priority motion       
/* (REQUIRED) */   MotionType	j_MotionType;	// Rotational or linear motion               
/* (REQUIRED) */   Drive	j_Drive;	// Active or passive joint                   
                   MinMax	j_MotionRange;	// Range of motion                           
                   MinMaxFixed	j_Speed;	// Range of speed, or fixed                  
                   MinMaxFixed	j_Acceleration;	// Range of acceleration, or fixed           
                   MinMaxFixed	j_Torque;	// Range of torque, or fixed                 
/* (REQUIRED) */   Actuator	j_Actuator;	// Actuator informations                     
                   Sensor	j_Sensor;	// Sensor informations                       
                   Landmark	j_Landmark;	// Landmark informations                     
  };

} // end namespace nitro

#endif
