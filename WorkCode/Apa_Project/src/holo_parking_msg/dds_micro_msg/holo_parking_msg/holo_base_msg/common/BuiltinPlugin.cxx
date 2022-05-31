/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Builtin.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "Builtin.h"
#include "reda/reda_bufferpool.h"
#include "xcdr/xcdr_interpreter.h"
#include "dds_c/dds_c_xcdr_type_plugin.h"
#include "BuiltinPlugin.h"
#include "BuiltinSupport.h"

/*** SOURCE_BEGIN ***/
#ifndef UNUSED_ARG
#define UNUSED_ARG(x) (void)(x)
#endif

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------
Typed-endpoint support for C++:
* -------------------------------------------------------------------------- */

void* 
opendds_wrapper_BuiltinTimestampPlugin_create_typed_datawriter(void *writer)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * so writer is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataWriter *cpp_writer = 
    new opendds_wrapper_BuiltinTimestampDataWriter((DDS_DataWriter*)writer);

    return cpp_writer;   
}

#ifndef RTI_CERT
void 
opendds_wrapper_BuiltinTimestampPlugin_delete_typed_datawriter(void *wrapper)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * and DDS_Publisher_delete_datawriter so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataWriter_impl *cpp_writer = (DDSDataWriter_impl *) wrapper;

    opendds_wrapper_BuiltinTimestampDataWriter *t_writer = 
    static_cast<opendds_wrapper_BuiltinTimestampDataWriter *>(cpp_writer);

    delete t_writer;
}
#endif

void* 
opendds_wrapper_BuiltinTimestampPlugin_create_typed_datareader(void *reader)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * so reader is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataReader *cpp_reader = 
    new opendds_wrapper_BuiltinTimestampDataReader((DDS_DataReader*)reader);

    return cpp_reader;      
}

#ifndef RTI_CERT
void
opendds_wrapper_BuiltinTimestampPlugin_delete_typed_datareader(void *wrapper)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * and DDS_Subscriber_delete_datareader so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataReader_impl *cpp_reader = (DDSDataReader_impl *) wrapper;

    opendds_wrapper_BuiltinTimestampDataReader *t_reader = 
    static_cast<opendds_wrapper_BuiltinTimestampDataReader *>(cpp_reader);

    delete t_reader;
}
#endif

/* --------------------------------------------------------------------------
*  Sample Support functions:
* -------------------------------------------------------------------------- */
RTI_BOOL
opendds_wrapper_BuiltinTimestampPlugin_create_sample(struct DDS_TypePlugin *plugin,
void **sample)
{
    UNUSED_ARG(plugin);

    *sample = (void *) opendds_wrapper_BuiltinTimestamp_create();
    return (*sample != NULL);
}

#ifndef RTI_CERT
RTI_BOOL
opendds_wrapper_BuiltinTimestampPlugin_delete_sample(struct DDS_TypePlugin *plugin, 
void *sample)
{
    UNUSED_ARG(plugin);

    opendds_wrapper_BuiltinTimestamp_delete((opendds_wrapper_BuiltinTimestamp *) sample);
    return RTI_TRUE;
}
#endif

RTI_BOOL 
opendds_wrapper_BuiltinTimestampPlugin_copy_sample(struct DDS_TypePlugin *plugin, 
void *dst, 
const void *src)
{
    UNUSED_ARG(plugin);

    return opendds_wrapper_BuiltinTimestamp_copy(
        (opendds_wrapper_BuiltinTimestamp*)dst,
        (const opendds_wrapper_BuiltinTimestamp*)src);
}
/* --------------------------------------------------------------------------
*  Type opendds_wrapper_BuiltinTimestamp Plugin Instantiation
* -------------------------------------------------------------------------- */

NDDSCDREncapsulation opendds_wrapper_BuiltinTimestampEncapsulationKind[] =
{ 
    {
        DDS_ENCAPSULATION_ID_CDR_LE,
        DDS_ENCAPSULATION_ID_CDR_BE,
        0
    }
};

NDDSCDREncapsulation opendds_wrapper_BuiltinTimestampV2EncapsulationKind[] =
{ 
    {

        DDS_ENCAPSULATION_ID_XCDR2_A_LE,
        DDS_ENCAPSULATION_ID_XCDR2_A_BE,
        0

    }
};

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinTimestampTypePlugin_initialize_sample(struct DDS_TypePlugin *plugin, void *buffer)
{
    UNUSED_ARG(plugin);
    return opendds_wrapper_BuiltinTimestamp_initialize((opendds_wrapper_BuiltinTimestamp*)buffer);
}

RTI_PRIVATE RTI_UINT32 
opendds_wrapper_BuiltinTimestamp_get_user_sample_size(
    struct DDS_TypePlugin *tp)
{
    UNUSED_ARG(tp);        
    return sizeof(opendds_wrapper_BuiltinTimestamp);
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinTimestamp_cdr_initialize(void *init_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)init_config;
    void *sample;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!opendds_wrapper_BuiltinTimestampPlugin_create_sample(&plugin->_parent,&sample))
    {
        return RTI_FALSE;
    }

    sh->sample = sample;

    return RTI_TRUE;
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinTimestamp_cdr_finalize(void *finalize_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)finalize_config;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!opendds_wrapper_BuiltinTimestampPlugin_delete_sample(&plugin->_parent,sh->sample))
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

RTI_PRIVATE void 
opendds_wrapper_BuiltinTimestampTypePlugin_return_sample(
    struct DDS_TypePlugin *tp,
    struct DDS_TypePluginSampleHolder *sample)
{
    opendds_wrapper_BuiltinTimestamp_finalize_optional_members((opendds_wrapper_BuiltinTimestamp*)sample->sample, RTI_FALSE);
    XCDR_GenericStreamPlugin_return_sample(tp, sample);
}

RTI_PRIVATE struct DDS_TypeMemoryPlugin*
opendds_wrapper_BuiltinTimestampXTypesHeapPlugin_create(struct DDS_TypePlugin *tp,
DDS_DomainParticipant *participant,
struct DDS_DomainParticipantQos *dp_qos,
DDS_TypePluginMode_T endpoint_mode,
DDS_TypePluginEndpoint *endpoint,
DDS_TypePluginEndpointQos *qos)
{
    return DDS_XTypesHeapPlugin_create(
        tp,
        participant,
        dp_qos,
        endpoint_mode,
        endpoint,
        qos,
        NULL,
        NULL,
        opendds_wrapper_BuiltinTimestamp_cdr_initialize,
        opendds_wrapper_BuiltinTimestamp_cdr_finalize,
        sizeof(opendds_wrapper_BuiltinTimestamp),
        RTI_FALSE
        );
}

RTI_PRIVATE struct DDS_TypeMemoryI opendds_wrapper_BuiltinTimestamp_fv_XTypesHeapPluginI =
{
    RTI_MEMORY_MANAGER_HEAP,
    RTI_MEMORY_TYPE_HEAP,
    opendds_wrapper_BuiltinTimestampPlugin_create_sample,
    #ifndef RTI_CERT
    opendds_wrapper_BuiltinTimestampPlugin_delete_sample,
    #else
    NULL,
    #endif
    NULL, /* get_address */
    NULL, /* return_address */
    NULL,
    DDS_XTypesHeapPlugin_get_sample_state,
    DDS_XTypesHeapPlugin_set_sample_state,
    DDS_XTypesHeapPlugin_is_owner,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    opendds_wrapper_BuiltinTimestampXTypesHeapPlugin_create,
    DDS_XTypesHeapPlugin_delete
};	

RTI_PRIVATE DDS_Boolean 
opendds_wrapper_BuiltinTimestamp_on_type_registered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    struct RTIXCdrInterpreterProgramsGenProperty programProperty =
    RTIXCdrInterpreterProgramsGenProperty_INITIALIZER;

    programProperty.resolveAlias = RTI_XCDR_TRUE;
    programProperty.inlineStruct = RTI_XCDR_TRUE;
    programProperty.optimizeEnum = RTI_XCDR_TRUE;

    programs = RTIXCdrInterpreterPrograms_new(
        (RTIXCdrTypeCode *)opendds_wrapper_BuiltinTimestamp_get_typecode(),
        &programProperty,
        RTI_XCDR_PROGRAM_MASK_TYPEPLUGIN
        );

    if (programs == NULL)
    {
        return DDS_BOOLEAN_FALSE;
    }

    DDS_TypeImpl_set_programs(type_impl, programs);
    DDS_TypeImpl_set_typecode(type_impl,  opendds_wrapper_BuiltinTimestamp_get_typecode());

    return DDS_BOOLEAN_TRUE;
}
RTI_PRIVATE DDS_Boolean 
opendds_wrapper_BuiltinTimestamp_on_type_unregistered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    programs = DDS_TypeImpl_get_programs(type_impl);

    if (programs != NULL) 
    {
        RTIXCdrInterpreterPrograms_delete(programs);
    }
    DDS_TypeImpl_set_programs(type_impl, NULL); 

    return DDS_BOOLEAN_TRUE;   
}

RTI_PRIVATE 
struct DDS_TypeEncapsulationI opendds_wrapper_BuiltinTimestamp_fv_XCDRv1PluginI =
{
    DDS_XCDR_DATA_REPRESENTATION,
    NULL,
    opendds_wrapper_BuiltinTimestampEncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,
    opendds_wrapper_BuiltinTimestampTypePlugin_return_sample,
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv1_StreamPlugin_get_serialized_sample_size,
    XCDRv1_StreamPlugin_create,
    XCDRv1_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI opendds_wrapper_BuiltinTimestamp_fv_XCDRv2PluginI =
{
    DDS_XCDR2_DATA_REPRESENTATION,
    NULL,
    opendds_wrapper_BuiltinTimestampV2EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,

    opendds_wrapper_BuiltinTimestampTypePlugin_return_sample,   
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv2_StreamPlugin_get_serialized_sample_size,
    XCDRv2_StreamPlugin_create,
    XCDRv2_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI *opendds_wrapper_BuiltinTimestamp_fv_WirePlugins[] =
{
    &opendds_wrapper_BuiltinTimestamp_fv_XCDRv2PluginI,
    &opendds_wrapper_BuiltinTimestamp_fv_XCDRv1PluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypeMemoryI *opendds_wrapper_BuiltinTimestamp_fv_MemoryPlugins[] =
{
    &opendds_wrapper_BuiltinTimestamp_fv_XTypesHeapPluginI,

    NULL
};

RTI_PRIVATE struct DDS_TypePlugin*
opendds_wrapper_BuiltinTimestampTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property);
RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinTimestampTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin);

RTI_PRIVATE struct DDS_TypePluginI opendds_wrapper_BuiltinTimestamp_fv_TypePluginI =
{
    /**************************************************************************
    *                   Type information functions
    **************************************************************************/

    NULL,                       /* DDS_TypeCode_t* */
    NDDS_TYPEPLUGIN_NO_KEY,     /* NDDS_TypePluginKeyKind */

    NDDS_TYPEPLUGIN_EH_LOCATION_PAYLOAD,
    opendds_wrapper_BuiltinTimestamp_get_user_sample_size,   
    RTI_MEMORY_TYPE_HEAP,
    NULL,
    opendds_wrapper_BuiltinTimestampPlugin_copy_sample,

    opendds_wrapper_BuiltinTimestampTypePlugin_initialize_sample,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    opendds_wrapper_BuiltinTimestamp_fv_MemoryPlugins,
    opendds_wrapper_BuiltinTimestamp_fv_WirePlugins,

    /**************************************************************************
    *       Helper APIs to create language binding wrapper Functions
    **************************************************************************/

    opendds_wrapper_BuiltinTimestampPlugin_create_typed_datawriter,
    #ifndef RTI_CERT
    opendds_wrapper_BuiltinTimestampPlugin_delete_typed_datawriter,
    #else
    NULL,
    #endif
    opendds_wrapper_BuiltinTimestampPlugin_create_typed_datareader,
    #ifndef RTI_CERT
    opendds_wrapper_BuiltinTimestampPlugin_delete_typed_datareader,
    #else
    NULL,
    #endif
    opendds_wrapper_BuiltinTimestampTypePlugin_create_plugin,
    opendds_wrapper_BuiltinTimestampTypePlugin_delete_plugin,
    opendds_wrapper_BuiltinTimestamp_on_type_registered,
    opendds_wrapper_BuiltinTimestamp_on_type_unregistered,

};

/* --------------------------------------------------------------------------
*  Type opendds_wrapper_BuiltinTimestamp Plugin Methods
* -------------------------------------------------------------------------- */

struct DDS_TypePluginI*
opendds_wrapper_BuiltinTimestampTypePlugin_get(void) 
{ 
    return &opendds_wrapper_BuiltinTimestamp_fv_TypePluginI;
} 

RTI_PRIVATE struct DDS_TypePlugin*
opendds_wrapper_BuiltinTimestampTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property)
{
    return DDS_TypePluginDefault_create(&opendds_wrapper_BuiltinTimestamp_fv_TypePluginI,
    participant,dp_qos,
    endpoint_mode,endpoint,qos,
    property);
}

RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinTimestampTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin)
{
    return DDS_TypePluginDefault_delete(plugin);
}

struct DDS_TypePlugin*
opendds_wrapper_BuiltinTimestampWriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &opendds_wrapper_BuiltinTimestamp_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_WRITER,
        (DDS_TypePluginEndpoint*)writer,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

struct DDS_TypePlugin*
opendds_wrapper_BuiltinTimestampReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &opendds_wrapper_BuiltinTimestamp_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_READER,
        (DDS_TypePluginEndpoint*)reader,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

const char*
opendds_wrapper_BuiltinTimestampTypePlugin_get_default_type_name(void) 
{ 
    return opendds_wrapper_BuiltinTimestampTYPENAME;
} 

NDDS_TypePluginKeyKind 
opendds_wrapper_BuiltinTimestampI_get_key_kind(void)
{
    return opendds_wrapper_BuiltinTimestamp_fv_TypePluginI.key_kind;
}

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------
Typed-endpoint support for C++:
* -------------------------------------------------------------------------- */

void* 
opendds_wrapper_BuiltinUint8Plugin_create_typed_datawriter(void *writer)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * so writer is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataWriter *cpp_writer = 
    new opendds_wrapper_BuiltinUint8DataWriter((DDS_DataWriter*)writer);

    return cpp_writer;   
}

#ifndef RTI_CERT
void 
opendds_wrapper_BuiltinUint8Plugin_delete_typed_datawriter(void *wrapper)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * and DDS_Publisher_delete_datawriter so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataWriter_impl *cpp_writer = (DDSDataWriter_impl *) wrapper;

    opendds_wrapper_BuiltinUint8DataWriter *t_writer = 
    static_cast<opendds_wrapper_BuiltinUint8DataWriter *>(cpp_writer);

    delete t_writer;
}
#endif

void* 
opendds_wrapper_BuiltinUint8Plugin_create_typed_datareader(void *reader)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * so reader is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataReader *cpp_reader = 
    new opendds_wrapper_BuiltinUint8DataReader((DDS_DataReader*)reader);

    return cpp_reader;      
}

#ifndef RTI_CERT
void
opendds_wrapper_BuiltinUint8Plugin_delete_typed_datareader(void *wrapper)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * and DDS_Subscriber_delete_datareader so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataReader_impl *cpp_reader = (DDSDataReader_impl *) wrapper;

    opendds_wrapper_BuiltinUint8DataReader *t_reader = 
    static_cast<opendds_wrapper_BuiltinUint8DataReader *>(cpp_reader);

    delete t_reader;
}
#endif

/* --------------------------------------------------------------------------
*  Sample Support functions:
* -------------------------------------------------------------------------- */
RTI_BOOL
opendds_wrapper_BuiltinUint8Plugin_create_sample(struct DDS_TypePlugin *plugin,
void **sample)
{
    UNUSED_ARG(plugin);

    *sample = (void *) opendds_wrapper_BuiltinUint8_create();
    return (*sample != NULL);
}

#ifndef RTI_CERT
RTI_BOOL
opendds_wrapper_BuiltinUint8Plugin_delete_sample(struct DDS_TypePlugin *plugin, 
void *sample)
{
    UNUSED_ARG(plugin);

    opendds_wrapper_BuiltinUint8_delete((opendds_wrapper_BuiltinUint8 *) sample);
    return RTI_TRUE;
}
#endif

RTI_BOOL 
opendds_wrapper_BuiltinUint8Plugin_copy_sample(struct DDS_TypePlugin *plugin, 
void *dst, 
const void *src)
{
    UNUSED_ARG(plugin);

    return opendds_wrapper_BuiltinUint8_copy(
        (opendds_wrapper_BuiltinUint8*)dst,
        (const opendds_wrapper_BuiltinUint8*)src);
}
/* --------------------------------------------------------------------------
*  Type opendds_wrapper_BuiltinUint8 Plugin Instantiation
* -------------------------------------------------------------------------- */

NDDSCDREncapsulation opendds_wrapper_BuiltinUint8EncapsulationKind[] =
{ 
    {
        DDS_ENCAPSULATION_ID_CDR_LE,
        DDS_ENCAPSULATION_ID_CDR_BE,
        0
    }
};

NDDSCDREncapsulation opendds_wrapper_BuiltinUint8V2EncapsulationKind[] =
{ 
    {

        DDS_ENCAPSULATION_ID_XCDR2_A_LE,
        DDS_ENCAPSULATION_ID_XCDR2_A_BE,
        0

    }
};

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinUint8TypePlugin_initialize_sample(struct DDS_TypePlugin *plugin, void *buffer)
{
    UNUSED_ARG(plugin);
    return opendds_wrapper_BuiltinUint8_initialize((opendds_wrapper_BuiltinUint8*)buffer);
}

RTI_PRIVATE RTI_UINT32 
opendds_wrapper_BuiltinUint8_get_user_sample_size(
    struct DDS_TypePlugin *tp)
{
    UNUSED_ARG(tp);        
    return sizeof(opendds_wrapper_BuiltinUint8);
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinUint8_cdr_initialize(void *init_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)init_config;
    void *sample;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!opendds_wrapper_BuiltinUint8Plugin_create_sample(&plugin->_parent,&sample))
    {
        return RTI_FALSE;
    }

    sh->sample = sample;

    return RTI_TRUE;
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinUint8_cdr_finalize(void *finalize_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)finalize_config;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!opendds_wrapper_BuiltinUint8Plugin_delete_sample(&plugin->_parent,sh->sample))
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

RTI_PRIVATE void 
opendds_wrapper_BuiltinUint8TypePlugin_return_sample(
    struct DDS_TypePlugin *tp,
    struct DDS_TypePluginSampleHolder *sample)
{
    opendds_wrapper_BuiltinUint8_finalize_optional_members((opendds_wrapper_BuiltinUint8*)sample->sample, RTI_FALSE);
    XCDR_GenericStreamPlugin_return_sample(tp, sample);
}

RTI_PRIVATE struct DDS_TypeMemoryPlugin*
opendds_wrapper_BuiltinUint8XTypesHeapPlugin_create(struct DDS_TypePlugin *tp,
DDS_DomainParticipant *participant,
struct DDS_DomainParticipantQos *dp_qos,
DDS_TypePluginMode_T endpoint_mode,
DDS_TypePluginEndpoint *endpoint,
DDS_TypePluginEndpointQos *qos)
{
    return DDS_XTypesHeapPlugin_create(
        tp,
        participant,
        dp_qos,
        endpoint_mode,
        endpoint,
        qos,
        NULL,
        NULL,
        opendds_wrapper_BuiltinUint8_cdr_initialize,
        opendds_wrapper_BuiltinUint8_cdr_finalize,
        sizeof(opendds_wrapper_BuiltinUint8),
        RTI_FALSE
        );
}

RTI_PRIVATE struct DDS_TypeMemoryI opendds_wrapper_BuiltinUint8_fv_XTypesHeapPluginI =
{
    RTI_MEMORY_MANAGER_HEAP,
    RTI_MEMORY_TYPE_HEAP,
    opendds_wrapper_BuiltinUint8Plugin_create_sample,
    #ifndef RTI_CERT
    opendds_wrapper_BuiltinUint8Plugin_delete_sample,
    #else
    NULL,
    #endif
    NULL, /* get_address */
    NULL, /* return_address */
    NULL,
    DDS_XTypesHeapPlugin_get_sample_state,
    DDS_XTypesHeapPlugin_set_sample_state,
    DDS_XTypesHeapPlugin_is_owner,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    opendds_wrapper_BuiltinUint8XTypesHeapPlugin_create,
    DDS_XTypesHeapPlugin_delete
};	

RTI_PRIVATE DDS_Boolean 
opendds_wrapper_BuiltinUint8_on_type_registered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    struct RTIXCdrInterpreterProgramsGenProperty programProperty =
    RTIXCdrInterpreterProgramsGenProperty_INITIALIZER;

    programProperty.resolveAlias = RTI_XCDR_TRUE;
    programProperty.inlineStruct = RTI_XCDR_TRUE;
    programProperty.optimizeEnum = RTI_XCDR_TRUE;

    programs = RTIXCdrInterpreterPrograms_new(
        (RTIXCdrTypeCode *)opendds_wrapper_BuiltinUint8_get_typecode(),
        &programProperty,
        RTI_XCDR_PROGRAM_MASK_TYPEPLUGIN
        );

    if (programs == NULL)
    {
        return DDS_BOOLEAN_FALSE;
    }

    DDS_TypeImpl_set_programs(type_impl, programs);
    DDS_TypeImpl_set_typecode(type_impl,  opendds_wrapper_BuiltinUint8_get_typecode());

    return DDS_BOOLEAN_TRUE;
}
RTI_PRIVATE DDS_Boolean 
opendds_wrapper_BuiltinUint8_on_type_unregistered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    programs = DDS_TypeImpl_get_programs(type_impl);

    if (programs != NULL) 
    {
        RTIXCdrInterpreterPrograms_delete(programs);
    }
    DDS_TypeImpl_set_programs(type_impl, NULL); 

    return DDS_BOOLEAN_TRUE;   
}

RTI_PRIVATE 
struct DDS_TypeEncapsulationI opendds_wrapper_BuiltinUint8_fv_XCDRv1PluginI =
{
    DDS_XCDR_DATA_REPRESENTATION,
    NULL,
    opendds_wrapper_BuiltinUint8EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,
    opendds_wrapper_BuiltinUint8TypePlugin_return_sample,
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv1_StreamPlugin_get_serialized_sample_size,
    XCDRv1_StreamPlugin_create,
    XCDRv1_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI opendds_wrapper_BuiltinUint8_fv_XCDRv2PluginI =
{
    DDS_XCDR2_DATA_REPRESENTATION,
    NULL,
    opendds_wrapper_BuiltinUint8V2EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,

    opendds_wrapper_BuiltinUint8TypePlugin_return_sample,   
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv2_StreamPlugin_get_serialized_sample_size,
    XCDRv2_StreamPlugin_create,
    XCDRv2_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI *opendds_wrapper_BuiltinUint8_fv_WirePlugins[] =
{
    &opendds_wrapper_BuiltinUint8_fv_XCDRv2PluginI,
    &opendds_wrapper_BuiltinUint8_fv_XCDRv1PluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypeMemoryI *opendds_wrapper_BuiltinUint8_fv_MemoryPlugins[] =
{
    &opendds_wrapper_BuiltinUint8_fv_XTypesHeapPluginI,

    NULL
};

RTI_PRIVATE struct DDS_TypePlugin*
opendds_wrapper_BuiltinUint8TypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property);
RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinUint8TypePlugin_delete_plugin(struct DDS_TypePlugin *plugin);

RTI_PRIVATE struct DDS_TypePluginI opendds_wrapper_BuiltinUint8_fv_TypePluginI =
{
    /**************************************************************************
    *                   Type information functions
    **************************************************************************/

    NULL,                       /* DDS_TypeCode_t* */
    NDDS_TYPEPLUGIN_NO_KEY,     /* NDDS_TypePluginKeyKind */

    NDDS_TYPEPLUGIN_EH_LOCATION_PAYLOAD,
    opendds_wrapper_BuiltinUint8_get_user_sample_size,   
    RTI_MEMORY_TYPE_HEAP,
    NULL,
    opendds_wrapper_BuiltinUint8Plugin_copy_sample,

    opendds_wrapper_BuiltinUint8TypePlugin_initialize_sample,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    opendds_wrapper_BuiltinUint8_fv_MemoryPlugins,
    opendds_wrapper_BuiltinUint8_fv_WirePlugins,

    /**************************************************************************
    *       Helper APIs to create language binding wrapper Functions
    **************************************************************************/

    opendds_wrapper_BuiltinUint8Plugin_create_typed_datawriter,
    #ifndef RTI_CERT
    opendds_wrapper_BuiltinUint8Plugin_delete_typed_datawriter,
    #else
    NULL,
    #endif
    opendds_wrapper_BuiltinUint8Plugin_create_typed_datareader,
    #ifndef RTI_CERT
    opendds_wrapper_BuiltinUint8Plugin_delete_typed_datareader,
    #else
    NULL,
    #endif
    opendds_wrapper_BuiltinUint8TypePlugin_create_plugin,
    opendds_wrapper_BuiltinUint8TypePlugin_delete_plugin,
    opendds_wrapper_BuiltinUint8_on_type_registered,
    opendds_wrapper_BuiltinUint8_on_type_unregistered,

};

/* --------------------------------------------------------------------------
*  Type opendds_wrapper_BuiltinUint8 Plugin Methods
* -------------------------------------------------------------------------- */

struct DDS_TypePluginI*
opendds_wrapper_BuiltinUint8TypePlugin_get(void) 
{ 
    return &opendds_wrapper_BuiltinUint8_fv_TypePluginI;
} 

RTI_PRIVATE struct DDS_TypePlugin*
opendds_wrapper_BuiltinUint8TypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property)
{
    return DDS_TypePluginDefault_create(&opendds_wrapper_BuiltinUint8_fv_TypePluginI,
    participant,dp_qos,
    endpoint_mode,endpoint,qos,
    property);
}

RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinUint8TypePlugin_delete_plugin(struct DDS_TypePlugin *plugin)
{
    return DDS_TypePluginDefault_delete(plugin);
}

struct DDS_TypePlugin*
opendds_wrapper_BuiltinUint8WriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &opendds_wrapper_BuiltinUint8_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_WRITER,
        (DDS_TypePluginEndpoint*)writer,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

struct DDS_TypePlugin*
opendds_wrapper_BuiltinUint8ReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &opendds_wrapper_BuiltinUint8_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_READER,
        (DDS_TypePluginEndpoint*)reader,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

const char*
opendds_wrapper_BuiltinUint8TypePlugin_get_default_type_name(void) 
{ 
    return opendds_wrapper_BuiltinUint8TYPENAME;
} 

NDDS_TypePluginKeyKind 
opendds_wrapper_BuiltinUint8I_get_key_kind(void)
{
    return opendds_wrapper_BuiltinUint8_fv_TypePluginI.key_kind;
}

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------
Typed-endpoint support for C++:
* -------------------------------------------------------------------------- */

void* 
opendds_wrapper_BuiltinUint16Plugin_create_typed_datawriter(void *writer)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * so writer is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataWriter *cpp_writer = 
    new opendds_wrapper_BuiltinUint16DataWriter((DDS_DataWriter*)writer);

    return cpp_writer;   
}

#ifndef RTI_CERT
void 
opendds_wrapper_BuiltinUint16Plugin_delete_typed_datawriter(void *wrapper)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * and DDS_Publisher_delete_datawriter so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataWriter_impl *cpp_writer = (DDSDataWriter_impl *) wrapper;

    opendds_wrapper_BuiltinUint16DataWriter *t_writer = 
    static_cast<opendds_wrapper_BuiltinUint16DataWriter *>(cpp_writer);

    delete t_writer;
}
#endif

void* 
opendds_wrapper_BuiltinUint16Plugin_create_typed_datareader(void *reader)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * so reader is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataReader *cpp_reader = 
    new opendds_wrapper_BuiltinUint16DataReader((DDS_DataReader*)reader);

    return cpp_reader;      
}

#ifndef RTI_CERT
void
opendds_wrapper_BuiltinUint16Plugin_delete_typed_datareader(void *wrapper)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * and DDS_Subscriber_delete_datareader so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataReader_impl *cpp_reader = (DDSDataReader_impl *) wrapper;

    opendds_wrapper_BuiltinUint16DataReader *t_reader = 
    static_cast<opendds_wrapper_BuiltinUint16DataReader *>(cpp_reader);

    delete t_reader;
}
#endif

/* --------------------------------------------------------------------------
*  Sample Support functions:
* -------------------------------------------------------------------------- */
RTI_BOOL
opendds_wrapper_BuiltinUint16Plugin_create_sample(struct DDS_TypePlugin *plugin,
void **sample)
{
    UNUSED_ARG(plugin);

    *sample = (void *) opendds_wrapper_BuiltinUint16_create();
    return (*sample != NULL);
}

#ifndef RTI_CERT
RTI_BOOL
opendds_wrapper_BuiltinUint16Plugin_delete_sample(struct DDS_TypePlugin *plugin, 
void *sample)
{
    UNUSED_ARG(plugin);

    opendds_wrapper_BuiltinUint16_delete((opendds_wrapper_BuiltinUint16 *) sample);
    return RTI_TRUE;
}
#endif

RTI_BOOL 
opendds_wrapper_BuiltinUint16Plugin_copy_sample(struct DDS_TypePlugin *plugin, 
void *dst, 
const void *src)
{
    UNUSED_ARG(plugin);

    return opendds_wrapper_BuiltinUint16_copy(
        (opendds_wrapper_BuiltinUint16*)dst,
        (const opendds_wrapper_BuiltinUint16*)src);
}
/* --------------------------------------------------------------------------
*  Type opendds_wrapper_BuiltinUint16 Plugin Instantiation
* -------------------------------------------------------------------------- */

NDDSCDREncapsulation opendds_wrapper_BuiltinUint16EncapsulationKind[] =
{ 
    {
        DDS_ENCAPSULATION_ID_CDR_LE,
        DDS_ENCAPSULATION_ID_CDR_BE,
        0
    }
};

NDDSCDREncapsulation opendds_wrapper_BuiltinUint16V2EncapsulationKind[] =
{ 
    {

        DDS_ENCAPSULATION_ID_XCDR2_A_LE,
        DDS_ENCAPSULATION_ID_XCDR2_A_BE,
        0

    }
};

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinUint16TypePlugin_initialize_sample(struct DDS_TypePlugin *plugin, void *buffer)
{
    UNUSED_ARG(plugin);
    return opendds_wrapper_BuiltinUint16_initialize((opendds_wrapper_BuiltinUint16*)buffer);
}

RTI_PRIVATE RTI_UINT32 
opendds_wrapper_BuiltinUint16_get_user_sample_size(
    struct DDS_TypePlugin *tp)
{
    UNUSED_ARG(tp);        
    return sizeof(opendds_wrapper_BuiltinUint16);
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinUint16_cdr_initialize(void *init_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)init_config;
    void *sample;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!opendds_wrapper_BuiltinUint16Plugin_create_sample(&plugin->_parent,&sample))
    {
        return RTI_FALSE;
    }

    sh->sample = sample;

    return RTI_TRUE;
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinUint16_cdr_finalize(void *finalize_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)finalize_config;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!opendds_wrapper_BuiltinUint16Plugin_delete_sample(&plugin->_parent,sh->sample))
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

RTI_PRIVATE void 
opendds_wrapper_BuiltinUint16TypePlugin_return_sample(
    struct DDS_TypePlugin *tp,
    struct DDS_TypePluginSampleHolder *sample)
{
    opendds_wrapper_BuiltinUint16_finalize_optional_members((opendds_wrapper_BuiltinUint16*)sample->sample, RTI_FALSE);
    XCDR_GenericStreamPlugin_return_sample(tp, sample);
}

RTI_PRIVATE struct DDS_TypeMemoryPlugin*
opendds_wrapper_BuiltinUint16XTypesHeapPlugin_create(struct DDS_TypePlugin *tp,
DDS_DomainParticipant *participant,
struct DDS_DomainParticipantQos *dp_qos,
DDS_TypePluginMode_T endpoint_mode,
DDS_TypePluginEndpoint *endpoint,
DDS_TypePluginEndpointQos *qos)
{
    return DDS_XTypesHeapPlugin_create(
        tp,
        participant,
        dp_qos,
        endpoint_mode,
        endpoint,
        qos,
        NULL,
        NULL,
        opendds_wrapper_BuiltinUint16_cdr_initialize,
        opendds_wrapper_BuiltinUint16_cdr_finalize,
        sizeof(opendds_wrapper_BuiltinUint16),
        RTI_FALSE
        );
}

RTI_PRIVATE struct DDS_TypeMemoryI opendds_wrapper_BuiltinUint16_fv_XTypesHeapPluginI =
{
    RTI_MEMORY_MANAGER_HEAP,
    RTI_MEMORY_TYPE_HEAP,
    opendds_wrapper_BuiltinUint16Plugin_create_sample,
    #ifndef RTI_CERT
    opendds_wrapper_BuiltinUint16Plugin_delete_sample,
    #else
    NULL,
    #endif
    NULL, /* get_address */
    NULL, /* return_address */
    NULL,
    DDS_XTypesHeapPlugin_get_sample_state,
    DDS_XTypesHeapPlugin_set_sample_state,
    DDS_XTypesHeapPlugin_is_owner,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    opendds_wrapper_BuiltinUint16XTypesHeapPlugin_create,
    DDS_XTypesHeapPlugin_delete
};	

RTI_PRIVATE DDS_Boolean 
opendds_wrapper_BuiltinUint16_on_type_registered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    struct RTIXCdrInterpreterProgramsGenProperty programProperty =
    RTIXCdrInterpreterProgramsGenProperty_INITIALIZER;

    programProperty.resolveAlias = RTI_XCDR_TRUE;
    programProperty.inlineStruct = RTI_XCDR_TRUE;
    programProperty.optimizeEnum = RTI_XCDR_TRUE;

    programs = RTIXCdrInterpreterPrograms_new(
        (RTIXCdrTypeCode *)opendds_wrapper_BuiltinUint16_get_typecode(),
        &programProperty,
        RTI_XCDR_PROGRAM_MASK_TYPEPLUGIN
        );

    if (programs == NULL)
    {
        return DDS_BOOLEAN_FALSE;
    }

    DDS_TypeImpl_set_programs(type_impl, programs);
    DDS_TypeImpl_set_typecode(type_impl,  opendds_wrapper_BuiltinUint16_get_typecode());

    return DDS_BOOLEAN_TRUE;
}
RTI_PRIVATE DDS_Boolean 
opendds_wrapper_BuiltinUint16_on_type_unregistered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    programs = DDS_TypeImpl_get_programs(type_impl);

    if (programs != NULL) 
    {
        RTIXCdrInterpreterPrograms_delete(programs);
    }
    DDS_TypeImpl_set_programs(type_impl, NULL); 

    return DDS_BOOLEAN_TRUE;   
}

RTI_PRIVATE 
struct DDS_TypeEncapsulationI opendds_wrapper_BuiltinUint16_fv_XCDRv1PluginI =
{
    DDS_XCDR_DATA_REPRESENTATION,
    NULL,
    opendds_wrapper_BuiltinUint16EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,
    opendds_wrapper_BuiltinUint16TypePlugin_return_sample,
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv1_StreamPlugin_get_serialized_sample_size,
    XCDRv1_StreamPlugin_create,
    XCDRv1_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI opendds_wrapper_BuiltinUint16_fv_XCDRv2PluginI =
{
    DDS_XCDR2_DATA_REPRESENTATION,
    NULL,
    opendds_wrapper_BuiltinUint16V2EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,

    opendds_wrapper_BuiltinUint16TypePlugin_return_sample,   
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv2_StreamPlugin_get_serialized_sample_size,
    XCDRv2_StreamPlugin_create,
    XCDRv2_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI *opendds_wrapper_BuiltinUint16_fv_WirePlugins[] =
{
    &opendds_wrapper_BuiltinUint16_fv_XCDRv2PluginI,
    &opendds_wrapper_BuiltinUint16_fv_XCDRv1PluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypeMemoryI *opendds_wrapper_BuiltinUint16_fv_MemoryPlugins[] =
{
    &opendds_wrapper_BuiltinUint16_fv_XTypesHeapPluginI,

    NULL
};

RTI_PRIVATE struct DDS_TypePlugin*
opendds_wrapper_BuiltinUint16TypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property);
RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinUint16TypePlugin_delete_plugin(struct DDS_TypePlugin *plugin);

RTI_PRIVATE struct DDS_TypePluginI opendds_wrapper_BuiltinUint16_fv_TypePluginI =
{
    /**************************************************************************
    *                   Type information functions
    **************************************************************************/

    NULL,                       /* DDS_TypeCode_t* */
    NDDS_TYPEPLUGIN_NO_KEY,     /* NDDS_TypePluginKeyKind */

    NDDS_TYPEPLUGIN_EH_LOCATION_PAYLOAD,
    opendds_wrapper_BuiltinUint16_get_user_sample_size,   
    RTI_MEMORY_TYPE_HEAP,
    NULL,
    opendds_wrapper_BuiltinUint16Plugin_copy_sample,

    opendds_wrapper_BuiltinUint16TypePlugin_initialize_sample,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    opendds_wrapper_BuiltinUint16_fv_MemoryPlugins,
    opendds_wrapper_BuiltinUint16_fv_WirePlugins,

    /**************************************************************************
    *       Helper APIs to create language binding wrapper Functions
    **************************************************************************/

    opendds_wrapper_BuiltinUint16Plugin_create_typed_datawriter,
    #ifndef RTI_CERT
    opendds_wrapper_BuiltinUint16Plugin_delete_typed_datawriter,
    #else
    NULL,
    #endif
    opendds_wrapper_BuiltinUint16Plugin_create_typed_datareader,
    #ifndef RTI_CERT
    opendds_wrapper_BuiltinUint16Plugin_delete_typed_datareader,
    #else
    NULL,
    #endif
    opendds_wrapper_BuiltinUint16TypePlugin_create_plugin,
    opendds_wrapper_BuiltinUint16TypePlugin_delete_plugin,
    opendds_wrapper_BuiltinUint16_on_type_registered,
    opendds_wrapper_BuiltinUint16_on_type_unregistered,

};

/* --------------------------------------------------------------------------
*  Type opendds_wrapper_BuiltinUint16 Plugin Methods
* -------------------------------------------------------------------------- */

struct DDS_TypePluginI*
opendds_wrapper_BuiltinUint16TypePlugin_get(void) 
{ 
    return &opendds_wrapper_BuiltinUint16_fv_TypePluginI;
} 

RTI_PRIVATE struct DDS_TypePlugin*
opendds_wrapper_BuiltinUint16TypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property)
{
    return DDS_TypePluginDefault_create(&opendds_wrapper_BuiltinUint16_fv_TypePluginI,
    participant,dp_qos,
    endpoint_mode,endpoint,qos,
    property);
}

RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinUint16TypePlugin_delete_plugin(struct DDS_TypePlugin *plugin)
{
    return DDS_TypePluginDefault_delete(plugin);
}

struct DDS_TypePlugin*
opendds_wrapper_BuiltinUint16WriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &opendds_wrapper_BuiltinUint16_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_WRITER,
        (DDS_TypePluginEndpoint*)writer,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

struct DDS_TypePlugin*
opendds_wrapper_BuiltinUint16ReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &opendds_wrapper_BuiltinUint16_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_READER,
        (DDS_TypePluginEndpoint*)reader,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

const char*
opendds_wrapper_BuiltinUint16TypePlugin_get_default_type_name(void) 
{ 
    return opendds_wrapper_BuiltinUint16TYPENAME;
} 

NDDS_TypePluginKeyKind 
opendds_wrapper_BuiltinUint16I_get_key_kind(void)
{
    return opendds_wrapper_BuiltinUint16_fv_TypePluginI.key_kind;
}

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------
Typed-endpoint support for C++:
* -------------------------------------------------------------------------- */

void* 
opendds_wrapper_BuiltinUint32Plugin_create_typed_datawriter(void *writer)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * so writer is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataWriter *cpp_writer = 
    new opendds_wrapper_BuiltinUint32DataWriter((DDS_DataWriter*)writer);

    return cpp_writer;   
}

#ifndef RTI_CERT
void 
opendds_wrapper_BuiltinUint32Plugin_delete_typed_datawriter(void *wrapper)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * and DDS_Publisher_delete_datawriter so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataWriter_impl *cpp_writer = (DDSDataWriter_impl *) wrapper;

    opendds_wrapper_BuiltinUint32DataWriter *t_writer = 
    static_cast<opendds_wrapper_BuiltinUint32DataWriter *>(cpp_writer);

    delete t_writer;
}
#endif

void* 
opendds_wrapper_BuiltinUint32Plugin_create_typed_datareader(void *reader)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * so reader is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataReader *cpp_reader = 
    new opendds_wrapper_BuiltinUint32DataReader((DDS_DataReader*)reader);

    return cpp_reader;      
}

#ifndef RTI_CERT
void
opendds_wrapper_BuiltinUint32Plugin_delete_typed_datareader(void *wrapper)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * and DDS_Subscriber_delete_datareader so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataReader_impl *cpp_reader = (DDSDataReader_impl *) wrapper;

    opendds_wrapper_BuiltinUint32DataReader *t_reader = 
    static_cast<opendds_wrapper_BuiltinUint32DataReader *>(cpp_reader);

    delete t_reader;
}
#endif

/* --------------------------------------------------------------------------
*  Sample Support functions:
* -------------------------------------------------------------------------- */
RTI_BOOL
opendds_wrapper_BuiltinUint32Plugin_create_sample(struct DDS_TypePlugin *plugin,
void **sample)
{
    UNUSED_ARG(plugin);

    *sample = (void *) opendds_wrapper_BuiltinUint32_create();
    return (*sample != NULL);
}

#ifndef RTI_CERT
RTI_BOOL
opendds_wrapper_BuiltinUint32Plugin_delete_sample(struct DDS_TypePlugin *plugin, 
void *sample)
{
    UNUSED_ARG(plugin);

    opendds_wrapper_BuiltinUint32_delete((opendds_wrapper_BuiltinUint32 *) sample);
    return RTI_TRUE;
}
#endif

RTI_BOOL 
opendds_wrapper_BuiltinUint32Plugin_copy_sample(struct DDS_TypePlugin *plugin, 
void *dst, 
const void *src)
{
    UNUSED_ARG(plugin);

    return opendds_wrapper_BuiltinUint32_copy(
        (opendds_wrapper_BuiltinUint32*)dst,
        (const opendds_wrapper_BuiltinUint32*)src);
}
/* --------------------------------------------------------------------------
*  Type opendds_wrapper_BuiltinUint32 Plugin Instantiation
* -------------------------------------------------------------------------- */

NDDSCDREncapsulation opendds_wrapper_BuiltinUint32EncapsulationKind[] =
{ 
    {
        DDS_ENCAPSULATION_ID_CDR_LE,
        DDS_ENCAPSULATION_ID_CDR_BE,
        0
    }
};

NDDSCDREncapsulation opendds_wrapper_BuiltinUint32V2EncapsulationKind[] =
{ 
    {

        DDS_ENCAPSULATION_ID_XCDR2_A_LE,
        DDS_ENCAPSULATION_ID_XCDR2_A_BE,
        0

    }
};

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinUint32TypePlugin_initialize_sample(struct DDS_TypePlugin *plugin, void *buffer)
{
    UNUSED_ARG(plugin);
    return opendds_wrapper_BuiltinUint32_initialize((opendds_wrapper_BuiltinUint32*)buffer);
}

RTI_PRIVATE RTI_UINT32 
opendds_wrapper_BuiltinUint32_get_user_sample_size(
    struct DDS_TypePlugin *tp)
{
    UNUSED_ARG(tp);        
    return sizeof(opendds_wrapper_BuiltinUint32);
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinUint32_cdr_initialize(void *init_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)init_config;
    void *sample;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!opendds_wrapper_BuiltinUint32Plugin_create_sample(&plugin->_parent,&sample))
    {
        return RTI_FALSE;
    }

    sh->sample = sample;

    return RTI_TRUE;
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinUint32_cdr_finalize(void *finalize_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)finalize_config;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!opendds_wrapper_BuiltinUint32Plugin_delete_sample(&plugin->_parent,sh->sample))
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

RTI_PRIVATE void 
opendds_wrapper_BuiltinUint32TypePlugin_return_sample(
    struct DDS_TypePlugin *tp,
    struct DDS_TypePluginSampleHolder *sample)
{
    opendds_wrapper_BuiltinUint32_finalize_optional_members((opendds_wrapper_BuiltinUint32*)sample->sample, RTI_FALSE);
    XCDR_GenericStreamPlugin_return_sample(tp, sample);
}

RTI_PRIVATE struct DDS_TypeMemoryPlugin*
opendds_wrapper_BuiltinUint32XTypesHeapPlugin_create(struct DDS_TypePlugin *tp,
DDS_DomainParticipant *participant,
struct DDS_DomainParticipantQos *dp_qos,
DDS_TypePluginMode_T endpoint_mode,
DDS_TypePluginEndpoint *endpoint,
DDS_TypePluginEndpointQos *qos)
{
    return DDS_XTypesHeapPlugin_create(
        tp,
        participant,
        dp_qos,
        endpoint_mode,
        endpoint,
        qos,
        NULL,
        NULL,
        opendds_wrapper_BuiltinUint32_cdr_initialize,
        opendds_wrapper_BuiltinUint32_cdr_finalize,
        sizeof(opendds_wrapper_BuiltinUint32),
        RTI_FALSE
        );
}

RTI_PRIVATE struct DDS_TypeMemoryI opendds_wrapper_BuiltinUint32_fv_XTypesHeapPluginI =
{
    RTI_MEMORY_MANAGER_HEAP,
    RTI_MEMORY_TYPE_HEAP,
    opendds_wrapper_BuiltinUint32Plugin_create_sample,
    #ifndef RTI_CERT
    opendds_wrapper_BuiltinUint32Plugin_delete_sample,
    #else
    NULL,
    #endif
    NULL, /* get_address */
    NULL, /* return_address */
    NULL,
    DDS_XTypesHeapPlugin_get_sample_state,
    DDS_XTypesHeapPlugin_set_sample_state,
    DDS_XTypesHeapPlugin_is_owner,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    opendds_wrapper_BuiltinUint32XTypesHeapPlugin_create,
    DDS_XTypesHeapPlugin_delete
};	

RTI_PRIVATE DDS_Boolean 
opendds_wrapper_BuiltinUint32_on_type_registered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    struct RTIXCdrInterpreterProgramsGenProperty programProperty =
    RTIXCdrInterpreterProgramsGenProperty_INITIALIZER;

    programProperty.resolveAlias = RTI_XCDR_TRUE;
    programProperty.inlineStruct = RTI_XCDR_TRUE;
    programProperty.optimizeEnum = RTI_XCDR_TRUE;

    programs = RTIXCdrInterpreterPrograms_new(
        (RTIXCdrTypeCode *)opendds_wrapper_BuiltinUint32_get_typecode(),
        &programProperty,
        RTI_XCDR_PROGRAM_MASK_TYPEPLUGIN
        );

    if (programs == NULL)
    {
        return DDS_BOOLEAN_FALSE;
    }

    DDS_TypeImpl_set_programs(type_impl, programs);
    DDS_TypeImpl_set_typecode(type_impl,  opendds_wrapper_BuiltinUint32_get_typecode());

    return DDS_BOOLEAN_TRUE;
}
RTI_PRIVATE DDS_Boolean 
opendds_wrapper_BuiltinUint32_on_type_unregistered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    programs = DDS_TypeImpl_get_programs(type_impl);

    if (programs != NULL) 
    {
        RTIXCdrInterpreterPrograms_delete(programs);
    }
    DDS_TypeImpl_set_programs(type_impl, NULL); 

    return DDS_BOOLEAN_TRUE;   
}

RTI_PRIVATE 
struct DDS_TypeEncapsulationI opendds_wrapper_BuiltinUint32_fv_XCDRv1PluginI =
{
    DDS_XCDR_DATA_REPRESENTATION,
    NULL,
    opendds_wrapper_BuiltinUint32EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,
    opendds_wrapper_BuiltinUint32TypePlugin_return_sample,
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv1_StreamPlugin_get_serialized_sample_size,
    XCDRv1_StreamPlugin_create,
    XCDRv1_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI opendds_wrapper_BuiltinUint32_fv_XCDRv2PluginI =
{
    DDS_XCDR2_DATA_REPRESENTATION,
    NULL,
    opendds_wrapper_BuiltinUint32V2EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,

    opendds_wrapper_BuiltinUint32TypePlugin_return_sample,   
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv2_StreamPlugin_get_serialized_sample_size,
    XCDRv2_StreamPlugin_create,
    XCDRv2_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI *opendds_wrapper_BuiltinUint32_fv_WirePlugins[] =
{
    &opendds_wrapper_BuiltinUint32_fv_XCDRv2PluginI,
    &opendds_wrapper_BuiltinUint32_fv_XCDRv1PluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypeMemoryI *opendds_wrapper_BuiltinUint32_fv_MemoryPlugins[] =
{
    &opendds_wrapper_BuiltinUint32_fv_XTypesHeapPluginI,

    NULL
};

RTI_PRIVATE struct DDS_TypePlugin*
opendds_wrapper_BuiltinUint32TypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property);
RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinUint32TypePlugin_delete_plugin(struct DDS_TypePlugin *plugin);

RTI_PRIVATE struct DDS_TypePluginI opendds_wrapper_BuiltinUint32_fv_TypePluginI =
{
    /**************************************************************************
    *                   Type information functions
    **************************************************************************/

    NULL,                       /* DDS_TypeCode_t* */
    NDDS_TYPEPLUGIN_NO_KEY,     /* NDDS_TypePluginKeyKind */

    NDDS_TYPEPLUGIN_EH_LOCATION_PAYLOAD,
    opendds_wrapper_BuiltinUint32_get_user_sample_size,   
    RTI_MEMORY_TYPE_HEAP,
    NULL,
    opendds_wrapper_BuiltinUint32Plugin_copy_sample,

    opendds_wrapper_BuiltinUint32TypePlugin_initialize_sample,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    opendds_wrapper_BuiltinUint32_fv_MemoryPlugins,
    opendds_wrapper_BuiltinUint32_fv_WirePlugins,

    /**************************************************************************
    *       Helper APIs to create language binding wrapper Functions
    **************************************************************************/

    opendds_wrapper_BuiltinUint32Plugin_create_typed_datawriter,
    #ifndef RTI_CERT
    opendds_wrapper_BuiltinUint32Plugin_delete_typed_datawriter,
    #else
    NULL,
    #endif
    opendds_wrapper_BuiltinUint32Plugin_create_typed_datareader,
    #ifndef RTI_CERT
    opendds_wrapper_BuiltinUint32Plugin_delete_typed_datareader,
    #else
    NULL,
    #endif
    opendds_wrapper_BuiltinUint32TypePlugin_create_plugin,
    opendds_wrapper_BuiltinUint32TypePlugin_delete_plugin,
    opendds_wrapper_BuiltinUint32_on_type_registered,
    opendds_wrapper_BuiltinUint32_on_type_unregistered,

};

/* --------------------------------------------------------------------------
*  Type opendds_wrapper_BuiltinUint32 Plugin Methods
* -------------------------------------------------------------------------- */

struct DDS_TypePluginI*
opendds_wrapper_BuiltinUint32TypePlugin_get(void) 
{ 
    return &opendds_wrapper_BuiltinUint32_fv_TypePluginI;
} 

RTI_PRIVATE struct DDS_TypePlugin*
opendds_wrapper_BuiltinUint32TypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property)
{
    return DDS_TypePluginDefault_create(&opendds_wrapper_BuiltinUint32_fv_TypePluginI,
    participant,dp_qos,
    endpoint_mode,endpoint,qos,
    property);
}

RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinUint32TypePlugin_delete_plugin(struct DDS_TypePlugin *plugin)
{
    return DDS_TypePluginDefault_delete(plugin);
}

struct DDS_TypePlugin*
opendds_wrapper_BuiltinUint32WriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &opendds_wrapper_BuiltinUint32_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_WRITER,
        (DDS_TypePluginEndpoint*)writer,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

struct DDS_TypePlugin*
opendds_wrapper_BuiltinUint32ReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &opendds_wrapper_BuiltinUint32_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_READER,
        (DDS_TypePluginEndpoint*)reader,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

const char*
opendds_wrapper_BuiltinUint32TypePlugin_get_default_type_name(void) 
{ 
    return opendds_wrapper_BuiltinUint32TYPENAME;
} 

NDDS_TypePluginKeyKind 
opendds_wrapper_BuiltinUint32I_get_key_kind(void)
{
    return opendds_wrapper_BuiltinUint32_fv_TypePluginI.key_kind;
}

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------
Typed-endpoint support for C++:
* -------------------------------------------------------------------------- */

void* 
opendds_wrapper_BuiltinUint64Plugin_create_typed_datawriter(void *writer)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * so writer is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataWriter *cpp_writer = 
    new opendds_wrapper_BuiltinUint64DataWriter((DDS_DataWriter*)writer);

    return cpp_writer;   
}

#ifndef RTI_CERT
void 
opendds_wrapper_BuiltinUint64Plugin_delete_typed_datawriter(void *wrapper)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * and DDS_Publisher_delete_datawriter so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataWriter_impl *cpp_writer = (DDSDataWriter_impl *) wrapper;

    opendds_wrapper_BuiltinUint64DataWriter *t_writer = 
    static_cast<opendds_wrapper_BuiltinUint64DataWriter *>(cpp_writer);

    delete t_writer;
}
#endif

void* 
opendds_wrapper_BuiltinUint64Plugin_create_typed_datareader(void *reader)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * so reader is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataReader *cpp_reader = 
    new opendds_wrapper_BuiltinUint64DataReader((DDS_DataReader*)reader);

    return cpp_reader;      
}

#ifndef RTI_CERT
void
opendds_wrapper_BuiltinUint64Plugin_delete_typed_datareader(void *wrapper)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * and DDS_Subscriber_delete_datareader so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataReader_impl *cpp_reader = (DDSDataReader_impl *) wrapper;

    opendds_wrapper_BuiltinUint64DataReader *t_reader = 
    static_cast<opendds_wrapper_BuiltinUint64DataReader *>(cpp_reader);

    delete t_reader;
}
#endif

/* --------------------------------------------------------------------------
*  Sample Support functions:
* -------------------------------------------------------------------------- */
RTI_BOOL
opendds_wrapper_BuiltinUint64Plugin_create_sample(struct DDS_TypePlugin *plugin,
void **sample)
{
    UNUSED_ARG(plugin);

    *sample = (void *) opendds_wrapper_BuiltinUint64_create();
    return (*sample != NULL);
}

#ifndef RTI_CERT
RTI_BOOL
opendds_wrapper_BuiltinUint64Plugin_delete_sample(struct DDS_TypePlugin *plugin, 
void *sample)
{
    UNUSED_ARG(plugin);

    opendds_wrapper_BuiltinUint64_delete((opendds_wrapper_BuiltinUint64 *) sample);
    return RTI_TRUE;
}
#endif

RTI_BOOL 
opendds_wrapper_BuiltinUint64Plugin_copy_sample(struct DDS_TypePlugin *plugin, 
void *dst, 
const void *src)
{
    UNUSED_ARG(plugin);

    return opendds_wrapper_BuiltinUint64_copy(
        (opendds_wrapper_BuiltinUint64*)dst,
        (const opendds_wrapper_BuiltinUint64*)src);
}
/* --------------------------------------------------------------------------
*  Type opendds_wrapper_BuiltinUint64 Plugin Instantiation
* -------------------------------------------------------------------------- */

NDDSCDREncapsulation opendds_wrapper_BuiltinUint64EncapsulationKind[] =
{ 
    {
        DDS_ENCAPSULATION_ID_CDR_LE,
        DDS_ENCAPSULATION_ID_CDR_BE,
        0
    }
};

NDDSCDREncapsulation opendds_wrapper_BuiltinUint64V2EncapsulationKind[] =
{ 
    {

        DDS_ENCAPSULATION_ID_XCDR2_A_LE,
        DDS_ENCAPSULATION_ID_XCDR2_A_BE,
        0

    }
};

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinUint64TypePlugin_initialize_sample(struct DDS_TypePlugin *plugin, void *buffer)
{
    UNUSED_ARG(plugin);
    return opendds_wrapper_BuiltinUint64_initialize((opendds_wrapper_BuiltinUint64*)buffer);
}

RTI_PRIVATE RTI_UINT32 
opendds_wrapper_BuiltinUint64_get_user_sample_size(
    struct DDS_TypePlugin *tp)
{
    UNUSED_ARG(tp);        
    return sizeof(opendds_wrapper_BuiltinUint64);
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinUint64_cdr_initialize(void *init_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)init_config;
    void *sample;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!opendds_wrapper_BuiltinUint64Plugin_create_sample(&plugin->_parent,&sample))
    {
        return RTI_FALSE;
    }

    sh->sample = sample;

    return RTI_TRUE;
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinUint64_cdr_finalize(void *finalize_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)finalize_config;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!opendds_wrapper_BuiltinUint64Plugin_delete_sample(&plugin->_parent,sh->sample))
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

RTI_PRIVATE void 
opendds_wrapper_BuiltinUint64TypePlugin_return_sample(
    struct DDS_TypePlugin *tp,
    struct DDS_TypePluginSampleHolder *sample)
{
    opendds_wrapper_BuiltinUint64_finalize_optional_members((opendds_wrapper_BuiltinUint64*)sample->sample, RTI_FALSE);
    XCDR_GenericStreamPlugin_return_sample(tp, sample);
}

RTI_PRIVATE struct DDS_TypeMemoryPlugin*
opendds_wrapper_BuiltinUint64XTypesHeapPlugin_create(struct DDS_TypePlugin *tp,
DDS_DomainParticipant *participant,
struct DDS_DomainParticipantQos *dp_qos,
DDS_TypePluginMode_T endpoint_mode,
DDS_TypePluginEndpoint *endpoint,
DDS_TypePluginEndpointQos *qos)
{
    return DDS_XTypesHeapPlugin_create(
        tp,
        participant,
        dp_qos,
        endpoint_mode,
        endpoint,
        qos,
        NULL,
        NULL,
        opendds_wrapper_BuiltinUint64_cdr_initialize,
        opendds_wrapper_BuiltinUint64_cdr_finalize,
        sizeof(opendds_wrapper_BuiltinUint64),
        RTI_FALSE
        );
}

RTI_PRIVATE struct DDS_TypeMemoryI opendds_wrapper_BuiltinUint64_fv_XTypesHeapPluginI =
{
    RTI_MEMORY_MANAGER_HEAP,
    RTI_MEMORY_TYPE_HEAP,
    opendds_wrapper_BuiltinUint64Plugin_create_sample,
    #ifndef RTI_CERT
    opendds_wrapper_BuiltinUint64Plugin_delete_sample,
    #else
    NULL,
    #endif
    NULL, /* get_address */
    NULL, /* return_address */
    NULL,
    DDS_XTypesHeapPlugin_get_sample_state,
    DDS_XTypesHeapPlugin_set_sample_state,
    DDS_XTypesHeapPlugin_is_owner,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    opendds_wrapper_BuiltinUint64XTypesHeapPlugin_create,
    DDS_XTypesHeapPlugin_delete
};	

RTI_PRIVATE DDS_Boolean 
opendds_wrapper_BuiltinUint64_on_type_registered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    struct RTIXCdrInterpreterProgramsGenProperty programProperty =
    RTIXCdrInterpreterProgramsGenProperty_INITIALIZER;

    programProperty.resolveAlias = RTI_XCDR_TRUE;
    programProperty.inlineStruct = RTI_XCDR_TRUE;
    programProperty.optimizeEnum = RTI_XCDR_TRUE;

    programs = RTIXCdrInterpreterPrograms_new(
        (RTIXCdrTypeCode *)opendds_wrapper_BuiltinUint64_get_typecode(),
        &programProperty,
        RTI_XCDR_PROGRAM_MASK_TYPEPLUGIN
        );

    if (programs == NULL)
    {
        return DDS_BOOLEAN_FALSE;
    }

    DDS_TypeImpl_set_programs(type_impl, programs);
    DDS_TypeImpl_set_typecode(type_impl,  opendds_wrapper_BuiltinUint64_get_typecode());

    return DDS_BOOLEAN_TRUE;
}
RTI_PRIVATE DDS_Boolean 
opendds_wrapper_BuiltinUint64_on_type_unregistered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    programs = DDS_TypeImpl_get_programs(type_impl);

    if (programs != NULL) 
    {
        RTIXCdrInterpreterPrograms_delete(programs);
    }
    DDS_TypeImpl_set_programs(type_impl, NULL); 

    return DDS_BOOLEAN_TRUE;   
}

RTI_PRIVATE 
struct DDS_TypeEncapsulationI opendds_wrapper_BuiltinUint64_fv_XCDRv1PluginI =
{
    DDS_XCDR_DATA_REPRESENTATION,
    NULL,
    opendds_wrapper_BuiltinUint64EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,
    opendds_wrapper_BuiltinUint64TypePlugin_return_sample,
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv1_StreamPlugin_get_serialized_sample_size,
    XCDRv1_StreamPlugin_create,
    XCDRv1_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI opendds_wrapper_BuiltinUint64_fv_XCDRv2PluginI =
{
    DDS_XCDR2_DATA_REPRESENTATION,
    NULL,
    opendds_wrapper_BuiltinUint64V2EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,

    opendds_wrapper_BuiltinUint64TypePlugin_return_sample,   
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv2_StreamPlugin_get_serialized_sample_size,
    XCDRv2_StreamPlugin_create,
    XCDRv2_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI *opendds_wrapper_BuiltinUint64_fv_WirePlugins[] =
{
    &opendds_wrapper_BuiltinUint64_fv_XCDRv2PluginI,
    &opendds_wrapper_BuiltinUint64_fv_XCDRv1PluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypeMemoryI *opendds_wrapper_BuiltinUint64_fv_MemoryPlugins[] =
{
    &opendds_wrapper_BuiltinUint64_fv_XTypesHeapPluginI,

    NULL
};

RTI_PRIVATE struct DDS_TypePlugin*
opendds_wrapper_BuiltinUint64TypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property);
RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinUint64TypePlugin_delete_plugin(struct DDS_TypePlugin *plugin);

RTI_PRIVATE struct DDS_TypePluginI opendds_wrapper_BuiltinUint64_fv_TypePluginI =
{
    /**************************************************************************
    *                   Type information functions
    **************************************************************************/

    NULL,                       /* DDS_TypeCode_t* */
    NDDS_TYPEPLUGIN_NO_KEY,     /* NDDS_TypePluginKeyKind */

    NDDS_TYPEPLUGIN_EH_LOCATION_PAYLOAD,
    opendds_wrapper_BuiltinUint64_get_user_sample_size,   
    RTI_MEMORY_TYPE_HEAP,
    NULL,
    opendds_wrapper_BuiltinUint64Plugin_copy_sample,

    opendds_wrapper_BuiltinUint64TypePlugin_initialize_sample,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    opendds_wrapper_BuiltinUint64_fv_MemoryPlugins,
    opendds_wrapper_BuiltinUint64_fv_WirePlugins,

    /**************************************************************************
    *       Helper APIs to create language binding wrapper Functions
    **************************************************************************/

    opendds_wrapper_BuiltinUint64Plugin_create_typed_datawriter,
    #ifndef RTI_CERT
    opendds_wrapper_BuiltinUint64Plugin_delete_typed_datawriter,
    #else
    NULL,
    #endif
    opendds_wrapper_BuiltinUint64Plugin_create_typed_datareader,
    #ifndef RTI_CERT
    opendds_wrapper_BuiltinUint64Plugin_delete_typed_datareader,
    #else
    NULL,
    #endif
    opendds_wrapper_BuiltinUint64TypePlugin_create_plugin,
    opendds_wrapper_BuiltinUint64TypePlugin_delete_plugin,
    opendds_wrapper_BuiltinUint64_on_type_registered,
    opendds_wrapper_BuiltinUint64_on_type_unregistered,

};

/* --------------------------------------------------------------------------
*  Type opendds_wrapper_BuiltinUint64 Plugin Methods
* -------------------------------------------------------------------------- */

struct DDS_TypePluginI*
opendds_wrapper_BuiltinUint64TypePlugin_get(void) 
{ 
    return &opendds_wrapper_BuiltinUint64_fv_TypePluginI;
} 

RTI_PRIVATE struct DDS_TypePlugin*
opendds_wrapper_BuiltinUint64TypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property)
{
    return DDS_TypePluginDefault_create(&opendds_wrapper_BuiltinUint64_fv_TypePluginI,
    participant,dp_qos,
    endpoint_mode,endpoint,qos,
    property);
}

RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinUint64TypePlugin_delete_plugin(struct DDS_TypePlugin *plugin)
{
    return DDS_TypePluginDefault_delete(plugin);
}

struct DDS_TypePlugin*
opendds_wrapper_BuiltinUint64WriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &opendds_wrapper_BuiltinUint64_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_WRITER,
        (DDS_TypePluginEndpoint*)writer,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

struct DDS_TypePlugin*
opendds_wrapper_BuiltinUint64ReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &opendds_wrapper_BuiltinUint64_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_READER,
        (DDS_TypePluginEndpoint*)reader,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

const char*
opendds_wrapper_BuiltinUint64TypePlugin_get_default_type_name(void) 
{ 
    return opendds_wrapper_BuiltinUint64TYPENAME;
} 

NDDS_TypePluginKeyKind 
opendds_wrapper_BuiltinUint64I_get_key_kind(void)
{
    return opendds_wrapper_BuiltinUint64_fv_TypePluginI.key_kind;
}

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------
Typed-endpoint support for C++:
* -------------------------------------------------------------------------- */

void* 
opendds_wrapper_BuiltinFloat32Plugin_create_typed_datawriter(void *writer)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * so writer is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataWriter *cpp_writer = 
    new opendds_wrapper_BuiltinFloat32DataWriter((DDS_DataWriter*)writer);

    return cpp_writer;   
}

#ifndef RTI_CERT
void 
opendds_wrapper_BuiltinFloat32Plugin_delete_typed_datawriter(void *wrapper)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * and DDS_Publisher_delete_datawriter so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataWriter_impl *cpp_writer = (DDSDataWriter_impl *) wrapper;

    opendds_wrapper_BuiltinFloat32DataWriter *t_writer = 
    static_cast<opendds_wrapper_BuiltinFloat32DataWriter *>(cpp_writer);

    delete t_writer;
}
#endif

void* 
opendds_wrapper_BuiltinFloat32Plugin_create_typed_datareader(void *reader)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * so reader is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataReader *cpp_reader = 
    new opendds_wrapper_BuiltinFloat32DataReader((DDS_DataReader*)reader);

    return cpp_reader;      
}

#ifndef RTI_CERT
void
opendds_wrapper_BuiltinFloat32Plugin_delete_typed_datareader(void *wrapper)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * and DDS_Subscriber_delete_datareader so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataReader_impl *cpp_reader = (DDSDataReader_impl *) wrapper;

    opendds_wrapper_BuiltinFloat32DataReader *t_reader = 
    static_cast<opendds_wrapper_BuiltinFloat32DataReader *>(cpp_reader);

    delete t_reader;
}
#endif

/* --------------------------------------------------------------------------
*  Sample Support functions:
* -------------------------------------------------------------------------- */
RTI_BOOL
opendds_wrapper_BuiltinFloat32Plugin_create_sample(struct DDS_TypePlugin *plugin,
void **sample)
{
    UNUSED_ARG(plugin);

    *sample = (void *) opendds_wrapper_BuiltinFloat32_create();
    return (*sample != NULL);
}

#ifndef RTI_CERT
RTI_BOOL
opendds_wrapper_BuiltinFloat32Plugin_delete_sample(struct DDS_TypePlugin *plugin, 
void *sample)
{
    UNUSED_ARG(plugin);

    opendds_wrapper_BuiltinFloat32_delete((opendds_wrapper_BuiltinFloat32 *) sample);
    return RTI_TRUE;
}
#endif

RTI_BOOL 
opendds_wrapper_BuiltinFloat32Plugin_copy_sample(struct DDS_TypePlugin *plugin, 
void *dst, 
const void *src)
{
    UNUSED_ARG(plugin);

    return opendds_wrapper_BuiltinFloat32_copy(
        (opendds_wrapper_BuiltinFloat32*)dst,
        (const opendds_wrapper_BuiltinFloat32*)src);
}
/* --------------------------------------------------------------------------
*  Type opendds_wrapper_BuiltinFloat32 Plugin Instantiation
* -------------------------------------------------------------------------- */

NDDSCDREncapsulation opendds_wrapper_BuiltinFloat32EncapsulationKind[] =
{ 
    {
        DDS_ENCAPSULATION_ID_CDR_LE,
        DDS_ENCAPSULATION_ID_CDR_BE,
        0
    }
};

NDDSCDREncapsulation opendds_wrapper_BuiltinFloat32V2EncapsulationKind[] =
{ 
    {

        DDS_ENCAPSULATION_ID_XCDR2_A_LE,
        DDS_ENCAPSULATION_ID_XCDR2_A_BE,
        0

    }
};

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinFloat32TypePlugin_initialize_sample(struct DDS_TypePlugin *plugin, void *buffer)
{
    UNUSED_ARG(plugin);
    return opendds_wrapper_BuiltinFloat32_initialize((opendds_wrapper_BuiltinFloat32*)buffer);
}

RTI_PRIVATE RTI_UINT32 
opendds_wrapper_BuiltinFloat32_get_user_sample_size(
    struct DDS_TypePlugin *tp)
{
    UNUSED_ARG(tp);        
    return sizeof(opendds_wrapper_BuiltinFloat32);
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinFloat32_cdr_initialize(void *init_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)init_config;
    void *sample;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!opendds_wrapper_BuiltinFloat32Plugin_create_sample(&plugin->_parent,&sample))
    {
        return RTI_FALSE;
    }

    sh->sample = sample;

    return RTI_TRUE;
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinFloat32_cdr_finalize(void *finalize_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)finalize_config;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!opendds_wrapper_BuiltinFloat32Plugin_delete_sample(&plugin->_parent,sh->sample))
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

RTI_PRIVATE void 
opendds_wrapper_BuiltinFloat32TypePlugin_return_sample(
    struct DDS_TypePlugin *tp,
    struct DDS_TypePluginSampleHolder *sample)
{
    opendds_wrapper_BuiltinFloat32_finalize_optional_members((opendds_wrapper_BuiltinFloat32*)sample->sample, RTI_FALSE);
    XCDR_GenericStreamPlugin_return_sample(tp, sample);
}

RTI_PRIVATE struct DDS_TypeMemoryPlugin*
opendds_wrapper_BuiltinFloat32XTypesHeapPlugin_create(struct DDS_TypePlugin *tp,
DDS_DomainParticipant *participant,
struct DDS_DomainParticipantQos *dp_qos,
DDS_TypePluginMode_T endpoint_mode,
DDS_TypePluginEndpoint *endpoint,
DDS_TypePluginEndpointQos *qos)
{
    return DDS_XTypesHeapPlugin_create(
        tp,
        participant,
        dp_qos,
        endpoint_mode,
        endpoint,
        qos,
        NULL,
        NULL,
        opendds_wrapper_BuiltinFloat32_cdr_initialize,
        opendds_wrapper_BuiltinFloat32_cdr_finalize,
        sizeof(opendds_wrapper_BuiltinFloat32),
        RTI_FALSE
        );
}

RTI_PRIVATE struct DDS_TypeMemoryI opendds_wrapper_BuiltinFloat32_fv_XTypesHeapPluginI =
{
    RTI_MEMORY_MANAGER_HEAP,
    RTI_MEMORY_TYPE_HEAP,
    opendds_wrapper_BuiltinFloat32Plugin_create_sample,
    #ifndef RTI_CERT
    opendds_wrapper_BuiltinFloat32Plugin_delete_sample,
    #else
    NULL,
    #endif
    NULL, /* get_address */
    NULL, /* return_address */
    NULL,
    DDS_XTypesHeapPlugin_get_sample_state,
    DDS_XTypesHeapPlugin_set_sample_state,
    DDS_XTypesHeapPlugin_is_owner,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    opendds_wrapper_BuiltinFloat32XTypesHeapPlugin_create,
    DDS_XTypesHeapPlugin_delete
};	

RTI_PRIVATE DDS_Boolean 
opendds_wrapper_BuiltinFloat32_on_type_registered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    struct RTIXCdrInterpreterProgramsGenProperty programProperty =
    RTIXCdrInterpreterProgramsGenProperty_INITIALIZER;

    programProperty.resolveAlias = RTI_XCDR_TRUE;
    programProperty.inlineStruct = RTI_XCDR_TRUE;
    programProperty.optimizeEnum = RTI_XCDR_TRUE;

    programs = RTIXCdrInterpreterPrograms_new(
        (RTIXCdrTypeCode *)opendds_wrapper_BuiltinFloat32_get_typecode(),
        &programProperty,
        RTI_XCDR_PROGRAM_MASK_TYPEPLUGIN
        );

    if (programs == NULL)
    {
        return DDS_BOOLEAN_FALSE;
    }

    DDS_TypeImpl_set_programs(type_impl, programs);
    DDS_TypeImpl_set_typecode(type_impl,  opendds_wrapper_BuiltinFloat32_get_typecode());

    return DDS_BOOLEAN_TRUE;
}
RTI_PRIVATE DDS_Boolean 
opendds_wrapper_BuiltinFloat32_on_type_unregistered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    programs = DDS_TypeImpl_get_programs(type_impl);

    if (programs != NULL) 
    {
        RTIXCdrInterpreterPrograms_delete(programs);
    }
    DDS_TypeImpl_set_programs(type_impl, NULL); 

    return DDS_BOOLEAN_TRUE;   
}

RTI_PRIVATE 
struct DDS_TypeEncapsulationI opendds_wrapper_BuiltinFloat32_fv_XCDRv1PluginI =
{
    DDS_XCDR_DATA_REPRESENTATION,
    NULL,
    opendds_wrapper_BuiltinFloat32EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,
    opendds_wrapper_BuiltinFloat32TypePlugin_return_sample,
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv1_StreamPlugin_get_serialized_sample_size,
    XCDRv1_StreamPlugin_create,
    XCDRv1_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI opendds_wrapper_BuiltinFloat32_fv_XCDRv2PluginI =
{
    DDS_XCDR2_DATA_REPRESENTATION,
    NULL,
    opendds_wrapper_BuiltinFloat32V2EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,

    opendds_wrapper_BuiltinFloat32TypePlugin_return_sample,   
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv2_StreamPlugin_get_serialized_sample_size,
    XCDRv2_StreamPlugin_create,
    XCDRv2_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI *opendds_wrapper_BuiltinFloat32_fv_WirePlugins[] =
{
    &opendds_wrapper_BuiltinFloat32_fv_XCDRv2PluginI,
    &opendds_wrapper_BuiltinFloat32_fv_XCDRv1PluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypeMemoryI *opendds_wrapper_BuiltinFloat32_fv_MemoryPlugins[] =
{
    &opendds_wrapper_BuiltinFloat32_fv_XTypesHeapPluginI,

    NULL
};

RTI_PRIVATE struct DDS_TypePlugin*
opendds_wrapper_BuiltinFloat32TypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property);
RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinFloat32TypePlugin_delete_plugin(struct DDS_TypePlugin *plugin);

RTI_PRIVATE struct DDS_TypePluginI opendds_wrapper_BuiltinFloat32_fv_TypePluginI =
{
    /**************************************************************************
    *                   Type information functions
    **************************************************************************/

    NULL,                       /* DDS_TypeCode_t* */
    NDDS_TYPEPLUGIN_NO_KEY,     /* NDDS_TypePluginKeyKind */

    NDDS_TYPEPLUGIN_EH_LOCATION_PAYLOAD,
    opendds_wrapper_BuiltinFloat32_get_user_sample_size,   
    RTI_MEMORY_TYPE_HEAP,
    NULL,
    opendds_wrapper_BuiltinFloat32Plugin_copy_sample,

    opendds_wrapper_BuiltinFloat32TypePlugin_initialize_sample,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    opendds_wrapper_BuiltinFloat32_fv_MemoryPlugins,
    opendds_wrapper_BuiltinFloat32_fv_WirePlugins,

    /**************************************************************************
    *       Helper APIs to create language binding wrapper Functions
    **************************************************************************/

    opendds_wrapper_BuiltinFloat32Plugin_create_typed_datawriter,
    #ifndef RTI_CERT
    opendds_wrapper_BuiltinFloat32Plugin_delete_typed_datawriter,
    #else
    NULL,
    #endif
    opendds_wrapper_BuiltinFloat32Plugin_create_typed_datareader,
    #ifndef RTI_CERT
    opendds_wrapper_BuiltinFloat32Plugin_delete_typed_datareader,
    #else
    NULL,
    #endif
    opendds_wrapper_BuiltinFloat32TypePlugin_create_plugin,
    opendds_wrapper_BuiltinFloat32TypePlugin_delete_plugin,
    opendds_wrapper_BuiltinFloat32_on_type_registered,
    opendds_wrapper_BuiltinFloat32_on_type_unregistered,

};

/* --------------------------------------------------------------------------
*  Type opendds_wrapper_BuiltinFloat32 Plugin Methods
* -------------------------------------------------------------------------- */

struct DDS_TypePluginI*
opendds_wrapper_BuiltinFloat32TypePlugin_get(void) 
{ 
    return &opendds_wrapper_BuiltinFloat32_fv_TypePluginI;
} 

RTI_PRIVATE struct DDS_TypePlugin*
opendds_wrapper_BuiltinFloat32TypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property)
{
    return DDS_TypePluginDefault_create(&opendds_wrapper_BuiltinFloat32_fv_TypePluginI,
    participant,dp_qos,
    endpoint_mode,endpoint,qos,
    property);
}

RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinFloat32TypePlugin_delete_plugin(struct DDS_TypePlugin *plugin)
{
    return DDS_TypePluginDefault_delete(plugin);
}

struct DDS_TypePlugin*
opendds_wrapper_BuiltinFloat32WriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &opendds_wrapper_BuiltinFloat32_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_WRITER,
        (DDS_TypePluginEndpoint*)writer,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

struct DDS_TypePlugin*
opendds_wrapper_BuiltinFloat32ReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &opendds_wrapper_BuiltinFloat32_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_READER,
        (DDS_TypePluginEndpoint*)reader,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

const char*
opendds_wrapper_BuiltinFloat32TypePlugin_get_default_type_name(void) 
{ 
    return opendds_wrapper_BuiltinFloat32TYPENAME;
} 

NDDS_TypePluginKeyKind 
opendds_wrapper_BuiltinFloat32I_get_key_kind(void)
{
    return opendds_wrapper_BuiltinFloat32_fv_TypePluginI.key_kind;
}

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------
Typed-endpoint support for C++:
* -------------------------------------------------------------------------- */

void* 
opendds_wrapper_BuiltinFloat64Plugin_create_typed_datawriter(void *writer)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * so writer is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataWriter *cpp_writer = 
    new opendds_wrapper_BuiltinFloat64DataWriter((DDS_DataWriter*)writer);

    return cpp_writer;   
}

#ifndef RTI_CERT
void 
opendds_wrapper_BuiltinFloat64Plugin_delete_typed_datawriter(void *wrapper)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * and DDS_Publisher_delete_datawriter so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataWriter_impl *cpp_writer = (DDSDataWriter_impl *) wrapper;

    opendds_wrapper_BuiltinFloat64DataWriter *t_writer = 
    static_cast<opendds_wrapper_BuiltinFloat64DataWriter *>(cpp_writer);

    delete t_writer;
}
#endif

void* 
opendds_wrapper_BuiltinFloat64Plugin_create_typed_datareader(void *reader)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * so reader is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataReader *cpp_reader = 
    new opendds_wrapper_BuiltinFloat64DataReader((DDS_DataReader*)reader);

    return cpp_reader;      
}

#ifndef RTI_CERT
void
opendds_wrapper_BuiltinFloat64Plugin_delete_typed_datareader(void *wrapper)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * and DDS_Subscriber_delete_datareader so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataReader_impl *cpp_reader = (DDSDataReader_impl *) wrapper;

    opendds_wrapper_BuiltinFloat64DataReader *t_reader = 
    static_cast<opendds_wrapper_BuiltinFloat64DataReader *>(cpp_reader);

    delete t_reader;
}
#endif

/* --------------------------------------------------------------------------
*  Sample Support functions:
* -------------------------------------------------------------------------- */
RTI_BOOL
opendds_wrapper_BuiltinFloat64Plugin_create_sample(struct DDS_TypePlugin *plugin,
void **sample)
{
    UNUSED_ARG(plugin);

    *sample = (void *) opendds_wrapper_BuiltinFloat64_create();
    return (*sample != NULL);
}

#ifndef RTI_CERT
RTI_BOOL
opendds_wrapper_BuiltinFloat64Plugin_delete_sample(struct DDS_TypePlugin *plugin, 
void *sample)
{
    UNUSED_ARG(plugin);

    opendds_wrapper_BuiltinFloat64_delete((opendds_wrapper_BuiltinFloat64 *) sample);
    return RTI_TRUE;
}
#endif

RTI_BOOL 
opendds_wrapper_BuiltinFloat64Plugin_copy_sample(struct DDS_TypePlugin *plugin, 
void *dst, 
const void *src)
{
    UNUSED_ARG(plugin);

    return opendds_wrapper_BuiltinFloat64_copy(
        (opendds_wrapper_BuiltinFloat64*)dst,
        (const opendds_wrapper_BuiltinFloat64*)src);
}
/* --------------------------------------------------------------------------
*  Type opendds_wrapper_BuiltinFloat64 Plugin Instantiation
* -------------------------------------------------------------------------- */

NDDSCDREncapsulation opendds_wrapper_BuiltinFloat64EncapsulationKind[] =
{ 
    {
        DDS_ENCAPSULATION_ID_CDR_LE,
        DDS_ENCAPSULATION_ID_CDR_BE,
        0
    }
};

NDDSCDREncapsulation opendds_wrapper_BuiltinFloat64V2EncapsulationKind[] =
{ 
    {

        DDS_ENCAPSULATION_ID_XCDR2_A_LE,
        DDS_ENCAPSULATION_ID_XCDR2_A_BE,
        0

    }
};

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinFloat64TypePlugin_initialize_sample(struct DDS_TypePlugin *plugin, void *buffer)
{
    UNUSED_ARG(plugin);
    return opendds_wrapper_BuiltinFloat64_initialize((opendds_wrapper_BuiltinFloat64*)buffer);
}

RTI_PRIVATE RTI_UINT32 
opendds_wrapper_BuiltinFloat64_get_user_sample_size(
    struct DDS_TypePlugin *tp)
{
    UNUSED_ARG(tp);        
    return sizeof(opendds_wrapper_BuiltinFloat64);
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinFloat64_cdr_initialize(void *init_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)init_config;
    void *sample;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!opendds_wrapper_BuiltinFloat64Plugin_create_sample(&plugin->_parent,&sample))
    {
        return RTI_FALSE;
    }

    sh->sample = sample;

    return RTI_TRUE;
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinFloat64_cdr_finalize(void *finalize_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)finalize_config;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!opendds_wrapper_BuiltinFloat64Plugin_delete_sample(&plugin->_parent,sh->sample))
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

RTI_PRIVATE void 
opendds_wrapper_BuiltinFloat64TypePlugin_return_sample(
    struct DDS_TypePlugin *tp,
    struct DDS_TypePluginSampleHolder *sample)
{
    opendds_wrapper_BuiltinFloat64_finalize_optional_members((opendds_wrapper_BuiltinFloat64*)sample->sample, RTI_FALSE);
    XCDR_GenericStreamPlugin_return_sample(tp, sample);
}

RTI_PRIVATE struct DDS_TypeMemoryPlugin*
opendds_wrapper_BuiltinFloat64XTypesHeapPlugin_create(struct DDS_TypePlugin *tp,
DDS_DomainParticipant *participant,
struct DDS_DomainParticipantQos *dp_qos,
DDS_TypePluginMode_T endpoint_mode,
DDS_TypePluginEndpoint *endpoint,
DDS_TypePluginEndpointQos *qos)
{
    return DDS_XTypesHeapPlugin_create(
        tp,
        participant,
        dp_qos,
        endpoint_mode,
        endpoint,
        qos,
        NULL,
        NULL,
        opendds_wrapper_BuiltinFloat64_cdr_initialize,
        opendds_wrapper_BuiltinFloat64_cdr_finalize,
        sizeof(opendds_wrapper_BuiltinFloat64),
        RTI_FALSE
        );
}

RTI_PRIVATE struct DDS_TypeMemoryI opendds_wrapper_BuiltinFloat64_fv_XTypesHeapPluginI =
{
    RTI_MEMORY_MANAGER_HEAP,
    RTI_MEMORY_TYPE_HEAP,
    opendds_wrapper_BuiltinFloat64Plugin_create_sample,
    #ifndef RTI_CERT
    opendds_wrapper_BuiltinFloat64Plugin_delete_sample,
    #else
    NULL,
    #endif
    NULL, /* get_address */
    NULL, /* return_address */
    NULL,
    DDS_XTypesHeapPlugin_get_sample_state,
    DDS_XTypesHeapPlugin_set_sample_state,
    DDS_XTypesHeapPlugin_is_owner,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    opendds_wrapper_BuiltinFloat64XTypesHeapPlugin_create,
    DDS_XTypesHeapPlugin_delete
};	

RTI_PRIVATE DDS_Boolean 
opendds_wrapper_BuiltinFloat64_on_type_registered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    struct RTIXCdrInterpreterProgramsGenProperty programProperty =
    RTIXCdrInterpreterProgramsGenProperty_INITIALIZER;

    programProperty.resolveAlias = RTI_XCDR_TRUE;
    programProperty.inlineStruct = RTI_XCDR_TRUE;
    programProperty.optimizeEnum = RTI_XCDR_TRUE;

    programs = RTIXCdrInterpreterPrograms_new(
        (RTIXCdrTypeCode *)opendds_wrapper_BuiltinFloat64_get_typecode(),
        &programProperty,
        RTI_XCDR_PROGRAM_MASK_TYPEPLUGIN
        );

    if (programs == NULL)
    {
        return DDS_BOOLEAN_FALSE;
    }

    DDS_TypeImpl_set_programs(type_impl, programs);
    DDS_TypeImpl_set_typecode(type_impl,  opendds_wrapper_BuiltinFloat64_get_typecode());

    return DDS_BOOLEAN_TRUE;
}
RTI_PRIVATE DDS_Boolean 
opendds_wrapper_BuiltinFloat64_on_type_unregistered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    programs = DDS_TypeImpl_get_programs(type_impl);

    if (programs != NULL) 
    {
        RTIXCdrInterpreterPrograms_delete(programs);
    }
    DDS_TypeImpl_set_programs(type_impl, NULL); 

    return DDS_BOOLEAN_TRUE;   
}

RTI_PRIVATE 
struct DDS_TypeEncapsulationI opendds_wrapper_BuiltinFloat64_fv_XCDRv1PluginI =
{
    DDS_XCDR_DATA_REPRESENTATION,
    NULL,
    opendds_wrapper_BuiltinFloat64EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,
    opendds_wrapper_BuiltinFloat64TypePlugin_return_sample,
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv1_StreamPlugin_get_serialized_sample_size,
    XCDRv1_StreamPlugin_create,
    XCDRv1_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI opendds_wrapper_BuiltinFloat64_fv_XCDRv2PluginI =
{
    DDS_XCDR2_DATA_REPRESENTATION,
    NULL,
    opendds_wrapper_BuiltinFloat64V2EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,

    opendds_wrapper_BuiltinFloat64TypePlugin_return_sample,   
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv2_StreamPlugin_get_serialized_sample_size,
    XCDRv2_StreamPlugin_create,
    XCDRv2_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI *opendds_wrapper_BuiltinFloat64_fv_WirePlugins[] =
{
    &opendds_wrapper_BuiltinFloat64_fv_XCDRv2PluginI,
    &opendds_wrapper_BuiltinFloat64_fv_XCDRv1PluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypeMemoryI *opendds_wrapper_BuiltinFloat64_fv_MemoryPlugins[] =
{
    &opendds_wrapper_BuiltinFloat64_fv_XTypesHeapPluginI,

    NULL
};

RTI_PRIVATE struct DDS_TypePlugin*
opendds_wrapper_BuiltinFloat64TypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property);
RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinFloat64TypePlugin_delete_plugin(struct DDS_TypePlugin *plugin);

RTI_PRIVATE struct DDS_TypePluginI opendds_wrapper_BuiltinFloat64_fv_TypePluginI =
{
    /**************************************************************************
    *                   Type information functions
    **************************************************************************/

    NULL,                       /* DDS_TypeCode_t* */
    NDDS_TYPEPLUGIN_NO_KEY,     /* NDDS_TypePluginKeyKind */

    NDDS_TYPEPLUGIN_EH_LOCATION_PAYLOAD,
    opendds_wrapper_BuiltinFloat64_get_user_sample_size,   
    RTI_MEMORY_TYPE_HEAP,
    NULL,
    opendds_wrapper_BuiltinFloat64Plugin_copy_sample,

    opendds_wrapper_BuiltinFloat64TypePlugin_initialize_sample,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    opendds_wrapper_BuiltinFloat64_fv_MemoryPlugins,
    opendds_wrapper_BuiltinFloat64_fv_WirePlugins,

    /**************************************************************************
    *       Helper APIs to create language binding wrapper Functions
    **************************************************************************/

    opendds_wrapper_BuiltinFloat64Plugin_create_typed_datawriter,
    #ifndef RTI_CERT
    opendds_wrapper_BuiltinFloat64Plugin_delete_typed_datawriter,
    #else
    NULL,
    #endif
    opendds_wrapper_BuiltinFloat64Plugin_create_typed_datareader,
    #ifndef RTI_CERT
    opendds_wrapper_BuiltinFloat64Plugin_delete_typed_datareader,
    #else
    NULL,
    #endif
    opendds_wrapper_BuiltinFloat64TypePlugin_create_plugin,
    opendds_wrapper_BuiltinFloat64TypePlugin_delete_plugin,
    opendds_wrapper_BuiltinFloat64_on_type_registered,
    opendds_wrapper_BuiltinFloat64_on_type_unregistered,

};

/* --------------------------------------------------------------------------
*  Type opendds_wrapper_BuiltinFloat64 Plugin Methods
* -------------------------------------------------------------------------- */

struct DDS_TypePluginI*
opendds_wrapper_BuiltinFloat64TypePlugin_get(void) 
{ 
    return &opendds_wrapper_BuiltinFloat64_fv_TypePluginI;
} 

RTI_PRIVATE struct DDS_TypePlugin*
opendds_wrapper_BuiltinFloat64TypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property)
{
    return DDS_TypePluginDefault_create(&opendds_wrapper_BuiltinFloat64_fv_TypePluginI,
    participant,dp_qos,
    endpoint_mode,endpoint,qos,
    property);
}

RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinFloat64TypePlugin_delete_plugin(struct DDS_TypePlugin *plugin)
{
    return DDS_TypePluginDefault_delete(plugin);
}

struct DDS_TypePlugin*
opendds_wrapper_BuiltinFloat64WriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &opendds_wrapper_BuiltinFloat64_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_WRITER,
        (DDS_TypePluginEndpoint*)writer,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

struct DDS_TypePlugin*
opendds_wrapper_BuiltinFloat64ReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &opendds_wrapper_BuiltinFloat64_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_READER,
        (DDS_TypePluginEndpoint*)reader,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

const char*
opendds_wrapper_BuiltinFloat64TypePlugin_get_default_type_name(void) 
{ 
    return opendds_wrapper_BuiltinFloat64TYPENAME;
} 

NDDS_TypePluginKeyKind 
opendds_wrapper_BuiltinFloat64I_get_key_kind(void)
{
    return opendds_wrapper_BuiltinFloat64_fv_TypePluginI.key_kind;
}

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------
Typed-endpoint support for C++:
* -------------------------------------------------------------------------- */

void* 
opendds_wrapper_BuiltinStringPlugin_create_typed_datawriter(void *writer)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * so writer is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataWriter *cpp_writer = 
    new opendds_wrapper_BuiltinStringDataWriter((DDS_DataWriter*)writer);

    return cpp_writer;   
}

#ifndef RTI_CERT
void 
opendds_wrapper_BuiltinStringPlugin_delete_typed_datawriter(void *wrapper)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * and DDS_Publisher_delete_datawriter so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataWriter_impl *cpp_writer = (DDSDataWriter_impl *) wrapper;

    opendds_wrapper_BuiltinStringDataWriter *t_writer = 
    static_cast<opendds_wrapper_BuiltinStringDataWriter *>(cpp_writer);

    delete t_writer;
}
#endif

void* 
opendds_wrapper_BuiltinStringPlugin_create_typed_datareader(void *reader)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * so reader is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataReader *cpp_reader = 
    new opendds_wrapper_BuiltinStringDataReader((DDS_DataReader*)reader);

    return cpp_reader;      
}

#ifndef RTI_CERT
void
opendds_wrapper_BuiltinStringPlugin_delete_typed_datareader(void *wrapper)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * and DDS_Subscriber_delete_datareader so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataReader_impl *cpp_reader = (DDSDataReader_impl *) wrapper;

    opendds_wrapper_BuiltinStringDataReader *t_reader = 
    static_cast<opendds_wrapper_BuiltinStringDataReader *>(cpp_reader);

    delete t_reader;
}
#endif

/* --------------------------------------------------------------------------
*  Sample Support functions:
* -------------------------------------------------------------------------- */
RTI_BOOL
opendds_wrapper_BuiltinStringPlugin_create_sample(struct DDS_TypePlugin *plugin,
void **sample)
{
    UNUSED_ARG(plugin);

    *sample = (void *) opendds_wrapper_BuiltinString_create();
    return (*sample != NULL);
}

#ifndef RTI_CERT
RTI_BOOL
opendds_wrapper_BuiltinStringPlugin_delete_sample(struct DDS_TypePlugin *plugin, 
void *sample)
{
    UNUSED_ARG(plugin);

    opendds_wrapper_BuiltinString_delete((opendds_wrapper_BuiltinString *) sample);
    return RTI_TRUE;
}
#endif

RTI_BOOL 
opendds_wrapper_BuiltinStringPlugin_copy_sample(struct DDS_TypePlugin *plugin, 
void *dst, 
const void *src)
{
    UNUSED_ARG(plugin);

    return opendds_wrapper_BuiltinString_copy(
        (opendds_wrapper_BuiltinString*)dst,
        (const opendds_wrapper_BuiltinString*)src);
}
/* --------------------------------------------------------------------------
*  Type opendds_wrapper_BuiltinString Plugin Instantiation
* -------------------------------------------------------------------------- */

NDDSCDREncapsulation opendds_wrapper_BuiltinStringEncapsulationKind[] =
{ 
    {
        DDS_ENCAPSULATION_ID_CDR_LE,
        DDS_ENCAPSULATION_ID_CDR_BE,
        0
    }
};

NDDSCDREncapsulation opendds_wrapper_BuiltinStringV2EncapsulationKind[] =
{ 
    {

        DDS_ENCAPSULATION_ID_XCDR2_A_LE,
        DDS_ENCAPSULATION_ID_XCDR2_A_BE,
        0

    }
};

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinStringTypePlugin_initialize_sample(struct DDS_TypePlugin *plugin, void *buffer)
{
    UNUSED_ARG(plugin);
    return opendds_wrapper_BuiltinString_initialize((opendds_wrapper_BuiltinString*)buffer);
}

RTI_PRIVATE RTI_UINT32 
opendds_wrapper_BuiltinString_get_user_sample_size(
    struct DDS_TypePlugin *tp)
{
    UNUSED_ARG(tp);        
    return sizeof(opendds_wrapper_BuiltinString);
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinString_cdr_initialize(void *init_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)init_config;
    void *sample;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!opendds_wrapper_BuiltinStringPlugin_create_sample(&plugin->_parent,&sample))
    {
        return RTI_FALSE;
    }

    sh->sample = sample;

    return RTI_TRUE;
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinString_cdr_finalize(void *finalize_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)finalize_config;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!opendds_wrapper_BuiltinStringPlugin_delete_sample(&plugin->_parent,sh->sample))
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

RTI_PRIVATE void 
opendds_wrapper_BuiltinStringTypePlugin_return_sample(
    struct DDS_TypePlugin *tp,
    struct DDS_TypePluginSampleHolder *sample)
{
    opendds_wrapper_BuiltinString_finalize_optional_members((opendds_wrapper_BuiltinString*)sample->sample, RTI_FALSE);
    XCDR_GenericStreamPlugin_return_sample(tp, sample);
}

RTI_PRIVATE struct DDS_TypeMemoryPlugin*
opendds_wrapper_BuiltinStringXTypesHeapPlugin_create(struct DDS_TypePlugin *tp,
DDS_DomainParticipant *participant,
struct DDS_DomainParticipantQos *dp_qos,
DDS_TypePluginMode_T endpoint_mode,
DDS_TypePluginEndpoint *endpoint,
DDS_TypePluginEndpointQos *qos)
{
    return DDS_XTypesHeapPlugin_create(
        tp,
        participant,
        dp_qos,
        endpoint_mode,
        endpoint,
        qos,
        NULL,
        NULL,
        opendds_wrapper_BuiltinString_cdr_initialize,
        opendds_wrapper_BuiltinString_cdr_finalize,
        sizeof(opendds_wrapper_BuiltinString),
        RTI_FALSE
        );
}

RTI_PRIVATE struct DDS_TypeMemoryI opendds_wrapper_BuiltinString_fv_XTypesHeapPluginI =
{
    RTI_MEMORY_MANAGER_HEAP,
    RTI_MEMORY_TYPE_HEAP,
    opendds_wrapper_BuiltinStringPlugin_create_sample,
    #ifndef RTI_CERT
    opendds_wrapper_BuiltinStringPlugin_delete_sample,
    #else
    NULL,
    #endif
    NULL, /* get_address */
    NULL, /* return_address */
    NULL,
    DDS_XTypesHeapPlugin_get_sample_state,
    DDS_XTypesHeapPlugin_set_sample_state,
    DDS_XTypesHeapPlugin_is_owner,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    opendds_wrapper_BuiltinStringXTypesHeapPlugin_create,
    DDS_XTypesHeapPlugin_delete
};	

RTI_PRIVATE DDS_Boolean 
opendds_wrapper_BuiltinString_on_type_registered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    struct RTIXCdrInterpreterProgramsGenProperty programProperty =
    RTIXCdrInterpreterProgramsGenProperty_INITIALIZER;

    programProperty.resolveAlias = RTI_XCDR_TRUE;
    programProperty.inlineStruct = RTI_XCDR_TRUE;
    programProperty.optimizeEnum = RTI_XCDR_TRUE;

    programs = RTIXCdrInterpreterPrograms_new(
        (RTIXCdrTypeCode *)opendds_wrapper_BuiltinString_get_typecode(),
        &programProperty,
        RTI_XCDR_PROGRAM_MASK_TYPEPLUGIN
        );

    if (programs == NULL)
    {
        return DDS_BOOLEAN_FALSE;
    }

    DDS_TypeImpl_set_programs(type_impl, programs);
    DDS_TypeImpl_set_typecode(type_impl,  opendds_wrapper_BuiltinString_get_typecode());

    return DDS_BOOLEAN_TRUE;
}
RTI_PRIVATE DDS_Boolean 
opendds_wrapper_BuiltinString_on_type_unregistered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    programs = DDS_TypeImpl_get_programs(type_impl);

    if (programs != NULL) 
    {
        RTIXCdrInterpreterPrograms_delete(programs);
    }
    DDS_TypeImpl_set_programs(type_impl, NULL); 

    return DDS_BOOLEAN_TRUE;   
}

RTI_PRIVATE 
struct DDS_TypeEncapsulationI opendds_wrapper_BuiltinString_fv_XCDRv1PluginI =
{
    DDS_XCDR_DATA_REPRESENTATION,
    NULL,
    opendds_wrapper_BuiltinStringEncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,
    opendds_wrapper_BuiltinStringTypePlugin_return_sample,
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv1_StreamPlugin_get_serialized_sample_size,
    XCDRv1_StreamPlugin_create,
    XCDRv1_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI opendds_wrapper_BuiltinString_fv_XCDRv2PluginI =
{
    DDS_XCDR2_DATA_REPRESENTATION,
    NULL,
    opendds_wrapper_BuiltinStringV2EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,

    opendds_wrapper_BuiltinStringTypePlugin_return_sample,   
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv2_StreamPlugin_get_serialized_sample_size,
    XCDRv2_StreamPlugin_create,
    XCDRv2_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI *opendds_wrapper_BuiltinString_fv_WirePlugins[] =
{
    &opendds_wrapper_BuiltinString_fv_XCDRv2PluginI,
    &opendds_wrapper_BuiltinString_fv_XCDRv1PluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypeMemoryI *opendds_wrapper_BuiltinString_fv_MemoryPlugins[] =
{
    &opendds_wrapper_BuiltinString_fv_XTypesHeapPluginI,

    NULL
};

RTI_PRIVATE struct DDS_TypePlugin*
opendds_wrapper_BuiltinStringTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property);
RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinStringTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin);

RTI_PRIVATE struct DDS_TypePluginI opendds_wrapper_BuiltinString_fv_TypePluginI =
{
    /**************************************************************************
    *                   Type information functions
    **************************************************************************/

    NULL,                       /* DDS_TypeCode_t* */
    NDDS_TYPEPLUGIN_NO_KEY,     /* NDDS_TypePluginKeyKind */

    NDDS_TYPEPLUGIN_EH_LOCATION_PAYLOAD,
    opendds_wrapper_BuiltinString_get_user_sample_size,   
    RTI_MEMORY_TYPE_HEAP,
    NULL,
    opendds_wrapper_BuiltinStringPlugin_copy_sample,

    opendds_wrapper_BuiltinStringTypePlugin_initialize_sample,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    opendds_wrapper_BuiltinString_fv_MemoryPlugins,
    opendds_wrapper_BuiltinString_fv_WirePlugins,

    /**************************************************************************
    *       Helper APIs to create language binding wrapper Functions
    **************************************************************************/

    opendds_wrapper_BuiltinStringPlugin_create_typed_datawriter,
    #ifndef RTI_CERT
    opendds_wrapper_BuiltinStringPlugin_delete_typed_datawriter,
    #else
    NULL,
    #endif
    opendds_wrapper_BuiltinStringPlugin_create_typed_datareader,
    #ifndef RTI_CERT
    opendds_wrapper_BuiltinStringPlugin_delete_typed_datareader,
    #else
    NULL,
    #endif
    opendds_wrapper_BuiltinStringTypePlugin_create_plugin,
    opendds_wrapper_BuiltinStringTypePlugin_delete_plugin,
    opendds_wrapper_BuiltinString_on_type_registered,
    opendds_wrapper_BuiltinString_on_type_unregistered,

};

/* --------------------------------------------------------------------------
*  Type opendds_wrapper_BuiltinString Plugin Methods
* -------------------------------------------------------------------------- */

struct DDS_TypePluginI*
opendds_wrapper_BuiltinStringTypePlugin_get(void) 
{ 
    return &opendds_wrapper_BuiltinString_fv_TypePluginI;
} 

RTI_PRIVATE struct DDS_TypePlugin*
opendds_wrapper_BuiltinStringTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property)
{
    return DDS_TypePluginDefault_create(&opendds_wrapper_BuiltinString_fv_TypePluginI,
    participant,dp_qos,
    endpoint_mode,endpoint,qos,
    property);
}

RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinStringTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin)
{
    return DDS_TypePluginDefault_delete(plugin);
}

struct DDS_TypePlugin*
opendds_wrapper_BuiltinStringWriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &opendds_wrapper_BuiltinString_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_WRITER,
        (DDS_TypePluginEndpoint*)writer,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

struct DDS_TypePlugin*
opendds_wrapper_BuiltinStringReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &opendds_wrapper_BuiltinString_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_READER,
        (DDS_TypePluginEndpoint*)reader,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

const char*
opendds_wrapper_BuiltinStringTypePlugin_get_default_type_name(void) 
{ 
    return opendds_wrapper_BuiltinStringTYPENAME;
} 

NDDS_TypePluginKeyKind 
opendds_wrapper_BuiltinStringI_get_key_kind(void)
{
    return opendds_wrapper_BuiltinString_fv_TypePluginI.key_kind;
}

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------
Typed-endpoint support for C++:
* -------------------------------------------------------------------------- */

void* 
opendds_wrapper_BuiltinBufferPlugin_create_typed_datawriter(void *writer)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * so writer is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataWriter *cpp_writer = 
    new opendds_wrapper_BuiltinBufferDataWriter((DDS_DataWriter*)writer);

    return cpp_writer;   
}

#ifndef RTI_CERT
void 
opendds_wrapper_BuiltinBufferPlugin_delete_typed_datawriter(void *wrapper)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * and DDS_Publisher_delete_datawriter so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataWriter_impl *cpp_writer = (DDSDataWriter_impl *) wrapper;

    opendds_wrapper_BuiltinBufferDataWriter *t_writer = 
    static_cast<opendds_wrapper_BuiltinBufferDataWriter *>(cpp_writer);

    delete t_writer;
}
#endif

void* 
opendds_wrapper_BuiltinBufferPlugin_create_typed_datareader(void *reader)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * so reader is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataReader *cpp_reader = 
    new opendds_wrapper_BuiltinBufferDataReader((DDS_DataReader*)reader);

    return cpp_reader;      
}

#ifndef RTI_CERT
void
opendds_wrapper_BuiltinBufferPlugin_delete_typed_datareader(void *wrapper)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * and DDS_Subscriber_delete_datareader so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataReader_impl *cpp_reader = (DDSDataReader_impl *) wrapper;

    opendds_wrapper_BuiltinBufferDataReader *t_reader = 
    static_cast<opendds_wrapper_BuiltinBufferDataReader *>(cpp_reader);

    delete t_reader;
}
#endif

/* --------------------------------------------------------------------------
*  Sample Support functions:
* -------------------------------------------------------------------------- */
RTI_BOOL
opendds_wrapper_BuiltinBufferPlugin_create_sample(struct DDS_TypePlugin *plugin,
void **sample)
{
    UNUSED_ARG(plugin);

    *sample = (void *) opendds_wrapper_BuiltinBuffer_create();
    return (*sample != NULL);
}

#ifndef RTI_CERT
RTI_BOOL
opendds_wrapper_BuiltinBufferPlugin_delete_sample(struct DDS_TypePlugin *plugin, 
void *sample)
{
    UNUSED_ARG(plugin);

    opendds_wrapper_BuiltinBuffer_delete((opendds_wrapper_BuiltinBuffer *) sample);
    return RTI_TRUE;
}
#endif

RTI_BOOL 
opendds_wrapper_BuiltinBufferPlugin_copy_sample(struct DDS_TypePlugin *plugin, 
void *dst, 
const void *src)
{
    UNUSED_ARG(plugin);

    return opendds_wrapper_BuiltinBuffer_copy(
        (opendds_wrapper_BuiltinBuffer*)dst,
        (const opendds_wrapper_BuiltinBuffer*)src);
}
/* --------------------------------------------------------------------------
*  Type opendds_wrapper_BuiltinBuffer Plugin Instantiation
* -------------------------------------------------------------------------- */

NDDSCDREncapsulation opendds_wrapper_BuiltinBufferEncapsulationKind[] =
{ 
    {
        DDS_ENCAPSULATION_ID_CDR_LE,
        DDS_ENCAPSULATION_ID_CDR_BE,
        0
    }
};

NDDSCDREncapsulation opendds_wrapper_BuiltinBufferV2EncapsulationKind[] =
{ 
    {

        DDS_ENCAPSULATION_ID_XCDR2_A_LE,
        DDS_ENCAPSULATION_ID_XCDR2_A_BE,
        0

    }
};

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinBufferTypePlugin_initialize_sample(struct DDS_TypePlugin *plugin, void *buffer)
{
    UNUSED_ARG(plugin);
    return opendds_wrapper_BuiltinBuffer_initialize((opendds_wrapper_BuiltinBuffer*)buffer);
}

RTI_PRIVATE RTI_UINT32 
opendds_wrapper_BuiltinBuffer_get_user_sample_size(
    struct DDS_TypePlugin *tp)
{
    UNUSED_ARG(tp);        
    return sizeof(opendds_wrapper_BuiltinBuffer);
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinBuffer_cdr_initialize(void *init_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)init_config;
    void *sample;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!opendds_wrapper_BuiltinBufferPlugin_create_sample(&plugin->_parent,&sample))
    {
        return RTI_FALSE;
    }

    sh->sample = sample;

    return RTI_TRUE;
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinBuffer_cdr_finalize(void *finalize_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)finalize_config;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!opendds_wrapper_BuiltinBufferPlugin_delete_sample(&plugin->_parent,sh->sample))
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

RTI_PRIVATE void 
opendds_wrapper_BuiltinBufferTypePlugin_return_sample(
    struct DDS_TypePlugin *tp,
    struct DDS_TypePluginSampleHolder *sample)
{
    opendds_wrapper_BuiltinBuffer_finalize_optional_members((opendds_wrapper_BuiltinBuffer*)sample->sample, RTI_FALSE);
    XCDR_GenericStreamPlugin_return_sample(tp, sample);
}

RTI_PRIVATE struct DDS_TypeMemoryPlugin*
opendds_wrapper_BuiltinBufferXTypesHeapPlugin_create(struct DDS_TypePlugin *tp,
DDS_DomainParticipant *participant,
struct DDS_DomainParticipantQos *dp_qos,
DDS_TypePluginMode_T endpoint_mode,
DDS_TypePluginEndpoint *endpoint,
DDS_TypePluginEndpointQos *qos)
{
    return DDS_XTypesHeapPlugin_create(
        tp,
        participant,
        dp_qos,
        endpoint_mode,
        endpoint,
        qos,
        NULL,
        NULL,
        opendds_wrapper_BuiltinBuffer_cdr_initialize,
        opendds_wrapper_BuiltinBuffer_cdr_finalize,
        sizeof(opendds_wrapper_BuiltinBuffer),
        RTI_FALSE
        );
}

RTI_PRIVATE struct DDS_TypeMemoryI opendds_wrapper_BuiltinBuffer_fv_XTypesHeapPluginI =
{
    RTI_MEMORY_MANAGER_HEAP,
    RTI_MEMORY_TYPE_HEAP,
    opendds_wrapper_BuiltinBufferPlugin_create_sample,
    #ifndef RTI_CERT
    opendds_wrapper_BuiltinBufferPlugin_delete_sample,
    #else
    NULL,
    #endif
    NULL, /* get_address */
    NULL, /* return_address */
    NULL,
    DDS_XTypesHeapPlugin_get_sample_state,
    DDS_XTypesHeapPlugin_set_sample_state,
    DDS_XTypesHeapPlugin_is_owner,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    opendds_wrapper_BuiltinBufferXTypesHeapPlugin_create,
    DDS_XTypesHeapPlugin_delete
};	

RTI_PRIVATE DDS_Boolean 
opendds_wrapper_BuiltinBuffer_on_type_registered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    struct RTIXCdrInterpreterProgramsGenProperty programProperty =
    RTIXCdrInterpreterProgramsGenProperty_INITIALIZER;

    programProperty.resolveAlias = RTI_XCDR_TRUE;
    programProperty.inlineStruct = RTI_XCDR_TRUE;
    programProperty.optimizeEnum = RTI_XCDR_TRUE;

    programs = RTIXCdrInterpreterPrograms_new(
        (RTIXCdrTypeCode *)opendds_wrapper_BuiltinBuffer_get_typecode(),
        &programProperty,
        RTI_XCDR_PROGRAM_MASK_TYPEPLUGIN
        );

    if (programs == NULL)
    {
        return DDS_BOOLEAN_FALSE;
    }

    DDS_TypeImpl_set_programs(type_impl, programs);
    DDS_TypeImpl_set_typecode(type_impl,  opendds_wrapper_BuiltinBuffer_get_typecode());

    return DDS_BOOLEAN_TRUE;
}
RTI_PRIVATE DDS_Boolean 
opendds_wrapper_BuiltinBuffer_on_type_unregistered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    programs = DDS_TypeImpl_get_programs(type_impl);

    if (programs != NULL) 
    {
        RTIXCdrInterpreterPrograms_delete(programs);
    }
    DDS_TypeImpl_set_programs(type_impl, NULL); 

    return DDS_BOOLEAN_TRUE;   
}

RTI_PRIVATE 
struct DDS_TypeEncapsulationI opendds_wrapper_BuiltinBuffer_fv_XCDRv1PluginI =
{
    DDS_XCDR_DATA_REPRESENTATION,
    NULL,
    opendds_wrapper_BuiltinBufferEncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,
    opendds_wrapper_BuiltinBufferTypePlugin_return_sample,
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv1_StreamPlugin_get_serialized_sample_size,
    XCDRv1_StreamPlugin_create,
    XCDRv1_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI opendds_wrapper_BuiltinBuffer_fv_XCDRv2PluginI =
{
    DDS_XCDR2_DATA_REPRESENTATION,
    NULL,
    opendds_wrapper_BuiltinBufferV2EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,

    opendds_wrapper_BuiltinBufferTypePlugin_return_sample,   
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv2_StreamPlugin_get_serialized_sample_size,
    XCDRv2_StreamPlugin_create,
    XCDRv2_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI *opendds_wrapper_BuiltinBuffer_fv_WirePlugins[] =
{
    &opendds_wrapper_BuiltinBuffer_fv_XCDRv2PluginI,
    &opendds_wrapper_BuiltinBuffer_fv_XCDRv1PluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypeMemoryI *opendds_wrapper_BuiltinBuffer_fv_MemoryPlugins[] =
{
    &opendds_wrapper_BuiltinBuffer_fv_XTypesHeapPluginI,

    NULL
};

RTI_PRIVATE struct DDS_TypePlugin*
opendds_wrapper_BuiltinBufferTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property);
RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinBufferTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin);

RTI_PRIVATE struct DDS_TypePluginI opendds_wrapper_BuiltinBuffer_fv_TypePluginI =
{
    /**************************************************************************
    *                   Type information functions
    **************************************************************************/

    NULL,                       /* DDS_TypeCode_t* */
    NDDS_TYPEPLUGIN_NO_KEY,     /* NDDS_TypePluginKeyKind */

    NDDS_TYPEPLUGIN_EH_LOCATION_PAYLOAD,
    opendds_wrapper_BuiltinBuffer_get_user_sample_size,   
    RTI_MEMORY_TYPE_HEAP,
    NULL,
    opendds_wrapper_BuiltinBufferPlugin_copy_sample,

    opendds_wrapper_BuiltinBufferTypePlugin_initialize_sample,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    opendds_wrapper_BuiltinBuffer_fv_MemoryPlugins,
    opendds_wrapper_BuiltinBuffer_fv_WirePlugins,

    /**************************************************************************
    *       Helper APIs to create language binding wrapper Functions
    **************************************************************************/

    opendds_wrapper_BuiltinBufferPlugin_create_typed_datawriter,
    #ifndef RTI_CERT
    opendds_wrapper_BuiltinBufferPlugin_delete_typed_datawriter,
    #else
    NULL,
    #endif
    opendds_wrapper_BuiltinBufferPlugin_create_typed_datareader,
    #ifndef RTI_CERT
    opendds_wrapper_BuiltinBufferPlugin_delete_typed_datareader,
    #else
    NULL,
    #endif
    opendds_wrapper_BuiltinBufferTypePlugin_create_plugin,
    opendds_wrapper_BuiltinBufferTypePlugin_delete_plugin,
    opendds_wrapper_BuiltinBuffer_on_type_registered,
    opendds_wrapper_BuiltinBuffer_on_type_unregistered,

};

/* --------------------------------------------------------------------------
*  Type opendds_wrapper_BuiltinBuffer Plugin Methods
* -------------------------------------------------------------------------- */

struct DDS_TypePluginI*
opendds_wrapper_BuiltinBufferTypePlugin_get(void) 
{ 
    return &opendds_wrapper_BuiltinBuffer_fv_TypePluginI;
} 

RTI_PRIVATE struct DDS_TypePlugin*
opendds_wrapper_BuiltinBufferTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property)
{
    return DDS_TypePluginDefault_create(&opendds_wrapper_BuiltinBuffer_fv_TypePluginI,
    participant,dp_qos,
    endpoint_mode,endpoint,qos,
    property);
}

RTI_PRIVATE RTI_BOOL
opendds_wrapper_BuiltinBufferTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin)
{
    return DDS_TypePluginDefault_delete(plugin);
}

struct DDS_TypePlugin*
opendds_wrapper_BuiltinBufferWriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &opendds_wrapper_BuiltinBuffer_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_WRITER,
        (DDS_TypePluginEndpoint*)writer,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

struct DDS_TypePlugin*
opendds_wrapper_BuiltinBufferReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &opendds_wrapper_BuiltinBuffer_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_READER,
        (DDS_TypePluginEndpoint*)reader,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

const char*
opendds_wrapper_BuiltinBufferTypePlugin_get_default_type_name(void) 
{ 
    return opendds_wrapper_BuiltinBufferTYPENAME;
} 

NDDS_TypePluginKeyKind 
opendds_wrapper_BuiltinBufferI_get_key_kind(void)
{
    return opendds_wrapper_BuiltinBuffer_fv_TypePluginI.key_kind;
}

