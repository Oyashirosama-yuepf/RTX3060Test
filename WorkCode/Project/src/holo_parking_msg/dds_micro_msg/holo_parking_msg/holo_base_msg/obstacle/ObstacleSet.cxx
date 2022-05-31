/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ObstacleSet.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "ObstacleSet.h"

#ifndef UNUSED_ARG
#define UNUSED_ARG(x) (void)(x)
#endif

#include "dds_c/dds_c_typecode.h"
/*** SOURCE_BEGIN ***/

holo_base_msg_obstacle_CutInCutOut *
holo_base_msg_obstacle_CutInCutOut_create(void)
{
    holo_base_msg_obstacle_CutInCutOut* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_obstacle_CutInCutOut);
    if (sample != NULL) {
        if (!holo_base_msg_obstacle_CutInCutOut_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_obstacle_CutInCutOut_delete(holo_base_msg_obstacle_CutInCutOut*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_obstacle_CutInCutOut_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_obstacle_CutInCutOut_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_obstacle_CutInCutOut_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_obstacle_CutInCutOut_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::obstacle::CutInCutOut", /* Name */
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
        }}; /* Type code for  holo_base_msg_obstacle_CutInCutOut */

    if (is_initialized) {
        return &holo_base_msg_obstacle_CutInCutOut_g_tc;
    }

    holo_base_msg_obstacle_CutInCutOut_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_obstacle_CutInCutOut_g_tc._data._typeCode =  (RTICdrTypeCode *)holo_base_msg_core_uint8_t_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_obstacle_CutInCutOut_g_tc._data._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_obstacle_CutInCutOut_g_tc._data._annotations._defaultValue._u.octet_value = 0;
    holo_base_msg_obstacle_CutInCutOut_g_tc._data._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_obstacle_CutInCutOut_g_tc._data._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    holo_base_msg_obstacle_CutInCutOut_g_tc._data._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_obstacle_CutInCutOut_g_tc._data._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    holo_base_msg_obstacle_CutInCutOut_g_tc._data._sampleAccessInfo =
    holo_base_msg_obstacle_CutInCutOut_get_sample_access_info();
    holo_base_msg_obstacle_CutInCutOut_g_tc._data._typePlugin =
    holo_base_msg_obstacle_CutInCutOut_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_obstacle_CutInCutOut_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_obstacle_CutInCutOut_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_obstacle_CutInCutOut_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_obstacle_CutInCutOut_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_obstacle_CutInCutOut_g_sampleAccessInfo;
    }

    holo_base_msg_obstacle_CutInCutOut_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_obstacle_CutInCutOut_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_obstacle_CutInCutOut_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_obstacle_CutInCutOut);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_obstacle_CutInCutOut_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_obstacle_CutInCutOut_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_obstacle_CutInCutOut_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_obstacle_CutInCutOut_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_obstacle_CutInCutOut_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_obstacle_CutInCutOut_g_typePlugin = 
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
        holo_base_msg_obstacle_CutInCutOut_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_obstacle_CutInCutOut_finalize_w_return,
        NULL
    };

    return &holo_base_msg_obstacle_CutInCutOut_g_typePlugin;
}
#endif

RTIBool holo_base_msg_obstacle_CutInCutOut_initialize(
    holo_base_msg_obstacle_CutInCutOut* sample) {
    return holo_base_msg_obstacle_CutInCutOut_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_obstacle_CutInCutOut_initialize_ex(
    holo_base_msg_obstacle_CutInCutOut* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_obstacle_CutInCutOut_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_obstacle_CutInCutOut_initialize_w_params(
    holo_base_msg_obstacle_CutInCutOut* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

RTIBool holo_base_msg_obstacle_CutInCutOut_finalize(
    holo_base_msg_obstacle_CutInCutOut* sample)
{

    holo_base_msg_obstacle_CutInCutOut_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_obstacle_CutInCutOut_finalize_w_return(
    holo_base_msg_obstacle_CutInCutOut* sample)
{

    holo_base_msg_obstacle_CutInCutOut_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_obstacle_CutInCutOut_finalize_ex(
    holo_base_msg_obstacle_CutInCutOut* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_obstacle_CutInCutOut_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_obstacle_CutInCutOut_finalize_w_params(
    holo_base_msg_obstacle_CutInCutOut* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_obstacle_CutInCutOut_finalize_optional_members(
    holo_base_msg_obstacle_CutInCutOut* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_obstacle_CutInCutOut_copy(
    holo_base_msg_obstacle_CutInCutOut* dst,
    const holo_base_msg_obstacle_CutInCutOut* src)
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
* Configure and implement 'holo_base_msg_obstacle_CutInCutOut' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_CutInCutOut
#define TSeq holo_base_msg_obstacle_CutInCutOutSeq

#define T_initialize holo_base_msg_obstacle_CutInCutOut_initialize

#define T_finalize   holo_base_msg_obstacle_CutInCutOut_finalize
#define T_copy       holo_base_msg_obstacle_CutInCutOut_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_CutInCutOut
#define TSeq holo_base_msg_obstacle_CutInCutOutSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_obstacle_MotionStatus *
holo_base_msg_obstacle_MotionStatus_create(void)
{
    holo_base_msg_obstacle_MotionStatus* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_obstacle_MotionStatus);
    if (sample != NULL) {
        if (!holo_base_msg_obstacle_MotionStatus_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_obstacle_MotionStatus_delete(holo_base_msg_obstacle_MotionStatus*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_obstacle_MotionStatus_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_obstacle_MotionStatus_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_obstacle_MotionStatus_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_obstacle_MotionStatus_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::obstacle::MotionStatus", /* Name */
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
        }}; /* Type code for  holo_base_msg_obstacle_MotionStatus */

    if (is_initialized) {
        return &holo_base_msg_obstacle_MotionStatus_g_tc;
    }

    holo_base_msg_obstacle_MotionStatus_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_obstacle_MotionStatus_g_tc._data._typeCode =  (RTICdrTypeCode *)holo_base_msg_core_uint8_t_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_obstacle_MotionStatus_g_tc._data._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_obstacle_MotionStatus_g_tc._data._annotations._defaultValue._u.octet_value = 0;
    holo_base_msg_obstacle_MotionStatus_g_tc._data._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_obstacle_MotionStatus_g_tc._data._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    holo_base_msg_obstacle_MotionStatus_g_tc._data._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_obstacle_MotionStatus_g_tc._data._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    holo_base_msg_obstacle_MotionStatus_g_tc._data._sampleAccessInfo =
    holo_base_msg_obstacle_MotionStatus_get_sample_access_info();
    holo_base_msg_obstacle_MotionStatus_g_tc._data._typePlugin =
    holo_base_msg_obstacle_MotionStatus_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_obstacle_MotionStatus_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_obstacle_MotionStatus_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_obstacle_MotionStatus_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_obstacle_MotionStatus_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_obstacle_MotionStatus_g_sampleAccessInfo;
    }

    holo_base_msg_obstacle_MotionStatus_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_obstacle_MotionStatus_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_obstacle_MotionStatus_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_obstacle_MotionStatus);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_obstacle_MotionStatus_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_obstacle_MotionStatus_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_obstacle_MotionStatus_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_obstacle_MotionStatus_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_obstacle_MotionStatus_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_obstacle_MotionStatus_g_typePlugin = 
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
        holo_base_msg_obstacle_MotionStatus_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_obstacle_MotionStatus_finalize_w_return,
        NULL
    };

    return &holo_base_msg_obstacle_MotionStatus_g_typePlugin;
}
#endif

RTIBool holo_base_msg_obstacle_MotionStatus_initialize(
    holo_base_msg_obstacle_MotionStatus* sample) {
    return holo_base_msg_obstacle_MotionStatus_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_obstacle_MotionStatus_initialize_ex(
    holo_base_msg_obstacle_MotionStatus* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_obstacle_MotionStatus_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_obstacle_MotionStatus_initialize_w_params(
    holo_base_msg_obstacle_MotionStatus* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

RTIBool holo_base_msg_obstacle_MotionStatus_finalize(
    holo_base_msg_obstacle_MotionStatus* sample)
{

    holo_base_msg_obstacle_MotionStatus_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_obstacle_MotionStatus_finalize_w_return(
    holo_base_msg_obstacle_MotionStatus* sample)
{

    holo_base_msg_obstacle_MotionStatus_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_obstacle_MotionStatus_finalize_ex(
    holo_base_msg_obstacle_MotionStatus* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_obstacle_MotionStatus_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_obstacle_MotionStatus_finalize_w_params(
    holo_base_msg_obstacle_MotionStatus* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_obstacle_MotionStatus_finalize_optional_members(
    holo_base_msg_obstacle_MotionStatus* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_obstacle_MotionStatus_copy(
    holo_base_msg_obstacle_MotionStatus* dst,
    const holo_base_msg_obstacle_MotionStatus* src)
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
* Configure and implement 'holo_base_msg_obstacle_MotionStatus' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_MotionStatus
#define TSeq holo_base_msg_obstacle_MotionStatusSeq

#define T_initialize holo_base_msg_obstacle_MotionStatus_initialize

#define T_finalize   holo_base_msg_obstacle_MotionStatus_finalize
#define T_copy       holo_base_msg_obstacle_MotionStatus_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_MotionStatus
#define TSeq holo_base_msg_obstacle_MotionStatusSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_obstacle_PerceptionAbility *
holo_base_msg_obstacle_PerceptionAbility_create(void)
{
    holo_base_msg_obstacle_PerceptionAbility* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_obstacle_PerceptionAbility);
    if (sample != NULL) {
        if (!holo_base_msg_obstacle_PerceptionAbility_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_obstacle_PerceptionAbility_delete(holo_base_msg_obstacle_PerceptionAbility*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_obstacle_PerceptionAbility_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_obstacle_PerceptionAbility_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_obstacle_PerceptionAbility_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_obstacle_PerceptionAbility_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::obstacle::PerceptionAbility", /* Name */
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
        }}; /* Type code for  holo_base_msg_obstacle_PerceptionAbility */

    if (is_initialized) {
        return &holo_base_msg_obstacle_PerceptionAbility_g_tc;
    }

    holo_base_msg_obstacle_PerceptionAbility_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_obstacle_PerceptionAbility_g_tc._data._typeCode =  (RTICdrTypeCode *)holo_base_msg_core_uint32_t_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_obstacle_PerceptionAbility_g_tc._data._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_PerceptionAbility_g_tc._data._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_obstacle_PerceptionAbility_g_tc._data._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_PerceptionAbility_g_tc._data._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_obstacle_PerceptionAbility_g_tc._data._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_PerceptionAbility_g_tc._data._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_obstacle_PerceptionAbility_g_tc._data._sampleAccessInfo =
    holo_base_msg_obstacle_PerceptionAbility_get_sample_access_info();
    holo_base_msg_obstacle_PerceptionAbility_g_tc._data._typePlugin =
    holo_base_msg_obstacle_PerceptionAbility_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_obstacle_PerceptionAbility_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_obstacle_PerceptionAbility_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_obstacle_PerceptionAbility_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_obstacle_PerceptionAbility_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_obstacle_PerceptionAbility_g_sampleAccessInfo;
    }

    holo_base_msg_obstacle_PerceptionAbility_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_obstacle_PerceptionAbility_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_obstacle_PerceptionAbility_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_obstacle_PerceptionAbility);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_obstacle_PerceptionAbility_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_obstacle_PerceptionAbility_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_obstacle_PerceptionAbility_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_obstacle_PerceptionAbility_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_obstacle_PerceptionAbility_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_obstacle_PerceptionAbility_g_typePlugin = 
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
        holo_base_msg_obstacle_PerceptionAbility_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_obstacle_PerceptionAbility_finalize_w_return,
        NULL
    };

    return &holo_base_msg_obstacle_PerceptionAbility_g_typePlugin;
}
#endif

RTIBool holo_base_msg_obstacle_PerceptionAbility_initialize(
    holo_base_msg_obstacle_PerceptionAbility* sample) {
    return holo_base_msg_obstacle_PerceptionAbility_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_obstacle_PerceptionAbility_initialize_ex(
    holo_base_msg_obstacle_PerceptionAbility* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_obstacle_PerceptionAbility_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_obstacle_PerceptionAbility_initialize_w_params(
    holo_base_msg_obstacle_PerceptionAbility* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

RTIBool holo_base_msg_obstacle_PerceptionAbility_finalize(
    holo_base_msg_obstacle_PerceptionAbility* sample)
{

    holo_base_msg_obstacle_PerceptionAbility_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_obstacle_PerceptionAbility_finalize_w_return(
    holo_base_msg_obstacle_PerceptionAbility* sample)
{

    holo_base_msg_obstacle_PerceptionAbility_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_obstacle_PerceptionAbility_finalize_ex(
    holo_base_msg_obstacle_PerceptionAbility* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_obstacle_PerceptionAbility_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_obstacle_PerceptionAbility_finalize_w_params(
    holo_base_msg_obstacle_PerceptionAbility* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_obstacle_PerceptionAbility_finalize_optional_members(
    holo_base_msg_obstacle_PerceptionAbility* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_obstacle_PerceptionAbility_copy(
    holo_base_msg_obstacle_PerceptionAbility* dst,
    const holo_base_msg_obstacle_PerceptionAbility* src)
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
* Configure and implement 'holo_base_msg_obstacle_PerceptionAbility' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_PerceptionAbility
#define TSeq holo_base_msg_obstacle_PerceptionAbilitySeq

#define T_initialize holo_base_msg_obstacle_PerceptionAbility_initialize

#define T_finalize   holo_base_msg_obstacle_PerceptionAbility_finalize
#define T_copy       holo_base_msg_obstacle_PerceptionAbility_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_PerceptionAbility
#define TSeq holo_base_msg_obstacle_PerceptionAbilitySeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_obstacle_ObstacleGeneral *
holo_base_msg_obstacle_ObstacleGeneral_create(void)
{
    holo_base_msg_obstacle_ObstacleGeneral* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_obstacle_ObstacleGeneral);
    if (sample != NULL) {
        if (!holo_base_msg_obstacle_ObstacleGeneral_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_obstacle_ObstacleGeneral_delete(holo_base_msg_obstacle_ObstacleGeneral*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_obstacle_ObstacleGeneral_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_obstacle_ObstacleGeneral_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_obstacle_ObstacleGeneralTYPENAME = "holo_base_msg::obstacle::ObstacleGeneral";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_obstacle_ObstacleGeneral_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[14]=
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
            (char *)"obstacle_id",/* Member name */
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
            (char *)"sensor_id",/* Member name */
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
            (char *)"classification",/* Member name */
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
            (char *)"obstacle_exist_score",/* Member name */
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
            (char *)"position",/* Member name */
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
            (char *)"relative_velocity",/* Member name */
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
            (char *)"absolute_velocity",/* Member name */
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
            (char *)"acceleration",/* Member name */
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
            (char *)"motion_status",/* Member name */
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
        }, 
        {
            (char *)"bounding_box3",/* Member name */
            {
                11,/* Representation ID */
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
            (char *)"cut_in_cut_out",/* Member name */
            {
                12,/* Representation ID */
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
            (char *)"contour_points",/* Member name */
            {
                13,/* Representation ID */
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

    static DDS_TypeCode holo_base_msg_obstacle_ObstacleGeneral_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::obstacle::ObstacleGeneral", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            14, /* Number of members */
            holo_base_msg_obstacle_ObstacleGeneral_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_obstacle_ObstacleGeneral*/

    if (is_initialized) {
        return &holo_base_msg_obstacle_ObstacleGeneral_g_tc;
    }

    holo_base_msg_obstacle_ObstacleGeneral_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Coordinate_get_typecode();
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint32_t_get_typecode();
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_SensorId_get_typecode();
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Classification_get_typecode();
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[6]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Point3f_get_typecode();
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[7]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Vector3f_get_typecode();
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[8]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Vector3f_get_typecode();
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[9]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Vector3f_get_typecode();
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[10]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_obstacle_MotionStatus_get_typecode();
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[11]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Box3f_get_typecode();
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[12]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_obstacle_CutInCutOut_get_typecode();
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[13]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Point3fSequence_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[2]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[2]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[2]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[3]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[3]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[3]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[4]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[4]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[4]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[4]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[4]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[4]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[5]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[5]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[5]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[5]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[5]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[5]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[10]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[10]._annotations._defaultValue._u.octet_value = 0;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[10]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[10]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[10]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[10]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[12]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[12]._annotations._defaultValue._u.octet_value = 0;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[12]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[12]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[12]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_obstacle_ObstacleGeneral_g_tc_members[12]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    holo_base_msg_obstacle_ObstacleGeneral_g_tc._data._sampleAccessInfo =
    holo_base_msg_obstacle_ObstacleGeneral_get_sample_access_info();
    holo_base_msg_obstacle_ObstacleGeneral_g_tc._data._typePlugin =
    holo_base_msg_obstacle_ObstacleGeneral_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_obstacle_ObstacleGeneral_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_obstacle_ObstacleGeneral_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_obstacle_ObstacleGeneral *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_obstacle_ObstacleGeneral_g_memberAccessInfos[14] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_obstacle_ObstacleGeneral_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_obstacle_ObstacleGeneral_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_obstacle_ObstacleGeneral);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_obstacle_ObstacleGeneral_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stamp - (char *)sample);

    holo_base_msg_obstacle_ObstacleGeneral_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->coord - (char *)sample);

    holo_base_msg_obstacle_ObstacleGeneral_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->obstacle_id - (char *)sample);

    holo_base_msg_obstacle_ObstacleGeneral_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->sensor_id - (char *)sample);

    holo_base_msg_obstacle_ObstacleGeneral_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->classification - (char *)sample);

    holo_base_msg_obstacle_ObstacleGeneral_g_memberAccessInfos[5].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->obstacle_exist_score - (char *)sample);

    holo_base_msg_obstacle_ObstacleGeneral_g_memberAccessInfos[6].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->position - (char *)sample);

    holo_base_msg_obstacle_ObstacleGeneral_g_memberAccessInfos[7].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->relative_velocity - (char *)sample);

    holo_base_msg_obstacle_ObstacleGeneral_g_memberAccessInfos[8].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->absolute_velocity - (char *)sample);

    holo_base_msg_obstacle_ObstacleGeneral_g_memberAccessInfos[9].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->acceleration - (char *)sample);

    holo_base_msg_obstacle_ObstacleGeneral_g_memberAccessInfos[10].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->motion_status - (char *)sample);

    holo_base_msg_obstacle_ObstacleGeneral_g_memberAccessInfos[11].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->bounding_box3 - (char *)sample);

    holo_base_msg_obstacle_ObstacleGeneral_g_memberAccessInfos[12].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->cut_in_cut_out - (char *)sample);

    holo_base_msg_obstacle_ObstacleGeneral_g_memberAccessInfos[13].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->contour_points - (char *)sample);

    holo_base_msg_obstacle_ObstacleGeneral_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_obstacle_ObstacleGeneral_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_obstacle_ObstacleGeneral);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_obstacle_ObstacleGeneral_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_obstacle_ObstacleGeneral_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_obstacle_ObstacleGeneral_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_obstacle_ObstacleGeneral_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_obstacle_ObstacleGeneral_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_obstacle_ObstacleGeneral_g_typePlugin = 
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
        holo_base_msg_obstacle_ObstacleGeneral_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_obstacle_ObstacleGeneral_finalize_w_return,
        NULL
    };

    return &holo_base_msg_obstacle_ObstacleGeneral_g_typePlugin;
}
#endif

RTIBool holo_base_msg_obstacle_ObstacleGeneral_initialize(
    holo_base_msg_obstacle_ObstacleGeneral* sample) {
    return holo_base_msg_obstacle_ObstacleGeneral_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_obstacle_ObstacleGeneral_initialize_ex(
    holo_base_msg_obstacle_ObstacleGeneral* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_obstacle_ObstacleGeneral_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_obstacle_ObstacleGeneral_initialize_w_params(
    holo_base_msg_obstacle_ObstacleGeneral* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

    sample->obstacle_id = 0u;

    sample->sensor_id = 0u;

    sample->classification = 0u;

    sample->obstacle_exist_score = 0.0f;

    if (!holo_base_msg_geometry_Point3f_initialize_w_params(&sample->position,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_numerics_Vector3f_initialize_w_params(&sample->relative_velocity,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_numerics_Vector3f_initialize_w_params(&sample->absolute_velocity,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_numerics_Vector3f_initialize_w_params(&sample->acceleration,
    allocParams)) {
        return RTI_FALSE;
    }

    sample->motion_status = 0;

    if (!holo_base_msg_geometry_Box3f_initialize_w_params(&sample->bounding_box3,
    allocParams)) {
        return RTI_FALSE;
    }

    sample->cut_in_cut_out = 0;

    if (!holo_base_msg_geometry_Point3fSequence_initialize_w_params(&sample->contour_points,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_obstacle_ObstacleGeneral_finalize(
    holo_base_msg_obstacle_ObstacleGeneral* sample)
{

    holo_base_msg_obstacle_ObstacleGeneral_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_obstacle_ObstacleGeneral_finalize_w_return(
    holo_base_msg_obstacle_ObstacleGeneral* sample)
{

    holo_base_msg_obstacle_ObstacleGeneral_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_obstacle_ObstacleGeneral_finalize_ex(
    holo_base_msg_obstacle_ObstacleGeneral* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_obstacle_ObstacleGeneral_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_obstacle_ObstacleGeneral_finalize_w_params(
    holo_base_msg_obstacle_ObstacleGeneral* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->stamp,deallocParams);

    holo_base_msg_geometry_Point3f_finalize_w_params(&sample->position,deallocParams);

    holo_base_msg_numerics_Vector3f_finalize_w_params(&sample->relative_velocity,deallocParams);

    holo_base_msg_numerics_Vector3f_finalize_w_params(&sample->absolute_velocity,deallocParams);

    holo_base_msg_numerics_Vector3f_finalize_w_params(&sample->acceleration,deallocParams);

    holo_base_msg_geometry_Box3f_finalize_w_params(&sample->bounding_box3,deallocParams);

    holo_base_msg_geometry_Point3fSequence_finalize_w_params(&sample->contour_points,deallocParams);

}

void holo_base_msg_obstacle_ObstacleGeneral_finalize_optional_members(
    holo_base_msg_obstacle_ObstacleGeneral* sample, RTIBool deletePointers)
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
    holo_base_msg_geometry_Point3f_finalize_optional_members(&sample->position, deallocParams->delete_pointers);
    holo_base_msg_numerics_Vector3f_finalize_optional_members(&sample->relative_velocity, deallocParams->delete_pointers);
    holo_base_msg_numerics_Vector3f_finalize_optional_members(&sample->absolute_velocity, deallocParams->delete_pointers);
    holo_base_msg_numerics_Vector3f_finalize_optional_members(&sample->acceleration, deallocParams->delete_pointers);
    holo_base_msg_geometry_Box3f_finalize_optional_members(&sample->bounding_box3, deallocParams->delete_pointers);
    holo_base_msg_geometry_Point3fSequence_finalize_optional_members(&sample->contour_points, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_obstacle_ObstacleGeneral_copy(
    holo_base_msg_obstacle_ObstacleGeneral* dst,
    const holo_base_msg_obstacle_ObstacleGeneral* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_copy(
        &dst->stamp,(const holo_base_msg_common_Timestamp*)&src->stamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->coord, &src->coord);
    DDS_Primitive_copy (&dst->obstacle_id, &src->obstacle_id);
    DDS_Primitive_copy (&dst->sensor_id, &src->sensor_id);
    DDS_Primitive_copy (&dst->classification, &src->classification);
    DDS_Primitive_copy (&dst->obstacle_exist_score, &src->obstacle_exist_score);
    if (!holo_base_msg_geometry_Point3f_copy(
        &dst->position,(const holo_base_msg_geometry_Point3f*)&src->position)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_numerics_Vector3f_copy(
        &dst->relative_velocity,(const holo_base_msg_numerics_Vector3f*)&src->relative_velocity)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_numerics_Vector3f_copy(
        &dst->absolute_velocity,(const holo_base_msg_numerics_Vector3f*)&src->absolute_velocity)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_numerics_Vector3f_copy(
        &dst->acceleration,(const holo_base_msg_numerics_Vector3f*)&src->acceleration)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->motion_status, &src->motion_status);
    if (!holo_base_msg_geometry_Box3f_copy(
        &dst->bounding_box3,(const holo_base_msg_geometry_Box3f*)&src->bounding_box3)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->cut_in_cut_out, &src->cut_in_cut_out);
    if (!holo_base_msg_geometry_Point3fSequence_copy(
        &dst->contour_points,(const holo_base_msg_geometry_Point3fSequence*)&src->contour_points)) {
        return RTI_FALSE;
    } 

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_obstacle_ObstacleGeneral' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleGeneral
#define TSeq holo_base_msg_obstacle_ObstacleGeneralSeq

#define T_initialize holo_base_msg_obstacle_ObstacleGeneral_initialize

#define T_finalize   holo_base_msg_obstacle_ObstacleGeneral_finalize
#define T_copy       holo_base_msg_obstacle_ObstacleGeneral_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleGeneral
#define TSeq holo_base_msg_obstacle_ObstacleGeneralSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_obstacle_ObstacleGeneralSequence *
holo_base_msg_obstacle_ObstacleGeneralSequence_create(void)
{
    holo_base_msg_obstacle_ObstacleGeneralSequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_obstacle_ObstacleGeneralSequence);
    if (sample != NULL) {
        if (!holo_base_msg_obstacle_ObstacleGeneralSequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_obstacle_ObstacleGeneralSequence_delete(holo_base_msg_obstacle_ObstacleGeneralSequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_obstacle_ObstacleGeneralSequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_obstacle_ObstacleGeneralSequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_obstacle_ObstacleGeneralSequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_obstacle_ObstacleGeneralSequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_obstacle_ObstacleGeneralSequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::obstacle::ObstacleGeneralSequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_obstacle_ObstacleGeneralSequence */

    if (is_initialized) {
        return &holo_base_msg_obstacle_ObstacleGeneralSequence_g_tc;
    }

    holo_base_msg_obstacle_ObstacleGeneralSequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_obstacle_ObstacleGeneralSequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_obstacle_ObstacleGeneral_get_typecode();
    holo_base_msg_obstacle_ObstacleGeneralSequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_obstacle_ObstacleGeneralSequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_obstacle_ObstacleGeneralSequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_obstacle_ObstacleGeneralSequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_obstacle_ObstacleGeneralSequence_get_sample_access_info();
    holo_base_msg_obstacle_ObstacleGeneralSequence_g_tc._data._typePlugin =
    holo_base_msg_obstacle_ObstacleGeneralSequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_obstacle_ObstacleGeneralSequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_obstacle_ObstacleGeneralSequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_obstacle_ObstacleGeneralSequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_obstacle_ObstacleGeneralSequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_obstacle_ObstacleGeneralSequence_g_sampleAccessInfo;
    }

    holo_base_msg_obstacle_ObstacleGeneralSequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_obstacle_ObstacleGeneralSequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_obstacle_ObstacleGeneralSequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_obstacle_ObstacleGeneralSequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_obstacle_ObstacleGeneralSequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_obstacle_ObstacleGeneralSequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_obstacle_ObstacleGeneralSequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_obstacle_ObstacleGeneralSequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_obstacle_ObstacleGeneralSequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_obstacle_ObstacleGeneralSequence_g_typePlugin = 
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
        holo_base_msg_obstacle_ObstacleGeneralSequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_obstacle_ObstacleGeneralSequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_obstacle_ObstacleGeneralSequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_obstacle_ObstacleGeneralSequence_initialize(
    holo_base_msg_obstacle_ObstacleGeneralSequence* sample) {
    return holo_base_msg_obstacle_ObstacleGeneralSequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_obstacle_ObstacleGeneralSequence_initialize_ex(
    holo_base_msg_obstacle_ObstacleGeneralSequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_obstacle_ObstacleGeneralSequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_obstacle_ObstacleGeneralSequence_initialize_w_params(
    holo_base_msg_obstacle_ObstacleGeneralSequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    void* buffer = NULL;
    if (buffer) {} /* To avoid warnings */

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    if (allocParams->allocate_memory) {
        if(!holo_base_msg_obstacle_ObstacleGeneralSeq_initialize(sample )){
            return RTI_FALSE;
        };
        if (!holo_base_msg_obstacle_ObstacleGeneralSeq_set_maximum(sample, (100))) {
            return RTI_FALSE;
        }
    } else { 
        if(!holo_base_msg_obstacle_ObstacleGeneralSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_obstacle_ObstacleGeneralSequence_finalize(
    holo_base_msg_obstacle_ObstacleGeneralSequence* sample)
{

    holo_base_msg_obstacle_ObstacleGeneralSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_obstacle_ObstacleGeneralSequence_finalize_w_return(
    holo_base_msg_obstacle_ObstacleGeneralSequence* sample)
{

    holo_base_msg_obstacle_ObstacleGeneralSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_obstacle_ObstacleGeneralSequence_finalize_ex(
    holo_base_msg_obstacle_ObstacleGeneralSequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_obstacle_ObstacleGeneralSequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_obstacle_ObstacleGeneralSequence_finalize_w_params(
    holo_base_msg_obstacle_ObstacleGeneralSequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!holo_base_msg_obstacle_ObstacleGeneralSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_obstacle_ObstacleGeneralSequence_finalize_optional_members(
    holo_base_msg_obstacle_ObstacleGeneralSequence* sample, RTIBool deletePointers)
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

    {
        DDS_UnsignedLong i, length;
        length = (RTI_UINT32)holo_base_msg_obstacle_ObstacleGeneralSeq_get_length(
            sample);

        for (i = 0; i < length; i++) {
            holo_base_msg_obstacle_ObstacleGeneral_finalize_optional_members(
                holo_base_msg_obstacle_ObstacleGeneralSeq_get_reference(
                    sample, (RTI_INT32)i), deallocParams->delete_pointers);
        }
    }  

}

RTIBool holo_base_msg_obstacle_ObstacleGeneralSequence_copy(
    holo_base_msg_obstacle_ObstacleGeneralSequence* dst,
    const holo_base_msg_obstacle_ObstacleGeneralSequence* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_obstacle_ObstacleGeneralSeq_copy(dst ,
    src  )) {
        return RTI_FALSE;
    }

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_obstacle_ObstacleGeneralSequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleGeneralSequence
#define TSeq holo_base_msg_obstacle_ObstacleGeneralSequenceSeq

#define T_initialize holo_base_msg_obstacle_ObstacleGeneralSequence_initialize

#define T_finalize   holo_base_msg_obstacle_ObstacleGeneralSequence_finalize
#define T_copy       holo_base_msg_obstacle_ObstacleGeneralSequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleGeneralSequence
#define TSeq holo_base_msg_obstacle_ObstacleGeneralSequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_obstacle_ObstacleGeneralList *
holo_base_msg_obstacle_ObstacleGeneralList_create(void)
{
    holo_base_msg_obstacle_ObstacleGeneralList* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_obstacle_ObstacleGeneralList);
    if (sample != NULL) {
        if (!holo_base_msg_obstacle_ObstacleGeneralList_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_obstacle_ObstacleGeneralList_delete(holo_base_msg_obstacle_ObstacleGeneralList*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_obstacle_ObstacleGeneralList_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_obstacle_ObstacleGeneralList_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_obstacle_ObstacleGeneralListTYPENAME = "holo_base_msg::obstacle::ObstacleGeneralList";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_obstacle_ObstacleGeneralList_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_obstacle_ObstacleGeneralList_g_tc_members[5]=
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
            (char *)"sensor_id",/* Member name */
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
            (char *)"perception_ability",/* Member name */
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
            (char *)"obstacles",/* Member name */
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

    static DDS_TypeCode holo_base_msg_obstacle_ObstacleGeneralList_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::obstacle::ObstacleGeneralList", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            5, /* Number of members */
            holo_base_msg_obstacle_ObstacleGeneralList_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_obstacle_ObstacleGeneralList*/

    if (is_initialized) {
        return &holo_base_msg_obstacle_ObstacleGeneralList_g_tc;
    }

    holo_base_msg_obstacle_ObstacleGeneralList_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_obstacle_ObstacleGeneralList_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_obstacle_ObstacleGeneralList_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Coordinate_get_typecode();
    holo_base_msg_obstacle_ObstacleGeneralList_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_SensorId_get_typecode();
    holo_base_msg_obstacle_ObstacleGeneralList_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_obstacle_PerceptionAbility_get_typecode();
    holo_base_msg_obstacle_ObstacleGeneralList_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_obstacle_ObstacleGeneralSequence_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_obstacle_ObstacleGeneralList_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleGeneralList_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_obstacle_ObstacleGeneralList_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleGeneralList_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_obstacle_ObstacleGeneralList_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleGeneralList_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_obstacle_ObstacleGeneralList_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleGeneralList_g_tc_members[2]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_obstacle_ObstacleGeneralList_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleGeneralList_g_tc_members[2]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_obstacle_ObstacleGeneralList_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleGeneralList_g_tc_members[2]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_obstacle_ObstacleGeneralList_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleGeneralList_g_tc_members[3]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_obstacle_ObstacleGeneralList_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleGeneralList_g_tc_members[3]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_obstacle_ObstacleGeneralList_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleGeneralList_g_tc_members[3]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_obstacle_ObstacleGeneralList_g_tc._data._sampleAccessInfo =
    holo_base_msg_obstacle_ObstacleGeneralList_get_sample_access_info();
    holo_base_msg_obstacle_ObstacleGeneralList_g_tc._data._typePlugin =
    holo_base_msg_obstacle_ObstacleGeneralList_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_obstacle_ObstacleGeneralList_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_obstacle_ObstacleGeneralList_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_obstacle_ObstacleGeneralList *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_obstacle_ObstacleGeneralList_g_memberAccessInfos[5] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_obstacle_ObstacleGeneralList_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_obstacle_ObstacleGeneralList_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_obstacle_ObstacleGeneralList);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_obstacle_ObstacleGeneralList_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stamp - (char *)sample);

    holo_base_msg_obstacle_ObstacleGeneralList_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->coord - (char *)sample);

    holo_base_msg_obstacle_ObstacleGeneralList_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->sensor_id - (char *)sample);

    holo_base_msg_obstacle_ObstacleGeneralList_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->perception_ability - (char *)sample);

    holo_base_msg_obstacle_ObstacleGeneralList_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->obstacles - (char *)sample);

    holo_base_msg_obstacle_ObstacleGeneralList_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_obstacle_ObstacleGeneralList_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_obstacle_ObstacleGeneralList);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_obstacle_ObstacleGeneralList_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_obstacle_ObstacleGeneralList_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_obstacle_ObstacleGeneralList_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_obstacle_ObstacleGeneralList_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_obstacle_ObstacleGeneralList_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_obstacle_ObstacleGeneralList_g_typePlugin = 
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
        holo_base_msg_obstacle_ObstacleGeneralList_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_obstacle_ObstacleGeneralList_finalize_w_return,
        NULL
    };

    return &holo_base_msg_obstacle_ObstacleGeneralList_g_typePlugin;
}
#endif

RTIBool holo_base_msg_obstacle_ObstacleGeneralList_initialize(
    holo_base_msg_obstacle_ObstacleGeneralList* sample) {
    return holo_base_msg_obstacle_ObstacleGeneralList_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_obstacle_ObstacleGeneralList_initialize_ex(
    holo_base_msg_obstacle_ObstacleGeneralList* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_obstacle_ObstacleGeneralList_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_obstacle_ObstacleGeneralList_initialize_w_params(
    holo_base_msg_obstacle_ObstacleGeneralList* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

    sample->sensor_id = 0u;

    sample->perception_ability = 0u;

    if (!holo_base_msg_obstacle_ObstacleGeneralSequence_initialize_w_params(&sample->obstacles,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_obstacle_ObstacleGeneralList_finalize(
    holo_base_msg_obstacle_ObstacleGeneralList* sample)
{

    holo_base_msg_obstacle_ObstacleGeneralList_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_obstacle_ObstacleGeneralList_finalize_w_return(
    holo_base_msg_obstacle_ObstacleGeneralList* sample)
{

    holo_base_msg_obstacle_ObstacleGeneralList_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_obstacle_ObstacleGeneralList_finalize_ex(
    holo_base_msg_obstacle_ObstacleGeneralList* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_obstacle_ObstacleGeneralList_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_obstacle_ObstacleGeneralList_finalize_w_params(
    holo_base_msg_obstacle_ObstacleGeneralList* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->stamp,deallocParams);

    holo_base_msg_obstacle_ObstacleGeneralSequence_finalize_w_params(&sample->obstacles,deallocParams);

}

void holo_base_msg_obstacle_ObstacleGeneralList_finalize_optional_members(
    holo_base_msg_obstacle_ObstacleGeneralList* sample, RTIBool deletePointers)
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
    holo_base_msg_obstacle_ObstacleGeneralSequence_finalize_optional_members(&sample->obstacles, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_obstacle_ObstacleGeneralList_copy(
    holo_base_msg_obstacle_ObstacleGeneralList* dst,
    const holo_base_msg_obstacle_ObstacleGeneralList* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_copy(
        &dst->stamp,(const holo_base_msg_common_Timestamp*)&src->stamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->coord, &src->coord);
    DDS_Primitive_copy (&dst->sensor_id, &src->sensor_id);
    DDS_Primitive_copy (&dst->perception_ability, &src->perception_ability);
    if (!holo_base_msg_obstacle_ObstacleGeneralSequence_copy(
        &dst->obstacles,(const holo_base_msg_obstacle_ObstacleGeneralSequence*)&src->obstacles)) {
        return RTI_FALSE;
    } 

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_obstacle_ObstacleGeneralList' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleGeneralList
#define TSeq holo_base_msg_obstacle_ObstacleGeneralListSeq

#define T_initialize holo_base_msg_obstacle_ObstacleGeneralList_initialize

#define T_finalize   holo_base_msg_obstacle_ObstacleGeneralList_finalize
#define T_copy       holo_base_msg_obstacle_ObstacleGeneralList_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleGeneralList
#define TSeq holo_base_msg_obstacle_ObstacleGeneralListSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_obstacle_ObstacleRadar *
holo_base_msg_obstacle_ObstacleRadar_create(void)
{
    holo_base_msg_obstacle_ObstacleRadar* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_obstacle_ObstacleRadar);
    if (sample != NULL) {
        if (!holo_base_msg_obstacle_ObstacleRadar_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_obstacle_ObstacleRadar_delete(holo_base_msg_obstacle_ObstacleRadar*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_obstacle_ObstacleRadar_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_obstacle_ObstacleRadar_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_obstacle_ObstacleRadarTYPENAME = "holo_base_msg::obstacle::ObstacleRadar";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_obstacle_ObstacleRadar_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_obstacle_ObstacleRadar_g_tc_members[15]=
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
            (char *)"obstacle_id",/* Member name */
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
            (char *)"sensor_id",/* Member name */
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
            (char *)"classification",/* Member name */
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
            (char *)"obstacle_exist_score",/* Member name */
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
            (char *)"position",/* Member name */
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
            (char *)"position_sigma",/* Member name */
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
            (char *)"relative_velocity",/* Member name */
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
            (char *)"relative_velocity_sigma",/* Member name */
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
            (char *)"acceleration",/* Member name */
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
        }, 
        {
            (char *)"acceleration_sigma",/* Member name */
            {
                11,/* Representation ID */
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
            (char *)"motion_status",/* Member name */
            {
                12,/* Representation ID */
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
            (char *)"shape",/* Member name */
            {
                13,/* Representation ID */
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
            (char *)"obstacle_rcs",/* Member name */
            {
                14,/* Representation ID */
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

    static DDS_TypeCode holo_base_msg_obstacle_ObstacleRadar_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::obstacle::ObstacleRadar", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            15, /* Number of members */
            holo_base_msg_obstacle_ObstacleRadar_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_obstacle_ObstacleRadar*/

    if (is_initialized) {
        return &holo_base_msg_obstacle_ObstacleRadar_g_tc;
    }

    holo_base_msg_obstacle_ObstacleRadar_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Coordinate_get_typecode();
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint32_t_get_typecode();
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_SensorId_get_typecode();
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Classification_get_typecode();
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[6]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Point3f_get_typecode();
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[7]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Point3f_get_typecode();
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[8]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Vector3f_get_typecode();
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[9]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Vector3f_get_typecode();
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[10]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Vector3f_get_typecode();
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[11]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Vector3f_get_typecode();
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[12]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_obstacle_MotionStatus_get_typecode();
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[13]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Vector3f_get_typecode();
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[14]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[2]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[2]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[2]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[3]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[3]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[3]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[4]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[4]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[4]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[4]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[4]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[4]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[5]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[5]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[5]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[5]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[5]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[5]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[12]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[12]._annotations._defaultValue._u.octet_value = 0;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[12]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[12]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[12]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[12]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[14]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[14]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[14]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[14]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[14]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_obstacle_ObstacleRadar_g_tc_members[14]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_obstacle_ObstacleRadar_g_tc._data._sampleAccessInfo =
    holo_base_msg_obstacle_ObstacleRadar_get_sample_access_info();
    holo_base_msg_obstacle_ObstacleRadar_g_tc._data._typePlugin =
    holo_base_msg_obstacle_ObstacleRadar_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_obstacle_ObstacleRadar_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_obstacle_ObstacleRadar_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_obstacle_ObstacleRadar *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_obstacle_ObstacleRadar_g_memberAccessInfos[15] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_obstacle_ObstacleRadar_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_obstacle_ObstacleRadar_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_obstacle_ObstacleRadar);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_obstacle_ObstacleRadar_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stamp - (char *)sample);

    holo_base_msg_obstacle_ObstacleRadar_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->coord - (char *)sample);

    holo_base_msg_obstacle_ObstacleRadar_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->obstacle_id - (char *)sample);

    holo_base_msg_obstacle_ObstacleRadar_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->sensor_id - (char *)sample);

    holo_base_msg_obstacle_ObstacleRadar_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->classification - (char *)sample);

    holo_base_msg_obstacle_ObstacleRadar_g_memberAccessInfos[5].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->obstacle_exist_score - (char *)sample);

    holo_base_msg_obstacle_ObstacleRadar_g_memberAccessInfos[6].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->position - (char *)sample);

    holo_base_msg_obstacle_ObstacleRadar_g_memberAccessInfos[7].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->position_sigma - (char *)sample);

    holo_base_msg_obstacle_ObstacleRadar_g_memberAccessInfos[8].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->relative_velocity - (char *)sample);

    holo_base_msg_obstacle_ObstacleRadar_g_memberAccessInfos[9].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->relative_velocity_sigma - (char *)sample);

    holo_base_msg_obstacle_ObstacleRadar_g_memberAccessInfos[10].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->acceleration - (char *)sample);

    holo_base_msg_obstacle_ObstacleRadar_g_memberAccessInfos[11].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->acceleration_sigma - (char *)sample);

    holo_base_msg_obstacle_ObstacleRadar_g_memberAccessInfos[12].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->motion_status - (char *)sample);

    holo_base_msg_obstacle_ObstacleRadar_g_memberAccessInfos[13].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->shape - (char *)sample);

    holo_base_msg_obstacle_ObstacleRadar_g_memberAccessInfos[14].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->obstacle_rcs - (char *)sample);

    holo_base_msg_obstacle_ObstacleRadar_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_obstacle_ObstacleRadar_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_obstacle_ObstacleRadar);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_obstacle_ObstacleRadar_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_obstacle_ObstacleRadar_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_obstacle_ObstacleRadar_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_obstacle_ObstacleRadar_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_obstacle_ObstacleRadar_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_obstacle_ObstacleRadar_g_typePlugin = 
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
        holo_base_msg_obstacle_ObstacleRadar_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_obstacle_ObstacleRadar_finalize_w_return,
        NULL
    };

    return &holo_base_msg_obstacle_ObstacleRadar_g_typePlugin;
}
#endif

RTIBool holo_base_msg_obstacle_ObstacleRadar_initialize(
    holo_base_msg_obstacle_ObstacleRadar* sample) {
    return holo_base_msg_obstacle_ObstacleRadar_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_obstacle_ObstacleRadar_initialize_ex(
    holo_base_msg_obstacle_ObstacleRadar* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_obstacle_ObstacleRadar_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_obstacle_ObstacleRadar_initialize_w_params(
    holo_base_msg_obstacle_ObstacleRadar* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

    sample->obstacle_id = 0u;

    sample->sensor_id = 0u;

    sample->classification = 0u;

    sample->obstacle_exist_score = 0.0f;

    if (!holo_base_msg_geometry_Point3f_initialize_w_params(&sample->position,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_geometry_Point3f_initialize_w_params(&sample->position_sigma,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_numerics_Vector3f_initialize_w_params(&sample->relative_velocity,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_numerics_Vector3f_initialize_w_params(&sample->relative_velocity_sigma,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_numerics_Vector3f_initialize_w_params(&sample->acceleration,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_numerics_Vector3f_initialize_w_params(&sample->acceleration_sigma,
    allocParams)) {
        return RTI_FALSE;
    }

    sample->motion_status = 0;

    if (!holo_base_msg_numerics_Vector3f_initialize_w_params(&sample->shape,
    allocParams)) {
        return RTI_FALSE;
    }

    sample->obstacle_rcs = 0.0f;

    return RTI_TRUE;
}

RTIBool holo_base_msg_obstacle_ObstacleRadar_finalize(
    holo_base_msg_obstacle_ObstacleRadar* sample)
{

    holo_base_msg_obstacle_ObstacleRadar_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_obstacle_ObstacleRadar_finalize_w_return(
    holo_base_msg_obstacle_ObstacleRadar* sample)
{

    holo_base_msg_obstacle_ObstacleRadar_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_obstacle_ObstacleRadar_finalize_ex(
    holo_base_msg_obstacle_ObstacleRadar* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_obstacle_ObstacleRadar_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_obstacle_ObstacleRadar_finalize_w_params(
    holo_base_msg_obstacle_ObstacleRadar* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->stamp,deallocParams);

    holo_base_msg_geometry_Point3f_finalize_w_params(&sample->position,deallocParams);

    holo_base_msg_geometry_Point3f_finalize_w_params(&sample->position_sigma,deallocParams);

    holo_base_msg_numerics_Vector3f_finalize_w_params(&sample->relative_velocity,deallocParams);

    holo_base_msg_numerics_Vector3f_finalize_w_params(&sample->relative_velocity_sigma,deallocParams);

    holo_base_msg_numerics_Vector3f_finalize_w_params(&sample->acceleration,deallocParams);

    holo_base_msg_numerics_Vector3f_finalize_w_params(&sample->acceleration_sigma,deallocParams);

    holo_base_msg_numerics_Vector3f_finalize_w_params(&sample->shape,deallocParams);

}

void holo_base_msg_obstacle_ObstacleRadar_finalize_optional_members(
    holo_base_msg_obstacle_ObstacleRadar* sample, RTIBool deletePointers)
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
    holo_base_msg_geometry_Point3f_finalize_optional_members(&sample->position, deallocParams->delete_pointers);
    holo_base_msg_geometry_Point3f_finalize_optional_members(&sample->position_sigma, deallocParams->delete_pointers);
    holo_base_msg_numerics_Vector3f_finalize_optional_members(&sample->relative_velocity, deallocParams->delete_pointers);
    holo_base_msg_numerics_Vector3f_finalize_optional_members(&sample->relative_velocity_sigma, deallocParams->delete_pointers);
    holo_base_msg_numerics_Vector3f_finalize_optional_members(&sample->acceleration, deallocParams->delete_pointers);
    holo_base_msg_numerics_Vector3f_finalize_optional_members(&sample->acceleration_sigma, deallocParams->delete_pointers);
    holo_base_msg_numerics_Vector3f_finalize_optional_members(&sample->shape, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_obstacle_ObstacleRadar_copy(
    holo_base_msg_obstacle_ObstacleRadar* dst,
    const holo_base_msg_obstacle_ObstacleRadar* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_copy(
        &dst->stamp,(const holo_base_msg_common_Timestamp*)&src->stamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->coord, &src->coord);
    DDS_Primitive_copy (&dst->obstacle_id, &src->obstacle_id);
    DDS_Primitive_copy (&dst->sensor_id, &src->sensor_id);
    DDS_Primitive_copy (&dst->classification, &src->classification);
    DDS_Primitive_copy (&dst->obstacle_exist_score, &src->obstacle_exist_score);
    if (!holo_base_msg_geometry_Point3f_copy(
        &dst->position,(const holo_base_msg_geometry_Point3f*)&src->position)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_geometry_Point3f_copy(
        &dst->position_sigma,(const holo_base_msg_geometry_Point3f*)&src->position_sigma)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_numerics_Vector3f_copy(
        &dst->relative_velocity,(const holo_base_msg_numerics_Vector3f*)&src->relative_velocity)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_numerics_Vector3f_copy(
        &dst->relative_velocity_sigma,(const holo_base_msg_numerics_Vector3f*)&src->relative_velocity_sigma)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_numerics_Vector3f_copy(
        &dst->acceleration,(const holo_base_msg_numerics_Vector3f*)&src->acceleration)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_numerics_Vector3f_copy(
        &dst->acceleration_sigma,(const holo_base_msg_numerics_Vector3f*)&src->acceleration_sigma)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->motion_status, &src->motion_status);
    if (!holo_base_msg_numerics_Vector3f_copy(
        &dst->shape,(const holo_base_msg_numerics_Vector3f*)&src->shape)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->obstacle_rcs, &src->obstacle_rcs);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_obstacle_ObstacleRadar' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleRadar
#define TSeq holo_base_msg_obstacle_ObstacleRadarSeq

#define T_initialize holo_base_msg_obstacle_ObstacleRadar_initialize

#define T_finalize   holo_base_msg_obstacle_ObstacleRadar_finalize
#define T_copy       holo_base_msg_obstacle_ObstacleRadar_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleRadar
#define TSeq holo_base_msg_obstacle_ObstacleRadarSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_obstacle_ObstacleRadarSequence *
holo_base_msg_obstacle_ObstacleRadarSequence_create(void)
{
    holo_base_msg_obstacle_ObstacleRadarSequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_obstacle_ObstacleRadarSequence);
    if (sample != NULL) {
        if (!holo_base_msg_obstacle_ObstacleRadarSequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_obstacle_ObstacleRadarSequence_delete(holo_base_msg_obstacle_ObstacleRadarSequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_obstacle_ObstacleRadarSequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_obstacle_ObstacleRadarSequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_obstacle_ObstacleRadarSequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_obstacle_ObstacleRadarSequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_obstacle_ObstacleRadarSequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::obstacle::ObstacleRadarSequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_obstacle_ObstacleRadarSequence */

    if (is_initialized) {
        return &holo_base_msg_obstacle_ObstacleRadarSequence_g_tc;
    }

    holo_base_msg_obstacle_ObstacleRadarSequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_obstacle_ObstacleRadarSequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_obstacle_ObstacleRadar_get_typecode();
    holo_base_msg_obstacle_ObstacleRadarSequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_obstacle_ObstacleRadarSequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_obstacle_ObstacleRadarSequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_obstacle_ObstacleRadarSequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_obstacle_ObstacleRadarSequence_get_sample_access_info();
    holo_base_msg_obstacle_ObstacleRadarSequence_g_tc._data._typePlugin =
    holo_base_msg_obstacle_ObstacleRadarSequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_obstacle_ObstacleRadarSequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_obstacle_ObstacleRadarSequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_obstacle_ObstacleRadarSequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_obstacle_ObstacleRadarSequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_obstacle_ObstacleRadarSequence_g_sampleAccessInfo;
    }

    holo_base_msg_obstacle_ObstacleRadarSequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_obstacle_ObstacleRadarSequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_obstacle_ObstacleRadarSequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_obstacle_ObstacleRadarSequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_obstacle_ObstacleRadarSequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_obstacle_ObstacleRadarSequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_obstacle_ObstacleRadarSequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_obstacle_ObstacleRadarSequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_obstacle_ObstacleRadarSequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_obstacle_ObstacleRadarSequence_g_typePlugin = 
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
        holo_base_msg_obstacle_ObstacleRadarSequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_obstacle_ObstacleRadarSequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_obstacle_ObstacleRadarSequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_obstacle_ObstacleRadarSequence_initialize(
    holo_base_msg_obstacle_ObstacleRadarSequence* sample) {
    return holo_base_msg_obstacle_ObstacleRadarSequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_obstacle_ObstacleRadarSequence_initialize_ex(
    holo_base_msg_obstacle_ObstacleRadarSequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_obstacle_ObstacleRadarSequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_obstacle_ObstacleRadarSequence_initialize_w_params(
    holo_base_msg_obstacle_ObstacleRadarSequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    void* buffer = NULL;
    if (buffer) {} /* To avoid warnings */

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    if (allocParams->allocate_memory) {
        if(!holo_base_msg_obstacle_ObstacleRadarSeq_initialize(sample )){
            return RTI_FALSE;
        };
        if (!holo_base_msg_obstacle_ObstacleRadarSeq_set_maximum(sample, (100))) {
            return RTI_FALSE;
        }
    } else { 
        if(!holo_base_msg_obstacle_ObstacleRadarSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_obstacle_ObstacleRadarSequence_finalize(
    holo_base_msg_obstacle_ObstacleRadarSequence* sample)
{

    holo_base_msg_obstacle_ObstacleRadarSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_obstacle_ObstacleRadarSequence_finalize_w_return(
    holo_base_msg_obstacle_ObstacleRadarSequence* sample)
{

    holo_base_msg_obstacle_ObstacleRadarSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_obstacle_ObstacleRadarSequence_finalize_ex(
    holo_base_msg_obstacle_ObstacleRadarSequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_obstacle_ObstacleRadarSequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_obstacle_ObstacleRadarSequence_finalize_w_params(
    holo_base_msg_obstacle_ObstacleRadarSequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!holo_base_msg_obstacle_ObstacleRadarSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_obstacle_ObstacleRadarSequence_finalize_optional_members(
    holo_base_msg_obstacle_ObstacleRadarSequence* sample, RTIBool deletePointers)
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

    {
        DDS_UnsignedLong i, length;
        length = (RTI_UINT32)holo_base_msg_obstacle_ObstacleRadarSeq_get_length(
            sample);

        for (i = 0; i < length; i++) {
            holo_base_msg_obstacle_ObstacleRadar_finalize_optional_members(
                holo_base_msg_obstacle_ObstacleRadarSeq_get_reference(
                    sample, (RTI_INT32)i), deallocParams->delete_pointers);
        }
    }  

}

RTIBool holo_base_msg_obstacle_ObstacleRadarSequence_copy(
    holo_base_msg_obstacle_ObstacleRadarSequence* dst,
    const holo_base_msg_obstacle_ObstacleRadarSequence* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_obstacle_ObstacleRadarSeq_copy(dst ,
    src  )) {
        return RTI_FALSE;
    }

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_obstacle_ObstacleRadarSequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleRadarSequence
#define TSeq holo_base_msg_obstacle_ObstacleRadarSequenceSeq

#define T_initialize holo_base_msg_obstacle_ObstacleRadarSequence_initialize

#define T_finalize   holo_base_msg_obstacle_ObstacleRadarSequence_finalize
#define T_copy       holo_base_msg_obstacle_ObstacleRadarSequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleRadarSequence
#define TSeq holo_base_msg_obstacle_ObstacleRadarSequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_obstacle_ObstacleRadarList *
holo_base_msg_obstacle_ObstacleRadarList_create(void)
{
    holo_base_msg_obstacle_ObstacleRadarList* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_obstacle_ObstacleRadarList);
    if (sample != NULL) {
        if (!holo_base_msg_obstacle_ObstacleRadarList_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_obstacle_ObstacleRadarList_delete(holo_base_msg_obstacle_ObstacleRadarList*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_obstacle_ObstacleRadarList_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_obstacle_ObstacleRadarList_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_obstacle_ObstacleRadarListTYPENAME = "holo_base_msg::obstacle::ObstacleRadarList";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_obstacle_ObstacleRadarList_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_obstacle_ObstacleRadarList_g_tc_members[5]=
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
            (char *)"sensor_id",/* Member name */
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
            (char *)"perception_ability",/* Member name */
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
            (char *)"obstacles",/* Member name */
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

    static DDS_TypeCode holo_base_msg_obstacle_ObstacleRadarList_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::obstacle::ObstacleRadarList", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            5, /* Number of members */
            holo_base_msg_obstacle_ObstacleRadarList_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_obstacle_ObstacleRadarList*/

    if (is_initialized) {
        return &holo_base_msg_obstacle_ObstacleRadarList_g_tc;
    }

    holo_base_msg_obstacle_ObstacleRadarList_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_obstacle_ObstacleRadarList_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_obstacle_ObstacleRadarList_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Coordinate_get_typecode();
    holo_base_msg_obstacle_ObstacleRadarList_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_SensorId_get_typecode();
    holo_base_msg_obstacle_ObstacleRadarList_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_obstacle_PerceptionAbility_get_typecode();
    holo_base_msg_obstacle_ObstacleRadarList_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_obstacle_ObstacleRadarSequence_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_obstacle_ObstacleRadarList_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleRadarList_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_obstacle_ObstacleRadarList_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleRadarList_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_obstacle_ObstacleRadarList_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleRadarList_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_obstacle_ObstacleRadarList_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleRadarList_g_tc_members[2]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_obstacle_ObstacleRadarList_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleRadarList_g_tc_members[2]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_obstacle_ObstacleRadarList_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleRadarList_g_tc_members[2]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_obstacle_ObstacleRadarList_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleRadarList_g_tc_members[3]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_obstacle_ObstacleRadarList_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleRadarList_g_tc_members[3]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_obstacle_ObstacleRadarList_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleRadarList_g_tc_members[3]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_obstacle_ObstacleRadarList_g_tc._data._sampleAccessInfo =
    holo_base_msg_obstacle_ObstacleRadarList_get_sample_access_info();
    holo_base_msg_obstacle_ObstacleRadarList_g_tc._data._typePlugin =
    holo_base_msg_obstacle_ObstacleRadarList_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_obstacle_ObstacleRadarList_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_obstacle_ObstacleRadarList_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_obstacle_ObstacleRadarList *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_obstacle_ObstacleRadarList_g_memberAccessInfos[5] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_obstacle_ObstacleRadarList_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_obstacle_ObstacleRadarList_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_obstacle_ObstacleRadarList);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_obstacle_ObstacleRadarList_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stamp - (char *)sample);

    holo_base_msg_obstacle_ObstacleRadarList_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->coord - (char *)sample);

    holo_base_msg_obstacle_ObstacleRadarList_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->sensor_id - (char *)sample);

    holo_base_msg_obstacle_ObstacleRadarList_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->perception_ability - (char *)sample);

    holo_base_msg_obstacle_ObstacleRadarList_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->obstacles - (char *)sample);

    holo_base_msg_obstacle_ObstacleRadarList_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_obstacle_ObstacleRadarList_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_obstacle_ObstacleRadarList);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_obstacle_ObstacleRadarList_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_obstacle_ObstacleRadarList_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_obstacle_ObstacleRadarList_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_obstacle_ObstacleRadarList_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_obstacle_ObstacleRadarList_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_obstacle_ObstacleRadarList_g_typePlugin = 
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
        holo_base_msg_obstacle_ObstacleRadarList_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_obstacle_ObstacleRadarList_finalize_w_return,
        NULL
    };

    return &holo_base_msg_obstacle_ObstacleRadarList_g_typePlugin;
}
#endif

RTIBool holo_base_msg_obstacle_ObstacleRadarList_initialize(
    holo_base_msg_obstacle_ObstacleRadarList* sample) {
    return holo_base_msg_obstacle_ObstacleRadarList_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_obstacle_ObstacleRadarList_initialize_ex(
    holo_base_msg_obstacle_ObstacleRadarList* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_obstacle_ObstacleRadarList_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_obstacle_ObstacleRadarList_initialize_w_params(
    holo_base_msg_obstacle_ObstacleRadarList* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

    sample->sensor_id = 0u;

    sample->perception_ability = 0u;

    if (!holo_base_msg_obstacle_ObstacleRadarSequence_initialize_w_params(&sample->obstacles,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_obstacle_ObstacleRadarList_finalize(
    holo_base_msg_obstacle_ObstacleRadarList* sample)
{

    holo_base_msg_obstacle_ObstacleRadarList_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_obstacle_ObstacleRadarList_finalize_w_return(
    holo_base_msg_obstacle_ObstacleRadarList* sample)
{

    holo_base_msg_obstacle_ObstacleRadarList_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_obstacle_ObstacleRadarList_finalize_ex(
    holo_base_msg_obstacle_ObstacleRadarList* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_obstacle_ObstacleRadarList_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_obstacle_ObstacleRadarList_finalize_w_params(
    holo_base_msg_obstacle_ObstacleRadarList* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->stamp,deallocParams);

    holo_base_msg_obstacle_ObstacleRadarSequence_finalize_w_params(&sample->obstacles,deallocParams);

}

void holo_base_msg_obstacle_ObstacleRadarList_finalize_optional_members(
    holo_base_msg_obstacle_ObstacleRadarList* sample, RTIBool deletePointers)
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
    holo_base_msg_obstacle_ObstacleRadarSequence_finalize_optional_members(&sample->obstacles, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_obstacle_ObstacleRadarList_copy(
    holo_base_msg_obstacle_ObstacleRadarList* dst,
    const holo_base_msg_obstacle_ObstacleRadarList* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_copy(
        &dst->stamp,(const holo_base_msg_common_Timestamp*)&src->stamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->coord, &src->coord);
    DDS_Primitive_copy (&dst->sensor_id, &src->sensor_id);
    DDS_Primitive_copy (&dst->perception_ability, &src->perception_ability);
    if (!holo_base_msg_obstacle_ObstacleRadarSequence_copy(
        &dst->obstacles,(const holo_base_msg_obstacle_ObstacleRadarSequence*)&src->obstacles)) {
        return RTI_FALSE;
    } 

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_obstacle_ObstacleRadarList' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleRadarList
#define TSeq holo_base_msg_obstacle_ObstacleRadarListSeq

#define T_initialize holo_base_msg_obstacle_ObstacleRadarList_initialize

#define T_finalize   holo_base_msg_obstacle_ObstacleRadarList_finalize
#define T_copy       holo_base_msg_obstacle_ObstacleRadarList_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleRadarList
#define TSeq holo_base_msg_obstacle_ObstacleRadarListSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_obstacle_ObstacleUss *
holo_base_msg_obstacle_ObstacleUss_create(void)
{
    holo_base_msg_obstacle_ObstacleUss* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_obstacle_ObstacleUss);
    if (sample != NULL) {
        if (!holo_base_msg_obstacle_ObstacleUss_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_obstacle_ObstacleUss_delete(holo_base_msg_obstacle_ObstacleUss*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_obstacle_ObstacleUss_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_obstacle_ObstacleUss_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_obstacle_ObstacleUssTYPENAME = "holo_base_msg::obstacle::ObstacleUss";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_obstacle_ObstacleUss_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_obstacle_ObstacleUss_g_tc_members[9]=
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
            (char *)"obstacle_id",/* Member name */
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
            (char *)"sensor_id",/* Member name */
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
            (char *)"classification",/* Member name */
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
            (char *)"obstacle_exist_score",/* Member name */
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
            (char *)"position",/* Member name */
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
            (char *)"position_sigma",/* Member name */
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
            (char *)"fov",/* Member name */
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
        }
    };

    static DDS_TypeCode holo_base_msg_obstacle_ObstacleUss_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::obstacle::ObstacleUss", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            9, /* Number of members */
            holo_base_msg_obstacle_ObstacleUss_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_obstacle_ObstacleUss*/

    if (is_initialized) {
        return &holo_base_msg_obstacle_ObstacleUss_g_tc;
    }

    holo_base_msg_obstacle_ObstacleUss_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_obstacle_ObstacleUss_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Coordinate_get_typecode();
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint32_t_get_typecode();
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_SensorId_get_typecode();
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Classification_get_typecode();
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[6]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Point3f_get_typecode();
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[7]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Point3f_get_typecode();
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[8]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_obstacle_ObstacleUss_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_obstacle_ObstacleUss_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[2]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[2]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[2]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_obstacle_ObstacleUss_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[3]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[3]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[3]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_obstacle_ObstacleUss_g_tc_members[4]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[4]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[4]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[4]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[4]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[4]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_obstacle_ObstacleUss_g_tc_members[5]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[5]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[5]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[5]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[5]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[5]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_obstacle_ObstacleUss_g_tc_members[8]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[8]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[8]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[8]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[8]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_obstacle_ObstacleUss_g_tc_members[8]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_obstacle_ObstacleUss_g_tc._data._sampleAccessInfo =
    holo_base_msg_obstacle_ObstacleUss_get_sample_access_info();
    holo_base_msg_obstacle_ObstacleUss_g_tc._data._typePlugin =
    holo_base_msg_obstacle_ObstacleUss_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_obstacle_ObstacleUss_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_obstacle_ObstacleUss_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_obstacle_ObstacleUss *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_obstacle_ObstacleUss_g_memberAccessInfos[9] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_obstacle_ObstacleUss_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_obstacle_ObstacleUss_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_obstacle_ObstacleUss);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_obstacle_ObstacleUss_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stamp - (char *)sample);

    holo_base_msg_obstacle_ObstacleUss_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->coord - (char *)sample);

    holo_base_msg_obstacle_ObstacleUss_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->obstacle_id - (char *)sample);

    holo_base_msg_obstacle_ObstacleUss_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->sensor_id - (char *)sample);

    holo_base_msg_obstacle_ObstacleUss_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->classification - (char *)sample);

    holo_base_msg_obstacle_ObstacleUss_g_memberAccessInfos[5].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->obstacle_exist_score - (char *)sample);

    holo_base_msg_obstacle_ObstacleUss_g_memberAccessInfos[6].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->position - (char *)sample);

    holo_base_msg_obstacle_ObstacleUss_g_memberAccessInfos[7].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->position_sigma - (char *)sample);

    holo_base_msg_obstacle_ObstacleUss_g_memberAccessInfos[8].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->fov - (char *)sample);

    holo_base_msg_obstacle_ObstacleUss_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_obstacle_ObstacleUss_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_obstacle_ObstacleUss);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_obstacle_ObstacleUss_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_obstacle_ObstacleUss_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_obstacle_ObstacleUss_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_obstacle_ObstacleUss_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_obstacle_ObstacleUss_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_obstacle_ObstacleUss_g_typePlugin = 
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
        holo_base_msg_obstacle_ObstacleUss_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_obstacle_ObstacleUss_finalize_w_return,
        NULL
    };

    return &holo_base_msg_obstacle_ObstacleUss_g_typePlugin;
}
#endif

RTIBool holo_base_msg_obstacle_ObstacleUss_initialize(
    holo_base_msg_obstacle_ObstacleUss* sample) {
    return holo_base_msg_obstacle_ObstacleUss_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_obstacle_ObstacleUss_initialize_ex(
    holo_base_msg_obstacle_ObstacleUss* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_obstacle_ObstacleUss_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_obstacle_ObstacleUss_initialize_w_params(
    holo_base_msg_obstacle_ObstacleUss* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

    sample->obstacle_id = 0u;

    sample->sensor_id = 0u;

    sample->classification = 0u;

    sample->obstacle_exist_score = 0.0f;

    if (!holo_base_msg_geometry_Point3f_initialize_w_params(&sample->position,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_geometry_Point3f_initialize_w_params(&sample->position_sigma,
    allocParams)) {
        return RTI_FALSE;
    }

    sample->fov = 0.0f;

    return RTI_TRUE;
}

RTIBool holo_base_msg_obstacle_ObstacleUss_finalize(
    holo_base_msg_obstacle_ObstacleUss* sample)
{

    holo_base_msg_obstacle_ObstacleUss_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_obstacle_ObstacleUss_finalize_w_return(
    holo_base_msg_obstacle_ObstacleUss* sample)
{

    holo_base_msg_obstacle_ObstacleUss_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_obstacle_ObstacleUss_finalize_ex(
    holo_base_msg_obstacle_ObstacleUss* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_obstacle_ObstacleUss_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_obstacle_ObstacleUss_finalize_w_params(
    holo_base_msg_obstacle_ObstacleUss* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->stamp,deallocParams);

    holo_base_msg_geometry_Point3f_finalize_w_params(&sample->position,deallocParams);

    holo_base_msg_geometry_Point3f_finalize_w_params(&sample->position_sigma,deallocParams);

}

void holo_base_msg_obstacle_ObstacleUss_finalize_optional_members(
    holo_base_msg_obstacle_ObstacleUss* sample, RTIBool deletePointers)
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
    holo_base_msg_geometry_Point3f_finalize_optional_members(&sample->position, deallocParams->delete_pointers);
    holo_base_msg_geometry_Point3f_finalize_optional_members(&sample->position_sigma, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_obstacle_ObstacleUss_copy(
    holo_base_msg_obstacle_ObstacleUss* dst,
    const holo_base_msg_obstacle_ObstacleUss* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_copy(
        &dst->stamp,(const holo_base_msg_common_Timestamp*)&src->stamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->coord, &src->coord);
    DDS_Primitive_copy (&dst->obstacle_id, &src->obstacle_id);
    DDS_Primitive_copy (&dst->sensor_id, &src->sensor_id);
    DDS_Primitive_copy (&dst->classification, &src->classification);
    DDS_Primitive_copy (&dst->obstacle_exist_score, &src->obstacle_exist_score);
    if (!holo_base_msg_geometry_Point3f_copy(
        &dst->position,(const holo_base_msg_geometry_Point3f*)&src->position)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_geometry_Point3f_copy(
        &dst->position_sigma,(const holo_base_msg_geometry_Point3f*)&src->position_sigma)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->fov, &src->fov);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_obstacle_ObstacleUss' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleUss
#define TSeq holo_base_msg_obstacle_ObstacleUssSeq

#define T_initialize holo_base_msg_obstacle_ObstacleUss_initialize

#define T_finalize   holo_base_msg_obstacle_ObstacleUss_finalize
#define T_copy       holo_base_msg_obstacle_ObstacleUss_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleUss
#define TSeq holo_base_msg_obstacle_ObstacleUssSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_obstacle_ObstacleUssSequence *
holo_base_msg_obstacle_ObstacleUssSequence_create(void)
{
    holo_base_msg_obstacle_ObstacleUssSequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_obstacle_ObstacleUssSequence);
    if (sample != NULL) {
        if (!holo_base_msg_obstacle_ObstacleUssSequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_obstacle_ObstacleUssSequence_delete(holo_base_msg_obstacle_ObstacleUssSequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_obstacle_ObstacleUssSequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_obstacle_ObstacleUssSequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_obstacle_ObstacleUssSequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_obstacle_ObstacleUssSequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_obstacle_ObstacleUssSequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::obstacle::ObstacleUssSequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_obstacle_ObstacleUssSequence */

    if (is_initialized) {
        return &holo_base_msg_obstacle_ObstacleUssSequence_g_tc;
    }

    holo_base_msg_obstacle_ObstacleUssSequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_obstacle_ObstacleUssSequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_obstacle_ObstacleUss_get_typecode();
    holo_base_msg_obstacle_ObstacleUssSequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_obstacle_ObstacleUssSequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_obstacle_ObstacleUssSequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_obstacle_ObstacleUssSequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_obstacle_ObstacleUssSequence_get_sample_access_info();
    holo_base_msg_obstacle_ObstacleUssSequence_g_tc._data._typePlugin =
    holo_base_msg_obstacle_ObstacleUssSequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_obstacle_ObstacleUssSequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_obstacle_ObstacleUssSequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_obstacle_ObstacleUssSequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_obstacle_ObstacleUssSequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_obstacle_ObstacleUssSequence_g_sampleAccessInfo;
    }

    holo_base_msg_obstacle_ObstacleUssSequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_obstacle_ObstacleUssSequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_obstacle_ObstacleUssSequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_obstacle_ObstacleUssSequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_obstacle_ObstacleUssSequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_obstacle_ObstacleUssSequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_obstacle_ObstacleUssSequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_obstacle_ObstacleUssSequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_obstacle_ObstacleUssSequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_obstacle_ObstacleUssSequence_g_typePlugin = 
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
        holo_base_msg_obstacle_ObstacleUssSequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_obstacle_ObstacleUssSequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_obstacle_ObstacleUssSequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_obstacle_ObstacleUssSequence_initialize(
    holo_base_msg_obstacle_ObstacleUssSequence* sample) {
    return holo_base_msg_obstacle_ObstacleUssSequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_obstacle_ObstacleUssSequence_initialize_ex(
    holo_base_msg_obstacle_ObstacleUssSequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_obstacle_ObstacleUssSequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_obstacle_ObstacleUssSequence_initialize_w_params(
    holo_base_msg_obstacle_ObstacleUssSequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    void* buffer = NULL;
    if (buffer) {} /* To avoid warnings */

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    if (allocParams->allocate_memory) {
        if(!holo_base_msg_obstacle_ObstacleUssSeq_initialize(sample )){
            return RTI_FALSE;
        };
        if (!holo_base_msg_obstacle_ObstacleUssSeq_set_maximum(sample, (100))) {
            return RTI_FALSE;
        }
    } else { 
        if(!holo_base_msg_obstacle_ObstacleUssSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_obstacle_ObstacleUssSequence_finalize(
    holo_base_msg_obstacle_ObstacleUssSequence* sample)
{

    holo_base_msg_obstacle_ObstacleUssSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_obstacle_ObstacleUssSequence_finalize_w_return(
    holo_base_msg_obstacle_ObstacleUssSequence* sample)
{

    holo_base_msg_obstacle_ObstacleUssSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_obstacle_ObstacleUssSequence_finalize_ex(
    holo_base_msg_obstacle_ObstacleUssSequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_obstacle_ObstacleUssSequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_obstacle_ObstacleUssSequence_finalize_w_params(
    holo_base_msg_obstacle_ObstacleUssSequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!holo_base_msg_obstacle_ObstacleUssSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_obstacle_ObstacleUssSequence_finalize_optional_members(
    holo_base_msg_obstacle_ObstacleUssSequence* sample, RTIBool deletePointers)
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

    {
        DDS_UnsignedLong i, length;
        length = (RTI_UINT32)holo_base_msg_obstacle_ObstacleUssSeq_get_length(
            sample);

        for (i = 0; i < length; i++) {
            holo_base_msg_obstacle_ObstacleUss_finalize_optional_members(
                holo_base_msg_obstacle_ObstacleUssSeq_get_reference(
                    sample, (RTI_INT32)i), deallocParams->delete_pointers);
        }
    }  

}

RTIBool holo_base_msg_obstacle_ObstacleUssSequence_copy(
    holo_base_msg_obstacle_ObstacleUssSequence* dst,
    const holo_base_msg_obstacle_ObstacleUssSequence* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_obstacle_ObstacleUssSeq_copy(dst ,
    src  )) {
        return RTI_FALSE;
    }

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_obstacle_ObstacleUssSequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleUssSequence
#define TSeq holo_base_msg_obstacle_ObstacleUssSequenceSeq

#define T_initialize holo_base_msg_obstacle_ObstacleUssSequence_initialize

#define T_finalize   holo_base_msg_obstacle_ObstacleUssSequence_finalize
#define T_copy       holo_base_msg_obstacle_ObstacleUssSequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleUssSequence
#define TSeq holo_base_msg_obstacle_ObstacleUssSequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_obstacle_ObstacleUssList *
holo_base_msg_obstacle_ObstacleUssList_create(void)
{
    holo_base_msg_obstacle_ObstacleUssList* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_obstacle_ObstacleUssList);
    if (sample != NULL) {
        if (!holo_base_msg_obstacle_ObstacleUssList_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_obstacle_ObstacleUssList_delete(holo_base_msg_obstacle_ObstacleUssList*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_obstacle_ObstacleUssList_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_obstacle_ObstacleUssList_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_obstacle_ObstacleUssListTYPENAME = "holo_base_msg::obstacle::ObstacleUssList";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_obstacle_ObstacleUssList_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_obstacle_ObstacleUssList_g_tc_members[5]=
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
            (char *)"sensor_id",/* Member name */
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
            (char *)"perception_ability",/* Member name */
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
            (char *)"obstacles",/* Member name */
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

    static DDS_TypeCode holo_base_msg_obstacle_ObstacleUssList_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::obstacle::ObstacleUssList", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            5, /* Number of members */
            holo_base_msg_obstacle_ObstacleUssList_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_obstacle_ObstacleUssList*/

    if (is_initialized) {
        return &holo_base_msg_obstacle_ObstacleUssList_g_tc;
    }

    holo_base_msg_obstacle_ObstacleUssList_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_obstacle_ObstacleUssList_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_obstacle_ObstacleUssList_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Coordinate_get_typecode();
    holo_base_msg_obstacle_ObstacleUssList_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_SensorId_get_typecode();
    holo_base_msg_obstacle_ObstacleUssList_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_obstacle_PerceptionAbility_get_typecode();
    holo_base_msg_obstacle_ObstacleUssList_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_obstacle_ObstacleUssSequence_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_obstacle_ObstacleUssList_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleUssList_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_obstacle_ObstacleUssList_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleUssList_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_obstacle_ObstacleUssList_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleUssList_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_obstacle_ObstacleUssList_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleUssList_g_tc_members[2]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_obstacle_ObstacleUssList_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleUssList_g_tc_members[2]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_obstacle_ObstacleUssList_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleUssList_g_tc_members[2]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_obstacle_ObstacleUssList_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleUssList_g_tc_members[3]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_obstacle_ObstacleUssList_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleUssList_g_tc_members[3]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_obstacle_ObstacleUssList_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleUssList_g_tc_members[3]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_obstacle_ObstacleUssList_g_tc._data._sampleAccessInfo =
    holo_base_msg_obstacle_ObstacleUssList_get_sample_access_info();
    holo_base_msg_obstacle_ObstacleUssList_g_tc._data._typePlugin =
    holo_base_msg_obstacle_ObstacleUssList_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_obstacle_ObstacleUssList_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_obstacle_ObstacleUssList_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_obstacle_ObstacleUssList *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_obstacle_ObstacleUssList_g_memberAccessInfos[5] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_obstacle_ObstacleUssList_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_obstacle_ObstacleUssList_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_obstacle_ObstacleUssList);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_obstacle_ObstacleUssList_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stamp - (char *)sample);

    holo_base_msg_obstacle_ObstacleUssList_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->coord - (char *)sample);

    holo_base_msg_obstacle_ObstacleUssList_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->sensor_id - (char *)sample);

    holo_base_msg_obstacle_ObstacleUssList_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->perception_ability - (char *)sample);

    holo_base_msg_obstacle_ObstacleUssList_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->obstacles - (char *)sample);

    holo_base_msg_obstacle_ObstacleUssList_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_obstacle_ObstacleUssList_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_obstacle_ObstacleUssList);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_obstacle_ObstacleUssList_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_obstacle_ObstacleUssList_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_obstacle_ObstacleUssList_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_obstacle_ObstacleUssList_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_obstacle_ObstacleUssList_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_obstacle_ObstacleUssList_g_typePlugin = 
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
        holo_base_msg_obstacle_ObstacleUssList_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_obstacle_ObstacleUssList_finalize_w_return,
        NULL
    };

    return &holo_base_msg_obstacle_ObstacleUssList_g_typePlugin;
}
#endif

RTIBool holo_base_msg_obstacle_ObstacleUssList_initialize(
    holo_base_msg_obstacle_ObstacleUssList* sample) {
    return holo_base_msg_obstacle_ObstacleUssList_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_obstacle_ObstacleUssList_initialize_ex(
    holo_base_msg_obstacle_ObstacleUssList* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_obstacle_ObstacleUssList_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_obstacle_ObstacleUssList_initialize_w_params(
    holo_base_msg_obstacle_ObstacleUssList* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

    sample->sensor_id = 0u;

    sample->perception_ability = 0u;

    if (!holo_base_msg_obstacle_ObstacleUssSequence_initialize_w_params(&sample->obstacles,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_obstacle_ObstacleUssList_finalize(
    holo_base_msg_obstacle_ObstacleUssList* sample)
{

    holo_base_msg_obstacle_ObstacleUssList_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_obstacle_ObstacleUssList_finalize_w_return(
    holo_base_msg_obstacle_ObstacleUssList* sample)
{

    holo_base_msg_obstacle_ObstacleUssList_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_obstacle_ObstacleUssList_finalize_ex(
    holo_base_msg_obstacle_ObstacleUssList* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_obstacle_ObstacleUssList_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_obstacle_ObstacleUssList_finalize_w_params(
    holo_base_msg_obstacle_ObstacleUssList* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->stamp,deallocParams);

    holo_base_msg_obstacle_ObstacleUssSequence_finalize_w_params(&sample->obstacles,deallocParams);

}

void holo_base_msg_obstacle_ObstacleUssList_finalize_optional_members(
    holo_base_msg_obstacle_ObstacleUssList* sample, RTIBool deletePointers)
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
    holo_base_msg_obstacle_ObstacleUssSequence_finalize_optional_members(&sample->obstacles, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_obstacle_ObstacleUssList_copy(
    holo_base_msg_obstacle_ObstacleUssList* dst,
    const holo_base_msg_obstacle_ObstacleUssList* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_copy(
        &dst->stamp,(const holo_base_msg_common_Timestamp*)&src->stamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->coord, &src->coord);
    DDS_Primitive_copy (&dst->sensor_id, &src->sensor_id);
    DDS_Primitive_copy (&dst->perception_ability, &src->perception_ability);
    if (!holo_base_msg_obstacle_ObstacleUssSequence_copy(
        &dst->obstacles,(const holo_base_msg_obstacle_ObstacleUssSequence*)&src->obstacles)) {
        return RTI_FALSE;
    } 

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_obstacle_ObstacleUssList' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleUssList
#define TSeq holo_base_msg_obstacle_ObstacleUssListSeq

#define T_initialize holo_base_msg_obstacle_ObstacleUssList_initialize

#define T_finalize   holo_base_msg_obstacle_ObstacleUssList_finalize
#define T_copy       holo_base_msg_obstacle_ObstacleUssList_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleUssList
#define TSeq holo_base_msg_obstacle_ObstacleUssListSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_obstacle_ObstacleVision *
holo_base_msg_obstacle_ObstacleVision_create(void)
{
    holo_base_msg_obstacle_ObstacleVision* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_obstacle_ObstacleVision);
    if (sample != NULL) {
        if (!holo_base_msg_obstacle_ObstacleVision_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_obstacle_ObstacleVision_delete(holo_base_msg_obstacle_ObstacleVision*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_obstacle_ObstacleVision_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_obstacle_ObstacleVision_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_obstacle_ObstacleVisionTYPENAME = "holo_base_msg::obstacle::ObstacleVision";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_obstacle_ObstacleVision_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_obstacle_ObstacleVision_g_tc_members[17]=
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
            (char *)"obstacle_id",/* Member name */
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
            (char *)"sensor_id",/* Member name */
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
            (char *)"classification",/* Member name */
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
            (char *)"obstacle_exist_score",/* Member name */
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
            (char *)"position",/* Member name */
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
            (char *)"position_sigma",/* Member name */
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
            (char *)"relative_velocity",/* Member name */
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
            (char *)"relative_velocity_sigma",/* Member name */
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
            (char *)"acceleration",/* Member name */
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
        }, 
        {
            (char *)"acceleration_sigma",/* Member name */
            {
                11,/* Representation ID */
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
            (char *)"motion_status",/* Member name */
            {
                12,/* Representation ID */
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
            (char *)"bounding_box2",/* Member name */
            {
                13,/* Representation ID */
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
            (char *)"bounding_box3",/* Member name */
            {
                14,/* Representation ID */
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
            (char *)"cut_in_cut_out",/* Member name */
            {
                15,/* Representation ID */
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
            (char *)"key_points",/* Member name */
            {
                16,/* Representation ID */
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

    static DDS_TypeCode holo_base_msg_obstacle_ObstacleVision_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::obstacle::ObstacleVision", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            17, /* Number of members */
            holo_base_msg_obstacle_ObstacleVision_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_obstacle_ObstacleVision*/

    if (is_initialized) {
        return &holo_base_msg_obstacle_ObstacleVision_g_tc;
    }

    holo_base_msg_obstacle_ObstacleVision_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_obstacle_ObstacleVision_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Coordinate_get_typecode();
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint32_t_get_typecode();
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_SensorId_get_typecode();
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Classification_get_typecode();
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[6]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Point3f_get_typecode();
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[7]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Point3f_get_typecode();
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[8]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Vector3f_get_typecode();
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[9]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Vector3f_get_typecode();
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[10]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Vector3f_get_typecode();
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[11]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_Vector3f_get_typecode();
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[12]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_obstacle_MotionStatus_get_typecode();
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[13]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Box2f_get_typecode();
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[14]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Box3f_get_typecode();
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[15]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_obstacle_CutInCutOut_get_typecode();
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[16]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_vision_KeyPoint2fSequence_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_obstacle_ObstacleVision_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_obstacle_ObstacleVision_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[2]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[2]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[2]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_obstacle_ObstacleVision_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[3]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[3]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[3]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_obstacle_ObstacleVision_g_tc_members[4]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[4]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[4]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[4]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[4]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[4]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_obstacle_ObstacleVision_g_tc_members[5]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[5]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[5]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[5]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[5]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[5]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_obstacle_ObstacleVision_g_tc_members[12]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[12]._annotations._defaultValue._u.octet_value = 0;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[12]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[12]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[12]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[12]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    holo_base_msg_obstacle_ObstacleVision_g_tc_members[15]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[15]._annotations._defaultValue._u.octet_value = 0;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[15]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[15]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[15]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_obstacle_ObstacleVision_g_tc_members[15]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    holo_base_msg_obstacle_ObstacleVision_g_tc._data._sampleAccessInfo =
    holo_base_msg_obstacle_ObstacleVision_get_sample_access_info();
    holo_base_msg_obstacle_ObstacleVision_g_tc._data._typePlugin =
    holo_base_msg_obstacle_ObstacleVision_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_obstacle_ObstacleVision_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_obstacle_ObstacleVision_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_obstacle_ObstacleVision *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_obstacle_ObstacleVision_g_memberAccessInfos[17] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_obstacle_ObstacleVision_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_obstacle_ObstacleVision_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_obstacle_ObstacleVision);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_obstacle_ObstacleVision_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stamp - (char *)sample);

    holo_base_msg_obstacle_ObstacleVision_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->coord - (char *)sample);

    holo_base_msg_obstacle_ObstacleVision_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->obstacle_id - (char *)sample);

    holo_base_msg_obstacle_ObstacleVision_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->sensor_id - (char *)sample);

    holo_base_msg_obstacle_ObstacleVision_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->classification - (char *)sample);

    holo_base_msg_obstacle_ObstacleVision_g_memberAccessInfos[5].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->obstacle_exist_score - (char *)sample);

    holo_base_msg_obstacle_ObstacleVision_g_memberAccessInfos[6].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->position - (char *)sample);

    holo_base_msg_obstacle_ObstacleVision_g_memberAccessInfos[7].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->position_sigma - (char *)sample);

    holo_base_msg_obstacle_ObstacleVision_g_memberAccessInfos[8].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->relative_velocity - (char *)sample);

    holo_base_msg_obstacle_ObstacleVision_g_memberAccessInfos[9].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->relative_velocity_sigma - (char *)sample);

    holo_base_msg_obstacle_ObstacleVision_g_memberAccessInfos[10].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->acceleration - (char *)sample);

    holo_base_msg_obstacle_ObstacleVision_g_memberAccessInfos[11].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->acceleration_sigma - (char *)sample);

    holo_base_msg_obstacle_ObstacleVision_g_memberAccessInfos[12].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->motion_status - (char *)sample);

    holo_base_msg_obstacle_ObstacleVision_g_memberAccessInfos[13].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->bounding_box2 - (char *)sample);

    holo_base_msg_obstacle_ObstacleVision_g_memberAccessInfos[14].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->bounding_box3 - (char *)sample);

    holo_base_msg_obstacle_ObstacleVision_g_memberAccessInfos[15].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->cut_in_cut_out - (char *)sample);

    holo_base_msg_obstacle_ObstacleVision_g_memberAccessInfos[16].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->key_points - (char *)sample);

    holo_base_msg_obstacle_ObstacleVision_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_obstacle_ObstacleVision_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_obstacle_ObstacleVision);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_obstacle_ObstacleVision_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_obstacle_ObstacleVision_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_obstacle_ObstacleVision_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_obstacle_ObstacleVision_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_obstacle_ObstacleVision_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_obstacle_ObstacleVision_g_typePlugin = 
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
        holo_base_msg_obstacle_ObstacleVision_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_obstacle_ObstacleVision_finalize_w_return,
        NULL
    };

    return &holo_base_msg_obstacle_ObstacleVision_g_typePlugin;
}
#endif

RTIBool holo_base_msg_obstacle_ObstacleVision_initialize(
    holo_base_msg_obstacle_ObstacleVision* sample) {
    return holo_base_msg_obstacle_ObstacleVision_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_obstacle_ObstacleVision_initialize_ex(
    holo_base_msg_obstacle_ObstacleVision* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_obstacle_ObstacleVision_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_obstacle_ObstacleVision_initialize_w_params(
    holo_base_msg_obstacle_ObstacleVision* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

    sample->obstacle_id = 0u;

    sample->sensor_id = 0u;

    sample->classification = 0u;

    sample->obstacle_exist_score = 0.0f;

    if (!holo_base_msg_geometry_Point3f_initialize_w_params(&sample->position,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_geometry_Point3f_initialize_w_params(&sample->position_sigma,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_numerics_Vector3f_initialize_w_params(&sample->relative_velocity,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_numerics_Vector3f_initialize_w_params(&sample->relative_velocity_sigma,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_numerics_Vector3f_initialize_w_params(&sample->acceleration,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_numerics_Vector3f_initialize_w_params(&sample->acceleration_sigma,
    allocParams)) {
        return RTI_FALSE;
    }

    sample->motion_status = 0;

    if (!holo_base_msg_geometry_Box2f_initialize_w_params(&sample->bounding_box2,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_geometry_Box3f_initialize_w_params(&sample->bounding_box3,
    allocParams)) {
        return RTI_FALSE;
    }

    sample->cut_in_cut_out = 0;

    if (!holo_base_msg_vision_KeyPoint2fSequence_initialize_w_params(&sample->key_points,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_obstacle_ObstacleVision_finalize(
    holo_base_msg_obstacle_ObstacleVision* sample)
{

    holo_base_msg_obstacle_ObstacleVision_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_obstacle_ObstacleVision_finalize_w_return(
    holo_base_msg_obstacle_ObstacleVision* sample)
{

    holo_base_msg_obstacle_ObstacleVision_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_obstacle_ObstacleVision_finalize_ex(
    holo_base_msg_obstacle_ObstacleVision* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_obstacle_ObstacleVision_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_obstacle_ObstacleVision_finalize_w_params(
    holo_base_msg_obstacle_ObstacleVision* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->stamp,deallocParams);

    holo_base_msg_geometry_Point3f_finalize_w_params(&sample->position,deallocParams);

    holo_base_msg_geometry_Point3f_finalize_w_params(&sample->position_sigma,deallocParams);

    holo_base_msg_numerics_Vector3f_finalize_w_params(&sample->relative_velocity,deallocParams);

    holo_base_msg_numerics_Vector3f_finalize_w_params(&sample->relative_velocity_sigma,deallocParams);

    holo_base_msg_numerics_Vector3f_finalize_w_params(&sample->acceleration,deallocParams);

    holo_base_msg_numerics_Vector3f_finalize_w_params(&sample->acceleration_sigma,deallocParams);

    holo_base_msg_geometry_Box2f_finalize_w_params(&sample->bounding_box2,deallocParams);

    holo_base_msg_geometry_Box3f_finalize_w_params(&sample->bounding_box3,deallocParams);

    holo_base_msg_vision_KeyPoint2fSequence_finalize_w_params(&sample->key_points,deallocParams);

}

void holo_base_msg_obstacle_ObstacleVision_finalize_optional_members(
    holo_base_msg_obstacle_ObstacleVision* sample, RTIBool deletePointers)
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
    holo_base_msg_geometry_Point3f_finalize_optional_members(&sample->position, deallocParams->delete_pointers);
    holo_base_msg_geometry_Point3f_finalize_optional_members(&sample->position_sigma, deallocParams->delete_pointers);
    holo_base_msg_numerics_Vector3f_finalize_optional_members(&sample->relative_velocity, deallocParams->delete_pointers);
    holo_base_msg_numerics_Vector3f_finalize_optional_members(&sample->relative_velocity_sigma, deallocParams->delete_pointers);
    holo_base_msg_numerics_Vector3f_finalize_optional_members(&sample->acceleration, deallocParams->delete_pointers);
    holo_base_msg_numerics_Vector3f_finalize_optional_members(&sample->acceleration_sigma, deallocParams->delete_pointers);
    holo_base_msg_geometry_Box2f_finalize_optional_members(&sample->bounding_box2, deallocParams->delete_pointers);
    holo_base_msg_geometry_Box3f_finalize_optional_members(&sample->bounding_box3, deallocParams->delete_pointers);
    holo_base_msg_vision_KeyPoint2fSequence_finalize_optional_members(&sample->key_points, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_obstacle_ObstacleVision_copy(
    holo_base_msg_obstacle_ObstacleVision* dst,
    const holo_base_msg_obstacle_ObstacleVision* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_copy(
        &dst->stamp,(const holo_base_msg_common_Timestamp*)&src->stamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->coord, &src->coord);
    DDS_Primitive_copy (&dst->obstacle_id, &src->obstacle_id);
    DDS_Primitive_copy (&dst->sensor_id, &src->sensor_id);
    DDS_Primitive_copy (&dst->classification, &src->classification);
    DDS_Primitive_copy (&dst->obstacle_exist_score, &src->obstacle_exist_score);
    if (!holo_base_msg_geometry_Point3f_copy(
        &dst->position,(const holo_base_msg_geometry_Point3f*)&src->position)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_geometry_Point3f_copy(
        &dst->position_sigma,(const holo_base_msg_geometry_Point3f*)&src->position_sigma)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_numerics_Vector3f_copy(
        &dst->relative_velocity,(const holo_base_msg_numerics_Vector3f*)&src->relative_velocity)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_numerics_Vector3f_copy(
        &dst->relative_velocity_sigma,(const holo_base_msg_numerics_Vector3f*)&src->relative_velocity_sigma)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_numerics_Vector3f_copy(
        &dst->acceleration,(const holo_base_msg_numerics_Vector3f*)&src->acceleration)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_numerics_Vector3f_copy(
        &dst->acceleration_sigma,(const holo_base_msg_numerics_Vector3f*)&src->acceleration_sigma)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->motion_status, &src->motion_status);
    if (!holo_base_msg_geometry_Box2f_copy(
        &dst->bounding_box2,(const holo_base_msg_geometry_Box2f*)&src->bounding_box2)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_geometry_Box3f_copy(
        &dst->bounding_box3,(const holo_base_msg_geometry_Box3f*)&src->bounding_box3)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->cut_in_cut_out, &src->cut_in_cut_out);
    if (!holo_base_msg_vision_KeyPoint2fSequence_copy(
        &dst->key_points,(const holo_base_msg_vision_KeyPoint2fSequence*)&src->key_points)) {
        return RTI_FALSE;
    } 

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_obstacle_ObstacleVision' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleVision
#define TSeq holo_base_msg_obstacle_ObstacleVisionSeq

#define T_initialize holo_base_msg_obstacle_ObstacleVision_initialize

#define T_finalize   holo_base_msg_obstacle_ObstacleVision_finalize
#define T_copy       holo_base_msg_obstacle_ObstacleVision_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleVision
#define TSeq holo_base_msg_obstacle_ObstacleVisionSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_obstacle_ObstacleVisionSequence *
holo_base_msg_obstacle_ObstacleVisionSequence_create(void)
{
    holo_base_msg_obstacle_ObstacleVisionSequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_obstacle_ObstacleVisionSequence);
    if (sample != NULL) {
        if (!holo_base_msg_obstacle_ObstacleVisionSequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_obstacle_ObstacleVisionSequence_delete(holo_base_msg_obstacle_ObstacleVisionSequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_obstacle_ObstacleVisionSequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_obstacle_ObstacleVisionSequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_obstacle_ObstacleVisionSequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_obstacle_ObstacleVisionSequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_obstacle_ObstacleVisionSequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::obstacle::ObstacleVisionSequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_obstacle_ObstacleVisionSequence */

    if (is_initialized) {
        return &holo_base_msg_obstacle_ObstacleVisionSequence_g_tc;
    }

    holo_base_msg_obstacle_ObstacleVisionSequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_obstacle_ObstacleVisionSequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_obstacle_ObstacleVision_get_typecode();
    holo_base_msg_obstacle_ObstacleVisionSequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_obstacle_ObstacleVisionSequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_obstacle_ObstacleVisionSequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_obstacle_ObstacleVisionSequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_obstacle_ObstacleVisionSequence_get_sample_access_info();
    holo_base_msg_obstacle_ObstacleVisionSequence_g_tc._data._typePlugin =
    holo_base_msg_obstacle_ObstacleVisionSequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_obstacle_ObstacleVisionSequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_obstacle_ObstacleVisionSequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_obstacle_ObstacleVisionSequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_obstacle_ObstacleVisionSequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_obstacle_ObstacleVisionSequence_g_sampleAccessInfo;
    }

    holo_base_msg_obstacle_ObstacleVisionSequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_obstacle_ObstacleVisionSequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_obstacle_ObstacleVisionSequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_obstacle_ObstacleVisionSequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_obstacle_ObstacleVisionSequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_obstacle_ObstacleVisionSequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_obstacle_ObstacleVisionSequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_obstacle_ObstacleVisionSequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_obstacle_ObstacleVisionSequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_obstacle_ObstacleVisionSequence_g_typePlugin = 
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
        holo_base_msg_obstacle_ObstacleVisionSequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_obstacle_ObstacleVisionSequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_obstacle_ObstacleVisionSequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_obstacle_ObstacleVisionSequence_initialize(
    holo_base_msg_obstacle_ObstacleVisionSequence* sample) {
    return holo_base_msg_obstacle_ObstacleVisionSequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_obstacle_ObstacleVisionSequence_initialize_ex(
    holo_base_msg_obstacle_ObstacleVisionSequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_obstacle_ObstacleVisionSequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_obstacle_ObstacleVisionSequence_initialize_w_params(
    holo_base_msg_obstacle_ObstacleVisionSequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    void* buffer = NULL;
    if (buffer) {} /* To avoid warnings */

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    if (allocParams->allocate_memory) {
        if(!holo_base_msg_obstacle_ObstacleVisionSeq_initialize(sample )){
            return RTI_FALSE;
        };
        if (!holo_base_msg_obstacle_ObstacleVisionSeq_set_maximum(sample, (100))) {
            return RTI_FALSE;
        }
    } else { 
        if(!holo_base_msg_obstacle_ObstacleVisionSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_obstacle_ObstacleVisionSequence_finalize(
    holo_base_msg_obstacle_ObstacleVisionSequence* sample)
{

    holo_base_msg_obstacle_ObstacleVisionSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_obstacle_ObstacleVisionSequence_finalize_w_return(
    holo_base_msg_obstacle_ObstacleVisionSequence* sample)
{

    holo_base_msg_obstacle_ObstacleVisionSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_obstacle_ObstacleVisionSequence_finalize_ex(
    holo_base_msg_obstacle_ObstacleVisionSequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_obstacle_ObstacleVisionSequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_obstacle_ObstacleVisionSequence_finalize_w_params(
    holo_base_msg_obstacle_ObstacleVisionSequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!holo_base_msg_obstacle_ObstacleVisionSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_obstacle_ObstacleVisionSequence_finalize_optional_members(
    holo_base_msg_obstacle_ObstacleVisionSequence* sample, RTIBool deletePointers)
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

    {
        DDS_UnsignedLong i, length;
        length = (RTI_UINT32)holo_base_msg_obstacle_ObstacleVisionSeq_get_length(
            sample);

        for (i = 0; i < length; i++) {
            holo_base_msg_obstacle_ObstacleVision_finalize_optional_members(
                holo_base_msg_obstacle_ObstacleVisionSeq_get_reference(
                    sample, (RTI_INT32)i), deallocParams->delete_pointers);
        }
    }  

}

RTIBool holo_base_msg_obstacle_ObstacleVisionSequence_copy(
    holo_base_msg_obstacle_ObstacleVisionSequence* dst,
    const holo_base_msg_obstacle_ObstacleVisionSequence* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_obstacle_ObstacleVisionSeq_copy(dst ,
    src  )) {
        return RTI_FALSE;
    }

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_obstacle_ObstacleVisionSequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleVisionSequence
#define TSeq holo_base_msg_obstacle_ObstacleVisionSequenceSeq

#define T_initialize holo_base_msg_obstacle_ObstacleVisionSequence_initialize

#define T_finalize   holo_base_msg_obstacle_ObstacleVisionSequence_finalize
#define T_copy       holo_base_msg_obstacle_ObstacleVisionSequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleVisionSequence
#define TSeq holo_base_msg_obstacle_ObstacleVisionSequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_obstacle_ObstacleVisionList *
holo_base_msg_obstacle_ObstacleVisionList_create(void)
{
    holo_base_msg_obstacle_ObstacleVisionList* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_obstacle_ObstacleVisionList);
    if (sample != NULL) {
        if (!holo_base_msg_obstacle_ObstacleVisionList_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_obstacle_ObstacleVisionList_delete(holo_base_msg_obstacle_ObstacleVisionList*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_obstacle_ObstacleVisionList_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_obstacle_ObstacleVisionList_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_obstacle_ObstacleVisionListTYPENAME = "holo_base_msg::obstacle::ObstacleVisionList";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_obstacle_ObstacleVisionList_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_obstacle_ObstacleVisionList_g_tc_members[5]=
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
            (char *)"sensor_id",/* Member name */
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
            (char *)"perception_ability",/* Member name */
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
            (char *)"obstacles",/* Member name */
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

    static DDS_TypeCode holo_base_msg_obstacle_ObstacleVisionList_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::obstacle::ObstacleVisionList", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            5, /* Number of members */
            holo_base_msg_obstacle_ObstacleVisionList_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_obstacle_ObstacleVisionList*/

    if (is_initialized) {
        return &holo_base_msg_obstacle_ObstacleVisionList_g_tc;
    }

    holo_base_msg_obstacle_ObstacleVisionList_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_obstacle_ObstacleVisionList_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_obstacle_ObstacleVisionList_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Coordinate_get_typecode();
    holo_base_msg_obstacle_ObstacleVisionList_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_SensorId_get_typecode();
    holo_base_msg_obstacle_ObstacleVisionList_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_obstacle_PerceptionAbility_get_typecode();
    holo_base_msg_obstacle_ObstacleVisionList_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_obstacle_ObstacleVisionSequence_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_obstacle_ObstacleVisionList_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleVisionList_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_obstacle_ObstacleVisionList_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleVisionList_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_obstacle_ObstacleVisionList_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleVisionList_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_obstacle_ObstacleVisionList_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleVisionList_g_tc_members[2]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_obstacle_ObstacleVisionList_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleVisionList_g_tc_members[2]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_obstacle_ObstacleVisionList_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleVisionList_g_tc_members[2]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_obstacle_ObstacleVisionList_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleVisionList_g_tc_members[3]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_obstacle_ObstacleVisionList_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleVisionList_g_tc_members[3]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_obstacle_ObstacleVisionList_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_obstacle_ObstacleVisionList_g_tc_members[3]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_obstacle_ObstacleVisionList_g_tc._data._sampleAccessInfo =
    holo_base_msg_obstacle_ObstacleVisionList_get_sample_access_info();
    holo_base_msg_obstacle_ObstacleVisionList_g_tc._data._typePlugin =
    holo_base_msg_obstacle_ObstacleVisionList_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_obstacle_ObstacleVisionList_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_obstacle_ObstacleVisionList_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_obstacle_ObstacleVisionList *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_obstacle_ObstacleVisionList_g_memberAccessInfos[5] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_obstacle_ObstacleVisionList_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_obstacle_ObstacleVisionList_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_obstacle_ObstacleVisionList);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_obstacle_ObstacleVisionList_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stamp - (char *)sample);

    holo_base_msg_obstacle_ObstacleVisionList_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->coord - (char *)sample);

    holo_base_msg_obstacle_ObstacleVisionList_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->sensor_id - (char *)sample);

    holo_base_msg_obstacle_ObstacleVisionList_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->perception_ability - (char *)sample);

    holo_base_msg_obstacle_ObstacleVisionList_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->obstacles - (char *)sample);

    holo_base_msg_obstacle_ObstacleVisionList_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_obstacle_ObstacleVisionList_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_obstacle_ObstacleVisionList);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_obstacle_ObstacleVisionList_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_obstacle_ObstacleVisionList_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_obstacle_ObstacleVisionList_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_obstacle_ObstacleVisionList_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_obstacle_ObstacleVisionList_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_obstacle_ObstacleVisionList_g_typePlugin = 
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
        holo_base_msg_obstacle_ObstacleVisionList_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_obstacle_ObstacleVisionList_finalize_w_return,
        NULL
    };

    return &holo_base_msg_obstacle_ObstacleVisionList_g_typePlugin;
}
#endif

RTIBool holo_base_msg_obstacle_ObstacleVisionList_initialize(
    holo_base_msg_obstacle_ObstacleVisionList* sample) {
    return holo_base_msg_obstacle_ObstacleVisionList_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_obstacle_ObstacleVisionList_initialize_ex(
    holo_base_msg_obstacle_ObstacleVisionList* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_obstacle_ObstacleVisionList_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_obstacle_ObstacleVisionList_initialize_w_params(
    holo_base_msg_obstacle_ObstacleVisionList* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

    sample->sensor_id = 0u;

    sample->perception_ability = 0u;

    if (!holo_base_msg_obstacle_ObstacleVisionSequence_initialize_w_params(&sample->obstacles,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_obstacle_ObstacleVisionList_finalize(
    holo_base_msg_obstacle_ObstacleVisionList* sample)
{

    holo_base_msg_obstacle_ObstacleVisionList_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_obstacle_ObstacleVisionList_finalize_w_return(
    holo_base_msg_obstacle_ObstacleVisionList* sample)
{

    holo_base_msg_obstacle_ObstacleVisionList_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_obstacle_ObstacleVisionList_finalize_ex(
    holo_base_msg_obstacle_ObstacleVisionList* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_obstacle_ObstacleVisionList_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_obstacle_ObstacleVisionList_finalize_w_params(
    holo_base_msg_obstacle_ObstacleVisionList* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->stamp,deallocParams);

    holo_base_msg_obstacle_ObstacleVisionSequence_finalize_w_params(&sample->obstacles,deallocParams);

}

void holo_base_msg_obstacle_ObstacleVisionList_finalize_optional_members(
    holo_base_msg_obstacle_ObstacleVisionList* sample, RTIBool deletePointers)
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
    holo_base_msg_obstacle_ObstacleVisionSequence_finalize_optional_members(&sample->obstacles, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_obstacle_ObstacleVisionList_copy(
    holo_base_msg_obstacle_ObstacleVisionList* dst,
    const holo_base_msg_obstacle_ObstacleVisionList* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_copy(
        &dst->stamp,(const holo_base_msg_common_Timestamp*)&src->stamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->coord, &src->coord);
    DDS_Primitive_copy (&dst->sensor_id, &src->sensor_id);
    DDS_Primitive_copy (&dst->perception_ability, &src->perception_ability);
    if (!holo_base_msg_obstacle_ObstacleVisionSequence_copy(
        &dst->obstacles,(const holo_base_msg_obstacle_ObstacleVisionSequence*)&src->obstacles)) {
        return RTI_FALSE;
    } 

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_obstacle_ObstacleVisionList' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleVisionList
#define TSeq holo_base_msg_obstacle_ObstacleVisionListSeq

#define T_initialize holo_base_msg_obstacle_ObstacleVisionList_initialize

#define T_finalize   holo_base_msg_obstacle_ObstacleVisionList_finalize
#define T_copy       holo_base_msg_obstacle_ObstacleVisionList_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleVisionList
#define TSeq holo_base_msg_obstacle_ObstacleVisionListSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

