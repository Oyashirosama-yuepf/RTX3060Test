/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Builtin.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef BuiltinPlugin_1564184277_h
#define BuiltinPlugin_1564184277_h

#include "Builtin.h"

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

struct opendds_wrapper_BuiltinTimestampTypePlugin;

NDDSUSERDllExport extern RTI_BOOL
opendds_wrapper_BuiltinTimestampTypePlugin_delete(struct DDS_TypePlugin *self);

NDDSUSERDllExport extern struct DDS_TypePlugin*
opendds_wrapper_BuiltinTimestampWriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property);

NDDSUSERDllExport extern struct DDS_TypePlugin*
opendds_wrapper_BuiltinTimestampReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property);

NDDSUSERDllExport extern struct DDS_TypePluginI*
opendds_wrapper_BuiltinTimestampTypePlugin_get(void);
NDDSUSERDllExport extern const char*
opendds_wrapper_BuiltinTimestampTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind 
opendds_wrapper_BuiltinTimestampI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
opendds_wrapper_BuiltinTimestampPlugin_create_sample(
    struct DDS_TypePlugin *plugin, void **sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinTimestampPlugin_delete_sample(
    struct DDS_TypePlugin *plugin, void *sample);
#endif

NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinTimestampPlugin_copy_sample(
    struct DDS_TypePlugin *plugin, void *dst, const void *src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinTimestamp_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinTimestamp_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
opendds_wrapper_BuiltinTimestamp_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define opendds_wrapper_BuiltinTimestamp_cdr_serialize_key opendds_wrapper_BuiltinTimestamp_cdr_serialize
#define opendds_wrapper_BuiltinTimestamp_cdr_deserialize_key opendds_wrapper_BuiltinTimestamp_cdr_deserialize
#define opendds_wrapper_BuiltinTimestamp_get_serialized_key_size opendds_wrapper_BuiltinTimestamp_get_serialized_sample_size

struct opendds_wrapper_BuiltinUint8TypePlugin;

NDDSUSERDllExport extern RTI_BOOL
opendds_wrapper_BuiltinUint8TypePlugin_delete(struct DDS_TypePlugin *self);

NDDSUSERDllExport extern struct DDS_TypePlugin*
opendds_wrapper_BuiltinUint8WriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property);

NDDSUSERDllExport extern struct DDS_TypePlugin*
opendds_wrapper_BuiltinUint8ReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property);

NDDSUSERDllExport extern struct DDS_TypePluginI*
opendds_wrapper_BuiltinUint8TypePlugin_get(void);
NDDSUSERDllExport extern const char*
opendds_wrapper_BuiltinUint8TypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind 
opendds_wrapper_BuiltinUint8I_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
opendds_wrapper_BuiltinUint8Plugin_create_sample(
    struct DDS_TypePlugin *plugin, void **sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinUint8Plugin_delete_sample(
    struct DDS_TypePlugin *plugin, void *sample);
#endif

NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinUint8Plugin_copy_sample(
    struct DDS_TypePlugin *plugin, void *dst, const void *src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinUint8_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinUint8_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
opendds_wrapper_BuiltinUint8_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define opendds_wrapper_BuiltinUint8_cdr_serialize_key opendds_wrapper_BuiltinUint8_cdr_serialize
#define opendds_wrapper_BuiltinUint8_cdr_deserialize_key opendds_wrapper_BuiltinUint8_cdr_deserialize
#define opendds_wrapper_BuiltinUint8_get_serialized_key_size opendds_wrapper_BuiltinUint8_get_serialized_sample_size

struct opendds_wrapper_BuiltinUint16TypePlugin;

NDDSUSERDllExport extern RTI_BOOL
opendds_wrapper_BuiltinUint16TypePlugin_delete(struct DDS_TypePlugin *self);

NDDSUSERDllExport extern struct DDS_TypePlugin*
opendds_wrapper_BuiltinUint16WriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property);

NDDSUSERDllExport extern struct DDS_TypePlugin*
opendds_wrapper_BuiltinUint16ReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property);

NDDSUSERDllExport extern struct DDS_TypePluginI*
opendds_wrapper_BuiltinUint16TypePlugin_get(void);
NDDSUSERDllExport extern const char*
opendds_wrapper_BuiltinUint16TypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind 
opendds_wrapper_BuiltinUint16I_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
opendds_wrapper_BuiltinUint16Plugin_create_sample(
    struct DDS_TypePlugin *plugin, void **sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinUint16Plugin_delete_sample(
    struct DDS_TypePlugin *plugin, void *sample);
#endif

NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinUint16Plugin_copy_sample(
    struct DDS_TypePlugin *plugin, void *dst, const void *src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinUint16_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinUint16_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
opendds_wrapper_BuiltinUint16_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define opendds_wrapper_BuiltinUint16_cdr_serialize_key opendds_wrapper_BuiltinUint16_cdr_serialize
#define opendds_wrapper_BuiltinUint16_cdr_deserialize_key opendds_wrapper_BuiltinUint16_cdr_deserialize
#define opendds_wrapper_BuiltinUint16_get_serialized_key_size opendds_wrapper_BuiltinUint16_get_serialized_sample_size

struct opendds_wrapper_BuiltinUint32TypePlugin;

NDDSUSERDllExport extern RTI_BOOL
opendds_wrapper_BuiltinUint32TypePlugin_delete(struct DDS_TypePlugin *self);

NDDSUSERDllExport extern struct DDS_TypePlugin*
opendds_wrapper_BuiltinUint32WriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property);

NDDSUSERDllExport extern struct DDS_TypePlugin*
opendds_wrapper_BuiltinUint32ReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property);

NDDSUSERDllExport extern struct DDS_TypePluginI*
opendds_wrapper_BuiltinUint32TypePlugin_get(void);
NDDSUSERDllExport extern const char*
opendds_wrapper_BuiltinUint32TypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind 
opendds_wrapper_BuiltinUint32I_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
opendds_wrapper_BuiltinUint32Plugin_create_sample(
    struct DDS_TypePlugin *plugin, void **sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinUint32Plugin_delete_sample(
    struct DDS_TypePlugin *plugin, void *sample);
#endif

NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinUint32Plugin_copy_sample(
    struct DDS_TypePlugin *plugin, void *dst, const void *src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinUint32_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinUint32_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
opendds_wrapper_BuiltinUint32_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define opendds_wrapper_BuiltinUint32_cdr_serialize_key opendds_wrapper_BuiltinUint32_cdr_serialize
#define opendds_wrapper_BuiltinUint32_cdr_deserialize_key opendds_wrapper_BuiltinUint32_cdr_deserialize
#define opendds_wrapper_BuiltinUint32_get_serialized_key_size opendds_wrapper_BuiltinUint32_get_serialized_sample_size

struct opendds_wrapper_BuiltinUint64TypePlugin;

NDDSUSERDllExport extern RTI_BOOL
opendds_wrapper_BuiltinUint64TypePlugin_delete(struct DDS_TypePlugin *self);

NDDSUSERDllExport extern struct DDS_TypePlugin*
opendds_wrapper_BuiltinUint64WriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property);

NDDSUSERDllExport extern struct DDS_TypePlugin*
opendds_wrapper_BuiltinUint64ReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property);

NDDSUSERDllExport extern struct DDS_TypePluginI*
opendds_wrapper_BuiltinUint64TypePlugin_get(void);
NDDSUSERDllExport extern const char*
opendds_wrapper_BuiltinUint64TypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind 
opendds_wrapper_BuiltinUint64I_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
opendds_wrapper_BuiltinUint64Plugin_create_sample(
    struct DDS_TypePlugin *plugin, void **sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinUint64Plugin_delete_sample(
    struct DDS_TypePlugin *plugin, void *sample);
#endif

NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinUint64Plugin_copy_sample(
    struct DDS_TypePlugin *plugin, void *dst, const void *src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinUint64_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinUint64_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
opendds_wrapper_BuiltinUint64_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define opendds_wrapper_BuiltinUint64_cdr_serialize_key opendds_wrapper_BuiltinUint64_cdr_serialize
#define opendds_wrapper_BuiltinUint64_cdr_deserialize_key opendds_wrapper_BuiltinUint64_cdr_deserialize
#define opendds_wrapper_BuiltinUint64_get_serialized_key_size opendds_wrapper_BuiltinUint64_get_serialized_sample_size

struct opendds_wrapper_BuiltinFloat32TypePlugin;

NDDSUSERDllExport extern RTI_BOOL
opendds_wrapper_BuiltinFloat32TypePlugin_delete(struct DDS_TypePlugin *self);

NDDSUSERDllExport extern struct DDS_TypePlugin*
opendds_wrapper_BuiltinFloat32WriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property);

NDDSUSERDllExport extern struct DDS_TypePlugin*
opendds_wrapper_BuiltinFloat32ReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property);

NDDSUSERDllExport extern struct DDS_TypePluginI*
opendds_wrapper_BuiltinFloat32TypePlugin_get(void);
NDDSUSERDllExport extern const char*
opendds_wrapper_BuiltinFloat32TypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind 
opendds_wrapper_BuiltinFloat32I_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
opendds_wrapper_BuiltinFloat32Plugin_create_sample(
    struct DDS_TypePlugin *plugin, void **sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinFloat32Plugin_delete_sample(
    struct DDS_TypePlugin *plugin, void *sample);
#endif

NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinFloat32Plugin_copy_sample(
    struct DDS_TypePlugin *plugin, void *dst, const void *src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinFloat32_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinFloat32_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
opendds_wrapper_BuiltinFloat32_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define opendds_wrapper_BuiltinFloat32_cdr_serialize_key opendds_wrapper_BuiltinFloat32_cdr_serialize
#define opendds_wrapper_BuiltinFloat32_cdr_deserialize_key opendds_wrapper_BuiltinFloat32_cdr_deserialize
#define opendds_wrapper_BuiltinFloat32_get_serialized_key_size opendds_wrapper_BuiltinFloat32_get_serialized_sample_size

struct opendds_wrapper_BuiltinFloat64TypePlugin;

NDDSUSERDllExport extern RTI_BOOL
opendds_wrapper_BuiltinFloat64TypePlugin_delete(struct DDS_TypePlugin *self);

NDDSUSERDllExport extern struct DDS_TypePlugin*
opendds_wrapper_BuiltinFloat64WriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property);

NDDSUSERDllExport extern struct DDS_TypePlugin*
opendds_wrapper_BuiltinFloat64ReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property);

NDDSUSERDllExport extern struct DDS_TypePluginI*
opendds_wrapper_BuiltinFloat64TypePlugin_get(void);
NDDSUSERDllExport extern const char*
opendds_wrapper_BuiltinFloat64TypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind 
opendds_wrapper_BuiltinFloat64I_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
opendds_wrapper_BuiltinFloat64Plugin_create_sample(
    struct DDS_TypePlugin *plugin, void **sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinFloat64Plugin_delete_sample(
    struct DDS_TypePlugin *plugin, void *sample);
#endif

NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinFloat64Plugin_copy_sample(
    struct DDS_TypePlugin *plugin, void *dst, const void *src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinFloat64_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinFloat64_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
opendds_wrapper_BuiltinFloat64_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define opendds_wrapper_BuiltinFloat64_cdr_serialize_key opendds_wrapper_BuiltinFloat64_cdr_serialize
#define opendds_wrapper_BuiltinFloat64_cdr_deserialize_key opendds_wrapper_BuiltinFloat64_cdr_deserialize
#define opendds_wrapper_BuiltinFloat64_get_serialized_key_size opendds_wrapper_BuiltinFloat64_get_serialized_sample_size

struct opendds_wrapper_BuiltinStringTypePlugin;

NDDSUSERDllExport extern RTI_BOOL
opendds_wrapper_BuiltinStringTypePlugin_delete(struct DDS_TypePlugin *self);

NDDSUSERDllExport extern struct DDS_TypePlugin*
opendds_wrapper_BuiltinStringWriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property);

NDDSUSERDllExport extern struct DDS_TypePlugin*
opendds_wrapper_BuiltinStringReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property);

NDDSUSERDllExport extern struct DDS_TypePluginI*
opendds_wrapper_BuiltinStringTypePlugin_get(void);
NDDSUSERDllExport extern const char*
opendds_wrapper_BuiltinStringTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind 
opendds_wrapper_BuiltinStringI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
opendds_wrapper_BuiltinStringPlugin_create_sample(
    struct DDS_TypePlugin *plugin, void **sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinStringPlugin_delete_sample(
    struct DDS_TypePlugin *plugin, void *sample);
#endif

NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinStringPlugin_copy_sample(
    struct DDS_TypePlugin *plugin, void *dst, const void *src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinString_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinString_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
opendds_wrapper_BuiltinString_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define opendds_wrapper_BuiltinString_cdr_serialize_key opendds_wrapper_BuiltinString_cdr_serialize
#define opendds_wrapper_BuiltinString_cdr_deserialize_key opendds_wrapper_BuiltinString_cdr_deserialize
#define opendds_wrapper_BuiltinString_get_serialized_key_size opendds_wrapper_BuiltinString_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_OctetSequence_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_OctetSequence_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
opendds_wrapper_OctetSequence_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define opendds_wrapper_OctetSequence_cdr_serialize_key opendds_wrapper_OctetSequence_cdr_serialize
#define opendds_wrapper_OctetSequence_cdr_deserialize_key opendds_wrapper_OctetSequence_cdr_deserialize
#define opendds_wrapper_OctetSequence_get_serialized_key_size opendds_wrapper_OctetSequence_get_serialized_sample_size

struct opendds_wrapper_BuiltinBufferTypePlugin;

NDDSUSERDllExport extern RTI_BOOL
opendds_wrapper_BuiltinBufferTypePlugin_delete(struct DDS_TypePlugin *self);

NDDSUSERDllExport extern struct DDS_TypePlugin*
opendds_wrapper_BuiltinBufferWriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property);

NDDSUSERDllExport extern struct DDS_TypePlugin*
opendds_wrapper_BuiltinBufferReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property);

NDDSUSERDllExport extern struct DDS_TypePluginI*
opendds_wrapper_BuiltinBufferTypePlugin_get(void);
NDDSUSERDllExport extern const char*
opendds_wrapper_BuiltinBufferTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind 
opendds_wrapper_BuiltinBufferI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
opendds_wrapper_BuiltinBufferPlugin_create_sample(
    struct DDS_TypePlugin *plugin, void **sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinBufferPlugin_delete_sample(
    struct DDS_TypePlugin *plugin, void *sample);
#endif

NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinBufferPlugin_copy_sample(
    struct DDS_TypePlugin *plugin, void *dst, const void *src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinBuffer_cdr_serialize(struct DDS_TypePlugin *plugin, 
struct CDR_Stream_t *stream, 
const void *void_sample,
DDS_InstanceHandle_t *destination);

NDDSUSERDllExport extern RTI_BOOL 
opendds_wrapper_BuiltinBuffer_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source); 

NDDSUSERDllExport extern RTI_UINT32
opendds_wrapper_BuiltinBuffer_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define opendds_wrapper_BuiltinBuffer_cdr_serialize_key opendds_wrapper_BuiltinBuffer_cdr_serialize
#define opendds_wrapper_BuiltinBuffer_cdr_deserialize_key opendds_wrapper_BuiltinBuffer_cdr_deserialize
#define opendds_wrapper_BuiltinBuffer_get_serialized_key_size opendds_wrapper_BuiltinBuffer_get_serialized_sample_size

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* BuiltinPlugin_1564184277_h */

