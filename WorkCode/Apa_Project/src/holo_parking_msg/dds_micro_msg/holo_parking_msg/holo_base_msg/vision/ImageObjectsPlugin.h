/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ImageObjects.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef ImageObjectsPlugin_1109333664_h
#define ImageObjectsPlugin_1109333664_h

#include "ImageObjects.h"

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#include "holo_parking_msg/holo_base_msg/core/TypesPlugin.h"

#include "holo_parking_msg/holo_base_msg/core/TypesPlugin.h"

#include "holo_parking_msg/holo_base_msg/common/CommonPlugin.h"

#include "holo_parking_msg/holo_base_msg/geometry/PointPlugin.h"

struct holo_base_msg_vision_KeyPoint2dTypePlugin;

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_KeyPoint2dTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_vision_KeyPoint2dWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_vision_KeyPoint2dReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_vision_KeyPoint2dTypePlugin_get(void);
NDDSUSERDllExport extern const char*             holo_base_msg_vision_KeyPoint2dTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind  holo_base_msg_vision_KeyPoint2dI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_KeyPoint2dPlugin_create_sample(struct DDS_TypePlugin* plugin,
                                                                                      void**                 sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_KeyPoint2dPlugin_delete_sample(struct DDS_TypePlugin* plugin,
                                                                                      void*                  sample);
#endif

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_KeyPoint2dPlugin_copy_sample(struct DDS_TypePlugin* plugin,
                                                                                    void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_KeyPoint2d_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                struct CDR_Stream_t*   stream,
                                                                                const void*            void_sample,
                                                                                DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_KeyPoint2d_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                  void*                  void_sample,
                                                                                  struct CDR_Stream_t*   stream,
                                                                                  DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_vision_KeyPoint2d_get_serialized_sample_size(struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_vision_KeyPoint2d_cdr_serialize_key holo_base_msg_vision_KeyPoint2d_cdr_serialize
#define holo_base_msg_vision_KeyPoint2d_cdr_deserialize_key holo_base_msg_vision_KeyPoint2d_cdr_deserialize
#define holo_base_msg_vision_KeyPoint2d_get_serialized_key_size                                                        \
    holo_base_msg_vision_KeyPoint2d_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_KeyPoint2dSequence_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                      const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_KeyPoint2dSequence_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                          void* void_sample,
                                                                                          struct CDR_Stream_t*  stream,
                                                                                          DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_vision_KeyPoint2dSequence_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_vision_KeyPoint2dSequence_cdr_serialize_key holo_base_msg_vision_KeyPoint2dSequence_cdr_serialize
#define holo_base_msg_vision_KeyPoint2dSequence_cdr_deserialize_key                                                    \
    holo_base_msg_vision_KeyPoint2dSequence_cdr_deserialize
#define holo_base_msg_vision_KeyPoint2dSequence_get_serialized_key_size                                                \
    holo_base_msg_vision_KeyPoint2dSequence_get_serialized_sample_size

struct holo_base_msg_vision_KeyPoint2fTypePlugin;

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_KeyPoint2fTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_vision_KeyPoint2fWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_vision_KeyPoint2fReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_vision_KeyPoint2fTypePlugin_get(void);
NDDSUSERDllExport extern const char*             holo_base_msg_vision_KeyPoint2fTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind  holo_base_msg_vision_KeyPoint2fI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_KeyPoint2fPlugin_create_sample(struct DDS_TypePlugin* plugin,
                                                                                      void**                 sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_KeyPoint2fPlugin_delete_sample(struct DDS_TypePlugin* plugin,
                                                                                      void*                  sample);
#endif

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_KeyPoint2fPlugin_copy_sample(struct DDS_TypePlugin* plugin,
                                                                                    void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_KeyPoint2f_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                struct CDR_Stream_t*   stream,
                                                                                const void*            void_sample,
                                                                                DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_KeyPoint2f_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                  void*                  void_sample,
                                                                                  struct CDR_Stream_t*   stream,
                                                                                  DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_vision_KeyPoint2f_get_serialized_sample_size(struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_vision_KeyPoint2f_cdr_serialize_key holo_base_msg_vision_KeyPoint2f_cdr_serialize
#define holo_base_msg_vision_KeyPoint2f_cdr_deserialize_key holo_base_msg_vision_KeyPoint2f_cdr_deserialize
#define holo_base_msg_vision_KeyPoint2f_get_serialized_key_size                                                        \
    holo_base_msg_vision_KeyPoint2f_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_KeyPoint2fSequence_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                      const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_KeyPoint2fSequence_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                          void* void_sample,
                                                                                          struct CDR_Stream_t*  stream,
                                                                                          DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_vision_KeyPoint2fSequence_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_vision_KeyPoint2fSequence_cdr_serialize_key holo_base_msg_vision_KeyPoint2fSequence_cdr_serialize
#define holo_base_msg_vision_KeyPoint2fSequence_cdr_deserialize_key                                                    \
    holo_base_msg_vision_KeyPoint2fSequence_cdr_deserialize
#define holo_base_msg_vision_KeyPoint2fSequence_get_serialized_key_size                                                \
    holo_base_msg_vision_KeyPoint2fSequence_get_serialized_sample_size

struct holo_base_msg_vision_ObjectKeyPoint2dTypePlugin;

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectKeyPoint2dTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_vision_ObjectKeyPoint2dWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_vision_ObjectKeyPoint2dReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_vision_ObjectKeyPoint2dTypePlugin_get(void);
NDDSUSERDllExport extern const char* holo_base_msg_vision_ObjectKeyPoint2dTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind holo_base_msg_vision_ObjectKeyPoint2dI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ObjectKeyPoint2dPlugin_create_sample(struct DDS_TypePlugin* plugin, void** sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ObjectKeyPoint2dPlugin_delete_sample(struct DDS_TypePlugin* plugin, void* sample);
#endif

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectKeyPoint2dPlugin_copy_sample(struct DDS_TypePlugin* plugin,
                                                                                          void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ObjectKeyPoint2d_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                    const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectKeyPoint2d_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                        void* void_sample,
                                                                                        struct CDR_Stream_t*  stream,
                                                                                        DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_vision_ObjectKeyPoint2d_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_vision_ObjectKeyPoint2d_cdr_serialize_key holo_base_msg_vision_ObjectKeyPoint2d_cdr_serialize
#define holo_base_msg_vision_ObjectKeyPoint2d_cdr_deserialize_key holo_base_msg_vision_ObjectKeyPoint2d_cdr_deserialize
#define holo_base_msg_vision_ObjectKeyPoint2d_get_serialized_key_size                                                  \
    holo_base_msg_vision_ObjectKeyPoint2d_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ObjectKeyPoint2dSequence_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                            const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectKeyPoint2dSequence_cdr_deserialize(
    struct DDS_TypePlugin* plugin, void* void_sample, struct CDR_Stream_t* stream, DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_vision_ObjectKeyPoint2dSequence_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_vision_ObjectKeyPoint2dSequence_cdr_serialize_key                                                \
    holo_base_msg_vision_ObjectKeyPoint2dSequence_cdr_serialize
#define holo_base_msg_vision_ObjectKeyPoint2dSequence_cdr_deserialize_key                                              \
    holo_base_msg_vision_ObjectKeyPoint2dSequence_cdr_deserialize
#define holo_base_msg_vision_ObjectKeyPoint2dSequence_get_serialized_key_size                                          \
    holo_base_msg_vision_ObjectKeyPoint2dSequence_get_serialized_sample_size

struct holo_base_msg_vision_ObjectKeyPoint2fTypePlugin;

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectKeyPoint2fTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_vision_ObjectKeyPoint2fWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_vision_ObjectKeyPoint2fReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_vision_ObjectKeyPoint2fTypePlugin_get(void);
NDDSUSERDllExport extern const char* holo_base_msg_vision_ObjectKeyPoint2fTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind holo_base_msg_vision_ObjectKeyPoint2fI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ObjectKeyPoint2fPlugin_create_sample(struct DDS_TypePlugin* plugin, void** sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ObjectKeyPoint2fPlugin_delete_sample(struct DDS_TypePlugin* plugin, void* sample);
#endif

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectKeyPoint2fPlugin_copy_sample(struct DDS_TypePlugin* plugin,
                                                                                          void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ObjectKeyPoint2f_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                    const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectKeyPoint2f_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                        void* void_sample,
                                                                                        struct CDR_Stream_t*  stream,
                                                                                        DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_vision_ObjectKeyPoint2f_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_vision_ObjectKeyPoint2f_cdr_serialize_key holo_base_msg_vision_ObjectKeyPoint2f_cdr_serialize
#define holo_base_msg_vision_ObjectKeyPoint2f_cdr_deserialize_key holo_base_msg_vision_ObjectKeyPoint2f_cdr_deserialize
#define holo_base_msg_vision_ObjectKeyPoint2f_get_serialized_key_size                                                  \
    holo_base_msg_vision_ObjectKeyPoint2f_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ObjectKeyPoint2fSequence_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                            const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectKeyPoint2fSequence_cdr_deserialize(
    struct DDS_TypePlugin* plugin, void* void_sample, struct CDR_Stream_t* stream, DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_vision_ObjectKeyPoint2fSequence_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_vision_ObjectKeyPoint2fSequence_cdr_serialize_key                                                \
    holo_base_msg_vision_ObjectKeyPoint2fSequence_cdr_serialize
#define holo_base_msg_vision_ObjectKeyPoint2fSequence_cdr_deserialize_key                                              \
    holo_base_msg_vision_ObjectKeyPoint2fSequence_cdr_deserialize
#define holo_base_msg_vision_ObjectKeyPoint2fSequence_get_serialized_key_size                                          \
    holo_base_msg_vision_ObjectKeyPoint2fSequence_get_serialized_sample_size

struct holo_base_msg_vision_ObjectPoint2dTypePlugin;

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectPoint2dTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_vision_ObjectPoint2dWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_vision_ObjectPoint2dReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_vision_ObjectPoint2dTypePlugin_get(void);
NDDSUSERDllExport extern const char* holo_base_msg_vision_ObjectPoint2dTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind holo_base_msg_vision_ObjectPoint2dI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectPoint2dPlugin_create_sample(struct DDS_TypePlugin* plugin,
                                                                                         void**                 sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectPoint2dPlugin_delete_sample(struct DDS_TypePlugin* plugin,
                                                                                         void*                  sample);
#endif

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectPoint2dPlugin_copy_sample(struct DDS_TypePlugin* plugin,
                                                                                       void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectPoint2d_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                   struct CDR_Stream_t*   stream,
                                                                                   const void*            void_sample,
                                                                                   DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectPoint2d_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                     void*                  void_sample,
                                                                                     struct CDR_Stream_t*   stream,
                                                                                     DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_vision_ObjectPoint2d_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_vision_ObjectPoint2d_cdr_serialize_key holo_base_msg_vision_ObjectPoint2d_cdr_serialize
#define holo_base_msg_vision_ObjectPoint2d_cdr_deserialize_key holo_base_msg_vision_ObjectPoint2d_cdr_deserialize
#define holo_base_msg_vision_ObjectPoint2d_get_serialized_key_size                                                     \
    holo_base_msg_vision_ObjectPoint2d_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ObjectPoint2dSequence_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                         const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectPoint2dSequence_cdr_deserialize(
    struct DDS_TypePlugin* plugin, void* void_sample, struct CDR_Stream_t* stream, DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_vision_ObjectPoint2dSequence_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_vision_ObjectPoint2dSequence_cdr_serialize_key                                                   \
    holo_base_msg_vision_ObjectPoint2dSequence_cdr_serialize
#define holo_base_msg_vision_ObjectPoint2dSequence_cdr_deserialize_key                                                 \
    holo_base_msg_vision_ObjectPoint2dSequence_cdr_deserialize
#define holo_base_msg_vision_ObjectPoint2dSequence_get_serialized_key_size                                             \
    holo_base_msg_vision_ObjectPoint2dSequence_get_serialized_sample_size

struct holo_base_msg_vision_ObjectPoint2fTypePlugin;

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectPoint2fTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_vision_ObjectPoint2fWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_vision_ObjectPoint2fReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_vision_ObjectPoint2fTypePlugin_get(void);
NDDSUSERDllExport extern const char* holo_base_msg_vision_ObjectPoint2fTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind holo_base_msg_vision_ObjectPoint2fI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectPoint2fPlugin_create_sample(struct DDS_TypePlugin* plugin,
                                                                                         void**                 sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectPoint2fPlugin_delete_sample(struct DDS_TypePlugin* plugin,
                                                                                         void*                  sample);
#endif

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectPoint2fPlugin_copy_sample(struct DDS_TypePlugin* plugin,
                                                                                       void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectPoint2f_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                   struct CDR_Stream_t*   stream,
                                                                                   const void*            void_sample,
                                                                                   DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectPoint2f_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                     void*                  void_sample,
                                                                                     struct CDR_Stream_t*   stream,
                                                                                     DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_vision_ObjectPoint2f_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_vision_ObjectPoint2f_cdr_serialize_key holo_base_msg_vision_ObjectPoint2f_cdr_serialize
#define holo_base_msg_vision_ObjectPoint2f_cdr_deserialize_key holo_base_msg_vision_ObjectPoint2f_cdr_deserialize
#define holo_base_msg_vision_ObjectPoint2f_get_serialized_key_size                                                     \
    holo_base_msg_vision_ObjectPoint2f_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ObjectPoint2fSequence_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                         const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectPoint2fSequence_cdr_deserialize(
    struct DDS_TypePlugin* plugin, void* void_sample, struct CDR_Stream_t* stream, DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_vision_ObjectPoint2fSequence_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_vision_ObjectPoint2fSequence_cdr_serialize_key                                                   \
    holo_base_msg_vision_ObjectPoint2fSequence_cdr_serialize
#define holo_base_msg_vision_ObjectPoint2fSequence_cdr_deserialize_key                                                 \
    holo_base_msg_vision_ObjectPoint2fSequence_cdr_deserialize
#define holo_base_msg_vision_ObjectPoint2fSequence_get_serialized_key_size                                             \
    holo_base_msg_vision_ObjectPoint2fSequence_get_serialized_sample_size

struct holo_base_msg_vision_ObjectPoint3dTypePlugin;

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectPoint3dTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_vision_ObjectPoint3dWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_vision_ObjectPoint3dReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_vision_ObjectPoint3dTypePlugin_get(void);
NDDSUSERDllExport extern const char* holo_base_msg_vision_ObjectPoint3dTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind holo_base_msg_vision_ObjectPoint3dI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectPoint3dPlugin_create_sample(struct DDS_TypePlugin* plugin,
                                                                                         void**                 sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectPoint3dPlugin_delete_sample(struct DDS_TypePlugin* plugin,
                                                                                         void*                  sample);
#endif

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectPoint3dPlugin_copy_sample(struct DDS_TypePlugin* plugin,
                                                                                       void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectPoint3d_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                   struct CDR_Stream_t*   stream,
                                                                                   const void*            void_sample,
                                                                                   DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectPoint3d_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                     void*                  void_sample,
                                                                                     struct CDR_Stream_t*   stream,
                                                                                     DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_vision_ObjectPoint3d_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_vision_ObjectPoint3d_cdr_serialize_key holo_base_msg_vision_ObjectPoint3d_cdr_serialize
#define holo_base_msg_vision_ObjectPoint3d_cdr_deserialize_key holo_base_msg_vision_ObjectPoint3d_cdr_deserialize
#define holo_base_msg_vision_ObjectPoint3d_get_serialized_key_size                                                     \
    holo_base_msg_vision_ObjectPoint3d_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ObjectPoint3dSequence_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                         const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectPoint3dSequence_cdr_deserialize(
    struct DDS_TypePlugin* plugin, void* void_sample, struct CDR_Stream_t* stream, DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_vision_ObjectPoint3dSequence_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_vision_ObjectPoint3dSequence_cdr_serialize_key                                                   \
    holo_base_msg_vision_ObjectPoint3dSequence_cdr_serialize
#define holo_base_msg_vision_ObjectPoint3dSequence_cdr_deserialize_key                                                 \
    holo_base_msg_vision_ObjectPoint3dSequence_cdr_deserialize
#define holo_base_msg_vision_ObjectPoint3dSequence_get_serialized_key_size                                             \
    holo_base_msg_vision_ObjectPoint3dSequence_get_serialized_sample_size

struct holo_base_msg_vision_ObjectPoint3fTypePlugin;

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectPoint3fTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_vision_ObjectPoint3fWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_vision_ObjectPoint3fReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_vision_ObjectPoint3fTypePlugin_get(void);
NDDSUSERDllExport extern const char* holo_base_msg_vision_ObjectPoint3fTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind holo_base_msg_vision_ObjectPoint3fI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectPoint3fPlugin_create_sample(struct DDS_TypePlugin* plugin,
                                                                                         void**                 sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectPoint3fPlugin_delete_sample(struct DDS_TypePlugin* plugin,
                                                                                         void*                  sample);
#endif

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectPoint3fPlugin_copy_sample(struct DDS_TypePlugin* plugin,
                                                                                       void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectPoint3f_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                   struct CDR_Stream_t*   stream,
                                                                                   const void*            void_sample,
                                                                                   DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectPoint3f_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                     void*                  void_sample,
                                                                                     struct CDR_Stream_t*   stream,
                                                                                     DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_vision_ObjectPoint3f_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_vision_ObjectPoint3f_cdr_serialize_key holo_base_msg_vision_ObjectPoint3f_cdr_serialize
#define holo_base_msg_vision_ObjectPoint3f_cdr_deserialize_key holo_base_msg_vision_ObjectPoint3f_cdr_deserialize
#define holo_base_msg_vision_ObjectPoint3f_get_serialized_key_size                                                     \
    holo_base_msg_vision_ObjectPoint3f_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ObjectPoint3fSequence_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                         const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ObjectPoint3fSequence_cdr_deserialize(
    struct DDS_TypePlugin* plugin, void* void_sample, struct CDR_Stream_t* stream, DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_vision_ObjectPoint3fSequence_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_vision_ObjectPoint3fSequence_cdr_serialize_key                                                   \
    holo_base_msg_vision_ObjectPoint3fSequence_cdr_serialize
#define holo_base_msg_vision_ObjectPoint3fSequence_cdr_deserialize_key                                                 \
    holo_base_msg_vision_ObjectPoint3fSequence_cdr_deserialize
#define holo_base_msg_vision_ObjectPoint3fSequence_get_serialized_key_size                                             \
    holo_base_msg_vision_ObjectPoint3fSequence_get_serialized_sample_size

struct holo_base_msg_vision_ImageObjectsKeyPoint2dTypePlugin;

NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ImageObjectsKeyPoint2dTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_vision_ImageObjectsKeyPoint2dWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_vision_ImageObjectsKeyPoint2dReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_vision_ImageObjectsKeyPoint2dTypePlugin_get(void);
NDDSUSERDllExport extern const char* holo_base_msg_vision_ImageObjectsKeyPoint2dTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind holo_base_msg_vision_ImageObjectsKeyPoint2dI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ImageObjectsKeyPoint2dPlugin_create_sample(struct DDS_TypePlugin* plugin, void** sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ImageObjectsKeyPoint2dPlugin_delete_sample(struct DDS_TypePlugin* plugin, void* sample);
#endif

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ImageObjectsKeyPoint2dPlugin_copy_sample(
    struct DDS_TypePlugin* plugin, void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ImageObjectsKeyPoint2d_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                          const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ImageObjectsKeyPoint2d_cdr_deserialize(
    struct DDS_TypePlugin* plugin, void* void_sample, struct CDR_Stream_t* stream, DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_vision_ImageObjectsKeyPoint2d_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_vision_ImageObjectsKeyPoint2d_cdr_serialize_key                                                  \
    holo_base_msg_vision_ImageObjectsKeyPoint2d_cdr_serialize
#define holo_base_msg_vision_ImageObjectsKeyPoint2d_cdr_deserialize_key                                                \
    holo_base_msg_vision_ImageObjectsKeyPoint2d_cdr_deserialize
#define holo_base_msg_vision_ImageObjectsKeyPoint2d_get_serialized_key_size                                            \
    holo_base_msg_vision_ImageObjectsKeyPoint2d_get_serialized_sample_size

struct holo_base_msg_vision_ImageObjectsKeyPoint2fTypePlugin;

NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ImageObjectsKeyPoint2fTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_vision_ImageObjectsKeyPoint2fWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_vision_ImageObjectsKeyPoint2fReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_vision_ImageObjectsKeyPoint2fTypePlugin_get(void);
NDDSUSERDllExport extern const char* holo_base_msg_vision_ImageObjectsKeyPoint2fTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind holo_base_msg_vision_ImageObjectsKeyPoint2fI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ImageObjectsKeyPoint2fPlugin_create_sample(struct DDS_TypePlugin* plugin, void** sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ImageObjectsKeyPoint2fPlugin_delete_sample(struct DDS_TypePlugin* plugin, void* sample);
#endif

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ImageObjectsKeyPoint2fPlugin_copy_sample(
    struct DDS_TypePlugin* plugin, void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ImageObjectsKeyPoint2f_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                          const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ImageObjectsKeyPoint2f_cdr_deserialize(
    struct DDS_TypePlugin* plugin, void* void_sample, struct CDR_Stream_t* stream, DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_vision_ImageObjectsKeyPoint2f_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_vision_ImageObjectsKeyPoint2f_cdr_serialize_key                                                  \
    holo_base_msg_vision_ImageObjectsKeyPoint2f_cdr_serialize
#define holo_base_msg_vision_ImageObjectsKeyPoint2f_cdr_deserialize_key                                                \
    holo_base_msg_vision_ImageObjectsKeyPoint2f_cdr_deserialize
#define holo_base_msg_vision_ImageObjectsKeyPoint2f_get_serialized_key_size                                            \
    holo_base_msg_vision_ImageObjectsKeyPoint2f_get_serialized_sample_size

struct holo_base_msg_vision_ImageObjectsPoint2dTypePlugin;

NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ImageObjectsPoint2dTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_vision_ImageObjectsPoint2dWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_vision_ImageObjectsPoint2dReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_vision_ImageObjectsPoint2dTypePlugin_get(void);
NDDSUSERDllExport extern const char* holo_base_msg_vision_ImageObjectsPoint2dTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind holo_base_msg_vision_ImageObjectsPoint2dI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ImageObjectsPoint2dPlugin_create_sample(struct DDS_TypePlugin* plugin, void** sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ImageObjectsPoint2dPlugin_delete_sample(struct DDS_TypePlugin* plugin, void* sample);
#endif

NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ImageObjectsPoint2dPlugin_copy_sample(struct DDS_TypePlugin* plugin, void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ImageObjectsPoint2d_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                       const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ImageObjectsPoint2d_cdr_deserialize(
    struct DDS_TypePlugin* plugin, void* void_sample, struct CDR_Stream_t* stream, DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_vision_ImageObjectsPoint2d_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_vision_ImageObjectsPoint2d_cdr_serialize_key                                                     \
    holo_base_msg_vision_ImageObjectsPoint2d_cdr_serialize
#define holo_base_msg_vision_ImageObjectsPoint2d_cdr_deserialize_key                                                   \
    holo_base_msg_vision_ImageObjectsPoint2d_cdr_deserialize
#define holo_base_msg_vision_ImageObjectsPoint2d_get_serialized_key_size                                               \
    holo_base_msg_vision_ImageObjectsPoint2d_get_serialized_sample_size

struct holo_base_msg_vision_ImageObjectsPoint2fTypePlugin;

NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ImageObjectsPoint2fTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_vision_ImageObjectsPoint2fWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_vision_ImageObjectsPoint2fReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_vision_ImageObjectsPoint2fTypePlugin_get(void);
NDDSUSERDllExport extern const char* holo_base_msg_vision_ImageObjectsPoint2fTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind holo_base_msg_vision_ImageObjectsPoint2fI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ImageObjectsPoint2fPlugin_create_sample(struct DDS_TypePlugin* plugin, void** sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ImageObjectsPoint2fPlugin_delete_sample(struct DDS_TypePlugin* plugin, void* sample);
#endif

NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ImageObjectsPoint2fPlugin_copy_sample(struct DDS_TypePlugin* plugin, void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ImageObjectsPoint2f_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                       const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ImageObjectsPoint2f_cdr_deserialize(
    struct DDS_TypePlugin* plugin, void* void_sample, struct CDR_Stream_t* stream, DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_vision_ImageObjectsPoint2f_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_vision_ImageObjectsPoint2f_cdr_serialize_key                                                     \
    holo_base_msg_vision_ImageObjectsPoint2f_cdr_serialize
#define holo_base_msg_vision_ImageObjectsPoint2f_cdr_deserialize_key                                                   \
    holo_base_msg_vision_ImageObjectsPoint2f_cdr_deserialize
#define holo_base_msg_vision_ImageObjectsPoint2f_get_serialized_key_size                                               \
    holo_base_msg_vision_ImageObjectsPoint2f_get_serialized_sample_size

struct holo_base_msg_vision_ImageObjectsPoint3dTypePlugin;

NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ImageObjectsPoint3dTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_vision_ImageObjectsPoint3dWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_vision_ImageObjectsPoint3dReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_vision_ImageObjectsPoint3dTypePlugin_get(void);
NDDSUSERDllExport extern const char* holo_base_msg_vision_ImageObjectsPoint3dTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind holo_base_msg_vision_ImageObjectsPoint3dI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ImageObjectsPoint3dPlugin_create_sample(struct DDS_TypePlugin* plugin, void** sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ImageObjectsPoint3dPlugin_delete_sample(struct DDS_TypePlugin* plugin, void* sample);
#endif

NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ImageObjectsPoint3dPlugin_copy_sample(struct DDS_TypePlugin* plugin, void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ImageObjectsPoint3d_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                       const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ImageObjectsPoint3d_cdr_deserialize(
    struct DDS_TypePlugin* plugin, void* void_sample, struct CDR_Stream_t* stream, DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_vision_ImageObjectsPoint3d_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_vision_ImageObjectsPoint3d_cdr_serialize_key                                                     \
    holo_base_msg_vision_ImageObjectsPoint3d_cdr_serialize
#define holo_base_msg_vision_ImageObjectsPoint3d_cdr_deserialize_key                                                   \
    holo_base_msg_vision_ImageObjectsPoint3d_cdr_deserialize
#define holo_base_msg_vision_ImageObjectsPoint3d_get_serialized_key_size                                               \
    holo_base_msg_vision_ImageObjectsPoint3d_get_serialized_sample_size

struct holo_base_msg_vision_ImageObjectsPoint3fTypePlugin;

NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ImageObjectsPoint3fTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_vision_ImageObjectsPoint3fWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_vision_ImageObjectsPoint3fReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_vision_ImageObjectsPoint3fTypePlugin_get(void);
NDDSUSERDllExport extern const char* holo_base_msg_vision_ImageObjectsPoint3fTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind holo_base_msg_vision_ImageObjectsPoint3fI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ImageObjectsPoint3fPlugin_create_sample(struct DDS_TypePlugin* plugin, void** sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ImageObjectsPoint3fPlugin_delete_sample(struct DDS_TypePlugin* plugin, void* sample);
#endif

NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ImageObjectsPoint3fPlugin_copy_sample(struct DDS_TypePlugin* plugin, void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_vision_ImageObjectsPoint3f_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                       const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_vision_ImageObjectsPoint3f_cdr_deserialize(
    struct DDS_TypePlugin* plugin, void* void_sample, struct CDR_Stream_t* stream, DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_vision_ImageObjectsPoint3f_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_vision_ImageObjectsPoint3f_cdr_serialize_key                                                     \
    holo_base_msg_vision_ImageObjectsPoint3f_cdr_serialize
#define holo_base_msg_vision_ImageObjectsPoint3f_cdr_deserialize_key                                                   \
    holo_base_msg_vision_ImageObjectsPoint3f_cdr_deserialize
#define holo_base_msg_vision_ImageObjectsPoint3f_get_serialized_key_size                                               \
    holo_base_msg_vision_ImageObjectsPoint3f_get_serialized_sample_size

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* ImageObjectsPlugin_1109333664_h */
