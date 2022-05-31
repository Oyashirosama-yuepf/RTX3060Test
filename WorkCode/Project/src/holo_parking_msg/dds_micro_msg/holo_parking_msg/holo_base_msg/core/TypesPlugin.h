/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Types.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef TypesPlugin_1755247134_h
#define TypesPlugin_1755247134_h

#include "Types.h"

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_bool_t_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_bool_t_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_core_bool_t_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_core_bool_t_cdr_serialize_key holo_base_msg_core_bool_t_cdr_serialize
#define holo_base_msg_core_bool_t_cdr_deserialize_key holo_base_msg_core_bool_t_cdr_deserialize
#define holo_base_msg_core_bool_t_get_serialized_key_size holo_base_msg_core_bool_t_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_char_t_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_char_t_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_core_char_t_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_core_char_t_cdr_serialize_key holo_base_msg_core_char_t_cdr_serialize
#define holo_base_msg_core_char_t_cdr_deserialize_key holo_base_msg_core_char_t_cdr_deserialize
#define holo_base_msg_core_char_t_get_serialized_key_size holo_base_msg_core_char_t_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core__cxx_wchar_t_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core__cxx_wchar_t_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_core__cxx_wchar_t_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_core__cxx_wchar_t_cdr_serialize_key holo_base_msg_core__cxx_wchar_t_cdr_serialize
#define holo_base_msg_core__cxx_wchar_t_cdr_deserialize_key holo_base_msg_core__cxx_wchar_t_cdr_deserialize
#define holo_base_msg_core__cxx_wchar_t_get_serialized_key_size holo_base_msg_core__cxx_wchar_t_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_int8_t_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_int8_t_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_core_int8_t_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_core_int8_t_cdr_serialize_key holo_base_msg_core_int8_t_cdr_serialize
#define holo_base_msg_core_int8_t_cdr_deserialize_key holo_base_msg_core_int8_t_cdr_deserialize
#define holo_base_msg_core_int8_t_get_serialized_key_size holo_base_msg_core_int8_t_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_uint8_t_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_uint8_t_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_core_uint8_t_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_core_uint8_t_cdr_serialize_key holo_base_msg_core_uint8_t_cdr_serialize
#define holo_base_msg_core_uint8_t_cdr_deserialize_key holo_base_msg_core_uint8_t_cdr_deserialize
#define holo_base_msg_core_uint8_t_get_serialized_key_size holo_base_msg_core_uint8_t_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_int16_t_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_int16_t_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_core_int16_t_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_core_int16_t_cdr_serialize_key holo_base_msg_core_int16_t_cdr_serialize
#define holo_base_msg_core_int16_t_cdr_deserialize_key holo_base_msg_core_int16_t_cdr_deserialize
#define holo_base_msg_core_int16_t_get_serialized_key_size holo_base_msg_core_int16_t_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_uint16_t_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_uint16_t_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_core_uint16_t_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_core_uint16_t_cdr_serialize_key holo_base_msg_core_uint16_t_cdr_serialize
#define holo_base_msg_core_uint16_t_cdr_deserialize_key holo_base_msg_core_uint16_t_cdr_deserialize
#define holo_base_msg_core_uint16_t_get_serialized_key_size holo_base_msg_core_uint16_t_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_int32_t_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_int32_t_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_core_int32_t_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_core_int32_t_cdr_serialize_key holo_base_msg_core_int32_t_cdr_serialize
#define holo_base_msg_core_int32_t_cdr_deserialize_key holo_base_msg_core_int32_t_cdr_deserialize
#define holo_base_msg_core_int32_t_get_serialized_key_size holo_base_msg_core_int32_t_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_uint32_t_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_uint32_t_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_core_uint32_t_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_core_uint32_t_cdr_serialize_key holo_base_msg_core_uint32_t_cdr_serialize
#define holo_base_msg_core_uint32_t_cdr_deserialize_key holo_base_msg_core_uint32_t_cdr_deserialize
#define holo_base_msg_core_uint32_t_get_serialized_key_size holo_base_msg_core_uint32_t_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_int64_t_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_int64_t_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_core_int64_t_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_core_int64_t_cdr_serialize_key holo_base_msg_core_int64_t_cdr_serialize
#define holo_base_msg_core_int64_t_cdr_deserialize_key holo_base_msg_core_int64_t_cdr_deserialize
#define holo_base_msg_core_int64_t_get_serialized_key_size holo_base_msg_core_int64_t_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_uint64_t_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_uint64_t_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_core_uint64_t_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_core_uint64_t_cdr_serialize_key holo_base_msg_core_uint64_t_cdr_serialize
#define holo_base_msg_core_uint64_t_cdr_deserialize_key holo_base_msg_core_uint64_t_cdr_deserialize
#define holo_base_msg_core_uint64_t_get_serialized_key_size holo_base_msg_core_uint64_t_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_float32_t_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_float32_t_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_core_float32_t_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_core_float32_t_cdr_serialize_key holo_base_msg_core_float32_t_cdr_serialize
#define holo_base_msg_core_float32_t_cdr_deserialize_key holo_base_msg_core_float32_t_cdr_deserialize
#define holo_base_msg_core_float32_t_get_serialized_key_size holo_base_msg_core_float32_t_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_float64_t_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_float64_t_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_core_float64_t_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_core_float64_t_cdr_serialize_key holo_base_msg_core_float64_t_cdr_serialize
#define holo_base_msg_core_float64_t_cdr_deserialize_key holo_base_msg_core_float64_t_cdr_deserialize
#define holo_base_msg_core_float64_t_get_serialized_key_size holo_base_msg_core_float64_t_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_BoolSequence_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_BoolSequence_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_core_BoolSequence_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_core_BoolSequence_cdr_serialize_key holo_base_msg_core_BoolSequence_cdr_serialize
#define holo_base_msg_core_BoolSequence_cdr_deserialize_key holo_base_msg_core_BoolSequence_cdr_deserialize
#define holo_base_msg_core_BoolSequence_get_serialized_key_size holo_base_msg_core_BoolSequence_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_CharSequence_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_CharSequence_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_core_CharSequence_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_core_CharSequence_cdr_serialize_key holo_base_msg_core_CharSequence_cdr_serialize
#define holo_base_msg_core_CharSequence_cdr_deserialize_key holo_base_msg_core_CharSequence_cdr_deserialize
#define holo_base_msg_core_CharSequence_get_serialized_key_size holo_base_msg_core_CharSequence_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_WcharSequence_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_WcharSequence_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_core_WcharSequence_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_core_WcharSequence_cdr_serialize_key holo_base_msg_core_WcharSequence_cdr_serialize
#define holo_base_msg_core_WcharSequence_cdr_deserialize_key holo_base_msg_core_WcharSequence_cdr_deserialize
#define holo_base_msg_core_WcharSequence_get_serialized_key_size holo_base_msg_core_WcharSequence_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_Int8Sequence_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_Int8Sequence_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_core_Int8Sequence_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_core_Int8Sequence_cdr_serialize_key holo_base_msg_core_Int8Sequence_cdr_serialize
#define holo_base_msg_core_Int8Sequence_cdr_deserialize_key holo_base_msg_core_Int8Sequence_cdr_deserialize
#define holo_base_msg_core_Int8Sequence_get_serialized_key_size holo_base_msg_core_Int8Sequence_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_Uint8Sequence_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_Uint8Sequence_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_core_Uint8Sequence_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_core_Uint8Sequence_cdr_serialize_key holo_base_msg_core_Uint8Sequence_cdr_serialize
#define holo_base_msg_core_Uint8Sequence_cdr_deserialize_key holo_base_msg_core_Uint8Sequence_cdr_deserialize
#define holo_base_msg_core_Uint8Sequence_get_serialized_key_size holo_base_msg_core_Uint8Sequence_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_Int16Sequence_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_Int16Sequence_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_core_Int16Sequence_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_core_Int16Sequence_cdr_serialize_key holo_base_msg_core_Int16Sequence_cdr_serialize
#define holo_base_msg_core_Int16Sequence_cdr_deserialize_key holo_base_msg_core_Int16Sequence_cdr_deserialize
#define holo_base_msg_core_Int16Sequence_get_serialized_key_size holo_base_msg_core_Int16Sequence_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_Uint16Sequence_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_Uint16Sequence_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_core_Uint16Sequence_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_core_Uint16Sequence_cdr_serialize_key holo_base_msg_core_Uint16Sequence_cdr_serialize
#define holo_base_msg_core_Uint16Sequence_cdr_deserialize_key holo_base_msg_core_Uint16Sequence_cdr_deserialize
#define holo_base_msg_core_Uint16Sequence_get_serialized_key_size holo_base_msg_core_Uint16Sequence_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_Int32Sequence_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_Int32Sequence_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_core_Int32Sequence_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_core_Int32Sequence_cdr_serialize_key holo_base_msg_core_Int32Sequence_cdr_serialize
#define holo_base_msg_core_Int32Sequence_cdr_deserialize_key holo_base_msg_core_Int32Sequence_cdr_deserialize
#define holo_base_msg_core_Int32Sequence_get_serialized_key_size holo_base_msg_core_Int32Sequence_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_Uint32Sequence_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_Uint32Sequence_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_core_Uint32Sequence_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_core_Uint32Sequence_cdr_serialize_key holo_base_msg_core_Uint32Sequence_cdr_serialize
#define holo_base_msg_core_Uint32Sequence_cdr_deserialize_key holo_base_msg_core_Uint32Sequence_cdr_deserialize
#define holo_base_msg_core_Uint32Sequence_get_serialized_key_size holo_base_msg_core_Uint32Sequence_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_Int64Sequence_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_Int64Sequence_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_core_Int64Sequence_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_core_Int64Sequence_cdr_serialize_key holo_base_msg_core_Int64Sequence_cdr_serialize
#define holo_base_msg_core_Int64Sequence_cdr_deserialize_key holo_base_msg_core_Int64Sequence_cdr_deserialize
#define holo_base_msg_core_Int64Sequence_get_serialized_key_size holo_base_msg_core_Int64Sequence_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_Uint64Sequence_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_Uint64Sequence_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_core_Uint64Sequence_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_core_Uint64Sequence_cdr_serialize_key holo_base_msg_core_Uint64Sequence_cdr_serialize
#define holo_base_msg_core_Uint64Sequence_cdr_deserialize_key holo_base_msg_core_Uint64Sequence_cdr_deserialize
#define holo_base_msg_core_Uint64Sequence_get_serialized_key_size holo_base_msg_core_Uint64Sequence_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_Float32Sequence_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_Float32Sequence_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_core_Float32Sequence_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_core_Float32Sequence_cdr_serialize_key holo_base_msg_core_Float32Sequence_cdr_serialize
#define holo_base_msg_core_Float32Sequence_cdr_deserialize_key holo_base_msg_core_Float32Sequence_cdr_deserialize
#define holo_base_msg_core_Float32Sequence_get_serialized_key_size holo_base_msg_core_Float32Sequence_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_Float64Sequence_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
holo_base_msg_core_Float64Sequence_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_core_Float64Sequence_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_core_Float64Sequence_cdr_serialize_key holo_base_msg_core_Float64Sequence_cdr_serialize
#define holo_base_msg_core_Float64Sequence_cdr_deserialize_key holo_base_msg_core_Float64Sequence_cdr_deserialize
#define holo_base_msg_core_Float64Sequence_get_serialized_key_size holo_base_msg_core_Float64Sequence_get_serialized_sample_size

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* TypesPlugin_1755247134_h */

