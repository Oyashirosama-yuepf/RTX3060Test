/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Imu.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "Imu.h"

#ifndef UNUSED_ARG
#define UNUSED_ARG(x) (void)(x)
#endif

#include "dds_c/dds_c_typecode.h"
/*** SOURCE_BEGIN ***/

holo_base_msg_common_ImuStatus *
holo_base_msg_common_ImuStatus_create(void)
{
    holo_base_msg_common_ImuStatus* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_ImuStatus);
    if (sample != NULL) {
        if (!holo_base_msg_common_ImuStatus_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_ImuStatus_delete(holo_base_msg_common_ImuStatus*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_ImuStatus_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_ImuStatus_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_ImuStatus_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_common_ImuStatus_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::common::ImuStatus", /* Name */
            NULL, /* Content type code is assigned later */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for  holo_base_msg_common_ImuStatus */

    if (is_initialized) {
        return &holo_base_msg_common_ImuStatus_g_tc;
    }

    holo_base_msg_common_ImuStatus_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_ImuStatus_g_tc._data._typeCode =  (RTICdrTypeCode *)holo_base_msg_core_uint32_t_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_common_ImuStatus_g_tc._data._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ImuStatus_g_tc._data._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_ImuStatus_g_tc._data._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ImuStatus_g_tc._data._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_ImuStatus_g_tc._data._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ImuStatus_g_tc._data._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_ImuStatus_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_ImuStatus_get_sample_access_info();
    holo_base_msg_common_ImuStatus_g_tc._data._typePlugin =
    holo_base_msg_common_ImuStatus_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_ImuStatus_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_ImuStatus_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_ImuStatus_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_ImuStatus_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_ImuStatus_g_sampleAccessInfo;
    }

    holo_base_msg_common_ImuStatus_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_common_ImuStatus_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_ImuStatus_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_ImuStatus);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_ImuStatus_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_ImuStatus_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_ImuStatus_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_ImuStatus_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_ImuStatus_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_ImuStatus_g_typePlugin = 
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
        holo_base_msg_common_ImuStatus_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_ImuStatus_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_ImuStatus_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_ImuStatus_initialize(
    holo_base_msg_common_ImuStatus* sample) {
    return holo_base_msg_common_ImuStatus_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_ImuStatus_initialize_ex(
    holo_base_msg_common_ImuStatus* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_ImuStatus_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_ImuStatus_initialize_w_params(
    holo_base_msg_common_ImuStatus* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    (*sample) = 0u;

    return RTI_TRUE;
}

RTIBool holo_base_msg_common_ImuStatus_finalize(
    holo_base_msg_common_ImuStatus* sample)
{

    holo_base_msg_common_ImuStatus_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_ImuStatus_finalize_w_return(
    holo_base_msg_common_ImuStatus* sample)
{

    holo_base_msg_common_ImuStatus_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_ImuStatus_finalize_ex(
    holo_base_msg_common_ImuStatus* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_ImuStatus_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_ImuStatus_finalize_w_params(
    holo_base_msg_common_ImuStatus* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_common_ImuStatus_finalize_optional_members(
    holo_base_msg_common_ImuStatus* sample, RTIBool deletePointers)
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

}

RTIBool holo_base_msg_common_ImuStatus_copy(
    holo_base_msg_common_ImuStatus* dst,
    const holo_base_msg_common_ImuStatus* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (dst, src);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_ImuStatus' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ImuStatus
#define TSeq holo_base_msg_common_ImuStatusSeq

#define T_initialize holo_base_msg_common_ImuStatus_initialize

#define T_finalize   holo_base_msg_common_ImuStatus_finalize
#define T_copy       holo_base_msg_common_ImuStatus_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ImuStatus
#define TSeq holo_base_msg_common_ImuStatusSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_Imuf *
holo_base_msg_common_Imuf_create(void)
{
    holo_base_msg_common_Imuf* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_Imuf);
    if (sample != NULL) {
        if (!holo_base_msg_common_Imuf_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_Imuf_delete(holo_base_msg_common_Imuf*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_Imuf_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_Imuf_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_common_ImufTYPENAME = "holo_base_msg::common::Imuf";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_Imuf_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_common_Imuf_g_tc_members[5]=
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
            (char *)"coord",/* Member name */
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
            (char *)"angular_velocity",/* Member name */
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
        }, 
        {
            (char *)"linear_acceleration",/* Member name */
            {
                3,/* Representation ID */
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
            (char *)"status",/* Member name */
            {
                4,/* Representation ID */
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

    static DDS_TypeCode holo_base_msg_common_Imuf_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::common::Imuf", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            5, /* Number of members */
            holo_base_msg_common_Imuf_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_common_Imuf*/

    if (is_initialized) {
        return &holo_base_msg_common_Imuf_g_tc;
    }

    holo_base_msg_common_Imuf_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_Imuf_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_common_Imuf_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Coordinate_get_typecode();
    holo_base_msg_common_Imuf_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Vector3f_get_typecode();
    holo_base_msg_common_Imuf_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Vector3f_get_typecode();
    holo_base_msg_common_Imuf_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_ImuStatus_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_common_Imuf_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Imuf_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_Imuf_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Imuf_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_Imuf_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Imuf_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_Imuf_g_tc_members[4]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Imuf_g_tc_members[4]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_Imuf_g_tc_members[4]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Imuf_g_tc_members[4]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_Imuf_g_tc_members[4]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Imuf_g_tc_members[4]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_Imuf_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_Imuf_get_sample_access_info();
    holo_base_msg_common_Imuf_g_tc._data._typePlugin =
    holo_base_msg_common_Imuf_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_Imuf_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_Imuf_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_common_Imuf *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_Imuf_g_memberAccessInfos[5] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_Imuf_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_Imuf_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_common_Imuf);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_common_Imuf_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stamp - (char *)sample);

    holo_base_msg_common_Imuf_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->coord - (char *)sample);

    holo_base_msg_common_Imuf_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->angular_velocity - (char *)sample);

    holo_base_msg_common_Imuf_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->linear_acceleration - (char *)sample);

    holo_base_msg_common_Imuf_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->status - (char *)sample);

    holo_base_msg_common_Imuf_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_Imuf_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_Imuf);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_Imuf_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_Imuf_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_Imuf_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_Imuf_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_Imuf_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_Imuf_g_typePlugin = 
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
        holo_base_msg_common_Imuf_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_Imuf_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_Imuf_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_Imuf_initialize(
    holo_base_msg_common_Imuf* sample) {
    return holo_base_msg_common_Imuf_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_Imuf_initialize_ex(
    holo_base_msg_common_Imuf* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_Imuf_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_Imuf_initialize_w_params(
    holo_base_msg_common_Imuf* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

    sample->coord = 0u;

    if (!holo_base_msg_numerics_Vector3f_initialize_w_params(&sample->angular_velocity,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_numerics_Vector3f_initialize_w_params(&sample->linear_acceleration,
    allocParams)) {
        return RTI_FALSE;
    }

    sample->status = 0u;

    return RTI_TRUE;
}

RTIBool holo_base_msg_common_Imuf_finalize(
    holo_base_msg_common_Imuf* sample)
{

    holo_base_msg_common_Imuf_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_Imuf_finalize_w_return(
    holo_base_msg_common_Imuf* sample)
{

    holo_base_msg_common_Imuf_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_Imuf_finalize_ex(
    holo_base_msg_common_Imuf* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_Imuf_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_Imuf_finalize_w_params(
    holo_base_msg_common_Imuf* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->stamp,deallocParams);

    holo_base_msg_numerics_Vector3f_finalize_w_params(&sample->angular_velocity,deallocParams);

    holo_base_msg_numerics_Vector3f_finalize_w_params(&sample->linear_acceleration,deallocParams);

}

void holo_base_msg_common_Imuf_finalize_optional_members(
    holo_base_msg_common_Imuf* sample, RTIBool deletePointers)
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
    holo_base_msg_numerics_Vector3f_finalize_optional_members(&sample->angular_velocity, deallocParams->delete_pointers);
    holo_base_msg_numerics_Vector3f_finalize_optional_members(&sample->linear_acceleration, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_common_Imuf_copy(
    holo_base_msg_common_Imuf* dst,
    const holo_base_msg_common_Imuf* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_copy(
        &dst->stamp,(const holo_base_msg_common_Timestamp*)&src->stamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->coord, &src->coord);
    if (!holo_base_msg_numerics_Vector3f_copy(
        &dst->angular_velocity,(const holo_base_msg_numerics_Vector3f*)&src->angular_velocity)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_numerics_Vector3f_copy(
        &dst->linear_acceleration,(const holo_base_msg_numerics_Vector3f*)&src->linear_acceleration)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->status, &src->status);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_Imuf' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Imuf
#define TSeq holo_base_msg_common_ImufSeq

#define T_initialize holo_base_msg_common_Imuf_initialize

#define T_finalize   holo_base_msg_common_Imuf_finalize
#define T_copy       holo_base_msg_common_Imuf_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Imuf
#define TSeq holo_base_msg_common_ImufSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_Imud *
holo_base_msg_common_Imud_create(void)
{
    holo_base_msg_common_Imud* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_Imud);
    if (sample != NULL) {
        if (!holo_base_msg_common_Imud_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_Imud_delete(holo_base_msg_common_Imud*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_Imud_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_Imud_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_common_ImudTYPENAME = "holo_base_msg::common::Imud";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_Imud_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_common_Imud_g_tc_members[5]=
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
            (char *)"coord",/* Member name */
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
            (char *)"angular_velocity",/* Member name */
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
        }, 
        {
            (char *)"linear_acceleration",/* Member name */
            {
                3,/* Representation ID */
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
            (char *)"status",/* Member name */
            {
                4,/* Representation ID */
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

    static DDS_TypeCode holo_base_msg_common_Imud_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::common::Imud", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            5, /* Number of members */
            holo_base_msg_common_Imud_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_common_Imud*/

    if (is_initialized) {
        return &holo_base_msg_common_Imud_g_tc;
    }

    holo_base_msg_common_Imud_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_Imud_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_common_Imud_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Coordinate_get_typecode();
    holo_base_msg_common_Imud_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Vector3d_get_typecode();
    holo_base_msg_common_Imud_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Vector3d_get_typecode();
    holo_base_msg_common_Imud_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_ImuStatus_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_common_Imud_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Imud_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_Imud_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Imud_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_Imud_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Imud_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_Imud_g_tc_members[4]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Imud_g_tc_members[4]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_Imud_g_tc_members[4]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Imud_g_tc_members[4]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_Imud_g_tc_members[4]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Imud_g_tc_members[4]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_Imud_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_Imud_get_sample_access_info();
    holo_base_msg_common_Imud_g_tc._data._typePlugin =
    holo_base_msg_common_Imud_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_Imud_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_Imud_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_common_Imud *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_Imud_g_memberAccessInfos[5] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_Imud_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_Imud_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_common_Imud);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_common_Imud_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stamp - (char *)sample);

    holo_base_msg_common_Imud_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->coord - (char *)sample);

    holo_base_msg_common_Imud_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->angular_velocity - (char *)sample);

    holo_base_msg_common_Imud_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->linear_acceleration - (char *)sample);

    holo_base_msg_common_Imud_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->status - (char *)sample);

    holo_base_msg_common_Imud_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_Imud_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_Imud);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_Imud_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_Imud_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_Imud_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_Imud_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_Imud_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_Imud_g_typePlugin = 
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
        holo_base_msg_common_Imud_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_Imud_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_Imud_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_Imud_initialize(
    holo_base_msg_common_Imud* sample) {
    return holo_base_msg_common_Imud_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_Imud_initialize_ex(
    holo_base_msg_common_Imud* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_Imud_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_Imud_initialize_w_params(
    holo_base_msg_common_Imud* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

    sample->coord = 0u;

    if (!holo_base_msg_numerics_Vector3d_initialize_w_params(&sample->angular_velocity,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_numerics_Vector3d_initialize_w_params(&sample->linear_acceleration,
    allocParams)) {
        return RTI_FALSE;
    }

    sample->status = 0u;

    return RTI_TRUE;
}

RTIBool holo_base_msg_common_Imud_finalize(
    holo_base_msg_common_Imud* sample)
{

    holo_base_msg_common_Imud_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_Imud_finalize_w_return(
    holo_base_msg_common_Imud* sample)
{

    holo_base_msg_common_Imud_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_Imud_finalize_ex(
    holo_base_msg_common_Imud* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_Imud_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_Imud_finalize_w_params(
    holo_base_msg_common_Imud* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->stamp,deallocParams);

    holo_base_msg_numerics_Vector3d_finalize_w_params(&sample->angular_velocity,deallocParams);

    holo_base_msg_numerics_Vector3d_finalize_w_params(&sample->linear_acceleration,deallocParams);

}

void holo_base_msg_common_Imud_finalize_optional_members(
    holo_base_msg_common_Imud* sample, RTIBool deletePointers)
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
    holo_base_msg_numerics_Vector3d_finalize_optional_members(&sample->angular_velocity, deallocParams->delete_pointers);
    holo_base_msg_numerics_Vector3d_finalize_optional_members(&sample->linear_acceleration, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_common_Imud_copy(
    holo_base_msg_common_Imud* dst,
    const holo_base_msg_common_Imud* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_copy(
        &dst->stamp,(const holo_base_msg_common_Timestamp*)&src->stamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->coord, &src->coord);
    if (!holo_base_msg_numerics_Vector3d_copy(
        &dst->angular_velocity,(const holo_base_msg_numerics_Vector3d*)&src->angular_velocity)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_numerics_Vector3d_copy(
        &dst->linear_acceleration,(const holo_base_msg_numerics_Vector3d*)&src->linear_acceleration)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->status, &src->status);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_Imud' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Imud
#define TSeq holo_base_msg_common_ImudSeq

#define T_initialize holo_base_msg_common_Imud_initialize

#define T_finalize   holo_base_msg_common_Imud_finalize
#define T_copy       holo_base_msg_common_Imud_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Imud
#define TSeq holo_base_msg_common_ImudSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_ImuBiasf *
holo_base_msg_common_ImuBiasf_create(void)
{
    holo_base_msg_common_ImuBiasf* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_ImuBiasf);
    if (sample != NULL) {
        if (!holo_base_msg_common_ImuBiasf_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_ImuBiasf_delete(holo_base_msg_common_ImuBiasf*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_ImuBiasf_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_ImuBiasf_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_common_ImuBiasfTYPENAME = "holo_base_msg::common::ImuBiasf";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_ImuBiasf_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_common_ImuBiasf_g_tc_members[6]=
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
            (char *)"coord",/* Member name */
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
            (char *)"angular_velocity_bias",/* Member name */
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
        }, 
        {
            (char *)"linear_acceleration_bias",/* Member name */
            {
                3,/* Representation ID */
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
            (char *)"angular_velocity_bias_cov",/* Member name */
            {
                4,/* Representation ID */
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
            (char *)"linear_acceleration_bias_cov",/* Member name */
            {
                5,/* Representation ID */
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

    static DDS_TypeCode holo_base_msg_common_ImuBiasf_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::common::ImuBiasf", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            6, /* Number of members */
            holo_base_msg_common_ImuBiasf_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_common_ImuBiasf*/

    if (is_initialized) {
        return &holo_base_msg_common_ImuBiasf_g_tc;
    }

    holo_base_msg_common_ImuBiasf_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_ImuBiasf_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_common_ImuBiasf_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Coordinate_get_typecode();
    holo_base_msg_common_ImuBiasf_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Vector3f_get_typecode();
    holo_base_msg_common_ImuBiasf_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Vector3f_get_typecode();
    holo_base_msg_common_ImuBiasf_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Vector3f_get_typecode();
    holo_base_msg_common_ImuBiasf_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Vector3f_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_common_ImuBiasf_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ImuBiasf_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_ImuBiasf_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ImuBiasf_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_ImuBiasf_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ImuBiasf_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_ImuBiasf_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_ImuBiasf_get_sample_access_info();
    holo_base_msg_common_ImuBiasf_g_tc._data._typePlugin =
    holo_base_msg_common_ImuBiasf_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_ImuBiasf_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_ImuBiasf_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_common_ImuBiasf *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_ImuBiasf_g_memberAccessInfos[6] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_ImuBiasf_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_ImuBiasf_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_common_ImuBiasf);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_common_ImuBiasf_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stamp - (char *)sample);

    holo_base_msg_common_ImuBiasf_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->coord - (char *)sample);

    holo_base_msg_common_ImuBiasf_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->angular_velocity_bias - (char *)sample);

    holo_base_msg_common_ImuBiasf_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->linear_acceleration_bias - (char *)sample);

    holo_base_msg_common_ImuBiasf_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->angular_velocity_bias_cov - (char *)sample);

    holo_base_msg_common_ImuBiasf_g_memberAccessInfos[5].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->linear_acceleration_bias_cov - (char *)sample);

    holo_base_msg_common_ImuBiasf_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_ImuBiasf_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_ImuBiasf);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_ImuBiasf_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_ImuBiasf_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_ImuBiasf_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_ImuBiasf_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_ImuBiasf_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_ImuBiasf_g_typePlugin = 
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
        holo_base_msg_common_ImuBiasf_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_ImuBiasf_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_ImuBiasf_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_ImuBiasf_initialize(
    holo_base_msg_common_ImuBiasf* sample) {
    return holo_base_msg_common_ImuBiasf_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_ImuBiasf_initialize_ex(
    holo_base_msg_common_ImuBiasf* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_ImuBiasf_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_ImuBiasf_initialize_w_params(
    holo_base_msg_common_ImuBiasf* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

    sample->coord = 0u;

    if (!holo_base_msg_numerics_Vector3f_initialize_w_params(&sample->angular_velocity_bias,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_numerics_Vector3f_initialize_w_params(&sample->linear_acceleration_bias,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_numerics_Vector3f_initialize_w_params(&sample->angular_velocity_bias_cov,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_numerics_Vector3f_initialize_w_params(&sample->linear_acceleration_bias_cov,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_ImuBiasf_finalize(
    holo_base_msg_common_ImuBiasf* sample)
{

    holo_base_msg_common_ImuBiasf_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_ImuBiasf_finalize_w_return(
    holo_base_msg_common_ImuBiasf* sample)
{

    holo_base_msg_common_ImuBiasf_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_ImuBiasf_finalize_ex(
    holo_base_msg_common_ImuBiasf* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_ImuBiasf_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_ImuBiasf_finalize_w_params(
    holo_base_msg_common_ImuBiasf* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->stamp,deallocParams);

    holo_base_msg_numerics_Vector3f_finalize_w_params(&sample->angular_velocity_bias,deallocParams);

    holo_base_msg_numerics_Vector3f_finalize_w_params(&sample->linear_acceleration_bias,deallocParams);

    holo_base_msg_numerics_Vector3f_finalize_w_params(&sample->angular_velocity_bias_cov,deallocParams);

    holo_base_msg_numerics_Vector3f_finalize_w_params(&sample->linear_acceleration_bias_cov,deallocParams);

}

void holo_base_msg_common_ImuBiasf_finalize_optional_members(
    holo_base_msg_common_ImuBiasf* sample, RTIBool deletePointers)
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
    holo_base_msg_numerics_Vector3f_finalize_optional_members(&sample->angular_velocity_bias, deallocParams->delete_pointers);
    holo_base_msg_numerics_Vector3f_finalize_optional_members(&sample->linear_acceleration_bias, deallocParams->delete_pointers);
    holo_base_msg_numerics_Vector3f_finalize_optional_members(&sample->angular_velocity_bias_cov, deallocParams->delete_pointers);
    holo_base_msg_numerics_Vector3f_finalize_optional_members(&sample->linear_acceleration_bias_cov, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_common_ImuBiasf_copy(
    holo_base_msg_common_ImuBiasf* dst,
    const holo_base_msg_common_ImuBiasf* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_copy(
        &dst->stamp,(const holo_base_msg_common_Timestamp*)&src->stamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->coord, &src->coord);
    if (!holo_base_msg_numerics_Vector3f_copy(
        &dst->angular_velocity_bias,(const holo_base_msg_numerics_Vector3f*)&src->angular_velocity_bias)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_numerics_Vector3f_copy(
        &dst->linear_acceleration_bias,(const holo_base_msg_numerics_Vector3f*)&src->linear_acceleration_bias)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_numerics_Vector3f_copy(
        &dst->angular_velocity_bias_cov,(const holo_base_msg_numerics_Vector3f*)&src->angular_velocity_bias_cov)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_numerics_Vector3f_copy(
        &dst->linear_acceleration_bias_cov,(const holo_base_msg_numerics_Vector3f*)&src->linear_acceleration_bias_cov)) {
        return RTI_FALSE;
    } 

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_ImuBiasf' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ImuBiasf
#define TSeq holo_base_msg_common_ImuBiasfSeq

#define T_initialize holo_base_msg_common_ImuBiasf_initialize

#define T_finalize   holo_base_msg_common_ImuBiasf_finalize
#define T_copy       holo_base_msg_common_ImuBiasf_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ImuBiasf
#define TSeq holo_base_msg_common_ImuBiasfSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_ImuBiasd *
holo_base_msg_common_ImuBiasd_create(void)
{
    holo_base_msg_common_ImuBiasd* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_ImuBiasd);
    if (sample != NULL) {
        if (!holo_base_msg_common_ImuBiasd_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_ImuBiasd_delete(holo_base_msg_common_ImuBiasd*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_ImuBiasd_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_ImuBiasd_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_common_ImuBiasdTYPENAME = "holo_base_msg::common::ImuBiasd";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_ImuBiasd_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_common_ImuBiasd_g_tc_members[6]=
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
            (char *)"coord",/* Member name */
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
            (char *)"angular_velocity_bias",/* Member name */
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
        }, 
        {
            (char *)"linear_acceleration_bias",/* Member name */
            {
                3,/* Representation ID */
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
            (char *)"angular_velocity_bias_cov",/* Member name */
            {
                4,/* Representation ID */
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
            (char *)"linear_acceleration_bias_cov",/* Member name */
            {
                5,/* Representation ID */
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

    static DDS_TypeCode holo_base_msg_common_ImuBiasd_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::common::ImuBiasd", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            6, /* Number of members */
            holo_base_msg_common_ImuBiasd_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_common_ImuBiasd*/

    if (is_initialized) {
        return &holo_base_msg_common_ImuBiasd_g_tc;
    }

    holo_base_msg_common_ImuBiasd_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_ImuBiasd_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_common_ImuBiasd_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Coordinate_get_typecode();
    holo_base_msg_common_ImuBiasd_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Vector3d_get_typecode();
    holo_base_msg_common_ImuBiasd_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Vector3d_get_typecode();
    holo_base_msg_common_ImuBiasd_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Vector3d_get_typecode();
    holo_base_msg_common_ImuBiasd_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Vector3d_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_common_ImuBiasd_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ImuBiasd_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_ImuBiasd_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ImuBiasd_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_ImuBiasd_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ImuBiasd_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_ImuBiasd_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_ImuBiasd_get_sample_access_info();
    holo_base_msg_common_ImuBiasd_g_tc._data._typePlugin =
    holo_base_msg_common_ImuBiasd_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_ImuBiasd_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_ImuBiasd_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_common_ImuBiasd *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_ImuBiasd_g_memberAccessInfos[6] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_ImuBiasd_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_ImuBiasd_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_common_ImuBiasd);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_common_ImuBiasd_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stamp - (char *)sample);

    holo_base_msg_common_ImuBiasd_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->coord - (char *)sample);

    holo_base_msg_common_ImuBiasd_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->angular_velocity_bias - (char *)sample);

    holo_base_msg_common_ImuBiasd_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->linear_acceleration_bias - (char *)sample);

    holo_base_msg_common_ImuBiasd_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->angular_velocity_bias_cov - (char *)sample);

    holo_base_msg_common_ImuBiasd_g_memberAccessInfos[5].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->linear_acceleration_bias_cov - (char *)sample);

    holo_base_msg_common_ImuBiasd_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_ImuBiasd_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_ImuBiasd);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_ImuBiasd_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_ImuBiasd_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_ImuBiasd_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_ImuBiasd_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_ImuBiasd_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_ImuBiasd_g_typePlugin = 
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
        holo_base_msg_common_ImuBiasd_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_ImuBiasd_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_ImuBiasd_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_ImuBiasd_initialize(
    holo_base_msg_common_ImuBiasd* sample) {
    return holo_base_msg_common_ImuBiasd_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_ImuBiasd_initialize_ex(
    holo_base_msg_common_ImuBiasd* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_ImuBiasd_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_ImuBiasd_initialize_w_params(
    holo_base_msg_common_ImuBiasd* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

    sample->coord = 0u;

    if (!holo_base_msg_numerics_Vector3d_initialize_w_params(&sample->angular_velocity_bias,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_numerics_Vector3d_initialize_w_params(&sample->linear_acceleration_bias,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_numerics_Vector3d_initialize_w_params(&sample->angular_velocity_bias_cov,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_numerics_Vector3d_initialize_w_params(&sample->linear_acceleration_bias_cov,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_ImuBiasd_finalize(
    holo_base_msg_common_ImuBiasd* sample)
{

    holo_base_msg_common_ImuBiasd_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_ImuBiasd_finalize_w_return(
    holo_base_msg_common_ImuBiasd* sample)
{

    holo_base_msg_common_ImuBiasd_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_ImuBiasd_finalize_ex(
    holo_base_msg_common_ImuBiasd* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_ImuBiasd_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_ImuBiasd_finalize_w_params(
    holo_base_msg_common_ImuBiasd* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->stamp,deallocParams);

    holo_base_msg_numerics_Vector3d_finalize_w_params(&sample->angular_velocity_bias,deallocParams);

    holo_base_msg_numerics_Vector3d_finalize_w_params(&sample->linear_acceleration_bias,deallocParams);

    holo_base_msg_numerics_Vector3d_finalize_w_params(&sample->angular_velocity_bias_cov,deallocParams);

    holo_base_msg_numerics_Vector3d_finalize_w_params(&sample->linear_acceleration_bias_cov,deallocParams);

}

void holo_base_msg_common_ImuBiasd_finalize_optional_members(
    holo_base_msg_common_ImuBiasd* sample, RTIBool deletePointers)
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
    holo_base_msg_numerics_Vector3d_finalize_optional_members(&sample->angular_velocity_bias, deallocParams->delete_pointers);
    holo_base_msg_numerics_Vector3d_finalize_optional_members(&sample->linear_acceleration_bias, deallocParams->delete_pointers);
    holo_base_msg_numerics_Vector3d_finalize_optional_members(&sample->angular_velocity_bias_cov, deallocParams->delete_pointers);
    holo_base_msg_numerics_Vector3d_finalize_optional_members(&sample->linear_acceleration_bias_cov, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_common_ImuBiasd_copy(
    holo_base_msg_common_ImuBiasd* dst,
    const holo_base_msg_common_ImuBiasd* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_copy(
        &dst->stamp,(const holo_base_msg_common_Timestamp*)&src->stamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->coord, &src->coord);
    if (!holo_base_msg_numerics_Vector3d_copy(
        &dst->angular_velocity_bias,(const holo_base_msg_numerics_Vector3d*)&src->angular_velocity_bias)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_numerics_Vector3d_copy(
        &dst->linear_acceleration_bias,(const holo_base_msg_numerics_Vector3d*)&src->linear_acceleration_bias)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_numerics_Vector3d_copy(
        &dst->angular_velocity_bias_cov,(const holo_base_msg_numerics_Vector3d*)&src->angular_velocity_bias_cov)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_numerics_Vector3d_copy(
        &dst->linear_acceleration_bias_cov,(const holo_base_msg_numerics_Vector3d*)&src->linear_acceleration_bias_cov)) {
        return RTI_FALSE;
    } 

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_ImuBiasd' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ImuBiasd
#define TSeq holo_base_msg_common_ImuBiasdSeq

#define T_initialize holo_base_msg_common_ImuBiasd_initialize

#define T_finalize   holo_base_msg_common_ImuBiasd_finalize
#define T_copy       holo_base_msg_common_ImuBiasd_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ImuBiasd
#define TSeq holo_base_msg_common_ImuBiasdSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

