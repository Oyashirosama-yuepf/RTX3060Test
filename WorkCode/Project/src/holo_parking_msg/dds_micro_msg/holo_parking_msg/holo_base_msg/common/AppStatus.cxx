/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from AppStatus.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "AppStatus.h"

#ifndef UNUSED_ARG
#define UNUSED_ARG(x) (void)(x)
#endif

#include "dds_c/dds_c_typecode.h"
/*** SOURCE_BEGIN ***/

holo_base_msg_common_AppStatus *
holo_base_msg_common_AppStatus_create(void)
{
    holo_base_msg_common_AppStatus* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_AppStatus);
    if (sample != NULL) {
        if (!holo_base_msg_common_AppStatus_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_AppStatus_delete(holo_base_msg_common_AppStatus*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_AppStatus_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_AppStatus_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_common_AppStatusTYPENAME = "holo_base_msg::common::AppStatus";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_AppStatus_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_common_AppStatus_g_tc_members[3]=
    {

        {
            (char *)"stamp",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"nodeid",/* Member name */
            {
                1,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"status_codes",/* Member name */
            {
                2,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }
    };

    static DDS_TypeCode holo_base_msg_common_AppStatus_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::common::AppStatus", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            3, /* Number of members */
            holo_base_msg_common_AppStatus_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_common_AppStatus*/

    if (is_initialized) {
        return &holo_base_msg_common_AppStatus_g_tc;
    }

    holo_base_msg_common_AppStatus_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_AppStatus_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_common_AppStatus_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint8_t_get_typecode();
    holo_base_msg_common_AppStatus_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_Uint8Sequence_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_common_AppStatus_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_AppStatus_g_tc_members[1]._annotations._defaultValue._u.octet_value = 0;
    holo_base_msg_common_AppStatus_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_AppStatus_g_tc_members[1]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    holo_base_msg_common_AppStatus_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_AppStatus_g_tc_members[1]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    holo_base_msg_common_AppStatus_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_AppStatus_get_sample_access_info();
    holo_base_msg_common_AppStatus_g_tc._data._typePlugin =
    holo_base_msg_common_AppStatus_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_AppStatus_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_AppStatus_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_common_AppStatus *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_AppStatus_g_memberAccessInfos[3] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_AppStatus_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_AppStatus_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_common_AppStatus);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_common_AppStatus_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stamp - (char *)sample);

    holo_base_msg_common_AppStatus_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->nodeid - (char *)sample);

    holo_base_msg_common_AppStatus_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->status_codes - (char *)sample);

    holo_base_msg_common_AppStatus_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_AppStatus_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_AppStatus);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_AppStatus_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_AppStatus_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_AppStatus_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_AppStatus_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_AppStatus_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_AppStatus_g_typePlugin = 
    {
        NULL, /* serialize */
        NULL, /* serialize_key */
        NULL, /* deserialize_sample */
        NULL, /* deserialize_key_sample */
        NULL, /* skip */
        NULL, /* get_serialized_sample_size */
        NULL, /* get_serialized_sample_max_size_ex */
        NULL, /* get_serialized_key_max_size_ex */
        NULL, /* get_serialized_sample_min_size */
        NULL, /* serialized_sample_to_key */
        (RTIXCdrTypePluginInitializeSampleFunction) 
        holo_base_msg_common_AppStatus_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_AppStatus_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_AppStatus_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_AppStatus_initialize(
    holo_base_msg_common_AppStatus* sample) {
    return holo_base_msg_common_AppStatus_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_AppStatus_initialize_ex(
    holo_base_msg_common_AppStatus* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_AppStatus_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_AppStatus_initialize_w_params(
    holo_base_msg_common_AppStatus* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_initialize_w_params(&sample->stamp,
    allocParams)) {
        return RTI_FALSE;
    }

    sample->nodeid = 0;

    if (!holo_base_msg_core_Uint8Sequence_initialize_w_params(&sample->status_codes,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_AppStatus_finalize(
    holo_base_msg_common_AppStatus* sample)
{

    holo_base_msg_common_AppStatus_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_AppStatus_finalize_w_return(
    holo_base_msg_common_AppStatus* sample)
{

    holo_base_msg_common_AppStatus_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_AppStatus_finalize_ex(
    holo_base_msg_common_AppStatus* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_AppStatus_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_AppStatus_finalize_w_params(
    holo_base_msg_common_AppStatus* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->stamp,deallocParams);

    holo_base_msg_core_Uint8Sequence_finalize_w_params(&sample->status_codes,deallocParams);

}

void holo_base_msg_common_AppStatus_finalize_optional_members(
    holo_base_msg_common_AppStatus* sample, RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParamsTmp =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
    struct DDS_TypeDeallocationParams_t * deallocParams =
    &deallocParamsTmp;

    if (sample==NULL) {
        return;
    } 
    if (deallocParams) {} /* To avoid warnings */

    deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
    deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

    holo_base_msg_common_Timestamp_finalize_optional_members(&sample->stamp, deallocParams->delete_pointers);
    holo_base_msg_core_Uint8Sequence_finalize_optional_members(&sample->status_codes, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_common_AppStatus_copy(
    holo_base_msg_common_AppStatus* dst,
    const holo_base_msg_common_AppStatus* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_copy(
        &dst->stamp,(const holo_base_msg_common_Timestamp*)&src->stamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->nodeid, &src->nodeid);
    if (!holo_base_msg_core_Uint8Sequence_copy(
        &dst->status_codes,(const holo_base_msg_core_Uint8Sequence*)&src->status_codes)) {
        return RTI_FALSE;
    } 

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_AppStatus' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_AppStatus
#define TSeq holo_base_msg_common_AppStatusSeq

#define T_initialize holo_base_msg_common_AppStatus_initialize

#define T_finalize   holo_base_msg_common_AppStatus_finalize
#define T_copy       holo_base_msg_common_AppStatus_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_AppStatus
#define TSeq holo_base_msg_common_AppStatusSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

