/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ParkingSlot.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "ParkingSlot.h"
#include "reda/reda_bufferpool.h"
#include "xcdr/xcdr_interpreter.h"
#include "dds_c/dds_c_xcdr_type_plugin.h"
#include "ParkingSlotPlugin.h"
#include "ParkingSlotSupport.h"

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
holo_base_msg_common_ParkingSlotfPlugin_create_typed_datawriter(void *writer)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * so writer is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataWriter *cpp_writer = 
    new holo_base_msg_common_ParkingSlotfDataWriter((DDS_DataWriter*)writer);

    return cpp_writer;   
}

#ifndef RTI_CERT
void 
holo_base_msg_common_ParkingSlotfPlugin_delete_typed_datawriter(void *wrapper)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * and DDS_Publisher_delete_datawriter so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataWriter_impl *cpp_writer = (DDSDataWriter_impl *) wrapper;

    holo_base_msg_common_ParkingSlotfDataWriter *t_writer = 
    static_cast<holo_base_msg_common_ParkingSlotfDataWriter *>(cpp_writer);

    delete t_writer;
}
#endif

void* 
holo_base_msg_common_ParkingSlotfPlugin_create_typed_datareader(void *reader)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * so reader is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataReader *cpp_reader = 
    new holo_base_msg_common_ParkingSlotfDataReader((DDS_DataReader*)reader);

    return cpp_reader;      
}

#ifndef RTI_CERT
void
holo_base_msg_common_ParkingSlotfPlugin_delete_typed_datareader(void *wrapper)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * and DDS_Subscriber_delete_datareader so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataReader_impl *cpp_reader = (DDSDataReader_impl *) wrapper;

    holo_base_msg_common_ParkingSlotfDataReader *t_reader = 
    static_cast<holo_base_msg_common_ParkingSlotfDataReader *>(cpp_reader);

    delete t_reader;
}
#endif

/* --------------------------------------------------------------------------
*  Sample Support functions:
* -------------------------------------------------------------------------- */
RTI_BOOL
holo_base_msg_common_ParkingSlotfPlugin_create_sample(struct DDS_TypePlugin *plugin,
void **sample)
{
    UNUSED_ARG(plugin);

    *sample = (void *) holo_base_msg_common_ParkingSlotf_create();
    return (*sample != NULL);
}

#ifndef RTI_CERT
RTI_BOOL
holo_base_msg_common_ParkingSlotfPlugin_delete_sample(struct DDS_TypePlugin *plugin, 
void *sample)
{
    UNUSED_ARG(plugin);

    holo_base_msg_common_ParkingSlotf_delete((holo_base_msg_common_ParkingSlotf *) sample);
    return RTI_TRUE;
}
#endif

RTI_BOOL 
holo_base_msg_common_ParkingSlotfPlugin_copy_sample(struct DDS_TypePlugin *plugin, 
void *dst, 
const void *src)
{
    UNUSED_ARG(plugin);

    return holo_base_msg_common_ParkingSlotf_copy(
        (holo_base_msg_common_ParkingSlotf*)dst,
        (const holo_base_msg_common_ParkingSlotf*)src);
}
/* --------------------------------------------------------------------------
*  Type holo_base_msg_common_ParkingSlotf Plugin Instantiation
* -------------------------------------------------------------------------- */

NDDSCDREncapsulation holo_base_msg_common_ParkingSlotfEncapsulationKind[] =
{ 
    {
        DDS_ENCAPSULATION_ID_CDR_LE,
        DDS_ENCAPSULATION_ID_CDR_BE,
        0
    }
};

NDDSCDREncapsulation holo_base_msg_common_ParkingSlotfV2EncapsulationKind[] =
{ 
    {

        DDS_ENCAPSULATION_ID_XCDR2_A_LE,
        DDS_ENCAPSULATION_ID_XCDR2_A_BE,
        0

    }
};

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_common_ParkingSlotfTypePlugin_initialize_sample(struct DDS_TypePlugin *plugin, void *buffer)
{
    UNUSED_ARG(plugin);
    return holo_base_msg_common_ParkingSlotf_initialize((holo_base_msg_common_ParkingSlotf*)buffer);
}

RTI_PRIVATE RTI_UINT32 
holo_base_msg_common_ParkingSlotf_get_user_sample_size(
    struct DDS_TypePlugin *tp)
{
    UNUSED_ARG(tp);        
    return sizeof(holo_base_msg_common_ParkingSlotf);
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_common_ParkingSlotf_cdr_initialize(void *init_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)init_config;
    void *sample;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_common_ParkingSlotfPlugin_create_sample(&plugin->_parent,&sample))
    {
        return RTI_FALSE;
    }

    sh->sample = sample;

    return RTI_TRUE;
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_common_ParkingSlotf_cdr_finalize(void *finalize_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)finalize_config;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_common_ParkingSlotfPlugin_delete_sample(&plugin->_parent,sh->sample))
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

RTI_PRIVATE void 
holo_base_msg_common_ParkingSlotfTypePlugin_return_sample(
    struct DDS_TypePlugin *tp,
    struct DDS_TypePluginSampleHolder *sample)
{
    holo_base_msg_common_ParkingSlotf_finalize_optional_members((holo_base_msg_common_ParkingSlotf*)sample->sample, RTI_FALSE);
    XCDR_GenericStreamPlugin_return_sample(tp, sample);
}

RTI_PRIVATE struct DDS_TypeMemoryPlugin*
holo_base_msg_common_ParkingSlotfXTypesHeapPlugin_create(struct DDS_TypePlugin *tp,
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
        holo_base_msg_common_ParkingSlotf_cdr_initialize,
        holo_base_msg_common_ParkingSlotf_cdr_finalize,
        sizeof(holo_base_msg_common_ParkingSlotf),
        RTI_FALSE
        );
}

RTI_PRIVATE struct DDS_TypeMemoryI holo_base_msg_common_ParkingSlotf_fv_XTypesHeapPluginI =
{
    RTI_MEMORY_MANAGER_HEAP,
    RTI_MEMORY_TYPE_HEAP,
    holo_base_msg_common_ParkingSlotfPlugin_create_sample,
    #ifndef RTI_CERT
    holo_base_msg_common_ParkingSlotfPlugin_delete_sample,
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
    holo_base_msg_common_ParkingSlotfXTypesHeapPlugin_create,
    DDS_XTypesHeapPlugin_delete
};	

RTI_PRIVATE DDS_Boolean 
holo_base_msg_common_ParkingSlotf_on_type_registered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    struct RTIXCdrInterpreterProgramsGenProperty programProperty =
    RTIXCdrInterpreterProgramsGenProperty_INITIALIZER;

    programProperty.resolveAlias = RTI_XCDR_TRUE;
    programProperty.inlineStruct = RTI_XCDR_TRUE;
    programProperty.optimizeEnum = RTI_XCDR_TRUE;

    programs = RTIXCdrInterpreterPrograms_new(
        (RTIXCdrTypeCode *)holo_base_msg_common_ParkingSlotf_get_typecode(),
        &programProperty,
        RTI_XCDR_PROGRAM_MASK_TYPEPLUGIN
        );

    if (programs == NULL)
    {
        return DDS_BOOLEAN_FALSE;
    }

    DDS_TypeImpl_set_programs(type_impl, programs);
    DDS_TypeImpl_set_typecode(type_impl,  holo_base_msg_common_ParkingSlotf_get_typecode());

    return DDS_BOOLEAN_TRUE;
}
RTI_PRIVATE DDS_Boolean 
holo_base_msg_common_ParkingSlotf_on_type_unregistered(struct DDS_TypeImpl* type_impl)
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
struct DDS_TypeEncapsulationI holo_base_msg_common_ParkingSlotf_fv_XCDRv1PluginI =
{
    DDS_XCDR_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_common_ParkingSlotfEncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,
    holo_base_msg_common_ParkingSlotfTypePlugin_return_sample,
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv1_StreamPlugin_get_serialized_sample_size,
    XCDRv1_StreamPlugin_create,
    XCDRv1_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI holo_base_msg_common_ParkingSlotf_fv_XCDRv2PluginI =
{
    DDS_XCDR2_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_common_ParkingSlotfV2EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,

    holo_base_msg_common_ParkingSlotfTypePlugin_return_sample,   
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv2_StreamPlugin_get_serialized_sample_size,
    XCDRv2_StreamPlugin_create,
    XCDRv2_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI *holo_base_msg_common_ParkingSlotf_fv_WirePlugins[] =
{
    &holo_base_msg_common_ParkingSlotf_fv_XCDRv2PluginI,
    &holo_base_msg_common_ParkingSlotf_fv_XCDRv1PluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypeMemoryI *holo_base_msg_common_ParkingSlotf_fv_MemoryPlugins[] =
{
    &holo_base_msg_common_ParkingSlotf_fv_XTypesHeapPluginI,

    NULL
};

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_common_ParkingSlotfTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property);
RTI_PRIVATE RTI_BOOL
holo_base_msg_common_ParkingSlotfTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin);

RTI_PRIVATE struct DDS_TypePluginI holo_base_msg_common_ParkingSlotf_fv_TypePluginI =
{
    /**************************************************************************
    *                   Type information functions
    **************************************************************************/

    NULL,                       /* DDS_TypeCode_t* */
    NDDS_TYPEPLUGIN_NO_KEY,     /* NDDS_TypePluginKeyKind */

    NDDS_TYPEPLUGIN_EH_LOCATION_PAYLOAD,
    holo_base_msg_common_ParkingSlotf_get_user_sample_size,   
    RTI_MEMORY_TYPE_HEAP,
    NULL,
    holo_base_msg_common_ParkingSlotfPlugin_copy_sample,

    holo_base_msg_common_ParkingSlotfTypePlugin_initialize_sample,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    holo_base_msg_common_ParkingSlotf_fv_MemoryPlugins,
    holo_base_msg_common_ParkingSlotf_fv_WirePlugins,

    /**************************************************************************
    *       Helper APIs to create language binding wrapper Functions
    **************************************************************************/

    holo_base_msg_common_ParkingSlotfPlugin_create_typed_datawriter,
    #ifndef RTI_CERT
    holo_base_msg_common_ParkingSlotfPlugin_delete_typed_datawriter,
    #else
    NULL,
    #endif
    holo_base_msg_common_ParkingSlotfPlugin_create_typed_datareader,
    #ifndef RTI_CERT
    holo_base_msg_common_ParkingSlotfPlugin_delete_typed_datareader,
    #else
    NULL,
    #endif
    holo_base_msg_common_ParkingSlotfTypePlugin_create_plugin,
    holo_base_msg_common_ParkingSlotfTypePlugin_delete_plugin,
    holo_base_msg_common_ParkingSlotf_on_type_registered,
    holo_base_msg_common_ParkingSlotf_on_type_unregistered,

};

/* --------------------------------------------------------------------------
*  Type holo_base_msg_common_ParkingSlotf Plugin Methods
* -------------------------------------------------------------------------- */

struct DDS_TypePluginI*
holo_base_msg_common_ParkingSlotfTypePlugin_get(void) 
{ 
    return &holo_base_msg_common_ParkingSlotf_fv_TypePluginI;
} 

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_common_ParkingSlotfTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property)
{
    return DDS_TypePluginDefault_create(&holo_base_msg_common_ParkingSlotf_fv_TypePluginI,
    participant,dp_qos,
    endpoint_mode,endpoint,qos,
    property);
}

RTI_PRIVATE RTI_BOOL
holo_base_msg_common_ParkingSlotfTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin)
{
    return DDS_TypePluginDefault_delete(plugin);
}

struct DDS_TypePlugin*
holo_base_msg_common_ParkingSlotfWriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_common_ParkingSlotf_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_WRITER,
        (DDS_TypePluginEndpoint*)writer,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

struct DDS_TypePlugin*
holo_base_msg_common_ParkingSlotfReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_common_ParkingSlotf_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_READER,
        (DDS_TypePluginEndpoint*)reader,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

const char*
holo_base_msg_common_ParkingSlotfTypePlugin_get_default_type_name(void) 
{ 
    return holo_base_msg_common_ParkingSlotfTYPENAME;
} 

NDDS_TypePluginKeyKind 
holo_base_msg_common_ParkingSlotfI_get_key_kind(void)
{
    return holo_base_msg_common_ParkingSlotf_fv_TypePluginI.key_kind;
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
holo_base_msg_common_ParkingSlotdPlugin_create_typed_datawriter(void *writer)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * so writer is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataWriter *cpp_writer = 
    new holo_base_msg_common_ParkingSlotdDataWriter((DDS_DataWriter*)writer);

    return cpp_writer;   
}

#ifndef RTI_CERT
void 
holo_base_msg_common_ParkingSlotdPlugin_delete_typed_datawriter(void *wrapper)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * and DDS_Publisher_delete_datawriter so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataWriter_impl *cpp_writer = (DDSDataWriter_impl *) wrapper;

    holo_base_msg_common_ParkingSlotdDataWriter *t_writer = 
    static_cast<holo_base_msg_common_ParkingSlotdDataWriter *>(cpp_writer);

    delete t_writer;
}
#endif

void* 
holo_base_msg_common_ParkingSlotdPlugin_create_typed_datareader(void *reader)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * so reader is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataReader *cpp_reader = 
    new holo_base_msg_common_ParkingSlotdDataReader((DDS_DataReader*)reader);

    return cpp_reader;      
}

#ifndef RTI_CERT
void
holo_base_msg_common_ParkingSlotdPlugin_delete_typed_datareader(void *wrapper)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * and DDS_Subscriber_delete_datareader so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataReader_impl *cpp_reader = (DDSDataReader_impl *) wrapper;

    holo_base_msg_common_ParkingSlotdDataReader *t_reader = 
    static_cast<holo_base_msg_common_ParkingSlotdDataReader *>(cpp_reader);

    delete t_reader;
}
#endif

/* --------------------------------------------------------------------------
*  Sample Support functions:
* -------------------------------------------------------------------------- */
RTI_BOOL
holo_base_msg_common_ParkingSlotdPlugin_create_sample(struct DDS_TypePlugin *plugin,
void **sample)
{
    UNUSED_ARG(plugin);

    *sample = (void *) holo_base_msg_common_ParkingSlotd_create();
    return (*sample != NULL);
}

#ifndef RTI_CERT
RTI_BOOL
holo_base_msg_common_ParkingSlotdPlugin_delete_sample(struct DDS_TypePlugin *plugin, 
void *sample)
{
    UNUSED_ARG(plugin);

    holo_base_msg_common_ParkingSlotd_delete((holo_base_msg_common_ParkingSlotd *) sample);
    return RTI_TRUE;
}
#endif

RTI_BOOL 
holo_base_msg_common_ParkingSlotdPlugin_copy_sample(struct DDS_TypePlugin *plugin, 
void *dst, 
const void *src)
{
    UNUSED_ARG(plugin);

    return holo_base_msg_common_ParkingSlotd_copy(
        (holo_base_msg_common_ParkingSlotd*)dst,
        (const holo_base_msg_common_ParkingSlotd*)src);
}
/* --------------------------------------------------------------------------
*  Type holo_base_msg_common_ParkingSlotd Plugin Instantiation
* -------------------------------------------------------------------------- */

NDDSCDREncapsulation holo_base_msg_common_ParkingSlotdEncapsulationKind[] =
{ 
    {
        DDS_ENCAPSULATION_ID_CDR_LE,
        DDS_ENCAPSULATION_ID_CDR_BE,
        0
    }
};

NDDSCDREncapsulation holo_base_msg_common_ParkingSlotdV2EncapsulationKind[] =
{ 
    {

        DDS_ENCAPSULATION_ID_XCDR2_A_LE,
        DDS_ENCAPSULATION_ID_XCDR2_A_BE,
        0

    }
};

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_common_ParkingSlotdTypePlugin_initialize_sample(struct DDS_TypePlugin *plugin, void *buffer)
{
    UNUSED_ARG(plugin);
    return holo_base_msg_common_ParkingSlotd_initialize((holo_base_msg_common_ParkingSlotd*)buffer);
}

RTI_PRIVATE RTI_UINT32 
holo_base_msg_common_ParkingSlotd_get_user_sample_size(
    struct DDS_TypePlugin *tp)
{
    UNUSED_ARG(tp);        
    return sizeof(holo_base_msg_common_ParkingSlotd);
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_common_ParkingSlotd_cdr_initialize(void *init_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)init_config;
    void *sample;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_common_ParkingSlotdPlugin_create_sample(&plugin->_parent,&sample))
    {
        return RTI_FALSE;
    }

    sh->sample = sample;

    return RTI_TRUE;
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_common_ParkingSlotd_cdr_finalize(void *finalize_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)finalize_config;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_common_ParkingSlotdPlugin_delete_sample(&plugin->_parent,sh->sample))
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

RTI_PRIVATE void 
holo_base_msg_common_ParkingSlotdTypePlugin_return_sample(
    struct DDS_TypePlugin *tp,
    struct DDS_TypePluginSampleHolder *sample)
{
    holo_base_msg_common_ParkingSlotd_finalize_optional_members((holo_base_msg_common_ParkingSlotd*)sample->sample, RTI_FALSE);
    XCDR_GenericStreamPlugin_return_sample(tp, sample);
}

RTI_PRIVATE struct DDS_TypeMemoryPlugin*
holo_base_msg_common_ParkingSlotdXTypesHeapPlugin_create(struct DDS_TypePlugin *tp,
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
        holo_base_msg_common_ParkingSlotd_cdr_initialize,
        holo_base_msg_common_ParkingSlotd_cdr_finalize,
        sizeof(holo_base_msg_common_ParkingSlotd),
        RTI_FALSE
        );
}

RTI_PRIVATE struct DDS_TypeMemoryI holo_base_msg_common_ParkingSlotd_fv_XTypesHeapPluginI =
{
    RTI_MEMORY_MANAGER_HEAP,
    RTI_MEMORY_TYPE_HEAP,
    holo_base_msg_common_ParkingSlotdPlugin_create_sample,
    #ifndef RTI_CERT
    holo_base_msg_common_ParkingSlotdPlugin_delete_sample,
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
    holo_base_msg_common_ParkingSlotdXTypesHeapPlugin_create,
    DDS_XTypesHeapPlugin_delete
};	

RTI_PRIVATE DDS_Boolean 
holo_base_msg_common_ParkingSlotd_on_type_registered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    struct RTIXCdrInterpreterProgramsGenProperty programProperty =
    RTIXCdrInterpreterProgramsGenProperty_INITIALIZER;

    programProperty.resolveAlias = RTI_XCDR_TRUE;
    programProperty.inlineStruct = RTI_XCDR_TRUE;
    programProperty.optimizeEnum = RTI_XCDR_TRUE;

    programs = RTIXCdrInterpreterPrograms_new(
        (RTIXCdrTypeCode *)holo_base_msg_common_ParkingSlotd_get_typecode(),
        &programProperty,
        RTI_XCDR_PROGRAM_MASK_TYPEPLUGIN
        );

    if (programs == NULL)
    {
        return DDS_BOOLEAN_FALSE;
    }

    DDS_TypeImpl_set_programs(type_impl, programs);
    DDS_TypeImpl_set_typecode(type_impl,  holo_base_msg_common_ParkingSlotd_get_typecode());

    return DDS_BOOLEAN_TRUE;
}
RTI_PRIVATE DDS_Boolean 
holo_base_msg_common_ParkingSlotd_on_type_unregistered(struct DDS_TypeImpl* type_impl)
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
struct DDS_TypeEncapsulationI holo_base_msg_common_ParkingSlotd_fv_XCDRv1PluginI =
{
    DDS_XCDR_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_common_ParkingSlotdEncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,
    holo_base_msg_common_ParkingSlotdTypePlugin_return_sample,
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv1_StreamPlugin_get_serialized_sample_size,
    XCDRv1_StreamPlugin_create,
    XCDRv1_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI holo_base_msg_common_ParkingSlotd_fv_XCDRv2PluginI =
{
    DDS_XCDR2_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_common_ParkingSlotdV2EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,

    holo_base_msg_common_ParkingSlotdTypePlugin_return_sample,   
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv2_StreamPlugin_get_serialized_sample_size,
    XCDRv2_StreamPlugin_create,
    XCDRv2_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI *holo_base_msg_common_ParkingSlotd_fv_WirePlugins[] =
{
    &holo_base_msg_common_ParkingSlotd_fv_XCDRv2PluginI,
    &holo_base_msg_common_ParkingSlotd_fv_XCDRv1PluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypeMemoryI *holo_base_msg_common_ParkingSlotd_fv_MemoryPlugins[] =
{
    &holo_base_msg_common_ParkingSlotd_fv_XTypesHeapPluginI,

    NULL
};

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_common_ParkingSlotdTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property);
RTI_PRIVATE RTI_BOOL
holo_base_msg_common_ParkingSlotdTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin);

RTI_PRIVATE struct DDS_TypePluginI holo_base_msg_common_ParkingSlotd_fv_TypePluginI =
{
    /**************************************************************************
    *                   Type information functions
    **************************************************************************/

    NULL,                       /* DDS_TypeCode_t* */
    NDDS_TYPEPLUGIN_NO_KEY,     /* NDDS_TypePluginKeyKind */

    NDDS_TYPEPLUGIN_EH_LOCATION_PAYLOAD,
    holo_base_msg_common_ParkingSlotd_get_user_sample_size,   
    RTI_MEMORY_TYPE_HEAP,
    NULL,
    holo_base_msg_common_ParkingSlotdPlugin_copy_sample,

    holo_base_msg_common_ParkingSlotdTypePlugin_initialize_sample,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    holo_base_msg_common_ParkingSlotd_fv_MemoryPlugins,
    holo_base_msg_common_ParkingSlotd_fv_WirePlugins,

    /**************************************************************************
    *       Helper APIs to create language binding wrapper Functions
    **************************************************************************/

    holo_base_msg_common_ParkingSlotdPlugin_create_typed_datawriter,
    #ifndef RTI_CERT
    holo_base_msg_common_ParkingSlotdPlugin_delete_typed_datawriter,
    #else
    NULL,
    #endif
    holo_base_msg_common_ParkingSlotdPlugin_create_typed_datareader,
    #ifndef RTI_CERT
    holo_base_msg_common_ParkingSlotdPlugin_delete_typed_datareader,
    #else
    NULL,
    #endif
    holo_base_msg_common_ParkingSlotdTypePlugin_create_plugin,
    holo_base_msg_common_ParkingSlotdTypePlugin_delete_plugin,
    holo_base_msg_common_ParkingSlotd_on_type_registered,
    holo_base_msg_common_ParkingSlotd_on_type_unregistered,

};

/* --------------------------------------------------------------------------
*  Type holo_base_msg_common_ParkingSlotd Plugin Methods
* -------------------------------------------------------------------------- */

struct DDS_TypePluginI*
holo_base_msg_common_ParkingSlotdTypePlugin_get(void) 
{ 
    return &holo_base_msg_common_ParkingSlotd_fv_TypePluginI;
} 

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_common_ParkingSlotdTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property)
{
    return DDS_TypePluginDefault_create(&holo_base_msg_common_ParkingSlotd_fv_TypePluginI,
    participant,dp_qos,
    endpoint_mode,endpoint,qos,
    property);
}

RTI_PRIVATE RTI_BOOL
holo_base_msg_common_ParkingSlotdTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin)
{
    return DDS_TypePluginDefault_delete(plugin);
}

struct DDS_TypePlugin*
holo_base_msg_common_ParkingSlotdWriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_common_ParkingSlotd_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_WRITER,
        (DDS_TypePluginEndpoint*)writer,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

struct DDS_TypePlugin*
holo_base_msg_common_ParkingSlotdReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_common_ParkingSlotd_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_READER,
        (DDS_TypePluginEndpoint*)reader,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

const char*
holo_base_msg_common_ParkingSlotdTypePlugin_get_default_type_name(void) 
{ 
    return holo_base_msg_common_ParkingSlotdTYPENAME;
} 

NDDS_TypePluginKeyKind 
holo_base_msg_common_ParkingSlotdI_get_key_kind(void)
{
    return holo_base_msg_common_ParkingSlotd_fv_TypePluginI.key_kind;
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
holo_base_msg_common_ParkingSlotFramefPlugin_create_typed_datawriter(void *writer)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * so writer is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataWriter *cpp_writer = 
    new holo_base_msg_common_ParkingSlotFramefDataWriter((DDS_DataWriter*)writer);

    return cpp_writer;   
}

#ifndef RTI_CERT
void 
holo_base_msg_common_ParkingSlotFramefPlugin_delete_typed_datawriter(void *wrapper)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * and DDS_Publisher_delete_datawriter so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataWriter_impl *cpp_writer = (DDSDataWriter_impl *) wrapper;

    holo_base_msg_common_ParkingSlotFramefDataWriter *t_writer = 
    static_cast<holo_base_msg_common_ParkingSlotFramefDataWriter *>(cpp_writer);

    delete t_writer;
}
#endif

void* 
holo_base_msg_common_ParkingSlotFramefPlugin_create_typed_datareader(void *reader)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * so reader is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataReader *cpp_reader = 
    new holo_base_msg_common_ParkingSlotFramefDataReader((DDS_DataReader*)reader);

    return cpp_reader;      
}

#ifndef RTI_CERT
void
holo_base_msg_common_ParkingSlotFramefPlugin_delete_typed_datareader(void *wrapper)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * and DDS_Subscriber_delete_datareader so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataReader_impl *cpp_reader = (DDSDataReader_impl *) wrapper;

    holo_base_msg_common_ParkingSlotFramefDataReader *t_reader = 
    static_cast<holo_base_msg_common_ParkingSlotFramefDataReader *>(cpp_reader);

    delete t_reader;
}
#endif

/* --------------------------------------------------------------------------
*  Sample Support functions:
* -------------------------------------------------------------------------- */
RTI_BOOL
holo_base_msg_common_ParkingSlotFramefPlugin_create_sample(struct DDS_TypePlugin *plugin,
void **sample)
{
    UNUSED_ARG(plugin);

    *sample = (void *) holo_base_msg_common_ParkingSlotFramef_create();
    return (*sample != NULL);
}

#ifndef RTI_CERT
RTI_BOOL
holo_base_msg_common_ParkingSlotFramefPlugin_delete_sample(struct DDS_TypePlugin *plugin, 
void *sample)
{
    UNUSED_ARG(plugin);

    holo_base_msg_common_ParkingSlotFramef_delete((holo_base_msg_common_ParkingSlotFramef *) sample);
    return RTI_TRUE;
}
#endif

RTI_BOOL 
holo_base_msg_common_ParkingSlotFramefPlugin_copy_sample(struct DDS_TypePlugin *plugin, 
void *dst, 
const void *src)
{
    UNUSED_ARG(plugin);

    return holo_base_msg_common_ParkingSlotFramef_copy(
        (holo_base_msg_common_ParkingSlotFramef*)dst,
        (const holo_base_msg_common_ParkingSlotFramef*)src);
}
/* --------------------------------------------------------------------------
*  Type holo_base_msg_common_ParkingSlotFramef Plugin Instantiation
* -------------------------------------------------------------------------- */

NDDSCDREncapsulation holo_base_msg_common_ParkingSlotFramefEncapsulationKind[] =
{ 
    {
        DDS_ENCAPSULATION_ID_CDR_LE,
        DDS_ENCAPSULATION_ID_CDR_BE,
        0
    }
};

NDDSCDREncapsulation holo_base_msg_common_ParkingSlotFramefV2EncapsulationKind[] =
{ 
    {

        DDS_ENCAPSULATION_ID_XCDR2_A_LE,
        DDS_ENCAPSULATION_ID_XCDR2_A_BE,
        0

    }
};

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_common_ParkingSlotFramefTypePlugin_initialize_sample(struct DDS_TypePlugin *plugin, void *buffer)
{
    UNUSED_ARG(plugin);
    return holo_base_msg_common_ParkingSlotFramef_initialize((holo_base_msg_common_ParkingSlotFramef*)buffer);
}

RTI_PRIVATE RTI_UINT32 
holo_base_msg_common_ParkingSlotFramef_get_user_sample_size(
    struct DDS_TypePlugin *tp)
{
    UNUSED_ARG(tp);        
    return sizeof(holo_base_msg_common_ParkingSlotFramef);
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_common_ParkingSlotFramef_cdr_initialize(void *init_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)init_config;
    void *sample;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_common_ParkingSlotFramefPlugin_create_sample(&plugin->_parent,&sample))
    {
        return RTI_FALSE;
    }

    sh->sample = sample;

    return RTI_TRUE;
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_common_ParkingSlotFramef_cdr_finalize(void *finalize_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)finalize_config;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_common_ParkingSlotFramefPlugin_delete_sample(&plugin->_parent,sh->sample))
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

RTI_PRIVATE void 
holo_base_msg_common_ParkingSlotFramefTypePlugin_return_sample(
    struct DDS_TypePlugin *tp,
    struct DDS_TypePluginSampleHolder *sample)
{
    holo_base_msg_common_ParkingSlotFramef_finalize_optional_members((holo_base_msg_common_ParkingSlotFramef*)sample->sample, RTI_FALSE);
    XCDR_GenericStreamPlugin_return_sample(tp, sample);
}

RTI_PRIVATE struct DDS_TypeMemoryPlugin*
holo_base_msg_common_ParkingSlotFramefXTypesHeapPlugin_create(struct DDS_TypePlugin *tp,
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
        holo_base_msg_common_ParkingSlotFramef_cdr_initialize,
        holo_base_msg_common_ParkingSlotFramef_cdr_finalize,
        sizeof(holo_base_msg_common_ParkingSlotFramef),
        RTI_FALSE
        );
}

RTI_PRIVATE struct DDS_TypeMemoryI holo_base_msg_common_ParkingSlotFramef_fv_XTypesHeapPluginI =
{
    RTI_MEMORY_MANAGER_HEAP,
    RTI_MEMORY_TYPE_HEAP,
    holo_base_msg_common_ParkingSlotFramefPlugin_create_sample,
    #ifndef RTI_CERT
    holo_base_msg_common_ParkingSlotFramefPlugin_delete_sample,
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
    holo_base_msg_common_ParkingSlotFramefXTypesHeapPlugin_create,
    DDS_XTypesHeapPlugin_delete
};	

RTI_PRIVATE DDS_Boolean 
holo_base_msg_common_ParkingSlotFramef_on_type_registered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    struct RTIXCdrInterpreterProgramsGenProperty programProperty =
    RTIXCdrInterpreterProgramsGenProperty_INITIALIZER;

    programProperty.resolveAlias = RTI_XCDR_TRUE;
    programProperty.inlineStruct = RTI_XCDR_TRUE;
    programProperty.optimizeEnum = RTI_XCDR_TRUE;

    programs = RTIXCdrInterpreterPrograms_new(
        (RTIXCdrTypeCode *)holo_base_msg_common_ParkingSlotFramef_get_typecode(),
        &programProperty,
        RTI_XCDR_PROGRAM_MASK_TYPEPLUGIN
        );

    if (programs == NULL)
    {
        return DDS_BOOLEAN_FALSE;
    }

    DDS_TypeImpl_set_programs(type_impl, programs);
    DDS_TypeImpl_set_typecode(type_impl,  holo_base_msg_common_ParkingSlotFramef_get_typecode());

    return DDS_BOOLEAN_TRUE;
}
RTI_PRIVATE DDS_Boolean 
holo_base_msg_common_ParkingSlotFramef_on_type_unregistered(struct DDS_TypeImpl* type_impl)
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
struct DDS_TypeEncapsulationI holo_base_msg_common_ParkingSlotFramef_fv_XCDRv1PluginI =
{
    DDS_XCDR_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_common_ParkingSlotFramefEncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,
    holo_base_msg_common_ParkingSlotFramefTypePlugin_return_sample,
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv1_StreamPlugin_get_serialized_sample_size,
    XCDRv1_StreamPlugin_create,
    XCDRv1_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI holo_base_msg_common_ParkingSlotFramef_fv_XCDRv2PluginI =
{
    DDS_XCDR2_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_common_ParkingSlotFramefV2EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,

    holo_base_msg_common_ParkingSlotFramefTypePlugin_return_sample,   
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv2_StreamPlugin_get_serialized_sample_size,
    XCDRv2_StreamPlugin_create,
    XCDRv2_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI *holo_base_msg_common_ParkingSlotFramef_fv_WirePlugins[] =
{
    &holo_base_msg_common_ParkingSlotFramef_fv_XCDRv2PluginI,
    &holo_base_msg_common_ParkingSlotFramef_fv_XCDRv1PluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypeMemoryI *holo_base_msg_common_ParkingSlotFramef_fv_MemoryPlugins[] =
{
    &holo_base_msg_common_ParkingSlotFramef_fv_XTypesHeapPluginI,

    NULL
};

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_common_ParkingSlotFramefTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property);
RTI_PRIVATE RTI_BOOL
holo_base_msg_common_ParkingSlotFramefTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin);

RTI_PRIVATE struct DDS_TypePluginI holo_base_msg_common_ParkingSlotFramef_fv_TypePluginI =
{
    /**************************************************************************
    *                   Type information functions
    **************************************************************************/

    NULL,                       /* DDS_TypeCode_t* */
    NDDS_TYPEPLUGIN_NO_KEY,     /* NDDS_TypePluginKeyKind */

    NDDS_TYPEPLUGIN_EH_LOCATION_PAYLOAD,
    holo_base_msg_common_ParkingSlotFramef_get_user_sample_size,   
    RTI_MEMORY_TYPE_HEAP,
    NULL,
    holo_base_msg_common_ParkingSlotFramefPlugin_copy_sample,

    holo_base_msg_common_ParkingSlotFramefTypePlugin_initialize_sample,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    holo_base_msg_common_ParkingSlotFramef_fv_MemoryPlugins,
    holo_base_msg_common_ParkingSlotFramef_fv_WirePlugins,

    /**************************************************************************
    *       Helper APIs to create language binding wrapper Functions
    **************************************************************************/

    holo_base_msg_common_ParkingSlotFramefPlugin_create_typed_datawriter,
    #ifndef RTI_CERT
    holo_base_msg_common_ParkingSlotFramefPlugin_delete_typed_datawriter,
    #else
    NULL,
    #endif
    holo_base_msg_common_ParkingSlotFramefPlugin_create_typed_datareader,
    #ifndef RTI_CERT
    holo_base_msg_common_ParkingSlotFramefPlugin_delete_typed_datareader,
    #else
    NULL,
    #endif
    holo_base_msg_common_ParkingSlotFramefTypePlugin_create_plugin,
    holo_base_msg_common_ParkingSlotFramefTypePlugin_delete_plugin,
    holo_base_msg_common_ParkingSlotFramef_on_type_registered,
    holo_base_msg_common_ParkingSlotFramef_on_type_unregistered,

};

/* --------------------------------------------------------------------------
*  Type holo_base_msg_common_ParkingSlotFramef Plugin Methods
* -------------------------------------------------------------------------- */

struct DDS_TypePluginI*
holo_base_msg_common_ParkingSlotFramefTypePlugin_get(void) 
{ 
    return &holo_base_msg_common_ParkingSlotFramef_fv_TypePluginI;
} 

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_common_ParkingSlotFramefTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property)
{
    return DDS_TypePluginDefault_create(&holo_base_msg_common_ParkingSlotFramef_fv_TypePluginI,
    participant,dp_qos,
    endpoint_mode,endpoint,qos,
    property);
}

RTI_PRIVATE RTI_BOOL
holo_base_msg_common_ParkingSlotFramefTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin)
{
    return DDS_TypePluginDefault_delete(plugin);
}

struct DDS_TypePlugin*
holo_base_msg_common_ParkingSlotFramefWriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_common_ParkingSlotFramef_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_WRITER,
        (DDS_TypePluginEndpoint*)writer,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

struct DDS_TypePlugin*
holo_base_msg_common_ParkingSlotFramefReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_common_ParkingSlotFramef_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_READER,
        (DDS_TypePluginEndpoint*)reader,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

const char*
holo_base_msg_common_ParkingSlotFramefTypePlugin_get_default_type_name(void) 
{ 
    return holo_base_msg_common_ParkingSlotFramefTYPENAME;
} 

NDDS_TypePluginKeyKind 
holo_base_msg_common_ParkingSlotFramefI_get_key_kind(void)
{
    return holo_base_msg_common_ParkingSlotFramef_fv_TypePluginI.key_kind;
}

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------
Typed-endpoint support for C++:
* -------------------------------------------------------------------------- */

void* 
holo_base_msg_common_ParkingSlotFramedPlugin_create_typed_datawriter(void *writer)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * so writer is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataWriter *cpp_writer = 
    new holo_base_msg_common_ParkingSlotFramedDataWriter((DDS_DataWriter*)writer);

    return cpp_writer;   
}

#ifndef RTI_CERT
void 
holo_base_msg_common_ParkingSlotFramedPlugin_delete_typed_datawriter(void *wrapper)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * and DDS_Publisher_delete_datawriter so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataWriter_impl *cpp_writer = (DDSDataWriter_impl *) wrapper;

    holo_base_msg_common_ParkingSlotFramedDataWriter *t_writer = 
    static_cast<holo_base_msg_common_ParkingSlotFramedDataWriter *>(cpp_writer);

    delete t_writer;
}
#endif

void* 
holo_base_msg_common_ParkingSlotFramedPlugin_create_typed_datareader(void *reader)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * so reader is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataReader *cpp_reader = 
    new holo_base_msg_common_ParkingSlotFramedDataReader((DDS_DataReader*)reader);

    return cpp_reader;      
}

#ifndef RTI_CERT
void
holo_base_msg_common_ParkingSlotFramedPlugin_delete_typed_datareader(void *wrapper)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * and DDS_Subscriber_delete_datareader so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataReader_impl *cpp_reader = (DDSDataReader_impl *) wrapper;

    holo_base_msg_common_ParkingSlotFramedDataReader *t_reader = 
    static_cast<holo_base_msg_common_ParkingSlotFramedDataReader *>(cpp_reader);

    delete t_reader;
}
#endif

/* --------------------------------------------------------------------------
*  Sample Support functions:
* -------------------------------------------------------------------------- */
RTI_BOOL
holo_base_msg_common_ParkingSlotFramedPlugin_create_sample(struct DDS_TypePlugin *plugin,
void **sample)
{
    UNUSED_ARG(plugin);

    *sample = (void *) holo_base_msg_common_ParkingSlotFramed_create();
    return (*sample != NULL);
}

#ifndef RTI_CERT
RTI_BOOL
holo_base_msg_common_ParkingSlotFramedPlugin_delete_sample(struct DDS_TypePlugin *plugin, 
void *sample)
{
    UNUSED_ARG(plugin);

    holo_base_msg_common_ParkingSlotFramed_delete((holo_base_msg_common_ParkingSlotFramed *) sample);
    return RTI_TRUE;
}
#endif

RTI_BOOL 
holo_base_msg_common_ParkingSlotFramedPlugin_copy_sample(struct DDS_TypePlugin *plugin, 
void *dst, 
const void *src)
{
    UNUSED_ARG(plugin);

    return holo_base_msg_common_ParkingSlotFramed_copy(
        (holo_base_msg_common_ParkingSlotFramed*)dst,
        (const holo_base_msg_common_ParkingSlotFramed*)src);
}
/* --------------------------------------------------------------------------
*  Type holo_base_msg_common_ParkingSlotFramed Plugin Instantiation
* -------------------------------------------------------------------------- */

NDDSCDREncapsulation holo_base_msg_common_ParkingSlotFramedEncapsulationKind[] =
{ 
    {
        DDS_ENCAPSULATION_ID_CDR_LE,
        DDS_ENCAPSULATION_ID_CDR_BE,
        0
    }
};

NDDSCDREncapsulation holo_base_msg_common_ParkingSlotFramedV2EncapsulationKind[] =
{ 
    {

        DDS_ENCAPSULATION_ID_XCDR2_A_LE,
        DDS_ENCAPSULATION_ID_XCDR2_A_BE,
        0

    }
};

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_common_ParkingSlotFramedTypePlugin_initialize_sample(struct DDS_TypePlugin *plugin, void *buffer)
{
    UNUSED_ARG(plugin);
    return holo_base_msg_common_ParkingSlotFramed_initialize((holo_base_msg_common_ParkingSlotFramed*)buffer);
}

RTI_PRIVATE RTI_UINT32 
holo_base_msg_common_ParkingSlotFramed_get_user_sample_size(
    struct DDS_TypePlugin *tp)
{
    UNUSED_ARG(tp);        
    return sizeof(holo_base_msg_common_ParkingSlotFramed);
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_common_ParkingSlotFramed_cdr_initialize(void *init_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)init_config;
    void *sample;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_common_ParkingSlotFramedPlugin_create_sample(&plugin->_parent,&sample))
    {
        return RTI_FALSE;
    }

    sh->sample = sample;

    return RTI_TRUE;
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_common_ParkingSlotFramed_cdr_finalize(void *finalize_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)finalize_config;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_common_ParkingSlotFramedPlugin_delete_sample(&plugin->_parent,sh->sample))
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

RTI_PRIVATE void 
holo_base_msg_common_ParkingSlotFramedTypePlugin_return_sample(
    struct DDS_TypePlugin *tp,
    struct DDS_TypePluginSampleHolder *sample)
{
    holo_base_msg_common_ParkingSlotFramed_finalize_optional_members((holo_base_msg_common_ParkingSlotFramed*)sample->sample, RTI_FALSE);
    XCDR_GenericStreamPlugin_return_sample(tp, sample);
}

RTI_PRIVATE struct DDS_TypeMemoryPlugin*
holo_base_msg_common_ParkingSlotFramedXTypesHeapPlugin_create(struct DDS_TypePlugin *tp,
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
        holo_base_msg_common_ParkingSlotFramed_cdr_initialize,
        holo_base_msg_common_ParkingSlotFramed_cdr_finalize,
        sizeof(holo_base_msg_common_ParkingSlotFramed),
        RTI_FALSE
        );
}

RTI_PRIVATE struct DDS_TypeMemoryI holo_base_msg_common_ParkingSlotFramed_fv_XTypesHeapPluginI =
{
    RTI_MEMORY_MANAGER_HEAP,
    RTI_MEMORY_TYPE_HEAP,
    holo_base_msg_common_ParkingSlotFramedPlugin_create_sample,
    #ifndef RTI_CERT
    holo_base_msg_common_ParkingSlotFramedPlugin_delete_sample,
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
    holo_base_msg_common_ParkingSlotFramedXTypesHeapPlugin_create,
    DDS_XTypesHeapPlugin_delete
};	

RTI_PRIVATE DDS_Boolean 
holo_base_msg_common_ParkingSlotFramed_on_type_registered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    struct RTIXCdrInterpreterProgramsGenProperty programProperty =
    RTIXCdrInterpreterProgramsGenProperty_INITIALIZER;

    programProperty.resolveAlias = RTI_XCDR_TRUE;
    programProperty.inlineStruct = RTI_XCDR_TRUE;
    programProperty.optimizeEnum = RTI_XCDR_TRUE;

    programs = RTIXCdrInterpreterPrograms_new(
        (RTIXCdrTypeCode *)holo_base_msg_common_ParkingSlotFramed_get_typecode(),
        &programProperty,
        RTI_XCDR_PROGRAM_MASK_TYPEPLUGIN
        );

    if (programs == NULL)
    {
        return DDS_BOOLEAN_FALSE;
    }

    DDS_TypeImpl_set_programs(type_impl, programs);
    DDS_TypeImpl_set_typecode(type_impl,  holo_base_msg_common_ParkingSlotFramed_get_typecode());

    return DDS_BOOLEAN_TRUE;
}
RTI_PRIVATE DDS_Boolean 
holo_base_msg_common_ParkingSlotFramed_on_type_unregistered(struct DDS_TypeImpl* type_impl)
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
struct DDS_TypeEncapsulationI holo_base_msg_common_ParkingSlotFramed_fv_XCDRv1PluginI =
{
    DDS_XCDR_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_common_ParkingSlotFramedEncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,
    holo_base_msg_common_ParkingSlotFramedTypePlugin_return_sample,
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv1_StreamPlugin_get_serialized_sample_size,
    XCDRv1_StreamPlugin_create,
    XCDRv1_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI holo_base_msg_common_ParkingSlotFramed_fv_XCDRv2PluginI =
{
    DDS_XCDR2_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_common_ParkingSlotFramedV2EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,

    holo_base_msg_common_ParkingSlotFramedTypePlugin_return_sample,   
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv2_StreamPlugin_get_serialized_sample_size,
    XCDRv2_StreamPlugin_create,
    XCDRv2_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI *holo_base_msg_common_ParkingSlotFramed_fv_WirePlugins[] =
{
    &holo_base_msg_common_ParkingSlotFramed_fv_XCDRv2PluginI,
    &holo_base_msg_common_ParkingSlotFramed_fv_XCDRv1PluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypeMemoryI *holo_base_msg_common_ParkingSlotFramed_fv_MemoryPlugins[] =
{
    &holo_base_msg_common_ParkingSlotFramed_fv_XTypesHeapPluginI,

    NULL
};

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_common_ParkingSlotFramedTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property);
RTI_PRIVATE RTI_BOOL
holo_base_msg_common_ParkingSlotFramedTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin);

RTI_PRIVATE struct DDS_TypePluginI holo_base_msg_common_ParkingSlotFramed_fv_TypePluginI =
{
    /**************************************************************************
    *                   Type information functions
    **************************************************************************/

    NULL,                       /* DDS_TypeCode_t* */
    NDDS_TYPEPLUGIN_NO_KEY,     /* NDDS_TypePluginKeyKind */

    NDDS_TYPEPLUGIN_EH_LOCATION_PAYLOAD,
    holo_base_msg_common_ParkingSlotFramed_get_user_sample_size,   
    RTI_MEMORY_TYPE_HEAP,
    NULL,
    holo_base_msg_common_ParkingSlotFramedPlugin_copy_sample,

    holo_base_msg_common_ParkingSlotFramedTypePlugin_initialize_sample,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    holo_base_msg_common_ParkingSlotFramed_fv_MemoryPlugins,
    holo_base_msg_common_ParkingSlotFramed_fv_WirePlugins,

    /**************************************************************************
    *       Helper APIs to create language binding wrapper Functions
    **************************************************************************/

    holo_base_msg_common_ParkingSlotFramedPlugin_create_typed_datawriter,
    #ifndef RTI_CERT
    holo_base_msg_common_ParkingSlotFramedPlugin_delete_typed_datawriter,
    #else
    NULL,
    #endif
    holo_base_msg_common_ParkingSlotFramedPlugin_create_typed_datareader,
    #ifndef RTI_CERT
    holo_base_msg_common_ParkingSlotFramedPlugin_delete_typed_datareader,
    #else
    NULL,
    #endif
    holo_base_msg_common_ParkingSlotFramedTypePlugin_create_plugin,
    holo_base_msg_common_ParkingSlotFramedTypePlugin_delete_plugin,
    holo_base_msg_common_ParkingSlotFramed_on_type_registered,
    holo_base_msg_common_ParkingSlotFramed_on_type_unregistered,

};

/* --------------------------------------------------------------------------
*  Type holo_base_msg_common_ParkingSlotFramed Plugin Methods
* -------------------------------------------------------------------------- */

struct DDS_TypePluginI*
holo_base_msg_common_ParkingSlotFramedTypePlugin_get(void) 
{ 
    return &holo_base_msg_common_ParkingSlotFramed_fv_TypePluginI;
} 

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_common_ParkingSlotFramedTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property)
{
    return DDS_TypePluginDefault_create(&holo_base_msg_common_ParkingSlotFramed_fv_TypePluginI,
    participant,dp_qos,
    endpoint_mode,endpoint,qos,
    property);
}

RTI_PRIVATE RTI_BOOL
holo_base_msg_common_ParkingSlotFramedTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin)
{
    return DDS_TypePluginDefault_delete(plugin);
}

struct DDS_TypePlugin*
holo_base_msg_common_ParkingSlotFramedWriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_common_ParkingSlotFramed_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_WRITER,
        (DDS_TypePluginEndpoint*)writer,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

struct DDS_TypePlugin*
holo_base_msg_common_ParkingSlotFramedReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_common_ParkingSlotFramed_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_READER,
        (DDS_TypePluginEndpoint*)reader,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

const char*
holo_base_msg_common_ParkingSlotFramedTypePlugin_get_default_type_name(void) 
{ 
    return holo_base_msg_common_ParkingSlotFramedTYPENAME;
} 

NDDS_TypePluginKeyKind 
holo_base_msg_common_ParkingSlotFramedI_get_key_kind(void)
{
    return holo_base_msg_common_ParkingSlotFramed_fv_TypePluginI.key_kind;
}

