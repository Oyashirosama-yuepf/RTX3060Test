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

#ifndef _TAO_IDL__HOME_YUEPF_DOCUMENTS_CODE_APA_PROJECT_BUILD_TDA4_UBUNTU_18_04_DEBUG_HOLO_PARKING_MSG_INCLUDE_HOLO_PARKING_MSG_COMMON_COMMONC_QO9YO2_H_
#define _TAO_IDL__HOME_YUEPF_DOCUMENTS_CODE_APA_PROJECT_BUILD_TDA4_UBUNTU_18_04_DEBUG_HOLO_PARKING_MSG_INCLUDE_HOLO_PARKING_MSG_COMMON_COMMONC_QO9YO2_H_

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

#include "holo_parking_msg/core/TypesC.h"

#if TAO_MAJOR_VERSION != 2 || TAO_MINOR_VERSION != 2 || TAO_BETA_VERSION != 0
#error This file should be regenerated with TAO_IDL
#endif

#if defined (TAO_EXPORT_MACRO)
#undef TAO_EXPORT_MACRO
#endif
#define TAO_EXPORT_MACRO 

// TAO_IDL - Generated from
// be/be_visitor_module/module_ch.cpp:38

namespace holo_parking_msg
{

  // TAO_IDL - Generated from
  // be/be_visitor_module/module_ch.cpp:38

  namespace common
  {

    // TAO_IDL - Generated from
    // be/be_visitor_typedef/typedef_ch.cpp:373

    typedef holo_parking_msg::core::uint32_t SensorId;
    typedef holo_parking_msg::core::uint32_t_out SensorId_out;

    // TAO_IDL - Generated from
    // be/be_visitor_typecode/typecode_decl.cpp:37

    extern  ::CORBA::TypeCode_ptr const _tc_SensorId;

    // TAO_IDL - Generated from
    // be/be_type.cpp:261

    struct Timestamp;

    typedef
      ::TAO_Fixed_Var_T<
          Timestamp
        >
      Timestamp_var;

    typedef
      Timestamp &
      Timestamp_out;

    // TAO_IDL - Generated from
    // be/be_visitor_structure/structure_ch.cpp:51

    struct  Timestamp
    {

      // TAO_IDL - Generated from
      // be/be_type.cpp:307

      
      typedef Timestamp_var _var_type;
      typedef Timestamp_out _out_type;

      static void _tao_any_destructor (void *);
      
      holo_parking_msg::core::uint32_t sec;
      holo_parking_msg::core::uint32_t nsec;
    };

    // TAO_IDL - Generated from
    // be/be_visitor_typecode/typecode_decl.cpp:37

    extern  ::CORBA::TypeCode_ptr const _tc_Timestamp;
  
  // TAO_IDL - Generated from
  // be/be_visitor_module/module_ch.cpp:67
  
  } // module holo_parking_msg::common

// TAO_IDL - Generated from
// be/be_visitor_module/module_ch.cpp:67

} // module holo_parking_msg

// TAO_IDL - Generated from
// be/be_visitor_arg_traits.cpp:68

TAO_BEGIN_VERSIONED_NAMESPACE_DECL


// Arg traits specializations.
namespace TAO
{

  // TAO_IDL - Generated from
  // be/be_visitor_arg_traits.cpp:947

  template<>
  class Arg_Traits< ::holo_parking_msg::common::Timestamp>
    : public
        Fixed_Size_Arg_Traits_T<
            ::holo_parking_msg::common::Timestamp,
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

namespace holo_parking_msg
{
  
  namespace common
  {
     void operator<<= (::CORBA::Any &, const ::holo_parking_msg::common::Timestamp &); // copying version
     void operator<<= (::CORBA::Any &, ::holo_parking_msg::common::Timestamp*); // noncopying version
     ::CORBA::Boolean operator>>= (const ::CORBA::Any &, ::holo_parking_msg::common::Timestamp *&); // deprecated
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, const ::holo_parking_msg::common::Timestamp *&);
  }
}

#else


TAO_BEGIN_VERSIONED_NAMESPACE_DECL

 void operator<<= (::CORBA::Any &, const holo_parking_msg::common::Timestamp &); // copying version
 void operator<<= (::CORBA::Any &, holo_parking_msg::common::Timestamp*); // noncopying version
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, holo_parking_msg::common::Timestamp *&); // deprecated
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, const holo_parking_msg::common::Timestamp *&);
TAO_END_VERSIONED_NAMESPACE_DECL



#endif

// TAO_IDL - Generated from
// be/be_visitor_structure/cdr_op_ch.cpp:46


TAO_BEGIN_VERSIONED_NAMESPACE_DECL

 ::CORBA::Boolean operator<< (TAO_OutputCDR &, const holo_parking_msg::common::Timestamp &);
 ::CORBA::Boolean operator>> (TAO_InputCDR &, holo_parking_msg::common::Timestamp &);

TAO_END_VERSIONED_NAMESPACE_DECL



// TAO_IDL - Generated from
// be/be_codegen.cpp:1703
#if defined (__ACE_INLINE__)
#include "CommonC.inl"
#endif /* defined INLINE */

#include /**/ "ace/post.h"

#endif /* ifndef */
