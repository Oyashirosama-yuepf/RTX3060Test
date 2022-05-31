/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Vector.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef Vector_2010769341_h
#define Vector_2010769341_h

#ifndef rti_me_cpp_hxx
#include "rti_me_cpp.hxx"
#endif

#include "dds_c/dds_c_typecode.h"

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#include "holo_parking_msg/holo_base_msg/core/Types.h"

typedef DDS_DoubleSeq holo_base_msg_numerics_Vectord;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_numerics_Vectord_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_numerics_Vectord_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_numerics_Vectord_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vectord
#define TSeq holo_base_msg_numerics_VectordSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vectord
#define TSeq holo_base_msg_numerics_VectordSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_numerics_Vectord* holo_base_msg_numerics_Vectord_create();

NDDSUSERDllExport extern void holo_base_msg_numerics_Vectord_delete(holo_base_msg_numerics_Vectord* sample);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vectord_initialize(holo_base_msg_numerics_Vectord* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vectord_initialize_ex(holo_base_msg_numerics_Vectord* self,
                                                                       RTIBool                         allocatePointers,
                                                                       RTIBool                         allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vectord_initialize_w_params(
    holo_base_msg_numerics_Vectord* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vectord_finalize(holo_base_msg_numerics_Vectord* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vectord_finalize_w_return(holo_base_msg_numerics_Vectord* self);

NDDSUSERDllExport void holo_base_msg_numerics_Vectord_finalize_ex(holo_base_msg_numerics_Vectord* self,
                                                                  RTIBool                         deletePointers);

NDDSUSERDllExport void holo_base_msg_numerics_Vectord_finalize_w_params(
    holo_base_msg_numerics_Vectord* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_numerics_Vectord_finalize_optional_members(holo_base_msg_numerics_Vectord* self,
                                                                                RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vectord_copy(holo_base_msg_numerics_Vectord*       dst,
                                                              const holo_base_msg_numerics_Vectord* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_Double holo_base_msg_numerics_Vector2d[2];
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_numerics_Vector2d_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_numerics_Vector2d_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_numerics_Vector2d_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector2d
#define TSeq holo_base_msg_numerics_Vector2dSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector2d
#define TSeq holo_base_msg_numerics_Vector2dSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_numerics_Vector2d* holo_base_msg_numerics_Vector2d_create();

NDDSUSERDllExport extern void holo_base_msg_numerics_Vector2d_delete(holo_base_msg_numerics_Vector2d* sample);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector2d_initialize(holo_base_msg_numerics_Vector2d* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector2d_initialize_ex(holo_base_msg_numerics_Vector2d* self,
                                                                        RTIBool allocatePointers,
                                                                        RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector2d_initialize_w_params(
    holo_base_msg_numerics_Vector2d* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector2d_finalize(holo_base_msg_numerics_Vector2d* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector2d_finalize_w_return(holo_base_msg_numerics_Vector2d* self);

NDDSUSERDllExport void holo_base_msg_numerics_Vector2d_finalize_ex(holo_base_msg_numerics_Vector2d* self,
                                                                   RTIBool                          deletePointers);

NDDSUSERDllExport void holo_base_msg_numerics_Vector2d_finalize_w_params(
    holo_base_msg_numerics_Vector2d* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_numerics_Vector2d_finalize_optional_members(holo_base_msg_numerics_Vector2d* self,
                                                                                 RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector2d_copy(holo_base_msg_numerics_Vector2d*       dst,
                                                               const holo_base_msg_numerics_Vector2d* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_Double holo_base_msg_numerics_Vector3d[3];
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_numerics_Vector3d_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_numerics_Vector3d_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_numerics_Vector3d_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector3d
#define TSeq holo_base_msg_numerics_Vector3dSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector3d
#define TSeq holo_base_msg_numerics_Vector3dSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_numerics_Vector3d* holo_base_msg_numerics_Vector3d_create();

NDDSUSERDllExport extern void holo_base_msg_numerics_Vector3d_delete(holo_base_msg_numerics_Vector3d* sample);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector3d_initialize(holo_base_msg_numerics_Vector3d* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector3d_initialize_ex(holo_base_msg_numerics_Vector3d* self,
                                                                        RTIBool allocatePointers,
                                                                        RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector3d_initialize_w_params(
    holo_base_msg_numerics_Vector3d* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector3d_finalize(holo_base_msg_numerics_Vector3d* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector3d_finalize_w_return(holo_base_msg_numerics_Vector3d* self);

NDDSUSERDllExport void holo_base_msg_numerics_Vector3d_finalize_ex(holo_base_msg_numerics_Vector3d* self,
                                                                   RTIBool                          deletePointers);

NDDSUSERDllExport void holo_base_msg_numerics_Vector3d_finalize_w_params(
    holo_base_msg_numerics_Vector3d* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_numerics_Vector3d_finalize_optional_members(holo_base_msg_numerics_Vector3d* self,
                                                                                 RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector3d_copy(holo_base_msg_numerics_Vector3d*       dst,
                                                               const holo_base_msg_numerics_Vector3d* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_Double holo_base_msg_numerics_Vector4d[4];
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_numerics_Vector4d_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_numerics_Vector4d_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_numerics_Vector4d_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector4d
#define TSeq holo_base_msg_numerics_Vector4dSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector4d
#define TSeq holo_base_msg_numerics_Vector4dSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_numerics_Vector4d* holo_base_msg_numerics_Vector4d_create();

NDDSUSERDllExport extern void holo_base_msg_numerics_Vector4d_delete(holo_base_msg_numerics_Vector4d* sample);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector4d_initialize(holo_base_msg_numerics_Vector4d* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector4d_initialize_ex(holo_base_msg_numerics_Vector4d* self,
                                                                        RTIBool allocatePointers,
                                                                        RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector4d_initialize_w_params(
    holo_base_msg_numerics_Vector4d* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector4d_finalize(holo_base_msg_numerics_Vector4d* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector4d_finalize_w_return(holo_base_msg_numerics_Vector4d* self);

NDDSUSERDllExport void holo_base_msg_numerics_Vector4d_finalize_ex(holo_base_msg_numerics_Vector4d* self,
                                                                   RTIBool                          deletePointers);

NDDSUSERDllExport void holo_base_msg_numerics_Vector4d_finalize_w_params(
    holo_base_msg_numerics_Vector4d* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_numerics_Vector4d_finalize_optional_members(holo_base_msg_numerics_Vector4d* self,
                                                                                 RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector4d_copy(holo_base_msg_numerics_Vector4d*       dst,
                                                               const holo_base_msg_numerics_Vector4d* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_Double holo_base_msg_numerics_Vector5d[5];
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_numerics_Vector5d_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_numerics_Vector5d_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_numerics_Vector5d_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector5d
#define TSeq holo_base_msg_numerics_Vector5dSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector5d
#define TSeq holo_base_msg_numerics_Vector5dSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_numerics_Vector5d* holo_base_msg_numerics_Vector5d_create();

NDDSUSERDllExport extern void holo_base_msg_numerics_Vector5d_delete(holo_base_msg_numerics_Vector5d* sample);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector5d_initialize(holo_base_msg_numerics_Vector5d* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector5d_initialize_ex(holo_base_msg_numerics_Vector5d* self,
                                                                        RTIBool allocatePointers,
                                                                        RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector5d_initialize_w_params(
    holo_base_msg_numerics_Vector5d* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector5d_finalize(holo_base_msg_numerics_Vector5d* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector5d_finalize_w_return(holo_base_msg_numerics_Vector5d* self);

NDDSUSERDllExport void holo_base_msg_numerics_Vector5d_finalize_ex(holo_base_msg_numerics_Vector5d* self,
                                                                   RTIBool                          deletePointers);

NDDSUSERDllExport void holo_base_msg_numerics_Vector5d_finalize_w_params(
    holo_base_msg_numerics_Vector5d* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_numerics_Vector5d_finalize_optional_members(holo_base_msg_numerics_Vector5d* self,
                                                                                 RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector5d_copy(holo_base_msg_numerics_Vector5d*       dst,
                                                               const holo_base_msg_numerics_Vector5d* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_Double holo_base_msg_numerics_Vector6d[6];
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_numerics_Vector6d_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_numerics_Vector6d_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_numerics_Vector6d_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector6d
#define TSeq holo_base_msg_numerics_Vector6dSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector6d
#define TSeq holo_base_msg_numerics_Vector6dSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_numerics_Vector6d* holo_base_msg_numerics_Vector6d_create();

NDDSUSERDllExport extern void holo_base_msg_numerics_Vector6d_delete(holo_base_msg_numerics_Vector6d* sample);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector6d_initialize(holo_base_msg_numerics_Vector6d* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector6d_initialize_ex(holo_base_msg_numerics_Vector6d* self,
                                                                        RTIBool allocatePointers,
                                                                        RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector6d_initialize_w_params(
    holo_base_msg_numerics_Vector6d* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector6d_finalize(holo_base_msg_numerics_Vector6d* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector6d_finalize_w_return(holo_base_msg_numerics_Vector6d* self);

NDDSUSERDllExport void holo_base_msg_numerics_Vector6d_finalize_ex(holo_base_msg_numerics_Vector6d* self,
                                                                   RTIBool                          deletePointers);

NDDSUSERDllExport void holo_base_msg_numerics_Vector6d_finalize_w_params(
    holo_base_msg_numerics_Vector6d* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_numerics_Vector6d_finalize_optional_members(holo_base_msg_numerics_Vector6d* self,
                                                                                 RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector6d_copy(holo_base_msg_numerics_Vector6d*       dst,
                                                               const holo_base_msg_numerics_Vector6d* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_Double holo_base_msg_numerics_Vector7d[7];
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_numerics_Vector7d_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_numerics_Vector7d_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_numerics_Vector7d_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector7d
#define TSeq holo_base_msg_numerics_Vector7dSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector7d
#define TSeq holo_base_msg_numerics_Vector7dSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_numerics_Vector7d* holo_base_msg_numerics_Vector7d_create();

NDDSUSERDllExport extern void holo_base_msg_numerics_Vector7d_delete(holo_base_msg_numerics_Vector7d* sample);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector7d_initialize(holo_base_msg_numerics_Vector7d* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector7d_initialize_ex(holo_base_msg_numerics_Vector7d* self,
                                                                        RTIBool allocatePointers,
                                                                        RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector7d_initialize_w_params(
    holo_base_msg_numerics_Vector7d* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector7d_finalize(holo_base_msg_numerics_Vector7d* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector7d_finalize_w_return(holo_base_msg_numerics_Vector7d* self);

NDDSUSERDllExport void holo_base_msg_numerics_Vector7d_finalize_ex(holo_base_msg_numerics_Vector7d* self,
                                                                   RTIBool                          deletePointers);

NDDSUSERDllExport void holo_base_msg_numerics_Vector7d_finalize_w_params(
    holo_base_msg_numerics_Vector7d* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_numerics_Vector7d_finalize_optional_members(holo_base_msg_numerics_Vector7d* self,
                                                                                 RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector7d_copy(holo_base_msg_numerics_Vector7d*       dst,
                                                               const holo_base_msg_numerics_Vector7d* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_Double holo_base_msg_numerics_Vector8d[8];
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_numerics_Vector8d_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_numerics_Vector8d_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_numerics_Vector8d_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector8d
#define TSeq holo_base_msg_numerics_Vector8dSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector8d
#define TSeq holo_base_msg_numerics_Vector8dSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_numerics_Vector8d* holo_base_msg_numerics_Vector8d_create();

NDDSUSERDllExport extern void holo_base_msg_numerics_Vector8d_delete(holo_base_msg_numerics_Vector8d* sample);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector8d_initialize(holo_base_msg_numerics_Vector8d* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector8d_initialize_ex(holo_base_msg_numerics_Vector8d* self,
                                                                        RTIBool allocatePointers,
                                                                        RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector8d_initialize_w_params(
    holo_base_msg_numerics_Vector8d* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector8d_finalize(holo_base_msg_numerics_Vector8d* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector8d_finalize_w_return(holo_base_msg_numerics_Vector8d* self);

NDDSUSERDllExport void holo_base_msg_numerics_Vector8d_finalize_ex(holo_base_msg_numerics_Vector8d* self,
                                                                   RTIBool                          deletePointers);

NDDSUSERDllExport void holo_base_msg_numerics_Vector8d_finalize_w_params(
    holo_base_msg_numerics_Vector8d* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_numerics_Vector8d_finalize_optional_members(holo_base_msg_numerics_Vector8d* self,
                                                                                 RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector8d_copy(holo_base_msg_numerics_Vector8d*       dst,
                                                               const holo_base_msg_numerics_Vector8d* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_FloatSeq holo_base_msg_numerics_Vectorf;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_numerics_Vectorf_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_numerics_Vectorf_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_numerics_Vectorf_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vectorf
#define TSeq holo_base_msg_numerics_VectorfSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vectorf
#define TSeq holo_base_msg_numerics_VectorfSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_numerics_Vectorf* holo_base_msg_numerics_Vectorf_create();

NDDSUSERDllExport extern void holo_base_msg_numerics_Vectorf_delete(holo_base_msg_numerics_Vectorf* sample);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vectorf_initialize(holo_base_msg_numerics_Vectorf* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vectorf_initialize_ex(holo_base_msg_numerics_Vectorf* self,
                                                                       RTIBool                         allocatePointers,
                                                                       RTIBool                         allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vectorf_initialize_w_params(
    holo_base_msg_numerics_Vectorf* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vectorf_finalize(holo_base_msg_numerics_Vectorf* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vectorf_finalize_w_return(holo_base_msg_numerics_Vectorf* self);

NDDSUSERDllExport void holo_base_msg_numerics_Vectorf_finalize_ex(holo_base_msg_numerics_Vectorf* self,
                                                                  RTIBool                         deletePointers);

NDDSUSERDllExport void holo_base_msg_numerics_Vectorf_finalize_w_params(
    holo_base_msg_numerics_Vectorf* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_numerics_Vectorf_finalize_optional_members(holo_base_msg_numerics_Vectorf* self,
                                                                                RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vectorf_copy(holo_base_msg_numerics_Vectorf*       dst,
                                                              const holo_base_msg_numerics_Vectorf* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_Float holo_base_msg_numerics_Vector2f[2];
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_numerics_Vector2f_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_numerics_Vector2f_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_numerics_Vector2f_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector2f
#define TSeq holo_base_msg_numerics_Vector2fSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector2f
#define TSeq holo_base_msg_numerics_Vector2fSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_numerics_Vector2f* holo_base_msg_numerics_Vector2f_create();

NDDSUSERDllExport extern void holo_base_msg_numerics_Vector2f_delete(holo_base_msg_numerics_Vector2f* sample);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector2f_initialize(holo_base_msg_numerics_Vector2f* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector2f_initialize_ex(holo_base_msg_numerics_Vector2f* self,
                                                                        RTIBool allocatePointers,
                                                                        RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector2f_initialize_w_params(
    holo_base_msg_numerics_Vector2f* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector2f_finalize(holo_base_msg_numerics_Vector2f* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector2f_finalize_w_return(holo_base_msg_numerics_Vector2f* self);

NDDSUSERDllExport void holo_base_msg_numerics_Vector2f_finalize_ex(holo_base_msg_numerics_Vector2f* self,
                                                                   RTIBool                          deletePointers);

NDDSUSERDllExport void holo_base_msg_numerics_Vector2f_finalize_w_params(
    holo_base_msg_numerics_Vector2f* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_numerics_Vector2f_finalize_optional_members(holo_base_msg_numerics_Vector2f* self,
                                                                                 RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector2f_copy(holo_base_msg_numerics_Vector2f*       dst,
                                                               const holo_base_msg_numerics_Vector2f* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_Float holo_base_msg_numerics_Vector3f[3];
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_numerics_Vector3f_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_numerics_Vector3f_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_numerics_Vector3f_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector3f
#define TSeq holo_base_msg_numerics_Vector3fSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector3f
#define TSeq holo_base_msg_numerics_Vector3fSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_numerics_Vector3f* holo_base_msg_numerics_Vector3f_create();

NDDSUSERDllExport extern void holo_base_msg_numerics_Vector3f_delete(holo_base_msg_numerics_Vector3f* sample);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector3f_initialize(holo_base_msg_numerics_Vector3f* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector3f_initialize_ex(holo_base_msg_numerics_Vector3f* self,
                                                                        RTIBool allocatePointers,
                                                                        RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector3f_initialize_w_params(
    holo_base_msg_numerics_Vector3f* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector3f_finalize(holo_base_msg_numerics_Vector3f* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector3f_finalize_w_return(holo_base_msg_numerics_Vector3f* self);

NDDSUSERDllExport void holo_base_msg_numerics_Vector3f_finalize_ex(holo_base_msg_numerics_Vector3f* self,
                                                                   RTIBool                          deletePointers);

NDDSUSERDllExport void holo_base_msg_numerics_Vector3f_finalize_w_params(
    holo_base_msg_numerics_Vector3f* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_numerics_Vector3f_finalize_optional_members(holo_base_msg_numerics_Vector3f* self,
                                                                                 RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector3f_copy(holo_base_msg_numerics_Vector3f*       dst,
                                                               const holo_base_msg_numerics_Vector3f* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_Float holo_base_msg_numerics_Vector4f[4];
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_numerics_Vector4f_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_numerics_Vector4f_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_numerics_Vector4f_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector4f
#define TSeq holo_base_msg_numerics_Vector4fSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector4f
#define TSeq holo_base_msg_numerics_Vector4fSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_numerics_Vector4f* holo_base_msg_numerics_Vector4f_create();

NDDSUSERDllExport extern void holo_base_msg_numerics_Vector4f_delete(holo_base_msg_numerics_Vector4f* sample);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector4f_initialize(holo_base_msg_numerics_Vector4f* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector4f_initialize_ex(holo_base_msg_numerics_Vector4f* self,
                                                                        RTIBool allocatePointers,
                                                                        RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector4f_initialize_w_params(
    holo_base_msg_numerics_Vector4f* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector4f_finalize(holo_base_msg_numerics_Vector4f* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector4f_finalize_w_return(holo_base_msg_numerics_Vector4f* self);

NDDSUSERDllExport void holo_base_msg_numerics_Vector4f_finalize_ex(holo_base_msg_numerics_Vector4f* self,
                                                                   RTIBool                          deletePointers);

NDDSUSERDllExport void holo_base_msg_numerics_Vector4f_finalize_w_params(
    holo_base_msg_numerics_Vector4f* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_numerics_Vector4f_finalize_optional_members(holo_base_msg_numerics_Vector4f* self,
                                                                                 RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector4f_copy(holo_base_msg_numerics_Vector4f*       dst,
                                                               const holo_base_msg_numerics_Vector4f* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_Float holo_base_msg_numerics_Vector5f[5];
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_numerics_Vector5f_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_numerics_Vector5f_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_numerics_Vector5f_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector5f
#define TSeq holo_base_msg_numerics_Vector5fSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector5f
#define TSeq holo_base_msg_numerics_Vector5fSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_numerics_Vector5f* holo_base_msg_numerics_Vector5f_create();

NDDSUSERDllExport extern void holo_base_msg_numerics_Vector5f_delete(holo_base_msg_numerics_Vector5f* sample);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector5f_initialize(holo_base_msg_numerics_Vector5f* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector5f_initialize_ex(holo_base_msg_numerics_Vector5f* self,
                                                                        RTIBool allocatePointers,
                                                                        RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector5f_initialize_w_params(
    holo_base_msg_numerics_Vector5f* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector5f_finalize(holo_base_msg_numerics_Vector5f* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector5f_finalize_w_return(holo_base_msg_numerics_Vector5f* self);

NDDSUSERDllExport void holo_base_msg_numerics_Vector5f_finalize_ex(holo_base_msg_numerics_Vector5f* self,
                                                                   RTIBool                          deletePointers);

NDDSUSERDllExport void holo_base_msg_numerics_Vector5f_finalize_w_params(
    holo_base_msg_numerics_Vector5f* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_numerics_Vector5f_finalize_optional_members(holo_base_msg_numerics_Vector5f* self,
                                                                                 RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector5f_copy(holo_base_msg_numerics_Vector5f*       dst,
                                                               const holo_base_msg_numerics_Vector5f* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_Float holo_base_msg_numerics_Vector6f[6];
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_numerics_Vector6f_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_numerics_Vector6f_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_numerics_Vector6f_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector6f
#define TSeq holo_base_msg_numerics_Vector6fSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector6f
#define TSeq holo_base_msg_numerics_Vector6fSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_numerics_Vector6f* holo_base_msg_numerics_Vector6f_create();

NDDSUSERDllExport extern void holo_base_msg_numerics_Vector6f_delete(holo_base_msg_numerics_Vector6f* sample);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector6f_initialize(holo_base_msg_numerics_Vector6f* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector6f_initialize_ex(holo_base_msg_numerics_Vector6f* self,
                                                                        RTIBool allocatePointers,
                                                                        RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector6f_initialize_w_params(
    holo_base_msg_numerics_Vector6f* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector6f_finalize(holo_base_msg_numerics_Vector6f* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector6f_finalize_w_return(holo_base_msg_numerics_Vector6f* self);

NDDSUSERDllExport void holo_base_msg_numerics_Vector6f_finalize_ex(holo_base_msg_numerics_Vector6f* self,
                                                                   RTIBool                          deletePointers);

NDDSUSERDllExport void holo_base_msg_numerics_Vector6f_finalize_w_params(
    holo_base_msg_numerics_Vector6f* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_numerics_Vector6f_finalize_optional_members(holo_base_msg_numerics_Vector6f* self,
                                                                                 RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector6f_copy(holo_base_msg_numerics_Vector6f*       dst,
                                                               const holo_base_msg_numerics_Vector6f* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_Float holo_base_msg_numerics_Vector7f[7];
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_numerics_Vector7f_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_numerics_Vector7f_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_numerics_Vector7f_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector7f
#define TSeq holo_base_msg_numerics_Vector7fSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector7f
#define TSeq holo_base_msg_numerics_Vector7fSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_numerics_Vector7f* holo_base_msg_numerics_Vector7f_create();

NDDSUSERDllExport extern void holo_base_msg_numerics_Vector7f_delete(holo_base_msg_numerics_Vector7f* sample);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector7f_initialize(holo_base_msg_numerics_Vector7f* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector7f_initialize_ex(holo_base_msg_numerics_Vector7f* self,
                                                                        RTIBool allocatePointers,
                                                                        RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector7f_initialize_w_params(
    holo_base_msg_numerics_Vector7f* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector7f_finalize(holo_base_msg_numerics_Vector7f* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector7f_finalize_w_return(holo_base_msg_numerics_Vector7f* self);

NDDSUSERDllExport void holo_base_msg_numerics_Vector7f_finalize_ex(holo_base_msg_numerics_Vector7f* self,
                                                                   RTIBool                          deletePointers);

NDDSUSERDllExport void holo_base_msg_numerics_Vector7f_finalize_w_params(
    holo_base_msg_numerics_Vector7f* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_numerics_Vector7f_finalize_optional_members(holo_base_msg_numerics_Vector7f* self,
                                                                                 RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector7f_copy(holo_base_msg_numerics_Vector7f*       dst,
                                                               const holo_base_msg_numerics_Vector7f* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_Float holo_base_msg_numerics_Vector8f[8];
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_numerics_Vector8f_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_numerics_Vector8f_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_numerics_Vector8f_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector8f
#define TSeq holo_base_msg_numerics_Vector8fSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Vector8f
#define TSeq holo_base_msg_numerics_Vector8fSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_numerics_Vector8f* holo_base_msg_numerics_Vector8f_create();

NDDSUSERDllExport extern void holo_base_msg_numerics_Vector8f_delete(holo_base_msg_numerics_Vector8f* sample);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector8f_initialize(holo_base_msg_numerics_Vector8f* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector8f_initialize_ex(holo_base_msg_numerics_Vector8f* self,
                                                                        RTIBool allocatePointers,
                                                                        RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector8f_initialize_w_params(
    holo_base_msg_numerics_Vector8f* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector8f_finalize(holo_base_msg_numerics_Vector8f* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector8f_finalize_w_return(holo_base_msg_numerics_Vector8f* self);

NDDSUSERDllExport void holo_base_msg_numerics_Vector8f_finalize_ex(holo_base_msg_numerics_Vector8f* self,
                                                                   RTIBool                          deletePointers);

NDDSUSERDllExport void holo_base_msg_numerics_Vector8f_finalize_w_params(
    holo_base_msg_numerics_Vector8f* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_numerics_Vector8f_finalize_optional_members(holo_base_msg_numerics_Vector8f* self,
                                                                                 RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Vector8f_copy(holo_base_msg_numerics_Vector8f*       dst,
                                                               const holo_base_msg_numerics_Vector8f* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#ifndef NDDS_STANDALONE_TYPE
#endif

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* Vector */
