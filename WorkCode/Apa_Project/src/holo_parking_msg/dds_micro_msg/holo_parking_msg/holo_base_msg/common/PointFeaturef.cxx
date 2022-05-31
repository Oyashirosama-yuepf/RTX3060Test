/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from PointFeaturef.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "PointFeaturef.h"

#ifndef UNUSED_ARG
#define UNUSED_ARG(x) (void)(x)
#endif

#include "dds_c/dds_c_typecode.h"
/*** SOURCE_BEGIN ***/

holo_base_msg_common_DescriptorType *
holo_base_msg_common_DescriptorType_create(void)
{
    holo_base_msg_common_DescriptorType* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_DescriptorType);
    if (sample != NULL) {
        if (!holo_base_msg_common_DescriptorType_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_DescriptorType_delete(holo_base_msg_common_DescriptorType*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_DescriptorType_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_DescriptorType_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_DescriptorType_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_common_DescriptorType_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_common_DescriptorType_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::common::DescriptorType", /* Name */
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
        }}; /* Type code for  holo_base_msg_common_DescriptorType */

    if (is_initialized) {
        return &holo_base_msg_common_DescriptorType_g_tc;
    }

    holo_base_msg_common_DescriptorType_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_DescriptorType_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_DescriptorType_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_common_DescriptorType_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_common_DescriptorType_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_common_DescriptorType_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_DescriptorType_get_sample_access_info();
    holo_base_msg_common_DescriptorType_g_tc._data._typePlugin =
    holo_base_msg_common_DescriptorType_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_DescriptorType_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_DescriptorType_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_DescriptorType_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_DescriptorType_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_DescriptorType_g_sampleAccessInfo;
    }

    holo_base_msg_common_DescriptorType_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_common_DescriptorType_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_DescriptorType_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_DescriptorType);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_DescriptorType_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_DescriptorType_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_DescriptorType_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_DescriptorType_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_DescriptorType_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_DescriptorType_g_typePlugin = 
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
        holo_base_msg_common_DescriptorType_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_DescriptorType_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_DescriptorType_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_DescriptorType_initialize(
    holo_base_msg_common_DescriptorType* sample) {
    return holo_base_msg_common_DescriptorType_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_DescriptorType_initialize_ex(
    holo_base_msg_common_DescriptorType* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_DescriptorType_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_DescriptorType_initialize_w_params(
    holo_base_msg_common_DescriptorType* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!DDS_FloatSeq_initialize(sample  )){
            return RTI_FALSE;
        }
        if (!DDS_FloatSeq_set_maximum(sample , (100) )) {
            return RTI_FALSE;
        }
    } else { 
        if(!DDS_FloatSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_DescriptorType_finalize(
    holo_base_msg_common_DescriptorType* sample)
{

    holo_base_msg_common_DescriptorType_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_DescriptorType_finalize_w_return(
    holo_base_msg_common_DescriptorType* sample)
{

    holo_base_msg_common_DescriptorType_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_DescriptorType_finalize_ex(
    holo_base_msg_common_DescriptorType* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_DescriptorType_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_DescriptorType_finalize_w_params(
    holo_base_msg_common_DescriptorType* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!DDS_FloatSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_common_DescriptorType_finalize_optional_members(
    holo_base_msg_common_DescriptorType* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_common_DescriptorType_copy(
    holo_base_msg_common_DescriptorType* dst,
    const holo_base_msg_common_DescriptorType* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!DDS_FloatSeq_copy(dst ,
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
* Configure and implement 'holo_base_msg_common_DescriptorType' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_DescriptorType
#define TSeq holo_base_msg_common_DescriptorTypeSeq

#define T_initialize holo_base_msg_common_DescriptorType_initialize

#define T_finalize   holo_base_msg_common_DescriptorType_finalize
#define T_copy       holo_base_msg_common_DescriptorType_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_DescriptorType
#define TSeq holo_base_msg_common_DescriptorTypeSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_PointFeaturef *
holo_base_msg_common_PointFeaturef_create(void)
{
    holo_base_msg_common_PointFeaturef* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_PointFeaturef);
    if (sample != NULL) {
        if (!holo_base_msg_common_PointFeaturef_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_PointFeaturef_delete(holo_base_msg_common_PointFeaturef*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_PointFeaturef_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_PointFeaturef_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_common_PointFeaturefTYPENAME = "holo_base_msg::common::PointFeaturef";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_PointFeaturef_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_common_PointFeaturef_g_tc_members[4]=
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
            (char *)"descriptor",/* Member name */
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
        }
    };

    static DDS_TypeCode holo_base_msg_common_PointFeaturef_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::common::PointFeaturef", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            4, /* Number of members */
            holo_base_msg_common_PointFeaturef_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_common_PointFeaturef*/

    if (is_initialized) {
        return &holo_base_msg_common_PointFeaturef_g_tc;
    }

    holo_base_msg_common_PointFeaturef_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_PointFeaturef_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_PointFeaturef_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_PointFeaturef_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_DescriptorType_get_typecode();
    holo_base_msg_common_PointFeaturef_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_common_PointFeaturef_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PointFeaturef_g_tc_members[0]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_PointFeaturef_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PointFeaturef_g_tc_members[0]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_PointFeaturef_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PointFeaturef_g_tc_members[0]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_PointFeaturef_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PointFeaturef_g_tc_members[1]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_PointFeaturef_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PointFeaturef_g_tc_members[1]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_PointFeaturef_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PointFeaturef_g_tc_members[1]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_PointFeaturef_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PointFeaturef_g_tc_members[3]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_PointFeaturef_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PointFeaturef_g_tc_members[3]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_PointFeaturef_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PointFeaturef_g_tc_members[3]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_PointFeaturef_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_PointFeaturef_get_sample_access_info();
    holo_base_msg_common_PointFeaturef_g_tc._data._typePlugin =
    holo_base_msg_common_PointFeaturef_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_PointFeaturef_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_PointFeaturef_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_common_PointFeaturef *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_PointFeaturef_g_memberAccessInfos[4] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_PointFeaturef_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_PointFeaturef_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_common_PointFeaturef);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_common_PointFeaturef_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->x - (char *)sample);

    holo_base_msg_common_PointFeaturef_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->y - (char *)sample);

    holo_base_msg_common_PointFeaturef_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->descriptor - (char *)sample);

    holo_base_msg_common_PointFeaturef_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->confidence - (char *)sample);

    holo_base_msg_common_PointFeaturef_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_PointFeaturef_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_PointFeaturef);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_PointFeaturef_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_PointFeaturef_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_PointFeaturef_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_PointFeaturef_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_PointFeaturef_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_PointFeaturef_g_typePlugin = 
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
        holo_base_msg_common_PointFeaturef_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_PointFeaturef_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_PointFeaturef_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_PointFeaturef_initialize(
    holo_base_msg_common_PointFeaturef* sample) {
    return holo_base_msg_common_PointFeaturef_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_PointFeaturef_initialize_ex(
    holo_base_msg_common_PointFeaturef* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_PointFeaturef_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_PointFeaturef_initialize_w_params(
    holo_base_msg_common_PointFeaturef* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->x = 0.0f;

    sample->y = 0.0f;

    if (!holo_base_msg_common_DescriptorType_initialize_w_params(&sample->descriptor,
    allocParams)) {
        return RTI_FALSE;
    }

    sample->confidence = 0.0f;

    return RTI_TRUE;
}

RTIBool holo_base_msg_common_PointFeaturef_finalize(
    holo_base_msg_common_PointFeaturef* sample)
{

    holo_base_msg_common_PointFeaturef_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_PointFeaturef_finalize_w_return(
    holo_base_msg_common_PointFeaturef* sample)
{

    holo_base_msg_common_PointFeaturef_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_PointFeaturef_finalize_ex(
    holo_base_msg_common_PointFeaturef* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_PointFeaturef_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_PointFeaturef_finalize_w_params(
    holo_base_msg_common_PointFeaturef* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_DescriptorType_finalize_w_params(&sample->descriptor,deallocParams);

}

void holo_base_msg_common_PointFeaturef_finalize_optional_members(
    holo_base_msg_common_PointFeaturef* sample, RTIBool deletePointers)
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

    holo_base_msg_common_DescriptorType_finalize_optional_members(&sample->descriptor, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_common_PointFeaturef_copy(
    holo_base_msg_common_PointFeaturef* dst,
    const holo_base_msg_common_PointFeaturef* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (&dst->x, &src->x);
    DDS_Primitive_copy (&dst->y, &src->y);
    if (!holo_base_msg_common_DescriptorType_copy(
        &dst->descriptor,(const holo_base_msg_common_DescriptorType*)&src->descriptor)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->confidence, &src->confidence);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_PointFeaturef' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PointFeaturef
#define TSeq holo_base_msg_common_PointFeaturefSeq

#define T_initialize holo_base_msg_common_PointFeaturef_initialize

#define T_finalize   holo_base_msg_common_PointFeaturef_finalize
#define T_copy       holo_base_msg_common_PointFeaturef_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PointFeaturef
#define TSeq holo_base_msg_common_PointFeaturefSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

