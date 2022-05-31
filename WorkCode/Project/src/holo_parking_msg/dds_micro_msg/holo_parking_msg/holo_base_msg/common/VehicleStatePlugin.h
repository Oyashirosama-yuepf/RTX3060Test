/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from VehicleState.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef VehicleStatePlugin_157436955_h
#define VehicleStatePlugin_157436955_h

#include "VehicleState.h"

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#include "holo_parking_msg/holo_base_msg/common/CommonPlugin.h"

#include "holo_parking_msg/holo_base_msg/core/TypesPlugin.h"

struct holo_base_msg_common_ChassisStateTypePlugin;

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_ChassisStateTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_ChassisStateWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_ChassisStateReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_common_ChassisStateTypePlugin_get(void);
NDDSUSERDllExport extern const char*            holo_base_msg_common_ChassisStateTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind holo_base_msg_common_ChassisStateI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_ChassisStatePlugin_create_sample(struct DDS_TypePlugin* plugin,
                                                                                        void**                 sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_ChassisStatePlugin_delete_sample(struct DDS_TypePlugin* plugin,
                                                                                        void*                  sample);
#endif

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_ChassisStatePlugin_copy_sample(struct DDS_TypePlugin* plugin,
                                                                                      void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_ChassisState_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                  struct CDR_Stream_t*   stream,
                                                                                  const void*            void_sample,
                                                                                  DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_ChassisState_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                    void*                  void_sample,
                                                                                    struct CDR_Stream_t*   stream,
                                                                                    DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_common_ChassisState_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_common_ChassisState_cdr_serialize_key holo_base_msg_common_ChassisState_cdr_serialize
#define holo_base_msg_common_ChassisState_cdr_deserialize_key holo_base_msg_common_ChassisState_cdr_deserialize
#define holo_base_msg_common_ChassisState_get_serialized_key_size                                                      \
    holo_base_msg_common_ChassisState_get_serialized_sample_size

struct holo_base_msg_common_VehicleBodyStateTypePlugin;

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_VehicleBodyStateTypePlugin_delete(struct DDS_TypePlugin* self);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_VehicleBodyStateWriterTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataWriter* writer,
    struct DDS_DataWriterQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePlugin* holo_base_msg_common_VehicleBodyStateReaderTypePlugin_create(
    DDS_DomainParticipant* participant, struct DDS_DomainParticipantQos* dp_qos, DDS_DataReader* reader,
    struct DDS_DataReaderQos* qos, struct DDS_TypePluginProperty* property);

NDDSUSERDllExport extern struct DDS_TypePluginI* holo_base_msg_common_VehicleBodyStateTypePlugin_get(void);
NDDSUSERDllExport extern const char* holo_base_msg_common_VehicleBodyStateTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind holo_base_msg_common_VehicleBodyStateI_get_key_kind();
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_VehicleBodyStatePlugin_create_sample(struct DDS_TypePlugin* plugin, void** sample);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_VehicleBodyStatePlugin_delete_sample(struct DDS_TypePlugin* plugin, void* sample);
#endif

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_VehicleBodyStatePlugin_copy_sample(struct DDS_TypePlugin* plugin,
                                                                                          void* dst, const void* src);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
holo_base_msg_common_VehicleBodyState_cdr_serialize(struct DDS_TypePlugin* plugin, struct CDR_Stream_t* stream,
                                                    const void* void_sample, DDS_InstanceHandle_t* destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_common_VehicleBodyState_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                        void* void_sample,
                                                                                        struct CDR_Stream_t*  stream,
                                                                                        DDS_InstanceHandle_t* source);

NDDSUSERDllExport extern RTI_UINT32 holo_base_msg_common_VehicleBodyState_get_serialized_sample_size(
    struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_common_VehicleBodyState_cdr_serialize_key holo_base_msg_common_VehicleBodyState_cdr_serialize
#define holo_base_msg_common_VehicleBodyState_cdr_deserialize_key holo_base_msg_common_VehicleBodyState_cdr_deserialize
#define holo_base_msg_common_VehicleBodyState_get_serialized_key_size                                                  \
    holo_base_msg_common_VehicleBodyState_get_serialized_sample_size

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* VehicleStatePlugin_157436955_h */
