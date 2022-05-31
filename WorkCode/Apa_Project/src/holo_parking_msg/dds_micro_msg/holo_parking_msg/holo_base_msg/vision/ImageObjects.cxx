/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ImageObjects.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "ImageObjects.h"

#ifndef UNUSED_ARG
#define UNUSED_ARG(x) (void)(x)
#endif

#include "dds_c/dds_c_typecode.h"
/*** SOURCE_BEGIN ***/

holo_base_msg_vision_KeyPoint2d *
holo_base_msg_vision_KeyPoint2d_create(void)
{
    holo_base_msg_vision_KeyPoint2d* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_vision_KeyPoint2d);
    if (sample != NULL) {
        if (!holo_base_msg_vision_KeyPoint2d_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_vision_KeyPoint2d_delete(holo_base_msg_vision_KeyPoint2d*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_vision_KeyPoint2d_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_vision_KeyPoint2d_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_vision_KeyPoint2dTYPENAME = "holo_base_msg::vision::KeyPoint2d";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_vision_KeyPoint2d_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_vision_KeyPoint2d_g_tc_members[4]=
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
            (char *)"confidence",/* Member name */
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
            (char *)"visibility",/* Member name */
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

    static DDS_TypeCode holo_base_msg_vision_KeyPoint2d_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::vision::KeyPoint2d", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            4, /* Number of members */
            holo_base_msg_vision_KeyPoint2d_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_vision_KeyPoint2d*/

    if (is_initialized) {
        return &holo_base_msg_vision_KeyPoint2d_g_tc;
    }

    holo_base_msg_vision_KeyPoint2d_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_vision_KeyPoint2d_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();
    holo_base_msg_vision_KeyPoint2d_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();
    holo_base_msg_vision_KeyPoint2d_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_vision_KeyPoint2d_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_bool_t_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_vision_KeyPoint2d_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_vision_KeyPoint2d_g_tc_members[0]._annotations._defaultValue._u.double_value = 0.0;
    holo_base_msg_vision_KeyPoint2d_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_vision_KeyPoint2d_g_tc_members[0]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
    holo_base_msg_vision_KeyPoint2d_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_vision_KeyPoint2d_g_tc_members[0]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;

    holo_base_msg_vision_KeyPoint2d_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_vision_KeyPoint2d_g_tc_members[1]._annotations._defaultValue._u.double_value = 0.0;
    holo_base_msg_vision_KeyPoint2d_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_vision_KeyPoint2d_g_tc_members[1]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
    holo_base_msg_vision_KeyPoint2d_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_vision_KeyPoint2d_g_tc_members[1]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;

    holo_base_msg_vision_KeyPoint2d_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_vision_KeyPoint2d_g_tc_members[2]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_vision_KeyPoint2d_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_vision_KeyPoint2d_g_tc_members[2]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_vision_KeyPoint2d_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_vision_KeyPoint2d_g_tc_members[2]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_vision_KeyPoint2d_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_BOOLEAN;
    holo_base_msg_vision_KeyPoint2d_g_tc_members[3]._annotations._defaultValue._u.boolean_value = 0;

    holo_base_msg_vision_KeyPoint2d_g_tc._data._sampleAccessInfo =
    holo_base_msg_vision_KeyPoint2d_get_sample_access_info();
    holo_base_msg_vision_KeyPoint2d_g_tc._data._typePlugin =
    holo_base_msg_vision_KeyPoint2d_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_vision_KeyPoint2d_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_vision_KeyPoint2d_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_vision_KeyPoint2d *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_vision_KeyPoint2d_g_memberAccessInfos[4] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_vision_KeyPoint2d_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_KeyPoint2d_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_vision_KeyPoint2d);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_vision_KeyPoint2d_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->x - (char *)sample);

    holo_base_msg_vision_KeyPoint2d_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->y - (char *)sample);

    holo_base_msg_vision_KeyPoint2d_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->confidence - (char *)sample);

    holo_base_msg_vision_KeyPoint2d_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->visibility - (char *)sample);

    holo_base_msg_vision_KeyPoint2d_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_vision_KeyPoint2d_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_vision_KeyPoint2d);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_vision_KeyPoint2d_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_vision_KeyPoint2d_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_vision_KeyPoint2d_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_KeyPoint2d_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_vision_KeyPoint2d_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_vision_KeyPoint2d_g_typePlugin = 
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
        holo_base_msg_vision_KeyPoint2d_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_vision_KeyPoint2d_finalize_w_return,
        NULL
    };

    return &holo_base_msg_vision_KeyPoint2d_g_typePlugin;
}
#endif

RTIBool holo_base_msg_vision_KeyPoint2d_initialize(
    holo_base_msg_vision_KeyPoint2d* sample) {
    return holo_base_msg_vision_KeyPoint2d_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_vision_KeyPoint2d_initialize_ex(
    holo_base_msg_vision_KeyPoint2d* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_vision_KeyPoint2d_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_vision_KeyPoint2d_initialize_w_params(
    holo_base_msg_vision_KeyPoint2d* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->x = 0.0;

    sample->y = 0.0;

    sample->confidence = 0.0f;

    sample->visibility = 0;

    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_KeyPoint2d_finalize(
    holo_base_msg_vision_KeyPoint2d* sample)
{

    holo_base_msg_vision_KeyPoint2d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_KeyPoint2d_finalize_w_return(
    holo_base_msg_vision_KeyPoint2d* sample)
{

    holo_base_msg_vision_KeyPoint2d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_vision_KeyPoint2d_finalize_ex(
    holo_base_msg_vision_KeyPoint2d* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_vision_KeyPoint2d_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_vision_KeyPoint2d_finalize_w_params(
    holo_base_msg_vision_KeyPoint2d* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_vision_KeyPoint2d_finalize_optional_members(
    holo_base_msg_vision_KeyPoint2d* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_vision_KeyPoint2d_copy(
    holo_base_msg_vision_KeyPoint2d* dst,
    const holo_base_msg_vision_KeyPoint2d* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (&dst->x, &src->x);
    DDS_Primitive_copy (&dst->y, &src->y);
    DDS_Primitive_copy (&dst->confidence, &src->confidence);
    DDS_Primitive_copy (&dst->visibility, &src->visibility);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_vision_KeyPoint2d' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_KeyPoint2d
#define TSeq holo_base_msg_vision_KeyPoint2dSeq

#define T_initialize holo_base_msg_vision_KeyPoint2d_initialize

#define T_finalize   holo_base_msg_vision_KeyPoint2d_finalize
#define T_copy       holo_base_msg_vision_KeyPoint2d_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_KeyPoint2d
#define TSeq holo_base_msg_vision_KeyPoint2dSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_vision_KeyPoint2dSequence *
holo_base_msg_vision_KeyPoint2dSequence_create(void)
{
    holo_base_msg_vision_KeyPoint2dSequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_vision_KeyPoint2dSequence);
    if (sample != NULL) {
        if (!holo_base_msg_vision_KeyPoint2dSequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_vision_KeyPoint2dSequence_delete(holo_base_msg_vision_KeyPoint2dSequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_vision_KeyPoint2dSequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_vision_KeyPoint2dSequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_vision_KeyPoint2dSequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_vision_KeyPoint2dSequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_vision_KeyPoint2dSequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::vision::KeyPoint2dSequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_vision_KeyPoint2dSequence */

    if (is_initialized) {
        return &holo_base_msg_vision_KeyPoint2dSequence_g_tc;
    }

    holo_base_msg_vision_KeyPoint2dSequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_vision_KeyPoint2dSequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_vision_KeyPoint2d_get_typecode();
    holo_base_msg_vision_KeyPoint2dSequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_vision_KeyPoint2dSequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_vision_KeyPoint2dSequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_vision_KeyPoint2dSequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_vision_KeyPoint2dSequence_get_sample_access_info();
    holo_base_msg_vision_KeyPoint2dSequence_g_tc._data._typePlugin =
    holo_base_msg_vision_KeyPoint2dSequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_vision_KeyPoint2dSequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_vision_KeyPoint2dSequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_vision_KeyPoint2dSequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_vision_KeyPoint2dSequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_KeyPoint2dSequence_g_sampleAccessInfo;
    }

    holo_base_msg_vision_KeyPoint2dSequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_vision_KeyPoint2dSequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_vision_KeyPoint2dSequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_vision_KeyPoint2dSequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_vision_KeyPoint2dSequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_vision_KeyPoint2dSequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_vision_KeyPoint2dSequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_KeyPoint2dSequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_vision_KeyPoint2dSequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_vision_KeyPoint2dSequence_g_typePlugin = 
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
        holo_base_msg_vision_KeyPoint2dSequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_vision_KeyPoint2dSequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_vision_KeyPoint2dSequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_vision_KeyPoint2dSequence_initialize(
    holo_base_msg_vision_KeyPoint2dSequence* sample) {
    return holo_base_msg_vision_KeyPoint2dSequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_vision_KeyPoint2dSequence_initialize_ex(
    holo_base_msg_vision_KeyPoint2dSequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_vision_KeyPoint2dSequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_vision_KeyPoint2dSequence_initialize_w_params(
    holo_base_msg_vision_KeyPoint2dSequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!holo_base_msg_vision_KeyPoint2dSeq_initialize(sample )){
            return RTI_FALSE;
        };
        if (!holo_base_msg_vision_KeyPoint2dSeq_set_maximum(sample, (100))) {
            return RTI_FALSE;
        }
    } else { 
        if(!holo_base_msg_vision_KeyPoint2dSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_KeyPoint2dSequence_finalize(
    holo_base_msg_vision_KeyPoint2dSequence* sample)
{

    holo_base_msg_vision_KeyPoint2dSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_KeyPoint2dSequence_finalize_w_return(
    holo_base_msg_vision_KeyPoint2dSequence* sample)
{

    holo_base_msg_vision_KeyPoint2dSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_vision_KeyPoint2dSequence_finalize_ex(
    holo_base_msg_vision_KeyPoint2dSequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_vision_KeyPoint2dSequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_vision_KeyPoint2dSequence_finalize_w_params(
    holo_base_msg_vision_KeyPoint2dSequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!holo_base_msg_vision_KeyPoint2dSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_vision_KeyPoint2dSequence_finalize_optional_members(
    holo_base_msg_vision_KeyPoint2dSequence* sample, RTIBool deletePointers)
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
        length = (RTI_UINT32)holo_base_msg_vision_KeyPoint2dSeq_get_length(
            sample);

        for (i = 0; i < length; i++) {
            holo_base_msg_vision_KeyPoint2d_finalize_optional_members(
                holo_base_msg_vision_KeyPoint2dSeq_get_reference(
                    sample, (RTI_INT32)i), deallocParams->delete_pointers);
        }
    }  

}

RTIBool holo_base_msg_vision_KeyPoint2dSequence_copy(
    holo_base_msg_vision_KeyPoint2dSequence* dst,
    const holo_base_msg_vision_KeyPoint2dSequence* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_vision_KeyPoint2dSeq_copy(dst ,
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
* Configure and implement 'holo_base_msg_vision_KeyPoint2dSequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_KeyPoint2dSequence
#define TSeq holo_base_msg_vision_KeyPoint2dSequenceSeq

#define T_initialize holo_base_msg_vision_KeyPoint2dSequence_initialize

#define T_finalize   holo_base_msg_vision_KeyPoint2dSequence_finalize
#define T_copy       holo_base_msg_vision_KeyPoint2dSequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_KeyPoint2dSequence
#define TSeq holo_base_msg_vision_KeyPoint2dSequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_vision_KeyPoint2f *
holo_base_msg_vision_KeyPoint2f_create(void)
{
    holo_base_msg_vision_KeyPoint2f* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_vision_KeyPoint2f);
    if (sample != NULL) {
        if (!holo_base_msg_vision_KeyPoint2f_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_vision_KeyPoint2f_delete(holo_base_msg_vision_KeyPoint2f*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_vision_KeyPoint2f_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_vision_KeyPoint2f_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_vision_KeyPoint2fTYPENAME = "holo_base_msg::vision::KeyPoint2f";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_vision_KeyPoint2f_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_vision_KeyPoint2f_g_tc_members[4]=
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
            (char *)"confidence",/* Member name */
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
            (char *)"visibility",/* Member name */
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

    static DDS_TypeCode holo_base_msg_vision_KeyPoint2f_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::vision::KeyPoint2f", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            4, /* Number of members */
            holo_base_msg_vision_KeyPoint2f_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_vision_KeyPoint2f*/

    if (is_initialized) {
        return &holo_base_msg_vision_KeyPoint2f_g_tc;
    }

    holo_base_msg_vision_KeyPoint2f_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_vision_KeyPoint2f_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_vision_KeyPoint2f_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_vision_KeyPoint2f_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_vision_KeyPoint2f_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_bool_t_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_vision_KeyPoint2f_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_vision_KeyPoint2f_g_tc_members[0]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_vision_KeyPoint2f_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_vision_KeyPoint2f_g_tc_members[0]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_vision_KeyPoint2f_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_vision_KeyPoint2f_g_tc_members[0]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_vision_KeyPoint2f_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_vision_KeyPoint2f_g_tc_members[1]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_vision_KeyPoint2f_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_vision_KeyPoint2f_g_tc_members[1]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_vision_KeyPoint2f_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_vision_KeyPoint2f_g_tc_members[1]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_vision_KeyPoint2f_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_vision_KeyPoint2f_g_tc_members[2]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_vision_KeyPoint2f_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_vision_KeyPoint2f_g_tc_members[2]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_vision_KeyPoint2f_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_vision_KeyPoint2f_g_tc_members[2]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_vision_KeyPoint2f_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_BOOLEAN;
    holo_base_msg_vision_KeyPoint2f_g_tc_members[3]._annotations._defaultValue._u.boolean_value = 0;

    holo_base_msg_vision_KeyPoint2f_g_tc._data._sampleAccessInfo =
    holo_base_msg_vision_KeyPoint2f_get_sample_access_info();
    holo_base_msg_vision_KeyPoint2f_g_tc._data._typePlugin =
    holo_base_msg_vision_KeyPoint2f_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_vision_KeyPoint2f_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_vision_KeyPoint2f_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_vision_KeyPoint2f *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_vision_KeyPoint2f_g_memberAccessInfos[4] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_vision_KeyPoint2f_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_KeyPoint2f_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_vision_KeyPoint2f);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_vision_KeyPoint2f_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->x - (char *)sample);

    holo_base_msg_vision_KeyPoint2f_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->y - (char *)sample);

    holo_base_msg_vision_KeyPoint2f_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->confidence - (char *)sample);

    holo_base_msg_vision_KeyPoint2f_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->visibility - (char *)sample);

    holo_base_msg_vision_KeyPoint2f_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_vision_KeyPoint2f_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_vision_KeyPoint2f);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_vision_KeyPoint2f_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_vision_KeyPoint2f_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_vision_KeyPoint2f_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_KeyPoint2f_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_vision_KeyPoint2f_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_vision_KeyPoint2f_g_typePlugin = 
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
        holo_base_msg_vision_KeyPoint2f_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_vision_KeyPoint2f_finalize_w_return,
        NULL
    };

    return &holo_base_msg_vision_KeyPoint2f_g_typePlugin;
}
#endif

RTIBool holo_base_msg_vision_KeyPoint2f_initialize(
    holo_base_msg_vision_KeyPoint2f* sample) {
    return holo_base_msg_vision_KeyPoint2f_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_vision_KeyPoint2f_initialize_ex(
    holo_base_msg_vision_KeyPoint2f* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_vision_KeyPoint2f_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_vision_KeyPoint2f_initialize_w_params(
    holo_base_msg_vision_KeyPoint2f* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->x = 0.0f;

    sample->y = 0.0f;

    sample->confidence = 0.0f;

    sample->visibility = 0;

    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_KeyPoint2f_finalize(
    holo_base_msg_vision_KeyPoint2f* sample)
{

    holo_base_msg_vision_KeyPoint2f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_KeyPoint2f_finalize_w_return(
    holo_base_msg_vision_KeyPoint2f* sample)
{

    holo_base_msg_vision_KeyPoint2f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_vision_KeyPoint2f_finalize_ex(
    holo_base_msg_vision_KeyPoint2f* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_vision_KeyPoint2f_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_vision_KeyPoint2f_finalize_w_params(
    holo_base_msg_vision_KeyPoint2f* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_vision_KeyPoint2f_finalize_optional_members(
    holo_base_msg_vision_KeyPoint2f* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_vision_KeyPoint2f_copy(
    holo_base_msg_vision_KeyPoint2f* dst,
    const holo_base_msg_vision_KeyPoint2f* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (&dst->x, &src->x);
    DDS_Primitive_copy (&dst->y, &src->y);
    DDS_Primitive_copy (&dst->confidence, &src->confidence);
    DDS_Primitive_copy (&dst->visibility, &src->visibility);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_vision_KeyPoint2f' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_KeyPoint2f
#define TSeq holo_base_msg_vision_KeyPoint2fSeq

#define T_initialize holo_base_msg_vision_KeyPoint2f_initialize

#define T_finalize   holo_base_msg_vision_KeyPoint2f_finalize
#define T_copy       holo_base_msg_vision_KeyPoint2f_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_KeyPoint2f
#define TSeq holo_base_msg_vision_KeyPoint2fSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_vision_KeyPoint2fSequence *
holo_base_msg_vision_KeyPoint2fSequence_create(void)
{
    holo_base_msg_vision_KeyPoint2fSequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_vision_KeyPoint2fSequence);
    if (sample != NULL) {
        if (!holo_base_msg_vision_KeyPoint2fSequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_vision_KeyPoint2fSequence_delete(holo_base_msg_vision_KeyPoint2fSequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_vision_KeyPoint2fSequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_vision_KeyPoint2fSequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_vision_KeyPoint2fSequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_vision_KeyPoint2fSequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_vision_KeyPoint2fSequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::vision::KeyPoint2fSequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_vision_KeyPoint2fSequence */

    if (is_initialized) {
        return &holo_base_msg_vision_KeyPoint2fSequence_g_tc;
    }

    holo_base_msg_vision_KeyPoint2fSequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_vision_KeyPoint2fSequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_vision_KeyPoint2f_get_typecode();
    holo_base_msg_vision_KeyPoint2fSequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_vision_KeyPoint2fSequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_vision_KeyPoint2fSequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_vision_KeyPoint2fSequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_vision_KeyPoint2fSequence_get_sample_access_info();
    holo_base_msg_vision_KeyPoint2fSequence_g_tc._data._typePlugin =
    holo_base_msg_vision_KeyPoint2fSequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_vision_KeyPoint2fSequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_vision_KeyPoint2fSequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_vision_KeyPoint2fSequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_vision_KeyPoint2fSequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_KeyPoint2fSequence_g_sampleAccessInfo;
    }

    holo_base_msg_vision_KeyPoint2fSequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_vision_KeyPoint2fSequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_vision_KeyPoint2fSequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_vision_KeyPoint2fSequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_vision_KeyPoint2fSequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_vision_KeyPoint2fSequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_vision_KeyPoint2fSequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_KeyPoint2fSequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_vision_KeyPoint2fSequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_vision_KeyPoint2fSequence_g_typePlugin = 
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
        holo_base_msg_vision_KeyPoint2fSequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_vision_KeyPoint2fSequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_vision_KeyPoint2fSequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_vision_KeyPoint2fSequence_initialize(
    holo_base_msg_vision_KeyPoint2fSequence* sample) {
    return holo_base_msg_vision_KeyPoint2fSequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_vision_KeyPoint2fSequence_initialize_ex(
    holo_base_msg_vision_KeyPoint2fSequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_vision_KeyPoint2fSequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_vision_KeyPoint2fSequence_initialize_w_params(
    holo_base_msg_vision_KeyPoint2fSequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!holo_base_msg_vision_KeyPoint2fSeq_initialize(sample )){
            return RTI_FALSE;
        };
        if (!holo_base_msg_vision_KeyPoint2fSeq_set_maximum(sample, (100))) {
            return RTI_FALSE;
        }
    } else { 
        if(!holo_base_msg_vision_KeyPoint2fSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_KeyPoint2fSequence_finalize(
    holo_base_msg_vision_KeyPoint2fSequence* sample)
{

    holo_base_msg_vision_KeyPoint2fSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_KeyPoint2fSequence_finalize_w_return(
    holo_base_msg_vision_KeyPoint2fSequence* sample)
{

    holo_base_msg_vision_KeyPoint2fSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_vision_KeyPoint2fSequence_finalize_ex(
    holo_base_msg_vision_KeyPoint2fSequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_vision_KeyPoint2fSequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_vision_KeyPoint2fSequence_finalize_w_params(
    holo_base_msg_vision_KeyPoint2fSequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!holo_base_msg_vision_KeyPoint2fSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_vision_KeyPoint2fSequence_finalize_optional_members(
    holo_base_msg_vision_KeyPoint2fSequence* sample, RTIBool deletePointers)
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
        length = (RTI_UINT32)holo_base_msg_vision_KeyPoint2fSeq_get_length(
            sample);

        for (i = 0; i < length; i++) {
            holo_base_msg_vision_KeyPoint2f_finalize_optional_members(
                holo_base_msg_vision_KeyPoint2fSeq_get_reference(
                    sample, (RTI_INT32)i), deallocParams->delete_pointers);
        }
    }  

}

RTIBool holo_base_msg_vision_KeyPoint2fSequence_copy(
    holo_base_msg_vision_KeyPoint2fSequence* dst,
    const holo_base_msg_vision_KeyPoint2fSequence* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_vision_KeyPoint2fSeq_copy(dst ,
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
* Configure and implement 'holo_base_msg_vision_KeyPoint2fSequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_KeyPoint2fSequence
#define TSeq holo_base_msg_vision_KeyPoint2fSequenceSeq

#define T_initialize holo_base_msg_vision_KeyPoint2fSequence_initialize

#define T_finalize   holo_base_msg_vision_KeyPoint2fSequence_finalize
#define T_copy       holo_base_msg_vision_KeyPoint2fSequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_KeyPoint2fSequence
#define TSeq holo_base_msg_vision_KeyPoint2fSequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_vision_ObjectKeyPoint2d *
holo_base_msg_vision_ObjectKeyPoint2d_create(void)
{
    holo_base_msg_vision_ObjectKeyPoint2d* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_vision_ObjectKeyPoint2d);
    if (sample != NULL) {
        if (!holo_base_msg_vision_ObjectKeyPoint2d_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_vision_ObjectKeyPoint2d_delete(holo_base_msg_vision_ObjectKeyPoint2d*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_vision_ObjectKeyPoint2d_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_vision_ObjectKeyPoint2d_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_vision_ObjectKeyPoint2dTYPENAME = "holo_base_msg::vision::ObjectKeyPoint2d";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_vision_ObjectKeyPoint2d_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_vision_ObjectKeyPoint2d_g_tc_members[3]=
    {

        {
            (char *)"points",/* Member name */
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
            (char *)"category",/* Member name */
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
            (char *)"confidence",/* Member name */
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

    static DDS_TypeCode holo_base_msg_vision_ObjectKeyPoint2d_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::vision::ObjectKeyPoint2d", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            3, /* Number of members */
            holo_base_msg_vision_ObjectKeyPoint2d_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_vision_ObjectKeyPoint2d*/

    if (is_initialized) {
        return &holo_base_msg_vision_ObjectKeyPoint2d_g_tc;
    }

    holo_base_msg_vision_ObjectKeyPoint2d_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_vision_ObjectKeyPoint2d_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_vision_KeyPoint2dSequence_get_typecode();
    holo_base_msg_vision_ObjectKeyPoint2d_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Classification_get_typecode();
    holo_base_msg_vision_ObjectKeyPoint2d_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_vision_ObjectKeyPoint2d_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ObjectKeyPoint2d_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_vision_ObjectKeyPoint2d_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ObjectKeyPoint2d_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_vision_ObjectKeyPoint2d_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ObjectKeyPoint2d_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_vision_ObjectKeyPoint2d_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_vision_ObjectKeyPoint2d_g_tc_members[2]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_vision_ObjectKeyPoint2d_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_vision_ObjectKeyPoint2d_g_tc_members[2]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_vision_ObjectKeyPoint2d_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_vision_ObjectKeyPoint2d_g_tc_members[2]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_vision_ObjectKeyPoint2d_g_tc._data._sampleAccessInfo =
    holo_base_msg_vision_ObjectKeyPoint2d_get_sample_access_info();
    holo_base_msg_vision_ObjectKeyPoint2d_g_tc._data._typePlugin =
    holo_base_msg_vision_ObjectKeyPoint2d_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_vision_ObjectKeyPoint2d_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_vision_ObjectKeyPoint2d_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_vision_ObjectKeyPoint2d *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_vision_ObjectKeyPoint2d_g_memberAccessInfos[3] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_vision_ObjectKeyPoint2d_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ObjectKeyPoint2d_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_vision_ObjectKeyPoint2d);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_vision_ObjectKeyPoint2d_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->points - (char *)sample);

    holo_base_msg_vision_ObjectKeyPoint2d_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->category - (char *)sample);

    holo_base_msg_vision_ObjectKeyPoint2d_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->confidence - (char *)sample);

    holo_base_msg_vision_ObjectKeyPoint2d_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_vision_ObjectKeyPoint2d_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_vision_ObjectKeyPoint2d);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_vision_ObjectKeyPoint2d_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_vision_ObjectKeyPoint2d_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_vision_ObjectKeyPoint2d_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ObjectKeyPoint2d_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_vision_ObjectKeyPoint2d_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_vision_ObjectKeyPoint2d_g_typePlugin = 
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
        holo_base_msg_vision_ObjectKeyPoint2d_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_vision_ObjectKeyPoint2d_finalize_w_return,
        NULL
    };

    return &holo_base_msg_vision_ObjectKeyPoint2d_g_typePlugin;
}
#endif

RTIBool holo_base_msg_vision_ObjectKeyPoint2d_initialize(
    holo_base_msg_vision_ObjectKeyPoint2d* sample) {
    return holo_base_msg_vision_ObjectKeyPoint2d_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_vision_ObjectKeyPoint2d_initialize_ex(
    holo_base_msg_vision_ObjectKeyPoint2d* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_vision_ObjectKeyPoint2d_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_vision_ObjectKeyPoint2d_initialize_w_params(
    holo_base_msg_vision_ObjectKeyPoint2d* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_vision_KeyPoint2dSequence_initialize_w_params(&sample->points,
    allocParams)) {
        return RTI_FALSE;
    }

    sample->category = 0u;

    sample->confidence = 0.0f;

    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ObjectKeyPoint2d_finalize(
    holo_base_msg_vision_ObjectKeyPoint2d* sample)
{

    holo_base_msg_vision_ObjectKeyPoint2d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ObjectKeyPoint2d_finalize_w_return(
    holo_base_msg_vision_ObjectKeyPoint2d* sample)
{

    holo_base_msg_vision_ObjectKeyPoint2d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_vision_ObjectKeyPoint2d_finalize_ex(
    holo_base_msg_vision_ObjectKeyPoint2d* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_vision_ObjectKeyPoint2d_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_vision_ObjectKeyPoint2d_finalize_w_params(
    holo_base_msg_vision_ObjectKeyPoint2d* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_vision_KeyPoint2dSequence_finalize_w_params(&sample->points,deallocParams);

}

void holo_base_msg_vision_ObjectKeyPoint2d_finalize_optional_members(
    holo_base_msg_vision_ObjectKeyPoint2d* sample, RTIBool deletePointers)
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

    holo_base_msg_vision_KeyPoint2dSequence_finalize_optional_members(&sample->points, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_vision_ObjectKeyPoint2d_copy(
    holo_base_msg_vision_ObjectKeyPoint2d* dst,
    const holo_base_msg_vision_ObjectKeyPoint2d* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_vision_KeyPoint2dSequence_copy(
        &dst->points,(const holo_base_msg_vision_KeyPoint2dSequence*)&src->points)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->category, &src->category);
    DDS_Primitive_copy (&dst->confidence, &src->confidence);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_vision_ObjectKeyPoint2d' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectKeyPoint2d
#define TSeq holo_base_msg_vision_ObjectKeyPoint2dSeq

#define T_initialize holo_base_msg_vision_ObjectKeyPoint2d_initialize

#define T_finalize   holo_base_msg_vision_ObjectKeyPoint2d_finalize
#define T_copy       holo_base_msg_vision_ObjectKeyPoint2d_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectKeyPoint2d
#define TSeq holo_base_msg_vision_ObjectKeyPoint2dSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_vision_ObjectKeyPoint2dSequence *
holo_base_msg_vision_ObjectKeyPoint2dSequence_create(void)
{
    holo_base_msg_vision_ObjectKeyPoint2dSequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_vision_ObjectKeyPoint2dSequence);
    if (sample != NULL) {
        if (!holo_base_msg_vision_ObjectKeyPoint2dSequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_vision_ObjectKeyPoint2dSequence_delete(holo_base_msg_vision_ObjectKeyPoint2dSequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_vision_ObjectKeyPoint2dSequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_vision_ObjectKeyPoint2dSequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_vision_ObjectKeyPoint2dSequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_vision_ObjectKeyPoint2dSequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_vision_ObjectKeyPoint2dSequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::vision::ObjectKeyPoint2dSequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_vision_ObjectKeyPoint2dSequence */

    if (is_initialized) {
        return &holo_base_msg_vision_ObjectKeyPoint2dSequence_g_tc;
    }

    holo_base_msg_vision_ObjectKeyPoint2dSequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_vision_ObjectKeyPoint2dSequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_vision_ObjectKeyPoint2d_get_typecode();
    holo_base_msg_vision_ObjectKeyPoint2dSequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_vision_ObjectKeyPoint2dSequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_vision_ObjectKeyPoint2dSequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_vision_ObjectKeyPoint2dSequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_vision_ObjectKeyPoint2dSequence_get_sample_access_info();
    holo_base_msg_vision_ObjectKeyPoint2dSequence_g_tc._data._typePlugin =
    holo_base_msg_vision_ObjectKeyPoint2dSequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_vision_ObjectKeyPoint2dSequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_vision_ObjectKeyPoint2dSequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_vision_ObjectKeyPoint2dSequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_vision_ObjectKeyPoint2dSequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ObjectKeyPoint2dSequence_g_sampleAccessInfo;
    }

    holo_base_msg_vision_ObjectKeyPoint2dSequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_vision_ObjectKeyPoint2dSequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_vision_ObjectKeyPoint2dSequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_vision_ObjectKeyPoint2dSequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_vision_ObjectKeyPoint2dSequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_vision_ObjectKeyPoint2dSequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_vision_ObjectKeyPoint2dSequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ObjectKeyPoint2dSequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_vision_ObjectKeyPoint2dSequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_vision_ObjectKeyPoint2dSequence_g_typePlugin = 
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
        holo_base_msg_vision_ObjectKeyPoint2dSequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_vision_ObjectKeyPoint2dSequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_vision_ObjectKeyPoint2dSequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_vision_ObjectKeyPoint2dSequence_initialize(
    holo_base_msg_vision_ObjectKeyPoint2dSequence* sample) {
    return holo_base_msg_vision_ObjectKeyPoint2dSequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_vision_ObjectKeyPoint2dSequence_initialize_ex(
    holo_base_msg_vision_ObjectKeyPoint2dSequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_vision_ObjectKeyPoint2dSequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_vision_ObjectKeyPoint2dSequence_initialize_w_params(
    holo_base_msg_vision_ObjectKeyPoint2dSequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!holo_base_msg_vision_ObjectKeyPoint2dSeq_initialize(sample )){
            return RTI_FALSE;
        };
        if (!holo_base_msg_vision_ObjectKeyPoint2dSeq_set_maximum(sample, (100))) {
            return RTI_FALSE;
        }
    } else { 
        if(!holo_base_msg_vision_ObjectKeyPoint2dSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ObjectKeyPoint2dSequence_finalize(
    holo_base_msg_vision_ObjectKeyPoint2dSequence* sample)
{

    holo_base_msg_vision_ObjectKeyPoint2dSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ObjectKeyPoint2dSequence_finalize_w_return(
    holo_base_msg_vision_ObjectKeyPoint2dSequence* sample)
{

    holo_base_msg_vision_ObjectKeyPoint2dSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_vision_ObjectKeyPoint2dSequence_finalize_ex(
    holo_base_msg_vision_ObjectKeyPoint2dSequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_vision_ObjectKeyPoint2dSequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_vision_ObjectKeyPoint2dSequence_finalize_w_params(
    holo_base_msg_vision_ObjectKeyPoint2dSequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!holo_base_msg_vision_ObjectKeyPoint2dSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_vision_ObjectKeyPoint2dSequence_finalize_optional_members(
    holo_base_msg_vision_ObjectKeyPoint2dSequence* sample, RTIBool deletePointers)
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
        length = (RTI_UINT32)holo_base_msg_vision_ObjectKeyPoint2dSeq_get_length(
            sample);

        for (i = 0; i < length; i++) {
            holo_base_msg_vision_ObjectKeyPoint2d_finalize_optional_members(
                holo_base_msg_vision_ObjectKeyPoint2dSeq_get_reference(
                    sample, (RTI_INT32)i), deallocParams->delete_pointers);
        }
    }  

}

RTIBool holo_base_msg_vision_ObjectKeyPoint2dSequence_copy(
    holo_base_msg_vision_ObjectKeyPoint2dSequence* dst,
    const holo_base_msg_vision_ObjectKeyPoint2dSequence* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_vision_ObjectKeyPoint2dSeq_copy(dst ,
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
* Configure and implement 'holo_base_msg_vision_ObjectKeyPoint2dSequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectKeyPoint2dSequence
#define TSeq holo_base_msg_vision_ObjectKeyPoint2dSequenceSeq

#define T_initialize holo_base_msg_vision_ObjectKeyPoint2dSequence_initialize

#define T_finalize   holo_base_msg_vision_ObjectKeyPoint2dSequence_finalize
#define T_copy       holo_base_msg_vision_ObjectKeyPoint2dSequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectKeyPoint2dSequence
#define TSeq holo_base_msg_vision_ObjectKeyPoint2dSequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_vision_ObjectKeyPoint2f *
holo_base_msg_vision_ObjectKeyPoint2f_create(void)
{
    holo_base_msg_vision_ObjectKeyPoint2f* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_vision_ObjectKeyPoint2f);
    if (sample != NULL) {
        if (!holo_base_msg_vision_ObjectKeyPoint2f_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_vision_ObjectKeyPoint2f_delete(holo_base_msg_vision_ObjectKeyPoint2f*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_vision_ObjectKeyPoint2f_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_vision_ObjectKeyPoint2f_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_vision_ObjectKeyPoint2fTYPENAME = "holo_base_msg::vision::ObjectKeyPoint2f";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_vision_ObjectKeyPoint2f_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_vision_ObjectKeyPoint2f_g_tc_members[3]=
    {

        {
            (char *)"points",/* Member name */
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
            (char *)"category",/* Member name */
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
            (char *)"confidence",/* Member name */
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

    static DDS_TypeCode holo_base_msg_vision_ObjectKeyPoint2f_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::vision::ObjectKeyPoint2f", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            3, /* Number of members */
            holo_base_msg_vision_ObjectKeyPoint2f_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_vision_ObjectKeyPoint2f*/

    if (is_initialized) {
        return &holo_base_msg_vision_ObjectKeyPoint2f_g_tc;
    }

    holo_base_msg_vision_ObjectKeyPoint2f_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_vision_ObjectKeyPoint2f_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_vision_KeyPoint2fSequence_get_typecode();
    holo_base_msg_vision_ObjectKeyPoint2f_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Classification_get_typecode();
    holo_base_msg_vision_ObjectKeyPoint2f_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_vision_ObjectKeyPoint2f_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ObjectKeyPoint2f_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_vision_ObjectKeyPoint2f_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ObjectKeyPoint2f_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_vision_ObjectKeyPoint2f_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ObjectKeyPoint2f_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_vision_ObjectKeyPoint2f_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_vision_ObjectKeyPoint2f_g_tc_members[2]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_vision_ObjectKeyPoint2f_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_vision_ObjectKeyPoint2f_g_tc_members[2]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_vision_ObjectKeyPoint2f_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_vision_ObjectKeyPoint2f_g_tc_members[2]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_vision_ObjectKeyPoint2f_g_tc._data._sampleAccessInfo =
    holo_base_msg_vision_ObjectKeyPoint2f_get_sample_access_info();
    holo_base_msg_vision_ObjectKeyPoint2f_g_tc._data._typePlugin =
    holo_base_msg_vision_ObjectKeyPoint2f_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_vision_ObjectKeyPoint2f_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_vision_ObjectKeyPoint2f_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_vision_ObjectKeyPoint2f *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_vision_ObjectKeyPoint2f_g_memberAccessInfos[3] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_vision_ObjectKeyPoint2f_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ObjectKeyPoint2f_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_vision_ObjectKeyPoint2f);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_vision_ObjectKeyPoint2f_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->points - (char *)sample);

    holo_base_msg_vision_ObjectKeyPoint2f_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->category - (char *)sample);

    holo_base_msg_vision_ObjectKeyPoint2f_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->confidence - (char *)sample);

    holo_base_msg_vision_ObjectKeyPoint2f_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_vision_ObjectKeyPoint2f_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_vision_ObjectKeyPoint2f);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_vision_ObjectKeyPoint2f_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_vision_ObjectKeyPoint2f_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_vision_ObjectKeyPoint2f_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ObjectKeyPoint2f_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_vision_ObjectKeyPoint2f_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_vision_ObjectKeyPoint2f_g_typePlugin = 
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
        holo_base_msg_vision_ObjectKeyPoint2f_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_vision_ObjectKeyPoint2f_finalize_w_return,
        NULL
    };

    return &holo_base_msg_vision_ObjectKeyPoint2f_g_typePlugin;
}
#endif

RTIBool holo_base_msg_vision_ObjectKeyPoint2f_initialize(
    holo_base_msg_vision_ObjectKeyPoint2f* sample) {
    return holo_base_msg_vision_ObjectKeyPoint2f_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_vision_ObjectKeyPoint2f_initialize_ex(
    holo_base_msg_vision_ObjectKeyPoint2f* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_vision_ObjectKeyPoint2f_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_vision_ObjectKeyPoint2f_initialize_w_params(
    holo_base_msg_vision_ObjectKeyPoint2f* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_vision_KeyPoint2fSequence_initialize_w_params(&sample->points,
    allocParams)) {
        return RTI_FALSE;
    }

    sample->category = 0u;

    sample->confidence = 0.0f;

    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ObjectKeyPoint2f_finalize(
    holo_base_msg_vision_ObjectKeyPoint2f* sample)
{

    holo_base_msg_vision_ObjectKeyPoint2f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ObjectKeyPoint2f_finalize_w_return(
    holo_base_msg_vision_ObjectKeyPoint2f* sample)
{

    holo_base_msg_vision_ObjectKeyPoint2f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_vision_ObjectKeyPoint2f_finalize_ex(
    holo_base_msg_vision_ObjectKeyPoint2f* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_vision_ObjectKeyPoint2f_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_vision_ObjectKeyPoint2f_finalize_w_params(
    holo_base_msg_vision_ObjectKeyPoint2f* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_vision_KeyPoint2fSequence_finalize_w_params(&sample->points,deallocParams);

}

void holo_base_msg_vision_ObjectKeyPoint2f_finalize_optional_members(
    holo_base_msg_vision_ObjectKeyPoint2f* sample, RTIBool deletePointers)
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

    holo_base_msg_vision_KeyPoint2fSequence_finalize_optional_members(&sample->points, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_vision_ObjectKeyPoint2f_copy(
    holo_base_msg_vision_ObjectKeyPoint2f* dst,
    const holo_base_msg_vision_ObjectKeyPoint2f* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_vision_KeyPoint2fSequence_copy(
        &dst->points,(const holo_base_msg_vision_KeyPoint2fSequence*)&src->points)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->category, &src->category);
    DDS_Primitive_copy (&dst->confidence, &src->confidence);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_vision_ObjectKeyPoint2f' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectKeyPoint2f
#define TSeq holo_base_msg_vision_ObjectKeyPoint2fSeq

#define T_initialize holo_base_msg_vision_ObjectKeyPoint2f_initialize

#define T_finalize   holo_base_msg_vision_ObjectKeyPoint2f_finalize
#define T_copy       holo_base_msg_vision_ObjectKeyPoint2f_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectKeyPoint2f
#define TSeq holo_base_msg_vision_ObjectKeyPoint2fSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_vision_ObjectKeyPoint2fSequence *
holo_base_msg_vision_ObjectKeyPoint2fSequence_create(void)
{
    holo_base_msg_vision_ObjectKeyPoint2fSequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_vision_ObjectKeyPoint2fSequence);
    if (sample != NULL) {
        if (!holo_base_msg_vision_ObjectKeyPoint2fSequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_vision_ObjectKeyPoint2fSequence_delete(holo_base_msg_vision_ObjectKeyPoint2fSequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_vision_ObjectKeyPoint2fSequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_vision_ObjectKeyPoint2fSequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_vision_ObjectKeyPoint2fSequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_vision_ObjectKeyPoint2fSequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_vision_ObjectKeyPoint2fSequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::vision::ObjectKeyPoint2fSequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_vision_ObjectKeyPoint2fSequence */

    if (is_initialized) {
        return &holo_base_msg_vision_ObjectKeyPoint2fSequence_g_tc;
    }

    holo_base_msg_vision_ObjectKeyPoint2fSequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_vision_ObjectKeyPoint2fSequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_vision_ObjectKeyPoint2f_get_typecode();
    holo_base_msg_vision_ObjectKeyPoint2fSequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_vision_ObjectKeyPoint2fSequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_vision_ObjectKeyPoint2fSequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_vision_ObjectKeyPoint2fSequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_vision_ObjectKeyPoint2fSequence_get_sample_access_info();
    holo_base_msg_vision_ObjectKeyPoint2fSequence_g_tc._data._typePlugin =
    holo_base_msg_vision_ObjectKeyPoint2fSequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_vision_ObjectKeyPoint2fSequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_vision_ObjectKeyPoint2fSequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_vision_ObjectKeyPoint2fSequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_vision_ObjectKeyPoint2fSequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ObjectKeyPoint2fSequence_g_sampleAccessInfo;
    }

    holo_base_msg_vision_ObjectKeyPoint2fSequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_vision_ObjectKeyPoint2fSequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_vision_ObjectKeyPoint2fSequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_vision_ObjectKeyPoint2fSequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_vision_ObjectKeyPoint2fSequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_vision_ObjectKeyPoint2fSequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_vision_ObjectKeyPoint2fSequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ObjectKeyPoint2fSequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_vision_ObjectKeyPoint2fSequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_vision_ObjectKeyPoint2fSequence_g_typePlugin = 
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
        holo_base_msg_vision_ObjectKeyPoint2fSequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_vision_ObjectKeyPoint2fSequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_vision_ObjectKeyPoint2fSequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_vision_ObjectKeyPoint2fSequence_initialize(
    holo_base_msg_vision_ObjectKeyPoint2fSequence* sample) {
    return holo_base_msg_vision_ObjectKeyPoint2fSequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_vision_ObjectKeyPoint2fSequence_initialize_ex(
    holo_base_msg_vision_ObjectKeyPoint2fSequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_vision_ObjectKeyPoint2fSequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_vision_ObjectKeyPoint2fSequence_initialize_w_params(
    holo_base_msg_vision_ObjectKeyPoint2fSequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!holo_base_msg_vision_ObjectKeyPoint2fSeq_initialize(sample )){
            return RTI_FALSE;
        };
        if (!holo_base_msg_vision_ObjectKeyPoint2fSeq_set_maximum(sample, (100))) {
            return RTI_FALSE;
        }
    } else { 
        if(!holo_base_msg_vision_ObjectKeyPoint2fSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ObjectKeyPoint2fSequence_finalize(
    holo_base_msg_vision_ObjectKeyPoint2fSequence* sample)
{

    holo_base_msg_vision_ObjectKeyPoint2fSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ObjectKeyPoint2fSequence_finalize_w_return(
    holo_base_msg_vision_ObjectKeyPoint2fSequence* sample)
{

    holo_base_msg_vision_ObjectKeyPoint2fSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_vision_ObjectKeyPoint2fSequence_finalize_ex(
    holo_base_msg_vision_ObjectKeyPoint2fSequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_vision_ObjectKeyPoint2fSequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_vision_ObjectKeyPoint2fSequence_finalize_w_params(
    holo_base_msg_vision_ObjectKeyPoint2fSequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!holo_base_msg_vision_ObjectKeyPoint2fSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_vision_ObjectKeyPoint2fSequence_finalize_optional_members(
    holo_base_msg_vision_ObjectKeyPoint2fSequence* sample, RTIBool deletePointers)
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
        length = (RTI_UINT32)holo_base_msg_vision_ObjectKeyPoint2fSeq_get_length(
            sample);

        for (i = 0; i < length; i++) {
            holo_base_msg_vision_ObjectKeyPoint2f_finalize_optional_members(
                holo_base_msg_vision_ObjectKeyPoint2fSeq_get_reference(
                    sample, (RTI_INT32)i), deallocParams->delete_pointers);
        }
    }  

}

RTIBool holo_base_msg_vision_ObjectKeyPoint2fSequence_copy(
    holo_base_msg_vision_ObjectKeyPoint2fSequence* dst,
    const holo_base_msg_vision_ObjectKeyPoint2fSequence* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_vision_ObjectKeyPoint2fSeq_copy(dst ,
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
* Configure and implement 'holo_base_msg_vision_ObjectKeyPoint2fSequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectKeyPoint2fSequence
#define TSeq holo_base_msg_vision_ObjectKeyPoint2fSequenceSeq

#define T_initialize holo_base_msg_vision_ObjectKeyPoint2fSequence_initialize

#define T_finalize   holo_base_msg_vision_ObjectKeyPoint2fSequence_finalize
#define T_copy       holo_base_msg_vision_ObjectKeyPoint2fSequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectKeyPoint2fSequence
#define TSeq holo_base_msg_vision_ObjectKeyPoint2fSequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_vision_ObjectPoint2d *
holo_base_msg_vision_ObjectPoint2d_create(void)
{
    holo_base_msg_vision_ObjectPoint2d* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_vision_ObjectPoint2d);
    if (sample != NULL) {
        if (!holo_base_msg_vision_ObjectPoint2d_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_vision_ObjectPoint2d_delete(holo_base_msg_vision_ObjectPoint2d*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_vision_ObjectPoint2d_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_vision_ObjectPoint2d_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_vision_ObjectPoint2dTYPENAME = "holo_base_msg::vision::ObjectPoint2d";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_vision_ObjectPoint2d_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_vision_ObjectPoint2d_g_tc_members[3]=
    {

        {
            (char *)"points",/* Member name */
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
            (char *)"category",/* Member name */
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
            (char *)"confidence",/* Member name */
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

    static DDS_TypeCode holo_base_msg_vision_ObjectPoint2d_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::vision::ObjectPoint2d", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            3, /* Number of members */
            holo_base_msg_vision_ObjectPoint2d_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_vision_ObjectPoint2d*/

    if (is_initialized) {
        return &holo_base_msg_vision_ObjectPoint2d_g_tc;
    }

    holo_base_msg_vision_ObjectPoint2d_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_vision_ObjectPoint2d_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Point2dSequence_get_typecode();
    holo_base_msg_vision_ObjectPoint2d_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Classification_get_typecode();
    holo_base_msg_vision_ObjectPoint2d_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_vision_ObjectPoint2d_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ObjectPoint2d_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_vision_ObjectPoint2d_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ObjectPoint2d_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_vision_ObjectPoint2d_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ObjectPoint2d_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_vision_ObjectPoint2d_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_vision_ObjectPoint2d_g_tc_members[2]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_vision_ObjectPoint2d_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_vision_ObjectPoint2d_g_tc_members[2]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_vision_ObjectPoint2d_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_vision_ObjectPoint2d_g_tc_members[2]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_vision_ObjectPoint2d_g_tc._data._sampleAccessInfo =
    holo_base_msg_vision_ObjectPoint2d_get_sample_access_info();
    holo_base_msg_vision_ObjectPoint2d_g_tc._data._typePlugin =
    holo_base_msg_vision_ObjectPoint2d_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_vision_ObjectPoint2d_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_vision_ObjectPoint2d_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_vision_ObjectPoint2d *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_vision_ObjectPoint2d_g_memberAccessInfos[3] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_vision_ObjectPoint2d_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ObjectPoint2d_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_vision_ObjectPoint2d);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_vision_ObjectPoint2d_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->points - (char *)sample);

    holo_base_msg_vision_ObjectPoint2d_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->category - (char *)sample);

    holo_base_msg_vision_ObjectPoint2d_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->confidence - (char *)sample);

    holo_base_msg_vision_ObjectPoint2d_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_vision_ObjectPoint2d_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_vision_ObjectPoint2d);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_vision_ObjectPoint2d_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_vision_ObjectPoint2d_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_vision_ObjectPoint2d_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ObjectPoint2d_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_vision_ObjectPoint2d_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_vision_ObjectPoint2d_g_typePlugin = 
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
        holo_base_msg_vision_ObjectPoint2d_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_vision_ObjectPoint2d_finalize_w_return,
        NULL
    };

    return &holo_base_msg_vision_ObjectPoint2d_g_typePlugin;
}
#endif

RTIBool holo_base_msg_vision_ObjectPoint2d_initialize(
    holo_base_msg_vision_ObjectPoint2d* sample) {
    return holo_base_msg_vision_ObjectPoint2d_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_vision_ObjectPoint2d_initialize_ex(
    holo_base_msg_vision_ObjectPoint2d* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_vision_ObjectPoint2d_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_vision_ObjectPoint2d_initialize_w_params(
    holo_base_msg_vision_ObjectPoint2d* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_geometry_Point2dSequence_initialize_w_params(&sample->points,
    allocParams)) {
        return RTI_FALSE;
    }

    sample->category = 0u;

    sample->confidence = 0.0f;

    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ObjectPoint2d_finalize(
    holo_base_msg_vision_ObjectPoint2d* sample)
{

    holo_base_msg_vision_ObjectPoint2d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ObjectPoint2d_finalize_w_return(
    holo_base_msg_vision_ObjectPoint2d* sample)
{

    holo_base_msg_vision_ObjectPoint2d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_vision_ObjectPoint2d_finalize_ex(
    holo_base_msg_vision_ObjectPoint2d* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_vision_ObjectPoint2d_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_vision_ObjectPoint2d_finalize_w_params(
    holo_base_msg_vision_ObjectPoint2d* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_geometry_Point2dSequence_finalize_w_params(&sample->points,deallocParams);

}

void holo_base_msg_vision_ObjectPoint2d_finalize_optional_members(
    holo_base_msg_vision_ObjectPoint2d* sample, RTIBool deletePointers)
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

    holo_base_msg_geometry_Point2dSequence_finalize_optional_members(&sample->points, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_vision_ObjectPoint2d_copy(
    holo_base_msg_vision_ObjectPoint2d* dst,
    const holo_base_msg_vision_ObjectPoint2d* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_geometry_Point2dSequence_copy(
        &dst->points,(const holo_base_msg_geometry_Point2dSequence*)&src->points)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->category, &src->category);
    DDS_Primitive_copy (&dst->confidence, &src->confidence);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_vision_ObjectPoint2d' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint2d
#define TSeq holo_base_msg_vision_ObjectPoint2dSeq

#define T_initialize holo_base_msg_vision_ObjectPoint2d_initialize

#define T_finalize   holo_base_msg_vision_ObjectPoint2d_finalize
#define T_copy       holo_base_msg_vision_ObjectPoint2d_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint2d
#define TSeq holo_base_msg_vision_ObjectPoint2dSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_vision_ObjectPoint2dSequence *
holo_base_msg_vision_ObjectPoint2dSequence_create(void)
{
    holo_base_msg_vision_ObjectPoint2dSequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_vision_ObjectPoint2dSequence);
    if (sample != NULL) {
        if (!holo_base_msg_vision_ObjectPoint2dSequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_vision_ObjectPoint2dSequence_delete(holo_base_msg_vision_ObjectPoint2dSequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_vision_ObjectPoint2dSequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_vision_ObjectPoint2dSequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_vision_ObjectPoint2dSequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_vision_ObjectPoint2dSequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_vision_ObjectPoint2dSequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::vision::ObjectPoint2dSequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_vision_ObjectPoint2dSequence */

    if (is_initialized) {
        return &holo_base_msg_vision_ObjectPoint2dSequence_g_tc;
    }

    holo_base_msg_vision_ObjectPoint2dSequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_vision_ObjectPoint2dSequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_vision_ObjectPoint2d_get_typecode();
    holo_base_msg_vision_ObjectPoint2dSequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_vision_ObjectPoint2dSequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_vision_ObjectPoint2dSequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_vision_ObjectPoint2dSequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_vision_ObjectPoint2dSequence_get_sample_access_info();
    holo_base_msg_vision_ObjectPoint2dSequence_g_tc._data._typePlugin =
    holo_base_msg_vision_ObjectPoint2dSequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_vision_ObjectPoint2dSequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_vision_ObjectPoint2dSequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_vision_ObjectPoint2dSequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_vision_ObjectPoint2dSequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ObjectPoint2dSequence_g_sampleAccessInfo;
    }

    holo_base_msg_vision_ObjectPoint2dSequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_vision_ObjectPoint2dSequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_vision_ObjectPoint2dSequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_vision_ObjectPoint2dSequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_vision_ObjectPoint2dSequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_vision_ObjectPoint2dSequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_vision_ObjectPoint2dSequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ObjectPoint2dSequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_vision_ObjectPoint2dSequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_vision_ObjectPoint2dSequence_g_typePlugin = 
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
        holo_base_msg_vision_ObjectPoint2dSequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_vision_ObjectPoint2dSequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_vision_ObjectPoint2dSequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_vision_ObjectPoint2dSequence_initialize(
    holo_base_msg_vision_ObjectPoint2dSequence* sample) {
    return holo_base_msg_vision_ObjectPoint2dSequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_vision_ObjectPoint2dSequence_initialize_ex(
    holo_base_msg_vision_ObjectPoint2dSequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_vision_ObjectPoint2dSequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_vision_ObjectPoint2dSequence_initialize_w_params(
    holo_base_msg_vision_ObjectPoint2dSequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!holo_base_msg_vision_ObjectPoint2dSeq_initialize(sample )){
            return RTI_FALSE;
        };
        if (!holo_base_msg_vision_ObjectPoint2dSeq_set_maximum(sample, (100))) {
            return RTI_FALSE;
        }
    } else { 
        if(!holo_base_msg_vision_ObjectPoint2dSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ObjectPoint2dSequence_finalize(
    holo_base_msg_vision_ObjectPoint2dSequence* sample)
{

    holo_base_msg_vision_ObjectPoint2dSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ObjectPoint2dSequence_finalize_w_return(
    holo_base_msg_vision_ObjectPoint2dSequence* sample)
{

    holo_base_msg_vision_ObjectPoint2dSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_vision_ObjectPoint2dSequence_finalize_ex(
    holo_base_msg_vision_ObjectPoint2dSequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_vision_ObjectPoint2dSequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_vision_ObjectPoint2dSequence_finalize_w_params(
    holo_base_msg_vision_ObjectPoint2dSequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!holo_base_msg_vision_ObjectPoint2dSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_vision_ObjectPoint2dSequence_finalize_optional_members(
    holo_base_msg_vision_ObjectPoint2dSequence* sample, RTIBool deletePointers)
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
        length = (RTI_UINT32)holo_base_msg_vision_ObjectPoint2dSeq_get_length(
            sample);

        for (i = 0; i < length; i++) {
            holo_base_msg_vision_ObjectPoint2d_finalize_optional_members(
                holo_base_msg_vision_ObjectPoint2dSeq_get_reference(
                    sample, (RTI_INT32)i), deallocParams->delete_pointers);
        }
    }  

}

RTIBool holo_base_msg_vision_ObjectPoint2dSequence_copy(
    holo_base_msg_vision_ObjectPoint2dSequence* dst,
    const holo_base_msg_vision_ObjectPoint2dSequence* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_vision_ObjectPoint2dSeq_copy(dst ,
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
* Configure and implement 'holo_base_msg_vision_ObjectPoint2dSequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint2dSequence
#define TSeq holo_base_msg_vision_ObjectPoint2dSequenceSeq

#define T_initialize holo_base_msg_vision_ObjectPoint2dSequence_initialize

#define T_finalize   holo_base_msg_vision_ObjectPoint2dSequence_finalize
#define T_copy       holo_base_msg_vision_ObjectPoint2dSequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint2dSequence
#define TSeq holo_base_msg_vision_ObjectPoint2dSequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_vision_ObjectPoint2f *
holo_base_msg_vision_ObjectPoint2f_create(void)
{
    holo_base_msg_vision_ObjectPoint2f* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_vision_ObjectPoint2f);
    if (sample != NULL) {
        if (!holo_base_msg_vision_ObjectPoint2f_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_vision_ObjectPoint2f_delete(holo_base_msg_vision_ObjectPoint2f*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_vision_ObjectPoint2f_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_vision_ObjectPoint2f_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_vision_ObjectPoint2fTYPENAME = "holo_base_msg::vision::ObjectPoint2f";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_vision_ObjectPoint2f_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_vision_ObjectPoint2f_g_tc_members[3]=
    {

        {
            (char *)"points",/* Member name */
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
            (char *)"category",/* Member name */
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
            (char *)"confidence",/* Member name */
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

    static DDS_TypeCode holo_base_msg_vision_ObjectPoint2f_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::vision::ObjectPoint2f", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            3, /* Number of members */
            holo_base_msg_vision_ObjectPoint2f_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_vision_ObjectPoint2f*/

    if (is_initialized) {
        return &holo_base_msg_vision_ObjectPoint2f_g_tc;
    }

    holo_base_msg_vision_ObjectPoint2f_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_vision_ObjectPoint2f_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Point2fSequence_get_typecode();
    holo_base_msg_vision_ObjectPoint2f_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Classification_get_typecode();
    holo_base_msg_vision_ObjectPoint2f_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_vision_ObjectPoint2f_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ObjectPoint2f_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_vision_ObjectPoint2f_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ObjectPoint2f_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_vision_ObjectPoint2f_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ObjectPoint2f_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_vision_ObjectPoint2f_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_vision_ObjectPoint2f_g_tc_members[2]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_vision_ObjectPoint2f_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_vision_ObjectPoint2f_g_tc_members[2]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_vision_ObjectPoint2f_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_vision_ObjectPoint2f_g_tc_members[2]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_vision_ObjectPoint2f_g_tc._data._sampleAccessInfo =
    holo_base_msg_vision_ObjectPoint2f_get_sample_access_info();
    holo_base_msg_vision_ObjectPoint2f_g_tc._data._typePlugin =
    holo_base_msg_vision_ObjectPoint2f_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_vision_ObjectPoint2f_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_vision_ObjectPoint2f_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_vision_ObjectPoint2f *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_vision_ObjectPoint2f_g_memberAccessInfos[3] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_vision_ObjectPoint2f_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ObjectPoint2f_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_vision_ObjectPoint2f);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_vision_ObjectPoint2f_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->points - (char *)sample);

    holo_base_msg_vision_ObjectPoint2f_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->category - (char *)sample);

    holo_base_msg_vision_ObjectPoint2f_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->confidence - (char *)sample);

    holo_base_msg_vision_ObjectPoint2f_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_vision_ObjectPoint2f_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_vision_ObjectPoint2f);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_vision_ObjectPoint2f_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_vision_ObjectPoint2f_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_vision_ObjectPoint2f_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ObjectPoint2f_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_vision_ObjectPoint2f_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_vision_ObjectPoint2f_g_typePlugin = 
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
        holo_base_msg_vision_ObjectPoint2f_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_vision_ObjectPoint2f_finalize_w_return,
        NULL
    };

    return &holo_base_msg_vision_ObjectPoint2f_g_typePlugin;
}
#endif

RTIBool holo_base_msg_vision_ObjectPoint2f_initialize(
    holo_base_msg_vision_ObjectPoint2f* sample) {
    return holo_base_msg_vision_ObjectPoint2f_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_vision_ObjectPoint2f_initialize_ex(
    holo_base_msg_vision_ObjectPoint2f* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_vision_ObjectPoint2f_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_vision_ObjectPoint2f_initialize_w_params(
    holo_base_msg_vision_ObjectPoint2f* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_geometry_Point2fSequence_initialize_w_params(&sample->points,
    allocParams)) {
        return RTI_FALSE;
    }

    sample->category = 0u;

    sample->confidence = 0.0f;

    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ObjectPoint2f_finalize(
    holo_base_msg_vision_ObjectPoint2f* sample)
{

    holo_base_msg_vision_ObjectPoint2f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ObjectPoint2f_finalize_w_return(
    holo_base_msg_vision_ObjectPoint2f* sample)
{

    holo_base_msg_vision_ObjectPoint2f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_vision_ObjectPoint2f_finalize_ex(
    holo_base_msg_vision_ObjectPoint2f* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_vision_ObjectPoint2f_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_vision_ObjectPoint2f_finalize_w_params(
    holo_base_msg_vision_ObjectPoint2f* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_geometry_Point2fSequence_finalize_w_params(&sample->points,deallocParams);

}

void holo_base_msg_vision_ObjectPoint2f_finalize_optional_members(
    holo_base_msg_vision_ObjectPoint2f* sample, RTIBool deletePointers)
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

    holo_base_msg_geometry_Point2fSequence_finalize_optional_members(&sample->points, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_vision_ObjectPoint2f_copy(
    holo_base_msg_vision_ObjectPoint2f* dst,
    const holo_base_msg_vision_ObjectPoint2f* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_geometry_Point2fSequence_copy(
        &dst->points,(const holo_base_msg_geometry_Point2fSequence*)&src->points)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->category, &src->category);
    DDS_Primitive_copy (&dst->confidence, &src->confidence);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_vision_ObjectPoint2f' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint2f
#define TSeq holo_base_msg_vision_ObjectPoint2fSeq

#define T_initialize holo_base_msg_vision_ObjectPoint2f_initialize

#define T_finalize   holo_base_msg_vision_ObjectPoint2f_finalize
#define T_copy       holo_base_msg_vision_ObjectPoint2f_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint2f
#define TSeq holo_base_msg_vision_ObjectPoint2fSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_vision_ObjectPoint2fSequence *
holo_base_msg_vision_ObjectPoint2fSequence_create(void)
{
    holo_base_msg_vision_ObjectPoint2fSequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_vision_ObjectPoint2fSequence);
    if (sample != NULL) {
        if (!holo_base_msg_vision_ObjectPoint2fSequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_vision_ObjectPoint2fSequence_delete(holo_base_msg_vision_ObjectPoint2fSequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_vision_ObjectPoint2fSequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_vision_ObjectPoint2fSequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_vision_ObjectPoint2fSequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_vision_ObjectPoint2fSequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_vision_ObjectPoint2fSequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::vision::ObjectPoint2fSequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_vision_ObjectPoint2fSequence */

    if (is_initialized) {
        return &holo_base_msg_vision_ObjectPoint2fSequence_g_tc;
    }

    holo_base_msg_vision_ObjectPoint2fSequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_vision_ObjectPoint2fSequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_vision_ObjectPoint2f_get_typecode();
    holo_base_msg_vision_ObjectPoint2fSequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_vision_ObjectPoint2fSequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_vision_ObjectPoint2fSequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_vision_ObjectPoint2fSequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_vision_ObjectPoint2fSequence_get_sample_access_info();
    holo_base_msg_vision_ObjectPoint2fSequence_g_tc._data._typePlugin =
    holo_base_msg_vision_ObjectPoint2fSequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_vision_ObjectPoint2fSequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_vision_ObjectPoint2fSequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_vision_ObjectPoint2fSequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_vision_ObjectPoint2fSequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ObjectPoint2fSequence_g_sampleAccessInfo;
    }

    holo_base_msg_vision_ObjectPoint2fSequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_vision_ObjectPoint2fSequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_vision_ObjectPoint2fSequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_vision_ObjectPoint2fSequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_vision_ObjectPoint2fSequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_vision_ObjectPoint2fSequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_vision_ObjectPoint2fSequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ObjectPoint2fSequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_vision_ObjectPoint2fSequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_vision_ObjectPoint2fSequence_g_typePlugin = 
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
        holo_base_msg_vision_ObjectPoint2fSequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_vision_ObjectPoint2fSequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_vision_ObjectPoint2fSequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_vision_ObjectPoint2fSequence_initialize(
    holo_base_msg_vision_ObjectPoint2fSequence* sample) {
    return holo_base_msg_vision_ObjectPoint2fSequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_vision_ObjectPoint2fSequence_initialize_ex(
    holo_base_msg_vision_ObjectPoint2fSequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_vision_ObjectPoint2fSequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_vision_ObjectPoint2fSequence_initialize_w_params(
    holo_base_msg_vision_ObjectPoint2fSequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!holo_base_msg_vision_ObjectPoint2fSeq_initialize(sample )){
            return RTI_FALSE;
        };
        if (!holo_base_msg_vision_ObjectPoint2fSeq_set_maximum(sample, (100))) {
            return RTI_FALSE;
        }
    } else { 
        if(!holo_base_msg_vision_ObjectPoint2fSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ObjectPoint2fSequence_finalize(
    holo_base_msg_vision_ObjectPoint2fSequence* sample)
{

    holo_base_msg_vision_ObjectPoint2fSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ObjectPoint2fSequence_finalize_w_return(
    holo_base_msg_vision_ObjectPoint2fSequence* sample)
{

    holo_base_msg_vision_ObjectPoint2fSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_vision_ObjectPoint2fSequence_finalize_ex(
    holo_base_msg_vision_ObjectPoint2fSequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_vision_ObjectPoint2fSequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_vision_ObjectPoint2fSequence_finalize_w_params(
    holo_base_msg_vision_ObjectPoint2fSequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!holo_base_msg_vision_ObjectPoint2fSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_vision_ObjectPoint2fSequence_finalize_optional_members(
    holo_base_msg_vision_ObjectPoint2fSequence* sample, RTIBool deletePointers)
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
        length = (RTI_UINT32)holo_base_msg_vision_ObjectPoint2fSeq_get_length(
            sample);

        for (i = 0; i < length; i++) {
            holo_base_msg_vision_ObjectPoint2f_finalize_optional_members(
                holo_base_msg_vision_ObjectPoint2fSeq_get_reference(
                    sample, (RTI_INT32)i), deallocParams->delete_pointers);
        }
    }  

}

RTIBool holo_base_msg_vision_ObjectPoint2fSequence_copy(
    holo_base_msg_vision_ObjectPoint2fSequence* dst,
    const holo_base_msg_vision_ObjectPoint2fSequence* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_vision_ObjectPoint2fSeq_copy(dst ,
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
* Configure and implement 'holo_base_msg_vision_ObjectPoint2fSequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint2fSequence
#define TSeq holo_base_msg_vision_ObjectPoint2fSequenceSeq

#define T_initialize holo_base_msg_vision_ObjectPoint2fSequence_initialize

#define T_finalize   holo_base_msg_vision_ObjectPoint2fSequence_finalize
#define T_copy       holo_base_msg_vision_ObjectPoint2fSequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint2fSequence
#define TSeq holo_base_msg_vision_ObjectPoint2fSequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_vision_ObjectPoint3d *
holo_base_msg_vision_ObjectPoint3d_create(void)
{
    holo_base_msg_vision_ObjectPoint3d* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_vision_ObjectPoint3d);
    if (sample != NULL) {
        if (!holo_base_msg_vision_ObjectPoint3d_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_vision_ObjectPoint3d_delete(holo_base_msg_vision_ObjectPoint3d*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_vision_ObjectPoint3d_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_vision_ObjectPoint3d_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_vision_ObjectPoint3dTYPENAME = "holo_base_msg::vision::ObjectPoint3d";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_vision_ObjectPoint3d_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_vision_ObjectPoint3d_g_tc_members[3]=
    {

        {
            (char *)"points",/* Member name */
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
            (char *)"category",/* Member name */
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
            (char *)"confidence",/* Member name */
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

    static DDS_TypeCode holo_base_msg_vision_ObjectPoint3d_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::vision::ObjectPoint3d", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            3, /* Number of members */
            holo_base_msg_vision_ObjectPoint3d_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_vision_ObjectPoint3d*/

    if (is_initialized) {
        return &holo_base_msg_vision_ObjectPoint3d_g_tc;
    }

    holo_base_msg_vision_ObjectPoint3d_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_vision_ObjectPoint3d_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Point3dSequence_get_typecode();
    holo_base_msg_vision_ObjectPoint3d_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Classification_get_typecode();
    holo_base_msg_vision_ObjectPoint3d_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_vision_ObjectPoint3d_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ObjectPoint3d_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_vision_ObjectPoint3d_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ObjectPoint3d_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_vision_ObjectPoint3d_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ObjectPoint3d_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_vision_ObjectPoint3d_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_vision_ObjectPoint3d_g_tc_members[2]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_vision_ObjectPoint3d_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_vision_ObjectPoint3d_g_tc_members[2]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_vision_ObjectPoint3d_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_vision_ObjectPoint3d_g_tc_members[2]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_vision_ObjectPoint3d_g_tc._data._sampleAccessInfo =
    holo_base_msg_vision_ObjectPoint3d_get_sample_access_info();
    holo_base_msg_vision_ObjectPoint3d_g_tc._data._typePlugin =
    holo_base_msg_vision_ObjectPoint3d_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_vision_ObjectPoint3d_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_vision_ObjectPoint3d_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_vision_ObjectPoint3d *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_vision_ObjectPoint3d_g_memberAccessInfos[3] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_vision_ObjectPoint3d_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ObjectPoint3d_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_vision_ObjectPoint3d);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_vision_ObjectPoint3d_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->points - (char *)sample);

    holo_base_msg_vision_ObjectPoint3d_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->category - (char *)sample);

    holo_base_msg_vision_ObjectPoint3d_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->confidence - (char *)sample);

    holo_base_msg_vision_ObjectPoint3d_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_vision_ObjectPoint3d_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_vision_ObjectPoint3d);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_vision_ObjectPoint3d_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_vision_ObjectPoint3d_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_vision_ObjectPoint3d_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ObjectPoint3d_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_vision_ObjectPoint3d_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_vision_ObjectPoint3d_g_typePlugin = 
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
        holo_base_msg_vision_ObjectPoint3d_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_vision_ObjectPoint3d_finalize_w_return,
        NULL
    };

    return &holo_base_msg_vision_ObjectPoint3d_g_typePlugin;
}
#endif

RTIBool holo_base_msg_vision_ObjectPoint3d_initialize(
    holo_base_msg_vision_ObjectPoint3d* sample) {
    return holo_base_msg_vision_ObjectPoint3d_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_vision_ObjectPoint3d_initialize_ex(
    holo_base_msg_vision_ObjectPoint3d* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_vision_ObjectPoint3d_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_vision_ObjectPoint3d_initialize_w_params(
    holo_base_msg_vision_ObjectPoint3d* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_geometry_Point3dSequence_initialize_w_params(&sample->points,
    allocParams)) {
        return RTI_FALSE;
    }

    sample->category = 0u;

    sample->confidence = 0.0f;

    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ObjectPoint3d_finalize(
    holo_base_msg_vision_ObjectPoint3d* sample)
{

    holo_base_msg_vision_ObjectPoint3d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ObjectPoint3d_finalize_w_return(
    holo_base_msg_vision_ObjectPoint3d* sample)
{

    holo_base_msg_vision_ObjectPoint3d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_vision_ObjectPoint3d_finalize_ex(
    holo_base_msg_vision_ObjectPoint3d* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_vision_ObjectPoint3d_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_vision_ObjectPoint3d_finalize_w_params(
    holo_base_msg_vision_ObjectPoint3d* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_geometry_Point3dSequence_finalize_w_params(&sample->points,deallocParams);

}

void holo_base_msg_vision_ObjectPoint3d_finalize_optional_members(
    holo_base_msg_vision_ObjectPoint3d* sample, RTIBool deletePointers)
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

    holo_base_msg_geometry_Point3dSequence_finalize_optional_members(&sample->points, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_vision_ObjectPoint3d_copy(
    holo_base_msg_vision_ObjectPoint3d* dst,
    const holo_base_msg_vision_ObjectPoint3d* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_geometry_Point3dSequence_copy(
        &dst->points,(const holo_base_msg_geometry_Point3dSequence*)&src->points)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->category, &src->category);
    DDS_Primitive_copy (&dst->confidence, &src->confidence);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_vision_ObjectPoint3d' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint3d
#define TSeq holo_base_msg_vision_ObjectPoint3dSeq

#define T_initialize holo_base_msg_vision_ObjectPoint3d_initialize

#define T_finalize   holo_base_msg_vision_ObjectPoint3d_finalize
#define T_copy       holo_base_msg_vision_ObjectPoint3d_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint3d
#define TSeq holo_base_msg_vision_ObjectPoint3dSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_vision_ObjectPoint3dSequence *
holo_base_msg_vision_ObjectPoint3dSequence_create(void)
{
    holo_base_msg_vision_ObjectPoint3dSequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_vision_ObjectPoint3dSequence);
    if (sample != NULL) {
        if (!holo_base_msg_vision_ObjectPoint3dSequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_vision_ObjectPoint3dSequence_delete(holo_base_msg_vision_ObjectPoint3dSequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_vision_ObjectPoint3dSequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_vision_ObjectPoint3dSequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_vision_ObjectPoint3dSequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_vision_ObjectPoint3dSequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_vision_ObjectPoint3dSequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::vision::ObjectPoint3dSequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_vision_ObjectPoint3dSequence */

    if (is_initialized) {
        return &holo_base_msg_vision_ObjectPoint3dSequence_g_tc;
    }

    holo_base_msg_vision_ObjectPoint3dSequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_vision_ObjectPoint3dSequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_vision_ObjectPoint3d_get_typecode();
    holo_base_msg_vision_ObjectPoint3dSequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_vision_ObjectPoint3dSequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_vision_ObjectPoint3dSequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_vision_ObjectPoint3dSequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_vision_ObjectPoint3dSequence_get_sample_access_info();
    holo_base_msg_vision_ObjectPoint3dSequence_g_tc._data._typePlugin =
    holo_base_msg_vision_ObjectPoint3dSequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_vision_ObjectPoint3dSequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_vision_ObjectPoint3dSequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_vision_ObjectPoint3dSequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_vision_ObjectPoint3dSequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ObjectPoint3dSequence_g_sampleAccessInfo;
    }

    holo_base_msg_vision_ObjectPoint3dSequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_vision_ObjectPoint3dSequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_vision_ObjectPoint3dSequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_vision_ObjectPoint3dSequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_vision_ObjectPoint3dSequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_vision_ObjectPoint3dSequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_vision_ObjectPoint3dSequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ObjectPoint3dSequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_vision_ObjectPoint3dSequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_vision_ObjectPoint3dSequence_g_typePlugin = 
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
        holo_base_msg_vision_ObjectPoint3dSequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_vision_ObjectPoint3dSequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_vision_ObjectPoint3dSequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_vision_ObjectPoint3dSequence_initialize(
    holo_base_msg_vision_ObjectPoint3dSequence* sample) {
    return holo_base_msg_vision_ObjectPoint3dSequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_vision_ObjectPoint3dSequence_initialize_ex(
    holo_base_msg_vision_ObjectPoint3dSequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_vision_ObjectPoint3dSequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_vision_ObjectPoint3dSequence_initialize_w_params(
    holo_base_msg_vision_ObjectPoint3dSequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!holo_base_msg_vision_ObjectPoint3dSeq_initialize(sample )){
            return RTI_FALSE;
        };
        if (!holo_base_msg_vision_ObjectPoint3dSeq_set_maximum(sample, (100))) {
            return RTI_FALSE;
        }
    } else { 
        if(!holo_base_msg_vision_ObjectPoint3dSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ObjectPoint3dSequence_finalize(
    holo_base_msg_vision_ObjectPoint3dSequence* sample)
{

    holo_base_msg_vision_ObjectPoint3dSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ObjectPoint3dSequence_finalize_w_return(
    holo_base_msg_vision_ObjectPoint3dSequence* sample)
{

    holo_base_msg_vision_ObjectPoint3dSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_vision_ObjectPoint3dSequence_finalize_ex(
    holo_base_msg_vision_ObjectPoint3dSequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_vision_ObjectPoint3dSequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_vision_ObjectPoint3dSequence_finalize_w_params(
    holo_base_msg_vision_ObjectPoint3dSequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!holo_base_msg_vision_ObjectPoint3dSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_vision_ObjectPoint3dSequence_finalize_optional_members(
    holo_base_msg_vision_ObjectPoint3dSequence* sample, RTIBool deletePointers)
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
        length = (RTI_UINT32)holo_base_msg_vision_ObjectPoint3dSeq_get_length(
            sample);

        for (i = 0; i < length; i++) {
            holo_base_msg_vision_ObjectPoint3d_finalize_optional_members(
                holo_base_msg_vision_ObjectPoint3dSeq_get_reference(
                    sample, (RTI_INT32)i), deallocParams->delete_pointers);
        }
    }  

}

RTIBool holo_base_msg_vision_ObjectPoint3dSequence_copy(
    holo_base_msg_vision_ObjectPoint3dSequence* dst,
    const holo_base_msg_vision_ObjectPoint3dSequence* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_vision_ObjectPoint3dSeq_copy(dst ,
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
* Configure and implement 'holo_base_msg_vision_ObjectPoint3dSequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint3dSequence
#define TSeq holo_base_msg_vision_ObjectPoint3dSequenceSeq

#define T_initialize holo_base_msg_vision_ObjectPoint3dSequence_initialize

#define T_finalize   holo_base_msg_vision_ObjectPoint3dSequence_finalize
#define T_copy       holo_base_msg_vision_ObjectPoint3dSequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint3dSequence
#define TSeq holo_base_msg_vision_ObjectPoint3dSequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_vision_ObjectPoint3f *
holo_base_msg_vision_ObjectPoint3f_create(void)
{
    holo_base_msg_vision_ObjectPoint3f* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_vision_ObjectPoint3f);
    if (sample != NULL) {
        if (!holo_base_msg_vision_ObjectPoint3f_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_vision_ObjectPoint3f_delete(holo_base_msg_vision_ObjectPoint3f*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_vision_ObjectPoint3f_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_vision_ObjectPoint3f_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_vision_ObjectPoint3fTYPENAME = "holo_base_msg::vision::ObjectPoint3f";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_vision_ObjectPoint3f_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_vision_ObjectPoint3f_g_tc_members[3]=
    {

        {
            (char *)"points",/* Member name */
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
            (char *)"category",/* Member name */
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
            (char *)"confidence",/* Member name */
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

    static DDS_TypeCode holo_base_msg_vision_ObjectPoint3f_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::vision::ObjectPoint3f", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            3, /* Number of members */
            holo_base_msg_vision_ObjectPoint3f_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_vision_ObjectPoint3f*/

    if (is_initialized) {
        return &holo_base_msg_vision_ObjectPoint3f_g_tc;
    }

    holo_base_msg_vision_ObjectPoint3f_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_vision_ObjectPoint3f_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Point3fSequence_get_typecode();
    holo_base_msg_vision_ObjectPoint3f_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Classification_get_typecode();
    holo_base_msg_vision_ObjectPoint3f_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_vision_ObjectPoint3f_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ObjectPoint3f_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_vision_ObjectPoint3f_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ObjectPoint3f_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_vision_ObjectPoint3f_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ObjectPoint3f_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_vision_ObjectPoint3f_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_vision_ObjectPoint3f_g_tc_members[2]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_vision_ObjectPoint3f_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_vision_ObjectPoint3f_g_tc_members[2]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_vision_ObjectPoint3f_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_vision_ObjectPoint3f_g_tc_members[2]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_vision_ObjectPoint3f_g_tc._data._sampleAccessInfo =
    holo_base_msg_vision_ObjectPoint3f_get_sample_access_info();
    holo_base_msg_vision_ObjectPoint3f_g_tc._data._typePlugin =
    holo_base_msg_vision_ObjectPoint3f_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_vision_ObjectPoint3f_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_vision_ObjectPoint3f_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_vision_ObjectPoint3f *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_vision_ObjectPoint3f_g_memberAccessInfos[3] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_vision_ObjectPoint3f_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ObjectPoint3f_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_vision_ObjectPoint3f);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_vision_ObjectPoint3f_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->points - (char *)sample);

    holo_base_msg_vision_ObjectPoint3f_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->category - (char *)sample);

    holo_base_msg_vision_ObjectPoint3f_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->confidence - (char *)sample);

    holo_base_msg_vision_ObjectPoint3f_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_vision_ObjectPoint3f_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_vision_ObjectPoint3f);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_vision_ObjectPoint3f_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_vision_ObjectPoint3f_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_vision_ObjectPoint3f_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ObjectPoint3f_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_vision_ObjectPoint3f_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_vision_ObjectPoint3f_g_typePlugin = 
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
        holo_base_msg_vision_ObjectPoint3f_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_vision_ObjectPoint3f_finalize_w_return,
        NULL
    };

    return &holo_base_msg_vision_ObjectPoint3f_g_typePlugin;
}
#endif

RTIBool holo_base_msg_vision_ObjectPoint3f_initialize(
    holo_base_msg_vision_ObjectPoint3f* sample) {
    return holo_base_msg_vision_ObjectPoint3f_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_vision_ObjectPoint3f_initialize_ex(
    holo_base_msg_vision_ObjectPoint3f* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_vision_ObjectPoint3f_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_vision_ObjectPoint3f_initialize_w_params(
    holo_base_msg_vision_ObjectPoint3f* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_geometry_Point3fSequence_initialize_w_params(&sample->points,
    allocParams)) {
        return RTI_FALSE;
    }

    sample->category = 0u;

    sample->confidence = 0.0f;

    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ObjectPoint3f_finalize(
    holo_base_msg_vision_ObjectPoint3f* sample)
{

    holo_base_msg_vision_ObjectPoint3f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ObjectPoint3f_finalize_w_return(
    holo_base_msg_vision_ObjectPoint3f* sample)
{

    holo_base_msg_vision_ObjectPoint3f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_vision_ObjectPoint3f_finalize_ex(
    holo_base_msg_vision_ObjectPoint3f* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_vision_ObjectPoint3f_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_vision_ObjectPoint3f_finalize_w_params(
    holo_base_msg_vision_ObjectPoint3f* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_geometry_Point3fSequence_finalize_w_params(&sample->points,deallocParams);

}

void holo_base_msg_vision_ObjectPoint3f_finalize_optional_members(
    holo_base_msg_vision_ObjectPoint3f* sample, RTIBool deletePointers)
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

    holo_base_msg_geometry_Point3fSequence_finalize_optional_members(&sample->points, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_vision_ObjectPoint3f_copy(
    holo_base_msg_vision_ObjectPoint3f* dst,
    const holo_base_msg_vision_ObjectPoint3f* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_geometry_Point3fSequence_copy(
        &dst->points,(const holo_base_msg_geometry_Point3fSequence*)&src->points)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->category, &src->category);
    DDS_Primitive_copy (&dst->confidence, &src->confidence);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_vision_ObjectPoint3f' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint3f
#define TSeq holo_base_msg_vision_ObjectPoint3fSeq

#define T_initialize holo_base_msg_vision_ObjectPoint3f_initialize

#define T_finalize   holo_base_msg_vision_ObjectPoint3f_finalize
#define T_copy       holo_base_msg_vision_ObjectPoint3f_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint3f
#define TSeq holo_base_msg_vision_ObjectPoint3fSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_vision_ObjectPoint3fSequence *
holo_base_msg_vision_ObjectPoint3fSequence_create(void)
{
    holo_base_msg_vision_ObjectPoint3fSequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_vision_ObjectPoint3fSequence);
    if (sample != NULL) {
        if (!holo_base_msg_vision_ObjectPoint3fSequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_vision_ObjectPoint3fSequence_delete(holo_base_msg_vision_ObjectPoint3fSequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_vision_ObjectPoint3fSequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_vision_ObjectPoint3fSequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_vision_ObjectPoint3fSequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_vision_ObjectPoint3fSequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_vision_ObjectPoint3fSequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::vision::ObjectPoint3fSequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_vision_ObjectPoint3fSequence */

    if (is_initialized) {
        return &holo_base_msg_vision_ObjectPoint3fSequence_g_tc;
    }

    holo_base_msg_vision_ObjectPoint3fSequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_vision_ObjectPoint3fSequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_vision_ObjectPoint3f_get_typecode();
    holo_base_msg_vision_ObjectPoint3fSequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_vision_ObjectPoint3fSequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_vision_ObjectPoint3fSequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_vision_ObjectPoint3fSequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_vision_ObjectPoint3fSequence_get_sample_access_info();
    holo_base_msg_vision_ObjectPoint3fSequence_g_tc._data._typePlugin =
    holo_base_msg_vision_ObjectPoint3fSequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_vision_ObjectPoint3fSequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_vision_ObjectPoint3fSequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_vision_ObjectPoint3fSequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_vision_ObjectPoint3fSequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ObjectPoint3fSequence_g_sampleAccessInfo;
    }

    holo_base_msg_vision_ObjectPoint3fSequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_vision_ObjectPoint3fSequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_vision_ObjectPoint3fSequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_vision_ObjectPoint3fSequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_vision_ObjectPoint3fSequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_vision_ObjectPoint3fSequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_vision_ObjectPoint3fSequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ObjectPoint3fSequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_vision_ObjectPoint3fSequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_vision_ObjectPoint3fSequence_g_typePlugin = 
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
        holo_base_msg_vision_ObjectPoint3fSequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_vision_ObjectPoint3fSequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_vision_ObjectPoint3fSequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_vision_ObjectPoint3fSequence_initialize(
    holo_base_msg_vision_ObjectPoint3fSequence* sample) {
    return holo_base_msg_vision_ObjectPoint3fSequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_vision_ObjectPoint3fSequence_initialize_ex(
    holo_base_msg_vision_ObjectPoint3fSequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_vision_ObjectPoint3fSequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_vision_ObjectPoint3fSequence_initialize_w_params(
    holo_base_msg_vision_ObjectPoint3fSequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!holo_base_msg_vision_ObjectPoint3fSeq_initialize(sample )){
            return RTI_FALSE;
        };
        if (!holo_base_msg_vision_ObjectPoint3fSeq_set_maximum(sample, (100))) {
            return RTI_FALSE;
        }
    } else { 
        if(!holo_base_msg_vision_ObjectPoint3fSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ObjectPoint3fSequence_finalize(
    holo_base_msg_vision_ObjectPoint3fSequence* sample)
{

    holo_base_msg_vision_ObjectPoint3fSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ObjectPoint3fSequence_finalize_w_return(
    holo_base_msg_vision_ObjectPoint3fSequence* sample)
{

    holo_base_msg_vision_ObjectPoint3fSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_vision_ObjectPoint3fSequence_finalize_ex(
    holo_base_msg_vision_ObjectPoint3fSequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_vision_ObjectPoint3fSequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_vision_ObjectPoint3fSequence_finalize_w_params(
    holo_base_msg_vision_ObjectPoint3fSequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!holo_base_msg_vision_ObjectPoint3fSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_vision_ObjectPoint3fSequence_finalize_optional_members(
    holo_base_msg_vision_ObjectPoint3fSequence* sample, RTIBool deletePointers)
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
        length = (RTI_UINT32)holo_base_msg_vision_ObjectPoint3fSeq_get_length(
            sample);

        for (i = 0; i < length; i++) {
            holo_base_msg_vision_ObjectPoint3f_finalize_optional_members(
                holo_base_msg_vision_ObjectPoint3fSeq_get_reference(
                    sample, (RTI_INT32)i), deallocParams->delete_pointers);
        }
    }  

}

RTIBool holo_base_msg_vision_ObjectPoint3fSequence_copy(
    holo_base_msg_vision_ObjectPoint3fSequence* dst,
    const holo_base_msg_vision_ObjectPoint3fSequence* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_vision_ObjectPoint3fSeq_copy(dst ,
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
* Configure and implement 'holo_base_msg_vision_ObjectPoint3fSequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint3fSequence
#define TSeq holo_base_msg_vision_ObjectPoint3fSequenceSeq

#define T_initialize holo_base_msg_vision_ObjectPoint3fSequence_initialize

#define T_finalize   holo_base_msg_vision_ObjectPoint3fSequence_finalize
#define T_copy       holo_base_msg_vision_ObjectPoint3fSequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint3fSequence
#define TSeq holo_base_msg_vision_ObjectPoint3fSequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_vision_ImageObjectsKeyPoint2d *
holo_base_msg_vision_ImageObjectsKeyPoint2d_create(void)
{
    holo_base_msg_vision_ImageObjectsKeyPoint2d* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_vision_ImageObjectsKeyPoint2d);
    if (sample != NULL) {
        if (!holo_base_msg_vision_ImageObjectsKeyPoint2d_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_vision_ImageObjectsKeyPoint2d_delete(holo_base_msg_vision_ImageObjectsKeyPoint2d*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_vision_ImageObjectsKeyPoint2d_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_vision_ImageObjectsKeyPoint2d_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_vision_ImageObjectsKeyPoint2dTYPENAME = "holo_base_msg::vision::ImageObjectsKeyPoint2d";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_vision_ImageObjectsKeyPoint2d_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_vision_ImageObjectsKeyPoint2d_g_tc_members[3]=
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
            (char *)"sensor_id",/* Member name */
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
            (char *)"objects",/* Member name */
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

    static DDS_TypeCode holo_base_msg_vision_ImageObjectsKeyPoint2d_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::vision::ImageObjectsKeyPoint2d", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            3, /* Number of members */
            holo_base_msg_vision_ImageObjectsKeyPoint2d_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_vision_ImageObjectsKeyPoint2d*/

    if (is_initialized) {
        return &holo_base_msg_vision_ImageObjectsKeyPoint2d_g_tc;
    }

    holo_base_msg_vision_ImageObjectsKeyPoint2d_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_vision_ImageObjectsKeyPoint2d_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_vision_ImageObjectsKeyPoint2d_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_SensorId_get_typecode();
    holo_base_msg_vision_ImageObjectsKeyPoint2d_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_vision_ObjectKeyPoint2dSequence_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_vision_ImageObjectsKeyPoint2d_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ImageObjectsKeyPoint2d_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_vision_ImageObjectsKeyPoint2d_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ImageObjectsKeyPoint2d_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_vision_ImageObjectsKeyPoint2d_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ImageObjectsKeyPoint2d_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_vision_ImageObjectsKeyPoint2d_g_tc._data._sampleAccessInfo =
    holo_base_msg_vision_ImageObjectsKeyPoint2d_get_sample_access_info();
    holo_base_msg_vision_ImageObjectsKeyPoint2d_g_tc._data._typePlugin =
    holo_base_msg_vision_ImageObjectsKeyPoint2d_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_vision_ImageObjectsKeyPoint2d_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_vision_ImageObjectsKeyPoint2d_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_vision_ImageObjectsKeyPoint2d *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_vision_ImageObjectsKeyPoint2d_g_memberAccessInfos[3] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_vision_ImageObjectsKeyPoint2d_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ImageObjectsKeyPoint2d_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_vision_ImageObjectsKeyPoint2d);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_vision_ImageObjectsKeyPoint2d_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stamp - (char *)sample);

    holo_base_msg_vision_ImageObjectsKeyPoint2d_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->sensor_id - (char *)sample);

    holo_base_msg_vision_ImageObjectsKeyPoint2d_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->objects - (char *)sample);

    holo_base_msg_vision_ImageObjectsKeyPoint2d_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_vision_ImageObjectsKeyPoint2d_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_vision_ImageObjectsKeyPoint2d);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_vision_ImageObjectsKeyPoint2d_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_vision_ImageObjectsKeyPoint2d_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_vision_ImageObjectsKeyPoint2d_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ImageObjectsKeyPoint2d_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_vision_ImageObjectsKeyPoint2d_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_vision_ImageObjectsKeyPoint2d_g_typePlugin = 
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
        holo_base_msg_vision_ImageObjectsKeyPoint2d_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_vision_ImageObjectsKeyPoint2d_finalize_w_return,
        NULL
    };

    return &holo_base_msg_vision_ImageObjectsKeyPoint2d_g_typePlugin;
}
#endif

RTIBool holo_base_msg_vision_ImageObjectsKeyPoint2d_initialize(
    holo_base_msg_vision_ImageObjectsKeyPoint2d* sample) {
    return holo_base_msg_vision_ImageObjectsKeyPoint2d_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_vision_ImageObjectsKeyPoint2d_initialize_ex(
    holo_base_msg_vision_ImageObjectsKeyPoint2d* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_vision_ImageObjectsKeyPoint2d_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_vision_ImageObjectsKeyPoint2d_initialize_w_params(
    holo_base_msg_vision_ImageObjectsKeyPoint2d* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

    sample->sensor_id = 0u;

    if (!holo_base_msg_vision_ObjectKeyPoint2dSequence_initialize_w_params(&sample->objects,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ImageObjectsKeyPoint2d_finalize(
    holo_base_msg_vision_ImageObjectsKeyPoint2d* sample)
{

    holo_base_msg_vision_ImageObjectsKeyPoint2d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ImageObjectsKeyPoint2d_finalize_w_return(
    holo_base_msg_vision_ImageObjectsKeyPoint2d* sample)
{

    holo_base_msg_vision_ImageObjectsKeyPoint2d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_vision_ImageObjectsKeyPoint2d_finalize_ex(
    holo_base_msg_vision_ImageObjectsKeyPoint2d* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_vision_ImageObjectsKeyPoint2d_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_vision_ImageObjectsKeyPoint2d_finalize_w_params(
    holo_base_msg_vision_ImageObjectsKeyPoint2d* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->stamp,deallocParams);

    holo_base_msg_vision_ObjectKeyPoint2dSequence_finalize_w_params(&sample->objects,deallocParams);

}

void holo_base_msg_vision_ImageObjectsKeyPoint2d_finalize_optional_members(
    holo_base_msg_vision_ImageObjectsKeyPoint2d* sample, RTIBool deletePointers)
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
    holo_base_msg_vision_ObjectKeyPoint2dSequence_finalize_optional_members(&sample->objects, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_vision_ImageObjectsKeyPoint2d_copy(
    holo_base_msg_vision_ImageObjectsKeyPoint2d* dst,
    const holo_base_msg_vision_ImageObjectsKeyPoint2d* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_copy(
        &dst->stamp,(const holo_base_msg_common_Timestamp*)&src->stamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->sensor_id, &src->sensor_id);
    if (!holo_base_msg_vision_ObjectKeyPoint2dSequence_copy(
        &dst->objects,(const holo_base_msg_vision_ObjectKeyPoint2dSequence*)&src->objects)) {
        return RTI_FALSE;
    } 

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_vision_ImageObjectsKeyPoint2d' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ImageObjectsKeyPoint2d
#define TSeq holo_base_msg_vision_ImageObjectsKeyPoint2dSeq

#define T_initialize holo_base_msg_vision_ImageObjectsKeyPoint2d_initialize

#define T_finalize   holo_base_msg_vision_ImageObjectsKeyPoint2d_finalize
#define T_copy       holo_base_msg_vision_ImageObjectsKeyPoint2d_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ImageObjectsKeyPoint2d
#define TSeq holo_base_msg_vision_ImageObjectsKeyPoint2dSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_vision_ImageObjectsKeyPoint2f *
holo_base_msg_vision_ImageObjectsKeyPoint2f_create(void)
{
    holo_base_msg_vision_ImageObjectsKeyPoint2f* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_vision_ImageObjectsKeyPoint2f);
    if (sample != NULL) {
        if (!holo_base_msg_vision_ImageObjectsKeyPoint2f_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_vision_ImageObjectsKeyPoint2f_delete(holo_base_msg_vision_ImageObjectsKeyPoint2f*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_vision_ImageObjectsKeyPoint2f_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_vision_ImageObjectsKeyPoint2f_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_vision_ImageObjectsKeyPoint2fTYPENAME = "holo_base_msg::vision::ImageObjectsKeyPoint2f";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_vision_ImageObjectsKeyPoint2f_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_vision_ImageObjectsKeyPoint2f_g_tc_members[3]=
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
            (char *)"sensor_id",/* Member name */
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
            (char *)"objects",/* Member name */
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

    static DDS_TypeCode holo_base_msg_vision_ImageObjectsKeyPoint2f_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::vision::ImageObjectsKeyPoint2f", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            3, /* Number of members */
            holo_base_msg_vision_ImageObjectsKeyPoint2f_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_vision_ImageObjectsKeyPoint2f*/

    if (is_initialized) {
        return &holo_base_msg_vision_ImageObjectsKeyPoint2f_g_tc;
    }

    holo_base_msg_vision_ImageObjectsKeyPoint2f_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_vision_ImageObjectsKeyPoint2f_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_vision_ImageObjectsKeyPoint2f_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_SensorId_get_typecode();
    holo_base_msg_vision_ImageObjectsKeyPoint2f_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_vision_ObjectKeyPoint2fSequence_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_vision_ImageObjectsKeyPoint2f_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ImageObjectsKeyPoint2f_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_vision_ImageObjectsKeyPoint2f_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ImageObjectsKeyPoint2f_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_vision_ImageObjectsKeyPoint2f_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ImageObjectsKeyPoint2f_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_vision_ImageObjectsKeyPoint2f_g_tc._data._sampleAccessInfo =
    holo_base_msg_vision_ImageObjectsKeyPoint2f_get_sample_access_info();
    holo_base_msg_vision_ImageObjectsKeyPoint2f_g_tc._data._typePlugin =
    holo_base_msg_vision_ImageObjectsKeyPoint2f_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_vision_ImageObjectsKeyPoint2f_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_vision_ImageObjectsKeyPoint2f_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_vision_ImageObjectsKeyPoint2f *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_vision_ImageObjectsKeyPoint2f_g_memberAccessInfos[3] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_vision_ImageObjectsKeyPoint2f_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ImageObjectsKeyPoint2f_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_vision_ImageObjectsKeyPoint2f);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_vision_ImageObjectsKeyPoint2f_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stamp - (char *)sample);

    holo_base_msg_vision_ImageObjectsKeyPoint2f_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->sensor_id - (char *)sample);

    holo_base_msg_vision_ImageObjectsKeyPoint2f_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->objects - (char *)sample);

    holo_base_msg_vision_ImageObjectsKeyPoint2f_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_vision_ImageObjectsKeyPoint2f_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_vision_ImageObjectsKeyPoint2f);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_vision_ImageObjectsKeyPoint2f_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_vision_ImageObjectsKeyPoint2f_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_vision_ImageObjectsKeyPoint2f_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ImageObjectsKeyPoint2f_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_vision_ImageObjectsKeyPoint2f_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_vision_ImageObjectsKeyPoint2f_g_typePlugin = 
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
        holo_base_msg_vision_ImageObjectsKeyPoint2f_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_vision_ImageObjectsKeyPoint2f_finalize_w_return,
        NULL
    };

    return &holo_base_msg_vision_ImageObjectsKeyPoint2f_g_typePlugin;
}
#endif

RTIBool holo_base_msg_vision_ImageObjectsKeyPoint2f_initialize(
    holo_base_msg_vision_ImageObjectsKeyPoint2f* sample) {
    return holo_base_msg_vision_ImageObjectsKeyPoint2f_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_vision_ImageObjectsKeyPoint2f_initialize_ex(
    holo_base_msg_vision_ImageObjectsKeyPoint2f* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_vision_ImageObjectsKeyPoint2f_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_vision_ImageObjectsKeyPoint2f_initialize_w_params(
    holo_base_msg_vision_ImageObjectsKeyPoint2f* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

    sample->sensor_id = 0u;

    if (!holo_base_msg_vision_ObjectKeyPoint2fSequence_initialize_w_params(&sample->objects,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ImageObjectsKeyPoint2f_finalize(
    holo_base_msg_vision_ImageObjectsKeyPoint2f* sample)
{

    holo_base_msg_vision_ImageObjectsKeyPoint2f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ImageObjectsKeyPoint2f_finalize_w_return(
    holo_base_msg_vision_ImageObjectsKeyPoint2f* sample)
{

    holo_base_msg_vision_ImageObjectsKeyPoint2f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_vision_ImageObjectsKeyPoint2f_finalize_ex(
    holo_base_msg_vision_ImageObjectsKeyPoint2f* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_vision_ImageObjectsKeyPoint2f_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_vision_ImageObjectsKeyPoint2f_finalize_w_params(
    holo_base_msg_vision_ImageObjectsKeyPoint2f* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->stamp,deallocParams);

    holo_base_msg_vision_ObjectKeyPoint2fSequence_finalize_w_params(&sample->objects,deallocParams);

}

void holo_base_msg_vision_ImageObjectsKeyPoint2f_finalize_optional_members(
    holo_base_msg_vision_ImageObjectsKeyPoint2f* sample, RTIBool deletePointers)
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
    holo_base_msg_vision_ObjectKeyPoint2fSequence_finalize_optional_members(&sample->objects, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_vision_ImageObjectsKeyPoint2f_copy(
    holo_base_msg_vision_ImageObjectsKeyPoint2f* dst,
    const holo_base_msg_vision_ImageObjectsKeyPoint2f* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_copy(
        &dst->stamp,(const holo_base_msg_common_Timestamp*)&src->stamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->sensor_id, &src->sensor_id);
    if (!holo_base_msg_vision_ObjectKeyPoint2fSequence_copy(
        &dst->objects,(const holo_base_msg_vision_ObjectKeyPoint2fSequence*)&src->objects)) {
        return RTI_FALSE;
    } 

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_vision_ImageObjectsKeyPoint2f' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ImageObjectsKeyPoint2f
#define TSeq holo_base_msg_vision_ImageObjectsKeyPoint2fSeq

#define T_initialize holo_base_msg_vision_ImageObjectsKeyPoint2f_initialize

#define T_finalize   holo_base_msg_vision_ImageObjectsKeyPoint2f_finalize
#define T_copy       holo_base_msg_vision_ImageObjectsKeyPoint2f_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ImageObjectsKeyPoint2f
#define TSeq holo_base_msg_vision_ImageObjectsKeyPoint2fSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_vision_ImageObjectsPoint2d *
holo_base_msg_vision_ImageObjectsPoint2d_create(void)
{
    holo_base_msg_vision_ImageObjectsPoint2d* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_vision_ImageObjectsPoint2d);
    if (sample != NULL) {
        if (!holo_base_msg_vision_ImageObjectsPoint2d_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_vision_ImageObjectsPoint2d_delete(holo_base_msg_vision_ImageObjectsPoint2d*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_vision_ImageObjectsPoint2d_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_vision_ImageObjectsPoint2d_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_vision_ImageObjectsPoint2dTYPENAME = "holo_base_msg::vision::ImageObjectsPoint2d";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_vision_ImageObjectsPoint2d_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_vision_ImageObjectsPoint2d_g_tc_members[3]=
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
            (char *)"sensor_id",/* Member name */
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
            (char *)"objects",/* Member name */
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

    static DDS_TypeCode holo_base_msg_vision_ImageObjectsPoint2d_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::vision::ImageObjectsPoint2d", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            3, /* Number of members */
            holo_base_msg_vision_ImageObjectsPoint2d_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_vision_ImageObjectsPoint2d*/

    if (is_initialized) {
        return &holo_base_msg_vision_ImageObjectsPoint2d_g_tc;
    }

    holo_base_msg_vision_ImageObjectsPoint2d_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_vision_ImageObjectsPoint2d_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_vision_ImageObjectsPoint2d_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_SensorId_get_typecode();
    holo_base_msg_vision_ImageObjectsPoint2d_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_vision_ObjectPoint2dSequence_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_vision_ImageObjectsPoint2d_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ImageObjectsPoint2d_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_vision_ImageObjectsPoint2d_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ImageObjectsPoint2d_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_vision_ImageObjectsPoint2d_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ImageObjectsPoint2d_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_vision_ImageObjectsPoint2d_g_tc._data._sampleAccessInfo =
    holo_base_msg_vision_ImageObjectsPoint2d_get_sample_access_info();
    holo_base_msg_vision_ImageObjectsPoint2d_g_tc._data._typePlugin =
    holo_base_msg_vision_ImageObjectsPoint2d_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_vision_ImageObjectsPoint2d_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_vision_ImageObjectsPoint2d_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_vision_ImageObjectsPoint2d *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_vision_ImageObjectsPoint2d_g_memberAccessInfos[3] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_vision_ImageObjectsPoint2d_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ImageObjectsPoint2d_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_vision_ImageObjectsPoint2d);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_vision_ImageObjectsPoint2d_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stamp - (char *)sample);

    holo_base_msg_vision_ImageObjectsPoint2d_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->sensor_id - (char *)sample);

    holo_base_msg_vision_ImageObjectsPoint2d_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->objects - (char *)sample);

    holo_base_msg_vision_ImageObjectsPoint2d_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_vision_ImageObjectsPoint2d_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_vision_ImageObjectsPoint2d);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_vision_ImageObjectsPoint2d_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_vision_ImageObjectsPoint2d_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_vision_ImageObjectsPoint2d_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ImageObjectsPoint2d_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_vision_ImageObjectsPoint2d_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_vision_ImageObjectsPoint2d_g_typePlugin = 
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
        holo_base_msg_vision_ImageObjectsPoint2d_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_vision_ImageObjectsPoint2d_finalize_w_return,
        NULL
    };

    return &holo_base_msg_vision_ImageObjectsPoint2d_g_typePlugin;
}
#endif

RTIBool holo_base_msg_vision_ImageObjectsPoint2d_initialize(
    holo_base_msg_vision_ImageObjectsPoint2d* sample) {
    return holo_base_msg_vision_ImageObjectsPoint2d_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_vision_ImageObjectsPoint2d_initialize_ex(
    holo_base_msg_vision_ImageObjectsPoint2d* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_vision_ImageObjectsPoint2d_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_vision_ImageObjectsPoint2d_initialize_w_params(
    holo_base_msg_vision_ImageObjectsPoint2d* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

    sample->sensor_id = 0u;

    if (!holo_base_msg_vision_ObjectPoint2dSequence_initialize_w_params(&sample->objects,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ImageObjectsPoint2d_finalize(
    holo_base_msg_vision_ImageObjectsPoint2d* sample)
{

    holo_base_msg_vision_ImageObjectsPoint2d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ImageObjectsPoint2d_finalize_w_return(
    holo_base_msg_vision_ImageObjectsPoint2d* sample)
{

    holo_base_msg_vision_ImageObjectsPoint2d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_vision_ImageObjectsPoint2d_finalize_ex(
    holo_base_msg_vision_ImageObjectsPoint2d* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_vision_ImageObjectsPoint2d_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_vision_ImageObjectsPoint2d_finalize_w_params(
    holo_base_msg_vision_ImageObjectsPoint2d* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->stamp,deallocParams);

    holo_base_msg_vision_ObjectPoint2dSequence_finalize_w_params(&sample->objects,deallocParams);

}

void holo_base_msg_vision_ImageObjectsPoint2d_finalize_optional_members(
    holo_base_msg_vision_ImageObjectsPoint2d* sample, RTIBool deletePointers)
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
    holo_base_msg_vision_ObjectPoint2dSequence_finalize_optional_members(&sample->objects, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_vision_ImageObjectsPoint2d_copy(
    holo_base_msg_vision_ImageObjectsPoint2d* dst,
    const holo_base_msg_vision_ImageObjectsPoint2d* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_copy(
        &dst->stamp,(const holo_base_msg_common_Timestamp*)&src->stamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->sensor_id, &src->sensor_id);
    if (!holo_base_msg_vision_ObjectPoint2dSequence_copy(
        &dst->objects,(const holo_base_msg_vision_ObjectPoint2dSequence*)&src->objects)) {
        return RTI_FALSE;
    } 

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_vision_ImageObjectsPoint2d' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ImageObjectsPoint2d
#define TSeq holo_base_msg_vision_ImageObjectsPoint2dSeq

#define T_initialize holo_base_msg_vision_ImageObjectsPoint2d_initialize

#define T_finalize   holo_base_msg_vision_ImageObjectsPoint2d_finalize
#define T_copy       holo_base_msg_vision_ImageObjectsPoint2d_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ImageObjectsPoint2d
#define TSeq holo_base_msg_vision_ImageObjectsPoint2dSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_vision_ImageObjectsPoint2f *
holo_base_msg_vision_ImageObjectsPoint2f_create(void)
{
    holo_base_msg_vision_ImageObjectsPoint2f* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_vision_ImageObjectsPoint2f);
    if (sample != NULL) {
        if (!holo_base_msg_vision_ImageObjectsPoint2f_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_vision_ImageObjectsPoint2f_delete(holo_base_msg_vision_ImageObjectsPoint2f*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_vision_ImageObjectsPoint2f_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_vision_ImageObjectsPoint2f_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_vision_ImageObjectsPoint2fTYPENAME = "holo_base_msg::vision::ImageObjectsPoint2f";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_vision_ImageObjectsPoint2f_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_vision_ImageObjectsPoint2f_g_tc_members[3]=
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
            (char *)"sensor_id",/* Member name */
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
            (char *)"objects",/* Member name */
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

    static DDS_TypeCode holo_base_msg_vision_ImageObjectsPoint2f_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::vision::ImageObjectsPoint2f", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            3, /* Number of members */
            holo_base_msg_vision_ImageObjectsPoint2f_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_vision_ImageObjectsPoint2f*/

    if (is_initialized) {
        return &holo_base_msg_vision_ImageObjectsPoint2f_g_tc;
    }

    holo_base_msg_vision_ImageObjectsPoint2f_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_vision_ImageObjectsPoint2f_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_vision_ImageObjectsPoint2f_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_SensorId_get_typecode();
    holo_base_msg_vision_ImageObjectsPoint2f_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_vision_ObjectPoint2fSequence_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_vision_ImageObjectsPoint2f_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ImageObjectsPoint2f_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_vision_ImageObjectsPoint2f_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ImageObjectsPoint2f_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_vision_ImageObjectsPoint2f_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ImageObjectsPoint2f_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_vision_ImageObjectsPoint2f_g_tc._data._sampleAccessInfo =
    holo_base_msg_vision_ImageObjectsPoint2f_get_sample_access_info();
    holo_base_msg_vision_ImageObjectsPoint2f_g_tc._data._typePlugin =
    holo_base_msg_vision_ImageObjectsPoint2f_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_vision_ImageObjectsPoint2f_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_vision_ImageObjectsPoint2f_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_vision_ImageObjectsPoint2f *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_vision_ImageObjectsPoint2f_g_memberAccessInfos[3] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_vision_ImageObjectsPoint2f_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ImageObjectsPoint2f_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_vision_ImageObjectsPoint2f);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_vision_ImageObjectsPoint2f_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stamp - (char *)sample);

    holo_base_msg_vision_ImageObjectsPoint2f_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->sensor_id - (char *)sample);

    holo_base_msg_vision_ImageObjectsPoint2f_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->objects - (char *)sample);

    holo_base_msg_vision_ImageObjectsPoint2f_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_vision_ImageObjectsPoint2f_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_vision_ImageObjectsPoint2f);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_vision_ImageObjectsPoint2f_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_vision_ImageObjectsPoint2f_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_vision_ImageObjectsPoint2f_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ImageObjectsPoint2f_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_vision_ImageObjectsPoint2f_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_vision_ImageObjectsPoint2f_g_typePlugin = 
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
        holo_base_msg_vision_ImageObjectsPoint2f_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_vision_ImageObjectsPoint2f_finalize_w_return,
        NULL
    };

    return &holo_base_msg_vision_ImageObjectsPoint2f_g_typePlugin;
}
#endif

RTIBool holo_base_msg_vision_ImageObjectsPoint2f_initialize(
    holo_base_msg_vision_ImageObjectsPoint2f* sample) {
    return holo_base_msg_vision_ImageObjectsPoint2f_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_vision_ImageObjectsPoint2f_initialize_ex(
    holo_base_msg_vision_ImageObjectsPoint2f* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_vision_ImageObjectsPoint2f_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_vision_ImageObjectsPoint2f_initialize_w_params(
    holo_base_msg_vision_ImageObjectsPoint2f* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

    sample->sensor_id = 0u;

    if (!holo_base_msg_vision_ObjectPoint2fSequence_initialize_w_params(&sample->objects,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ImageObjectsPoint2f_finalize(
    holo_base_msg_vision_ImageObjectsPoint2f* sample)
{

    holo_base_msg_vision_ImageObjectsPoint2f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ImageObjectsPoint2f_finalize_w_return(
    holo_base_msg_vision_ImageObjectsPoint2f* sample)
{

    holo_base_msg_vision_ImageObjectsPoint2f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_vision_ImageObjectsPoint2f_finalize_ex(
    holo_base_msg_vision_ImageObjectsPoint2f* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_vision_ImageObjectsPoint2f_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_vision_ImageObjectsPoint2f_finalize_w_params(
    holo_base_msg_vision_ImageObjectsPoint2f* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->stamp,deallocParams);

    holo_base_msg_vision_ObjectPoint2fSequence_finalize_w_params(&sample->objects,deallocParams);

}

void holo_base_msg_vision_ImageObjectsPoint2f_finalize_optional_members(
    holo_base_msg_vision_ImageObjectsPoint2f* sample, RTIBool deletePointers)
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
    holo_base_msg_vision_ObjectPoint2fSequence_finalize_optional_members(&sample->objects, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_vision_ImageObjectsPoint2f_copy(
    holo_base_msg_vision_ImageObjectsPoint2f* dst,
    const holo_base_msg_vision_ImageObjectsPoint2f* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_copy(
        &dst->stamp,(const holo_base_msg_common_Timestamp*)&src->stamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->sensor_id, &src->sensor_id);
    if (!holo_base_msg_vision_ObjectPoint2fSequence_copy(
        &dst->objects,(const holo_base_msg_vision_ObjectPoint2fSequence*)&src->objects)) {
        return RTI_FALSE;
    } 

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_vision_ImageObjectsPoint2f' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ImageObjectsPoint2f
#define TSeq holo_base_msg_vision_ImageObjectsPoint2fSeq

#define T_initialize holo_base_msg_vision_ImageObjectsPoint2f_initialize

#define T_finalize   holo_base_msg_vision_ImageObjectsPoint2f_finalize
#define T_copy       holo_base_msg_vision_ImageObjectsPoint2f_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ImageObjectsPoint2f
#define TSeq holo_base_msg_vision_ImageObjectsPoint2fSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_vision_ImageObjectsPoint3d *
holo_base_msg_vision_ImageObjectsPoint3d_create(void)
{
    holo_base_msg_vision_ImageObjectsPoint3d* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_vision_ImageObjectsPoint3d);
    if (sample != NULL) {
        if (!holo_base_msg_vision_ImageObjectsPoint3d_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_vision_ImageObjectsPoint3d_delete(holo_base_msg_vision_ImageObjectsPoint3d*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_vision_ImageObjectsPoint3d_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_vision_ImageObjectsPoint3d_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_vision_ImageObjectsPoint3dTYPENAME = "holo_base_msg::vision::ImageObjectsPoint3d";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_vision_ImageObjectsPoint3d_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_vision_ImageObjectsPoint3d_g_tc_members[3]=
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
            (char *)"sensor_id",/* Member name */
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
            (char *)"objects",/* Member name */
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

    static DDS_TypeCode holo_base_msg_vision_ImageObjectsPoint3d_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::vision::ImageObjectsPoint3d", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            3, /* Number of members */
            holo_base_msg_vision_ImageObjectsPoint3d_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_vision_ImageObjectsPoint3d*/

    if (is_initialized) {
        return &holo_base_msg_vision_ImageObjectsPoint3d_g_tc;
    }

    holo_base_msg_vision_ImageObjectsPoint3d_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_vision_ImageObjectsPoint3d_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_vision_ImageObjectsPoint3d_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_SensorId_get_typecode();
    holo_base_msg_vision_ImageObjectsPoint3d_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_vision_ObjectPoint3dSequence_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_vision_ImageObjectsPoint3d_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ImageObjectsPoint3d_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_vision_ImageObjectsPoint3d_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ImageObjectsPoint3d_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_vision_ImageObjectsPoint3d_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ImageObjectsPoint3d_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_vision_ImageObjectsPoint3d_g_tc._data._sampleAccessInfo =
    holo_base_msg_vision_ImageObjectsPoint3d_get_sample_access_info();
    holo_base_msg_vision_ImageObjectsPoint3d_g_tc._data._typePlugin =
    holo_base_msg_vision_ImageObjectsPoint3d_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_vision_ImageObjectsPoint3d_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_vision_ImageObjectsPoint3d_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_vision_ImageObjectsPoint3d *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_vision_ImageObjectsPoint3d_g_memberAccessInfos[3] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_vision_ImageObjectsPoint3d_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ImageObjectsPoint3d_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_vision_ImageObjectsPoint3d);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_vision_ImageObjectsPoint3d_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stamp - (char *)sample);

    holo_base_msg_vision_ImageObjectsPoint3d_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->sensor_id - (char *)sample);

    holo_base_msg_vision_ImageObjectsPoint3d_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->objects - (char *)sample);

    holo_base_msg_vision_ImageObjectsPoint3d_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_vision_ImageObjectsPoint3d_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_vision_ImageObjectsPoint3d);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_vision_ImageObjectsPoint3d_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_vision_ImageObjectsPoint3d_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_vision_ImageObjectsPoint3d_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ImageObjectsPoint3d_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_vision_ImageObjectsPoint3d_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_vision_ImageObjectsPoint3d_g_typePlugin = 
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
        holo_base_msg_vision_ImageObjectsPoint3d_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_vision_ImageObjectsPoint3d_finalize_w_return,
        NULL
    };

    return &holo_base_msg_vision_ImageObjectsPoint3d_g_typePlugin;
}
#endif

RTIBool holo_base_msg_vision_ImageObjectsPoint3d_initialize(
    holo_base_msg_vision_ImageObjectsPoint3d* sample) {
    return holo_base_msg_vision_ImageObjectsPoint3d_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_vision_ImageObjectsPoint3d_initialize_ex(
    holo_base_msg_vision_ImageObjectsPoint3d* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_vision_ImageObjectsPoint3d_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_vision_ImageObjectsPoint3d_initialize_w_params(
    holo_base_msg_vision_ImageObjectsPoint3d* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

    sample->sensor_id = 0u;

    if (!holo_base_msg_vision_ObjectPoint3dSequence_initialize_w_params(&sample->objects,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ImageObjectsPoint3d_finalize(
    holo_base_msg_vision_ImageObjectsPoint3d* sample)
{

    holo_base_msg_vision_ImageObjectsPoint3d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ImageObjectsPoint3d_finalize_w_return(
    holo_base_msg_vision_ImageObjectsPoint3d* sample)
{

    holo_base_msg_vision_ImageObjectsPoint3d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_vision_ImageObjectsPoint3d_finalize_ex(
    holo_base_msg_vision_ImageObjectsPoint3d* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_vision_ImageObjectsPoint3d_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_vision_ImageObjectsPoint3d_finalize_w_params(
    holo_base_msg_vision_ImageObjectsPoint3d* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->stamp,deallocParams);

    holo_base_msg_vision_ObjectPoint3dSequence_finalize_w_params(&sample->objects,deallocParams);

}

void holo_base_msg_vision_ImageObjectsPoint3d_finalize_optional_members(
    holo_base_msg_vision_ImageObjectsPoint3d* sample, RTIBool deletePointers)
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
    holo_base_msg_vision_ObjectPoint3dSequence_finalize_optional_members(&sample->objects, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_vision_ImageObjectsPoint3d_copy(
    holo_base_msg_vision_ImageObjectsPoint3d* dst,
    const holo_base_msg_vision_ImageObjectsPoint3d* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_copy(
        &dst->stamp,(const holo_base_msg_common_Timestamp*)&src->stamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->sensor_id, &src->sensor_id);
    if (!holo_base_msg_vision_ObjectPoint3dSequence_copy(
        &dst->objects,(const holo_base_msg_vision_ObjectPoint3dSequence*)&src->objects)) {
        return RTI_FALSE;
    } 

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_vision_ImageObjectsPoint3d' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ImageObjectsPoint3d
#define TSeq holo_base_msg_vision_ImageObjectsPoint3dSeq

#define T_initialize holo_base_msg_vision_ImageObjectsPoint3d_initialize

#define T_finalize   holo_base_msg_vision_ImageObjectsPoint3d_finalize
#define T_copy       holo_base_msg_vision_ImageObjectsPoint3d_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ImageObjectsPoint3d
#define TSeq holo_base_msg_vision_ImageObjectsPoint3dSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_vision_ImageObjectsPoint3f *
holo_base_msg_vision_ImageObjectsPoint3f_create(void)
{
    holo_base_msg_vision_ImageObjectsPoint3f* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_vision_ImageObjectsPoint3f);
    if (sample != NULL) {
        if (!holo_base_msg_vision_ImageObjectsPoint3f_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_vision_ImageObjectsPoint3f_delete(holo_base_msg_vision_ImageObjectsPoint3f*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_vision_ImageObjectsPoint3f_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_vision_ImageObjectsPoint3f_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_vision_ImageObjectsPoint3fTYPENAME = "holo_base_msg::vision::ImageObjectsPoint3f";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_vision_ImageObjectsPoint3f_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_vision_ImageObjectsPoint3f_g_tc_members[3]=
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
            (char *)"sensor_id",/* Member name */
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
            (char *)"objects",/* Member name */
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

    static DDS_TypeCode holo_base_msg_vision_ImageObjectsPoint3f_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::vision::ImageObjectsPoint3f", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            3, /* Number of members */
            holo_base_msg_vision_ImageObjectsPoint3f_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_vision_ImageObjectsPoint3f*/

    if (is_initialized) {
        return &holo_base_msg_vision_ImageObjectsPoint3f_g_tc;
    }

    holo_base_msg_vision_ImageObjectsPoint3f_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_vision_ImageObjectsPoint3f_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_vision_ImageObjectsPoint3f_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_SensorId_get_typecode();
    holo_base_msg_vision_ImageObjectsPoint3f_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_vision_ObjectPoint3fSequence_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_vision_ImageObjectsPoint3f_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ImageObjectsPoint3f_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_vision_ImageObjectsPoint3f_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ImageObjectsPoint3f_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_vision_ImageObjectsPoint3f_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_vision_ImageObjectsPoint3f_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_vision_ImageObjectsPoint3f_g_tc._data._sampleAccessInfo =
    holo_base_msg_vision_ImageObjectsPoint3f_get_sample_access_info();
    holo_base_msg_vision_ImageObjectsPoint3f_g_tc._data._typePlugin =
    holo_base_msg_vision_ImageObjectsPoint3f_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_vision_ImageObjectsPoint3f_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_vision_ImageObjectsPoint3f_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_vision_ImageObjectsPoint3f *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_vision_ImageObjectsPoint3f_g_memberAccessInfos[3] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_vision_ImageObjectsPoint3f_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ImageObjectsPoint3f_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_vision_ImageObjectsPoint3f);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_vision_ImageObjectsPoint3f_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stamp - (char *)sample);

    holo_base_msg_vision_ImageObjectsPoint3f_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->sensor_id - (char *)sample);

    holo_base_msg_vision_ImageObjectsPoint3f_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->objects - (char *)sample);

    holo_base_msg_vision_ImageObjectsPoint3f_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_vision_ImageObjectsPoint3f_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_vision_ImageObjectsPoint3f);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_vision_ImageObjectsPoint3f_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_vision_ImageObjectsPoint3f_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_vision_ImageObjectsPoint3f_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_vision_ImageObjectsPoint3f_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_vision_ImageObjectsPoint3f_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_vision_ImageObjectsPoint3f_g_typePlugin = 
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
        holo_base_msg_vision_ImageObjectsPoint3f_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_vision_ImageObjectsPoint3f_finalize_w_return,
        NULL
    };

    return &holo_base_msg_vision_ImageObjectsPoint3f_g_typePlugin;
}
#endif

RTIBool holo_base_msg_vision_ImageObjectsPoint3f_initialize(
    holo_base_msg_vision_ImageObjectsPoint3f* sample) {
    return holo_base_msg_vision_ImageObjectsPoint3f_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_vision_ImageObjectsPoint3f_initialize_ex(
    holo_base_msg_vision_ImageObjectsPoint3f* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_vision_ImageObjectsPoint3f_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_vision_ImageObjectsPoint3f_initialize_w_params(
    holo_base_msg_vision_ImageObjectsPoint3f* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

    sample->sensor_id = 0u;

    if (!holo_base_msg_vision_ObjectPoint3fSequence_initialize_w_params(&sample->objects,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ImageObjectsPoint3f_finalize(
    holo_base_msg_vision_ImageObjectsPoint3f* sample)
{

    holo_base_msg_vision_ImageObjectsPoint3f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_vision_ImageObjectsPoint3f_finalize_w_return(
    holo_base_msg_vision_ImageObjectsPoint3f* sample)
{

    holo_base_msg_vision_ImageObjectsPoint3f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_vision_ImageObjectsPoint3f_finalize_ex(
    holo_base_msg_vision_ImageObjectsPoint3f* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_vision_ImageObjectsPoint3f_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_vision_ImageObjectsPoint3f_finalize_w_params(
    holo_base_msg_vision_ImageObjectsPoint3f* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->stamp,deallocParams);

    holo_base_msg_vision_ObjectPoint3fSequence_finalize_w_params(&sample->objects,deallocParams);

}

void holo_base_msg_vision_ImageObjectsPoint3f_finalize_optional_members(
    holo_base_msg_vision_ImageObjectsPoint3f* sample, RTIBool deletePointers)
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
    holo_base_msg_vision_ObjectPoint3fSequence_finalize_optional_members(&sample->objects, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_vision_ImageObjectsPoint3f_copy(
    holo_base_msg_vision_ImageObjectsPoint3f* dst,
    const holo_base_msg_vision_ImageObjectsPoint3f* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_copy(
        &dst->stamp,(const holo_base_msg_common_Timestamp*)&src->stamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->sensor_id, &src->sensor_id);
    if (!holo_base_msg_vision_ObjectPoint3fSequence_copy(
        &dst->objects,(const holo_base_msg_vision_ObjectPoint3fSequence*)&src->objects)) {
        return RTI_FALSE;
    } 

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_vision_ImageObjectsPoint3f' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ImageObjectsPoint3f
#define TSeq holo_base_msg_vision_ImageObjectsPoint3fSeq

#define T_initialize holo_base_msg_vision_ImageObjectsPoint3f_initialize

#define T_finalize   holo_base_msg_vision_ImageObjectsPoint3f_finalize
#define T_copy       holo_base_msg_vision_ImageObjectsPoint3f_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ImageObjectsPoint3f
#define TSeq holo_base_msg_vision_ImageObjectsPoint3fSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

