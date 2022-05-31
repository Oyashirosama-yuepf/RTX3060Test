/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ObstacleSet.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "ObstacleSet.h"
#include "reda/reda_bufferpool.h"
#include "xcdr/xcdr_interpreter.h"
#include "dds_c/dds_c_xcdr_type_plugin.h"
#include "ObstacleSetPlugin.h"
#include "ObstacleSetSupport.h"

/*** SOURCE_BEGIN ***/
#ifndef UNUSED_ARG
#define UNUSED_ARG(x) (void)(x)
#endif

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */

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
holo_base_msg_obstacle_ObstacleGeneralPlugin_create_typed_datawriter(void *writer)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * so writer is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataWriter *cpp_writer = 
    new holo_base_msg_obstacle_ObstacleGeneralDataWriter((DDS_DataWriter*)writer);

    return cpp_writer;   
}

#ifndef RTI_CERT
void 
holo_base_msg_obstacle_ObstacleGeneralPlugin_delete_typed_datawriter(void *wrapper)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * and DDS_Publisher_delete_datawriter so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataWriter_impl *cpp_writer = (DDSDataWriter_impl *) wrapper;

    holo_base_msg_obstacle_ObstacleGeneralDataWriter *t_writer = 
    static_cast<holo_base_msg_obstacle_ObstacleGeneralDataWriter *>(cpp_writer);

    delete t_writer;
}
#endif

void* 
holo_base_msg_obstacle_ObstacleGeneralPlugin_create_typed_datareader(void *reader)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * so reader is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataReader *cpp_reader = 
    new holo_base_msg_obstacle_ObstacleGeneralDataReader((DDS_DataReader*)reader);

    return cpp_reader;      
}

#ifndef RTI_CERT
void
holo_base_msg_obstacle_ObstacleGeneralPlugin_delete_typed_datareader(void *wrapper)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * and DDS_Subscriber_delete_datareader so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataReader_impl *cpp_reader = (DDSDataReader_impl *) wrapper;

    holo_base_msg_obstacle_ObstacleGeneralDataReader *t_reader = 
    static_cast<holo_base_msg_obstacle_ObstacleGeneralDataReader *>(cpp_reader);

    delete t_reader;
}
#endif

/* --------------------------------------------------------------------------
*  Sample Support functions:
* -------------------------------------------------------------------------- */
RTI_BOOL
holo_base_msg_obstacle_ObstacleGeneralPlugin_create_sample(struct DDS_TypePlugin *plugin,
void **sample)
{
    UNUSED_ARG(plugin);

    *sample = (void *) holo_base_msg_obstacle_ObstacleGeneral_create();
    return (*sample != NULL);
}

#ifndef RTI_CERT
RTI_BOOL
holo_base_msg_obstacle_ObstacleGeneralPlugin_delete_sample(struct DDS_TypePlugin *plugin, 
void *sample)
{
    UNUSED_ARG(plugin);

    holo_base_msg_obstacle_ObstacleGeneral_delete((holo_base_msg_obstacle_ObstacleGeneral *) sample);
    return RTI_TRUE;
}
#endif

RTI_BOOL 
holo_base_msg_obstacle_ObstacleGeneralPlugin_copy_sample(struct DDS_TypePlugin *plugin, 
void *dst, 
const void *src)
{
    UNUSED_ARG(plugin);

    return holo_base_msg_obstacle_ObstacleGeneral_copy(
        (holo_base_msg_obstacle_ObstacleGeneral*)dst,
        (const holo_base_msg_obstacle_ObstacleGeneral*)src);
}
/* --------------------------------------------------------------------------
*  Type holo_base_msg_obstacle_ObstacleGeneral Plugin Instantiation
* -------------------------------------------------------------------------- */

NDDSCDREncapsulation holo_base_msg_obstacle_ObstacleGeneralEncapsulationKind[] =
{ 
    {
        DDS_ENCAPSULATION_ID_CDR_LE,
        DDS_ENCAPSULATION_ID_CDR_BE,
        0
    }
};

NDDSCDREncapsulation holo_base_msg_obstacle_ObstacleGeneralV2EncapsulationKind[] =
{ 
    {

        DDS_ENCAPSULATION_ID_XCDR2_A_LE,
        DDS_ENCAPSULATION_ID_XCDR2_A_BE,
        0

    }
};

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleGeneralTypePlugin_initialize_sample(struct DDS_TypePlugin *plugin, void *buffer)
{
    UNUSED_ARG(plugin);
    return holo_base_msg_obstacle_ObstacleGeneral_initialize((holo_base_msg_obstacle_ObstacleGeneral*)buffer);
}

RTI_PRIVATE RTI_UINT32 
holo_base_msg_obstacle_ObstacleGeneral_get_user_sample_size(
    struct DDS_TypePlugin *tp)
{
    UNUSED_ARG(tp);        
    return sizeof(holo_base_msg_obstacle_ObstacleGeneral);
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleGeneral_cdr_initialize(void *init_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)init_config;
    void *sample;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_obstacle_ObstacleGeneralPlugin_create_sample(&plugin->_parent,&sample))
    {
        return RTI_FALSE;
    }

    sh->sample = sample;

    return RTI_TRUE;
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleGeneral_cdr_finalize(void *finalize_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)finalize_config;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_obstacle_ObstacleGeneralPlugin_delete_sample(&plugin->_parent,sh->sample))
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

RTI_PRIVATE void 
holo_base_msg_obstacle_ObstacleGeneralTypePlugin_return_sample(
    struct DDS_TypePlugin *tp,
    struct DDS_TypePluginSampleHolder *sample)
{
    holo_base_msg_obstacle_ObstacleGeneral_finalize_optional_members((holo_base_msg_obstacle_ObstacleGeneral*)sample->sample, RTI_FALSE);
    XCDR_GenericStreamPlugin_return_sample(tp, sample);
}

RTI_PRIVATE struct DDS_TypeMemoryPlugin*
holo_base_msg_obstacle_ObstacleGeneralXTypesHeapPlugin_create(struct DDS_TypePlugin *tp,
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
        holo_base_msg_obstacle_ObstacleGeneral_cdr_initialize,
        holo_base_msg_obstacle_ObstacleGeneral_cdr_finalize,
        sizeof(holo_base_msg_obstacle_ObstacleGeneral),
        RTI_FALSE
        );
}

RTI_PRIVATE struct DDS_TypeMemoryI holo_base_msg_obstacle_ObstacleGeneral_fv_XTypesHeapPluginI =
{
    RTI_MEMORY_MANAGER_HEAP,
    RTI_MEMORY_TYPE_HEAP,
    holo_base_msg_obstacle_ObstacleGeneralPlugin_create_sample,
    #ifndef RTI_CERT
    holo_base_msg_obstacle_ObstacleGeneralPlugin_delete_sample,
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
    holo_base_msg_obstacle_ObstacleGeneralXTypesHeapPlugin_create,
    DDS_XTypesHeapPlugin_delete
};	

RTI_PRIVATE DDS_Boolean 
holo_base_msg_obstacle_ObstacleGeneral_on_type_registered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    struct RTIXCdrInterpreterProgramsGenProperty programProperty =
    RTIXCdrInterpreterProgramsGenProperty_INITIALIZER;

    programProperty.resolveAlias = RTI_XCDR_TRUE;
    programProperty.inlineStruct = RTI_XCDR_TRUE;
    programProperty.optimizeEnum = RTI_XCDR_TRUE;

    programs = RTIXCdrInterpreterPrograms_new(
        (RTIXCdrTypeCode *)holo_base_msg_obstacle_ObstacleGeneral_get_typecode(),
        &programProperty,
        RTI_XCDR_PROGRAM_MASK_TYPEPLUGIN
        );

    if (programs == NULL)
    {
        return DDS_BOOLEAN_FALSE;
    }

    DDS_TypeImpl_set_programs(type_impl, programs);
    DDS_TypeImpl_set_typecode(type_impl,  holo_base_msg_obstacle_ObstacleGeneral_get_typecode());

    return DDS_BOOLEAN_TRUE;
}
RTI_PRIVATE DDS_Boolean 
holo_base_msg_obstacle_ObstacleGeneral_on_type_unregistered(struct DDS_TypeImpl* type_impl)
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
struct DDS_TypeEncapsulationI holo_base_msg_obstacle_ObstacleGeneral_fv_XCDRv1PluginI =
{
    DDS_XCDR_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_obstacle_ObstacleGeneralEncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,
    holo_base_msg_obstacle_ObstacleGeneralTypePlugin_return_sample,
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv1_StreamPlugin_get_serialized_sample_size,
    XCDRv1_StreamPlugin_create,
    XCDRv1_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI holo_base_msg_obstacle_ObstacleGeneral_fv_XCDRv2PluginI =
{
    DDS_XCDR2_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_obstacle_ObstacleGeneralV2EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,

    holo_base_msg_obstacle_ObstacleGeneralTypePlugin_return_sample,   
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv2_StreamPlugin_get_serialized_sample_size,
    XCDRv2_StreamPlugin_create,
    XCDRv2_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI *holo_base_msg_obstacle_ObstacleGeneral_fv_WirePlugins[] =
{
    &holo_base_msg_obstacle_ObstacleGeneral_fv_XCDRv2PluginI,
    &holo_base_msg_obstacle_ObstacleGeneral_fv_XCDRv1PluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypeMemoryI *holo_base_msg_obstacle_ObstacleGeneral_fv_MemoryPlugins[] =
{
    &holo_base_msg_obstacle_ObstacleGeneral_fv_XTypesHeapPluginI,

    NULL
};

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleGeneralTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property);
RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleGeneralTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin);

RTI_PRIVATE struct DDS_TypePluginI holo_base_msg_obstacle_ObstacleGeneral_fv_TypePluginI =
{
    /**************************************************************************
    *                   Type information functions
    **************************************************************************/

    NULL,                       /* DDS_TypeCode_t* */
    NDDS_TYPEPLUGIN_NO_KEY,     /* NDDS_TypePluginKeyKind */

    NDDS_TYPEPLUGIN_EH_LOCATION_PAYLOAD,
    holo_base_msg_obstacle_ObstacleGeneral_get_user_sample_size,   
    RTI_MEMORY_TYPE_HEAP,
    NULL,
    holo_base_msg_obstacle_ObstacleGeneralPlugin_copy_sample,

    holo_base_msg_obstacle_ObstacleGeneralTypePlugin_initialize_sample,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    holo_base_msg_obstacle_ObstacleGeneral_fv_MemoryPlugins,
    holo_base_msg_obstacle_ObstacleGeneral_fv_WirePlugins,

    /**************************************************************************
    *       Helper APIs to create language binding wrapper Functions
    **************************************************************************/

    holo_base_msg_obstacle_ObstacleGeneralPlugin_create_typed_datawriter,
    #ifndef RTI_CERT
    holo_base_msg_obstacle_ObstacleGeneralPlugin_delete_typed_datawriter,
    #else
    NULL,
    #endif
    holo_base_msg_obstacle_ObstacleGeneralPlugin_create_typed_datareader,
    #ifndef RTI_CERT
    holo_base_msg_obstacle_ObstacleGeneralPlugin_delete_typed_datareader,
    #else
    NULL,
    #endif
    holo_base_msg_obstacle_ObstacleGeneralTypePlugin_create_plugin,
    holo_base_msg_obstacle_ObstacleGeneralTypePlugin_delete_plugin,
    holo_base_msg_obstacle_ObstacleGeneral_on_type_registered,
    holo_base_msg_obstacle_ObstacleGeneral_on_type_unregistered,

};

/* --------------------------------------------------------------------------
*  Type holo_base_msg_obstacle_ObstacleGeneral Plugin Methods
* -------------------------------------------------------------------------- */

struct DDS_TypePluginI*
holo_base_msg_obstacle_ObstacleGeneralTypePlugin_get(void) 
{ 
    return &holo_base_msg_obstacle_ObstacleGeneral_fv_TypePluginI;
} 

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleGeneralTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property)
{
    return DDS_TypePluginDefault_create(&holo_base_msg_obstacle_ObstacleGeneral_fv_TypePluginI,
    participant,dp_qos,
    endpoint_mode,endpoint,qos,
    property);
}

RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleGeneralTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin)
{
    return DDS_TypePluginDefault_delete(plugin);
}

struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleGeneralWriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_obstacle_ObstacleGeneral_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_WRITER,
        (DDS_TypePluginEndpoint*)writer,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleGeneralReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_obstacle_ObstacleGeneral_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_READER,
        (DDS_TypePluginEndpoint*)reader,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

const char*
holo_base_msg_obstacle_ObstacleGeneralTypePlugin_get_default_type_name(void) 
{ 
    return holo_base_msg_obstacle_ObstacleGeneralTYPENAME;
} 

NDDS_TypePluginKeyKind 
holo_base_msg_obstacle_ObstacleGeneralI_get_key_kind(void)
{
    return holo_base_msg_obstacle_ObstacleGeneral_fv_TypePluginI.key_kind;
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
holo_base_msg_obstacle_ObstacleGeneralListPlugin_create_typed_datawriter(void *writer)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * so writer is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataWriter *cpp_writer = 
    new holo_base_msg_obstacle_ObstacleGeneralListDataWriter((DDS_DataWriter*)writer);

    return cpp_writer;   
}

#ifndef RTI_CERT
void 
holo_base_msg_obstacle_ObstacleGeneralListPlugin_delete_typed_datawriter(void *wrapper)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * and DDS_Publisher_delete_datawriter so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataWriter_impl *cpp_writer = (DDSDataWriter_impl *) wrapper;

    holo_base_msg_obstacle_ObstacleGeneralListDataWriter *t_writer = 
    static_cast<holo_base_msg_obstacle_ObstacleGeneralListDataWriter *>(cpp_writer);

    delete t_writer;
}
#endif

void* 
holo_base_msg_obstacle_ObstacleGeneralListPlugin_create_typed_datareader(void *reader)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * so reader is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataReader *cpp_reader = 
    new holo_base_msg_obstacle_ObstacleGeneralListDataReader((DDS_DataReader*)reader);

    return cpp_reader;      
}

#ifndef RTI_CERT
void
holo_base_msg_obstacle_ObstacleGeneralListPlugin_delete_typed_datareader(void *wrapper)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * and DDS_Subscriber_delete_datareader so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataReader_impl *cpp_reader = (DDSDataReader_impl *) wrapper;

    holo_base_msg_obstacle_ObstacleGeneralListDataReader *t_reader = 
    static_cast<holo_base_msg_obstacle_ObstacleGeneralListDataReader *>(cpp_reader);

    delete t_reader;
}
#endif

/* --------------------------------------------------------------------------
*  Sample Support functions:
* -------------------------------------------------------------------------- */
RTI_BOOL
holo_base_msg_obstacle_ObstacleGeneralListPlugin_create_sample(struct DDS_TypePlugin *plugin,
void **sample)
{
    UNUSED_ARG(plugin);

    *sample = (void *) holo_base_msg_obstacle_ObstacleGeneralList_create();
    return (*sample != NULL);
}

#ifndef RTI_CERT
RTI_BOOL
holo_base_msg_obstacle_ObstacleGeneralListPlugin_delete_sample(struct DDS_TypePlugin *plugin, 
void *sample)
{
    UNUSED_ARG(plugin);

    holo_base_msg_obstacle_ObstacleGeneralList_delete((holo_base_msg_obstacle_ObstacleGeneralList *) sample);
    return RTI_TRUE;
}
#endif

RTI_BOOL 
holo_base_msg_obstacle_ObstacleGeneralListPlugin_copy_sample(struct DDS_TypePlugin *plugin, 
void *dst, 
const void *src)
{
    UNUSED_ARG(plugin);

    return holo_base_msg_obstacle_ObstacleGeneralList_copy(
        (holo_base_msg_obstacle_ObstacleGeneralList*)dst,
        (const holo_base_msg_obstacle_ObstacleGeneralList*)src);
}
/* --------------------------------------------------------------------------
*  Type holo_base_msg_obstacle_ObstacleGeneralList Plugin Instantiation
* -------------------------------------------------------------------------- */

NDDSCDREncapsulation holo_base_msg_obstacle_ObstacleGeneralListEncapsulationKind[] =
{ 
    {
        DDS_ENCAPSULATION_ID_CDR_LE,
        DDS_ENCAPSULATION_ID_CDR_BE,
        0
    }
};

NDDSCDREncapsulation holo_base_msg_obstacle_ObstacleGeneralListV2EncapsulationKind[] =
{ 
    {

        DDS_ENCAPSULATION_ID_XCDR2_A_LE,
        DDS_ENCAPSULATION_ID_XCDR2_A_BE,
        0

    }
};

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleGeneralListTypePlugin_initialize_sample(struct DDS_TypePlugin *plugin, void *buffer)
{
    UNUSED_ARG(plugin);
    return holo_base_msg_obstacle_ObstacleGeneralList_initialize((holo_base_msg_obstacle_ObstacleGeneralList*)buffer);
}

RTI_PRIVATE RTI_UINT32 
holo_base_msg_obstacle_ObstacleGeneralList_get_user_sample_size(
    struct DDS_TypePlugin *tp)
{
    UNUSED_ARG(tp);        
    return sizeof(holo_base_msg_obstacle_ObstacleGeneralList);
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleGeneralList_cdr_initialize(void *init_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)init_config;
    void *sample;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_obstacle_ObstacleGeneralListPlugin_create_sample(&plugin->_parent,&sample))
    {
        return RTI_FALSE;
    }

    sh->sample = sample;

    return RTI_TRUE;
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleGeneralList_cdr_finalize(void *finalize_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)finalize_config;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_obstacle_ObstacleGeneralListPlugin_delete_sample(&plugin->_parent,sh->sample))
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

RTI_PRIVATE void 
holo_base_msg_obstacle_ObstacleGeneralListTypePlugin_return_sample(
    struct DDS_TypePlugin *tp,
    struct DDS_TypePluginSampleHolder *sample)
{
    holo_base_msg_obstacle_ObstacleGeneralList_finalize_optional_members((holo_base_msg_obstacle_ObstacleGeneralList*)sample->sample, RTI_FALSE);
    XCDR_GenericStreamPlugin_return_sample(tp, sample);
}

RTI_PRIVATE struct DDS_TypeMemoryPlugin*
holo_base_msg_obstacle_ObstacleGeneralListXTypesHeapPlugin_create(struct DDS_TypePlugin *tp,
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
        holo_base_msg_obstacle_ObstacleGeneralList_cdr_initialize,
        holo_base_msg_obstacle_ObstacleGeneralList_cdr_finalize,
        sizeof(holo_base_msg_obstacle_ObstacleGeneralList),
        RTI_FALSE
        );
}

RTI_PRIVATE struct DDS_TypeMemoryI holo_base_msg_obstacle_ObstacleGeneralList_fv_XTypesHeapPluginI =
{
    RTI_MEMORY_MANAGER_HEAP,
    RTI_MEMORY_TYPE_HEAP,
    holo_base_msg_obstacle_ObstacleGeneralListPlugin_create_sample,
    #ifndef RTI_CERT
    holo_base_msg_obstacle_ObstacleGeneralListPlugin_delete_sample,
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
    holo_base_msg_obstacle_ObstacleGeneralListXTypesHeapPlugin_create,
    DDS_XTypesHeapPlugin_delete
};	

RTI_PRIVATE DDS_Boolean 
holo_base_msg_obstacle_ObstacleGeneralList_on_type_registered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    struct RTIXCdrInterpreterProgramsGenProperty programProperty =
    RTIXCdrInterpreterProgramsGenProperty_INITIALIZER;

    programProperty.resolveAlias = RTI_XCDR_TRUE;
    programProperty.inlineStruct = RTI_XCDR_TRUE;
    programProperty.optimizeEnum = RTI_XCDR_TRUE;

    programs = RTIXCdrInterpreterPrograms_new(
        (RTIXCdrTypeCode *)holo_base_msg_obstacle_ObstacleGeneralList_get_typecode(),
        &programProperty,
        RTI_XCDR_PROGRAM_MASK_TYPEPLUGIN
        );

    if (programs == NULL)
    {
        return DDS_BOOLEAN_FALSE;
    }

    DDS_TypeImpl_set_programs(type_impl, programs);
    DDS_TypeImpl_set_typecode(type_impl,  holo_base_msg_obstacle_ObstacleGeneralList_get_typecode());

    return DDS_BOOLEAN_TRUE;
}
RTI_PRIVATE DDS_Boolean 
holo_base_msg_obstacle_ObstacleGeneralList_on_type_unregistered(struct DDS_TypeImpl* type_impl)
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
struct DDS_TypeEncapsulationI holo_base_msg_obstacle_ObstacleGeneralList_fv_XCDRv1PluginI =
{
    DDS_XCDR_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_obstacle_ObstacleGeneralListEncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,
    holo_base_msg_obstacle_ObstacleGeneralListTypePlugin_return_sample,
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv1_StreamPlugin_get_serialized_sample_size,
    XCDRv1_StreamPlugin_create,
    XCDRv1_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI holo_base_msg_obstacle_ObstacleGeneralList_fv_XCDRv2PluginI =
{
    DDS_XCDR2_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_obstacle_ObstacleGeneralListV2EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,

    holo_base_msg_obstacle_ObstacleGeneralListTypePlugin_return_sample,   
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv2_StreamPlugin_get_serialized_sample_size,
    XCDRv2_StreamPlugin_create,
    XCDRv2_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI *holo_base_msg_obstacle_ObstacleGeneralList_fv_WirePlugins[] =
{
    &holo_base_msg_obstacle_ObstacleGeneralList_fv_XCDRv2PluginI,
    &holo_base_msg_obstacle_ObstacleGeneralList_fv_XCDRv1PluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypeMemoryI *holo_base_msg_obstacle_ObstacleGeneralList_fv_MemoryPlugins[] =
{
    &holo_base_msg_obstacle_ObstacleGeneralList_fv_XTypesHeapPluginI,

    NULL
};

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleGeneralListTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property);
RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleGeneralListTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin);

RTI_PRIVATE struct DDS_TypePluginI holo_base_msg_obstacle_ObstacleGeneralList_fv_TypePluginI =
{
    /**************************************************************************
    *                   Type information functions
    **************************************************************************/

    NULL,                       /* DDS_TypeCode_t* */
    NDDS_TYPEPLUGIN_NO_KEY,     /* NDDS_TypePluginKeyKind */

    NDDS_TYPEPLUGIN_EH_LOCATION_PAYLOAD,
    holo_base_msg_obstacle_ObstacleGeneralList_get_user_sample_size,   
    RTI_MEMORY_TYPE_HEAP,
    NULL,
    holo_base_msg_obstacle_ObstacleGeneralListPlugin_copy_sample,

    holo_base_msg_obstacle_ObstacleGeneralListTypePlugin_initialize_sample,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    holo_base_msg_obstacle_ObstacleGeneralList_fv_MemoryPlugins,
    holo_base_msg_obstacle_ObstacleGeneralList_fv_WirePlugins,

    /**************************************************************************
    *       Helper APIs to create language binding wrapper Functions
    **************************************************************************/

    holo_base_msg_obstacle_ObstacleGeneralListPlugin_create_typed_datawriter,
    #ifndef RTI_CERT
    holo_base_msg_obstacle_ObstacleGeneralListPlugin_delete_typed_datawriter,
    #else
    NULL,
    #endif
    holo_base_msg_obstacle_ObstacleGeneralListPlugin_create_typed_datareader,
    #ifndef RTI_CERT
    holo_base_msg_obstacle_ObstacleGeneralListPlugin_delete_typed_datareader,
    #else
    NULL,
    #endif
    holo_base_msg_obstacle_ObstacleGeneralListTypePlugin_create_plugin,
    holo_base_msg_obstacle_ObstacleGeneralListTypePlugin_delete_plugin,
    holo_base_msg_obstacle_ObstacleGeneralList_on_type_registered,
    holo_base_msg_obstacle_ObstacleGeneralList_on_type_unregistered,

};

/* --------------------------------------------------------------------------
*  Type holo_base_msg_obstacle_ObstacleGeneralList Plugin Methods
* -------------------------------------------------------------------------- */

struct DDS_TypePluginI*
holo_base_msg_obstacle_ObstacleGeneralListTypePlugin_get(void) 
{ 
    return &holo_base_msg_obstacle_ObstacleGeneralList_fv_TypePluginI;
} 

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleGeneralListTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property)
{
    return DDS_TypePluginDefault_create(&holo_base_msg_obstacle_ObstacleGeneralList_fv_TypePluginI,
    participant,dp_qos,
    endpoint_mode,endpoint,qos,
    property);
}

RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleGeneralListTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin)
{
    return DDS_TypePluginDefault_delete(plugin);
}

struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleGeneralListWriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_obstacle_ObstacleGeneralList_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_WRITER,
        (DDS_TypePluginEndpoint*)writer,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleGeneralListReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_obstacle_ObstacleGeneralList_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_READER,
        (DDS_TypePluginEndpoint*)reader,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

const char*
holo_base_msg_obstacle_ObstacleGeneralListTypePlugin_get_default_type_name(void) 
{ 
    return holo_base_msg_obstacle_ObstacleGeneralListTYPENAME;
} 

NDDS_TypePluginKeyKind 
holo_base_msg_obstacle_ObstacleGeneralListI_get_key_kind(void)
{
    return holo_base_msg_obstacle_ObstacleGeneralList_fv_TypePluginI.key_kind;
}

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------
Typed-endpoint support for C++:
* -------------------------------------------------------------------------- */

void* 
holo_base_msg_obstacle_ObstacleRadarPlugin_create_typed_datawriter(void *writer)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * so writer is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataWriter *cpp_writer = 
    new holo_base_msg_obstacle_ObstacleRadarDataWriter((DDS_DataWriter*)writer);

    return cpp_writer;   
}

#ifndef RTI_CERT
void 
holo_base_msg_obstacle_ObstacleRadarPlugin_delete_typed_datawriter(void *wrapper)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * and DDS_Publisher_delete_datawriter so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataWriter_impl *cpp_writer = (DDSDataWriter_impl *) wrapper;

    holo_base_msg_obstacle_ObstacleRadarDataWriter *t_writer = 
    static_cast<holo_base_msg_obstacle_ObstacleRadarDataWriter *>(cpp_writer);

    delete t_writer;
}
#endif

void* 
holo_base_msg_obstacle_ObstacleRadarPlugin_create_typed_datareader(void *reader)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * so reader is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataReader *cpp_reader = 
    new holo_base_msg_obstacle_ObstacleRadarDataReader((DDS_DataReader*)reader);

    return cpp_reader;      
}

#ifndef RTI_CERT
void
holo_base_msg_obstacle_ObstacleRadarPlugin_delete_typed_datareader(void *wrapper)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * and DDS_Subscriber_delete_datareader so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataReader_impl *cpp_reader = (DDSDataReader_impl *) wrapper;

    holo_base_msg_obstacle_ObstacleRadarDataReader *t_reader = 
    static_cast<holo_base_msg_obstacle_ObstacleRadarDataReader *>(cpp_reader);

    delete t_reader;
}
#endif

/* --------------------------------------------------------------------------
*  Sample Support functions:
* -------------------------------------------------------------------------- */
RTI_BOOL
holo_base_msg_obstacle_ObstacleRadarPlugin_create_sample(struct DDS_TypePlugin *plugin,
void **sample)
{
    UNUSED_ARG(plugin);

    *sample = (void *) holo_base_msg_obstacle_ObstacleRadar_create();
    return (*sample != NULL);
}

#ifndef RTI_CERT
RTI_BOOL
holo_base_msg_obstacle_ObstacleRadarPlugin_delete_sample(struct DDS_TypePlugin *plugin, 
void *sample)
{
    UNUSED_ARG(plugin);

    holo_base_msg_obstacle_ObstacleRadar_delete((holo_base_msg_obstacle_ObstacleRadar *) sample);
    return RTI_TRUE;
}
#endif

RTI_BOOL 
holo_base_msg_obstacle_ObstacleRadarPlugin_copy_sample(struct DDS_TypePlugin *plugin, 
void *dst, 
const void *src)
{
    UNUSED_ARG(plugin);

    return holo_base_msg_obstacle_ObstacleRadar_copy(
        (holo_base_msg_obstacle_ObstacleRadar*)dst,
        (const holo_base_msg_obstacle_ObstacleRadar*)src);
}
/* --------------------------------------------------------------------------
*  Type holo_base_msg_obstacle_ObstacleRadar Plugin Instantiation
* -------------------------------------------------------------------------- */

NDDSCDREncapsulation holo_base_msg_obstacle_ObstacleRadarEncapsulationKind[] =
{ 
    {
        DDS_ENCAPSULATION_ID_CDR_LE,
        DDS_ENCAPSULATION_ID_CDR_BE,
        0
    }
};

NDDSCDREncapsulation holo_base_msg_obstacle_ObstacleRadarV2EncapsulationKind[] =
{ 
    {

        DDS_ENCAPSULATION_ID_XCDR2_A_LE,
        DDS_ENCAPSULATION_ID_XCDR2_A_BE,
        0

    }
};

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleRadarTypePlugin_initialize_sample(struct DDS_TypePlugin *plugin, void *buffer)
{
    UNUSED_ARG(plugin);
    return holo_base_msg_obstacle_ObstacleRadar_initialize((holo_base_msg_obstacle_ObstacleRadar*)buffer);
}

RTI_PRIVATE RTI_UINT32 
holo_base_msg_obstacle_ObstacleRadar_get_user_sample_size(
    struct DDS_TypePlugin *tp)
{
    UNUSED_ARG(tp);        
    return sizeof(holo_base_msg_obstacle_ObstacleRadar);
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleRadar_cdr_initialize(void *init_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)init_config;
    void *sample;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_obstacle_ObstacleRadarPlugin_create_sample(&plugin->_parent,&sample))
    {
        return RTI_FALSE;
    }

    sh->sample = sample;

    return RTI_TRUE;
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleRadar_cdr_finalize(void *finalize_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)finalize_config;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_obstacle_ObstacleRadarPlugin_delete_sample(&plugin->_parent,sh->sample))
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

RTI_PRIVATE void 
holo_base_msg_obstacle_ObstacleRadarTypePlugin_return_sample(
    struct DDS_TypePlugin *tp,
    struct DDS_TypePluginSampleHolder *sample)
{
    holo_base_msg_obstacle_ObstacleRadar_finalize_optional_members((holo_base_msg_obstacle_ObstacleRadar*)sample->sample, RTI_FALSE);
    XCDR_GenericStreamPlugin_return_sample(tp, sample);
}

RTI_PRIVATE struct DDS_TypeMemoryPlugin*
holo_base_msg_obstacle_ObstacleRadarXTypesHeapPlugin_create(struct DDS_TypePlugin *tp,
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
        holo_base_msg_obstacle_ObstacleRadar_cdr_initialize,
        holo_base_msg_obstacle_ObstacleRadar_cdr_finalize,
        sizeof(holo_base_msg_obstacle_ObstacleRadar),
        RTI_FALSE
        );
}

RTI_PRIVATE struct DDS_TypeMemoryI holo_base_msg_obstacle_ObstacleRadar_fv_XTypesHeapPluginI =
{
    RTI_MEMORY_MANAGER_HEAP,
    RTI_MEMORY_TYPE_HEAP,
    holo_base_msg_obstacle_ObstacleRadarPlugin_create_sample,
    #ifndef RTI_CERT
    holo_base_msg_obstacle_ObstacleRadarPlugin_delete_sample,
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
    holo_base_msg_obstacle_ObstacleRadarXTypesHeapPlugin_create,
    DDS_XTypesHeapPlugin_delete
};	

RTI_PRIVATE DDS_Boolean 
holo_base_msg_obstacle_ObstacleRadar_on_type_registered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    struct RTIXCdrInterpreterProgramsGenProperty programProperty =
    RTIXCdrInterpreterProgramsGenProperty_INITIALIZER;

    programProperty.resolveAlias = RTI_XCDR_TRUE;
    programProperty.inlineStruct = RTI_XCDR_TRUE;
    programProperty.optimizeEnum = RTI_XCDR_TRUE;

    programs = RTIXCdrInterpreterPrograms_new(
        (RTIXCdrTypeCode *)holo_base_msg_obstacle_ObstacleRadar_get_typecode(),
        &programProperty,
        RTI_XCDR_PROGRAM_MASK_TYPEPLUGIN
        );

    if (programs == NULL)
    {
        return DDS_BOOLEAN_FALSE;
    }

    DDS_TypeImpl_set_programs(type_impl, programs);
    DDS_TypeImpl_set_typecode(type_impl,  holo_base_msg_obstacle_ObstacleRadar_get_typecode());

    return DDS_BOOLEAN_TRUE;
}
RTI_PRIVATE DDS_Boolean 
holo_base_msg_obstacle_ObstacleRadar_on_type_unregistered(struct DDS_TypeImpl* type_impl)
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
struct DDS_TypeEncapsulationI holo_base_msg_obstacle_ObstacleRadar_fv_XCDRv1PluginI =
{
    DDS_XCDR_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_obstacle_ObstacleRadarEncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,
    holo_base_msg_obstacle_ObstacleRadarTypePlugin_return_sample,
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv1_StreamPlugin_get_serialized_sample_size,
    XCDRv1_StreamPlugin_create,
    XCDRv1_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI holo_base_msg_obstacle_ObstacleRadar_fv_XCDRv2PluginI =
{
    DDS_XCDR2_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_obstacle_ObstacleRadarV2EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,

    holo_base_msg_obstacle_ObstacleRadarTypePlugin_return_sample,   
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv2_StreamPlugin_get_serialized_sample_size,
    XCDRv2_StreamPlugin_create,
    XCDRv2_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI *holo_base_msg_obstacle_ObstacleRadar_fv_WirePlugins[] =
{
    &holo_base_msg_obstacle_ObstacleRadar_fv_XCDRv2PluginI,
    &holo_base_msg_obstacle_ObstacleRadar_fv_XCDRv1PluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypeMemoryI *holo_base_msg_obstacle_ObstacleRadar_fv_MemoryPlugins[] =
{
    &holo_base_msg_obstacle_ObstacleRadar_fv_XTypesHeapPluginI,

    NULL
};

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleRadarTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property);
RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleRadarTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin);

RTI_PRIVATE struct DDS_TypePluginI holo_base_msg_obstacle_ObstacleRadar_fv_TypePluginI =
{
    /**************************************************************************
    *                   Type information functions
    **************************************************************************/

    NULL,                       /* DDS_TypeCode_t* */
    NDDS_TYPEPLUGIN_NO_KEY,     /* NDDS_TypePluginKeyKind */

    NDDS_TYPEPLUGIN_EH_LOCATION_PAYLOAD,
    holo_base_msg_obstacle_ObstacleRadar_get_user_sample_size,   
    RTI_MEMORY_TYPE_HEAP,
    NULL,
    holo_base_msg_obstacle_ObstacleRadarPlugin_copy_sample,

    holo_base_msg_obstacle_ObstacleRadarTypePlugin_initialize_sample,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    holo_base_msg_obstacle_ObstacleRadar_fv_MemoryPlugins,
    holo_base_msg_obstacle_ObstacleRadar_fv_WirePlugins,

    /**************************************************************************
    *       Helper APIs to create language binding wrapper Functions
    **************************************************************************/

    holo_base_msg_obstacle_ObstacleRadarPlugin_create_typed_datawriter,
    #ifndef RTI_CERT
    holo_base_msg_obstacle_ObstacleRadarPlugin_delete_typed_datawriter,
    #else
    NULL,
    #endif
    holo_base_msg_obstacle_ObstacleRadarPlugin_create_typed_datareader,
    #ifndef RTI_CERT
    holo_base_msg_obstacle_ObstacleRadarPlugin_delete_typed_datareader,
    #else
    NULL,
    #endif
    holo_base_msg_obstacle_ObstacleRadarTypePlugin_create_plugin,
    holo_base_msg_obstacle_ObstacleRadarTypePlugin_delete_plugin,
    holo_base_msg_obstacle_ObstacleRadar_on_type_registered,
    holo_base_msg_obstacle_ObstacleRadar_on_type_unregistered,

};

/* --------------------------------------------------------------------------
*  Type holo_base_msg_obstacle_ObstacleRadar Plugin Methods
* -------------------------------------------------------------------------- */

struct DDS_TypePluginI*
holo_base_msg_obstacle_ObstacleRadarTypePlugin_get(void) 
{ 
    return &holo_base_msg_obstacle_ObstacleRadar_fv_TypePluginI;
} 

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleRadarTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property)
{
    return DDS_TypePluginDefault_create(&holo_base_msg_obstacle_ObstacleRadar_fv_TypePluginI,
    participant,dp_qos,
    endpoint_mode,endpoint,qos,
    property);
}

RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleRadarTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin)
{
    return DDS_TypePluginDefault_delete(plugin);
}

struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleRadarWriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_obstacle_ObstacleRadar_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_WRITER,
        (DDS_TypePluginEndpoint*)writer,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleRadarReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_obstacle_ObstacleRadar_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_READER,
        (DDS_TypePluginEndpoint*)reader,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

const char*
holo_base_msg_obstacle_ObstacleRadarTypePlugin_get_default_type_name(void) 
{ 
    return holo_base_msg_obstacle_ObstacleRadarTYPENAME;
} 

NDDS_TypePluginKeyKind 
holo_base_msg_obstacle_ObstacleRadarI_get_key_kind(void)
{
    return holo_base_msg_obstacle_ObstacleRadar_fv_TypePluginI.key_kind;
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
holo_base_msg_obstacle_ObstacleRadarListPlugin_create_typed_datawriter(void *writer)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * so writer is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataWriter *cpp_writer = 
    new holo_base_msg_obstacle_ObstacleRadarListDataWriter((DDS_DataWriter*)writer);

    return cpp_writer;   
}

#ifndef RTI_CERT
void 
holo_base_msg_obstacle_ObstacleRadarListPlugin_delete_typed_datawriter(void *wrapper)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * and DDS_Publisher_delete_datawriter so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataWriter_impl *cpp_writer = (DDSDataWriter_impl *) wrapper;

    holo_base_msg_obstacle_ObstacleRadarListDataWriter *t_writer = 
    static_cast<holo_base_msg_obstacle_ObstacleRadarListDataWriter *>(cpp_writer);

    delete t_writer;
}
#endif

void* 
holo_base_msg_obstacle_ObstacleRadarListPlugin_create_typed_datareader(void *reader)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * so reader is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataReader *cpp_reader = 
    new holo_base_msg_obstacle_ObstacleRadarListDataReader((DDS_DataReader*)reader);

    return cpp_reader;      
}

#ifndef RTI_CERT
void
holo_base_msg_obstacle_ObstacleRadarListPlugin_delete_typed_datareader(void *wrapper)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * and DDS_Subscriber_delete_datareader so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataReader_impl *cpp_reader = (DDSDataReader_impl *) wrapper;

    holo_base_msg_obstacle_ObstacleRadarListDataReader *t_reader = 
    static_cast<holo_base_msg_obstacle_ObstacleRadarListDataReader *>(cpp_reader);

    delete t_reader;
}
#endif

/* --------------------------------------------------------------------------
*  Sample Support functions:
* -------------------------------------------------------------------------- */
RTI_BOOL
holo_base_msg_obstacle_ObstacleRadarListPlugin_create_sample(struct DDS_TypePlugin *plugin,
void **sample)
{
    UNUSED_ARG(plugin);

    *sample = (void *) holo_base_msg_obstacle_ObstacleRadarList_create();
    return (*sample != NULL);
}

#ifndef RTI_CERT
RTI_BOOL
holo_base_msg_obstacle_ObstacleRadarListPlugin_delete_sample(struct DDS_TypePlugin *plugin, 
void *sample)
{
    UNUSED_ARG(plugin);

    holo_base_msg_obstacle_ObstacleRadarList_delete((holo_base_msg_obstacle_ObstacleRadarList *) sample);
    return RTI_TRUE;
}
#endif

RTI_BOOL 
holo_base_msg_obstacle_ObstacleRadarListPlugin_copy_sample(struct DDS_TypePlugin *plugin, 
void *dst, 
const void *src)
{
    UNUSED_ARG(plugin);

    return holo_base_msg_obstacle_ObstacleRadarList_copy(
        (holo_base_msg_obstacle_ObstacleRadarList*)dst,
        (const holo_base_msg_obstacle_ObstacleRadarList*)src);
}
/* --------------------------------------------------------------------------
*  Type holo_base_msg_obstacle_ObstacleRadarList Plugin Instantiation
* -------------------------------------------------------------------------- */

NDDSCDREncapsulation holo_base_msg_obstacle_ObstacleRadarListEncapsulationKind[] =
{ 
    {
        DDS_ENCAPSULATION_ID_CDR_LE,
        DDS_ENCAPSULATION_ID_CDR_BE,
        0
    }
};

NDDSCDREncapsulation holo_base_msg_obstacle_ObstacleRadarListV2EncapsulationKind[] =
{ 
    {

        DDS_ENCAPSULATION_ID_XCDR2_A_LE,
        DDS_ENCAPSULATION_ID_XCDR2_A_BE,
        0

    }
};

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleRadarListTypePlugin_initialize_sample(struct DDS_TypePlugin *plugin, void *buffer)
{
    UNUSED_ARG(plugin);
    return holo_base_msg_obstacle_ObstacleRadarList_initialize((holo_base_msg_obstacle_ObstacleRadarList*)buffer);
}

RTI_PRIVATE RTI_UINT32 
holo_base_msg_obstacle_ObstacleRadarList_get_user_sample_size(
    struct DDS_TypePlugin *tp)
{
    UNUSED_ARG(tp);        
    return sizeof(holo_base_msg_obstacle_ObstacleRadarList);
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleRadarList_cdr_initialize(void *init_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)init_config;
    void *sample;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_obstacle_ObstacleRadarListPlugin_create_sample(&plugin->_parent,&sample))
    {
        return RTI_FALSE;
    }

    sh->sample = sample;

    return RTI_TRUE;
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleRadarList_cdr_finalize(void *finalize_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)finalize_config;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_obstacle_ObstacleRadarListPlugin_delete_sample(&plugin->_parent,sh->sample))
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

RTI_PRIVATE void 
holo_base_msg_obstacle_ObstacleRadarListTypePlugin_return_sample(
    struct DDS_TypePlugin *tp,
    struct DDS_TypePluginSampleHolder *sample)
{
    holo_base_msg_obstacle_ObstacleRadarList_finalize_optional_members((holo_base_msg_obstacle_ObstacleRadarList*)sample->sample, RTI_FALSE);
    XCDR_GenericStreamPlugin_return_sample(tp, sample);
}

RTI_PRIVATE struct DDS_TypeMemoryPlugin*
holo_base_msg_obstacle_ObstacleRadarListXTypesHeapPlugin_create(struct DDS_TypePlugin *tp,
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
        holo_base_msg_obstacle_ObstacleRadarList_cdr_initialize,
        holo_base_msg_obstacle_ObstacleRadarList_cdr_finalize,
        sizeof(holo_base_msg_obstacle_ObstacleRadarList),
        RTI_FALSE
        );
}

RTI_PRIVATE struct DDS_TypeMemoryI holo_base_msg_obstacle_ObstacleRadarList_fv_XTypesHeapPluginI =
{
    RTI_MEMORY_MANAGER_HEAP,
    RTI_MEMORY_TYPE_HEAP,
    holo_base_msg_obstacle_ObstacleRadarListPlugin_create_sample,
    #ifndef RTI_CERT
    holo_base_msg_obstacle_ObstacleRadarListPlugin_delete_sample,
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
    holo_base_msg_obstacle_ObstacleRadarListXTypesHeapPlugin_create,
    DDS_XTypesHeapPlugin_delete
};	

RTI_PRIVATE DDS_Boolean 
holo_base_msg_obstacle_ObstacleRadarList_on_type_registered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    struct RTIXCdrInterpreterProgramsGenProperty programProperty =
    RTIXCdrInterpreterProgramsGenProperty_INITIALIZER;

    programProperty.resolveAlias = RTI_XCDR_TRUE;
    programProperty.inlineStruct = RTI_XCDR_TRUE;
    programProperty.optimizeEnum = RTI_XCDR_TRUE;

    programs = RTIXCdrInterpreterPrograms_new(
        (RTIXCdrTypeCode *)holo_base_msg_obstacle_ObstacleRadarList_get_typecode(),
        &programProperty,
        RTI_XCDR_PROGRAM_MASK_TYPEPLUGIN
        );

    if (programs == NULL)
    {
        return DDS_BOOLEAN_FALSE;
    }

    DDS_TypeImpl_set_programs(type_impl, programs);
    DDS_TypeImpl_set_typecode(type_impl,  holo_base_msg_obstacle_ObstacleRadarList_get_typecode());

    return DDS_BOOLEAN_TRUE;
}
RTI_PRIVATE DDS_Boolean 
holo_base_msg_obstacle_ObstacleRadarList_on_type_unregistered(struct DDS_TypeImpl* type_impl)
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
struct DDS_TypeEncapsulationI holo_base_msg_obstacle_ObstacleRadarList_fv_XCDRv1PluginI =
{
    DDS_XCDR_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_obstacle_ObstacleRadarListEncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,
    holo_base_msg_obstacle_ObstacleRadarListTypePlugin_return_sample,
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv1_StreamPlugin_get_serialized_sample_size,
    XCDRv1_StreamPlugin_create,
    XCDRv1_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI holo_base_msg_obstacle_ObstacleRadarList_fv_XCDRv2PluginI =
{
    DDS_XCDR2_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_obstacle_ObstacleRadarListV2EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,

    holo_base_msg_obstacle_ObstacleRadarListTypePlugin_return_sample,   
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv2_StreamPlugin_get_serialized_sample_size,
    XCDRv2_StreamPlugin_create,
    XCDRv2_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI *holo_base_msg_obstacle_ObstacleRadarList_fv_WirePlugins[] =
{
    &holo_base_msg_obstacle_ObstacleRadarList_fv_XCDRv2PluginI,
    &holo_base_msg_obstacle_ObstacleRadarList_fv_XCDRv1PluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypeMemoryI *holo_base_msg_obstacle_ObstacleRadarList_fv_MemoryPlugins[] =
{
    &holo_base_msg_obstacle_ObstacleRadarList_fv_XTypesHeapPluginI,

    NULL
};

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleRadarListTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property);
RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleRadarListTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin);

RTI_PRIVATE struct DDS_TypePluginI holo_base_msg_obstacle_ObstacleRadarList_fv_TypePluginI =
{
    /**************************************************************************
    *                   Type information functions
    **************************************************************************/

    NULL,                       /* DDS_TypeCode_t* */
    NDDS_TYPEPLUGIN_NO_KEY,     /* NDDS_TypePluginKeyKind */

    NDDS_TYPEPLUGIN_EH_LOCATION_PAYLOAD,
    holo_base_msg_obstacle_ObstacleRadarList_get_user_sample_size,   
    RTI_MEMORY_TYPE_HEAP,
    NULL,
    holo_base_msg_obstacle_ObstacleRadarListPlugin_copy_sample,

    holo_base_msg_obstacle_ObstacleRadarListTypePlugin_initialize_sample,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    holo_base_msg_obstacle_ObstacleRadarList_fv_MemoryPlugins,
    holo_base_msg_obstacle_ObstacleRadarList_fv_WirePlugins,

    /**************************************************************************
    *       Helper APIs to create language binding wrapper Functions
    **************************************************************************/

    holo_base_msg_obstacle_ObstacleRadarListPlugin_create_typed_datawriter,
    #ifndef RTI_CERT
    holo_base_msg_obstacle_ObstacleRadarListPlugin_delete_typed_datawriter,
    #else
    NULL,
    #endif
    holo_base_msg_obstacle_ObstacleRadarListPlugin_create_typed_datareader,
    #ifndef RTI_CERT
    holo_base_msg_obstacle_ObstacleRadarListPlugin_delete_typed_datareader,
    #else
    NULL,
    #endif
    holo_base_msg_obstacle_ObstacleRadarListTypePlugin_create_plugin,
    holo_base_msg_obstacle_ObstacleRadarListTypePlugin_delete_plugin,
    holo_base_msg_obstacle_ObstacleRadarList_on_type_registered,
    holo_base_msg_obstacle_ObstacleRadarList_on_type_unregistered,

};

/* --------------------------------------------------------------------------
*  Type holo_base_msg_obstacle_ObstacleRadarList Plugin Methods
* -------------------------------------------------------------------------- */

struct DDS_TypePluginI*
holo_base_msg_obstacle_ObstacleRadarListTypePlugin_get(void) 
{ 
    return &holo_base_msg_obstacle_ObstacleRadarList_fv_TypePluginI;
} 

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleRadarListTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property)
{
    return DDS_TypePluginDefault_create(&holo_base_msg_obstacle_ObstacleRadarList_fv_TypePluginI,
    participant,dp_qos,
    endpoint_mode,endpoint,qos,
    property);
}

RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleRadarListTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin)
{
    return DDS_TypePluginDefault_delete(plugin);
}

struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleRadarListWriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_obstacle_ObstacleRadarList_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_WRITER,
        (DDS_TypePluginEndpoint*)writer,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleRadarListReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_obstacle_ObstacleRadarList_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_READER,
        (DDS_TypePluginEndpoint*)reader,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

const char*
holo_base_msg_obstacle_ObstacleRadarListTypePlugin_get_default_type_name(void) 
{ 
    return holo_base_msg_obstacle_ObstacleRadarListTYPENAME;
} 

NDDS_TypePluginKeyKind 
holo_base_msg_obstacle_ObstacleRadarListI_get_key_kind(void)
{
    return holo_base_msg_obstacle_ObstacleRadarList_fv_TypePluginI.key_kind;
}

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------
Typed-endpoint support for C++:
* -------------------------------------------------------------------------- */

void* 
holo_base_msg_obstacle_ObstacleUssPlugin_create_typed_datawriter(void *writer)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * so writer is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataWriter *cpp_writer = 
    new holo_base_msg_obstacle_ObstacleUssDataWriter((DDS_DataWriter*)writer);

    return cpp_writer;   
}

#ifndef RTI_CERT
void 
holo_base_msg_obstacle_ObstacleUssPlugin_delete_typed_datawriter(void *wrapper)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * and DDS_Publisher_delete_datawriter so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataWriter_impl *cpp_writer = (DDSDataWriter_impl *) wrapper;

    holo_base_msg_obstacle_ObstacleUssDataWriter *t_writer = 
    static_cast<holo_base_msg_obstacle_ObstacleUssDataWriter *>(cpp_writer);

    delete t_writer;
}
#endif

void* 
holo_base_msg_obstacle_ObstacleUssPlugin_create_typed_datareader(void *reader)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * so reader is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataReader *cpp_reader = 
    new holo_base_msg_obstacle_ObstacleUssDataReader((DDS_DataReader*)reader);

    return cpp_reader;      
}

#ifndef RTI_CERT
void
holo_base_msg_obstacle_ObstacleUssPlugin_delete_typed_datareader(void *wrapper)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * and DDS_Subscriber_delete_datareader so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataReader_impl *cpp_reader = (DDSDataReader_impl *) wrapper;

    holo_base_msg_obstacle_ObstacleUssDataReader *t_reader = 
    static_cast<holo_base_msg_obstacle_ObstacleUssDataReader *>(cpp_reader);

    delete t_reader;
}
#endif

/* --------------------------------------------------------------------------
*  Sample Support functions:
* -------------------------------------------------------------------------- */
RTI_BOOL
holo_base_msg_obstacle_ObstacleUssPlugin_create_sample(struct DDS_TypePlugin *plugin,
void **sample)
{
    UNUSED_ARG(plugin);

    *sample = (void *) holo_base_msg_obstacle_ObstacleUss_create();
    return (*sample != NULL);
}

#ifndef RTI_CERT
RTI_BOOL
holo_base_msg_obstacle_ObstacleUssPlugin_delete_sample(struct DDS_TypePlugin *plugin, 
void *sample)
{
    UNUSED_ARG(plugin);

    holo_base_msg_obstacle_ObstacleUss_delete((holo_base_msg_obstacle_ObstacleUss *) sample);
    return RTI_TRUE;
}
#endif

RTI_BOOL 
holo_base_msg_obstacle_ObstacleUssPlugin_copy_sample(struct DDS_TypePlugin *plugin, 
void *dst, 
const void *src)
{
    UNUSED_ARG(plugin);

    return holo_base_msg_obstacle_ObstacleUss_copy(
        (holo_base_msg_obstacle_ObstacleUss*)dst,
        (const holo_base_msg_obstacle_ObstacleUss*)src);
}
/* --------------------------------------------------------------------------
*  Type holo_base_msg_obstacle_ObstacleUss Plugin Instantiation
* -------------------------------------------------------------------------- */

NDDSCDREncapsulation holo_base_msg_obstacle_ObstacleUssEncapsulationKind[] =
{ 
    {
        DDS_ENCAPSULATION_ID_CDR_LE,
        DDS_ENCAPSULATION_ID_CDR_BE,
        0
    }
};

NDDSCDREncapsulation holo_base_msg_obstacle_ObstacleUssV2EncapsulationKind[] =
{ 
    {

        DDS_ENCAPSULATION_ID_XCDR2_A_LE,
        DDS_ENCAPSULATION_ID_XCDR2_A_BE,
        0

    }
};

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleUssTypePlugin_initialize_sample(struct DDS_TypePlugin *plugin, void *buffer)
{
    UNUSED_ARG(plugin);
    return holo_base_msg_obstacle_ObstacleUss_initialize((holo_base_msg_obstacle_ObstacleUss*)buffer);
}

RTI_PRIVATE RTI_UINT32 
holo_base_msg_obstacle_ObstacleUss_get_user_sample_size(
    struct DDS_TypePlugin *tp)
{
    UNUSED_ARG(tp);        
    return sizeof(holo_base_msg_obstacle_ObstacleUss);
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleUss_cdr_initialize(void *init_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)init_config;
    void *sample;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_obstacle_ObstacleUssPlugin_create_sample(&plugin->_parent,&sample))
    {
        return RTI_FALSE;
    }

    sh->sample = sample;

    return RTI_TRUE;
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleUss_cdr_finalize(void *finalize_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)finalize_config;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_obstacle_ObstacleUssPlugin_delete_sample(&plugin->_parent,sh->sample))
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

RTI_PRIVATE void 
holo_base_msg_obstacle_ObstacleUssTypePlugin_return_sample(
    struct DDS_TypePlugin *tp,
    struct DDS_TypePluginSampleHolder *sample)
{
    holo_base_msg_obstacle_ObstacleUss_finalize_optional_members((holo_base_msg_obstacle_ObstacleUss*)sample->sample, RTI_FALSE);
    XCDR_GenericStreamPlugin_return_sample(tp, sample);
}

RTI_PRIVATE struct DDS_TypeMemoryPlugin*
holo_base_msg_obstacle_ObstacleUssXTypesHeapPlugin_create(struct DDS_TypePlugin *tp,
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
        holo_base_msg_obstacle_ObstacleUss_cdr_initialize,
        holo_base_msg_obstacle_ObstacleUss_cdr_finalize,
        sizeof(holo_base_msg_obstacle_ObstacleUss),
        RTI_FALSE
        );
}

RTI_PRIVATE struct DDS_TypeMemoryI holo_base_msg_obstacle_ObstacleUss_fv_XTypesHeapPluginI =
{
    RTI_MEMORY_MANAGER_HEAP,
    RTI_MEMORY_TYPE_HEAP,
    holo_base_msg_obstacle_ObstacleUssPlugin_create_sample,
    #ifndef RTI_CERT
    holo_base_msg_obstacle_ObstacleUssPlugin_delete_sample,
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
    holo_base_msg_obstacle_ObstacleUssXTypesHeapPlugin_create,
    DDS_XTypesHeapPlugin_delete
};	

RTI_PRIVATE DDS_Boolean 
holo_base_msg_obstacle_ObstacleUss_on_type_registered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    struct RTIXCdrInterpreterProgramsGenProperty programProperty =
    RTIXCdrInterpreterProgramsGenProperty_INITIALIZER;

    programProperty.resolveAlias = RTI_XCDR_TRUE;
    programProperty.inlineStruct = RTI_XCDR_TRUE;
    programProperty.optimizeEnum = RTI_XCDR_TRUE;

    programs = RTIXCdrInterpreterPrograms_new(
        (RTIXCdrTypeCode *)holo_base_msg_obstacle_ObstacleUss_get_typecode(),
        &programProperty,
        RTI_XCDR_PROGRAM_MASK_TYPEPLUGIN
        );

    if (programs == NULL)
    {
        return DDS_BOOLEAN_FALSE;
    }

    DDS_TypeImpl_set_programs(type_impl, programs);
    DDS_TypeImpl_set_typecode(type_impl,  holo_base_msg_obstacle_ObstacleUss_get_typecode());

    return DDS_BOOLEAN_TRUE;
}
RTI_PRIVATE DDS_Boolean 
holo_base_msg_obstacle_ObstacleUss_on_type_unregistered(struct DDS_TypeImpl* type_impl)
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
struct DDS_TypeEncapsulationI holo_base_msg_obstacle_ObstacleUss_fv_XCDRv1PluginI =
{
    DDS_XCDR_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_obstacle_ObstacleUssEncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,
    holo_base_msg_obstacle_ObstacleUssTypePlugin_return_sample,
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv1_StreamPlugin_get_serialized_sample_size,
    XCDRv1_StreamPlugin_create,
    XCDRv1_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI holo_base_msg_obstacle_ObstacleUss_fv_XCDRv2PluginI =
{
    DDS_XCDR2_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_obstacle_ObstacleUssV2EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,

    holo_base_msg_obstacle_ObstacleUssTypePlugin_return_sample,   
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv2_StreamPlugin_get_serialized_sample_size,
    XCDRv2_StreamPlugin_create,
    XCDRv2_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI *holo_base_msg_obstacle_ObstacleUss_fv_WirePlugins[] =
{
    &holo_base_msg_obstacle_ObstacleUss_fv_XCDRv2PluginI,
    &holo_base_msg_obstacle_ObstacleUss_fv_XCDRv1PluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypeMemoryI *holo_base_msg_obstacle_ObstacleUss_fv_MemoryPlugins[] =
{
    &holo_base_msg_obstacle_ObstacleUss_fv_XTypesHeapPluginI,

    NULL
};

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleUssTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property);
RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleUssTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin);

RTI_PRIVATE struct DDS_TypePluginI holo_base_msg_obstacle_ObstacleUss_fv_TypePluginI =
{
    /**************************************************************************
    *                   Type information functions
    **************************************************************************/

    NULL,                       /* DDS_TypeCode_t* */
    NDDS_TYPEPLUGIN_NO_KEY,     /* NDDS_TypePluginKeyKind */

    NDDS_TYPEPLUGIN_EH_LOCATION_PAYLOAD,
    holo_base_msg_obstacle_ObstacleUss_get_user_sample_size,   
    RTI_MEMORY_TYPE_HEAP,
    NULL,
    holo_base_msg_obstacle_ObstacleUssPlugin_copy_sample,

    holo_base_msg_obstacle_ObstacleUssTypePlugin_initialize_sample,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    holo_base_msg_obstacle_ObstacleUss_fv_MemoryPlugins,
    holo_base_msg_obstacle_ObstacleUss_fv_WirePlugins,

    /**************************************************************************
    *       Helper APIs to create language binding wrapper Functions
    **************************************************************************/

    holo_base_msg_obstacle_ObstacleUssPlugin_create_typed_datawriter,
    #ifndef RTI_CERT
    holo_base_msg_obstacle_ObstacleUssPlugin_delete_typed_datawriter,
    #else
    NULL,
    #endif
    holo_base_msg_obstacle_ObstacleUssPlugin_create_typed_datareader,
    #ifndef RTI_CERT
    holo_base_msg_obstacle_ObstacleUssPlugin_delete_typed_datareader,
    #else
    NULL,
    #endif
    holo_base_msg_obstacle_ObstacleUssTypePlugin_create_plugin,
    holo_base_msg_obstacle_ObstacleUssTypePlugin_delete_plugin,
    holo_base_msg_obstacle_ObstacleUss_on_type_registered,
    holo_base_msg_obstacle_ObstacleUss_on_type_unregistered,

};

/* --------------------------------------------------------------------------
*  Type holo_base_msg_obstacle_ObstacleUss Plugin Methods
* -------------------------------------------------------------------------- */

struct DDS_TypePluginI*
holo_base_msg_obstacle_ObstacleUssTypePlugin_get(void) 
{ 
    return &holo_base_msg_obstacle_ObstacleUss_fv_TypePluginI;
} 

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleUssTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property)
{
    return DDS_TypePluginDefault_create(&holo_base_msg_obstacle_ObstacleUss_fv_TypePluginI,
    participant,dp_qos,
    endpoint_mode,endpoint,qos,
    property);
}

RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleUssTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin)
{
    return DDS_TypePluginDefault_delete(plugin);
}

struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleUssWriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_obstacle_ObstacleUss_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_WRITER,
        (DDS_TypePluginEndpoint*)writer,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleUssReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_obstacle_ObstacleUss_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_READER,
        (DDS_TypePluginEndpoint*)reader,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

const char*
holo_base_msg_obstacle_ObstacleUssTypePlugin_get_default_type_name(void) 
{ 
    return holo_base_msg_obstacle_ObstacleUssTYPENAME;
} 

NDDS_TypePluginKeyKind 
holo_base_msg_obstacle_ObstacleUssI_get_key_kind(void)
{
    return holo_base_msg_obstacle_ObstacleUss_fv_TypePluginI.key_kind;
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
holo_base_msg_obstacle_ObstacleUssListPlugin_create_typed_datawriter(void *writer)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * so writer is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataWriter *cpp_writer = 
    new holo_base_msg_obstacle_ObstacleUssListDataWriter((DDS_DataWriter*)writer);

    return cpp_writer;   
}

#ifndef RTI_CERT
void 
holo_base_msg_obstacle_ObstacleUssListPlugin_delete_typed_datawriter(void *wrapper)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * and DDS_Publisher_delete_datawriter so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataWriter_impl *cpp_writer = (DDSDataWriter_impl *) wrapper;

    holo_base_msg_obstacle_ObstacleUssListDataWriter *t_writer = 
    static_cast<holo_base_msg_obstacle_ObstacleUssListDataWriter *>(cpp_writer);

    delete t_writer;
}
#endif

void* 
holo_base_msg_obstacle_ObstacleUssListPlugin_create_typed_datareader(void *reader)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * so reader is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataReader *cpp_reader = 
    new holo_base_msg_obstacle_ObstacleUssListDataReader((DDS_DataReader*)reader);

    return cpp_reader;      
}

#ifndef RTI_CERT
void
holo_base_msg_obstacle_ObstacleUssListPlugin_delete_typed_datareader(void *wrapper)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * and DDS_Subscriber_delete_datareader so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataReader_impl *cpp_reader = (DDSDataReader_impl *) wrapper;

    holo_base_msg_obstacle_ObstacleUssListDataReader *t_reader = 
    static_cast<holo_base_msg_obstacle_ObstacleUssListDataReader *>(cpp_reader);

    delete t_reader;
}
#endif

/* --------------------------------------------------------------------------
*  Sample Support functions:
* -------------------------------------------------------------------------- */
RTI_BOOL
holo_base_msg_obstacle_ObstacleUssListPlugin_create_sample(struct DDS_TypePlugin *plugin,
void **sample)
{
    UNUSED_ARG(plugin);

    *sample = (void *) holo_base_msg_obstacle_ObstacleUssList_create();
    return (*sample != NULL);
}

#ifndef RTI_CERT
RTI_BOOL
holo_base_msg_obstacle_ObstacleUssListPlugin_delete_sample(struct DDS_TypePlugin *plugin, 
void *sample)
{
    UNUSED_ARG(plugin);

    holo_base_msg_obstacle_ObstacleUssList_delete((holo_base_msg_obstacle_ObstacleUssList *) sample);
    return RTI_TRUE;
}
#endif

RTI_BOOL 
holo_base_msg_obstacle_ObstacleUssListPlugin_copy_sample(struct DDS_TypePlugin *plugin, 
void *dst, 
const void *src)
{
    UNUSED_ARG(plugin);

    return holo_base_msg_obstacle_ObstacleUssList_copy(
        (holo_base_msg_obstacle_ObstacleUssList*)dst,
        (const holo_base_msg_obstacle_ObstacleUssList*)src);
}
/* --------------------------------------------------------------------------
*  Type holo_base_msg_obstacle_ObstacleUssList Plugin Instantiation
* -------------------------------------------------------------------------- */

NDDSCDREncapsulation holo_base_msg_obstacle_ObstacleUssListEncapsulationKind[] =
{ 
    {
        DDS_ENCAPSULATION_ID_CDR_LE,
        DDS_ENCAPSULATION_ID_CDR_BE,
        0
    }
};

NDDSCDREncapsulation holo_base_msg_obstacle_ObstacleUssListV2EncapsulationKind[] =
{ 
    {

        DDS_ENCAPSULATION_ID_XCDR2_A_LE,
        DDS_ENCAPSULATION_ID_XCDR2_A_BE,
        0

    }
};

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleUssListTypePlugin_initialize_sample(struct DDS_TypePlugin *plugin, void *buffer)
{
    UNUSED_ARG(plugin);
    return holo_base_msg_obstacle_ObstacleUssList_initialize((holo_base_msg_obstacle_ObstacleUssList*)buffer);
}

RTI_PRIVATE RTI_UINT32 
holo_base_msg_obstacle_ObstacleUssList_get_user_sample_size(
    struct DDS_TypePlugin *tp)
{
    UNUSED_ARG(tp);        
    return sizeof(holo_base_msg_obstacle_ObstacleUssList);
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleUssList_cdr_initialize(void *init_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)init_config;
    void *sample;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_obstacle_ObstacleUssListPlugin_create_sample(&plugin->_parent,&sample))
    {
        return RTI_FALSE;
    }

    sh->sample = sample;

    return RTI_TRUE;
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleUssList_cdr_finalize(void *finalize_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)finalize_config;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_obstacle_ObstacleUssListPlugin_delete_sample(&plugin->_parent,sh->sample))
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

RTI_PRIVATE void 
holo_base_msg_obstacle_ObstacleUssListTypePlugin_return_sample(
    struct DDS_TypePlugin *tp,
    struct DDS_TypePluginSampleHolder *sample)
{
    holo_base_msg_obstacle_ObstacleUssList_finalize_optional_members((holo_base_msg_obstacle_ObstacleUssList*)sample->sample, RTI_FALSE);
    XCDR_GenericStreamPlugin_return_sample(tp, sample);
}

RTI_PRIVATE struct DDS_TypeMemoryPlugin*
holo_base_msg_obstacle_ObstacleUssListXTypesHeapPlugin_create(struct DDS_TypePlugin *tp,
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
        holo_base_msg_obstacle_ObstacleUssList_cdr_initialize,
        holo_base_msg_obstacle_ObstacleUssList_cdr_finalize,
        sizeof(holo_base_msg_obstacle_ObstacleUssList),
        RTI_FALSE
        );
}

RTI_PRIVATE struct DDS_TypeMemoryI holo_base_msg_obstacle_ObstacleUssList_fv_XTypesHeapPluginI =
{
    RTI_MEMORY_MANAGER_HEAP,
    RTI_MEMORY_TYPE_HEAP,
    holo_base_msg_obstacle_ObstacleUssListPlugin_create_sample,
    #ifndef RTI_CERT
    holo_base_msg_obstacle_ObstacleUssListPlugin_delete_sample,
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
    holo_base_msg_obstacle_ObstacleUssListXTypesHeapPlugin_create,
    DDS_XTypesHeapPlugin_delete
};	

RTI_PRIVATE DDS_Boolean 
holo_base_msg_obstacle_ObstacleUssList_on_type_registered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    struct RTIXCdrInterpreterProgramsGenProperty programProperty =
    RTIXCdrInterpreterProgramsGenProperty_INITIALIZER;

    programProperty.resolveAlias = RTI_XCDR_TRUE;
    programProperty.inlineStruct = RTI_XCDR_TRUE;
    programProperty.optimizeEnum = RTI_XCDR_TRUE;

    programs = RTIXCdrInterpreterPrograms_new(
        (RTIXCdrTypeCode *)holo_base_msg_obstacle_ObstacleUssList_get_typecode(),
        &programProperty,
        RTI_XCDR_PROGRAM_MASK_TYPEPLUGIN
        );

    if (programs == NULL)
    {
        return DDS_BOOLEAN_FALSE;
    }

    DDS_TypeImpl_set_programs(type_impl, programs);
    DDS_TypeImpl_set_typecode(type_impl,  holo_base_msg_obstacle_ObstacleUssList_get_typecode());

    return DDS_BOOLEAN_TRUE;
}
RTI_PRIVATE DDS_Boolean 
holo_base_msg_obstacle_ObstacleUssList_on_type_unregistered(struct DDS_TypeImpl* type_impl)
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
struct DDS_TypeEncapsulationI holo_base_msg_obstacle_ObstacleUssList_fv_XCDRv1PluginI =
{
    DDS_XCDR_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_obstacle_ObstacleUssListEncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,
    holo_base_msg_obstacle_ObstacleUssListTypePlugin_return_sample,
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv1_StreamPlugin_get_serialized_sample_size,
    XCDRv1_StreamPlugin_create,
    XCDRv1_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI holo_base_msg_obstacle_ObstacleUssList_fv_XCDRv2PluginI =
{
    DDS_XCDR2_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_obstacle_ObstacleUssListV2EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,

    holo_base_msg_obstacle_ObstacleUssListTypePlugin_return_sample,   
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv2_StreamPlugin_get_serialized_sample_size,
    XCDRv2_StreamPlugin_create,
    XCDRv2_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI *holo_base_msg_obstacle_ObstacleUssList_fv_WirePlugins[] =
{
    &holo_base_msg_obstacle_ObstacleUssList_fv_XCDRv2PluginI,
    &holo_base_msg_obstacle_ObstacleUssList_fv_XCDRv1PluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypeMemoryI *holo_base_msg_obstacle_ObstacleUssList_fv_MemoryPlugins[] =
{
    &holo_base_msg_obstacle_ObstacleUssList_fv_XTypesHeapPluginI,

    NULL
};

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleUssListTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property);
RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleUssListTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin);

RTI_PRIVATE struct DDS_TypePluginI holo_base_msg_obstacle_ObstacleUssList_fv_TypePluginI =
{
    /**************************************************************************
    *                   Type information functions
    **************************************************************************/

    NULL,                       /* DDS_TypeCode_t* */
    NDDS_TYPEPLUGIN_NO_KEY,     /* NDDS_TypePluginKeyKind */

    NDDS_TYPEPLUGIN_EH_LOCATION_PAYLOAD,
    holo_base_msg_obstacle_ObstacleUssList_get_user_sample_size,   
    RTI_MEMORY_TYPE_HEAP,
    NULL,
    holo_base_msg_obstacle_ObstacleUssListPlugin_copy_sample,

    holo_base_msg_obstacle_ObstacleUssListTypePlugin_initialize_sample,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    holo_base_msg_obstacle_ObstacleUssList_fv_MemoryPlugins,
    holo_base_msg_obstacle_ObstacleUssList_fv_WirePlugins,

    /**************************************************************************
    *       Helper APIs to create language binding wrapper Functions
    **************************************************************************/

    holo_base_msg_obstacle_ObstacleUssListPlugin_create_typed_datawriter,
    #ifndef RTI_CERT
    holo_base_msg_obstacle_ObstacleUssListPlugin_delete_typed_datawriter,
    #else
    NULL,
    #endif
    holo_base_msg_obstacle_ObstacleUssListPlugin_create_typed_datareader,
    #ifndef RTI_CERT
    holo_base_msg_obstacle_ObstacleUssListPlugin_delete_typed_datareader,
    #else
    NULL,
    #endif
    holo_base_msg_obstacle_ObstacleUssListTypePlugin_create_plugin,
    holo_base_msg_obstacle_ObstacleUssListTypePlugin_delete_plugin,
    holo_base_msg_obstacle_ObstacleUssList_on_type_registered,
    holo_base_msg_obstacle_ObstacleUssList_on_type_unregistered,

};

/* --------------------------------------------------------------------------
*  Type holo_base_msg_obstacle_ObstacleUssList Plugin Methods
* -------------------------------------------------------------------------- */

struct DDS_TypePluginI*
holo_base_msg_obstacle_ObstacleUssListTypePlugin_get(void) 
{ 
    return &holo_base_msg_obstacle_ObstacleUssList_fv_TypePluginI;
} 

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleUssListTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property)
{
    return DDS_TypePluginDefault_create(&holo_base_msg_obstacle_ObstacleUssList_fv_TypePluginI,
    participant,dp_qos,
    endpoint_mode,endpoint,qos,
    property);
}

RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleUssListTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin)
{
    return DDS_TypePluginDefault_delete(plugin);
}

struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleUssListWriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_obstacle_ObstacleUssList_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_WRITER,
        (DDS_TypePluginEndpoint*)writer,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleUssListReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_obstacle_ObstacleUssList_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_READER,
        (DDS_TypePluginEndpoint*)reader,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

const char*
holo_base_msg_obstacle_ObstacleUssListTypePlugin_get_default_type_name(void) 
{ 
    return holo_base_msg_obstacle_ObstacleUssListTYPENAME;
} 

NDDS_TypePluginKeyKind 
holo_base_msg_obstacle_ObstacleUssListI_get_key_kind(void)
{
    return holo_base_msg_obstacle_ObstacleUssList_fv_TypePluginI.key_kind;
}

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------
Typed-endpoint support for C++:
* -------------------------------------------------------------------------- */

void* 
holo_base_msg_obstacle_ObstacleVisionPlugin_create_typed_datawriter(void *writer)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * so writer is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataWriter *cpp_writer = 
    new holo_base_msg_obstacle_ObstacleVisionDataWriter((DDS_DataWriter*)writer);

    return cpp_writer;   
}

#ifndef RTI_CERT
void 
holo_base_msg_obstacle_ObstacleVisionPlugin_delete_typed_datawriter(void *wrapper)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * and DDS_Publisher_delete_datawriter so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataWriter_impl *cpp_writer = (DDSDataWriter_impl *) wrapper;

    holo_base_msg_obstacle_ObstacleVisionDataWriter *t_writer = 
    static_cast<holo_base_msg_obstacle_ObstacleVisionDataWriter *>(cpp_writer);

    delete t_writer;
}
#endif

void* 
holo_base_msg_obstacle_ObstacleVisionPlugin_create_typed_datareader(void *reader)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * so reader is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataReader *cpp_reader = 
    new holo_base_msg_obstacle_ObstacleVisionDataReader((DDS_DataReader*)reader);

    return cpp_reader;      
}

#ifndef RTI_CERT
void
holo_base_msg_obstacle_ObstacleVisionPlugin_delete_typed_datareader(void *wrapper)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * and DDS_Subscriber_delete_datareader so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataReader_impl *cpp_reader = (DDSDataReader_impl *) wrapper;

    holo_base_msg_obstacle_ObstacleVisionDataReader *t_reader = 
    static_cast<holo_base_msg_obstacle_ObstacleVisionDataReader *>(cpp_reader);

    delete t_reader;
}
#endif

/* --------------------------------------------------------------------------
*  Sample Support functions:
* -------------------------------------------------------------------------- */
RTI_BOOL
holo_base_msg_obstacle_ObstacleVisionPlugin_create_sample(struct DDS_TypePlugin *plugin,
void **sample)
{
    UNUSED_ARG(plugin);

    *sample = (void *) holo_base_msg_obstacle_ObstacleVision_create();
    return (*sample != NULL);
}

#ifndef RTI_CERT
RTI_BOOL
holo_base_msg_obstacle_ObstacleVisionPlugin_delete_sample(struct DDS_TypePlugin *plugin, 
void *sample)
{
    UNUSED_ARG(plugin);

    holo_base_msg_obstacle_ObstacleVision_delete((holo_base_msg_obstacle_ObstacleVision *) sample);
    return RTI_TRUE;
}
#endif

RTI_BOOL 
holo_base_msg_obstacle_ObstacleVisionPlugin_copy_sample(struct DDS_TypePlugin *plugin, 
void *dst, 
const void *src)
{
    UNUSED_ARG(plugin);

    return holo_base_msg_obstacle_ObstacleVision_copy(
        (holo_base_msg_obstacle_ObstacleVision*)dst,
        (const holo_base_msg_obstacle_ObstacleVision*)src);
}
/* --------------------------------------------------------------------------
*  Type holo_base_msg_obstacle_ObstacleVision Plugin Instantiation
* -------------------------------------------------------------------------- */

NDDSCDREncapsulation holo_base_msg_obstacle_ObstacleVisionEncapsulationKind[] =
{ 
    {
        DDS_ENCAPSULATION_ID_CDR_LE,
        DDS_ENCAPSULATION_ID_CDR_BE,
        0
    }
};

NDDSCDREncapsulation holo_base_msg_obstacle_ObstacleVisionV2EncapsulationKind[] =
{ 
    {

        DDS_ENCAPSULATION_ID_XCDR2_A_LE,
        DDS_ENCAPSULATION_ID_XCDR2_A_BE,
        0

    }
};

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleVisionTypePlugin_initialize_sample(struct DDS_TypePlugin *plugin, void *buffer)
{
    UNUSED_ARG(plugin);
    return holo_base_msg_obstacle_ObstacleVision_initialize((holo_base_msg_obstacle_ObstacleVision*)buffer);
}

RTI_PRIVATE RTI_UINT32 
holo_base_msg_obstacle_ObstacleVision_get_user_sample_size(
    struct DDS_TypePlugin *tp)
{
    UNUSED_ARG(tp);        
    return sizeof(holo_base_msg_obstacle_ObstacleVision);
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleVision_cdr_initialize(void *init_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)init_config;
    void *sample;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_obstacle_ObstacleVisionPlugin_create_sample(&plugin->_parent,&sample))
    {
        return RTI_FALSE;
    }

    sh->sample = sample;

    return RTI_TRUE;
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleVision_cdr_finalize(void *finalize_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)finalize_config;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_obstacle_ObstacleVisionPlugin_delete_sample(&plugin->_parent,sh->sample))
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

RTI_PRIVATE void 
holo_base_msg_obstacle_ObstacleVisionTypePlugin_return_sample(
    struct DDS_TypePlugin *tp,
    struct DDS_TypePluginSampleHolder *sample)
{
    holo_base_msg_obstacle_ObstacleVision_finalize_optional_members((holo_base_msg_obstacle_ObstacleVision*)sample->sample, RTI_FALSE);
    XCDR_GenericStreamPlugin_return_sample(tp, sample);
}

RTI_PRIVATE struct DDS_TypeMemoryPlugin*
holo_base_msg_obstacle_ObstacleVisionXTypesHeapPlugin_create(struct DDS_TypePlugin *tp,
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
        holo_base_msg_obstacle_ObstacleVision_cdr_initialize,
        holo_base_msg_obstacle_ObstacleVision_cdr_finalize,
        sizeof(holo_base_msg_obstacle_ObstacleVision),
        RTI_FALSE
        );
}

RTI_PRIVATE struct DDS_TypeMemoryI holo_base_msg_obstacle_ObstacleVision_fv_XTypesHeapPluginI =
{
    RTI_MEMORY_MANAGER_HEAP,
    RTI_MEMORY_TYPE_HEAP,
    holo_base_msg_obstacle_ObstacleVisionPlugin_create_sample,
    #ifndef RTI_CERT
    holo_base_msg_obstacle_ObstacleVisionPlugin_delete_sample,
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
    holo_base_msg_obstacle_ObstacleVisionXTypesHeapPlugin_create,
    DDS_XTypesHeapPlugin_delete
};	

RTI_PRIVATE DDS_Boolean 
holo_base_msg_obstacle_ObstacleVision_on_type_registered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    struct RTIXCdrInterpreterProgramsGenProperty programProperty =
    RTIXCdrInterpreterProgramsGenProperty_INITIALIZER;

    programProperty.resolveAlias = RTI_XCDR_TRUE;
    programProperty.inlineStruct = RTI_XCDR_TRUE;
    programProperty.optimizeEnum = RTI_XCDR_TRUE;

    programs = RTIXCdrInterpreterPrograms_new(
        (RTIXCdrTypeCode *)holo_base_msg_obstacle_ObstacleVision_get_typecode(),
        &programProperty,
        RTI_XCDR_PROGRAM_MASK_TYPEPLUGIN
        );

    if (programs == NULL)
    {
        return DDS_BOOLEAN_FALSE;
    }

    DDS_TypeImpl_set_programs(type_impl, programs);
    DDS_TypeImpl_set_typecode(type_impl,  holo_base_msg_obstacle_ObstacleVision_get_typecode());

    return DDS_BOOLEAN_TRUE;
}
RTI_PRIVATE DDS_Boolean 
holo_base_msg_obstacle_ObstacleVision_on_type_unregistered(struct DDS_TypeImpl* type_impl)
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
struct DDS_TypeEncapsulationI holo_base_msg_obstacle_ObstacleVision_fv_XCDRv1PluginI =
{
    DDS_XCDR_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_obstacle_ObstacleVisionEncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,
    holo_base_msg_obstacle_ObstacleVisionTypePlugin_return_sample,
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv1_StreamPlugin_get_serialized_sample_size,
    XCDRv1_StreamPlugin_create,
    XCDRv1_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI holo_base_msg_obstacle_ObstacleVision_fv_XCDRv2PluginI =
{
    DDS_XCDR2_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_obstacle_ObstacleVisionV2EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,

    holo_base_msg_obstacle_ObstacleVisionTypePlugin_return_sample,   
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv2_StreamPlugin_get_serialized_sample_size,
    XCDRv2_StreamPlugin_create,
    XCDRv2_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI *holo_base_msg_obstacle_ObstacleVision_fv_WirePlugins[] =
{
    &holo_base_msg_obstacle_ObstacleVision_fv_XCDRv2PluginI,
    &holo_base_msg_obstacle_ObstacleVision_fv_XCDRv1PluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypeMemoryI *holo_base_msg_obstacle_ObstacleVision_fv_MemoryPlugins[] =
{
    &holo_base_msg_obstacle_ObstacleVision_fv_XTypesHeapPluginI,

    NULL
};

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleVisionTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property);
RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleVisionTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin);

RTI_PRIVATE struct DDS_TypePluginI holo_base_msg_obstacle_ObstacleVision_fv_TypePluginI =
{
    /**************************************************************************
    *                   Type information functions
    **************************************************************************/

    NULL,                       /* DDS_TypeCode_t* */
    NDDS_TYPEPLUGIN_NO_KEY,     /* NDDS_TypePluginKeyKind */

    NDDS_TYPEPLUGIN_EH_LOCATION_PAYLOAD,
    holo_base_msg_obstacle_ObstacleVision_get_user_sample_size,   
    RTI_MEMORY_TYPE_HEAP,
    NULL,
    holo_base_msg_obstacle_ObstacleVisionPlugin_copy_sample,

    holo_base_msg_obstacle_ObstacleVisionTypePlugin_initialize_sample,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    holo_base_msg_obstacle_ObstacleVision_fv_MemoryPlugins,
    holo_base_msg_obstacle_ObstacleVision_fv_WirePlugins,

    /**************************************************************************
    *       Helper APIs to create language binding wrapper Functions
    **************************************************************************/

    holo_base_msg_obstacle_ObstacleVisionPlugin_create_typed_datawriter,
    #ifndef RTI_CERT
    holo_base_msg_obstacle_ObstacleVisionPlugin_delete_typed_datawriter,
    #else
    NULL,
    #endif
    holo_base_msg_obstacle_ObstacleVisionPlugin_create_typed_datareader,
    #ifndef RTI_CERT
    holo_base_msg_obstacle_ObstacleVisionPlugin_delete_typed_datareader,
    #else
    NULL,
    #endif
    holo_base_msg_obstacle_ObstacleVisionTypePlugin_create_plugin,
    holo_base_msg_obstacle_ObstacleVisionTypePlugin_delete_plugin,
    holo_base_msg_obstacle_ObstacleVision_on_type_registered,
    holo_base_msg_obstacle_ObstacleVision_on_type_unregistered,

};

/* --------------------------------------------------------------------------
*  Type holo_base_msg_obstacle_ObstacleVision Plugin Methods
* -------------------------------------------------------------------------- */

struct DDS_TypePluginI*
holo_base_msg_obstacle_ObstacleVisionTypePlugin_get(void) 
{ 
    return &holo_base_msg_obstacle_ObstacleVision_fv_TypePluginI;
} 

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleVisionTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property)
{
    return DDS_TypePluginDefault_create(&holo_base_msg_obstacle_ObstacleVision_fv_TypePluginI,
    participant,dp_qos,
    endpoint_mode,endpoint,qos,
    property);
}

RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleVisionTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin)
{
    return DDS_TypePluginDefault_delete(plugin);
}

struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleVisionWriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_obstacle_ObstacleVision_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_WRITER,
        (DDS_TypePluginEndpoint*)writer,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleVisionReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_obstacle_ObstacleVision_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_READER,
        (DDS_TypePluginEndpoint*)reader,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

const char*
holo_base_msg_obstacle_ObstacleVisionTypePlugin_get_default_type_name(void) 
{ 
    return holo_base_msg_obstacle_ObstacleVisionTYPENAME;
} 

NDDS_TypePluginKeyKind 
holo_base_msg_obstacle_ObstacleVisionI_get_key_kind(void)
{
    return holo_base_msg_obstacle_ObstacleVision_fv_TypePluginI.key_kind;
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
holo_base_msg_obstacle_ObstacleVisionListPlugin_create_typed_datawriter(void *writer)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * so writer is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataWriter *cpp_writer = 
    new holo_base_msg_obstacle_ObstacleVisionListDataWriter((DDS_DataWriter*)writer);

    return cpp_writer;   
}

#ifndef RTI_CERT
void 
holo_base_msg_obstacle_ObstacleVisionListPlugin_delete_typed_datawriter(void *wrapper)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * and DDS_Publisher_delete_datawriter so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataWriter_impl *cpp_writer = (DDSDataWriter_impl *) wrapper;

    holo_base_msg_obstacle_ObstacleVisionListDataWriter *t_writer = 
    static_cast<holo_base_msg_obstacle_ObstacleVisionListDataWriter *>(cpp_writer);

    delete t_writer;
}
#endif

void* 
holo_base_msg_obstacle_ObstacleVisionListPlugin_create_typed_datareader(void *reader)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * so reader is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataReader *cpp_reader = 
    new holo_base_msg_obstacle_ObstacleVisionListDataReader((DDS_DataReader*)reader);

    return cpp_reader;      
}

#ifndef RTI_CERT
void
holo_base_msg_obstacle_ObstacleVisionListPlugin_delete_typed_datareader(void *wrapper)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * and DDS_Subscriber_delete_datareader so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataReader_impl *cpp_reader = (DDSDataReader_impl *) wrapper;

    holo_base_msg_obstacle_ObstacleVisionListDataReader *t_reader = 
    static_cast<holo_base_msg_obstacle_ObstacleVisionListDataReader *>(cpp_reader);

    delete t_reader;
}
#endif

/* --------------------------------------------------------------------------
*  Sample Support functions:
* -------------------------------------------------------------------------- */
RTI_BOOL
holo_base_msg_obstacle_ObstacleVisionListPlugin_create_sample(struct DDS_TypePlugin *plugin,
void **sample)
{
    UNUSED_ARG(plugin);

    *sample = (void *) holo_base_msg_obstacle_ObstacleVisionList_create();
    return (*sample != NULL);
}

#ifndef RTI_CERT
RTI_BOOL
holo_base_msg_obstacle_ObstacleVisionListPlugin_delete_sample(struct DDS_TypePlugin *plugin, 
void *sample)
{
    UNUSED_ARG(plugin);

    holo_base_msg_obstacle_ObstacleVisionList_delete((holo_base_msg_obstacle_ObstacleVisionList *) sample);
    return RTI_TRUE;
}
#endif

RTI_BOOL 
holo_base_msg_obstacle_ObstacleVisionListPlugin_copy_sample(struct DDS_TypePlugin *plugin, 
void *dst, 
const void *src)
{
    UNUSED_ARG(plugin);

    return holo_base_msg_obstacle_ObstacleVisionList_copy(
        (holo_base_msg_obstacle_ObstacleVisionList*)dst,
        (const holo_base_msg_obstacle_ObstacleVisionList*)src);
}
/* --------------------------------------------------------------------------
*  Type holo_base_msg_obstacle_ObstacleVisionList Plugin Instantiation
* -------------------------------------------------------------------------- */

NDDSCDREncapsulation holo_base_msg_obstacle_ObstacleVisionListEncapsulationKind[] =
{ 
    {
        DDS_ENCAPSULATION_ID_CDR_LE,
        DDS_ENCAPSULATION_ID_CDR_BE,
        0
    }
};

NDDSCDREncapsulation holo_base_msg_obstacle_ObstacleVisionListV2EncapsulationKind[] =
{ 
    {

        DDS_ENCAPSULATION_ID_XCDR2_A_LE,
        DDS_ENCAPSULATION_ID_XCDR2_A_BE,
        0

    }
};

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleVisionListTypePlugin_initialize_sample(struct DDS_TypePlugin *plugin, void *buffer)
{
    UNUSED_ARG(plugin);
    return holo_base_msg_obstacle_ObstacleVisionList_initialize((holo_base_msg_obstacle_ObstacleVisionList*)buffer);
}

RTI_PRIVATE RTI_UINT32 
holo_base_msg_obstacle_ObstacleVisionList_get_user_sample_size(
    struct DDS_TypePlugin *tp)
{
    UNUSED_ARG(tp);        
    return sizeof(holo_base_msg_obstacle_ObstacleVisionList);
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleVisionList_cdr_initialize(void *init_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)init_config;
    void *sample;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_obstacle_ObstacleVisionListPlugin_create_sample(&plugin->_parent,&sample))
    {
        return RTI_FALSE;
    }

    sh->sample = sample;

    return RTI_TRUE;
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleVisionList_cdr_finalize(void *finalize_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)finalize_config;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_obstacle_ObstacleVisionListPlugin_delete_sample(&plugin->_parent,sh->sample))
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

RTI_PRIVATE void 
holo_base_msg_obstacle_ObstacleVisionListTypePlugin_return_sample(
    struct DDS_TypePlugin *tp,
    struct DDS_TypePluginSampleHolder *sample)
{
    holo_base_msg_obstacle_ObstacleVisionList_finalize_optional_members((holo_base_msg_obstacle_ObstacleVisionList*)sample->sample, RTI_FALSE);
    XCDR_GenericStreamPlugin_return_sample(tp, sample);
}

RTI_PRIVATE struct DDS_TypeMemoryPlugin*
holo_base_msg_obstacle_ObstacleVisionListXTypesHeapPlugin_create(struct DDS_TypePlugin *tp,
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
        holo_base_msg_obstacle_ObstacleVisionList_cdr_initialize,
        holo_base_msg_obstacle_ObstacleVisionList_cdr_finalize,
        sizeof(holo_base_msg_obstacle_ObstacleVisionList),
        RTI_FALSE
        );
}

RTI_PRIVATE struct DDS_TypeMemoryI holo_base_msg_obstacle_ObstacleVisionList_fv_XTypesHeapPluginI =
{
    RTI_MEMORY_MANAGER_HEAP,
    RTI_MEMORY_TYPE_HEAP,
    holo_base_msg_obstacle_ObstacleVisionListPlugin_create_sample,
    #ifndef RTI_CERT
    holo_base_msg_obstacle_ObstacleVisionListPlugin_delete_sample,
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
    holo_base_msg_obstacle_ObstacleVisionListXTypesHeapPlugin_create,
    DDS_XTypesHeapPlugin_delete
};	

RTI_PRIVATE DDS_Boolean 
holo_base_msg_obstacle_ObstacleVisionList_on_type_registered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    struct RTIXCdrInterpreterProgramsGenProperty programProperty =
    RTIXCdrInterpreterProgramsGenProperty_INITIALIZER;

    programProperty.resolveAlias = RTI_XCDR_TRUE;
    programProperty.inlineStruct = RTI_XCDR_TRUE;
    programProperty.optimizeEnum = RTI_XCDR_TRUE;

    programs = RTIXCdrInterpreterPrograms_new(
        (RTIXCdrTypeCode *)holo_base_msg_obstacle_ObstacleVisionList_get_typecode(),
        &programProperty,
        RTI_XCDR_PROGRAM_MASK_TYPEPLUGIN
        );

    if (programs == NULL)
    {
        return DDS_BOOLEAN_FALSE;
    }

    DDS_TypeImpl_set_programs(type_impl, programs);
    DDS_TypeImpl_set_typecode(type_impl,  holo_base_msg_obstacle_ObstacleVisionList_get_typecode());

    return DDS_BOOLEAN_TRUE;
}
RTI_PRIVATE DDS_Boolean 
holo_base_msg_obstacle_ObstacleVisionList_on_type_unregistered(struct DDS_TypeImpl* type_impl)
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
struct DDS_TypeEncapsulationI holo_base_msg_obstacle_ObstacleVisionList_fv_XCDRv1PluginI =
{
    DDS_XCDR_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_obstacle_ObstacleVisionListEncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,
    holo_base_msg_obstacle_ObstacleVisionListTypePlugin_return_sample,
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv1_StreamPlugin_get_serialized_sample_size,
    XCDRv1_StreamPlugin_create,
    XCDRv1_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI holo_base_msg_obstacle_ObstacleVisionList_fv_XCDRv2PluginI =
{
    DDS_XCDR2_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_obstacle_ObstacleVisionListV2EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,

    holo_base_msg_obstacle_ObstacleVisionListTypePlugin_return_sample,   
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv2_StreamPlugin_get_serialized_sample_size,
    XCDRv2_StreamPlugin_create,
    XCDRv2_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI *holo_base_msg_obstacle_ObstacleVisionList_fv_WirePlugins[] =
{
    &holo_base_msg_obstacle_ObstacleVisionList_fv_XCDRv2PluginI,
    &holo_base_msg_obstacle_ObstacleVisionList_fv_XCDRv1PluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypeMemoryI *holo_base_msg_obstacle_ObstacleVisionList_fv_MemoryPlugins[] =
{
    &holo_base_msg_obstacle_ObstacleVisionList_fv_XTypesHeapPluginI,

    NULL
};

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleVisionListTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property);
RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleVisionListTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin);

RTI_PRIVATE struct DDS_TypePluginI holo_base_msg_obstacle_ObstacleVisionList_fv_TypePluginI =
{
    /**************************************************************************
    *                   Type information functions
    **************************************************************************/

    NULL,                       /* DDS_TypeCode_t* */
    NDDS_TYPEPLUGIN_NO_KEY,     /* NDDS_TypePluginKeyKind */

    NDDS_TYPEPLUGIN_EH_LOCATION_PAYLOAD,
    holo_base_msg_obstacle_ObstacleVisionList_get_user_sample_size,   
    RTI_MEMORY_TYPE_HEAP,
    NULL,
    holo_base_msg_obstacle_ObstacleVisionListPlugin_copy_sample,

    holo_base_msg_obstacle_ObstacleVisionListTypePlugin_initialize_sample,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    holo_base_msg_obstacle_ObstacleVisionList_fv_MemoryPlugins,
    holo_base_msg_obstacle_ObstacleVisionList_fv_WirePlugins,

    /**************************************************************************
    *       Helper APIs to create language binding wrapper Functions
    **************************************************************************/

    holo_base_msg_obstacle_ObstacleVisionListPlugin_create_typed_datawriter,
    #ifndef RTI_CERT
    holo_base_msg_obstacle_ObstacleVisionListPlugin_delete_typed_datawriter,
    #else
    NULL,
    #endif
    holo_base_msg_obstacle_ObstacleVisionListPlugin_create_typed_datareader,
    #ifndef RTI_CERT
    holo_base_msg_obstacle_ObstacleVisionListPlugin_delete_typed_datareader,
    #else
    NULL,
    #endif
    holo_base_msg_obstacle_ObstacleVisionListTypePlugin_create_plugin,
    holo_base_msg_obstacle_ObstacleVisionListTypePlugin_delete_plugin,
    holo_base_msg_obstacle_ObstacleVisionList_on_type_registered,
    holo_base_msg_obstacle_ObstacleVisionList_on_type_unregistered,

};

/* --------------------------------------------------------------------------
*  Type holo_base_msg_obstacle_ObstacleVisionList Plugin Methods
* -------------------------------------------------------------------------- */

struct DDS_TypePluginI*
holo_base_msg_obstacle_ObstacleVisionListTypePlugin_get(void) 
{ 
    return &holo_base_msg_obstacle_ObstacleVisionList_fv_TypePluginI;
} 

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleVisionListTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property)
{
    return DDS_TypePluginDefault_create(&holo_base_msg_obstacle_ObstacleVisionList_fv_TypePluginI,
    participant,dp_qos,
    endpoint_mode,endpoint,qos,
    property);
}

RTI_PRIVATE RTI_BOOL
holo_base_msg_obstacle_ObstacleVisionListTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin)
{
    return DDS_TypePluginDefault_delete(plugin);
}

struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleVisionListWriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_obstacle_ObstacleVisionList_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_WRITER,
        (DDS_TypePluginEndpoint*)writer,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

struct DDS_TypePlugin*
holo_base_msg_obstacle_ObstacleVisionListReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_obstacle_ObstacleVisionList_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_READER,
        (DDS_TypePluginEndpoint*)reader,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

const char*
holo_base_msg_obstacle_ObstacleVisionListTypePlugin_get_default_type_name(void) 
{ 
    return holo_base_msg_obstacle_ObstacleVisionListTYPENAME;
} 

NDDS_TypePluginKeyKind 
holo_base_msg_obstacle_ObstacleVisionListI_get_key_kind(void)
{
    return holo_base_msg_obstacle_ObstacleVisionList_fv_TypePluginI.key_kind;
}

