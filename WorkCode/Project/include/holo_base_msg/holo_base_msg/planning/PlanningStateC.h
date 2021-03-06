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

#ifndef _TAO_IDL__HOME_HOLO_WORKSPACE_BUILD_TDA4_UBUNTU_18_04_DEBUG_HOLO_BASE_MSG_INCLUDE_HOLO_BASE_MSG_PLANNING_PLANNINGSTATEC_TXFMGH_H_
#define _TAO_IDL__HOME_HOLO_WORKSPACE_BUILD_TDA4_UBUNTU_18_04_DEBUG_HOLO_BASE_MSG_INCLUDE_HOLO_BASE_MSG_PLANNING_PLANNINGSTATEC_TXFMGH_H_

#include /**/ "ace/pre.h"


#include /**/ "ace/config-all.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */


#include "tao/AnyTypeCode/AnyTypeCode_methods.h"
#include "tao/AnyTypeCode/Any.h"
#include "tao/ORB.h"
#include "tao/Basic_Types.h"
#include "tao/Sequence_T.h"
#include "tao/Seq_Var_T.h"
#include "tao/Seq_Out_T.h"
#include "tao/VarOut_T.h"
#include "tao/Arg_Traits_T.h"
#include "tao/Basic_Arguments.h"
#include "tao/Special_Basic_Arguments.h"
#include "tao/Any_Insert_Policy_T.h"
#include "tao/Fixed_Size_Argument_T.h"
#include "tao/Var_Size_Argument_T.h"
#include /**/ "tao/Version.h"
#include /**/ "tao/Versioned_Namespace.h"

#include "holo_base_msg/core/TypesC.h"

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

  namespace planning
  {

    // TAO_IDL - Generated from
    // be/be_visitor_sequence/sequence_ch.cpp:102

#if !defined (_HOLO_BASE_MSG_PLANNING_ERRORCODELIST_CH_)
#define _HOLO_BASE_MSG_PLANNING_ERRORCODELIST_CH_

    class ErrorCodeList;

    typedef
      ::TAO_FixedSeq_Var_T<
          ErrorCodeList
        >
      ErrorCodeList_var;

    typedef
      ::TAO_Seq_Out_T<
          ErrorCodeList
        >
      ErrorCodeList_out;

    class  ErrorCodeList
      : public
          ::TAO::unbounded_value_sequence<
              holo_base_msg::core::uint32_t
            >
    {
    public:
      ErrorCodeList (void);
      ErrorCodeList ( ::CORBA::ULong max);
      ErrorCodeList (
        ::CORBA::ULong max,
        ::CORBA::ULong length,
        ::CORBA::ULong* buffer,
        ::CORBA::Boolean release = false);
#if defined (ACE_HAS_CPP11)
      ErrorCodeList (const ErrorCodeList &) = default;
      ErrorCodeList (ErrorCodeList &&) = default;
      ErrorCodeList& operator= (const ErrorCodeList &) = default;
      ErrorCodeList& operator= (ErrorCodeList &&) = default;
#endif /* ACE_HAS_CPP11 */
      virtual ~ErrorCodeList (void);
      

      // TAO_IDL - Generated from
      // be/be_type.cpp:307

      
      typedef ErrorCodeList_var _var_type;
      typedef ErrorCodeList_out _out_type;

      static void _tao_any_destructor (void *);
    };

#endif /* end #if !defined */

    // TAO_IDL - Generated from
    // be/be_visitor_typecode/typecode_decl.cpp:37

    extern  ::CORBA::TypeCode_ptr const _tc_ErrorCodeList;

    // TAO_IDL - Generated from
    // be/be_visitor_sequence/sequence_ch.cpp:102

#if !defined (_HOLO_BASE_MSG_PLANNING_OBSIDLIST_CH_)
#define _HOLO_BASE_MSG_PLANNING_OBSIDLIST_CH_

    class ObsIdList;

    typedef
      ::TAO_FixedSeq_Var_T<
          ObsIdList
        >
      ObsIdList_var;

    typedef
      ::TAO_Seq_Out_T<
          ObsIdList
        >
      ObsIdList_out;

    class  ObsIdList
      : public
          ::TAO::unbounded_value_sequence<
              holo_base_msg::core::uint32_t
            >
    {
    public:
      ObsIdList (void);
      ObsIdList ( ::CORBA::ULong max);
      ObsIdList (
        ::CORBA::ULong max,
        ::CORBA::ULong length,
        ::CORBA::ULong* buffer,
        ::CORBA::Boolean release = false);
#if defined (ACE_HAS_CPP11)
      ObsIdList (const ObsIdList &) = default;
      ObsIdList (ObsIdList &&) = default;
      ObsIdList& operator= (const ObsIdList &) = default;
      ObsIdList& operator= (ObsIdList &&) = default;
#endif /* ACE_HAS_CPP11 */
      virtual ~ObsIdList (void);
      

      // TAO_IDL - Generated from
      // be/be_type.cpp:307

      
      typedef ObsIdList_var _var_type;
      typedef ObsIdList_out _out_type;

      static void _tao_any_destructor (void *);
    };

#endif /* end #if !defined */

    // TAO_IDL - Generated from
    // be/be_visitor_typecode/typecode_decl.cpp:37

    extern  ::CORBA::TypeCode_ptr const _tc_ObsIdList;

    // TAO_IDL - Generated from
    // be/be_type.cpp:261

    struct PlanningState;

    typedef
      ::TAO_Var_Var_T<
          PlanningState
        >
      PlanningState_var;

    typedef
      ::TAO_Out_T<
          PlanningState
        >
      PlanningState_out;

    // TAO_IDL - Generated from
    // be/be_visitor_structure/structure_ch.cpp:51

    struct  PlanningState
    {

      // TAO_IDL - Generated from
      // be/be_type.cpp:307

      
      typedef PlanningState_var _var_type;
      typedef PlanningState_out _out_type;

      static void _tao_any_destructor (void *);
      
      holo_base_msg::core::uint32_t mode_num;
      holo_base_msg::core::uint32_t curr_state;
      holo_base_msg::core::uint32_t activatable_mode;
      holo_base_msg::planning::ErrorCodeList error_code_list;
      holo_base_msg::planning::ObsIdList following_obs_ids;
      holo_base_msg::planning::ObsIdList cut_in_obs_ids;
      holo_base_msg::planning::ObsIdList avoiding_obs_ids;
      holo_base_msg::planning::ObsIdList lane_change_obs_ids;
    };

    // TAO_IDL - Generated from
    // be/be_visitor_typecode/typecode_decl.cpp:37

    extern  ::CORBA::TypeCode_ptr const _tc_PlanningState;

    // TAO_IDL - Generated from
    // be/be_type.cpp:261

    struct PlanningStateFunction;

    typedef
      ::TAO_Fixed_Var_T<
          PlanningStateFunction
        >
      PlanningStateFunction_var;

    typedef
      PlanningStateFunction &
      PlanningStateFunction_out;

    // TAO_IDL - Generated from
    // be/be_visitor_structure/structure_ch.cpp:51

    struct  PlanningStateFunction
    {

      // TAO_IDL - Generated from
      // be/be_type.cpp:307

      
      typedef PlanningStateFunction_var _var_type;
      typedef PlanningStateFunction_out _out_type;

      static void _tao_any_destructor (void *);
      
      holo_base_msg::core::uint16_t type;
      holo_base_msg::core::uint16_t alarm;
    };

    // TAO_IDL - Generated from
    // be/be_visitor_typecode/typecode_decl.cpp:37

    extern  ::CORBA::TypeCode_ptr const _tc_PlanningStateFunction;

    // TAO_IDL - Generated from
    // be/be_visitor_sequence/sequence_ch.cpp:102

#if !defined (_HOLO_BASE_MSG_PLANNING_PLANNINGSTATEFUNCTIONSEQUENCE_CH_)
#define _HOLO_BASE_MSG_PLANNING_PLANNINGSTATEFUNCTIONSEQUENCE_CH_

    class PlanningStateFunctionSequence;

    typedef
      ::TAO_FixedSeq_Var_T<
          PlanningStateFunctionSequence
        >
      PlanningStateFunctionSequence_var;

    typedef
      ::TAO_Seq_Out_T<
          PlanningStateFunctionSequence
        >
      PlanningStateFunctionSequence_out;

    class  PlanningStateFunctionSequence
      : public
          ::TAO::unbounded_value_sequence<
              PlanningStateFunction
            >
    {
    public:
      PlanningStateFunctionSequence (void);
      PlanningStateFunctionSequence ( ::CORBA::ULong max);
      PlanningStateFunctionSequence (
        ::CORBA::ULong max,
        ::CORBA::ULong length,
        PlanningStateFunction* buffer,
        ::CORBA::Boolean release = false);
#if defined (ACE_HAS_CPP11)
      PlanningStateFunctionSequence (const PlanningStateFunctionSequence &) = default;
      PlanningStateFunctionSequence (PlanningStateFunctionSequence &&) = default;
      PlanningStateFunctionSequence& operator= (const PlanningStateFunctionSequence &) = default;
      PlanningStateFunctionSequence& operator= (PlanningStateFunctionSequence &&) = default;
#endif /* ACE_HAS_CPP11 */
      virtual ~PlanningStateFunctionSequence (void);
      

      // TAO_IDL - Generated from
      // be/be_type.cpp:307

      
      typedef PlanningStateFunctionSequence_var _var_type;
      typedef PlanningStateFunctionSequence_out _out_type;

      static void _tao_any_destructor (void *);
    };

#endif /* end #if !defined */

    // TAO_IDL - Generated from
    // be/be_visitor_typecode/typecode_decl.cpp:37

    extern  ::CORBA::TypeCode_ptr const _tc_PlanningStateFunctionSequence;

    // TAO_IDL - Generated from
    // be/be_type.cpp:261

    struct State;

    typedef
      ::TAO_Var_Var_T<
          State
        >
      State_var;

    typedef
      ::TAO_Out_T<
          State
        >
      State_out;

    // TAO_IDL - Generated from
    // be/be_visitor_structure/structure_ch.cpp:51

    struct  State
    {

      // TAO_IDL - Generated from
      // be/be_type.cpp:307

      
      typedef State_var _var_type;
      typedef State_out _out_type;

      static void _tao_any_destructor (void *);
      
      holo_base_msg::core::uint16_t main_state;
      holo_base_msg::core::uint8_t longitudinal_state;
      holo_base_msg::core::uint8_t lateral_state;
      holo_base_msg::planning::PlanningStateFunctionSequence functions;
      holo_base_msg::planning::ObsIdList following_obs_ids;
      holo_base_msg::planning::ObsIdList cut_in_obs_ids;
      holo_base_msg::planning::ObsIdList avoiding_obs_ids;
      holo_base_msg::planning::ObsIdList lane_change_obs_ids;
    };

    // TAO_IDL - Generated from
    // be/be_visitor_typecode/typecode_decl.cpp:37

    extern  ::CORBA::TypeCode_ptr const _tc_State;
  
  // TAO_IDL - Generated from
  // be/be_visitor_module/module_ch.cpp:67
  
  } // module holo_base_msg::planning

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
  // be/be_visitor_arg_traits.cpp:685

  template<>
  class Arg_Traits< ::holo_base_msg::planning::ErrorCodeList>
    : public
        Var_Size_Arg_Traits_T<
            ::holo_base_msg::planning::ErrorCodeList,
            TAO::Any_Insert_Policy_Stream
          >
  {
  };

  // TAO_IDL - Generated from
  // be/be_visitor_arg_traits.cpp:685

  template<>
  class Arg_Traits< ::holo_base_msg::planning::ObsIdList>
    : public
        Var_Size_Arg_Traits_T<
            ::holo_base_msg::planning::ObsIdList,
            TAO::Any_Insert_Policy_Stream
          >
  {
  };

  // TAO_IDL - Generated from
  // be/be_visitor_arg_traits.cpp:947

  template<>
  class Arg_Traits< ::holo_base_msg::planning::PlanningState>
    : public
        Var_Size_Arg_Traits_T<
            ::holo_base_msg::planning::PlanningState,
            TAO::Any_Insert_Policy_Stream
          >
  {
  };

  // TAO_IDL - Generated from
  // be/be_visitor_arg_traits.cpp:947

  template<>
  class Arg_Traits< ::holo_base_msg::planning::PlanningStateFunction>
    : public
        Fixed_Size_Arg_Traits_T<
            ::holo_base_msg::planning::PlanningStateFunction,
            TAO::Any_Insert_Policy_Stream
          >
  {
  };

  // TAO_IDL - Generated from
  // be/be_visitor_arg_traits.cpp:685

  template<>
  class Arg_Traits< ::holo_base_msg::planning::PlanningStateFunctionSequence>
    : public
        Var_Size_Arg_Traits_T<
            ::holo_base_msg::planning::PlanningStateFunctionSequence,
            TAO::Any_Insert_Policy_Stream
          >
  {
  };

  // TAO_IDL - Generated from
  // be/be_visitor_arg_traits.cpp:947

  template<>
  class Arg_Traits< ::holo_base_msg::planning::State>
    : public
        Var_Size_Arg_Traits_T<
            ::holo_base_msg::planning::State,
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
// be/be_visitor_sequence/any_op_ch.cpp:50



#if defined (ACE_ANY_OPS_USE_NAMESPACE)

namespace holo_base_msg
{
  
  namespace planning
  {
     void operator<<= ( ::CORBA::Any &, const ::holo_base_msg::planning::ErrorCodeList &); // copying version
     void operator<<= ( ::CORBA::Any &, ::holo_base_msg::planning::ErrorCodeList*); // noncopying version
     ::CORBA::Boolean operator>>= (const ::CORBA::Any &, ::holo_base_msg::planning::ErrorCodeList *&); // deprecated
     ::CORBA::Boolean operator>>= (const ::CORBA::Any &, const ::holo_base_msg::planning::ErrorCodeList *&);
  }
}

#else


TAO_BEGIN_VERSIONED_NAMESPACE_DECL

 void operator<<= ( ::CORBA::Any &, const holo_base_msg::planning::ErrorCodeList &); // copying version
 void operator<<= ( ::CORBA::Any &, holo_base_msg::planning::ErrorCodeList*); // noncopying version
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, holo_base_msg::planning::ErrorCodeList *&); // deprecated
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, const holo_base_msg::planning::ErrorCodeList *&);
TAO_END_VERSIONED_NAMESPACE_DECL



#endif

// TAO_IDL - Generated from
// be/be_visitor_sequence/any_op_ch.cpp:50



#if defined (ACE_ANY_OPS_USE_NAMESPACE)

namespace holo_base_msg
{
  
  namespace planning
  {
     void operator<<= ( ::CORBA::Any &, const ::holo_base_msg::planning::ObsIdList &); // copying version
     void operator<<= ( ::CORBA::Any &, ::holo_base_msg::planning::ObsIdList*); // noncopying version
     ::CORBA::Boolean operator>>= (const ::CORBA::Any &, ::holo_base_msg::planning::ObsIdList *&); // deprecated
     ::CORBA::Boolean operator>>= (const ::CORBA::Any &, const ::holo_base_msg::planning::ObsIdList *&);
  }
}

#else


TAO_BEGIN_VERSIONED_NAMESPACE_DECL

 void operator<<= ( ::CORBA::Any &, const holo_base_msg::planning::ObsIdList &); // copying version
 void operator<<= ( ::CORBA::Any &, holo_base_msg::planning::ObsIdList*); // noncopying version
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, holo_base_msg::planning::ObsIdList *&); // deprecated
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, const holo_base_msg::planning::ObsIdList *&);
TAO_END_VERSIONED_NAMESPACE_DECL



#endif

// TAO_IDL - Generated from
// be/be_visitor_structure/any_op_ch.cpp:45



#if defined (ACE_ANY_OPS_USE_NAMESPACE)

namespace holo_base_msg
{
  
  namespace planning
  {
     void operator<<= (::CORBA::Any &, const ::holo_base_msg::planning::PlanningState &); // copying version
     void operator<<= (::CORBA::Any &, ::holo_base_msg::planning::PlanningState*); // noncopying version
     ::CORBA::Boolean operator>>= (const ::CORBA::Any &, ::holo_base_msg::planning::PlanningState *&); // deprecated
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, const ::holo_base_msg::planning::PlanningState *&);
  }
}

#else


TAO_BEGIN_VERSIONED_NAMESPACE_DECL

 void operator<<= (::CORBA::Any &, const holo_base_msg::planning::PlanningState &); // copying version
 void operator<<= (::CORBA::Any &, holo_base_msg::planning::PlanningState*); // noncopying version
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, holo_base_msg::planning::PlanningState *&); // deprecated
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, const holo_base_msg::planning::PlanningState *&);
TAO_END_VERSIONED_NAMESPACE_DECL



#endif

// TAO_IDL - Generated from
// be/be_visitor_structure/any_op_ch.cpp:45



#if defined (ACE_ANY_OPS_USE_NAMESPACE)

namespace holo_base_msg
{
  
  namespace planning
  {
     void operator<<= (::CORBA::Any &, const ::holo_base_msg::planning::PlanningStateFunction &); // copying version
     void operator<<= (::CORBA::Any &, ::holo_base_msg::planning::PlanningStateFunction*); // noncopying version
     ::CORBA::Boolean operator>>= (const ::CORBA::Any &, ::holo_base_msg::planning::PlanningStateFunction *&); // deprecated
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, const ::holo_base_msg::planning::PlanningStateFunction *&);
  }
}

#else


TAO_BEGIN_VERSIONED_NAMESPACE_DECL

 void operator<<= (::CORBA::Any &, const holo_base_msg::planning::PlanningStateFunction &); // copying version
 void operator<<= (::CORBA::Any &, holo_base_msg::planning::PlanningStateFunction*); // noncopying version
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, holo_base_msg::planning::PlanningStateFunction *&); // deprecated
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, const holo_base_msg::planning::PlanningStateFunction *&);
TAO_END_VERSIONED_NAMESPACE_DECL



#endif

// TAO_IDL - Generated from
// be/be_visitor_sequence/any_op_ch.cpp:50



#if defined (ACE_ANY_OPS_USE_NAMESPACE)

namespace holo_base_msg
{
  
  namespace planning
  {
     void operator<<= ( ::CORBA::Any &, const ::holo_base_msg::planning::PlanningStateFunctionSequence &); // copying version
     void operator<<= ( ::CORBA::Any &, ::holo_base_msg::planning::PlanningStateFunctionSequence*); // noncopying version
     ::CORBA::Boolean operator>>= (const ::CORBA::Any &, ::holo_base_msg::planning::PlanningStateFunctionSequence *&); // deprecated
     ::CORBA::Boolean operator>>= (const ::CORBA::Any &, const ::holo_base_msg::planning::PlanningStateFunctionSequence *&);
  }
}

#else


TAO_BEGIN_VERSIONED_NAMESPACE_DECL

 void operator<<= ( ::CORBA::Any &, const holo_base_msg::planning::PlanningStateFunctionSequence &); // copying version
 void operator<<= ( ::CORBA::Any &, holo_base_msg::planning::PlanningStateFunctionSequence*); // noncopying version
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, holo_base_msg::planning::PlanningStateFunctionSequence *&); // deprecated
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, const holo_base_msg::planning::PlanningStateFunctionSequence *&);
TAO_END_VERSIONED_NAMESPACE_DECL



#endif

// TAO_IDL - Generated from
// be/be_visitor_structure/any_op_ch.cpp:45



#if defined (ACE_ANY_OPS_USE_NAMESPACE)

namespace holo_base_msg
{
  
  namespace planning
  {
     void operator<<= (::CORBA::Any &, const ::holo_base_msg::planning::State &); // copying version
     void operator<<= (::CORBA::Any &, ::holo_base_msg::planning::State*); // noncopying version
     ::CORBA::Boolean operator>>= (const ::CORBA::Any &, ::holo_base_msg::planning::State *&); // deprecated
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, const ::holo_base_msg::planning::State *&);
  }
}

#else


TAO_BEGIN_VERSIONED_NAMESPACE_DECL

 void operator<<= (::CORBA::Any &, const holo_base_msg::planning::State &); // copying version
 void operator<<= (::CORBA::Any &, holo_base_msg::planning::State*); // noncopying version
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, holo_base_msg::planning::State *&); // deprecated
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, const holo_base_msg::planning::State *&);
TAO_END_VERSIONED_NAMESPACE_DECL



#endif

// TAO_IDL - Generated from
// be/be_visitor_sequence/cdr_op_ch.cpp:68

#if !defined _TAO_CDR_OP_holo_base_msg_planning_ErrorCodeList_H_
#define _TAO_CDR_OP_holo_base_msg_planning_ErrorCodeList_H_
TAO_BEGIN_VERSIONED_NAMESPACE_DECL


 ::CORBA::Boolean operator<< (
    TAO_OutputCDR &strm,
    const holo_base_msg::planning::ErrorCodeList &_tao_sequence);
 ::CORBA::Boolean operator>> (
    TAO_InputCDR &strm,
    holo_base_msg::planning::ErrorCodeList &_tao_sequence);

TAO_END_VERSIONED_NAMESPACE_DECL



#endif /* _TAO_CDR_OP_holo_base_msg_planning_ErrorCodeList_H_ */

// TAO_IDL - Generated from
// be/be_visitor_sequence/cdr_op_ch.cpp:68

#if !defined _TAO_CDR_OP_holo_base_msg_planning_ObsIdList_H_
#define _TAO_CDR_OP_holo_base_msg_planning_ObsIdList_H_
TAO_BEGIN_VERSIONED_NAMESPACE_DECL


 ::CORBA::Boolean operator<< (
    TAO_OutputCDR &strm,
    const holo_base_msg::planning::ObsIdList &_tao_sequence);
 ::CORBA::Boolean operator>> (
    TAO_InputCDR &strm,
    holo_base_msg::planning::ObsIdList &_tao_sequence);

TAO_END_VERSIONED_NAMESPACE_DECL



#endif /* _TAO_CDR_OP_holo_base_msg_planning_ObsIdList_H_ */

// TAO_IDL - Generated from
// be/be_visitor_structure/cdr_op_ch.cpp:46


TAO_BEGIN_VERSIONED_NAMESPACE_DECL

 ::CORBA::Boolean operator<< (TAO_OutputCDR &, const holo_base_msg::planning::PlanningState &);
 ::CORBA::Boolean operator>> (TAO_InputCDR &, holo_base_msg::planning::PlanningState &);

TAO_END_VERSIONED_NAMESPACE_DECL



// TAO_IDL - Generated from
// be/be_visitor_structure/cdr_op_ch.cpp:46


TAO_BEGIN_VERSIONED_NAMESPACE_DECL

 ::CORBA::Boolean operator<< (TAO_OutputCDR &, const holo_base_msg::planning::PlanningStateFunction &);
 ::CORBA::Boolean operator>> (TAO_InputCDR &, holo_base_msg::planning::PlanningStateFunction &);

TAO_END_VERSIONED_NAMESPACE_DECL



// TAO_IDL - Generated from
// be/be_visitor_sequence/cdr_op_ch.cpp:68

#if !defined _TAO_CDR_OP_holo_base_msg_planning_PlanningStateFunctionSequence_H_
#define _TAO_CDR_OP_holo_base_msg_planning_PlanningStateFunctionSequence_H_
TAO_BEGIN_VERSIONED_NAMESPACE_DECL


 ::CORBA::Boolean operator<< (
    TAO_OutputCDR &strm,
    const holo_base_msg::planning::PlanningStateFunctionSequence &_tao_sequence);
 ::CORBA::Boolean operator>> (
    TAO_InputCDR &strm,
    holo_base_msg::planning::PlanningStateFunctionSequence &_tao_sequence);

TAO_END_VERSIONED_NAMESPACE_DECL



#endif /* _TAO_CDR_OP_holo_base_msg_planning_PlanningStateFunctionSequence_H_ */

// TAO_IDL - Generated from
// be/be_visitor_structure/cdr_op_ch.cpp:46


TAO_BEGIN_VERSIONED_NAMESPACE_DECL

 ::CORBA::Boolean operator<< (TAO_OutputCDR &, const holo_base_msg::planning::State &);
 ::CORBA::Boolean operator>> (TAO_InputCDR &, holo_base_msg::planning::State &);

TAO_END_VERSIONED_NAMESPACE_DECL



// TAO_IDL - Generated from
// be/be_codegen.cpp:1703
#if defined (__ACE_INLINE__)
#include "PlanningStateC.inl"
#endif /* defined INLINE */

#include /**/ "ace/post.h"

#endif /* ifndef */

