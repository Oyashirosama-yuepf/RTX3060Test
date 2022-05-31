/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ParkingSlot.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef ParkingSlotPlugin_1960983127_h
#define ParkingSlotPlugin_1960983127_h

#include "ParkingSlot.h"

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#include "holo_parking_msg/holo_base_msg/common/CommonPlugin.h"

#include "holo_parking_msg/holo_base_msg/core/TypesPlugin.h"

#include "holo_parking_msg/holo_base_msg/geometry/PointPlugin.h"

struct holo_base_msg_common_ParkingSlotfTypePlugin;

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_ParkingSlotfTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_ParkingSlotfWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_ParkingSlotfReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_common_ParkingSlotfTypePlugin_get(void);
NDDSUSERDllExport extern const char*            holo_base_msg_common_ParkingSlotfTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind holo_base_msg_common_ParkingSlotfI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_ParkingSlotfPlugin_create_sample(struct DDS_TypePlugin* plugin,
                                                                                        void**                 sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_ParkingSlotfPlugin_delete_sample(struct DDS_TypePlugin* plugin,
                                                                                        void*                  sample);
#endif

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_ParkingSlotfPlugin_copy_sample(struct DDS_TypePlugin* plugin,
                                                                                      void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_ParkingSlotf_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                  struct CDR_Stream_t*   stream,
                                                                                  const void*            void_sample,
                                                                                  DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_ParkingSlotf_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                    void*                  void_sample,
                                                                                    struct CDR_Stream_t*   stream,
                                                                                    DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_common_ParkingSlotf_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_common_ParkingSlotf_cdr_serialize_key holo_base_msg_common_ParkingSlotf_cdr_serialize
#define holo_base_msg_common_ParkingSlotf_cdr_deserialize_key holo_base_msg_common_ParkingSlotf_cdr_deserialize
#define holo_base_msg_common_ParkingSlotf_get_serialized_key_size                                                      \
    holo_base_msg_common_ParkingSlotf_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_ParkingSlotfSequence_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                        const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_ParkingSlotfSequence_cdr_deserialize(
    struct DDS_TypePlugin* plugin, void* void_sample, struct CDR_Stream_t* stream, DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_common_ParkingSlotfSequence_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_common_ParkingSlotfSequence_cdr_serialize_key                                                    \
    holo_base_msg_common_ParkingSlotfSequence_cdr_serialize
#define holo_base_msg_common_ParkingSlotfSequence_cdr_deserialize_key                                                  \
    holo_base_msg_common_ParkingSlotfSequence_cdr_deserialize
#define holo_base_msg_common_ParkingSlotfSequence_get_serialized_key_size                                              \
    holo_base_msg_common_ParkingSlotfSequence_get_serialized_sample_size

struct holo_base_msg_common_ParkingSlotdTypePlugin;

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_ParkingSlotdTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_ParkingSlotdWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_ParkingSlotdReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_common_ParkingSlotdTypePlugin_get(void);
NDDSUSERDllExport extern const char*            holo_base_msg_common_ParkingSlotdTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind holo_base_msg_common_ParkingSlotdI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_ParkingSlotdPlugin_create_sample(struct DDS_TypePlugin* plugin,
                                                                                        void**                 sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_ParkingSlotdPlugin_delete_sample(struct DDS_TypePlugin* plugin,
                                                                                        void*                  sample);
#endif

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_ParkingSlotdPlugin_copy_sample(struct DDS_TypePlugin* plugin,
                                                                                      void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_ParkingSlotd_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                  struct CDR_Stream_t*   stream,
                                                                                  const void*            void_sample,
                                                                                  DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_ParkingSlotd_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                    void*                  void_sample,
                                                                                    struct CDR_Stream_t*   stream,
                                                                                    DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_common_ParkingSlotd_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_common_ParkingSlotd_cdr_serialize_key holo_base_msg_common_ParkingSlotd_cdr_serialize
#define holo_base_msg_common_ParkingSlotd_cdr_deserialize_key holo_base_msg_common_ParkingSlotd_cdr_deserialize
#define holo_base_msg_common_ParkingSlotd_get_serialized_key_size                                                      \
    holo_base_msg_common_ParkingSlotd_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_ParkingSlotdSequence_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                        const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_ParkingSlotdSequence_cdr_deserialize(
    struct DDS_TypePlugin* plugin, void* void_sample, struct CDR_Stream_t* stream, DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_common_ParkingSlotdSequence_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_common_ParkingSlotdSequence_cdr_serialize_key                                                    \
    holo_base_msg_common_ParkingSlotdSequence_cdr_serialize
#define holo_base_msg_common_ParkingSlotdSequence_cdr_deserialize_key                                                  \
    holo_base_msg_common_ParkingSlotdSequence_cdr_deserialize
#define holo_base_msg_common_ParkingSlotdSequence_get_serialized_key_size                                              \
    holo_base_msg_common_ParkingSlotdSequence_get_serialized_sample_size

struct holo_base_msg_common_ParkingSlotFramefTypePlugin;

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_ParkingSlotFramefTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_ParkingSlotFramefWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_ParkingSlotFramefReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_common_ParkingSlotFramefTypePlugin_get(void);
NDDSUSERDllExport extern const char* holo_base_msg_common_ParkingSlotFramefTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind holo_base_msg_common_ParkingSlotFramefI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_ParkingSlotFramefPlugin_create_sample(struct DDS_TypePlugin* plugin, void** sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_ParkingSlotFramefPlugin_delete_sample(struct DDS_TypePlugin* plugin, void* sample);
#endif

NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_ParkingSlotFramefPlugin_copy_sample(struct DDS_TypePlugin* plugin, void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_ParkingSlotFramef_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                     const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_ParkingSlotFramef_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                         void* void_sample,
                                                                                         struct CDR_Stream_t*  stream,
                                                                                         DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_common_ParkingSlotFramef_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_common_ParkingSlotFramef_cdr_serialize_key holo_base_msg_common_ParkingSlotFramef_cdr_serialize
#define holo_base_msg_common_ParkingSlotFramef_cdr_deserialize_key                                                     \
    holo_base_msg_common_ParkingSlotFramef_cdr_deserialize
#define holo_base_msg_common_ParkingSlotFramef_get_serialized_key_size                                                 \
    holo_base_msg_common_ParkingSlotFramef_get_serialized_sample_size

struct holo_base_msg_common_ParkingSlotFramedTypePlugin;

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_ParkingSlotFramedTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_ParkingSlotFramedWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_ParkingSlotFramedReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_common_ParkingSlotFramedTypePlugin_get(void);
NDDSUSERDllExport extern const char* holo_base_msg_common_ParkingSlotFramedTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind holo_base_msg_common_ParkingSlotFramedI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_ParkingSlotFramedPlugin_create_sample(struct DDS_TypePlugin* plugin, void** sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_ParkingSlotFramedPlugin_delete_sample(struct DDS_TypePlugin* plugin, void* sample);
#endif

NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_ParkingSlotFramedPlugin_copy_sample(struct DDS_TypePlugin* plugin, void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_ParkingSlotFramed_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                     const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_ParkingSlotFramed_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                         void* void_sample,
                                                                                         struct CDR_Stream_t*  stream,
                                                                                         DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_common_ParkingSlotFramed_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_common_ParkingSlotFramed_cdr_serialize_key holo_base_msg_common_ParkingSlotFramed_cdr_serialize
#define holo_base_msg_common_ParkingSlotFramed_cdr_deserialize_key                                                     \
    holo_base_msg_common_ParkingSlotFramed_cdr_deserialize
#define holo_base_msg_common_ParkingSlotFramed_get_serialized_key_size                                                 \
    holo_base_msg_common_ParkingSlotFramed_get_serialized_sample_size

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* ParkingSlotPlugin_1960983127_h */
