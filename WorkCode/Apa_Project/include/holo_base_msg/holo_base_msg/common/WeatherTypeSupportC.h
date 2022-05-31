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

#ifndef _TAO_IDL__HOME_HOLO_WORKSPACE_BUILD_TDA4_UBUNTU_18_04_DEBUG_HOLO_BASE_MSG_INCLUDE_HOLO_BASE_MSG_COMMON_WEATHERTYPESUPPORTC_SHV8WN_H_
#define _TAO_IDL__HOME_HOLO_WORKSPACE_BUILD_TDA4_UBUNTU_18_04_DEBUG_HOLO_BASE_MSG_INCLUDE_HOLO_BASE_MSG_COMMON_WEATHERTYPESUPPORTC_SHV8WN_H_

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

#include "WeatherC.h"
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

namespace holo_base_msg
{

  // TAO_IDL - Generated from
  // be/be_visitor_module/module_ch.cpp:38

  namespace common
  {

    // TAO_IDL - Generated from
    // be/be_visitor_sequence/sequence_ch.cpp:102

    typedef ::TAO::DCPS::ZeroCopyDataSeq< holo_base_msg::common::Weather, DCPS_ZERO_COPY_SEQ_DEFAULT_SIZE> WeatherSeq;
    

    // TAO_IDL - Generated from
    // be/be_visitor_typecode/typecode_decl.cpp:37

    extern  ::CORBA::TypeCode_ptr const _tc_WeatherSeq;

    // TAO_IDL - Generated from
    // be/be_interface.cpp:751

#if !defined (_HOLO_BASE_MSG_COMMON_WEATHERTYPESUPPORT__VAR_OUT_CH_)
#define _HOLO_BASE_MSG_COMMON_WEATHERTYPESUPPORT__VAR_OUT_CH_

    class WeatherTypeSupport;
    typedef WeatherTypeSupport *WeatherTypeSupport_ptr;

    typedef
      TAO_Objref_Var_T<
          WeatherTypeSupport
        >
      WeatherTypeSupport_var;
    
    typedef
      TAO_Objref_Out_T<
          WeatherTypeSupport
        >
      WeatherTypeSupport_out;

#endif /* end #if !defined */

    // TAO_IDL - Generated from
    // be/be_visitor_interface/interface_ch.cpp:43

    class  WeatherTypeSupport
      : public virtual ::OpenDDS::DCPS::TypeSupport
    
    {
    public:

      // TAO_IDL - Generated from
      // be/be_type.cpp:307

      typedef WeatherTypeSupport_ptr _ptr_type;
      typedef WeatherTypeSupport_var _var_type;
      typedef WeatherTypeSupport_out _out_type;

      static void _tao_any_destructor (void *);

      // The static operations.
      static WeatherTypeSupport_ptr _duplicate (WeatherTypeSupport_ptr obj);

      static void _tao_release (WeatherTypeSupport_ptr obj);

      static WeatherTypeSupport_ptr _narrow (::CORBA::Object_ptr obj);
      static WeatherTypeSupport_ptr _unchecked_narrow (::CORBA::Object_ptr obj);
      static WeatherTypeSupport_ptr _nil (void);

      // TAO_IDL - Generated from
      // be/be_visitor_interface/interface_ch.cpp:140

      virtual ::CORBA::Boolean _is_a (const char *type_id);
      virtual const char* _interface_repository_id (void) const;
      virtual ::CORBA::Boolean marshal (TAO_OutputCDR &cdr);
    
    protected:
      // Abstract or local interface only.
      WeatherTypeSupport (void);

      

      virtual ~WeatherTypeSupport (void);
    
    private:
      // Private and unimplemented for concrete interfaces.
      ACE_UNIMPLEMENTED_FUNC (WeatherTypeSupport (const WeatherTypeSupport &))
#if defined (ACE_HAS_CPP11)
      ACE_UNIMPLEMENTED_FUNC (WeatherTypeSupport (WeatherTypeSupport &&))
#endif /* ACE_HAS_CPP11 */
      ACE_UNIMPLEMENTED_FUNC (WeatherTypeSupport &operator= (const WeatherTypeSupport &))
#if defined (ACE_HAS_CPP11)
      ACE_UNIMPLEMENTED_FUNC (WeatherTypeSupport &operator= (WeatherTypeSupport &&))
#endif /* ACE_HAS_CPP11 */
    };

    // TAO_IDL - Generated from
    // be/be_visitor_typecode/typecode_decl.cpp:37

    extern  ::CORBA::TypeCode_ptr const _tc_WeatherTypeSupport;

    // TAO_IDL - Generated from
    // be/be_interface.cpp:751

#if !defined (_HOLO_BASE_MSG_COMMON_WEATHERDATAWRITER__VAR_OUT_CH_)
#define _HOLO_BASE_MSG_COMMON_WEATHERDATAWRITER__VAR_OUT_CH_

    class WeatherDataWriter;
    typedef WeatherDataWriter *WeatherDataWriter_ptr;

    typedef
      TAO_Objref_Var_T<
          WeatherDataWriter
        >
      WeatherDataWriter_var;
    
    typedef
      TAO_Objref_Out_T<
          WeatherDataWriter
        >
      WeatherDataWriter_out;

#endif /* end #if !defined */

    // TAO_IDL - Generated from
    // be/be_visitor_interface/interface_ch.cpp:43

    class  WeatherDataWriter
      : public virtual ::DDS::DataWriter
    
    {
    public:

      // TAO_IDL - Generated from
      // be/be_type.cpp:307

      typedef WeatherDataWriter_ptr _ptr_type;
      typedef WeatherDataWriter_var _var_type;
      typedef WeatherDataWriter_out _out_type;

      static void _tao_any_destructor (void *);

      // The static operations.
      static WeatherDataWriter_ptr _duplicate (WeatherDataWriter_ptr obj);

      static void _tao_release (WeatherDataWriter_ptr obj);

      static WeatherDataWriter_ptr _narrow (::CORBA::Object_ptr obj);
      static WeatherDataWriter_ptr _unchecked_narrow (::CORBA::Object_ptr obj);
      static WeatherDataWriter_ptr _nil (void);

      virtual ::DDS::InstanceHandle_t register_instance (
        const ::holo_base_msg::common::Weather & instance) = 0;

      virtual ::DDS::InstanceHandle_t register_instance_w_timestamp (
        const ::holo_base_msg::common::Weather & instance,
        const ::DDS::Time_t & timestamp) = 0;

      virtual ::DDS::ReturnCode_t unregister_instance (
        const ::holo_base_msg::common::Weather & instance,
        ::DDS::InstanceHandle_t handle) = 0;

      virtual ::DDS::ReturnCode_t unregister_instance_w_timestamp (
        const ::holo_base_msg::common::Weather & instance,
        ::DDS::InstanceHandle_t handle,
        const ::DDS::Time_t & timestamp) = 0;

      virtual ::DDS::ReturnCode_t write (
        const ::holo_base_msg::common::Weather & instance_data,
        ::DDS::InstanceHandle_t handle) = 0;

      virtual ::DDS::ReturnCode_t write_w_timestamp (
        const ::holo_base_msg::common::Weather & instance_data,
        ::DDS::InstanceHandle_t handle,
        const ::DDS::Time_t & source_timestamp) = 0;

      virtual ::DDS::ReturnCode_t dispose (
        const ::holo_base_msg::common::Weather & instance_data,
        ::DDS::InstanceHandle_t instance_handle) = 0;

      virtual ::DDS::ReturnCode_t dispose_w_timestamp (
        const ::holo_base_msg::common::Weather & instance_data,
        ::DDS::InstanceHandle_t instance_handle,
        const ::DDS::Time_t & source_timestamp) = 0;

      virtual ::DDS::ReturnCode_t get_key_value (
        ::holo_base_msg::common::Weather & key_holder,
        ::DDS::InstanceHandle_t handle) = 0;

      virtual ::DDS::InstanceHandle_t lookup_instance (
        const ::holo_base_msg::common::Weather & instance_data) = 0;

      // TAO_IDL - Generated from
      // be/be_visitor_interface/interface_ch.cpp:140

      virtual ::CORBA::Boolean _is_a (const char *type_id);
      virtual const char* _interface_repository_id (void) const;
      virtual ::CORBA::Boolean marshal (TAO_OutputCDR &cdr);
    
    protected:
      // Abstract or local interface only.
      WeatherDataWriter (void);

      

      virtual ~WeatherDataWriter (void);
    
    private:
      // Private and unimplemented for concrete interfaces.
      ACE_UNIMPLEMENTED_FUNC (WeatherDataWriter (const WeatherDataWriter &))
#if defined (ACE_HAS_CPP11)
      ACE_UNIMPLEMENTED_FUNC (WeatherDataWriter (WeatherDataWriter &&))
#endif /* ACE_HAS_CPP11 */
      ACE_UNIMPLEMENTED_FUNC (WeatherDataWriter &operator= (const WeatherDataWriter &))
#if defined (ACE_HAS_CPP11)
      ACE_UNIMPLEMENTED_FUNC (WeatherDataWriter &operator= (WeatherDataWriter &&))
#endif /* ACE_HAS_CPP11 */
    };

    // TAO_IDL - Generated from
    // be/be_visitor_typecode/typecode_decl.cpp:37

    extern  ::CORBA::TypeCode_ptr const _tc_WeatherDataWriter;

    // TAO_IDL - Generated from
    // be/be_interface.cpp:751

#if !defined (_HOLO_BASE_MSG_COMMON_WEATHERDATAREADER__VAR_OUT_CH_)
#define _HOLO_BASE_MSG_COMMON_WEATHERDATAREADER__VAR_OUT_CH_

    class WeatherDataReader;
    typedef WeatherDataReader *WeatherDataReader_ptr;

    typedef
      TAO_Objref_Var_T<
          WeatherDataReader
        >
      WeatherDataReader_var;
    
    typedef
      TAO_Objref_Out_T<
          WeatherDataReader
        >
      WeatherDataReader_out;

#endif /* end #if !defined */

    // TAO_IDL - Generated from
    // be/be_visitor_interface/interface_ch.cpp:43

    class  WeatherDataReader
      : public virtual ::OpenDDS::DCPS::DataReaderEx
    
    {
    public:

      // TAO_IDL - Generated from
      // be/be_type.cpp:307

      typedef WeatherDataReader_ptr _ptr_type;
      typedef WeatherDataReader_var _var_type;
      typedef WeatherDataReader_out _out_type;

      static void _tao_any_destructor (void *);

      // The static operations.
      static WeatherDataReader_ptr _duplicate (WeatherDataReader_ptr obj);

      static void _tao_release (WeatherDataReader_ptr obj);

      static WeatherDataReader_ptr _narrow (::CORBA::Object_ptr obj);
      static WeatherDataReader_ptr _unchecked_narrow (::CORBA::Object_ptr obj);
      static WeatherDataReader_ptr _nil (void);

      virtual ::DDS::ReturnCode_t read (
        ::holo_base_msg::common::WeatherSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        ::CORBA::Long max_samples,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) = 0;

      virtual ::DDS::ReturnCode_t take (
        ::holo_base_msg::common::WeatherSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        ::CORBA::Long max_samples,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) = 0;

      virtual ::DDS::ReturnCode_t read_w_condition (
        ::holo_base_msg::common::WeatherSeq & data_values,
        ::DDS::SampleInfoSeq & sample_infos,
        ::CORBA::Long max_samples,
        ::DDS::ReadCondition_ptr a_condition) = 0;

      virtual ::DDS::ReturnCode_t take_w_condition (
        ::holo_base_msg::common::WeatherSeq & data_values,
        ::DDS::SampleInfoSeq & sample_infos,
        ::CORBA::Long max_samples,
        ::DDS::ReadCondition_ptr a_condition) = 0;

      virtual ::DDS::ReturnCode_t read_next_sample (
        ::holo_base_msg::common::Weather & received_data,
        ::DDS::SampleInfo & sample_info) = 0;

      virtual ::DDS::ReturnCode_t take_next_sample (
        ::holo_base_msg::common::Weather & received_data,
        ::DDS::SampleInfo & sample_info) = 0;

      virtual ::DDS::ReturnCode_t read_instance (
        ::holo_base_msg::common::WeatherSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        ::CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) = 0;

      virtual ::DDS::ReturnCode_t take_instance (
        ::holo_base_msg::common::WeatherSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        ::CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) = 0;

      virtual ::DDS::ReturnCode_t read_instance_w_condition (
        ::holo_base_msg::common::WeatherSeq & received_data,
        ::DDS::SampleInfoSeq & sample_infos,
        ::CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::ReadCondition_ptr a_condition) = 0;

      virtual ::DDS::ReturnCode_t take_instance_w_condition (
        ::holo_base_msg::common::WeatherSeq & received_data,
        ::DDS::SampleInfoSeq & sample_infos,
        ::CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::ReadCondition_ptr a_condition) = 0;

      virtual ::DDS::ReturnCode_t read_next_instance (
        ::holo_base_msg::common::WeatherSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        ::CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) = 0;

      virtual ::DDS::ReturnCode_t take_next_instance (
        ::holo_base_msg::common::WeatherSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        ::CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) = 0;

      virtual ::DDS::ReturnCode_t read_next_instance_w_condition (
        ::holo_base_msg::common::WeatherSeq & data_values,
        ::DDS::SampleInfoSeq & sample_infos,
        ::CORBA::Long max_samples,
        ::DDS::InstanceHandle_t previous_handle,
        ::DDS::ReadCondition_ptr a_condition) = 0;

      virtual ::DDS::ReturnCode_t take_next_instance_w_condition (
        ::holo_base_msg::common::WeatherSeq & data_values,
        ::DDS::SampleInfoSeq & sample_infos,
        ::CORBA::Long max_samples,
        ::DDS::InstanceHandle_t previous_handle,
        ::DDS::ReadCondition_ptr a_condition) = 0;

      virtual ::DDS::ReturnCode_t return_loan (
        ::holo_base_msg::common::WeatherSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq) = 0;

      virtual ::DDS::ReturnCode_t get_key_value (
        ::holo_base_msg::common::Weather & key_holder,
        ::DDS::InstanceHandle_t handle) = 0;

      virtual ::DDS::InstanceHandle_t lookup_instance (
        const ::holo_base_msg::common::Weather & instance_data) = 0;

      // TAO_IDL - Generated from
      // be/be_visitor_interface/interface_ch.cpp:140

      virtual ::CORBA::Boolean _is_a (const char *type_id);
      virtual const char* _interface_repository_id (void) const;
      virtual ::CORBA::Boolean marshal (TAO_OutputCDR &cdr);
    
    protected:
      // Abstract or local interface only.
      WeatherDataReader (void);

      

      virtual ~WeatherDataReader (void);
    
    private:
      // Private and unimplemented for concrete interfaces.
      ACE_UNIMPLEMENTED_FUNC (WeatherDataReader (const WeatherDataReader &))
#if defined (ACE_HAS_CPP11)
      ACE_UNIMPLEMENTED_FUNC (WeatherDataReader (WeatherDataReader &&))
#endif /* ACE_HAS_CPP11 */
      ACE_UNIMPLEMENTED_FUNC (WeatherDataReader &operator= (const WeatherDataReader &))
#if defined (ACE_HAS_CPP11)
      ACE_UNIMPLEMENTED_FUNC (WeatherDataReader &operator= (WeatherDataReader &&))
#endif /* ACE_HAS_CPP11 */
    };

    // TAO_IDL - Generated from
    // be/be_visitor_typecode/typecode_decl.cpp:37

    extern  ::CORBA::TypeCode_ptr const _tc_WeatherDataReader;
  
  // TAO_IDL - Generated from
  // be/be_visitor_module/module_ch.cpp:67
  
  } // module holo_base_msg::common

// TAO_IDL - Generated from
// be/be_visitor_module/module_ch.cpp:67

} // module holo_base_msg

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

#if !defined (_HOLO_BASE_MSG_COMMON_WEATHERTYPESUPPORT__TRAITS_)
#define _HOLO_BASE_MSG_COMMON_WEATHERTYPESUPPORT__TRAITS_

  template<>
  struct  Objref_Traits< ::holo_base_msg::common::WeatherTypeSupport>
  {
    static ::holo_base_msg::common::WeatherTypeSupport_ptr duplicate (
        ::holo_base_msg::common::WeatherTypeSupport_ptr p);
    static void release (
        ::holo_base_msg::common::WeatherTypeSupport_ptr p);
    static ::holo_base_msg::common::WeatherTypeSupport_ptr nil (void);
    static ::CORBA::Boolean marshal (
        const ::holo_base_msg::common::WeatherTypeSupport_ptr p,
        TAO_OutputCDR & cdr);
  };

#endif /* end #if !defined */

#if !defined (_HOLO_BASE_MSG_COMMON_WEATHERDATAWRITER__TRAITS_)
#define _HOLO_BASE_MSG_COMMON_WEATHERDATAWRITER__TRAITS_

  template<>
  struct  Objref_Traits< ::holo_base_msg::common::WeatherDataWriter>
  {
    static ::holo_base_msg::common::WeatherDataWriter_ptr duplicate (
        ::holo_base_msg::common::WeatherDataWriter_ptr p);
    static void release (
        ::holo_base_msg::common::WeatherDataWriter_ptr p);
    static ::holo_base_msg::common::WeatherDataWriter_ptr nil (void);
    static ::CORBA::Boolean marshal (
        const ::holo_base_msg::common::WeatherDataWriter_ptr p,
        TAO_OutputCDR & cdr);
  };

#endif /* end #if !defined */

#if !defined (_HOLO_BASE_MSG_COMMON_WEATHERDATAREADER__TRAITS_)
#define _HOLO_BASE_MSG_COMMON_WEATHERDATAREADER__TRAITS_

  template<>
  struct  Objref_Traits< ::holo_base_msg::common::WeatherDataReader>
  {
    static ::holo_base_msg::common::WeatherDataReader_ptr duplicate (
        ::holo_base_msg::common::WeatherDataReader_ptr p);
    static void release (
        ::holo_base_msg::common::WeatherDataReader_ptr p);
    static ::holo_base_msg::common::WeatherDataReader_ptr nil (void);
    static ::CORBA::Boolean marshal (
        const ::holo_base_msg::common::WeatherDataReader_ptr p,
        TAO_OutputCDR & cdr);
  };

#endif /* end #if !defined */
}
TAO_END_VERSIONED_NAMESPACE_DECL



// TAO_IDL - Generated from
// be/be_visitor_interface/any_op_ch.cpp:44



#if defined (ACE_ANY_OPS_USE_NAMESPACE)

namespace holo_base_msg
{
  
  namespace common
  {
     void operator<<= ( ::CORBA::Any &, WeatherTypeSupport_ptr); // copying
     void operator<<= ( ::CORBA::Any &, WeatherTypeSupport_ptr *); // non-copying
     ::CORBA::Boolean operator>>= (const ::CORBA::Any &, WeatherTypeSupport_ptr &);
  }
}

#else


TAO_BEGIN_VERSIONED_NAMESPACE_DECL

 void operator<<= (::CORBA::Any &, holo_base_msg::common::WeatherTypeSupport_ptr); // copying
 void operator<<= (::CORBA::Any &, holo_base_msg::common::WeatherTypeSupport_ptr *); // non-copying
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, holo_base_msg::common::WeatherTypeSupport_ptr &);
TAO_END_VERSIONED_NAMESPACE_DECL



#endif

// TAO_IDL - Generated from
// be/be_visitor_interface/any_op_ch.cpp:44



#if defined (ACE_ANY_OPS_USE_NAMESPACE)

namespace holo_base_msg
{
  
  namespace common
  {
     void operator<<= ( ::CORBA::Any &, WeatherDataWriter_ptr); // copying
     void operator<<= ( ::CORBA::Any &, WeatherDataWriter_ptr *); // non-copying
     ::CORBA::Boolean operator>>= (const ::CORBA::Any &, WeatherDataWriter_ptr &);
  }
}

#else


TAO_BEGIN_VERSIONED_NAMESPACE_DECL

 void operator<<= (::CORBA::Any &, holo_base_msg::common::WeatherDataWriter_ptr); // copying
 void operator<<= (::CORBA::Any &, holo_base_msg::common::WeatherDataWriter_ptr *); // non-copying
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, holo_base_msg::common::WeatherDataWriter_ptr &);
TAO_END_VERSIONED_NAMESPACE_DECL



#endif

// TAO_IDL - Generated from
// be/be_visitor_interface/any_op_ch.cpp:44



#if defined (ACE_ANY_OPS_USE_NAMESPACE)

namespace holo_base_msg
{
  
  namespace common
  {
     void operator<<= ( ::CORBA::Any &, WeatherDataReader_ptr); // copying
     void operator<<= ( ::CORBA::Any &, WeatherDataReader_ptr *); // non-copying
     ::CORBA::Boolean operator>>= (const ::CORBA::Any &, WeatherDataReader_ptr &);
  }
}

#else


TAO_BEGIN_VERSIONED_NAMESPACE_DECL

 void operator<<= (::CORBA::Any &, holo_base_msg::common::WeatherDataReader_ptr); // copying
 void operator<<= (::CORBA::Any &, holo_base_msg::common::WeatherDataReader_ptr *); // non-copying
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, holo_base_msg::common::WeatherDataReader_ptr &);
TAO_END_VERSIONED_NAMESPACE_DECL



#endif

// TAO_IDL - Generated from
// be/be_codegen.cpp:1703
#if defined (__ACE_INLINE__)
#include "WeatherTypeSupportC.inl"
#endif /* defined INLINE */

#include /**/ "ace/post.h"

#endif /* ifndef */
