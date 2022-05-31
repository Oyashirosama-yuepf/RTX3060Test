/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from PathAttribute.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "PathAttribute.h"

#ifndef UNUSED_ARG
#define UNUSED_ARG(x) (void)(x)
#endif

#include "dds_c/dds_c_typecode.h"
/*** SOURCE_BEGIN ***/

holo_base_msg_common_PathAttribute *
holo_base_msg_common_PathAttribute_create(void)
{
    holo_base_msg_common_PathAttribute* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_PathAttribute);
    if (sample != NULL) {
        if (!holo_base_msg_common_PathAttribute_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_PathAttribute_delete(holo_base_msg_common_PathAttribute*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_PathAttribute_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_PathAttribute_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_common_PathAttributeTYPENAME = "holo_base_msg::common::PathAttribute";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_PathAttribute_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_common_PathAttribute_g_tc_members[17]=
    {

        {
            (char *)"timestamp",/* Member name */
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
            (char *)"path_gear",/* Member name */
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
            (char *)"path_id",/* Member name */
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
            (char *)"path_type",/* Member name */
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
            (char *)"path_size",/* Member name */
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
            (char *)"plan_complete",/* Member name */
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
            (char *)"plan_error",/* Member name */
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
            (char *)"path_len",/* Member name */
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
            (char *)"remain_path_len",/* Member name */
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
            (char *)"brk_flag",/* Member name */
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
            (char *)"brk_dist",/* Member name */
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
            (char *)"speed_limit",/* Member name */
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
            (char *)"lamp_req",/* Member name */
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
            (char *)"read_file_status",/* Member name */
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
            (char *)"ref_lat_error",/* Member name */
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
            (char *)"ref_heading_error",/* Member name */
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
        }, 
        {
            (char *)"road_curvature",/* Member name */
            {
                16,/* Representation ID */
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

    static DDS_TypeCode holo_base_msg_common_PathAttribute_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::common::PathAttribute", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            17, /* Number of members */
            holo_base_msg_common_PathAttribute_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_common_PathAttribute*/

    if (is_initialized) {
        return &holo_base_msg_common_PathAttribute_g_tc;
    }

    holo_base_msg_common_PathAttribute_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_PathAttribute_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_common_PathAttribute_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint8_t_get_typecode();
    holo_base_msg_common_PathAttribute_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint8_t_get_typecode();
    holo_base_msg_common_PathAttribute_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint8_t_get_typecode();
    holo_base_msg_common_PathAttribute_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint8_t_get_typecode();
    holo_base_msg_common_PathAttribute_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint8_t_get_typecode();
    holo_base_msg_common_PathAttribute_g_tc_members[6]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint8_t_get_typecode();
    holo_base_msg_common_PathAttribute_g_tc_members[7]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_PathAttribute_g_tc_members[8]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_PathAttribute_g_tc_members[9]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint8_t_get_typecode();
    holo_base_msg_common_PathAttribute_g_tc_members[10]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_PathAttribute_g_tc_members[11]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_PathAttribute_g_tc_members[12]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint8_t_get_typecode();
    holo_base_msg_common_PathAttribute_g_tc_members[13]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint8_t_get_typecode();
    holo_base_msg_common_PathAttribute_g_tc_members[14]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_PathAttribute_g_tc_members[15]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_PathAttribute_g_tc_members[16]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_common_PathAttribute_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PathAttribute_g_tc_members[1]._annotations._defaultValue._u.octet_value = 0;
    holo_base_msg_common_PathAttribute_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PathAttribute_g_tc_members[1]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    holo_base_msg_common_PathAttribute_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PathAttribute_g_tc_members[1]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    holo_base_msg_common_PathAttribute_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PathAttribute_g_tc_members[2]._annotations._defaultValue._u.octet_value = 0;
    holo_base_msg_common_PathAttribute_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PathAttribute_g_tc_members[2]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    holo_base_msg_common_PathAttribute_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PathAttribute_g_tc_members[2]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    holo_base_msg_common_PathAttribute_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PathAttribute_g_tc_members[3]._annotations._defaultValue._u.octet_value = 0;
    holo_base_msg_common_PathAttribute_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PathAttribute_g_tc_members[3]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    holo_base_msg_common_PathAttribute_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PathAttribute_g_tc_members[3]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    holo_base_msg_common_PathAttribute_g_tc_members[4]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PathAttribute_g_tc_members[4]._annotations._defaultValue._u.octet_value = 0;
    holo_base_msg_common_PathAttribute_g_tc_members[4]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PathAttribute_g_tc_members[4]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    holo_base_msg_common_PathAttribute_g_tc_members[4]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PathAttribute_g_tc_members[4]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    holo_base_msg_common_PathAttribute_g_tc_members[5]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PathAttribute_g_tc_members[5]._annotations._defaultValue._u.octet_value = 0;
    holo_base_msg_common_PathAttribute_g_tc_members[5]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PathAttribute_g_tc_members[5]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    holo_base_msg_common_PathAttribute_g_tc_members[5]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PathAttribute_g_tc_members[5]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    holo_base_msg_common_PathAttribute_g_tc_members[6]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PathAttribute_g_tc_members[6]._annotations._defaultValue._u.octet_value = 0;
    holo_base_msg_common_PathAttribute_g_tc_members[6]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PathAttribute_g_tc_members[6]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    holo_base_msg_common_PathAttribute_g_tc_members[6]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PathAttribute_g_tc_members[6]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    holo_base_msg_common_PathAttribute_g_tc_members[7]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathAttribute_g_tc_members[7]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_PathAttribute_g_tc_members[7]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathAttribute_g_tc_members[7]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_PathAttribute_g_tc_members[7]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathAttribute_g_tc_members[7]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_PathAttribute_g_tc_members[8]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathAttribute_g_tc_members[8]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_PathAttribute_g_tc_members[8]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathAttribute_g_tc_members[8]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_PathAttribute_g_tc_members[8]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathAttribute_g_tc_members[8]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_PathAttribute_g_tc_members[9]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PathAttribute_g_tc_members[9]._annotations._defaultValue._u.octet_value = 0;
    holo_base_msg_common_PathAttribute_g_tc_members[9]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PathAttribute_g_tc_members[9]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    holo_base_msg_common_PathAttribute_g_tc_members[9]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PathAttribute_g_tc_members[9]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    holo_base_msg_common_PathAttribute_g_tc_members[10]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathAttribute_g_tc_members[10]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_PathAttribute_g_tc_members[10]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathAttribute_g_tc_members[10]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_PathAttribute_g_tc_members[10]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathAttribute_g_tc_members[10]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_PathAttribute_g_tc_members[11]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathAttribute_g_tc_members[11]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_PathAttribute_g_tc_members[11]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathAttribute_g_tc_members[11]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_PathAttribute_g_tc_members[11]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathAttribute_g_tc_members[11]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_PathAttribute_g_tc_members[12]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PathAttribute_g_tc_members[12]._annotations._defaultValue._u.octet_value = 0;
    holo_base_msg_common_PathAttribute_g_tc_members[12]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PathAttribute_g_tc_members[12]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    holo_base_msg_common_PathAttribute_g_tc_members[12]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PathAttribute_g_tc_members[12]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    holo_base_msg_common_PathAttribute_g_tc_members[13]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PathAttribute_g_tc_members[13]._annotations._defaultValue._u.octet_value = 0;
    holo_base_msg_common_PathAttribute_g_tc_members[13]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PathAttribute_g_tc_members[13]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    holo_base_msg_common_PathAttribute_g_tc_members[13]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_common_PathAttribute_g_tc_members[13]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    holo_base_msg_common_PathAttribute_g_tc_members[14]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathAttribute_g_tc_members[14]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_PathAttribute_g_tc_members[14]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathAttribute_g_tc_members[14]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_PathAttribute_g_tc_members[14]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathAttribute_g_tc_members[14]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_PathAttribute_g_tc_members[15]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathAttribute_g_tc_members[15]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_PathAttribute_g_tc_members[15]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathAttribute_g_tc_members[15]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_PathAttribute_g_tc_members[15]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathAttribute_g_tc_members[15]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_PathAttribute_g_tc_members[16]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathAttribute_g_tc_members[16]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_PathAttribute_g_tc_members[16]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathAttribute_g_tc_members[16]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_PathAttribute_g_tc_members[16]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_PathAttribute_g_tc_members[16]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_PathAttribute_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_PathAttribute_get_sample_access_info();
    holo_base_msg_common_PathAttribute_g_tc._data._typePlugin =
    holo_base_msg_common_PathAttribute_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_PathAttribute_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_PathAttribute_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_common_PathAttribute *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_PathAttribute_g_memberAccessInfos[17] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_PathAttribute_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_PathAttribute_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_common_PathAttribute);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_common_PathAttribute_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->timestamp - (char *)sample);

    holo_base_msg_common_PathAttribute_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->path_gear - (char *)sample);

    holo_base_msg_common_PathAttribute_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->path_id - (char *)sample);

    holo_base_msg_common_PathAttribute_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->path_type - (char *)sample);

    holo_base_msg_common_PathAttribute_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->path_size - (char *)sample);

    holo_base_msg_common_PathAttribute_g_memberAccessInfos[5].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->plan_complete - (char *)sample);

    holo_base_msg_common_PathAttribute_g_memberAccessInfos[6].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->plan_error - (char *)sample);

    holo_base_msg_common_PathAttribute_g_memberAccessInfos[7].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->path_len - (char *)sample);

    holo_base_msg_common_PathAttribute_g_memberAccessInfos[8].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->remain_path_len - (char *)sample);

    holo_base_msg_common_PathAttribute_g_memberAccessInfos[9].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->brk_flag - (char *)sample);

    holo_base_msg_common_PathAttribute_g_memberAccessInfos[10].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->brk_dist - (char *)sample);

    holo_base_msg_common_PathAttribute_g_memberAccessInfos[11].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->speed_limit - (char *)sample);

    holo_base_msg_common_PathAttribute_g_memberAccessInfos[12].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->lamp_req - (char *)sample);

    holo_base_msg_common_PathAttribute_g_memberAccessInfos[13].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->read_file_status - (char *)sample);

    holo_base_msg_common_PathAttribute_g_memberAccessInfos[14].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->ref_lat_error - (char *)sample);

    holo_base_msg_common_PathAttribute_g_memberAccessInfos[15].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->ref_heading_error - (char *)sample);

    holo_base_msg_common_PathAttribute_g_memberAccessInfos[16].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->road_curvature - (char *)sample);

    holo_base_msg_common_PathAttribute_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_PathAttribute_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_PathAttribute);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_PathAttribute_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_PathAttribute_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_PathAttribute_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_PathAttribute_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_PathAttribute_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_PathAttribute_g_typePlugin = 
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
        holo_base_msg_common_PathAttribute_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_PathAttribute_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_PathAttribute_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_PathAttribute_initialize(
    holo_base_msg_common_PathAttribute* sample) {
    return holo_base_msg_common_PathAttribute_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_PathAttribute_initialize_ex(
    holo_base_msg_common_PathAttribute* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_PathAttribute_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_PathAttribute_initialize_w_params(
    holo_base_msg_common_PathAttribute* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_initialize_w_params(&sample->timestamp,
    allocParams)) {
        return RTI_FALSE;
    }

    sample->path_gear = 0;

    sample->path_id = 0;

    sample->path_type = 0;

    sample->path_size = 0;

    sample->plan_complete = 0;

    sample->plan_error = 0;

    sample->path_len = 0.0f;

    sample->remain_path_len = 0.0f;

    sample->brk_flag = 0;

    sample->brk_dist = 0.0f;

    sample->speed_limit = 0.0f;

    sample->lamp_req = 0;

    sample->read_file_status = 0;

    sample->ref_lat_error = 0.0f;

    sample->ref_heading_error = 0.0f;

    sample->road_curvature = 0.0f;

    return RTI_TRUE;
}

RTIBool holo_base_msg_common_PathAttribute_finalize(
    holo_base_msg_common_PathAttribute* sample)
{

    holo_base_msg_common_PathAttribute_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_PathAttribute_finalize_w_return(
    holo_base_msg_common_PathAttribute* sample)
{

    holo_base_msg_common_PathAttribute_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_PathAttribute_finalize_ex(
    holo_base_msg_common_PathAttribute* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_PathAttribute_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_PathAttribute_finalize_w_params(
    holo_base_msg_common_PathAttribute* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->timestamp,deallocParams);

}

void holo_base_msg_common_PathAttribute_finalize_optional_members(
    holo_base_msg_common_PathAttribute* sample, RTIBool deletePointers)
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

    holo_base_msg_common_Timestamp_finalize_optional_members(&sample->timestamp, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_common_PathAttribute_copy(
    holo_base_msg_common_PathAttribute* dst,
    const holo_base_msg_common_PathAttribute* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_copy(
        &dst->timestamp,(const holo_base_msg_common_Timestamp*)&src->timestamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->path_gear, &src->path_gear);
    DDS_Primitive_copy (&dst->path_id, &src->path_id);
    DDS_Primitive_copy (&dst->path_type, &src->path_type);
    DDS_Primitive_copy (&dst->path_size, &src->path_size);
    DDS_Primitive_copy (&dst->plan_complete, &src->plan_complete);
    DDS_Primitive_copy (&dst->plan_error, &src->plan_error);
    DDS_Primitive_copy (&dst->path_len, &src->path_len);
    DDS_Primitive_copy (&dst->remain_path_len, &src->remain_path_len);
    DDS_Primitive_copy (&dst->brk_flag, &src->brk_flag);
    DDS_Primitive_copy (&dst->brk_dist, &src->brk_dist);
    DDS_Primitive_copy (&dst->speed_limit, &src->speed_limit);
    DDS_Primitive_copy (&dst->lamp_req, &src->lamp_req);
    DDS_Primitive_copy (&dst->read_file_status, &src->read_file_status);
    DDS_Primitive_copy (&dst->ref_lat_error, &src->ref_lat_error);
    DDS_Primitive_copy (&dst->ref_heading_error, &src->ref_heading_error);
    DDS_Primitive_copy (&dst->road_curvature, &src->road_curvature);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_PathAttribute' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PathAttribute
#define TSeq holo_base_msg_common_PathAttributeSeq

#define T_initialize holo_base_msg_common_PathAttribute_initialize

#define T_finalize   holo_base_msg_common_PathAttribute_finalize
#define T_copy       holo_base_msg_common_PathAttribute_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PathAttribute
#define TSeq holo_base_msg_common_PathAttributeSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

