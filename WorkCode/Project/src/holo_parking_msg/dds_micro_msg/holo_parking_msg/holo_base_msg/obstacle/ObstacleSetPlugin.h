/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ObstacleSet.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef ObstacleSetPlugin_406046225_h
#define ObstacleSetPlugin_406046225_h

#include "ObstacleSet.h"

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#include "holo_parking_msg/holo_base_msg/core/TypesPlugin.h"

#include "holo_parking_msg/holo_base_msg/common/CommonPlugin.h"

#include "holo_parking_msg/holo_base_msg/geometry/BoxPlugin.h"

#include "holo_parking_msg/holo_base_msg/geometry/PointPlugin.h"

#include "holo_parking_msg/holo_base_msg/numerics/VectorPlugin.h"

#include "holo_parking_msg/holo_base_msg/vision/ImageObjectsPlugin.h"

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_obstacle_CutInCutOut_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                   struct CDR_Stream_t*   stream,
                                                                                   const void*            void_sample,
                                                                                   DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_obstacle_CutInCutOut_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                     void*                  void_sample,
                                                                                     struct CDR_Stream_t*   stream,
                                                                                     DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_obstacle_CutInCutOut_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_obstacle_CutInCutOut_cdr_serialize_key holo_base_msg_obstacle_CutInCutOut_cdr_serialize
#define holo_base_msg_obstacle_CutInCutOut_cdr_deserialize_key holo_base_msg_obstacle_CutInCutOut_cdr_deserialize
#define holo_base_msg_obstacle_CutInCutOut_get_serialized_key_size                                                     \
    holo_base_msg_obstacle_CutInCutOut_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_obstacle_MotionStatus_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                    struct CDR_Stream_t*   stream,
                                                                                    const void*            void_sample,
                                                                                    DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_obstacle_MotionStatus_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                      void*                 void_sample,
                                                                                      struct CDR_Stream_t*  stream,
                                                                                      DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_obstacle_MotionStatus_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_obstacle_MotionStatus_cdr_serialize_key holo_base_msg_obstacle_MotionStatus_cdr_serialize
#define holo_base_msg_obstacle_MotionStatus_cdr_deserialize_key holo_base_msg_obstacle_MotionStatus_cdr_deserialize
#define holo_base_msg_obstacle_MotionStatus_get_serialized_key_size                                                    \
    holo_base_msg_obstacle_MotionStatus_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_PerceptionAbility_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                       const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_obstacle_PerceptionAbility_cdr_deserialize(
    struct DDS_TypePlugin* plugin, void* void_sample, struct CDR_Stream_t* stream, DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_obstacle_PerceptionAbility_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_obstacle_PerceptionAbility_cdr_serialize_key                                                     \
    holo_base_msg_obstacle_PerceptionAbility_cdr_serialize
#define holo_base_msg_obstacle_PerceptionAbility_cdr_deserialize_key                                                   \
    holo_base_msg_obstacle_PerceptionAbility_cdr_deserialize
#define holo_base_msg_obstacle_PerceptionAbility_get_serialized_key_size                                               \
    holo_base_msg_obstacle_PerceptionAbility_get_serialized_sample_size

struct holo_base_msg_obstacle_ObstacleGeneralTypePlugin;

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_obstacle_ObstacleGeneralTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_obstacle_ObstacleGeneralWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_obstacle_ObstacleGeneralReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_obstacle_ObstacleGeneralTypePlugin_get(void);
NDDSUSERDllExport extern const char* holo_base_msg_obstacle_ObstacleGeneralTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind holo_base_msg_obstacle_ObstacleGeneralI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_ObstacleGeneralPlugin_create_sample(struct DDS_TypePlugin* plugin, void** sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_ObstacleGeneralPlugin_delete_sample(struct DDS_TypePlugin* plugin, void* sample);
#endif

NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_ObstacleGeneralPlugin_copy_sample(struct DDS_TypePlugin* plugin, void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_ObstacleGeneral_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                     const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_obstacle_ObstacleGeneral_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                         void* void_sample,
                                                                                         struct CDR_Stream_t*  stream,
                                                                                         DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_obstacle_ObstacleGeneral_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_obstacle_ObstacleGeneral_cdr_serialize_key holo_base_msg_obstacle_ObstacleGeneral_cdr_serialize
#define holo_base_msg_obstacle_ObstacleGeneral_cdr_deserialize_key                                                     \
    holo_base_msg_obstacle_ObstacleGeneral_cdr_deserialize
#define holo_base_msg_obstacle_ObstacleGeneral_get_serialized_key_size                                                 \
    holo_base_msg_obstacle_ObstacleGeneral_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_obstacle_ObstacleGeneralSequence_cdr_serialize(
    struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream, const void* void_sample,
    DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_obstacle_ObstacleGeneralSequence_cdr_deserialize(
    struct DDS_TypePlugin* plugin, void* void_sample, struct CDR_Stream_t* stream, DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_obstacle_ObstacleGeneralSequence_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_obstacle_ObstacleGeneralSequence_cdr_serialize_key                                               \
    holo_base_msg_obstacle_ObstacleGeneralSequence_cdr_serialize
#define holo_base_msg_obstacle_ObstacleGeneralSequence_cdr_deserialize_key                                             \
    holo_base_msg_obstacle_ObstacleGeneralSequence_cdr_deserialize
#define holo_base_msg_obstacle_ObstacleGeneralSequence_get_serialized_key_size                                         \
    holo_base_msg_obstacle_ObstacleGeneralSequence_get_serialized_sample_size

struct holo_base_msg_obstacle_ObstacleGeneralListTypePlugin;

NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_ObstacleGeneralListTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_obstacle_ObstacleGeneralListWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_obstacle_ObstacleGeneralListReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_obstacle_ObstacleGeneralListTypePlugin_get(void);
NDDSUSERDllExport extern const char* holo_base_msg_obstacle_ObstacleGeneralListTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind holo_base_msg_obstacle_ObstacleGeneralListI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_ObstacleGeneralListPlugin_create_sample(struct DDS_TypePlugin* plugin, void** sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_ObstacleGeneralListPlugin_delete_sample(struct DDS_TypePlugin* plugin, void* sample);
#endif

NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_ObstacleGeneralListPlugin_copy_sample(struct DDS_TypePlugin* plugin, void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_ObstacleGeneralList_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                         const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_obstacle_ObstacleGeneralList_cdr_deserialize(
    struct DDS_TypePlugin* plugin, void* void_sample, struct CDR_Stream_t* stream, DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_obstacle_ObstacleGeneralList_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_obstacle_ObstacleGeneralList_cdr_serialize_key                                                   \
    holo_base_msg_obstacle_ObstacleGeneralList_cdr_serialize
#define holo_base_msg_obstacle_ObstacleGeneralList_cdr_deserialize_key                                                 \
    holo_base_msg_obstacle_ObstacleGeneralList_cdr_deserialize
#define holo_base_msg_obstacle_ObstacleGeneralList_get_serialized_key_size                                             \
    holo_base_msg_obstacle_ObstacleGeneralList_get_serialized_sample_size

struct holo_base_msg_obstacle_ObstacleRadarTypePlugin;

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_obstacle_ObstacleRadarTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_obstacle_ObstacleRadarWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_obstacle_ObstacleRadarReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_obstacle_ObstacleRadarTypePlugin_get(void);
NDDSUSERDllExport extern const char* holo_base_msg_obstacle_ObstacleRadarTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind holo_base_msg_obstacle_ObstacleRadarI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_ObstacleRadarPlugin_create_sample(struct DDS_TypePlugin* plugin, void** sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_ObstacleRadarPlugin_delete_sample(struct DDS_TypePlugin* plugin, void* sample);
#endif

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_obstacle_ObstacleRadarPlugin_copy_sample(struct DDS_TypePlugin* plugin,
                                                                                         void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_obstacle_ObstacleRadar_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                     struct CDR_Stream_t*   stream,
                                                                                     const void*            void_sample,
                                                                                     DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_obstacle_ObstacleRadar_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                       void*                void_sample,
                                                                                       struct CDR_Stream_t* stream,
                                                                                       DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_obstacle_ObstacleRadar_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_obstacle_ObstacleRadar_cdr_serialize_key holo_base_msg_obstacle_ObstacleRadar_cdr_serialize
#define holo_base_msg_obstacle_ObstacleRadar_cdr_deserialize_key holo_base_msg_obstacle_ObstacleRadar_cdr_deserialize
#define holo_base_msg_obstacle_ObstacleRadar_get_serialized_key_size                                                   \
    holo_base_msg_obstacle_ObstacleRadar_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_ObstacleRadarSequence_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                           const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_obstacle_ObstacleRadarSequence_cdr_deserialize(
    struct DDS_TypePlugin* plugin, void* void_sample, struct CDR_Stream_t* stream, DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_obstacle_ObstacleRadarSequence_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_obstacle_ObstacleRadarSequence_cdr_serialize_key                                                 \
    holo_base_msg_obstacle_ObstacleRadarSequence_cdr_serialize
#define holo_base_msg_obstacle_ObstacleRadarSequence_cdr_deserialize_key                                               \
    holo_base_msg_obstacle_ObstacleRadarSequence_cdr_deserialize
#define holo_base_msg_obstacle_ObstacleRadarSequence_get_serialized_key_size                                           \
    holo_base_msg_obstacle_ObstacleRadarSequence_get_serialized_sample_size

struct holo_base_msg_obstacle_ObstacleRadarListTypePlugin;

NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_ObstacleRadarListTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_obstacle_ObstacleRadarListWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_obstacle_ObstacleRadarListReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_obstacle_ObstacleRadarListTypePlugin_get(void);
NDDSUSERDllExport extern const char* holo_base_msg_obstacle_ObstacleRadarListTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind holo_base_msg_obstacle_ObstacleRadarListI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_ObstacleRadarListPlugin_create_sample(struct DDS_TypePlugin* plugin, void** sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_ObstacleRadarListPlugin_delete_sample(struct DDS_TypePlugin* plugin, void* sample);
#endif

NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_ObstacleRadarListPlugin_copy_sample(struct DDS_TypePlugin* plugin, void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_ObstacleRadarList_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                       const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_obstacle_ObstacleRadarList_cdr_deserialize(
    struct DDS_TypePlugin* plugin, void* void_sample, struct CDR_Stream_t* stream, DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_obstacle_ObstacleRadarList_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_obstacle_ObstacleRadarList_cdr_serialize_key                                                     \
    holo_base_msg_obstacle_ObstacleRadarList_cdr_serialize
#define holo_base_msg_obstacle_ObstacleRadarList_cdr_deserialize_key                                                   \
    holo_base_msg_obstacle_ObstacleRadarList_cdr_deserialize
#define holo_base_msg_obstacle_ObstacleRadarList_get_serialized_key_size                                               \
    holo_base_msg_obstacle_ObstacleRadarList_get_serialized_sample_size

struct holo_base_msg_obstacle_ObstacleUssTypePlugin;

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_obstacle_ObstacleUssTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_obstacle_ObstacleUssWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_obstacle_ObstacleUssReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_obstacle_ObstacleUssTypePlugin_get(void);
NDDSUSERDllExport extern const char* holo_base_msg_obstacle_ObstacleUssTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind holo_base_msg_obstacle_ObstacleUssI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_obstacle_ObstacleUssPlugin_create_sample(struct DDS_TypePlugin* plugin,
                                                                                         void**                 sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_obstacle_ObstacleUssPlugin_delete_sample(struct DDS_TypePlugin* plugin,
                                                                                         void*                  sample);
#endif

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_obstacle_ObstacleUssPlugin_copy_sample(struct DDS_TypePlugin* plugin,
                                                                                       void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_obstacle_ObstacleUss_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                   struct CDR_Stream_t*   stream,
                                                                                   const void*            void_sample,
                                                                                   DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_obstacle_ObstacleUss_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                     void*                  void_sample,
                                                                                     struct CDR_Stream_t*   stream,
                                                                                     DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_obstacle_ObstacleUss_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_obstacle_ObstacleUss_cdr_serialize_key holo_base_msg_obstacle_ObstacleUss_cdr_serialize
#define holo_base_msg_obstacle_ObstacleUss_cdr_deserialize_key holo_base_msg_obstacle_ObstacleUss_cdr_deserialize
#define holo_base_msg_obstacle_ObstacleUss_get_serialized_key_size                                                     \
    holo_base_msg_obstacle_ObstacleUss_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_ObstacleUssSequence_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                         const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_obstacle_ObstacleUssSequence_cdr_deserialize(
    struct DDS_TypePlugin* plugin, void* void_sample, struct CDR_Stream_t* stream, DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_obstacle_ObstacleUssSequence_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_obstacle_ObstacleUssSequence_cdr_serialize_key                                                   \
    holo_base_msg_obstacle_ObstacleUssSequence_cdr_serialize
#define holo_base_msg_obstacle_ObstacleUssSequence_cdr_deserialize_key                                                 \
    holo_base_msg_obstacle_ObstacleUssSequence_cdr_deserialize
#define holo_base_msg_obstacle_ObstacleUssSequence_get_serialized_key_size                                             \
    holo_base_msg_obstacle_ObstacleUssSequence_get_serialized_sample_size

struct holo_base_msg_obstacle_ObstacleUssListTypePlugin;

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_obstacle_ObstacleUssListTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_obstacle_ObstacleUssListWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_obstacle_ObstacleUssListReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_obstacle_ObstacleUssListTypePlugin_get(void);
NDDSUSERDllExport extern const char* holo_base_msg_obstacle_ObstacleUssListTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind holo_base_msg_obstacle_ObstacleUssListI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_ObstacleUssListPlugin_create_sample(struct DDS_TypePlugin* plugin, void** sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_ObstacleUssListPlugin_delete_sample(struct DDS_TypePlugin* plugin, void* sample);
#endif

NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_ObstacleUssListPlugin_copy_sample(struct DDS_TypePlugin* plugin, void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_ObstacleUssList_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                     const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_obstacle_ObstacleUssList_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                         void* void_sample,
                                                                                         struct CDR_Stream_t*  stream,
                                                                                         DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_obstacle_ObstacleUssList_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_obstacle_ObstacleUssList_cdr_serialize_key holo_base_msg_obstacle_ObstacleUssList_cdr_serialize
#define holo_base_msg_obstacle_ObstacleUssList_cdr_deserialize_key                                                     \
    holo_base_msg_obstacle_ObstacleUssList_cdr_deserialize
#define holo_base_msg_obstacle_ObstacleUssList_get_serialized_key_size                                                 \
    holo_base_msg_obstacle_ObstacleUssList_get_serialized_sample_size

struct holo_base_msg_obstacle_ObstacleVisionTypePlugin;

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_obstacle_ObstacleVisionTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_obstacle_ObstacleVisionWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_obstacle_ObstacleVisionReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_obstacle_ObstacleVisionTypePlugin_get(void);
NDDSUSERDllExport extern const char* holo_base_msg_obstacle_ObstacleVisionTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind holo_base_msg_obstacle_ObstacleVisionI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_ObstacleVisionPlugin_create_sample(struct DDS_TypePlugin* plugin, void** sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_ObstacleVisionPlugin_delete_sample(struct DDS_TypePlugin* plugin, void* sample);
#endif

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_obstacle_ObstacleVisionPlugin_copy_sample(struct DDS_TypePlugin* plugin,
                                                                                          void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_ObstacleVision_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                    const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_obstacle_ObstacleVision_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                        void* void_sample,
                                                                                        struct CDR_Stream_t*  stream,
                                                                                        DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_obstacle_ObstacleVision_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_obstacle_ObstacleVision_cdr_serialize_key holo_base_msg_obstacle_ObstacleVision_cdr_serialize
#define holo_base_msg_obstacle_ObstacleVision_cdr_deserialize_key holo_base_msg_obstacle_ObstacleVision_cdr_deserialize
#define holo_base_msg_obstacle_ObstacleVision_get_serialized_key_size                                                  \
    holo_base_msg_obstacle_ObstacleVision_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_ObstacleVisionSequence_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                            const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_obstacle_ObstacleVisionSequence_cdr_deserialize(
    struct DDS_TypePlugin* plugin, void* void_sample, struct CDR_Stream_t* stream, DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_obstacle_ObstacleVisionSequence_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_obstacle_ObstacleVisionSequence_cdr_serialize_key                                                \
    holo_base_msg_obstacle_ObstacleVisionSequence_cdr_serialize
#define holo_base_msg_obstacle_ObstacleVisionSequence_cdr_deserialize_key                                              \
    holo_base_msg_obstacle_ObstacleVisionSequence_cdr_deserialize
#define holo_base_msg_obstacle_ObstacleVisionSequence_get_serialized_key_size                                          \
    holo_base_msg_obstacle_ObstacleVisionSequence_get_serialized_sample_size

struct holo_base_msg_obstacle_ObstacleVisionListTypePlugin;

NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_ObstacleVisionListTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_obstacle_ObstacleVisionListWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_obstacle_ObstacleVisionListReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_obstacle_ObstacleVisionListTypePlugin_get(void);
NDDSUSERDllExport extern const char* holo_base_msg_obstacle_ObstacleVisionListTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind holo_base_msg_obstacle_ObstacleVisionListI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_ObstacleVisionListPlugin_create_sample(struct DDS_TypePlugin* plugin, void** sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_ObstacleVisionListPlugin_delete_sample(struct DDS_TypePlugin* plugin, void* sample);
#endif

NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_ObstacleVisionListPlugin_copy_sample(struct DDS_TypePlugin* plugin, void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_obstacle_ObstacleVisionList_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                        const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_obstacle_ObstacleVisionList_cdr_deserialize(
    struct DDS_TypePlugin* plugin, void* void_sample, struct CDR_Stream_t* stream, DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_obstacle_ObstacleVisionList_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_obstacle_ObstacleVisionList_cdr_serialize_key                                                    \
    holo_base_msg_obstacle_ObstacleVisionList_cdr_serialize
#define holo_base_msg_obstacle_ObstacleVisionList_cdr_deserialize_key                                                  \
    holo_base_msg_obstacle_ObstacleVisionList_cdr_deserialize
#define holo_base_msg_obstacle_ObstacleVisionList_get_serialized_key_size                                              \
    holo_base_msg_obstacle_ObstacleVisionList_get_serialized_sample_size

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* ObstacleSetPlugin_406046225_h */
