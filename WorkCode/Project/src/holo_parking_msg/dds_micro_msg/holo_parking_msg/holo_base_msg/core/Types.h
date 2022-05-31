/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Types.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef Types_1755247134_h
#define Types_1755247134_h

#ifndef rti_me_cpp_hxx
#include "rti_me_cpp.hxx"
#endif

#include "dds_c/dds_c_typecode.h"

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

typedef    DDS_Boolean   holo_base_msg_core_bool_t ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_core_bool_t_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *holo_base_msg_core_bool_t_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *holo_base_msg_core_bool_t_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_bool_t
#define TSeq holo_base_msg_core_bool_tSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_bool_t
#define TSeq holo_base_msg_core_bool_tSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_core_bool_t*
holo_base_msg_core_bool_t_create();

NDDSUSERDllExport extern void
holo_base_msg_core_bool_t_delete(holo_base_msg_core_bool_t* sample);

NDDSUSERDllExport
RTIBool holo_base_msg_core_bool_t_initialize(
    holo_base_msg_core_bool_t* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_bool_t_initialize_ex(
    holo_base_msg_core_bool_t* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool holo_base_msg_core_bool_t_initialize_w_params(
    holo_base_msg_core_bool_t* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_bool_t_finalize(
    holo_base_msg_core_bool_t* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_bool_t_finalize_w_return(
    holo_base_msg_core_bool_t* self);

NDDSUSERDllExport
void holo_base_msg_core_bool_t_finalize_ex(
    holo_base_msg_core_bool_t* self,RTIBool deletePointers);

NDDSUSERDllExport
void holo_base_msg_core_bool_t_finalize_w_params(
    holo_base_msg_core_bool_t* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void holo_base_msg_core_bool_t_finalize_optional_members(
    holo_base_msg_core_bool_t* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_bool_t_copy(
    holo_base_msg_core_bool_t* dst,
    const holo_base_msg_core_bool_t* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef    DDS_Char   holo_base_msg_core_char_t ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_core_char_t_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *holo_base_msg_core_char_t_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *holo_base_msg_core_char_t_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_char_t
#define TSeq holo_base_msg_core_char_tSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_char_t
#define TSeq holo_base_msg_core_char_tSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_core_char_t*
holo_base_msg_core_char_t_create();

NDDSUSERDllExport extern void
holo_base_msg_core_char_t_delete(holo_base_msg_core_char_t* sample);

NDDSUSERDllExport
RTIBool holo_base_msg_core_char_t_initialize(
    holo_base_msg_core_char_t* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_char_t_initialize_ex(
    holo_base_msg_core_char_t* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool holo_base_msg_core_char_t_initialize_w_params(
    holo_base_msg_core_char_t* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_char_t_finalize(
    holo_base_msg_core_char_t* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_char_t_finalize_w_return(
    holo_base_msg_core_char_t* self);

NDDSUSERDllExport
void holo_base_msg_core_char_t_finalize_ex(
    holo_base_msg_core_char_t* self,RTIBool deletePointers);

NDDSUSERDllExport
void holo_base_msg_core_char_t_finalize_w_params(
    holo_base_msg_core_char_t* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void holo_base_msg_core_char_t_finalize_optional_members(
    holo_base_msg_core_char_t* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_char_t_copy(
    holo_base_msg_core_char_t* dst,
    const holo_base_msg_core_char_t* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef    DDS_Wchar   holo_base_msg_core__cxx_wchar_t ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_core__cxx_wchar_t_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *holo_base_msg_core__cxx_wchar_t_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *holo_base_msg_core__cxx_wchar_t_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core__cxx_wchar_t
#define TSeq holo_base_msg_core__cxx_wchar_tSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core__cxx_wchar_t
#define TSeq holo_base_msg_core__cxx_wchar_tSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_core__cxx_wchar_t*
holo_base_msg_core__cxx_wchar_t_create();

NDDSUSERDllExport extern void
holo_base_msg_core__cxx_wchar_t_delete(holo_base_msg_core__cxx_wchar_t* sample);

NDDSUSERDllExport
RTIBool holo_base_msg_core__cxx_wchar_t_initialize(
    holo_base_msg_core__cxx_wchar_t* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core__cxx_wchar_t_initialize_ex(
    holo_base_msg_core__cxx_wchar_t* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool holo_base_msg_core__cxx_wchar_t_initialize_w_params(
    holo_base_msg_core__cxx_wchar_t* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool holo_base_msg_core__cxx_wchar_t_finalize(
    holo_base_msg_core__cxx_wchar_t* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core__cxx_wchar_t_finalize_w_return(
    holo_base_msg_core__cxx_wchar_t* self);

NDDSUSERDllExport
void holo_base_msg_core__cxx_wchar_t_finalize_ex(
    holo_base_msg_core__cxx_wchar_t* self,RTIBool deletePointers);

NDDSUSERDllExport
void holo_base_msg_core__cxx_wchar_t_finalize_w_params(
    holo_base_msg_core__cxx_wchar_t* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void holo_base_msg_core__cxx_wchar_t_finalize_optional_members(
    holo_base_msg_core__cxx_wchar_t* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool holo_base_msg_core__cxx_wchar_t_copy(
    holo_base_msg_core__cxx_wchar_t* dst,
    const holo_base_msg_core__cxx_wchar_t* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef    DDS_Char   holo_base_msg_core_int8_t ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_core_int8_t_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *holo_base_msg_core_int8_t_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *holo_base_msg_core_int8_t_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_int8_t
#define TSeq holo_base_msg_core_int8_tSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_int8_t
#define TSeq holo_base_msg_core_int8_tSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_core_int8_t*
holo_base_msg_core_int8_t_create();

NDDSUSERDllExport extern void
holo_base_msg_core_int8_t_delete(holo_base_msg_core_int8_t* sample);

NDDSUSERDllExport
RTIBool holo_base_msg_core_int8_t_initialize(
    holo_base_msg_core_int8_t* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_int8_t_initialize_ex(
    holo_base_msg_core_int8_t* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool holo_base_msg_core_int8_t_initialize_w_params(
    holo_base_msg_core_int8_t* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_int8_t_finalize(
    holo_base_msg_core_int8_t* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_int8_t_finalize_w_return(
    holo_base_msg_core_int8_t* self);

NDDSUSERDllExport
void holo_base_msg_core_int8_t_finalize_ex(
    holo_base_msg_core_int8_t* self,RTIBool deletePointers);

NDDSUSERDllExport
void holo_base_msg_core_int8_t_finalize_w_params(
    holo_base_msg_core_int8_t* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void holo_base_msg_core_int8_t_finalize_optional_members(
    holo_base_msg_core_int8_t* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_int8_t_copy(
    holo_base_msg_core_int8_t* dst,
    const holo_base_msg_core_int8_t* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef    DDS_Octet   holo_base_msg_core_uint8_t ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_core_uint8_t_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *holo_base_msg_core_uint8_t_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *holo_base_msg_core_uint8_t_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_uint8_t
#define TSeq holo_base_msg_core_uint8_tSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_uint8_t
#define TSeq holo_base_msg_core_uint8_tSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_core_uint8_t*
holo_base_msg_core_uint8_t_create();

NDDSUSERDllExport extern void
holo_base_msg_core_uint8_t_delete(holo_base_msg_core_uint8_t* sample);

NDDSUSERDllExport
RTIBool holo_base_msg_core_uint8_t_initialize(
    holo_base_msg_core_uint8_t* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_uint8_t_initialize_ex(
    holo_base_msg_core_uint8_t* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool holo_base_msg_core_uint8_t_initialize_w_params(
    holo_base_msg_core_uint8_t* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_uint8_t_finalize(
    holo_base_msg_core_uint8_t* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_uint8_t_finalize_w_return(
    holo_base_msg_core_uint8_t* self);

NDDSUSERDllExport
void holo_base_msg_core_uint8_t_finalize_ex(
    holo_base_msg_core_uint8_t* self,RTIBool deletePointers);

NDDSUSERDllExport
void holo_base_msg_core_uint8_t_finalize_w_params(
    holo_base_msg_core_uint8_t* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void holo_base_msg_core_uint8_t_finalize_optional_members(
    holo_base_msg_core_uint8_t* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_uint8_t_copy(
    holo_base_msg_core_uint8_t* dst,
    const holo_base_msg_core_uint8_t* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef    DDS_Short   holo_base_msg_core_int16_t ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_core_int16_t_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *holo_base_msg_core_int16_t_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *holo_base_msg_core_int16_t_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_int16_t
#define TSeq holo_base_msg_core_int16_tSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_int16_t
#define TSeq holo_base_msg_core_int16_tSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_core_int16_t*
holo_base_msg_core_int16_t_create();

NDDSUSERDllExport extern void
holo_base_msg_core_int16_t_delete(holo_base_msg_core_int16_t* sample);

NDDSUSERDllExport
RTIBool holo_base_msg_core_int16_t_initialize(
    holo_base_msg_core_int16_t* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_int16_t_initialize_ex(
    holo_base_msg_core_int16_t* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool holo_base_msg_core_int16_t_initialize_w_params(
    holo_base_msg_core_int16_t* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_int16_t_finalize(
    holo_base_msg_core_int16_t* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_int16_t_finalize_w_return(
    holo_base_msg_core_int16_t* self);

NDDSUSERDllExport
void holo_base_msg_core_int16_t_finalize_ex(
    holo_base_msg_core_int16_t* self,RTIBool deletePointers);

NDDSUSERDllExport
void holo_base_msg_core_int16_t_finalize_w_params(
    holo_base_msg_core_int16_t* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void holo_base_msg_core_int16_t_finalize_optional_members(
    holo_base_msg_core_int16_t* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_int16_t_copy(
    holo_base_msg_core_int16_t* dst,
    const holo_base_msg_core_int16_t* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef    DDS_UnsignedShort   holo_base_msg_core_uint16_t ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_core_uint16_t_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *holo_base_msg_core_uint16_t_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *holo_base_msg_core_uint16_t_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_uint16_t
#define TSeq holo_base_msg_core_uint16_tSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_uint16_t
#define TSeq holo_base_msg_core_uint16_tSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_core_uint16_t*
holo_base_msg_core_uint16_t_create();

NDDSUSERDllExport extern void
holo_base_msg_core_uint16_t_delete(holo_base_msg_core_uint16_t* sample);

NDDSUSERDllExport
RTIBool holo_base_msg_core_uint16_t_initialize(
    holo_base_msg_core_uint16_t* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_uint16_t_initialize_ex(
    holo_base_msg_core_uint16_t* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool holo_base_msg_core_uint16_t_initialize_w_params(
    holo_base_msg_core_uint16_t* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_uint16_t_finalize(
    holo_base_msg_core_uint16_t* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_uint16_t_finalize_w_return(
    holo_base_msg_core_uint16_t* self);

NDDSUSERDllExport
void holo_base_msg_core_uint16_t_finalize_ex(
    holo_base_msg_core_uint16_t* self,RTIBool deletePointers);

NDDSUSERDllExport
void holo_base_msg_core_uint16_t_finalize_w_params(
    holo_base_msg_core_uint16_t* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void holo_base_msg_core_uint16_t_finalize_optional_members(
    holo_base_msg_core_uint16_t* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_uint16_t_copy(
    holo_base_msg_core_uint16_t* dst,
    const holo_base_msg_core_uint16_t* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef    DDS_Long   holo_base_msg_core_int32_t ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_core_int32_t_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *holo_base_msg_core_int32_t_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *holo_base_msg_core_int32_t_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_int32_t
#define TSeq holo_base_msg_core_int32_tSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_int32_t
#define TSeq holo_base_msg_core_int32_tSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_core_int32_t*
holo_base_msg_core_int32_t_create();

NDDSUSERDllExport extern void
holo_base_msg_core_int32_t_delete(holo_base_msg_core_int32_t* sample);

NDDSUSERDllExport
RTIBool holo_base_msg_core_int32_t_initialize(
    holo_base_msg_core_int32_t* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_int32_t_initialize_ex(
    holo_base_msg_core_int32_t* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool holo_base_msg_core_int32_t_initialize_w_params(
    holo_base_msg_core_int32_t* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_int32_t_finalize(
    holo_base_msg_core_int32_t* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_int32_t_finalize_w_return(
    holo_base_msg_core_int32_t* self);

NDDSUSERDllExport
void holo_base_msg_core_int32_t_finalize_ex(
    holo_base_msg_core_int32_t* self,RTIBool deletePointers);

NDDSUSERDllExport
void holo_base_msg_core_int32_t_finalize_w_params(
    holo_base_msg_core_int32_t* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void holo_base_msg_core_int32_t_finalize_optional_members(
    holo_base_msg_core_int32_t* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_int32_t_copy(
    holo_base_msg_core_int32_t* dst,
    const holo_base_msg_core_int32_t* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef    DDS_UnsignedLong   holo_base_msg_core_uint32_t ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_core_uint32_t_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *holo_base_msg_core_uint32_t_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *holo_base_msg_core_uint32_t_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_uint32_t
#define TSeq holo_base_msg_core_uint32_tSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_uint32_t
#define TSeq holo_base_msg_core_uint32_tSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_core_uint32_t*
holo_base_msg_core_uint32_t_create();

NDDSUSERDllExport extern void
holo_base_msg_core_uint32_t_delete(holo_base_msg_core_uint32_t* sample);

NDDSUSERDllExport
RTIBool holo_base_msg_core_uint32_t_initialize(
    holo_base_msg_core_uint32_t* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_uint32_t_initialize_ex(
    holo_base_msg_core_uint32_t* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool holo_base_msg_core_uint32_t_initialize_w_params(
    holo_base_msg_core_uint32_t* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_uint32_t_finalize(
    holo_base_msg_core_uint32_t* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_uint32_t_finalize_w_return(
    holo_base_msg_core_uint32_t* self);

NDDSUSERDllExport
void holo_base_msg_core_uint32_t_finalize_ex(
    holo_base_msg_core_uint32_t* self,RTIBool deletePointers);

NDDSUSERDllExport
void holo_base_msg_core_uint32_t_finalize_w_params(
    holo_base_msg_core_uint32_t* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void holo_base_msg_core_uint32_t_finalize_optional_members(
    holo_base_msg_core_uint32_t* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_uint32_t_copy(
    holo_base_msg_core_uint32_t* dst,
    const holo_base_msg_core_uint32_t* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef    DDS_LongLong   holo_base_msg_core_int64_t ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_core_int64_t_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *holo_base_msg_core_int64_t_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *holo_base_msg_core_int64_t_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_int64_t
#define TSeq holo_base_msg_core_int64_tSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_int64_t
#define TSeq holo_base_msg_core_int64_tSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_core_int64_t*
holo_base_msg_core_int64_t_create();

NDDSUSERDllExport extern void
holo_base_msg_core_int64_t_delete(holo_base_msg_core_int64_t* sample);

NDDSUSERDllExport
RTIBool holo_base_msg_core_int64_t_initialize(
    holo_base_msg_core_int64_t* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_int64_t_initialize_ex(
    holo_base_msg_core_int64_t* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool holo_base_msg_core_int64_t_initialize_w_params(
    holo_base_msg_core_int64_t* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_int64_t_finalize(
    holo_base_msg_core_int64_t* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_int64_t_finalize_w_return(
    holo_base_msg_core_int64_t* self);

NDDSUSERDllExport
void holo_base_msg_core_int64_t_finalize_ex(
    holo_base_msg_core_int64_t* self,RTIBool deletePointers);

NDDSUSERDllExport
void holo_base_msg_core_int64_t_finalize_w_params(
    holo_base_msg_core_int64_t* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void holo_base_msg_core_int64_t_finalize_optional_members(
    holo_base_msg_core_int64_t* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_int64_t_copy(
    holo_base_msg_core_int64_t* dst,
    const holo_base_msg_core_int64_t* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef    DDS_UnsignedLongLong   holo_base_msg_core_uint64_t ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_core_uint64_t_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *holo_base_msg_core_uint64_t_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *holo_base_msg_core_uint64_t_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_uint64_t
#define TSeq holo_base_msg_core_uint64_tSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_uint64_t
#define TSeq holo_base_msg_core_uint64_tSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_core_uint64_t*
holo_base_msg_core_uint64_t_create();

NDDSUSERDllExport extern void
holo_base_msg_core_uint64_t_delete(holo_base_msg_core_uint64_t* sample);

NDDSUSERDllExport
RTIBool holo_base_msg_core_uint64_t_initialize(
    holo_base_msg_core_uint64_t* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_uint64_t_initialize_ex(
    holo_base_msg_core_uint64_t* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool holo_base_msg_core_uint64_t_initialize_w_params(
    holo_base_msg_core_uint64_t* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_uint64_t_finalize(
    holo_base_msg_core_uint64_t* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_uint64_t_finalize_w_return(
    holo_base_msg_core_uint64_t* self);

NDDSUSERDllExport
void holo_base_msg_core_uint64_t_finalize_ex(
    holo_base_msg_core_uint64_t* self,RTIBool deletePointers);

NDDSUSERDllExport
void holo_base_msg_core_uint64_t_finalize_w_params(
    holo_base_msg_core_uint64_t* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void holo_base_msg_core_uint64_t_finalize_optional_members(
    holo_base_msg_core_uint64_t* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_uint64_t_copy(
    holo_base_msg_core_uint64_t* dst,
    const holo_base_msg_core_uint64_t* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef    DDS_Float   holo_base_msg_core_float32_t ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_core_float32_t_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *holo_base_msg_core_float32_t_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *holo_base_msg_core_float32_t_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_float32_t
#define TSeq holo_base_msg_core_float32_tSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_float32_t
#define TSeq holo_base_msg_core_float32_tSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_core_float32_t*
holo_base_msg_core_float32_t_create();

NDDSUSERDllExport extern void
holo_base_msg_core_float32_t_delete(holo_base_msg_core_float32_t* sample);

NDDSUSERDllExport
RTIBool holo_base_msg_core_float32_t_initialize(
    holo_base_msg_core_float32_t* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_float32_t_initialize_ex(
    holo_base_msg_core_float32_t* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool holo_base_msg_core_float32_t_initialize_w_params(
    holo_base_msg_core_float32_t* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_float32_t_finalize(
    holo_base_msg_core_float32_t* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_float32_t_finalize_w_return(
    holo_base_msg_core_float32_t* self);

NDDSUSERDllExport
void holo_base_msg_core_float32_t_finalize_ex(
    holo_base_msg_core_float32_t* self,RTIBool deletePointers);

NDDSUSERDllExport
void holo_base_msg_core_float32_t_finalize_w_params(
    holo_base_msg_core_float32_t* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void holo_base_msg_core_float32_t_finalize_optional_members(
    holo_base_msg_core_float32_t* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_float32_t_copy(
    holo_base_msg_core_float32_t* dst,
    const holo_base_msg_core_float32_t* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef    DDS_Double   holo_base_msg_core_float64_t ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_core_float64_t_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *holo_base_msg_core_float64_t_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *holo_base_msg_core_float64_t_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_float64_t
#define TSeq holo_base_msg_core_float64_tSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_float64_t
#define TSeq holo_base_msg_core_float64_tSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_core_float64_t*
holo_base_msg_core_float64_t_create();

NDDSUSERDllExport extern void
holo_base_msg_core_float64_t_delete(holo_base_msg_core_float64_t* sample);

NDDSUSERDllExport
RTIBool holo_base_msg_core_float64_t_initialize(
    holo_base_msg_core_float64_t* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_float64_t_initialize_ex(
    holo_base_msg_core_float64_t* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool holo_base_msg_core_float64_t_initialize_w_params(
    holo_base_msg_core_float64_t* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_float64_t_finalize(
    holo_base_msg_core_float64_t* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_float64_t_finalize_w_return(
    holo_base_msg_core_float64_t* self);

NDDSUSERDllExport
void holo_base_msg_core_float64_t_finalize_ex(
    holo_base_msg_core_float64_t* self,RTIBool deletePointers);

NDDSUSERDllExport
void holo_base_msg_core_float64_t_finalize_w_params(
    holo_base_msg_core_float64_t* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void holo_base_msg_core_float64_t_finalize_optional_members(
    holo_base_msg_core_float64_t* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_float64_t_copy(
    holo_base_msg_core_float64_t* dst,
    const holo_base_msg_core_float64_t* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef     DDS_BooleanSeq  holo_base_msg_core_BoolSequence ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_core_BoolSequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *holo_base_msg_core_BoolSequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *holo_base_msg_core_BoolSequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_BoolSequence
#define TSeq holo_base_msg_core_BoolSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_BoolSequence
#define TSeq holo_base_msg_core_BoolSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_core_BoolSequence*
holo_base_msg_core_BoolSequence_create();

NDDSUSERDllExport extern void
holo_base_msg_core_BoolSequence_delete(holo_base_msg_core_BoolSequence* sample);

NDDSUSERDllExport
RTIBool holo_base_msg_core_BoolSequence_initialize(
    holo_base_msg_core_BoolSequence* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_BoolSequence_initialize_ex(
    holo_base_msg_core_BoolSequence* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool holo_base_msg_core_BoolSequence_initialize_w_params(
    holo_base_msg_core_BoolSequence* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_BoolSequence_finalize(
    holo_base_msg_core_BoolSequence* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_BoolSequence_finalize_w_return(
    holo_base_msg_core_BoolSequence* self);

NDDSUSERDllExport
void holo_base_msg_core_BoolSequence_finalize_ex(
    holo_base_msg_core_BoolSequence* self,RTIBool deletePointers);

NDDSUSERDllExport
void holo_base_msg_core_BoolSequence_finalize_w_params(
    holo_base_msg_core_BoolSequence* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void holo_base_msg_core_BoolSequence_finalize_optional_members(
    holo_base_msg_core_BoolSequence* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_BoolSequence_copy(
    holo_base_msg_core_BoolSequence* dst,
    const holo_base_msg_core_BoolSequence* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef     DDS_CharSeq  holo_base_msg_core_CharSequence ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_core_CharSequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *holo_base_msg_core_CharSequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *holo_base_msg_core_CharSequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_CharSequence
#define TSeq holo_base_msg_core_CharSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_CharSequence
#define TSeq holo_base_msg_core_CharSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_core_CharSequence*
holo_base_msg_core_CharSequence_create();

NDDSUSERDllExport extern void
holo_base_msg_core_CharSequence_delete(holo_base_msg_core_CharSequence* sample);

NDDSUSERDllExport
RTIBool holo_base_msg_core_CharSequence_initialize(
    holo_base_msg_core_CharSequence* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_CharSequence_initialize_ex(
    holo_base_msg_core_CharSequence* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool holo_base_msg_core_CharSequence_initialize_w_params(
    holo_base_msg_core_CharSequence* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_CharSequence_finalize(
    holo_base_msg_core_CharSequence* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_CharSequence_finalize_w_return(
    holo_base_msg_core_CharSequence* self);

NDDSUSERDllExport
void holo_base_msg_core_CharSequence_finalize_ex(
    holo_base_msg_core_CharSequence* self,RTIBool deletePointers);

NDDSUSERDllExport
void holo_base_msg_core_CharSequence_finalize_w_params(
    holo_base_msg_core_CharSequence* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void holo_base_msg_core_CharSequence_finalize_optional_members(
    holo_base_msg_core_CharSequence* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_CharSequence_copy(
    holo_base_msg_core_CharSequence* dst,
    const holo_base_msg_core_CharSequence* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef     DDS_WcharSeq  holo_base_msg_core_WcharSequence ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_core_WcharSequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *holo_base_msg_core_WcharSequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *holo_base_msg_core_WcharSequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_WcharSequence
#define TSeq holo_base_msg_core_WcharSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_WcharSequence
#define TSeq holo_base_msg_core_WcharSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_core_WcharSequence*
holo_base_msg_core_WcharSequence_create();

NDDSUSERDllExport extern void
holo_base_msg_core_WcharSequence_delete(holo_base_msg_core_WcharSequence* sample);

NDDSUSERDllExport
RTIBool holo_base_msg_core_WcharSequence_initialize(
    holo_base_msg_core_WcharSequence* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_WcharSequence_initialize_ex(
    holo_base_msg_core_WcharSequence* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool holo_base_msg_core_WcharSequence_initialize_w_params(
    holo_base_msg_core_WcharSequence* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_WcharSequence_finalize(
    holo_base_msg_core_WcharSequence* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_WcharSequence_finalize_w_return(
    holo_base_msg_core_WcharSequence* self);

NDDSUSERDllExport
void holo_base_msg_core_WcharSequence_finalize_ex(
    holo_base_msg_core_WcharSequence* self,RTIBool deletePointers);

NDDSUSERDllExport
void holo_base_msg_core_WcharSequence_finalize_w_params(
    holo_base_msg_core_WcharSequence* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void holo_base_msg_core_WcharSequence_finalize_optional_members(
    holo_base_msg_core_WcharSequence* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_WcharSequence_copy(
    holo_base_msg_core_WcharSequence* dst,
    const holo_base_msg_core_WcharSequence* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef     DDS_CharSeq  holo_base_msg_core_Int8Sequence ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_core_Int8Sequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *holo_base_msg_core_Int8Sequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *holo_base_msg_core_Int8Sequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Int8Sequence
#define TSeq holo_base_msg_core_Int8SequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Int8Sequence
#define TSeq holo_base_msg_core_Int8SequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_core_Int8Sequence*
holo_base_msg_core_Int8Sequence_create();

NDDSUSERDllExport extern void
holo_base_msg_core_Int8Sequence_delete(holo_base_msg_core_Int8Sequence* sample);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Int8Sequence_initialize(
    holo_base_msg_core_Int8Sequence* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Int8Sequence_initialize_ex(
    holo_base_msg_core_Int8Sequence* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Int8Sequence_initialize_w_params(
    holo_base_msg_core_Int8Sequence* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_Int8Sequence_finalize(
    holo_base_msg_core_Int8Sequence* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Int8Sequence_finalize_w_return(
    holo_base_msg_core_Int8Sequence* self);

NDDSUSERDllExport
void holo_base_msg_core_Int8Sequence_finalize_ex(
    holo_base_msg_core_Int8Sequence* self,RTIBool deletePointers);

NDDSUSERDllExport
void holo_base_msg_core_Int8Sequence_finalize_w_params(
    holo_base_msg_core_Int8Sequence* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void holo_base_msg_core_Int8Sequence_finalize_optional_members(
    holo_base_msg_core_Int8Sequence* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_Int8Sequence_copy(
    holo_base_msg_core_Int8Sequence* dst,
    const holo_base_msg_core_Int8Sequence* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef     DDS_OctetSeq  holo_base_msg_core_Uint8Sequence ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_core_Uint8Sequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *holo_base_msg_core_Uint8Sequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *holo_base_msg_core_Uint8Sequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Uint8Sequence
#define TSeq holo_base_msg_core_Uint8SequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Uint8Sequence
#define TSeq holo_base_msg_core_Uint8SequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_core_Uint8Sequence*
holo_base_msg_core_Uint8Sequence_create();

NDDSUSERDllExport extern void
holo_base_msg_core_Uint8Sequence_delete(holo_base_msg_core_Uint8Sequence* sample);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Uint8Sequence_initialize(
    holo_base_msg_core_Uint8Sequence* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Uint8Sequence_initialize_ex(
    holo_base_msg_core_Uint8Sequence* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Uint8Sequence_initialize_w_params(
    holo_base_msg_core_Uint8Sequence* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_Uint8Sequence_finalize(
    holo_base_msg_core_Uint8Sequence* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Uint8Sequence_finalize_w_return(
    holo_base_msg_core_Uint8Sequence* self);

NDDSUSERDllExport
void holo_base_msg_core_Uint8Sequence_finalize_ex(
    holo_base_msg_core_Uint8Sequence* self,RTIBool deletePointers);

NDDSUSERDllExport
void holo_base_msg_core_Uint8Sequence_finalize_w_params(
    holo_base_msg_core_Uint8Sequence* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void holo_base_msg_core_Uint8Sequence_finalize_optional_members(
    holo_base_msg_core_Uint8Sequence* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_Uint8Sequence_copy(
    holo_base_msg_core_Uint8Sequence* dst,
    const holo_base_msg_core_Uint8Sequence* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef     DDS_ShortSeq  holo_base_msg_core_Int16Sequence ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_core_Int16Sequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *holo_base_msg_core_Int16Sequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *holo_base_msg_core_Int16Sequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Int16Sequence
#define TSeq holo_base_msg_core_Int16SequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Int16Sequence
#define TSeq holo_base_msg_core_Int16SequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_core_Int16Sequence*
holo_base_msg_core_Int16Sequence_create();

NDDSUSERDllExport extern void
holo_base_msg_core_Int16Sequence_delete(holo_base_msg_core_Int16Sequence* sample);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Int16Sequence_initialize(
    holo_base_msg_core_Int16Sequence* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Int16Sequence_initialize_ex(
    holo_base_msg_core_Int16Sequence* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Int16Sequence_initialize_w_params(
    holo_base_msg_core_Int16Sequence* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_Int16Sequence_finalize(
    holo_base_msg_core_Int16Sequence* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Int16Sequence_finalize_w_return(
    holo_base_msg_core_Int16Sequence* self);

NDDSUSERDllExport
void holo_base_msg_core_Int16Sequence_finalize_ex(
    holo_base_msg_core_Int16Sequence* self,RTIBool deletePointers);

NDDSUSERDllExport
void holo_base_msg_core_Int16Sequence_finalize_w_params(
    holo_base_msg_core_Int16Sequence* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void holo_base_msg_core_Int16Sequence_finalize_optional_members(
    holo_base_msg_core_Int16Sequence* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_Int16Sequence_copy(
    holo_base_msg_core_Int16Sequence* dst,
    const holo_base_msg_core_Int16Sequence* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef     DDS_UnsignedShortSeq  holo_base_msg_core_Uint16Sequence ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_core_Uint16Sequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *holo_base_msg_core_Uint16Sequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *holo_base_msg_core_Uint16Sequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Uint16Sequence
#define TSeq holo_base_msg_core_Uint16SequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Uint16Sequence
#define TSeq holo_base_msg_core_Uint16SequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_core_Uint16Sequence*
holo_base_msg_core_Uint16Sequence_create();

NDDSUSERDllExport extern void
holo_base_msg_core_Uint16Sequence_delete(holo_base_msg_core_Uint16Sequence* sample);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Uint16Sequence_initialize(
    holo_base_msg_core_Uint16Sequence* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Uint16Sequence_initialize_ex(
    holo_base_msg_core_Uint16Sequence* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Uint16Sequence_initialize_w_params(
    holo_base_msg_core_Uint16Sequence* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_Uint16Sequence_finalize(
    holo_base_msg_core_Uint16Sequence* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Uint16Sequence_finalize_w_return(
    holo_base_msg_core_Uint16Sequence* self);

NDDSUSERDllExport
void holo_base_msg_core_Uint16Sequence_finalize_ex(
    holo_base_msg_core_Uint16Sequence* self,RTIBool deletePointers);

NDDSUSERDllExport
void holo_base_msg_core_Uint16Sequence_finalize_w_params(
    holo_base_msg_core_Uint16Sequence* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void holo_base_msg_core_Uint16Sequence_finalize_optional_members(
    holo_base_msg_core_Uint16Sequence* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_Uint16Sequence_copy(
    holo_base_msg_core_Uint16Sequence* dst,
    const holo_base_msg_core_Uint16Sequence* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef     DDS_LongSeq  holo_base_msg_core_Int32Sequence ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_core_Int32Sequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *holo_base_msg_core_Int32Sequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *holo_base_msg_core_Int32Sequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Int32Sequence
#define TSeq holo_base_msg_core_Int32SequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Int32Sequence
#define TSeq holo_base_msg_core_Int32SequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_core_Int32Sequence*
holo_base_msg_core_Int32Sequence_create();

NDDSUSERDllExport extern void
holo_base_msg_core_Int32Sequence_delete(holo_base_msg_core_Int32Sequence* sample);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Int32Sequence_initialize(
    holo_base_msg_core_Int32Sequence* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Int32Sequence_initialize_ex(
    holo_base_msg_core_Int32Sequence* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Int32Sequence_initialize_w_params(
    holo_base_msg_core_Int32Sequence* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_Int32Sequence_finalize(
    holo_base_msg_core_Int32Sequence* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Int32Sequence_finalize_w_return(
    holo_base_msg_core_Int32Sequence* self);

NDDSUSERDllExport
void holo_base_msg_core_Int32Sequence_finalize_ex(
    holo_base_msg_core_Int32Sequence* self,RTIBool deletePointers);

NDDSUSERDllExport
void holo_base_msg_core_Int32Sequence_finalize_w_params(
    holo_base_msg_core_Int32Sequence* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void holo_base_msg_core_Int32Sequence_finalize_optional_members(
    holo_base_msg_core_Int32Sequence* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_Int32Sequence_copy(
    holo_base_msg_core_Int32Sequence* dst,
    const holo_base_msg_core_Int32Sequence* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef     DDS_UnsignedLongSeq  holo_base_msg_core_Uint32Sequence ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_core_Uint32Sequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *holo_base_msg_core_Uint32Sequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *holo_base_msg_core_Uint32Sequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Uint32Sequence
#define TSeq holo_base_msg_core_Uint32SequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Uint32Sequence
#define TSeq holo_base_msg_core_Uint32SequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_core_Uint32Sequence*
holo_base_msg_core_Uint32Sequence_create();

NDDSUSERDllExport extern void
holo_base_msg_core_Uint32Sequence_delete(holo_base_msg_core_Uint32Sequence* sample);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Uint32Sequence_initialize(
    holo_base_msg_core_Uint32Sequence* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Uint32Sequence_initialize_ex(
    holo_base_msg_core_Uint32Sequence* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Uint32Sequence_initialize_w_params(
    holo_base_msg_core_Uint32Sequence* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_Uint32Sequence_finalize(
    holo_base_msg_core_Uint32Sequence* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Uint32Sequence_finalize_w_return(
    holo_base_msg_core_Uint32Sequence* self);

NDDSUSERDllExport
void holo_base_msg_core_Uint32Sequence_finalize_ex(
    holo_base_msg_core_Uint32Sequence* self,RTIBool deletePointers);

NDDSUSERDllExport
void holo_base_msg_core_Uint32Sequence_finalize_w_params(
    holo_base_msg_core_Uint32Sequence* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void holo_base_msg_core_Uint32Sequence_finalize_optional_members(
    holo_base_msg_core_Uint32Sequence* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_Uint32Sequence_copy(
    holo_base_msg_core_Uint32Sequence* dst,
    const holo_base_msg_core_Uint32Sequence* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef     DDS_LongLongSeq  holo_base_msg_core_Int64Sequence ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_core_Int64Sequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *holo_base_msg_core_Int64Sequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *holo_base_msg_core_Int64Sequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Int64Sequence
#define TSeq holo_base_msg_core_Int64SequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Int64Sequence
#define TSeq holo_base_msg_core_Int64SequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_core_Int64Sequence*
holo_base_msg_core_Int64Sequence_create();

NDDSUSERDllExport extern void
holo_base_msg_core_Int64Sequence_delete(holo_base_msg_core_Int64Sequence* sample);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Int64Sequence_initialize(
    holo_base_msg_core_Int64Sequence* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Int64Sequence_initialize_ex(
    holo_base_msg_core_Int64Sequence* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Int64Sequence_initialize_w_params(
    holo_base_msg_core_Int64Sequence* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_Int64Sequence_finalize(
    holo_base_msg_core_Int64Sequence* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Int64Sequence_finalize_w_return(
    holo_base_msg_core_Int64Sequence* self);

NDDSUSERDllExport
void holo_base_msg_core_Int64Sequence_finalize_ex(
    holo_base_msg_core_Int64Sequence* self,RTIBool deletePointers);

NDDSUSERDllExport
void holo_base_msg_core_Int64Sequence_finalize_w_params(
    holo_base_msg_core_Int64Sequence* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void holo_base_msg_core_Int64Sequence_finalize_optional_members(
    holo_base_msg_core_Int64Sequence* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_Int64Sequence_copy(
    holo_base_msg_core_Int64Sequence* dst,
    const holo_base_msg_core_Int64Sequence* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef     DDS_UnsignedLongLongSeq  holo_base_msg_core_Uint64Sequence ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_core_Uint64Sequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *holo_base_msg_core_Uint64Sequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *holo_base_msg_core_Uint64Sequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Uint64Sequence
#define TSeq holo_base_msg_core_Uint64SequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Uint64Sequence
#define TSeq holo_base_msg_core_Uint64SequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_core_Uint64Sequence*
holo_base_msg_core_Uint64Sequence_create();

NDDSUSERDllExport extern void
holo_base_msg_core_Uint64Sequence_delete(holo_base_msg_core_Uint64Sequence* sample);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Uint64Sequence_initialize(
    holo_base_msg_core_Uint64Sequence* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Uint64Sequence_initialize_ex(
    holo_base_msg_core_Uint64Sequence* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Uint64Sequence_initialize_w_params(
    holo_base_msg_core_Uint64Sequence* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_Uint64Sequence_finalize(
    holo_base_msg_core_Uint64Sequence* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Uint64Sequence_finalize_w_return(
    holo_base_msg_core_Uint64Sequence* self);

NDDSUSERDllExport
void holo_base_msg_core_Uint64Sequence_finalize_ex(
    holo_base_msg_core_Uint64Sequence* self,RTIBool deletePointers);

NDDSUSERDllExport
void holo_base_msg_core_Uint64Sequence_finalize_w_params(
    holo_base_msg_core_Uint64Sequence* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void holo_base_msg_core_Uint64Sequence_finalize_optional_members(
    holo_base_msg_core_Uint64Sequence* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_Uint64Sequence_copy(
    holo_base_msg_core_Uint64Sequence* dst,
    const holo_base_msg_core_Uint64Sequence* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef     DDS_FloatSeq  holo_base_msg_core_Float32Sequence ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_core_Float32Sequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *holo_base_msg_core_Float32Sequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *holo_base_msg_core_Float32Sequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Float32Sequence
#define TSeq holo_base_msg_core_Float32SequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Float32Sequence
#define TSeq holo_base_msg_core_Float32SequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_core_Float32Sequence*
holo_base_msg_core_Float32Sequence_create();

NDDSUSERDllExport extern void
holo_base_msg_core_Float32Sequence_delete(holo_base_msg_core_Float32Sequence* sample);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Float32Sequence_initialize(
    holo_base_msg_core_Float32Sequence* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Float32Sequence_initialize_ex(
    holo_base_msg_core_Float32Sequence* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Float32Sequence_initialize_w_params(
    holo_base_msg_core_Float32Sequence* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_Float32Sequence_finalize(
    holo_base_msg_core_Float32Sequence* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Float32Sequence_finalize_w_return(
    holo_base_msg_core_Float32Sequence* self);

NDDSUSERDllExport
void holo_base_msg_core_Float32Sequence_finalize_ex(
    holo_base_msg_core_Float32Sequence* self,RTIBool deletePointers);

NDDSUSERDllExport
void holo_base_msg_core_Float32Sequence_finalize_w_params(
    holo_base_msg_core_Float32Sequence* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void holo_base_msg_core_Float32Sequence_finalize_optional_members(
    holo_base_msg_core_Float32Sequence* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_Float32Sequence_copy(
    holo_base_msg_core_Float32Sequence* dst,
    const holo_base_msg_core_Float32Sequence* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef     DDS_DoubleSeq  holo_base_msg_core_Float64Sequence ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_core_Float64Sequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *holo_base_msg_core_Float64Sequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *holo_base_msg_core_Float64Sequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Float64Sequence
#define TSeq holo_base_msg_core_Float64SequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_core_Float64Sequence
#define TSeq holo_base_msg_core_Float64SequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_core_Float64Sequence*
holo_base_msg_core_Float64Sequence_create();

NDDSUSERDllExport extern void
holo_base_msg_core_Float64Sequence_delete(holo_base_msg_core_Float64Sequence* sample);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Float64Sequence_initialize(
    holo_base_msg_core_Float64Sequence* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Float64Sequence_initialize_ex(
    holo_base_msg_core_Float64Sequence* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Float64Sequence_initialize_w_params(
    holo_base_msg_core_Float64Sequence* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_Float64Sequence_finalize(
    holo_base_msg_core_Float64Sequence* self);

NDDSUSERDllExport
RTIBool holo_base_msg_core_Float64Sequence_finalize_w_return(
    holo_base_msg_core_Float64Sequence* self);

NDDSUSERDllExport
void holo_base_msg_core_Float64Sequence_finalize_ex(
    holo_base_msg_core_Float64Sequence* self,RTIBool deletePointers);

NDDSUSERDllExport
void holo_base_msg_core_Float64Sequence_finalize_w_params(
    holo_base_msg_core_Float64Sequence* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void holo_base_msg_core_Float64Sequence_finalize_optional_members(
    holo_base_msg_core_Float64Sequence* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool holo_base_msg_core_Float64Sequence_copy(
    holo_base_msg_core_Float64Sequence* dst,
    const holo_base_msg_core_Float64Sequence* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#ifndef NDDS_STANDALONE_TYPE
#endif

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* Types */

