/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from VehPos.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "VehPos.h"

#ifndef UNUSED_ARG
#define UNUSED_ARG(x) (void)(x)
#endif

#include "dds_c/dds_c_typecode.h"
/*** SOURCE_BEGIN ***/

holo_base_msg_common_VehPosX3V *
holo_base_msg_common_VehPosX3V_create(void)
{
    holo_base_msg_common_VehPosX3V* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_VehPosX3V);
    if (sample != NULL) {
        if (!holo_base_msg_common_VehPosX3V_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_VehPosX3V_delete(holo_base_msg_common_VehPosX3V*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_VehPosX3V_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_VehPosX3V_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_common_VehPosX3VTYPENAME = "holo_base_msg::common::VehPosX3V";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_VehPosX3V_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_common_VehPosX3V_g_tc_members[8]=
    {

        {
            (char *)"curv",/* Member name */
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
            (char *)"vehPos_X",/* Member name */
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
            (char *)"vehPos_Y",/* Member name */
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
            (char *)"vehPos_Yaw",/* Member name */
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
            (char *)"vehPosPred_X",/* Member name */
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
            (char *)"vehPosPred_Y",/* Member name */
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
            (char *)"vehPosPred_Yaw",/* Member name */
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
            (char *)"vehStatus",/* Member name */
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
        }
    };

    static DDS_TypeCode holo_base_msg_common_VehPosX3V_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::common::VehPosX3V", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            8, /* Number of members */
            holo_base_msg_common_VehPosX3V_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_common_VehPosX3V*/

    if (is_initialized) {
        return &holo_base_msg_common_VehPosX3V_g_tc;
    }

    holo_base_msg_common_VehPosX3V_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_VehPosX3V_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_VehPosX3V_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_VehPosX3V_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_VehPosX3V_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_VehPosX3V_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_VehPosX3V_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_VehPosX3V_g_tc_members[6]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_VehPosX3V_g_tc_members[7]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint8_t_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_common_VehPosX3V_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehPosX3V_g_tc_members[0]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_VehPosX3V_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehPosX3V_g_tc_members[0]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_VehPosX3V_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehPosX3V_g_tc_members[0]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_VehPosX3V_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehPosX3V_g_tc_members[1]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_VehPosX3V_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehPosX3V_g_tc_members[1]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_VehPosX3V_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehPosX3V_g_tc_members[1]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_VehPosX3V_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehPosX3V_g_tc_members[2]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_VehPosX3V_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehPosX3V_g_tc_members[2]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_VehPosX3V_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehPosX3V_g_tc_members[2]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_VehPosX3V_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehPosX3V_g_tc_members[3]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_VehPosX3V_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehPosX3V_g_tc_members[3]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_VehPosX3V_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehPosX3V_g_tc_members[3]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_VehPosX3V_g_tc_members[4]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehPosX3V_g_tc_members[4]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_VehPosX3V_g_tc_members[4]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehPosX3V_g_tc_members[4]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_VehPosX3V_g_tc_members[4]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehPosX3V_g_tc_members[4]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_VehPosX3V_g_tc_members[5]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehPosX3V_g_tc_members[5]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_VehPosX3V_g_tc_members[5]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehPosX3V_g_tc_members[5]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_VehPosX3V_g_tc_members[5]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehPosX3V_g_tc_members[5]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_VehPosX3V_g_tc_members[6]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehPosX3V_g_tc_members[6]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_VehPosX3V_g_tc_members[6]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehPosX3V_g_tc_members[6]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_VehPosX3V_g_tc_members[6]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehPosX3V_g_tc_members[6]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_VehPosX3V_g_tc_members[7]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_VehPosX3V_g_tc_members[7]._annotations._defaultValue._u.octet_value = 0;
    holo_base_msg_common_VehPosX3V_g_tc_members[7]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_VehPosX3V_g_tc_members[7]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    holo_base_msg_common_VehPosX3V_g_tc_members[7]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_VehPosX3V_g_tc_members[7]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    holo_base_msg_common_VehPosX3V_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_VehPosX3V_get_sample_access_info();
    holo_base_msg_common_VehPosX3V_g_tc._data._typePlugin =
    holo_base_msg_common_VehPosX3V_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_VehPosX3V_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_VehPosX3V_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_common_VehPosX3V *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_VehPosX3V_g_memberAccessInfos[8] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_VehPosX3V_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_VehPosX3V_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_common_VehPosX3V);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_common_VehPosX3V_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->curv - (char *)sample);

    holo_base_msg_common_VehPosX3V_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->vehPos_X - (char *)sample);

    holo_base_msg_common_VehPosX3V_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->vehPos_Y - (char *)sample);

    holo_base_msg_common_VehPosX3V_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->vehPos_Yaw - (char *)sample);

    holo_base_msg_common_VehPosX3V_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->vehPosPred_X - (char *)sample);

    holo_base_msg_common_VehPosX3V_g_memberAccessInfos[5].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->vehPosPred_Y - (char *)sample);

    holo_base_msg_common_VehPosX3V_g_memberAccessInfos[6].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->vehPosPred_Yaw - (char *)sample);

    holo_base_msg_common_VehPosX3V_g_memberAccessInfos[7].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->vehStatus - (char *)sample);

    holo_base_msg_common_VehPosX3V_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_VehPosX3V_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_VehPosX3V);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_VehPosX3V_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_VehPosX3V_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_VehPosX3V_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_VehPosX3V_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_VehPosX3V_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_VehPosX3V_g_typePlugin = 
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
        holo_base_msg_common_VehPosX3V_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_VehPosX3V_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_VehPosX3V_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_VehPosX3V_initialize(
    holo_base_msg_common_VehPosX3V* sample) {
    return holo_base_msg_common_VehPosX3V_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_VehPosX3V_initialize_ex(
    holo_base_msg_common_VehPosX3V* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_VehPosX3V_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_VehPosX3V_initialize_w_params(
    holo_base_msg_common_VehPosX3V* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->curv = 0.0f;

    sample->vehPos_X = 0.0f;

    sample->vehPos_Y = 0.0f;

    sample->vehPos_Yaw = 0.0f;

    sample->vehPosPred_X = 0.0f;

    sample->vehPosPred_Y = 0.0f;

    sample->vehPosPred_Yaw = 0.0f;

    sample->vehStatus = 0;

    return RTI_TRUE;
}

RTIBool holo_base_msg_common_VehPosX3V_finalize(
    holo_base_msg_common_VehPosX3V* sample)
{

    holo_base_msg_common_VehPosX3V_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_VehPosX3V_finalize_w_return(
    holo_base_msg_common_VehPosX3V* sample)
{

    holo_base_msg_common_VehPosX3V_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_VehPosX3V_finalize_ex(
    holo_base_msg_common_VehPosX3V* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_VehPosX3V_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_VehPosX3V_finalize_w_params(
    holo_base_msg_common_VehPosX3V* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_common_VehPosX3V_finalize_optional_members(
    holo_base_msg_common_VehPosX3V* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_common_VehPosX3V_copy(
    holo_base_msg_common_VehPosX3V* dst,
    const holo_base_msg_common_VehPosX3V* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (&dst->curv, &src->curv);
    DDS_Primitive_copy (&dst->vehPos_X, &src->vehPos_X);
    DDS_Primitive_copy (&dst->vehPos_Y, &src->vehPos_Y);
    DDS_Primitive_copy (&dst->vehPos_Yaw, &src->vehPos_Yaw);
    DDS_Primitive_copy (&dst->vehPosPred_X, &src->vehPosPred_X);
    DDS_Primitive_copy (&dst->vehPosPred_Y, &src->vehPosPred_Y);
    DDS_Primitive_copy (&dst->vehPosPred_Yaw, &src->vehPosPred_Yaw);
    DDS_Primitive_copy (&dst->vehStatus, &src->vehStatus);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_VehPosX3V' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_VehPosX3V
#define TSeq holo_base_msg_common_VehPosX3VSeq

#define T_initialize holo_base_msg_common_VehPosX3V_initialize

#define T_finalize   holo_base_msg_common_VehPosX3V_finalize
#define T_copy       holo_base_msg_common_VehPosX3V_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_VehPosX3V
#define TSeq holo_base_msg_common_VehPosX3VSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

