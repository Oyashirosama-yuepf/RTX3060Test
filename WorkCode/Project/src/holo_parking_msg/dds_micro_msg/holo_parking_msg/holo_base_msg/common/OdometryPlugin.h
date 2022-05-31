/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Odometry.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef OdometryPlugin_1402263134_h
#define OdometryPlugin_1402263134_h

#include "Odometry.h"

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#include "holo_parking_msg/holo_base_msg/common/CommonPlugin.h"

#include "holo_parking_msg/holo_base_msg/geometry/PosePlugin.h"

#include "holo_parking_msg/holo_base_msg/numerics/VectorPlugin.h"

#include "holo_parking_msg/holo_base_msg/numerics/MatrixPlugin.h"

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_OdometrySource_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                    struct CDR_Stream_t*   stream,
                                                                                    const void*            void_sample,
                                                                                    DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_OdometrySource_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                      void*                 void_sample,
                                                                                      struct CDR_Stream_t*  stream,
                                                                                      DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_common_OdometrySource_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_common_OdometrySource_cdr_serialize_key holo_base_msg_common_OdometrySource_cdr_serialize
#define holo_base_msg_common_OdometrySource_cdr_deserialize_key holo_base_msg_common_OdometrySource_cdr_deserialize
#define holo_base_msg_common_OdometrySource_get_serialized_key_size                                                    \
    holo_base_msg_common_OdometrySource_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_OdometryStatus_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                    struct CDR_Stream_t*   stream,
                                                                                    const void*            void_sample,
                                                                                    DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_OdometryStatus_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                      void*                 void_sample,
                                                                                      struct CDR_Stream_t*  stream,
                                                                                      DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_common_OdometryStatus_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_common_OdometryStatus_cdr_serialize_key holo_base_msg_common_OdometryStatus_cdr_serialize
#define holo_base_msg_common_OdometryStatus_cdr_deserialize_key holo_base_msg_common_OdometryStatus_cdr_deserialize
#define holo_base_msg_common_OdometryStatus_get_serialized_key_size                                                    \
    holo_base_msg_common_OdometryStatus_get_serialized_sample_size

struct holo_base_msg_common_OdometryfTypePlugin;

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_OdometryfTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_OdometryfWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_OdometryfReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_common_OdometryfTypePlugin_get(void);
NDDSUSERDllExport extern const char*             holo_base_msg_common_OdometryfTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind  holo_base_msg_common_OdometryfI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_OdometryfPlugin_create_sample(struct DDS_TypePlugin* plugin,
                                                                                     void**                 sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_OdometryfPlugin_delete_sample(struct DDS_TypePlugin* plugin,
                                                                                     void*                  sample);
#endif

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_OdometryfPlugin_copy_sample(struct DDS_TypePlugin* plugin,
                                                                                   void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_Odometryf_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                               struct CDR_Stream_t*   stream,
                                                                               const void*            void_sample,
                                                                               DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_Odometryf_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                 void*                  void_sample,
                                                                                 struct CDR_Stream_t*   stream,
                                                                                 DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_common_Odometryf_get_serialized_sample_size(struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_common_Odometryf_cdr_serialize_key holo_base_msg_common_Odometryf_cdr_serialize
#define holo_base_msg_common_Odometryf_cdr_deserialize_key holo_base_msg_common_Odometryf_cdr_deserialize
#define holo_base_msg_common_Odometryf_get_serialized_key_size holo_base_msg_common_Odometryf_get_serialized_sample_size

struct holo_base_msg_common_OdometrydTypePlugin;

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_OdometrydTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_OdometrydWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_OdometrydReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_common_OdometrydTypePlugin_get(void);
NDDSUSERDllExport extern const char*             holo_base_msg_common_OdometrydTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind  holo_base_msg_common_OdometrydI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_OdometrydPlugin_create_sample(struct DDS_TypePlugin* plugin,
                                                                                     void**                 sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_OdometrydPlugin_delete_sample(struct DDS_TypePlugin* plugin,
                                                                                     void*                  sample);
#endif

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_OdometrydPlugin_copy_sample(struct DDS_TypePlugin* plugin,
                                                                                   void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_Odometryd_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                               struct CDR_Stream_t*   stream,
                                                                               const void*            void_sample,
                                                                               DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_Odometryd_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                 void*                  void_sample,
                                                                                 struct CDR_Stream_t*   stream,
                                                                                 DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_common_Odometryd_get_serialized_sample_size(struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_common_Odometryd_cdr_serialize_key holo_base_msg_common_Odometryd_cdr_serialize
#define holo_base_msg_common_Odometryd_cdr_deserialize_key holo_base_msg_common_Odometryd_cdr_deserialize
#define holo_base_msg_common_Odometryd_get_serialized_key_size holo_base_msg_common_Odometryd_get_serialized_sample_size

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* OdometryPlugin_1402263134_h */
