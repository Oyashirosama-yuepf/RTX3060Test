/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Vector.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef VectorPlugin_2010769341_h
#define VectorPlugin_2010769341_h

#include "Vector.h"

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#include "holo_parking_msg/holo_base_msg/core/TypesPlugin.h"

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vectord_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                               struct CDR_Stream_t*   stream,
                                                                               const void*            void_sample,
                                                                               DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vectord_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                 void*                  void_sample,
                                                                                 struct CDR_Stream_t*   stream,
                                                                                 DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_numerics_Vectord_get_serialized_sample_size(struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_numerics_Vectord_cdr_serialize_key holo_base_msg_numerics_Vectord_cdr_serialize
#define holo_base_msg_numerics_Vectord_cdr_deserialize_key holo_base_msg_numerics_Vectord_cdr_deserialize
#define holo_base_msg_numerics_Vectord_get_serialized_key_size holo_base_msg_numerics_Vectord_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vector2d_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                struct CDR_Stream_t*   stream,
                                                                                const void*            void_sample,
                                                                                DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vector2d_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                  void*                  void_sample,
                                                                                  struct CDR_Stream_t*   stream,
                                                                                  DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_numerics_Vector2d_get_serialized_sample_size(struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_numerics_Vector2d_cdr_serialize_key holo_base_msg_numerics_Vector2d_cdr_serialize
#define holo_base_msg_numerics_Vector2d_cdr_deserialize_key holo_base_msg_numerics_Vector2d_cdr_deserialize
#define holo_base_msg_numerics_Vector2d_get_serialized_key_size                                                        \
    holo_base_msg_numerics_Vector2d_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vector3d_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                struct CDR_Stream_t*   stream,
                                                                                const void*            void_sample,
                                                                                DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vector3d_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                  void*                  void_sample,
                                                                                  struct CDR_Stream_t*   stream,
                                                                                  DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_numerics_Vector3d_get_serialized_sample_size(struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_numerics_Vector3d_cdr_serialize_key holo_base_msg_numerics_Vector3d_cdr_serialize
#define holo_base_msg_numerics_Vector3d_cdr_deserialize_key holo_base_msg_numerics_Vector3d_cdr_deserialize
#define holo_base_msg_numerics_Vector3d_get_serialized_key_size                                                        \
    holo_base_msg_numerics_Vector3d_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vector4d_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                struct CDR_Stream_t*   stream,
                                                                                const void*            void_sample,
                                                                                DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vector4d_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                  void*                  void_sample,
                                                                                  struct CDR_Stream_t*   stream,
                                                                                  DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_numerics_Vector4d_get_serialized_sample_size(struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_numerics_Vector4d_cdr_serialize_key holo_base_msg_numerics_Vector4d_cdr_serialize
#define holo_base_msg_numerics_Vector4d_cdr_deserialize_key holo_base_msg_numerics_Vector4d_cdr_deserialize
#define holo_base_msg_numerics_Vector4d_get_serialized_key_size                                                        \
    holo_base_msg_numerics_Vector4d_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vector5d_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                struct CDR_Stream_t*   stream,
                                                                                const void*            void_sample,
                                                                                DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vector5d_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                  void*                  void_sample,
                                                                                  struct CDR_Stream_t*   stream,
                                                                                  DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_numerics_Vector5d_get_serialized_sample_size(struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_numerics_Vector5d_cdr_serialize_key holo_base_msg_numerics_Vector5d_cdr_serialize
#define holo_base_msg_numerics_Vector5d_cdr_deserialize_key holo_base_msg_numerics_Vector5d_cdr_deserialize
#define holo_base_msg_numerics_Vector5d_get_serialized_key_size                                                        \
    holo_base_msg_numerics_Vector5d_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vector6d_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                struct CDR_Stream_t*   stream,
                                                                                const void*            void_sample,
                                                                                DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vector6d_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                  void*                  void_sample,
                                                                                  struct CDR_Stream_t*   stream,
                                                                                  DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_numerics_Vector6d_get_serialized_sample_size(struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_numerics_Vector6d_cdr_serialize_key holo_base_msg_numerics_Vector6d_cdr_serialize
#define holo_base_msg_numerics_Vector6d_cdr_deserialize_key holo_base_msg_numerics_Vector6d_cdr_deserialize
#define holo_base_msg_numerics_Vector6d_get_serialized_key_size                                                        \
    holo_base_msg_numerics_Vector6d_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vector7d_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                struct CDR_Stream_t*   stream,
                                                                                const void*            void_sample,
                                                                                DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vector7d_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                  void*                  void_sample,
                                                                                  struct CDR_Stream_t*   stream,
                                                                                  DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_numerics_Vector7d_get_serialized_sample_size(struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_numerics_Vector7d_cdr_serialize_key holo_base_msg_numerics_Vector7d_cdr_serialize
#define holo_base_msg_numerics_Vector7d_cdr_deserialize_key holo_base_msg_numerics_Vector7d_cdr_deserialize
#define holo_base_msg_numerics_Vector7d_get_serialized_key_size                                                        \
    holo_base_msg_numerics_Vector7d_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vector8d_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                struct CDR_Stream_t*   stream,
                                                                                const void*            void_sample,
                                                                                DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vector8d_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                  void*                  void_sample,
                                                                                  struct CDR_Stream_t*   stream,
                                                                                  DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_numerics_Vector8d_get_serialized_sample_size(struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_numerics_Vector8d_cdr_serialize_key holo_base_msg_numerics_Vector8d_cdr_serialize
#define holo_base_msg_numerics_Vector8d_cdr_deserialize_key holo_base_msg_numerics_Vector8d_cdr_deserialize
#define holo_base_msg_numerics_Vector8d_get_serialized_key_size                                                        \
    holo_base_msg_numerics_Vector8d_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vectorf_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                               struct CDR_Stream_t*   stream,
                                                                               const void*            void_sample,
                                                                               DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vectorf_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                 void*                  void_sample,
                                                                                 struct CDR_Stream_t*   stream,
                                                                                 DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_numerics_Vectorf_get_serialized_sample_size(struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_numerics_Vectorf_cdr_serialize_key holo_base_msg_numerics_Vectorf_cdr_serialize
#define holo_base_msg_numerics_Vectorf_cdr_deserialize_key holo_base_msg_numerics_Vectorf_cdr_deserialize
#define holo_base_msg_numerics_Vectorf_get_serialized_key_size holo_base_msg_numerics_Vectorf_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vector2f_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                struct CDR_Stream_t*   stream,
                                                                                const void*            void_sample,
                                                                                DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vector2f_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                  void*                  void_sample,
                                                                                  struct CDR_Stream_t*   stream,
                                                                                  DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_numerics_Vector2f_get_serialized_sample_size(struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_numerics_Vector2f_cdr_serialize_key holo_base_msg_numerics_Vector2f_cdr_serialize
#define holo_base_msg_numerics_Vector2f_cdr_deserialize_key holo_base_msg_numerics_Vector2f_cdr_deserialize
#define holo_base_msg_numerics_Vector2f_get_serialized_key_size                                                        \
    holo_base_msg_numerics_Vector2f_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vector3f_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                struct CDR_Stream_t*   stream,
                                                                                const void*            void_sample,
                                                                                DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vector3f_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                  void*                  void_sample,
                                                                                  struct CDR_Stream_t*   stream,
                                                                                  DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_numerics_Vector3f_get_serialized_sample_size(struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_numerics_Vector3f_cdr_serialize_key holo_base_msg_numerics_Vector3f_cdr_serialize
#define holo_base_msg_numerics_Vector3f_cdr_deserialize_key holo_base_msg_numerics_Vector3f_cdr_deserialize
#define holo_base_msg_numerics_Vector3f_get_serialized_key_size                                                        \
    holo_base_msg_numerics_Vector3f_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vector4f_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                struct CDR_Stream_t*   stream,
                                                                                const void*            void_sample,
                                                                                DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vector4f_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                  void*                  void_sample,
                                                                                  struct CDR_Stream_t*   stream,
                                                                                  DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_numerics_Vector4f_get_serialized_sample_size(struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_numerics_Vector4f_cdr_serialize_key holo_base_msg_numerics_Vector4f_cdr_serialize
#define holo_base_msg_numerics_Vector4f_cdr_deserialize_key holo_base_msg_numerics_Vector4f_cdr_deserialize
#define holo_base_msg_numerics_Vector4f_get_serialized_key_size                                                        \
    holo_base_msg_numerics_Vector4f_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vector5f_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                struct CDR_Stream_t*   stream,
                                                                                const void*            void_sample,
                                                                                DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vector5f_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                  void*                  void_sample,
                                                                                  struct CDR_Stream_t*   stream,
                                                                                  DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_numerics_Vector5f_get_serialized_sample_size(struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_numerics_Vector5f_cdr_serialize_key holo_base_msg_numerics_Vector5f_cdr_serialize
#define holo_base_msg_numerics_Vector5f_cdr_deserialize_key holo_base_msg_numerics_Vector5f_cdr_deserialize
#define holo_base_msg_numerics_Vector5f_get_serialized_key_size                                                        \
    holo_base_msg_numerics_Vector5f_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vector6f_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                struct CDR_Stream_t*   stream,
                                                                                const void*            void_sample,
                                                                                DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vector6f_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                  void*                  void_sample,
                                                                                  struct CDR_Stream_t*   stream,
                                                                                  DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_numerics_Vector6f_get_serialized_sample_size(struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_numerics_Vector6f_cdr_serialize_key holo_base_msg_numerics_Vector6f_cdr_serialize
#define holo_base_msg_numerics_Vector6f_cdr_deserialize_key holo_base_msg_numerics_Vector6f_cdr_deserialize
#define holo_base_msg_numerics_Vector6f_get_serialized_key_size                                                        \
    holo_base_msg_numerics_Vector6f_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vector7f_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                struct CDR_Stream_t*   stream,
                                                                                const void*            void_sample,
                                                                                DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vector7f_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                  void*                  void_sample,
                                                                                  struct CDR_Stream_t*   stream,
                                                                                  DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_numerics_Vector7f_get_serialized_sample_size(struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_numerics_Vector7f_cdr_serialize_key holo_base_msg_numerics_Vector7f_cdr_serialize
#define holo_base_msg_numerics_Vector7f_cdr_deserialize_key holo_base_msg_numerics_Vector7f_cdr_deserialize
#define holo_base_msg_numerics_Vector7f_get_serialized_key_size                                                        \
    holo_base_msg_numerics_Vector7f_get_serialized_sample_size

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vector8f_cdr_serialize(struct DDS_TypePlugin* plugin,
                                                                                struct CDR_Stream_t*   stream,
                                                                                const void*            void_sample,
                                                                                DDS_InstanceHandle_t*  destination);

NDDSUSERDllExport extern RTI_BOOL holo_base_msg_numerics_Vector8f_cdr_deserialize(struct DDS_TypePlugin* plugin,
                                                                                  void*                  void_sample,
                                                                                  struct CDR_Stream_t*   stream,
                                                                                  DDS_InstanceHandle_t*  source);

NDDSUSERDllExport extern RTI_UINT32
holo_base_msg_numerics_Vector8f_get_serialized_sample_size(struct DDS_TypePlugin* plugin, RTI_UINT32 current_alignment);
/* Unkeyed type key serialization equivalent to sample serialization */
#define holo_base_msg_numerics_Vector8f_cdr_serialize_key holo_base_msg_numerics_Vector8f_cdr_serialize
#define holo_base_msg_numerics_Vector8f_cdr_deserialize_key holo_base_msg_numerics_Vector8f_cdr_deserialize
#define holo_base_msg_numerics_Vector8f_get_serialized_key_size                                                        \
    holo_base_msg_numerics_Vector8f_get_serialized_sample_size

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* VectorPlugin_2010769341_h */
