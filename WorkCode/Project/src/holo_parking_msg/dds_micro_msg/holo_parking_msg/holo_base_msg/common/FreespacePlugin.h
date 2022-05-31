/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Freespace.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef FreespacePlugin_1959326732_h
#define FreespacePlugin_1959326732_h

#include "Freespace.h"

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#include "holo_parking_msg/holo_base_msg/common/CommonPlugin.h"

#include "holo_parking_msg/holo_base_msg/geometry/PointPlugin.h"

#include "holo_parking_msg/holo_base_msg/core/TypesPlugin.h"

struct holo_base_msg_common_freespace3f_SegmentInfoTypePlugin;

NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_freespace3f_SegmentInfoTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_freespace3f_SegmentInfoWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_freespace3f_SegmentInfoReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_common_freespace3f_SegmentInfoTypePlugin_get(void);
NDDSUSERDllExport extern const char* holo_base_msg_common_freespace3f_SegmentInfoTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind holo_base_msg_common_freespace3f_SegmentInfoI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_freespace3f_SegmentInfoPlugin_create_sample(struct DDS_TypePlugin* plugin, void** sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_freespace3f_SegmentInfoPlugin_delete_sample(struct DDS_TypePlugin* plugin, void* sample);
#endif

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_freespace3f_SegmentInfoPlugin_copy_sample(
    struct DDS_TypePlugin* plugin, void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_freespace3f_SegmentInfo_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                           const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_freespace3f_SegmentInfo_cdr_deserialize(
    struct DDS_TypePlugin* plugin, void* void_sample, struct CDR_Stream_t* stream, DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_common_freespace3f_SegmentInfo_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_common_freespace3f_SegmentInfo_cdr_serialize_key                                                 \
    holo_base_msg_common_freespace3f_SegmentInfo_cdr_serialize
#define holo_base_msg_common_freespace3f_SegmentInfo_cdr_deserialize_key                                               \
    holo_base_msg_common_freespace3f_SegmentInfo_cdr_deserialize
#define holo_base_msg_common_freespace3f_SegmentInfo_get_serialized_key_size                                           \
    holo_base_msg_common_freespace3f_SegmentInfo_get_serialized_sample_size

struct holo_base_msg_common_freespace3f_FreespaceInteriorTypePlugin;

NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_freespace3f_FreespaceInteriorTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin*
holo_base_msg_common_freespace3f_FreespaceInteriorWriterTypePlugin_create(DDS_DomainParticipant*           participant,
                                                                          struct DDS_DomainParticipantQos* dp_qos,
                                                                          DDS_DataWriter*                  writer,
                                                                          struct DDS_DataWriterQos*        qos,
                                                                          struct DDS_TypePluginProperty*   property);

NDDSUSERDllExport extern struct DDS_TypePlugin*
holo_base_msg_common_freespace3f_FreespaceInteriorReaderTypePlugin_create(DDS_DomainParticipant*           participant,
                                                                          struct DDS_DomainParticipantQos* dp_qos,
                                                                          DDS_DataReader*                  reader,
                                                                          struct DDS_DataReaderQos*        qos,
                                                                          struct DDS_TypePluginProperty*   property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_common_freespace3f_FreespaceInteriorTypePlugin_get(void);
NDDSUSERDllExport extern const char*
holo_base_msg_common_freespace3f_FreespaceInteriorTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind holo_base_msg_common_freespace3f_FreespaceInteriorI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_freespace3f_FreespaceInteriorPlugin_create_sample(struct DDS_TypePlugin* plugin, void** sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_freespace3f_FreespaceInteriorPlugin_delete_sample(struct DDS_TypePlugin* plugin, void* sample);
#endif

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_freespace3f_FreespaceInteriorPlugin_copy_sample(
    struct DDS_TypePlugin* plugin, void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_freespace3f_FreespaceInterior_cdr_serialize(
    struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream, const void* void_sample,
    DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_freespace3f_FreespaceInterior_cdr_deserialize(
    struct DDS_TypePlugin* plugin, void* void_sample, struct CDR_Stream_t* stream, DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_common_freespace3f_FreespaceInterior_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_common_freespace3f_FreespaceInterior_cdr_serialize_key                                           \
    holo_base_msg_common_freespace3f_FreespaceInterior_cdr_serialize
#define holo_base_msg_common_freespace3f_FreespaceInterior_cdr_deserialize_key                                         \
    holo_base_msg_common_freespace3f_FreespaceInterior_cdr_deserialize
#define holo_base_msg_common_freespace3f_FreespaceInterior_get_serialized_key_size                                     \
    holo_base_msg_common_freespace3f_FreespaceInterior_get_serialized_sample_size

struct holo_base_msg_common_freespace3f_FreespaceExteriorTypePlugin;

NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_freespace3f_FreespaceExteriorTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin*
holo_base_msg_common_freespace3f_FreespaceExteriorWriterTypePlugin_create(DDS_DomainParticipant*           participant,
                                                                          struct DDS_DomainParticipantQos* dp_qos,
                                                                          DDS_DataWriter*                  writer,
                                                                          struct DDS_DataWriterQos*        qos,
                                                                          struct DDS_TypePluginProperty*   property);

NDDSUSERDllExport extern struct DDS_TypePlugin*
holo_base_msg_common_freespace3f_FreespaceExteriorReaderTypePlugin_create(DDS_DomainParticipant*           participant,
                                                                          struct DDS_DomainParticipantQos* dp_qos,
                                                                          DDS_DataReader*                  reader,
                                                                          struct DDS_DataReaderQos*        qos,
                                                                          struct DDS_TypePluginProperty*   property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_common_freespace3f_FreespaceExteriorTypePlugin_get(void);
NDDSUSERDllExport extern const char*
holo_base_msg_common_freespace3f_FreespaceExteriorTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind holo_base_msg_common_freespace3f_FreespaceExteriorI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_freespace3f_FreespaceExteriorPlugin_create_sample(struct DDS_TypePlugin* plugin, void** sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_freespace3f_FreespaceExteriorPlugin_delete_sample(struct DDS_TypePlugin* plugin, void* sample);
#endif

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_freespace3f_FreespaceExteriorPlugin_copy_sample(
    struct DDS_TypePlugin* plugin, void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_freespace3f_FreespaceExterior_cdr_serialize(
    struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream, const void* void_sample,
    DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_freespace3f_FreespaceExterior_cdr_deserialize(
    struct DDS_TypePlugin* plugin, void* void_sample, struct CDR_Stream_t* stream, DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_common_freespace3f_FreespaceExterior_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_common_freespace3f_FreespaceExterior_cdr_serialize_key                                           \
    holo_base_msg_common_freespace3f_FreespaceExterior_cdr_serialize
#define holo_base_msg_common_freespace3f_FreespaceExterior_cdr_deserialize_key                                         \
    holo_base_msg_common_freespace3f_FreespaceExterior_cdr_deserialize
#define holo_base_msg_common_freespace3f_FreespaceExterior_get_serialized_key_size                                     \
    holo_base_msg_common_freespace3f_FreespaceExterior_get_serialized_sample_size

struct holo_base_msg_common_freespace3f_FreespaceTypePlugin;

NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_freespace3f_FreespaceTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_freespace3f_FreespaceWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_freespace3f_FreespaceReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_common_freespace3f_FreespaceTypePlugin_get(void);
NDDSUSERDllExport extern const char* holo_base_msg_common_freespace3f_FreespaceTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind holo_base_msg_common_freespace3f_FreespaceI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_freespace3f_FreespacePlugin_create_sample(struct DDS_TypePlugin* plugin, void** sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_freespace3f_FreespacePlugin_delete_sample(struct DDS_TypePlugin* plugin, void* sample);
#endif

NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_freespace3f_FreespacePlugin_copy_sample(struct DDS_TypePlugin* plugin, void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_freespace3f_Freespace_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                         const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_freespace3f_Freespace_cdr_deserialize(
    struct DDS_TypePlugin* plugin, void* void_sample, struct CDR_Stream_t* stream, DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_common_freespace3f_Freespace_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_common_freespace3f_Freespace_cdr_serialize_key                                                   \
    holo_base_msg_common_freespace3f_Freespace_cdr_serialize
#define holo_base_msg_common_freespace3f_Freespace_cdr_deserialize_key                                                 \
    holo_base_msg_common_freespace3f_Freespace_cdr_deserialize
#define holo_base_msg_common_freespace3f_Freespace_get_serialized_key_size                                             \
    holo_base_msg_common_freespace3f_Freespace_get_serialized_sample_size

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* FreespacePlugin_1959326732_h */
