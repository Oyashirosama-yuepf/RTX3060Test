/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from PointCloudGeneral.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "PointCloudGeneral.h"

#ifndef UNUSED_ARG
#define UNUSED_ARG(x) (void)(x)
#endif

#include "dds_c/dds_c_typecode.h"
/*** SOURCE_BEGIN ***/

holo_base_msg_common_float32_t *
holo_base_msg_common_float32_t_create(void)
{
    holo_base_msg_common_float32_t* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_float32_t);
    if (sample != NULL) {
        if (!holo_base_msg_common_float32_t_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_float32_t_delete(holo_base_msg_common_float32_t*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_float32_t_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_float32_t_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_float32_t_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_common_float32_t_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::common::float32_t", /* Name */
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
        }}; /* Type code for  holo_base_msg_common_float32_t */

    if (is_initialized) {
        return &holo_base_msg_common_float32_t_g_tc;
    }

    holo_base_msg_common_float32_t_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_float32_t_g_tc._data._typeCode =  (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_common_float32_t_g_tc._data._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_float32_t_g_tc._data._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_float32_t_g_tc._data._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_float32_t_g_tc._data._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_float32_t_g_tc._data._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_float32_t_g_tc._data._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_float32_t_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_float32_t_get_sample_access_info();
    holo_base_msg_common_float32_t_g_tc._data._typePlugin =
    holo_base_msg_common_float32_t_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_float32_t_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_float32_t_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_float32_t_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_float32_t_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_float32_t_g_sampleAccessInfo;
    }

    holo_base_msg_common_float32_t_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_common_float32_t_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_float32_t_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_float32_t);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_float32_t_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_float32_t_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_float32_t_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_float32_t_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_float32_t_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_float32_t_g_typePlugin = 
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
        holo_base_msg_common_float32_t_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_float32_t_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_float32_t_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_float32_t_initialize(
    holo_base_msg_common_float32_t* sample) {
    return holo_base_msg_common_float32_t_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_float32_t_initialize_ex(
    holo_base_msg_common_float32_t* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_float32_t_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_float32_t_initialize_w_params(
    holo_base_msg_common_float32_t* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    (*sample) = 0.0f;

    return RTI_TRUE;
}

RTIBool holo_base_msg_common_float32_t_finalize(
    holo_base_msg_common_float32_t* sample)
{

    holo_base_msg_common_float32_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_float32_t_finalize_w_return(
    holo_base_msg_common_float32_t* sample)
{

    holo_base_msg_common_float32_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_float32_t_finalize_ex(
    holo_base_msg_common_float32_t* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_float32_t_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_float32_t_finalize_w_params(
    holo_base_msg_common_float32_t* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_common_float32_t_finalize_optional_members(
    holo_base_msg_common_float32_t* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_common_float32_t_copy(
    holo_base_msg_common_float32_t* dst,
    const holo_base_msg_common_float32_t* src)
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
* Configure and implement 'holo_base_msg_common_float32_t' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_float32_t
#define TSeq holo_base_msg_common_float32_tSeq

#define T_initialize holo_base_msg_common_float32_t_initialize

#define T_finalize   holo_base_msg_common_float32_t_finalize
#define T_copy       holo_base_msg_common_float32_t_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_float32_t
#define TSeq holo_base_msg_common_float32_tSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_bool_t *
holo_base_msg_common_bool_t_create(void)
{
    holo_base_msg_common_bool_t* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_bool_t);
    if (sample != NULL) {
        if (!holo_base_msg_common_bool_t_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_bool_t_delete(holo_base_msg_common_bool_t*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_bool_t_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_bool_t_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_bool_t_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_common_bool_t_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::common::bool_t", /* Name */
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
        }}; /* Type code for  holo_base_msg_common_bool_t */

    if (is_initialized) {
        return &holo_base_msg_common_bool_t_g_tc;
    }

    holo_base_msg_common_bool_t_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_bool_t_g_tc._data._typeCode =  (RTICdrTypeCode *)holo_base_msg_core_bool_t_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_common_bool_t_g_tc._data._annotations._defaultValue._d = RTI_XCDR_TK_BOOLEAN;
    holo_base_msg_common_bool_t_g_tc._data._annotations._defaultValue._u.boolean_value = 0;

    holo_base_msg_common_bool_t_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_bool_t_get_sample_access_info();
    holo_base_msg_common_bool_t_g_tc._data._typePlugin =
    holo_base_msg_common_bool_t_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_bool_t_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_bool_t_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_bool_t_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_bool_t_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_bool_t_g_sampleAccessInfo;
    }

    holo_base_msg_common_bool_t_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_common_bool_t_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_bool_t_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_bool_t);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_bool_t_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_bool_t_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_bool_t_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_bool_t_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_bool_t_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_bool_t_g_typePlugin = 
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
        holo_base_msg_common_bool_t_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_bool_t_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_bool_t_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_bool_t_initialize(
    holo_base_msg_common_bool_t* sample) {
    return holo_base_msg_common_bool_t_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_bool_t_initialize_ex(
    holo_base_msg_common_bool_t* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_bool_t_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_bool_t_initialize_w_params(
    holo_base_msg_common_bool_t* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

RTIBool holo_base_msg_common_bool_t_finalize(
    holo_base_msg_common_bool_t* sample)
{

    holo_base_msg_common_bool_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_bool_t_finalize_w_return(
    holo_base_msg_common_bool_t* sample)
{

    holo_base_msg_common_bool_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_bool_t_finalize_ex(
    holo_base_msg_common_bool_t* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_bool_t_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_bool_t_finalize_w_params(
    holo_base_msg_common_bool_t* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_common_bool_t_finalize_optional_members(
    holo_base_msg_common_bool_t* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_common_bool_t_copy(
    holo_base_msg_common_bool_t* dst,
    const holo_base_msg_common_bool_t* src)
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
* Configure and implement 'holo_base_msg_common_bool_t' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_bool_t
#define TSeq holo_base_msg_common_bool_tSeq

#define T_initialize holo_base_msg_common_bool_t_initialize

#define T_finalize   holo_base_msg_common_bool_t_finalize
#define T_copy       holo_base_msg_common_bool_t_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_bool_t
#define TSeq holo_base_msg_common_bool_tSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_uint8_t *
holo_base_msg_common_uint8_t_create(void)
{
    holo_base_msg_common_uint8_t* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_uint8_t);
    if (sample != NULL) {
        if (!holo_base_msg_common_uint8_t_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_uint8_t_delete(holo_base_msg_common_uint8_t*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_uint8_t_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_uint8_t_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_uint8_t_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_common_uint8_t_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::common::uint8_t", /* Name */
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
        }}; /* Type code for  holo_base_msg_common_uint8_t */

    if (is_initialized) {
        return &holo_base_msg_common_uint8_t_g_tc;
    }

    holo_base_msg_common_uint8_t_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_uint8_t_g_tc._data._typeCode =  (RTICdrTypeCode *)holo_base_msg_core_uint8_t_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_common_uint8_t_g_tc._data._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_uint8_t_g_tc._data._annotations._defaultValue._u.octet_value = 0;
    holo_base_msg_common_uint8_t_g_tc._data._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_uint8_t_g_tc._data._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    holo_base_msg_common_uint8_t_g_tc._data._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_uint8_t_g_tc._data._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    holo_base_msg_common_uint8_t_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_uint8_t_get_sample_access_info();
    holo_base_msg_common_uint8_t_g_tc._data._typePlugin =
    holo_base_msg_common_uint8_t_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_uint8_t_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_uint8_t_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_uint8_t_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_uint8_t_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_uint8_t_g_sampleAccessInfo;
    }

    holo_base_msg_common_uint8_t_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_common_uint8_t_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_uint8_t_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_uint8_t);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_uint8_t_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_uint8_t_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_uint8_t_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_uint8_t_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_uint8_t_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_uint8_t_g_typePlugin = 
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
        holo_base_msg_common_uint8_t_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_uint8_t_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_uint8_t_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_uint8_t_initialize(
    holo_base_msg_common_uint8_t* sample) {
    return holo_base_msg_common_uint8_t_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_uint8_t_initialize_ex(
    holo_base_msg_common_uint8_t* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_uint8_t_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_uint8_t_initialize_w_params(
    holo_base_msg_common_uint8_t* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

RTIBool holo_base_msg_common_uint8_t_finalize(
    holo_base_msg_common_uint8_t* sample)
{

    holo_base_msg_common_uint8_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_uint8_t_finalize_w_return(
    holo_base_msg_common_uint8_t* sample)
{

    holo_base_msg_common_uint8_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_uint8_t_finalize_ex(
    holo_base_msg_common_uint8_t* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_uint8_t_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_uint8_t_finalize_w_params(
    holo_base_msg_common_uint8_t* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_common_uint8_t_finalize_optional_members(
    holo_base_msg_common_uint8_t* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_common_uint8_t_copy(
    holo_base_msg_common_uint8_t* dst,
    const holo_base_msg_common_uint8_t* src)
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
* Configure and implement 'holo_base_msg_common_uint8_t' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_uint8_t
#define TSeq holo_base_msg_common_uint8_tSeq

#define T_initialize holo_base_msg_common_uint8_t_initialize

#define T_finalize   holo_base_msg_common_uint8_t_finalize
#define T_copy       holo_base_msg_common_uint8_t_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_uint8_t
#define TSeq holo_base_msg_common_uint8_tSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_uint64_t *
holo_base_msg_common_uint64_t_create(void)
{
    holo_base_msg_common_uint64_t* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_uint64_t);
    if (sample != NULL) {
        if (!holo_base_msg_common_uint64_t_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_uint64_t_delete(holo_base_msg_common_uint64_t*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_uint64_t_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_uint64_t_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_uint64_t_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_common_uint64_t_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::common::uint64_t", /* Name */
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
        }}; /* Type code for  holo_base_msg_common_uint64_t */

    if (is_initialized) {
        return &holo_base_msg_common_uint64_t_g_tc;
    }

    holo_base_msg_common_uint64_t_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_uint64_t_g_tc._data._typeCode =  (RTICdrTypeCode *)holo_base_msg_core_uint64_t_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_common_uint64_t_g_tc._data._annotations._defaultValue._d = RTI_XCDR_TK_ULONGLONG;
    holo_base_msg_common_uint64_t_g_tc._data._annotations._defaultValue._u.ulong_long_value = 0ull;
    holo_base_msg_common_uint64_t_g_tc._data._annotations._minValue._d = RTI_XCDR_TK_ULONGLONG;
    holo_base_msg_common_uint64_t_g_tc._data._annotations._minValue._u.ulong_long_value = RTIXCdrUnsignedLongLong_MIN;
    holo_base_msg_common_uint64_t_g_tc._data._annotations._maxValue._d = RTI_XCDR_TK_ULONGLONG;
    holo_base_msg_common_uint64_t_g_tc._data._annotations._maxValue._u.ulong_long_value = RTIXCdrUnsignedLongLong_MAX;

    holo_base_msg_common_uint64_t_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_uint64_t_get_sample_access_info();
    holo_base_msg_common_uint64_t_g_tc._data._typePlugin =
    holo_base_msg_common_uint64_t_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_uint64_t_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_uint64_t_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_uint64_t_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_uint64_t_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_uint64_t_g_sampleAccessInfo;
    }

    holo_base_msg_common_uint64_t_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_common_uint64_t_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_uint64_t_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_uint64_t);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_uint64_t_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_uint64_t_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_uint64_t_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_uint64_t_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_uint64_t_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_uint64_t_g_typePlugin = 
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
        holo_base_msg_common_uint64_t_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_uint64_t_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_uint64_t_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_uint64_t_initialize(
    holo_base_msg_common_uint64_t* sample) {
    return holo_base_msg_common_uint64_t_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_uint64_t_initialize_ex(
    holo_base_msg_common_uint64_t* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_uint64_t_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_uint64_t_initialize_w_params(
    holo_base_msg_common_uint64_t* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    (*sample) = 0ull;

    return RTI_TRUE;
}

RTIBool holo_base_msg_common_uint64_t_finalize(
    holo_base_msg_common_uint64_t* sample)
{

    holo_base_msg_common_uint64_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_uint64_t_finalize_w_return(
    holo_base_msg_common_uint64_t* sample)
{

    holo_base_msg_common_uint64_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_uint64_t_finalize_ex(
    holo_base_msg_common_uint64_t* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_uint64_t_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_uint64_t_finalize_w_params(
    holo_base_msg_common_uint64_t* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_common_uint64_t_finalize_optional_members(
    holo_base_msg_common_uint64_t* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_common_uint64_t_copy(
    holo_base_msg_common_uint64_t* dst,
    const holo_base_msg_common_uint64_t* src)
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
* Configure and implement 'holo_base_msg_common_uint64_t' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_uint64_t
#define TSeq holo_base_msg_common_uint64_tSeq

#define T_initialize holo_base_msg_common_uint64_t_initialize

#define T_finalize   holo_base_msg_common_uint64_t_finalize
#define T_copy       holo_base_msg_common_uint64_t_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_uint64_t
#define TSeq holo_base_msg_common_uint64_tSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_Pose *
holo_base_msg_common_Pose_create(void)
{
    holo_base_msg_common_Pose* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_Pose);
    if (sample != NULL) {
        if (!holo_base_msg_common_Pose_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_Pose_delete(holo_base_msg_common_Pose*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_Pose_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_Pose_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_Pose_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_common_Pose_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::common::Pose", /* Name */
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
        }}; /* Type code for  holo_base_msg_common_Pose */

    if (is_initialized) {
        return &holo_base_msg_common_Pose_g_tc;
    }

    holo_base_msg_common_Pose_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_Pose_g_tc._data._typeCode =  (RTICdrTypeCode *)holo_base_msg_geometry_Pose3f_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_common_Pose_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_Pose_get_sample_access_info();
    holo_base_msg_common_Pose_g_tc._data._typePlugin =
    holo_base_msg_common_Pose_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_Pose_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_Pose_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_Pose_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_Pose_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_Pose_g_sampleAccessInfo;
    }

    holo_base_msg_common_Pose_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_common_Pose_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_Pose_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_Pose);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_Pose_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_Pose_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_Pose_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_Pose_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_Pose_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_Pose_g_typePlugin = 
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
        holo_base_msg_common_Pose_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_Pose_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_Pose_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_Pose_initialize(
    holo_base_msg_common_Pose* sample) {
    return holo_base_msg_common_Pose_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_Pose_initialize_ex(
    holo_base_msg_common_Pose* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_Pose_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_Pose_initialize_w_params(
    holo_base_msg_common_Pose* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_geometry_Pose3f_initialize_w_params(sample,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_Pose_finalize(
    holo_base_msg_common_Pose* sample)
{

    holo_base_msg_common_Pose_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_Pose_finalize_w_return(
    holo_base_msg_common_Pose* sample)
{

    holo_base_msg_common_Pose_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_Pose_finalize_ex(
    holo_base_msg_common_Pose* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_Pose_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_Pose_finalize_w_params(
    holo_base_msg_common_Pose* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_geometry_Pose3f_finalize_w_params(sample,deallocParams);

}

void holo_base_msg_common_Pose_finalize_optional_members(
    holo_base_msg_common_Pose* sample, RTIBool deletePointers)
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

    holo_base_msg_geometry_Pose3f_finalize_optional_members(sample, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_common_Pose_copy(
    holo_base_msg_common_Pose* dst,
    const holo_base_msg_common_Pose* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_geometry_Pose3f_copy(
        dst,(const holo_base_msg_geometry_Pose3f*)src)) {
        return RTI_FALSE;
    } 

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_Pose' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Pose
#define TSeq holo_base_msg_common_PoseSeq

#define T_initialize holo_base_msg_common_Pose_initialize

#define T_finalize   holo_base_msg_common_Pose_finalize
#define T_copy       holo_base_msg_common_Pose_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Pose
#define TSeq holo_base_msg_common_PoseSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_PointXYZRGB *
holo_base_msg_common_PointXYZRGB_create(void)
{
    holo_base_msg_common_PointXYZRGB* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_PointXYZRGB);
    if (sample != NULL) {
        if (!holo_base_msg_common_PointXYZRGB_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_PointXYZRGB_delete(holo_base_msg_common_PointXYZRGB*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_PointXYZRGB_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_PointXYZRGB_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_common_PointXYZRGBTYPENAME = "holo_base_msg::common::PointXYZRGB";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_PointXYZRGB_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_common_PointXYZRGB_g_tc_members[7]=
    {

        {
            (char *)"x",/* Member name */
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
            (char *)"y",/* Member name */
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
            (char *)"z",/* Member name */
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
            (char *)"confidence",/* Member name */
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
            (char *)"r",/* Member name */
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
            (char *)"g",/* Member name */
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
            (char *)"b",/* Member name */
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
        }
    };

    static DDS_TypeCode holo_base_msg_common_PointXYZRGB_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::common::PointXYZRGB", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            7, /* Number of members */
            holo_base_msg_common_PointXYZRGB_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_common_PointXYZRGB*/

    if (is_initialized) {
        return &holo_base_msg_common_PointXYZRGB_g_tc;
    }

    holo_base_msg_common_PointXYZRGB_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_PointXYZRGB_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_float32_t_get_typecode();
    holo_base_msg_common_PointXYZRGB_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_float32_t_get_typecode();
    holo_base_msg_common_PointXYZRGB_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_float32_t_get_typecode();
    holo_base_msg_common_PointXYZRGB_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_float32_t_get_typecode();
    holo_base_msg_common_PointXYZRGB_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_uint8_t_get_typecode();
    holo_base_msg_common_PointXYZRGB_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_uint8_t_get_typecode();
    holo_base_msg_common_PointXYZRGB_g_tc_members[6]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_uint8_t_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_common_PointXYZRGB_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PointXYZRGB_g_tc_members[0]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_PointXYZRGB_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PointXYZRGB_g_tc_members[0]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_PointXYZRGB_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PointXYZRGB_g_tc_members[0]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_PointXYZRGB_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PointXYZRGB_g_tc_members[1]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_PointXYZRGB_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PointXYZRGB_g_tc_members[1]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_PointXYZRGB_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PointXYZRGB_g_tc_members[1]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_PointXYZRGB_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PointXYZRGB_g_tc_members[2]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_PointXYZRGB_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PointXYZRGB_g_tc_members[2]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_PointXYZRGB_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PointXYZRGB_g_tc_members[2]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_PointXYZRGB_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PointXYZRGB_g_tc_members[3]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_PointXYZRGB_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PointXYZRGB_g_tc_members[3]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_PointXYZRGB_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PointXYZRGB_g_tc_members[3]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_PointXYZRGB_g_tc_members[4]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PointXYZRGB_g_tc_members[4]._annotations._defaultValue._u.octet_value = 0;
    holo_base_msg_common_PointXYZRGB_g_tc_members[4]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PointXYZRGB_g_tc_members[4]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    holo_base_msg_common_PointXYZRGB_g_tc_members[4]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PointXYZRGB_g_tc_members[4]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    holo_base_msg_common_PointXYZRGB_g_tc_members[5]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PointXYZRGB_g_tc_members[5]._annotations._defaultValue._u.octet_value = 0;
    holo_base_msg_common_PointXYZRGB_g_tc_members[5]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PointXYZRGB_g_tc_members[5]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    holo_base_msg_common_PointXYZRGB_g_tc_members[5]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PointXYZRGB_g_tc_members[5]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    holo_base_msg_common_PointXYZRGB_g_tc_members[6]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PointXYZRGB_g_tc_members[6]._annotations._defaultValue._u.octet_value = 0;
    holo_base_msg_common_PointXYZRGB_g_tc_members[6]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PointXYZRGB_g_tc_members[6]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    holo_base_msg_common_PointXYZRGB_g_tc_members[6]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PointXYZRGB_g_tc_members[6]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    holo_base_msg_common_PointXYZRGB_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_PointXYZRGB_get_sample_access_info();
    holo_base_msg_common_PointXYZRGB_g_tc._data._typePlugin =
    holo_base_msg_common_PointXYZRGB_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_PointXYZRGB_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_PointXYZRGB_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_common_PointXYZRGB *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_PointXYZRGB_g_memberAccessInfos[7] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_PointXYZRGB_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_PointXYZRGB_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_common_PointXYZRGB);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_common_PointXYZRGB_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->x - (char *)sample);

    holo_base_msg_common_PointXYZRGB_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->y - (char *)sample);

    holo_base_msg_common_PointXYZRGB_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->z - (char *)sample);

    holo_base_msg_common_PointXYZRGB_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->confidence - (char *)sample);

    holo_base_msg_common_PointXYZRGB_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->r - (char *)sample);

    holo_base_msg_common_PointXYZRGB_g_memberAccessInfos[5].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->g - (char *)sample);

    holo_base_msg_common_PointXYZRGB_g_memberAccessInfos[6].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->b - (char *)sample);

    holo_base_msg_common_PointXYZRGB_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_PointXYZRGB_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_PointXYZRGB);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_PointXYZRGB_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_PointXYZRGB_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_PointXYZRGB_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_PointXYZRGB_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_PointXYZRGB_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_PointXYZRGB_g_typePlugin = 
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
        holo_base_msg_common_PointXYZRGB_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_PointXYZRGB_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_PointXYZRGB_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_PointXYZRGB_initialize(
    holo_base_msg_common_PointXYZRGB* sample) {
    return holo_base_msg_common_PointXYZRGB_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_PointXYZRGB_initialize_ex(
    holo_base_msg_common_PointXYZRGB* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_PointXYZRGB_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_PointXYZRGB_initialize_w_params(
    holo_base_msg_common_PointXYZRGB* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->x = 0.0f;

    sample->y = 0.0f;

    sample->z = 0.0f;

    sample->confidence = 0.0f;

    sample->r = 0;

    sample->g = 0;

    sample->b = 0;

    return RTI_TRUE;
}

RTIBool holo_base_msg_common_PointXYZRGB_finalize(
    holo_base_msg_common_PointXYZRGB* sample)
{

    holo_base_msg_common_PointXYZRGB_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_PointXYZRGB_finalize_w_return(
    holo_base_msg_common_PointXYZRGB* sample)
{

    holo_base_msg_common_PointXYZRGB_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_PointXYZRGB_finalize_ex(
    holo_base_msg_common_PointXYZRGB* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_PointXYZRGB_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_PointXYZRGB_finalize_w_params(
    holo_base_msg_common_PointXYZRGB* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_common_PointXYZRGB_finalize_optional_members(
    holo_base_msg_common_PointXYZRGB* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_common_PointXYZRGB_copy(
    holo_base_msg_common_PointXYZRGB* dst,
    const holo_base_msg_common_PointXYZRGB* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (&dst->x, &src->x);
    DDS_Primitive_copy (&dst->y, &src->y);
    DDS_Primitive_copy (&dst->z, &src->z);
    DDS_Primitive_copy (&dst->confidence, &src->confidence);
    DDS_Primitive_copy (&dst->r, &src->r);
    DDS_Primitive_copy (&dst->g, &src->g);
    DDS_Primitive_copy (&dst->b, &src->b);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_PointXYZRGB' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PointXYZRGB
#define TSeq holo_base_msg_common_PointXYZRGBSeq

#define T_initialize holo_base_msg_common_PointXYZRGB_initialize

#define T_finalize   holo_base_msg_common_PointXYZRGB_finalize
#define T_copy       holo_base_msg_common_PointXYZRGB_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PointXYZRGB
#define TSeq holo_base_msg_common_PointXYZRGBSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_PointXYZRGBSeqTypeDef *
holo_base_msg_common_PointXYZRGBSeqTypeDef_create(void)
{
    holo_base_msg_common_PointXYZRGBSeqTypeDef* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_PointXYZRGBSeqTypeDef);
    if (sample != NULL) {
        if (!holo_base_msg_common_PointXYZRGBSeqTypeDef_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_PointXYZRGBSeqTypeDef_delete(holo_base_msg_common_PointXYZRGBSeqTypeDef*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_PointXYZRGBSeqTypeDef_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_PointXYZRGBSeqTypeDef_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_PointXYZRGBSeqTypeDef_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_common_PointXYZRGBSeqTypeDef_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_common_PointXYZRGBSeqTypeDef_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::common::PointXYZRGBSeqTypeDef", /* Name */
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
        }}; /* Type code for  holo_base_msg_common_PointXYZRGBSeqTypeDef */

    if (is_initialized) {
        return &holo_base_msg_common_PointXYZRGBSeqTypeDef_g_tc;
    }

    holo_base_msg_common_PointXYZRGBSeqTypeDef_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_PointXYZRGBSeqTypeDef_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_common_PointXYZRGB_get_typecode();
    holo_base_msg_common_PointXYZRGBSeqTypeDef_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_common_PointXYZRGBSeqTypeDef_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_common_PointXYZRGBSeqTypeDef_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_common_PointXYZRGBSeqTypeDef_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_PointXYZRGBSeqTypeDef_get_sample_access_info();
    holo_base_msg_common_PointXYZRGBSeqTypeDef_g_tc._data._typePlugin =
    holo_base_msg_common_PointXYZRGBSeqTypeDef_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_PointXYZRGBSeqTypeDef_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_PointXYZRGBSeqTypeDef_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_PointXYZRGBSeqTypeDef_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_PointXYZRGBSeqTypeDef_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_PointXYZRGBSeqTypeDef_g_sampleAccessInfo;
    }

    holo_base_msg_common_PointXYZRGBSeqTypeDef_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_common_PointXYZRGBSeqTypeDef_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_PointXYZRGBSeqTypeDef_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_PointXYZRGBSeqTypeDef);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_PointXYZRGBSeqTypeDef_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_PointXYZRGBSeqTypeDef_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_PointXYZRGBSeqTypeDef_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_PointXYZRGBSeqTypeDef_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_PointXYZRGBSeqTypeDef_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_PointXYZRGBSeqTypeDef_g_typePlugin = 
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
        holo_base_msg_common_PointXYZRGBSeqTypeDef_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_PointXYZRGBSeqTypeDef_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_PointXYZRGBSeqTypeDef_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_PointXYZRGBSeqTypeDef_initialize(
    holo_base_msg_common_PointXYZRGBSeqTypeDef* sample) {
    return holo_base_msg_common_PointXYZRGBSeqTypeDef_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_PointXYZRGBSeqTypeDef_initialize_ex(
    holo_base_msg_common_PointXYZRGBSeqTypeDef* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_PointXYZRGBSeqTypeDef_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_PointXYZRGBSeqTypeDef_initialize_w_params(
    holo_base_msg_common_PointXYZRGBSeqTypeDef* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!holo_base_msg_common_PointXYZRGBSeq_initialize(sample )){
            return RTI_FALSE;
        };
        if (!holo_base_msg_common_PointXYZRGBSeq_set_maximum(sample, (100))) {
            return RTI_FALSE;
        }
    } else { 
        if(!holo_base_msg_common_PointXYZRGBSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_PointXYZRGBSeqTypeDef_finalize(
    holo_base_msg_common_PointXYZRGBSeqTypeDef* sample)
{

    holo_base_msg_common_PointXYZRGBSeqTypeDef_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_PointXYZRGBSeqTypeDef_finalize_w_return(
    holo_base_msg_common_PointXYZRGBSeqTypeDef* sample)
{

    holo_base_msg_common_PointXYZRGBSeqTypeDef_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_PointXYZRGBSeqTypeDef_finalize_ex(
    holo_base_msg_common_PointXYZRGBSeqTypeDef* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_PointXYZRGBSeqTypeDef_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_PointXYZRGBSeqTypeDef_finalize_w_params(
    holo_base_msg_common_PointXYZRGBSeqTypeDef* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!holo_base_msg_common_PointXYZRGBSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_common_PointXYZRGBSeqTypeDef_finalize_optional_members(
    holo_base_msg_common_PointXYZRGBSeqTypeDef* sample, RTIBool deletePointers)
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
        length = (RTI_UINT32)holo_base_msg_common_PointXYZRGBSeq_get_length(
            sample);

        for (i = 0; i < length; i++) {
            holo_base_msg_common_PointXYZRGB_finalize_optional_members(
                holo_base_msg_common_PointXYZRGBSeq_get_reference(
                    sample, (RTI_INT32)i), deallocParams->delete_pointers);
        }
    }  

}

RTIBool holo_base_msg_common_PointXYZRGBSeqTypeDef_copy(
    holo_base_msg_common_PointXYZRGBSeqTypeDef* dst,
    const holo_base_msg_common_PointXYZRGBSeqTypeDef* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_PointXYZRGBSeq_copy(dst ,
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
* Configure and implement 'holo_base_msg_common_PointXYZRGBSeqTypeDef' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PointXYZRGBSeqTypeDef
#define TSeq holo_base_msg_common_PointXYZRGBSeqTypeDefSeq

#define T_initialize holo_base_msg_common_PointXYZRGBSeqTypeDef_initialize

#define T_finalize   holo_base_msg_common_PointXYZRGBSeqTypeDef_finalize
#define T_copy       holo_base_msg_common_PointXYZRGBSeqTypeDef_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PointXYZRGBSeqTypeDef
#define TSeq holo_base_msg_common_PointXYZRGBSeqTypeDefSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_PointCloudGeneral *
holo_base_msg_common_PointCloudGeneral_create(void)
{
    holo_base_msg_common_PointCloudGeneral* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_PointCloudGeneral);
    if (sample != NULL) {
        if (!holo_base_msg_common_PointCloudGeneral_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_PointCloudGeneral_delete(holo_base_msg_common_PointCloudGeneral*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_PointCloudGeneral_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_PointCloudGeneral_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_common_PointCloudGeneralTYPENAME = "holo_base_msg::common::PointCloudGeneral";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_PointCloudGeneral_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_common_PointCloudGeneral_g_tc_members[6]=
    {

        {
            (char *)"timestamp",/* Member name */
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
            (char *)"width",/* Member name */
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
            (char *)"height",/* Member name */
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
            (char *)"is_dense",/* Member name */
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
            (char *)"pose",/* Member name */
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
            (char *)"point_list",/* Member name */
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

    static DDS_TypeCode holo_base_msg_common_PointCloudGeneral_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::common::PointCloudGeneral", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            6, /* Number of members */
            holo_base_msg_common_PointCloudGeneral_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_common_PointCloudGeneral*/

    if (is_initialized) {
        return &holo_base_msg_common_PointCloudGeneral_g_tc;
    }

    holo_base_msg_common_PointCloudGeneral_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_PointCloudGeneral_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_common_PointCloudGeneral_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_uint64_t_get_typecode();
    holo_base_msg_common_PointCloudGeneral_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_uint64_t_get_typecode();
    holo_base_msg_common_PointCloudGeneral_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_boolean;
    holo_base_msg_common_PointCloudGeneral_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Pose_get_typecode();
    holo_base_msg_common_PointCloudGeneral_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_PointXYZRGBSeqTypeDef_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_common_PointCloudGeneral_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONGLONG;
    holo_base_msg_common_PointCloudGeneral_g_tc_members[1]._annotations._defaultValue._u.ulong_long_value = 0ull;
    holo_base_msg_common_PointCloudGeneral_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONGLONG;
    holo_base_msg_common_PointCloudGeneral_g_tc_members[1]._annotations._minValue._u.ulong_long_value = RTIXCdrUnsignedLongLong_MIN;
    holo_base_msg_common_PointCloudGeneral_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONGLONG;
    holo_base_msg_common_PointCloudGeneral_g_tc_members[1]._annotations._maxValue._u.ulong_long_value = RTIXCdrUnsignedLongLong_MAX;

    holo_base_msg_common_PointCloudGeneral_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_ULONGLONG;
    holo_base_msg_common_PointCloudGeneral_g_tc_members[2]._annotations._defaultValue._u.ulong_long_value = 0ull;
    holo_base_msg_common_PointCloudGeneral_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_ULONGLONG;
    holo_base_msg_common_PointCloudGeneral_g_tc_members[2]._annotations._minValue._u.ulong_long_value = RTIXCdrUnsignedLongLong_MIN;
    holo_base_msg_common_PointCloudGeneral_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_ULONGLONG;
    holo_base_msg_common_PointCloudGeneral_g_tc_members[2]._annotations._maxValue._u.ulong_long_value = RTIXCdrUnsignedLongLong_MAX;

    holo_base_msg_common_PointCloudGeneral_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_BOOLEAN;
    holo_base_msg_common_PointCloudGeneral_g_tc_members[3]._annotations._defaultValue._u.boolean_value = 0;

    holo_base_msg_common_PointCloudGeneral_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_PointCloudGeneral_get_sample_access_info();
    holo_base_msg_common_PointCloudGeneral_g_tc._data._typePlugin =
    holo_base_msg_common_PointCloudGeneral_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_PointCloudGeneral_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_PointCloudGeneral_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_common_PointCloudGeneral *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_PointCloudGeneral_g_memberAccessInfos[6] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_PointCloudGeneral_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_PointCloudGeneral_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_common_PointCloudGeneral);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_common_PointCloudGeneral_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->timestamp - (char *)sample);

    holo_base_msg_common_PointCloudGeneral_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->width - (char *)sample);

    holo_base_msg_common_PointCloudGeneral_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->height - (char *)sample);

    holo_base_msg_common_PointCloudGeneral_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->is_dense - (char *)sample);

    holo_base_msg_common_PointCloudGeneral_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->pose - (char *)sample);

    holo_base_msg_common_PointCloudGeneral_g_memberAccessInfos[5].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->point_list - (char *)sample);

    holo_base_msg_common_PointCloudGeneral_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_PointCloudGeneral_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_PointCloudGeneral);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_PointCloudGeneral_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_PointCloudGeneral_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_PointCloudGeneral_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_PointCloudGeneral_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_PointCloudGeneral_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_PointCloudGeneral_g_typePlugin = 
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
        holo_base_msg_common_PointCloudGeneral_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_PointCloudGeneral_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_PointCloudGeneral_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_PointCloudGeneral_initialize(
    holo_base_msg_common_PointCloudGeneral* sample) {
    return holo_base_msg_common_PointCloudGeneral_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_PointCloudGeneral_initialize_ex(
    holo_base_msg_common_PointCloudGeneral* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_PointCloudGeneral_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_PointCloudGeneral_initialize_w_params(
    holo_base_msg_common_PointCloudGeneral* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_initialize_w_params(&sample->timestamp,
    allocParams)) {
        return RTI_FALSE;
    }

    sample->width = 0ull;

    sample->height = 0ull;

    sample->is_dense = 0;

    if (!holo_base_msg_geometry_Pose3f_initialize_w_params(&sample->pose,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_common_PointXYZRGBSeqTypeDef_initialize_w_params(&sample->point_list,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_PointCloudGeneral_finalize(
    holo_base_msg_common_PointCloudGeneral* sample)
{

    holo_base_msg_common_PointCloudGeneral_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_PointCloudGeneral_finalize_w_return(
    holo_base_msg_common_PointCloudGeneral* sample)
{

    holo_base_msg_common_PointCloudGeneral_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_PointCloudGeneral_finalize_ex(
    holo_base_msg_common_PointCloudGeneral* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_PointCloudGeneral_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_PointCloudGeneral_finalize_w_params(
    holo_base_msg_common_PointCloudGeneral* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->timestamp,deallocParams);

    holo_base_msg_geometry_Pose3f_finalize_w_params(&sample->pose,deallocParams);

    holo_base_msg_common_PointXYZRGBSeqTypeDef_finalize_w_params(&sample->point_list,deallocParams);

}

void holo_base_msg_common_PointCloudGeneral_finalize_optional_members(
    holo_base_msg_common_PointCloudGeneral* sample, RTIBool deletePointers)
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

    holo_base_msg_common_Timestamp_finalize_optional_members(&sample->timestamp, deallocParams->delete_pointers);
    holo_base_msg_geometry_Pose3f_finalize_optional_members(&sample->pose, deallocParams->delete_pointers);
    holo_base_msg_common_PointXYZRGBSeqTypeDef_finalize_optional_members(&sample->point_list, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_common_PointCloudGeneral_copy(
    holo_base_msg_common_PointCloudGeneral* dst,
    const holo_base_msg_common_PointCloudGeneral* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_copy(
        &dst->timestamp,(const holo_base_msg_common_Timestamp*)&src->timestamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->width, &src->width);
    DDS_Primitive_copy (&dst->height, &src->height);
    DDS_Primitive_copy (&dst->is_dense, &src->is_dense);
    if (!holo_base_msg_geometry_Pose3f_copy(
        &dst->pose,(const holo_base_msg_geometry_Pose3f*)&src->pose)) {
        return RTI_FALSE;
    } 
    if (!holo_base_msg_common_PointXYZRGBSeqTypeDef_copy(
        &dst->point_list,(const holo_base_msg_common_PointXYZRGBSeqTypeDef*)&src->point_list)) {
        return RTI_FALSE;
    } 

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_PointCloudGeneral' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PointCloudGeneral
#define TSeq holo_base_msg_common_PointCloudGeneralSeq

#define T_initialize holo_base_msg_common_PointCloudGeneral_initialize

#define T_finalize   holo_base_msg_common_PointCloudGeneral_finalize
#define T_copy       holo_base_msg_common_PointCloudGeneral_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PointCloudGeneral
#define TSeq holo_base_msg_common_PointCloudGeneralSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

