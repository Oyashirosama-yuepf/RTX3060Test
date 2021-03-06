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

#ifndef _TAO_IDL__HOME_YUEPF_DOCUMENTS_CODE_APA_PROJECT_BUILD_TDA4_UBUNTU_18_04_DEBUG_HOLO_PARKING_MSG_INCLUDE_HOLO_PARKING_MSG_PLANNING_PATHATTRIBUTETYPESUPPORTC_Y4LBFL_H_
#define _TAO_IDL__HOME_YUEPF_DOCUMENTS_CODE_APA_PROJECT_BUILD_TDA4_UBUNTU_18_04_DEBUG_HOLO_PARKING_MSG_INCLUDE_HOLO_PARKING_MSG_PLANNING_PATHATTRIBUTETYPESUPPORTC_Y4LBFL_H_

#include /**/ "ace/pre.h"


#include /**/ "ace/config-all.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */


#include "tao/AnyTypeCode/AnyTypeCode_methods.h"
#include "tao/AnyTypeCode/Any.h"
#include "tao/ORB.h"
#include "tao/SystemException.h"
#include "tao/Basic_Types.h"
#include "tao/ORB_Constants.h"
#include "dds/DCPS/ZeroCopyInfoSeq_T.h"
#include "dds/DCPS/ZeroCopySeq_T.h"
#include "tao/Object.h"
#include "tao/String_Manager_T.h"
#include "tao/Sequence_T.h"
#include "tao/Objref_VarOut_T.h"
#include "tao/Seq_Var_T.h"
#include "tao/Seq_Out_T.h"
#include "tao/Arg_Traits_T.h"
#include "tao/Basic_Arguments.h"
#include "tao/Special_Basic_Arguments.h"
#include "tao/Any_Insert_Policy_T.h"
#include "tao/Fixed_Size_Argument_T.h"
#include "tao/Var_Size_Argument_T.h"
#include /**/ "tao/Version.h"
#include /**/ "tao/Versioned_Namespace.h"

#include "PathAttributeC.h"
#include "dds/DdsDcpsInfrastructureC.h"
#include "dds/DdsDcpsPublicationC.h"
#include "dds/DdsDcpsSubscriptionExtC.h"
#include "dds/DdsDcpsTopicC.h"
#include "dds/DdsDcpsTypeSupportExtC.h"

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

  namespace planning
  {

    // TAO_IDL - Generated from
    // be/be_visitor_sequence/sequence_ch.cpp:102

    typedef ::TAO::DCPS::ZeroCopyDataSeq< holo_parking_msg::planning::PathAttribute, DCPS_ZERO_COPY_SEQ_DEFAULT_SIZE> PathAttributeSeq;
    

    // TAO_IDL - Generated from
    // be/be_visitor_typecode/typecode_decl.cpp:37

    extern  ::CORBA::TypeCode_ptr const _tc_PathAttributeSeq;

    // TAO_IDL - Generated from
    // be/be_interface.cpp:751

#if !defined (_HOLO_PARKING_MSG_PLANNING_PATHATTRIBUTETYPESUPPORT__VAR_OUT_CH_)
#define _HOLO_PARKING_MSG_PLANNING_PATHATTRIBUTETYPESUPPORT__VAR_OUT_CH_

    class PathAttributeTypeSupport;
    typedef PathAttributeTypeSupport *PathAttributeTypeSupport_ptr;

    typedef
      TAO_Objref_Var_T<
          PathAttributeTypeSupport
        >
      PathAttributeTypeSupport_var;
    
    typedef
      TAO_Objref_Out_T<
          PathAttributeTypeSupport
        >
      PathAttributeTypeSupport_out;

#endif /* end #if !defined */

    // TAO_IDL - Generated from
    // be/be_visitor_interface/interface_ch.cpp:43

    class  PathAttributeTypeSupport
      : public virtual ::OpenDDS::DCPS::TypeSupport
    
    {
    public:

      // TAO_IDL - Generated from
      // be/be_type.cpp:307

      typedef PathAttributeTypeSupport_ptr _ptr_type;
      typedef PathAttributeTypeSupport_var _var_type;
      typedef PathAttributeTypeSupport_out _out_type;

      static void _tao_any_destructor (void *);

      // The static operations.
      static PathAttributeTypeSupport_ptr _duplicate (PathAttributeTypeSupport_ptr obj);

      static void _tao_release (PathAttributeTypeSupport_ptr obj);

      static PathAttributeTypeSupport_ptr _narrow (::CORBA::Object_ptr obj);
      static PathAttributeTypeSupport_ptr _unchecked_narrow (::CORBA::Object_ptr obj);
      static PathAttributeTypeSupport_ptr _nil (void);

      // TAO_IDL - Generated from
      // be/be_visitor_interface/interface_ch.cpp:140

      virtual ::CORBA::Boolean _is_a (const char *type_id);
      virtual const char* _interface_repository_id (void) const;
      virtual ::CORBA::Boolean marshal (TAO_OutputCDR &cdr);
    
    protected:
      // Abstract or local interface only.
      PathAttributeTypeSupport (void);

      

      virtual ~PathAttributeTypeSupport (void);
    
    private:
      // Private and unimplemented for concrete interfaces.
      ACE_UNIMPLEMENTED_FUNC (PathAttributeTypeSupport (const PathAttributeTypeSupport &))
#if defined (ACE_HAS_CPP11)
      ACE_UNIMPLEMENTED_FUNC (PathAttributeTypeSupport (PathAttributeTypeSupport &&))
#endif /* ACE_HAS_CPP11 */
      ACE_UNIMPLEMENTED_FUNC (PathAttributeTypeSupport &operator= (const PathAttributeTypeSupport &))
#if defined (ACE_HAS_CPP11)
      ACE_UNIMPLEMENTED_FUNC (PathAttributeTypeSupport &operator= (PathAttributeTypeSupport &&))
#endif /* ACE_HAS_CPP11 */
    };

    // TAO_IDL - Generated from
    // be/be_visitor_typecode/typecode_decl.cpp:37

    extern  ::CORBA::TypeCode_ptr const _tc_PathAttributeTypeSupport;

    // TAO_IDL - Generated from
    // be/be_interface.cpp:751

#if !defined (_HOLO_PARKING_MSG_PLANNING_PATHATTRIBUTEDATAWRITER__VAR_OUT_CH_)
#define _HOLO_PARKING_MSG_PLANNING_PATHATTRIBUTEDATAWRITER__VAR_OUT_CH_

    class PathAttributeDataWriter;
    typedef PathAttributeDataWriter *PathAttributeDataWriter_ptr;

    typedef
      TAO_Objref_Var_T<
          PathAttributeDataWriter
        >
      PathAttributeDataWriter_var;
    
    typedef
      TAO_Objref_Out_T<
          PathAttributeDataWriter
        >
      PathAttributeDataWriter_out;

#endif /* end #if !defined */

    // TAO_IDL - Generated from
    // be/be_visitor_interface/interface_ch.cpp:43

    class  PathAttributeDataWriter
      : public virtual ::DDS::DataWriter
    
    {
    public:

      // TAO_IDL - Generated from
      // be/be_type.cpp:307

      typedef PathAttributeDataWriter_ptr _ptr_type;
      typedef PathAttributeDataWriter_var _var_type;
      typedef PathAttributeDataWriter_out _out_type;

      static void _tao_any_destructor (void *);

      // The static operations.
      static PathAttributeDataWriter_ptr _duplicate (PathAttributeDataWriter_ptr obj);

      static void _tao_release (PathAttributeDataWriter_ptr obj);

      static PathAttributeDataWriter_ptr _narrow (::CORBA::Object_ptr obj);
      static PathAttributeDataWriter_ptr _unchecked_narrow (::CORBA::Object_ptr obj);
      static PathAttributeDataWriter_ptr _nil (void);

      virtual ::DDS::InstanceHandle_t register_instance (
        const ::holo_parking_msg::planning::PathAttribute & instance) = 0;

      virtual ::DDS::InstanceHandle_t register_instance_w_timestamp (
        const ::holo_parking_msg::planning::PathAttribute & instance,
        const ::DDS::Time_t & timestamp) = 0;

      virtual ::DDS::ReturnCode_t unregister_instance (
        const ::holo_parking_msg::planning::PathAttribute & instance,
        ::DDS::InstanceHandle_t handle) = 0;

      virtual ::DDS::ReturnCode_t unregister_instance_w_timestamp (
        const ::holo_parking_msg::planning::PathAttribute & instance,
        ::DDS::InstanceHandle_t handle,
        const ::DDS::Time_t & timestamp) = 0;

      virtual ::DDS::ReturnCode_t write (
        const ::holo_parking_msg::planning::PathAttribute & instance_data,
        ::DDS::InstanceHandle_t handle) = 0;

      virtual ::DDS::ReturnCode_t write_w_timestamp (
        const ::holo_parking_msg::planning::PathAttribute & instance_data,
        ::DDS::InstanceHandle_t handle,
        const ::DDS::Time_t & source_timestamp) = 0;

      virtual ::DDS::ReturnCode_t dispose (
        const ::holo_parking_msg::planning::PathAttribute & instance_data,
        ::DDS::InstanceHandle_t instance_handle) = 0;

      virtual ::DDS::ReturnCode_t dispose_w_timestamp (
        const ::holo_parking_msg::planning::PathAttribute & instance_data,
        ::DDS::InstanceHandle_t instance_handle,
        const ::DDS::Time_t & source_timestamp) = 0;

      virtual ::DDS::ReturnCode_t get_key_value (
        ::holo_parking_msg::planning::PathAttribute & key_holder,
        ::DDS::InstanceHandle_t handle) = 0;

      virtual ::DDS::InstanceHandle_t lookup_instance (
        const ::holo_parking_msg::planning::PathAttribute & instance_data) = 0;

      // TAO_IDL - Generated from
      // be/be_visitor_interface/interface_ch.cpp:140

      virtual ::CORBA::Boolean _is_a (const char *type_id);
      virtual const char* _interface_repository_id (void) const;
      virtual ::CORBA::Boolean marshal (TAO_OutputCDR &cdr);
    
    protected:
      // Abstract or local interface only.
      PathAttributeDataWriter (void);

      

      virtual ~PathAttributeDataWriter (void);
    
    private:
      // Private and unimplemented for concrete interfaces.
      ACE_UNIMPLEMENTED_FUNC (PathAttributeDataWriter (const PathAttributeDataWriter &))
#if defined (ACE_HAS_CPP11)
      ACE_UNIMPLEMENTED_FUNC (PathAttributeDataWriter (PathAttributeDataWriter &&))
#endif /* ACE_HAS_CPP11 */
      ACE_UNIMPLEMENTED_FUNC (PathAttributeDataWriter &operator= (const PathAttributeDataWriter &))
#if defined (ACE_HAS_CPP11)
      ACE_UNIMPLEMENTED_FUNC (PathAttributeDataWriter &operator= (PathAttributeDataWriter &&))
#endif /* ACE_HAS_CPP11 */
    };

    // TAO_IDL - Generated from
    // be/be_visitor_typecode/typecode_decl.cpp:37

    extern  ::CORBA::TypeCode_ptr const _tc_PathAttributeDataWriter;

    // TAO_IDL - Generated from
    // be/be_interface.cpp:751

#if !defined (_HOLO_PARKING_MSG_PLANNING_PATHATTRIBUTEDATAREADER__VAR_OUT_CH_)
#define _HOLO_PARKING_MSG_PLANNING_PATHATTRIBUTEDATAREADER__VAR_OUT_CH_

    class PathAttributeDataReader;
    typedef PathAttributeDataReader *PathAttributeDataReader_ptr;

    typedef
      TAO_Objref_Var_T<
          PathAttributeDataReader
        >
      PathAttributeDataReader_var;
    
    typedef
      TAO_Objref_Out_T<
          PathAttributeDataReader
        >
      PathAttributeDataReader_out;

#endif /* end #if !defined */

    // TAO_IDL - Generated from
    // be/be_visitor_interface/interface_ch.cpp:43

    class  PathAttributeDataReader
      : public virtual ::OpenDDS::DCPS::DataReaderEx
    
    {
    public:

      // TAO_IDL - Generated from
      // be/be_type.cpp:307

      typedef PathAttributeDataReader_ptr _ptr_type;
      typedef PathAttributeDataReader_var _var_type;
      typedef PathAttributeDataReader_out _out_type;

      static void _tao_any_destructor (void *);

      // The static operations.
      static PathAttributeDataReader_ptr _duplicate (PathAttributeDataReader_ptr obj);

      static void _tao_release (PathAttributeDataReader_ptr obj);

      static PathAttributeDataReader_ptr _narrow (::CORBA::Object_ptr obj);
      static PathAttributeDataReader_ptr _unchecked_narrow (::CORBA::Object_ptr obj);
      static PathAttributeDataReader_ptr _nil (void);

      virtual ::DDS::ReturnCode_t read (
        ::holo_parking_msg::planning::PathAttributeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        ::CORBA::Long max_samples,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) = 0;

      virtual ::DDS::ReturnCode_t take (
        ::holo_parking_msg::planning::PathAttributeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        ::CORBA::Long max_samples,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) = 0;

      virtual ::DDS::ReturnCode_t read_w_condition (
        ::holo_parking_msg::planning::PathAttributeSeq & data_values,
        ::DDS::SampleInfoSeq & sample_infos,
        ::CORBA::Long max_samples,
        ::DDS::ReadCondition_ptr a_condition) = 0;

      virtual ::DDS::ReturnCode_t take_w_condition (
        ::holo_parking_msg::planning::PathAttributeSeq & data_values,
        ::DDS::SampleInfoSeq & sample_infos,
        ::CORBA::Long max_samples,
        ::DDS::ReadCondition_ptr a_condition) = 0;

      virtual ::DDS::ReturnCode_t read_next_sample (
        ::holo_parking_msg::planning::PathAttribute & received_data,
        ::DDS::SampleInfo & sample_info) = 0;

      virtual ::DDS::ReturnCode_t take_next_sample (
        ::holo_parking_msg::planning::PathAttribute & received_data,
        ::DDS::SampleInfo & sample_info) = 0;

      virtual ::DDS::ReturnCode_t read_instance (
        ::holo_parking_msg::planning::PathAttributeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        ::CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) = 0;

      virtual ::DDS::ReturnCode_t take_instance (
        ::holo_parking_msg::planning::PathAttributeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        ::CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) = 0;

      virtual ::DDS::ReturnCode_t read_instance_w_condition (
        ::holo_parking_msg::planning::PathAttributeSeq & received_data,
        ::DDS::SampleInfoSeq & sample_infos,
        ::CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::ReadCondition_ptr a_condition) = 0;

      virtual ::DDS::ReturnCode_t take_instance_w_condition (
        ::holo_parking_msg::planning::PathAttributeSeq & received_data,
        ::DDS::SampleInfoSeq & sample_infos,
        ::CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::ReadCondition_ptr a_condition) = 0;

      virtual ::DDS::ReturnCode_t read_next_instance (
        ::holo_parking_msg::planning::PathAttributeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        ::CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) = 0;

      virtual ::DDS::ReturnCode_t take_next_instance (
        ::holo_parking_msg::planning::PathAttributeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        ::CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) = 0;

      virtual ::DDS::ReturnCode_t read_next_instance_w_condition (
        ::holo_parking_msg::planning::PathAttributeSeq & data_values,
        ::DDS::SampleInfoSeq & sample_infos,
        ::CORBA::Long max_samples,
        ::DDS::InstanceHandle_t previous_handle,
        ::DDS::ReadCondition_ptr a_condition) = 0;

      virtual ::DDS::ReturnCode_t take_next_instance_w_condition (
        ::holo_parking_msg::planning::PathAttributeSeq & data_values,
        ::DDS::SampleInfoSeq & sample_infos,
        ::CORBA::Long max_samples,
        ::DDS::InstanceHandle_t previous_handle,
        ::DDS::ReadCondition_ptr a_condition) = 0;

      virtual ::DDS::ReturnCode_t return_loan (
        ::holo_parking_msg::planning::PathAttributeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq) = 0;

      virtual ::DDS::ReturnCode_t get_key_value (
        ::holo_parking_msg::planning::PathAttribute & key_holder,
        ::DDS::InstanceHandle_t handle) = 0;

      virtual ::DDS::InstanceHandle_t lookup_instance (
        const ::holo_parking_msg::planning::PathAttribute & instance_data) = 0;

      // TAO_IDL - Generated from
      // be/be_visitor_interface/interface_ch.cpp:140

      virtual ::CORBA::Boolean _is_a (const char *type_id);
      virtual const char* _interface_repository_id (void) const;
      virtual ::CORBA::Boolean marshal (TAO_OutputCDR &cdr);
    
    protected:
      // Abstract or local interface only.
      PathAttributeDataReader (void);

      

      virtual ~PathAttributeDataReader (void);
    
    private:
      // Private and unimplemented for concrete interfaces.
      ACE_UNIMPLEMENTED_FUNC (PathAttributeDataReader (const PathAttributeDataReader &))
#if defined (ACE_HAS_CPP11)
      ACE_UNIMPLEMENTED_FUNC (PathAttributeDataReader (PathAttributeDataReader &&))
#endif /* ACE_HAS_CPP11 */
      ACE_UNIMPLEMENTED_FUNC (PathAttributeDataReader &operator= (const PathAttributeDataReader &))
#if defined (ACE_HAS_CPP11)
      ACE_UNIMPLEMENTED_FUNC (PathAttributeDataReader &operator= (PathAttributeDataReader &&))
#endif /* ACE_HAS_CPP11 */
    };

    // TAO_IDL - Generated from
    // be/be_visitor_typecode/typecode_decl.cpp:37

    extern  ::CORBA::TypeCode_ptr const _tc_PathAttributeDataReader;
  
  // TAO_IDL - Generated from
  // be/be_visitor_module/module_ch.cpp:67
  
  } // module holo_parking_msg::planning

// TAO_IDL - Generated from
// be/be_visitor_module/module_ch.cpp:67

} // module holo_parking_msg

// TAO_IDL - Generated from
// be/be_visitor_arg_traits.cpp:68

TAO_BEGIN_VERSIONED_NAMESPACE_DECL


// Arg traits specializations.
namespace TAO
{
}

TAO_END_VERSIONED_NAMESPACE_DECL



// TAO_IDL - Generated from
// be/be_visitor_traits.cpp:62

TAO_BEGIN_VERSIONED_NAMESPACE_DECL

// Traits specializations.
namespace TAO
{

#if !defined (_HOLO_PARKING_MSG_PLANNING_PATHATTRIBUTETYPESUPPORT__TRAITS_)
#define _HOLO_PARKING_MSG_PLANNING_PATHATTRIBUTETYPESUPPORT__TRAITS_

  template<>
  struct  Objref_Traits< ::holo_parking_msg::planning::PathAttributeTypeSupport>
  {
    static ::holo_parking_msg::planning::PathAttributeTypeSupport_ptr duplicate (
        ::holo_parking_msg::planning::PathAttributeTypeSupport_ptr p);
    static void release (
        ::holo_parking_msg::planning::PathAttributeTypeSupport_ptr p);
    static ::holo_parking_msg::planning::PathAttributeTypeSupport_ptr nil (void);
    static ::CORBA::Boolean marshal (
        const ::holo_parking_msg::planning::PathAttributeTypeSupport_ptr p,
        TAO_OutputCDR & cdr);
  };

#endif /* end #if !defined */

#if !defined (_HOLO_PARKING_MSG_PLANNING_PATHATTRIBUTEDATAWRITER__TRAITS_)
#define _HOLO_PARKING_MSG_PLANNING_PATHATTRIBUTEDATAWRITER__TRAITS_

  template<>
  struct  Objref_Traits< ::holo_parking_msg::planning::PathAttributeDataWriter>
  {
    static ::holo_parking_msg::planning::PathAttributeDataWriter_ptr duplicate (
        ::holo_parking_msg::planning::PathAttributeDataWriter_ptr p);
    static void release (
        ::holo_parking_msg::planning::PathAttributeDataWriter_ptr p);
    static ::holo_parking_msg::planning::PathAttributeDataWriter_ptr nil (void);
    static ::CORBA::Boolean marshal (
        const ::holo_parking_msg::planning::PathAttributeDataWriter_ptr p,
        TAO_OutputCDR & cdr);
  };

#endif /* end #if !defined */

#if !defined (_HOLO_PARKING_MSG_PLANNING_PATHATTRIBUTEDATAREADER__TRAITS_)
#define _HOLO_PARKING_MSG_PLANNING_PATHATTRIBUTEDATAREADER__TRAITS_

  template<>
  struct  Objref_Traits< ::holo_parking_msg::planning::PathAttributeDataReader>
  {
    static ::holo_parking_msg::planning::PathAttributeDataReader_ptr duplicate (
        ::holo_parking_msg::planning::PathAttributeDataReader_ptr p);
    static void release (
        ::holo_parking_msg::planning::PathAttributeDataReader_ptr p);
    static ::holo_parking_msg::planning::PathAttributeDataReader_ptr nil (void);
    static ::CORBA::Boolean marshal (
        const ::holo_parking_msg::planning::PathAttributeDataReader_ptr p,
        TAO_OutputCDR & cdr);
  };

#endif /* end #if !defined */
}
TAO_END_VERSIONED_NAMESPACE_DECL



// TAO_IDL - Generated from
// be/be_visitor_interface/any_op_ch.cpp:44



#if defined (ACE_ANY_OPS_USE_NAMESPACE)

namespace holo_parking_msg
{
  
  namespace planning
  {
     void operator<<= ( ::CORBA::Any &, PathAttributeTypeSupport_ptr); // copying
     void operator<<= ( ::CORBA::Any &, PathAttributeTypeSupport_ptr *); // non-copying
     ::CORBA::Boolean operator>>= (const ::CORBA::Any &, PathAttributeTypeSupport_ptr &);
  }
}

#else


TAO_BEGIN_VERSIONED_NAMESPACE_DECL

 void operator<<= (::CORBA::Any &, holo_parking_msg::planning::PathAttributeTypeSupport_ptr); // copying
 void operator<<= (::CORBA::Any &, holo_parking_msg::planning::PathAttributeTypeSupport_ptr *); // non-copying
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, holo_parking_msg::planning::PathAttributeTypeSupport_ptr &);
TAO_END_VERSIONED_NAMESPACE_DECL



#endif

// TAO_IDL - Generated from
// be/be_visitor_interface/any_op_ch.cpp:44



#if defined (ACE_ANY_OPS_USE_NAMESPACE)

namespace holo_parking_msg
{
  
  namespace planning
  {
     void operator<<= ( ::CORBA::Any &, PathAttributeDataWriter_ptr); // copying
     void operator<<= ( ::CORBA::Any &, PathAttributeDataWriter_ptr *); // non-copying
     ::CORBA::Boolean operator>>= (const ::CORBA::Any &, PathAttributeDataWriter_ptr &);
  }
}

#else


TAO_BEGIN_VERSIONED_NAMESPACE_DECL

 void operator<<= (::CORBA::Any &, holo_parking_msg::planning::PathAttributeDataWriter_ptr); // copying
 void operator<<= (::CORBA::Any &, holo_parking_msg::planning::PathAttributeDataWriter_ptr *); // non-copying
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, holo_parking_msg::planning::PathAttributeDataWriter_ptr &);
TAO_END_VERSIONED_NAMESPACE_DECL



#endif

// TAO_IDL - Generated from
// be/be_visitor_interface/any_op_ch.cpp:44



#if defined (ACE_ANY_OPS_USE_NAMESPACE)

namespace holo_parking_msg
{
  
  namespace planning
  {
     void operator<<= ( ::CORBA::Any &, PathAttributeDataReader_ptr); // copying
     void operator<<= ( ::CORBA::Any &, PathAttributeDataReader_ptr *); // non-copying
     ::CORBA::Boolean operator>>= (const ::CORBA::Any &, PathAttributeDataReader_ptr &);
  }
}

#else


TAO_BEGIN_VERSIONED_NAMESPACE_DECL

 void operator<<= (::CORBA::Any &, holo_parking_msg::planning::PathAttributeDataReader_ptr); // copying
 void operator<<= (::CORBA::Any &, holo_parking_msg::planning::PathAttributeDataReader_ptr *); // non-copying
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, holo_parking_msg::planning::PathAttributeDataReader_ptr &);
TAO_END_VERSIONED_NAMESPACE_DECL



#endif

// TAO_IDL - Generated from
// be/be_codegen.cpp:1703
#if defined (__ACE_INLINE__)
#include "PathAttributeTypeSupportC.inl"
#endif /* defined INLINE */

#include /**/ "ace/post.h"

#endif /* ifndef */

