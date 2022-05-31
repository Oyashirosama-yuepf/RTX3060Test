/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Box.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "Box.h"

#ifndef UNUSED_ARG
#define UNUSED_ARG(x) (void)(x)
#endif

#include "dds_c/dds_c_typecode.h"
/*** SOURCE_BEGIN ***/

holo_base_msg_geometry_Box2f *
holo_base_msg_geometry_Box2f_create(void)
{
    holo_base_msg_geometry_Box2f* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_geometry_Box2f);
    if (sample != NULL) {
        if (!holo_base_msg_geometry_Box2f_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_geometry_Box2f_delete(holo_base_msg_geometry_Box2f*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_geometry_Box2f_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_geometry_Box2f_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_geometry_Box2fTYPENAME = "holo_base_msg::geometry::Box2f";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_geometry_Box2f_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_geometry_Box2f_g_tc_members[3]=
    {

        {
            (char *)"width",/* Member name */
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
            (char *)"height",/* Member name */
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
            (char *)"pose",/* Member name */
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

    static DDS_TypeCode holo_base_msg_geometry_Box2f_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::geometry::Box2f", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            3, /* Number of members */
            holo_base_msg_geometry_Box2f_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_geometry_Box2f*/

    if (is_initialized) {
        return &holo_base_msg_geometry_Box2f_g_tc;
    }

    holo_base_msg_geometry_Box2f_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_geometry_Box2f_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_geometry_Box2f_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_geometry_Box2f_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Pose2f_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_geometry_Box2f_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_geometry_Box2f_g_tc_members[0]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_geometry_Box2f_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_geometry_Box2f_g_tc_members[0]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_geometry_Box2f_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_geometry_Box2f_g_tc_members[0]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_geometry_Box2f_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_geometry_Box2f_g_tc_members[1]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_geometry_Box2f_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_geometry_Box2f_g_tc_members[1]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_geometry_Box2f_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_geometry_Box2f_g_tc_members[1]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_geometry_Box2f_g_tc._data._sampleAccessInfo =
    holo_base_msg_geometry_Box2f_get_sample_access_info();
    holo_base_msg_geometry_Box2f_g_tc._data._typePlugin =
    holo_base_msg_geometry_Box2f_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_geometry_Box2f_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_geometry_Box2f_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_geometry_Box2f *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_geometry_Box2f_g_memberAccessInfos[3] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_geometry_Box2f_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_geometry_Box2f_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_geometry_Box2f);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_geometry_Box2f_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->width - (char *)sample);

    holo_base_msg_geometry_Box2f_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->height - (char *)sample);

    holo_base_msg_geometry_Box2f_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->pose - (char *)sample);

    holo_base_msg_geometry_Box2f_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_geometry_Box2f_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_geometry_Box2f);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_geometry_Box2f_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_geometry_Box2f_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_geometry_Box2f_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_geometry_Box2f_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_geometry_Box2f_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_geometry_Box2f_g_typePlugin = 
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
        holo_base_msg_geometry_Box2f_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_geometry_Box2f_finalize_w_return,
        NULL
    };

    return &holo_base_msg_geometry_Box2f_g_typePlugin;
}
#endif

RTIBool holo_base_msg_geometry_Box2f_initialize(
    holo_base_msg_geometry_Box2f* sample) {
    return holo_base_msg_geometry_Box2f_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_geometry_Box2f_initialize_ex(
    holo_base_msg_geometry_Box2f* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_geometry_Box2f_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_geometry_Box2f_initialize_w_params(
    holo_base_msg_geometry_Box2f* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->width = 0.0f;

    sample->height = 0.0f;

    if (!holo_base_msg_geometry_Pose2f_initialize_w_params(&sample->pose,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_geometry_Box2f_finalize(
    holo_base_msg_geometry_Box2f* sample)
{

    holo_base_msg_geometry_Box2f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_geometry_Box2f_finalize_w_return(
    holo_base_msg_geometry_Box2f* sample)
{

    holo_base_msg_geometry_Box2f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_geometry_Box2f_finalize_ex(
    holo_base_msg_geometry_Box2f* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_geometry_Box2f_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_geometry_Box2f_finalize_w_params(
    holo_base_msg_geometry_Box2f* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_geometry_Pose2f_finalize_w_params(&sample->pose,deallocParams);

}

void holo_base_msg_geometry_Box2f_finalize_optional_members(
    holo_base_msg_geometry_Box2f* sample, RTIBool deletePointers)
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

    holo_base_msg_geometry_Pose2f_finalize_optional_members(&sample->pose, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_geometry_Box2f_copy(
    holo_base_msg_geometry_Box2f* dst,
    const holo_base_msg_geometry_Box2f* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (&dst->width, &src->width);
    DDS_Primitive_copy (&dst->height, &src->height);
    if (!holo_base_msg_geometry_Pose2f_copy(
        &dst->pose,(const holo_base_msg_geometry_Pose2f*)&src->pose)) {
        return RTI_FALSE;
    } 

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_geometry_Box2f' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Box2f
#define TSeq holo_base_msg_geometry_Box2fSeq

#define T_initialize holo_base_msg_geometry_Box2f_initialize

#define T_finalize   holo_base_msg_geometry_Box2f_finalize
#define T_copy       holo_base_msg_geometry_Box2f_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Box2f
#define TSeq holo_base_msg_geometry_Box2fSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_geometry_Box2d *
holo_base_msg_geometry_Box2d_create(void)
{
    holo_base_msg_geometry_Box2d* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_geometry_Box2d);
    if (sample != NULL) {
        if (!holo_base_msg_geometry_Box2d_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_geometry_Box2d_delete(holo_base_msg_geometry_Box2d*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_geometry_Box2d_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_geometry_Box2d_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_geometry_Box2dTYPENAME = "holo_base_msg::geometry::Box2d";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_geometry_Box2d_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_geometry_Box2d_g_tc_members[3]=
    {

        {
            (char *)"width",/* Member name */
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
            (char *)"height",/* Member name */
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
            (char *)"pose",/* Member name */
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

    static DDS_TypeCode holo_base_msg_geometry_Box2d_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::geometry::Box2d", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            3, /* Number of members */
            holo_base_msg_geometry_Box2d_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_geometry_Box2d*/

    if (is_initialized) {
        return &holo_base_msg_geometry_Box2d_g_tc;
    }

    holo_base_msg_geometry_Box2d_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_geometry_Box2d_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();
    holo_base_msg_geometry_Box2d_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();
    holo_base_msg_geometry_Box2d_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Pose2d_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_geometry_Box2d_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_geometry_Box2d_g_tc_members[0]._annotations._defaultValue._u.double_value = 0.0;
    holo_base_msg_geometry_Box2d_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_geometry_Box2d_g_tc_members[0]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
    holo_base_msg_geometry_Box2d_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_geometry_Box2d_g_tc_members[0]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;

    holo_base_msg_geometry_Box2d_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_geometry_Box2d_g_tc_members[1]._annotations._defaultValue._u.double_value = 0.0;
    holo_base_msg_geometry_Box2d_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_geometry_Box2d_g_tc_members[1]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
    holo_base_msg_geometry_Box2d_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_geometry_Box2d_g_tc_members[1]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;

    holo_base_msg_geometry_Box2d_g_tc._data._sampleAccessInfo =
    holo_base_msg_geometry_Box2d_get_sample_access_info();
    holo_base_msg_geometry_Box2d_g_tc._data._typePlugin =
    holo_base_msg_geometry_Box2d_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_geometry_Box2d_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_geometry_Box2d_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_geometry_Box2d *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_geometry_Box2d_g_memberAccessInfos[3] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_geometry_Box2d_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_geometry_Box2d_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_geometry_Box2d);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_geometry_Box2d_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->width - (char *)sample);

    holo_base_msg_geometry_Box2d_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->height - (char *)sample);

    holo_base_msg_geometry_Box2d_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->pose - (char *)sample);

    holo_base_msg_geometry_Box2d_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_geometry_Box2d_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_geometry_Box2d);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_geometry_Box2d_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_geometry_Box2d_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_geometry_Box2d_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_geometry_Box2d_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_geometry_Box2d_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_geometry_Box2d_g_typePlugin = 
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
        holo_base_msg_geometry_Box2d_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_geometry_Box2d_finalize_w_return,
        NULL
    };

    return &holo_base_msg_geometry_Box2d_g_typePlugin;
}
#endif

RTIBool holo_base_msg_geometry_Box2d_initialize(
    holo_base_msg_geometry_Box2d* sample) {
    return holo_base_msg_geometry_Box2d_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_geometry_Box2d_initialize_ex(
    holo_base_msg_geometry_Box2d* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_geometry_Box2d_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_geometry_Box2d_initialize_w_params(
    holo_base_msg_geometry_Box2d* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->width = 0.0;

    sample->height = 0.0;

    if (!holo_base_msg_geometry_Pose2d_initialize_w_params(&sample->pose,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_geometry_Box2d_finalize(
    holo_base_msg_geometry_Box2d* sample)
{

    holo_base_msg_geometry_Box2d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_geometry_Box2d_finalize_w_return(
    holo_base_msg_geometry_Box2d* sample)
{

    holo_base_msg_geometry_Box2d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_geometry_Box2d_finalize_ex(
    holo_base_msg_geometry_Box2d* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_geometry_Box2d_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_geometry_Box2d_finalize_w_params(
    holo_base_msg_geometry_Box2d* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_geometry_Pose2d_finalize_w_params(&sample->pose,deallocParams);

}

void holo_base_msg_geometry_Box2d_finalize_optional_members(
    holo_base_msg_geometry_Box2d* sample, RTIBool deletePointers)
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

    holo_base_msg_geometry_Pose2d_finalize_optional_members(&sample->pose, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_geometry_Box2d_copy(
    holo_base_msg_geometry_Box2d* dst,
    const holo_base_msg_geometry_Box2d* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (&dst->width, &src->width);
    DDS_Primitive_copy (&dst->height, &src->height);
    if (!holo_base_msg_geometry_Pose2d_copy(
        &dst->pose,(const holo_base_msg_geometry_Pose2d*)&src->pose)) {
        return RTI_FALSE;
    } 

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_geometry_Box2d' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Box2d
#define TSeq holo_base_msg_geometry_Box2dSeq

#define T_initialize holo_base_msg_geometry_Box2d_initialize

#define T_finalize   holo_base_msg_geometry_Box2d_finalize
#define T_copy       holo_base_msg_geometry_Box2d_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Box2d
#define TSeq holo_base_msg_geometry_Box2dSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_geometry_Box3f *
holo_base_msg_geometry_Box3f_create(void)
{
    holo_base_msg_geometry_Box3f* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_geometry_Box3f);
    if (sample != NULL) {
        if (!holo_base_msg_geometry_Box3f_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_geometry_Box3f_delete(holo_base_msg_geometry_Box3f*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_geometry_Box3f_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_geometry_Box3f_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_geometry_Box3fTYPENAME = "holo_base_msg::geometry::Box3f";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_geometry_Box3f_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_geometry_Box3f_g_tc_members[4]=
    {

        {
            (char *)"width",/* Member name */
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
            (char *)"height",/* Member name */
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
            (char *)"depth",/* Member name */
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
            (char *)"pose",/* Member name */
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

    static DDS_TypeCode holo_base_msg_geometry_Box3f_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::geometry::Box3f", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            4, /* Number of members */
            holo_base_msg_geometry_Box3f_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_geometry_Box3f*/

    if (is_initialized) {
        return &holo_base_msg_geometry_Box3f_g_tc;
    }

    holo_base_msg_geometry_Box3f_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_geometry_Box3f_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_geometry_Box3f_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_geometry_Box3f_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_geometry_Box3f_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Pose3f_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_geometry_Box3f_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_geometry_Box3f_g_tc_members[0]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_geometry_Box3f_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_geometry_Box3f_g_tc_members[0]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_geometry_Box3f_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_geometry_Box3f_g_tc_members[0]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_geometry_Box3f_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_geometry_Box3f_g_tc_members[1]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_geometry_Box3f_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_geometry_Box3f_g_tc_members[1]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_geometry_Box3f_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_geometry_Box3f_g_tc_members[1]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_geometry_Box3f_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_geometry_Box3f_g_tc_members[2]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_geometry_Box3f_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_geometry_Box3f_g_tc_members[2]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_geometry_Box3f_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_geometry_Box3f_g_tc_members[2]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_geometry_Box3f_g_tc._data._sampleAccessInfo =
    holo_base_msg_geometry_Box3f_get_sample_access_info();
    holo_base_msg_geometry_Box3f_g_tc._data._typePlugin =
    holo_base_msg_geometry_Box3f_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_geometry_Box3f_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_geometry_Box3f_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_geometry_Box3f *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_geometry_Box3f_g_memberAccessInfos[4] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_geometry_Box3f_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_geometry_Box3f_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_geometry_Box3f);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_geometry_Box3f_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->width - (char *)sample);

    holo_base_msg_geometry_Box3f_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->height - (char *)sample);

    holo_base_msg_geometry_Box3f_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->depth - (char *)sample);

    holo_base_msg_geometry_Box3f_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->pose - (char *)sample);

    holo_base_msg_geometry_Box3f_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_geometry_Box3f_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_geometry_Box3f);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_geometry_Box3f_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_geometry_Box3f_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_geometry_Box3f_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_geometry_Box3f_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_geometry_Box3f_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_geometry_Box3f_g_typePlugin = 
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
        holo_base_msg_geometry_Box3f_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_geometry_Box3f_finalize_w_return,
        NULL
    };

    return &holo_base_msg_geometry_Box3f_g_typePlugin;
}
#endif

RTIBool holo_base_msg_geometry_Box3f_initialize(
    holo_base_msg_geometry_Box3f* sample) {
    return holo_base_msg_geometry_Box3f_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_geometry_Box3f_initialize_ex(
    holo_base_msg_geometry_Box3f* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_geometry_Box3f_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_geometry_Box3f_initialize_w_params(
    holo_base_msg_geometry_Box3f* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->width = 0.0f;

    sample->height = 0.0f;

    sample->depth = 0.0f;

    if (!holo_base_msg_geometry_Pose3f_initialize_w_params(&sample->pose,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_geometry_Box3f_finalize(
    holo_base_msg_geometry_Box3f* sample)
{

    holo_base_msg_geometry_Box3f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_geometry_Box3f_finalize_w_return(
    holo_base_msg_geometry_Box3f* sample)
{

    holo_base_msg_geometry_Box3f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_geometry_Box3f_finalize_ex(
    holo_base_msg_geometry_Box3f* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_geometry_Box3f_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_geometry_Box3f_finalize_w_params(
    holo_base_msg_geometry_Box3f* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_geometry_Pose3f_finalize_w_params(&sample->pose,deallocParams);

}

void holo_base_msg_geometry_Box3f_finalize_optional_members(
    holo_base_msg_geometry_Box3f* sample, RTIBool deletePointers)
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

    holo_base_msg_geometry_Pose3f_finalize_optional_members(&sample->pose, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_geometry_Box3f_copy(
    holo_base_msg_geometry_Box3f* dst,
    const holo_base_msg_geometry_Box3f* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (&dst->width, &src->width);
    DDS_Primitive_copy (&dst->height, &src->height);
    DDS_Primitive_copy (&dst->depth, &src->depth);
    if (!holo_base_msg_geometry_Pose3f_copy(
        &dst->pose,(const holo_base_msg_geometry_Pose3f*)&src->pose)) {
        return RTI_FALSE;
    } 

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_geometry_Box3f' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Box3f
#define TSeq holo_base_msg_geometry_Box3fSeq

#define T_initialize holo_base_msg_geometry_Box3f_initialize

#define T_finalize   holo_base_msg_geometry_Box3f_finalize
#define T_copy       holo_base_msg_geometry_Box3f_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Box3f
#define TSeq holo_base_msg_geometry_Box3fSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_geometry_Box3d *
holo_base_msg_geometry_Box3d_create(void)
{
    holo_base_msg_geometry_Box3d* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_geometry_Box3d);
    if (sample != NULL) {
        if (!holo_base_msg_geometry_Box3d_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_geometry_Box3d_delete(holo_base_msg_geometry_Box3d*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_geometry_Box3d_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_geometry_Box3d_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_geometry_Box3dTYPENAME = "holo_base_msg::geometry::Box3d";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_geometry_Box3d_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_geometry_Box3d_g_tc_members[4]=
    {

        {
            (char *)"width",/* Member name */
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
            (char *)"height",/* Member name */
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
            (char *)"depth",/* Member name */
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
            (char *)"pose",/* Member name */
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

    static DDS_TypeCode holo_base_msg_geometry_Box3d_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::geometry::Box3d", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            4, /* Number of members */
            holo_base_msg_geometry_Box3d_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_geometry_Box3d*/

    if (is_initialized) {
        return &holo_base_msg_geometry_Box3d_g_tc;
    }

    holo_base_msg_geometry_Box3d_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_geometry_Box3d_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();
    holo_base_msg_geometry_Box3d_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();
    holo_base_msg_geometry_Box3d_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();
    holo_base_msg_geometry_Box3d_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Pose3d_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_geometry_Box3d_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_geometry_Box3d_g_tc_members[0]._annotations._defaultValue._u.double_value = 0.0;
    holo_base_msg_geometry_Box3d_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_geometry_Box3d_g_tc_members[0]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
    holo_base_msg_geometry_Box3d_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_geometry_Box3d_g_tc_members[0]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;

    holo_base_msg_geometry_Box3d_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_geometry_Box3d_g_tc_members[1]._annotations._defaultValue._u.double_value = 0.0;
    holo_base_msg_geometry_Box3d_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_geometry_Box3d_g_tc_members[1]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
    holo_base_msg_geometry_Box3d_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_geometry_Box3d_g_tc_members[1]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;

    holo_base_msg_geometry_Box3d_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_geometry_Box3d_g_tc_members[2]._annotations._defaultValue._u.double_value = 0.0;
    holo_base_msg_geometry_Box3d_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_geometry_Box3d_g_tc_members[2]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
    holo_base_msg_geometry_Box3d_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_geometry_Box3d_g_tc_members[2]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;

    holo_base_msg_geometry_Box3d_g_tc._data._sampleAccessInfo =
    holo_base_msg_geometry_Box3d_get_sample_access_info();
    holo_base_msg_geometry_Box3d_g_tc._data._typePlugin =
    holo_base_msg_geometry_Box3d_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_geometry_Box3d_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_geometry_Box3d_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_geometry_Box3d *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_geometry_Box3d_g_memberAccessInfos[4] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_geometry_Box3d_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_geometry_Box3d_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_geometry_Box3d);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_geometry_Box3d_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->width - (char *)sample);

    holo_base_msg_geometry_Box3d_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->height - (char *)sample);

    holo_base_msg_geometry_Box3d_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->depth - (char *)sample);

    holo_base_msg_geometry_Box3d_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->pose - (char *)sample);

    holo_base_msg_geometry_Box3d_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_geometry_Box3d_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_geometry_Box3d);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_geometry_Box3d_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_geometry_Box3d_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_geometry_Box3d_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_geometry_Box3d_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_geometry_Box3d_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_geometry_Box3d_g_typePlugin = 
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
        holo_base_msg_geometry_Box3d_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_geometry_Box3d_finalize_w_return,
        NULL
    };

    return &holo_base_msg_geometry_Box3d_g_typePlugin;
}
#endif

RTIBool holo_base_msg_geometry_Box3d_initialize(
    holo_base_msg_geometry_Box3d* sample) {
    return holo_base_msg_geometry_Box3d_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_geometry_Box3d_initialize_ex(
    holo_base_msg_geometry_Box3d* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_geometry_Box3d_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_geometry_Box3d_initialize_w_params(
    holo_base_msg_geometry_Box3d* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->width = 0.0;

    sample->height = 0.0;

    sample->depth = 0.0;

    if (!holo_base_msg_geometry_Pose3d_initialize_w_params(&sample->pose,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_geometry_Box3d_finalize(
    holo_base_msg_geometry_Box3d* sample)
{

    holo_base_msg_geometry_Box3d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_geometry_Box3d_finalize_w_return(
    holo_base_msg_geometry_Box3d* sample)
{

    holo_base_msg_geometry_Box3d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_geometry_Box3d_finalize_ex(
    holo_base_msg_geometry_Box3d* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_geometry_Box3d_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_geometry_Box3d_finalize_w_params(
    holo_base_msg_geometry_Box3d* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_geometry_Pose3d_finalize_w_params(&sample->pose,deallocParams);

}

void holo_base_msg_geometry_Box3d_finalize_optional_members(
    holo_base_msg_geometry_Box3d* sample, RTIBool deletePointers)
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

    holo_base_msg_geometry_Pose3d_finalize_optional_members(&sample->pose, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_geometry_Box3d_copy(
    holo_base_msg_geometry_Box3d* dst,
    const holo_base_msg_geometry_Box3d* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (&dst->width, &src->width);
    DDS_Primitive_copy (&dst->height, &src->height);
    DDS_Primitive_copy (&dst->depth, &src->depth);
    if (!holo_base_msg_geometry_Pose3d_copy(
        &dst->pose,(const holo_base_msg_geometry_Pose3d*)&src->pose)) {
        return RTI_FALSE;
    } 

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_geometry_Box3d' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Box3d
#define TSeq holo_base_msg_geometry_Box3dSeq

#define T_initialize holo_base_msg_geometry_Box3d_initialize

#define T_finalize   holo_base_msg_geometry_Box3d_finalize
#define T_copy       holo_base_msg_geometry_Box3d_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Box3d
#define TSeq holo_base_msg_geometry_Box3dSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

