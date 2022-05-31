/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Odometry.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "Odometry.h"

#ifndef UNUSED_ARG
#define UNUSED_ARG(x) (void)(x)
#endif

#include "dds_c/dds_c_typecode.h"
/*** SOURCE_BEGIN ***/

holo_base_msg_common_OdometrySource *
holo_base_msg_common_OdometrySource_create(void)
{
    holo_base_msg_common_OdometrySource* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_OdometrySource);
    if (sample != NULL) {
        if (!holo_base_msg_common_OdometrySource_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_OdometrySource_delete(holo_base_msg_common_OdometrySource*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_OdometrySource_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_OdometrySource_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_OdometrySource_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_common_OdometrySource_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::common::OdometrySource", /* Name */
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
        }}; /* Type code for  holo_base_msg_common_OdometrySource */

    if (is_initialized) {
        return &holo_base_msg_common_OdometrySource_g_tc;
    }

    holo_base_msg_common_OdometrySource_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_OdometrySource_g_tc._data._typeCode =  (RTICdrTypeCode *)holo_base_msg_core_uint16_t_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_common_OdometrySource_g_tc._data._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
    holo_base_msg_common_OdometrySource_g_tc._data._annotations._defaultValue._u.ushort_value = 0;
    holo_base_msg_common_OdometrySource_g_tc._data._annotations._minValue._d = RTI_XCDR_TK_USHORT;
    holo_base_msg_common_OdometrySource_g_tc._data._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
    holo_base_msg_common_OdometrySource_g_tc._data._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
    holo_base_msg_common_OdometrySource_g_tc._data._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

    holo_base_msg_common_OdometrySource_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_OdometrySource_get_sample_access_info();
    holo_base_msg_common_OdometrySource_g_tc._data._typePlugin =
    holo_base_msg_common_OdometrySource_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_OdometrySource_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_OdometrySource_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_OdometrySource_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_OdometrySource_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_OdometrySource_g_sampleAccessInfo;
    }

    holo_base_msg_common_OdometrySource_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_common_OdometrySource_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_OdometrySource_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_OdometrySource);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_OdometrySource_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_OdometrySource_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_OdometrySource_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_OdometrySource_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_OdometrySource_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_OdometrySource_g_typePlugin = 
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
        holo_base_msg_common_OdometrySource_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_OdometrySource_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_OdometrySource_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_OdometrySource_initialize(
    holo_base_msg_common_OdometrySource* sample) {
    return holo_base_msg_common_OdometrySource_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_OdometrySource_initialize_ex(
    holo_base_msg_common_OdometrySource* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_OdometrySource_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_OdometrySource_initialize_w_params(
    holo_base_msg_common_OdometrySource* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    (*sample) = 0;

    return RTI_TRUE;
}

RTIBool holo_base_msg_common_OdometrySource_finalize(
    holo_base_msg_common_OdometrySource* sample)
{

    holo_base_msg_common_OdometrySource_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_OdometrySource_finalize_w_return(
    holo_base_msg_common_OdometrySource* sample)
{

    holo_base_msg_common_OdometrySource_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_OdometrySource_finalize_ex(
    holo_base_msg_common_OdometrySource* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_OdometrySource_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_OdometrySource_finalize_w_params(
    holo_base_msg_common_OdometrySource* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_common_OdometrySource_finalize_optional_members(
    holo_base_msg_common_OdometrySource* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_common_OdometrySource_copy(
    holo_base_msg_common_OdometrySource* dst,
    const holo_base_msg_common_OdometrySource* src)
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
* Configure and implement 'holo_base_msg_common_OdometrySource' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_OdometrySource
#define TSeq holo_base_msg_common_OdometrySourceSeq

#define T_initialize holo_base_msg_common_OdometrySource_initialize

#define T_finalize   holo_base_msg_common_OdometrySource_finalize
#define T_copy       holo_base_msg_common_OdometrySource_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_OdometrySource
#define TSeq holo_base_msg_common_OdometrySourceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_OdometryStatus *
holo_base_msg_common_OdometryStatus_create(void)
{
    holo_base_msg_common_OdometryStatus* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_OdometryStatus);
    if (sample != NULL) {
        if (!holo_base_msg_common_OdometryStatus_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_OdometryStatus_delete(holo_base_msg_common_OdometryStatus*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_OdometryStatus_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_OdometryStatus_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_OdometryStatus_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_common_OdometryStatus_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::common::OdometryStatus", /* Name */
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
        }}; /* Type code for  holo_base_msg_common_OdometryStatus */

    if (is_initialized) {
        return &holo_base_msg_common_OdometryStatus_g_tc;
    }

    holo_base_msg_common_OdometryStatus_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_OdometryStatus_g_tc._data._typeCode =  (RTICdrTypeCode *)holo_base_msg_core_uint16_t_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_common_OdometryStatus_g_tc._data._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
    holo_base_msg_common_OdometryStatus_g_tc._data._annotations._defaultValue._u.ushort_value = 0;
    holo_base_msg_common_OdometryStatus_g_tc._data._annotations._minValue._d = RTI_XCDR_TK_USHORT;
    holo_base_msg_common_OdometryStatus_g_tc._data._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
    holo_base_msg_common_OdometryStatus_g_tc._data._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
    holo_base_msg_common_OdometryStatus_g_tc._data._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

    holo_base_msg_common_OdometryStatus_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_OdometryStatus_get_sample_access_info();
    holo_base_msg_common_OdometryStatus_g_tc._data._typePlugin =
    holo_base_msg_common_OdometryStatus_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_OdometryStatus_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_OdometryStatus_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_OdometryStatus_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_OdometryStatus_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_OdometryStatus_g_sampleAccessInfo;
    }

    holo_base_msg_common_OdometryStatus_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_common_OdometryStatus_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_OdometryStatus_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_OdometryStatus);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_OdometryStatus_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_OdometryStatus_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_OdometryStatus_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_OdometryStatus_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_OdometryStatus_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_OdometryStatus_g_typePlugin = 
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
        holo_base_msg_common_OdometryStatus_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_OdometryStatus_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_OdometryStatus_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_OdometryStatus_initialize(
    holo_base_msg_common_OdometryStatus* sample) {
    return holo_base_msg_common_OdometryStatus_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_OdometryStatus_initialize_ex(
    holo_base_msg_common_OdometryStatus* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_OdometryStatus_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_OdometryStatus_initialize_w_params(
    holo_base_msg_common_OdometryStatus* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    (*sample) = 0;

    return RTI_TRUE;
}

RTIBool holo_base_msg_common_OdometryStatus_finalize(
    holo_base_msg_common_OdometryStatus* sample)
{

    holo_base_msg_common_OdometryStatus_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_OdometryStatus_finalize_w_return(
    holo_base_msg_common_OdometryStatus* sample)
{

    holo_base_msg_common_OdometryStatus_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_OdometryStatus_finalize_ex(
    holo_base_msg_common_OdometryStatus* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_OdometryStatus_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_OdometryStatus_finalize_w_params(
    holo_base_msg_common_OdometryStatus* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_common_OdometryStatus_finalize_optional_members(
    holo_base_msg_common_OdometryStatus* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_common_OdometryStatus_copy(
    holo_base_msg_common_OdometryStatus* dst,
    const holo_base_msg_common_OdometryStatus* src)
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
* Configure and implement 'holo_base_msg_common_OdometryStatus' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_OdometryStatus
#define TSeq holo_base_msg_common_OdometryStatusSeq

#define T_initialize holo_base_msg_common_OdometryStatus_initialize

#define T_finalize   holo_base_msg_common_OdometryStatus_finalize
#define T_copy       holo_base_msg_common_OdometryStatus_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_OdometryStatus
#define TSeq holo_base_msg_common_OdometryStatusSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_Odometryf *
holo_base_msg_common_Odometryf_create(void)
{
    holo_base_msg_common_Odometryf* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_Odometryf);
    if (sample != NULL) {
        if (!holo_base_msg_common_Odometryf_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_Odometryf_delete(holo_base_msg_common_Odometryf*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_Odometryf_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_Odometryf_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_common_OdometryfTYPENAME = "holo_base_msg::common::Odometryf";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_Odometryf_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_common_Odometryf_g_tc_members[11]=
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
            (char *)"child_coord",/* Member name */
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
            (char *)"status",/* Member name */
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
            (char *)"source",/* Member name */
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
            (char *)"precision",/* Member name */
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
        }, 
        {
            (char *)"pose",/* Member name */
            {
                6,/* Representation ID */
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
            (char *)"velocity",/* Member name */
            {
                7,/* Representation ID */
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
            (char *)"pose_covariance",/* Member name */
            {
                8,/* Representation ID */
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
            (char *)"velocity_covariance",/* Member name */
            {
                9,/* Representation ID */
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
                10,/* Representation ID */
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

    static DDS_TypeCode holo_base_msg_common_Odometryf_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::common::Odometryf", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            11, /* Number of members */
            holo_base_msg_common_Odometryf_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_common_Odometryf*/

    if (is_initialized) {
        return &holo_base_msg_common_Odometryf_g_tc;
    }

    holo_base_msg_common_Odometryf_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_Odometryf_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_common_Odometryf_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Coordinate_get_typecode();
    holo_base_msg_common_Odometryf_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Coordinate_get_typecode();
    holo_base_msg_common_Odometryf_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_OdometryStatus_get_typecode();
    holo_base_msg_common_Odometryf_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_OdometrySource_get_typecode();
    holo_base_msg_common_Odometryf_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint32_t_get_typecode();
    holo_base_msg_common_Odometryf_g_tc_members[6]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Pose3f_get_typecode();
    holo_base_msg_common_Odometryf_g_tc_members[7]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Vector6f_get_typecode();
    holo_base_msg_common_Odometryf_g_tc_members[8]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Matrix66f_get_typecode();
    holo_base_msg_common_Odometryf_g_tc_members[9]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Matrix66f_get_typecode();
    holo_base_msg_common_Odometryf_g_tc_members[10]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Vector3f_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_common_Odometryf_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Odometryf_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_Odometryf_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Odometryf_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_Odometryf_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Odometryf_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_Odometryf_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Odometryf_g_tc_members[2]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_Odometryf_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Odometryf_g_tc_members[2]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_Odometryf_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Odometryf_g_tc_members[2]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_Odometryf_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
    holo_base_msg_common_Odometryf_g_tc_members[3]._annotations._defaultValue._u.ushort_value = 0;
    holo_base_msg_common_Odometryf_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
    holo_base_msg_common_Odometryf_g_tc_members[3]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
    holo_base_msg_common_Odometryf_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
    holo_base_msg_common_Odometryf_g_tc_members[3]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

    holo_base_msg_common_Odometryf_g_tc_members[4]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
    holo_base_msg_common_Odometryf_g_tc_members[4]._annotations._defaultValue._u.ushort_value = 0;
    holo_base_msg_common_Odometryf_g_tc_members[4]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
    holo_base_msg_common_Odometryf_g_tc_members[4]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
    holo_base_msg_common_Odometryf_g_tc_members[4]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
    holo_base_msg_common_Odometryf_g_tc_members[4]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

    holo_base_msg_common_Odometryf_g_tc_members[5]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Odometryf_g_tc_members[5]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_Odometryf_g_tc_members[5]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Odometryf_g_tc_members[5]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_Odometryf_g_tc_members[5]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Odometryf_g_tc_members[5]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_Odometryf_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_Odometryf_get_sample_access_info();
    holo_base_msg_common_Odometryf_g_tc._data._typePlugin =
    holo_base_msg_common_Odometryf_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_Odometryf_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_Odometryf_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_common_Odometryf *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_Odometryf_g_memberAccessInfos[11] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_Odometryf_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_Odometryf_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_common_Odometryf);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_common_Odometryf_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stamp - (char *)sample);

    holo_base_msg_common_Odometryf_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->coord - (char *)sample);

    holo_base_msg_common_Odometryf_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->child_coord - (char *)sample);

    holo_base_msg_common_Odometryf_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->status - (char *)sample);

    holo_base_msg_common_Odometryf_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->source - (char *)sample);

    holo_base_msg_common_Odometryf_g_memberAccessInfos[5].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->precision - (char *)sample);

    holo_base_msg_common_Odometryf_g_memberAccessInfos[6].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->pose - (char *)sample);

    holo_base_msg_common_Odometryf_g_memberAccessInfos[7].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->velocity - (char *)sample);

    holo_base_msg_common_Odometryf_g_memberAccessInfos[8].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->pose_covariance - (char *)sample);

    holo_base_msg_common_Odometryf_g_memberAccessInfos[9].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->velocity_covariance - (char *)sample);

    holo_base_msg_common_Odometryf_g_memberAccessInfos[10].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->linear_acceleration - (char *)sample);

    holo_base_msg_common_Odometryf_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_Odometryf_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_Odometryf);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_Odometryf_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_Odometryf_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_Odometryf_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_Odometryf_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_Odometryf_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_Odometryf_g_typePlugin = 
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
        holo_base_msg_common_Odometryf_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_Odometryf_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_Odometryf_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_Odometryf_initialize(
    holo_base_msg_common_Odometryf* sample) {
    return holo_base_msg_common_Odometryf_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_Odometryf_initialize_ex(
    holo_base_msg_common_Odometryf* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_Odometryf_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_Odometryf_initialize_w_params(
    holo_base_msg_common_Odometryf* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

    sample->child_coord = 0u;

    sample->status = 0;

    sample->source = 0;

    sample->precision = 0u;

    if (!holo_base_msg_geometry_Pose3f_initialize_w_params(&sample->pose,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_numerics_Vector6f_initialize_w_params(&sample->velocity,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_numerics_Matrix66f_initialize_w_params(&sample->pose_covariance,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_numerics_Matrix66f_initialize_w_params(&sample->velocity_covariance,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_numerics_Vector3f_initialize_w_params(&sample->linear_acceleration,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_Odometryf_finalize(
    holo_base_msg_common_Odometryf* sample)
{

    holo_base_msg_common_Odometryf_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_Odometryf_finalize_w_return(
    holo_base_msg_common_Odometryf* sample)
{

    holo_base_msg_common_Odometryf_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_Odometryf_finalize_ex(
    holo_base_msg_common_Odometryf* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_Odometryf_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_Odometryf_finalize_w_params(
    holo_base_msg_common_Odometryf* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->stamp,deallocParams);

    holo_base_msg_geometry_Pose3f_finalize_w_params(&sample->pose,deallocParams);

    holo_base_msg_numerics_Vector6f_finalize_w_params(&sample->velocity,deallocParams);

    holo_base_msg_numerics_Matrix66f_finalize_w_params(&sample->pose_covariance,deallocParams);

    holo_base_msg_numerics_Matrix66f_finalize_w_params(&sample->velocity_covariance,deallocParams);

    holo_base_msg_numerics_Vector3f_finalize_w_params(&sample->linear_acceleration,deallocParams);

}

void holo_base_msg_common_Odometryf_finalize_optional_members(
    holo_base_msg_common_Odometryf* sample, RTIBool deletePointers)
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
    holo_base_msg_geometry_Pose3f_finalize_optional_members(&sample->pose, deallocParams->delete_pointers);
    holo_base_msg_numerics_Vector6f_finalize_optional_members(&sample->velocity, deallocParams->delete_pointers);
    holo_base_msg_numerics_Matrix66f_finalize_optional_members(&sample->pose_covariance, deallocParams->delete_pointers);
    holo_base_msg_numerics_Matrix66f_finalize_optional_members(&sample->velocity_covariance, deallocParams->delete_pointers);
    holo_base_msg_numerics_Vector3f_finalize_optional_members(&sample->linear_acceleration, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_common_Odometryf_copy(
    holo_base_msg_common_Odometryf* dst,
    const holo_base_msg_common_Odometryf* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_copy(
        &dst->stamp,(const holo_base_msg_common_Timestamp*)&src->stamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->coord, &src->coord);
    DDS_Primitive_copy (&dst->child_coord, &src->child_coord);
    DDS_Primitive_copy (&dst->status, &src->status);
    DDS_Primitive_copy (&dst->source, &src->source);
    DDS_Primitive_copy (&dst->precision, &src->precision);
    if (!holo_base_msg_geometry_Pose3f_copy(
        &dst->pose,(const holo_base_msg_geometry_Pose3f*)&src->pose)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_numerics_Vector6f_copy(
        &dst->velocity,(const holo_base_msg_numerics_Vector6f*)&src->velocity)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_numerics_Matrix66f_copy(
        &dst->pose_covariance,(const holo_base_msg_numerics_Matrix66f*)&src->pose_covariance)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_numerics_Matrix66f_copy(
        &dst->velocity_covariance,(const holo_base_msg_numerics_Matrix66f*)&src->velocity_covariance)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_numerics_Vector3f_copy(
        &dst->linear_acceleration,(const holo_base_msg_numerics_Vector3f*)&src->linear_acceleration)) {
        return RTI_FALSE;
    } 

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_Odometryf' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Odometryf
#define TSeq holo_base_msg_common_OdometryfSeq

#define T_initialize holo_base_msg_common_Odometryf_initialize

#define T_finalize   holo_base_msg_common_Odometryf_finalize
#define T_copy       holo_base_msg_common_Odometryf_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Odometryf
#define TSeq holo_base_msg_common_OdometryfSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_Odometryd *
holo_base_msg_common_Odometryd_create(void)
{
    holo_base_msg_common_Odometryd* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_Odometryd);
    if (sample != NULL) {
        if (!holo_base_msg_common_Odometryd_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_Odometryd_delete(holo_base_msg_common_Odometryd*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_Odometryd_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_Odometryd_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_common_OdometrydTYPENAME = "holo_base_msg::common::Odometryd";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_Odometryd_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_common_Odometryd_g_tc_members[11]=
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
            (char *)"child_coord",/* Member name */
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
            (char *)"status",/* Member name */
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
            (char *)"source",/* Member name */
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
            (char *)"precision",/* Member name */
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
        }, 
        {
            (char *)"pose",/* Member name */
            {
                6,/* Representation ID */
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
            (char *)"velocity",/* Member name */
            {
                7,/* Representation ID */
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
            (char *)"pose_covariance",/* Member name */
            {
                8,/* Representation ID */
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
            (char *)"velocity_covariance",/* Member name */
            {
                9,/* Representation ID */
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
                10,/* Representation ID */
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

    static DDS_TypeCode holo_base_msg_common_Odometryd_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::common::Odometryd", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            11, /* Number of members */
            holo_base_msg_common_Odometryd_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_common_Odometryd*/

    if (is_initialized) {
        return &holo_base_msg_common_Odometryd_g_tc;
    }

    holo_base_msg_common_Odometryd_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_Odometryd_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_common_Odometryd_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Coordinate_get_typecode();
    holo_base_msg_common_Odometryd_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Coordinate_get_typecode();
    holo_base_msg_common_Odometryd_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_OdometryStatus_get_typecode();
    holo_base_msg_common_Odometryd_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_OdometrySource_get_typecode();
    holo_base_msg_common_Odometryd_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint32_t_get_typecode();
    holo_base_msg_common_Odometryd_g_tc_members[6]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Pose3d_get_typecode();
    holo_base_msg_common_Odometryd_g_tc_members[7]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Vector6d_get_typecode();
    holo_base_msg_common_Odometryd_g_tc_members[8]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Matrix66d_get_typecode();
    holo_base_msg_common_Odometryd_g_tc_members[9]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Matrix66d_get_typecode();
    holo_base_msg_common_Odometryd_g_tc_members[10]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Vector3d_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_common_Odometryd_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Odometryd_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_Odometryd_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Odometryd_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_Odometryd_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Odometryd_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_Odometryd_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Odometryd_g_tc_members[2]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_Odometryd_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Odometryd_g_tc_members[2]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_Odometryd_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Odometryd_g_tc_members[2]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_Odometryd_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
    holo_base_msg_common_Odometryd_g_tc_members[3]._annotations._defaultValue._u.ushort_value = 0;
    holo_base_msg_common_Odometryd_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
    holo_base_msg_common_Odometryd_g_tc_members[3]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
    holo_base_msg_common_Odometryd_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
    holo_base_msg_common_Odometryd_g_tc_members[3]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

    holo_base_msg_common_Odometryd_g_tc_members[4]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
    holo_base_msg_common_Odometryd_g_tc_members[4]._annotations._defaultValue._u.ushort_value = 0;
    holo_base_msg_common_Odometryd_g_tc_members[4]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
    holo_base_msg_common_Odometryd_g_tc_members[4]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
    holo_base_msg_common_Odometryd_g_tc_members[4]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
    holo_base_msg_common_Odometryd_g_tc_members[4]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

    holo_base_msg_common_Odometryd_g_tc_members[5]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Odometryd_g_tc_members[5]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_Odometryd_g_tc_members[5]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Odometryd_g_tc_members[5]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_Odometryd_g_tc_members[5]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Odometryd_g_tc_members[5]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_Odometryd_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_Odometryd_get_sample_access_info();
    holo_base_msg_common_Odometryd_g_tc._data._typePlugin =
    holo_base_msg_common_Odometryd_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_Odometryd_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_Odometryd_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_common_Odometryd *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_Odometryd_g_memberAccessInfos[11] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_Odometryd_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_Odometryd_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_common_Odometryd);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_common_Odometryd_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stamp - (char *)sample);

    holo_base_msg_common_Odometryd_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->coord - (char *)sample);

    holo_base_msg_common_Odometryd_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->child_coord - (char *)sample);

    holo_base_msg_common_Odometryd_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->status - (char *)sample);

    holo_base_msg_common_Odometryd_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->source - (char *)sample);

    holo_base_msg_common_Odometryd_g_memberAccessInfos[5].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->precision - (char *)sample);

    holo_base_msg_common_Odometryd_g_memberAccessInfos[6].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->pose - (char *)sample);

    holo_base_msg_common_Odometryd_g_memberAccessInfos[7].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->velocity - (char *)sample);

    holo_base_msg_common_Odometryd_g_memberAccessInfos[8].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->pose_covariance - (char *)sample);

    holo_base_msg_common_Odometryd_g_memberAccessInfos[9].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->velocity_covariance - (char *)sample);

    holo_base_msg_common_Odometryd_g_memberAccessInfos[10].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->linear_acceleration - (char *)sample);

    holo_base_msg_common_Odometryd_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_Odometryd_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_Odometryd);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_Odometryd_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_Odometryd_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_Odometryd_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_Odometryd_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_Odometryd_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_Odometryd_g_typePlugin = 
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
        holo_base_msg_common_Odometryd_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_Odometryd_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_Odometryd_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_Odometryd_initialize(
    holo_base_msg_common_Odometryd* sample) {
    return holo_base_msg_common_Odometryd_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_Odometryd_initialize_ex(
    holo_base_msg_common_Odometryd* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_Odometryd_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_Odometryd_initialize_w_params(
    holo_base_msg_common_Odometryd* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

    sample->child_coord = 0u;

    sample->status = 0;

    sample->source = 0;

    sample->precision = 0u;

    if (!holo_base_msg_geometry_Pose3d_initialize_w_params(&sample->pose,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_numerics_Vector6d_initialize_w_params(&sample->velocity,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_numerics_Matrix66d_initialize_w_params(&sample->pose_covariance,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_numerics_Matrix66d_initialize_w_params(&sample->velocity_covariance,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_numerics_Vector3d_initialize_w_params(&sample->linear_acceleration,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_Odometryd_finalize(
    holo_base_msg_common_Odometryd* sample)
{

    holo_base_msg_common_Odometryd_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_Odometryd_finalize_w_return(
    holo_base_msg_common_Odometryd* sample)
{

    holo_base_msg_common_Odometryd_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_Odometryd_finalize_ex(
    holo_base_msg_common_Odometryd* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_Odometryd_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_Odometryd_finalize_w_params(
    holo_base_msg_common_Odometryd* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->stamp,deallocParams);

    holo_base_msg_geometry_Pose3d_finalize_w_params(&sample->pose,deallocParams);

    holo_base_msg_numerics_Vector6d_finalize_w_params(&sample->velocity,deallocParams);

    holo_base_msg_numerics_Matrix66d_finalize_w_params(&sample->pose_covariance,deallocParams);

    holo_base_msg_numerics_Matrix66d_finalize_w_params(&sample->velocity_covariance,deallocParams);

    holo_base_msg_numerics_Vector3d_finalize_w_params(&sample->linear_acceleration,deallocParams);

}

void holo_base_msg_common_Odometryd_finalize_optional_members(
    holo_base_msg_common_Odometryd* sample, RTIBool deletePointers)
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
    holo_base_msg_geometry_Pose3d_finalize_optional_members(&sample->pose, deallocParams->delete_pointers);
    holo_base_msg_numerics_Vector6d_finalize_optional_members(&sample->velocity, deallocParams->delete_pointers);
    holo_base_msg_numerics_Matrix66d_finalize_optional_members(&sample->pose_covariance, deallocParams->delete_pointers);
    holo_base_msg_numerics_Matrix66d_finalize_optional_members(&sample->velocity_covariance, deallocParams->delete_pointers);
    holo_base_msg_numerics_Vector3d_finalize_optional_members(&sample->linear_acceleration, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_common_Odometryd_copy(
    holo_base_msg_common_Odometryd* dst,
    const holo_base_msg_common_Odometryd* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_copy(
        &dst->stamp,(const holo_base_msg_common_Timestamp*)&src->stamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->coord, &src->coord);
    DDS_Primitive_copy (&dst->child_coord, &src->child_coord);
    DDS_Primitive_copy (&dst->status, &src->status);
    DDS_Primitive_copy (&dst->source, &src->source);
    DDS_Primitive_copy (&dst->precision, &src->precision);
    if (!holo_base_msg_geometry_Pose3d_copy(
        &dst->pose,(const holo_base_msg_geometry_Pose3d*)&src->pose)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_numerics_Vector6d_copy(
        &dst->velocity,(const holo_base_msg_numerics_Vector6d*)&src->velocity)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_numerics_Matrix66d_copy(
        &dst->pose_covariance,(const holo_base_msg_numerics_Matrix66d*)&src->pose_covariance)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_numerics_Matrix66d_copy(
        &dst->velocity_covariance,(const holo_base_msg_numerics_Matrix66d*)&src->velocity_covariance)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_numerics_Vector3d_copy(
        &dst->linear_acceleration,(const holo_base_msg_numerics_Vector3d*)&src->linear_acceleration)) {
        return RTI_FALSE;
    } 

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_Odometryd' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Odometryd
#define TSeq holo_base_msg_common_OdometrydSeq

#define T_initialize holo_base_msg_common_Odometryd_initialize

#define T_finalize   holo_base_msg_common_Odometryd_finalize
#define T_copy       holo_base_msg_common_Odometryd_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Odometryd
#define TSeq holo_base_msg_common_OdometrydSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

