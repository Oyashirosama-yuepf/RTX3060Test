/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from PointCloudGeneral.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef PointCloudGeneralPlugin_963373545_h
#define PointCloudGeneralPlugin_963373545_h

#include "PointCloudGeneral.h"

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#include "holo_parking_msg/holo_base_msg/common/CommonPlugin.h"

#include "holo_parking_msg/holo_base_msg/core/TypesPlugin.h"

#include "holo_parking_msg/holo_base_msg/geometry/PosePlugin.h"

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_float32_t_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                               struct CDR_Stream_t*   stream,
                                                                               const void*            void_sample,
                                                                               DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_float32_t_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                 void*                  void_sample,
                                                                                 struct CDR_Stream_t*   stream,
                                                                                 DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_common_float32_t_get_serialized_sample_size(struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_common_float32_t_cdr_serialize_key holo_base_msg_common_float32_t_cdr_serialize
#define holo_base_msg_common_float32_t_cdr_deserialize_key holo_base_msg_common_float32_t_cdr_deserialize
#define holo_base_msg_common_float32_t_get_serialized_key_size holo_base_msg_common_float32_t_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_bool_t_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                            struct CDR_Stream_t*   stream,
                                                                            const void*            void_sample,
                                                                            DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_bool_t_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                              void*                  void_sample,
                                                                              struct CDR_Stream_t*   stream,
                                                                              DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_common_bool_t_get_serialized_sample_size(struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_common_bool_t_cdr_serialize_key holo_base_msg_common_bool_t_cdr_serialize
#define holo_base_msg_common_bool_t_cdr_deserialize_key holo_base_msg_common_bool_t_cdr_deserialize
#define holo_base_msg_common_bool_t_get_serialized_key_size holo_base_msg_common_bool_t_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_uint8_t_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                             struct CDR_Stream_t*   stream,
                                                                             const void*            void_sample,
                                                                             DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_uint8_t_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                               void*                  void_sample,
                                                                               struct CDR_Stream_t*   stream,
                                                                               DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_common_uint8_t_get_serialized_sample_size(struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_common_uint8_t_cdr_serialize_key holo_base_msg_common_uint8_t_cdr_serialize
#define holo_base_msg_common_uint8_t_cdr_deserialize_key holo_base_msg_common_uint8_t_cdr_deserialize
#define holo_base_msg_common_uint8_t_get_serialized_key_size holo_base_msg_common_uint8_t_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_uint64_t_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                              struct CDR_Stream_t*   stream,
                                                                              const void*            void_sample,
                                                                              DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_uint64_t_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                void*                  void_sample,
                                                                                struct CDR_Stream_t*   stream,
                                                                                DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_common_uint64_t_get_serialized_sample_size(struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_common_uint64_t_cdr_serialize_key holo_base_msg_common_uint64_t_cdr_serialize
#define holo_base_msg_common_uint64_t_cdr_deserialize_key holo_base_msg_common_uint64_t_cdr_deserialize
#define holo_base_msg_common_uint64_t_get_serialized_key_size holo_base_msg_common_uint64_t_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_Pose_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                          struct CDR_Stream_t*   stream,
                                                                          const void*            void_sample,
                                                                          DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_Pose_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                            void*                  void_sample,
                                                                            struct CDR_Stream_t*   stream,
                                                                            DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_common_Pose_get_serialized_sample_size(struct DDS_TypePlugin* plugin,
                                                                                         RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_common_Pose_cdr_serialize_key holo_base_msg_common_Pose_cdr_serialize
#define holo_base_msg_common_Pose_cdr_deserialize_key holo_base_msg_common_Pose_cdr_deserialize
#define holo_base_msg_common_Pose_get_serialized_key_size holo_base_msg_common_Pose_get_serialized_sample_size

struct holo_base_msg_common_PointXYZRGBTypePlugin;

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_PointXYZRGBTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_PointXYZRGBWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_PointXYZRGBReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_common_PointXYZRGBTypePlugin_get(void);
NDDSUSERDllExport extern const char*             holo_base_msg_common_PointXYZRGBTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind  holo_base_msg_common_PointXYZRGBI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_PointXYZRGBPlugin_create_sample(struct DDS_TypePlugin* plugin,
                                                                                       void**                 sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_PointXYZRGBPlugin_delete_sample(struct DDS_TypePlugin* plugin,
                                                                                       void*                  sample);
#endif

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_PointXYZRGBPlugin_copy_sample(struct DDS_TypePlugin* plugin,
                                                                                     void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_PointXYZRGB_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                 struct CDR_Stream_t*   stream,
                                                                                 const void*            void_sample,
                                                                                 DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_PointXYZRGB_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                   void*                  void_sample,
                                                                                   struct CDR_Stream_t*   stream,
                                                                                   DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_common_PointXYZRGB_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_common_PointXYZRGB_cdr_serialize_key holo_base_msg_common_PointXYZRGB_cdr_serialize
#define holo_base_msg_common_PointXYZRGB_cdr_deserialize_key holo_base_msg_common_PointXYZRGB_cdr_deserialize
#define holo_base_msg_common_PointXYZRGB_get_serialized_key_size                                                       \
    holo_base_msg_common_PointXYZRGB_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_PointXYZRGBSeqTypeDef_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                         const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_PointXYZRGBSeqTypeDef_cdr_deserialize(
    struct DDS_TypePlugin* plugin, void* void_sample, struct CDR_Stream_t* stream, DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_common_PointXYZRGBSeqTypeDef_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_common_PointXYZRGBSeqTypeDef_cdr_serialize_key                                                   \
    holo_base_msg_common_PointXYZRGBSeqTypeDef_cdr_serialize
#define holo_base_msg_common_PointXYZRGBSeqTypeDef_cdr_deserialize_key                                                 \
    holo_base_msg_common_PointXYZRGBSeqTypeDef_cdr_deserialize
#define holo_base_msg_common_PointXYZRGBSeqTypeDef_get_serialized_key_size                                             \
    holo_base_msg_common_PointXYZRGBSeqTypeDef_get_serialized_sample_size

struct holo_base_msg_common_PointCloudGeneralTypePlugin;

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_PointCloudGeneralTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_PointCloudGeneralWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_PointCloudGeneralReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_common_PointCloudGeneralTypePlugin_get(void);
NDDSUSERDllExport extern const char* holo_base_msg_common_PointCloudGeneralTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind holo_base_msg_common_PointCloudGeneralI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_PointCloudGeneralPlugin_create_sample(struct DDS_TypePlugin* plugin, void** sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_PointCloudGeneralPlugin_delete_sample(struct DDS_TypePlugin* plugin, void* sample);
#endif

NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_PointCloudGeneralPlugin_copy_sample(struct DDS_TypePlugin* plugin, void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_PointCloudGeneral_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                     const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_PointCloudGeneral_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                         void* void_sample,
                                                                                         struct CDR_Stream_t*  stream,
                                                                                         DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_common_PointCloudGeneral_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_common_PointCloudGeneral_cdr_serialize_key holo_base_msg_common_PointCloudGeneral_cdr_serialize
#define holo_base_msg_common_PointCloudGeneral_cdr_deserialize_key                                                     \
    holo_base_msg_common_PointCloudGeneral_cdr_deserialize
#define holo_base_msg_common_PointCloudGeneral_get_serialized_key_size                                                 \
    holo_base_msg_common_PointCloudGeneral_get_serialized_sample_size

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* PointCloudGeneralPlugin_963373545_h */
