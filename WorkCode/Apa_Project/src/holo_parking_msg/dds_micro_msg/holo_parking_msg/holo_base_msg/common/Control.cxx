/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Control.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "Control.h"

#ifndef UNUSED_ARG
#define UNUSED_ARG(x) (void)(x)
#endif

#include "dds_c/dds_c_typecode.h"
/*** SOURCE_BEGIN ***/

holo_base_msg_common_ControlCommand *
holo_base_msg_common_ControlCommand_create(void)
{
    holo_base_msg_common_ControlCommand* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_ControlCommand);
    if (sample != NULL) {
        if (!holo_base_msg_common_ControlCommand_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_ControlCommand_delete(holo_base_msg_common_ControlCommand*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_ControlCommand_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_ControlCommand_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_common_ControlCommandTYPENAME = "holo_base_msg::common::ControlCommand";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_ControlCommand_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_common_ControlCommand_g_tc_members[7]=
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
            (char *)"acceleration",/* Member name */
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
            (char *)"front_wheel_angle",/* Member name */
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
            (char *)"light_control_command",/* Member name */
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
            (char *)"cockpit_control_command",/* Member name */
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
            (char *)"gear_control_command",/* Member name */
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
            (char *)"actuator_control_command",/* Member name */
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

    static DDS_TypeCode holo_base_msg_common_ControlCommand_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::common::ControlCommand", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            7, /* Number of members */
            holo_base_msg_common_ControlCommand_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_common_ControlCommand*/

    if (is_initialized) {
        return &holo_base_msg_common_ControlCommand_g_tc;
    }

    holo_base_msg_common_ControlCommand_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_ControlCommand_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_common_ControlCommand_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_ControlCommand_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_ControlCommand_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint16_t_get_typecode();
    holo_base_msg_common_ControlCommand_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint16_t_get_typecode();
    holo_base_msg_common_ControlCommand_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint8_t_get_typecode();
    holo_base_msg_common_ControlCommand_g_tc_members[6]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint8_t_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_common_ControlCommand_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ControlCommand_g_tc_members[1]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_ControlCommand_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ControlCommand_g_tc_members[1]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_ControlCommand_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ControlCommand_g_tc_members[1]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_ControlCommand_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ControlCommand_g_tc_members[2]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_ControlCommand_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ControlCommand_g_tc_members[2]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_ControlCommand_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ControlCommand_g_tc_members[2]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_ControlCommand_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
    holo_base_msg_common_ControlCommand_g_tc_members[3]._annotations._defaultValue._u.ushort_value = 0;
    holo_base_msg_common_ControlCommand_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
    holo_base_msg_common_ControlCommand_g_tc_members[3]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
    holo_base_msg_common_ControlCommand_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
    holo_base_msg_common_ControlCommand_g_tc_members[3]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

    holo_base_msg_common_ControlCommand_g_tc_members[4]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
    holo_base_msg_common_ControlCommand_g_tc_members[4]._annotations._defaultValue._u.ushort_value = 0;
    holo_base_msg_common_ControlCommand_g_tc_members[4]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
    holo_base_msg_common_ControlCommand_g_tc_members[4]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
    holo_base_msg_common_ControlCommand_g_tc_members[4]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
    holo_base_msg_common_ControlCommand_g_tc_members[4]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

    holo_base_msg_common_ControlCommand_g_tc_members[5]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_ControlCommand_g_tc_members[5]._annotations._defaultValue._u.octet_value = 0;
    holo_base_msg_common_ControlCommand_g_tc_members[5]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_ControlCommand_g_tc_members[5]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    holo_base_msg_common_ControlCommand_g_tc_members[5]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_ControlCommand_g_tc_members[5]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    holo_base_msg_common_ControlCommand_g_tc_members[6]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_ControlCommand_g_tc_members[6]._annotations._defaultValue._u.octet_value = 0;
    holo_base_msg_common_ControlCommand_g_tc_members[6]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_ControlCommand_g_tc_members[6]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    holo_base_msg_common_ControlCommand_g_tc_members[6]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_ControlCommand_g_tc_members[6]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    holo_base_msg_common_ControlCommand_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_ControlCommand_get_sample_access_info();
    holo_base_msg_common_ControlCommand_g_tc._data._typePlugin =
    holo_base_msg_common_ControlCommand_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_ControlCommand_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_ControlCommand_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_common_ControlCommand *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_ControlCommand_g_memberAccessInfos[7] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_ControlCommand_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_ControlCommand_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_common_ControlCommand);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_common_ControlCommand_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stamp - (char *)sample);

    holo_base_msg_common_ControlCommand_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->acceleration - (char *)sample);

    holo_base_msg_common_ControlCommand_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->front_wheel_angle - (char *)sample);

    holo_base_msg_common_ControlCommand_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->light_control_command - (char *)sample);

    holo_base_msg_common_ControlCommand_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->cockpit_control_command - (char *)sample);

    holo_base_msg_common_ControlCommand_g_memberAccessInfos[5].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->gear_control_command - (char *)sample);

    holo_base_msg_common_ControlCommand_g_memberAccessInfos[6].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->actuator_control_command - (char *)sample);

    holo_base_msg_common_ControlCommand_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_ControlCommand_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_ControlCommand);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_ControlCommand_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_ControlCommand_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_ControlCommand_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_ControlCommand_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_ControlCommand_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_ControlCommand_g_typePlugin = 
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
        holo_base_msg_common_ControlCommand_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_ControlCommand_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_ControlCommand_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_ControlCommand_initialize(
    holo_base_msg_common_ControlCommand* sample) {
    return holo_base_msg_common_ControlCommand_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_ControlCommand_initialize_ex(
    holo_base_msg_common_ControlCommand* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_ControlCommand_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_ControlCommand_initialize_w_params(
    holo_base_msg_common_ControlCommand* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

    sample->acceleration = 0.0f;

    sample->front_wheel_angle = 0.0f;

    sample->light_control_command = 0;

    sample->cockpit_control_command = 0;

    sample->gear_control_command = 0;

    sample->actuator_control_command = 0;

    return RTI_TRUE;
}

RTIBool holo_base_msg_common_ControlCommand_finalize(
    holo_base_msg_common_ControlCommand* sample)
{

    holo_base_msg_common_ControlCommand_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_ControlCommand_finalize_w_return(
    holo_base_msg_common_ControlCommand* sample)
{

    holo_base_msg_common_ControlCommand_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_ControlCommand_finalize_ex(
    holo_base_msg_common_ControlCommand* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_ControlCommand_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_ControlCommand_finalize_w_params(
    holo_base_msg_common_ControlCommand* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->stamp,deallocParams);

}

void holo_base_msg_common_ControlCommand_finalize_optional_members(
    holo_base_msg_common_ControlCommand* sample, RTIBool deletePointers)
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
}

RTIBool holo_base_msg_common_ControlCommand_copy(
    holo_base_msg_common_ControlCommand* dst,
    const holo_base_msg_common_ControlCommand* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_copy(
        &dst->stamp,(const holo_base_msg_common_Timestamp*)&src->stamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->acceleration, &src->acceleration);
    DDS_Primitive_copy (&dst->front_wheel_angle, &src->front_wheel_angle);
    DDS_Primitive_copy (&dst->light_control_command, &src->light_control_command);
    DDS_Primitive_copy (&dst->cockpit_control_command, &src->cockpit_control_command);
    DDS_Primitive_copy (&dst->gear_control_command, &src->gear_control_command);
    DDS_Primitive_copy (&dst->actuator_control_command, &src->actuator_control_command);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_ControlCommand' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ControlCommand
#define TSeq holo_base_msg_common_ControlCommandSeq

#define T_initialize holo_base_msg_common_ControlCommand_initialize

#define T_finalize   holo_base_msg_common_ControlCommand_finalize
#define T_copy       holo_base_msg_common_ControlCommand_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ControlCommand
#define TSeq holo_base_msg_common_ControlCommandSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

