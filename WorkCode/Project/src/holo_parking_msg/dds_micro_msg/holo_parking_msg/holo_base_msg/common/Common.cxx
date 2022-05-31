/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Common.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "Common.h"

#ifndef UNUSED_ARG
#define UNUSED_ARG(x) (void)(x)
#endif

#include "dds_c/dds_c_typecode.h"
/*** SOURCE_BEGIN ***/

holo_base_msg_common_Coordinate *
holo_base_msg_common_Coordinate_create(void)
{
    holo_base_msg_common_Coordinate* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_Coordinate);
    if (sample != NULL) {
        if (!holo_base_msg_common_Coordinate_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_Coordinate_delete(holo_base_msg_common_Coordinate*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_Coordinate_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_Coordinate_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_Coordinate_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_common_Coordinate_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::common::Coordinate", /* Name */
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
        }}; /* Type code for  holo_base_msg_common_Coordinate */

    if (is_initialized) {
        return &holo_base_msg_common_Coordinate_g_tc;
    }

    holo_base_msg_common_Coordinate_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_Coordinate_g_tc._data._typeCode =  (RTICdrTypeCode *)holo_base_msg_core_uint32_t_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_common_Coordinate_g_tc._data._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Coordinate_g_tc._data._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_Coordinate_g_tc._data._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Coordinate_g_tc._data._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_Coordinate_g_tc._data._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Coordinate_g_tc._data._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_Coordinate_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_Coordinate_get_sample_access_info();
    holo_base_msg_common_Coordinate_g_tc._data._typePlugin =
    holo_base_msg_common_Coordinate_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_Coordinate_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_Coordinate_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_Coordinate_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_Coordinate_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_Coordinate_g_sampleAccessInfo;
    }

    holo_base_msg_common_Coordinate_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_common_Coordinate_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_Coordinate_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_Coordinate);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_Coordinate_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_Coordinate_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_Coordinate_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_Coordinate_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_Coordinate_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_Coordinate_g_typePlugin = 
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
        holo_base_msg_common_Coordinate_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_Coordinate_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_Coordinate_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_Coordinate_initialize(
    holo_base_msg_common_Coordinate* sample) {
    return holo_base_msg_common_Coordinate_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_Coordinate_initialize_ex(
    holo_base_msg_common_Coordinate* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_Coordinate_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_Coordinate_initialize_w_params(
    holo_base_msg_common_Coordinate* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

RTIBool holo_base_msg_common_Coordinate_finalize(
    holo_base_msg_common_Coordinate* sample)
{

    holo_base_msg_common_Coordinate_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_Coordinate_finalize_w_return(
    holo_base_msg_common_Coordinate* sample)
{

    holo_base_msg_common_Coordinate_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_Coordinate_finalize_ex(
    holo_base_msg_common_Coordinate* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_Coordinate_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_Coordinate_finalize_w_params(
    holo_base_msg_common_Coordinate* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_common_Coordinate_finalize_optional_members(
    holo_base_msg_common_Coordinate* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_common_Coordinate_copy(
    holo_base_msg_common_Coordinate* dst,
    const holo_base_msg_common_Coordinate* src)
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
* Configure and implement 'holo_base_msg_common_Coordinate' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Coordinate
#define TSeq holo_base_msg_common_CoordinateSeq

#define T_initialize holo_base_msg_common_Coordinate_initialize

#define T_finalize   holo_base_msg_common_Coordinate_finalize
#define T_copy       holo_base_msg_common_Coordinate_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Coordinate
#define TSeq holo_base_msg_common_CoordinateSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_SensorId *
holo_base_msg_common_SensorId_create(void)
{
    holo_base_msg_common_SensorId* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_SensorId);
    if (sample != NULL) {
        if (!holo_base_msg_common_SensorId_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_SensorId_delete(holo_base_msg_common_SensorId*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_SensorId_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_SensorId_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_SensorId_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_common_SensorId_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::common::SensorId", /* Name */
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
        }}; /* Type code for  holo_base_msg_common_SensorId */

    if (is_initialized) {
        return &holo_base_msg_common_SensorId_g_tc;
    }

    holo_base_msg_common_SensorId_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_SensorId_g_tc._data._typeCode =  (RTICdrTypeCode *)holo_base_msg_core_uint32_t_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_common_SensorId_g_tc._data._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_SensorId_g_tc._data._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_SensorId_g_tc._data._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_SensorId_g_tc._data._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_SensorId_g_tc._data._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_SensorId_g_tc._data._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_SensorId_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_SensorId_get_sample_access_info();
    holo_base_msg_common_SensorId_g_tc._data._typePlugin =
    holo_base_msg_common_SensorId_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_SensorId_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_SensorId_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_SensorId_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_SensorId_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_SensorId_g_sampleAccessInfo;
    }

    holo_base_msg_common_SensorId_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_common_SensorId_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_SensorId_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_SensorId);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_SensorId_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_SensorId_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_SensorId_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_SensorId_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_SensorId_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_SensorId_g_typePlugin = 
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
        holo_base_msg_common_SensorId_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_SensorId_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_SensorId_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_SensorId_initialize(
    holo_base_msg_common_SensorId* sample) {
    return holo_base_msg_common_SensorId_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_SensorId_initialize_ex(
    holo_base_msg_common_SensorId* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_SensorId_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_SensorId_initialize_w_params(
    holo_base_msg_common_SensorId* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

RTIBool holo_base_msg_common_SensorId_finalize(
    holo_base_msg_common_SensorId* sample)
{

    holo_base_msg_common_SensorId_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_SensorId_finalize_w_return(
    holo_base_msg_common_SensorId* sample)
{

    holo_base_msg_common_SensorId_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_SensorId_finalize_ex(
    holo_base_msg_common_SensorId* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_SensorId_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_SensorId_finalize_w_params(
    holo_base_msg_common_SensorId* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_common_SensorId_finalize_optional_members(
    holo_base_msg_common_SensorId* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_common_SensorId_copy(
    holo_base_msg_common_SensorId* dst,
    const holo_base_msg_common_SensorId* src)
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
* Configure and implement 'holo_base_msg_common_SensorId' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_SensorId
#define TSeq holo_base_msg_common_SensorIdSeq

#define T_initialize holo_base_msg_common_SensorId_initialize

#define T_finalize   holo_base_msg_common_SensorId_finalize
#define T_copy       holo_base_msg_common_SensorId_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_SensorId
#define TSeq holo_base_msg_common_SensorIdSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_Classification *
holo_base_msg_common_Classification_create(void)
{
    holo_base_msg_common_Classification* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_Classification);
    if (sample != NULL) {
        if (!holo_base_msg_common_Classification_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_Classification_delete(holo_base_msg_common_Classification*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_Classification_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_Classification_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_Classification_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_common_Classification_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::common::Classification", /* Name */
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
        }}; /* Type code for  holo_base_msg_common_Classification */

    if (is_initialized) {
        return &holo_base_msg_common_Classification_g_tc;
    }

    holo_base_msg_common_Classification_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_Classification_g_tc._data._typeCode =  (RTICdrTypeCode *)holo_base_msg_core_uint32_t_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_common_Classification_g_tc._data._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Classification_g_tc._data._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_Classification_g_tc._data._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Classification_g_tc._data._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_Classification_g_tc._data._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Classification_g_tc._data._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_Classification_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_Classification_get_sample_access_info();
    holo_base_msg_common_Classification_g_tc._data._typePlugin =
    holo_base_msg_common_Classification_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_Classification_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_Classification_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_Classification_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_Classification_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_Classification_g_sampleAccessInfo;
    }

    holo_base_msg_common_Classification_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_common_Classification_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_Classification_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_Classification);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_Classification_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_Classification_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_Classification_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_Classification_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_Classification_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_Classification_g_typePlugin = 
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
        holo_base_msg_common_Classification_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_Classification_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_Classification_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_Classification_initialize(
    holo_base_msg_common_Classification* sample) {
    return holo_base_msg_common_Classification_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_Classification_initialize_ex(
    holo_base_msg_common_Classification* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_Classification_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_Classification_initialize_w_params(
    holo_base_msg_common_Classification* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

RTIBool holo_base_msg_common_Classification_finalize(
    holo_base_msg_common_Classification* sample)
{

    holo_base_msg_common_Classification_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_Classification_finalize_w_return(
    holo_base_msg_common_Classification* sample)
{

    holo_base_msg_common_Classification_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_Classification_finalize_ex(
    holo_base_msg_common_Classification* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_Classification_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_Classification_finalize_w_params(
    holo_base_msg_common_Classification* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_common_Classification_finalize_optional_members(
    holo_base_msg_common_Classification* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_common_Classification_copy(
    holo_base_msg_common_Classification* dst,
    const holo_base_msg_common_Classification* src)
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
* Configure and implement 'holo_base_msg_common_Classification' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Classification
#define TSeq holo_base_msg_common_ClassificationSeq

#define T_initialize holo_base_msg_common_Classification_initialize

#define T_finalize   holo_base_msg_common_Classification_finalize
#define T_copy       holo_base_msg_common_Classification_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Classification
#define TSeq holo_base_msg_common_ClassificationSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_Duration *
holo_base_msg_common_Duration_create(void)
{
    holo_base_msg_common_Duration* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_Duration);
    if (sample != NULL) {
        if (!holo_base_msg_common_Duration_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_Duration_delete(holo_base_msg_common_Duration*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_Duration_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_Duration_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_common_DurationTYPENAME = "holo_base_msg::common::Duration";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_Duration_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_common_Duration_g_tc_members[2]=
    {

        {
            (char *)"sec",/* Member name */
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
            (char *)"nsec",/* Member name */
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
        }
    };

    static DDS_TypeCode holo_base_msg_common_Duration_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::common::Duration", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            2, /* Number of members */
            holo_base_msg_common_Duration_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_common_Duration*/

    if (is_initialized) {
        return &holo_base_msg_common_Duration_g_tc;
    }

    holo_base_msg_common_Duration_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_Duration_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_int32_t_get_typecode();
    holo_base_msg_common_Duration_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint32_t_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_common_Duration_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    holo_base_msg_common_Duration_g_tc_members[0]._annotations._defaultValue._u.long_value = 0;
    holo_base_msg_common_Duration_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_LONG;
    holo_base_msg_common_Duration_g_tc_members[0]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    holo_base_msg_common_Duration_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    holo_base_msg_common_Duration_g_tc_members[0]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    holo_base_msg_common_Duration_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Duration_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_Duration_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Duration_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_Duration_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Duration_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_Duration_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_Duration_get_sample_access_info();
    holo_base_msg_common_Duration_g_tc._data._typePlugin =
    holo_base_msg_common_Duration_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_Duration_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_Duration_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_common_Duration *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_Duration_g_memberAccessInfos[2] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_Duration_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_Duration_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_common_Duration);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_common_Duration_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->sec - (char *)sample);

    holo_base_msg_common_Duration_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->nsec - (char *)sample);

    holo_base_msg_common_Duration_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_Duration_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_Duration);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_Duration_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_Duration_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_Duration_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_Duration_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_Duration_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_Duration_g_typePlugin = 
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
        holo_base_msg_common_Duration_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_Duration_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_Duration_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_Duration_initialize(
    holo_base_msg_common_Duration* sample) {
    return holo_base_msg_common_Duration_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_Duration_initialize_ex(
    holo_base_msg_common_Duration* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_Duration_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_Duration_initialize_w_params(
    holo_base_msg_common_Duration* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->sec = 0;

    sample->nsec = 0u;

    return RTI_TRUE;
}

RTIBool holo_base_msg_common_Duration_finalize(
    holo_base_msg_common_Duration* sample)
{

    holo_base_msg_common_Duration_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_Duration_finalize_w_return(
    holo_base_msg_common_Duration* sample)
{

    holo_base_msg_common_Duration_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_Duration_finalize_ex(
    holo_base_msg_common_Duration* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_Duration_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_Duration_finalize_w_params(
    holo_base_msg_common_Duration* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_common_Duration_finalize_optional_members(
    holo_base_msg_common_Duration* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_common_Duration_copy(
    holo_base_msg_common_Duration* dst,
    const holo_base_msg_common_Duration* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (&dst->sec, &src->sec);
    DDS_Primitive_copy (&dst->nsec, &src->nsec);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_Duration' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Duration
#define TSeq holo_base_msg_common_DurationSeq

#define T_initialize holo_base_msg_common_Duration_initialize

#define T_finalize   holo_base_msg_common_Duration_finalize
#define T_copy       holo_base_msg_common_Duration_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Duration
#define TSeq holo_base_msg_common_DurationSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_Timestamp *
holo_base_msg_common_Timestamp_create(void)
{
    holo_base_msg_common_Timestamp* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_Timestamp);
    if (sample != NULL) {
        if (!holo_base_msg_common_Timestamp_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_Timestamp_delete(holo_base_msg_common_Timestamp*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_Timestamp_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_Timestamp_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_common_TimestampTYPENAME = "holo_base_msg::common::Timestamp";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_Timestamp_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_common_Timestamp_g_tc_members[2]=
    {

        {
            (char *)"sec",/* Member name */
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
            (char *)"nsec",/* Member name */
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
        }
    };

    static DDS_TypeCode holo_base_msg_common_Timestamp_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::common::Timestamp", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            2, /* Number of members */
            holo_base_msg_common_Timestamp_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_common_Timestamp*/

    if (is_initialized) {
        return &holo_base_msg_common_Timestamp_g_tc;
    }

    holo_base_msg_common_Timestamp_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_Timestamp_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint32_t_get_typecode();
    holo_base_msg_common_Timestamp_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint32_t_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_common_Timestamp_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Timestamp_g_tc_members[0]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_Timestamp_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Timestamp_g_tc_members[0]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_Timestamp_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Timestamp_g_tc_members[0]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_Timestamp_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Timestamp_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_Timestamp_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Timestamp_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_Timestamp_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Timestamp_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_Timestamp_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_Timestamp_get_sample_access_info();
    holo_base_msg_common_Timestamp_g_tc._data._typePlugin =
    holo_base_msg_common_Timestamp_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_Timestamp_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_Timestamp_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_common_Timestamp *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_Timestamp_g_memberAccessInfos[2] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_Timestamp_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_Timestamp_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_common_Timestamp);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_common_Timestamp_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->sec - (char *)sample);

    holo_base_msg_common_Timestamp_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->nsec - (char *)sample);

    holo_base_msg_common_Timestamp_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_Timestamp_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_Timestamp);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_Timestamp_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_Timestamp_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_Timestamp_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_Timestamp_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_Timestamp_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_Timestamp_g_typePlugin = 
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
        holo_base_msg_common_Timestamp_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_Timestamp_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_Timestamp_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_Timestamp_initialize(
    holo_base_msg_common_Timestamp* sample) {
    return holo_base_msg_common_Timestamp_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_Timestamp_initialize_ex(
    holo_base_msg_common_Timestamp* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_Timestamp_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_Timestamp_initialize_w_params(
    holo_base_msg_common_Timestamp* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->sec = 0u;

    sample->nsec = 0u;

    return RTI_TRUE;
}

RTIBool holo_base_msg_common_Timestamp_finalize(
    holo_base_msg_common_Timestamp* sample)
{

    holo_base_msg_common_Timestamp_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_Timestamp_finalize_w_return(
    holo_base_msg_common_Timestamp* sample)
{

    holo_base_msg_common_Timestamp_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_Timestamp_finalize_ex(
    holo_base_msg_common_Timestamp* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_Timestamp_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_Timestamp_finalize_w_params(
    holo_base_msg_common_Timestamp* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_common_Timestamp_finalize_optional_members(
    holo_base_msg_common_Timestamp* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_common_Timestamp_copy(
    holo_base_msg_common_Timestamp* dst,
    const holo_base_msg_common_Timestamp* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (&dst->sec, &src->sec);
    DDS_Primitive_copy (&dst->nsec, &src->nsec);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_Timestamp' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Timestamp
#define TSeq holo_base_msg_common_TimestampSeq

#define T_initialize holo_base_msg_common_Timestamp_initialize

#define T_finalize   holo_base_msg_common_Timestamp_finalize
#define T_copy       holo_base_msg_common_Timestamp_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Timestamp
#define TSeq holo_base_msg_common_TimestampSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

