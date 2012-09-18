/*=========================================================================

  Program:   NITRO
  Language:  C++

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

  =========================================================================*/
/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkCreateObjectFunction.h,v $
  Language:  C++
  Date:      $Date: 2008-12-22 19:05:42 -0500 (Mon, 22 Dec 2008) $
  Version:   $Revision: 3460 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

  =========================================================================*/
#ifndef __nitroCreateObjectFunction_h
#define __nitroCreateObjectFunction_h

#include "nitroObject.h"

namespace nitro
{

/** \class CreateObjectFunctionBase
 * \brief Define API for object creation callback functions.
 *
 * \ingroup NITROSystemObjects
 */
  class CreateObjectFunctionBase: public Object
  {
  public:
    /** Standard typedefs. */
    typedef CreateObjectFunctionBase  Self;
    typedef Object                    Superclass;
    typedef SmartPointer<Self>        Pointer;
    typedef SmartPointer<const Self>  ConstPointer;

    /** Create an object and return a pointer to it as an
     * nitro::LightObject. */
    virtual SmartPointer<LightObject> CreateObject() = 0;

  protected:
    CreateObjectFunctionBase() {}
    ~CreateObjectFunctionBase() {}

  private:
    CreateObjectFunctionBase(const Self&); //purposely not implemented
    void operator=(const Self&); //purposely not implemented
  };


/** \class CreateObjectFunction
 * \brief CreateObjectFunction is used to create callback functions that
 * create NITRO Objects for use with the nitro::ObjectFactory.
 *
 * \ingroup NITROSystemObjects
 */
  template <class T>
    class CreateObjectFunction : public CreateObjectFunctionBase
    {
    public:
    /** Standard class typedefs. */
    typedef CreateObjectFunction  Self;
    typedef SmartPointer<Self>    Pointer;

    /** Methods from nitro:LightObject. */
    nitroFactorylessNewMacro(Self);
    LightObject::Pointer CreateObject() { return T::New().GetPointer(); }

    protected:
    CreateObjectFunction() {}
    ~CreateObjectFunction() {}

    private:
    CreateObjectFunction(const Self&); //purposely not implemented
    void operator=(const Self&); //purposely not implemented
    };

} // end namespace nitro

#endif
