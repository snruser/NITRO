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
  Module:    $RCSfile: itkMacro.h,v $
  Language:  C++
  Date:      $Date: 2009-05-22 15:29:17 -0400 (Fri, 22 May 2009) $
  Version:   $Revision: 4248 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

  Portions of this code are covered under the VTK copyright.
  See VTKCopyright.txt or http://www.kitware.com/VTKCopyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
/**
 * nitroMacro.h defines standard system-wide macros, constants, and other
 * parameters. One of its most important functions is to define macros used
 * to interface to instance variables in a standard fashion. For example,
 * these macros manage modified time, debugging information, and provide a
 * standard interface to set and get instance variables.  Macros are
 * available for built-in types; for string classe; vector arrays;
 * object pointers; and debug, warning, and error printout information. 
 */
  
#ifndef __nitroMacro_h
#define __nitroMacro_h

#include "nitroWin32Header.h"
//#include "nitroConfigure.h"

#include <string>

// Determine type of string stream to use.
#if !defined(CMAKE_NO_ANSI_STRING_STREAM)
#  include <sstream>
#elif !defined(CMAKE_NO_ANSI_STREAM_HEADERS)
#  include <strstream>
#  define NITRO_NO_ANSI_STRING_STREAM
#else
#  include <strstream.h>
#  define NITRO_NO_ANSI_STRING_STREAM
#endif

/** \namespace nitro
 * \brief The "nitro" namespace contains all Insight Segmentation and
 * Registration Toolkit (NITRO) classes. There are several nested namespaces
 * within the nitro:: namespace. */
namespace nitro
{
} // end namespace nitro - this is here for documentation purposes

/** A convenience macro marks variables as not being used by a method,
 * avoiding compile-time warnings. */
#define nitroNotUsed(x)

/** Macro to initialize static constants.  This is used frequently to replace
 * the use of enum's within a class.  Some compilers do not allow an enum of
 * one class to be passed as template argument to another class. Other
 * uses of this macro as possible.
 *
 * This is based (verbatim) on the BOOST_STATIC_CONSTANT macro. The original
 * Boost documentation is below.
 *
 * BOOST_STATIC_CONSTANT workaround --------------------------------------- //
 * On compilers which don't allow in-class initialization of static integral
 * constant members, we must use enums as a workaround if we want the constants
 * to be available at compile-time. This macro gives us a convenient way to
 * declare such constants.
 */
#if defined(_MSC_VER) && (_MSC_VER <= 1300) 
#   define NITRO_NO_INCLASS_MEMBER_INITIALIZATION
#endif
#if defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x540)
#   define NITRO_NO_INCLASS_MEMBER_INITIALIZATION
#endif
#if defined(__SVR4) && !defined(__SUNPRO_CC)
#   define NITRO_NO_INCLASS_MEMBER_INITIALIZATION
#endif

// A class template like this will not instantiate on GCC 2.95:
//   template<class T> struct A
//   {
//     static const int N = 1;
//     enum { S = sizeof(A::N) };
//   };
// We need to use enum for static constants instead.
#if defined(__GNUC__)
# define NITRO_NO_SIZEOF_CONSTANT_LOOKUP
#endif

#if defined(_MSC_VER) && (_MSC_VER <= 1300) 
#define NITRO_NO_SELF_AS_TRAIT_IN_TEMPLATE_ARGUMENTS
#endif

#if defined(NITRO_NO_INCLASS_MEMBER_INITIALIZATION) || \
    defined(NITRO_NO_SIZEOF_CONSTANT_LOOKUP)
#   define nitroStaticConstMacro(name,type,value) enum { name = value }
#else
#   define nitroStaticConstMacro(name,type,value) static const type name = value
#endif

#ifdef NITRO_NO_SELF_AS_TRAIT_IN_TEMPLATE_ARGUMENTS
#   define nitroGetStaticConstMacro(name) name
#else
#   define nitroGetStaticConstMacro(name) (Self::name)
#endif

/** Set an input. This defines the Set"name"Input() method */
#define nitroSetInputMacro(name, type, number) \
  virtual void Set##name##Input(const type *_arg) \
  { \
    nitroDebugMacro("setting input " #name " to " << _arg); \
    if (_arg != static_cast<type *>(this->ProcessObject::GetInput( number ))) \
      { \
      this->ProcessObject::SetNthInput( number, const_cast<type *>(_arg) ); \
      } \
  } \
  virtual void SetInput##number(const type *_arg) \
  { \
    nitroDebugMacro("setting input " #number " to " << _arg); \
    if (_arg != static_cast<type *>(this->ProcessObject::GetInput( number ))) \
      { \
      this->ProcessObject::SetNthInput( number, const_cast<type *>(_arg) ); \
      } \
  } 

/** Macro used to redefine a type from the superclass. */
#define nitroSuperclassTraitMacro(traitnameType) \
  typedef typename Superclass::traitnameType traitnameType;

/** Get an input. This defines the Get"name"Input() method */
#define nitroGetInputMacro(name, type, number) \
  virtual const type * Get##name##Input() const \
  { \
    nitroDebugMacro("returning input " << #name " of " << static_cast<const type *>(this->ProcessObject::GetInput( number )) ); \
    return static_cast<const type *>(this->ProcessObject::GetInput( number )); \
  } \
  virtual const type * GetInput##number() const \
  { \
    nitroDebugMacro("returning input " << #number " of " << static_cast<const type *>(this->ProcessObject::GetInput( number )) ); \
    return static_cast<const type *>(this->ProcessObject::GetInput( number )); \
  } 

/** Set a decorated input. This defines the Set"name"() method.
 * It invokes SetInputMacro() and GetInputMacro() for the decorated object */
#define nitroSetDecoratedInputMacro(name, type, number) \
  nitroSetInputMacro(name, SimpleDataObjectDecorator<type>, number); \
  nitroGetInputMacro(name, SimpleDataObjectDecorator<type>, number); \
  virtual void Set##name(const type &_arg) \
  { \
    typedef SimpleDataObjectDecorator< type > DecoratorType; \
    nitroDebugMacro("setting input " #name " to " << _arg); \
    const DecoratorType * oldInput = \
      static_cast< const DecoratorType * >( \
        this->ProcessObject::GetInput(number) ); \
    if( oldInput && oldInput->Get() == _arg ) \
      { \
      return; \
      } \
    typename DecoratorType::Pointer newInput = DecoratorType::New(); \
    newInput->Set( _arg ); \
    this->Set##name##Input( newInput ); \
  }

/** Set a decorated input that derives from nitro::Object, but not from
 * nitro::DataObject. This defines the Set"name"() method.  It invokes
 * SetInputMacro() and GetInputMacro() for the decorated object */
#define nitroSetDecoratedObjectInputMacro(name, type, number) \
  nitroSetInputMacro(name, DataObjectDecorator<type>, number); \
  nitroGetInputMacro(name, DataObjectDecorator<type>, number); \
  virtual void Set##name(const type *_arg) \
  { \
    typedef DataObjectDecorator< type > DecoratorType; \
    nitroDebugMacro("setting input " #name " to " << _arg); \
    const DecoratorType * oldInput = \
      static_cast< const DecoratorType * >( \
        this->ProcessObject::GetInput(number) ); \
    if( oldInput && oldInput->Get() == _arg ) \
      { \
      return; \
      } \
    typename DecoratorType::Pointer newInput = DecoratorType::New(); \
    newInput->Set( _arg ); \
    this->Set##name##Input( newInput ); \
  }


/** Set built-in type.  Creates member Set"name"() (e.g., SetVisibility()); */
#define nitroSetMacro(name,type) \
  virtual void Set##name (const type _arg) \
  { \
    nitroDebugMacro("setting " #name " to " << _arg); \
    if (this->m_##name != _arg) \
      { \
      this->m_##name = _arg; \
      } \
  } 

/** Get built-in type.  Creates member Get"name"() (e.g., GetVisibility()); */
#define nitroGetMacro(name,type) \
  virtual type Get##name () \
  { \
    nitroDebugMacro("returning " << #name " of " << this->m_##name ); \
    return this->m_##name; \
  }

/** Get built-in type.  Creates member Get"name"() (e.g., GetVisibility());
 * This is the "const" form of the nitroGetMacro.  It should be used unless
 * the member can be changed through the "Get" access routine. */
#define nitroGetConstMacro(name,type) \
  virtual type Get##name () const \
  { \
    nitroDebugMacro("returning " << #name " of " << this->m_##name ); \
    return this->m_##name; \
  }

/** Get built-in type.  Creates member Get"name"() (e.g., GetVisibility());
 * This is the "const" form of the nitroGetMacro.  It should be used unless
 * the member can be changed through the "Get" access routine.
 * This versions returns a const reference to the variable. */
#define nitroGetConstReferenceMacro(name,type) \
  virtual const type & Get##name () const \
  { \
    nitroDebugMacro("returning " << #name " of " << this->m_##name ); \
    return this->m_##name; \
  }
  
  /** Set built-in type.  Creates member Set"name"() (e.g., SetVisibility());
  * This should be use when the type is an enum. It is use to avoid warnings on
  * some compilers with non specified enum types passed to nitroDebugMacro.*/
#define nitroSetEnumMacro(name,type) \
  virtual void Set##name (const type _arg) \
  { \
    nitroDebugMacro("setting " #name " to " << static_cast<long>(_arg)); \
    if (this->m_##name != _arg) \
      { \
      this->m_##name = _arg; \
      } \
  } 

/** Get built-in type.  Creates member Get"name"() (e.g., GetVisibility()); 
  * This should be use when the type is an enum. It is use to avoid warnings on
  * some compilers with non specified enum types passed to nitroDebugMacro.*/
#define nitroGetEnumMacro(name,type) \
  virtual type Get##name () const \
  { \
    nitroDebugMacro("returning " << #name " of " << static_cast<long>(this->m_##name) ); \
    return this->m_##name; \
  }

/** Set character string.  Creates member Set"name"() 
 * (e.g., SetFilename(char *)). The macro assumes that
 * the class member (name) is declared a type std::string. */
#define nitroSetStringMacro(name) \
  virtual void Set##name (const char* _arg) \
  { \
    if ( _arg && (_arg == this->m_##name) ) { return;} \
    if (_arg) \
      { \
      this->m_##name = _arg;\
      } \
     else \
      { \
      this->m_##name = ""; \
      } \
  } \
  virtual void Set##name (const std::string & _arg) \
  { \
    this->Set##name( _arg.c_str() ); \
  } \


/** Get character string.  Creates member Get"name"() 
 * (e.g., SetFilename(char *)). The macro assumes that
 * the class member (name) is declared as a type std::string. */
#define nitroGetStringMacro(name) \
  virtual const char* Get##name () const \
  { \
    return this->m_##name.c_str(); \
  }

/** Set built-in type where value is constrained between min/max limits.
 * Create member Set"name"() (e.q., SetRadius()). #defines are 
 * convienience for clamping open-ended values. */
#define nitroSetClampMacro(name,type,min,max) \
  virtual void Set##name (type _arg) \
  { \
    nitroDebugMacro("setting " << #name " to " << _arg ); \
    if (this->m_##name != (_arg<min?min:(_arg>max?max:_arg))) \
      { \
      this->m_##name = (_arg<min?min:(_arg>max?max:_arg)); \
      } \
  } 

/** Set pointer to object; uses Object reference counting methodology.
 * Creates method Set"name"() (e.g., SetPoints()). Note that using
 * smart pointers requires using real pointers when setting input,
 * but returning smart pointers on output. */
#define nitroSetObjectMacro(name,type) \
  virtual void Set##name (type* _arg) \
  { \
    nitroDebugMacro("setting " << #name " to " << _arg ); \
    if (this->m_##name != _arg) \
      { \
      this->m_##name = _arg; \
      } \
  } 

/** Get a smart pointer to an object.  Creates the member 
 * Get"name"() (e.g., GetPoints()). */
#define nitroGetObjectMacro(name,type) \
  virtual type * Get##name () \
  { \
    nitroDebugMacro("returning " #name " address " << this->m_##name ); \
    return this->m_##name.GetPointer(); \
  } 

/** Set const pointer to object; uses Object reference counting methodology.
 * Creates method Set"name"() (e.g., SetPoints()). Note that using
 * smart pointers requires using real pointers when setting input,
 * but returning smart pointers on output. */
#define nitroSetConstObjectMacro(name,type) \
  virtual void Set##name (const type* _arg) \
  { \
    nitroDebugMacro("setting " << #name " to " << _arg ); \
    if (this->m_##name != _arg) \
      { \
      this->m_##name = _arg; \
      } \
  } 


/** Get a smart const pointer to an object.  Creates the member 
 * Get"name"() (e.g., GetPoints()). */
#define nitroGetConstObjectMacro(name,type) \
  virtual const type * Get##name () const \
  { \
    nitroDebugMacro("returning " #name " address " << this->m_##name ); \
    return this->m_##name.GetPointer(); \
  } 

/** Get a const reference to a smart pointer to an object.  
 * Creates the member Get"name"() (e.g., GetPoints()). */
#define nitroGetConstReferenceObjectMacro(name,type) \
  virtual const typename type::Pointer & Get##name () const \
  { \
    nitroDebugMacro("returning " #name " address " << this->m_##name ); \
    return this->m_##name; \
  } 

/** Create members "name"On() and "name"Off() (e.g., DebugOn() DebugOff()).
 * Set method must be defined to use this macro. */
#define nitroBooleanMacro(name) \
  virtual void name##On () { this->Set##name(true);} \
  virtual void name##Off () { this->Set##name(false);}

/** General set vector macro creates a single method that copies specified
 * number of values into object.
 * Examples: void SetColor(c,3) */
#define nitroSetVectorMacro(name,type,count) \
  virtual void Set##name(type data[]) \
  { \
    unsigned int i; \
    for (i=0; i<count; i++) { if ( data[i] != this->m_##name[i] ) { break; }} \
    if ( i < count ) \
      { \
      for (i=0; i<count; i++) { this->m_##name[i] = data[i]; }\
      } \
  }

/** Get vector macro. Returns pointer to type (i.e., array of type).
 * This is for efficiency. */
#define nitroGetVectorMacro(name,type,count) \
  virtual type *Get##name () const \
  { \
    return this->m_##name; \
  } 

/** Define two object creation methods.  The first method, New(),
 * creates an object from a class, potentially deferring to a factory.
 * The second method, CreateAnother(), creates an object from an
 * instance, potentially deferring to a factory.  This second method
 * allows you to create an instance of an object that is exactly the
 * same type as the referring object.  This is useful in cases where
 * an object has been cast back to a base class.
 *
 * These creation methods first try asking the object factory to create
 * an instance, and then default to the standard "new" operator if the
 * factory fails.
 *
 * These routines assigns the raw pointer to a smart pointer and then call
 * UnRegister() on the rawPtr to compensate for LightObject's constructor
 * initializing an object's reference count to 1 (needed for proper
 * initialization of process objects and data objects cycles). */
#define nitroNewMacro(x) \
static Pointer New(void) \
{ \
  Pointer smartPtr = ::nitro::ObjectFactory<x>::Create(); \
  if(smartPtr.GetPointer() == NULL) \
    { \
    smartPtr = new x; \
    } \
  smartPtr->UnRegister(); \
  return smartPtr; \
} \
virtual ::nitro::LightObject::Pointer CreateAnother(void) const \
{ \
  ::nitro::LightObject::Pointer smartPtr; \
  smartPtr = x::New().GetPointer(); \
  return smartPtr; \
}


/** Define two object creation methods.  The first method, New(),
 * creates an object from a class but does not defer to a factory.
 * The second method, CreateAnother(), creates an object from an
 * instance, again without deferring to a factory.  This second method
 * allows you to create an instance of an object that is exactly the
 * same type as the referring object.  This is useful in cases where
 * an object has been cast back to a base class.
 *
 * These creation methods first try asking the object factory to create
 * an instance, and then default to the standard "new" operator if the
 * factory fails.
 *
 * These routines assigns the raw pointer to a smart pointer and then call
 * UnRegister() on the rawPtr to compensate for LightObject's constructor
 * initializing an object's reference count to 1 (needed for proper
 * initialization of process objects and data objects cycles). */
#define nitroFactorylessNewMacro(x) \
static Pointer New(void) \
{ \
  Pointer smartPtr; \
  x *rawPtr = new x; \
  smartPtr = rawPtr; \
  rawPtr->UnRegister(); \
  return smartPtr; \
} \
  virtual ::nitro::LightObject::Pointer CreateAnother(void) const \
{ \
  ::nitro::LightObject::Pointer smartPtr;         \
  smartPtr = x::New().GetPointer(); \
  return smartPtr; \
}

/** Macro used to add standard methods to all classes, mainly type
 * information. */
#define nitroTypeMacro(thisClass,superclass) \
    virtual const char *GetNameOfClass() const \
        {return #thisClass;} 


//namespace nitro
//{
///**
// * The following is used to output debug, warning, and error messages.
// * Use a global function which actually calls:
// * OutputWindow::GetInstance()->DisplayText();
// * This is to avoid Object #include of OutputWindow
// * while OutputWindow #includes Object. */
//extern NITROCommon_EXPORT void OutputWindowDisplayText(const char*);
//extern NITROCommon_EXPORT void OutputWindowDisplayErrorText(const char*);
//extern NITROCommon_EXPORT void OutputWindowDisplayWarningText(const char*);
//extern NITROCommon_EXPORT void OutputWindowDisplayGenericOutputText(const char*);
//extern NITROCommon_EXPORT void OutputWindowDisplayDebugText(const char*);
//} // end namespace nitro

/** This macro is used to print debug (or other information). They are
 * also used to catch errors, etc. Example usage looks like:
 * nitroDebugMacro(<< "this is debug info" << this->SomeVariable); */
#if defined(NITRO_LEAN_AND_MEAN) || defined(__BORLANDC__)
#define nitroDebugMacro(x)
#else
#define nitroDebugMacro(x) \
  { if (this->GetDebug() /*&& ::nitro::Object::GetGlobalWarningDisplay()*/)   \
    { ::nitro::OStringStream nitromsg; \
      nitromsg << "Debug: In " __FILE__ ", line " << __LINE__ << "\n" \
             << this->GetNameOfClass() << " (" << this << "): " x  \
             << "\n\n"; \
      std::cerr << nitromsg.str(); /*::nitro::OutputWindowDisplayDebugText(nitromsg.str().c_str());*/} \
}
#endif


/** This macro is used to print warning information (i.e., unusual circumstance
 * but not necessarily fatal.) Example usage looks like:
 * nitroWarningMacro(<< "this is warning info" << this->SomeVariable); */
#ifdef NITRO_LEAN_AND_MEAN
#define nitroWarningMacro(x)
#else
#define nitroWarningMacro(x) \
  { if ( 1/*::nitro::Object::GetGlobalWarningDisplay()*/)  \
    { ::nitro::OStringStream nitromsg; \
      nitromsg << "WARNING: In " __FILE__ ", line " << __LINE__ << "\n" \
             << this->GetNameOfClass() << " (" << this << "): " x  \
             << "\n\n"; \
      std::cerr << nitromsg.str(); /*::nitro::OutputWindowDisplayWarningText(nitromsg.str().c_str());*/} \
}
#endif

namespace nitro
{

/**
 * nitro::OStringStream wrapper to hide differences between
 * std::ostringstream and the old ostrstream.  Necessary for
 * portability.
 */
#if !defined(NITRO_NO_ANSI_STRING_STREAM)
class OStringStream: public std::ostringstream
{
public:
  OStringStream() {}
private:
  OStringStream(const OStringStream&);
  void operator=(const OStringStream&);
};
#else
namespace OStringStreamDetail
{
  class Cleanup
  {
  public:
    Cleanup(std::ostrstream& ostr): m_OStrStream(ostr) {}
    ~Cleanup() { m_OStrStream.rdbuf()->freeze(0); }
    static void IgnoreUnusedVariable(const Cleanup&) {}
  protected:
    std::ostrstream& m_OStrStream;
  };
}//namespace OStringStreamDetail

class OStringStream: public std::ostrstream
{
public:
  typedef std::ostrstream Superclass;
  OStringStream() {}
  std::string str()
    {
      OStringStreamDetail::Cleanup cleanup(*this);
      OStringStreamDetail::Cleanup::IgnoreUnusedVariable(cleanup);
      int pcount = this->pcount();
      const char* ptr = this->Superclass::str();
      return std::string(ptr?ptr:"", pcount);
    }
private:
  OStringStream(const OStringStream&);
  void operator=(const OStringStream&);
};
#endif

}//namespace nitro

#if defined(NITRO_CPP_FUNCTION)
  #if defined(__BORLANDC__)
    #define NITRO_LOCATION __FUNC__
  #elif defined(_WIN32) && !defined(__MINGW32__) && !defined(__CYGWIN__) && !defined(CABLE_CONFIGURATION) && !defined(CSWIG)
    #define NITRO_LOCATION __FUNCSIG__
  #elif defined(__GNUC__)
    #define NITRO_LOCATION __PRETTY_FUNCTION__
  #else
    #define NITRO_LOCATION __FUNCTION__
  #endif
#else
  #define NITRO_LOCATION "unknown"
#endif

#define nitroExceptionMacro(x) \
  { \
  ::nitro::OStringStream nitromsg;                                 \
  nitromsg << "Debug: In " __FILE__ ", line " << __LINE__ << "\n" \
          << this->GetNameOfClass() << " (" << this << "): " x   \
          << "\n\n";                                             \
  std::cerr << nitromsg.str(); /*::nitro::OutputWindowDisplayDebugText(nitromsg.str().c_str());*/ \
}

#define nitroErrorMacro(x) \
  { \
  ::nitro::OStringStream nitromsg;                                 \
  nitromsg << "Debug: In " __FILE__ ", line " << __LINE__ << "\n" \
          << this->GetNameOfClass() << " (" << this << "): " x   \
          << "\n\n";                                             \
  std::cerr << nitromsg.str(); /*::nitro::OutputWindowDisplayDebugText(nitromsg.str().c_str());*/ \
}


#ifdef NITRO_LEAN_AND_MEAN
#define nitroGenericOutputMacro(x)
#else
#define nitroGenericOutputMacro(x) \
  { if (1/*::nitro::Object::GetGlobalWarningDisplay()*/) \
    { ::nitro::OStringStream nitromsg; \
      nitromsg << "WARNING: In " __FILE__ ", line " << __LINE__ << "\n" \
             x << "\n\n"; \
      std::cerr << nitromsg.str();/*::nitro::OutputWindowDisplayGenericOutputText(nitromsg.str().c_str());*/} \
}
#endif



//----------------------------------------------------------------------------
// Macros for simplifying the use of logging
//
#define nitroLogMacro( x, y)  \
{         \
  if (this->GetLogger() ) \
    {  \
    this->GetLogger()->Write(::nitro::LoggerBase::x, y); \
    }  \
}


#define nitroLogMacroStatic( obj, x, y)  \
{         \
  if (obj->GetLogger() ) \
    {  \
    obj->GetLogger()->Write(::nitro::LoggerBase::x, y); \
    }  \
}


//----------------------------------------------------------------------------
// Setup legacy code policy.
//
// CMake options NITRO_LEGACY_REMOVE and NITRO_LEGACY_SILENT are converted
// to definitions (or non-defs) in nitroConfigure.h and tested below.
// They may be used to completely remove legacy code or silence the
// warnings.  The default is to warn about their use.
//
// Source files that test the legacy code may define NITRO_LEGACY_TEST
// like this:
//
//  #define NITRO_LEGACY_TEST
//  #include "nitroClassWithDeprecatedMethod.h"
//
// in order to silence the warnings for calling deprecated methods.
// No other source files in NITRO should call the methods since they are
// provided only for compatibility with older user code.

// Define nitroLegacyMacro to mark legacy methods where they are
// declared in their class.  Example usage:
//
//   // @deprecated Replaced by MyOtherMethod() as of NITRO 2.0.
//   nitroLegacyMacro(void MyMethod());
#if defined(NITRO_LEGACY_REMOVE)
// Remove legacy methods completely.  Put a bogus declaration in
// place to avoid stray semicolons because this is an error for some
// compilers.  Using a class forward declaration allows any number
// of repeats in any context without generating unique names.
# define nitroLegacyMacro(method) class nitroLegacyMethodRemoved /* no ';' */
#elif defined(NITRO_LEGACY_SILENT) || defined(NITRO_LEGACY_TEST) || defined(CSWIG)
  // Provide legacy methods with no warnings.
# define nitroLegacyMacro(method) method
#else
  // Setup compile-time warnings for uses of deprecated methods if
  // possible on this compiler.
# if defined(__GNUC__) && !defined(__INTEL_COMPILER) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1))
#  define nitroLegacyMacro(method) method __attribute__((deprecated))
# elif defined(_MSC_VER) && _MSC_VER >= 1300
#  define nitroLegacyMacro(method) __declspec(deprecated) method
# else
#  define nitroLegacyMacro(method) method
# endif
#endif

// Macros to create runtime deprecation warning messages in function
// bodies.  Example usage:
//
//   void nitroMyClass::MyOldMethod()
//     {
//     nitroLegacyBodyMacro(nitroMyClass::MyOldMethod, 2.0);
//     }
//
//   void nitroMyClass::MyMethod()
//     {
//     nitroLegacyReplaceBodyMacro(nitroMyClass::MyMethod, 2.0,
//                               nitroMyClass::MyOtherMethod);
//     }
#if defined(NITRO_LEGACY_REMOVE) || defined(NITRO_LEGACY_SILENT)
# define nitroLegacyBodyMacro(method, version)
# define nitroLegacyReplaceBodyMacro(method, version, replace)
#else
# define nitroLegacyBodyMacro(method, version) \
  nitroWarningMacro(#method " was deprecated for NITRO " #version " and will be removed in a future version.")
# define nitroLegacyReplaceBodyMacro(method, version, replace) \
  nitroWarningMacro(#method " was deprecated for NITRO " #version " and will be removed in a future version.  Use " #replace " instead.")
#endif

#if defined(__INTEL_COMPILER)
# pragma warning (disable: 193) /* #if testing undefined identifier */
#endif

//=============================================================================
/* Choose a way to prevent template instantiation on this platform.
  - NITRO_TEMPLATE_DO_NOT_INSTANTIATE = use #pragma do_not_instantiate to
                                      prevent instantiation
  - NITRO_TEMPLATE_EXTERN = use extern template to prevent instantiation

   Note that VS 6 supports extern template instantiation but it is
   hard to block the resulting warning because its stream headers
   re-enable it.  Therefore we just disable support for now.
*/
#if defined(__sgi) && defined(_COMPILER_VERSION)
# define NITRO_TEMPLATE_DO_NOT_INSTANTIATE 1
#elif defined(__INTEL_COMPILER) && __INTEL_COMPILER >= 700
# define NITRO_TEMPLATE_EXTERN 1
#elif defined(__GNUC__) && __GNUC__ >= 3
# define NITRO_TEMPLATE_EXTERN 1
#elif defined(_MSC_VER) && _MSC_VER >= 1300
# define NITRO_TEMPLATE_EXTERN 1
#endif
#if !defined(NITRO_TEMPLATE_DO_NOT_INSTANTIATE)
# define NITRO_TEMPLATE_DO_NOT_INSTANTIATE 0
#endif
#if !defined(NITRO_TEMPLATE_EXTERN)
# define NITRO_TEMPLATE_EXTERN 0
#endif

/* Define a macro to explicitly instantiate a template.
  - NITRO_TEMPLATE_EXPORT(X) =
      Explicitly instantiate X, where X is of the form N(a1[,a2...,aN]).
      examples: NITRO_TEMPLATE_EXPORT(1(class Foo<int>))
                NITRO_TEMPLATE_EXPORT(2(class Bar<int, char>))
      Use one level of expansion delay to allow user code to have
      a macro determining the number of arguments. */
#define NITRO_TEMPLATE_EXPORT(x) NITRO_TEMPLATE_EXPORT_DELAY(x)
#define NITRO_TEMPLATE_EXPORT_DELAY(x) template NITRO_TEMPLATE_##x;

/* Define a macro to prevent template instantiations.
  - NITRO_TEMPLATE_IMPORT(X) =
      Prevent instantiation of X, where X is of the form N(a1[,a2...,aN]).
      examples: NITRO_TEMPLATE_IMPORT(1(class Foo<int>))
                NITRO_TEMPLATE_IMPORT(2(class Bar<int, char>))
      Use one level of expansion delay to allow user code to have
      a macro determining the number of arguments.
*/
#if NITRO_TEMPLATE_EXTERN
# define NITRO_TEMPLATE_IMPORT_DELAY(x) extern template NITRO_TEMPLATE_##x;
# if defined(_MSC_VER)
#  pragma warning (disable: 4231) /* extern template extension */
# endif
#elif NITRO_TEMPLATE_DO_NOT_INSTANTIATE
# define NITRO_TEMPLATE_IMPORT_DELAY(x) \
         NITRO_TEMPLATE_IMPORT_IMPL(do_not_instantiate NITRO_TEMPLATE_##x)
# define NITRO_TEMPLATE_IMPORT_IMPL(x) _Pragma(#x)
#endif
#if defined(NITRO_TEMPLATE_IMPORT_DELAY)
# define NITRO_TEMPLATE_IMPORT(x) NITRO_TEMPLATE_IMPORT_DELAY(x)
# define NITRO_TEMPLATE_IMPORT_WORKS 1
#else
# define NITRO_TEMPLATE_IMPORT(x)
# define NITRO_TEMPLATE_IMPORT_WORKS 0
#endif

/* Define macros to export and import template instantiations.  These
   depend on each class providing a macro defining the instantiations
   given template arguments in X.  The argument X is of the form
   N(a1[,a2...,aN]).  The argument Y is a valid preprocessing token
   unique to the template arguments given in X.  Typical usage is

     NITRO_EXPORT_TEMPLATE(nitrofoo_EXPORT, Foo, (int), I)
     NITRO_EXPORT_TEMPLATE(nitrofoo_EXPORT, Bar, (int, char), IC)

   The NITRO_TEMPLATE_<name> macro should be defined in nitro<name>.h and
   is of the following form:

     #define NITRO_TEMPLATE_<name>(_, EXPORT, x, y) namespace nitro { \
       _(<n>(class EXPORT <name>< NITRO_TEMPLATE_<n> x >)) \
       namespace Templates { typedef <name>< NITRO_TEMPLATE_<n> x > <name>##y; }\
     }

   The argument "_" will be replaced by another macro such as
   NITRO_TEMPLATE_EXPORT or NITRO_TEMPLATE_IMPORT, so it should be used as
   if calling one of these macros.  The argument "EXPORT" will be
   replaced by a dllexport/dllimport macro such as NITROCommon_EXPORT.
   The argument "x" is a paren-enclosed list of template arguments.
   The argument "y" is a preprocessing token corresponding to the
   given template arguments and should be used to construct typedef
   names for the instantiations.

   Note the use of NITRO_TEMPLATE_<n>, where <n> is the number of
   template arguments for the class template.  Note also that the
   number of template arguments is usually the length of the list
   nested within the inner parentheses, so the instantiation is listed
   with the form <n>(...).  Example definitions:

     #define NITRO_TEMPLATE_Foo(_, EXPORT, x, y) namespace nitro { \
       _(1(class EXPORT Foo< NITRO_TEMPLATE_1 x >)) \
       _(1(EXPORT std::ostream& operator<<(std::ostream&, \
                                           const Foo< NITRO_TEMPLATE_1 x >&))) \
       namespace Templates { typedef Foo< NITRO_TEMPLATE_1 x > Foo##y; }\
     }

     #define NITRO_TEMPLATE_Bar(_, EXPORT, x, y) namespace nitro { \
       _(2(class EXPORT Bar< NITRO_TEMPLATE_2 x >)) \
       _(1(EXPORT std::ostream& operator<<(std::ostream&, \
                                           const Bar< NITRO_TEMPLATE_2 x >&))) \
       namespace Templates { typedef Bar< NITRO_TEMPLATE_2 x > Bar##y; }\
     }

   Note that in the stream operator for template Bar there is a "1" at
   the beginning even though two arguments are taken.  This is because
   the expression "NITRO_TEMPLATE_2 x" is contained inside the
   parentheses of the function signature which protects the resulting
   comma from separating macro arguments.  Therefore the nested
   parentheses contain a list of only one macro argument.

   The NITRO_EMPTY macro used in these definitions is a hack to work
   around a VS 6.0 preprocessor bug when EXPORT is empty.
*/
#define NITRO_EXPORT_TEMPLATE(EXPORT, c, x, y) \
        NITRO_TEMPLATE_##c(NITRO_TEMPLATE_EXPORT, EXPORT NITRO_EMPTY, x, y)
#define NITRO_IMPORT_TEMPLATE(EXPORT, c, x, y) \
        NITRO_TEMPLATE_##c(NITRO_TEMPLATE_IMPORT, EXPORT NITRO_EMPTY, x, y)
#define NITRO_EMPTY

/* Define macros to support passing a variable number of arguments
   throug other macros.  This is used by NITRO_TEMPLATE_EXPORT,
   NITRO_TEMPLATE_IMPORT, and by each template's instantiation
   macro.  */
#define NITRO_TEMPLATE_1(x1)                         x1
#define NITRO_TEMPLATE_2(x1,x2)                      x1,x2
#define NITRO_TEMPLATE_3(x1,x2,x3)                   x1,x2,x3
#define NITRO_TEMPLATE_4(x1,x2,x3,x4)                x1,x2,x3,x4
#define NITRO_TEMPLATE_5(x1,x2,x3,x4,x5)             x1,x2,x3,x4,x5
#define NITRO_TEMPLATE_6(x1,x2,x3,x4,x5,x6)          x1,x2,x3,x4,x5,x6
#define NITRO_TEMPLATE_7(x1,x2,x3,x4,x5,x6,x7)       x1,x2,x3,x4,x5,x6,x7
#define NITRO_TEMPLATE_8(x1,x2,x3,x4,x5,x6,x7,x8)    x1,x2,x3,x4,x5,x6,x7,x8
#define NITRO_TEMPLATE_9(x1,x2,x3,x4,x5,x6,x7,x8,x9) x1,x2,x3,x4,x5,x6,x7,x8,x9

/* In order to support both implicit and explicit instantation a .h
   file needs to know whether it should include its .txx file
   containing the template definitions.  Define a macro to tell
   it.  Typical usage in nitroFoo.h:
     #if NITRO_TEMPLATE_TXX
     # include "nitroFoo.txx"
     #endif
*/
#if defined(NITRO_MANUAL_INSTANTIATION)
# define NITRO_TEMPLATE_TXX 0
#else
# define NITRO_TEMPLATE_TXX !(NITRO_TEMPLATE_CXX || NITRO_TEMPLATE_TYPE)
#endif

/* All explicit instantiation source files define NITRO_TEMPLATE_CXX.
   Define NITRO_MANUAL_INSTANTIATION to tell .h files that have not been
   converted to this explicit instantiation scheme to not include
   their .txx files.  Also disable warnings that commonly occur in
   these files but are not useful.  */
#if NITRO_TEMPLATE_CXX
# undef NITRO_MANUAL_INSTANTIATION
# define NITRO_MANUAL_INSTANTIATION
# if defined(_MSC_VER)
#  pragma warning (disable: 4275) /* non dll-interface base */
#  pragma warning (disable: 4661) /* no definition available */
# endif
#endif
//=============================================================================

/* Define macros to export and import template instantiations for each
   library in NITRO.  */
#define NITRO_EXPORT_NITROCommon(c, x, n) \
        NITRO_EXPORT_TEMPLATE(NITROCommon_EXPORT, c, x, n)
#define NITRO_IMPORT_NITROCommon(c, x, n) \
        NITRO_IMPORT_TEMPLATE(NITROCommon_EXPORT, c, x, n)

/* Define a macro to decide whether to block instantiation of NITRO
   templates.  They should be blocked only if the platform supports
   blocking template instantiation and the explicit instantiations are
   available.

   - NITRO_TEMPLATE_EXPLICIT =
      Whether to include "XXX+-.h" from "XXX.h" to prevent implicit
      instantiations of templates explicitly instantiated elsewhere.
      Typical usage in nitroFoo.h:
        #if NITRO_TEMPLATE_EXPLICIT
        # include "nitroFoo+-.h"
        #endif
*/
#if NITRO_TEMPLATE_IMPORT_WORKS && defined(NITRO_EXPLICIT_INSTANTIATION)
# define NITRO_TEMPLATE_EXPLICIT !NITRO_TEMPLATE_CXX
#else
# define NITRO_TEMPLATE_EXPLICIT 0
#endif


//----------------------------------------------------------------------------
// Macro to declare that a function does not return. __attribute__((noreturn))
//    On some compiler, functions that do not return (ex: exit(0)) must
//    have the noreturn attribute. Otherwise, a warning is raised. Use
//    that macro to avoid those warnings. GCC defines the attribute
//    noreturn for versions 2.5 and higher.
#if defined(__GNUC__)
#  if (((__GNUC__ == 2) && (__GNUC_MINOR__ >= 5)) || (__GNUC__ >= 3))
#    define NITRO_NO_RETURN \
       __attribute__ ((noreturn))
#  endif
#else
#  define NITRO_NO_RETURN
#endif


#ifdef NITRO_USE_TEMPLATE_META_PROGRAMMING_LOOP_UNROLLING
//--------------------------------------------------------------------------------
//  Helper macros for Template Meta-Programming techniques of for-loops unrolling
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
// Macro that generates an unrolled for loop for assigning elements of one array
// to elements of another array The array are assumed to be of same length
// (dimension), and this is also assumed to be the value of NumberOfIterations.
// No verification of size is performed. Casting is perfomed as part of the
// assignment, by using the DestinationElementType as the casting type. 
// Source and destination array types must have defined opearator[] in their API.
#define nitroFoorLoopAssignmentMacro(DestinationType,SourceType,DestinationElementType,DestinationArray,SourceArray,NumberOfIterations) \
    for(unsigned int i=0;i < NumberOfIterations; ++i) \
      { \
      DestinationArray[i] = static_cast< DestinationElementType >( SourceArray[i] ); \
      }

//--------------------------------------------------------------------------------
// Macro that generates an unrolled for loop for rounding and assigning
// elements of one array to elements of another array The array are assumed to
// be of same length (dimension), and this is also assumed to be the value of
// NumberOfIterations.  No verification of size is performed. Casting is
// perfomed as part of the assignment, by using the DestinationElementType as
// the casting type. 
// Source and destination array types must have defined opearator[] in their API.
#define nitroFoorLoopRoundingAndAssignmentMacro(DestinationType,SourceType,DestinationElementType,DestinationArray,SourceArray,NumberOfIterations) \
    for(unsigned int i=0;i < NumberOfIterations; ++i) \
      { \
      DestinationArray[i] = static_cast< DestinationElementType >( vnl_math_rnd( SourceArray[i] ) ); \
      }

#endif
// end of Template Meta Programming helper macros


#endif //end of nitroMacro.h
