/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

  =========================================================================*/

#ifndef  __nitroLogRecorder_h
#define  __nitroLogRecorder_h

#include <fstream>
#include "nitroConfigure.h"
#include "nitroObject.h"
#include "nitroObjectFactory.h"

namespace nitro {

  class NITROCommon_EXPORT LogRecorder : public Object
  {
  public:
    typedef LogRecorder              Self;
    typedef Object                   Superclass;
    typedef SmartPointer<Self>       Pointer;
    typedef SmartPointer<const Self> ConstPointer;

    nitroNewMacro(Self);
    nitroTypeMacro(LogRecorder, Object);

  public:

    void SetLogFile(const char* fpath);
    const char* GetLogFile();
    void Log(const char* logData);
    void Close();

    // Create continous recording ?
    //void StartRecording();
    //void StopRecording();

    // Description:
    // Initialization function. Could be overloaded.
    virtual void Initialize() {};

    // Description:
    // Close connections, delete classes
    virtual void Exit() {};


  protected:

    // Description:
    // Constructor/Destructor
    LogRecorder();
    ~LogRecorder();

  protected:

    std::ofstream LogFile;
    std::string LogPath;
  };

} // end namespace nitro

#endif
