/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Point.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "Point.h"

#ifndef UNUSED_ARG
#define UNUSED_ARG(x) (void)(x)
#endif

#include "dds_c/dds_c_typecode.h"
/*** SOURCE_BEGIN ***/

holo_base_msg_geometry_Point3f *
holo_base_msg_geometry_Point3f_create(void)
{
    holo_base_msg_geometry_Point3f* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_geometry_Point3f);
    if (sample != NULL) {
        if (!holo_base_msg_geometry_Point3f_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_geometry_Point3f_delete(holo_base_msg_geometry_Point3f*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_geometry_Point3f_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_geometry_Point3f_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_geometry_Point3fTYPENAME = "holo_base_msg::geometry::Point3f";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_geometry_Point3f_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_geometry_Point3f_g_tc_members[3]=
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
        }
    };

    static DDS_TypeCode holo_base_msg_geometry_Point3f_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::geometry::Point3f", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            3, /* Number of members */
            holo_base_msg_geometry_Point3f_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_geometry_Point3f*/

    if (is_initialized) {
        return &holo_base_msg_geometry_Point3f_g_tc;
    }

    holo_base_msg_geometry_Point3f_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_geometry_Point3f_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_geometry_Point3f_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_geometry_Point3f_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_geometry_Point3f_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_geometry_Point3f_g_tc_members[0]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_geometry_Point3f_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_geometry_Point3f_g_tc_members[0]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_geometry_Point3f_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_geometry_Point3f_g_tc_members[0]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_geometry_Point3f_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_geometry_Point3f_g_tc_members[1]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_geometry_Point3f_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_geometry_Point3f_g_tc_members[1]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_geometry_Point3f_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_geometry_Point3f_g_tc_members[1]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_geometry_Point3f_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_geometry_Point3f_g_tc_members[2]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_geometry_Point3f_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_geometry_Point3f_g_tc_members[2]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_geometry_Point3f_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_geometry_Point3f_g_tc_members[2]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_geometry_Point3f_g_tc._data._sampleAccessInfo =
    holo_base_msg_geometry_Point3f_get_sample_access_info();
    holo_base_msg_geometry_Point3f_g_tc._data._typePlugin =
    holo_base_msg_geometry_Point3f_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_geometry_Point3f_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_geometry_Point3f_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_geometry_Point3f *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_geometry_Point3f_g_memberAccessInfos[3] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_geometry_Point3f_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_geometry_Point3f_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_geometry_Point3f);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_geometry_Point3f_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->x - (char *)sample);

    holo_base_msg_geometry_Point3f_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->y - (char *)sample);

    holo_base_msg_geometry_Point3f_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->z - (char *)sample);

    holo_base_msg_geometry_Point3f_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_geometry_Point3f_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_geometry_Point3f);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_geometry_Point3f_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_geometry_Point3f_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_geometry_Point3f_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_geometry_Point3f_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_geometry_Point3f_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_geometry_Point3f_g_typePlugin = 
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
        holo_base_msg_geometry_Point3f_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_geometry_Point3f_finalize_w_return,
        NULL
    };

    return &holo_base_msg_geometry_Point3f_g_typePlugin;
}
#endif

RTIBool holo_base_msg_geometry_Point3f_initialize(
    holo_base_msg_geometry_Point3f* sample) {
    return holo_base_msg_geometry_Point3f_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_geometry_Point3f_initialize_ex(
    holo_base_msg_geometry_Point3f* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_geometry_Point3f_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_geometry_Point3f_initialize_w_params(
    holo_base_msg_geometry_Point3f* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

    return RTI_TRUE;
}

RTIBool holo_base_msg_geometry_Point3f_finalize(
    holo_base_msg_geometry_Point3f* sample)
{

    holo_base_msg_geometry_Point3f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_geometry_Point3f_finalize_w_return(
    holo_base_msg_geometry_Point3f* sample)
{

    holo_base_msg_geometry_Point3f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_geometry_Point3f_finalize_ex(
    holo_base_msg_geometry_Point3f* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_geometry_Point3f_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_geometry_Point3f_finalize_w_params(
    holo_base_msg_geometry_Point3f* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_geometry_Point3f_finalize_optional_members(
    holo_base_msg_geometry_Point3f* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_geometry_Point3f_copy(
    holo_base_msg_geometry_Point3f* dst,
    const holo_base_msg_geometry_Point3f* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (&dst->x, &src->x);
    DDS_Primitive_copy (&dst->y, &src->y);
    DDS_Primitive_copy (&dst->z, &src->z);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_geometry_Point3f' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point3f
#define TSeq holo_base_msg_geometry_Point3fSeq

#define T_initialize holo_base_msg_geometry_Point3f_initialize

#define T_finalize   holo_base_msg_geometry_Point3f_finalize
#define T_copy       holo_base_msg_geometry_Point3f_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point3f
#define TSeq holo_base_msg_geometry_Point3fSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_geometry_Point3fSequence *
holo_base_msg_geometry_Point3fSequence_create(void)
{
    holo_base_msg_geometry_Point3fSequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_geometry_Point3fSequence);
    if (sample != NULL) {
        if (!holo_base_msg_geometry_Point3fSequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_geometry_Point3fSequence_delete(holo_base_msg_geometry_Point3fSequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_geometry_Point3fSequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_geometry_Point3fSequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_geometry_Point3fSequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_geometry_Point3fSequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_geometry_Point3fSequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::geometry::Point3fSequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_geometry_Point3fSequence */

    if (is_initialized) {
        return &holo_base_msg_geometry_Point3fSequence_g_tc;
    }

    holo_base_msg_geometry_Point3fSequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_geometry_Point3fSequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Point3f_get_typecode();
    holo_base_msg_geometry_Point3fSequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_geometry_Point3fSequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_geometry_Point3fSequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_geometry_Point3fSequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_geometry_Point3fSequence_get_sample_access_info();
    holo_base_msg_geometry_Point3fSequence_g_tc._data._typePlugin =
    holo_base_msg_geometry_Point3fSequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_geometry_Point3fSequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_geometry_Point3fSequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_geometry_Point3fSequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_geometry_Point3fSequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_geometry_Point3fSequence_g_sampleAccessInfo;
    }

    holo_base_msg_geometry_Point3fSequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_geometry_Point3fSequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_geometry_Point3fSequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_geometry_Point3fSequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_geometry_Point3fSequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_geometry_Point3fSequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_geometry_Point3fSequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_geometry_Point3fSequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_geometry_Point3fSequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_geometry_Point3fSequence_g_typePlugin = 
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
        holo_base_msg_geometry_Point3fSequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_geometry_Point3fSequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_geometry_Point3fSequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_geometry_Point3fSequence_initialize(
    holo_base_msg_geometry_Point3fSequence* sample) {
    return holo_base_msg_geometry_Point3fSequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_geometry_Point3fSequence_initialize_ex(
    holo_base_msg_geometry_Point3fSequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_geometry_Point3fSequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_geometry_Point3fSequence_initialize_w_params(
    holo_base_msg_geometry_Point3fSequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!holo_base_msg_geometry_Point3fSeq_initialize(sample )){
            return RTI_FALSE;
        };
        if (!holo_base_msg_geometry_Point3fSeq_set_maximum(sample, (100))) {
            return RTI_FALSE;
        }
    } else { 
        if(!holo_base_msg_geometry_Point3fSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_geometry_Point3fSequence_finalize(
    holo_base_msg_geometry_Point3fSequence* sample)
{

    holo_base_msg_geometry_Point3fSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_geometry_Point3fSequence_finalize_w_return(
    holo_base_msg_geometry_Point3fSequence* sample)
{

    holo_base_msg_geometry_Point3fSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_geometry_Point3fSequence_finalize_ex(
    holo_base_msg_geometry_Point3fSequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_geometry_Point3fSequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_geometry_Point3fSequence_finalize_w_params(
    holo_base_msg_geometry_Point3fSequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!holo_base_msg_geometry_Point3fSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_geometry_Point3fSequence_finalize_optional_members(
    holo_base_msg_geometry_Point3fSequence* sample, RTIBool deletePointers)
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
        length = (RTI_UINT32)holo_base_msg_geometry_Point3fSeq_get_length(
            sample);

        for (i = 0; i < length; i++) {
            holo_base_msg_geometry_Point3f_finalize_optional_members(
                holo_base_msg_geometry_Point3fSeq_get_reference(
                    sample, (RTI_INT32)i), deallocParams->delete_pointers);
        }
    }  

}

RTIBool holo_base_msg_geometry_Point3fSequence_copy(
    holo_base_msg_geometry_Point3fSequence* dst,
    const holo_base_msg_geometry_Point3fSequence* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_geometry_Point3fSeq_copy(dst ,
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
* Configure and implement 'holo_base_msg_geometry_Point3fSequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point3fSequence
#define TSeq holo_base_msg_geometry_Point3fSequenceSeq

#define T_initialize holo_base_msg_geometry_Point3fSequence_initialize

#define T_finalize   holo_base_msg_geometry_Point3fSequence_finalize
#define T_copy       holo_base_msg_geometry_Point3fSequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point3fSequence
#define TSeq holo_base_msg_geometry_Point3fSequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_geometry_Point3d *
holo_base_msg_geometry_Point3d_create(void)
{
    holo_base_msg_geometry_Point3d* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_geometry_Point3d);
    if (sample != NULL) {
        if (!holo_base_msg_geometry_Point3d_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_geometry_Point3d_delete(holo_base_msg_geometry_Point3d*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_geometry_Point3d_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_geometry_Point3d_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_geometry_Point3dTYPENAME = "holo_base_msg::geometry::Point3d";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_geometry_Point3d_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_geometry_Point3d_g_tc_members[3]=
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
        }
    };

    static DDS_TypeCode holo_base_msg_geometry_Point3d_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::geometry::Point3d", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            3, /* Number of members */
            holo_base_msg_geometry_Point3d_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_geometry_Point3d*/

    if (is_initialized) {
        return &holo_base_msg_geometry_Point3d_g_tc;
    }

    holo_base_msg_geometry_Point3d_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_geometry_Point3d_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();
    holo_base_msg_geometry_Point3d_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();
    holo_base_msg_geometry_Point3d_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_geometry_Point3d_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_geometry_Point3d_g_tc_members[0]._annotations._defaultValue._u.double_value = 0.0;
    holo_base_msg_geometry_Point3d_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_geometry_Point3d_g_tc_members[0]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
    holo_base_msg_geometry_Point3d_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_geometry_Point3d_g_tc_members[0]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;

    holo_base_msg_geometry_Point3d_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_geometry_Point3d_g_tc_members[1]._annotations._defaultValue._u.double_value = 0.0;
    holo_base_msg_geometry_Point3d_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_geometry_Point3d_g_tc_members[1]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
    holo_base_msg_geometry_Point3d_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_geometry_Point3d_g_tc_members[1]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;

    holo_base_msg_geometry_Point3d_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_geometry_Point3d_g_tc_members[2]._annotations._defaultValue._u.double_value = 0.0;
    holo_base_msg_geometry_Point3d_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_geometry_Point3d_g_tc_members[2]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
    holo_base_msg_geometry_Point3d_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_geometry_Point3d_g_tc_members[2]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;

    holo_base_msg_geometry_Point3d_g_tc._data._sampleAccessInfo =
    holo_base_msg_geometry_Point3d_get_sample_access_info();
    holo_base_msg_geometry_Point3d_g_tc._data._typePlugin =
    holo_base_msg_geometry_Point3d_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_geometry_Point3d_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_geometry_Point3d_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_geometry_Point3d *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_geometry_Point3d_g_memberAccessInfos[3] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_geometry_Point3d_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_geometry_Point3d_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_geometry_Point3d);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_geometry_Point3d_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->x - (char *)sample);

    holo_base_msg_geometry_Point3d_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->y - (char *)sample);

    holo_base_msg_geometry_Point3d_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->z - (char *)sample);

    holo_base_msg_geometry_Point3d_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_geometry_Point3d_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_geometry_Point3d);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_geometry_Point3d_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_geometry_Point3d_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_geometry_Point3d_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_geometry_Point3d_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_geometry_Point3d_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_geometry_Point3d_g_typePlugin = 
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
        holo_base_msg_geometry_Point3d_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_geometry_Point3d_finalize_w_return,
        NULL
    };

    return &holo_base_msg_geometry_Point3d_g_typePlugin;
}
#endif

RTIBool holo_base_msg_geometry_Point3d_initialize(
    holo_base_msg_geometry_Point3d* sample) {
    return holo_base_msg_geometry_Point3d_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_geometry_Point3d_initialize_ex(
    holo_base_msg_geometry_Point3d* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_geometry_Point3d_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_geometry_Point3d_initialize_w_params(
    holo_base_msg_geometry_Point3d* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->x = 0.0;

    sample->y = 0.0;

    sample->z = 0.0;

    return RTI_TRUE;
}

RTIBool holo_base_msg_geometry_Point3d_finalize(
    holo_base_msg_geometry_Point3d* sample)
{

    holo_base_msg_geometry_Point3d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_geometry_Point3d_finalize_w_return(
    holo_base_msg_geometry_Point3d* sample)
{

    holo_base_msg_geometry_Point3d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_geometry_Point3d_finalize_ex(
    holo_base_msg_geometry_Point3d* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_geometry_Point3d_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_geometry_Point3d_finalize_w_params(
    holo_base_msg_geometry_Point3d* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_geometry_Point3d_finalize_optional_members(
    holo_base_msg_geometry_Point3d* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_geometry_Point3d_copy(
    holo_base_msg_geometry_Point3d* dst,
    const holo_base_msg_geometry_Point3d* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (&dst->x, &src->x);
    DDS_Primitive_copy (&dst->y, &src->y);
    DDS_Primitive_copy (&dst->z, &src->z);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_geometry_Point3d' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point3d
#define TSeq holo_base_msg_geometry_Point3dSeq

#define T_initialize holo_base_msg_geometry_Point3d_initialize

#define T_finalize   holo_base_msg_geometry_Point3d_finalize
#define T_copy       holo_base_msg_geometry_Point3d_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point3d
#define TSeq holo_base_msg_geometry_Point3dSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_geometry_Point3dSequence *
holo_base_msg_geometry_Point3dSequence_create(void)
{
    holo_base_msg_geometry_Point3dSequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_geometry_Point3dSequence);
    if (sample != NULL) {
        if (!holo_base_msg_geometry_Point3dSequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_geometry_Point3dSequence_delete(holo_base_msg_geometry_Point3dSequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_geometry_Point3dSequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_geometry_Point3dSequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_geometry_Point3dSequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_geometry_Point3dSequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_geometry_Point3dSequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::geometry::Point3dSequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_geometry_Point3dSequence */

    if (is_initialized) {
        return &holo_base_msg_geometry_Point3dSequence_g_tc;
    }

    holo_base_msg_geometry_Point3dSequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_geometry_Point3dSequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Point3d_get_typecode();
    holo_base_msg_geometry_Point3dSequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_geometry_Point3dSequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_geometry_Point3dSequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_geometry_Point3dSequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_geometry_Point3dSequence_get_sample_access_info();
    holo_base_msg_geometry_Point3dSequence_g_tc._data._typePlugin =
    holo_base_msg_geometry_Point3dSequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_geometry_Point3dSequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_geometry_Point3dSequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_geometry_Point3dSequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_geometry_Point3dSequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_geometry_Point3dSequence_g_sampleAccessInfo;
    }

    holo_base_msg_geometry_Point3dSequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_geometry_Point3dSequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_geometry_Point3dSequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_geometry_Point3dSequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_geometry_Point3dSequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_geometry_Point3dSequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_geometry_Point3dSequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_geometry_Point3dSequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_geometry_Point3dSequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_geometry_Point3dSequence_g_typePlugin = 
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
        holo_base_msg_geometry_Point3dSequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_geometry_Point3dSequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_geometry_Point3dSequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_geometry_Point3dSequence_initialize(
    holo_base_msg_geometry_Point3dSequence* sample) {
    return holo_base_msg_geometry_Point3dSequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_geometry_Point3dSequence_initialize_ex(
    holo_base_msg_geometry_Point3dSequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_geometry_Point3dSequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_geometry_Point3dSequence_initialize_w_params(
    holo_base_msg_geometry_Point3dSequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!holo_base_msg_geometry_Point3dSeq_initialize(sample )){
            return RTI_FALSE;
        };
        if (!holo_base_msg_geometry_Point3dSeq_set_maximum(sample, (100))) {
            return RTI_FALSE;
        }
    } else { 
        if(!holo_base_msg_geometry_Point3dSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_geometry_Point3dSequence_finalize(
    holo_base_msg_geometry_Point3dSequence* sample)
{

    holo_base_msg_geometry_Point3dSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_geometry_Point3dSequence_finalize_w_return(
    holo_base_msg_geometry_Point3dSequence* sample)
{

    holo_base_msg_geometry_Point3dSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_geometry_Point3dSequence_finalize_ex(
    holo_base_msg_geometry_Point3dSequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_geometry_Point3dSequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_geometry_Point3dSequence_finalize_w_params(
    holo_base_msg_geometry_Point3dSequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!holo_base_msg_geometry_Point3dSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_geometry_Point3dSequence_finalize_optional_members(
    holo_base_msg_geometry_Point3dSequence* sample, RTIBool deletePointers)
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
        length = (RTI_UINT32)holo_base_msg_geometry_Point3dSeq_get_length(
            sample);

        for (i = 0; i < length; i++) {
            holo_base_msg_geometry_Point3d_finalize_optional_members(
                holo_base_msg_geometry_Point3dSeq_get_reference(
                    sample, (RTI_INT32)i), deallocParams->delete_pointers);
        }
    }  

}

RTIBool holo_base_msg_geometry_Point3dSequence_copy(
    holo_base_msg_geometry_Point3dSequence* dst,
    const holo_base_msg_geometry_Point3dSequence* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_geometry_Point3dSeq_copy(dst ,
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
* Configure and implement 'holo_base_msg_geometry_Point3dSequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point3dSequence
#define TSeq holo_base_msg_geometry_Point3dSequenceSeq

#define T_initialize holo_base_msg_geometry_Point3dSequence_initialize

#define T_finalize   holo_base_msg_geometry_Point3dSequence_finalize
#define T_copy       holo_base_msg_geometry_Point3dSequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point3dSequence
#define TSeq holo_base_msg_geometry_Point3dSequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_geometry_Point2f *
holo_base_msg_geometry_Point2f_create(void)
{
    holo_base_msg_geometry_Point2f* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_geometry_Point2f);
    if (sample != NULL) {
        if (!holo_base_msg_geometry_Point2f_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_geometry_Point2f_delete(holo_base_msg_geometry_Point2f*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_geometry_Point2f_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_geometry_Point2f_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_geometry_Point2fTYPENAME = "holo_base_msg::geometry::Point2f";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_geometry_Point2f_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_geometry_Point2f_g_tc_members[2]=
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
        }
    };

    static DDS_TypeCode holo_base_msg_geometry_Point2f_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::geometry::Point2f", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            2, /* Number of members */
            holo_base_msg_geometry_Point2f_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_geometry_Point2f*/

    if (is_initialized) {
        return &holo_base_msg_geometry_Point2f_g_tc;
    }

    holo_base_msg_geometry_Point2f_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_geometry_Point2f_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_geometry_Point2f_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_geometry_Point2f_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_geometry_Point2f_g_tc_members[0]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_geometry_Point2f_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_geometry_Point2f_g_tc_members[0]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_geometry_Point2f_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_geometry_Point2f_g_tc_members[0]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_geometry_Point2f_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_geometry_Point2f_g_tc_members[1]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_geometry_Point2f_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_geometry_Point2f_g_tc_members[1]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_geometry_Point2f_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_geometry_Point2f_g_tc_members[1]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_geometry_Point2f_g_tc._data._sampleAccessInfo =
    holo_base_msg_geometry_Point2f_get_sample_access_info();
    holo_base_msg_geometry_Point2f_g_tc._data._typePlugin =
    holo_base_msg_geometry_Point2f_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_geometry_Point2f_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_geometry_Point2f_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_geometry_Point2f *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_geometry_Point2f_g_memberAccessInfos[2] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_geometry_Point2f_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_geometry_Point2f_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_geometry_Point2f);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_geometry_Point2f_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->x - (char *)sample);

    holo_base_msg_geometry_Point2f_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->y - (char *)sample);

    holo_base_msg_geometry_Point2f_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_geometry_Point2f_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_geometry_Point2f);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_geometry_Point2f_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_geometry_Point2f_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_geometry_Point2f_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_geometry_Point2f_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_geometry_Point2f_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_geometry_Point2f_g_typePlugin = 
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
        holo_base_msg_geometry_Point2f_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_geometry_Point2f_finalize_w_return,
        NULL
    };

    return &holo_base_msg_geometry_Point2f_g_typePlugin;
}
#endif

RTIBool holo_base_msg_geometry_Point2f_initialize(
    holo_base_msg_geometry_Point2f* sample) {
    return holo_base_msg_geometry_Point2f_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_geometry_Point2f_initialize_ex(
    holo_base_msg_geometry_Point2f* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_geometry_Point2f_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_geometry_Point2f_initialize_w_params(
    holo_base_msg_geometry_Point2f* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->x = 0.0f;

    sample->y = 0.0f;

    return RTI_TRUE;
}

RTIBool holo_base_msg_geometry_Point2f_finalize(
    holo_base_msg_geometry_Point2f* sample)
{

    holo_base_msg_geometry_Point2f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_geometry_Point2f_finalize_w_return(
    holo_base_msg_geometry_Point2f* sample)
{

    holo_base_msg_geometry_Point2f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_geometry_Point2f_finalize_ex(
    holo_base_msg_geometry_Point2f* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_geometry_Point2f_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_geometry_Point2f_finalize_w_params(
    holo_base_msg_geometry_Point2f* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_geometry_Point2f_finalize_optional_members(
    holo_base_msg_geometry_Point2f* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_geometry_Point2f_copy(
    holo_base_msg_geometry_Point2f* dst,
    const holo_base_msg_geometry_Point2f* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (&dst->x, &src->x);
    DDS_Primitive_copy (&dst->y, &src->y);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_geometry_Point2f' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point2f
#define TSeq holo_base_msg_geometry_Point2fSeq

#define T_initialize holo_base_msg_geometry_Point2f_initialize

#define T_finalize   holo_base_msg_geometry_Point2f_finalize
#define T_copy       holo_base_msg_geometry_Point2f_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point2f
#define TSeq holo_base_msg_geometry_Point2fSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_geometry_Point2fSequence *
holo_base_msg_geometry_Point2fSequence_create(void)
{
    holo_base_msg_geometry_Point2fSequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_geometry_Point2fSequence);
    if (sample != NULL) {
        if (!holo_base_msg_geometry_Point2fSequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_geometry_Point2fSequence_delete(holo_base_msg_geometry_Point2fSequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_geometry_Point2fSequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_geometry_Point2fSequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_geometry_Point2fSequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_geometry_Point2fSequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_geometry_Point2fSequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::geometry::Point2fSequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_geometry_Point2fSequence */

    if (is_initialized) {
        return &holo_base_msg_geometry_Point2fSequence_g_tc;
    }

    holo_base_msg_geometry_Point2fSequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_geometry_Point2fSequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Point2f_get_typecode();
    holo_base_msg_geometry_Point2fSequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_geometry_Point2fSequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_geometry_Point2fSequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_geometry_Point2fSequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_geometry_Point2fSequence_get_sample_access_info();
    holo_base_msg_geometry_Point2fSequence_g_tc._data._typePlugin =
    holo_base_msg_geometry_Point2fSequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_geometry_Point2fSequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_geometry_Point2fSequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_geometry_Point2fSequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_geometry_Point2fSequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_geometry_Point2fSequence_g_sampleAccessInfo;
    }

    holo_base_msg_geometry_Point2fSequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_geometry_Point2fSequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_geometry_Point2fSequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_geometry_Point2fSequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_geometry_Point2fSequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_geometry_Point2fSequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_geometry_Point2fSequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_geometry_Point2fSequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_geometry_Point2fSequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_geometry_Point2fSequence_g_typePlugin = 
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
        holo_base_msg_geometry_Point2fSequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_geometry_Point2fSequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_geometry_Point2fSequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_geometry_Point2fSequence_initialize(
    holo_base_msg_geometry_Point2fSequence* sample) {
    return holo_base_msg_geometry_Point2fSequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_geometry_Point2fSequence_initialize_ex(
    holo_base_msg_geometry_Point2fSequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_geometry_Point2fSequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_geometry_Point2fSequence_initialize_w_params(
    holo_base_msg_geometry_Point2fSequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!holo_base_msg_geometry_Point2fSeq_initialize(sample )){
            return RTI_FALSE;
        };
        if (!holo_base_msg_geometry_Point2fSeq_set_maximum(sample, (100))) {
            return RTI_FALSE;
        }
    } else { 
        if(!holo_base_msg_geometry_Point2fSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_geometry_Point2fSequence_finalize(
    holo_base_msg_geometry_Point2fSequence* sample)
{

    holo_base_msg_geometry_Point2fSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_geometry_Point2fSequence_finalize_w_return(
    holo_base_msg_geometry_Point2fSequence* sample)
{

    holo_base_msg_geometry_Point2fSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_geometry_Point2fSequence_finalize_ex(
    holo_base_msg_geometry_Point2fSequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_geometry_Point2fSequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_geometry_Point2fSequence_finalize_w_params(
    holo_base_msg_geometry_Point2fSequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!holo_base_msg_geometry_Point2fSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_geometry_Point2fSequence_finalize_optional_members(
    holo_base_msg_geometry_Point2fSequence* sample, RTIBool deletePointers)
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
        length = (RTI_UINT32)holo_base_msg_geometry_Point2fSeq_get_length(
            sample);

        for (i = 0; i < length; i++) {
            holo_base_msg_geometry_Point2f_finalize_optional_members(
                holo_base_msg_geometry_Point2fSeq_get_reference(
                    sample, (RTI_INT32)i), deallocParams->delete_pointers);
        }
    }  

}

RTIBool holo_base_msg_geometry_Point2fSequence_copy(
    holo_base_msg_geometry_Point2fSequence* dst,
    const holo_base_msg_geometry_Point2fSequence* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_geometry_Point2fSeq_copy(dst ,
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
* Configure and implement 'holo_base_msg_geometry_Point2fSequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point2fSequence
#define TSeq holo_base_msg_geometry_Point2fSequenceSeq

#define T_initialize holo_base_msg_geometry_Point2fSequence_initialize

#define T_finalize   holo_base_msg_geometry_Point2fSequence_finalize
#define T_copy       holo_base_msg_geometry_Point2fSequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point2fSequence
#define TSeq holo_base_msg_geometry_Point2fSequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_geometry_Point2d *
holo_base_msg_geometry_Point2d_create(void)
{
    holo_base_msg_geometry_Point2d* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_geometry_Point2d);
    if (sample != NULL) {
        if (!holo_base_msg_geometry_Point2d_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_geometry_Point2d_delete(holo_base_msg_geometry_Point2d*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_geometry_Point2d_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_geometry_Point2d_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_geometry_Point2dTYPENAME = "holo_base_msg::geometry::Point2d";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_geometry_Point2d_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_geometry_Point2d_g_tc_members[2]=
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
        }
    };

    static DDS_TypeCode holo_base_msg_geometry_Point2d_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::geometry::Point2d", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            2, /* Number of members */
            holo_base_msg_geometry_Point2d_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_geometry_Point2d*/

    if (is_initialized) {
        return &holo_base_msg_geometry_Point2d_g_tc;
    }

    holo_base_msg_geometry_Point2d_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_geometry_Point2d_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();
    holo_base_msg_geometry_Point2d_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_geometry_Point2d_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_geometry_Point2d_g_tc_members[0]._annotations._defaultValue._u.double_value = 0.0;
    holo_base_msg_geometry_Point2d_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_geometry_Point2d_g_tc_members[0]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
    holo_base_msg_geometry_Point2d_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_geometry_Point2d_g_tc_members[0]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;

    holo_base_msg_geometry_Point2d_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_geometry_Point2d_g_tc_members[1]._annotations._defaultValue._u.double_value = 0.0;
    holo_base_msg_geometry_Point2d_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_geometry_Point2d_g_tc_members[1]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
    holo_base_msg_geometry_Point2d_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_geometry_Point2d_g_tc_members[1]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;

    holo_base_msg_geometry_Point2d_g_tc._data._sampleAccessInfo =
    holo_base_msg_geometry_Point2d_get_sample_access_info();
    holo_base_msg_geometry_Point2d_g_tc._data._typePlugin =
    holo_base_msg_geometry_Point2d_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_geometry_Point2d_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_geometry_Point2d_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_geometry_Point2d *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_geometry_Point2d_g_memberAccessInfos[2] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_geometry_Point2d_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_geometry_Point2d_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_geometry_Point2d);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_geometry_Point2d_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->x - (char *)sample);

    holo_base_msg_geometry_Point2d_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->y - (char *)sample);

    holo_base_msg_geometry_Point2d_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_geometry_Point2d_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_geometry_Point2d);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_geometry_Point2d_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_geometry_Point2d_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_geometry_Point2d_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_geometry_Point2d_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_geometry_Point2d_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_geometry_Point2d_g_typePlugin = 
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
        holo_base_msg_geometry_Point2d_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_geometry_Point2d_finalize_w_return,
        NULL
    };

    return &holo_base_msg_geometry_Point2d_g_typePlugin;
}
#endif

RTIBool holo_base_msg_geometry_Point2d_initialize(
    holo_base_msg_geometry_Point2d* sample) {
    return holo_base_msg_geometry_Point2d_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_geometry_Point2d_initialize_ex(
    holo_base_msg_geometry_Point2d* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_geometry_Point2d_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_geometry_Point2d_initialize_w_params(
    holo_base_msg_geometry_Point2d* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->x = 0.0;

    sample->y = 0.0;

    return RTI_TRUE;
}

RTIBool holo_base_msg_geometry_Point2d_finalize(
    holo_base_msg_geometry_Point2d* sample)
{

    holo_base_msg_geometry_Point2d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_geometry_Point2d_finalize_w_return(
    holo_base_msg_geometry_Point2d* sample)
{

    holo_base_msg_geometry_Point2d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_geometry_Point2d_finalize_ex(
    holo_base_msg_geometry_Point2d* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_geometry_Point2d_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_geometry_Point2d_finalize_w_params(
    holo_base_msg_geometry_Point2d* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_geometry_Point2d_finalize_optional_members(
    holo_base_msg_geometry_Point2d* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_geometry_Point2d_copy(
    holo_base_msg_geometry_Point2d* dst,
    const holo_base_msg_geometry_Point2d* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (&dst->x, &src->x);
    DDS_Primitive_copy (&dst->y, &src->y);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_geometry_Point2d' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point2d
#define TSeq holo_base_msg_geometry_Point2dSeq

#define T_initialize holo_base_msg_geometry_Point2d_initialize

#define T_finalize   holo_base_msg_geometry_Point2d_finalize
#define T_copy       holo_base_msg_geometry_Point2d_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point2d
#define TSeq holo_base_msg_geometry_Point2dSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_geometry_Point2dSequence *
holo_base_msg_geometry_Point2dSequence_create(void)
{
    holo_base_msg_geometry_Point2dSequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_geometry_Point2dSequence);
    if (sample != NULL) {
        if (!holo_base_msg_geometry_Point2dSequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_geometry_Point2dSequence_delete(holo_base_msg_geometry_Point2dSequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_geometry_Point2dSequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_geometry_Point2dSequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_geometry_Point2dSequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_geometry_Point2dSequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_geometry_Point2dSequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::geometry::Point2dSequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_geometry_Point2dSequence */

    if (is_initialized) {
        return &holo_base_msg_geometry_Point2dSequence_g_tc;
    }

    holo_base_msg_geometry_Point2dSequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_geometry_Point2dSequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Point2d_get_typecode();
    holo_base_msg_geometry_Point2dSequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_geometry_Point2dSequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_geometry_Point2dSequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_geometry_Point2dSequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_geometry_Point2dSequence_get_sample_access_info();
    holo_base_msg_geometry_Point2dSequence_g_tc._data._typePlugin =
    holo_base_msg_geometry_Point2dSequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_geometry_Point2dSequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_geometry_Point2dSequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_geometry_Point2dSequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_geometry_Point2dSequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_geometry_Point2dSequence_g_sampleAccessInfo;
    }

    holo_base_msg_geometry_Point2dSequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_geometry_Point2dSequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_geometry_Point2dSequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_geometry_Point2dSequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_geometry_Point2dSequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_geometry_Point2dSequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_geometry_Point2dSequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_geometry_Point2dSequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_geometry_Point2dSequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_geometry_Point2dSequence_g_typePlugin = 
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
        holo_base_msg_geometry_Point2dSequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_geometry_Point2dSequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_geometry_Point2dSequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_geometry_Point2dSequence_initialize(
    holo_base_msg_geometry_Point2dSequence* sample) {
    return holo_base_msg_geometry_Point2dSequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_geometry_Point2dSequence_initialize_ex(
    holo_base_msg_geometry_Point2dSequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_geometry_Point2dSequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_geometry_Point2dSequence_initialize_w_params(
    holo_base_msg_geometry_Point2dSequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!holo_base_msg_geometry_Point2dSeq_initialize(sample )){
            return RTI_FALSE;
        };
        if (!holo_base_msg_geometry_Point2dSeq_set_maximum(sample, (100))) {
            return RTI_FALSE;
        }
    } else { 
        if(!holo_base_msg_geometry_Point2dSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_geometry_Point2dSequence_finalize(
    holo_base_msg_geometry_Point2dSequence* sample)
{

    holo_base_msg_geometry_Point2dSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_geometry_Point2dSequence_finalize_w_return(
    holo_base_msg_geometry_Point2dSequence* sample)
{

    holo_base_msg_geometry_Point2dSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_geometry_Point2dSequence_finalize_ex(
    holo_base_msg_geometry_Point2dSequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_geometry_Point2dSequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_geometry_Point2dSequence_finalize_w_params(
    holo_base_msg_geometry_Point2dSequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!holo_base_msg_geometry_Point2dSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_geometry_Point2dSequence_finalize_optional_members(
    holo_base_msg_geometry_Point2dSequence* sample, RTIBool deletePointers)
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
        length = (RTI_UINT32)holo_base_msg_geometry_Point2dSeq_get_length(
            sample);

        for (i = 0; i < length; i++) {
            holo_base_msg_geometry_Point2d_finalize_optional_members(
                holo_base_msg_geometry_Point2dSeq_get_reference(
                    sample, (RTI_INT32)i), deallocParams->delete_pointers);
        }
    }  

}

RTIBool holo_base_msg_geometry_Point2dSequence_copy(
    holo_base_msg_geometry_Point2dSequence* dst,
    const holo_base_msg_geometry_Point2dSequence* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_geometry_Point2dSeq_copy(dst ,
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
* Configure and implement 'holo_base_msg_geometry_Point2dSequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point2dSequence
#define TSeq holo_base_msg_geometry_Point2dSequenceSeq

#define T_initialize holo_base_msg_geometry_Point2dSequence_initialize

#define T_finalize   holo_base_msg_geometry_Point2dSequence_finalize
#define T_copy       holo_base_msg_geometry_Point2dSequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point2dSequence
#define TSeq holo_base_msg_geometry_Point2dSequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

