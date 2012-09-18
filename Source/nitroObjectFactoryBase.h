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
  Module:    $RCSfile: itkObjectFactoryBase.h,v $
  Language:  C++
  Date:      $Date: 2008-12-22 19:05:42 -0500 (Mon, 22 Dec 2008) $
  Version:   $Revision: 3460 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

  Portions of this code are covered under the VTK copyright.
  See VTKCopyright.txt or http://www.kitware.com/VTKCopyright.htm for details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

  =========================================================================*/
#ifndef __nitroObjectFactoryBase_h
#define __nitroObjectFactoryBase_h

#include "nitroObject.h"
#include "nitroCreateObjectFunction.h"
#include <list>
#include <vector>

namespace nitro
{
/** \class ObjectFactoryBase
 * \brief Create instances of classes using an object factory.
 *
 * ObjectFactoryBase is used to create nitro objects. The base class
 * ObjectFactoryBase contains a static method CreateInstance() that is
 * used to create nitro objects from the list of registerd ObjectFactoryBase
 * sub-classes.  The first time CreateInstance() is called, all dll's or
 * shared libraries in the environment variable NITRO_AUTOLOAD_PATH are loaded
 * into the current process.  The C function nitroLoad is called on each dll.
 * nitroLoad should return an instance of the factory sub-class implemented in
 * the shared library. NITRO_AUTOLOAD_PATH is an environment variable
 * containing a colon separated (semi-colon on win32) list of paths.
 *
 * This can be use to overide the creation of any object in NITRO.
 *
 * \ingroup NITROSystemObjects
 */

  class OverRideMap;

  class NITROCommon_EXPORT ObjectFactoryBase : public Object
  {
  public:
    /** Standard class typedefs. */
    typedef ObjectFactoryBase           Self;
    typedef Object                      Superclass;
    typedef SmartPointer<Self>          Pointer;
    typedef SmartPointer<const Self>    ConstPointer;

    /** Run-time type information (and related methods). */
    nitroTypeMacro(ObjectFactoryBase, Object);

    /** Create and return an instance of the named nitro object.
     * Each loaded ObjectFactoryBase will be asked in the order
     * the factory was in the NITRO_AUTOLOAD_PATH.  After the
     * first factory returns the object no other factories are asked. */
    static LightObject::Pointer CreateInstance(const char* nitroclassname);

    /** Create and return all possible instances of the named nitro object.
     * Each loaded ObjectFactoryBase will be asked in the order
     * the factory was in the NITRO_AUTOLOAD_PATH.  All created objects
     * will be returned in the list. */
    static std::list<LightObject::Pointer>
      CreateAllInstance(const char* nitroclassname);

    /** Re-check the NITRO_AUTOLOAD_PATH for new factory libraries.
     * This calls UnRegisterAll before re-loading. */
    static void ReHash();

    /** Register a factory so it can be used to create nitro objects. */
    static void RegisterFactory(ObjectFactoryBase* );

    /** Remove a factory from the list of registered factories. */
    static void UnRegisterFactory(ObjectFactoryBase*);

    /** Unregister all factories. */
    static void UnRegisterAllFactories();

    /** Return the list of all registered factories.  This is NOT a copy,
     * do not remove items from this list! */
    static std::list<ObjectFactoryBase*> GetRegisteredFactories();

    /** All sub-classes of ObjectFactoryBase should must return the version of
     * NITRO they were built with.  This should be implemented with the macro
     * NITRO_SOURCE_VERSION and NOT a call to Version::GetNITROSourceVersion.
     * As the version needs to be compiled into the file as a string constant.
     * This is critical to determine possible incompatible dynamic factory loads. */
    virtual const char* GetNITROSourceVersion(void) const = 0;

    /** Return a descriptive string describing the factory. */
    virtual const char* GetDescription(void) const = 0;

    /** Return a list of classes that this factory overrides. */
    virtual std::list<std::string> GetClassOverrideNames();

    /** Return a list of the names of classes that override classes. */
    virtual std::list<std::string> GetClassOverrideWithNames();

    /** Return a list of descriptions for class overrides. */
    virtual std::list<std::string> GetClassOverrideDescriptions();

    /** Return a list of enable flags. */
    virtual std::list<bool> GetEnableFlags();

    /** Set the Enable flag for the specific override of className. */
    virtual void SetEnableFlag(bool flag,
                               const char* className,
                               const char* subclassName);

    /** Get the Enable flag for the specific override of className. */
    virtual bool GetEnableFlag(const char* className,
                               const char* subclassName);

    /** Set all enable flags for the given class to 0.  This will
     * mean that the factory will stop producing class with the given
     * name. */
    virtual void Disable(const char* className);

    /** This returns the path to a dynamically loaded factory. */
    const char* GetLibraryPath();

    /** \class OverrideInformation
     * \brief Internal implementation class for ObjectFactorBase. */
    struct OverrideInformation
    {
      std::string m_Description;
      std::string m_OverrideWithName;
      bool m_EnabledFlag;
      CreateObjectFunctionBase::Pointer m_CreateObject;
    };

  protected:
    virtual void PrintSelf(std::ostream& os) const;

    /** Register object creation information with the factory. */
    void RegisterOverride(const char* classOverride,
                          const char* overrideClassName,
                          const char* description,
                          bool enableFlag,
                          CreateObjectFunctionBase* createFunction);

    /** This method is provided by sub-classes of ObjectFactoryBase.
     * It should create the named nitro object or return 0 if that object
     * is not supported by the factory implementation. */
    virtual LightObject::Pointer CreateObject(const char* nitroclassname );

    ObjectFactoryBase();
    virtual ~ObjectFactoryBase();

  private:
    OverRideMap* m_OverrideMap;

    ObjectFactoryBase(const Self&); //purposely not implemented
    void operator=(const Self&); //purposely not implemented

    /** Initialize the static members of ObjectFactoryBase.   RegisterDefaults
     * is called here. */
    static void Initialize();

    /** Register default factories which are not loaded at run time. */
    static void RegisterDefaults();

//  /** Load dynamic factories from the NITRO_AUTOLOAD_PATH */
//  static void LoadDynamicFactories();
//
//  /** Load all dynamic libraries in the given path */
//  static void LoadLibrariesInPath( const char*);
//
    /** list of registered factories */
    static std::list<ObjectFactoryBase*>* m_RegisteredFactories;

    /** Member variables for a factory set by the base class
     * at load or register time */
    void*         m_LibraryHandle;
    unsigned long m_LibraryDate;
    std::string   m_LibraryPath;
  };

} // end namespace nitro

#endif
