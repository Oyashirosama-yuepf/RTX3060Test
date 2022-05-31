/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Path.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "Path.h"

#ifndef UNUSED_ARG
#define UNUSED_ARG(x) (void)(x)
#endif

#include "dds_c/dds_c_typecode.h"
/*** SOURCE_BEGIN ***/

holo_base_msg_common_PathPointf *
holo_base_msg_common_PathPointf_create(void)
{
    holo_base_msg_common_PathPointf* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_PathPointf);
    if (sample != NULL) {
        if (!holo_base_msg_common_PathPointf_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_PathPointf_delete(holo_base_msg_common_PathPointf*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_PathPointf_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_PathPointf_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_common_PathPointfTYPENAME = "holo_base_msg::common::PathPointf";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_PathPointf_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_common_PathPointf_g_tc_members[5]=
    {

        {
            (char *)"point",/* Member name */
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
            (char *)"theta",/* Member name */
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
            (char *)"curvature",/* Member name */
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
            (char *)"speed",/* Member name */
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
            (char *)"acceleration",/* Member name */
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

    static DDS_TypeCode holo_base_msg_common_PathPointf_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::common::PathPointf", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            5, /* Number of members */
            holo_base_msg_common_PathPointf_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_common_PathPointf*/

    if (is_initialized) {
        return &holo_base_msg_common_PathPointf_g_tc;
    }

    holo_base_msg_common_PathPointf_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_PathPointf_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Point3f_get_typecode();
    holo_base_msg_common_PathPointf_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_PathPointf_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_PathPointf_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_PathPointf_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_common_PathPointf_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathPointf_g_tc_members[1]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_PathPointf_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathPointf_g_tc_members[1]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_PathPointf_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathPointf_g_tc_members[1]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_PathPointf_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathPointf_g_tc_members[2]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_PathPointf_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathPointf_g_tc_members[2]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_PathPointf_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathPointf_g_tc_members[2]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_PathPointf_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathPointf_g_tc_members[3]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_PathPointf_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathPointf_g_tc_members[3]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_PathPointf_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathPointf_g_tc_members[3]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_PathPointf_g_tc_members[4]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathPointf_g_tc_members[4]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_PathPointf_g_tc_members[4]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathPointf_g_tc_members[4]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_PathPointf_g_tc_members[4]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathPointf_g_tc_members[4]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_PathPointf_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_PathPointf_get_sample_access_info();
    holo_base_msg_common_PathPointf_g_tc._data._typePlugin =
    holo_base_msg_common_PathPointf_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_PathPointf_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_PathPointf_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_common_PathPointf *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_PathPointf_g_memberAccessInfos[5] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_PathPointf_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_PathPointf_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_common_PathPointf);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_common_PathPointf_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->point - (char *)sample);

    holo_base_msg_common_PathPointf_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->theta - (char *)sample);

    holo_base_msg_common_PathPointf_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->curvature - (char *)sample);

    holo_base_msg_common_PathPointf_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->speed - (char *)sample);

    holo_base_msg_common_PathPointf_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->acceleration - (char *)sample);

    holo_base_msg_common_PathPointf_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_PathPointf_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_PathPointf);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_PathPointf_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_PathPointf_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_PathPointf_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_PathPointf_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_PathPointf_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_PathPointf_g_typePlugin = 
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
        holo_base_msg_common_PathPointf_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_PathPointf_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_PathPointf_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_PathPointf_initialize(
    holo_base_msg_common_PathPointf* sample) {
    return holo_base_msg_common_PathPointf_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_PathPointf_initialize_ex(
    holo_base_msg_common_PathPointf* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_PathPointf_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_PathPointf_initialize_w_params(
    holo_base_msg_common_PathPointf* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_geometry_Point3f_initialize_w_params(&sample->point,
    allocParams)) {
        return RTI_FALSE;
    }

    sample->theta = 0.0f;

    sample->curvature = 0.0f;

    sample->speed = 0.0f;

    sample->acceleration = 0.0f;

    return RTI_TRUE;
}

RTIBool holo_base_msg_common_PathPointf_finalize(
    holo_base_msg_common_PathPointf* sample)
{

    holo_base_msg_common_PathPointf_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_PathPointf_finalize_w_return(
    holo_base_msg_common_PathPointf* sample)
{

    holo_base_msg_common_PathPointf_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_PathPointf_finalize_ex(
    holo_base_msg_common_PathPointf* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_PathPointf_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_PathPointf_finalize_w_params(
    holo_base_msg_common_PathPointf* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_geometry_Point3f_finalize_w_params(&sample->point,deallocParams);

}

void holo_base_msg_common_PathPointf_finalize_optional_members(
    holo_base_msg_common_PathPointf* sample, RTIBool deletePointers)
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

    holo_base_msg_geometry_Point3f_finalize_optional_members(&sample->point, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_common_PathPointf_copy(
    holo_base_msg_common_PathPointf* dst,
    const holo_base_msg_common_PathPointf* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_geometry_Point3f_copy(
        &dst->point,(const holo_base_msg_geometry_Point3f*)&src->point)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->theta, &src->theta);
    DDS_Primitive_copy (&dst->curvature, &src->curvature);
    DDS_Primitive_copy (&dst->speed, &src->speed);
    DDS_Primitive_copy (&dst->acceleration, &src->acceleration);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_PathPointf' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PathPointf
#define TSeq holo_base_msg_common_PathPointfSeq

#define T_initialize holo_base_msg_common_PathPointf_initialize

#define T_finalize   holo_base_msg_common_PathPointf_finalize
#define T_copy       holo_base_msg_common_PathPointf_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PathPointf
#define TSeq holo_base_msg_common_PathPointfSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_PathPointd *
holo_base_msg_common_PathPointd_create(void)
{
    holo_base_msg_common_PathPointd* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_PathPointd);
    if (sample != NULL) {
        if (!holo_base_msg_common_PathPointd_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_PathPointd_delete(holo_base_msg_common_PathPointd*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_PathPointd_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_PathPointd_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_common_PathPointdTYPENAME = "holo_base_msg::common::PathPointd";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_PathPointd_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_common_PathPointd_g_tc_members[5]=
    {

        {
            (char *)"point",/* Member name */
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
            (char *)"theta",/* Member name */
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
            (char *)"curvature",/* Member name */
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
            (char *)"speed",/* Member name */
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
            (char *)"acceleration",/* Member name */
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

    static DDS_TypeCode holo_base_msg_common_PathPointd_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::common::PathPointd", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            5, /* Number of members */
            holo_base_msg_common_PathPointd_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_common_PathPointd*/

    if (is_initialized) {
        return &holo_base_msg_common_PathPointd_g_tc;
    }

    holo_base_msg_common_PathPointd_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_PathPointd_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Point3d_get_typecode();
    holo_base_msg_common_PathPointd_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();
    holo_base_msg_common_PathPointd_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();
    holo_base_msg_common_PathPointd_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();
    holo_base_msg_common_PathPointd_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_common_PathPointd_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_common_PathPointd_g_tc_members[1]._annotations._defaultValue._u.double_value = 0.0;
    holo_base_msg_common_PathPointd_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_common_PathPointd_g_tc_members[1]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
    holo_base_msg_common_PathPointd_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_common_PathPointd_g_tc_members[1]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;

    holo_base_msg_common_PathPointd_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_common_PathPointd_g_tc_members[2]._annotations._defaultValue._u.double_value = 0.0;
    holo_base_msg_common_PathPointd_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_common_PathPointd_g_tc_members[2]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
    holo_base_msg_common_PathPointd_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_common_PathPointd_g_tc_members[2]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;

    holo_base_msg_common_PathPointd_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_common_PathPointd_g_tc_members[3]._annotations._defaultValue._u.double_value = 0.0;
    holo_base_msg_common_PathPointd_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_common_PathPointd_g_tc_members[3]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
    holo_base_msg_common_PathPointd_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_common_PathPointd_g_tc_members[3]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;

    holo_base_msg_common_PathPointd_g_tc_members[4]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_common_PathPointd_g_tc_members[4]._annotations._defaultValue._u.double_value = 0.0;
    holo_base_msg_common_PathPointd_g_tc_members[4]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_common_PathPointd_g_tc_members[4]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
    holo_base_msg_common_PathPointd_g_tc_members[4]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_common_PathPointd_g_tc_members[4]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;

    holo_base_msg_common_PathPointd_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_PathPointd_get_sample_access_info();
    holo_base_msg_common_PathPointd_g_tc._data._typePlugin =
    holo_base_msg_common_PathPointd_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_PathPointd_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_PathPointd_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_common_PathPointd *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_PathPointd_g_memberAccessInfos[5] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_PathPointd_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_PathPointd_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_common_PathPointd);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_common_PathPointd_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->point - (char *)sample);

    holo_base_msg_common_PathPointd_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->theta - (char *)sample);

    holo_base_msg_common_PathPointd_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->curvature - (char *)sample);

    holo_base_msg_common_PathPointd_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->speed - (char *)sample);

    holo_base_msg_common_PathPointd_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->acceleration - (char *)sample);

    holo_base_msg_common_PathPointd_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_PathPointd_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_PathPointd);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_PathPointd_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_PathPointd_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_PathPointd_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_PathPointd_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_PathPointd_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_PathPointd_g_typePlugin = 
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
        holo_base_msg_common_PathPointd_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_PathPointd_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_PathPointd_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_PathPointd_initialize(
    holo_base_msg_common_PathPointd* sample) {
    return holo_base_msg_common_PathPointd_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_PathPointd_initialize_ex(
    holo_base_msg_common_PathPointd* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_PathPointd_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_PathPointd_initialize_w_params(
    holo_base_msg_common_PathPointd* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_geometry_Point3d_initialize_w_params(&sample->point,
    allocParams)) {
        return RTI_FALSE;
    }

    sample->theta = 0.0;

    sample->curvature = 0.0;

    sample->speed = 0.0;

    sample->acceleration = 0.0;

    return RTI_TRUE;
}

RTIBool holo_base_msg_common_PathPointd_finalize(
    holo_base_msg_common_PathPointd* sample)
{

    holo_base_msg_common_PathPointd_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_PathPointd_finalize_w_return(
    holo_base_msg_common_PathPointd* sample)
{

    holo_base_msg_common_PathPointd_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_PathPointd_finalize_ex(
    holo_base_msg_common_PathPointd* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_PathPointd_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_PathPointd_finalize_w_params(
    holo_base_msg_common_PathPointd* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_geometry_Point3d_finalize_w_params(&sample->point,deallocParams);

}

void holo_base_msg_common_PathPointd_finalize_optional_members(
    holo_base_msg_common_PathPointd* sample, RTIBool deletePointers)
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

    holo_base_msg_geometry_Point3d_finalize_optional_members(&sample->point, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_common_PathPointd_copy(
    holo_base_msg_common_PathPointd* dst,
    const holo_base_msg_common_PathPointd* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_geometry_Point3d_copy(
        &dst->point,(const holo_base_msg_geometry_Point3d*)&src->point)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->theta, &src->theta);
    DDS_Primitive_copy (&dst->curvature, &src->curvature);
    DDS_Primitive_copy (&dst->speed, &src->speed);
    DDS_Primitive_copy (&dst->acceleration, &src->acceleration);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_PathPointd' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PathPointd
#define TSeq holo_base_msg_common_PathPointdSeq

#define T_initialize holo_base_msg_common_PathPointd_initialize

#define T_finalize   holo_base_msg_common_PathPointd_finalize
#define T_copy       holo_base_msg_common_PathPointd_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PathPointd
#define TSeq holo_base_msg_common_PathPointdSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_PathPointfSequence *
holo_base_msg_common_PathPointfSequence_create(void)
{
    holo_base_msg_common_PathPointfSequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_PathPointfSequence);
    if (sample != NULL) {
        if (!holo_base_msg_common_PathPointfSequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_PathPointfSequence_delete(holo_base_msg_common_PathPointfSequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_PathPointfSequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_PathPointfSequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_PathPointfSequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_common_PathPointfSequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_common_PathPointfSequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::common::PathPointfSequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_common_PathPointfSequence */

    if (is_initialized) {
        return &holo_base_msg_common_PathPointfSequence_g_tc;
    }

    holo_base_msg_common_PathPointfSequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_PathPointfSequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_common_PathPointf_get_typecode();
    holo_base_msg_common_PathPointfSequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_common_PathPointfSequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_common_PathPointfSequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_common_PathPointfSequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_PathPointfSequence_get_sample_access_info();
    holo_base_msg_common_PathPointfSequence_g_tc._data._typePlugin =
    holo_base_msg_common_PathPointfSequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_PathPointfSequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_PathPointfSequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_PathPointfSequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_PathPointfSequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_PathPointfSequence_g_sampleAccessInfo;
    }

    holo_base_msg_common_PathPointfSequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_common_PathPointfSequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_PathPointfSequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_PathPointfSequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_PathPointfSequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_PathPointfSequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_PathPointfSequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_PathPointfSequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_PathPointfSequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_PathPointfSequence_g_typePlugin = 
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
        holo_base_msg_common_PathPointfSequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_PathPointfSequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_PathPointfSequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_PathPointfSequence_initialize(
    holo_base_msg_common_PathPointfSequence* sample) {
    return holo_base_msg_common_PathPointfSequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_PathPointfSequence_initialize_ex(
    holo_base_msg_common_PathPointfSequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_PathPointfSequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_PathPointfSequence_initialize_w_params(
    holo_base_msg_common_PathPointfSequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!holo_base_msg_common_PathPointfSeq_initialize(sample )){
            return RTI_FALSE;
        };
        if (!holo_base_msg_common_PathPointfSeq_set_maximum(sample, (100))) {
            return RTI_FALSE;
        }
    } else { 
        if(!holo_base_msg_common_PathPointfSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_PathPointfSequence_finalize(
    holo_base_msg_common_PathPointfSequence* sample)
{

    holo_base_msg_common_PathPointfSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_PathPointfSequence_finalize_w_return(
    holo_base_msg_common_PathPointfSequence* sample)
{

    holo_base_msg_common_PathPointfSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_PathPointfSequence_finalize_ex(
    holo_base_msg_common_PathPointfSequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_PathPointfSequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_PathPointfSequence_finalize_w_params(
    holo_base_msg_common_PathPointfSequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!holo_base_msg_common_PathPointfSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_common_PathPointfSequence_finalize_optional_members(
    holo_base_msg_common_PathPointfSequence* sample, RTIBool deletePointers)
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
        length = (RTI_UINT32)holo_base_msg_common_PathPointfSeq_get_length(
            sample);

        for (i = 0; i < length; i++) {
            holo_base_msg_common_PathPointf_finalize_optional_members(
                holo_base_msg_common_PathPointfSeq_get_reference(
                    sample, (RTI_INT32)i), deallocParams->delete_pointers);
        }
    }  

}

RTIBool holo_base_msg_common_PathPointfSequence_copy(
    holo_base_msg_common_PathPointfSequence* dst,
    const holo_base_msg_common_PathPointfSequence* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_PathPointfSeq_copy(dst ,
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
* Configure and implement 'holo_base_msg_common_PathPointfSequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PathPointfSequence
#define TSeq holo_base_msg_common_PathPointfSequenceSeq

#define T_initialize holo_base_msg_common_PathPointfSequence_initialize

#define T_finalize   holo_base_msg_common_PathPointfSequence_finalize
#define T_copy       holo_base_msg_common_PathPointfSequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PathPointfSequence
#define TSeq holo_base_msg_common_PathPointfSequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_PathPointdSequence *
holo_base_msg_common_PathPointdSequence_create(void)
{
    holo_base_msg_common_PathPointdSequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_PathPointdSequence);
    if (sample != NULL) {
        if (!holo_base_msg_common_PathPointdSequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_PathPointdSequence_delete(holo_base_msg_common_PathPointdSequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_PathPointdSequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_PathPointdSequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_PathPointdSequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_common_PathPointdSequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_common_PathPointdSequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::common::PathPointdSequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_common_PathPointdSequence */

    if (is_initialized) {
        return &holo_base_msg_common_PathPointdSequence_g_tc;
    }

    holo_base_msg_common_PathPointdSequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_PathPointdSequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_common_PathPointd_get_typecode();
    holo_base_msg_common_PathPointdSequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_common_PathPointdSequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_common_PathPointdSequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_common_PathPointdSequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_PathPointdSequence_get_sample_access_info();
    holo_base_msg_common_PathPointdSequence_g_tc._data._typePlugin =
    holo_base_msg_common_PathPointdSequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_PathPointdSequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_PathPointdSequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_PathPointdSequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_PathPointdSequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_PathPointdSequence_g_sampleAccessInfo;
    }

    holo_base_msg_common_PathPointdSequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_common_PathPointdSequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_PathPointdSequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_PathPointdSequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_PathPointdSequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_PathPointdSequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_PathPointdSequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_PathPointdSequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_PathPointdSequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_PathPointdSequence_g_typePlugin = 
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
        holo_base_msg_common_PathPointdSequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_PathPointdSequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_PathPointdSequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_PathPointdSequence_initialize(
    holo_base_msg_common_PathPointdSequence* sample) {
    return holo_base_msg_common_PathPointdSequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_PathPointdSequence_initialize_ex(
    holo_base_msg_common_PathPointdSequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_PathPointdSequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_PathPointdSequence_initialize_w_params(
    holo_base_msg_common_PathPointdSequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!holo_base_msg_common_PathPointdSeq_initialize(sample )){
            return RTI_FALSE;
        };
        if (!holo_base_msg_common_PathPointdSeq_set_maximum(sample, (100))) {
            return RTI_FALSE;
        }
    } else { 
        if(!holo_base_msg_common_PathPointdSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_PathPointdSequence_finalize(
    holo_base_msg_common_PathPointdSequence* sample)
{

    holo_base_msg_common_PathPointdSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_PathPointdSequence_finalize_w_return(
    holo_base_msg_common_PathPointdSequence* sample)
{

    holo_base_msg_common_PathPointdSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_PathPointdSequence_finalize_ex(
    holo_base_msg_common_PathPointdSequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_PathPointdSequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_PathPointdSequence_finalize_w_params(
    holo_base_msg_common_PathPointdSequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!holo_base_msg_common_PathPointdSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_common_PathPointdSequence_finalize_optional_members(
    holo_base_msg_common_PathPointdSequence* sample, RTIBool deletePointers)
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
        length = (RTI_UINT32)holo_base_msg_common_PathPointdSeq_get_length(
            sample);

        for (i = 0; i < length; i++) {
            holo_base_msg_common_PathPointd_finalize_optional_members(
                holo_base_msg_common_PathPointdSeq_get_reference(
                    sample, (RTI_INT32)i), deallocParams->delete_pointers);
        }
    }  

}

RTIBool holo_base_msg_common_PathPointdSequence_copy(
    holo_base_msg_common_PathPointdSequence* dst,
    const holo_base_msg_common_PathPointdSequence* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_PathPointdSeq_copy(dst ,
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
* Configure and implement 'holo_base_msg_common_PathPointdSequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PathPointdSequence
#define TSeq holo_base_msg_common_PathPointdSequenceSeq

#define T_initialize holo_base_msg_common_PathPointdSequence_initialize

#define T_finalize   holo_base_msg_common_PathPointdSequence_finalize
#define T_copy       holo_base_msg_common_PathPointdSequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PathPointdSequence
#define TSeq holo_base_msg_common_PathPointdSequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_Pathf *
holo_base_msg_common_Pathf_create(void)
{
    holo_base_msg_common_Pathf* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_Pathf);
    if (sample != NULL) {
        if (!holo_base_msg_common_Pathf_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_Pathf_delete(holo_base_msg_common_Pathf*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_Pathf_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_Pathf_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_common_PathfTYPENAME = "holo_base_msg::common::Pathf";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_Pathf_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_common_Pathf_g_tc_members[4]=
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
            (char *)"point_list",/* Member name */
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
            (char *)"valid_value",/* Member name */
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

    static DDS_TypeCode holo_base_msg_common_Pathf_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::common::Pathf", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            4, /* Number of members */
            holo_base_msg_common_Pathf_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_common_Pathf*/

    if (is_initialized) {
        return &holo_base_msg_common_Pathf_g_tc;
    }

    holo_base_msg_common_Pathf_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_Pathf_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_common_Pathf_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Coordinate_get_typecode();
    holo_base_msg_common_Pathf_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_PathPointfSequence_get_typecode();
    holo_base_msg_common_Pathf_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint32_t_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_common_Pathf_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Pathf_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_Pathf_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Pathf_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_Pathf_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Pathf_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_Pathf_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Pathf_g_tc_members[3]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_Pathf_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Pathf_g_tc_members[3]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_Pathf_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Pathf_g_tc_members[3]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_Pathf_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_Pathf_get_sample_access_info();
    holo_base_msg_common_Pathf_g_tc._data._typePlugin =
    holo_base_msg_common_Pathf_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_Pathf_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_Pathf_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_common_Pathf *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_Pathf_g_memberAccessInfos[4] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_Pathf_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_Pathf_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_common_Pathf);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_common_Pathf_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stamp - (char *)sample);

    holo_base_msg_common_Pathf_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->coord - (char *)sample);

    holo_base_msg_common_Pathf_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->point_list - (char *)sample);

    holo_base_msg_common_Pathf_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->valid_value - (char *)sample);

    holo_base_msg_common_Pathf_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_Pathf_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_Pathf);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_Pathf_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_Pathf_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_Pathf_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_Pathf_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_Pathf_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_Pathf_g_typePlugin = 
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
        holo_base_msg_common_Pathf_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_Pathf_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_Pathf_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_Pathf_initialize(
    holo_base_msg_common_Pathf* sample) {
    return holo_base_msg_common_Pathf_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_Pathf_initialize_ex(
    holo_base_msg_common_Pathf* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_Pathf_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_Pathf_initialize_w_params(
    holo_base_msg_common_Pathf* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

    if (!holo_base_msg_common_PathPointfSequence_initialize_w_params(&sample->point_list,
    allocParams)) {
        return RTI_FALSE;
    }

    sample->valid_value = 0u;

    return RTI_TRUE;
}

RTIBool holo_base_msg_common_Pathf_finalize(
    holo_base_msg_common_Pathf* sample)
{

    holo_base_msg_common_Pathf_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_Pathf_finalize_w_return(
    holo_base_msg_common_Pathf* sample)
{

    holo_base_msg_common_Pathf_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_Pathf_finalize_ex(
    holo_base_msg_common_Pathf* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_Pathf_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_Pathf_finalize_w_params(
    holo_base_msg_common_Pathf* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->stamp,deallocParams);

    holo_base_msg_common_PathPointfSequence_finalize_w_params(&sample->point_list,deallocParams);

}

void holo_base_msg_common_Pathf_finalize_optional_members(
    holo_base_msg_common_Pathf* sample, RTIBool deletePointers)
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
    holo_base_msg_common_PathPointfSequence_finalize_optional_members(&sample->point_list, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_common_Pathf_copy(
    holo_base_msg_common_Pathf* dst,
    const holo_base_msg_common_Pathf* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_copy(
        &dst->stamp,(const holo_base_msg_common_Timestamp*)&src->stamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->coord, &src->coord);
    if (!holo_base_msg_common_PathPointfSequence_copy(
        &dst->point_list,(const holo_base_msg_common_PathPointfSequence*)&src->point_list)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->valid_value, &src->valid_value);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_Pathf' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Pathf
#define TSeq holo_base_msg_common_PathfSeq

#define T_initialize holo_base_msg_common_Pathf_initialize

#define T_finalize   holo_base_msg_common_Pathf_finalize
#define T_copy       holo_base_msg_common_Pathf_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Pathf
#define TSeq holo_base_msg_common_PathfSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_Pathd *
holo_base_msg_common_Pathd_create(void)
{
    holo_base_msg_common_Pathd* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_Pathd);
    if (sample != NULL) {
        if (!holo_base_msg_common_Pathd_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_Pathd_delete(holo_base_msg_common_Pathd*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_Pathd_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_Pathd_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_common_PathdTYPENAME = "holo_base_msg::common::Pathd";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_Pathd_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_common_Pathd_g_tc_members[4]=
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
            (char *)"point_list",/* Member name */
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
            (char *)"valid_value",/* Member name */
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

    static DDS_TypeCode holo_base_msg_common_Pathd_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::common::Pathd", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            4, /* Number of members */
            holo_base_msg_common_Pathd_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_common_Pathd*/

    if (is_initialized) {
        return &holo_base_msg_common_Pathd_g_tc;
    }

    holo_base_msg_common_Pathd_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_Pathd_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_common_Pathd_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Coordinate_get_typecode();
    holo_base_msg_common_Pathd_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_PathPointdSequence_get_typecode();
    holo_base_msg_common_Pathd_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint32_t_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_common_Pathd_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Pathd_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_Pathd_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Pathd_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_Pathd_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Pathd_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_Pathd_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Pathd_g_tc_members[3]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_Pathd_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Pathd_g_tc_members[3]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_Pathd_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_Pathd_g_tc_members[3]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_Pathd_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_Pathd_get_sample_access_info();
    holo_base_msg_common_Pathd_g_tc._data._typePlugin =
    holo_base_msg_common_Pathd_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_Pathd_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_Pathd_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_common_Pathd *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_Pathd_g_memberAccessInfos[4] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_Pathd_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_Pathd_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_common_Pathd);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_common_Pathd_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stamp - (char *)sample);

    holo_base_msg_common_Pathd_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->coord - (char *)sample);

    holo_base_msg_common_Pathd_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->point_list - (char *)sample);

    holo_base_msg_common_Pathd_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->valid_value - (char *)sample);

    holo_base_msg_common_Pathd_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_Pathd_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_Pathd);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_Pathd_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_Pathd_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_Pathd_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_Pathd_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_Pathd_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_Pathd_g_typePlugin = 
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
        holo_base_msg_common_Pathd_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_Pathd_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_Pathd_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_Pathd_initialize(
    holo_base_msg_common_Pathd* sample) {
    return holo_base_msg_common_Pathd_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_Pathd_initialize_ex(
    holo_base_msg_common_Pathd* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_Pathd_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_Pathd_initialize_w_params(
    holo_base_msg_common_Pathd* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

    if (!holo_base_msg_common_PathPointdSequence_initialize_w_params(&sample->point_list,
    allocParams)) {
        return RTI_FALSE;
    }

    sample->valid_value = 0u;

    return RTI_TRUE;
}

RTIBool holo_base_msg_common_Pathd_finalize(
    holo_base_msg_common_Pathd* sample)
{

    holo_base_msg_common_Pathd_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_Pathd_finalize_w_return(
    holo_base_msg_common_Pathd* sample)
{

    holo_base_msg_common_Pathd_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_Pathd_finalize_ex(
    holo_base_msg_common_Pathd* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_Pathd_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_Pathd_finalize_w_params(
    holo_base_msg_common_Pathd* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->stamp,deallocParams);

    holo_base_msg_common_PathPointdSequence_finalize_w_params(&sample->point_list,deallocParams);

}

void holo_base_msg_common_Pathd_finalize_optional_members(
    holo_base_msg_common_Pathd* sample, RTIBool deletePointers)
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
    holo_base_msg_common_PathPointdSequence_finalize_optional_members(&sample->point_list, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_common_Pathd_copy(
    holo_base_msg_common_Pathd* dst,
    const holo_base_msg_common_Pathd* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_copy(
        &dst->stamp,(const holo_base_msg_common_Timestamp*)&src->stamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->coord, &src->coord);
    if (!holo_base_msg_common_PathPointdSequence_copy(
        &dst->point_list,(const holo_base_msg_common_PathPointdSequence*)&src->point_list)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->valid_value, &src->valid_value);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_Pathd' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Pathd
#define TSeq holo_base_msg_common_PathdSeq

#define T_initialize holo_base_msg_common_Pathd_initialize

#define T_finalize   holo_base_msg_common_Pathd_finalize
#define T_copy       holo_base_msg_common_Pathd_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Pathd
#define TSeq holo_base_msg_common_PathdSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

