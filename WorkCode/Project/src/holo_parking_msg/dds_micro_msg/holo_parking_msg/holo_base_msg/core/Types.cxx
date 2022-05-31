/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Types.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "Types.h"

#ifndef UNUSED_ARG
#define UNUSED_ARG(x) (void)(x)
#endif

#include "dds_c/dds_c_typecode.h"
/*** SOURCE_BEGIN ***/

holo_base_msg_core_bool_t *
holo_base_msg_core_bool_t_create(void)
{
    holo_base_msg_core_bool_t* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_core_bool_t);
    if (sample != NULL) {
        if (!holo_base_msg_core_bool_t_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_core_bool_t_delete(holo_base_msg_core_bool_t*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_core_bool_t_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_core_bool_t_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_core_bool_t_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_core_bool_t_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::core::bool_t", /* Name */
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
        }}; /* Type code for  holo_base_msg_core_bool_t */

    if (is_initialized) {
        return &holo_base_msg_core_bool_t_g_tc;
    }

    holo_base_msg_core_bool_t_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_core_bool_t_g_tc._data._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_boolean;

    /* Initialize the values for member annotations. */
    holo_base_msg_core_bool_t_g_tc._data._annotations._defaultValue._d = RTI_XCDR_TK_BOOLEAN;
    holo_base_msg_core_bool_t_g_tc._data._annotations._defaultValue._u.boolean_value = 0;

    holo_base_msg_core_bool_t_g_tc._data._sampleAccessInfo =
    holo_base_msg_core_bool_t_get_sample_access_info();
    holo_base_msg_core_bool_t_g_tc._data._typePlugin =
    holo_base_msg_core_bool_t_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_core_bool_t_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_core_bool_t_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_core_bool_t_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_core_bool_t_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_bool_t_g_sampleAccessInfo;
    }

    holo_base_msg_core_bool_t_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_core_bool_t_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_core_bool_t_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_core_bool_t);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_core_bool_t_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_core_bool_t_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_core_bool_t_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_bool_t_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_core_bool_t_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_core_bool_t_g_typePlugin = 
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
        holo_base_msg_core_bool_t_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_core_bool_t_finalize_w_return,
        NULL
    };

    return &holo_base_msg_core_bool_t_g_typePlugin;
}
#endif

RTIBool holo_base_msg_core_bool_t_initialize(
    holo_base_msg_core_bool_t* sample) {
    return holo_base_msg_core_bool_t_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_core_bool_t_initialize_ex(
    holo_base_msg_core_bool_t* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_core_bool_t_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_core_bool_t_initialize_w_params(
    holo_base_msg_core_bool_t* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    (*sample) = 0;

    return RTI_TRUE;
}

RTIBool holo_base_msg_core_bool_t_finalize(
    holo_base_msg_core_bool_t* sample)
{

    holo_base_msg_core_bool_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_bool_t_finalize_w_return(
    holo_base_msg_core_bool_t* sample)
{

    holo_base_msg_core_bool_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_core_bool_t_finalize_ex(
    holo_base_msg_core_bool_t* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_core_bool_t_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_core_bool_t_finalize_w_params(
    holo_base_msg_core_bool_t* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_core_bool_t_finalize_optional_members(
    holo_base_msg_core_bool_t* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_core_bool_t_copy(
    holo_base_msg_core_bool_t* dst,
    const holo_base_msg_core_bool_t* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (dst, src);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_core_bool_t' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_bool_t
#define TSeq holo_base_msg_core_bool_tSeq

#define T_initialize holo_base_msg_core_bool_t_initialize

#define T_finalize   holo_base_msg_core_bool_t_finalize
#define T_copy       holo_base_msg_core_bool_t_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_bool_t
#define TSeq holo_base_msg_core_bool_tSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_core_char_t *
holo_base_msg_core_char_t_create(void)
{
    holo_base_msg_core_char_t* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_core_char_t);
    if (sample != NULL) {
        if (!holo_base_msg_core_char_t_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_core_char_t_delete(holo_base_msg_core_char_t*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_core_char_t_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_core_char_t_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_core_char_t_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_core_char_t_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::core::char_t", /* Name */
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
        }}; /* Type code for  holo_base_msg_core_char_t */

    if (is_initialized) {
        return &holo_base_msg_core_char_t_g_tc;
    }

    holo_base_msg_core_char_t_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_core_char_t_g_tc._data._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_char;

    /* Initialize the values for member annotations. */
    holo_base_msg_core_char_t_g_tc._data._annotations._defaultValue._d = RTI_XCDR_TK_CHAR;
    holo_base_msg_core_char_t_g_tc._data._annotations._defaultValue._u.char_value = 0;

    holo_base_msg_core_char_t_g_tc._data._sampleAccessInfo =
    holo_base_msg_core_char_t_get_sample_access_info();
    holo_base_msg_core_char_t_g_tc._data._typePlugin =
    holo_base_msg_core_char_t_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_core_char_t_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_core_char_t_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_core_char_t_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_core_char_t_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_char_t_g_sampleAccessInfo;
    }

    holo_base_msg_core_char_t_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_core_char_t_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_core_char_t_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_core_char_t);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_core_char_t_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_core_char_t_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_core_char_t_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_char_t_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_core_char_t_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_core_char_t_g_typePlugin = 
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
        holo_base_msg_core_char_t_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_core_char_t_finalize_w_return,
        NULL
    };

    return &holo_base_msg_core_char_t_g_typePlugin;
}
#endif

RTIBool holo_base_msg_core_char_t_initialize(
    holo_base_msg_core_char_t* sample) {
    return holo_base_msg_core_char_t_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_core_char_t_initialize_ex(
    holo_base_msg_core_char_t* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_core_char_t_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_core_char_t_initialize_w_params(
    holo_base_msg_core_char_t* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    (*sample) = 0;

    return RTI_TRUE;
}

RTIBool holo_base_msg_core_char_t_finalize(
    holo_base_msg_core_char_t* sample)
{

    holo_base_msg_core_char_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_char_t_finalize_w_return(
    holo_base_msg_core_char_t* sample)
{

    holo_base_msg_core_char_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_core_char_t_finalize_ex(
    holo_base_msg_core_char_t* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_core_char_t_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_core_char_t_finalize_w_params(
    holo_base_msg_core_char_t* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_core_char_t_finalize_optional_members(
    holo_base_msg_core_char_t* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_core_char_t_copy(
    holo_base_msg_core_char_t* dst,
    const holo_base_msg_core_char_t* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (dst, src);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_core_char_t' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_char_t
#define TSeq holo_base_msg_core_char_tSeq

#define T_initialize holo_base_msg_core_char_t_initialize

#define T_finalize   holo_base_msg_core_char_t_finalize
#define T_copy       holo_base_msg_core_char_t_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_char_t
#define TSeq holo_base_msg_core_char_tSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_core__cxx_wchar_t *
holo_base_msg_core__cxx_wchar_t_create(void)
{
    holo_base_msg_core__cxx_wchar_t* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_core__cxx_wchar_t);
    if (sample != NULL) {
        if (!holo_base_msg_core__cxx_wchar_t_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_core__cxx_wchar_t_delete(holo_base_msg_core__cxx_wchar_t*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_core__cxx_wchar_t_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_core__cxx_wchar_t_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_core__cxx_wchar_t_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_core__cxx_wchar_t_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::core::wchar_t", /* Name */
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
        }}; /* Type code for  holo_base_msg_core__cxx_wchar_t */

    if (is_initialized) {
        return &holo_base_msg_core__cxx_wchar_t_g_tc;
    }

    holo_base_msg_core__cxx_wchar_t_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_core__cxx_wchar_t_g_tc._data._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_wchar;

    /* Initialize the values for member annotations. */
    holo_base_msg_core__cxx_wchar_t_g_tc._data._annotations._defaultValue._d = RTI_XCDR_TK_WCHAR;
    holo_base_msg_core__cxx_wchar_t_g_tc._data._annotations._defaultValue._u.wchar_value = 0;

    holo_base_msg_core__cxx_wchar_t_g_tc._data._sampleAccessInfo =
    holo_base_msg_core__cxx_wchar_t_get_sample_access_info();
    holo_base_msg_core__cxx_wchar_t_g_tc._data._typePlugin =
    holo_base_msg_core__cxx_wchar_t_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_core__cxx_wchar_t_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_core__cxx_wchar_t_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_core__cxx_wchar_t_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_core__cxx_wchar_t_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core__cxx_wchar_t_g_sampleAccessInfo;
    }

    holo_base_msg_core__cxx_wchar_t_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_core__cxx_wchar_t_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_core__cxx_wchar_t_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_core__cxx_wchar_t);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_core__cxx_wchar_t_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_core__cxx_wchar_t_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_core__cxx_wchar_t_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core__cxx_wchar_t_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_core__cxx_wchar_t_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_core__cxx_wchar_t_g_typePlugin = 
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
        holo_base_msg_core__cxx_wchar_t_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_core__cxx_wchar_t_finalize_w_return,
        NULL
    };

    return &holo_base_msg_core__cxx_wchar_t_g_typePlugin;
}
#endif

RTIBool holo_base_msg_core__cxx_wchar_t_initialize(
    holo_base_msg_core__cxx_wchar_t* sample) {
    return holo_base_msg_core__cxx_wchar_t_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_core__cxx_wchar_t_initialize_ex(
    holo_base_msg_core__cxx_wchar_t* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_core__cxx_wchar_t_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_core__cxx_wchar_t_initialize_w_params(
    holo_base_msg_core__cxx_wchar_t* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    (*sample) = 0;

    return RTI_TRUE;
}

RTIBool holo_base_msg_core__cxx_wchar_t_finalize(
    holo_base_msg_core__cxx_wchar_t* sample)
{

    holo_base_msg_core__cxx_wchar_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_core__cxx_wchar_t_finalize_w_return(
    holo_base_msg_core__cxx_wchar_t* sample)
{

    holo_base_msg_core__cxx_wchar_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_core__cxx_wchar_t_finalize_ex(
    holo_base_msg_core__cxx_wchar_t* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_core__cxx_wchar_t_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_core__cxx_wchar_t_finalize_w_params(
    holo_base_msg_core__cxx_wchar_t* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_core__cxx_wchar_t_finalize_optional_members(
    holo_base_msg_core__cxx_wchar_t* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_core__cxx_wchar_t_copy(
    holo_base_msg_core__cxx_wchar_t* dst,
    const holo_base_msg_core__cxx_wchar_t* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (dst, src);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_core__cxx_wchar_t' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core__cxx_wchar_t
#define TSeq holo_base_msg_core__cxx_wchar_tSeq

#define T_initialize holo_base_msg_core__cxx_wchar_t_initialize

#define T_finalize   holo_base_msg_core__cxx_wchar_t_finalize
#define T_copy       holo_base_msg_core__cxx_wchar_t_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core__cxx_wchar_t
#define TSeq holo_base_msg_core__cxx_wchar_tSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_core_int8_t *
holo_base_msg_core_int8_t_create(void)
{
    holo_base_msg_core_int8_t* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_core_int8_t);
    if (sample != NULL) {
        if (!holo_base_msg_core_int8_t_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_core_int8_t_delete(holo_base_msg_core_int8_t*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_core_int8_t_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_core_int8_t_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_core_int8_t_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_core_int8_t_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::core::int8_t", /* Name */
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
        }}; /* Type code for  holo_base_msg_core_int8_t */

    if (is_initialized) {
        return &holo_base_msg_core_int8_t_g_tc;
    }

    holo_base_msg_core_int8_t_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_core_int8_t_g_tc._data._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_char;

    /* Initialize the values for member annotations. */
    holo_base_msg_core_int8_t_g_tc._data._annotations._defaultValue._d = RTI_XCDR_TK_CHAR;
    holo_base_msg_core_int8_t_g_tc._data._annotations._defaultValue._u.char_value = 0;

    holo_base_msg_core_int8_t_g_tc._data._sampleAccessInfo =
    holo_base_msg_core_int8_t_get_sample_access_info();
    holo_base_msg_core_int8_t_g_tc._data._typePlugin =
    holo_base_msg_core_int8_t_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_core_int8_t_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_core_int8_t_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_core_int8_t_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_core_int8_t_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_int8_t_g_sampleAccessInfo;
    }

    holo_base_msg_core_int8_t_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_core_int8_t_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_core_int8_t_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_core_int8_t);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_core_int8_t_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_core_int8_t_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_core_int8_t_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_int8_t_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_core_int8_t_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_core_int8_t_g_typePlugin = 
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
        holo_base_msg_core_int8_t_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_core_int8_t_finalize_w_return,
        NULL
    };

    return &holo_base_msg_core_int8_t_g_typePlugin;
}
#endif

RTIBool holo_base_msg_core_int8_t_initialize(
    holo_base_msg_core_int8_t* sample) {
    return holo_base_msg_core_int8_t_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_core_int8_t_initialize_ex(
    holo_base_msg_core_int8_t* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_core_int8_t_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_core_int8_t_initialize_w_params(
    holo_base_msg_core_int8_t* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    (*sample) = 0;

    return RTI_TRUE;
}

RTIBool holo_base_msg_core_int8_t_finalize(
    holo_base_msg_core_int8_t* sample)
{

    holo_base_msg_core_int8_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_int8_t_finalize_w_return(
    holo_base_msg_core_int8_t* sample)
{

    holo_base_msg_core_int8_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_core_int8_t_finalize_ex(
    holo_base_msg_core_int8_t* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_core_int8_t_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_core_int8_t_finalize_w_params(
    holo_base_msg_core_int8_t* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_core_int8_t_finalize_optional_members(
    holo_base_msg_core_int8_t* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_core_int8_t_copy(
    holo_base_msg_core_int8_t* dst,
    const holo_base_msg_core_int8_t* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (dst, src);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_core_int8_t' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_int8_t
#define TSeq holo_base_msg_core_int8_tSeq

#define T_initialize holo_base_msg_core_int8_t_initialize

#define T_finalize   holo_base_msg_core_int8_t_finalize
#define T_copy       holo_base_msg_core_int8_t_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_int8_t
#define TSeq holo_base_msg_core_int8_tSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_core_uint8_t *
holo_base_msg_core_uint8_t_create(void)
{
    holo_base_msg_core_uint8_t* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_core_uint8_t);
    if (sample != NULL) {
        if (!holo_base_msg_core_uint8_t_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_core_uint8_t_delete(holo_base_msg_core_uint8_t*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_core_uint8_t_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_core_uint8_t_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_core_uint8_t_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_core_uint8_t_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::core::uint8_t", /* Name */
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
        }}; /* Type code for  holo_base_msg_core_uint8_t */

    if (is_initialized) {
        return &holo_base_msg_core_uint8_t_g_tc;
    }

    holo_base_msg_core_uint8_t_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_core_uint8_t_g_tc._data._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_octet;

    /* Initialize the values for member annotations. */
    holo_base_msg_core_uint8_t_g_tc._data._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_core_uint8_t_g_tc._data._annotations._defaultValue._u.octet_value = 0;
    holo_base_msg_core_uint8_t_g_tc._data._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_core_uint8_t_g_tc._data._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    holo_base_msg_core_uint8_t_g_tc._data._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    holo_base_msg_core_uint8_t_g_tc._data._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    holo_base_msg_core_uint8_t_g_tc._data._sampleAccessInfo =
    holo_base_msg_core_uint8_t_get_sample_access_info();
    holo_base_msg_core_uint8_t_g_tc._data._typePlugin =
    holo_base_msg_core_uint8_t_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_core_uint8_t_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_core_uint8_t_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_core_uint8_t_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_core_uint8_t_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_uint8_t_g_sampleAccessInfo;
    }

    holo_base_msg_core_uint8_t_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_core_uint8_t_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_core_uint8_t_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_core_uint8_t);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_core_uint8_t_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_core_uint8_t_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_core_uint8_t_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_uint8_t_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_core_uint8_t_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_core_uint8_t_g_typePlugin = 
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
        holo_base_msg_core_uint8_t_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_core_uint8_t_finalize_w_return,
        NULL
    };

    return &holo_base_msg_core_uint8_t_g_typePlugin;
}
#endif

RTIBool holo_base_msg_core_uint8_t_initialize(
    holo_base_msg_core_uint8_t* sample) {
    return holo_base_msg_core_uint8_t_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_core_uint8_t_initialize_ex(
    holo_base_msg_core_uint8_t* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_core_uint8_t_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_core_uint8_t_initialize_w_params(
    holo_base_msg_core_uint8_t* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    (*sample) = 0;

    return RTI_TRUE;
}

RTIBool holo_base_msg_core_uint8_t_finalize(
    holo_base_msg_core_uint8_t* sample)
{

    holo_base_msg_core_uint8_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_uint8_t_finalize_w_return(
    holo_base_msg_core_uint8_t* sample)
{

    holo_base_msg_core_uint8_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_core_uint8_t_finalize_ex(
    holo_base_msg_core_uint8_t* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_core_uint8_t_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_core_uint8_t_finalize_w_params(
    holo_base_msg_core_uint8_t* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_core_uint8_t_finalize_optional_members(
    holo_base_msg_core_uint8_t* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_core_uint8_t_copy(
    holo_base_msg_core_uint8_t* dst,
    const holo_base_msg_core_uint8_t* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (dst, src);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_core_uint8_t' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_uint8_t
#define TSeq holo_base_msg_core_uint8_tSeq

#define T_initialize holo_base_msg_core_uint8_t_initialize

#define T_finalize   holo_base_msg_core_uint8_t_finalize
#define T_copy       holo_base_msg_core_uint8_t_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_uint8_t
#define TSeq holo_base_msg_core_uint8_tSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_core_int16_t *
holo_base_msg_core_int16_t_create(void)
{
    holo_base_msg_core_int16_t* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_core_int16_t);
    if (sample != NULL) {
        if (!holo_base_msg_core_int16_t_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_core_int16_t_delete(holo_base_msg_core_int16_t*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_core_int16_t_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_core_int16_t_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_core_int16_t_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_core_int16_t_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::core::int16_t", /* Name */
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
        }}; /* Type code for  holo_base_msg_core_int16_t */

    if (is_initialized) {
        return &holo_base_msg_core_int16_t_g_tc;
    }

    holo_base_msg_core_int16_t_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_core_int16_t_g_tc._data._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_short;

    /* Initialize the values for member annotations. */
    holo_base_msg_core_int16_t_g_tc._data._annotations._defaultValue._d = RTI_XCDR_TK_SHORT;
    holo_base_msg_core_int16_t_g_tc._data._annotations._defaultValue._u.short_value = 0;
    holo_base_msg_core_int16_t_g_tc._data._annotations._minValue._d = RTI_XCDR_TK_SHORT;
    holo_base_msg_core_int16_t_g_tc._data._annotations._minValue._u.short_value = RTIXCdrShort_MIN;
    holo_base_msg_core_int16_t_g_tc._data._annotations._maxValue._d = RTI_XCDR_TK_SHORT;
    holo_base_msg_core_int16_t_g_tc._data._annotations._maxValue._u.short_value = RTIXCdrShort_MAX;

    holo_base_msg_core_int16_t_g_tc._data._sampleAccessInfo =
    holo_base_msg_core_int16_t_get_sample_access_info();
    holo_base_msg_core_int16_t_g_tc._data._typePlugin =
    holo_base_msg_core_int16_t_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_core_int16_t_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_core_int16_t_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_core_int16_t_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_core_int16_t_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_int16_t_g_sampleAccessInfo;
    }

    holo_base_msg_core_int16_t_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_core_int16_t_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_core_int16_t_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_core_int16_t);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_core_int16_t_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_core_int16_t_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_core_int16_t_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_int16_t_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_core_int16_t_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_core_int16_t_g_typePlugin = 
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
        holo_base_msg_core_int16_t_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_core_int16_t_finalize_w_return,
        NULL
    };

    return &holo_base_msg_core_int16_t_g_typePlugin;
}
#endif

RTIBool holo_base_msg_core_int16_t_initialize(
    holo_base_msg_core_int16_t* sample) {
    return holo_base_msg_core_int16_t_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_core_int16_t_initialize_ex(
    holo_base_msg_core_int16_t* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_core_int16_t_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_core_int16_t_initialize_w_params(
    holo_base_msg_core_int16_t* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    (*sample) = 0;

    return RTI_TRUE;
}

RTIBool holo_base_msg_core_int16_t_finalize(
    holo_base_msg_core_int16_t* sample)
{

    holo_base_msg_core_int16_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_int16_t_finalize_w_return(
    holo_base_msg_core_int16_t* sample)
{

    holo_base_msg_core_int16_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_core_int16_t_finalize_ex(
    holo_base_msg_core_int16_t* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_core_int16_t_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_core_int16_t_finalize_w_params(
    holo_base_msg_core_int16_t* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_core_int16_t_finalize_optional_members(
    holo_base_msg_core_int16_t* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_core_int16_t_copy(
    holo_base_msg_core_int16_t* dst,
    const holo_base_msg_core_int16_t* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (dst, src);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_core_int16_t' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_int16_t
#define TSeq holo_base_msg_core_int16_tSeq

#define T_initialize holo_base_msg_core_int16_t_initialize

#define T_finalize   holo_base_msg_core_int16_t_finalize
#define T_copy       holo_base_msg_core_int16_t_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_int16_t
#define TSeq holo_base_msg_core_int16_tSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_core_uint16_t *
holo_base_msg_core_uint16_t_create(void)
{
    holo_base_msg_core_uint16_t* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_core_uint16_t);
    if (sample != NULL) {
        if (!holo_base_msg_core_uint16_t_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_core_uint16_t_delete(holo_base_msg_core_uint16_t*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_core_uint16_t_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_core_uint16_t_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_core_uint16_t_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_core_uint16_t_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::core::uint16_t", /* Name */
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
        }}; /* Type code for  holo_base_msg_core_uint16_t */

    if (is_initialized) {
        return &holo_base_msg_core_uint16_t_g_tc;
    }

    holo_base_msg_core_uint16_t_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_core_uint16_t_g_tc._data._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;

    /* Initialize the values for member annotations. */
    holo_base_msg_core_uint16_t_g_tc._data._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
    holo_base_msg_core_uint16_t_g_tc._data._annotations._defaultValue._u.ushort_value = 0;
    holo_base_msg_core_uint16_t_g_tc._data._annotations._minValue._d = RTI_XCDR_TK_USHORT;
    holo_base_msg_core_uint16_t_g_tc._data._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
    holo_base_msg_core_uint16_t_g_tc._data._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
    holo_base_msg_core_uint16_t_g_tc._data._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

    holo_base_msg_core_uint16_t_g_tc._data._sampleAccessInfo =
    holo_base_msg_core_uint16_t_get_sample_access_info();
    holo_base_msg_core_uint16_t_g_tc._data._typePlugin =
    holo_base_msg_core_uint16_t_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_core_uint16_t_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_core_uint16_t_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_core_uint16_t_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_core_uint16_t_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_uint16_t_g_sampleAccessInfo;
    }

    holo_base_msg_core_uint16_t_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_core_uint16_t_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_core_uint16_t_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_core_uint16_t);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_core_uint16_t_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_core_uint16_t_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_core_uint16_t_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_uint16_t_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_core_uint16_t_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_core_uint16_t_g_typePlugin = 
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
        holo_base_msg_core_uint16_t_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_core_uint16_t_finalize_w_return,
        NULL
    };

    return &holo_base_msg_core_uint16_t_g_typePlugin;
}
#endif

RTIBool holo_base_msg_core_uint16_t_initialize(
    holo_base_msg_core_uint16_t* sample) {
    return holo_base_msg_core_uint16_t_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_core_uint16_t_initialize_ex(
    holo_base_msg_core_uint16_t* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_core_uint16_t_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_core_uint16_t_initialize_w_params(
    holo_base_msg_core_uint16_t* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    (*sample) = 0;

    return RTI_TRUE;
}

RTIBool holo_base_msg_core_uint16_t_finalize(
    holo_base_msg_core_uint16_t* sample)
{

    holo_base_msg_core_uint16_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_uint16_t_finalize_w_return(
    holo_base_msg_core_uint16_t* sample)
{

    holo_base_msg_core_uint16_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_core_uint16_t_finalize_ex(
    holo_base_msg_core_uint16_t* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_core_uint16_t_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_core_uint16_t_finalize_w_params(
    holo_base_msg_core_uint16_t* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_core_uint16_t_finalize_optional_members(
    holo_base_msg_core_uint16_t* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_core_uint16_t_copy(
    holo_base_msg_core_uint16_t* dst,
    const holo_base_msg_core_uint16_t* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (dst, src);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_core_uint16_t' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_uint16_t
#define TSeq holo_base_msg_core_uint16_tSeq

#define T_initialize holo_base_msg_core_uint16_t_initialize

#define T_finalize   holo_base_msg_core_uint16_t_finalize
#define T_copy       holo_base_msg_core_uint16_t_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_uint16_t
#define TSeq holo_base_msg_core_uint16_tSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_core_int32_t *
holo_base_msg_core_int32_t_create(void)
{
    holo_base_msg_core_int32_t* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_core_int32_t);
    if (sample != NULL) {
        if (!holo_base_msg_core_int32_t_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_core_int32_t_delete(holo_base_msg_core_int32_t*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_core_int32_t_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_core_int32_t_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_core_int32_t_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_core_int32_t_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::core::int32_t", /* Name */
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
        }}; /* Type code for  holo_base_msg_core_int32_t */

    if (is_initialized) {
        return &holo_base_msg_core_int32_t_g_tc;
    }

    holo_base_msg_core_int32_t_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_core_int32_t_g_tc._data._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_long;

    /* Initialize the values for member annotations. */
    holo_base_msg_core_int32_t_g_tc._data._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    holo_base_msg_core_int32_t_g_tc._data._annotations._defaultValue._u.long_value = 0;
    holo_base_msg_core_int32_t_g_tc._data._annotations._minValue._d = RTI_XCDR_TK_LONG;
    holo_base_msg_core_int32_t_g_tc._data._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    holo_base_msg_core_int32_t_g_tc._data._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    holo_base_msg_core_int32_t_g_tc._data._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    holo_base_msg_core_int32_t_g_tc._data._sampleAccessInfo =
    holo_base_msg_core_int32_t_get_sample_access_info();
    holo_base_msg_core_int32_t_g_tc._data._typePlugin =
    holo_base_msg_core_int32_t_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_core_int32_t_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_core_int32_t_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_core_int32_t_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_core_int32_t_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_int32_t_g_sampleAccessInfo;
    }

    holo_base_msg_core_int32_t_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_core_int32_t_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_core_int32_t_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_core_int32_t);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_core_int32_t_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_core_int32_t_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_core_int32_t_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_int32_t_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_core_int32_t_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_core_int32_t_g_typePlugin = 
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
        holo_base_msg_core_int32_t_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_core_int32_t_finalize_w_return,
        NULL
    };

    return &holo_base_msg_core_int32_t_g_typePlugin;
}
#endif

RTIBool holo_base_msg_core_int32_t_initialize(
    holo_base_msg_core_int32_t* sample) {
    return holo_base_msg_core_int32_t_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_core_int32_t_initialize_ex(
    holo_base_msg_core_int32_t* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_core_int32_t_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_core_int32_t_initialize_w_params(
    holo_base_msg_core_int32_t* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    (*sample) = 0;

    return RTI_TRUE;
}

RTIBool holo_base_msg_core_int32_t_finalize(
    holo_base_msg_core_int32_t* sample)
{

    holo_base_msg_core_int32_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_int32_t_finalize_w_return(
    holo_base_msg_core_int32_t* sample)
{

    holo_base_msg_core_int32_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_core_int32_t_finalize_ex(
    holo_base_msg_core_int32_t* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_core_int32_t_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_core_int32_t_finalize_w_params(
    holo_base_msg_core_int32_t* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_core_int32_t_finalize_optional_members(
    holo_base_msg_core_int32_t* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_core_int32_t_copy(
    holo_base_msg_core_int32_t* dst,
    const holo_base_msg_core_int32_t* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (dst, src);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_core_int32_t' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_int32_t
#define TSeq holo_base_msg_core_int32_tSeq

#define T_initialize holo_base_msg_core_int32_t_initialize

#define T_finalize   holo_base_msg_core_int32_t_finalize
#define T_copy       holo_base_msg_core_int32_t_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_int32_t
#define TSeq holo_base_msg_core_int32_tSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_core_uint32_t *
holo_base_msg_core_uint32_t_create(void)
{
    holo_base_msg_core_uint32_t* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_core_uint32_t);
    if (sample != NULL) {
        if (!holo_base_msg_core_uint32_t_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_core_uint32_t_delete(holo_base_msg_core_uint32_t*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_core_uint32_t_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_core_uint32_t_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_core_uint32_t_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_core_uint32_t_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::core::uint32_t", /* Name */
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
        }}; /* Type code for  holo_base_msg_core_uint32_t */

    if (is_initialized) {
        return &holo_base_msg_core_uint32_t_g_tc;
    }

    holo_base_msg_core_uint32_t_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_core_uint32_t_g_tc._data._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ulong;

    /* Initialize the values for member annotations. */
    holo_base_msg_core_uint32_t_g_tc._data._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_core_uint32_t_g_tc._data._annotations._defaultValue._u.ulong_value = 0u;
    holo_base_msg_core_uint32_t_g_tc._data._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_core_uint32_t_g_tc._data._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    holo_base_msg_core_uint32_t_g_tc._data._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    holo_base_msg_core_uint32_t_g_tc._data._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    holo_base_msg_core_uint32_t_g_tc._data._sampleAccessInfo =
    holo_base_msg_core_uint32_t_get_sample_access_info();
    holo_base_msg_core_uint32_t_g_tc._data._typePlugin =
    holo_base_msg_core_uint32_t_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_core_uint32_t_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_core_uint32_t_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_core_uint32_t_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_core_uint32_t_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_uint32_t_g_sampleAccessInfo;
    }

    holo_base_msg_core_uint32_t_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_core_uint32_t_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_core_uint32_t_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_core_uint32_t);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_core_uint32_t_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_core_uint32_t_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_core_uint32_t_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_uint32_t_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_core_uint32_t_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_core_uint32_t_g_typePlugin = 
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
        holo_base_msg_core_uint32_t_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_core_uint32_t_finalize_w_return,
        NULL
    };

    return &holo_base_msg_core_uint32_t_g_typePlugin;
}
#endif

RTIBool holo_base_msg_core_uint32_t_initialize(
    holo_base_msg_core_uint32_t* sample) {
    return holo_base_msg_core_uint32_t_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_core_uint32_t_initialize_ex(
    holo_base_msg_core_uint32_t* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_core_uint32_t_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_core_uint32_t_initialize_w_params(
    holo_base_msg_core_uint32_t* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    (*sample) = 0u;

    return RTI_TRUE;
}

RTIBool holo_base_msg_core_uint32_t_finalize(
    holo_base_msg_core_uint32_t* sample)
{

    holo_base_msg_core_uint32_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_uint32_t_finalize_w_return(
    holo_base_msg_core_uint32_t* sample)
{

    holo_base_msg_core_uint32_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_core_uint32_t_finalize_ex(
    holo_base_msg_core_uint32_t* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_core_uint32_t_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_core_uint32_t_finalize_w_params(
    holo_base_msg_core_uint32_t* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_core_uint32_t_finalize_optional_members(
    holo_base_msg_core_uint32_t* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_core_uint32_t_copy(
    holo_base_msg_core_uint32_t* dst,
    const holo_base_msg_core_uint32_t* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (dst, src);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_core_uint32_t' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_uint32_t
#define TSeq holo_base_msg_core_uint32_tSeq

#define T_initialize holo_base_msg_core_uint32_t_initialize

#define T_finalize   holo_base_msg_core_uint32_t_finalize
#define T_copy       holo_base_msg_core_uint32_t_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_uint32_t
#define TSeq holo_base_msg_core_uint32_tSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_core_int64_t *
holo_base_msg_core_int64_t_create(void)
{
    holo_base_msg_core_int64_t* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_core_int64_t);
    if (sample != NULL) {
        if (!holo_base_msg_core_int64_t_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_core_int64_t_delete(holo_base_msg_core_int64_t*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_core_int64_t_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_core_int64_t_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_core_int64_t_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_core_int64_t_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::core::int64_t", /* Name */
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
        }}; /* Type code for  holo_base_msg_core_int64_t */

    if (is_initialized) {
        return &holo_base_msg_core_int64_t_g_tc;
    }

    holo_base_msg_core_int64_t_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_core_int64_t_g_tc._data._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_longlong;

    /* Initialize the values for member annotations. */
    holo_base_msg_core_int64_t_g_tc._data._annotations._defaultValue._d = RTI_XCDR_TK_LONGLONG;
    holo_base_msg_core_int64_t_g_tc._data._annotations._defaultValue._u.long_long_value = 0ll;
    holo_base_msg_core_int64_t_g_tc._data._annotations._minValue._d = RTI_XCDR_TK_LONGLONG;
    holo_base_msg_core_int64_t_g_tc._data._annotations._minValue._u.long_long_value = RTIXCdrLongLong_MIN;
    holo_base_msg_core_int64_t_g_tc._data._annotations._maxValue._d = RTI_XCDR_TK_LONGLONG;
    holo_base_msg_core_int64_t_g_tc._data._annotations._maxValue._u.long_long_value = RTIXCdrLongLong_MAX;

    holo_base_msg_core_int64_t_g_tc._data._sampleAccessInfo =
    holo_base_msg_core_int64_t_get_sample_access_info();
    holo_base_msg_core_int64_t_g_tc._data._typePlugin =
    holo_base_msg_core_int64_t_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_core_int64_t_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_core_int64_t_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_core_int64_t_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_core_int64_t_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_int64_t_g_sampleAccessInfo;
    }

    holo_base_msg_core_int64_t_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_core_int64_t_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_core_int64_t_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_core_int64_t);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_core_int64_t_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_core_int64_t_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_core_int64_t_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_int64_t_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_core_int64_t_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_core_int64_t_g_typePlugin = 
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
        holo_base_msg_core_int64_t_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_core_int64_t_finalize_w_return,
        NULL
    };

    return &holo_base_msg_core_int64_t_g_typePlugin;
}
#endif

RTIBool holo_base_msg_core_int64_t_initialize(
    holo_base_msg_core_int64_t* sample) {
    return holo_base_msg_core_int64_t_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_core_int64_t_initialize_ex(
    holo_base_msg_core_int64_t* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_core_int64_t_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_core_int64_t_initialize_w_params(
    holo_base_msg_core_int64_t* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    (*sample) = 0ll;

    return RTI_TRUE;
}

RTIBool holo_base_msg_core_int64_t_finalize(
    holo_base_msg_core_int64_t* sample)
{

    holo_base_msg_core_int64_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_int64_t_finalize_w_return(
    holo_base_msg_core_int64_t* sample)
{

    holo_base_msg_core_int64_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_core_int64_t_finalize_ex(
    holo_base_msg_core_int64_t* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_core_int64_t_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_core_int64_t_finalize_w_params(
    holo_base_msg_core_int64_t* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_core_int64_t_finalize_optional_members(
    holo_base_msg_core_int64_t* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_core_int64_t_copy(
    holo_base_msg_core_int64_t* dst,
    const holo_base_msg_core_int64_t* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (dst, src);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_core_int64_t' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_int64_t
#define TSeq holo_base_msg_core_int64_tSeq

#define T_initialize holo_base_msg_core_int64_t_initialize

#define T_finalize   holo_base_msg_core_int64_t_finalize
#define T_copy       holo_base_msg_core_int64_t_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_int64_t
#define TSeq holo_base_msg_core_int64_tSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_core_uint64_t *
holo_base_msg_core_uint64_t_create(void)
{
    holo_base_msg_core_uint64_t* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_core_uint64_t);
    if (sample != NULL) {
        if (!holo_base_msg_core_uint64_t_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_core_uint64_t_delete(holo_base_msg_core_uint64_t*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_core_uint64_t_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_core_uint64_t_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_core_uint64_t_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_core_uint64_t_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::core::uint64_t", /* Name */
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
        }}; /* Type code for  holo_base_msg_core_uint64_t */

    if (is_initialized) {
        return &holo_base_msg_core_uint64_t_g_tc;
    }

    holo_base_msg_core_uint64_t_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_core_uint64_t_g_tc._data._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ulonglong;

    /* Initialize the values for member annotations. */
    holo_base_msg_core_uint64_t_g_tc._data._annotations._defaultValue._d = RTI_XCDR_TK_ULONGLONG;
    holo_base_msg_core_uint64_t_g_tc._data._annotations._defaultValue._u.ulong_long_value = 0ull;
    holo_base_msg_core_uint64_t_g_tc._data._annotations._minValue._d = RTI_XCDR_TK_ULONGLONG;
    holo_base_msg_core_uint64_t_g_tc._data._annotations._minValue._u.ulong_long_value = RTIXCdrUnsignedLongLong_MIN;
    holo_base_msg_core_uint64_t_g_tc._data._annotations._maxValue._d = RTI_XCDR_TK_ULONGLONG;
    holo_base_msg_core_uint64_t_g_tc._data._annotations._maxValue._u.ulong_long_value = RTIXCdrUnsignedLongLong_MAX;

    holo_base_msg_core_uint64_t_g_tc._data._sampleAccessInfo =
    holo_base_msg_core_uint64_t_get_sample_access_info();
    holo_base_msg_core_uint64_t_g_tc._data._typePlugin =
    holo_base_msg_core_uint64_t_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_core_uint64_t_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_core_uint64_t_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_core_uint64_t_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_core_uint64_t_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_uint64_t_g_sampleAccessInfo;
    }

    holo_base_msg_core_uint64_t_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_core_uint64_t_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_core_uint64_t_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_core_uint64_t);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_core_uint64_t_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_core_uint64_t_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_core_uint64_t_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_uint64_t_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_core_uint64_t_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_core_uint64_t_g_typePlugin = 
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
        holo_base_msg_core_uint64_t_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_core_uint64_t_finalize_w_return,
        NULL
    };

    return &holo_base_msg_core_uint64_t_g_typePlugin;
}
#endif

RTIBool holo_base_msg_core_uint64_t_initialize(
    holo_base_msg_core_uint64_t* sample) {
    return holo_base_msg_core_uint64_t_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_core_uint64_t_initialize_ex(
    holo_base_msg_core_uint64_t* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_core_uint64_t_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_core_uint64_t_initialize_w_params(
    holo_base_msg_core_uint64_t* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    (*sample) = 0ull;

    return RTI_TRUE;
}

RTIBool holo_base_msg_core_uint64_t_finalize(
    holo_base_msg_core_uint64_t* sample)
{

    holo_base_msg_core_uint64_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_uint64_t_finalize_w_return(
    holo_base_msg_core_uint64_t* sample)
{

    holo_base_msg_core_uint64_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_core_uint64_t_finalize_ex(
    holo_base_msg_core_uint64_t* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_core_uint64_t_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_core_uint64_t_finalize_w_params(
    holo_base_msg_core_uint64_t* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_core_uint64_t_finalize_optional_members(
    holo_base_msg_core_uint64_t* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_core_uint64_t_copy(
    holo_base_msg_core_uint64_t* dst,
    const holo_base_msg_core_uint64_t* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (dst, src);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_core_uint64_t' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_uint64_t
#define TSeq holo_base_msg_core_uint64_tSeq

#define T_initialize holo_base_msg_core_uint64_t_initialize

#define T_finalize   holo_base_msg_core_uint64_t_finalize
#define T_copy       holo_base_msg_core_uint64_t_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_uint64_t
#define TSeq holo_base_msg_core_uint64_tSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_core_float32_t *
holo_base_msg_core_float32_t_create(void)
{
    holo_base_msg_core_float32_t* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_core_float32_t);
    if (sample != NULL) {
        if (!holo_base_msg_core_float32_t_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_core_float32_t_delete(holo_base_msg_core_float32_t*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_core_float32_t_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_core_float32_t_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_core_float32_t_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_core_float32_t_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::core::float32_t", /* Name */
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
        }}; /* Type code for  holo_base_msg_core_float32_t */

    if (is_initialized) {
        return &holo_base_msg_core_float32_t_g_tc;
    }

    holo_base_msg_core_float32_t_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_core_float32_t_g_tc._data._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_float;

    /* Initialize the values for member annotations. */
    holo_base_msg_core_float32_t_g_tc._data._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_core_float32_t_g_tc._data._annotations._defaultValue._u.float_value = 0.0f;
    holo_base_msg_core_float32_t_g_tc._data._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_core_float32_t_g_tc._data._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    holo_base_msg_core_float32_t_g_tc._data._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    holo_base_msg_core_float32_t_g_tc._data._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    holo_base_msg_core_float32_t_g_tc._data._sampleAccessInfo =
    holo_base_msg_core_float32_t_get_sample_access_info();
    holo_base_msg_core_float32_t_g_tc._data._typePlugin =
    holo_base_msg_core_float32_t_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_core_float32_t_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_core_float32_t_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_core_float32_t_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_core_float32_t_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_float32_t_g_sampleAccessInfo;
    }

    holo_base_msg_core_float32_t_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_core_float32_t_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_core_float32_t_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_core_float32_t);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_core_float32_t_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_core_float32_t_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_core_float32_t_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_float32_t_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_core_float32_t_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_core_float32_t_g_typePlugin = 
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
        holo_base_msg_core_float32_t_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_core_float32_t_finalize_w_return,
        NULL
    };

    return &holo_base_msg_core_float32_t_g_typePlugin;
}
#endif

RTIBool holo_base_msg_core_float32_t_initialize(
    holo_base_msg_core_float32_t* sample) {
    return holo_base_msg_core_float32_t_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_core_float32_t_initialize_ex(
    holo_base_msg_core_float32_t* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_core_float32_t_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_core_float32_t_initialize_w_params(
    holo_base_msg_core_float32_t* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    (*sample) = 0.0f;

    return RTI_TRUE;
}

RTIBool holo_base_msg_core_float32_t_finalize(
    holo_base_msg_core_float32_t* sample)
{

    holo_base_msg_core_float32_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_float32_t_finalize_w_return(
    holo_base_msg_core_float32_t* sample)
{

    holo_base_msg_core_float32_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_core_float32_t_finalize_ex(
    holo_base_msg_core_float32_t* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_core_float32_t_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_core_float32_t_finalize_w_params(
    holo_base_msg_core_float32_t* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_core_float32_t_finalize_optional_members(
    holo_base_msg_core_float32_t* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_core_float32_t_copy(
    holo_base_msg_core_float32_t* dst,
    const holo_base_msg_core_float32_t* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (dst, src);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_core_float32_t' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_float32_t
#define TSeq holo_base_msg_core_float32_tSeq

#define T_initialize holo_base_msg_core_float32_t_initialize

#define T_finalize   holo_base_msg_core_float32_t_finalize
#define T_copy       holo_base_msg_core_float32_t_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_float32_t
#define TSeq holo_base_msg_core_float32_tSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_core_float64_t *
holo_base_msg_core_float64_t_create(void)
{
    holo_base_msg_core_float64_t* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_core_float64_t);
    if (sample != NULL) {
        if (!holo_base_msg_core_float64_t_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_core_float64_t_delete(holo_base_msg_core_float64_t*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_core_float64_t_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_core_float64_t_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_core_float64_t_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_core_float64_t_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::core::float64_t", /* Name */
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
        }}; /* Type code for  holo_base_msg_core_float64_t */

    if (is_initialized) {
        return &holo_base_msg_core_float64_t_g_tc;
    }

    holo_base_msg_core_float64_t_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_core_float64_t_g_tc._data._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_double;

    /* Initialize the values for member annotations. */
    holo_base_msg_core_float64_t_g_tc._data._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_core_float64_t_g_tc._data._annotations._defaultValue._u.double_value = 0.0;
    holo_base_msg_core_float64_t_g_tc._data._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_core_float64_t_g_tc._data._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
    holo_base_msg_core_float64_t_g_tc._data._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
    holo_base_msg_core_float64_t_g_tc._data._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;

    holo_base_msg_core_float64_t_g_tc._data._sampleAccessInfo =
    holo_base_msg_core_float64_t_get_sample_access_info();
    holo_base_msg_core_float64_t_g_tc._data._typePlugin =
    holo_base_msg_core_float64_t_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_core_float64_t_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_core_float64_t_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_core_float64_t_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_core_float64_t_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_float64_t_g_sampleAccessInfo;
    }

    holo_base_msg_core_float64_t_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_core_float64_t_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_core_float64_t_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_core_float64_t);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_core_float64_t_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_core_float64_t_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_core_float64_t_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_float64_t_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_core_float64_t_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_core_float64_t_g_typePlugin = 
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
        holo_base_msg_core_float64_t_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_core_float64_t_finalize_w_return,
        NULL
    };

    return &holo_base_msg_core_float64_t_g_typePlugin;
}
#endif

RTIBool holo_base_msg_core_float64_t_initialize(
    holo_base_msg_core_float64_t* sample) {
    return holo_base_msg_core_float64_t_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_core_float64_t_initialize_ex(
    holo_base_msg_core_float64_t* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_core_float64_t_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_core_float64_t_initialize_w_params(
    holo_base_msg_core_float64_t* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    (*sample) = 0.0;

    return RTI_TRUE;
}

RTIBool holo_base_msg_core_float64_t_finalize(
    holo_base_msg_core_float64_t* sample)
{

    holo_base_msg_core_float64_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_float64_t_finalize_w_return(
    holo_base_msg_core_float64_t* sample)
{

    holo_base_msg_core_float64_t_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_core_float64_t_finalize_ex(
    holo_base_msg_core_float64_t* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_core_float64_t_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_core_float64_t_finalize_w_params(
    holo_base_msg_core_float64_t* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void holo_base_msg_core_float64_t_finalize_optional_members(
    holo_base_msg_core_float64_t* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_core_float64_t_copy(
    holo_base_msg_core_float64_t* dst,
    const holo_base_msg_core_float64_t* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    DDS_Primitive_copy (dst, src);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'holo_base_msg_core_float64_t' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_float64_t
#define TSeq holo_base_msg_core_float64_tSeq

#define T_initialize holo_base_msg_core_float64_t_initialize

#define T_finalize   holo_base_msg_core_float64_t_finalize
#define T_copy       holo_base_msg_core_float64_t_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_float64_t
#define TSeq holo_base_msg_core_float64_tSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_core_BoolSequence *
holo_base_msg_core_BoolSequence_create(void)
{
    holo_base_msg_core_BoolSequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_core_BoolSequence);
    if (sample != NULL) {
        if (!holo_base_msg_core_BoolSequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_core_BoolSequence_delete(holo_base_msg_core_BoolSequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_core_BoolSequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_core_BoolSequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_core_BoolSequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_core_BoolSequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_core_BoolSequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::core::BoolSequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_core_BoolSequence */

    if (is_initialized) {
        return &holo_base_msg_core_BoolSequence_g_tc;
    }

    holo_base_msg_core_BoolSequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_core_BoolSequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_boolean;
    holo_base_msg_core_BoolSequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_core_BoolSequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_core_BoolSequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_core_BoolSequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_core_BoolSequence_get_sample_access_info();
    holo_base_msg_core_BoolSequence_g_tc._data._typePlugin =
    holo_base_msg_core_BoolSequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_core_BoolSequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_core_BoolSequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_core_BoolSequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_core_BoolSequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_BoolSequence_g_sampleAccessInfo;
    }

    holo_base_msg_core_BoolSequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_core_BoolSequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_core_BoolSequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_core_BoolSequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_core_BoolSequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_core_BoolSequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_core_BoolSequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_BoolSequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_core_BoolSequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_core_BoolSequence_g_typePlugin = 
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
        holo_base_msg_core_BoolSequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_core_BoolSequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_core_BoolSequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_core_BoolSequence_initialize(
    holo_base_msg_core_BoolSequence* sample) {
    return holo_base_msg_core_BoolSequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_core_BoolSequence_initialize_ex(
    holo_base_msg_core_BoolSequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_core_BoolSequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_core_BoolSequence_initialize_w_params(
    holo_base_msg_core_BoolSequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!DDS_BooleanSeq_initialize(sample  )){
            return RTI_FALSE;
        }
        if (!DDS_BooleanSeq_set_maximum(sample , (100) )) {
            return RTI_FALSE;
        }
    } else { 
        if(!DDS_BooleanSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_BoolSequence_finalize(
    holo_base_msg_core_BoolSequence* sample)
{

    holo_base_msg_core_BoolSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_BoolSequence_finalize_w_return(
    holo_base_msg_core_BoolSequence* sample)
{

    holo_base_msg_core_BoolSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_core_BoolSequence_finalize_ex(
    holo_base_msg_core_BoolSequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_core_BoolSequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_core_BoolSequence_finalize_w_params(
    holo_base_msg_core_BoolSequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!DDS_BooleanSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_core_BoolSequence_finalize_optional_members(
    holo_base_msg_core_BoolSequence* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_core_BoolSequence_copy(
    holo_base_msg_core_BoolSequence* dst,
    const holo_base_msg_core_BoolSequence* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!DDS_BooleanSeq_copy(dst ,
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
* Configure and implement 'holo_base_msg_core_BoolSequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_BoolSequence
#define TSeq holo_base_msg_core_BoolSequenceSeq

#define T_initialize holo_base_msg_core_BoolSequence_initialize

#define T_finalize   holo_base_msg_core_BoolSequence_finalize
#define T_copy       holo_base_msg_core_BoolSequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_BoolSequence
#define TSeq holo_base_msg_core_BoolSequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_core_CharSequence *
holo_base_msg_core_CharSequence_create(void)
{
    holo_base_msg_core_CharSequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_core_CharSequence);
    if (sample != NULL) {
        if (!holo_base_msg_core_CharSequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_core_CharSequence_delete(holo_base_msg_core_CharSequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_core_CharSequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_core_CharSequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_core_CharSequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_core_CharSequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_core_CharSequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::core::CharSequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_core_CharSequence */

    if (is_initialized) {
        return &holo_base_msg_core_CharSequence_g_tc;
    }

    holo_base_msg_core_CharSequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_core_CharSequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_char;
    holo_base_msg_core_CharSequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_core_CharSequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_core_CharSequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_core_CharSequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_core_CharSequence_get_sample_access_info();
    holo_base_msg_core_CharSequence_g_tc._data._typePlugin =
    holo_base_msg_core_CharSequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_core_CharSequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_core_CharSequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_core_CharSequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_core_CharSequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_CharSequence_g_sampleAccessInfo;
    }

    holo_base_msg_core_CharSequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_core_CharSequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_core_CharSequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_core_CharSequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_core_CharSequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_core_CharSequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_core_CharSequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_CharSequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_core_CharSequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_core_CharSequence_g_typePlugin = 
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
        holo_base_msg_core_CharSequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_core_CharSequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_core_CharSequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_core_CharSequence_initialize(
    holo_base_msg_core_CharSequence* sample) {
    return holo_base_msg_core_CharSequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_core_CharSequence_initialize_ex(
    holo_base_msg_core_CharSequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_core_CharSequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_core_CharSequence_initialize_w_params(
    holo_base_msg_core_CharSequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!DDS_CharSeq_initialize(sample  )){
            return RTI_FALSE;
        }
        if (!DDS_CharSeq_set_maximum(sample , (100) )) {
            return RTI_FALSE;
        }
    } else { 
        if(!DDS_CharSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_CharSequence_finalize(
    holo_base_msg_core_CharSequence* sample)
{

    holo_base_msg_core_CharSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_CharSequence_finalize_w_return(
    holo_base_msg_core_CharSequence* sample)
{

    holo_base_msg_core_CharSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_core_CharSequence_finalize_ex(
    holo_base_msg_core_CharSequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_core_CharSequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_core_CharSequence_finalize_w_params(
    holo_base_msg_core_CharSequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!DDS_CharSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_core_CharSequence_finalize_optional_members(
    holo_base_msg_core_CharSequence* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_core_CharSequence_copy(
    holo_base_msg_core_CharSequence* dst,
    const holo_base_msg_core_CharSequence* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!DDS_CharSeq_copy(dst ,
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
* Configure and implement 'holo_base_msg_core_CharSequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_CharSequence
#define TSeq holo_base_msg_core_CharSequenceSeq

#define T_initialize holo_base_msg_core_CharSequence_initialize

#define T_finalize   holo_base_msg_core_CharSequence_finalize
#define T_copy       holo_base_msg_core_CharSequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_CharSequence
#define TSeq holo_base_msg_core_CharSequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_core_WcharSequence *
holo_base_msg_core_WcharSequence_create(void)
{
    holo_base_msg_core_WcharSequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_core_WcharSequence);
    if (sample != NULL) {
        if (!holo_base_msg_core_WcharSequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_core_WcharSequence_delete(holo_base_msg_core_WcharSequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_core_WcharSequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_core_WcharSequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_core_WcharSequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_core_WcharSequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_core_WcharSequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::core::WcharSequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_core_WcharSequence */

    if (is_initialized) {
        return &holo_base_msg_core_WcharSequence_g_tc;
    }

    holo_base_msg_core_WcharSequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_core_WcharSequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_wchar;
    holo_base_msg_core_WcharSequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_core_WcharSequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_core_WcharSequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_core_WcharSequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_core_WcharSequence_get_sample_access_info();
    holo_base_msg_core_WcharSequence_g_tc._data._typePlugin =
    holo_base_msg_core_WcharSequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_core_WcharSequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_core_WcharSequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_core_WcharSequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_core_WcharSequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_WcharSequence_g_sampleAccessInfo;
    }

    holo_base_msg_core_WcharSequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_core_WcharSequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_core_WcharSequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_core_WcharSequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_core_WcharSequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_core_WcharSequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_core_WcharSequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_WcharSequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_core_WcharSequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_core_WcharSequence_g_typePlugin = 
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
        holo_base_msg_core_WcharSequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_core_WcharSequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_core_WcharSequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_core_WcharSequence_initialize(
    holo_base_msg_core_WcharSequence* sample) {
    return holo_base_msg_core_WcharSequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_core_WcharSequence_initialize_ex(
    holo_base_msg_core_WcharSequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_core_WcharSequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_core_WcharSequence_initialize_w_params(
    holo_base_msg_core_WcharSequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!DDS_WcharSeq_initialize(sample  )){
            return RTI_FALSE;
        }
        if (!DDS_WcharSeq_set_maximum(sample , (100) )) {
            return RTI_FALSE;
        }
    } else { 
        if(!DDS_WcharSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_WcharSequence_finalize(
    holo_base_msg_core_WcharSequence* sample)
{

    holo_base_msg_core_WcharSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_WcharSequence_finalize_w_return(
    holo_base_msg_core_WcharSequence* sample)
{

    holo_base_msg_core_WcharSequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_core_WcharSequence_finalize_ex(
    holo_base_msg_core_WcharSequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_core_WcharSequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_core_WcharSequence_finalize_w_params(
    holo_base_msg_core_WcharSequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!DDS_WcharSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_core_WcharSequence_finalize_optional_members(
    holo_base_msg_core_WcharSequence* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_core_WcharSequence_copy(
    holo_base_msg_core_WcharSequence* dst,
    const holo_base_msg_core_WcharSequence* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!DDS_WcharSeq_copy(dst ,
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
* Configure and implement 'holo_base_msg_core_WcharSequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_WcharSequence
#define TSeq holo_base_msg_core_WcharSequenceSeq

#define T_initialize holo_base_msg_core_WcharSequence_initialize

#define T_finalize   holo_base_msg_core_WcharSequence_finalize
#define T_copy       holo_base_msg_core_WcharSequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_WcharSequence
#define TSeq holo_base_msg_core_WcharSequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_core_Int8Sequence *
holo_base_msg_core_Int8Sequence_create(void)
{
    holo_base_msg_core_Int8Sequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_core_Int8Sequence);
    if (sample != NULL) {
        if (!holo_base_msg_core_Int8Sequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_core_Int8Sequence_delete(holo_base_msg_core_Int8Sequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_core_Int8Sequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_core_Int8Sequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_core_Int8Sequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_core_Int8Sequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_core_Int8Sequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::core::Int8Sequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_core_Int8Sequence */

    if (is_initialized) {
        return &holo_base_msg_core_Int8Sequence_g_tc;
    }

    holo_base_msg_core_Int8Sequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_core_Int8Sequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_char;
    holo_base_msg_core_Int8Sequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_core_Int8Sequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_core_Int8Sequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_core_Int8Sequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_core_Int8Sequence_get_sample_access_info();
    holo_base_msg_core_Int8Sequence_g_tc._data._typePlugin =
    holo_base_msg_core_Int8Sequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_core_Int8Sequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_core_Int8Sequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_core_Int8Sequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_core_Int8Sequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_Int8Sequence_g_sampleAccessInfo;
    }

    holo_base_msg_core_Int8Sequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_core_Int8Sequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_core_Int8Sequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_core_Int8Sequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_core_Int8Sequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_core_Int8Sequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_core_Int8Sequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_Int8Sequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_core_Int8Sequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_core_Int8Sequence_g_typePlugin = 
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
        holo_base_msg_core_Int8Sequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_core_Int8Sequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_core_Int8Sequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_core_Int8Sequence_initialize(
    holo_base_msg_core_Int8Sequence* sample) {
    return holo_base_msg_core_Int8Sequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_core_Int8Sequence_initialize_ex(
    holo_base_msg_core_Int8Sequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_core_Int8Sequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_core_Int8Sequence_initialize_w_params(
    holo_base_msg_core_Int8Sequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!DDS_CharSeq_initialize(sample  )){
            return RTI_FALSE;
        }
        if (!DDS_CharSeq_set_maximum(sample , (100) )) {
            return RTI_FALSE;
        }
    } else { 
        if(!DDS_CharSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_Int8Sequence_finalize(
    holo_base_msg_core_Int8Sequence* sample)
{

    holo_base_msg_core_Int8Sequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_Int8Sequence_finalize_w_return(
    holo_base_msg_core_Int8Sequence* sample)
{

    holo_base_msg_core_Int8Sequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_core_Int8Sequence_finalize_ex(
    holo_base_msg_core_Int8Sequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_core_Int8Sequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_core_Int8Sequence_finalize_w_params(
    holo_base_msg_core_Int8Sequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!DDS_CharSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_core_Int8Sequence_finalize_optional_members(
    holo_base_msg_core_Int8Sequence* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_core_Int8Sequence_copy(
    holo_base_msg_core_Int8Sequence* dst,
    const holo_base_msg_core_Int8Sequence* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!DDS_CharSeq_copy(dst ,
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
* Configure and implement 'holo_base_msg_core_Int8Sequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Int8Sequence
#define TSeq holo_base_msg_core_Int8SequenceSeq

#define T_initialize holo_base_msg_core_Int8Sequence_initialize

#define T_finalize   holo_base_msg_core_Int8Sequence_finalize
#define T_copy       holo_base_msg_core_Int8Sequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Int8Sequence
#define TSeq holo_base_msg_core_Int8SequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_core_Uint8Sequence *
holo_base_msg_core_Uint8Sequence_create(void)
{
    holo_base_msg_core_Uint8Sequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_core_Uint8Sequence);
    if (sample != NULL) {
        if (!holo_base_msg_core_Uint8Sequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_core_Uint8Sequence_delete(holo_base_msg_core_Uint8Sequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_core_Uint8Sequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_core_Uint8Sequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_core_Uint8Sequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_core_Uint8Sequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_core_Uint8Sequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::core::Uint8Sequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_core_Uint8Sequence */

    if (is_initialized) {
        return &holo_base_msg_core_Uint8Sequence_g_tc;
    }

    holo_base_msg_core_Uint8Sequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_core_Uint8Sequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_octet;
    holo_base_msg_core_Uint8Sequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_core_Uint8Sequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_core_Uint8Sequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_core_Uint8Sequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_core_Uint8Sequence_get_sample_access_info();
    holo_base_msg_core_Uint8Sequence_g_tc._data._typePlugin =
    holo_base_msg_core_Uint8Sequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_core_Uint8Sequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_core_Uint8Sequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_core_Uint8Sequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_core_Uint8Sequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_Uint8Sequence_g_sampleAccessInfo;
    }

    holo_base_msg_core_Uint8Sequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_core_Uint8Sequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_core_Uint8Sequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_core_Uint8Sequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_core_Uint8Sequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_core_Uint8Sequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_core_Uint8Sequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_Uint8Sequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_core_Uint8Sequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_core_Uint8Sequence_g_typePlugin = 
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
        holo_base_msg_core_Uint8Sequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_core_Uint8Sequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_core_Uint8Sequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_core_Uint8Sequence_initialize(
    holo_base_msg_core_Uint8Sequence* sample) {
    return holo_base_msg_core_Uint8Sequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_core_Uint8Sequence_initialize_ex(
    holo_base_msg_core_Uint8Sequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_core_Uint8Sequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_core_Uint8Sequence_initialize_w_params(
    holo_base_msg_core_Uint8Sequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

RTIBool holo_base_msg_core_Uint8Sequence_finalize(
    holo_base_msg_core_Uint8Sequence* sample)
{

    holo_base_msg_core_Uint8Sequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_Uint8Sequence_finalize_w_return(
    holo_base_msg_core_Uint8Sequence* sample)
{

    holo_base_msg_core_Uint8Sequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_core_Uint8Sequence_finalize_ex(
    holo_base_msg_core_Uint8Sequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_core_Uint8Sequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_core_Uint8Sequence_finalize_w_params(
    holo_base_msg_core_Uint8Sequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
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

void holo_base_msg_core_Uint8Sequence_finalize_optional_members(
    holo_base_msg_core_Uint8Sequence* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_core_Uint8Sequence_copy(
    holo_base_msg_core_Uint8Sequence* dst,
    const holo_base_msg_core_Uint8Sequence* src)
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
* Configure and implement 'holo_base_msg_core_Uint8Sequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Uint8Sequence
#define TSeq holo_base_msg_core_Uint8SequenceSeq

#define T_initialize holo_base_msg_core_Uint8Sequence_initialize

#define T_finalize   holo_base_msg_core_Uint8Sequence_finalize
#define T_copy       holo_base_msg_core_Uint8Sequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Uint8Sequence
#define TSeq holo_base_msg_core_Uint8SequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_core_Int16Sequence *
holo_base_msg_core_Int16Sequence_create(void)
{
    holo_base_msg_core_Int16Sequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_core_Int16Sequence);
    if (sample != NULL) {
        if (!holo_base_msg_core_Int16Sequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_core_Int16Sequence_delete(holo_base_msg_core_Int16Sequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_core_Int16Sequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_core_Int16Sequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_core_Int16Sequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_core_Int16Sequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_core_Int16Sequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::core::Int16Sequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_core_Int16Sequence */

    if (is_initialized) {
        return &holo_base_msg_core_Int16Sequence_g_tc;
    }

    holo_base_msg_core_Int16Sequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_core_Int16Sequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_short;
    holo_base_msg_core_Int16Sequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_core_Int16Sequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_core_Int16Sequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_core_Int16Sequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_core_Int16Sequence_get_sample_access_info();
    holo_base_msg_core_Int16Sequence_g_tc._data._typePlugin =
    holo_base_msg_core_Int16Sequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_core_Int16Sequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_core_Int16Sequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_core_Int16Sequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_core_Int16Sequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_Int16Sequence_g_sampleAccessInfo;
    }

    holo_base_msg_core_Int16Sequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_core_Int16Sequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_core_Int16Sequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_core_Int16Sequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_core_Int16Sequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_core_Int16Sequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_core_Int16Sequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_Int16Sequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_core_Int16Sequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_core_Int16Sequence_g_typePlugin = 
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
        holo_base_msg_core_Int16Sequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_core_Int16Sequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_core_Int16Sequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_core_Int16Sequence_initialize(
    holo_base_msg_core_Int16Sequence* sample) {
    return holo_base_msg_core_Int16Sequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_core_Int16Sequence_initialize_ex(
    holo_base_msg_core_Int16Sequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_core_Int16Sequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_core_Int16Sequence_initialize_w_params(
    holo_base_msg_core_Int16Sequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!DDS_ShortSeq_initialize(sample  )){
            return RTI_FALSE;
        }
        if (!DDS_ShortSeq_set_maximum(sample , (100) )) {
            return RTI_FALSE;
        }
    } else { 
        if(!DDS_ShortSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_Int16Sequence_finalize(
    holo_base_msg_core_Int16Sequence* sample)
{

    holo_base_msg_core_Int16Sequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_Int16Sequence_finalize_w_return(
    holo_base_msg_core_Int16Sequence* sample)
{

    holo_base_msg_core_Int16Sequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_core_Int16Sequence_finalize_ex(
    holo_base_msg_core_Int16Sequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_core_Int16Sequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_core_Int16Sequence_finalize_w_params(
    holo_base_msg_core_Int16Sequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!DDS_ShortSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_core_Int16Sequence_finalize_optional_members(
    holo_base_msg_core_Int16Sequence* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_core_Int16Sequence_copy(
    holo_base_msg_core_Int16Sequence* dst,
    const holo_base_msg_core_Int16Sequence* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!DDS_ShortSeq_copy(dst ,
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
* Configure and implement 'holo_base_msg_core_Int16Sequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Int16Sequence
#define TSeq holo_base_msg_core_Int16SequenceSeq

#define T_initialize holo_base_msg_core_Int16Sequence_initialize

#define T_finalize   holo_base_msg_core_Int16Sequence_finalize
#define T_copy       holo_base_msg_core_Int16Sequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Int16Sequence
#define TSeq holo_base_msg_core_Int16SequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_core_Uint16Sequence *
holo_base_msg_core_Uint16Sequence_create(void)
{
    holo_base_msg_core_Uint16Sequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_core_Uint16Sequence);
    if (sample != NULL) {
        if (!holo_base_msg_core_Uint16Sequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_core_Uint16Sequence_delete(holo_base_msg_core_Uint16Sequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_core_Uint16Sequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_core_Uint16Sequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_core_Uint16Sequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_core_Uint16Sequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_core_Uint16Sequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::core::Uint16Sequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_core_Uint16Sequence */

    if (is_initialized) {
        return &holo_base_msg_core_Uint16Sequence_g_tc;
    }

    holo_base_msg_core_Uint16Sequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_core_Uint16Sequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ushort;
    holo_base_msg_core_Uint16Sequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_core_Uint16Sequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_core_Uint16Sequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_core_Uint16Sequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_core_Uint16Sequence_get_sample_access_info();
    holo_base_msg_core_Uint16Sequence_g_tc._data._typePlugin =
    holo_base_msg_core_Uint16Sequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_core_Uint16Sequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_core_Uint16Sequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_core_Uint16Sequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_core_Uint16Sequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_Uint16Sequence_g_sampleAccessInfo;
    }

    holo_base_msg_core_Uint16Sequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_core_Uint16Sequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_core_Uint16Sequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_core_Uint16Sequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_core_Uint16Sequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_core_Uint16Sequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_core_Uint16Sequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_Uint16Sequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_core_Uint16Sequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_core_Uint16Sequence_g_typePlugin = 
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
        holo_base_msg_core_Uint16Sequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_core_Uint16Sequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_core_Uint16Sequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_core_Uint16Sequence_initialize(
    holo_base_msg_core_Uint16Sequence* sample) {
    return holo_base_msg_core_Uint16Sequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_core_Uint16Sequence_initialize_ex(
    holo_base_msg_core_Uint16Sequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_core_Uint16Sequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_core_Uint16Sequence_initialize_w_params(
    holo_base_msg_core_Uint16Sequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!DDS_UnsignedShortSeq_initialize(sample  )){
            return RTI_FALSE;
        }
        if (!DDS_UnsignedShortSeq_set_maximum(sample , (100) )) {
            return RTI_FALSE;
        }
    } else { 
        if(!DDS_UnsignedShortSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_Uint16Sequence_finalize(
    holo_base_msg_core_Uint16Sequence* sample)
{

    holo_base_msg_core_Uint16Sequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_Uint16Sequence_finalize_w_return(
    holo_base_msg_core_Uint16Sequence* sample)
{

    holo_base_msg_core_Uint16Sequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_core_Uint16Sequence_finalize_ex(
    holo_base_msg_core_Uint16Sequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_core_Uint16Sequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_core_Uint16Sequence_finalize_w_params(
    holo_base_msg_core_Uint16Sequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!DDS_UnsignedShortSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_core_Uint16Sequence_finalize_optional_members(
    holo_base_msg_core_Uint16Sequence* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_core_Uint16Sequence_copy(
    holo_base_msg_core_Uint16Sequence* dst,
    const holo_base_msg_core_Uint16Sequence* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!DDS_UnsignedShortSeq_copy(dst ,
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
* Configure and implement 'holo_base_msg_core_Uint16Sequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Uint16Sequence
#define TSeq holo_base_msg_core_Uint16SequenceSeq

#define T_initialize holo_base_msg_core_Uint16Sequence_initialize

#define T_finalize   holo_base_msg_core_Uint16Sequence_finalize
#define T_copy       holo_base_msg_core_Uint16Sequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Uint16Sequence
#define TSeq holo_base_msg_core_Uint16SequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_core_Int32Sequence *
holo_base_msg_core_Int32Sequence_create(void)
{
    holo_base_msg_core_Int32Sequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_core_Int32Sequence);
    if (sample != NULL) {
        if (!holo_base_msg_core_Int32Sequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_core_Int32Sequence_delete(holo_base_msg_core_Int32Sequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_core_Int32Sequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_core_Int32Sequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_core_Int32Sequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_core_Int32Sequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_core_Int32Sequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::core::Int32Sequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_core_Int32Sequence */

    if (is_initialized) {
        return &holo_base_msg_core_Int32Sequence_g_tc;
    }

    holo_base_msg_core_Int32Sequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_core_Int32Sequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    holo_base_msg_core_Int32Sequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_core_Int32Sequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_core_Int32Sequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_core_Int32Sequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_core_Int32Sequence_get_sample_access_info();
    holo_base_msg_core_Int32Sequence_g_tc._data._typePlugin =
    holo_base_msg_core_Int32Sequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_core_Int32Sequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_core_Int32Sequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_core_Int32Sequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_core_Int32Sequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_Int32Sequence_g_sampleAccessInfo;
    }

    holo_base_msg_core_Int32Sequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_core_Int32Sequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_core_Int32Sequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_core_Int32Sequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_core_Int32Sequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_core_Int32Sequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_core_Int32Sequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_Int32Sequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_core_Int32Sequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_core_Int32Sequence_g_typePlugin = 
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
        holo_base_msg_core_Int32Sequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_core_Int32Sequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_core_Int32Sequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_core_Int32Sequence_initialize(
    holo_base_msg_core_Int32Sequence* sample) {
    return holo_base_msg_core_Int32Sequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_core_Int32Sequence_initialize_ex(
    holo_base_msg_core_Int32Sequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_core_Int32Sequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_core_Int32Sequence_initialize_w_params(
    holo_base_msg_core_Int32Sequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!DDS_LongSeq_initialize(sample  )){
            return RTI_FALSE;
        }
        if (!DDS_LongSeq_set_maximum(sample , (100) )) {
            return RTI_FALSE;
        }
    } else { 
        if(!DDS_LongSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_Int32Sequence_finalize(
    holo_base_msg_core_Int32Sequence* sample)
{

    holo_base_msg_core_Int32Sequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_Int32Sequence_finalize_w_return(
    holo_base_msg_core_Int32Sequence* sample)
{

    holo_base_msg_core_Int32Sequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_core_Int32Sequence_finalize_ex(
    holo_base_msg_core_Int32Sequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_core_Int32Sequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_core_Int32Sequence_finalize_w_params(
    holo_base_msg_core_Int32Sequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!DDS_LongSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_core_Int32Sequence_finalize_optional_members(
    holo_base_msg_core_Int32Sequence* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_core_Int32Sequence_copy(
    holo_base_msg_core_Int32Sequence* dst,
    const holo_base_msg_core_Int32Sequence* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!DDS_LongSeq_copy(dst ,
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
* Configure and implement 'holo_base_msg_core_Int32Sequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Int32Sequence
#define TSeq holo_base_msg_core_Int32SequenceSeq

#define T_initialize holo_base_msg_core_Int32Sequence_initialize

#define T_finalize   holo_base_msg_core_Int32Sequence_finalize
#define T_copy       holo_base_msg_core_Int32Sequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Int32Sequence
#define TSeq holo_base_msg_core_Int32SequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_core_Uint32Sequence *
holo_base_msg_core_Uint32Sequence_create(void)
{
    holo_base_msg_core_Uint32Sequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_core_Uint32Sequence);
    if (sample != NULL) {
        if (!holo_base_msg_core_Uint32Sequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_core_Uint32Sequence_delete(holo_base_msg_core_Uint32Sequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_core_Uint32Sequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_core_Uint32Sequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_core_Uint32Sequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_core_Uint32Sequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_core_Uint32Sequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::core::Uint32Sequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_core_Uint32Sequence */

    if (is_initialized) {
        return &holo_base_msg_core_Uint32Sequence_g_tc;
    }

    holo_base_msg_core_Uint32Sequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_core_Uint32Sequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ulong;
    holo_base_msg_core_Uint32Sequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_core_Uint32Sequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_core_Uint32Sequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_core_Uint32Sequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_core_Uint32Sequence_get_sample_access_info();
    holo_base_msg_core_Uint32Sequence_g_tc._data._typePlugin =
    holo_base_msg_core_Uint32Sequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_core_Uint32Sequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_core_Uint32Sequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_core_Uint32Sequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_core_Uint32Sequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_Uint32Sequence_g_sampleAccessInfo;
    }

    holo_base_msg_core_Uint32Sequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_core_Uint32Sequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_core_Uint32Sequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_core_Uint32Sequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_core_Uint32Sequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_core_Uint32Sequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_core_Uint32Sequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_Uint32Sequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_core_Uint32Sequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_core_Uint32Sequence_g_typePlugin = 
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
        holo_base_msg_core_Uint32Sequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_core_Uint32Sequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_core_Uint32Sequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_core_Uint32Sequence_initialize(
    holo_base_msg_core_Uint32Sequence* sample) {
    return holo_base_msg_core_Uint32Sequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_core_Uint32Sequence_initialize_ex(
    holo_base_msg_core_Uint32Sequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_core_Uint32Sequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_core_Uint32Sequence_initialize_w_params(
    holo_base_msg_core_Uint32Sequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!DDS_UnsignedLongSeq_initialize(sample  )){
            return RTI_FALSE;
        }
        if (!DDS_UnsignedLongSeq_set_maximum(sample , (100) )) {
            return RTI_FALSE;
        }
    } else { 
        if(!DDS_UnsignedLongSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_Uint32Sequence_finalize(
    holo_base_msg_core_Uint32Sequence* sample)
{

    holo_base_msg_core_Uint32Sequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_Uint32Sequence_finalize_w_return(
    holo_base_msg_core_Uint32Sequence* sample)
{

    holo_base_msg_core_Uint32Sequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_core_Uint32Sequence_finalize_ex(
    holo_base_msg_core_Uint32Sequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_core_Uint32Sequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_core_Uint32Sequence_finalize_w_params(
    holo_base_msg_core_Uint32Sequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!DDS_UnsignedLongSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_core_Uint32Sequence_finalize_optional_members(
    holo_base_msg_core_Uint32Sequence* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_core_Uint32Sequence_copy(
    holo_base_msg_core_Uint32Sequence* dst,
    const holo_base_msg_core_Uint32Sequence* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!DDS_UnsignedLongSeq_copy(dst ,
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
* Configure and implement 'holo_base_msg_core_Uint32Sequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Uint32Sequence
#define TSeq holo_base_msg_core_Uint32SequenceSeq

#define T_initialize holo_base_msg_core_Uint32Sequence_initialize

#define T_finalize   holo_base_msg_core_Uint32Sequence_finalize
#define T_copy       holo_base_msg_core_Uint32Sequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Uint32Sequence
#define TSeq holo_base_msg_core_Uint32SequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_core_Int64Sequence *
holo_base_msg_core_Int64Sequence_create(void)
{
    holo_base_msg_core_Int64Sequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_core_Int64Sequence);
    if (sample != NULL) {
        if (!holo_base_msg_core_Int64Sequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_core_Int64Sequence_delete(holo_base_msg_core_Int64Sequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_core_Int64Sequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_core_Int64Sequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_core_Int64Sequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_core_Int64Sequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_core_Int64Sequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::core::Int64Sequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_core_Int64Sequence */

    if (is_initialized) {
        return &holo_base_msg_core_Int64Sequence_g_tc;
    }

    holo_base_msg_core_Int64Sequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_core_Int64Sequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_longlong;
    holo_base_msg_core_Int64Sequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_core_Int64Sequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_core_Int64Sequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_core_Int64Sequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_core_Int64Sequence_get_sample_access_info();
    holo_base_msg_core_Int64Sequence_g_tc._data._typePlugin =
    holo_base_msg_core_Int64Sequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_core_Int64Sequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_core_Int64Sequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_core_Int64Sequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_core_Int64Sequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_Int64Sequence_g_sampleAccessInfo;
    }

    holo_base_msg_core_Int64Sequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_core_Int64Sequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_core_Int64Sequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_core_Int64Sequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_core_Int64Sequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_core_Int64Sequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_core_Int64Sequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_Int64Sequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_core_Int64Sequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_core_Int64Sequence_g_typePlugin = 
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
        holo_base_msg_core_Int64Sequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_core_Int64Sequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_core_Int64Sequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_core_Int64Sequence_initialize(
    holo_base_msg_core_Int64Sequence* sample) {
    return holo_base_msg_core_Int64Sequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_core_Int64Sequence_initialize_ex(
    holo_base_msg_core_Int64Sequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_core_Int64Sequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_core_Int64Sequence_initialize_w_params(
    holo_base_msg_core_Int64Sequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!DDS_LongLongSeq_initialize(sample  )){
            return RTI_FALSE;
        }
        if (!DDS_LongLongSeq_set_maximum(sample , (100) )) {
            return RTI_FALSE;
        }
    } else { 
        if(!DDS_LongLongSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_Int64Sequence_finalize(
    holo_base_msg_core_Int64Sequence* sample)
{

    holo_base_msg_core_Int64Sequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_Int64Sequence_finalize_w_return(
    holo_base_msg_core_Int64Sequence* sample)
{

    holo_base_msg_core_Int64Sequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_core_Int64Sequence_finalize_ex(
    holo_base_msg_core_Int64Sequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_core_Int64Sequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_core_Int64Sequence_finalize_w_params(
    holo_base_msg_core_Int64Sequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!DDS_LongLongSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_core_Int64Sequence_finalize_optional_members(
    holo_base_msg_core_Int64Sequence* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_core_Int64Sequence_copy(
    holo_base_msg_core_Int64Sequence* dst,
    const holo_base_msg_core_Int64Sequence* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!DDS_LongLongSeq_copy(dst ,
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
* Configure and implement 'holo_base_msg_core_Int64Sequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Int64Sequence
#define TSeq holo_base_msg_core_Int64SequenceSeq

#define T_initialize holo_base_msg_core_Int64Sequence_initialize

#define T_finalize   holo_base_msg_core_Int64Sequence_finalize
#define T_copy       holo_base_msg_core_Int64Sequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Int64Sequence
#define TSeq holo_base_msg_core_Int64SequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_core_Uint64Sequence *
holo_base_msg_core_Uint64Sequence_create(void)
{
    holo_base_msg_core_Uint64Sequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_core_Uint64Sequence);
    if (sample != NULL) {
        if (!holo_base_msg_core_Uint64Sequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_core_Uint64Sequence_delete(holo_base_msg_core_Uint64Sequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_core_Uint64Sequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_core_Uint64Sequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_core_Uint64Sequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_core_Uint64Sequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_core_Uint64Sequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::core::Uint64Sequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_core_Uint64Sequence */

    if (is_initialized) {
        return &holo_base_msg_core_Uint64Sequence_g_tc;
    }

    holo_base_msg_core_Uint64Sequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_core_Uint64Sequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ulonglong;
    holo_base_msg_core_Uint64Sequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_core_Uint64Sequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_core_Uint64Sequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_core_Uint64Sequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_core_Uint64Sequence_get_sample_access_info();
    holo_base_msg_core_Uint64Sequence_g_tc._data._typePlugin =
    holo_base_msg_core_Uint64Sequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_core_Uint64Sequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_core_Uint64Sequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_core_Uint64Sequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_core_Uint64Sequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_Uint64Sequence_g_sampleAccessInfo;
    }

    holo_base_msg_core_Uint64Sequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_core_Uint64Sequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_core_Uint64Sequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_core_Uint64Sequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_core_Uint64Sequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_core_Uint64Sequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_core_Uint64Sequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_Uint64Sequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_core_Uint64Sequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_core_Uint64Sequence_g_typePlugin = 
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
        holo_base_msg_core_Uint64Sequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_core_Uint64Sequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_core_Uint64Sequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_core_Uint64Sequence_initialize(
    holo_base_msg_core_Uint64Sequence* sample) {
    return holo_base_msg_core_Uint64Sequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_core_Uint64Sequence_initialize_ex(
    holo_base_msg_core_Uint64Sequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_core_Uint64Sequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_core_Uint64Sequence_initialize_w_params(
    holo_base_msg_core_Uint64Sequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
        if(!DDS_UnsignedLongLongSeq_initialize(sample  )){
            return RTI_FALSE;
        }
        if (!DDS_UnsignedLongLongSeq_set_maximum(sample , (100) )) {
            return RTI_FALSE;
        }
    } else { 
        if(!DDS_UnsignedLongLongSeq_set_length(sample, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_Uint64Sequence_finalize(
    holo_base_msg_core_Uint64Sequence* sample)
{

    holo_base_msg_core_Uint64Sequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_Uint64Sequence_finalize_w_return(
    holo_base_msg_core_Uint64Sequence* sample)
{

    holo_base_msg_core_Uint64Sequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_core_Uint64Sequence_finalize_ex(
    holo_base_msg_core_Uint64Sequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_core_Uint64Sequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_core_Uint64Sequence_finalize_w_params(
    holo_base_msg_core_Uint64Sequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if(!DDS_UnsignedLongLongSeq_finalize(sample)){
        return;
    }

}

void holo_base_msg_core_Uint64Sequence_finalize_optional_members(
    holo_base_msg_core_Uint64Sequence* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_core_Uint64Sequence_copy(
    holo_base_msg_core_Uint64Sequence* dst,
    const holo_base_msg_core_Uint64Sequence* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!DDS_UnsignedLongLongSeq_copy(dst ,
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
* Configure and implement 'holo_base_msg_core_Uint64Sequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Uint64Sequence
#define TSeq holo_base_msg_core_Uint64SequenceSeq

#define T_initialize holo_base_msg_core_Uint64Sequence_initialize

#define T_finalize   holo_base_msg_core_Uint64Sequence_finalize
#define T_copy       holo_base_msg_core_Uint64Sequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Uint64Sequence
#define TSeq holo_base_msg_core_Uint64SequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_core_Float32Sequence *
holo_base_msg_core_Float32Sequence_create(void)
{
    holo_base_msg_core_Float32Sequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_core_Float32Sequence);
    if (sample != NULL) {
        if (!holo_base_msg_core_Float32Sequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_core_Float32Sequence_delete(holo_base_msg_core_Float32Sequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_core_Float32Sequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_core_Float32Sequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_core_Float32Sequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_core_Float32Sequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_core_Float32Sequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::core::Float32Sequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_core_Float32Sequence */

    if (is_initialized) {
        return &holo_base_msg_core_Float32Sequence_g_tc;
    }

    holo_base_msg_core_Float32Sequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_core_Float32Sequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_float;
    holo_base_msg_core_Float32Sequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_core_Float32Sequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_core_Float32Sequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_core_Float32Sequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_core_Float32Sequence_get_sample_access_info();
    holo_base_msg_core_Float32Sequence_g_tc._data._typePlugin =
    holo_base_msg_core_Float32Sequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_core_Float32Sequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_core_Float32Sequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_core_Float32Sequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_core_Float32Sequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_Float32Sequence_g_sampleAccessInfo;
    }

    holo_base_msg_core_Float32Sequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_core_Float32Sequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_core_Float32Sequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_core_Float32Sequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_core_Float32Sequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_core_Float32Sequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_core_Float32Sequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_Float32Sequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_core_Float32Sequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_core_Float32Sequence_g_typePlugin = 
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
        holo_base_msg_core_Float32Sequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_core_Float32Sequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_core_Float32Sequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_core_Float32Sequence_initialize(
    holo_base_msg_core_Float32Sequence* sample) {
    return holo_base_msg_core_Float32Sequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_core_Float32Sequence_initialize_ex(
    holo_base_msg_core_Float32Sequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_core_Float32Sequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_core_Float32Sequence_initialize_w_params(
    holo_base_msg_core_Float32Sequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

RTIBool holo_base_msg_core_Float32Sequence_finalize(
    holo_base_msg_core_Float32Sequence* sample)
{

    holo_base_msg_core_Float32Sequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_Float32Sequence_finalize_w_return(
    holo_base_msg_core_Float32Sequence* sample)
{

    holo_base_msg_core_Float32Sequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_core_Float32Sequence_finalize_ex(
    holo_base_msg_core_Float32Sequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_core_Float32Sequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_core_Float32Sequence_finalize_w_params(
    holo_base_msg_core_Float32Sequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
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

void holo_base_msg_core_Float32Sequence_finalize_optional_members(
    holo_base_msg_core_Float32Sequence* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_core_Float32Sequence_copy(
    holo_base_msg_core_Float32Sequence* dst,
    const holo_base_msg_core_Float32Sequence* src)
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
* Configure and implement 'holo_base_msg_core_Float32Sequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Float32Sequence
#define TSeq holo_base_msg_core_Float32SequenceSeq

#define T_initialize holo_base_msg_core_Float32Sequence_initialize

#define T_finalize   holo_base_msg_core_Float32Sequence_finalize
#define T_copy       holo_base_msg_core_Float32Sequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Float32Sequence
#define TSeq holo_base_msg_core_Float32SequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

holo_base_msg_core_Float64Sequence *
holo_base_msg_core_Float64Sequence_create(void)
{
    holo_base_msg_core_Float64Sequence* sample;
    OSAPI_Heap_allocate_struct(&sample, holo_base_msg_core_Float64Sequence);
    if (sample != NULL) {
        if (!holo_base_msg_core_Float64Sequence_initialize(sample)) {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
void
holo_base_msg_core_Float64Sequence_delete(holo_base_msg_core_Float64Sequence*sample)
{
    if (sample != NULL) {
        /* holo_base_msg_core_Float64Sequence_finalize() always 
        returns RTI_TRUE when called with sample != NULL */
        holo_base_msg_core_Float64Sequence_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}

/* ========================================================================= */

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* holo_base_msg_core_Float64Sequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode holo_base_msg_core_Float64Sequence_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

    static DDS_TypeCode holo_base_msg_core_Float64Sequence_g_tc =
    {{
            DDS_TK_ALIAS, /* Kind*/
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Ignored */
            (char *)"holo_base_msg::core::Float64Sequence", /* Name */
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
        }}; /* Type code for  holo_base_msg_core_Float64Sequence */

    if (is_initialized) {
        return &holo_base_msg_core_Float64Sequence_g_tc;
    }

    holo_base_msg_core_Float64Sequence_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    holo_base_msg_core_Float64Sequence_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;
    holo_base_msg_core_Float64Sequence_g_tc_sequence._data._sampleAccessInfo = &DDS_g_sai_seq;
    holo_base_msg_core_Float64Sequence_g_tc._data._typeCode =  (RTICdrTypeCode *)& holo_base_msg_core_Float64Sequence_g_tc_sequence;

    /* Initialize the values for member annotations. */

    holo_base_msg_core_Float64Sequence_g_tc._data._sampleAccessInfo =
    holo_base_msg_core_Float64Sequence_get_sample_access_info();
    holo_base_msg_core_Float64Sequence_g_tc._data._typePlugin =
    holo_base_msg_core_Float64Sequence_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &holo_base_msg_core_Float64Sequence_g_tc;
}

RTIXCdrSampleAccessInfo *holo_base_msg_core_Float64Sequence_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo holo_base_msg_core_Float64Sequence_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo holo_base_msg_core_Float64Sequence_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_Float64Sequence_g_sampleAccessInfo;
    }

    holo_base_msg_core_Float64Sequence_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

    holo_base_msg_core_Float64Sequence_g_sampleAccessInfo.memberAccessInfos = 
    holo_base_msg_core_Float64Sequence_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(holo_base_msg_core_Float64Sequence);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            holo_base_msg_core_Float64Sequence_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            holo_base_msg_core_Float64Sequence_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    holo_base_msg_core_Float64Sequence_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &holo_base_msg_core_Float64Sequence_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *holo_base_msg_core_Float64Sequence_get_type_plugin_info()
{
    static RTIXCdrTypePlugin holo_base_msg_core_Float64Sequence_g_typePlugin = 
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
        holo_base_msg_core_Float64Sequence_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        holo_base_msg_core_Float64Sequence_finalize_w_return,
        NULL
    };

    return &holo_base_msg_core_Float64Sequence_g_typePlugin;
}
#endif

RTIBool holo_base_msg_core_Float64Sequence_initialize(
    holo_base_msg_core_Float64Sequence* sample) {
    return holo_base_msg_core_Float64Sequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool holo_base_msg_core_Float64Sequence_initialize_ex(
    holo_base_msg_core_Float64Sequence* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return holo_base_msg_core_Float64Sequence_initialize_w_params(
        sample,&allocParams);

}

RTIBool holo_base_msg_core_Float64Sequence_initialize_w_params(
    holo_base_msg_core_Float64Sequence* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

RTIBool holo_base_msg_core_Float64Sequence_finalize(
    holo_base_msg_core_Float64Sequence* sample)
{

    holo_base_msg_core_Float64Sequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

RTIBool holo_base_msg_core_Float64Sequence_finalize_w_return(
    holo_base_msg_core_Float64Sequence* sample)
{

    holo_base_msg_core_Float64Sequence_finalize_ex(sample,RTI_TRUE);
    return RTI_TRUE;
}

void holo_base_msg_core_Float64Sequence_finalize_ex(
    holo_base_msg_core_Float64Sequence* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    holo_base_msg_core_Float64Sequence_finalize_w_params(
        sample,&deallocParams);
}

void holo_base_msg_core_Float64Sequence_finalize_w_params(
    holo_base_msg_core_Float64Sequence* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
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

void holo_base_msg_core_Float64Sequence_finalize_optional_members(
    holo_base_msg_core_Float64Sequence* sample, RTIBool deletePointers)
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

RTIBool holo_base_msg_core_Float64Sequence_copy(
    holo_base_msg_core_Float64Sequence* dst,
    const holo_base_msg_core_Float64Sequence* src)
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
* Configure and implement 'holo_base_msg_core_Float64Sequence' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Float64Sequence
#define TSeq holo_base_msg_core_Float64SequenceSeq

#define T_initialize holo_base_msg_core_Float64Sequence_initialize

#define T_finalize   holo_base_msg_core_Float64Sequence_finalize
#define T_copy       holo_base_msg_core_Float64Sequence_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Float64Sequence
#define TSeq holo_base_msg_core_Float64SequenceSeq
#include "dds_cpp/dds_cpp_sequence_defn.hxx"

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

