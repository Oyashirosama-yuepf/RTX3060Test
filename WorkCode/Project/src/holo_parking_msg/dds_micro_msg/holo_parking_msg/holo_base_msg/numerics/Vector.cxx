/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Vector.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "Vector.h"

#ifndef UNUSED_ARG
#define UNUSED_ARG(x) (void)(x)
#endif

#include "dds_c/dds_c_typecode.h"
/*** SOURCE_BEGIN ***/

holo_base_msg_numerics_Vectord *
holo_base_msg_numerics_Vectord_create(void)
{
    holo_base_msg_numerics_Vectord* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_numerics_Vectord);
    if (sample != NULL) {
        if (!holo_base_msg_numerics_Vectord_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_numerics_Vectord_delete(holo_base_msg_numerics_Vectord*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_numerics_Vectord_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_numerics_Vectord_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_numerics_Vectord_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_numerics_Vectord_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_numerics_Vectord_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::numerics::Vectord", /* Name */
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
        }}; /* Type code for  holo_base_msg_numerics_Vectord */

    if (is_initialized) {
        return &holo_base_msg_numerics_Vectord_g_tc;
    }

    holo_base_msg_numerics_Vectord_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_numerics_Vectord_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();
    holo_base_msg_numerics_Vectord_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_numerics_Vectord_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_numerics_Vectord_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_numerics_Vectord_g_tc._data._sampleAccessInfo =
    holo_base_msg_numerics_Vectord_get_sample_access_info();
    holo_base_msg_numerics_Vectord_g_tc._data._typePlugin =
    holo_base_msg_numerics_Vectord_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_numerics_Vectord_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_numerics_Vectord_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_numerics_Vectord_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_numerics_Vectord_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vectord_g_sampleAccessInfo;
    }

    holo_base_msg_numerics_Vectord_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_numerics_Vectord_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_numerics_Vectord_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_numerics_Vectord);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_numerics_Vectord_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_numerics_Vectord_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_numerics_Vectord_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vectord_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_numerics_Vectord_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_numerics_Vectord_g_typePlugin = 
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
        holo_base_msg_numerics_Vectord_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_numerics_Vectord_finalize_w_return,
        NULL
    };

    return &holo_base_msg_numerics_Vectord_g_typePlugin;
}
#endif

RTIBool holo_base_msg_numerics_Vectord_initialize(
    holo_base_msg_numerics_Vectord* sample) {
    return holo_base_msg_numerics_Vectord_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_numerics_Vectord_initialize_ex(
    holo_base_msg_numerics_Vectord* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_numerics_Vectord_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_numerics_Vectord_initialize_w_params(
    holo_base_msg_numerics_Vectord* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

RTIBool holo_base_msg_numerics_Vectord_finalize(
    holo_base_msg_numerics_Vectord* sample)
{

    holo_base_msg_numerics_Vectord_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Vectord_finalize_w_return(
    holo_base_msg_numerics_Vectord* sample)
{

    holo_base_msg_numerics_Vectord_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_numerics_Vectord_finalize_ex(
    holo_base_msg_numerics_Vectord* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_numerics_Vectord_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_numerics_Vectord_finalize_w_params(
    holo_base_msg_numerics_Vectord* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
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

void holo_base_msg_numerics_Vectord_finalize_optional_members(
    holo_base_msg_numerics_Vectord* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_numerics_Vectord_copy(
    holo_base_msg_numerics_Vectord* dst,
    const holo_base_msg_numerics_Vectord* src)
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
* Configure and implement 'holo_base_msg_numerics_Vectord' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vectord
#define TSeq holo_base_msg_numerics_VectordSeq

#define T_initialize holo_base_msg_numerics_Vectord_initialize

#define T_finalize   holo_base_msg_numerics_Vectord_finalize
#define T_copy       holo_base_msg_numerics_Vectord_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vectord
#define TSeq holo_base_msg_numerics_VectordSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_numerics_Vector2d *
holo_base_msg_numerics_Vector2d_create(void)
{
    holo_base_msg_numerics_Vector2d* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_numerics_Vector2d);
    if (sample != NULL) {
        if (!holo_base_msg_numerics_Vector2d_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_numerics_Vector2d_delete(holo_base_msg_numerics_Vector2d*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_numerics_Vector2d_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_numerics_Vector2d_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_numerics_Vector2d_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_numerics_Vector2d_g_tc_array =DDS_INITIALIZE_ARRAY_TYPECODE(1,2, NULL,NULL);

    static DDS_TypeCode holo_base_msg_numerics_Vector2d_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::numerics::Vector2d", /* Name */
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
        }}; /* Type code for  holo_base_msg_numerics_Vector2d */

    if (is_initialized) {
        return &holo_base_msg_numerics_Vector2d_g_tc;
    }

    holo_base_msg_numerics_Vector2d_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_numerics_Vector2d_g_tc_array._data._typeCode =(RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();
    holo_base_msg_numerics_Vector2d_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_numerics_Vector2d_g_tc_array;

    /* Initialize the values for member annotations. */

    holo_base_msg_numerics_Vector2d_g_tc._data._sampleAccessInfo =
    holo_base_msg_numerics_Vector2d_get_sample_access_info();
    holo_base_msg_numerics_Vector2d_g_tc._data._typePlugin =
    holo_base_msg_numerics_Vector2d_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_numerics_Vector2d_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_numerics_Vector2d_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_numerics_Vector2d_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_numerics_Vector2d_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vector2d_g_sampleAccessInfo;
    }

    holo_base_msg_numerics_Vector2d_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_numerics_Vector2d_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_numerics_Vector2d_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_numerics_Vector2d);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_numerics_Vector2d_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_numerics_Vector2d_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_numerics_Vector2d_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vector2d_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_numerics_Vector2d_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_numerics_Vector2d_g_typePlugin = 
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
        holo_base_msg_numerics_Vector2d_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_numerics_Vector2d_finalize_w_return,
        NULL
    };

    return &holo_base_msg_numerics_Vector2d_g_typePlugin;
}
#endif

RTIBool holo_base_msg_numerics_Vector2d_initialize(
    holo_base_msg_numerics_Vector2d* sample) {
    return holo_base_msg_numerics_Vector2d_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_numerics_Vector2d_initialize_ex(
    holo_base_msg_numerics_Vector2d* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_numerics_Vector2d_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_numerics_Vector2d_initialize_w_params(
    holo_base_msg_numerics_Vector2d* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_init_array((*sample), ((2))* CDR_DOUBLE_SIZE);

    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Vector2d_finalize(
    holo_base_msg_numerics_Vector2d* sample)
{

    holo_base_msg_numerics_Vector2d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Vector2d_finalize_w_return(
    holo_base_msg_numerics_Vector2d* sample)
{

    holo_base_msg_numerics_Vector2d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_numerics_Vector2d_finalize_ex(
    holo_base_msg_numerics_Vector2d* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_numerics_Vector2d_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_numerics_Vector2d_finalize_w_params(
    holo_base_msg_numerics_Vector2d* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_numerics_Vector2d_finalize_optional_members(
    holo_base_msg_numerics_Vector2d* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_numerics_Vector2d_copy(
    holo_base_msg_numerics_Vector2d* dst,
    const holo_base_msg_numerics_Vector2d* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_copy_array((*dst) ,(*src),(2) * CDR_DOUBLE_SIZE);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_numerics_Vector2d' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector2d
#define TSeq holo_base_msg_numerics_Vector2dSeq

#define T_initialize holo_base_msg_numerics_Vector2d_initialize

#define T_finalize   holo_base_msg_numerics_Vector2d_finalize
#define T_copy       holo_base_msg_numerics_Vector2d_copy

#define T_no_get  
#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector2d
#define TSeq holo_base_msg_numerics_Vector2dSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_no_get  

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_numerics_Vector3d *
holo_base_msg_numerics_Vector3d_create(void)
{
    holo_base_msg_numerics_Vector3d* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_numerics_Vector3d);
    if (sample != NULL) {
        if (!holo_base_msg_numerics_Vector3d_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_numerics_Vector3d_delete(holo_base_msg_numerics_Vector3d*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_numerics_Vector3d_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_numerics_Vector3d_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_numerics_Vector3d_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_numerics_Vector3d_g_tc_array =DDS_INITIALIZE_ARRAY_TYPECODE(1,3, NULL,NULL);

    static DDS_TypeCode holo_base_msg_numerics_Vector3d_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::numerics::Vector3d", /* Name */
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
        }}; /* Type code for  holo_base_msg_numerics_Vector3d */

    if (is_initialized) {
        return &holo_base_msg_numerics_Vector3d_g_tc;
    }

    holo_base_msg_numerics_Vector3d_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_numerics_Vector3d_g_tc_array._data._typeCode =(RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();
    holo_base_msg_numerics_Vector3d_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_numerics_Vector3d_g_tc_array;

    /* Initialize the values for member annotations. */

    holo_base_msg_numerics_Vector3d_g_tc._data._sampleAccessInfo =
    holo_base_msg_numerics_Vector3d_get_sample_access_info();
    holo_base_msg_numerics_Vector3d_g_tc._data._typePlugin =
    holo_base_msg_numerics_Vector3d_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_numerics_Vector3d_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_numerics_Vector3d_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_numerics_Vector3d_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_numerics_Vector3d_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vector3d_g_sampleAccessInfo;
    }

    holo_base_msg_numerics_Vector3d_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_numerics_Vector3d_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_numerics_Vector3d_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_numerics_Vector3d);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_numerics_Vector3d_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_numerics_Vector3d_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_numerics_Vector3d_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vector3d_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_numerics_Vector3d_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_numerics_Vector3d_g_typePlugin = 
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
        holo_base_msg_numerics_Vector3d_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_numerics_Vector3d_finalize_w_return,
        NULL
    };

    return &holo_base_msg_numerics_Vector3d_g_typePlugin;
}
#endif

RTIBool holo_base_msg_numerics_Vector3d_initialize(
    holo_base_msg_numerics_Vector3d* sample) {
    return holo_base_msg_numerics_Vector3d_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_numerics_Vector3d_initialize_ex(
    holo_base_msg_numerics_Vector3d* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_numerics_Vector3d_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_numerics_Vector3d_initialize_w_params(
    holo_base_msg_numerics_Vector3d* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_init_array((*sample), ((3))* CDR_DOUBLE_SIZE);

    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Vector3d_finalize(
    holo_base_msg_numerics_Vector3d* sample)
{

    holo_base_msg_numerics_Vector3d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Vector3d_finalize_w_return(
    holo_base_msg_numerics_Vector3d* sample)
{

    holo_base_msg_numerics_Vector3d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_numerics_Vector3d_finalize_ex(
    holo_base_msg_numerics_Vector3d* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_numerics_Vector3d_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_numerics_Vector3d_finalize_w_params(
    holo_base_msg_numerics_Vector3d* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_numerics_Vector3d_finalize_optional_members(
    holo_base_msg_numerics_Vector3d* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_numerics_Vector3d_copy(
    holo_base_msg_numerics_Vector3d* dst,
    const holo_base_msg_numerics_Vector3d* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_copy_array((*dst) ,(*src),(3) * CDR_DOUBLE_SIZE);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_numerics_Vector3d' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector3d
#define TSeq holo_base_msg_numerics_Vector3dSeq

#define T_initialize holo_base_msg_numerics_Vector3d_initialize

#define T_finalize   holo_base_msg_numerics_Vector3d_finalize
#define T_copy       holo_base_msg_numerics_Vector3d_copy

#define T_no_get  
#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector3d
#define TSeq holo_base_msg_numerics_Vector3dSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_no_get  

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_numerics_Vector4d *
holo_base_msg_numerics_Vector4d_create(void)
{
    holo_base_msg_numerics_Vector4d* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_numerics_Vector4d);
    if (sample != NULL) {
        if (!holo_base_msg_numerics_Vector4d_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_numerics_Vector4d_delete(holo_base_msg_numerics_Vector4d*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_numerics_Vector4d_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_numerics_Vector4d_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_numerics_Vector4d_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_numerics_Vector4d_g_tc_array =DDS_INITIALIZE_ARRAY_TYPECODE(1,4, NULL,NULL);

    static DDS_TypeCode holo_base_msg_numerics_Vector4d_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::numerics::Vector4d", /* Name */
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
        }}; /* Type code for  holo_base_msg_numerics_Vector4d */

    if (is_initialized) {
        return &holo_base_msg_numerics_Vector4d_g_tc;
    }

    holo_base_msg_numerics_Vector4d_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_numerics_Vector4d_g_tc_array._data._typeCode =(RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();
    holo_base_msg_numerics_Vector4d_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_numerics_Vector4d_g_tc_array;

    /* Initialize the values for member annotations. */

    holo_base_msg_numerics_Vector4d_g_tc._data._sampleAccessInfo =
    holo_base_msg_numerics_Vector4d_get_sample_access_info();
    holo_base_msg_numerics_Vector4d_g_tc._data._typePlugin =
    holo_base_msg_numerics_Vector4d_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_numerics_Vector4d_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_numerics_Vector4d_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_numerics_Vector4d_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_numerics_Vector4d_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vector4d_g_sampleAccessInfo;
    }

    holo_base_msg_numerics_Vector4d_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_numerics_Vector4d_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_numerics_Vector4d_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_numerics_Vector4d);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_numerics_Vector4d_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_numerics_Vector4d_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_numerics_Vector4d_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vector4d_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_numerics_Vector4d_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_numerics_Vector4d_g_typePlugin = 
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
        holo_base_msg_numerics_Vector4d_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_numerics_Vector4d_finalize_w_return,
        NULL
    };

    return &holo_base_msg_numerics_Vector4d_g_typePlugin;
}
#endif

RTIBool holo_base_msg_numerics_Vector4d_initialize(
    holo_base_msg_numerics_Vector4d* sample) {
    return holo_base_msg_numerics_Vector4d_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_numerics_Vector4d_initialize_ex(
    holo_base_msg_numerics_Vector4d* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_numerics_Vector4d_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_numerics_Vector4d_initialize_w_params(
    holo_base_msg_numerics_Vector4d* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_init_array((*sample), ((4))* CDR_DOUBLE_SIZE);

    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Vector4d_finalize(
    holo_base_msg_numerics_Vector4d* sample)
{

    holo_base_msg_numerics_Vector4d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Vector4d_finalize_w_return(
    holo_base_msg_numerics_Vector4d* sample)
{

    holo_base_msg_numerics_Vector4d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_numerics_Vector4d_finalize_ex(
    holo_base_msg_numerics_Vector4d* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_numerics_Vector4d_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_numerics_Vector4d_finalize_w_params(
    holo_base_msg_numerics_Vector4d* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_numerics_Vector4d_finalize_optional_members(
    holo_base_msg_numerics_Vector4d* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_numerics_Vector4d_copy(
    holo_base_msg_numerics_Vector4d* dst,
    const holo_base_msg_numerics_Vector4d* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_copy_array((*dst) ,(*src),(4) * CDR_DOUBLE_SIZE);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_numerics_Vector4d' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector4d
#define TSeq holo_base_msg_numerics_Vector4dSeq

#define T_initialize holo_base_msg_numerics_Vector4d_initialize

#define T_finalize   holo_base_msg_numerics_Vector4d_finalize
#define T_copy       holo_base_msg_numerics_Vector4d_copy

#define T_no_get  
#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector4d
#define TSeq holo_base_msg_numerics_Vector4dSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_no_get  

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_numerics_Vector5d *
holo_base_msg_numerics_Vector5d_create(void)
{
    holo_base_msg_numerics_Vector5d* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_numerics_Vector5d);
    if (sample != NULL) {
        if (!holo_base_msg_numerics_Vector5d_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_numerics_Vector5d_delete(holo_base_msg_numerics_Vector5d*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_numerics_Vector5d_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_numerics_Vector5d_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_numerics_Vector5d_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_numerics_Vector5d_g_tc_array =DDS_INITIALIZE_ARRAY_TYPECODE(1,5, NULL,NULL);

    static DDS_TypeCode holo_base_msg_numerics_Vector5d_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::numerics::Vector5d", /* Name */
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
        }}; /* Type code for  holo_base_msg_numerics_Vector5d */

    if (is_initialized) {
        return &holo_base_msg_numerics_Vector5d_g_tc;
    }

    holo_base_msg_numerics_Vector5d_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_numerics_Vector5d_g_tc_array._data._typeCode =(RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();
    holo_base_msg_numerics_Vector5d_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_numerics_Vector5d_g_tc_array;

    /* Initialize the values for member annotations. */

    holo_base_msg_numerics_Vector5d_g_tc._data._sampleAccessInfo =
    holo_base_msg_numerics_Vector5d_get_sample_access_info();
    holo_base_msg_numerics_Vector5d_g_tc._data._typePlugin =
    holo_base_msg_numerics_Vector5d_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_numerics_Vector5d_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_numerics_Vector5d_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_numerics_Vector5d_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_numerics_Vector5d_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vector5d_g_sampleAccessInfo;
    }

    holo_base_msg_numerics_Vector5d_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_numerics_Vector5d_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_numerics_Vector5d_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_numerics_Vector5d);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_numerics_Vector5d_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_numerics_Vector5d_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_numerics_Vector5d_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vector5d_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_numerics_Vector5d_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_numerics_Vector5d_g_typePlugin = 
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
        holo_base_msg_numerics_Vector5d_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_numerics_Vector5d_finalize_w_return,
        NULL
    };

    return &holo_base_msg_numerics_Vector5d_g_typePlugin;
}
#endif

RTIBool holo_base_msg_numerics_Vector5d_initialize(
    holo_base_msg_numerics_Vector5d* sample) {
    return holo_base_msg_numerics_Vector5d_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_numerics_Vector5d_initialize_ex(
    holo_base_msg_numerics_Vector5d* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_numerics_Vector5d_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_numerics_Vector5d_initialize_w_params(
    holo_base_msg_numerics_Vector5d* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_init_array((*sample), ((5))* CDR_DOUBLE_SIZE);

    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Vector5d_finalize(
    holo_base_msg_numerics_Vector5d* sample)
{

    holo_base_msg_numerics_Vector5d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Vector5d_finalize_w_return(
    holo_base_msg_numerics_Vector5d* sample)
{

    holo_base_msg_numerics_Vector5d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_numerics_Vector5d_finalize_ex(
    holo_base_msg_numerics_Vector5d* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_numerics_Vector5d_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_numerics_Vector5d_finalize_w_params(
    holo_base_msg_numerics_Vector5d* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_numerics_Vector5d_finalize_optional_members(
    holo_base_msg_numerics_Vector5d* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_numerics_Vector5d_copy(
    holo_base_msg_numerics_Vector5d* dst,
    const holo_base_msg_numerics_Vector5d* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_copy_array((*dst) ,(*src),(5) * CDR_DOUBLE_SIZE);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_numerics_Vector5d' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector5d
#define TSeq holo_base_msg_numerics_Vector5dSeq

#define T_initialize holo_base_msg_numerics_Vector5d_initialize

#define T_finalize   holo_base_msg_numerics_Vector5d_finalize
#define T_copy       holo_base_msg_numerics_Vector5d_copy

#define T_no_get  
#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector5d
#define TSeq holo_base_msg_numerics_Vector5dSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_no_get  

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_numerics_Vector6d *
holo_base_msg_numerics_Vector6d_create(void)
{
    holo_base_msg_numerics_Vector6d* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_numerics_Vector6d);
    if (sample != NULL) {
        if (!holo_base_msg_numerics_Vector6d_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_numerics_Vector6d_delete(holo_base_msg_numerics_Vector6d*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_numerics_Vector6d_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_numerics_Vector6d_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_numerics_Vector6d_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_numerics_Vector6d_g_tc_array =DDS_INITIALIZE_ARRAY_TYPECODE(1,6, NULL,NULL);

    static DDS_TypeCode holo_base_msg_numerics_Vector6d_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::numerics::Vector6d", /* Name */
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
        }}; /* Type code for  holo_base_msg_numerics_Vector6d */

    if (is_initialized) {
        return &holo_base_msg_numerics_Vector6d_g_tc;
    }

    holo_base_msg_numerics_Vector6d_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_numerics_Vector6d_g_tc_array._data._typeCode =(RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();
    holo_base_msg_numerics_Vector6d_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_numerics_Vector6d_g_tc_array;

    /* Initialize the values for member annotations. */

    holo_base_msg_numerics_Vector6d_g_tc._data._sampleAccessInfo =
    holo_base_msg_numerics_Vector6d_get_sample_access_info();
    holo_base_msg_numerics_Vector6d_g_tc._data._typePlugin =
    holo_base_msg_numerics_Vector6d_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_numerics_Vector6d_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_numerics_Vector6d_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_numerics_Vector6d_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_numerics_Vector6d_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vector6d_g_sampleAccessInfo;
    }

    holo_base_msg_numerics_Vector6d_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_numerics_Vector6d_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_numerics_Vector6d_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_numerics_Vector6d);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_numerics_Vector6d_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_numerics_Vector6d_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_numerics_Vector6d_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vector6d_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_numerics_Vector6d_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_numerics_Vector6d_g_typePlugin = 
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
        holo_base_msg_numerics_Vector6d_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_numerics_Vector6d_finalize_w_return,
        NULL
    };

    return &holo_base_msg_numerics_Vector6d_g_typePlugin;
}
#endif

RTIBool holo_base_msg_numerics_Vector6d_initialize(
    holo_base_msg_numerics_Vector6d* sample) {
    return holo_base_msg_numerics_Vector6d_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_numerics_Vector6d_initialize_ex(
    holo_base_msg_numerics_Vector6d* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_numerics_Vector6d_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_numerics_Vector6d_initialize_w_params(
    holo_base_msg_numerics_Vector6d* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_init_array((*sample), ((6))* CDR_DOUBLE_SIZE);

    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Vector6d_finalize(
    holo_base_msg_numerics_Vector6d* sample)
{

    holo_base_msg_numerics_Vector6d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Vector6d_finalize_w_return(
    holo_base_msg_numerics_Vector6d* sample)
{

    holo_base_msg_numerics_Vector6d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_numerics_Vector6d_finalize_ex(
    holo_base_msg_numerics_Vector6d* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_numerics_Vector6d_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_numerics_Vector6d_finalize_w_params(
    holo_base_msg_numerics_Vector6d* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_numerics_Vector6d_finalize_optional_members(
    holo_base_msg_numerics_Vector6d* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_numerics_Vector6d_copy(
    holo_base_msg_numerics_Vector6d* dst,
    const holo_base_msg_numerics_Vector6d* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_copy_array((*dst) ,(*src),(6) * CDR_DOUBLE_SIZE);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_numerics_Vector6d' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector6d
#define TSeq holo_base_msg_numerics_Vector6dSeq

#define T_initialize holo_base_msg_numerics_Vector6d_initialize

#define T_finalize   holo_base_msg_numerics_Vector6d_finalize
#define T_copy       holo_base_msg_numerics_Vector6d_copy

#define T_no_get  
#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector6d
#define TSeq holo_base_msg_numerics_Vector6dSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_no_get  

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_numerics_Vector7d *
holo_base_msg_numerics_Vector7d_create(void)
{
    holo_base_msg_numerics_Vector7d* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_numerics_Vector7d);
    if (sample != NULL) {
        if (!holo_base_msg_numerics_Vector7d_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_numerics_Vector7d_delete(holo_base_msg_numerics_Vector7d*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_numerics_Vector7d_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_numerics_Vector7d_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_numerics_Vector7d_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_numerics_Vector7d_g_tc_array =DDS_INITIALIZE_ARRAY_TYPECODE(1,7, NULL,NULL);

    static DDS_TypeCode holo_base_msg_numerics_Vector7d_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::numerics::Vector7d", /* Name */
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
        }}; /* Type code for  holo_base_msg_numerics_Vector7d */

    if (is_initialized) {
        return &holo_base_msg_numerics_Vector7d_g_tc;
    }

    holo_base_msg_numerics_Vector7d_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_numerics_Vector7d_g_tc_array._data._typeCode =(RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();
    holo_base_msg_numerics_Vector7d_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_numerics_Vector7d_g_tc_array;

    /* Initialize the values for member annotations. */

    holo_base_msg_numerics_Vector7d_g_tc._data._sampleAccessInfo =
    holo_base_msg_numerics_Vector7d_get_sample_access_info();
    holo_base_msg_numerics_Vector7d_g_tc._data._typePlugin =
    holo_base_msg_numerics_Vector7d_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_numerics_Vector7d_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_numerics_Vector7d_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_numerics_Vector7d_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_numerics_Vector7d_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vector7d_g_sampleAccessInfo;
    }

    holo_base_msg_numerics_Vector7d_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_numerics_Vector7d_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_numerics_Vector7d_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_numerics_Vector7d);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_numerics_Vector7d_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_numerics_Vector7d_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_numerics_Vector7d_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vector7d_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_numerics_Vector7d_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_numerics_Vector7d_g_typePlugin = 
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
        holo_base_msg_numerics_Vector7d_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_numerics_Vector7d_finalize_w_return,
        NULL
    };

    return &holo_base_msg_numerics_Vector7d_g_typePlugin;
}
#endif

RTIBool holo_base_msg_numerics_Vector7d_initialize(
    holo_base_msg_numerics_Vector7d* sample) {
    return holo_base_msg_numerics_Vector7d_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_numerics_Vector7d_initialize_ex(
    holo_base_msg_numerics_Vector7d* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_numerics_Vector7d_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_numerics_Vector7d_initialize_w_params(
    holo_base_msg_numerics_Vector7d* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_init_array((*sample), ((7))* CDR_DOUBLE_SIZE);

    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Vector7d_finalize(
    holo_base_msg_numerics_Vector7d* sample)
{

    holo_base_msg_numerics_Vector7d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Vector7d_finalize_w_return(
    holo_base_msg_numerics_Vector7d* sample)
{

    holo_base_msg_numerics_Vector7d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_numerics_Vector7d_finalize_ex(
    holo_base_msg_numerics_Vector7d* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_numerics_Vector7d_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_numerics_Vector7d_finalize_w_params(
    holo_base_msg_numerics_Vector7d* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_numerics_Vector7d_finalize_optional_members(
    holo_base_msg_numerics_Vector7d* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_numerics_Vector7d_copy(
    holo_base_msg_numerics_Vector7d* dst,
    const holo_base_msg_numerics_Vector7d* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_copy_array((*dst) ,(*src),(7) * CDR_DOUBLE_SIZE);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_numerics_Vector7d' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector7d
#define TSeq holo_base_msg_numerics_Vector7dSeq

#define T_initialize holo_base_msg_numerics_Vector7d_initialize

#define T_finalize   holo_base_msg_numerics_Vector7d_finalize
#define T_copy       holo_base_msg_numerics_Vector7d_copy

#define T_no_get  
#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector7d
#define TSeq holo_base_msg_numerics_Vector7dSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_no_get  

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_numerics_Vector8d *
holo_base_msg_numerics_Vector8d_create(void)
{
    holo_base_msg_numerics_Vector8d* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_numerics_Vector8d);
    if (sample != NULL) {
        if (!holo_base_msg_numerics_Vector8d_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_numerics_Vector8d_delete(holo_base_msg_numerics_Vector8d*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_numerics_Vector8d_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_numerics_Vector8d_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_numerics_Vector8d_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_numerics_Vector8d_g_tc_array =DDS_INITIALIZE_ARRAY_TYPECODE(1,8, NULL,NULL);

    static DDS_TypeCode holo_base_msg_numerics_Vector8d_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::numerics::Vector8d", /* Name */
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
        }}; /* Type code for  holo_base_msg_numerics_Vector8d */

    if (is_initialized) {
        return &holo_base_msg_numerics_Vector8d_g_tc;
    }

    holo_base_msg_numerics_Vector8d_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_numerics_Vector8d_g_tc_array._data._typeCode =(RTICdrTypeCode *)holo_base_msg_core_float64_t_get_typecode();
    holo_base_msg_numerics_Vector8d_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_numerics_Vector8d_g_tc_array;

    /* Initialize the values for member annotations. */

    holo_base_msg_numerics_Vector8d_g_tc._data._sampleAccessInfo =
    holo_base_msg_numerics_Vector8d_get_sample_access_info();
    holo_base_msg_numerics_Vector8d_g_tc._data._typePlugin =
    holo_base_msg_numerics_Vector8d_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_numerics_Vector8d_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_numerics_Vector8d_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_numerics_Vector8d_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_numerics_Vector8d_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vector8d_g_sampleAccessInfo;
    }

    holo_base_msg_numerics_Vector8d_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_numerics_Vector8d_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_numerics_Vector8d_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_numerics_Vector8d);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_numerics_Vector8d_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_numerics_Vector8d_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_numerics_Vector8d_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vector8d_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_numerics_Vector8d_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_numerics_Vector8d_g_typePlugin = 
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
        holo_base_msg_numerics_Vector8d_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_numerics_Vector8d_finalize_w_return,
        NULL
    };

    return &holo_base_msg_numerics_Vector8d_g_typePlugin;
}
#endif

RTIBool holo_base_msg_numerics_Vector8d_initialize(
    holo_base_msg_numerics_Vector8d* sample) {
    return holo_base_msg_numerics_Vector8d_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_numerics_Vector8d_initialize_ex(
    holo_base_msg_numerics_Vector8d* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_numerics_Vector8d_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_numerics_Vector8d_initialize_w_params(
    holo_base_msg_numerics_Vector8d* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_init_array((*sample), ((8))* CDR_DOUBLE_SIZE);

    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Vector8d_finalize(
    holo_base_msg_numerics_Vector8d* sample)
{

    holo_base_msg_numerics_Vector8d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Vector8d_finalize_w_return(
    holo_base_msg_numerics_Vector8d* sample)
{

    holo_base_msg_numerics_Vector8d_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_numerics_Vector8d_finalize_ex(
    holo_base_msg_numerics_Vector8d* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_numerics_Vector8d_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_numerics_Vector8d_finalize_w_params(
    holo_base_msg_numerics_Vector8d* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_numerics_Vector8d_finalize_optional_members(
    holo_base_msg_numerics_Vector8d* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_numerics_Vector8d_copy(
    holo_base_msg_numerics_Vector8d* dst,
    const holo_base_msg_numerics_Vector8d* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_copy_array((*dst) ,(*src),(8) * CDR_DOUBLE_SIZE);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_numerics_Vector8d' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector8d
#define TSeq holo_base_msg_numerics_Vector8dSeq

#define T_initialize holo_base_msg_numerics_Vector8d_initialize

#define T_finalize   holo_base_msg_numerics_Vector8d_finalize
#define T_copy       holo_base_msg_numerics_Vector8d_copy

#define T_no_get  
#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector8d
#define TSeq holo_base_msg_numerics_Vector8dSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_no_get  

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_numerics_Vectorf *
holo_base_msg_numerics_Vectorf_create(void)
{
    holo_base_msg_numerics_Vectorf* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_numerics_Vectorf);
    if (sample != NULL) {
        if (!holo_base_msg_numerics_Vectorf_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_numerics_Vectorf_delete(holo_base_msg_numerics_Vectorf*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_numerics_Vectorf_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_numerics_Vectorf_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_numerics_Vectorf_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_numerics_Vectorf_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_numerics_Vectorf_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::numerics::Vectorf", /* Name */
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
        }}; /* Type code for  holo_base_msg_numerics_Vectorf */

    if (is_initialized) {
        return &holo_base_msg_numerics_Vectorf_g_tc;
    }

    holo_base_msg_numerics_Vectorf_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_numerics_Vectorf_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_numerics_Vectorf_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_numerics_Vectorf_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_numerics_Vectorf_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_numerics_Vectorf_g_tc._data._sampleAccessInfo =
    holo_base_msg_numerics_Vectorf_get_sample_access_info();
    holo_base_msg_numerics_Vectorf_g_tc._data._typePlugin =
    holo_base_msg_numerics_Vectorf_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_numerics_Vectorf_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_numerics_Vectorf_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_numerics_Vectorf_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_numerics_Vectorf_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vectorf_g_sampleAccessInfo;
    }

    holo_base_msg_numerics_Vectorf_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_numerics_Vectorf_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_numerics_Vectorf_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_numerics_Vectorf);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_numerics_Vectorf_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_numerics_Vectorf_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_numerics_Vectorf_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vectorf_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_numerics_Vectorf_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_numerics_Vectorf_g_typePlugin = 
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
        holo_base_msg_numerics_Vectorf_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_numerics_Vectorf_finalize_w_return,
        NULL
    };

    return &holo_base_msg_numerics_Vectorf_g_typePlugin;
}
#endif

RTIBool holo_base_msg_numerics_Vectorf_initialize(
    holo_base_msg_numerics_Vectorf* sample) {
    return holo_base_msg_numerics_Vectorf_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_numerics_Vectorf_initialize_ex(
    holo_base_msg_numerics_Vectorf* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_numerics_Vectorf_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_numerics_Vectorf_initialize_w_params(
    holo_base_msg_numerics_Vectorf* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

RTIBool holo_base_msg_numerics_Vectorf_finalize(
    holo_base_msg_numerics_Vectorf* sample)
{

    holo_base_msg_numerics_Vectorf_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Vectorf_finalize_w_return(
    holo_base_msg_numerics_Vectorf* sample)
{

    holo_base_msg_numerics_Vectorf_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_numerics_Vectorf_finalize_ex(
    holo_base_msg_numerics_Vectorf* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_numerics_Vectorf_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_numerics_Vectorf_finalize_w_params(
    holo_base_msg_numerics_Vectorf* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
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

void holo_base_msg_numerics_Vectorf_finalize_optional_members(
    holo_base_msg_numerics_Vectorf* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_numerics_Vectorf_copy(
    holo_base_msg_numerics_Vectorf* dst,
    const holo_base_msg_numerics_Vectorf* src)
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
* Configure and implement 'holo_base_msg_numerics_Vectorf' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vectorf
#define TSeq holo_base_msg_numerics_VectorfSeq

#define T_initialize holo_base_msg_numerics_Vectorf_initialize

#define T_finalize   holo_base_msg_numerics_Vectorf_finalize
#define T_copy       holo_base_msg_numerics_Vectorf_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vectorf
#define TSeq holo_base_msg_numerics_VectorfSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_numerics_Vector2f *
holo_base_msg_numerics_Vector2f_create(void)
{
    holo_base_msg_numerics_Vector2f* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_numerics_Vector2f);
    if (sample != NULL) {
        if (!holo_base_msg_numerics_Vector2f_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_numerics_Vector2f_delete(holo_base_msg_numerics_Vector2f*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_numerics_Vector2f_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_numerics_Vector2f_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_numerics_Vector2f_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_numerics_Vector2f_g_tc_array =DDS_INITIALIZE_ARRAY_TYPECODE(1,2, NULL,NULL);

    static DDS_TypeCode holo_base_msg_numerics_Vector2f_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::numerics::Vector2f", /* Name */
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
        }}; /* Type code for  holo_base_msg_numerics_Vector2f */

    if (is_initialized) {
        return &holo_base_msg_numerics_Vector2f_g_tc;
    }

    holo_base_msg_numerics_Vector2f_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_numerics_Vector2f_g_tc_array._data._typeCode =(RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_numerics_Vector2f_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_numerics_Vector2f_g_tc_array;

    /* Initialize the values for member annotations. */

    holo_base_msg_numerics_Vector2f_g_tc._data._sampleAccessInfo =
    holo_base_msg_numerics_Vector2f_get_sample_access_info();
    holo_base_msg_numerics_Vector2f_g_tc._data._typePlugin =
    holo_base_msg_numerics_Vector2f_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_numerics_Vector2f_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_numerics_Vector2f_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_numerics_Vector2f_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_numerics_Vector2f_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vector2f_g_sampleAccessInfo;
    }

    holo_base_msg_numerics_Vector2f_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_numerics_Vector2f_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_numerics_Vector2f_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_numerics_Vector2f);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_numerics_Vector2f_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_numerics_Vector2f_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_numerics_Vector2f_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vector2f_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_numerics_Vector2f_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_numerics_Vector2f_g_typePlugin = 
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
        holo_base_msg_numerics_Vector2f_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_numerics_Vector2f_finalize_w_return,
        NULL
    };

    return &holo_base_msg_numerics_Vector2f_g_typePlugin;
}
#endif

RTIBool holo_base_msg_numerics_Vector2f_initialize(
    holo_base_msg_numerics_Vector2f* sample) {
    return holo_base_msg_numerics_Vector2f_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_numerics_Vector2f_initialize_ex(
    holo_base_msg_numerics_Vector2f* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_numerics_Vector2f_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_numerics_Vector2f_initialize_w_params(
    holo_base_msg_numerics_Vector2f* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_init_array((*sample), ((2))* CDR_FLOAT_SIZE);

    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Vector2f_finalize(
    holo_base_msg_numerics_Vector2f* sample)
{

    holo_base_msg_numerics_Vector2f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Vector2f_finalize_w_return(
    holo_base_msg_numerics_Vector2f* sample)
{

    holo_base_msg_numerics_Vector2f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_numerics_Vector2f_finalize_ex(
    holo_base_msg_numerics_Vector2f* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_numerics_Vector2f_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_numerics_Vector2f_finalize_w_params(
    holo_base_msg_numerics_Vector2f* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_numerics_Vector2f_finalize_optional_members(
    holo_base_msg_numerics_Vector2f* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_numerics_Vector2f_copy(
    holo_base_msg_numerics_Vector2f* dst,
    const holo_base_msg_numerics_Vector2f* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_copy_array((*dst) ,(*src),(2) * CDR_FLOAT_SIZE);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_numerics_Vector2f' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector2f
#define TSeq holo_base_msg_numerics_Vector2fSeq

#define T_initialize holo_base_msg_numerics_Vector2f_initialize

#define T_finalize   holo_base_msg_numerics_Vector2f_finalize
#define T_copy       holo_base_msg_numerics_Vector2f_copy

#define T_no_get  
#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector2f
#define TSeq holo_base_msg_numerics_Vector2fSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_no_get  

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_numerics_Vector3f *
holo_base_msg_numerics_Vector3f_create(void)
{
    holo_base_msg_numerics_Vector3f* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_numerics_Vector3f);
    if (sample != NULL) {
        if (!holo_base_msg_numerics_Vector3f_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_numerics_Vector3f_delete(holo_base_msg_numerics_Vector3f*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_numerics_Vector3f_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_numerics_Vector3f_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_numerics_Vector3f_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_numerics_Vector3f_g_tc_array =DDS_INITIALIZE_ARRAY_TYPECODE(1,3, NULL,NULL);

    static DDS_TypeCode holo_base_msg_numerics_Vector3f_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::numerics::Vector3f", /* Name */
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
        }}; /* Type code for  holo_base_msg_numerics_Vector3f */

    if (is_initialized) {
        return &holo_base_msg_numerics_Vector3f_g_tc;
    }

    holo_base_msg_numerics_Vector3f_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_numerics_Vector3f_g_tc_array._data._typeCode =(RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_numerics_Vector3f_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_numerics_Vector3f_g_tc_array;

    /* Initialize the values for member annotations. */

    holo_base_msg_numerics_Vector3f_g_tc._data._sampleAccessInfo =
    holo_base_msg_numerics_Vector3f_get_sample_access_info();
    holo_base_msg_numerics_Vector3f_g_tc._data._typePlugin =
    holo_base_msg_numerics_Vector3f_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_numerics_Vector3f_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_numerics_Vector3f_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_numerics_Vector3f_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_numerics_Vector3f_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vector3f_g_sampleAccessInfo;
    }

    holo_base_msg_numerics_Vector3f_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_numerics_Vector3f_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_numerics_Vector3f_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_numerics_Vector3f);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_numerics_Vector3f_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_numerics_Vector3f_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_numerics_Vector3f_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vector3f_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_numerics_Vector3f_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_numerics_Vector3f_g_typePlugin = 
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
        holo_base_msg_numerics_Vector3f_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_numerics_Vector3f_finalize_w_return,
        NULL
    };

    return &holo_base_msg_numerics_Vector3f_g_typePlugin;
}
#endif

RTIBool holo_base_msg_numerics_Vector3f_initialize(
    holo_base_msg_numerics_Vector3f* sample) {
    return holo_base_msg_numerics_Vector3f_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_numerics_Vector3f_initialize_ex(
    holo_base_msg_numerics_Vector3f* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_numerics_Vector3f_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_numerics_Vector3f_initialize_w_params(
    holo_base_msg_numerics_Vector3f* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_init_array((*sample), ((3))* CDR_FLOAT_SIZE);

    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Vector3f_finalize(
    holo_base_msg_numerics_Vector3f* sample)
{

    holo_base_msg_numerics_Vector3f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Vector3f_finalize_w_return(
    holo_base_msg_numerics_Vector3f* sample)
{

    holo_base_msg_numerics_Vector3f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_numerics_Vector3f_finalize_ex(
    holo_base_msg_numerics_Vector3f* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_numerics_Vector3f_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_numerics_Vector3f_finalize_w_params(
    holo_base_msg_numerics_Vector3f* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_numerics_Vector3f_finalize_optional_members(
    holo_base_msg_numerics_Vector3f* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_numerics_Vector3f_copy(
    holo_base_msg_numerics_Vector3f* dst,
    const holo_base_msg_numerics_Vector3f* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_copy_array((*dst) ,(*src),(3) * CDR_FLOAT_SIZE);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_numerics_Vector3f' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector3f
#define TSeq holo_base_msg_numerics_Vector3fSeq

#define T_initialize holo_base_msg_numerics_Vector3f_initialize

#define T_finalize   holo_base_msg_numerics_Vector3f_finalize
#define T_copy       holo_base_msg_numerics_Vector3f_copy

#define T_no_get  
#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector3f
#define TSeq holo_base_msg_numerics_Vector3fSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_no_get  

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_numerics_Vector4f *
holo_base_msg_numerics_Vector4f_create(void)
{
    holo_base_msg_numerics_Vector4f* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_numerics_Vector4f);
    if (sample != NULL) {
        if (!holo_base_msg_numerics_Vector4f_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_numerics_Vector4f_delete(holo_base_msg_numerics_Vector4f*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_numerics_Vector4f_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_numerics_Vector4f_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_numerics_Vector4f_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_numerics_Vector4f_g_tc_array =DDS_INITIALIZE_ARRAY_TYPECODE(1,4, NULL,NULL);

    static DDS_TypeCode holo_base_msg_numerics_Vector4f_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::numerics::Vector4f", /* Name */
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
        }}; /* Type code for  holo_base_msg_numerics_Vector4f */

    if (is_initialized) {
        return &holo_base_msg_numerics_Vector4f_g_tc;
    }

    holo_base_msg_numerics_Vector4f_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_numerics_Vector4f_g_tc_array._data._typeCode =(RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_numerics_Vector4f_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_numerics_Vector4f_g_tc_array;

    /* Initialize the values for member annotations. */

    holo_base_msg_numerics_Vector4f_g_tc._data._sampleAccessInfo =
    holo_base_msg_numerics_Vector4f_get_sample_access_info();
    holo_base_msg_numerics_Vector4f_g_tc._data._typePlugin =
    holo_base_msg_numerics_Vector4f_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_numerics_Vector4f_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_numerics_Vector4f_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_numerics_Vector4f_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_numerics_Vector4f_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vector4f_g_sampleAccessInfo;
    }

    holo_base_msg_numerics_Vector4f_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_numerics_Vector4f_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_numerics_Vector4f_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_numerics_Vector4f);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_numerics_Vector4f_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_numerics_Vector4f_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_numerics_Vector4f_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vector4f_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_numerics_Vector4f_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_numerics_Vector4f_g_typePlugin = 
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
        holo_base_msg_numerics_Vector4f_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_numerics_Vector4f_finalize_w_return,
        NULL
    };

    return &holo_base_msg_numerics_Vector4f_g_typePlugin;
}
#endif

RTIBool holo_base_msg_numerics_Vector4f_initialize(
    holo_base_msg_numerics_Vector4f* sample) {
    return holo_base_msg_numerics_Vector4f_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_numerics_Vector4f_initialize_ex(
    holo_base_msg_numerics_Vector4f* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_numerics_Vector4f_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_numerics_Vector4f_initialize_w_params(
    holo_base_msg_numerics_Vector4f* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_init_array((*sample), ((4))* CDR_FLOAT_SIZE);

    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Vector4f_finalize(
    holo_base_msg_numerics_Vector4f* sample)
{

    holo_base_msg_numerics_Vector4f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Vector4f_finalize_w_return(
    holo_base_msg_numerics_Vector4f* sample)
{

    holo_base_msg_numerics_Vector4f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_numerics_Vector4f_finalize_ex(
    holo_base_msg_numerics_Vector4f* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_numerics_Vector4f_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_numerics_Vector4f_finalize_w_params(
    holo_base_msg_numerics_Vector4f* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_numerics_Vector4f_finalize_optional_members(
    holo_base_msg_numerics_Vector4f* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_numerics_Vector4f_copy(
    holo_base_msg_numerics_Vector4f* dst,
    const holo_base_msg_numerics_Vector4f* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_copy_array((*dst) ,(*src),(4) * CDR_FLOAT_SIZE);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_numerics_Vector4f' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector4f
#define TSeq holo_base_msg_numerics_Vector4fSeq

#define T_initialize holo_base_msg_numerics_Vector4f_initialize

#define T_finalize   holo_base_msg_numerics_Vector4f_finalize
#define T_copy       holo_base_msg_numerics_Vector4f_copy

#define T_no_get  
#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector4f
#define TSeq holo_base_msg_numerics_Vector4fSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_no_get  

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_numerics_Vector5f *
holo_base_msg_numerics_Vector5f_create(void)
{
    holo_base_msg_numerics_Vector5f* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_numerics_Vector5f);
    if (sample != NULL) {
        if (!holo_base_msg_numerics_Vector5f_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_numerics_Vector5f_delete(holo_base_msg_numerics_Vector5f*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_numerics_Vector5f_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_numerics_Vector5f_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_numerics_Vector5f_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_numerics_Vector5f_g_tc_array =DDS_INITIALIZE_ARRAY_TYPECODE(1,5, NULL,NULL);

    static DDS_TypeCode holo_base_msg_numerics_Vector5f_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::numerics::Vector5f", /* Name */
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
        }}; /* Type code for  holo_base_msg_numerics_Vector5f */

    if (is_initialized) {
        return &holo_base_msg_numerics_Vector5f_g_tc;
    }

    holo_base_msg_numerics_Vector5f_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_numerics_Vector5f_g_tc_array._data._typeCode =(RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_numerics_Vector5f_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_numerics_Vector5f_g_tc_array;

    /* Initialize the values for member annotations. */

    holo_base_msg_numerics_Vector5f_g_tc._data._sampleAccessInfo =
    holo_base_msg_numerics_Vector5f_get_sample_access_info();
    holo_base_msg_numerics_Vector5f_g_tc._data._typePlugin =
    holo_base_msg_numerics_Vector5f_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_numerics_Vector5f_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_numerics_Vector5f_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_numerics_Vector5f_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_numerics_Vector5f_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vector5f_g_sampleAccessInfo;
    }

    holo_base_msg_numerics_Vector5f_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_numerics_Vector5f_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_numerics_Vector5f_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_numerics_Vector5f);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_numerics_Vector5f_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_numerics_Vector5f_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_numerics_Vector5f_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vector5f_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_numerics_Vector5f_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_numerics_Vector5f_g_typePlugin = 
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
        holo_base_msg_numerics_Vector5f_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_numerics_Vector5f_finalize_w_return,
        NULL
    };

    return &holo_base_msg_numerics_Vector5f_g_typePlugin;
}
#endif

RTIBool holo_base_msg_numerics_Vector5f_initialize(
    holo_base_msg_numerics_Vector5f* sample) {
    return holo_base_msg_numerics_Vector5f_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_numerics_Vector5f_initialize_ex(
    holo_base_msg_numerics_Vector5f* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_numerics_Vector5f_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_numerics_Vector5f_initialize_w_params(
    holo_base_msg_numerics_Vector5f* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_init_array((*sample), ((5))* CDR_FLOAT_SIZE);

    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Vector5f_finalize(
    holo_base_msg_numerics_Vector5f* sample)
{

    holo_base_msg_numerics_Vector5f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Vector5f_finalize_w_return(
    holo_base_msg_numerics_Vector5f* sample)
{

    holo_base_msg_numerics_Vector5f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_numerics_Vector5f_finalize_ex(
    holo_base_msg_numerics_Vector5f* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_numerics_Vector5f_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_numerics_Vector5f_finalize_w_params(
    holo_base_msg_numerics_Vector5f* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_numerics_Vector5f_finalize_optional_members(
    holo_base_msg_numerics_Vector5f* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_numerics_Vector5f_copy(
    holo_base_msg_numerics_Vector5f* dst,
    const holo_base_msg_numerics_Vector5f* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_copy_array((*dst) ,(*src),(5) * CDR_FLOAT_SIZE);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_numerics_Vector5f' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector5f
#define TSeq holo_base_msg_numerics_Vector5fSeq

#define T_initialize holo_base_msg_numerics_Vector5f_initialize

#define T_finalize   holo_base_msg_numerics_Vector5f_finalize
#define T_copy       holo_base_msg_numerics_Vector5f_copy

#define T_no_get  
#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector5f
#define TSeq holo_base_msg_numerics_Vector5fSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_no_get  

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_numerics_Vector6f *
holo_base_msg_numerics_Vector6f_create(void)
{
    holo_base_msg_numerics_Vector6f* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_numerics_Vector6f);
    if (sample != NULL) {
        if (!holo_base_msg_numerics_Vector6f_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_numerics_Vector6f_delete(holo_base_msg_numerics_Vector6f*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_numerics_Vector6f_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_numerics_Vector6f_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_numerics_Vector6f_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_numerics_Vector6f_g_tc_array =DDS_INITIALIZE_ARRAY_TYPECODE(1,6, NULL,NULL);

    static DDS_TypeCode holo_base_msg_numerics_Vector6f_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::numerics::Vector6f", /* Name */
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
        }}; /* Type code for  holo_base_msg_numerics_Vector6f */

    if (is_initialized) {
        return &holo_base_msg_numerics_Vector6f_g_tc;
    }

    holo_base_msg_numerics_Vector6f_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_numerics_Vector6f_g_tc_array._data._typeCode =(RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_numerics_Vector6f_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_numerics_Vector6f_g_tc_array;

    /* Initialize the values for member annotations. */

    holo_base_msg_numerics_Vector6f_g_tc._data._sampleAccessInfo =
    holo_base_msg_numerics_Vector6f_get_sample_access_info();
    holo_base_msg_numerics_Vector6f_g_tc._data._typePlugin =
    holo_base_msg_numerics_Vector6f_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_numerics_Vector6f_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_numerics_Vector6f_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_numerics_Vector6f_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_numerics_Vector6f_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vector6f_g_sampleAccessInfo;
    }

    holo_base_msg_numerics_Vector6f_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_numerics_Vector6f_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_numerics_Vector6f_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_numerics_Vector6f);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_numerics_Vector6f_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_numerics_Vector6f_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_numerics_Vector6f_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vector6f_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_numerics_Vector6f_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_numerics_Vector6f_g_typePlugin = 
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
        holo_base_msg_numerics_Vector6f_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_numerics_Vector6f_finalize_w_return,
        NULL
    };

    return &holo_base_msg_numerics_Vector6f_g_typePlugin;
}
#endif

RTIBool holo_base_msg_numerics_Vector6f_initialize(
    holo_base_msg_numerics_Vector6f* sample) {
    return holo_base_msg_numerics_Vector6f_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_numerics_Vector6f_initialize_ex(
    holo_base_msg_numerics_Vector6f* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_numerics_Vector6f_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_numerics_Vector6f_initialize_w_params(
    holo_base_msg_numerics_Vector6f* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_init_array((*sample), ((6))* CDR_FLOAT_SIZE);

    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Vector6f_finalize(
    holo_base_msg_numerics_Vector6f* sample)
{

    holo_base_msg_numerics_Vector6f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Vector6f_finalize_w_return(
    holo_base_msg_numerics_Vector6f* sample)
{

    holo_base_msg_numerics_Vector6f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_numerics_Vector6f_finalize_ex(
    holo_base_msg_numerics_Vector6f* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_numerics_Vector6f_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_numerics_Vector6f_finalize_w_params(
    holo_base_msg_numerics_Vector6f* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_numerics_Vector6f_finalize_optional_members(
    holo_base_msg_numerics_Vector6f* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_numerics_Vector6f_copy(
    holo_base_msg_numerics_Vector6f* dst,
    const holo_base_msg_numerics_Vector6f* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_copy_array((*dst) ,(*src),(6) * CDR_FLOAT_SIZE);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_numerics_Vector6f' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector6f
#define TSeq holo_base_msg_numerics_Vector6fSeq

#define T_initialize holo_base_msg_numerics_Vector6f_initialize

#define T_finalize   holo_base_msg_numerics_Vector6f_finalize
#define T_copy       holo_base_msg_numerics_Vector6f_copy

#define T_no_get  
#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector6f
#define TSeq holo_base_msg_numerics_Vector6fSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_no_get  

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_numerics_Vector7f *
holo_base_msg_numerics_Vector7f_create(void)
{
    holo_base_msg_numerics_Vector7f* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_numerics_Vector7f);
    if (sample != NULL) {
        if (!holo_base_msg_numerics_Vector7f_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_numerics_Vector7f_delete(holo_base_msg_numerics_Vector7f*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_numerics_Vector7f_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_numerics_Vector7f_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_numerics_Vector7f_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_numerics_Vector7f_g_tc_array =DDS_INITIALIZE_ARRAY_TYPECODE(1,7, NULL,NULL);

    static DDS_TypeCode holo_base_msg_numerics_Vector7f_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::numerics::Vector7f", /* Name */
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
        }}; /* Type code for  holo_base_msg_numerics_Vector7f */

    if (is_initialized) {
        return &holo_base_msg_numerics_Vector7f_g_tc;
    }

    holo_base_msg_numerics_Vector7f_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_numerics_Vector7f_g_tc_array._data._typeCode =(RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_numerics_Vector7f_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_numerics_Vector7f_g_tc_array;

    /* Initialize the values for member annotations. */

    holo_base_msg_numerics_Vector7f_g_tc._data._sampleAccessInfo =
    holo_base_msg_numerics_Vector7f_get_sample_access_info();
    holo_base_msg_numerics_Vector7f_g_tc._data._typePlugin =
    holo_base_msg_numerics_Vector7f_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_numerics_Vector7f_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_numerics_Vector7f_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_numerics_Vector7f_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_numerics_Vector7f_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vector7f_g_sampleAccessInfo;
    }

    holo_base_msg_numerics_Vector7f_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_numerics_Vector7f_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_numerics_Vector7f_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_numerics_Vector7f);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_numerics_Vector7f_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_numerics_Vector7f_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_numerics_Vector7f_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vector7f_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_numerics_Vector7f_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_numerics_Vector7f_g_typePlugin = 
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
        holo_base_msg_numerics_Vector7f_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_numerics_Vector7f_finalize_w_return,
        NULL
    };

    return &holo_base_msg_numerics_Vector7f_g_typePlugin;
}
#endif

RTIBool holo_base_msg_numerics_Vector7f_initialize(
    holo_base_msg_numerics_Vector7f* sample) {
    return holo_base_msg_numerics_Vector7f_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_numerics_Vector7f_initialize_ex(
    holo_base_msg_numerics_Vector7f* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_numerics_Vector7f_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_numerics_Vector7f_initialize_w_params(
    holo_base_msg_numerics_Vector7f* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_init_array((*sample), ((7))* CDR_FLOAT_SIZE);

    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Vector7f_finalize(
    holo_base_msg_numerics_Vector7f* sample)
{

    holo_base_msg_numerics_Vector7f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Vector7f_finalize_w_return(
    holo_base_msg_numerics_Vector7f* sample)
{

    holo_base_msg_numerics_Vector7f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_numerics_Vector7f_finalize_ex(
    holo_base_msg_numerics_Vector7f* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_numerics_Vector7f_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_numerics_Vector7f_finalize_w_params(
    holo_base_msg_numerics_Vector7f* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_numerics_Vector7f_finalize_optional_members(
    holo_base_msg_numerics_Vector7f* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_numerics_Vector7f_copy(
    holo_base_msg_numerics_Vector7f* dst,
    const holo_base_msg_numerics_Vector7f* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_copy_array((*dst) ,(*src),(7) * CDR_FLOAT_SIZE);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_numerics_Vector7f' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector7f
#define TSeq holo_base_msg_numerics_Vector7fSeq

#define T_initialize holo_base_msg_numerics_Vector7f_initialize

#define T_finalize   holo_base_msg_numerics_Vector7f_finalize
#define T_copy       holo_base_msg_numerics_Vector7f_copy

#define T_no_get  
#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector7f
#define TSeq holo_base_msg_numerics_Vector7fSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_no_get  

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_numerics_Vector8f *
holo_base_msg_numerics_Vector8f_create(void)
{
    holo_base_msg_numerics_Vector8f* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_numerics_Vector8f);
    if (sample != NULL) {
        if (!holo_base_msg_numerics_Vector8f_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_numerics_Vector8f_delete(holo_base_msg_numerics_Vector8f*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_numerics_Vector8f_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_numerics_Vector8f_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_numerics_Vector8f_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_numerics_Vector8f_g_tc_array =DDS_INITIALIZE_ARRAY_TYPECODE(1,8, NULL,NULL);

    static DDS_TypeCode holo_base_msg_numerics_Vector8f_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::numerics::Vector8f", /* Name */
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
        }}; /* Type code for  holo_base_msg_numerics_Vector8f */

    if (is_initialized) {
        return &holo_base_msg_numerics_Vector8f_g_tc;
    }

    holo_base_msg_numerics_Vector8f_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_numerics_Vector8f_g_tc_array._data._typeCode =(RTICdrTypeCode *)holo_base_msg_core_float32_t_get_typecode();
    holo_base_msg_numerics_Vector8f_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_numerics_Vector8f_g_tc_array;

    /* Initialize the values for member annotations. */

    holo_base_msg_numerics_Vector8f_g_tc._data._sampleAccessInfo =
    holo_base_msg_numerics_Vector8f_get_sample_access_info();
    holo_base_msg_numerics_Vector8f_g_tc._data._typePlugin =
    holo_base_msg_numerics_Vector8f_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_numerics_Vector8f_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_numerics_Vector8f_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_numerics_Vector8f_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_numerics_Vector8f_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vector8f_g_sampleAccessInfo;
    }

    holo_base_msg_numerics_Vector8f_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_numerics_Vector8f_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_numerics_Vector8f_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_numerics_Vector8f);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_numerics_Vector8f_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_numerics_Vector8f_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_numerics_Vector8f_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_numerics_Vector8f_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_numerics_Vector8f_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_numerics_Vector8f_g_typePlugin = 
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
        holo_base_msg_numerics_Vector8f_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_numerics_Vector8f_finalize_w_return,
        NULL
    };

    return &holo_base_msg_numerics_Vector8f_g_typePlugin;
}
#endif

RTIBool holo_base_msg_numerics_Vector8f_initialize(
    holo_base_msg_numerics_Vector8f* sample) {
    return holo_base_msg_numerics_Vector8f_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_numerics_Vector8f_initialize_ex(
    holo_base_msg_numerics_Vector8f* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_numerics_Vector8f_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_numerics_Vector8f_initialize_w_params(
    holo_base_msg_numerics_Vector8f* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_init_array((*sample), ((8))* CDR_FLOAT_SIZE);

    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Vector8f_finalize(
    holo_base_msg_numerics_Vector8f* sample)
{

    holo_base_msg_numerics_Vector8f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_numerics_Vector8f_finalize_w_return(
    holo_base_msg_numerics_Vector8f* sample)
{

    holo_base_msg_numerics_Vector8f_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_numerics_Vector8f_finalize_ex(
    holo_base_msg_numerics_Vector8f* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_numerics_Vector8f_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_numerics_Vector8f_finalize_w_params(
    holo_base_msg_numerics_Vector8f* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_numerics_Vector8f_finalize_optional_members(
    holo_base_msg_numerics_Vector8f* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_numerics_Vector8f_copy(
    holo_base_msg_numerics_Vector8f* dst,
    const holo_base_msg_numerics_Vector8f* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    CDR_Primitive_copy_array((*dst) ,(*src),(8) * CDR_FLOAT_SIZE);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_numerics_Vector8f' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector8f
#define TSeq holo_base_msg_numerics_Vector8fSeq

#define T_initialize holo_base_msg_numerics_Vector8f_initialize

#define T_finalize   holo_base_msg_numerics_Vector8f_finalize
#define T_copy       holo_base_msg_numerics_Vector8f_copy

#define T_no_get  
#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector8f
#define TSeq holo_base_msg_numerics_Vector8fSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_no_get  

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

