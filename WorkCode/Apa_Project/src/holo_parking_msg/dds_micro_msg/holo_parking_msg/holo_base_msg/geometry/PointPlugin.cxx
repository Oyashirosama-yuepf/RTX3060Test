/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Point.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "Point.h"
#include "reda/reda_bufferpool.h"
#include "xcdr/xcdr_interpreter.h"
#include "dds_c/dds_c_xcdr_type_plugin.h"
#include "PointPlugin.h"
#include "PointSupport.h"

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
holo_base_msg_geometry_Point3fPlugin_create_typed_datawriter(void *writer)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * so writer is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataWriter *cpp_writer = 
    new holo_base_msg_geometry_Point3fDataWriter((DDS_DataWriter*)writer);

    return cpp_writer;   
}

#ifndef RTI_CERT
void 
holo_base_msg_geometry_Point3fPlugin_delete_typed_datawriter(void *wrapper)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * and DDS_Publisher_delete_datawriter so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataWriter_impl *cpp_writer = (DDSDataWriter_impl *) wrapper;

    holo_base_msg_geometry_Point3fDataWriter *t_writer = 
    static_cast<holo_base_msg_geometry_Point3fDataWriter *>(cpp_writer);

    delete t_writer;
}
#endif

void* 
holo_base_msg_geometry_Point3fPlugin_create_typed_datareader(void *reader)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * so reader is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataReader *cpp_reader = 
    new holo_base_msg_geometry_Point3fDataReader((DDS_DataReader*)reader);

    return cpp_reader;      
}

#ifndef RTI_CERT
void
holo_base_msg_geometry_Point3fPlugin_delete_typed_datareader(void *wrapper)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * and DDS_Subscriber_delete_datareader so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataReader_impl *cpp_reader = (DDSDataReader_impl *) wrapper;

    holo_base_msg_geometry_Point3fDataReader *t_reader = 
    static_cast<holo_base_msg_geometry_Point3fDataReader *>(cpp_reader);

    delete t_reader;
}
#endif

/* --------------------------------------------------------------------------
*  Sample Support functions:
* -------------------------------------------------------------------------- */
RTI_BOOL
holo_base_msg_geometry_Point3fPlugin_create_sample(struct DDS_TypePlugin *plugin,
void **sample)
{
    UNUSED_ARG(plugin);

    *sample = (void *) holo_base_msg_geometry_Point3f_create();
    return (*sample != NULL);
}

#ifndef RTI_CERT
RTI_BOOL
holo_base_msg_geometry_Point3fPlugin_delete_sample(struct DDS_TypePlugin *plugin, 
void *sample)
{
    UNUSED_ARG(plugin);

    holo_base_msg_geometry_Point3f_delete((holo_base_msg_geometry_Point3f *) sample);
    return RTI_TRUE;
}
#endif

RTI_BOOL 
holo_base_msg_geometry_Point3fPlugin_copy_sample(struct DDS_TypePlugin *plugin, 
void *dst, 
const void *src)
{
    UNUSED_ARG(plugin);

    return holo_base_msg_geometry_Point3f_copy(
        (holo_base_msg_geometry_Point3f*)dst,
        (const holo_base_msg_geometry_Point3f*)src);
}
/* --------------------------------------------------------------------------
*  Type holo_base_msg_geometry_Point3f Plugin Instantiation
* -------------------------------------------------------------------------- */

NDDSCDREncapsulation holo_base_msg_geometry_Point3fEncapsulationKind[] =
{ 
    {
        DDS_ENCAPSULATION_ID_CDR_LE,
        DDS_ENCAPSULATION_ID_CDR_BE,
        0
    }
};

NDDSCDREncapsulation holo_base_msg_geometry_Point3fV2EncapsulationKind[] =
{ 
    {

        DDS_ENCAPSULATION_ID_XCDR2_A_LE,
        DDS_ENCAPSULATION_ID_XCDR2_A_BE,
        0

    }
};

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_geometry_Point3fTypePlugin_initialize_sample(struct DDS_TypePlugin *plugin, void *buffer)
{
    UNUSED_ARG(plugin);
    return holo_base_msg_geometry_Point3f_initialize((holo_base_msg_geometry_Point3f*)buffer);
}

RTI_PRIVATE RTI_UINT32 
holo_base_msg_geometry_Point3f_get_user_sample_size(
    struct DDS_TypePlugin *tp)
{
    UNUSED_ARG(tp);        
    return sizeof(holo_base_msg_geometry_Point3f);
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_geometry_Point3f_cdr_initialize(void *init_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)init_config;
    void *sample;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_geometry_Point3fPlugin_create_sample(&plugin->_parent,&sample))
    {
        return RTI_FALSE;
    }

    sh->sample = sample;

    return RTI_TRUE;
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_geometry_Point3f_cdr_finalize(void *finalize_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)finalize_config;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_geometry_Point3fPlugin_delete_sample(&plugin->_parent,sh->sample))
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

RTI_PRIVATE void 
holo_base_msg_geometry_Point3fTypePlugin_return_sample(
    struct DDS_TypePlugin *tp,
    struct DDS_TypePluginSampleHolder *sample)
{
    holo_base_msg_geometry_Point3f_finalize_optional_members((holo_base_msg_geometry_Point3f*)sample->sample, RTI_FALSE);
    XCDR_GenericStreamPlugin_return_sample(tp, sample);
}

RTI_PRIVATE struct DDS_TypeMemoryPlugin*
holo_base_msg_geometry_Point3fXTypesHeapPlugin_create(struct DDS_TypePlugin *tp,
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
        holo_base_msg_geometry_Point3f_cdr_initialize,
        holo_base_msg_geometry_Point3f_cdr_finalize,
        sizeof(holo_base_msg_geometry_Point3f),
        RTI_FALSE
        );
}

RTI_PRIVATE struct DDS_TypeMemoryI holo_base_msg_geometry_Point3f_fv_XTypesHeapPluginI =
{
    RTI_MEMORY_MANAGER_HEAP,
    RTI_MEMORY_TYPE_HEAP,
    holo_base_msg_geometry_Point3fPlugin_create_sample,
    #ifndef RTI_CERT
    holo_base_msg_geometry_Point3fPlugin_delete_sample,
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
    holo_base_msg_geometry_Point3fXTypesHeapPlugin_create,
    DDS_XTypesHeapPlugin_delete
};	

RTI_PRIVATE DDS_Boolean 
holo_base_msg_geometry_Point3f_on_type_registered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    struct RTIXCdrInterpreterProgramsGenProperty programProperty =
    RTIXCdrInterpreterProgramsGenProperty_INITIALIZER;

    programProperty.resolveAlias = RTI_XCDR_TRUE;
    programProperty.inlineStruct = RTI_XCDR_TRUE;
    programProperty.optimizeEnum = RTI_XCDR_TRUE;

    programs = RTIXCdrInterpreterPrograms_new(
        (RTIXCdrTypeCode *)holo_base_msg_geometry_Point3f_get_typecode(),
        &programProperty,
        RTI_XCDR_PROGRAM_MASK_TYPEPLUGIN
        );

    if (programs == NULL)
    {
        return DDS_BOOLEAN_FALSE;
    }

    DDS_TypeImpl_set_programs(type_impl, programs);
    DDS_TypeImpl_set_typecode(type_impl,  holo_base_msg_geometry_Point3f_get_typecode());

    return DDS_BOOLEAN_TRUE;
}
RTI_PRIVATE DDS_Boolean 
holo_base_msg_geometry_Point3f_on_type_unregistered(struct DDS_TypeImpl* type_impl)
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
struct DDS_TypeEncapsulationI holo_base_msg_geometry_Point3f_fv_XCDRv1PluginI =
{
    DDS_XCDR_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_geometry_Point3fEncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,
    holo_base_msg_geometry_Point3fTypePlugin_return_sample,
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv1_StreamPlugin_get_serialized_sample_size,
    XCDRv1_StreamPlugin_create,
    XCDRv1_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI holo_base_msg_geometry_Point3f_fv_XCDRv2PluginI =
{
    DDS_XCDR2_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_geometry_Point3fV2EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,

    holo_base_msg_geometry_Point3fTypePlugin_return_sample,   
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv2_StreamPlugin_get_serialized_sample_size,
    XCDRv2_StreamPlugin_create,
    XCDRv2_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI *holo_base_msg_geometry_Point3f_fv_WirePlugins[] =
{
    &holo_base_msg_geometry_Point3f_fv_XCDRv2PluginI,
    &holo_base_msg_geometry_Point3f_fv_XCDRv1PluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypeMemoryI *holo_base_msg_geometry_Point3f_fv_MemoryPlugins[] =
{
    &holo_base_msg_geometry_Point3f_fv_XTypesHeapPluginI,

    NULL
};

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_geometry_Point3fTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property);
RTI_PRIVATE RTI_BOOL
holo_base_msg_geometry_Point3fTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin);

RTI_PRIVATE struct DDS_TypePluginI holo_base_msg_geometry_Point3f_fv_TypePluginI =
{
    /**************************************************************************
    *                   Type information functions
    **************************************************************************/

    NULL,                       /* DDS_TypeCode_t* */
    NDDS_TYPEPLUGIN_NO_KEY,     /* NDDS_TypePluginKeyKind */

    NDDS_TYPEPLUGIN_EH_LOCATION_PAYLOAD,
    holo_base_msg_geometry_Point3f_get_user_sample_size,   
    RTI_MEMORY_TYPE_HEAP,
    NULL,
    holo_base_msg_geometry_Point3fPlugin_copy_sample,

    holo_base_msg_geometry_Point3fTypePlugin_initialize_sample,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    holo_base_msg_geometry_Point3f_fv_MemoryPlugins,
    holo_base_msg_geometry_Point3f_fv_WirePlugins,

    /**************************************************************************
    *       Helper APIs to create language binding wrapper Functions
    **************************************************************************/

    holo_base_msg_geometry_Point3fPlugin_create_typed_datawriter,
    #ifndef RTI_CERT
    holo_base_msg_geometry_Point3fPlugin_delete_typed_datawriter,
    #else
    NULL,
    #endif
    holo_base_msg_geometry_Point3fPlugin_create_typed_datareader,
    #ifndef RTI_CERT
    holo_base_msg_geometry_Point3fPlugin_delete_typed_datareader,
    #else
    NULL,
    #endif
    holo_base_msg_geometry_Point3fTypePlugin_create_plugin,
    holo_base_msg_geometry_Point3fTypePlugin_delete_plugin,
    holo_base_msg_geometry_Point3f_on_type_registered,
    holo_base_msg_geometry_Point3f_on_type_unregistered,

};

/* --------------------------------------------------------------------------
*  Type holo_base_msg_geometry_Point3f Plugin Methods
* -------------------------------------------------------------------------- */

struct DDS_TypePluginI*
holo_base_msg_geometry_Point3fTypePlugin_get(void) 
{ 
    return &holo_base_msg_geometry_Point3f_fv_TypePluginI;
} 

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_geometry_Point3fTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property)
{
    return DDS_TypePluginDefault_create(&holo_base_msg_geometry_Point3f_fv_TypePluginI,
    participant,dp_qos,
    endpoint_mode,endpoint,qos,
    property);
}

RTI_PRIVATE RTI_BOOL
holo_base_msg_geometry_Point3fTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin)
{
    return DDS_TypePluginDefault_delete(plugin);
}

struct DDS_TypePlugin*
holo_base_msg_geometry_Point3fWriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_geometry_Point3f_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_WRITER,
        (DDS_TypePluginEndpoint*)writer,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

struct DDS_TypePlugin*
holo_base_msg_geometry_Point3fReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_geometry_Point3f_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_READER,
        (DDS_TypePluginEndpoint*)reader,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

const char*
holo_base_msg_geometry_Point3fTypePlugin_get_default_type_name(void) 
{ 
    return holo_base_msg_geometry_Point3fTYPENAME;
} 

NDDS_TypePluginKeyKind 
holo_base_msg_geometry_Point3fI_get_key_kind(void)
{
    return holo_base_msg_geometry_Point3f_fv_TypePluginI.key_kind;
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
holo_base_msg_geometry_Point3dPlugin_create_typed_datawriter(void *writer)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * so writer is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataWriter *cpp_writer = 
    new holo_base_msg_geometry_Point3dDataWriter((DDS_DataWriter*)writer);

    return cpp_writer;   
}

#ifndef RTI_CERT
void 
holo_base_msg_geometry_Point3dPlugin_delete_typed_datawriter(void *wrapper)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * and DDS_Publisher_delete_datawriter so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataWriter_impl *cpp_writer = (DDSDataWriter_impl *) wrapper;

    holo_base_msg_geometry_Point3dDataWriter *t_writer = 
    static_cast<holo_base_msg_geometry_Point3dDataWriter *>(cpp_writer);

    delete t_writer;
}
#endif

void* 
holo_base_msg_geometry_Point3dPlugin_create_typed_datareader(void *reader)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * so reader is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataReader *cpp_reader = 
    new holo_base_msg_geometry_Point3dDataReader((DDS_DataReader*)reader);

    return cpp_reader;      
}

#ifndef RTI_CERT
void
holo_base_msg_geometry_Point3dPlugin_delete_typed_datareader(void *wrapper)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * and DDS_Subscriber_delete_datareader so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataReader_impl *cpp_reader = (DDSDataReader_impl *) wrapper;

    holo_base_msg_geometry_Point3dDataReader *t_reader = 
    static_cast<holo_base_msg_geometry_Point3dDataReader *>(cpp_reader);

    delete t_reader;
}
#endif

/* --------------------------------------------------------------------------
*  Sample Support functions:
* -------------------------------------------------------------------------- */
RTI_BOOL
holo_base_msg_geometry_Point3dPlugin_create_sample(struct DDS_TypePlugin *plugin,
void **sample)
{
    UNUSED_ARG(plugin);

    *sample = (void *) holo_base_msg_geometry_Point3d_create();
    return (*sample != NULL);
}

#ifndef RTI_CERT
RTI_BOOL
holo_base_msg_geometry_Point3dPlugin_delete_sample(struct DDS_TypePlugin *plugin, 
void *sample)
{
    UNUSED_ARG(plugin);

    holo_base_msg_geometry_Point3d_delete((holo_base_msg_geometry_Point3d *) sample);
    return RTI_TRUE;
}
#endif

RTI_BOOL 
holo_base_msg_geometry_Point3dPlugin_copy_sample(struct DDS_TypePlugin *plugin, 
void *dst, 
const void *src)
{
    UNUSED_ARG(plugin);

    return holo_base_msg_geometry_Point3d_copy(
        (holo_base_msg_geometry_Point3d*)dst,
        (const holo_base_msg_geometry_Point3d*)src);
}
/* --------------------------------------------------------------------------
*  Type holo_base_msg_geometry_Point3d Plugin Instantiation
* -------------------------------------------------------------------------- */

NDDSCDREncapsulation holo_base_msg_geometry_Point3dEncapsulationKind[] =
{ 
    {
        DDS_ENCAPSULATION_ID_CDR_LE,
        DDS_ENCAPSULATION_ID_CDR_BE,
        0
    }
};

NDDSCDREncapsulation holo_base_msg_geometry_Point3dV2EncapsulationKind[] =
{ 
    {

        DDS_ENCAPSULATION_ID_XCDR2_A_LE,
        DDS_ENCAPSULATION_ID_XCDR2_A_BE,
        0

    }
};

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_geometry_Point3dTypePlugin_initialize_sample(struct DDS_TypePlugin *plugin, void *buffer)
{
    UNUSED_ARG(plugin);
    return holo_base_msg_geometry_Point3d_initialize((holo_base_msg_geometry_Point3d*)buffer);
}

RTI_PRIVATE RTI_UINT32 
holo_base_msg_geometry_Point3d_get_user_sample_size(
    struct DDS_TypePlugin *tp)
{
    UNUSED_ARG(tp);        
    return sizeof(holo_base_msg_geometry_Point3d);
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_geometry_Point3d_cdr_initialize(void *init_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)init_config;
    void *sample;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_geometry_Point3dPlugin_create_sample(&plugin->_parent,&sample))
    {
        return RTI_FALSE;
    }

    sh->sample = sample;

    return RTI_TRUE;
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_geometry_Point3d_cdr_finalize(void *finalize_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)finalize_config;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_geometry_Point3dPlugin_delete_sample(&plugin->_parent,sh->sample))
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

RTI_PRIVATE void 
holo_base_msg_geometry_Point3dTypePlugin_return_sample(
    struct DDS_TypePlugin *tp,
    struct DDS_TypePluginSampleHolder *sample)
{
    holo_base_msg_geometry_Point3d_finalize_optional_members((holo_base_msg_geometry_Point3d*)sample->sample, RTI_FALSE);
    XCDR_GenericStreamPlugin_return_sample(tp, sample);
}

RTI_PRIVATE struct DDS_TypeMemoryPlugin*
holo_base_msg_geometry_Point3dXTypesHeapPlugin_create(struct DDS_TypePlugin *tp,
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
        holo_base_msg_geometry_Point3d_cdr_initialize,
        holo_base_msg_geometry_Point3d_cdr_finalize,
        sizeof(holo_base_msg_geometry_Point3d),
        RTI_FALSE
        );
}

RTI_PRIVATE struct DDS_TypeMemoryI holo_base_msg_geometry_Point3d_fv_XTypesHeapPluginI =
{
    RTI_MEMORY_MANAGER_HEAP,
    RTI_MEMORY_TYPE_HEAP,
    holo_base_msg_geometry_Point3dPlugin_create_sample,
    #ifndef RTI_CERT
    holo_base_msg_geometry_Point3dPlugin_delete_sample,
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
    holo_base_msg_geometry_Point3dXTypesHeapPlugin_create,
    DDS_XTypesHeapPlugin_delete
};	

RTI_PRIVATE DDS_Boolean 
holo_base_msg_geometry_Point3d_on_type_registered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    struct RTIXCdrInterpreterProgramsGenProperty programProperty =
    RTIXCdrInterpreterProgramsGenProperty_INITIALIZER;

    programProperty.resolveAlias = RTI_XCDR_TRUE;
    programProperty.inlineStruct = RTI_XCDR_TRUE;
    programProperty.optimizeEnum = RTI_XCDR_TRUE;

    programs = RTIXCdrInterpreterPrograms_new(
        (RTIXCdrTypeCode *)holo_base_msg_geometry_Point3d_get_typecode(),
        &programProperty,
        RTI_XCDR_PROGRAM_MASK_TYPEPLUGIN
        );

    if (programs == NULL)
    {
        return DDS_BOOLEAN_FALSE;
    }

    DDS_TypeImpl_set_programs(type_impl, programs);
    DDS_TypeImpl_set_typecode(type_impl,  holo_base_msg_geometry_Point3d_get_typecode());

    return DDS_BOOLEAN_TRUE;
}
RTI_PRIVATE DDS_Boolean 
holo_base_msg_geometry_Point3d_on_type_unregistered(struct DDS_TypeImpl* type_impl)
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
struct DDS_TypeEncapsulationI holo_base_msg_geometry_Point3d_fv_XCDRv1PluginI =
{
    DDS_XCDR_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_geometry_Point3dEncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,
    holo_base_msg_geometry_Point3dTypePlugin_return_sample,
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv1_StreamPlugin_get_serialized_sample_size,
    XCDRv1_StreamPlugin_create,
    XCDRv1_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI holo_base_msg_geometry_Point3d_fv_XCDRv2PluginI =
{
    DDS_XCDR2_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_geometry_Point3dV2EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,

    holo_base_msg_geometry_Point3dTypePlugin_return_sample,   
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv2_StreamPlugin_get_serialized_sample_size,
    XCDRv2_StreamPlugin_create,
    XCDRv2_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI *holo_base_msg_geometry_Point3d_fv_WirePlugins[] =
{
    &holo_base_msg_geometry_Point3d_fv_XCDRv2PluginI,
    &holo_base_msg_geometry_Point3d_fv_XCDRv1PluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypeMemoryI *holo_base_msg_geometry_Point3d_fv_MemoryPlugins[] =
{
    &holo_base_msg_geometry_Point3d_fv_XTypesHeapPluginI,

    NULL
};

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_geometry_Point3dTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property);
RTI_PRIVATE RTI_BOOL
holo_base_msg_geometry_Point3dTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin);

RTI_PRIVATE struct DDS_TypePluginI holo_base_msg_geometry_Point3d_fv_TypePluginI =
{
    /**************************************************************************
    *                   Type information functions
    **************************************************************************/

    NULL,                       /* DDS_TypeCode_t* */
    NDDS_TYPEPLUGIN_NO_KEY,     /* NDDS_TypePluginKeyKind */

    NDDS_TYPEPLUGIN_EH_LOCATION_PAYLOAD,
    holo_base_msg_geometry_Point3d_get_user_sample_size,   
    RTI_MEMORY_TYPE_HEAP,
    NULL,
    holo_base_msg_geometry_Point3dPlugin_copy_sample,

    holo_base_msg_geometry_Point3dTypePlugin_initialize_sample,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    holo_base_msg_geometry_Point3d_fv_MemoryPlugins,
    holo_base_msg_geometry_Point3d_fv_WirePlugins,

    /**************************************************************************
    *       Helper APIs to create language binding wrapper Functions
    **************************************************************************/

    holo_base_msg_geometry_Point3dPlugin_create_typed_datawriter,
    #ifndef RTI_CERT
    holo_base_msg_geometry_Point3dPlugin_delete_typed_datawriter,
    #else
    NULL,
    #endif
    holo_base_msg_geometry_Point3dPlugin_create_typed_datareader,
    #ifndef RTI_CERT
    holo_base_msg_geometry_Point3dPlugin_delete_typed_datareader,
    #else
    NULL,
    #endif
    holo_base_msg_geometry_Point3dTypePlugin_create_plugin,
    holo_base_msg_geometry_Point3dTypePlugin_delete_plugin,
    holo_base_msg_geometry_Point3d_on_type_registered,
    holo_base_msg_geometry_Point3d_on_type_unregistered,

};

/* --------------------------------------------------------------------------
*  Type holo_base_msg_geometry_Point3d Plugin Methods
* -------------------------------------------------------------------------- */

struct DDS_TypePluginI*
holo_base_msg_geometry_Point3dTypePlugin_get(void) 
{ 
    return &holo_base_msg_geometry_Point3d_fv_TypePluginI;
} 

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_geometry_Point3dTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property)
{
    return DDS_TypePluginDefault_create(&holo_base_msg_geometry_Point3d_fv_TypePluginI,
    participant,dp_qos,
    endpoint_mode,endpoint,qos,
    property);
}

RTI_PRIVATE RTI_BOOL
holo_base_msg_geometry_Point3dTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin)
{
    return DDS_TypePluginDefault_delete(plugin);
}

struct DDS_TypePlugin*
holo_base_msg_geometry_Point3dWriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_geometry_Point3d_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_WRITER,
        (DDS_TypePluginEndpoint*)writer,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

struct DDS_TypePlugin*
holo_base_msg_geometry_Point3dReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_geometry_Point3d_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_READER,
        (DDS_TypePluginEndpoint*)reader,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

const char*
holo_base_msg_geometry_Point3dTypePlugin_get_default_type_name(void) 
{ 
    return holo_base_msg_geometry_Point3dTYPENAME;
} 

NDDS_TypePluginKeyKind 
holo_base_msg_geometry_Point3dI_get_key_kind(void)
{
    return holo_base_msg_geometry_Point3d_fv_TypePluginI.key_kind;
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
holo_base_msg_geometry_Point2fPlugin_create_typed_datawriter(void *writer)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * so writer is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataWriter *cpp_writer = 
    new holo_base_msg_geometry_Point2fDataWriter((DDS_DataWriter*)writer);

    return cpp_writer;   
}

#ifndef RTI_CERT
void 
holo_base_msg_geometry_Point2fPlugin_delete_typed_datawriter(void *wrapper)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * and DDS_Publisher_delete_datawriter so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataWriter_impl *cpp_writer = (DDSDataWriter_impl *) wrapper;

    holo_base_msg_geometry_Point2fDataWriter *t_writer = 
    static_cast<holo_base_msg_geometry_Point2fDataWriter *>(cpp_writer);

    delete t_writer;
}
#endif

void* 
holo_base_msg_geometry_Point2fPlugin_create_typed_datareader(void *reader)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * so reader is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataReader *cpp_reader = 
    new holo_base_msg_geometry_Point2fDataReader((DDS_DataReader*)reader);

    return cpp_reader;      
}

#ifndef RTI_CERT
void
holo_base_msg_geometry_Point2fPlugin_delete_typed_datareader(void *wrapper)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * and DDS_Subscriber_delete_datareader so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataReader_impl *cpp_reader = (DDSDataReader_impl *) wrapper;

    holo_base_msg_geometry_Point2fDataReader *t_reader = 
    static_cast<holo_base_msg_geometry_Point2fDataReader *>(cpp_reader);

    delete t_reader;
}
#endif

/* --------------------------------------------------------------------------
*  Sample Support functions:
* -------------------------------------------------------------------------- */
RTI_BOOL
holo_base_msg_geometry_Point2fPlugin_create_sample(struct DDS_TypePlugin *plugin,
void **sample)
{
    UNUSED_ARG(plugin);

    *sample = (void *) holo_base_msg_geometry_Point2f_create();
    return (*sample != NULL);
}

#ifndef RTI_CERT
RTI_BOOL
holo_base_msg_geometry_Point2fPlugin_delete_sample(struct DDS_TypePlugin *plugin, 
void *sample)
{
    UNUSED_ARG(plugin);

    holo_base_msg_geometry_Point2f_delete((holo_base_msg_geometry_Point2f *) sample);
    return RTI_TRUE;
}
#endif

RTI_BOOL 
holo_base_msg_geometry_Point2fPlugin_copy_sample(struct DDS_TypePlugin *plugin, 
void *dst, 
const void *src)
{
    UNUSED_ARG(plugin);

    return holo_base_msg_geometry_Point2f_copy(
        (holo_base_msg_geometry_Point2f*)dst,
        (const holo_base_msg_geometry_Point2f*)src);
}
/* --------------------------------------------------------------------------
*  Type holo_base_msg_geometry_Point2f Plugin Instantiation
* -------------------------------------------------------------------------- */

NDDSCDREncapsulation holo_base_msg_geometry_Point2fEncapsulationKind[] =
{ 
    {
        DDS_ENCAPSULATION_ID_CDR_LE,
        DDS_ENCAPSULATION_ID_CDR_BE,
        0
    }
};

NDDSCDREncapsulation holo_base_msg_geometry_Point2fV2EncapsulationKind[] =
{ 
    {

        DDS_ENCAPSULATION_ID_XCDR2_A_LE,
        DDS_ENCAPSULATION_ID_XCDR2_A_BE,
        0

    }
};

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_geometry_Point2fTypePlugin_initialize_sample(struct DDS_TypePlugin *plugin, void *buffer)
{
    UNUSED_ARG(plugin);
    return holo_base_msg_geometry_Point2f_initialize((holo_base_msg_geometry_Point2f*)buffer);
}

RTI_PRIVATE RTI_UINT32 
holo_base_msg_geometry_Point2f_get_user_sample_size(
    struct DDS_TypePlugin *tp)
{
    UNUSED_ARG(tp);        
    return sizeof(holo_base_msg_geometry_Point2f);
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_geometry_Point2f_cdr_initialize(void *init_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)init_config;
    void *sample;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_geometry_Point2fPlugin_create_sample(&plugin->_parent,&sample))
    {
        return RTI_FALSE;
    }

    sh->sample = sample;

    return RTI_TRUE;
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_geometry_Point2f_cdr_finalize(void *finalize_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)finalize_config;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_geometry_Point2fPlugin_delete_sample(&plugin->_parent,sh->sample))
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

RTI_PRIVATE void 
holo_base_msg_geometry_Point2fTypePlugin_return_sample(
    struct DDS_TypePlugin *tp,
    struct DDS_TypePluginSampleHolder *sample)
{
    holo_base_msg_geometry_Point2f_finalize_optional_members((holo_base_msg_geometry_Point2f*)sample->sample, RTI_FALSE);
    XCDR_GenericStreamPlugin_return_sample(tp, sample);
}

RTI_PRIVATE struct DDS_TypeMemoryPlugin*
holo_base_msg_geometry_Point2fXTypesHeapPlugin_create(struct DDS_TypePlugin *tp,
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
        holo_base_msg_geometry_Point2f_cdr_initialize,
        holo_base_msg_geometry_Point2f_cdr_finalize,
        sizeof(holo_base_msg_geometry_Point2f),
        RTI_FALSE
        );
}

RTI_PRIVATE struct DDS_TypeMemoryI holo_base_msg_geometry_Point2f_fv_XTypesHeapPluginI =
{
    RTI_MEMORY_MANAGER_HEAP,
    RTI_MEMORY_TYPE_HEAP,
    holo_base_msg_geometry_Point2fPlugin_create_sample,
    #ifndef RTI_CERT
    holo_base_msg_geometry_Point2fPlugin_delete_sample,
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
    holo_base_msg_geometry_Point2fXTypesHeapPlugin_create,
    DDS_XTypesHeapPlugin_delete
};	

RTI_PRIVATE DDS_Boolean 
holo_base_msg_geometry_Point2f_on_type_registered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    struct RTIXCdrInterpreterProgramsGenProperty programProperty =
    RTIXCdrInterpreterProgramsGenProperty_INITIALIZER;

    programProperty.resolveAlias = RTI_XCDR_TRUE;
    programProperty.inlineStruct = RTI_XCDR_TRUE;
    programProperty.optimizeEnum = RTI_XCDR_TRUE;

    programs = RTIXCdrInterpreterPrograms_new(
        (RTIXCdrTypeCode *)holo_base_msg_geometry_Point2f_get_typecode(),
        &programProperty,
        RTI_XCDR_PROGRAM_MASK_TYPEPLUGIN
        );

    if (programs == NULL)
    {
        return DDS_BOOLEAN_FALSE;
    }

    DDS_TypeImpl_set_programs(type_impl, programs);
    DDS_TypeImpl_set_typecode(type_impl,  holo_base_msg_geometry_Point2f_get_typecode());

    return DDS_BOOLEAN_TRUE;
}
RTI_PRIVATE DDS_Boolean 
holo_base_msg_geometry_Point2f_on_type_unregistered(struct DDS_TypeImpl* type_impl)
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
struct DDS_TypeEncapsulationI holo_base_msg_geometry_Point2f_fv_XCDRv1PluginI =
{
    DDS_XCDR_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_geometry_Point2fEncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,
    holo_base_msg_geometry_Point2fTypePlugin_return_sample,
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv1_StreamPlugin_get_serialized_sample_size,
    XCDRv1_StreamPlugin_create,
    XCDRv1_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI holo_base_msg_geometry_Point2f_fv_XCDRv2PluginI =
{
    DDS_XCDR2_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_geometry_Point2fV2EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,

    holo_base_msg_geometry_Point2fTypePlugin_return_sample,   
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv2_StreamPlugin_get_serialized_sample_size,
    XCDRv2_StreamPlugin_create,
    XCDRv2_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI *holo_base_msg_geometry_Point2f_fv_WirePlugins[] =
{
    &holo_base_msg_geometry_Point2f_fv_XCDRv2PluginI,
    &holo_base_msg_geometry_Point2f_fv_XCDRv1PluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypeMemoryI *holo_base_msg_geometry_Point2f_fv_MemoryPlugins[] =
{
    &holo_base_msg_geometry_Point2f_fv_XTypesHeapPluginI,

    NULL
};

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_geometry_Point2fTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property);
RTI_PRIVATE RTI_BOOL
holo_base_msg_geometry_Point2fTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin);

RTI_PRIVATE struct DDS_TypePluginI holo_base_msg_geometry_Point2f_fv_TypePluginI =
{
    /**************************************************************************
    *                   Type information functions
    **************************************************************************/

    NULL,                       /* DDS_TypeCode_t* */
    NDDS_TYPEPLUGIN_NO_KEY,     /* NDDS_TypePluginKeyKind */

    NDDS_TYPEPLUGIN_EH_LOCATION_PAYLOAD,
    holo_base_msg_geometry_Point2f_get_user_sample_size,   
    RTI_MEMORY_TYPE_HEAP,
    NULL,
    holo_base_msg_geometry_Point2fPlugin_copy_sample,

    holo_base_msg_geometry_Point2fTypePlugin_initialize_sample,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    holo_base_msg_geometry_Point2f_fv_MemoryPlugins,
    holo_base_msg_geometry_Point2f_fv_WirePlugins,

    /**************************************************************************
    *       Helper APIs to create language binding wrapper Functions
    **************************************************************************/

    holo_base_msg_geometry_Point2fPlugin_create_typed_datawriter,
    #ifndef RTI_CERT
    holo_base_msg_geometry_Point2fPlugin_delete_typed_datawriter,
    #else
    NULL,
    #endif
    holo_base_msg_geometry_Point2fPlugin_create_typed_datareader,
    #ifndef RTI_CERT
    holo_base_msg_geometry_Point2fPlugin_delete_typed_datareader,
    #else
    NULL,
    #endif
    holo_base_msg_geometry_Point2fTypePlugin_create_plugin,
    holo_base_msg_geometry_Point2fTypePlugin_delete_plugin,
    holo_base_msg_geometry_Point2f_on_type_registered,
    holo_base_msg_geometry_Point2f_on_type_unregistered,

};

/* --------------------------------------------------------------------------
*  Type holo_base_msg_geometry_Point2f Plugin Methods
* -------------------------------------------------------------------------- */

struct DDS_TypePluginI*
holo_base_msg_geometry_Point2fTypePlugin_get(void) 
{ 
    return &holo_base_msg_geometry_Point2f_fv_TypePluginI;
} 

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_geometry_Point2fTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property)
{
    return DDS_TypePluginDefault_create(&holo_base_msg_geometry_Point2f_fv_TypePluginI,
    participant,dp_qos,
    endpoint_mode,endpoint,qos,
    property);
}

RTI_PRIVATE RTI_BOOL
holo_base_msg_geometry_Point2fTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin)
{
    return DDS_TypePluginDefault_delete(plugin);
}

struct DDS_TypePlugin*
holo_base_msg_geometry_Point2fWriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_geometry_Point2f_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_WRITER,
        (DDS_TypePluginEndpoint*)writer,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

struct DDS_TypePlugin*
holo_base_msg_geometry_Point2fReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_geometry_Point2f_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_READER,
        (DDS_TypePluginEndpoint*)reader,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

const char*
holo_base_msg_geometry_Point2fTypePlugin_get_default_type_name(void) 
{ 
    return holo_base_msg_geometry_Point2fTYPENAME;
} 

NDDS_TypePluginKeyKind 
holo_base_msg_geometry_Point2fI_get_key_kind(void)
{
    return holo_base_msg_geometry_Point2f_fv_TypePluginI.key_kind;
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
holo_base_msg_geometry_Point2dPlugin_create_typed_datawriter(void *writer)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * so writer is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataWriter *cpp_writer = 
    new holo_base_msg_geometry_Point2dDataWriter((DDS_DataWriter*)writer);

    return cpp_writer;   
}

#ifndef RTI_CERT
void 
holo_base_msg_geometry_Point2dPlugin_delete_typed_datawriter(void *wrapper)
{
    /* This function is only called from DDS_Publisher_create_datawriter
    * and DDS_Publisher_delete_datawriter so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataWriter_impl *cpp_writer = (DDSDataWriter_impl *) wrapper;

    holo_base_msg_geometry_Point2dDataWriter *t_writer = 
    static_cast<holo_base_msg_geometry_Point2dDataWriter *>(cpp_writer);

    delete t_writer;
}
#endif

void* 
holo_base_msg_geometry_Point2dPlugin_create_typed_datareader(void *reader)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * so reader is guaranteed to have a valid (i.e. non-NULL) value 
    */
    DDSDataReader *cpp_reader = 
    new holo_base_msg_geometry_Point2dDataReader((DDS_DataReader*)reader);

    return cpp_reader;      
}

#ifndef RTI_CERT
void
holo_base_msg_geometry_Point2dPlugin_delete_typed_datareader(void *wrapper)
{
    /* This function is only called from DDS_Subscriber_create_datareader
    * and DDS_Subscriber_delete_datareader so wrapper is guaranteed to have
    * a valid (i.e. non-NULL) value 
    */
    DDSDataReader_impl *cpp_reader = (DDSDataReader_impl *) wrapper;

    holo_base_msg_geometry_Point2dDataReader *t_reader = 
    static_cast<holo_base_msg_geometry_Point2dDataReader *>(cpp_reader);

    delete t_reader;
}
#endif

/* --------------------------------------------------------------------------
*  Sample Support functions:
* -------------------------------------------------------------------------- */
RTI_BOOL
holo_base_msg_geometry_Point2dPlugin_create_sample(struct DDS_TypePlugin *plugin,
void **sample)
{
    UNUSED_ARG(plugin);

    *sample = (void *) holo_base_msg_geometry_Point2d_create();
    return (*sample != NULL);
}

#ifndef RTI_CERT
RTI_BOOL
holo_base_msg_geometry_Point2dPlugin_delete_sample(struct DDS_TypePlugin *plugin, 
void *sample)
{
    UNUSED_ARG(plugin);

    holo_base_msg_geometry_Point2d_delete((holo_base_msg_geometry_Point2d *) sample);
    return RTI_TRUE;
}
#endif

RTI_BOOL 
holo_base_msg_geometry_Point2dPlugin_copy_sample(struct DDS_TypePlugin *plugin, 
void *dst, 
const void *src)
{
    UNUSED_ARG(plugin);

    return holo_base_msg_geometry_Point2d_copy(
        (holo_base_msg_geometry_Point2d*)dst,
        (const holo_base_msg_geometry_Point2d*)src);
}
/* --------------------------------------------------------------------------
*  Type holo_base_msg_geometry_Point2d Plugin Instantiation
* -------------------------------------------------------------------------- */

NDDSCDREncapsulation holo_base_msg_geometry_Point2dEncapsulationKind[] =
{ 
    {
        DDS_ENCAPSULATION_ID_CDR_LE,
        DDS_ENCAPSULATION_ID_CDR_BE,
        0
    }
};

NDDSCDREncapsulation holo_base_msg_geometry_Point2dV2EncapsulationKind[] =
{ 
    {

        DDS_ENCAPSULATION_ID_XCDR2_A_LE,
        DDS_ENCAPSULATION_ID_XCDR2_A_BE,
        0

    }
};

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_geometry_Point2dTypePlugin_initialize_sample(struct DDS_TypePlugin *plugin, void *buffer)
{
    UNUSED_ARG(plugin);
    return holo_base_msg_geometry_Point2d_initialize((holo_base_msg_geometry_Point2d*)buffer);
}

RTI_PRIVATE RTI_UINT32 
holo_base_msg_geometry_Point2d_get_user_sample_size(
    struct DDS_TypePlugin *tp)
{
    UNUSED_ARG(tp);        
    return sizeof(holo_base_msg_geometry_Point2d);
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_geometry_Point2d_cdr_initialize(void *init_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)init_config;
    void *sample;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_geometry_Point2dPlugin_create_sample(&plugin->_parent,&sample))
    {
        return RTI_FALSE;
    }

    sh->sample = sample;

    return RTI_TRUE;
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
holo_base_msg_geometry_Point2d_cdr_finalize(void *finalize_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)finalize_config;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!holo_base_msg_geometry_Point2dPlugin_delete_sample(&plugin->_parent,sh->sample))
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

RTI_PRIVATE void 
holo_base_msg_geometry_Point2dTypePlugin_return_sample(
    struct DDS_TypePlugin *tp,
    struct DDS_TypePluginSampleHolder *sample)
{
    holo_base_msg_geometry_Point2d_finalize_optional_members((holo_base_msg_geometry_Point2d*)sample->sample, RTI_FALSE);
    XCDR_GenericStreamPlugin_return_sample(tp, sample);
}

RTI_PRIVATE struct DDS_TypeMemoryPlugin*
holo_base_msg_geometry_Point2dXTypesHeapPlugin_create(struct DDS_TypePlugin *tp,
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
        holo_base_msg_geometry_Point2d_cdr_initialize,
        holo_base_msg_geometry_Point2d_cdr_finalize,
        sizeof(holo_base_msg_geometry_Point2d),
        RTI_FALSE
        );
}

RTI_PRIVATE struct DDS_TypeMemoryI holo_base_msg_geometry_Point2d_fv_XTypesHeapPluginI =
{
    RTI_MEMORY_MANAGER_HEAP,
    RTI_MEMORY_TYPE_HEAP,
    holo_base_msg_geometry_Point2dPlugin_create_sample,
    #ifndef RTI_CERT
    holo_base_msg_geometry_Point2dPlugin_delete_sample,
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
    holo_base_msg_geometry_Point2dXTypesHeapPlugin_create,
    DDS_XTypesHeapPlugin_delete
};	

RTI_PRIVATE DDS_Boolean 
holo_base_msg_geometry_Point2d_on_type_registered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    struct RTIXCdrInterpreterProgramsGenProperty programProperty =
    RTIXCdrInterpreterProgramsGenProperty_INITIALIZER;

    programProperty.resolveAlias = RTI_XCDR_TRUE;
    programProperty.inlineStruct = RTI_XCDR_TRUE;
    programProperty.optimizeEnum = RTI_XCDR_TRUE;

    programs = RTIXCdrInterpreterPrograms_new(
        (RTIXCdrTypeCode *)holo_base_msg_geometry_Point2d_get_typecode(),
        &programProperty,
        RTI_XCDR_PROGRAM_MASK_TYPEPLUGIN
        );

    if (programs == NULL)
    {
        return DDS_BOOLEAN_FALSE;
    }

    DDS_TypeImpl_set_programs(type_impl, programs);
    DDS_TypeImpl_set_typecode(type_impl,  holo_base_msg_geometry_Point2d_get_typecode());

    return DDS_BOOLEAN_TRUE;
}
RTI_PRIVATE DDS_Boolean 
holo_base_msg_geometry_Point2d_on_type_unregistered(struct DDS_TypeImpl* type_impl)
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
struct DDS_TypeEncapsulationI holo_base_msg_geometry_Point2d_fv_XCDRv1PluginI =
{
    DDS_XCDR_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_geometry_Point2dEncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,
    holo_base_msg_geometry_Point2dTypePlugin_return_sample,
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv1_StreamPlugin_get_serialized_sample_size,
    XCDRv1_StreamPlugin_create,
    XCDRv1_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI holo_base_msg_geometry_Point2d_fv_XCDRv2PluginI =
{
    DDS_XCDR2_DATA_REPRESENTATION,
    NULL,
    holo_base_msg_geometry_Point2dV2EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,

    holo_base_msg_geometry_Point2dTypePlugin_return_sample,   
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv2_StreamPlugin_get_serialized_sample_size,
    XCDRv2_StreamPlugin_create,
    XCDRv2_StreamPlugin_delete,
};

RTI_PRIVATE struct DDS_TypeEncapsulationI *holo_base_msg_geometry_Point2d_fv_WirePlugins[] =
{
    &holo_base_msg_geometry_Point2d_fv_XCDRv2PluginI,
    &holo_base_msg_geometry_Point2d_fv_XCDRv1PluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypeMemoryI *holo_base_msg_geometry_Point2d_fv_MemoryPlugins[] =
{
    &holo_base_msg_geometry_Point2d_fv_XTypesHeapPluginI,

    NULL
};

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_geometry_Point2dTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property);
RTI_PRIVATE RTI_BOOL
holo_base_msg_geometry_Point2dTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin);

RTI_PRIVATE struct DDS_TypePluginI holo_base_msg_geometry_Point2d_fv_TypePluginI =
{
    /**************************************************************************
    *                   Type information functions
    **************************************************************************/

    NULL,                       /* DDS_TypeCode_t* */
    NDDS_TYPEPLUGIN_NO_KEY,     /* NDDS_TypePluginKeyKind */

    NDDS_TYPEPLUGIN_EH_LOCATION_PAYLOAD,
    holo_base_msg_geometry_Point2d_get_user_sample_size,   
    RTI_MEMORY_TYPE_HEAP,
    NULL,
    holo_base_msg_geometry_Point2dPlugin_copy_sample,

    holo_base_msg_geometry_Point2dTypePlugin_initialize_sample,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    holo_base_msg_geometry_Point2d_fv_MemoryPlugins,
    holo_base_msg_geometry_Point2d_fv_WirePlugins,

    /**************************************************************************
    *       Helper APIs to create language binding wrapper Functions
    **************************************************************************/

    holo_base_msg_geometry_Point2dPlugin_create_typed_datawriter,
    #ifndef RTI_CERT
    holo_base_msg_geometry_Point2dPlugin_delete_typed_datawriter,
    #else
    NULL,
    #endif
    holo_base_msg_geometry_Point2dPlugin_create_typed_datareader,
    #ifndef RTI_CERT
    holo_base_msg_geometry_Point2dPlugin_delete_typed_datareader,
    #else
    NULL,
    #endif
    holo_base_msg_geometry_Point2dTypePlugin_create_plugin,
    holo_base_msg_geometry_Point2dTypePlugin_delete_plugin,
    holo_base_msg_geometry_Point2d_on_type_registered,
    holo_base_msg_geometry_Point2d_on_type_unregistered,

};

/* --------------------------------------------------------------------------
*  Type holo_base_msg_geometry_Point2d Plugin Methods
* -------------------------------------------------------------------------- */

struct DDS_TypePluginI*
holo_base_msg_geometry_Point2dTypePlugin_get(void) 
{ 
    return &holo_base_msg_geometry_Point2d_fv_TypePluginI;
} 

RTI_PRIVATE struct DDS_TypePlugin*
holo_base_msg_geometry_Point2dTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property)
{
    return DDS_TypePluginDefault_create(&holo_base_msg_geometry_Point2d_fv_TypePluginI,
    participant,dp_qos,
    endpoint_mode,endpoint,qos,
    property);
}

RTI_PRIVATE RTI_BOOL
holo_base_msg_geometry_Point2dTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin)
{
    return DDS_TypePluginDefault_delete(plugin);
}

struct DDS_TypePlugin*
holo_base_msg_geometry_Point2dWriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_geometry_Point2d_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_WRITER,
        (DDS_TypePluginEndpoint*)writer,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

struct DDS_TypePlugin*
holo_base_msg_geometry_Point2dReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &holo_base_msg_geometry_Point2d_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_READER,
        (DDS_TypePluginEndpoint*)reader,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

const char*
holo_base_msg_geometry_Point2dTypePlugin_get_default_type_name(void) 
{ 
    return holo_base_msg_geometry_Point2dTYPENAME;
} 

NDDS_TypePluginKeyKind 
holo_base_msg_geometry_Point2dI_get_key_kind(void)
{
    return holo_base_msg_geometry_Point2d_fv_TypePluginI.key_kind;
}

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */

