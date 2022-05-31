/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from VehicleState.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "VehicleState.h"

#ifndef UNUSED_ARG
#define UNUSED_ARG(x) (void)(x)
#endif

#include "dds_c/dds_c_typecode.h"
/*** SOURCE_BEGIN ***/

holo_base_msg_common_ChassisState *
holo_base_msg_common_ChassisState_create(void)
{
    holo_base_msg_common_ChassisState* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_ChassisState);
    if (sample != NULL) {
        if (!holo_base_msg_common_ChassisState_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_ChassisState_delete(holo_base_msg_common_ChassisState*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_ChassisState_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_ChassisState_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_common_ChassisStateTYPENAME = "holo_base_msg::common::ChassisState";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_ChassisState_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_common_ChassisState_g_tc_members[16]=
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
            (char *)"vehicle_speed",/* Member name */
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
            (char *)"front_left_wheel_speed",/* Member name */
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
            (char *)"front_right_wheel_speed",/* Member name */
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
            (char *)"rear_left_wheel_speed",/* Member name */
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
            (char *)"rear_right_wheel_speed",/* Member name */
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
            (char *)"lon_acceleration",/* Member name */
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
            (char *)"lat_acceleration",/* Member name */
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
        }, 
        {
            (char *)"yaw_rate",/* Member name */
            {
                8,/* Representation ID */
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
                9,/* Representation ID */
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
            (char *)"longitudinal_control_value",/* Member name */
            {
                10,/* Representation ID */
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
            (char *)"energy_source_level",/* Member name */
            {
                11,/* Representation ID */
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
            (char *)"gear_pos",/* Member name */
            {
                12,/* Representation ID */
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
            (char *)"gear_level",/* Member name */
            {
                13,/* Representation ID */
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
            (char *)"state_flags",/* Member name */
            {
                14,/* Representation ID */
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
            (char *)"invalid_flags",/* Member name */
            {
                15,/* Representation ID */
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

    static DDS_TypeCode holo_base_msg_common_ChassisState_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::common::ChassisState", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            16, /* Number of members */
            holo_base_msg_common_ChassisState_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_common_ChassisState*/

    if (is_initialized) {
        return &holo_base_msg_common_ChassisState_g_tc;
    }

    holo_base_msg_common_ChassisState_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_ChassisState_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_common_ChassisState_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_ChassisState_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_ChassisState_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_ChassisState_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_ChassisState_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_ChassisState_g_tc_members[6]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_ChassisState_g_tc_members[7]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_ChassisState_g_tc_members[8]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_ChassisState_g_tc_members[9]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_ChassisState_g_tc_members[10]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_ChassisState_g_tc_members[11]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint8_t_get_typecode();
    holo_base_msg_common_ChassisState_g_tc_members[12]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint8_t_get_typecode();
    holo_base_msg_common_ChassisState_g_tc_members[13]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint8_t_get_typecode();
    holo_base_msg_common_ChassisState_g_tc_members[14]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint32_t_get_typecode();
    holo_base_msg_common_ChassisState_g_tc_members[15]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint32_t_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_common_ChassisState_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ChassisState_g_tc_members[1]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_ChassisState_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ChassisState_g_tc_members[1]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_ChassisState_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ChassisState_g_tc_members[1]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_ChassisState_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ChassisState_g_tc_members[2]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_ChassisState_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ChassisState_g_tc_members[2]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_ChassisState_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ChassisState_g_tc_members[2]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_ChassisState_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ChassisState_g_tc_members[3]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_ChassisState_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ChassisState_g_tc_members[3]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_ChassisState_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ChassisState_g_tc_members[3]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_ChassisState_g_tc_members[4]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ChassisState_g_tc_members[4]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_ChassisState_g_tc_members[4]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ChassisState_g_tc_members[4]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_ChassisState_g_tc_members[4]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ChassisState_g_tc_members[4]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_ChassisState_g_tc_members[5]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ChassisState_g_tc_members[5]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_ChassisState_g_tc_members[5]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ChassisState_g_tc_members[5]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_ChassisState_g_tc_members[5]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ChassisState_g_tc_members[5]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_ChassisState_g_tc_members[6]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ChassisState_g_tc_members[6]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_ChassisState_g_tc_members[6]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ChassisState_g_tc_members[6]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_ChassisState_g_tc_members[6]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ChassisState_g_tc_members[6]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_ChassisState_g_tc_members[7]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ChassisState_g_tc_members[7]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_ChassisState_g_tc_members[7]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ChassisState_g_tc_members[7]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_ChassisState_g_tc_members[7]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ChassisState_g_tc_members[7]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_ChassisState_g_tc_members[8]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ChassisState_g_tc_members[8]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_ChassisState_g_tc_members[8]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ChassisState_g_tc_members[8]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_ChassisState_g_tc_members[8]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ChassisState_g_tc_members[8]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_ChassisState_g_tc_members[9]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ChassisState_g_tc_members[9]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_ChassisState_g_tc_members[9]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ChassisState_g_tc_members[9]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_ChassisState_g_tc_members[9]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ChassisState_g_tc_members[9]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_ChassisState_g_tc_members[10]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ChassisState_g_tc_members[10]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_ChassisState_g_tc_members[10]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ChassisState_g_tc_members[10]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_ChassisState_g_tc_members[10]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ChassisState_g_tc_members[10]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_ChassisState_g_tc_members[11]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_ChassisState_g_tc_members[11]._annotations._defaultValue._u.octet_value = 0;
    holo_base_msg_common_ChassisState_g_tc_members[11]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_ChassisState_g_tc_members[11]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    holo_base_msg_common_ChassisState_g_tc_members[11]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_ChassisState_g_tc_members[11]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    holo_base_msg_common_ChassisState_g_tc_members[12]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_ChassisState_g_tc_members[12]._annotations._defaultValue._u.octet_value = 0;
    holo_base_msg_common_ChassisState_g_tc_members[12]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_ChassisState_g_tc_members[12]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    holo_base_msg_common_ChassisState_g_tc_members[12]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_ChassisState_g_tc_members[12]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    holo_base_msg_common_ChassisState_g_tc_members[13]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_ChassisState_g_tc_members[13]._annotations._defaultValue._u.octet_value = 0;
    holo_base_msg_common_ChassisState_g_tc_members[13]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_ChassisState_g_tc_members[13]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    holo_base_msg_common_ChassisState_g_tc_members[13]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_ChassisState_g_tc_members[13]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    holo_base_msg_common_ChassisState_g_tc_members[14]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ChassisState_g_tc_members[14]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_ChassisState_g_tc_members[14]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ChassisState_g_tc_members[14]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_ChassisState_g_tc_members[14]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ChassisState_g_tc_members[14]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_ChassisState_g_tc_members[15]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ChassisState_g_tc_members[15]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_ChassisState_g_tc_members[15]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ChassisState_g_tc_members[15]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_ChassisState_g_tc_members[15]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ChassisState_g_tc_members[15]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_ChassisState_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_ChassisState_get_sample_access_info();
    holo_base_msg_common_ChassisState_g_tc._data._typePlugin =
    holo_base_msg_common_ChassisState_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_ChassisState_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_ChassisState_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_common_ChassisState *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_ChassisState_g_memberAccessInfos[16] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_ChassisState_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_ChassisState_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_common_ChassisState);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_common_ChassisState_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stamp - (char *)sample);

    holo_base_msg_common_ChassisState_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->vehicle_speed - (char *)sample);

    holo_base_msg_common_ChassisState_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->front_left_wheel_speed - (char *)sample);

    holo_base_msg_common_ChassisState_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->front_right_wheel_speed - (char *)sample);

    holo_base_msg_common_ChassisState_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->rear_left_wheel_speed - (char *)sample);

    holo_base_msg_common_ChassisState_g_memberAccessInfos[5].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->rear_right_wheel_speed - (char *)sample);

    holo_base_msg_common_ChassisState_g_memberAccessInfos[6].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->lon_acceleration - (char *)sample);

    holo_base_msg_common_ChassisState_g_memberAccessInfos[7].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->lat_acceleration - (char *)sample);

    holo_base_msg_common_ChassisState_g_memberAccessInfos[8].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->yaw_rate - (char *)sample);

    holo_base_msg_common_ChassisState_g_memberAccessInfos[9].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->front_wheel_angle - (char *)sample);

    holo_base_msg_common_ChassisState_g_memberAccessInfos[10].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->longitudinal_control_value - (char *)sample);

    holo_base_msg_common_ChassisState_g_memberAccessInfos[11].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->energy_source_level - (char *)sample);

    holo_base_msg_common_ChassisState_g_memberAccessInfos[12].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->gear_pos - (char *)sample);

    holo_base_msg_common_ChassisState_g_memberAccessInfos[13].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->gear_level - (char *)sample);

    holo_base_msg_common_ChassisState_g_memberAccessInfos[14].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->state_flags - (char *)sample);

    holo_base_msg_common_ChassisState_g_memberAccessInfos[15].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->invalid_flags - (char *)sample);

    holo_base_msg_common_ChassisState_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_ChassisState_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_ChassisState);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_ChassisState_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_ChassisState_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_ChassisState_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_ChassisState_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_ChassisState_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_ChassisState_g_typePlugin = 
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
        holo_base_msg_common_ChassisState_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_ChassisState_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_ChassisState_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_ChassisState_initialize(
    holo_base_msg_common_ChassisState* sample) {
    return holo_base_msg_common_ChassisState_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_ChassisState_initialize_ex(
    holo_base_msg_common_ChassisState* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_ChassisState_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_ChassisState_initialize_w_params(
    holo_base_msg_common_ChassisState* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

    sample->vehicle_speed = 0.0f;

    sample->front_left_wheel_speed = 0.0f;

    sample->front_right_wheel_speed = 0.0f;

    sample->rear_left_wheel_speed = 0.0f;

    sample->rear_right_wheel_speed = 0.0f;

    sample->lon_acceleration = 0.0f;

    sample->lat_acceleration = 0.0f;

    sample->yaw_rate = 0.0f;

    sample->front_wheel_angle = 0.0f;

    sample->longitudinal_control_value = 0.0f;

    sample->energy_source_level = 0;

    sample->gear_pos = 0;

    sample->gear_level = 0;

    sample->state_flags = 0u;

    sample->invalid_flags = 0u;

    return RTI_TRUE;
}

RTIBool holo_base_msg_common_ChassisState_finalize(
    holo_base_msg_common_ChassisState* sample)
{

    holo_base_msg_common_ChassisState_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_ChassisState_finalize_w_return(
    holo_base_msg_common_ChassisState* sample)
{

    holo_base_msg_common_ChassisState_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_ChassisState_finalize_ex(
    holo_base_msg_common_ChassisState* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_ChassisState_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_ChassisState_finalize_w_params(
    holo_base_msg_common_ChassisState* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->stamp,deallocParams);

}

void holo_base_msg_common_ChassisState_finalize_optional_members(
    holo_base_msg_common_ChassisState* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_common_ChassisState_copy(
    holo_base_msg_common_ChassisState* dst,
    const holo_base_msg_common_ChassisState* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_copy(
        &dst->stamp,(const holo_base_msg_common_Timestamp*)&src->stamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->vehicle_speed, &src->vehicle_speed);
    DDS_Primitive_copy (&dst->front_left_wheel_speed, &src->front_left_wheel_speed);
    DDS_Primitive_copy (&dst->front_right_wheel_speed, &src->front_right_wheel_speed);
    DDS_Primitive_copy (&dst->rear_left_wheel_speed, &src->rear_left_wheel_speed);
    DDS_Primitive_copy (&dst->rear_right_wheel_speed, &src->rear_right_wheel_speed);
    DDS_Primitive_copy (&dst->lon_acceleration, &src->lon_acceleration);
    DDS_Primitive_copy (&dst->lat_acceleration, &src->lat_acceleration);
    DDS_Primitive_copy (&dst->yaw_rate, &src->yaw_rate);
    DDS_Primitive_copy (&dst->front_wheel_angle, &src->front_wheel_angle);
    DDS_Primitive_copy (&dst->longitudinal_control_value, &src->longitudinal_control_value);
    DDS_Primitive_copy (&dst->energy_source_level, &src->energy_source_level);
    DDS_Primitive_copy (&dst->gear_pos, &src->gear_pos);
    DDS_Primitive_copy (&dst->gear_level, &src->gear_level);
    DDS_Primitive_copy (&dst->state_flags, &src->state_flags);
    DDS_Primitive_copy (&dst->invalid_flags, &src->invalid_flags);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_ChassisState' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ChassisState
#define TSeq holo_base_msg_common_ChassisStateSeq

#define T_initialize holo_base_msg_common_ChassisState_initialize

#define T_finalize   holo_base_msg_common_ChassisState_finalize
#define T_copy       holo_base_msg_common_ChassisState_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ChassisState
#define TSeq holo_base_msg_common_ChassisStateSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_VehicleBodyState *
holo_base_msg_common_VehicleBodyState_create(void)
{
    holo_base_msg_common_VehicleBodyState* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_VehicleBodyState);
    if (sample != NULL) {
        if (!holo_base_msg_common_VehicleBodyState_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_VehicleBodyState_delete(holo_base_msg_common_VehicleBodyState*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_VehicleBodyState_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_VehicleBodyState_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_common_VehicleBodyStateTYPENAME = "holo_base_msg::common::VehicleBodyState";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_VehicleBodyState_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_common_VehicleBodyState_g_tc_members[7]=
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
            (char *)"front_left_tire_pressure",/* Member name */
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
            (char *)"front_right_tire_pressure",/* Member name */
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
            (char *)"rear_left_tire_pressure",/* Member name */
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
            (char *)"rear_right_tire_pressure",/* Member name */
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
            (char *)"state_flags",/* Member name */
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
            (char *)"invalid_flags",/* Member name */
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

    static DDS_TypeCode holo_base_msg_common_VehicleBodyState_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::common::VehicleBodyState", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            7, /* Number of members */
            holo_base_msg_common_VehicleBodyState_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_common_VehicleBodyState*/

    if (is_initialized) {
        return &holo_base_msg_common_VehicleBodyState_g_tc;
    }

    holo_base_msg_common_VehicleBodyState_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_VehicleBodyState_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_common_VehicleBodyState_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_VehicleBodyState_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_VehicleBodyState_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_VehicleBodyState_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_VehicleBodyState_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint32_t_get_typecode();
    holo_base_msg_common_VehicleBodyState_g_tc_members[6]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint32_t_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_common_VehicleBodyState_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehicleBodyState_g_tc_members[1]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_VehicleBodyState_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehicleBodyState_g_tc_members[1]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_VehicleBodyState_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehicleBodyState_g_tc_members[1]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_VehicleBodyState_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehicleBodyState_g_tc_members[2]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_VehicleBodyState_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehicleBodyState_g_tc_members[2]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_VehicleBodyState_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehicleBodyState_g_tc_members[2]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_VehicleBodyState_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehicleBodyState_g_tc_members[3]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_VehicleBodyState_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehicleBodyState_g_tc_members[3]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_VehicleBodyState_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehicleBodyState_g_tc_members[3]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_VehicleBodyState_g_tc_members[4]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehicleBodyState_g_tc_members[4]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_VehicleBodyState_g_tc_members[4]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehicleBodyState_g_tc_members[4]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_VehicleBodyState_g_tc_members[4]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_VehicleBodyState_g_tc_members[4]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_VehicleBodyState_g_tc_members[5]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_VehicleBodyState_g_tc_members[5]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_VehicleBodyState_g_tc_members[5]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_VehicleBodyState_g_tc_members[5]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_VehicleBodyState_g_tc_members[5]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_VehicleBodyState_g_tc_members[5]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_VehicleBodyState_g_tc_members[6]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_VehicleBodyState_g_tc_members[6]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_VehicleBodyState_g_tc_members[6]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_VehicleBodyState_g_tc_members[6]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_VehicleBodyState_g_tc_members[6]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_VehicleBodyState_g_tc_members[6]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_VehicleBodyState_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_VehicleBodyState_get_sample_access_info();
    holo_base_msg_common_VehicleBodyState_g_tc._data._typePlugin =
    holo_base_msg_common_VehicleBodyState_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_VehicleBodyState_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_VehicleBodyState_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_common_VehicleBodyState *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_VehicleBodyState_g_memberAccessInfos[7] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_VehicleBodyState_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_VehicleBodyState_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_common_VehicleBodyState);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_common_VehicleBodyState_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stamp - (char *)sample);

    holo_base_msg_common_VehicleBodyState_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->front_left_tire_pressure - (char *)sample);

    holo_base_msg_common_VehicleBodyState_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->front_right_tire_pressure - (char *)sample);

    holo_base_msg_common_VehicleBodyState_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->rear_left_tire_pressure - (char *)sample);

    holo_base_msg_common_VehicleBodyState_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->rear_right_tire_pressure - (char *)sample);

    holo_base_msg_common_VehicleBodyState_g_memberAccessInfos[5].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->state_flags - (char *)sample);

    holo_base_msg_common_VehicleBodyState_g_memberAccessInfos[6].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->invalid_flags - (char *)sample);

    holo_base_msg_common_VehicleBodyState_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_VehicleBodyState_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_VehicleBodyState);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_VehicleBodyState_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_VehicleBodyState_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_VehicleBodyState_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_VehicleBodyState_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_VehicleBodyState_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_VehicleBodyState_g_typePlugin = 
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
        holo_base_msg_common_VehicleBodyState_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_VehicleBodyState_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_VehicleBodyState_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_VehicleBodyState_initialize(
    holo_base_msg_common_VehicleBodyState* sample) {
    return holo_base_msg_common_VehicleBodyState_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_VehicleBodyState_initialize_ex(
    holo_base_msg_common_VehicleBodyState* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_VehicleBodyState_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_VehicleBodyState_initialize_w_params(
    holo_base_msg_common_VehicleBodyState* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

    sample->front_left_tire_pressure = 0.0f;

    sample->front_right_tire_pressure = 0.0f;

    sample->rear_left_tire_pressure = 0.0f;

    sample->rear_right_tire_pressure = 0.0f;

    sample->state_flags = 0u;

    sample->invalid_flags = 0u;

    return RTI_TRUE;
}

RTIBool holo_base_msg_common_VehicleBodyState_finalize(
    holo_base_msg_common_VehicleBodyState* sample)
{

    holo_base_msg_common_VehicleBodyState_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_VehicleBodyState_finalize_w_return(
    holo_base_msg_common_VehicleBodyState* sample)
{

    holo_base_msg_common_VehicleBodyState_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_VehicleBodyState_finalize_ex(
    holo_base_msg_common_VehicleBodyState* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_VehicleBodyState_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_VehicleBodyState_finalize_w_params(
    holo_base_msg_common_VehicleBodyState* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->stamp,deallocParams);

}

void holo_base_msg_common_VehicleBodyState_finalize_optional_members(
    holo_base_msg_common_VehicleBodyState* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_common_VehicleBodyState_copy(
    holo_base_msg_common_VehicleBodyState* dst,
    const holo_base_msg_common_VehicleBodyState* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_copy(
        &dst->stamp,(const holo_base_msg_common_Timestamp*)&src->stamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->front_left_tire_pressure, &src->front_left_tire_pressure);
    DDS_Primitive_copy (&dst->front_right_tire_pressure, &src->front_right_tire_pressure);
    DDS_Primitive_copy (&dst->rear_left_tire_pressure, &src->rear_left_tire_pressure);
    DDS_Primitive_copy (&dst->rear_right_tire_pressure, &src->rear_right_tire_pressure);
    DDS_Primitive_copy (&dst->state_flags, &src->state_flags);
    DDS_Primitive_copy (&dst->invalid_flags, &src->invalid_flags);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_VehicleBodyState' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_VehicleBodyState
#define TSeq holo_base_msg_common_VehicleBodyStateSeq

#define T_initialize holo_base_msg_common_VehicleBodyState_initialize

#define T_finalize   holo_base_msg_common_VehicleBodyState_finalize
#define T_copy       holo_base_msg_common_VehicleBodyState_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_VehicleBodyState
#define TSeq holo_base_msg_common_VehicleBodyStateSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

