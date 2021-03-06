// -*- C++ -*-
// $Id$

/**
 * Code generated by the The ACE ORB (TAO) IDL Compiler v2.2a_p19
 * TAO and the TAO IDL Compiler have been developed by:
 *       Center for Distributed Object Computing
 *       Washington University
 *       St. Louis, MO
 *       USA
 *       http://www.cs.wustl.edu/~schmidt/doc-center.html
 * and
 *       Distributed Object Computing Laboratory
 *       University of California at Irvine
 *       Irvine, CA
 *       USA
 * and
 *       Institute for Software Integrated Systems
 *       Vanderbilt University
 *       Nashville, TN
 *       USA
 *       http://www.isis.vanderbilt.edu/
 *
 * Information about TAO is available at:
 *     http://www.cs.wustl.edu/~schmidt/TAO.html
 **/

// TAO_IDL - Generated from
// be/be_codegen.cpp:152

#ifndef _TAO_IDL__HOME_HOLO_WORKSPACE_BUILD_TDA4_UBUNTU_18_04_DEBUG_HOLO_BASE_MSG_INCLUDE_HOLO_BASE_MSG_GEOMETRY_LINEC_163HPF_H_
#define _TAO_IDL__HOME_HOLO_WORKSPACE_BUILD_TDA4_UBUNTU_18_04_DEBUG_HOLO_BASE_MSG_INCLUDE_HOLO_BASE_MSG_GEOMETRY_LINEC_163HPF_H_

#include /**/ "ace/pre.h"


#include /**/ "ace/config-all.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */


#include "tao/AnyTypeCode/AnyTypeCode_methods.h"
#include "tao/AnyTypeCode/Any.h"
#include "tao/ORB.h"
#include "tao/Basic_Types.h"
#include "tao/VarOut_T.h"
#include "tao/Arg_Traits_T.h"
#include "tao/Basic_Arguments.h"
#include "tao/Special_Basic_Arguments.h"
#include "tao/Any_Insert_Policy_T.h"
#include "tao/Fixed_Size_Argument_T.h"
#include "tao/Var_Size_Argument_T.h"
#include /**/ "tao/Version.h"
#include /**/ "tao/Versioned_Namespace.h"

#include "holo_base_msg/numerics/VectorC.h"

#if TAO_MAJOR_VERSION != 2 || TAO_MINOR_VERSION != 2 || TAO_BETA_VERSION != 0
#error This file should be regenerated with TAO_IDL
#endif

#if defined (TAO_EXPORT_MACRO)
#undef TAO_EXPORT_MACRO
#endif
#define TAO_EXPORT_MACRO 

// TAO_IDL - Generated from
// be/be_visitor_module/module_ch.cpp:38

namespace holo_base_msg
{

  // TAO_IDL - Generated from
  // be/be_visitor_module/module_ch.cpp:38

  namespace geometry
  {

    // TAO_IDL - Generated from
    // be/be_type.cpp:261

    struct Line2f;

    typedef
      ::TAO_Fixed_Var_T<
          Line2f
        >
      Line2f_var;

    typedef
      Line2f &
      Line2f_out;

    // TAO_IDL - Generated from
    // be/be_visitor_structure/structure_ch.cpp:51

    struct  Line2f
    {

      // TAO_IDL - Generated from
      // be/be_type.cpp:307

      
      typedef Line2f_var _var_type;
      typedef Line2f_out _out_type;

      static void _tao_any_destructor (void *);
      
      holo_base_msg::numerics::Vector3f cofficients;
    };

    // TAO_IDL - Generated from
    // be/be_visitor_typecode/typecode_decl.cpp:37

    extern  ::CORBA::TypeCode_ptr const _tc_Line2f;

    // TAO_IDL - Generated from
    // be/be_type.cpp:261

    struct Line2d;

    typedef
      ::TAO_Fixed_Var_T<
          Line2d
        >
      Line2d_var;

    typedef
      Line2d &
      Line2d_out;

    // TAO_IDL - Generated from
    // be/be_visitor_structure/structure_ch.cpp:51

    struct  Line2d
    {

      // TAO_IDL - Generated from
      // be/be_type.cpp:307

      
      typedef Line2d_var _var_type;
      typedef Line2d_out _out_type;

      static void _tao_any_destructor (void *);
      
      holo_base_msg::numerics::Vector3d cofficients;
    };

    // TAO_IDL - Generated from
    // be/be_visitor_typecode/typecode_decl.cpp:37

    extern  ::CORBA::TypeCode_ptr const _tc_Line2d;
  
  // TAO_IDL - Generated from
  // be/be_visitor_module/module_ch.cpp:67
  
  } // module holo_base_msg::geometry

// TAO_IDL - Generated from
// be/be_visitor_module/module_ch.cpp:67

} // module holo_base_msg

// TAO_IDL - Generated from
// be/be_visitor_arg_traits.cpp:68

TAO_BEGIN_VERSIONED_NAMESPACE_DECL


// Arg traits specializations.
namespace TAO
{

  // TAO_IDL - Generated from
  // be/be_visitor_arg_traits.cpp:947

  template<>
  class Arg_Traits< ::holo_base_msg::geometry::Line2f>
    : public
        Fixed_Size_Arg_Traits_T<
            ::holo_base_msg::geometry::Line2f,
            TAO::Any_Insert_Policy_Stream
          >
  {
  };

  // TAO_IDL - Generated from
  // be/be_visitor_arg_traits.cpp:947

  template<>
  class Arg_Traits< ::holo_base_msg::geometry::Line2d>
    : public
        Fixed_Size_Arg_Traits_T<
            ::holo_base_msg::geometry::Line2d,
            TAO::Any_Insert_Policy_Stream
          >
  {
  };
}

TAO_END_VERSIONED_NAMESPACE_DECL



// TAO_IDL - Generated from
// be/be_visitor_traits.cpp:62

TAO_BEGIN_VERSIONED_NAMESPACE_DECL

// Traits specializations.
namespace TAO
{
}
TAO_END_VERSIONED_NAMESPACE_DECL



// TAO_IDL - Generated from
// be/be_visitor_structure/any_op_ch.cpp:45



#if defined (ACE_ANY_OPS_USE_NAMESPACE)

namespace holo_base_msg
{
  
  namespace geometry
  {
     void operator<<= (::CORBA::Any &, const ::holo_base_msg::geometry::Line2f &); // copying version
     void operator<<= (::CORBA::Any &, ::holo_base_msg::geometry::Line2f*); // noncopying version
     ::CORBA::Boolean operator>>= (const ::CORBA::Any &, ::holo_base_msg::geometry::Line2f *&); // deprecated
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, const ::holo_base_msg::geometry::Line2f *&);
  }
}

#else


TAO_BEGIN_VERSIONED_NAMESPACE_DECL

 void operator<<= (::CORBA::Any &, const holo_base_msg::geometry::Line2f &); // copying version
 void operator<<= (::CORBA::Any &, holo_base_msg::geometry::Line2f*); // noncopying version
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, holo_base_msg::geometry::Line2f *&); // deprecated
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, const holo_base_msg::geometry::Line2f *&);
TAO_END_VERSIONED_NAMESPACE_DECL



#endif

// TAO_IDL - Generated from
// be/be_visitor_structure/any_op_ch.cpp:45



#if defined (ACE_ANY_OPS_USE_NAMESPACE)

namespace holo_base_msg
{
  
  namespace geometry
  {
     void operator<<= (::CORBA::Any &, const ::holo_base_msg::geometry::Line2d &); // copying version
     void operator<<= (::CORBA::Any &, ::holo_base_msg::geometry::Line2d*); // noncopying version
     ::CORBA::Boolean operator>>= (const ::CORBA::Any &, ::holo_base_msg::geometry::Line2d *&); // deprecated
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, const ::holo_base_msg::geometry::Line2d *&);
  }
}

#else


TAO_BEGIN_VERSIONED_NAMESPACE_DECL

 void operator<<= (::CORBA::Any &, const holo_base_msg::geometry::Line2d &); // copying version
 void operator<<= (::CORBA::Any &, holo_base_msg::geometry::Line2d*); // noncopying version
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, holo_base_msg::geometry::Line2d *&); // deprecated
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, const holo_base_msg::geometry::Line2d *&);
TAO_END_VERSIONED_NAMESPACE_DECL



#endif

// TAO_IDL - Generated from
// be/be_visitor_structure/cdr_op_ch.cpp:46


TAO_BEGIN_VERSIONED_NAMESPACE_DECL

 ::CORBA::Boolean operator<< (TAO_OutputCDR &, const holo_base_msg::geometry::Line2f &);
 ::CORBA::Boolean operator>> (TAO_InputCDR &, holo_base_msg::geometry::Line2f &);

TAO_END_VERSIONED_NAMESPACE_DECL



// TAO_IDL - Generated from
// be/be_visitor_structure/cdr_op_ch.cpp:46


TAO_BEGIN_VERSIONED_NAMESPACE_DECL

 ::CORBA::Boolean operator<< (TAO_OutputCDR &, const holo_base_msg::geometry::Line2d &);
 ::CORBA::Boolean operator>> (TAO_InputCDR &, holo_base_msg::geometry::Line2d &);

TAO_END_VERSIONED_NAMESPACE_DECL



// TAO_IDL - Generated from
// be/be_codegen.cpp:1703
#if defined (__ACE_INLINE__)
#include "LineC.inl"
#endif /* defined INLINE */

#include /**/ "ace/post.h"

#endif /* ifndef */

