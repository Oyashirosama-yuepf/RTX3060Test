/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from PointFeaturefList.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "PointFeaturefList.h"

#ifndef UNUSED_ARG
#define UNUSED_ARG(x) (void)(x)
#endif

#include "dds_c/dds_c_typecode.h"
/*** SOURCE_BEGIN ***/

holo_base_msg_common_PointFeaturefVector *
holo_base_msg_common_PointFeaturefVector_create(void)
{
    holo_base_msg_common_PointFeaturefVector* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_PointFeaturefVector);
    if (sample != NULL) {
        if (!holo_base_msg_common_PointFeaturefVector_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_PointFeaturefVector_delete(holo_base_msg_common_PointFeaturefVector*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_PointFeaturefVector_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_PointFeaturefVector_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_PointFeaturefVector_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_common_PointFeaturefVector_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_common_PointFeaturefVector_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::common::PointFeaturefVector", /* Name */
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
        }}; /* Type code for  holo_base_msg_common_PointFeaturefVector */

    if (is_initialized) {
        return &holo_base_msg_common_PointFeaturefVector_g_tc;
    }

    holo_base_msg_common_PointFeaturefVector_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_PointFeaturefVector_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_common_PointFeaturef_get_typecode();
    holo_base_msg_common_PointFeaturefVector_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_common_PointFeaturefVector_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_common_PointFeaturefVector_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_common_PointFeaturefVector_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_PointFeaturefVector_get_sample_access_info();
    holo_base_msg_common_PointFeaturefVector_g_tc._data._typePlugin =
    holo_base_msg_common_PointFeaturefVector_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_PointFeaturefVector_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_PointFeaturefVector_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_PointFeaturefVector_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_PointFeaturefVector_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_PointFeaturefVector_g_sampleAccessInfo;
    }

    holo_base_msg_common_PointFeaturefVector_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_common_PointFeaturefVector_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_PointFeaturefVector_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_PointFeaturefVector);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_PointFeaturefVector_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_PointFeaturefVector_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_PointFeaturefVector_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_PointFeaturefVector_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_PointFeaturefVector_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_PointFeaturefVector_g_typePlugin = 
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
        holo_base_msg_common_PointFeaturefVector_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_PointFeaturefVector_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_PointFeaturefVector_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_PointFeaturefVector_initialize(
    holo_base_msg_common_PointFeaturefVector* sample) {
    return holo_base_msg_common_PointFeaturefVector_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_PointFeaturefVector_initialize_ex(
    holo_base_msg_common_PointFeaturefVector* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_PointFeaturefVector_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_PointFeaturefVector_initialize_w_params(
    holo_base_msg_common_PointFeaturefVector* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!holo_base_msg_common_PointFeaturefSeq_initialize(sample )){
            return RTI_FALSE;
        };
        if (!holo_base_msg_common_PointFeaturefSeq_set_maximum(sample, (100))) {
            return RTI_FALSE;
        }
    } else { 
        if(!holo_base_msg_common_PointFeaturefSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_PointFeaturefVector_finalize(
    holo_base_msg_common_PointFeaturefVector* sample)
{

    holo_base_msg_common_PointFeaturefVector_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_PointFeaturefVector_finalize_w_return(
    holo_base_msg_common_PointFeaturefVector* sample)
{

    holo_base_msg_common_PointFeaturefVector_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_PointFeaturefVector_finalize_ex(
    holo_base_msg_common_PointFeaturefVector* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_PointFeaturefVector_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_PointFeaturefVector_finalize_w_params(
    holo_base_msg_common_PointFeaturefVector* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!holo_base_msg_common_PointFeaturefSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_common_PointFeaturefVector_finalize_optional_members(
    holo_base_msg_common_PointFeaturefVector* sample, RTIBool deletePointers)
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
        length = (RTI_UINT32)holo_base_msg_common_PointFeaturefSeq_get_length(
            sample);

        for (i = 0; i < length; i++) {
            holo_base_msg_common_PointFeaturef_finalize_optional_members(
                holo_base_msg_common_PointFeaturefSeq_get_reference(
                    sample, (RTI_INT32)i), deallocParams->delete_pointers);
        }
    }  

}

RTIBool holo_base_msg_common_PointFeaturefVector_copy(
    holo_base_msg_common_PointFeaturefVector* dst,
    const holo_base_msg_common_PointFeaturefVector* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_PointFeaturefSeq_copy(dst ,
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
* Configure and implement 'holo_base_msg_common_PointFeaturefVector' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PointFeaturefVector
#define TSeq holo_base_msg_common_PointFeaturefVectorSeq

#define T_initialize holo_base_msg_common_PointFeaturefVector_initialize

#define T_finalize   holo_base_msg_common_PointFeaturefVector_finalize
#define T_copy       holo_base_msg_common_PointFeaturefVector_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PointFeaturefVector
#define TSeq holo_base_msg_common_PointFeaturefVectorSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_common_PointFeaturefList *
holo_base_msg_common_PointFeaturefList_create(void)
{
    holo_base_msg_common_PointFeaturefList* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_common_PointFeaturefList);
    if (sample != NULL) {
        if (!holo_base_msg_common_PointFeaturefList_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_common_PointFeaturefList_delete(holo_base_msg_common_PointFeaturefList*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_common_PointFeaturefList_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_common_PointFeaturefList_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_common_PointFeaturefListTYPENAME = "holo_base_msg::common::PointFeaturefList";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_common_PointFeaturefList_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_common_PointFeaturefList_g_tc_members[3]=
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
            (char *)"sensor_id",/* Member name */
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
            (char *)"point_feature_list",/* Member name */
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

    static DDS_TypeCode holo_base_msg_common_PointFeaturefList_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::common::PointFeaturefList", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            3, /* Number of members */
            holo_base_msg_common_PointFeaturefList_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_common_PointFeaturefList*/

    if (is_initialized) {
        return &holo_base_msg_common_PointFeaturefList_g_tc;
    }

    holo_base_msg_common_PointFeaturefList_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_common_PointFeaturefList_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_Timestamp_get_typecode();
    holo_base_msg_common_PointFeaturefList_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_SensorId_get_typecode();
    holo_base_msg_common_PointFeaturefList_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_common_PointFeaturefVector_get_typecode();

    /* Initialize the values for member annotations. */

    holo_base_msg_common_PointFeaturefList_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_PointFeaturefList_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_common_PointFeaturefList_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_PointFeaturefList_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_common_PointFeaturefList_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_common_PointFeaturefList_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_common_PointFeaturefList_g_tc._data._sampleAccessInfo =
    holo_base_msg_common_PointFeaturefList_get_sample_access_info();
    holo_base_msg_common_PointFeaturefList_g_tc._data._typePlugin =
    holo_base_msg_common_PointFeaturefList_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_common_PointFeaturefList_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_common_PointFeaturefList_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_common_PointFeaturefList *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_common_PointFeaturefList_g_memberAccessInfos[3] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_common_PointFeaturefList_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_PointFeaturefList_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_common_PointFeaturefList);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_common_PointFeaturefList_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->stamp - (char *)sample);

    holo_base_msg_common_PointFeaturefList_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->sensor_id - (char *)sample);

    holo_base_msg_common_PointFeaturefList_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->point_feature_list - (char *)sample);

    holo_base_msg_common_PointFeaturefList_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_common_PointFeaturefList_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_common_PointFeaturefList);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_common_PointFeaturefList_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_common_PointFeaturefList_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_common_PointFeaturefList_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_common_PointFeaturefList_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_common_PointFeaturefList_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_common_PointFeaturefList_g_typePlugin = 
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
        holo_base_msg_common_PointFeaturefList_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_common_PointFeaturefList_finalize_w_return,
        NULL
    };

    return &holo_base_msg_common_PointFeaturefList_g_typePlugin;
}
#endif

RTIBool holo_base_msg_common_PointFeaturefList_initialize(
    holo_base_msg_common_PointFeaturefList* sample) {
    return holo_base_msg_common_PointFeaturefList_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_common_PointFeaturefList_initialize_ex(
    holo_base_msg_common_PointFeaturefList* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_common_PointFeaturefList_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_common_PointFeaturefList_initialize_w_params(
    holo_base_msg_common_PointFeaturefList* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

    sample->sensor_id = 0u;

    if (!holo_base_msg_common_PointFeaturefVector_initialize_w_params(&sample->point_feature_list,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_PointFeaturefList_finalize(
    holo_base_msg_common_PointFeaturefList* sample)
{

    holo_base_msg_common_PointFeaturefList_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_common_PointFeaturefList_finalize_w_return(
    holo_base_msg_common_PointFeaturefList* sample)
{

    holo_base_msg_common_PointFeaturefList_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_common_PointFeaturefList_finalize_ex(
    holo_base_msg_common_PointFeaturefList* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_common_PointFeaturefList_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_common_PointFeaturefList_finalize_w_params(
    holo_base_msg_common_PointFeaturefList* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_common_Timestamp_finalize_w_params(&sample->stamp,deallocParams);

    holo_base_msg_common_PointFeaturefVector_finalize_w_params(&sample->point_feature_list,deallocParams);

}

void holo_base_msg_common_PointFeaturefList_finalize_optional_members(
    holo_base_msg_common_PointFeaturefList* sample, RTIBool deletePointers)
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
    holo_base_msg_common_PointFeaturefVector_finalize_optional_members(&sample->point_feature_list, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_common_PointFeaturefList_copy(
    holo_base_msg_common_PointFeaturefList* dst,
    const holo_base_msg_common_PointFeaturefList* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!holo_base_msg_common_Timestamp_copy(
        &dst->stamp,(const holo_base_msg_common_Timestamp*)&src->stamp)) {
        return RTI_FALSE;
    } 
    DDS_Primitive_copy (&dst->sensor_id, &src->sensor_id);
    if (!holo_base_msg_common_PointFeaturefVector_copy(
        &dst->point_feature_list,(const holo_base_msg_common_PointFeaturefVector*)&src->point_feature_list)) {
        return RTI_FALSE;
    } 

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_common_PointFeaturefList' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PointFeaturefList
#define TSeq holo_base_msg_common_PointFeaturefListSeq

#define T_initialize holo_base_msg_common_PointFeaturefList_initialize

#define T_finalize   holo_base_msg_common_PointFeaturefList_finalize
#define T_copy       holo_base_msg_common_PointFeaturefList_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PointFeaturefList
#define TSeq holo_base_msg_common_PointFeaturefListSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

