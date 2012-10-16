/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

  =========================================================================*/

#include "nitroLogRecorder.h"

namespace nitro {

  //----------------------------------------------------------------------------------------------------

  LogRecorder::LogRecorder()
  {
  }

  //----------------------------------------------------------------------------------------------------

  LogRecorder::~LogRecorder()
  {
  }

  //----------------------------------------------------------------------------------------------------

  // TODO: Return value ?
  void LogRecorder::SetLogFile(const char* fpath)
  {
    std::ios_base::openmode mode = std::ios::out;
    std::fstream testFile;

    // Set path
    this->LogPath.assign(fpath);

    // Check if file exists
    testFile.open(fpath);
    if(testFile.is_open())
      {
      // File exists. Append new data.
      testFile.close();
      mode = mode | std::ios::app;
      }

    // (Re)Open file with proper options
    this->LogFile.open(fpath,mode);
  }

  //----------------------------------------------------------------------------------------------------

  const char* LogRecorder::GetLogFile()
  {
    if(!this->LogPath.empty())
      {
      return this->LogPath.c_str();
      }
    return NULL;
  }

  //----------------------------------------------------------------------------------------------------

  // TODO: Return value ?
  void LogRecorder::Log(const char* logData)
  {
    if(this->LogFile.is_open())
      {
      this->LogFile << logData << std::endl;
      }
  }

  //----------------------------------------------------------------------------------------------------

  void LogRecorder::Close()
  {
    if(this->LogFile.is_open())
      {
      this->LogFile.close();
      }
  }

  //----------------------------------------------------------------------------------------------------

} // end namespace nitro
