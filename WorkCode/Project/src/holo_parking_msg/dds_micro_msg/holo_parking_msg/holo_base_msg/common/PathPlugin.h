/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Path.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef PathPlugin_1297920848_h
#define PathPlugin_1297920848_h

#include "Path.h"

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#include "holo_parking_msg/holo_base_msg/common/CommonPlugin.h"

#include "holo_parking_msg/holo_base_msg/core/TypesPlugin.h"

#include "holo_parking_msg/holo_base_msg/geometry/PointPlugin.h"

struct holo_base_msg_common_PathPointfTypePlugin;

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_PathPointfTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_PathPointfWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_PathPointfReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_common_PathPointfTypePlugin_get(void);
NDDSUSERDllExport extern const char*             holo_base_msg_common_PathPointfTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind  holo_base_msg_common_PathPointfI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_PathPointfPlugin_create_sample(struct DDS_TypePlugin* plugin,
                                                                                      void**                 sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_PathPointfPlugin_delete_sample(struct DDS_TypePlugin* plugin,
                                                                                      void*                  sample);
#endif

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_PathPointfPlugin_copy_sample(struct DDS_TypePlugin* plugin,
                                                                                    void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_PathPointf_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                struct CDR_Stream_t*   stream,
                                                                                const void*            void_sample,
                                                                                DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_PathPointf_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                  void*                  void_sample,
                                                                                  struct CDR_Stream_t*   stream,
                                                                                  DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_common_PathPointf_get_serialized_sample_size(struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_common_PathPointf_cdr_serialize_key holo_base_msg_common_PathPointf_cdr_serialize
#define holo_base_msg_common_PathPointf_cdr_deserialize_key holo_base_msg_common_PathPointf_cdr_deserialize
#define holo_base_msg_common_PathPointf_get_serialized_key_size                                                        \
    holo_base_msg_common_PathPointf_get_serialized_sample_size

struct holo_base_msg_common_PathPointdTypePlugin;

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_PathPointdTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_PathPointdWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_PathPointdReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_common_PathPointdTypePlugin_get(void);
NDDSUSERDllExport extern const char*             holo_base_msg_common_PathPointdTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind  holo_base_msg_common_PathPointdI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_PathPointdPlugin_create_sample(struct DDS_TypePlugin* plugin,
                                                                                      void**                 sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_PathPointdPlugin_delete_sample(struct DDS_TypePlugin* plugin,
                                                                                      void*                  sample);
#endif

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_PathPointdPlugin_copy_sample(struct DDS_TypePlugin* plugin,
                                                                                    void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_PathPointd_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                struct CDR_Stream_t*   stream,
                                                                                const void*            void_sample,
                                                                                DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_PathPointd_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                  void*                  void_sample,
                                                                                  struct CDR_Stream_t*   stream,
                                                                                  DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_common_PathPointd_get_serialized_sample_size(struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_common_PathPointd_cdr_serialize_key holo_base_msg_common_PathPointd_cdr_serialize
#define holo_base_msg_common_PathPointd_cdr_deserialize_key holo_base_msg_common_PathPointd_cdr_deserialize
#define holo_base_msg_common_PathPointd_get_serialized_key_size                                                        \
    holo_base_msg_common_PathPointd_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_PathPointfSequence_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                      const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_PathPointfSequence_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                          void* void_sample,
                                                                                          struct CDR_Stream_t*  stream,
                                                                                          DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_common_PathPointfSequence_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_common_PathPointfSequence_cdr_serialize_key holo_base_msg_common_PathPointfSequence_cdr_serialize
#define holo_base_msg_common_PathPointfSequence_cdr_deserialize_key                                                    \
    holo_base_msg_common_PathPointfSequence_cdr_deserialize
#define holo_base_msg_common_PathPointfSequence_get_serialized_key_size                                                \
    holo_base_msg_common_PathPointfSequence_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_PathPointdSequence_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                      const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_PathPointdSequence_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                          void* void_sample,
                                                                                          struct CDR_Stream_t*  stream,
                                                                                          DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_common_PathPointdSequence_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_common_PathPointdSequence_cdr_serialize_key holo_base_msg_common_PathPointdSequence_cdr_serialize
#define holo_base_msg_common_PathPointdSequence_cdr_deserialize_key                                                    \
    holo_base_msg_common_PathPointdSequence_cdr_deserialize
#define holo_base_msg_common_PathPointdSequence_get_serialized_key_size                                                \
    holo_base_msg_common_PathPointdSequence_get_serialized_sample_size

struct holo_base_msg_common_PathfTypePlugin;

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_PathfTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_PathfWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_PathfReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_common_PathfTypePlugin_get(void);
NDDSUSERDllExport extern const char*             holo_base_msg_common_PathfTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind  holo_base_msg_common_PathfI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_PathfPlugin_create_sample(struct DDS_TypePlugin* plugin,
                                                                                 void**                 sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_PathfPlugin_delete_sample(struct DDS_TypePlugin* plugin,
                                                                                 void*                  sample);
#endif

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_PathfPlugin_copy_sample(struct DDS_TypePlugin* plugin, void* dst,
                                                                               const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_Pathf_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                           struct CDR_Stream_t*   stream,
                                                                           const void*            void_sample,
                                                                           DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_Pathf_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                             void*                  void_sample,
                                                                             struct CDR_Stream_t*   stream,
                                                                             DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_common_Pathf_get_serialized_sample_size(struct DDS_TypePlugin* plugin,
                                                                                          RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_common_Pathf_cdr_serialize_key holo_base_msg_common_Pathf_cdr_serialize
#define holo_base_msg_common_Pathf_cdr_deserialize_key holo_base_msg_common_Pathf_cdr_deserialize
#define holo_base_msg_common_Pathf_get_serialized_key_size holo_base_msg_common_Pathf_get_serialized_sample_size

struct holo_base_msg_common_PathdTypePlugin;

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_PathdTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_PathdWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_PathdReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_common_PathdTypePlugin_get(void);
NDDSUSERDllExport extern const char*             holo_base_msg_common_PathdTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind  holo_base_msg_common_PathdI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_PathdPlugin_create_sample(struct DDS_TypePlugin* plugin,
                                                                                 void**                 sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_PathdPlugin_delete_sample(struct DDS_TypePlugin* plugin,
                                                                                 void*                  sample);
#endif

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_PathdPlugin_copy_sample(struct DDS_TypePlugin* plugin, void* dst,
                                                                               const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_Pathd_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                           struct CDR_Stream_t*   stream,
                                                                           const void*            void_sample,
                                                                           DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_Pathd_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                             void*                  void_sample,
                                                                             struct CDR_Stream_t*   stream,
                                                                             DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_common_Pathd_get_serialized_sample_size(struct DDS_TypePlugin* plugin,
                                                                                          RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_common_Pathd_cdr_serialize_key holo_base_msg_common_Pathd_cdr_serialize
#define holo_base_msg_common_Pathd_cdr_deserialize_key holo_base_msg_common_Pathd_cdr_deserialize
#define holo_base_msg_common_Pathd_get_serialized_key_size holo_base_msg_common_Pathd_get_serialized_sample_size

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* PathPlugin_1297920848_h */
