/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ParkingSlot.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "ParkingSlot.h"

#ifndef UNUSED_ARG
#define UNUSED_ARG(x) (void)(x)
#endif

#include "dds_c/dds_c_typecode.h"
/*** SOURCE_BEGIN ***/

holo_base_msg_common_ParkingSlotf *
holo_base_msg_common_ParkingSlotf_create(void)
{
    holo_base_msg_common_ParkingSlotf* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_ParkingSlotf);
    if (sample != NULL) {
        if (!holo_base_msg_common_ParkingSlotf_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_ParkingSlotf_delete(holo_base_msg_common_ParkingSlotf*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_ParkingSlotf_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_ParkingSlotf_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_common_ParkingSlotfTYPENAME = "holo_base_msg::common::ParkingSlotf";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_ParkingSlotf_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_common_ParkingSlotf_g_tc_members[15]=
    {

        {
            (char *)"id",/* Member name */
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
            (char *)"is_valid",/* Member name */
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
        }, 
        {
            (char *)"position",/* Member name */
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
            (char *)"status",/* Member name */
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
            (char *)"width",/* Member name */
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
            (char *)"height",/* Member name */
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
            (char *)"angle",/* Member name */
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
            (char *)"confidence",/* Member name */
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
            (char *)"is_rear_vertex_available",/* Member name */
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
            (char *)"vertices",/* Member name */
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
            (char *)"is_center_vertex_available",/* Member name */
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
            (char *)"center_vertex",/* Member name */
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
            (char *)"is_stopper_available",/* Member name */
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
            (char *)"stopper_vertices",/* Member name */
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
        }
    };

    static DDS_TypeCode holo_base_msg_common_ParkingSlotf_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::common::ParkingSlotf", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            15, /* Number of members */
            holo_base_msg_common_ParkingSlotf_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_common_ParkingSlotf*/

    if (is_initialized) {
        return &holo_base_msg_common_ParkingSlotf_g_tc;
    }

    holo_base_msg_common_ParkingSlotf_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_ParkingSlotf_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint64_t_get_typecode();
    holo_base_msg_common_ParkingSlotf_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_bool_t_get_typecode();
    holo_base_msg_common_ParkingSlotf_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint32_t_get_typecode();
    holo_base_msg_common_ParkingSlotf_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint32_t_get_typecode();
    holo_base_msg_common_ParkingSlotf_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint32_t_get_typecode();
    holo_base_msg_common_ParkingSlotf_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_ParkingSlotf_g_tc_members[6]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_ParkingSlotf_g_tc_members[7]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_ParkingSlotf_g_tc_members[8]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_common_ParkingSlotf_g_tc_members[9]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_bool_t_get_typecode();
    holo_base_msg_common_ParkingSlotf_g_tc_members[10]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Point3fSequence_get_typecode();
    holo_base_msg_common_ParkingSlotf_g_tc_members[11]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_bool_t_get_typecode();
    holo_base_msg_common_ParkingSlotf_g_tc_members[12]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Point3f_get_typecode();
    holo_base_msg_common_ParkingSlotf_g_tc_members[13]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_bool_t_get_typecode();
    holo_base_msg_common_ParkingSlotf_g_tc_members[14]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Point3fSequence_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_common_ParkingSlotf_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_ULONGLONG;
    holo_base_msg_common_ParkingSlotf_g_tc_members[0]._annotations._defaultValue._u.ulong_long_value = 0ull;
    holo_base_msg_common_ParkingSlotf_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_ULONGLONG;
    holo_base_msg_common_ParkingSlotf_g_tc_members[0]._annotations._minValue._u.ulong_long_value = RTIXCdrUnsignedLongLong_MIN;
    holo_base_msg_common_ParkingSlotf_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_ULONGLONG;
    holo_base_msg_common_ParkingSlotf_g_tc_members[0]._annotations._maxValue._u.ulong_long_value = RTIXCdrUnsignedLongLong_MAX;

    holo_base_msg_common_ParkingSlotf_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_BOOLEAN;
    holo_base_msg_common_ParkingSlotf_g_tc_members[1]._annotations._defaultValue._u.boolean_value = 0;

    holo_base_msg_common_ParkingSlotf_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ParkingSlotf_g_tc_members[2]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_ParkingSlotf_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ParkingSlotf_g_tc_members[2]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_ParkingSlotf_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ParkingSlotf_g_tc_members[2]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_ParkingSlotf_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ParkingSlotf_g_tc_members[3]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_ParkingSlotf_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ParkingSlotf_g_tc_members[3]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_ParkingSlotf_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ParkingSlotf_g_tc_members[3]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_ParkingSlotf_g_tc_members[4]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ParkingSlotf_g_tc_members[4]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_ParkingSlotf_g_tc_members[4]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ParkingSlotf_g_tc_members[4]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_ParkingSlotf_g_tc_members[4]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ParkingSlotf_g_tc_members[4]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_ParkingSlotf_g_tc_members[5]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ParkingSlotf_g_tc_members[5]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_ParkingSlotf_g_tc_members[5]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ParkingSlotf_g_tc_members[5]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_ParkingSlotf_g_tc_members[5]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ParkingSlotf_g_tc_members[5]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_ParkingSlotf_g_tc_members[6]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ParkingSlotf_g_tc_members[6]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_ParkingSlotf_g_tc_members[6]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ParkingSlotf_g_tc_members[6]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_ParkingSlotf_g_tc_members[6]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ParkingSlotf_g_tc_members[6]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_ParkingSlotf_g_tc_members[7]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ParkingSlotf_g_tc_members[7]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_ParkingSlotf_g_tc_members[7]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ParkingSlotf_g_tc_members[7]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_ParkingSlotf_g_tc_members[7]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ParkingSlotf_g_tc_members[7]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_ParkingSlotf_g_tc_members[8]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ParkingSlotf_g_tc_members[8]._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_common_ParkingSlotf_g_tc_members[8]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ParkingSlotf_g_tc_members[8]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_common_ParkingSlotf_g_tc_members[8]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_common_ParkingSlotf_g_tc_members[8]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_common_ParkingSlotf_g_tc_members[9]._annotations._defaultValue._d = RTI_XCDR_TK_BOOLEAN;
    holo_base_msg_common_ParkingSlotf_g_tc_members[9]._annotations._defaultValue._u.boolean_value = 0;

    holo_base_msg_common_ParkingSlotf_g_tc_members[11]._annotations._defaultValue._d = RTI_XCDR_TK_BOOLEAN;
    holo_base_msg_common_ParkingSlotf_g_tc_members[11]._annotations._defaultValue._u.boolean_value = 0;

    holo_base_msg_common_ParkingSlotf_g_tc_members[13]._annotations._defaultValue._d = RTI_XCDR_TK_BOOLEAN;
    holo_base_msg_common_ParkingSlotf_g_tc_members[13]._annotations._defaultValue._u.boolean_value = 0;

    holo_base_msg_common_ParkingSlotf_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_ParkingSlotf_get_sample_access_info();
    holo_base_msg_common_ParkingSlotf_g_tc._data._typePlugin =
    holo_base_msg_common_ParkingSlotf_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_ParkingSlotf_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_ParkingSlotf_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_common_ParkingSlotf *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_ParkingSlotf_g_memberAccessInfos[15] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_ParkingSlotf_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_ParkingSlotf_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_common_ParkingSlotf);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_common_ParkingSlotf_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->id - (char *)sample);

    holo_base_msg_common_ParkingSlotf_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->is_valid - (char *)sample);

    holo_base_msg_common_ParkingSlotf_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->type - (char *)sample);

    holo_base_msg_common_ParkingSlotf_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->position - (char *)sample);

    holo_base_msg_common_ParkingSlotf_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->status - (char *)sample);

    holo_base_msg_common_ParkingSlotf_g_memberAccessInfos[5].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->width - (char *)sample);

    holo_base_msg_common_ParkingSlotf_g_memberAccessInfos[6].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->height - (char *)sample);

    holo_base_msg_common_ParkingSlotf_g_memberAccessInfos[7].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->angle - (char *)sample);

    holo_base_msg_common_ParkingSlotf_g_memberAccessInfos[8].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->confidence - (char *)sample);

    holo_base_msg_common_ParkingSlotf_g_memberAccessInfos[9].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->is_rear_vertex_available - (char *)sample);

    holo_base_msg_common_ParkingSlotf_g_memberAccessInfos[10].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->vertices - (char *)sample);

    holo_base_msg_common_ParkingSlotf_g_memberAccessInfos[11].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->is_center_vertex_available - (char *)sample);

    holo_base_msg_common_ParkingSlotf_g_memberAccessInfos[12].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->center_vertex - (char *)sample);

    holo_base_msg_common_ParkingSlotf_g_memberAccessInfos[13].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->is_stopper_available - (char *)sample);

    holo_base_msg_common_ParkingSlotf_g_memberAccessInfos[14].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stopper_vertices - (char *)sample);

    holo_base_msg_common_ParkingSlotf_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_ParkingSlotf_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_ParkingSlotf);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_ParkingSlotf_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_ParkingSlotf_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_ParkingSlotf_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_ParkingSlotf_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_ParkingSlotf_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_ParkingSlotf_g_typePlugin = 
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
        holo_base_msg_common_ParkingSlotf_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_ParkingSlotf_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_ParkingSlotf_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_ParkingSlotf_initialize(
    holo_base_msg_common_ParkingSlotf* sample) {
    return holo_base_msg_common_ParkingSlotf_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_ParkingSlotf_initialize_ex(
    holo_base_msg_common_ParkingSlotf* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_ParkingSlotf_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_ParkingSlotf_initialize_w_params(
    holo_base_msg_common_ParkingSlotf* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->id = 0ull;

    sample->is_valid = 0;

    sample->type = 0u;

    sample->position = 0u;

    sample->status = 0u;

    sample->width = 0.0f;

    sample->height = 0.0f;

    sample->angle = 0.0f;

    sample->confidence = 0.0f;

    sample->is_rear_vertex_available = 0;

    if (!holo_base_msg_geometry_Point3fSequence_initialize_w_params(&sample->vertices,
    allocParams)) {
        return RTI_FALSE;
    }

    sample->is_center_vertex_available = 0;

    if (!holo_base_msg_geometry_Point3f_initialize_w_params(&sample->center_vertex,
    allocParams)) {
        return RTI_FALSE;
    }

    sample->is_stopper_available = 0;

    if (!holo_base_msg_geometry_Point3fSequence_initialize_w_params(&sample->stopper_vertices,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_ParkingSlotf_finalize(
    holo_base_msg_common_ParkingSlotf* sample)
{

    holo_base_msg_common_ParkingSlotf_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_ParkingSlotf_finalize_w_return(
    holo_base_msg_common_ParkingSlotf* sample)
{

    holo_base_msg_common_ParkingSlotf_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_ParkingSlotf_finalize_ex(
    holo_base_msg_common_ParkingSlotf* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_ParkingSlotf_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_ParkingSlotf_finalize_w_params(
    holo_base_msg_common_ParkingSlotf* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_geometry_Point3fSequence_finalize_w_params(&sample->vertices,deallocParams);

    holo_base_msg_geometry_Point3f_finalize_w_params(&sample->center_vertex,deallocParams);

    holo_base_msg_geometry_Point3fSequence_finalize_w_params(&sample->stopper_vertices,deallocParams);

}

void holo_base_msg_common_ParkingSlotf_finalize_optional_members(
    holo_base_msg_common_ParkingSlotf* sample, RTIBool deletePointers)
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

    holo_base_msg_geometry_Point3fSequence_finalize_optional_members(&sample->vertices, deallocParams->delete_pointers);
    holo_base_msg_geometry_Point3f_finalize_optional_members(&sample->center_vertex, deallocParams->delete_pointers);
    holo_base_msg_geometry_Point3fSequence_finalize_optional_members(&sample->stopper_vertices, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_common_ParkingSlotf_copy(
    holo_base_msg_common_ParkingSlotf* dst,
    const holo_base_msg_common_ParkingSlotf* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (&dst->id, &src->id);
    DDS_Primitive_copy (&dst->is_valid, &src->is_valid);
    DDS_Primitive_copy (&dst->type, &src->type);
    DDS_Primitive_copy (&dst->position, &src->position);
    DDS_Primitive_copy (&dst->status, &src->status);
    DDS_Primitive_copy (&dst->width, &src->width);
    DDS_Primitive_copy (&dst->height, &src->height);
    DDS_Primitive_copy (&dst->angle, &src->angle);
    DDS_Primitive_copy (&dst->confidence, &src->confidence);
    DDS_Primitive_copy (&dst->is_rear_vertex_available, &src->is_rear_vertex_available);
    if (!holo_base_msg_geometry_Point3fSequence_copy(
        &dst->vertices,(const holo_base_msg_geometry_Point3fSequence*)&src->vertices)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->is_center_vertex_available, &src->is_center_vertex_available);
    if (!holo_base_msg_geometry_Point3f_copy(
        &dst->center_vertex,(const holo_base_msg_geometry_Point3f*)&src->center_vertex)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->is_stopper_available, &src->is_stopper_available);
    if (!holo_base_msg_geometry_Point3fSequence_copy(
        &dst->stopper_vertices,(const holo_base_msg_geometry_Point3fSequence*)&src->stopper_vertices)) {
        return RTI_FALSE;
    } 

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_ParkingSlotf' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ParkingSlotf
#define TSeq holo_base_msg_common_ParkingSlotfSeq

#define T_initialize holo_base_msg_common_ParkingSlotf_initialize

#define T_finalize   holo_base_msg_common_ParkingSlotf_finalize
#define T_copy       holo_base_msg_common_ParkingSlotf_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ParkingSlotf
#define TSeq holo_base_msg_common_ParkingSlotfSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_ParkingSlotfSequence *
holo_base_msg_common_ParkingSlotfSequence_create(void)
{
    holo_base_msg_common_ParkingSlotfSequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_ParkingSlotfSequence);
    if (sample != NULL) {
        if (!holo_base_msg_common_ParkingSlotfSequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_ParkingSlotfSequence_delete(holo_base_msg_common_ParkingSlotfSequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_ParkingSlotfSequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_ParkingSlotfSequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_ParkingSlotfSequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_common_ParkingSlotfSequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_common_ParkingSlotfSequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::common::ParkingSlotfSequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_common_ParkingSlotfSequence */

    if (is_initialized) {
        return &holo_base_msg_common_ParkingSlotfSequence_g_tc;
    }

    holo_base_msg_common_ParkingSlotfSequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_ParkingSlotfSequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_common_ParkingSlotf_get_typecode();
    holo_base_msg_common_ParkingSlotfSequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_common_ParkingSlotfSequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_common_ParkingSlotfSequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_common_ParkingSlotfSequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_ParkingSlotfSequence_get_sample_access_info();
    holo_base_msg_common_ParkingSlotfSequence_g_tc._data._typePlugin =
    holo_base_msg_common_ParkingSlotfSequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_ParkingSlotfSequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_ParkingSlotfSequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_ParkingSlotfSequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_ParkingSlotfSequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_ParkingSlotfSequence_g_sampleAccessInfo;
    }

    holo_base_msg_common_ParkingSlotfSequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_common_ParkingSlotfSequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_ParkingSlotfSequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_ParkingSlotfSequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_ParkingSlotfSequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_ParkingSlotfSequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_ParkingSlotfSequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_ParkingSlotfSequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_ParkingSlotfSequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_ParkingSlotfSequence_g_typePlugin = 
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
        holo_base_msg_common_ParkingSlotfSequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_ParkingSlotfSequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_ParkingSlotfSequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_ParkingSlotfSequence_initialize(
    holo_base_msg_common_ParkingSlotfSequence* sample) {
    return holo_base_msg_common_ParkingSlotfSequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_ParkingSlotfSequence_initialize_ex(
    holo_base_msg_common_ParkingSlotfSequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_ParkingSlotfSequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_ParkingSlotfSequence_initialize_w_params(
    holo_base_msg_common_ParkingSlotfSequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!holo_base_msg_common_ParkingSlotfSeq_initialize(sample )){
            return RTI_FALSE;
        };
        if (!holo_base_msg_common_ParkingSlotfSeq_set_maximum(sample, (100))) {
            return RTI_FALSE;
        }
    } else { 
        if(!holo_base_msg_common_ParkingSlotfSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_ParkingSlotfSequence_finalize(
    holo_base_msg_common_ParkingSlotfSequence* sample)
{

    holo_base_msg_common_ParkingSlotfSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_ParkingSlotfSequence_finalize_w_return(
    holo_base_msg_common_ParkingSlotfSequence* sample)
{

    holo_base_msg_common_ParkingSlotfSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_ParkingSlotfSequence_finalize_ex(
    holo_base_msg_common_ParkingSlotfSequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_ParkingSlotfSequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_ParkingSlotfSequence_finalize_w_params(
    holo_base_msg_common_ParkingSlotfSequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!holo_base_msg_common_ParkingSlotfSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_common_ParkingSlotfSequence_finalize_optional_members(
    holo_base_msg_common_ParkingSlotfSequence* sample, RTIBool deletePointers)
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
        length = (RTI_UINT32)holo_base_msg_common_ParkingSlotfSeq_get_length(
            sample);

        for (i = 0; i < length; i++) {
            holo_base_msg_common_ParkingSlotf_finalize_optional_members(
                holo_base_msg_common_ParkingSlotfSeq_get_reference(
                    sample, (RTI_INT32)i), deallocParams->delete_pointers);
        }
    }  

}

RTIBool holo_base_msg_common_ParkingSlotfSequence_copy(
    holo_base_msg_common_ParkingSlotfSequence* dst,
    const holo_base_msg_common_ParkingSlotfSequence* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_ParkingSlotfSeq_copy(dst ,
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
* Configure and implement 'holo_base_msg_common_ParkingSlotfSequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ParkingSlotfSequence
#define TSeq holo_base_msg_common_ParkingSlotfSequenceSeq

#define T_initialize holo_base_msg_common_ParkingSlotfSequence_initialize

#define T_finalize   holo_base_msg_common_ParkingSlotfSequence_finalize
#define T_copy       holo_base_msg_common_ParkingSlotfSequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ParkingSlotfSequence
#define TSeq holo_base_msg_common_ParkingSlotfSequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_ParkingSlotd *
holo_base_msg_common_ParkingSlotd_create(void)
{
    holo_base_msg_common_ParkingSlotd* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_ParkingSlotd);
    if (sample != NULL) {
        if (!holo_base_msg_common_ParkingSlotd_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_ParkingSlotd_delete(holo_base_msg_common_ParkingSlotd*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_ParkingSlotd_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_ParkingSlotd_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_common_ParkingSlotdTYPENAME = "holo_base_msg::common::ParkingSlotd";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_ParkingSlotd_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_common_ParkingSlotd_g_tc_members[15]=
    {

        {
            (char *)"id",/* Member name */
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
            (char *)"is_valid",/* Member name */
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
        }, 
        {
            (char *)"position",/* Member name */
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
            (char *)"status",/* Member name */
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
            (char *)"width",/* Member name */
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
            (char *)"height",/* Member name */
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
            (char *)"angle",/* Member name */
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
            (char *)"confidence",/* Member name */
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
            (char *)"is_rear_vertex_available",/* Member name */
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
            (char *)"vertices",/* Member name */
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
            (char *)"is_center_vertex_available",/* Member name */
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
            (char *)"center_vertex",/* Member name */
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
            (char *)"is_stopper_available",/* Member name */
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
            (char *)"stopper_vertices",/* Member name */
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
        }
    };

    static DDS_TypeCode holo_base_msg_common_ParkingSlotd_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::common::ParkingSlotd", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            15, /* Number of members */
            holo_base_msg_common_ParkingSlotd_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_common_ParkingSlotd*/

    if (is_initialized) {
        return &holo_base_msg_common_ParkingSlotd_g_tc;
    }

    holo_base_msg_common_ParkingSlotd_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_ParkingSlotd_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint64_t_get_typecode();
    holo_base_msg_common_ParkingSlotd_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_bool_t_get_typecode();
    holo_base_msg_common_ParkingSlotd_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint32_t_get_typecode();
    holo_base_msg_common_ParkingSlotd_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint32_t_get_typecode();
    holo_base_msg_common_ParkingSlotd_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_uint32_t_get_typecode();
    holo_base_msg_common_ParkingSlotd_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();
    holo_base_msg_common_ParkingSlotd_g_tc_members[6]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();
    holo_base_msg_common_ParkingSlotd_g_tc_members[7]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();
    holo_base_msg_common_ParkingSlotd_g_tc_members[8]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();
    holo_base_msg_common_ParkingSlotd_g_tc_members[9]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_bool_t_get_typecode();
    holo_base_msg_common_ParkingSlotd_g_tc_members[10]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Point3dSequence_get_typecode();
    holo_base_msg_common_ParkingSlotd_g_tc_members[11]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_bool_t_get_typecode();
    holo_base_msg_common_ParkingSlotd_g_tc_members[12]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Point3d_get_typecode();
    holo_base_msg_common_ParkingSlotd_g_tc_members[13]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_bool_t_get_typecode();
    holo_base_msg_common_ParkingSlotd_g_tc_members[14]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_geometry_Point3dSequence_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_common_ParkingSlotd_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_ULONGLONG;
    holo_base_msg_common_ParkingSlotd_g_tc_members[0]._annotations._defaultValue._u.ulong_long_value = 0ull;
    holo_base_msg_common_ParkingSlotd_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_ULONGLONG;
    holo_base_msg_common_ParkingSlotd_g_tc_members[0]._annotations._minValue._u.ulong_long_value = RTIXCdrUnsignedLongLong_MIN;
    holo_base_msg_common_ParkingSlotd_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_ULONGLONG;
    holo_base_msg_common_ParkingSlotd_g_tc_members[0]._annotations._maxValue._u.ulong_long_value = RTIXCdrUnsignedLongLong_MAX;

    holo_base_msg_common_ParkingSlotd_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_BOOLEAN;
    holo_base_msg_common_ParkingSlotd_g_tc_members[1]._annotations._defaultValue._u.boolean_value = 0;

    holo_base_msg_common_ParkingSlotd_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ParkingSlotd_g_tc_members[2]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_ParkingSlotd_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ParkingSlotd_g_tc_members[2]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_ParkingSlotd_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ParkingSlotd_g_tc_members[2]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_ParkingSlotd_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ParkingSlotd_g_tc_members[3]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_ParkingSlotd_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ParkingSlotd_g_tc_members[3]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_ParkingSlotd_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ParkingSlotd_g_tc_members[3]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_ParkingSlotd_g_tc_members[4]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ParkingSlotd_g_tc_members[4]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_ParkingSlotd_g_tc_members[4]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ParkingSlotd_g_tc_members[4]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_ParkingSlotd_g_tc_members[4]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ParkingSlotd_g_tc_members[4]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_ParkingSlotd_g_tc_members[5]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_common_ParkingSlotd_g_tc_members[5]._annotations._defaultValue._u.double_value = 0.0;
    holo_base_msg_common_ParkingSlotd_g_tc_members[5]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_common_ParkingSlotd_g_tc_members[5]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
    holo_base_msg_common_ParkingSlotd_g_tc_members[5]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_common_ParkingSlotd_g_tc_members[5]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;

    holo_base_msg_common_ParkingSlotd_g_tc_members[6]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_common_ParkingSlotd_g_tc_members[6]._annotations._defaultValue._u.double_value = 0.0;
    holo_base_msg_common_ParkingSlotd_g_tc_members[6]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_common_ParkingSlotd_g_tc_members[6]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
    holo_base_msg_common_ParkingSlotd_g_tc_members[6]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_common_ParkingSlotd_g_tc_members[6]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;

    holo_base_msg_common_ParkingSlotd_g_tc_members[7]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_common_ParkingSlotd_g_tc_members[7]._annotations._defaultValue._u.double_value = 0.0;
    holo_base_msg_common_ParkingSlotd_g_tc_members[7]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_common_ParkingSlotd_g_tc_members[7]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
    holo_base_msg_common_ParkingSlotd_g_tc_members[7]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_common_ParkingSlotd_g_tc_members[7]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;

    holo_base_msg_common_ParkingSlotd_g_tc_members[8]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_common_ParkingSlotd_g_tc_members[8]._annotations._defaultValue._u.double_value = 0.0;
    holo_base_msg_common_ParkingSlotd_g_tc_members[8]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_common_ParkingSlotd_g_tc_members[8]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
    holo_base_msg_common_ParkingSlotd_g_tc_members[8]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_common_ParkingSlotd_g_tc_members[8]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;

    holo_base_msg_common_ParkingSlotd_g_tc_members[9]._annotations._defaultValue._d = RTI_XCDR_TK_BOOLEAN;
    holo_base_msg_common_ParkingSlotd_g_tc_members[9]._annotations._defaultValue._u.boolean_value = 0;

    holo_base_msg_common_ParkingSlotd_g_tc_members[11]._annotations._defaultValue._d = RTI_XCDR_TK_BOOLEAN;
    holo_base_msg_common_ParkingSlotd_g_tc_members[11]._annotations._defaultValue._u.boolean_value = 0;

    holo_base_msg_common_ParkingSlotd_g_tc_members[13]._annotations._defaultValue._d = RTI_XCDR_TK_BOOLEAN;
    holo_base_msg_common_ParkingSlotd_g_tc_members[13]._annotations._defaultValue._u.boolean_value = 0;

    holo_base_msg_common_ParkingSlotd_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_ParkingSlotd_get_sample_access_info();
    holo_base_msg_common_ParkingSlotd_g_tc._data._typePlugin =
    holo_base_msg_common_ParkingSlotd_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_ParkingSlotd_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_ParkingSlotd_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_common_ParkingSlotd *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_ParkingSlotd_g_memberAccessInfos[15] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_ParkingSlotd_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_ParkingSlotd_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_common_ParkingSlotd);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_common_ParkingSlotd_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->id - (char *)sample);

    holo_base_msg_common_ParkingSlotd_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->is_valid - (char *)sample);

    holo_base_msg_common_ParkingSlotd_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->type - (char *)sample);

    holo_base_msg_common_ParkingSlotd_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->position - (char *)sample);

    holo_base_msg_common_ParkingSlotd_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->status - (char *)sample);

    holo_base_msg_common_ParkingSlotd_g_memberAccessInfos[5].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->width - (char *)sample);

    holo_base_msg_common_ParkingSlotd_g_memberAccessInfos[6].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->height - (char *)sample);

    holo_base_msg_common_ParkingSlotd_g_memberAccessInfos[7].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->angle - (char *)sample);

    holo_base_msg_common_ParkingSlotd_g_memberAccessInfos[8].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->confidence - (char *)sample);

    holo_base_msg_common_ParkingSlotd_g_memberAccessInfos[9].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->is_rear_vertex_available - (char *)sample);

    holo_base_msg_common_ParkingSlotd_g_memberAccessInfos[10].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->vertices - (char *)sample);

    holo_base_msg_common_ParkingSlotd_g_memberAccessInfos[11].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->is_center_vertex_available - (char *)sample);

    holo_base_msg_common_ParkingSlotd_g_memberAccessInfos[12].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->center_vertex - (char *)sample);

    holo_base_msg_common_ParkingSlotd_g_memberAccessInfos[13].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->is_stopper_available - (char *)sample);

    holo_base_msg_common_ParkingSlotd_g_memberAccessInfos[14].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stopper_vertices - (char *)sample);

    holo_base_msg_common_ParkingSlotd_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_ParkingSlotd_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_ParkingSlotd);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_ParkingSlotd_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_ParkingSlotd_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_ParkingSlotd_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_ParkingSlotd_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_ParkingSlotd_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_ParkingSlotd_g_typePlugin = 
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
        holo_base_msg_common_ParkingSlotd_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_ParkingSlotd_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_ParkingSlotd_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_ParkingSlotd_initialize(
    holo_base_msg_common_ParkingSlotd* sample) {
    return holo_base_msg_common_ParkingSlotd_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_ParkingSlotd_initialize_ex(
    holo_base_msg_common_ParkingSlotd* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_ParkingSlotd_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_ParkingSlotd_initialize_w_params(
    holo_base_msg_common_ParkingSlotd* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->id = 0ull;

    sample->is_valid = 0;

    sample->type = 0u;

    sample->position = 0u;

    sample->status = 0u;

    sample->width = 0.0;

    sample->height = 0.0;

    sample->angle = 0.0;

    sample->confidence = 0.0;

    sample->is_rear_vertex_available = 0;

    if (!holo_base_msg_geometry_Point3dSequence_initialize_w_params(&sample->vertices,
    allocParams)) {
        return RTI_FALSE;
    }

    sample->is_center_vertex_available = 0;

    if (!holo_base_msg_geometry_Point3d_initialize_w_params(&sample->center_vertex,
    allocParams)) {
        return RTI_FALSE;
    }

    sample->is_stopper_available = 0;

    if (!holo_base_msg_geometry_Point3dSequence_initialize_w_params(&sample->stopper_vertices,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_ParkingSlotd_finalize(
    holo_base_msg_common_ParkingSlotd* sample)
{

    holo_base_msg_common_ParkingSlotd_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_ParkingSlotd_finalize_w_return(
    holo_base_msg_common_ParkingSlotd* sample)
{

    holo_base_msg_common_ParkingSlotd_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_ParkingSlotd_finalize_ex(
    holo_base_msg_common_ParkingSlotd* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_ParkingSlotd_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_ParkingSlotd_finalize_w_params(
    holo_base_msg_common_ParkingSlotd* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_geometry_Point3dSequence_finalize_w_params(&sample->vertices,deallocParams);

    holo_base_msg_geometry_Point3d_finalize_w_params(&sample->center_vertex,deallocParams);

    holo_base_msg_geometry_Point3dSequence_finalize_w_params(&sample->stopper_vertices,deallocParams);

}

void holo_base_msg_common_ParkingSlotd_finalize_optional_members(
    holo_base_msg_common_ParkingSlotd* sample, RTIBool deletePointers)
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

    holo_base_msg_geometry_Point3dSequence_finalize_optional_members(&sample->vertices, deallocParams->delete_pointers);
    holo_base_msg_geometry_Point3d_finalize_optional_members(&sample->center_vertex, deallocParams->delete_pointers);
    holo_base_msg_geometry_Point3dSequence_finalize_optional_members(&sample->stopper_vertices, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_common_ParkingSlotd_copy(
    holo_base_msg_common_ParkingSlotd* dst,
    const holo_base_msg_common_ParkingSlotd* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (&dst->id, &src->id);
    DDS_Primitive_copy (&dst->is_valid, &src->is_valid);
    DDS_Primitive_copy (&dst->type, &src->type);
    DDS_Primitive_copy (&dst->position, &src->position);
    DDS_Primitive_copy (&dst->status, &src->status);
    DDS_Primitive_copy (&dst->width, &src->width);
    DDS_Primitive_copy (&dst->height, &src->height);
    DDS_Primitive_copy (&dst->angle, &src->angle);
    DDS_Primitive_copy (&dst->confidence, &src->confidence);
    DDS_Primitive_copy (&dst->is_rear_vertex_available, &src->is_rear_vertex_available);
    if (!holo_base_msg_geometry_Point3dSequence_copy(
        &dst->vertices,(const holo_base_msg_geometry_Point3dSequence*)&src->vertices)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->is_center_vertex_available, &src->is_center_vertex_available);
    if (!holo_base_msg_geometry_Point3d_copy(
        &dst->center_vertex,(const holo_base_msg_geometry_Point3d*)&src->center_vertex)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->is_stopper_available, &src->is_stopper_available);
    if (!holo_base_msg_geometry_Point3dSequence_copy(
        &dst->stopper_vertices,(const holo_base_msg_geometry_Point3dSequence*)&src->stopper_vertices)) {
        return RTI_FALSE;
    } 

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_ParkingSlotd' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ParkingSlotd
#define TSeq holo_base_msg_common_ParkingSlotdSeq

#define T_initialize holo_base_msg_common_ParkingSlotd_initialize

#define T_finalize   holo_base_msg_common_ParkingSlotd_finalize
#define T_copy       holo_base_msg_common_ParkingSlotd_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ParkingSlotd
#define TSeq holo_base_msg_common_ParkingSlotdSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_ParkingSlotdSequence *
holo_base_msg_common_ParkingSlotdSequence_create(void)
{
    holo_base_msg_common_ParkingSlotdSequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_ParkingSlotdSequence);
    if (sample != NULL) {
        if (!holo_base_msg_common_ParkingSlotdSequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_ParkingSlotdSequence_delete(holo_base_msg_common_ParkingSlotdSequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_ParkingSlotdSequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_ParkingSlotdSequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_ParkingSlotdSequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_common_ParkingSlotdSequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_common_ParkingSlotdSequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::common::ParkingSlotdSequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_common_ParkingSlotdSequence */

    if (is_initialized) {
        return &holo_base_msg_common_ParkingSlotdSequence_g_tc;
    }

    holo_base_msg_common_ParkingSlotdSequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_ParkingSlotdSequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_common_ParkingSlotd_get_typecode();
    holo_base_msg_common_ParkingSlotdSequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_common_ParkingSlotdSequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_common_ParkingSlotdSequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_common_ParkingSlotdSequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_ParkingSlotdSequence_get_sample_access_info();
    holo_base_msg_common_ParkingSlotdSequence_g_tc._data._typePlugin =
    holo_base_msg_common_ParkingSlotdSequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_ParkingSlotdSequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_ParkingSlotdSequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_ParkingSlotdSequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_ParkingSlotdSequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_ParkingSlotdSequence_g_sampleAccessInfo;
    }

    holo_base_msg_common_ParkingSlotdSequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_common_ParkingSlotdSequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_ParkingSlotdSequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_ParkingSlotdSequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_ParkingSlotdSequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_ParkingSlotdSequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_ParkingSlotdSequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_ParkingSlotdSequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_ParkingSlotdSequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_ParkingSlotdSequence_g_typePlugin = 
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
        holo_base_msg_common_ParkingSlotdSequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_ParkingSlotdSequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_ParkingSlotdSequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_ParkingSlotdSequence_initialize(
    holo_base_msg_common_ParkingSlotdSequence* sample) {
    return holo_base_msg_common_ParkingSlotdSequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_ParkingSlotdSequence_initialize_ex(
    holo_base_msg_common_ParkingSlotdSequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_ParkingSlotdSequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_ParkingSlotdSequence_initialize_w_params(
    holo_base_msg_common_ParkingSlotdSequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!holo_base_msg_common_ParkingSlotdSeq_initialize(sample )){
            return RTI_FALSE;
        };
        if (!holo_base_msg_common_ParkingSlotdSeq_set_maximum(sample, (100))) {
            return RTI_FALSE;
        }
    } else { 
        if(!holo_base_msg_common_ParkingSlotdSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_ParkingSlotdSequence_finalize(
    holo_base_msg_common_ParkingSlotdSequence* sample)
{

    holo_base_msg_common_ParkingSlotdSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_ParkingSlotdSequence_finalize_w_return(
    holo_base_msg_common_ParkingSlotdSequence* sample)
{

    holo_base_msg_common_ParkingSlotdSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_ParkingSlotdSequence_finalize_ex(
    holo_base_msg_common_ParkingSlotdSequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_ParkingSlotdSequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_ParkingSlotdSequence_finalize_w_params(
    holo_base_msg_common_ParkingSlotdSequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!holo_base_msg_common_ParkingSlotdSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_common_ParkingSlotdSequence_finalize_optional_members(
    holo_base_msg_common_ParkingSlotdSequence* sample, RTIBool deletePointers)
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
        length = (RTI_UINT32)holo_base_msg_common_ParkingSlotdSeq_get_length(
            sample);

        for (i = 0; i < length; i++) {
            holo_base_msg_common_ParkingSlotd_finalize_optional_members(
                holo_base_msg_common_ParkingSlotdSeq_get_reference(
                    sample, (RTI_INT32)i), deallocParams->delete_pointers);
        }
    }  

}

RTIBool holo_base_msg_common_ParkingSlotdSequence_copy(
    holo_base_msg_common_ParkingSlotdSequence* dst,
    const holo_base_msg_common_ParkingSlotdSequence* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_ParkingSlotdSeq_copy(dst ,
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
* Configure and implement 'holo_base_msg_common_ParkingSlotdSequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ParkingSlotdSequence
#define TSeq holo_base_msg_common_ParkingSlotdSequenceSeq

#define T_initialize holo_base_msg_common_ParkingSlotdSequence_initialize

#define T_finalize   holo_base_msg_common_ParkingSlotdSequence_finalize
#define T_copy       holo_base_msg_common_ParkingSlotdSequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ParkingSlotdSequence
#define TSeq holo_base_msg_common_ParkingSlotdSequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_ParkingSlotFramef *
holo_base_msg_common_ParkingSlotFramef_create(void)
{
    holo_base_msg_common_ParkingSlotFramef* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_ParkingSlotFramef);
    if (sample != NULL) {
        if (!holo_base_msg_common_ParkingSlotFramef_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_ParkingSlotFramef_delete(holo_base_msg_common_ParkingSlotFramef*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_ParkingSlotFramef_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_ParkingSlotFramef_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_common_ParkingSlotFramefTYPENAME = "holo_base_msg::common::ParkingSlotFramef";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_ParkingSlotFramef_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_common_ParkingSlotFramef_g_tc_members[3]=
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
        }
    };

    static DDS_TypeCode holo_base_msg_common_ParkingSlotFramef_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::common::ParkingSlotFramef", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            3, /* Number of members */
            holo_base_msg_common_ParkingSlotFramef_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_common_ParkingSlotFramef*/

    if (is_initialized) {
        return &holo_base_msg_common_ParkingSlotFramef_g_tc;
    }

    holo_base_msg_common_ParkingSlotFramef_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_ParkingSlotFramef_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_common_ParkingSlotFramef_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Coordinate_get_typecode();
    holo_base_msg_common_ParkingSlotFramef_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_ParkingSlotfSequence_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_common_ParkingSlotFramef_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ParkingSlotFramef_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_ParkingSlotFramef_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ParkingSlotFramef_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_ParkingSlotFramef_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ParkingSlotFramef_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_ParkingSlotFramef_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_ParkingSlotFramef_get_sample_access_info();
    holo_base_msg_common_ParkingSlotFramef_g_tc._data._typePlugin =
    holo_base_msg_common_ParkingSlotFramef_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_ParkingSlotFramef_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_ParkingSlotFramef_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_common_ParkingSlotFramef *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_ParkingSlotFramef_g_memberAccessInfos[3] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_ParkingSlotFramef_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_ParkingSlotFramef_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_common_ParkingSlotFramef);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_common_ParkingSlotFramef_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stamp - (char *)sample);

    holo_base_msg_common_ParkingSlotFramef_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->coord - (char *)sample);

    holo_base_msg_common_ParkingSlotFramef_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->point_list - (char *)sample);

    holo_base_msg_common_ParkingSlotFramef_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_ParkingSlotFramef_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_ParkingSlotFramef);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_ParkingSlotFramef_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_ParkingSlotFramef_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_ParkingSlotFramef_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_ParkingSlotFramef_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_ParkingSlotFramef_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_ParkingSlotFramef_g_typePlugin = 
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
        holo_base_msg_common_ParkingSlotFramef_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_ParkingSlotFramef_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_ParkingSlotFramef_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_ParkingSlotFramef_initialize(
    holo_base_msg_common_ParkingSlotFramef* sample) {
    return holo_base_msg_common_ParkingSlotFramef_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_ParkingSlotFramef_initialize_ex(
    holo_base_msg_common_ParkingSlotFramef* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_ParkingSlotFramef_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_ParkingSlotFramef_initialize_w_params(
    holo_base_msg_common_ParkingSlotFramef* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

    if (!holo_base_msg_common_ParkingSlotfSequence_initialize_w_params(&sample->point_list,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_ParkingSlotFramef_finalize(
    holo_base_msg_common_ParkingSlotFramef* sample)
{

    holo_base_msg_common_ParkingSlotFramef_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_ParkingSlotFramef_finalize_w_return(
    holo_base_msg_common_ParkingSlotFramef* sample)
{

    holo_base_msg_common_ParkingSlotFramef_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_ParkingSlotFramef_finalize_ex(
    holo_base_msg_common_ParkingSlotFramef* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_ParkingSlotFramef_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_ParkingSlotFramef_finalize_w_params(
    holo_base_msg_common_ParkingSlotFramef* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->stamp,deallocParams);

    holo_base_msg_common_ParkingSlotfSequence_finalize_w_params(&sample->point_list,deallocParams);

}

void holo_base_msg_common_ParkingSlotFramef_finalize_optional_members(
    holo_base_msg_common_ParkingSlotFramef* sample, RTIBool deletePointers)
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
    holo_base_msg_common_ParkingSlotfSequence_finalize_optional_members(&sample->point_list, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_common_ParkingSlotFramef_copy(
    holo_base_msg_common_ParkingSlotFramef* dst,
    const holo_base_msg_common_ParkingSlotFramef* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_copy(
        &dst->stamp,(const holo_base_msg_common_Timestamp*)&src->stamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->coord, &src->coord);
    if (!holo_base_msg_common_ParkingSlotfSequence_copy(
        &dst->point_list,(const holo_base_msg_common_ParkingSlotfSequence*)&src->point_list)) {
        return RTI_FALSE;
    } 

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_ParkingSlotFramef' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ParkingSlotFramef
#define TSeq holo_base_msg_common_ParkingSlotFramefSeq

#define T_initialize holo_base_msg_common_ParkingSlotFramef_initialize

#define T_finalize   holo_base_msg_common_ParkingSlotFramef_finalize
#define T_copy       holo_base_msg_common_ParkingSlotFramef_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ParkingSlotFramef
#define TSeq holo_base_msg_common_ParkingSlotFramefSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_ParkingSlotFramed *
holo_base_msg_common_ParkingSlotFramed_create(void)
{
    holo_base_msg_common_ParkingSlotFramed* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_ParkingSlotFramed);
    if (sample != NULL) {
        if (!holo_base_msg_common_ParkingSlotFramed_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_ParkingSlotFramed_delete(holo_base_msg_common_ParkingSlotFramed*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_ParkingSlotFramed_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_ParkingSlotFramed_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_common_ParkingSlotFramedTYPENAME = "holo_base_msg::common::ParkingSlotFramed";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_ParkingSlotFramed_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_common_ParkingSlotFramed_g_tc_members[3]=
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
        }
    };

    static DDS_TypeCode holo_base_msg_common_ParkingSlotFramed_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::common::ParkingSlotFramed", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            3, /* Number of members */
            holo_base_msg_common_ParkingSlotFramed_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_common_ParkingSlotFramed*/

    if (is_initialized) {
        return &holo_base_msg_common_ParkingSlotFramed_g_tc;
    }

    holo_base_msg_common_ParkingSlotFramed_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_ParkingSlotFramed_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_common_ParkingSlotFramed_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Coordinate_get_typecode();
    holo_base_msg_common_ParkingSlotFramed_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_ParkingSlotdSequence_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_common_ParkingSlotFramed_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ParkingSlotFramed_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_ParkingSlotFramed_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ParkingSlotFramed_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_ParkingSlotFramed_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_ParkingSlotFramed_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_ParkingSlotFramed_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_ParkingSlotFramed_get_sample_access_info();
    holo_base_msg_common_ParkingSlotFramed_g_tc._data._typePlugin =
    holo_base_msg_common_ParkingSlotFramed_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_ParkingSlotFramed_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_ParkingSlotFramed_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_common_ParkingSlotFramed *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_ParkingSlotFramed_g_memberAccessInfos[3] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_ParkingSlotFramed_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_ParkingSlotFramed_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_common_ParkingSlotFramed);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_common_ParkingSlotFramed_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stamp - (char *)sample);

    holo_base_msg_common_ParkingSlotFramed_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->coord - (char *)sample);

    holo_base_msg_common_ParkingSlotFramed_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->point_list - (char *)sample);

    holo_base_msg_common_ParkingSlotFramed_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_ParkingSlotFramed_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_ParkingSlotFramed);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_ParkingSlotFramed_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_ParkingSlotFramed_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_ParkingSlotFramed_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_ParkingSlotFramed_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_ParkingSlotFramed_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_ParkingSlotFramed_g_typePlugin = 
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
        holo_base_msg_common_ParkingSlotFramed_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_ParkingSlotFramed_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_ParkingSlotFramed_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_ParkingSlotFramed_initialize(
    holo_base_msg_common_ParkingSlotFramed* sample) {
    return holo_base_msg_common_ParkingSlotFramed_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_ParkingSlotFramed_initialize_ex(
    holo_base_msg_common_ParkingSlotFramed* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_ParkingSlotFramed_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_ParkingSlotFramed_initialize_w_params(
    holo_base_msg_common_ParkingSlotFramed* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

    if (!holo_base_msg_common_ParkingSlotdSequence_initialize_w_params(&sample->point_list,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_ParkingSlotFramed_finalize(
    holo_base_msg_common_ParkingSlotFramed* sample)
{

    holo_base_msg_common_ParkingSlotFramed_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_ParkingSlotFramed_finalize_w_return(
    holo_base_msg_common_ParkingSlotFramed* sample)
{

    holo_base_msg_common_ParkingSlotFramed_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_ParkingSlotFramed_finalize_ex(
    holo_base_msg_common_ParkingSlotFramed* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_ParkingSlotFramed_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_ParkingSlotFramed_finalize_w_params(
    holo_base_msg_common_ParkingSlotFramed* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->stamp,deallocParams);

    holo_base_msg_common_ParkingSlotdSequence_finalize_w_params(&sample->point_list,deallocParams);

}

void holo_base_msg_common_ParkingSlotFramed_finalize_optional_members(
    holo_base_msg_common_ParkingSlotFramed* sample, RTIBool deletePointers)
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
    holo_base_msg_common_ParkingSlotdSequence_finalize_optional_members(&sample->point_list, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_common_ParkingSlotFramed_copy(
    holo_base_msg_common_ParkingSlotFramed* dst,
    const holo_base_msg_common_ParkingSlotFramed* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_copy(
        &dst->stamp,(const holo_base_msg_common_Timestamp*)&src->stamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->coord, &src->coord);
    if (!holo_base_msg_common_ParkingSlotdSequence_copy(
        &dst->point_list,(const holo_base_msg_common_ParkingSlotdSequence*)&src->point_list)) {
        return RTI_FALSE;
    } 

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_ParkingSlotFramed' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ParkingSlotFramed
#define TSeq holo_base_msg_common_ParkingSlotFramedSeq

#define T_initialize holo_base_msg_common_ParkingSlotFramed_initialize

#define T_finalize   holo_base_msg_common_ParkingSlotFramed_finalize
#define T_copy       holo_base_msg_common_ParkingSlotFramed_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ParkingSlotFramed
#define TSeq holo_base_msg_common_ParkingSlotFramedSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

