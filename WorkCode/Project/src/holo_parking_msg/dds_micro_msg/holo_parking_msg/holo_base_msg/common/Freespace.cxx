/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Freespace.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "Freespace.h"

#ifndef UNUSED_ARG
#define UNUSED_ARG(x) (void)(x)
#endif

#include "dds_c/dds_c_typecode.h"
/*** SOURCE_BEGIN ***/

holo_base_msg_common_freespace3f_SegmentInfo *
holo_base_msg_common_freespace3f_SegmentInfo_create(void)
{
    holo_base_msg_common_freespace3f_SegmentInfo* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_freespace3f_SegmentInfo);
    if (sample != NULL) {
        if (!holo_base_msg_common_freespace3f_SegmentInfo_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_freespace3f_SegmentInfo_delete(holo_base_msg_common_freespace3f_SegmentInfo*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_freespace3f_SegmentInfo_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_freespace3f_SegmentInfo_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_common_freespace3f_SegmentInfoTYPENAME = "holo_base_msg::common::freespace3f::SegmentInfo";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_freespace3f_SegmentInfo_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_common_freespace3f_SegmentInfo_g_tc_members[3]=
    {

        {
            (char *)"start",/* Member name */
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
            (char *)"end",/* Member name */
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
            (char *)"type",/* Member name */
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

    static DDS_TypeCode holo_base_msg_common_freespace3f_SegmentInfo_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::common::freespace3f::SegmentInfo", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            3, /* Number of members */
            holo_base_msg_common_freespace3f_SegmentInfo_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_common_freespace3f_SegmentInfo*/

    if (is_initialized) {
        return &holo_base_msg_common_freespace3f_SegmentInfo_g_tc;
    }

    holo_base_msg_common_freespace3f_SegmentInfo_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_freespace3f_SegmentInfo_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint32_t_get_typecode();
    holo_base_msg_common_freespace3f_SegmentInfo_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint32_t_get_typecode();
    holo_base_msg_common_freespace3f_SegmentInfo_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint32_t_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_common_freespace3f_SegmentInfo_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_freespace3f_SegmentInfo_g_tc_members[0]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_freespace3f_SegmentInfo_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_freespace3f_SegmentInfo_g_tc_members[0]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_freespace3f_SegmentInfo_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_freespace3f_SegmentInfo_g_tc_members[0]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_freespace3f_SegmentInfo_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_freespace3f_SegmentInfo_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_freespace3f_SegmentInfo_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_freespace3f_SegmentInfo_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_freespace3f_SegmentInfo_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_freespace3f_SegmentInfo_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_freespace3f_SegmentInfo_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_freespace3f_SegmentInfo_g_tc_members[2]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_freespace3f_SegmentInfo_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_freespace3f_SegmentInfo_g_tc_members[2]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_freespace3f_SegmentInfo_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_freespace3f_SegmentInfo_g_tc_members[2]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_freespace3f_SegmentInfo_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_freespace3f_SegmentInfo_get_sample_access_info();
    holo_base_msg_common_freespace3f_SegmentInfo_g_tc._data._typePlugin =
    holo_base_msg_common_freespace3f_SegmentInfo_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_freespace3f_SegmentInfo_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_freespace3f_SegmentInfo_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_common_freespace3f_SegmentInfo *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_freespace3f_SegmentInfo_g_memberAccessInfos[3] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_freespace3f_SegmentInfo_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_freespace3f_SegmentInfo_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_common_freespace3f_SegmentInfo);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_common_freespace3f_SegmentInfo_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->start - (char *)sample);

    holo_base_msg_common_freespace3f_SegmentInfo_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->end - (char *)sample);

    holo_base_msg_common_freespace3f_SegmentInfo_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->type - (char *)sample);

    holo_base_msg_common_freespace3f_SegmentInfo_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_freespace3f_SegmentInfo_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_freespace3f_SegmentInfo);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_freespace3f_SegmentInfo_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_freespace3f_SegmentInfo_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_freespace3f_SegmentInfo_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_freespace3f_SegmentInfo_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_freespace3f_SegmentInfo_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_freespace3f_SegmentInfo_g_typePlugin = 
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
        holo_base_msg_common_freespace3f_SegmentInfo_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_freespace3f_SegmentInfo_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_freespace3f_SegmentInfo_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_freespace3f_SegmentInfo_initialize(
    holo_base_msg_common_freespace3f_SegmentInfo* sample) {
    return holo_base_msg_common_freespace3f_SegmentInfo_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_freespace3f_SegmentInfo_initialize_ex(
    holo_base_msg_common_freespace3f_SegmentInfo* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_freespace3f_SegmentInfo_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_freespace3f_SegmentInfo_initialize_w_params(
    holo_base_msg_common_freespace3f_SegmentInfo* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->start = 0u;

    sample->end = 0u;

    sample->type = 0u;

    return RTI_TRUE;
}

RTIBool holo_base_msg_common_freespace3f_SegmentInfo_finalize(
    holo_base_msg_common_freespace3f_SegmentInfo* sample)
{

    holo_base_msg_common_freespace3f_SegmentInfo_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_freespace3f_SegmentInfo_finalize_w_return(
    holo_base_msg_common_freespace3f_SegmentInfo* sample)
{

    holo_base_msg_common_freespace3f_SegmentInfo_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_freespace3f_SegmentInfo_finalize_ex(
    holo_base_msg_common_freespace3f_SegmentInfo* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_freespace3f_SegmentInfo_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_freespace3f_SegmentInfo_finalize_w_params(
    holo_base_msg_common_freespace3f_SegmentInfo* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_common_freespace3f_SegmentInfo_finalize_optional_members(
    holo_base_msg_common_freespace3f_SegmentInfo* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_common_freespace3f_SegmentInfo_copy(
    holo_base_msg_common_freespace3f_SegmentInfo* dst,
    const holo_base_msg_common_freespace3f_SegmentInfo* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (&dst->start, &src->start);
    DDS_Primitive_copy (&dst->end, &src->end);
    DDS_Primitive_copy (&dst->type, &src->type);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_freespace3f_SegmentInfo' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_freespace3f_SegmentInfo
#define TSeq holo_base_msg_common_freespace3f_SegmentInfoSeq

#define T_initialize holo_base_msg_common_freespace3f_SegmentInfo_initialize

#define T_finalize   holo_base_msg_common_freespace3f_SegmentInfo_finalize
#define T_copy       holo_base_msg_common_freespace3f_SegmentInfo_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_freespace3f_SegmentInfo
#define TSeq holo_base_msg_common_freespace3f_SegmentInfoSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_freespace3f_FreespaceInterior *
holo_base_msg_common_freespace3f_FreespaceInterior_create(void)
{
    holo_base_msg_common_freespace3f_FreespaceInterior* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_freespace3f_FreespaceInterior);
    if (sample != NULL) {
        if (!holo_base_msg_common_freespace3f_FreespaceInterior_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_freespace3f_FreespaceInterior_delete(holo_base_msg_common_freespace3f_FreespaceInterior*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_freespace3f_FreespaceInterior_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_freespace3f_FreespaceInterior_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_common_freespace3f_FreespaceInteriorTYPENAME = "holo_base_msg::common::freespace3f::FreespaceInterior";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_freespace3f_FreespaceInterior_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_common_freespace3f_FreespaceInterior_g_tc_points_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);
    static DDS_TypeCode holo_base_msg_common_freespace3f_FreespaceInterior_g_tc_boundaries_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode_Member holo_base_msg_common_freespace3f_FreespaceInterior_g_tc_members[2]=
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
            (char *)"boundaries",/* Member name */
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

    static DDS_TypeCode holo_base_msg_common_freespace3f_FreespaceInterior_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::common::freespace3f::FreespaceInterior", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            2, /* Number of members */
            holo_base_msg_common_freespace3f_FreespaceInterior_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_common_freespace3f_FreespaceInterior*/

    if (is_initialized) {
        return &holo_base_msg_common_freespace3f_FreespaceInterior_g_tc;
    }

    holo_base_msg_common_freespace3f_FreespaceInterior_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_freespace3f_FreespaceInterior_g_tc_points_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Point3f_get_typecode();
    holo_base_msg_common_freespace3f_FreespaceInterior_g_tc_points_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_common_freespace3f_FreespaceInterior_g_tc_boundaries_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_common_freespace3f_SegmentInfo_get_typecode();
    holo_base_msg_common_freespace3f_FreespaceInterior_g_tc_boundaries_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_common_freespace3f_FreespaceInterior_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)& holo_base_msg_common_freespace3f_FreespaceInterior_g_tc_points_sequence;
    holo_base_msg_common_freespace3f_FreespaceInterior_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)& holo_base_msg_common_freespace3f_FreespaceInterior_g_tc_boundaries_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_common_freespace3f_FreespaceInterior_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_freespace3f_FreespaceInterior_get_sample_access_info();
    holo_base_msg_common_freespace3f_FreespaceInterior_g_tc._data._typePlugin =
    holo_base_msg_common_freespace3f_FreespaceInterior_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_freespace3f_FreespaceInterior_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_freespace3f_FreespaceInterior_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_common_freespace3f_FreespaceInterior *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_freespace3f_FreespaceInterior_g_memberAccessInfos[2] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_freespace3f_FreespaceInterior_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_freespace3f_FreespaceInterior_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_common_freespace3f_FreespaceInterior);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_common_freespace3f_FreespaceInterior_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->points - (char *)sample);

    holo_base_msg_common_freespace3f_FreespaceInterior_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->boundaries - (char *)sample);

    holo_base_msg_common_freespace3f_FreespaceInterior_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_freespace3f_FreespaceInterior_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_freespace3f_FreespaceInterior);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_freespace3f_FreespaceInterior_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_freespace3f_FreespaceInterior_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_freespace3f_FreespaceInterior_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_freespace3f_FreespaceInterior_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_freespace3f_FreespaceInterior_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_freespace3f_FreespaceInterior_g_typePlugin = 
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
        holo_base_msg_common_freespace3f_FreespaceInterior_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_freespace3f_FreespaceInterior_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_freespace3f_FreespaceInterior_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_freespace3f_FreespaceInterior_initialize(
    holo_base_msg_common_freespace3f_FreespaceInterior* sample) {
    return holo_base_msg_common_freespace3f_FreespaceInterior_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_freespace3f_FreespaceInterior_initialize_ex(
    holo_base_msg_common_freespace3f_FreespaceInterior* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_freespace3f_FreespaceInterior_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_freespace3f_FreespaceInterior_initialize_w_params(
    holo_base_msg_common_freespace3f_FreespaceInterior* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!holo_base_msg_geometry_Point3fSeq_initialize(&sample->points )){
            return RTI_FALSE;
        };
        if (!holo_base_msg_geometry_Point3fSeq_set_maximum(&sample->points, (100))) {
            return RTI_FALSE;
        }
    } else { 
        if(!holo_base_msg_geometry_Point3fSeq_set_length(&sample->points, 0)){
            return RTI_FALSE;
        }    
    }
    if (allocParams->allocate_memory) {
        if(!holo_base_msg_common_freespace3f_SegmentInfoSeq_initialize(&sample->boundaries )){
            return RTI_FALSE;
        };
        if (!holo_base_msg_common_freespace3f_SegmentInfoSeq_set_maximum(&sample->boundaries, (100))) {
            return RTI_FALSE;
        }
    } else { 
        if(!holo_base_msg_common_freespace3f_SegmentInfoSeq_set_length(&sample->boundaries, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_freespace3f_FreespaceInterior_finalize(
    holo_base_msg_common_freespace3f_FreespaceInterior* sample)
{

    holo_base_msg_common_freespace3f_FreespaceInterior_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_freespace3f_FreespaceInterior_finalize_w_return(
    holo_base_msg_common_freespace3f_FreespaceInterior* sample)
{

    holo_base_msg_common_freespace3f_FreespaceInterior_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_freespace3f_FreespaceInterior_finalize_ex(
    holo_base_msg_common_freespace3f_FreespaceInterior* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_freespace3f_FreespaceInterior_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_freespace3f_FreespaceInterior_finalize_w_params(
    holo_base_msg_common_freespace3f_FreespaceInterior* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!holo_base_msg_geometry_Point3fSeq_finalize(&sample->points)){
        return;
    }

    if(!holo_base_msg_common_freespace3f_SegmentInfoSeq_finalize(&sample->boundaries)){
        return;
    }

}

void holo_base_msg_common_freespace3f_FreespaceInterior_finalize_optional_members(
    holo_base_msg_common_freespace3f_FreespaceInterior* sample, RTIBool deletePointers)
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
            &sample->points);

        for (i = 0; i < length; i++) {
            holo_base_msg_geometry_Point3f_finalize_optional_members(
                holo_base_msg_geometry_Point3fSeq_get_reference(
                    &sample->points, (RTI_INT32)i), deallocParams->delete_pointers);
        }
    }  

    {
        DDS_UnsignedLong i, length;
        length = (RTI_UINT32)holo_base_msg_common_freespace3f_SegmentInfoSeq_get_length(
            &sample->boundaries);

        for (i = 0; i < length; i++) {
            holo_base_msg_common_freespace3f_SegmentInfo_finalize_optional_members(
                holo_base_msg_common_freespace3f_SegmentInfoSeq_get_reference(
                    &sample->boundaries, (RTI_INT32)i), deallocParams->delete_pointers);
        }
    }  

}

RTIBool holo_base_msg_common_freespace3f_FreespaceInterior_copy(
    holo_base_msg_common_freespace3f_FreespaceInterior* dst,
    const holo_base_msg_common_freespace3f_FreespaceInterior* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_geometry_Point3fSeq_copy(&dst->points ,
    &src->points  )) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_common_freespace3f_SegmentInfoSeq_copy(&dst->boundaries ,
    &src->boundaries  )) {
        return RTI_FALSE;
    }

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_freespace3f_FreespaceInterior' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_freespace3f_FreespaceInterior
#define TSeq holo_base_msg_common_freespace3f_FreespaceInteriorSeq

#define T_initialize holo_base_msg_common_freespace3f_FreespaceInterior_initialize

#define T_finalize   holo_base_msg_common_freespace3f_FreespaceInterior_finalize
#define T_copy       holo_base_msg_common_freespace3f_FreespaceInterior_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_freespace3f_FreespaceInterior
#define TSeq holo_base_msg_common_freespace3f_FreespaceInteriorSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_freespace3f_FreespaceExterior *
holo_base_msg_common_freespace3f_FreespaceExterior_create(void)
{
    holo_base_msg_common_freespace3f_FreespaceExterior* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_freespace3f_FreespaceExterior);
    if (sample != NULL) {
        if (!holo_base_msg_common_freespace3f_FreespaceExterior_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_freespace3f_FreespaceExterior_delete(holo_base_msg_common_freespace3f_FreespaceExterior*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_freespace3f_FreespaceExterior_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_freespace3f_FreespaceExterior_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_common_freespace3f_FreespaceExteriorTYPENAME = "holo_base_msg::common::freespace3f::FreespaceExterior";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_freespace3f_FreespaceExterior_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_common_freespace3f_FreespaceExterior_g_tc_points_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);
    static DDS_TypeCode holo_base_msg_common_freespace3f_FreespaceExterior_g_tc_boundaries_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);
    static DDS_TypeCode holo_base_msg_common_freespace3f_FreespaceExterior_g_tc_interiors_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode_Member holo_base_msg_common_freespace3f_FreespaceExterior_g_tc_members[3]=
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
            (char *)"boundaries",/* Member name */
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
            (char *)"interiors",/* Member name */
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

    static DDS_TypeCode holo_base_msg_common_freespace3f_FreespaceExterior_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::common::freespace3f::FreespaceExterior", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            3, /* Number of members */
            holo_base_msg_common_freespace3f_FreespaceExterior_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_common_freespace3f_FreespaceExterior*/

    if (is_initialized) {
        return &holo_base_msg_common_freespace3f_FreespaceExterior_g_tc;
    }

    holo_base_msg_common_freespace3f_FreespaceExterior_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_freespace3f_FreespaceExterior_g_tc_points_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Point3f_get_typecode();
    holo_base_msg_common_freespace3f_FreespaceExterior_g_tc_points_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_common_freespace3f_FreespaceExterior_g_tc_boundaries_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_common_freespace3f_SegmentInfo_get_typecode();
    holo_base_msg_common_freespace3f_FreespaceExterior_g_tc_boundaries_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_common_freespace3f_FreespaceExterior_g_tc_interiors_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_common_freespace3f_FreespaceInterior_get_typecode();
    holo_base_msg_common_freespace3f_FreespaceExterior_g_tc_interiors_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_common_freespace3f_FreespaceExterior_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)& holo_base_msg_common_freespace3f_FreespaceExterior_g_tc_points_sequence;
    holo_base_msg_common_freespace3f_FreespaceExterior_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)& holo_base_msg_common_freespace3f_FreespaceExterior_g_tc_boundaries_sequence;
    holo_base_msg_common_freespace3f_FreespaceExterior_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)& holo_base_msg_common_freespace3f_FreespaceExterior_g_tc_interiors_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_common_freespace3f_FreespaceExterior_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_freespace3f_FreespaceExterior_get_sample_access_info();
    holo_base_msg_common_freespace3f_FreespaceExterior_g_tc._data._typePlugin =
    holo_base_msg_common_freespace3f_FreespaceExterior_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_freespace3f_FreespaceExterior_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_freespace3f_FreespaceExterior_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_common_freespace3f_FreespaceExterior *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_freespace3f_FreespaceExterior_g_memberAccessInfos[3] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_freespace3f_FreespaceExterior_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_freespace3f_FreespaceExterior_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_common_freespace3f_FreespaceExterior);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_common_freespace3f_FreespaceExterior_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->points - (char *)sample);

    holo_base_msg_common_freespace3f_FreespaceExterior_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->boundaries - (char *)sample);

    holo_base_msg_common_freespace3f_FreespaceExterior_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->interiors - (char *)sample);

    holo_base_msg_common_freespace3f_FreespaceExterior_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_freespace3f_FreespaceExterior_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_freespace3f_FreespaceExterior);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_freespace3f_FreespaceExterior_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_freespace3f_FreespaceExterior_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_freespace3f_FreespaceExterior_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_freespace3f_FreespaceExterior_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_freespace3f_FreespaceExterior_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_freespace3f_FreespaceExterior_g_typePlugin = 
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
        holo_base_msg_common_freespace3f_FreespaceExterior_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_freespace3f_FreespaceExterior_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_freespace3f_FreespaceExterior_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_freespace3f_FreespaceExterior_initialize(
    holo_base_msg_common_freespace3f_FreespaceExterior* sample) {
    return holo_base_msg_common_freespace3f_FreespaceExterior_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_freespace3f_FreespaceExterior_initialize_ex(
    holo_base_msg_common_freespace3f_FreespaceExterior* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_freespace3f_FreespaceExterior_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_freespace3f_FreespaceExterior_initialize_w_params(
    holo_base_msg_common_freespace3f_FreespaceExterior* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!holo_base_msg_geometry_Point3fSeq_initialize(&sample->points )){
            return RTI_FALSE;
        };
        if (!holo_base_msg_geometry_Point3fSeq_set_maximum(&sample->points, (100))) {
            return RTI_FALSE;
        }
    } else { 
        if(!holo_base_msg_geometry_Point3fSeq_set_length(&sample->points, 0)){
            return RTI_FALSE;
        }    
    }
    if (allocParams->allocate_memory) {
        if(!holo_base_msg_common_freespace3f_SegmentInfoSeq_initialize(&sample->boundaries )){
            return RTI_FALSE;
        };
        if (!holo_base_msg_common_freespace3f_SegmentInfoSeq_set_maximum(&sample->boundaries, (100))) {
            return RTI_FALSE;
        }
    } else { 
        if(!holo_base_msg_common_freespace3f_SegmentInfoSeq_set_length(&sample->boundaries, 0)){
            return RTI_FALSE;
        }    
    }
    if (allocParams->allocate_memory) {
        if(!holo_base_msg_common_freespace3f_FreespaceInteriorSeq_initialize(&sample->interiors )){
            return RTI_FALSE;
        };
        if (!holo_base_msg_common_freespace3f_FreespaceInteriorSeq_set_maximum(&sample->interiors, (100))) {
            return RTI_FALSE;
        }
    } else { 
        if(!holo_base_msg_common_freespace3f_FreespaceInteriorSeq_set_length(&sample->interiors, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_freespace3f_FreespaceExterior_finalize(
    holo_base_msg_common_freespace3f_FreespaceExterior* sample)
{

    holo_base_msg_common_freespace3f_FreespaceExterior_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_freespace3f_FreespaceExterior_finalize_w_return(
    holo_base_msg_common_freespace3f_FreespaceExterior* sample)
{

    holo_base_msg_common_freespace3f_FreespaceExterior_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_freespace3f_FreespaceExterior_finalize_ex(
    holo_base_msg_common_freespace3f_FreespaceExterior* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_freespace3f_FreespaceExterior_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_freespace3f_FreespaceExterior_finalize_w_params(
    holo_base_msg_common_freespace3f_FreespaceExterior* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!holo_base_msg_geometry_Point3fSeq_finalize(&sample->points)){
        return;
    }

    if(!holo_base_msg_common_freespace3f_SegmentInfoSeq_finalize(&sample->boundaries)){
        return;
    }

    if(!holo_base_msg_common_freespace3f_FreespaceInteriorSeq_finalize(&sample->interiors)){
        return;
    }

}

void holo_base_msg_common_freespace3f_FreespaceExterior_finalize_optional_members(
    holo_base_msg_common_freespace3f_FreespaceExterior* sample, RTIBool deletePointers)
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
            &sample->points);

        for (i = 0; i < length; i++) {
            holo_base_msg_geometry_Point3f_finalize_optional_members(
                holo_base_msg_geometry_Point3fSeq_get_reference(
                    &sample->points, (RTI_INT32)i), deallocParams->delete_pointers);
        }
    }  

    {
        DDS_UnsignedLong i, length;
        length = (RTI_UINT32)holo_base_msg_common_freespace3f_SegmentInfoSeq_get_length(
            &sample->boundaries);

        for (i = 0; i < length; i++) {
            holo_base_msg_common_freespace3f_SegmentInfo_finalize_optional_members(
                holo_base_msg_common_freespace3f_SegmentInfoSeq_get_reference(
                    &sample->boundaries, (RTI_INT32)i), deallocParams->delete_pointers);
        }
    }  

    {
        DDS_UnsignedLong i, length;
        length = (RTI_UINT32)holo_base_msg_common_freespace3f_FreespaceInteriorSeq_get_length(
            &sample->interiors);

        for (i = 0; i < length; i++) {
            holo_base_msg_common_freespace3f_FreespaceInterior_finalize_optional_members(
                holo_base_msg_common_freespace3f_FreespaceInteriorSeq_get_reference(
                    &sample->interiors, (RTI_INT32)i), deallocParams->delete_pointers);
        }
    }  

}

RTIBool holo_base_msg_common_freespace3f_FreespaceExterior_copy(
    holo_base_msg_common_freespace3f_FreespaceExterior* dst,
    const holo_base_msg_common_freespace3f_FreespaceExterior* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_geometry_Point3fSeq_copy(&dst->points ,
    &src->points  )) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_common_freespace3f_SegmentInfoSeq_copy(&dst->boundaries ,
    &src->boundaries  )) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_common_freespace3f_FreespaceInteriorSeq_copy(&dst->interiors ,
    &src->interiors  )) {
        return RTI_FALSE;
    }

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_freespace3f_FreespaceExterior' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_freespace3f_FreespaceExterior
#define TSeq holo_base_msg_common_freespace3f_FreespaceExteriorSeq

#define T_initialize holo_base_msg_common_freespace3f_FreespaceExterior_initialize

#define T_finalize   holo_base_msg_common_freespace3f_FreespaceExterior_finalize
#define T_copy       holo_base_msg_common_freespace3f_FreespaceExterior_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_freespace3f_FreespaceExterior
#define TSeq holo_base_msg_common_freespace3f_FreespaceExteriorSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_freespace3f_Freespace *
holo_base_msg_common_freespace3f_Freespace_create(void)
{
    holo_base_msg_common_freespace3f_Freespace* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_freespace3f_Freespace);
    if (sample != NULL) {
        if (!holo_base_msg_common_freespace3f_Freespace_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_freespace3f_Freespace_delete(holo_base_msg_common_freespace3f_Freespace*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_freespace3f_Freespace_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_freespace3f_Freespace_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_common_freespace3f_FreespaceTYPENAME = "holo_base_msg::common::freespace3f::Freespace";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_freespace3f_Freespace_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_common_freespace3f_Freespace_g_tc_exteriors_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode_Member holo_base_msg_common_freespace3f_Freespace_g_tc_members[3]=
    {

        {
            (char *)"exteriors",/* Member name */
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
            (char *)"stamp",/* Member name */
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
            (char *)"coordinate",/* Member name */
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

    static DDS_TypeCode holo_base_msg_common_freespace3f_Freespace_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::common::freespace3f::Freespace", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            3, /* Number of members */
            holo_base_msg_common_freespace3f_Freespace_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_common_freespace3f_Freespace*/

    if (is_initialized) {
        return &holo_base_msg_common_freespace3f_Freespace_g_tc;
    }

    holo_base_msg_common_freespace3f_Freespace_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_freespace3f_Freespace_g_tc_exteriors_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_common_freespace3f_FreespaceExterior_get_typecode();
    holo_base_msg_common_freespace3f_Freespace_g_tc_exteriors_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_common_freespace3f_Freespace_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)& holo_base_msg_common_freespace3f_Freespace_g_tc_exteriors_sequence;
    holo_base_msg_common_freespace3f_Freespace_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_common_freespace3f_Freespace_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Coordinate_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_common_freespace3f_Freespace_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_freespace3f_Freespace_g_tc_members[2]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_freespace3f_Freespace_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_freespace3f_Freespace_g_tc_members[2]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_freespace3f_Freespace_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_freespace3f_Freespace_g_tc_members[2]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_freespace3f_Freespace_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_freespace3f_Freespace_get_sample_access_info();
    holo_base_msg_common_freespace3f_Freespace_g_tc._data._typePlugin =
    holo_base_msg_common_freespace3f_Freespace_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_freespace3f_Freespace_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_freespace3f_Freespace_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_common_freespace3f_Freespace *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_freespace3f_Freespace_g_memberAccessInfos[3] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_freespace3f_Freespace_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_freespace3f_Freespace_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_common_freespace3f_Freespace);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_common_freespace3f_Freespace_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->exteriors - (char *)sample);

    holo_base_msg_common_freespace3f_Freespace_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stamp - (char *)sample);

    holo_base_msg_common_freespace3f_Freespace_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->coordinate - (char *)sample);

    holo_base_msg_common_freespace3f_Freespace_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_freespace3f_Freespace_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_freespace3f_Freespace);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_freespace3f_Freespace_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_freespace3f_Freespace_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_freespace3f_Freespace_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_freespace3f_Freespace_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_freespace3f_Freespace_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_freespace3f_Freespace_g_typePlugin = 
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
        holo_base_msg_common_freespace3f_Freespace_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_freespace3f_Freespace_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_freespace3f_Freespace_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_freespace3f_Freespace_initialize(
    holo_base_msg_common_freespace3f_Freespace* sample) {
    return holo_base_msg_common_freespace3f_Freespace_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_freespace3f_Freespace_initialize_ex(
    holo_base_msg_common_freespace3f_Freespace* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_freespace3f_Freespace_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_freespace3f_Freespace_initialize_w_params(
    holo_base_msg_common_freespace3f_Freespace* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!holo_base_msg_common_freespace3f_FreespaceExteriorSeq_initialize(&sample->exteriors )){
            return RTI_FALSE;
        };
        if (!holo_base_msg_common_freespace3f_FreespaceExteriorSeq_set_maximum(&sample->exteriors, (100))) {
            return RTI_FALSE;
        }
    } else { 
        if(!holo_base_msg_common_freespace3f_FreespaceExteriorSeq_set_length(&sample->exteriors, 0)){
            return RTI_FALSE;
        }    
    }
    if (!holo_base_msg_common_Timestamp_initialize_w_params(&sample->stamp,
    allocParams)) {
        return RTI_FALSE;
    }

    sample->coordinate = 0u;

    return RTI_TRUE;
}

RTIBool holo_base_msg_common_freespace3f_Freespace_finalize(
    holo_base_msg_common_freespace3f_Freespace* sample)
{

    holo_base_msg_common_freespace3f_Freespace_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_freespace3f_Freespace_finalize_w_return(
    holo_base_msg_common_freespace3f_Freespace* sample)
{

    holo_base_msg_common_freespace3f_Freespace_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_freespace3f_Freespace_finalize_ex(
    holo_base_msg_common_freespace3f_Freespace* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_freespace3f_Freespace_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_freespace3f_Freespace_finalize_w_params(
    holo_base_msg_common_freespace3f_Freespace* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!holo_base_msg_common_freespace3f_FreespaceExteriorSeq_finalize(&sample->exteriors)){
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->stamp,deallocParams);

}

void holo_base_msg_common_freespace3f_Freespace_finalize_optional_members(
    holo_base_msg_common_freespace3f_Freespace* sample, RTIBool deletePointers)
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
        length = (RTI_UINT32)holo_base_msg_common_freespace3f_FreespaceExteriorSeq_get_length(
            &sample->exteriors);

        for (i = 0; i < length; i++) {
            holo_base_msg_common_freespace3f_FreespaceExterior_finalize_optional_members(
                holo_base_msg_common_freespace3f_FreespaceExteriorSeq_get_reference(
                    &sample->exteriors, (RTI_INT32)i), deallocParams->delete_pointers);
        }
    }  

    holo_base_msg_common_Timestamp_finalize_optional_members(&sample->stamp, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_common_freespace3f_Freespace_copy(
    holo_base_msg_common_freespace3f_Freespace* dst,
    const holo_base_msg_common_freespace3f_Freespace* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_freespace3f_FreespaceExteriorSeq_copy(&dst->exteriors ,
    &src->exteriors  )) {
        return RTI_FALSE;
    }
    if (!holo_base_msg_common_Timestamp_copy(
        &dst->stamp,(const holo_base_msg_common_Timestamp*)&src->stamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->coordinate, &src->coordinate);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_freespace3f_Freespace' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_freespace3f_Freespace
#define TSeq holo_base_msg_common_freespace3f_FreespaceSeq

#define T_initialize holo_base_msg_common_freespace3f_Freespace_initialize

#define T_finalize   holo_base_msg_common_freespace3f_Freespace_finalize
#define T_copy       holo_base_msg_common_freespace3f_Freespace_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_freespace3f_Freespace
#define TSeq holo_base_msg_common_freespace3f_FreespaceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

