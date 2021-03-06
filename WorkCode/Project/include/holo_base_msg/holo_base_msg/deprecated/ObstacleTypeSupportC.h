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

#ifndef _TAO_IDL__HOME_HOLO_WORKSPACE_BUILD_TDA4_UBUNTU_18_04_DEBUG_HOLO_BASE_MSG_INCLUDE_HOLO_BASE_MSG_DEPRECATED_OBSTACLETYPESUPPORTC_WZLIBS_H_
#define _TAO_IDL__HOME_HOLO_WORKSPACE_BUILD_TDA4_UBUNTU_18_04_DEBUG_HOLO_BASE_MSG_INCLUDE_HOLO_BASE_MSG_DEPRECATED_OBSTACLETYPESUPPORTC_WZLIBS_H_

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

#include "ObstacleC.h"
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

  namespace deprecated
  {

    // TAO_IDL - Generated from
    // be/be_visitor_module/module_ch.cpp:38

    namespace obstacle
    {

      // TAO_IDL - Generated from
      // be/be_visitor_sequence/sequence_ch.cpp:102

      typedef ::TAO::DCPS::ZeroCopyDataSeq< holo_base_msg::deprecated::obstacle::ObstacleGeneralList, DCPS_ZERO_COPY_SEQ_DEFAULT_SIZE> ObstacleGeneralListSeq;
      

      // TAO_IDL - Generated from
      // be/be_visitor_typecode/typecode_decl.cpp:37

      extern  ::CORBA::TypeCode_ptr const _tc_ObstacleGeneralListSeq;

      // TAO_IDL - Generated from
      // be/be_interface.cpp:751

#if !defined (_HOLO_BASE_MSG_DEPRECATED_OBSTACLE_OBSTACLEGENERALLISTTYPESUPPORT__VAR_OUT_CH_)
#define _HOLO_BASE_MSG_DEPRECATED_OBSTACLE_OBSTACLEGENERALLISTTYPESUPPORT__VAR_OUT_CH_

      class ObstacleGeneralListTypeSupport;
      typedef ObstacleGeneralListTypeSupport *ObstacleGeneralListTypeSupport_ptr;

      typedef
        TAO_Objref_Var_T<
            ObstacleGeneralListTypeSupport
          >
        ObstacleGeneralListTypeSupport_var;
      
      typedef
        TAO_Objref_Out_T<
            ObstacleGeneralListTypeSupport
          >
        ObstacleGeneralListTypeSupport_out;

#endif /* end #if !defined */

      // TAO_IDL - Generated from
      // be/be_visitor_interface/interface_ch.cpp:43

      class  ObstacleGeneralListTypeSupport
        : public virtual ::OpenDDS::DCPS::TypeSupport
      
      {
      public:

        // TAO_IDL - Generated from
        // be/be_type.cpp:307

        typedef ObstacleGeneralListTypeSupport_ptr _ptr_type;
        typedef ObstacleGeneralListTypeSupport_var _var_type;
        typedef ObstacleGeneralListTypeSupport_out _out_type;

        static void _tao_any_destructor (void *);

        // The static operations.
        static ObstacleGeneralListTypeSupport_ptr _duplicate (ObstacleGeneralListTypeSupport_ptr obj);

        static void _tao_release (ObstacleGeneralListTypeSupport_ptr obj);

        static ObstacleGeneralListTypeSupport_ptr _narrow (::CORBA::Object_ptr obj);
        static ObstacleGeneralListTypeSupport_ptr _unchecked_narrow (::CORBA::Object_ptr obj);
        static ObstacleGeneralListTypeSupport_ptr _nil (void);

        // TAO_IDL - Generated from
        // be/be_visitor_interface/interface_ch.cpp:140

        virtual ::CORBA::Boolean _is_a (const char *type_id);
        virtual const char* _interface_repository_id (void) const;
        virtual ::CORBA::Boolean marshal (TAO_OutputCDR &cdr);
      
      protected:
        // Abstract or local interface only.
        ObstacleGeneralListTypeSupport (void);

        

        virtual ~ObstacleGeneralListTypeSupport (void);
      
      private:
        // Private and unimplemented for concrete interfaces.
        ACE_UNIMPLEMENTED_FUNC (ObstacleGeneralListTypeSupport (const ObstacleGeneralListTypeSupport &))
#if defined (ACE_HAS_CPP11)
        ACE_UNIMPLEMENTED_FUNC (ObstacleGeneralListTypeSupport (ObstacleGeneralListTypeSupport &&))
#endif /* ACE_HAS_CPP11 */
        ACE_UNIMPLEMENTED_FUNC (ObstacleGeneralListTypeSupport &operator= (const ObstacleGeneralListTypeSupport &))
#if defined (ACE_HAS_CPP11)
        ACE_UNIMPLEMENTED_FUNC (ObstacleGeneralListTypeSupport &operator= (ObstacleGeneralListTypeSupport &&))
#endif /* ACE_HAS_CPP11 */
      };

      // TAO_IDL - Generated from
      // be/be_visitor_typecode/typecode_decl.cpp:37

      extern  ::CORBA::TypeCode_ptr const _tc_ObstacleGeneralListTypeSupport;

      // TAO_IDL - Generated from
      // be/be_interface.cpp:751

#if !defined (_HOLO_BASE_MSG_DEPRECATED_OBSTACLE_OBSTACLEGENERALLISTDATAWRITER__VAR_OUT_CH_)
#define _HOLO_BASE_MSG_DEPRECATED_OBSTACLE_OBSTACLEGENERALLISTDATAWRITER__VAR_OUT_CH_

      class ObstacleGeneralListDataWriter;
      typedef ObstacleGeneralListDataWriter *ObstacleGeneralListDataWriter_ptr;

      typedef
        TAO_Objref_Var_T<
            ObstacleGeneralListDataWriter
          >
        ObstacleGeneralListDataWriter_var;
      
      typedef
        TAO_Objref_Out_T<
            ObstacleGeneralListDataWriter
          >
        ObstacleGeneralListDataWriter_out;

#endif /* end #if !defined */

      // TAO_IDL - Generated from
      // be/be_visitor_interface/interface_ch.cpp:43

      class  ObstacleGeneralListDataWriter
        : public virtual ::DDS::DataWriter
      
      {
      public:

        // TAO_IDL - Generated from
        // be/be_type.cpp:307

        typedef ObstacleGeneralListDataWriter_ptr _ptr_type;
        typedef ObstacleGeneralListDataWriter_var _var_type;
        typedef ObstacleGeneralListDataWriter_out _out_type;

        static void _tao_any_destructor (void *);

        // The static operations.
        static ObstacleGeneralListDataWriter_ptr _duplicate (ObstacleGeneralListDataWriter_ptr obj);

        static void _tao_release (ObstacleGeneralListDataWriter_ptr obj);

        static ObstacleGeneralListDataWriter_ptr _narrow (::CORBA::Object_ptr obj);
        static ObstacleGeneralListDataWriter_ptr _unchecked_narrow (::CORBA::Object_ptr obj);
        static ObstacleGeneralListDataWriter_ptr _nil (void);

        virtual ::DDS::InstanceHandle_t register_instance (
          const ::holo_base_msg::deprecated::obstacle::ObstacleGeneralList & instance) = 0;

        virtual ::DDS::InstanceHandle_t register_instance_w_timestamp (
          const ::holo_base_msg::deprecated::obstacle::ObstacleGeneralList & instance,
          const ::DDS::Time_t & timestamp) = 0;

        virtual ::DDS::ReturnCode_t unregister_instance (
          const ::holo_base_msg::deprecated::obstacle::ObstacleGeneralList & instance,
          ::DDS::InstanceHandle_t handle) = 0;

        virtual ::DDS::ReturnCode_t unregister_instance_w_timestamp (
          const ::holo_base_msg::deprecated::obstacle::ObstacleGeneralList & instance,
          ::DDS::InstanceHandle_t handle,
          const ::DDS::Time_t & timestamp) = 0;

        virtual ::DDS::ReturnCode_t write (
          const ::holo_base_msg::deprecated::obstacle::ObstacleGeneralList & instance_data,
          ::DDS::InstanceHandle_t handle) = 0;

        virtual ::DDS::ReturnCode_t write_w_timestamp (
          const ::holo_base_msg::deprecated::obstacle::ObstacleGeneralList & instance_data,
          ::DDS::InstanceHandle_t handle,
          const ::DDS::Time_t & source_timestamp) = 0;

        virtual ::DDS::ReturnCode_t dispose (
          const ::holo_base_msg::deprecated::obstacle::ObstacleGeneralList & instance_data,
          ::DDS::InstanceHandle_t instance_handle) = 0;

        virtual ::DDS::ReturnCode_t dispose_w_timestamp (
          const ::holo_base_msg::deprecated::obstacle::ObstacleGeneralList & instance_data,
          ::DDS::InstanceHandle_t instance_handle,
          const ::DDS::Time_t & source_timestamp) = 0;

        virtual ::DDS::ReturnCode_t get_key_value (
          ::holo_base_msg::deprecated::obstacle::ObstacleGeneralList & key_holder,
          ::DDS::InstanceHandle_t handle) = 0;

        virtual ::DDS::InstanceHandle_t lookup_instance (
          const ::holo_base_msg::deprecated::obstacle::ObstacleGeneralList & instance_data) = 0;

        // TAO_IDL - Generated from
        // be/be_visitor_interface/interface_ch.cpp:140

        virtual ::CORBA::Boolean _is_a (const char *type_id);
        virtual const char* _interface_repository_id (void) const;
        virtual ::CORBA::Boolean marshal (TAO_OutputCDR &cdr);
      
      protected:
        // Abstract or local interface only.
        ObstacleGeneralListDataWriter (void);

        

        virtual ~ObstacleGeneralListDataWriter (void);
      
      private:
        // Private and unimplemented for concrete interfaces.
        ACE_UNIMPLEMENTED_FUNC (ObstacleGeneralListDataWriter (const ObstacleGeneralListDataWriter &))
#if defined (ACE_HAS_CPP11)
        ACE_UNIMPLEMENTED_FUNC (ObstacleGeneralListDataWriter (ObstacleGeneralListDataWriter &&))
#endif /* ACE_HAS_CPP11 */
        ACE_UNIMPLEMENTED_FUNC (ObstacleGeneralListDataWriter &operator= (const ObstacleGeneralListDataWriter &))
#if defined (ACE_HAS_CPP11)
        ACE_UNIMPLEMENTED_FUNC (ObstacleGeneralListDataWriter &operator= (ObstacleGeneralListDataWriter &&))
#endif /* ACE_HAS_CPP11 */
      };

      // TAO_IDL - Generated from
      // be/be_visitor_typecode/typecode_decl.cpp:37

      extern  ::CORBA::TypeCode_ptr const _tc_ObstacleGeneralListDataWriter;

      // TAO_IDL - Generated from
      // be/be_interface.cpp:751

#if !defined (_HOLO_BASE_MSG_DEPRECATED_OBSTACLE_OBSTACLEGENERALLISTDATAREADER__VAR_OUT_CH_)
#define _HOLO_BASE_MSG_DEPRECATED_OBSTACLE_OBSTACLEGENERALLISTDATAREADER__VAR_OUT_CH_

      class ObstacleGeneralListDataReader;
      typedef ObstacleGeneralListDataReader *ObstacleGeneralListDataReader_ptr;

      typedef
        TAO_Objref_Var_T<
            ObstacleGeneralListDataReader
          >
        ObstacleGeneralListDataReader_var;
      
      typedef
        TAO_Objref_Out_T<
            ObstacleGeneralListDataReader
          >
        ObstacleGeneralListDataReader_out;

#endif /* end #if !defined */

      // TAO_IDL - Generated from
      // be/be_visitor_interface/interface_ch.cpp:43

      class  ObstacleGeneralListDataReader
        : public virtual ::OpenDDS::DCPS::DataReaderEx
      
      {
      public:

        // TAO_IDL - Generated from
        // be/be_type.cpp:307

        typedef ObstacleGeneralListDataReader_ptr _ptr_type;
        typedef ObstacleGeneralListDataReader_var _var_type;
        typedef ObstacleGeneralListDataReader_out _out_type;

        static void _tao_any_destructor (void *);

        // The static operations.
        static ObstacleGeneralListDataReader_ptr _duplicate (ObstacleGeneralListDataReader_ptr obj);

        static void _tao_release (ObstacleGeneralListDataReader_ptr obj);

        static ObstacleGeneralListDataReader_ptr _narrow (::CORBA::Object_ptr obj);
        static ObstacleGeneralListDataReader_ptr _unchecked_narrow (::CORBA::Object_ptr obj);
        static ObstacleGeneralListDataReader_ptr _nil (void);

        virtual ::DDS::ReturnCode_t read (
          ::holo_base_msg::deprecated::obstacle::ObstacleGeneralListSeq & received_data,
          ::DDS::SampleInfoSeq & info_seq,
          ::CORBA::Long max_samples,
          ::DDS::SampleStateMask sample_states,
          ::DDS::ViewStateMask view_states,
          ::DDS::InstanceStateMask instance_states) = 0;

        virtual ::DDS::ReturnCode_t take (
          ::holo_base_msg::deprecated::obstacle::ObstacleGeneralListSeq & received_data,
          ::DDS::SampleInfoSeq & info_seq,
          ::CORBA::Long max_samples,
          ::DDS::SampleStateMask sample_states,
          ::DDS::ViewStateMask view_states,
          ::DDS::InstanceStateMask instance_states) = 0;

        virtual ::DDS::ReturnCode_t read_w_condition (
          ::holo_base_msg::deprecated::obstacle::ObstacleGeneralListSeq & data_values,
          ::DDS::SampleInfoSeq & sample_infos,
          ::CORBA::Long max_samples,
          ::DDS::ReadCondition_ptr a_condition) = 0;

        virtual ::DDS::ReturnCode_t take_w_condition (
          ::holo_base_msg::deprecated::obstacle::ObstacleGeneralListSeq & data_values,
          ::DDS::SampleInfoSeq & sample_infos,
          ::CORBA::Long max_samples,
          ::DDS::ReadCondition_ptr a_condition) = 0;

        virtual ::DDS::ReturnCode_t read_next_sample (
          ::holo_base_msg::deprecated::obstacle::ObstacleGeneralList & received_data,
          ::DDS::SampleInfo & sample_info) = 0;

        virtual ::DDS::ReturnCode_t take_next_sample (
          ::holo_base_msg::deprecated::obstacle::ObstacleGeneralList & received_data,
          ::DDS::SampleInfo & sample_info) = 0;

        virtual ::DDS::ReturnCode_t read_instance (
          ::holo_base_msg::deprecated::obstacle::ObstacleGeneralListSeq & received_data,
          ::DDS::SampleInfoSeq & info_seq,
          ::CORBA::Long max_samples,
          ::DDS::InstanceHandle_t a_handle,
          ::DDS::SampleStateMask sample_states,
          ::DDS::ViewStateMask view_states,
          ::DDS::InstanceStateMask instance_states) = 0;

        virtual ::DDS::ReturnCode_t take_instance (
          ::holo_base_msg::deprecated::obstacle::ObstacleGeneralListSeq & received_data,
          ::DDS::SampleInfoSeq & info_seq,
          ::CORBA::Long max_samples,
          ::DDS::InstanceHandle_t a_handle,
          ::DDS::SampleStateMask sample_states,
          ::DDS::ViewStateMask view_states,
          ::DDS::InstanceStateMask instance_states) = 0;

        virtual ::DDS::ReturnCode_t read_instance_w_condition (
          ::holo_base_msg::deprecated::obstacle::ObstacleGeneralListSeq & received_data,
          ::DDS::SampleInfoSeq & sample_infos,
          ::CORBA::Long max_samples,
          ::DDS::InstanceHandle_t a_handle,
          ::DDS::ReadCondition_ptr a_condition) = 0;

        virtual ::DDS::ReturnCode_t take_instance_w_condition (
          ::holo_base_msg::deprecated::obstacle::ObstacleGeneralListSeq & received_data,
          ::DDS::SampleInfoSeq & sample_infos,
          ::CORBA::Long max_samples,
          ::DDS::InstanceHandle_t a_handle,
          ::DDS::ReadCondition_ptr a_condition) = 0;

        virtual ::DDS::ReturnCode_t read_next_instance (
          ::holo_base_msg::deprecated::obstacle::ObstacleGeneralListSeq & received_data,
          ::DDS::SampleInfoSeq & info_seq,
          ::CORBA::Long max_samples,
          ::DDS::InstanceHandle_t a_handle,
          ::DDS::SampleStateMask sample_states,
          ::DDS::ViewStateMask view_states,
          ::DDS::InstanceStateMask instance_states) = 0;

        virtual ::DDS::ReturnCode_t take_next_instance (
          ::holo_base_msg::deprecated::obstacle::ObstacleGeneralListSeq & received_data,
          ::DDS::SampleInfoSeq & info_seq,
          ::CORBA::Long max_samples,
          ::DDS::InstanceHandle_t a_handle,
          ::DDS::SampleStateMask sample_states,
          ::DDS::ViewStateMask view_states,
          ::DDS::InstanceStateMask instance_states) = 0;

        virtual ::DDS::ReturnCode_t read_next_instance_w_condition (
          ::holo_base_msg::deprecated::obstacle::ObstacleGeneralListSeq & data_values,
          ::DDS::SampleInfoSeq & sample_infos,
          ::CORBA::Long max_samples,
          ::DDS::InstanceHandle_t previous_handle,
          ::DDS::ReadCondition_ptr a_condition) = 0;

        virtual ::DDS::ReturnCode_t take_next_instance_w_condition (
          ::holo_base_msg::deprecated::obstacle::ObstacleGeneralListSeq & data_values,
          ::DDS::SampleInfoSeq & sample_infos,
          ::CORBA::Long max_samples,
          ::DDS::InstanceHandle_t previous_handle,
          ::DDS::ReadCondition_ptr a_condition) = 0;

        virtual ::DDS::ReturnCode_t return_loan (
          ::holo_base_msg::deprecated::obstacle::ObstacleGeneralListSeq & received_data,
          ::DDS::SampleInfoSeq & info_seq) = 0;

        virtual ::DDS::ReturnCode_t get_key_value (
          ::holo_base_msg::deprecated::obstacle::ObstacleGeneralList & key_holder,
          ::DDS::InstanceHandle_t handle) = 0;

        virtual ::DDS::InstanceHandle_t lookup_instance (
          const ::holo_base_msg::deprecated::obstacle::ObstacleGeneralList & instance_data) = 0;

        // TAO_IDL - Generated from
        // be/be_visitor_interface/interface_ch.cpp:140

        virtual ::CORBA::Boolean _is_a (const char *type_id);
        virtual const char* _interface_repository_id (void) const;
        virtual ::CORBA::Boolean marshal (TAO_OutputCDR &cdr);
      
      protected:
        // Abstract or local interface only.
        ObstacleGeneralListDataReader (void);

        

        virtual ~ObstacleGeneralListDataReader (void);
      
      private:
        // Private and unimplemented for concrete interfaces.
        ACE_UNIMPLEMENTED_FUNC (ObstacleGeneralListDataReader (const ObstacleGeneralListDataReader &))
#if defined (ACE_HAS_CPP11)
        ACE_UNIMPLEMENTED_FUNC (ObstacleGeneralListDataReader (ObstacleGeneralListDataReader &&))
#endif /* ACE_HAS_CPP11 */
        ACE_UNIMPLEMENTED_FUNC (ObstacleGeneralListDataReader &operator= (const ObstacleGeneralListDataReader &))
#if defined (ACE_HAS_CPP11)
        ACE_UNIMPLEMENTED_FUNC (ObstacleGeneralListDataReader &operator= (ObstacleGeneralListDataReader &&))
#endif /* ACE_HAS_CPP11 */
      };

      // TAO_IDL - Generated from
      // be/be_visitor_typecode/typecode_decl.cpp:37

      extern  ::CORBA::TypeCode_ptr const _tc_ObstacleGeneralListDataReader;
    
    // TAO_IDL - Generated from
    // be/be_visitor_module/module_ch.cpp:67
    
    } // module holo_base_msg::deprecated::obstacle
  
  // TAO_IDL - Generated from
  // be/be_visitor_module/module_ch.cpp:67
  
  } // module holo_base_msg::deprecated

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

#if !defined (_HOLO_BASE_MSG_DEPRECATED_OBSTACLE_OBSTACLEGENERALLISTTYPESUPPORT__TRAITS_)
#define _HOLO_BASE_MSG_DEPRECATED_OBSTACLE_OBSTACLEGENERALLISTTYPESUPPORT__TRAITS_

  template<>
  struct  Objref_Traits< ::holo_base_msg::deprecated::obstacle::ObstacleGeneralListTypeSupport>
  {
    static ::holo_base_msg::deprecated::obstacle::ObstacleGeneralListTypeSupport_ptr duplicate (
        ::holo_base_msg::deprecated::obstacle::ObstacleGeneralListTypeSupport_ptr p);
    static void release (
        ::holo_base_msg::deprecated::obstacle::ObstacleGeneralListTypeSupport_ptr p);
    static ::holo_base_msg::deprecated::obstacle::ObstacleGeneralListTypeSupport_ptr nil (void);
    static ::CORBA::Boolean marshal (
        const ::holo_base_msg::deprecated::obstacle::ObstacleGeneralListTypeSupport_ptr p,
        TAO_OutputCDR & cdr);
  };

#endif /* end #if !defined */

#if !defined (_HOLO_BASE_MSG_DEPRECATED_OBSTACLE_OBSTACLEGENERALLISTDATAWRITER__TRAITS_)
#define _HOLO_BASE_MSG_DEPRECATED_OBSTACLE_OBSTACLEGENERALLISTDATAWRITER__TRAITS_

  template<>
  struct  Objref_Traits< ::holo_base_msg::deprecated::obstacle::ObstacleGeneralListDataWriter>
  {
    static ::holo_base_msg::deprecated::obstacle::ObstacleGeneralListDataWriter_ptr duplicate (
        ::holo_base_msg::deprecated::obstacle::ObstacleGeneralListDataWriter_ptr p);
    static void release (
        ::holo_base_msg::deprecated::obstacle::ObstacleGeneralListDataWriter_ptr p);
    static ::holo_base_msg::deprecated::obstacle::ObstacleGeneralListDataWriter_ptr nil (void);
    static ::CORBA::Boolean marshal (
        const ::holo_base_msg::deprecated::obstacle::ObstacleGeneralListDataWriter_ptr p,
        TAO_OutputCDR & cdr);
  };

#endif /* end #if !defined */

#if !defined (_HOLO_BASE_MSG_DEPRECATED_OBSTACLE_OBSTACLEGENERALLISTDATAREADER__TRAITS_)
#define _HOLO_BASE_MSG_DEPRECATED_OBSTACLE_OBSTACLEGENERALLISTDATAREADER__TRAITS_

  template<>
  struct  Objref_Traits< ::holo_base_msg::deprecated::obstacle::ObstacleGeneralListDataReader>
  {
    static ::holo_base_msg::deprecated::obstacle::ObstacleGeneralListDataReader_ptr duplicate (
        ::holo_base_msg::deprecated::obstacle::ObstacleGeneralListDataReader_ptr p);
    static void release (
        ::holo_base_msg::deprecated::obstacle::ObstacleGeneralListDataReader_ptr p);
    static ::holo_base_msg::deprecated::obstacle::ObstacleGeneralListDataReader_ptr nil (void);
    static ::CORBA::Boolean marshal (
        const ::holo_base_msg::deprecated::obstacle::ObstacleGeneralListDataReader_ptr p,
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
  
  namespace deprecated
  {
    
    namespace obstacle
    {
       void operator<<= ( ::CORBA::Any &, ObstacleGeneralListTypeSupport_ptr); // copying
       void operator<<= ( ::CORBA::Any &, ObstacleGeneralListTypeSupport_ptr *); // non-copying
       ::CORBA::Boolean operator>>= (const ::CORBA::Any &, ObstacleGeneralListTypeSupport_ptr &);
    }
  }
}

#else


TAO_BEGIN_VERSIONED_NAMESPACE_DECL

 void operator<<= (::CORBA::Any &, holo_base_msg::deprecated::obstacle::ObstacleGeneralListTypeSupport_ptr); // copying
 void operator<<= (::CORBA::Any &, holo_base_msg::deprecated::obstacle::ObstacleGeneralListTypeSupport_ptr *); // non-copying
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, holo_base_msg::deprecated::obstacle::ObstacleGeneralListTypeSupport_ptr &);
TAO_END_VERSIONED_NAMESPACE_DECL



#endif

// TAO_IDL - Generated from
// be/be_visitor_interface/any_op_ch.cpp:44



#if defined (ACE_ANY_OPS_USE_NAMESPACE)

namespace holo_base_msg
{
  
  namespace deprecated
  {
    
    namespace obstacle
    {
       void operator<<= ( ::CORBA::Any &, ObstacleGeneralListDataWriter_ptr); // copying
       void operator<<= ( ::CORBA::Any &, ObstacleGeneralListDataWriter_ptr *); // non-copying
       ::CORBA::Boolean operator>>= (const ::CORBA::Any &, ObstacleGeneralListDataWriter_ptr &);
    }
  }
}

#else


TAO_BEGIN_VERSIONED_NAMESPACE_DECL

 void operator<<= (::CORBA::Any &, holo_base_msg::deprecated::obstacle::ObstacleGeneralListDataWriter_ptr); // copying
 void operator<<= (::CORBA::Any &, holo_base_msg::deprecated::obstacle::ObstacleGeneralListDataWriter_ptr *); // non-copying
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, holo_base_msg::deprecated::obstacle::ObstacleGeneralListDataWriter_ptr &);
TAO_END_VERSIONED_NAMESPACE_DECL



#endif

// TAO_IDL - Generated from
// be/be_visitor_interface/any_op_ch.cpp:44



#if defined (ACE_ANY_OPS_USE_NAMESPACE)

namespace holo_base_msg
{
  
  namespace deprecated
  {
    
    namespace obstacle
    {
       void operator<<= ( ::CORBA::Any &, ObstacleGeneralListDataReader_ptr); // copying
       void operator<<= ( ::CORBA::Any &, ObstacleGeneralListDataReader_ptr *); // non-copying
       ::CORBA::Boolean operator>>= (const ::CORBA::Any &, ObstacleGeneralListDataReader_ptr &);
    }
  }
}

#else


TAO_BEGIN_VERSIONED_NAMESPACE_DECL

 void operator<<= (::CORBA::Any &, holo_base_msg::deprecated::obstacle::ObstacleGeneralListDataReader_ptr); // copying
 void operator<<= (::CORBA::Any &, holo_base_msg::deprecated::obstacle::ObstacleGeneralListDataReader_ptr *); // non-copying
 ::CORBA::Boolean operator>>= (const ::CORBA::Any &, holo_base_msg::deprecated::obstacle::ObstacleGeneralListDataReader_ptr &);
TAO_END_VERSIONED_NAMESPACE_DECL



#endif

// TAO_IDL - Generated from
// be/be_codegen.cpp:1703
#if defined (__ACE_INLINE__)
#include "ObstacleTypeSupportC.inl"
#endif /* defined INLINE */

#include /**/ "ace/post.h"

#endif /* ifndef */

