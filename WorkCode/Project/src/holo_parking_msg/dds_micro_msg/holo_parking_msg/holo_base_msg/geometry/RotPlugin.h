/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Rot.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef RotPlugin_1247671481_h
#define RotPlugin_1247671481_h

#include "Rot.h"

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#include "holo_parking_msg/holo_base_msg/core/TypesPlugin.h"

struct holo_base_msg_geometry_Rot2fTypePlugin;

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_geometry_Rot2fTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_geometry_Rot2fWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_geometry_Rot2fReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_geometry_Rot2fTypePlugin_get(void);
NDDSUSERDllExport extern const char*             holo_base_msg_geometry_Rot2fTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind  holo_base_msg_geometry_Rot2fI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_geometry_Rot2fPlugin_create_sample(struct DDS_TypePlugin* plugin,
                                                                                   void**                 sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_geometry_Rot2fPlugin_delete_sample(struct DDS_TypePlugin* plugin,
                                                                                   void*                  sample);
#endif

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_geometry_Rot2fPlugin_copy_sample(struct DDS_TypePlugin* plugin,
                                                                                 void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_geometry_Rot2f_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                             struct CDR_Stream_t*   stream,
                                                                             const void*            void_sample,
                                                                             DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_geometry_Rot2f_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                               void*                  void_sample,
                                                                               struct CDR_Stream_t*   stream,
                                                                               DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_geometry_Rot2f_get_serialized_sample_size(struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_geometry_Rot2f_cdr_serialize_key holo_base_msg_geometry_Rot2f_cdr_serialize
#define holo_base_msg_geometry_Rot2f_cdr_deserialize_key holo_base_msg_geometry_Rot2f_cdr_deserialize
#define holo_base_msg_geometry_Rot2f_get_serialized_key_size holo_base_msg_geometry_Rot2f_get_serialized_sample_size

struct holo_base_msg_geometry_Rot2dTypePlugin;

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_geometry_Rot2dTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_geometry_Rot2dWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_geometry_Rot2dReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_geometry_Rot2dTypePlugin_get(void);
NDDSUSERDllExport extern const char*             holo_base_msg_geometry_Rot2dTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind  holo_base_msg_geometry_Rot2dI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_geometry_Rot2dPlugin_create_sample(struct DDS_TypePlugin* plugin,
                                                                                   void**                 sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_geometry_Rot2dPlugin_delete_sample(struct DDS_TypePlugin* plugin,
                                                                                   void*                  sample);
#endif

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_geometry_Rot2dPlugin_copy_sample(struct DDS_TypePlugin* plugin,
                                                                                 void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_geometry_Rot2d_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                             struct CDR_Stream_t*   stream,
                                                                             const void*            void_sample,
                                                                             DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_geometry_Rot2d_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                               void*                  void_sample,
                                                                               struct CDR_Stream_t*   stream,
                                                                               DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_geometry_Rot2d_get_serialized_sample_size(struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_geometry_Rot2d_cdr_serialize_key holo_base_msg_geometry_Rot2d_cdr_serialize
#define holo_base_msg_geometry_Rot2d_cdr_deserialize_key holo_base_msg_geometry_Rot2d_cdr_deserialize
#define holo_base_msg_geometry_Rot2d_get_serialized_key_size holo_base_msg_geometry_Rot2d_get_serialized_sample_size

struct holo_base_msg_geometry_Rot3fTypePlugin;

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_geometry_Rot3fTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_geometry_Rot3fWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_geometry_Rot3fReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_geometry_Rot3fTypePlugin_get(void);
NDDSUSERDllExport extern const char*             holo_base_msg_geometry_Rot3fTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind  holo_base_msg_geometry_Rot3fI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_geometry_Rot3fPlugin_create_sample(struct DDS_TypePlugin* plugin,
                                                                                   void**                 sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_geometry_Rot3fPlugin_delete_sample(struct DDS_TypePlugin* plugin,
                                                                                   void*                  sample);
#endif

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_geometry_Rot3fPlugin_copy_sample(struct DDS_TypePlugin* plugin,
                                                                                 void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_geometry_Rot3f_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                             struct CDR_Stream_t*   stream,
                                                                             const void*            void_sample,
                                                                             DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_geometry_Rot3f_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                               void*                  void_sample,
                                                                               struct CDR_Stream_t*   stream,
                                                                               DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_geometry_Rot3f_get_serialized_sample_size(struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_geometry_Rot3f_cdr_serialize_key holo_base_msg_geometry_Rot3f_cdr_serialize
#define holo_base_msg_geometry_Rot3f_cdr_deserialize_key holo_base_msg_geometry_Rot3f_cdr_deserialize
#define holo_base_msg_geometry_Rot3f_get_serialized_key_size holo_base_msg_geometry_Rot3f_get_serialized_sample_size

struct holo_base_msg_geometry_Rot3dTypePlugin;

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_geometry_Rot3dTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_geometry_Rot3dWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_geometry_Rot3dReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_geometry_Rot3dTypePlugin_get(void);
NDDSUSERDllExport extern const char*             holo_base_msg_geometry_Rot3dTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind  holo_base_msg_geometry_Rot3dI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_geometry_Rot3dPlugin_create_sample(struct DDS_TypePlugin* plugin,
                                                                                   void**                 sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_geometry_Rot3dPlugin_delete_sample(struct DDS_TypePlugin* plugin,
                                                                                   void*                  sample);
#endif

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_geometry_Rot3dPlugin_copy_sample(struct DDS_TypePlugin* plugin,
                                                                                 void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_geometry_Rot3d_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                             struct CDR_Stream_t*   stream,
                                                                             const void*            void_sample,
                                                                             DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_geometry_Rot3d_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                               void*                  void_sample,
                                                                               struct CDR_Stream_t*   stream,
                                                                               DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_geometry_Rot3d_get_serialized_sample_size(struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_geometry_Rot3d_cdr_serialize_key holo_base_msg_geometry_Rot3d_cdr_serialize
#define holo_base_msg_geometry_Rot3d_cdr_deserialize_key holo_base_msg_geometry_Rot3d_cdr_deserialize
#define holo_base_msg_geometry_Rot3d_get_serialized_key_size holo_base_msg_geometry_Rot3d_get_serialized_sample_size

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* RotPlugin_1247671481_h */
