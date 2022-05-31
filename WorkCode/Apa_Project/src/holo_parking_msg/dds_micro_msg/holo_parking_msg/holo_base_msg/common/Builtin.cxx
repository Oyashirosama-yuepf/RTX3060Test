/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Builtin.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "Builtin.h"

#ifndef UNUSED_ARG
#define UNUSED_ARG(x) (void)(x)
#endif

#include "dds_c/dds_c_typecode.h"
/*** SOURCE_BEGIN ***/

opendds_wrapper_BuiltinTimestamp *
opendds_wrapper_BuiltinTimestamp_create(void)
{
    opendds_wrapper_BuiltinTimestamp* sample;
    OSAPI_Heap_allocate_struct(&sample, opendds_wrapper_BuiltinTimestamp);
    if (sample != NULL) {
        if (!opendds_wrapper_BuiltinTimestamp_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
opendds_wrapper_BuiltinTimestamp_delete(opendds_wrapper_BuiltinTimestamp*sample)
{
    if (sample != NULL) {
        /* opendds_wrapper_BuiltinTimestamp_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        opendds_wrapper_BuiltinTimestamp_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *opendds_wrapper_BuiltinTimestampTYPENAME = "opendds_wrapper::BuiltinTimestamp";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* opendds_wrapper_BuiltinTimestamp_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member opendds_wrapper_BuiltinTimestamp_g_tc_members[2]=
    {

        {
            (char *)"sec",/* Member name */
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
            (char *)"nsec",/* Member name */
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

    static DDS_TypeCode opendds_wrapper_BuiltinTimestamp_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"opendds_wrapper::BuiltinTimestamp", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            2, /* Number of members */
            opendds_wrapper_BuiltinTimestamp_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for opendds_wrapper_BuiltinTimestamp*/

    if (is_initialized) {
        return &opendds_wrapper_BuiltinTimestamp_g_tc;
    }

    opendds_wrapper_BuiltinTimestamp_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    opendds_wrapper_BuiltinTimestamp_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ulong;
    opendds_wrapper_BuiltinTimestamp_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ulong;

    /* Initialize the values for member annotations. */
    opendds_wrapper_BuiltinTimestamp_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    opendds_wrapper_BuiltinTimestamp_g_tc_members[0]._annotations._defaultValue._u.ulong_value = 0u;
    opendds_wrapper_BuiltinTimestamp_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    opendds_wrapper_BuiltinTimestamp_g_tc_members[0]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    opendds_wrapper_BuiltinTimestamp_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    opendds_wrapper_BuiltinTimestamp_g_tc_members[0]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    opendds_wrapper_BuiltinTimestamp_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    opendds_wrapper_BuiltinTimestamp_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    opendds_wrapper_BuiltinTimestamp_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    opendds_wrapper_BuiltinTimestamp_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    opendds_wrapper_BuiltinTimestamp_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    opendds_wrapper_BuiltinTimestamp_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    opendds_wrapper_BuiltinTimestamp_g_tc._data._sampleAccessInfo =
    opendds_wrapper_BuiltinTimestamp_get_sample_access_info();
    opendds_wrapper_BuiltinTimestamp_g_tc._data._typePlugin =
    opendds_wrapper_BuiltinTimestamp_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &opendds_wrapper_BuiltinTimestamp_g_tc;
}

RTIXCdrSampleAccessInfo *opendds_wrapper_BuiltinTimestamp_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    opendds_wrapper_BuiltinTimestamp *sample;

    static RTIXCdrMemberAccessInfo opendds_wrapper_BuiltinTimestamp_g_memberAccessInfos[2] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo opendds_wrapper_BuiltinTimestamp_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &opendds_wrapper_BuiltinTimestamp_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        opendds_wrapper_BuiltinTimestamp);
    if (sample == NULL) {
        return NULL;
    }

    opendds_wrapper_BuiltinTimestamp_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->sec - (char *)sample);

    opendds_wrapper_BuiltinTimestamp_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->nsec - (char *)sample);

    opendds_wrapper_BuiltinTimestamp_g_sampleAccessInfo.memberAccessInfos = 
    opendds_wrapper_BuiltinTimestamp_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(opendds_wrapper_BuiltinTimestamp);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            opendds_wrapper_BuiltinTimestamp_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            opendds_wrapper_BuiltinTimestamp_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    opendds_wrapper_BuiltinTimestamp_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &opendds_wrapper_BuiltinTimestamp_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *opendds_wrapper_BuiltinTimestamp_get_type_plugin_info()
{
    static RTIXCdrTypePlugin opendds_wrapper_BuiltinTimestamp_g_typePlugin = 
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
        opendds_wrapper_BuiltinTimestamp_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        opendds_wrapper_BuiltinTimestamp_finalize_w_return,
        NULL
    };

    return &opendds_wrapper_BuiltinTimestamp_g_typePlugin;
}
#endif

RTIBool opendds_wrapper_BuiltinTimestamp_initialize(
    opendds_wrapper_BuiltinTimestamp* sample) {
    return opendds_wrapper_BuiltinTimestamp_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool opendds_wrapper_BuiltinTimestamp_initialize_ex(
    opendds_wrapper_BuiltinTimestamp* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return opendds_wrapper_BuiltinTimestamp_initialize_w_params(
        sample,&allocParams);

}

RTIBool opendds_wrapper_BuiltinTimestamp_initialize_w_params(
    opendds_wrapper_BuiltinTimestamp* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->sec = 0u;

    sample->nsec = 0u;

    return RTI_TRUE;
}

RTIBool opendds_wrapper_BuiltinTimestamp_finalize(
    opendds_wrapper_BuiltinTimestamp* sample)
{

    opendds_wrapper_BuiltinTimestamp_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool opendds_wrapper_BuiltinTimestamp_finalize_w_return(
    opendds_wrapper_BuiltinTimestamp* sample)
{

    opendds_wrapper_BuiltinTimestamp_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void opendds_wrapper_BuiltinTimestamp_finalize_ex(
    opendds_wrapper_BuiltinTimestamp* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    opendds_wrapper_BuiltinTimestamp_finalize_w_params(
        sample,&deallocParams);
}

void opendds_wrapper_BuiltinTimestamp_finalize_w_params(
    opendds_wrapper_BuiltinTimestamp* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void opendds_wrapper_BuiltinTimestamp_finalize_optional_members(
    opendds_wrapper_BuiltinTimestamp* sample, RTIBool deletePointers)
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

RTIBool opendds_wrapper_BuiltinTimestamp_copy(
    opendds_wrapper_BuiltinTimestamp* dst,
    const opendds_wrapper_BuiltinTimestamp* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (&dst->sec, &src->sec);
    DDS_Primitive_copy (&dst->nsec, &src->nsec);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'opendds_wrapper_BuiltinTimestamp' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinTimestamp
#define TSeq opendds_wrapper_BuiltinTimestampSeq

#define T_initialize opendds_wrapper_BuiltinTimestamp_initialize

#define T_finalize   opendds_wrapper_BuiltinTimestamp_finalize
#define T_copy       opendds_wrapper_BuiltinTimestamp_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinTimestamp
#define TSeq opendds_wrapper_BuiltinTimestampSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

opendds_wrapper_BuiltinUint8 *
opendds_wrapper_BuiltinUint8_create(void)
{
    opendds_wrapper_BuiltinUint8* sample;
    OSAPI_Heap_allocate_struct(&sample, opendds_wrapper_BuiltinUint8);
    if (sample != NULL) {
        if (!opendds_wrapper_BuiltinUint8_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
opendds_wrapper_BuiltinUint8_delete(opendds_wrapper_BuiltinUint8*sample)
{
    if (sample != NULL) {
        /* opendds_wrapper_BuiltinUint8_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        opendds_wrapper_BuiltinUint8_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *opendds_wrapper_BuiltinUint8TYPENAME = "opendds_wrapper::BuiltinUint8";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* opendds_wrapper_BuiltinUint8_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member opendds_wrapper_BuiltinUint8_g_tc_members[1]=
    {

        {
            (char *)"value",/* Member name */
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
        }
    };

    static DDS_TypeCode opendds_wrapper_BuiltinUint8_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"opendds_wrapper::BuiltinUint8", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            1, /* Number of members */
            opendds_wrapper_BuiltinUint8_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for opendds_wrapper_BuiltinUint8*/

    if (is_initialized) {
        return &opendds_wrapper_BuiltinUint8_g_tc;
    }

    opendds_wrapper_BuiltinUint8_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    opendds_wrapper_BuiltinUint8_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_octet;

    /* Initialize the values for member annotations. */
    opendds_wrapper_BuiltinUint8_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    opendds_wrapper_BuiltinUint8_g_tc_members[0]._annotations._defaultValue._u.octet_value = 0;
    opendds_wrapper_BuiltinUint8_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    opendds_wrapper_BuiltinUint8_g_tc_members[0]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    opendds_wrapper_BuiltinUint8_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    opendds_wrapper_BuiltinUint8_g_tc_members[0]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    opendds_wrapper_BuiltinUint8_g_tc._data._sampleAccessInfo =
    opendds_wrapper_BuiltinUint8_get_sample_access_info();
    opendds_wrapper_BuiltinUint8_g_tc._data._typePlugin =
    opendds_wrapper_BuiltinUint8_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &opendds_wrapper_BuiltinUint8_g_tc;
}

RTIXCdrSampleAccessInfo *opendds_wrapper_BuiltinUint8_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    opendds_wrapper_BuiltinUint8 *sample;

    static RTIXCdrMemberAccessInfo opendds_wrapper_BuiltinUint8_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo opendds_wrapper_BuiltinUint8_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &opendds_wrapper_BuiltinUint8_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        opendds_wrapper_BuiltinUint8);
    if (sample == NULL) {
        return NULL;
    }

    opendds_wrapper_BuiltinUint8_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->value - (char *)sample);

    opendds_wrapper_BuiltinUint8_g_sampleAccessInfo.memberAccessInfos = 
    opendds_wrapper_BuiltinUint8_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(opendds_wrapper_BuiltinUint8);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            opendds_wrapper_BuiltinUint8_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            opendds_wrapper_BuiltinUint8_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    opendds_wrapper_BuiltinUint8_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &opendds_wrapper_BuiltinUint8_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *opendds_wrapper_BuiltinUint8_get_type_plugin_info()
{
    static RTIXCdrTypePlugin opendds_wrapper_BuiltinUint8_g_typePlugin = 
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
        opendds_wrapper_BuiltinUint8_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        opendds_wrapper_BuiltinUint8_finalize_w_return,
        NULL
    };

    return &opendds_wrapper_BuiltinUint8_g_typePlugin;
}
#endif

RTIBool opendds_wrapper_BuiltinUint8_initialize(
    opendds_wrapper_BuiltinUint8* sample) {
    return opendds_wrapper_BuiltinUint8_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool opendds_wrapper_BuiltinUint8_initialize_ex(
    opendds_wrapper_BuiltinUint8* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return opendds_wrapper_BuiltinUint8_initialize_w_params(
        sample,&allocParams);

}

RTIBool opendds_wrapper_BuiltinUint8_initialize_w_params(
    opendds_wrapper_BuiltinUint8* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->value = 0;

    return RTI_TRUE;
}

RTIBool opendds_wrapper_BuiltinUint8_finalize(
    opendds_wrapper_BuiltinUint8* sample)
{

    opendds_wrapper_BuiltinUint8_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool opendds_wrapper_BuiltinUint8_finalize_w_return(
    opendds_wrapper_BuiltinUint8* sample)
{

    opendds_wrapper_BuiltinUint8_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void opendds_wrapper_BuiltinUint8_finalize_ex(
    opendds_wrapper_BuiltinUint8* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    opendds_wrapper_BuiltinUint8_finalize_w_params(
        sample,&deallocParams);
}

void opendds_wrapper_BuiltinUint8_finalize_w_params(
    opendds_wrapper_BuiltinUint8* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void opendds_wrapper_BuiltinUint8_finalize_optional_members(
    opendds_wrapper_BuiltinUint8* sample, RTIBool deletePointers)
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

RTIBool opendds_wrapper_BuiltinUint8_copy(
    opendds_wrapper_BuiltinUint8* dst,
    const opendds_wrapper_BuiltinUint8* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (&dst->value, &src->value);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'opendds_wrapper_BuiltinUint8' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinUint8
#define TSeq opendds_wrapper_BuiltinUint8Seq

#define T_initialize opendds_wrapper_BuiltinUint8_initialize

#define T_finalize   opendds_wrapper_BuiltinUint8_finalize
#define T_copy       opendds_wrapper_BuiltinUint8_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinUint8
#define TSeq opendds_wrapper_BuiltinUint8Seq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

opendds_wrapper_BuiltinUint16 *
opendds_wrapper_BuiltinUint16_create(void)
{
    opendds_wrapper_BuiltinUint16* sample;
    OSAPI_Heap_allocate_struct(&sample, opendds_wrapper_BuiltinUint16);
    if (sample != NULL) {
        if (!opendds_wrapper_BuiltinUint16_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
opendds_wrapper_BuiltinUint16_delete(opendds_wrapper_BuiltinUint16*sample)
{
    if (sample != NULL) {
        /* opendds_wrapper_BuiltinUint16_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        opendds_wrapper_BuiltinUint16_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *opendds_wrapper_BuiltinUint16TYPENAME = "opendds_wrapper::BuiltinUint16";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* opendds_wrapper_BuiltinUint16_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member opendds_wrapper_BuiltinUint16_g_tc_members[1]=
    {

        {
            (char *)"value",/* Member name */
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
        }
    };

    static DDS_TypeCode opendds_wrapper_BuiltinUint16_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"opendds_wrapper::BuiltinUint16", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            1, /* Number of members */
            opendds_wrapper_BuiltinUint16_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for opendds_wrapper_BuiltinUint16*/

    if (is_initialized) {
        return &opendds_wrapper_BuiltinUint16_g_tc;
    }

    opendds_wrapper_BuiltinUint16_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    opendds_wrapper_BuiltinUint16_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ushort;

    /* Initialize the values for member annotations. */
    opendds_wrapper_BuiltinUint16_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
    opendds_wrapper_BuiltinUint16_g_tc_members[0]._annotations._defaultValue._u.ushort_value = 0;
    opendds_wrapper_BuiltinUint16_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
    opendds_wrapper_BuiltinUint16_g_tc_members[0]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
    opendds_wrapper_BuiltinUint16_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
    opendds_wrapper_BuiltinUint16_g_tc_members[0]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

    opendds_wrapper_BuiltinUint16_g_tc._data._sampleAccessInfo =
    opendds_wrapper_BuiltinUint16_get_sample_access_info();
    opendds_wrapper_BuiltinUint16_g_tc._data._typePlugin =
    opendds_wrapper_BuiltinUint16_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &opendds_wrapper_BuiltinUint16_g_tc;
}

RTIXCdrSampleAccessInfo *opendds_wrapper_BuiltinUint16_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    opendds_wrapper_BuiltinUint16 *sample;

    static RTIXCdrMemberAccessInfo opendds_wrapper_BuiltinUint16_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo opendds_wrapper_BuiltinUint16_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &opendds_wrapper_BuiltinUint16_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        opendds_wrapper_BuiltinUint16);
    if (sample == NULL) {
        return NULL;
    }

    opendds_wrapper_BuiltinUint16_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->value - (char *)sample);

    opendds_wrapper_BuiltinUint16_g_sampleAccessInfo.memberAccessInfos = 
    opendds_wrapper_BuiltinUint16_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(opendds_wrapper_BuiltinUint16);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            opendds_wrapper_BuiltinUint16_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            opendds_wrapper_BuiltinUint16_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    opendds_wrapper_BuiltinUint16_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &opendds_wrapper_BuiltinUint16_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *opendds_wrapper_BuiltinUint16_get_type_plugin_info()
{
    static RTIXCdrTypePlugin opendds_wrapper_BuiltinUint16_g_typePlugin = 
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
        opendds_wrapper_BuiltinUint16_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        opendds_wrapper_BuiltinUint16_finalize_w_return,
        NULL
    };

    return &opendds_wrapper_BuiltinUint16_g_typePlugin;
}
#endif

RTIBool opendds_wrapper_BuiltinUint16_initialize(
    opendds_wrapper_BuiltinUint16* sample) {
    return opendds_wrapper_BuiltinUint16_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool opendds_wrapper_BuiltinUint16_initialize_ex(
    opendds_wrapper_BuiltinUint16* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return opendds_wrapper_BuiltinUint16_initialize_w_params(
        sample,&allocParams);

}

RTIBool opendds_wrapper_BuiltinUint16_initialize_w_params(
    opendds_wrapper_BuiltinUint16* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->value = 0;

    return RTI_TRUE;
}

RTIBool opendds_wrapper_BuiltinUint16_finalize(
    opendds_wrapper_BuiltinUint16* sample)
{

    opendds_wrapper_BuiltinUint16_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool opendds_wrapper_BuiltinUint16_finalize_w_return(
    opendds_wrapper_BuiltinUint16* sample)
{

    opendds_wrapper_BuiltinUint16_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void opendds_wrapper_BuiltinUint16_finalize_ex(
    opendds_wrapper_BuiltinUint16* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    opendds_wrapper_BuiltinUint16_finalize_w_params(
        sample,&deallocParams);
}

void opendds_wrapper_BuiltinUint16_finalize_w_params(
    opendds_wrapper_BuiltinUint16* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void opendds_wrapper_BuiltinUint16_finalize_optional_members(
    opendds_wrapper_BuiltinUint16* sample, RTIBool deletePointers)
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

RTIBool opendds_wrapper_BuiltinUint16_copy(
    opendds_wrapper_BuiltinUint16* dst,
    const opendds_wrapper_BuiltinUint16* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (&dst->value, &src->value);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'opendds_wrapper_BuiltinUint16' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinUint16
#define TSeq opendds_wrapper_BuiltinUint16Seq

#define T_initialize opendds_wrapper_BuiltinUint16_initialize

#define T_finalize   opendds_wrapper_BuiltinUint16_finalize
#define T_copy       opendds_wrapper_BuiltinUint16_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinUint16
#define TSeq opendds_wrapper_BuiltinUint16Seq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

opendds_wrapper_BuiltinUint32 *
opendds_wrapper_BuiltinUint32_create(void)
{
    opendds_wrapper_BuiltinUint32* sample;
    OSAPI_Heap_allocate_struct(&sample, opendds_wrapper_BuiltinUint32);
    if (sample != NULL) {
        if (!opendds_wrapper_BuiltinUint32_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
opendds_wrapper_BuiltinUint32_delete(opendds_wrapper_BuiltinUint32*sample)
{
    if (sample != NULL) {
        /* opendds_wrapper_BuiltinUint32_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        opendds_wrapper_BuiltinUint32_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *opendds_wrapper_BuiltinUint32TYPENAME = "opendds_wrapper::BuiltinUint32";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* opendds_wrapper_BuiltinUint32_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member opendds_wrapper_BuiltinUint32_g_tc_members[1]=
    {

        {
            (char *)"value",/* Member name */
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
        }
    };

    static DDS_TypeCode opendds_wrapper_BuiltinUint32_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"opendds_wrapper::BuiltinUint32", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            1, /* Number of members */
            opendds_wrapper_BuiltinUint32_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for opendds_wrapper_BuiltinUint32*/

    if (is_initialized) {
        return &opendds_wrapper_BuiltinUint32_g_tc;
    }

    opendds_wrapper_BuiltinUint32_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    opendds_wrapper_BuiltinUint32_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ulong;

    /* Initialize the values for member annotations. */
    opendds_wrapper_BuiltinUint32_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    opendds_wrapper_BuiltinUint32_g_tc_members[0]._annotations._defaultValue._u.ulong_value = 0u;
    opendds_wrapper_BuiltinUint32_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    opendds_wrapper_BuiltinUint32_g_tc_members[0]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    opendds_wrapper_BuiltinUint32_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    opendds_wrapper_BuiltinUint32_g_tc_members[0]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    opendds_wrapper_BuiltinUint32_g_tc._data._sampleAccessInfo =
    opendds_wrapper_BuiltinUint32_get_sample_access_info();
    opendds_wrapper_BuiltinUint32_g_tc._data._typePlugin =
    opendds_wrapper_BuiltinUint32_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &opendds_wrapper_BuiltinUint32_g_tc;
}

RTIXCdrSampleAccessInfo *opendds_wrapper_BuiltinUint32_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    opendds_wrapper_BuiltinUint32 *sample;

    static RTIXCdrMemberAccessInfo opendds_wrapper_BuiltinUint32_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo opendds_wrapper_BuiltinUint32_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &opendds_wrapper_BuiltinUint32_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        opendds_wrapper_BuiltinUint32);
    if (sample == NULL) {
        return NULL;
    }

    opendds_wrapper_BuiltinUint32_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->value - (char *)sample);

    opendds_wrapper_BuiltinUint32_g_sampleAccessInfo.memberAccessInfos = 
    opendds_wrapper_BuiltinUint32_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(opendds_wrapper_BuiltinUint32);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            opendds_wrapper_BuiltinUint32_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            opendds_wrapper_BuiltinUint32_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    opendds_wrapper_BuiltinUint32_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &opendds_wrapper_BuiltinUint32_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *opendds_wrapper_BuiltinUint32_get_type_plugin_info()
{
    static RTIXCdrTypePlugin opendds_wrapper_BuiltinUint32_g_typePlugin = 
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
        opendds_wrapper_BuiltinUint32_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        opendds_wrapper_BuiltinUint32_finalize_w_return,
        NULL
    };

    return &opendds_wrapper_BuiltinUint32_g_typePlugin;
}
#endif

RTIBool opendds_wrapper_BuiltinUint32_initialize(
    opendds_wrapper_BuiltinUint32* sample) {
    return opendds_wrapper_BuiltinUint32_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool opendds_wrapper_BuiltinUint32_initialize_ex(
    opendds_wrapper_BuiltinUint32* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return opendds_wrapper_BuiltinUint32_initialize_w_params(
        sample,&allocParams);

}

RTIBool opendds_wrapper_BuiltinUint32_initialize_w_params(
    opendds_wrapper_BuiltinUint32* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->value = 0u;

    return RTI_TRUE;
}

RTIBool opendds_wrapper_BuiltinUint32_finalize(
    opendds_wrapper_BuiltinUint32* sample)
{

    opendds_wrapper_BuiltinUint32_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool opendds_wrapper_BuiltinUint32_finalize_w_return(
    opendds_wrapper_BuiltinUint32* sample)
{

    opendds_wrapper_BuiltinUint32_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void opendds_wrapper_BuiltinUint32_finalize_ex(
    opendds_wrapper_BuiltinUint32* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    opendds_wrapper_BuiltinUint32_finalize_w_params(
        sample,&deallocParams);
}

void opendds_wrapper_BuiltinUint32_finalize_w_params(
    opendds_wrapper_BuiltinUint32* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void opendds_wrapper_BuiltinUint32_finalize_optional_members(
    opendds_wrapper_BuiltinUint32* sample, RTIBool deletePointers)
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

RTIBool opendds_wrapper_BuiltinUint32_copy(
    opendds_wrapper_BuiltinUint32* dst,
    const opendds_wrapper_BuiltinUint32* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (&dst->value, &src->value);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'opendds_wrapper_BuiltinUint32' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinUint32
#define TSeq opendds_wrapper_BuiltinUint32Seq

#define T_initialize opendds_wrapper_BuiltinUint32_initialize

#define T_finalize   opendds_wrapper_BuiltinUint32_finalize
#define T_copy       opendds_wrapper_BuiltinUint32_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinUint32
#define TSeq opendds_wrapper_BuiltinUint32Seq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

opendds_wrapper_BuiltinUint64 *
opendds_wrapper_BuiltinUint64_create(void)
{
    opendds_wrapper_BuiltinUint64* sample;
    OSAPI_Heap_allocate_struct(&sample, opendds_wrapper_BuiltinUint64);
    if (sample != NULL) {
        if (!opendds_wrapper_BuiltinUint64_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
opendds_wrapper_BuiltinUint64_delete(opendds_wrapper_BuiltinUint64*sample)
{
    if (sample != NULL) {
        /* opendds_wrapper_BuiltinUint64_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        opendds_wrapper_BuiltinUint64_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *opendds_wrapper_BuiltinUint64TYPENAME = "opendds_wrapper::BuiltinUint64";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* opendds_wrapper_BuiltinUint64_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member opendds_wrapper_BuiltinUint64_g_tc_members[1]=
    {

        {
            (char *)"value",/* Member name */
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
        }
    };

    static DDS_TypeCode opendds_wrapper_BuiltinUint64_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"opendds_wrapper::BuiltinUint64", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            1, /* Number of members */
            opendds_wrapper_BuiltinUint64_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for opendds_wrapper_BuiltinUint64*/

    if (is_initialized) {
        return &opendds_wrapper_BuiltinUint64_g_tc;
    }

    opendds_wrapper_BuiltinUint64_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    opendds_wrapper_BuiltinUint64_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ulonglong;

    /* Initialize the values for member annotations. */
    opendds_wrapper_BuiltinUint64_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_ULONGLONG;
    opendds_wrapper_BuiltinUint64_g_tc_members[0]._annotations._defaultValue._u.ulong_long_value = 0ull;
    opendds_wrapper_BuiltinUint64_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_ULONGLONG;
    opendds_wrapper_BuiltinUint64_g_tc_members[0]._annotations._minValue._u.ulong_long_value = RTIXCdrUnsignedLongLong_MIN;
    opendds_wrapper_BuiltinUint64_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_ULONGLONG;
    opendds_wrapper_BuiltinUint64_g_tc_members[0]._annotations._maxValue._u.ulong_long_value = RTIXCdrUnsignedLongLong_MAX;

    opendds_wrapper_BuiltinUint64_g_tc._data._sampleAccessInfo =
    opendds_wrapper_BuiltinUint64_get_sample_access_info();
    opendds_wrapper_BuiltinUint64_g_tc._data._typePlugin =
    opendds_wrapper_BuiltinUint64_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &opendds_wrapper_BuiltinUint64_g_tc;
}

RTIXCdrSampleAccessInfo *opendds_wrapper_BuiltinUint64_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    opendds_wrapper_BuiltinUint64 *sample;

    static RTIXCdrMemberAccessInfo opendds_wrapper_BuiltinUint64_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo opendds_wrapper_BuiltinUint64_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &opendds_wrapper_BuiltinUint64_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        opendds_wrapper_BuiltinUint64);
    if (sample == NULL) {
        return NULL;
    }

    opendds_wrapper_BuiltinUint64_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->value - (char *)sample);

    opendds_wrapper_BuiltinUint64_g_sampleAccessInfo.memberAccessInfos = 
    opendds_wrapper_BuiltinUint64_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(opendds_wrapper_BuiltinUint64);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            opendds_wrapper_BuiltinUint64_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            opendds_wrapper_BuiltinUint64_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    opendds_wrapper_BuiltinUint64_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &opendds_wrapper_BuiltinUint64_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *opendds_wrapper_BuiltinUint64_get_type_plugin_info()
{
    static RTIXCdrTypePlugin opendds_wrapper_BuiltinUint64_g_typePlugin = 
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
        opendds_wrapper_BuiltinUint64_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        opendds_wrapper_BuiltinUint64_finalize_w_return,
        NULL
    };

    return &opendds_wrapper_BuiltinUint64_g_typePlugin;
}
#endif

RTIBool opendds_wrapper_BuiltinUint64_initialize(
    opendds_wrapper_BuiltinUint64* sample) {
    return opendds_wrapper_BuiltinUint64_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool opendds_wrapper_BuiltinUint64_initialize_ex(
    opendds_wrapper_BuiltinUint64* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return opendds_wrapper_BuiltinUint64_initialize_w_params(
        sample,&allocParams);

}

RTIBool opendds_wrapper_BuiltinUint64_initialize_w_params(
    opendds_wrapper_BuiltinUint64* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->value = 0ull;

    return RTI_TRUE;
}

RTIBool opendds_wrapper_BuiltinUint64_finalize(
    opendds_wrapper_BuiltinUint64* sample)
{

    opendds_wrapper_BuiltinUint64_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool opendds_wrapper_BuiltinUint64_finalize_w_return(
    opendds_wrapper_BuiltinUint64* sample)
{

    opendds_wrapper_BuiltinUint64_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void opendds_wrapper_BuiltinUint64_finalize_ex(
    opendds_wrapper_BuiltinUint64* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    opendds_wrapper_BuiltinUint64_finalize_w_params(
        sample,&deallocParams);
}

void opendds_wrapper_BuiltinUint64_finalize_w_params(
    opendds_wrapper_BuiltinUint64* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void opendds_wrapper_BuiltinUint64_finalize_optional_members(
    opendds_wrapper_BuiltinUint64* sample, RTIBool deletePointers)
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

RTIBool opendds_wrapper_BuiltinUint64_copy(
    opendds_wrapper_BuiltinUint64* dst,
    const opendds_wrapper_BuiltinUint64* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (&dst->value, &src->value);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'opendds_wrapper_BuiltinUint64' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinUint64
#define TSeq opendds_wrapper_BuiltinUint64Seq

#define T_initialize opendds_wrapper_BuiltinUint64_initialize

#define T_finalize   opendds_wrapper_BuiltinUint64_finalize
#define T_copy       opendds_wrapper_BuiltinUint64_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinUint64
#define TSeq opendds_wrapper_BuiltinUint64Seq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

opendds_wrapper_BuiltinFloat32 *
opendds_wrapper_BuiltinFloat32_create(void)
{
    opendds_wrapper_BuiltinFloat32* sample;
    OSAPI_Heap_allocate_struct(&sample, opendds_wrapper_BuiltinFloat32);
    if (sample != NULL) {
        if (!opendds_wrapper_BuiltinFloat32_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
opendds_wrapper_BuiltinFloat32_delete(opendds_wrapper_BuiltinFloat32*sample)
{
    if (sample != NULL) {
        /* opendds_wrapper_BuiltinFloat32_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        opendds_wrapper_BuiltinFloat32_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *opendds_wrapper_BuiltinFloat32TYPENAME = "opendds_wrapper::BuiltinFloat32";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* opendds_wrapper_BuiltinFloat32_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member opendds_wrapper_BuiltinFloat32_g_tc_members[1]=
    {

        {
            (char *)"value",/* Member name */
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
        }
    };

    static DDS_TypeCode opendds_wrapper_BuiltinFloat32_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"opendds_wrapper::BuiltinFloat32", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            1, /* Number of members */
            opendds_wrapper_BuiltinFloat32_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for opendds_wrapper_BuiltinFloat32*/

    if (is_initialized) {
        return &opendds_wrapper_BuiltinFloat32_g_tc;
    }

    opendds_wrapper_BuiltinFloat32_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    opendds_wrapper_BuiltinFloat32_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_float;

    /* Initialize the values for member annotations. */
    opendds_wrapper_BuiltinFloat32_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    opendds_wrapper_BuiltinFloat32_g_tc_members[0]._annotations._defaultValue._u.float_value = 0.0f;
    opendds_wrapper_BuiltinFloat32_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    opendds_wrapper_BuiltinFloat32_g_tc_members[0]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    opendds_wrapper_BuiltinFloat32_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    opendds_wrapper_BuiltinFloat32_g_tc_members[0]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    opendds_wrapper_BuiltinFloat32_g_tc._data._sampleAccessInfo =
    opendds_wrapper_BuiltinFloat32_get_sample_access_info();
    opendds_wrapper_BuiltinFloat32_g_tc._data._typePlugin =
    opendds_wrapper_BuiltinFloat32_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &opendds_wrapper_BuiltinFloat32_g_tc;
}

RTIXCdrSampleAccessInfo *opendds_wrapper_BuiltinFloat32_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    opendds_wrapper_BuiltinFloat32 *sample;

    static RTIXCdrMemberAccessInfo opendds_wrapper_BuiltinFloat32_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo opendds_wrapper_BuiltinFloat32_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &opendds_wrapper_BuiltinFloat32_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        opendds_wrapper_BuiltinFloat32);
    if (sample == NULL) {
        return NULL;
    }

    opendds_wrapper_BuiltinFloat32_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->value - (char *)sample);

    opendds_wrapper_BuiltinFloat32_g_sampleAccessInfo.memberAccessInfos = 
    opendds_wrapper_BuiltinFloat32_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(opendds_wrapper_BuiltinFloat32);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            opendds_wrapper_BuiltinFloat32_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            opendds_wrapper_BuiltinFloat32_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    opendds_wrapper_BuiltinFloat32_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &opendds_wrapper_BuiltinFloat32_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *opendds_wrapper_BuiltinFloat32_get_type_plugin_info()
{
    static RTIXCdrTypePlugin opendds_wrapper_BuiltinFloat32_g_typePlugin = 
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
        opendds_wrapper_BuiltinFloat32_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        opendds_wrapper_BuiltinFloat32_finalize_w_return,
        NULL
    };

    return &opendds_wrapper_BuiltinFloat32_g_typePlugin;
}
#endif

RTIBool opendds_wrapper_BuiltinFloat32_initialize(
    opendds_wrapper_BuiltinFloat32* sample) {
    return opendds_wrapper_BuiltinFloat32_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool opendds_wrapper_BuiltinFloat32_initialize_ex(
    opendds_wrapper_BuiltinFloat32* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return opendds_wrapper_BuiltinFloat32_initialize_w_params(
        sample,&allocParams);

}

RTIBool opendds_wrapper_BuiltinFloat32_initialize_w_params(
    opendds_wrapper_BuiltinFloat32* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->value = 0.0f;

    return RTI_TRUE;
}

RTIBool opendds_wrapper_BuiltinFloat32_finalize(
    opendds_wrapper_BuiltinFloat32* sample)
{

    opendds_wrapper_BuiltinFloat32_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool opendds_wrapper_BuiltinFloat32_finalize_w_return(
    opendds_wrapper_BuiltinFloat32* sample)
{

    opendds_wrapper_BuiltinFloat32_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void opendds_wrapper_BuiltinFloat32_finalize_ex(
    opendds_wrapper_BuiltinFloat32* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    opendds_wrapper_BuiltinFloat32_finalize_w_params(
        sample,&deallocParams);
}

void opendds_wrapper_BuiltinFloat32_finalize_w_params(
    opendds_wrapper_BuiltinFloat32* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void opendds_wrapper_BuiltinFloat32_finalize_optional_members(
    opendds_wrapper_BuiltinFloat32* sample, RTIBool deletePointers)
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

RTIBool opendds_wrapper_BuiltinFloat32_copy(
    opendds_wrapper_BuiltinFloat32* dst,
    const opendds_wrapper_BuiltinFloat32* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (&dst->value, &src->value);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'opendds_wrapper_BuiltinFloat32' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinFloat32
#define TSeq opendds_wrapper_BuiltinFloat32Seq

#define T_initialize opendds_wrapper_BuiltinFloat32_initialize

#define T_finalize   opendds_wrapper_BuiltinFloat32_finalize
#define T_copy       opendds_wrapper_BuiltinFloat32_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinFloat32
#define TSeq opendds_wrapper_BuiltinFloat32Seq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

opendds_wrapper_BuiltinFloat64 *
opendds_wrapper_BuiltinFloat64_create(void)
{
    opendds_wrapper_BuiltinFloat64* sample;
    OSAPI_Heap_allocate_struct(&sample, opendds_wrapper_BuiltinFloat64);
    if (sample != NULL) {
        if (!opendds_wrapper_BuiltinFloat64_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
opendds_wrapper_BuiltinFloat64_delete(opendds_wrapper_BuiltinFloat64*sample)
{
    if (sample != NULL) {
        /* opendds_wrapper_BuiltinFloat64_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        opendds_wrapper_BuiltinFloat64_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *opendds_wrapper_BuiltinFloat64TYPENAME = "opendds_wrapper::BuiltinFloat64";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* opendds_wrapper_BuiltinFloat64_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member opendds_wrapper_BuiltinFloat64_g_tc_members[1]=
    {

        {
            (char *)"value",/* Member name */
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
        }
    };

    static DDS_TypeCode opendds_wrapper_BuiltinFloat64_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"opendds_wrapper::BuiltinFloat64", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            1, /* Number of members */
            opendds_wrapper_BuiltinFloat64_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for opendds_wrapper_BuiltinFloat64*/

    if (is_initialized) {
        return &opendds_wrapper_BuiltinFloat64_g_tc;
    }

    opendds_wrapper_BuiltinFloat64_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    opendds_wrapper_BuiltinFloat64_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;

    /* Initialize the values for member annotations. */
    opendds_wrapper_BuiltinFloat64_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
    opendds_wrapper_BuiltinFloat64_g_tc_members[0]._annotations._defaultValue._u.double_value = 0.0;
    opendds_wrapper_BuiltinFloat64_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
    opendds_wrapper_BuiltinFloat64_g_tc_members[0]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
    opendds_wrapper_BuiltinFloat64_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
    opendds_wrapper_BuiltinFloat64_g_tc_members[0]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;

    opendds_wrapper_BuiltinFloat64_g_tc._data._sampleAccessInfo =
    opendds_wrapper_BuiltinFloat64_get_sample_access_info();
    opendds_wrapper_BuiltinFloat64_g_tc._data._typePlugin =
    opendds_wrapper_BuiltinFloat64_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &opendds_wrapper_BuiltinFloat64_g_tc;
}

RTIXCdrSampleAccessInfo *opendds_wrapper_BuiltinFloat64_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    opendds_wrapper_BuiltinFloat64 *sample;

    static RTIXCdrMemberAccessInfo opendds_wrapper_BuiltinFloat64_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo opendds_wrapper_BuiltinFloat64_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &opendds_wrapper_BuiltinFloat64_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        opendds_wrapper_BuiltinFloat64);
    if (sample == NULL) {
        return NULL;
    }

    opendds_wrapper_BuiltinFloat64_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->value - (char *)sample);

    opendds_wrapper_BuiltinFloat64_g_sampleAccessInfo.memberAccessInfos = 
    opendds_wrapper_BuiltinFloat64_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(opendds_wrapper_BuiltinFloat64);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            opendds_wrapper_BuiltinFloat64_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            opendds_wrapper_BuiltinFloat64_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    opendds_wrapper_BuiltinFloat64_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &opendds_wrapper_BuiltinFloat64_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *opendds_wrapper_BuiltinFloat64_get_type_plugin_info()
{
    static RTIXCdrTypePlugin opendds_wrapper_BuiltinFloat64_g_typePlugin = 
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
        opendds_wrapper_BuiltinFloat64_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        opendds_wrapper_BuiltinFloat64_finalize_w_return,
        NULL
    };

    return &opendds_wrapper_BuiltinFloat64_g_typePlugin;
}
#endif

RTIBool opendds_wrapper_BuiltinFloat64_initialize(
    opendds_wrapper_BuiltinFloat64* sample) {
    return opendds_wrapper_BuiltinFloat64_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool opendds_wrapper_BuiltinFloat64_initialize_ex(
    opendds_wrapper_BuiltinFloat64* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return opendds_wrapper_BuiltinFloat64_initialize_w_params(
        sample,&allocParams);

}

RTIBool opendds_wrapper_BuiltinFloat64_initialize_w_params(
    opendds_wrapper_BuiltinFloat64* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->value = 0.0;

    return RTI_TRUE;
}

RTIBool opendds_wrapper_BuiltinFloat64_finalize(
    opendds_wrapper_BuiltinFloat64* sample)
{

    opendds_wrapper_BuiltinFloat64_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool opendds_wrapper_BuiltinFloat64_finalize_w_return(
    opendds_wrapper_BuiltinFloat64* sample)
{

    opendds_wrapper_BuiltinFloat64_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void opendds_wrapper_BuiltinFloat64_finalize_ex(
    opendds_wrapper_BuiltinFloat64* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    opendds_wrapper_BuiltinFloat64_finalize_w_params(
        sample,&deallocParams);
}

void opendds_wrapper_BuiltinFloat64_finalize_w_params(
    opendds_wrapper_BuiltinFloat64* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void opendds_wrapper_BuiltinFloat64_finalize_optional_members(
    opendds_wrapper_BuiltinFloat64* sample, RTIBool deletePointers)
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

RTIBool opendds_wrapper_BuiltinFloat64_copy(
    opendds_wrapper_BuiltinFloat64* dst,
    const opendds_wrapper_BuiltinFloat64* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (&dst->value, &src->value);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'opendds_wrapper_BuiltinFloat64' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinFloat64
#define TSeq opendds_wrapper_BuiltinFloat64Seq

#define T_initialize opendds_wrapper_BuiltinFloat64_initialize

#define T_finalize   opendds_wrapper_BuiltinFloat64_finalize
#define T_copy       opendds_wrapper_BuiltinFloat64_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinFloat64
#define TSeq opendds_wrapper_BuiltinFloat64Seq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

opendds_wrapper_BuiltinString *
opendds_wrapper_BuiltinString_create(void)
{
    opendds_wrapper_BuiltinString* sample;
    OSAPI_Heap_allocate_struct(&sample, opendds_wrapper_BuiltinString);
    if (sample != NULL) {
        if (!opendds_wrapper_BuiltinString_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
opendds_wrapper_BuiltinString_delete(opendds_wrapper_BuiltinString*sample)
{
    if (sample != NULL) {
        /* opendds_wrapper_BuiltinString_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        opendds_wrapper_BuiltinString_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *opendds_wrapper_BuiltinStringTYPENAME = "opendds_wrapper::BuiltinString";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* opendds_wrapper_BuiltinString_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode opendds_wrapper_BuiltinString_g_tc_value_string = DDS_INITIALIZE_STRING_TYPECODE((255));

    static DDS_TypeCode_Member opendds_wrapper_BuiltinString_g_tc_members[1]=
    {

        {
            (char *)"value",/* Member name */
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
        }
    };

    static DDS_TypeCode opendds_wrapper_BuiltinString_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"opendds_wrapper::BuiltinString", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            1, /* Number of members */
            opendds_wrapper_BuiltinString_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for opendds_wrapper_BuiltinString*/

    if (is_initialized) {
        return &opendds_wrapper_BuiltinString_g_tc;
    }

    opendds_wrapper_BuiltinString_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    opendds_wrapper_BuiltinString_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&opendds_wrapper_BuiltinString_g_tc_value_string;

    /* Initialize the values for member annotations. */
    opendds_wrapper_BuiltinString_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_STRING;
    opendds_wrapper_BuiltinString_g_tc_members[0]._annotations._defaultValue._u.string_value = (DDS_Char *) "";

    opendds_wrapper_BuiltinString_g_tc._data._sampleAccessInfo =
    opendds_wrapper_BuiltinString_get_sample_access_info();
    opendds_wrapper_BuiltinString_g_tc._data._typePlugin =
    opendds_wrapper_BuiltinString_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &opendds_wrapper_BuiltinString_g_tc;
}

RTIXCdrSampleAccessInfo *opendds_wrapper_BuiltinString_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    opendds_wrapper_BuiltinString *sample;

    static RTIXCdrMemberAccessInfo opendds_wrapper_BuiltinString_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo opendds_wrapper_BuiltinString_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &opendds_wrapper_BuiltinString_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        opendds_wrapper_BuiltinString);
    if (sample == NULL) {
        return NULL;
    }

    opendds_wrapper_BuiltinString_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->value - (char *)sample);

    opendds_wrapper_BuiltinString_g_sampleAccessInfo.memberAccessInfos = 
    opendds_wrapper_BuiltinString_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(opendds_wrapper_BuiltinString);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            opendds_wrapper_BuiltinString_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            opendds_wrapper_BuiltinString_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    opendds_wrapper_BuiltinString_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &opendds_wrapper_BuiltinString_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *opendds_wrapper_BuiltinString_get_type_plugin_info()
{
    static RTIXCdrTypePlugin opendds_wrapper_BuiltinString_g_typePlugin = 
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
        opendds_wrapper_BuiltinString_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        opendds_wrapper_BuiltinString_finalize_w_return,
        NULL
    };

    return &opendds_wrapper_BuiltinString_g_typePlugin;
}
#endif

RTIBool opendds_wrapper_BuiltinString_initialize(
    opendds_wrapper_BuiltinString* sample) {
    return opendds_wrapper_BuiltinString_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool opendds_wrapper_BuiltinString_initialize_ex(
    opendds_wrapper_BuiltinString* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return opendds_wrapper_BuiltinString_initialize_w_params(
        sample,&allocParams);

}

RTIBool opendds_wrapper_BuiltinString_initialize_w_params(
    opendds_wrapper_BuiltinString* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    if (allocParams->allocate_memory) {
        const DDS_Char stringValue[] = "";
        const DDS_String temp = (const DDS_String)stringValue;  
        sample->value = DDS_String_alloc((255));  
        if (!CDR_String_copy(&sample->value, &temp, (255)))
        {
            return RTI_FALSE;
        }
        if (sample->value == NULL) {
            return RTI_FALSE;
        }
    } else {
        if (sample->value != NULL) {
            const DDS_Char stringValue[] = "";
            const DDS_String temp = (const DDS_String)stringValue;  
            if (!CDR_String_copy(&sample->value, &temp, (255)))
            {
                return RTI_FALSE;
            }
            if (sample->value == NULL) {
                return RTI_FALSE;
            }
        }
    }

    return RTI_TRUE;
}

RTIBool opendds_wrapper_BuiltinString_finalize(
    opendds_wrapper_BuiltinString* sample)
{

    opendds_wrapper_BuiltinString_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool opendds_wrapper_BuiltinString_finalize_w_return(
    opendds_wrapper_BuiltinString* sample)
{

    opendds_wrapper_BuiltinString_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void opendds_wrapper_BuiltinString_finalize_ex(
    opendds_wrapper_BuiltinString* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    opendds_wrapper_BuiltinString_finalize_w_params(
        sample,&deallocParams);
}

void opendds_wrapper_BuiltinString_finalize_w_params(
    opendds_wrapper_BuiltinString* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if (sample->value != NULL) {
        DDS_String_free(sample->value);
        sample->value=NULL;

    }
}

void opendds_wrapper_BuiltinString_finalize_optional_members(
    opendds_wrapper_BuiltinString* sample, RTIBool deletePointers)
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

RTIBool opendds_wrapper_BuiltinString_copy(
    opendds_wrapper_BuiltinString* dst,
    const opendds_wrapper_BuiltinString* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!DDS_String_copy (
        &dst->value, &src->value, 
        (255) + 1)){
        return RTI_FALSE;
    }

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'opendds_wrapper_BuiltinString' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinString
#define TSeq opendds_wrapper_BuiltinStringSeq

#define T_initialize opendds_wrapper_BuiltinString_initialize

#define T_finalize   opendds_wrapper_BuiltinString_finalize
#define T_copy       opendds_wrapper_BuiltinString_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinString
#define TSeq opendds_wrapper_BuiltinStringSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

opendds_wrapper_OctetSequence *
opendds_wrapper_OctetSequence_create(void)
{
    opendds_wrapper_OctetSequence* sample;
    OSAPI_Heap_allocate_struct(&sample, opendds_wrapper_OctetSequence);
    if (sample != NULL) {
        if (!opendds_wrapper_OctetSequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
opendds_wrapper_OctetSequence_delete(opendds_wrapper_OctetSequence*sample)
{
    if (sample != NULL) {
        /* opendds_wrapper_OctetSequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        opendds_wrapper_OctetSequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* opendds_wrapper_OctetSequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode opendds_wrapper_OctetSequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode opendds_wrapper_OctetSequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"opendds_wrapper::OctetSequence", /* Name */
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
        }}; /* Type code for  opendds_wrapper_OctetSequence */

    if (is_initialized) {
        return &opendds_wrapper_OctetSequence_g_tc;
    }

    opendds_wrapper_OctetSequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    opendds_wrapper_OctetSequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_octet;
    opendds_wrapper_OctetSequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    opendds_wrapper_OctetSequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& opendds_wrapper_OctetSequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    opendds_wrapper_OctetSequence_g_tc._data._sampleAccessInfo =
    opendds_wrapper_OctetSequence_get_sample_access_info();
    opendds_wrapper_OctetSequence_g_tc._data._typePlugin =
    opendds_wrapper_OctetSequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &opendds_wrapper_OctetSequence_g_tc;
}

RTIXCdrSampleAccessInfo *opendds_wrapper_OctetSequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo opendds_wrapper_OctetSequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo opendds_wrapper_OctetSequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &opendds_wrapper_OctetSequence_g_sampleAccessInfo;
    }

    opendds_wrapper_OctetSequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    opendds_wrapper_OctetSequence_g_sampleAccessInfo.memberAccessInfos = 
    opendds_wrapper_OctetSequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(opendds_wrapper_OctetSequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            opendds_wrapper_OctetSequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            opendds_wrapper_OctetSequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    opendds_wrapper_OctetSequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &opendds_wrapper_OctetSequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *opendds_wrapper_OctetSequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin opendds_wrapper_OctetSequence_g_typePlugin = 
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
        opendds_wrapper_OctetSequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        opendds_wrapper_OctetSequence_finalize_w_return,
        NULL
    };

    return &opendds_wrapper_OctetSequence_g_typePlugin;
}
#endif

RTIBool opendds_wrapper_OctetSequence_initialize(
    opendds_wrapper_OctetSequence* sample) {
    return opendds_wrapper_OctetSequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool opendds_wrapper_OctetSequence_initialize_ex(
    opendds_wrapper_OctetSequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return opendds_wrapper_OctetSequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool opendds_wrapper_OctetSequence_initialize_w_params(
    opendds_wrapper_OctetSequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!DDS_OctetSeq_initialize(sample  )){
            return RTI_FALSE;
        }
        if (!DDS_OctetSeq_set_maximum(sample , (100) )) {
            return RTI_FALSE;
        }
    } else { 
        if(!DDS_OctetSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool opendds_wrapper_OctetSequence_finalize(
    opendds_wrapper_OctetSequence* sample)
{

    opendds_wrapper_OctetSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool opendds_wrapper_OctetSequence_finalize_w_return(
    opendds_wrapper_OctetSequence* sample)
{

    opendds_wrapper_OctetSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void opendds_wrapper_OctetSequence_finalize_ex(
    opendds_wrapper_OctetSequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    opendds_wrapper_OctetSequence_finalize_w_params(
        sample,&deallocParams);
}

void opendds_wrapper_OctetSequence_finalize_w_params(
    opendds_wrapper_OctetSequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!DDS_OctetSeq_finalize(sample)){
        return;
    }

}

void opendds_wrapper_OctetSequence_finalize_optional_members(
    opendds_wrapper_OctetSequence* sample, RTIBool deletePointers)
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

RTIBool opendds_wrapper_OctetSequence_copy(
    opendds_wrapper_OctetSequence* dst,
    const opendds_wrapper_OctetSequence* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!DDS_OctetSeq_copy(dst ,
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
* Configure and implement 'opendds_wrapper_OctetSequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_OctetSequence
#define TSeq opendds_wrapper_OctetSequenceSeq

#define T_initialize opendds_wrapper_OctetSequence_initialize

#define T_finalize   opendds_wrapper_OctetSequence_finalize
#define T_copy       opendds_wrapper_OctetSequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_OctetSequence
#define TSeq opendds_wrapper_OctetSequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

opendds_wrapper_BuiltinBuffer *
opendds_wrapper_BuiltinBuffer_create(void)
{
    opendds_wrapper_BuiltinBuffer* sample;
    OSAPI_Heap_allocate_struct(&sample, opendds_wrapper_BuiltinBuffer);
    if (sample != NULL) {
        if (!opendds_wrapper_BuiltinBuffer_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
opendds_wrapper_BuiltinBuffer_delete(opendds_wrapper_BuiltinBuffer*sample)
{
    if (sample != NULL) {
        /* opendds_wrapper_BuiltinBuffer_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        opendds_wrapper_BuiltinBuffer_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *opendds_wrapper_BuiltinBufferTYPENAME = "opendds_wrapper::BuiltinBuffer";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* opendds_wrapper_BuiltinBuffer_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member opendds_wrapper_BuiltinBuffer_g_tc_members[1]=
    {

        {
            (char *)"value",/* Member name */
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
        }
    };

    static DDS_TypeCode opendds_wrapper_BuiltinBuffer_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"opendds_wrapper::BuiltinBuffer", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            1, /* Number of members */
            opendds_wrapper_BuiltinBuffer_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for opendds_wrapper_BuiltinBuffer*/

    if (is_initialized) {
        return &opendds_wrapper_BuiltinBuffer_g_tc;
    }

    opendds_wrapper_BuiltinBuffer_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    opendds_wrapper_BuiltinBuffer_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)opendds_wrapper_OctetSequence_get_typecode();

    /* Initialize the values for member annotations. */

    opendds_wrapper_BuiltinBuffer_g_tc._data._sampleAccessInfo =
    opendds_wrapper_BuiltinBuffer_get_sample_access_info();
    opendds_wrapper_BuiltinBuffer_g_tc._data._typePlugin =
    opendds_wrapper_BuiltinBuffer_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &opendds_wrapper_BuiltinBuffer_g_tc;
}

RTIXCdrSampleAccessInfo *opendds_wrapper_BuiltinBuffer_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    opendds_wrapper_BuiltinBuffer *sample;

    static RTIXCdrMemberAccessInfo opendds_wrapper_BuiltinBuffer_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo opendds_wrapper_BuiltinBuffer_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &opendds_wrapper_BuiltinBuffer_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        opendds_wrapper_BuiltinBuffer);
    if (sample == NULL) {
        return NULL;
    }

    opendds_wrapper_BuiltinBuffer_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->value - (char *)sample);

    opendds_wrapper_BuiltinBuffer_g_sampleAccessInfo.memberAccessInfos = 
    opendds_wrapper_BuiltinBuffer_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(opendds_wrapper_BuiltinBuffer);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            opendds_wrapper_BuiltinBuffer_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            opendds_wrapper_BuiltinBuffer_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    opendds_wrapper_BuiltinBuffer_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &opendds_wrapper_BuiltinBuffer_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *opendds_wrapper_BuiltinBuffer_get_type_plugin_info()
{
    static RTIXCdrTypePlugin opendds_wrapper_BuiltinBuffer_g_typePlugin = 
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
        opendds_wrapper_BuiltinBuffer_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        opendds_wrapper_BuiltinBuffer_finalize_w_return,
        NULL
    };

    return &opendds_wrapper_BuiltinBuffer_g_typePlugin;
}
#endif

RTIBool opendds_wrapper_BuiltinBuffer_initialize(
    opendds_wrapper_BuiltinBuffer* sample) {
    return opendds_wrapper_BuiltinBuffer_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool opendds_wrapper_BuiltinBuffer_initialize_ex(
    opendds_wrapper_BuiltinBuffer* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return opendds_wrapper_BuiltinBuffer_initialize_w_params(
        sample,&allocParams);

}

RTIBool opendds_wrapper_BuiltinBuffer_initialize_w_params(
    opendds_wrapper_BuiltinBuffer* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    if (!opendds_wrapper_OctetSequence_initialize_w_params(&sample->value,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool opendds_wrapper_BuiltinBuffer_finalize(
    opendds_wrapper_BuiltinBuffer* sample)
{

    opendds_wrapper_BuiltinBuffer_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool opendds_wrapper_BuiltinBuffer_finalize_w_return(
    opendds_wrapper_BuiltinBuffer* sample)
{

    opendds_wrapper_BuiltinBuffer_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void opendds_wrapper_BuiltinBuffer_finalize_ex(
    opendds_wrapper_BuiltinBuffer* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    opendds_wrapper_BuiltinBuffer_finalize_w_params(
        sample,&deallocParams);
}

void opendds_wrapper_BuiltinBuffer_finalize_w_params(
    opendds_wrapper_BuiltinBuffer* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    opendds_wrapper_OctetSequence_finalize_w_params(&sample->value,deallocParams);

}

void opendds_wrapper_BuiltinBuffer_finalize_optional_members(
    opendds_wrapper_BuiltinBuffer* sample, RTIBool deletePointers)
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

    opendds_wrapper_OctetSequence_finalize_optional_members(&sample->value, deallocParams->delete_pointers);
}

RTIBool opendds_wrapper_BuiltinBuffer_copy(
    opendds_wrapper_BuiltinBuffer* dst,
    const opendds_wrapper_BuiltinBuffer* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!opendds_wrapper_OctetSequence_copy(
        &dst->value,(const opendds_wrapper_OctetSequence*)&src->value)) {
        return RTI_FALSE;
    } 

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'opendds_wrapper_BuiltinBuffer' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinBuffer
#define TSeq opendds_wrapper_BuiltinBufferSeq

#define T_initialize opendds_wrapper_BuiltinBuffer_initialize

#define T_finalize   opendds_wrapper_BuiltinBuffer_finalize
#define T_copy       opendds_wrapper_BuiltinBuffer_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinBuffer
#define TSeq opendds_wrapper_BuiltinBufferSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

