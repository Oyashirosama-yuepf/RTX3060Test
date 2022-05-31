/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Matrix.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "Matrix.h"

#ifndef UNUSED_ARG
#define UNUSED_ARG(x) (void)(x)
#endif

#include "dds_c/dds_c_typecode.h"
/*** SOURCE_BEGIN ***/

holo_base_msg_numerics_MatrixdData *
holo_base_msg_numerics_MatrixdData_create(void)
{
    holo_base_msg_numerics_MatrixdData* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_numerics_MatrixdData);
    if (sample != NULL) {
        if (!holo_base_msg_numerics_MatrixdData_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_numerics_MatrixdData_delete(holo_base_msg_numerics_MatrixdData*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_numerics_MatrixdData_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_numerics_MatrixdData_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_numerics_MatrixdData_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_numerics_MatrixdData_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_numerics_MatrixdData_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::numerics::MatrixdData", /* Name */
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
        }}; /* Type code for  holo_base_msg_numerics_MatrixdData */

    if (is_initialized) {
        return &holo_base_msg_numerics_MatrixdData_g_tc;
    }

    holo_base_msg_numerics_MatrixdData_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_numerics_MatrixdData_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();
    holo_base_msg_numerics_MatrixdData_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_numerics_MatrixdData_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_numerics_MatrixdData_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_numerics_MatrixdData_g_tc._data._sampleAccessInfo =
    holo_base_msg_numerics_MatrixdData_get_sample_access_info();
    holo_base_msg_numerics_MatrixdData_g_tc._data._typePlugin =
    holo_base_msg_numerics_MatrixdData_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_numerics_MatrixdData_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_numerics_MatrixdData_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_numerics_MatrixdData_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_numerics_MatrixdData_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_MatrixdData_g_sampleAccessInfo;
    }

    holo_base_msg_numerics_MatrixdData_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_numerics_MatrixdData_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_numerics_MatrixdData_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_numerics_MatrixdData);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_numerics_MatrixdData_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_numerics_MatrixdData_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_numerics_MatrixdData_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_MatrixdData_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_numerics_MatrixdData_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_numerics_MatrixdData_g_typePlugin = 
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
        holo_base_msg_numerics_MatrixdData_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_numerics_MatrixdData_finalize_w_return,
        NULL
    };

    return &holo_base_msg_numerics_MatrixdData_g_typePlugin;
}
#endif

RTIBool holo_base_msg_numerics_MatrixdData_initialize(
    holo_base_msg_numerics_MatrixdData* sample) {
    return holo_base_msg_numerics_MatrixdData_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_numerics_MatrixdData_initialize_ex(
    holo_base_msg_numerics_MatrixdData* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_numerics_MatrixdData_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_numerics_MatrixdData_initialize_w_params(
    holo_base_msg_numerics_MatrixdData* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!DDS_DoubleSeq_initialize(sample  )){
            return RTI_FALSE;
        }
        if (!DDS_DoubleSeq_set_maximum(sample , (100) )) {
            return RTI_FALSE;
        }
    } else { 
        if(!DDS_DoubleSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_MatrixdData_finalize(
    holo_base_msg_numerics_MatrixdData* sample)
{

    holo_base_msg_numerics_MatrixdData_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_MatrixdData_finalize_w_return(
    holo_base_msg_numerics_MatrixdData* sample)
{

    holo_base_msg_numerics_MatrixdData_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_numerics_MatrixdData_finalize_ex(
    holo_base_msg_numerics_MatrixdData* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_numerics_MatrixdData_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_numerics_MatrixdData_finalize_w_params(
    holo_base_msg_numerics_MatrixdData* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!DDS_DoubleSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_numerics_MatrixdData_finalize_optional_members(
    holo_base_msg_numerics_MatrixdData* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_numerics_MatrixdData_copy(
    holo_base_msg_numerics_MatrixdData* dst,
    const holo_base_msg_numerics_MatrixdData* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!DDS_DoubleSeq_copy(dst ,
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
* Configure and implement 'holo_base_msg_numerics_MatrixdData' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_MatrixdData
#define TSeq holo_base_msg_numerics_MatrixdDataSeq

#define T_initialize holo_base_msg_numerics_MatrixdData_initialize

#define T_finalize   holo_base_msg_numerics_MatrixdData_finalize
#define T_copy       holo_base_msg_numerics_MatrixdData_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_MatrixdData
#define TSeq holo_base_msg_numerics_MatrixdDataSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_numerics_Matrixd *
holo_base_msg_numerics_Matrixd_create(void)
{
    holo_base_msg_numerics_Matrixd* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_numerics_Matrixd);
    if (sample != NULL) {
        if (!holo_base_msg_numerics_Matrixd_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_numerics_Matrixd_delete(holo_base_msg_numerics_Matrixd*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_numerics_Matrixd_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_numerics_Matrixd_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_numerics_MatrixdTYPENAME = "holo_base_msg::numerics::Matrixd";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_numerics_Matrixd_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_numerics_Matrixd_g_tc_members[3]=
    {

        {
            (char *)"rows",/* Member name */
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
            (char *)"cols",/* Member name */
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
            (char *)"data",/* Member name */
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

    static DDS_TypeCode holo_base_msg_numerics_Matrixd_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::numerics::Matrixd", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            3, /* Number of members */
            holo_base_msg_numerics_Matrixd_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_numerics_Matrixd*/

    if (is_initialized) {
        return &holo_base_msg_numerics_Matrixd_g_tc;
    }

    holo_base_msg_numerics_Matrixd_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_numerics_Matrixd_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_int32_t_get_typecode();
    holo_base_msg_numerics_Matrixd_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_int32_t_get_typecode();
    holo_base_msg_numerics_Matrixd_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_MatrixdData_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_numerics_Matrixd_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    holo_base_msg_numerics_Matrixd_g_tc_members[0]._annotations._defaultValue._u.long_value = 0;
    holo_base_msg_numerics_Matrixd_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_LONG;
    holo_base_msg_numerics_Matrixd_g_tc_members[0]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    holo_base_msg_numerics_Matrixd_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    holo_base_msg_numerics_Matrixd_g_tc_members[0]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    holo_base_msg_numerics_Matrixd_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    holo_base_msg_numerics_Matrixd_g_tc_members[1]._annotations._defaultValue._u.long_value = 0;
    holo_base_msg_numerics_Matrixd_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_LONG;
    holo_base_msg_numerics_Matrixd_g_tc_members[1]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    holo_base_msg_numerics_Matrixd_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    holo_base_msg_numerics_Matrixd_g_tc_members[1]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    holo_base_msg_numerics_Matrixd_g_tc._data._sampleAccessInfo =
    holo_base_msg_numerics_Matrixd_get_sample_access_info();
    holo_base_msg_numerics_Matrixd_g_tc._data._typePlugin =
    holo_base_msg_numerics_Matrixd_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_numerics_Matrixd_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_numerics_Matrixd_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_numerics_Matrixd *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_numerics_Matrixd_g_memberAccessInfos[3] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_numerics_Matrixd_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Matrixd_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_numerics_Matrixd);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_numerics_Matrixd_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->rows - (char *)sample);

    holo_base_msg_numerics_Matrixd_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->cols - (char *)sample);

    holo_base_msg_numerics_Matrixd_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->data - (char *)sample);

    holo_base_msg_numerics_Matrixd_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_numerics_Matrixd_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_numerics_Matrixd);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_numerics_Matrixd_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_numerics_Matrixd_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_numerics_Matrixd_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Matrixd_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_numerics_Matrixd_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_numerics_Matrixd_g_typePlugin = 
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
        holo_base_msg_numerics_Matrixd_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_numerics_Matrixd_finalize_w_return,
        NULL
    };

    return &holo_base_msg_numerics_Matrixd_g_typePlugin;
}
#endif

RTIBool holo_base_msg_numerics_Matrixd_initialize(
    holo_base_msg_numerics_Matrixd* sample) {
    return holo_base_msg_numerics_Matrixd_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_numerics_Matrixd_initialize_ex(
    holo_base_msg_numerics_Matrixd* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_numerics_Matrixd_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_numerics_Matrixd_initialize_w_params(
    holo_base_msg_numerics_Matrixd* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->rows = 0;

    sample->cols = 0;

    if (!holo_base_msg_numerics_MatrixdData_initialize_w_params(&sample->data,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Matrixd_finalize(
    holo_base_msg_numerics_Matrixd* sample)
{

    holo_base_msg_numerics_Matrixd_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Matrixd_finalize_w_return(
    holo_base_msg_numerics_Matrixd* sample)
{

    holo_base_msg_numerics_Matrixd_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_numerics_Matrixd_finalize_ex(
    holo_base_msg_numerics_Matrixd* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_numerics_Matrixd_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_numerics_Matrixd_finalize_w_params(
    holo_base_msg_numerics_Matrixd* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_numerics_MatrixdData_finalize_w_params(&sample->data,deallocParams);

}

void holo_base_msg_numerics_Matrixd_finalize_optional_members(
    holo_base_msg_numerics_Matrixd* sample, RTIBool deletePointers)
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

    holo_base_msg_numerics_MatrixdData_finalize_optional_members(&sample->data, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_numerics_Matrixd_copy(
    holo_base_msg_numerics_Matrixd* dst,
    const holo_base_msg_numerics_Matrixd* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (&dst->rows, &src->rows);
    DDS_Primitive_copy (&dst->cols, &src->cols);
    if (!holo_base_msg_numerics_MatrixdData_copy(
        &dst->data,(const holo_base_msg_numerics_MatrixdData*)&src->data)) {
        return RTI_FALSE;
    } 

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_numerics_Matrixd' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrixd
#define TSeq holo_base_msg_numerics_MatrixdSeq

#define T_initialize holo_base_msg_numerics_Matrixd_initialize

#define T_finalize   holo_base_msg_numerics_Matrixd_finalize
#define T_copy       holo_base_msg_numerics_Matrixd_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrixd
#define TSeq holo_base_msg_numerics_MatrixdSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_numerics_Matrix22d *
holo_base_msg_numerics_Matrix22d_create(void)
{
    holo_base_msg_numerics_Matrix22d* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_numerics_Matrix22d);
    if (sample != NULL) {
        if (!holo_base_msg_numerics_Matrix22d_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_numerics_Matrix22d_delete(holo_base_msg_numerics_Matrix22d*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_numerics_Matrix22d_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_numerics_Matrix22d_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_numerics_Matrix22d_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;
    static DDS_UnsignedLong holo_base_msg_numerics_Matrix22d_g_tc_dimensions [2] = {2, 2} ;

    static DDS_TypeCode holo_base_msg_numerics_Matrix22d_g_tc_array =DDS_INITIALIZE_ARRAY_TYPECODE(2,2,holo_base_msg_numerics_Matrix22d_g_tc_dimensions,NULL);

    static DDS_TypeCode holo_base_msg_numerics_Matrix22d_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::numerics::Matrix22d", /* Name */
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
        }}; /* Type code for  holo_base_msg_numerics_Matrix22d */

    if (is_initialized) {
        return &holo_base_msg_numerics_Matrix22d_g_tc;
    }

    holo_base_msg_numerics_Matrix22d_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_numerics_Matrix22d_g_tc_array._data._typeCode =(RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();
    holo_base_msg_numerics_Matrix22d_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_numerics_Matrix22d_g_tc_array;

    /* Initialize the values for member annotations. */

    holo_base_msg_numerics_Matrix22d_g_tc._data._sampleAccessInfo =
    holo_base_msg_numerics_Matrix22d_get_sample_access_info();
    holo_base_msg_numerics_Matrix22d_g_tc._data._typePlugin =
    holo_base_msg_numerics_Matrix22d_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_numerics_Matrix22d_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_numerics_Matrix22d_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_numerics_Matrix22d_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_numerics_Matrix22d_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Matrix22d_g_sampleAccessInfo;
    }

    holo_base_msg_numerics_Matrix22d_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_numerics_Matrix22d_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_numerics_Matrix22d_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_numerics_Matrix22d);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_numerics_Matrix22d_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_numerics_Matrix22d_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_numerics_Matrix22d_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Matrix22d_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_numerics_Matrix22d_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_numerics_Matrix22d_g_typePlugin = 
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
        holo_base_msg_numerics_Matrix22d_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_numerics_Matrix22d_finalize_w_return,
        NULL
    };

    return &holo_base_msg_numerics_Matrix22d_g_typePlugin;
}
#endif

RTIBool holo_base_msg_numerics_Matrix22d_initialize(
    holo_base_msg_numerics_Matrix22d* sample) {
    return holo_base_msg_numerics_Matrix22d_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_numerics_Matrix22d_initialize_ex(
    holo_base_msg_numerics_Matrix22d* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_numerics_Matrix22d_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_numerics_Matrix22d_initialize_w_params(
    holo_base_msg_numerics_Matrix22d* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_init_array((*sample), ((2)*(2))* CDR_DOUBLE_SIZE);

    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Matrix22d_finalize(
    holo_base_msg_numerics_Matrix22d* sample)
{

    holo_base_msg_numerics_Matrix22d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Matrix22d_finalize_w_return(
    holo_base_msg_numerics_Matrix22d* sample)
{

    holo_base_msg_numerics_Matrix22d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_numerics_Matrix22d_finalize_ex(
    holo_base_msg_numerics_Matrix22d* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_numerics_Matrix22d_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_numerics_Matrix22d_finalize_w_params(
    holo_base_msg_numerics_Matrix22d* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_numerics_Matrix22d_finalize_optional_members(
    holo_base_msg_numerics_Matrix22d* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_numerics_Matrix22d_copy(
    holo_base_msg_numerics_Matrix22d* dst,
    const holo_base_msg_numerics_Matrix22d* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_copy_array((*dst) ,(*src),(2)*(2) * CDR_DOUBLE_SIZE);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_numerics_Matrix22d' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix22d
#define TSeq holo_base_msg_numerics_Matrix22dSeq

#define T_initialize holo_base_msg_numerics_Matrix22d_initialize

#define T_finalize   holo_base_msg_numerics_Matrix22d_finalize
#define T_copy       holo_base_msg_numerics_Matrix22d_copy

#define T_no_get  
#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix22d
#define TSeq holo_base_msg_numerics_Matrix22dSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_no_get  

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_numerics_Matrix33d *
holo_base_msg_numerics_Matrix33d_create(void)
{
    holo_base_msg_numerics_Matrix33d* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_numerics_Matrix33d);
    if (sample != NULL) {
        if (!holo_base_msg_numerics_Matrix33d_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_numerics_Matrix33d_delete(holo_base_msg_numerics_Matrix33d*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_numerics_Matrix33d_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_numerics_Matrix33d_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_numerics_Matrix33d_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;
    static DDS_UnsignedLong holo_base_msg_numerics_Matrix33d_g_tc_dimensions [2] = {3, 3} ;

    static DDS_TypeCode holo_base_msg_numerics_Matrix33d_g_tc_array =DDS_INITIALIZE_ARRAY_TYPECODE(2,3,holo_base_msg_numerics_Matrix33d_g_tc_dimensions,NULL);

    static DDS_TypeCode holo_base_msg_numerics_Matrix33d_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::numerics::Matrix33d", /* Name */
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
        }}; /* Type code for  holo_base_msg_numerics_Matrix33d */

    if (is_initialized) {
        return &holo_base_msg_numerics_Matrix33d_g_tc;
    }

    holo_base_msg_numerics_Matrix33d_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_numerics_Matrix33d_g_tc_array._data._typeCode =(RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();
    holo_base_msg_numerics_Matrix33d_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_numerics_Matrix33d_g_tc_array;

    /* Initialize the values for member annotations. */

    holo_base_msg_numerics_Matrix33d_g_tc._data._sampleAccessInfo =
    holo_base_msg_numerics_Matrix33d_get_sample_access_info();
    holo_base_msg_numerics_Matrix33d_g_tc._data._typePlugin =
    holo_base_msg_numerics_Matrix33d_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_numerics_Matrix33d_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_numerics_Matrix33d_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_numerics_Matrix33d_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_numerics_Matrix33d_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Matrix33d_g_sampleAccessInfo;
    }

    holo_base_msg_numerics_Matrix33d_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_numerics_Matrix33d_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_numerics_Matrix33d_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_numerics_Matrix33d);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_numerics_Matrix33d_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_numerics_Matrix33d_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_numerics_Matrix33d_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Matrix33d_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_numerics_Matrix33d_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_numerics_Matrix33d_g_typePlugin = 
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
        holo_base_msg_numerics_Matrix33d_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_numerics_Matrix33d_finalize_w_return,
        NULL
    };

    return &holo_base_msg_numerics_Matrix33d_g_typePlugin;
}
#endif

RTIBool holo_base_msg_numerics_Matrix33d_initialize(
    holo_base_msg_numerics_Matrix33d* sample) {
    return holo_base_msg_numerics_Matrix33d_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_numerics_Matrix33d_initialize_ex(
    holo_base_msg_numerics_Matrix33d* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_numerics_Matrix33d_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_numerics_Matrix33d_initialize_w_params(
    holo_base_msg_numerics_Matrix33d* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_init_array((*sample), ((3)*(3))* CDR_DOUBLE_SIZE);

    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Matrix33d_finalize(
    holo_base_msg_numerics_Matrix33d* sample)
{

    holo_base_msg_numerics_Matrix33d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Matrix33d_finalize_w_return(
    holo_base_msg_numerics_Matrix33d* sample)
{

    holo_base_msg_numerics_Matrix33d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_numerics_Matrix33d_finalize_ex(
    holo_base_msg_numerics_Matrix33d* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_numerics_Matrix33d_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_numerics_Matrix33d_finalize_w_params(
    holo_base_msg_numerics_Matrix33d* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_numerics_Matrix33d_finalize_optional_members(
    holo_base_msg_numerics_Matrix33d* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_numerics_Matrix33d_copy(
    holo_base_msg_numerics_Matrix33d* dst,
    const holo_base_msg_numerics_Matrix33d* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_copy_array((*dst) ,(*src),(3)*(3) * CDR_DOUBLE_SIZE);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_numerics_Matrix33d' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix33d
#define TSeq holo_base_msg_numerics_Matrix33dSeq

#define T_initialize holo_base_msg_numerics_Matrix33d_initialize

#define T_finalize   holo_base_msg_numerics_Matrix33d_finalize
#define T_copy       holo_base_msg_numerics_Matrix33d_copy

#define T_no_get  
#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix33d
#define TSeq holo_base_msg_numerics_Matrix33dSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_no_get  

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_numerics_Matrix44d *
holo_base_msg_numerics_Matrix44d_create(void)
{
    holo_base_msg_numerics_Matrix44d* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_numerics_Matrix44d);
    if (sample != NULL) {
        if (!holo_base_msg_numerics_Matrix44d_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_numerics_Matrix44d_delete(holo_base_msg_numerics_Matrix44d*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_numerics_Matrix44d_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_numerics_Matrix44d_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_numerics_Matrix44d_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;
    static DDS_UnsignedLong holo_base_msg_numerics_Matrix44d_g_tc_dimensions [2] = {4, 4} ;

    static DDS_TypeCode holo_base_msg_numerics_Matrix44d_g_tc_array =DDS_INITIALIZE_ARRAY_TYPECODE(2,4,holo_base_msg_numerics_Matrix44d_g_tc_dimensions,NULL);

    static DDS_TypeCode holo_base_msg_numerics_Matrix44d_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::numerics::Matrix44d", /* Name */
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
        }}; /* Type code for  holo_base_msg_numerics_Matrix44d */

    if (is_initialized) {
        return &holo_base_msg_numerics_Matrix44d_g_tc;
    }

    holo_base_msg_numerics_Matrix44d_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_numerics_Matrix44d_g_tc_array._data._typeCode =(RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();
    holo_base_msg_numerics_Matrix44d_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_numerics_Matrix44d_g_tc_array;

    /* Initialize the values for member annotations. */

    holo_base_msg_numerics_Matrix44d_g_tc._data._sampleAccessInfo =
    holo_base_msg_numerics_Matrix44d_get_sample_access_info();
    holo_base_msg_numerics_Matrix44d_g_tc._data._typePlugin =
    holo_base_msg_numerics_Matrix44d_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_numerics_Matrix44d_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_numerics_Matrix44d_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_numerics_Matrix44d_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_numerics_Matrix44d_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Matrix44d_g_sampleAccessInfo;
    }

    holo_base_msg_numerics_Matrix44d_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_numerics_Matrix44d_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_numerics_Matrix44d_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_numerics_Matrix44d);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_numerics_Matrix44d_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_numerics_Matrix44d_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_numerics_Matrix44d_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Matrix44d_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_numerics_Matrix44d_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_numerics_Matrix44d_g_typePlugin = 
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
        holo_base_msg_numerics_Matrix44d_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_numerics_Matrix44d_finalize_w_return,
        NULL
    };

    return &holo_base_msg_numerics_Matrix44d_g_typePlugin;
}
#endif

RTIBool holo_base_msg_numerics_Matrix44d_initialize(
    holo_base_msg_numerics_Matrix44d* sample) {
    return holo_base_msg_numerics_Matrix44d_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_numerics_Matrix44d_initialize_ex(
    holo_base_msg_numerics_Matrix44d* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_numerics_Matrix44d_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_numerics_Matrix44d_initialize_w_params(
    holo_base_msg_numerics_Matrix44d* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_init_array((*sample), ((4)*(4))* CDR_DOUBLE_SIZE);

    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Matrix44d_finalize(
    holo_base_msg_numerics_Matrix44d* sample)
{

    holo_base_msg_numerics_Matrix44d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Matrix44d_finalize_w_return(
    holo_base_msg_numerics_Matrix44d* sample)
{

    holo_base_msg_numerics_Matrix44d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_numerics_Matrix44d_finalize_ex(
    holo_base_msg_numerics_Matrix44d* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_numerics_Matrix44d_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_numerics_Matrix44d_finalize_w_params(
    holo_base_msg_numerics_Matrix44d* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_numerics_Matrix44d_finalize_optional_members(
    holo_base_msg_numerics_Matrix44d* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_numerics_Matrix44d_copy(
    holo_base_msg_numerics_Matrix44d* dst,
    const holo_base_msg_numerics_Matrix44d* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_copy_array((*dst) ,(*src),(4)*(4) * CDR_DOUBLE_SIZE);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_numerics_Matrix44d' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix44d
#define TSeq holo_base_msg_numerics_Matrix44dSeq

#define T_initialize holo_base_msg_numerics_Matrix44d_initialize

#define T_finalize   holo_base_msg_numerics_Matrix44d_finalize
#define T_copy       holo_base_msg_numerics_Matrix44d_copy

#define T_no_get  
#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix44d
#define TSeq holo_base_msg_numerics_Matrix44dSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_no_get  

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_numerics_Matrix55d *
holo_base_msg_numerics_Matrix55d_create(void)
{
    holo_base_msg_numerics_Matrix55d* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_numerics_Matrix55d);
    if (sample != NULL) {
        if (!holo_base_msg_numerics_Matrix55d_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_numerics_Matrix55d_delete(holo_base_msg_numerics_Matrix55d*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_numerics_Matrix55d_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_numerics_Matrix55d_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_numerics_Matrix55d_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;
    static DDS_UnsignedLong holo_base_msg_numerics_Matrix55d_g_tc_dimensions [2] = {5, 5} ;

    static DDS_TypeCode holo_base_msg_numerics_Matrix55d_g_tc_array =DDS_INITIALIZE_ARRAY_TYPECODE(2,5,holo_base_msg_numerics_Matrix55d_g_tc_dimensions,NULL);

    static DDS_TypeCode holo_base_msg_numerics_Matrix55d_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::numerics::Matrix55d", /* Name */
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
        }}; /* Type code for  holo_base_msg_numerics_Matrix55d */

    if (is_initialized) {
        return &holo_base_msg_numerics_Matrix55d_g_tc;
    }

    holo_base_msg_numerics_Matrix55d_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_numerics_Matrix55d_g_tc_array._data._typeCode =(RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();
    holo_base_msg_numerics_Matrix55d_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_numerics_Matrix55d_g_tc_array;

    /* Initialize the values for member annotations. */

    holo_base_msg_numerics_Matrix55d_g_tc._data._sampleAccessInfo =
    holo_base_msg_numerics_Matrix55d_get_sample_access_info();
    holo_base_msg_numerics_Matrix55d_g_tc._data._typePlugin =
    holo_base_msg_numerics_Matrix55d_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_numerics_Matrix55d_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_numerics_Matrix55d_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_numerics_Matrix55d_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_numerics_Matrix55d_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Matrix55d_g_sampleAccessInfo;
    }

    holo_base_msg_numerics_Matrix55d_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_numerics_Matrix55d_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_numerics_Matrix55d_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_numerics_Matrix55d);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_numerics_Matrix55d_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_numerics_Matrix55d_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_numerics_Matrix55d_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Matrix55d_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_numerics_Matrix55d_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_numerics_Matrix55d_g_typePlugin = 
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
        holo_base_msg_numerics_Matrix55d_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_numerics_Matrix55d_finalize_w_return,
        NULL
    };

    return &holo_base_msg_numerics_Matrix55d_g_typePlugin;
}
#endif

RTIBool holo_base_msg_numerics_Matrix55d_initialize(
    holo_base_msg_numerics_Matrix55d* sample) {
    return holo_base_msg_numerics_Matrix55d_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_numerics_Matrix55d_initialize_ex(
    holo_base_msg_numerics_Matrix55d* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_numerics_Matrix55d_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_numerics_Matrix55d_initialize_w_params(
    holo_base_msg_numerics_Matrix55d* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_init_array((*sample), ((5)*(5))* CDR_DOUBLE_SIZE);

    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Matrix55d_finalize(
    holo_base_msg_numerics_Matrix55d* sample)
{

    holo_base_msg_numerics_Matrix55d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Matrix55d_finalize_w_return(
    holo_base_msg_numerics_Matrix55d* sample)
{

    holo_base_msg_numerics_Matrix55d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_numerics_Matrix55d_finalize_ex(
    holo_base_msg_numerics_Matrix55d* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_numerics_Matrix55d_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_numerics_Matrix55d_finalize_w_params(
    holo_base_msg_numerics_Matrix55d* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_numerics_Matrix55d_finalize_optional_members(
    holo_base_msg_numerics_Matrix55d* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_numerics_Matrix55d_copy(
    holo_base_msg_numerics_Matrix55d* dst,
    const holo_base_msg_numerics_Matrix55d* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_copy_array((*dst) ,(*src),(5)*(5) * CDR_DOUBLE_SIZE);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_numerics_Matrix55d' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix55d
#define TSeq holo_base_msg_numerics_Matrix55dSeq

#define T_initialize holo_base_msg_numerics_Matrix55d_initialize

#define T_finalize   holo_base_msg_numerics_Matrix55d_finalize
#define T_copy       holo_base_msg_numerics_Matrix55d_copy

#define T_no_get  
#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix55d
#define TSeq holo_base_msg_numerics_Matrix55dSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_no_get  

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_numerics_Matrix66d *
holo_base_msg_numerics_Matrix66d_create(void)
{
    holo_base_msg_numerics_Matrix66d* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_numerics_Matrix66d);
    if (sample != NULL) {
        if (!holo_base_msg_numerics_Matrix66d_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_numerics_Matrix66d_delete(holo_base_msg_numerics_Matrix66d*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_numerics_Matrix66d_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_numerics_Matrix66d_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_numerics_Matrix66d_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;
    static DDS_UnsignedLong holo_base_msg_numerics_Matrix66d_g_tc_dimensions [2] = {6, 6} ;

    static DDS_TypeCode holo_base_msg_numerics_Matrix66d_g_tc_array =DDS_INITIALIZE_ARRAY_TYPECODE(2,6,holo_base_msg_numerics_Matrix66d_g_tc_dimensions,NULL);

    static DDS_TypeCode holo_base_msg_numerics_Matrix66d_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::numerics::Matrix66d", /* Name */
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
        }}; /* Type code for  holo_base_msg_numerics_Matrix66d */

    if (is_initialized) {
        return &holo_base_msg_numerics_Matrix66d_g_tc;
    }

    holo_base_msg_numerics_Matrix66d_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_numerics_Matrix66d_g_tc_array._data._typeCode =(RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();
    holo_base_msg_numerics_Matrix66d_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_numerics_Matrix66d_g_tc_array;

    /* Initialize the values for member annotations. */

    holo_base_msg_numerics_Matrix66d_g_tc._data._sampleAccessInfo =
    holo_base_msg_numerics_Matrix66d_get_sample_access_info();
    holo_base_msg_numerics_Matrix66d_g_tc._data._typePlugin =
    holo_base_msg_numerics_Matrix66d_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_numerics_Matrix66d_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_numerics_Matrix66d_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_numerics_Matrix66d_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_numerics_Matrix66d_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Matrix66d_g_sampleAccessInfo;
    }

    holo_base_msg_numerics_Matrix66d_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_numerics_Matrix66d_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_numerics_Matrix66d_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_numerics_Matrix66d);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_numerics_Matrix66d_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_numerics_Matrix66d_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_numerics_Matrix66d_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Matrix66d_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_numerics_Matrix66d_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_numerics_Matrix66d_g_typePlugin = 
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
        holo_base_msg_numerics_Matrix66d_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_numerics_Matrix66d_finalize_w_return,
        NULL
    };

    return &holo_base_msg_numerics_Matrix66d_g_typePlugin;
}
#endif

RTIBool holo_base_msg_numerics_Matrix66d_initialize(
    holo_base_msg_numerics_Matrix66d* sample) {
    return holo_base_msg_numerics_Matrix66d_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_numerics_Matrix66d_initialize_ex(
    holo_base_msg_numerics_Matrix66d* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_numerics_Matrix66d_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_numerics_Matrix66d_initialize_w_params(
    holo_base_msg_numerics_Matrix66d* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_init_array((*sample), ((6)*(6))* CDR_DOUBLE_SIZE);

    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Matrix66d_finalize(
    holo_base_msg_numerics_Matrix66d* sample)
{

    holo_base_msg_numerics_Matrix66d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Matrix66d_finalize_w_return(
    holo_base_msg_numerics_Matrix66d* sample)
{

    holo_base_msg_numerics_Matrix66d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_numerics_Matrix66d_finalize_ex(
    holo_base_msg_numerics_Matrix66d* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_numerics_Matrix66d_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_numerics_Matrix66d_finalize_w_params(
    holo_base_msg_numerics_Matrix66d* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_numerics_Matrix66d_finalize_optional_members(
    holo_base_msg_numerics_Matrix66d* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_numerics_Matrix66d_copy(
    holo_base_msg_numerics_Matrix66d* dst,
    const holo_base_msg_numerics_Matrix66d* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_copy_array((*dst) ,(*src),(6)*(6) * CDR_DOUBLE_SIZE);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_numerics_Matrix66d' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix66d
#define TSeq holo_base_msg_numerics_Matrix66dSeq

#define T_initialize holo_base_msg_numerics_Matrix66d_initialize

#define T_finalize   holo_base_msg_numerics_Matrix66d_finalize
#define T_copy       holo_base_msg_numerics_Matrix66d_copy

#define T_no_get  
#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix66d
#define TSeq holo_base_msg_numerics_Matrix66dSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_no_get  

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_numerics_MatrixfData *
holo_base_msg_numerics_MatrixfData_create(void)
{
    holo_base_msg_numerics_MatrixfData* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_numerics_MatrixfData);
    if (sample != NULL) {
        if (!holo_base_msg_numerics_MatrixfData_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_numerics_MatrixfData_delete(holo_base_msg_numerics_MatrixfData*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_numerics_MatrixfData_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_numerics_MatrixfData_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_numerics_MatrixfData_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_numerics_MatrixfData_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_numerics_MatrixfData_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::numerics::MatrixfData", /* Name */
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
        }}; /* Type code for  holo_base_msg_numerics_MatrixfData */

    if (is_initialized) {
        return &holo_base_msg_numerics_MatrixfData_g_tc;
    }

    holo_base_msg_numerics_MatrixfData_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_numerics_MatrixfData_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_numerics_MatrixfData_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_numerics_MatrixfData_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_numerics_MatrixfData_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_numerics_MatrixfData_g_tc._data._sampleAccessInfo =
    holo_base_msg_numerics_MatrixfData_get_sample_access_info();
    holo_base_msg_numerics_MatrixfData_g_tc._data._typePlugin =
    holo_base_msg_numerics_MatrixfData_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_numerics_MatrixfData_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_numerics_MatrixfData_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_numerics_MatrixfData_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_numerics_MatrixfData_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_MatrixfData_g_sampleAccessInfo;
    }

    holo_base_msg_numerics_MatrixfData_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_numerics_MatrixfData_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_numerics_MatrixfData_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_numerics_MatrixfData);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_numerics_MatrixfData_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_numerics_MatrixfData_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_numerics_MatrixfData_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_MatrixfData_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_numerics_MatrixfData_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_numerics_MatrixfData_g_typePlugin = 
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
        holo_base_msg_numerics_MatrixfData_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_numerics_MatrixfData_finalize_w_return,
        NULL
    };

    return &holo_base_msg_numerics_MatrixfData_g_typePlugin;
}
#endif

RTIBool holo_base_msg_numerics_MatrixfData_initialize(
    holo_base_msg_numerics_MatrixfData* sample) {
    return holo_base_msg_numerics_MatrixfData_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_numerics_MatrixfData_initialize_ex(
    holo_base_msg_numerics_MatrixfData* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_numerics_MatrixfData_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_numerics_MatrixfData_initialize_w_params(
    holo_base_msg_numerics_MatrixfData* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!DDS_FloatSeq_initialize(sample  )){
            return RTI_FALSE;
        }
        if (!DDS_FloatSeq_set_maximum(sample , (100) )) {
            return RTI_FALSE;
        }
    } else { 
        if(!DDS_FloatSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_MatrixfData_finalize(
    holo_base_msg_numerics_MatrixfData* sample)
{

    holo_base_msg_numerics_MatrixfData_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_MatrixfData_finalize_w_return(
    holo_base_msg_numerics_MatrixfData* sample)
{

    holo_base_msg_numerics_MatrixfData_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_numerics_MatrixfData_finalize_ex(
    holo_base_msg_numerics_MatrixfData* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_numerics_MatrixfData_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_numerics_MatrixfData_finalize_w_params(
    holo_base_msg_numerics_MatrixfData* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!DDS_FloatSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_numerics_MatrixfData_finalize_optional_members(
    holo_base_msg_numerics_MatrixfData* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_numerics_MatrixfData_copy(
    holo_base_msg_numerics_MatrixfData* dst,
    const holo_base_msg_numerics_MatrixfData* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!DDS_FloatSeq_copy(dst ,
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
* Configure and implement 'holo_base_msg_numerics_MatrixfData' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_MatrixfData
#define TSeq holo_base_msg_numerics_MatrixfDataSeq

#define T_initialize holo_base_msg_numerics_MatrixfData_initialize

#define T_finalize   holo_base_msg_numerics_MatrixfData_finalize
#define T_copy       holo_base_msg_numerics_MatrixfData_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_MatrixfData
#define TSeq holo_base_msg_numerics_MatrixfDataSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_numerics_Matrixf *
holo_base_msg_numerics_Matrixf_create(void)
{
    holo_base_msg_numerics_Matrixf* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_numerics_Matrixf);
    if (sample != NULL) {
        if (!holo_base_msg_numerics_Matrixf_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_numerics_Matrixf_delete(holo_base_msg_numerics_Matrixf*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_numerics_Matrixf_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_numerics_Matrixf_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */
const char *holo_base_msg_numerics_MatrixfTYPENAME = "holo_base_msg::numerics::Matrixf";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_numerics_Matrixf_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member holo_base_msg_numerics_Matrixf_g_tc_members[3]=
    {

        {
            (char *)"rows",/* Member name */
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
            (char *)"cols",/* Member name */
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
            (char *)"data",/* Member name */
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

    static DDS_TypeCode holo_base_msg_numerics_Matrixf_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"holo_base_msg::numerics::Matrixf", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            3, /* Number of members */
            holo_base_msg_numerics_Matrixf_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for holo_base_msg_numerics_Matrixf*/

    if (is_initialized) {
        return &holo_base_msg_numerics_Matrixf_g_tc;
    }

    holo_base_msg_numerics_Matrixf_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_numerics_Matrixf_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_int32_t_get_typecode();
    holo_base_msg_numerics_Matrixf_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_core_int32_t_get_typecode();
    holo_base_msg_numerics_Matrixf_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)holo_base_msg_numerics_MatrixfData_get_typecode();

    /* Initialize the values for member annotations. */
    holo_base_msg_numerics_Matrixf_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    holo_base_msg_numerics_Matrixf_g_tc_members[0]._annotations._defaultValue._u.long_value = 0;
    holo_base_msg_numerics_Matrixf_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_LONG;
    holo_base_msg_numerics_Matrixf_g_tc_members[0]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    holo_base_msg_numerics_Matrixf_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    holo_base_msg_numerics_Matrixf_g_tc_members[0]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    holo_base_msg_numerics_Matrixf_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    holo_base_msg_numerics_Matrixf_g_tc_members[1]._annotations._defaultValue._u.long_value = 0;
    holo_base_msg_numerics_Matrixf_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_LONG;
    holo_base_msg_numerics_Matrixf_g_tc_members[1]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    holo_base_msg_numerics_Matrixf_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    holo_base_msg_numerics_Matrixf_g_tc_members[1]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    holo_base_msg_numerics_Matrixf_g_tc._data._sampleAccessInfo =
    holo_base_msg_numerics_Matrixf_get_sample_access_info();
    holo_base_msg_numerics_Matrixf_g_tc._data._typePlugin =
    holo_base_msg_numerics_Matrixf_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_numerics_Matrixf_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_numerics_Matrixf_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    holo_base_msg_numerics_Matrixf *sample;

    static RTIXCdrMemberAccessInfo holo_base_msg_numerics_Matrixf_g_memberAccessInfos[3] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_numerics_Matrixf_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Matrixf_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        holo_base_msg_numerics_Matrixf);
    if (sample == NULL) {
        return NULL;
    }

    holo_base_msg_numerics_Matrixf_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->rows - (char *)sample);

    holo_base_msg_numerics_Matrixf_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->cols - (char *)sample);

    holo_base_msg_numerics_Matrixf_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->data - (char *)sample);

    holo_base_msg_numerics_Matrixf_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_numerics_Matrixf_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_numerics_Matrixf);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_numerics_Matrixf_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_numerics_Matrixf_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_numerics_Matrixf_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Matrixf_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_numerics_Matrixf_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_numerics_Matrixf_g_typePlugin = 
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
        holo_base_msg_numerics_Matrixf_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_numerics_Matrixf_finalize_w_return,
        NULL
    };

    return &holo_base_msg_numerics_Matrixf_g_typePlugin;
}
#endif

RTIBool holo_base_msg_numerics_Matrixf_initialize(
    holo_base_msg_numerics_Matrixf* sample) {
    return holo_base_msg_numerics_Matrixf_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_numerics_Matrixf_initialize_ex(
    holo_base_msg_numerics_Matrixf* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_numerics_Matrixf_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_numerics_Matrixf_initialize_w_params(
    holo_base_msg_numerics_Matrixf* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->rows = 0;

    sample->cols = 0;

    if (!holo_base_msg_numerics_MatrixfData_initialize_w_params(&sample->data,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Matrixf_finalize(
    holo_base_msg_numerics_Matrixf* sample)
{

    holo_base_msg_numerics_Matrixf_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Matrixf_finalize_w_return(
    holo_base_msg_numerics_Matrixf* sample)
{

    holo_base_msg_numerics_Matrixf_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_numerics_Matrixf_finalize_ex(
    holo_base_msg_numerics_Matrixf* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_numerics_Matrixf_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_numerics_Matrixf_finalize_w_params(
    holo_base_msg_numerics_Matrixf* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    holo_base_msg_numerics_MatrixfData_finalize_w_params(&sample->data,deallocParams);

}

void holo_base_msg_numerics_Matrixf_finalize_optional_members(
    holo_base_msg_numerics_Matrixf* sample, RTIBool deletePointers)
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

    holo_base_msg_numerics_MatrixfData_finalize_optional_members(&sample->data, deallocParams->delete_pointers);
}

RTIBool holo_base_msg_numerics_Matrixf_copy(
    holo_base_msg_numerics_Matrixf* dst,
    const holo_base_msg_numerics_Matrixf* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (&dst->rows, &src->rows);
    DDS_Primitive_copy (&dst->cols, &src->cols);
    if (!holo_base_msg_numerics_MatrixfData_copy(
        &dst->data,(const holo_base_msg_numerics_MatrixfData*)&src->data)) {
        return RTI_FALSE;
    } 

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_numerics_Matrixf' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrixf
#define TSeq holo_base_msg_numerics_MatrixfSeq

#define T_initialize holo_base_msg_numerics_Matrixf_initialize

#define T_finalize   holo_base_msg_numerics_Matrixf_finalize
#define T_copy       holo_base_msg_numerics_Matrixf_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrixf
#define TSeq holo_base_msg_numerics_MatrixfSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_numerics_Matrix22f *
holo_base_msg_numerics_Matrix22f_create(void)
{
    holo_base_msg_numerics_Matrix22f* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_numerics_Matrix22f);
    if (sample != NULL) {
        if (!holo_base_msg_numerics_Matrix22f_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_numerics_Matrix22f_delete(holo_base_msg_numerics_Matrix22f*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_numerics_Matrix22f_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_numerics_Matrix22f_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_numerics_Matrix22f_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;
    static DDS_UnsignedLong holo_base_msg_numerics_Matrix22f_g_tc_dimensions [2] = {2, 2} ;

    static DDS_TypeCode holo_base_msg_numerics_Matrix22f_g_tc_array =DDS_INITIALIZE_ARRAY_TYPECODE(2,2,holo_base_msg_numerics_Matrix22f_g_tc_dimensions,NULL);

    static DDS_TypeCode holo_base_msg_numerics_Matrix22f_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::numerics::Matrix22f", /* Name */
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
        }}; /* Type code for  holo_base_msg_numerics_Matrix22f */

    if (is_initialized) {
        return &holo_base_msg_numerics_Matrix22f_g_tc;
    }

    holo_base_msg_numerics_Matrix22f_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_numerics_Matrix22f_g_tc_array._data._typeCode =(RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_numerics_Matrix22f_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_numerics_Matrix22f_g_tc_array;

    /* Initialize the values for member annotations. */

    holo_base_msg_numerics_Matrix22f_g_tc._data._sampleAccessInfo =
    holo_base_msg_numerics_Matrix22f_get_sample_access_info();
    holo_base_msg_numerics_Matrix22f_g_tc._data._typePlugin =
    holo_base_msg_numerics_Matrix22f_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_numerics_Matrix22f_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_numerics_Matrix22f_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_numerics_Matrix22f_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_numerics_Matrix22f_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Matrix22f_g_sampleAccessInfo;
    }

    holo_base_msg_numerics_Matrix22f_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_numerics_Matrix22f_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_numerics_Matrix22f_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_numerics_Matrix22f);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_numerics_Matrix22f_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_numerics_Matrix22f_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_numerics_Matrix22f_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Matrix22f_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_numerics_Matrix22f_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_numerics_Matrix22f_g_typePlugin = 
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
        holo_base_msg_numerics_Matrix22f_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_numerics_Matrix22f_finalize_w_return,
        NULL
    };

    return &holo_base_msg_numerics_Matrix22f_g_typePlugin;
}
#endif

RTIBool holo_base_msg_numerics_Matrix22f_initialize(
    holo_base_msg_numerics_Matrix22f* sample) {
    return holo_base_msg_numerics_Matrix22f_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_numerics_Matrix22f_initialize_ex(
    holo_base_msg_numerics_Matrix22f* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_numerics_Matrix22f_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_numerics_Matrix22f_initialize_w_params(
    holo_base_msg_numerics_Matrix22f* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_init_array((*sample), ((2)*(2))* CDR_FLOAT_SIZE);

    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Matrix22f_finalize(
    holo_base_msg_numerics_Matrix22f* sample)
{

    holo_base_msg_numerics_Matrix22f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Matrix22f_finalize_w_return(
    holo_base_msg_numerics_Matrix22f* sample)
{

    holo_base_msg_numerics_Matrix22f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_numerics_Matrix22f_finalize_ex(
    holo_base_msg_numerics_Matrix22f* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_numerics_Matrix22f_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_numerics_Matrix22f_finalize_w_params(
    holo_base_msg_numerics_Matrix22f* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_numerics_Matrix22f_finalize_optional_members(
    holo_base_msg_numerics_Matrix22f* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_numerics_Matrix22f_copy(
    holo_base_msg_numerics_Matrix22f* dst,
    const holo_base_msg_numerics_Matrix22f* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_copy_array((*dst) ,(*src),(2)*(2) * CDR_FLOAT_SIZE);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_numerics_Matrix22f' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix22f
#define TSeq holo_base_msg_numerics_Matrix22fSeq

#define T_initialize holo_base_msg_numerics_Matrix22f_initialize

#define T_finalize   holo_base_msg_numerics_Matrix22f_finalize
#define T_copy       holo_base_msg_numerics_Matrix22f_copy

#define T_no_get  
#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix22f
#define TSeq holo_base_msg_numerics_Matrix22fSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_no_get  

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_numerics_Matrix33f *
holo_base_msg_numerics_Matrix33f_create(void)
{
    holo_base_msg_numerics_Matrix33f* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_numerics_Matrix33f);
    if (sample != NULL) {
        if (!holo_base_msg_numerics_Matrix33f_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_numerics_Matrix33f_delete(holo_base_msg_numerics_Matrix33f*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_numerics_Matrix33f_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_numerics_Matrix33f_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_numerics_Matrix33f_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;
    static DDS_UnsignedLong holo_base_msg_numerics_Matrix33f_g_tc_dimensions [2] = {3, 3} ;

    static DDS_TypeCode holo_base_msg_numerics_Matrix33f_g_tc_array =DDS_INITIALIZE_ARRAY_TYPECODE(2,3,holo_base_msg_numerics_Matrix33f_g_tc_dimensions,NULL);

    static DDS_TypeCode holo_base_msg_numerics_Matrix33f_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::numerics::Matrix33f", /* Name */
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
        }}; /* Type code for  holo_base_msg_numerics_Matrix33f */

    if (is_initialized) {
        return &holo_base_msg_numerics_Matrix33f_g_tc;
    }

    holo_base_msg_numerics_Matrix33f_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_numerics_Matrix33f_g_tc_array._data._typeCode =(RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_numerics_Matrix33f_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_numerics_Matrix33f_g_tc_array;

    /* Initialize the values for member annotations. */

    holo_base_msg_numerics_Matrix33f_g_tc._data._sampleAccessInfo =
    holo_base_msg_numerics_Matrix33f_get_sample_access_info();
    holo_base_msg_numerics_Matrix33f_g_tc._data._typePlugin =
    holo_base_msg_numerics_Matrix33f_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_numerics_Matrix33f_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_numerics_Matrix33f_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_numerics_Matrix33f_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_numerics_Matrix33f_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Matrix33f_g_sampleAccessInfo;
    }

    holo_base_msg_numerics_Matrix33f_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_numerics_Matrix33f_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_numerics_Matrix33f_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_numerics_Matrix33f);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_numerics_Matrix33f_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_numerics_Matrix33f_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_numerics_Matrix33f_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Matrix33f_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_numerics_Matrix33f_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_numerics_Matrix33f_g_typePlugin = 
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
        holo_base_msg_numerics_Matrix33f_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_numerics_Matrix33f_finalize_w_return,
        NULL
    };

    return &holo_base_msg_numerics_Matrix33f_g_typePlugin;
}
#endif

RTIBool holo_base_msg_numerics_Matrix33f_initialize(
    holo_base_msg_numerics_Matrix33f* sample) {
    return holo_base_msg_numerics_Matrix33f_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_numerics_Matrix33f_initialize_ex(
    holo_base_msg_numerics_Matrix33f* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_numerics_Matrix33f_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_numerics_Matrix33f_initialize_w_params(
    holo_base_msg_numerics_Matrix33f* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_init_array((*sample), ((3)*(3))* CDR_FLOAT_SIZE);

    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Matrix33f_finalize(
    holo_base_msg_numerics_Matrix33f* sample)
{

    holo_base_msg_numerics_Matrix33f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Matrix33f_finalize_w_return(
    holo_base_msg_numerics_Matrix33f* sample)
{

    holo_base_msg_numerics_Matrix33f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_numerics_Matrix33f_finalize_ex(
    holo_base_msg_numerics_Matrix33f* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_numerics_Matrix33f_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_numerics_Matrix33f_finalize_w_params(
    holo_base_msg_numerics_Matrix33f* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_numerics_Matrix33f_finalize_optional_members(
    holo_base_msg_numerics_Matrix33f* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_numerics_Matrix33f_copy(
    holo_base_msg_numerics_Matrix33f* dst,
    const holo_base_msg_numerics_Matrix33f* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_copy_array((*dst) ,(*src),(3)*(3) * CDR_FLOAT_SIZE);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_numerics_Matrix33f' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix33f
#define TSeq holo_base_msg_numerics_Matrix33fSeq

#define T_initialize holo_base_msg_numerics_Matrix33f_initialize

#define T_finalize   holo_base_msg_numerics_Matrix33f_finalize
#define T_copy       holo_base_msg_numerics_Matrix33f_copy

#define T_no_get  
#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix33f
#define TSeq holo_base_msg_numerics_Matrix33fSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_no_get  

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_numerics_Matrix44f *
holo_base_msg_numerics_Matrix44f_create(void)
{
    holo_base_msg_numerics_Matrix44f* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_numerics_Matrix44f);
    if (sample != NULL) {
        if (!holo_base_msg_numerics_Matrix44f_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_numerics_Matrix44f_delete(holo_base_msg_numerics_Matrix44f*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_numerics_Matrix44f_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_numerics_Matrix44f_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_numerics_Matrix44f_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;
    static DDS_UnsignedLong holo_base_msg_numerics_Matrix44f_g_tc_dimensions [2] = {4, 4} ;

    static DDS_TypeCode holo_base_msg_numerics_Matrix44f_g_tc_array =DDS_INITIALIZE_ARRAY_TYPECODE(2,4,holo_base_msg_numerics_Matrix44f_g_tc_dimensions,NULL);

    static DDS_TypeCode holo_base_msg_numerics_Matrix44f_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::numerics::Matrix44f", /* Name */
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
        }}; /* Type code for  holo_base_msg_numerics_Matrix44f */

    if (is_initialized) {
        return &holo_base_msg_numerics_Matrix44f_g_tc;
    }

    holo_base_msg_numerics_Matrix44f_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_numerics_Matrix44f_g_tc_array._data._typeCode =(RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_numerics_Matrix44f_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_numerics_Matrix44f_g_tc_array;

    /* Initialize the values for member annotations. */

    holo_base_msg_numerics_Matrix44f_g_tc._data._sampleAccessInfo =
    holo_base_msg_numerics_Matrix44f_get_sample_access_info();
    holo_base_msg_numerics_Matrix44f_g_tc._data._typePlugin =
    holo_base_msg_numerics_Matrix44f_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_numerics_Matrix44f_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_numerics_Matrix44f_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_numerics_Matrix44f_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_numerics_Matrix44f_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Matrix44f_g_sampleAccessInfo;
    }

    holo_base_msg_numerics_Matrix44f_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_numerics_Matrix44f_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_numerics_Matrix44f_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_numerics_Matrix44f);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_numerics_Matrix44f_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_numerics_Matrix44f_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_numerics_Matrix44f_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Matrix44f_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_numerics_Matrix44f_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_numerics_Matrix44f_g_typePlugin = 
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
        holo_base_msg_numerics_Matrix44f_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_numerics_Matrix44f_finalize_w_return,
        NULL
    };

    return &holo_base_msg_numerics_Matrix44f_g_typePlugin;
}
#endif

RTIBool holo_base_msg_numerics_Matrix44f_initialize(
    holo_base_msg_numerics_Matrix44f* sample) {
    return holo_base_msg_numerics_Matrix44f_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_numerics_Matrix44f_initialize_ex(
    holo_base_msg_numerics_Matrix44f* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_numerics_Matrix44f_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_numerics_Matrix44f_initialize_w_params(
    holo_base_msg_numerics_Matrix44f* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_init_array((*sample), ((4)*(4))* CDR_FLOAT_SIZE);

    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Matrix44f_finalize(
    holo_base_msg_numerics_Matrix44f* sample)
{

    holo_base_msg_numerics_Matrix44f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Matrix44f_finalize_w_return(
    holo_base_msg_numerics_Matrix44f* sample)
{

    holo_base_msg_numerics_Matrix44f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_numerics_Matrix44f_finalize_ex(
    holo_base_msg_numerics_Matrix44f* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_numerics_Matrix44f_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_numerics_Matrix44f_finalize_w_params(
    holo_base_msg_numerics_Matrix44f* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_numerics_Matrix44f_finalize_optional_members(
    holo_base_msg_numerics_Matrix44f* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_numerics_Matrix44f_copy(
    holo_base_msg_numerics_Matrix44f* dst,
    const holo_base_msg_numerics_Matrix44f* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_copy_array((*dst) ,(*src),(4)*(4) * CDR_FLOAT_SIZE);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_numerics_Matrix44f' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix44f
#define TSeq holo_base_msg_numerics_Matrix44fSeq

#define T_initialize holo_base_msg_numerics_Matrix44f_initialize

#define T_finalize   holo_base_msg_numerics_Matrix44f_finalize
#define T_copy       holo_base_msg_numerics_Matrix44f_copy

#define T_no_get  
#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix44f
#define TSeq holo_base_msg_numerics_Matrix44fSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_no_get  

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_numerics_Matrix55f *
holo_base_msg_numerics_Matrix55f_create(void)
{
    holo_base_msg_numerics_Matrix55f* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_numerics_Matrix55f);
    if (sample != NULL) {
        if (!holo_base_msg_numerics_Matrix55f_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_numerics_Matrix55f_delete(holo_base_msg_numerics_Matrix55f*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_numerics_Matrix55f_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_numerics_Matrix55f_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_numerics_Matrix55f_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;
    static DDS_UnsignedLong holo_base_msg_numerics_Matrix55f_g_tc_dimensions [2] = {5, 5} ;

    static DDS_TypeCode holo_base_msg_numerics_Matrix55f_g_tc_array =DDS_INITIALIZE_ARRAY_TYPECODE(2,5,holo_base_msg_numerics_Matrix55f_g_tc_dimensions,NULL);

    static DDS_TypeCode holo_base_msg_numerics_Matrix55f_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::numerics::Matrix55f", /* Name */
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
        }}; /* Type code for  holo_base_msg_numerics_Matrix55f */

    if (is_initialized) {
        return &holo_base_msg_numerics_Matrix55f_g_tc;
    }

    holo_base_msg_numerics_Matrix55f_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_numerics_Matrix55f_g_tc_array._data._typeCode =(RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_numerics_Matrix55f_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_numerics_Matrix55f_g_tc_array;

    /* Initialize the values for member annotations. */

    holo_base_msg_numerics_Matrix55f_g_tc._data._sampleAccessInfo =
    holo_base_msg_numerics_Matrix55f_get_sample_access_info();
    holo_base_msg_numerics_Matrix55f_g_tc._data._typePlugin =
    holo_base_msg_numerics_Matrix55f_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_numerics_Matrix55f_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_numerics_Matrix55f_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_numerics_Matrix55f_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_numerics_Matrix55f_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Matrix55f_g_sampleAccessInfo;
    }

    holo_base_msg_numerics_Matrix55f_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_numerics_Matrix55f_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_numerics_Matrix55f_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_numerics_Matrix55f);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_numerics_Matrix55f_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_numerics_Matrix55f_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_numerics_Matrix55f_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Matrix55f_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_numerics_Matrix55f_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_numerics_Matrix55f_g_typePlugin = 
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
        holo_base_msg_numerics_Matrix55f_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_numerics_Matrix55f_finalize_w_return,
        NULL
    };

    return &holo_base_msg_numerics_Matrix55f_g_typePlugin;
}
#endif

RTIBool holo_base_msg_numerics_Matrix55f_initialize(
    holo_base_msg_numerics_Matrix55f* sample) {
    return holo_base_msg_numerics_Matrix55f_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_numerics_Matrix55f_initialize_ex(
    holo_base_msg_numerics_Matrix55f* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_numerics_Matrix55f_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_numerics_Matrix55f_initialize_w_params(
    holo_base_msg_numerics_Matrix55f* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_init_array((*sample), ((5)*(5))* CDR_FLOAT_SIZE);

    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Matrix55f_finalize(
    holo_base_msg_numerics_Matrix55f* sample)
{

    holo_base_msg_numerics_Matrix55f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Matrix55f_finalize_w_return(
    holo_base_msg_numerics_Matrix55f* sample)
{

    holo_base_msg_numerics_Matrix55f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_numerics_Matrix55f_finalize_ex(
    holo_base_msg_numerics_Matrix55f* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_numerics_Matrix55f_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_numerics_Matrix55f_finalize_w_params(
    holo_base_msg_numerics_Matrix55f* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_numerics_Matrix55f_finalize_optional_members(
    holo_base_msg_numerics_Matrix55f* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_numerics_Matrix55f_copy(
    holo_base_msg_numerics_Matrix55f* dst,
    const holo_base_msg_numerics_Matrix55f* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_copy_array((*dst) ,(*src),(5)*(5) * CDR_FLOAT_SIZE);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_numerics_Matrix55f' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix55f
#define TSeq holo_base_msg_numerics_Matrix55fSeq

#define T_initialize holo_base_msg_numerics_Matrix55f_initialize

#define T_finalize   holo_base_msg_numerics_Matrix55f_finalize
#define T_copy       holo_base_msg_numerics_Matrix55f_copy

#define T_no_get  
#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix55f
#define TSeq holo_base_msg_numerics_Matrix55fSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_no_get  

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_numerics_Matrix66f *
holo_base_msg_numerics_Matrix66f_create(void)
{
    holo_base_msg_numerics_Matrix66f* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_numerics_Matrix66f);
    if (sample != NULL) {
        if (!holo_base_msg_numerics_Matrix66f_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_numerics_Matrix66f_delete(holo_base_msg_numerics_Matrix66f*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_numerics_Matrix66f_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_numerics_Matrix66f_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_numerics_Matrix66f_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;
    static DDS_UnsignedLong holo_base_msg_numerics_Matrix66f_g_tc_dimensions [2] = {6, 6} ;

    static DDS_TypeCode holo_base_msg_numerics_Matrix66f_g_tc_array =DDS_INITIALIZE_ARRAY_TYPECODE(2,6,holo_base_msg_numerics_Matrix66f_g_tc_dimensions,NULL);

    static DDS_TypeCode holo_base_msg_numerics_Matrix66f_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::numerics::Matrix66f", /* Name */
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
        }}; /* Type code for  holo_base_msg_numerics_Matrix66f */

    if (is_initialized) {
        return &holo_base_msg_numerics_Matrix66f_g_tc;
    }

    holo_base_msg_numerics_Matrix66f_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_numerics_Matrix66f_g_tc_array._data._typeCode =(RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_numerics_Matrix66f_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_numerics_Matrix66f_g_tc_array;

    /* Initialize the values for member annotations. */

    holo_base_msg_numerics_Matrix66f_g_tc._data._sampleAccessInfo =
    holo_base_msg_numerics_Matrix66f_get_sample_access_info();
    holo_base_msg_numerics_Matrix66f_g_tc._data._typePlugin =
    holo_base_msg_numerics_Matrix66f_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_numerics_Matrix66f_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_numerics_Matrix66f_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_numerics_Matrix66f_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_numerics_Matrix66f_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Matrix66f_g_sampleAccessInfo;
    }

    holo_base_msg_numerics_Matrix66f_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_numerics_Matrix66f_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_numerics_Matrix66f_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_numerics_Matrix66f);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_numerics_Matrix66f_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_numerics_Matrix66f_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_numerics_Matrix66f_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Matrix66f_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_numerics_Matrix66f_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_numerics_Matrix66f_g_typePlugin = 
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
        holo_base_msg_numerics_Matrix66f_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_numerics_Matrix66f_finalize_w_return,
        NULL
    };

    return &holo_base_msg_numerics_Matrix66f_g_typePlugin;
}
#endif

RTIBool holo_base_msg_numerics_Matrix66f_initialize(
    holo_base_msg_numerics_Matrix66f* sample) {
    return holo_base_msg_numerics_Matrix66f_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_numerics_Matrix66f_initialize_ex(
    holo_base_msg_numerics_Matrix66f* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_numerics_Matrix66f_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_numerics_Matrix66f_initialize_w_params(
    holo_base_msg_numerics_Matrix66f* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_init_array((*sample), ((6)*(6))* CDR_FLOAT_SIZE);

    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Matrix66f_finalize(
    holo_base_msg_numerics_Matrix66f* sample)
{

    holo_base_msg_numerics_Matrix66f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Matrix66f_finalize_w_return(
    holo_base_msg_numerics_Matrix66f* sample)
{

    holo_base_msg_numerics_Matrix66f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_numerics_Matrix66f_finalize_ex(
    holo_base_msg_numerics_Matrix66f* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_numerics_Matrix66f_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_numerics_Matrix66f_finalize_w_params(
    holo_base_msg_numerics_Matrix66f* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_numerics_Matrix66f_finalize_optional_members(
    holo_base_msg_numerics_Matrix66f* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_numerics_Matrix66f_copy(
    holo_base_msg_numerics_Matrix66f* dst,
    const holo_base_msg_numerics_Matrix66f* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_copy_array((*dst) ,(*src),(6)*(6) * CDR_FLOAT_SIZE);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_numerics_Matrix66f' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix66f
#define TSeq holo_base_msg_numerics_Matrix66fSeq

#define T_initialize holo_base_msg_numerics_Matrix66f_initialize

#define T_finalize   holo_base_msg_numerics_Matrix66f_finalize
#define T_copy       holo_base_msg_numerics_Matrix66f_copy

#define T_no_get  
#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix66f
#define TSeq holo_base_msg_numerics_Matrix66fSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_no_get  

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

