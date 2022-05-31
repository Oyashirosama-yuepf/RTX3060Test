/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from PointCloudGeneral.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef PointCloudGeneral_963373545_h
#define PointCloudGeneral_963373545_h

#ifndef rti_me_cpp_hxx
#include "rti_me_cpp.hxx"
#endif

#include "dds_c/dds_c_typecode.h"

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#include "holo_parking_msg/holo_base_msg/common/Common.h"

#include "holo_parking_msg/holo_base_msg/core/Types.h"

#include "holo_parking_msg/holo_base_msg/geometry/Pose.h"

typedef DDS_Float holo_base_msg_common_float32_t;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_float32_t_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_float32_t_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_float32_t_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_float32_t
#define TSeq holo_base_msg_common_float32_tSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_float32_t
#define TSeq holo_base_msg_common_float32_tSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_float32_t* holo_base_msg_common_float32_t_create();

NDDSUSERDllExport extern void holo_base_msg_common_float32_t_delete(holo_base_msg_common_float32_t* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_float32_t_initialize(holo_base_msg_common_float32_t* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_float32_t_initialize_ex(holo_base_msg_common_float32_t* self,
                                                                       RTIBool                         allocatePointers,
                                                                       RTIBool                         allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_float32_t_initialize_w_params(
    holo_base_msg_common_float32_t* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_float32_t_finalize(holo_base_msg_common_float32_t* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_float32_t_finalize_w_return(holo_base_msg_common_float32_t* self);

NDDSUSERDllExport void holo_base_msg_common_float32_t_finalize_ex(holo_base_msg_common_float32_t* self,
                                                                  RTIBool                         deletePointers);

NDDSUSERDllExport void holo_base_msg_common_float32_t_finalize_w_params(
    holo_base_msg_common_float32_t* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_float32_t_finalize_optional_members(holo_base_msg_common_float32_t* self,
                                                                                RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_float32_t_copy(holo_base_msg_common_float32_t*       dst,
                                                              const holo_base_msg_common_float32_t* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_Boolean holo_base_msg_common_bool_t;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_bool_t_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_bool_t_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_bool_t_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_bool_t
#define TSeq holo_base_msg_common_bool_tSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_bool_t
#define TSeq holo_base_msg_common_bool_tSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_bool_t* holo_base_msg_common_bool_t_create();

NDDSUSERDllExport extern void holo_base_msg_common_bool_t_delete(holo_base_msg_common_bool_t* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_bool_t_initialize(holo_base_msg_common_bool_t* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_bool_t_initialize_ex(holo_base_msg_common_bool_t* self,
                                                                    RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_bool_t_initialize_w_params(
    holo_base_msg_common_bool_t* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_bool_t_finalize(holo_base_msg_common_bool_t* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_bool_t_finalize_w_return(holo_base_msg_common_bool_t* self);

NDDSUSERDllExport void holo_base_msg_common_bool_t_finalize_ex(holo_base_msg_common_bool_t* self,
                                                               RTIBool                      deletePointers);

NDDSUSERDllExport void holo_base_msg_common_bool_t_finalize_w_params(
    holo_base_msg_common_bool_t* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_bool_t_finalize_optional_members(holo_base_msg_common_bool_t* self,
                                                                             RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_bool_t_copy(holo_base_msg_common_bool_t*       dst,
                                                           const holo_base_msg_common_bool_t* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_Octet holo_base_msg_common_uint8_t;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_uint8_t_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_uint8_t_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_uint8_t_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_uint8_t
#define TSeq holo_base_msg_common_uint8_tSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_uint8_t
#define TSeq holo_base_msg_common_uint8_tSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_uint8_t* holo_base_msg_common_uint8_t_create();

NDDSUSERDllExport extern void holo_base_msg_common_uint8_t_delete(holo_base_msg_common_uint8_t* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_uint8_t_initialize(holo_base_msg_common_uint8_t* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_uint8_t_initialize_ex(holo_base_msg_common_uint8_t* self,
                                                                     RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_uint8_t_initialize_w_params(
    holo_base_msg_common_uint8_t* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_uint8_t_finalize(holo_base_msg_common_uint8_t* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_uint8_t_finalize_w_return(holo_base_msg_common_uint8_t* self);

NDDSUSERDllExport void holo_base_msg_common_uint8_t_finalize_ex(holo_base_msg_common_uint8_t* self,
                                                                RTIBool                       deletePointers);

NDDSUSERDllExport void holo_base_msg_common_uint8_t_finalize_w_params(
    holo_base_msg_common_uint8_t* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_uint8_t_finalize_optional_members(holo_base_msg_common_uint8_t* self,
                                                                              RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_uint8_t_copy(holo_base_msg_common_uint8_t*       dst,
                                                            const holo_base_msg_common_uint8_t* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_UnsignedLongLong holo_base_msg_common_uint64_t;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_uint64_t_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_uint64_t_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_uint64_t_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_uint64_t
#define TSeq holo_base_msg_common_uint64_tSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_uint64_t
#define TSeq holo_base_msg_common_uint64_tSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_uint64_t* holo_base_msg_common_uint64_t_create();

NDDSUSERDllExport extern void holo_base_msg_common_uint64_t_delete(holo_base_msg_common_uint64_t* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_uint64_t_initialize(holo_base_msg_common_uint64_t* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_uint64_t_initialize_ex(holo_base_msg_common_uint64_t* self,
                                                                      RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_uint64_t_initialize_w_params(
    holo_base_msg_common_uint64_t* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_uint64_t_finalize(holo_base_msg_common_uint64_t* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_uint64_t_finalize_w_return(holo_base_msg_common_uint64_t* self);

NDDSUSERDllExport void holo_base_msg_common_uint64_t_finalize_ex(holo_base_msg_common_uint64_t* self,
                                                                 RTIBool                        deletePointers);

NDDSUSERDllExport void holo_base_msg_common_uint64_t_finalize_w_params(
    holo_base_msg_common_uint64_t* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_uint64_t_finalize_optional_members(holo_base_msg_common_uint64_t* self,
                                                                               RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_uint64_t_copy(holo_base_msg_common_uint64_t*       dst,
                                                             const holo_base_msg_common_uint64_t* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef holo_base_msg_geometry_Pose3f holo_base_msg_common_Pose;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_Pose_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_Pose_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_Pose_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Pose
#define TSeq holo_base_msg_common_PoseSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Pose
#define TSeq holo_base_msg_common_PoseSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_Pose* holo_base_msg_common_Pose_create();

NDDSUSERDllExport extern void holo_base_msg_common_Pose_delete(holo_base_msg_common_Pose* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_Pose_initialize(holo_base_msg_common_Pose* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_Pose_initialize_ex(holo_base_msg_common_Pose* self,
                                                                  RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_Pose_initialize_w_params(
    holo_base_msg_common_Pose* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_Pose_finalize(holo_base_msg_common_Pose* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_Pose_finalize_w_return(holo_base_msg_common_Pose* self);

NDDSUSERDllExport void holo_base_msg_common_Pose_finalize_ex(holo_base_msg_common_Pose* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_common_Pose_finalize_w_params(
    holo_base_msg_common_Pose* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_Pose_finalize_optional_members(holo_base_msg_common_Pose* self,
                                                                           RTIBool                    deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_Pose_copy(holo_base_msg_common_Pose*       dst,
                                                         const holo_base_msg_common_Pose* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_common_PointXYZRGBTYPENAME;
}

struct holo_base_msg_common_PointXYZRGBSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_common_PointXYZRGBTypeSupport;
class holo_base_msg_common_PointXYZRGBDataWriter;
class holo_base_msg_common_PointXYZRGBDataReader;
#endif
class holo_base_msg_common_PointXYZRGB
{
public:
    typedef struct holo_base_msg_common_PointXYZRGBSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_common_PointXYZRGBTypeSupport TypeSupport;
    typedef holo_base_msg_common_PointXYZRGBDataWriter  DataWriter;
    typedef holo_base_msg_common_PointXYZRGBDataReader  DataReader;
#endif

    DDS_Float x;
    DDS_Float y;
    DDS_Float z;
    DDS_Float confidence;
    DDS_Octet r;
    DDS_Octet g;
    DDS_Octet b;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_PointXYZRGB_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_PointXYZRGB_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_PointXYZRGB_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PointXYZRGB
#define TSeq holo_base_msg_common_PointXYZRGBSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PointXYZRGB
#define TSeq holo_base_msg_common_PointXYZRGBSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_PointXYZRGB* holo_base_msg_common_PointXYZRGB_create();

NDDSUSERDllExport extern void holo_base_msg_common_PointXYZRGB_delete(holo_base_msg_common_PointXYZRGB* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_PointXYZRGB_initialize(holo_base_msg_common_PointXYZRGB* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_PointXYZRGB_initialize_ex(holo_base_msg_common_PointXYZRGB* self,
                                                                         RTIBool allocatePointers,
                                                                         RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_PointXYZRGB_initialize_w_params(
    holo_base_msg_common_PointXYZRGB* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_PointXYZRGB_finalize(holo_base_msg_common_PointXYZRGB* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_PointXYZRGB_finalize_w_return(holo_base_msg_common_PointXYZRGB* self);

NDDSUSERDllExport void holo_base_msg_common_PointXYZRGB_finalize_ex(holo_base_msg_common_PointXYZRGB* self,
                                                                    RTIBool                           deletePointers);

NDDSUSERDllExport void holo_base_msg_common_PointXYZRGB_finalize_w_params(
    holo_base_msg_common_PointXYZRGB* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_PointXYZRGB_finalize_optional_members(
    holo_base_msg_common_PointXYZRGB* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_PointXYZRGB_copy(holo_base_msg_common_PointXYZRGB*       dst,
                                                                const holo_base_msg_common_PointXYZRGB* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef holo_base_msg_common_PointXYZRGBSeq holo_base_msg_common_PointXYZRGBSeqTypeDef;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_PointXYZRGBSeqTypeDef_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_PointXYZRGBSeqTypeDef_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_PointXYZRGBSeqTypeDef_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PointXYZRGBSeqTypeDef
#define TSeq holo_base_msg_common_PointXYZRGBSeqTypeDefSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PointXYZRGBSeqTypeDef
#define TSeq holo_base_msg_common_PointXYZRGBSeqTypeDefSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_PointXYZRGBSeqTypeDef*
holo_base_msg_common_PointXYZRGBSeqTypeDef_create();

NDDSUSERDllExport extern void
holo_base_msg_common_PointXYZRGBSeqTypeDef_delete(holo_base_msg_common_PointXYZRGBSeqTypeDef* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_common_PointXYZRGBSeqTypeDef_initialize(holo_base_msg_common_PointXYZRGBSeqTypeDef* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_PointXYZRGBSeqTypeDef_initialize_ex(
    holo_base_msg_common_PointXYZRGBSeqTypeDef* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_PointXYZRGBSeqTypeDef_initialize_w_params(
    holo_base_msg_common_PointXYZRGBSeqTypeDef* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_common_PointXYZRGBSeqTypeDef_finalize(holo_base_msg_common_PointXYZRGBSeqTypeDef* self);

NDDSUSERDllExport RTIBool
holo_base_msg_common_PointXYZRGBSeqTypeDef_finalize_w_return(holo_base_msg_common_PointXYZRGBSeqTypeDef* self);

NDDSUSERDllExport void holo_base_msg_common_PointXYZRGBSeqTypeDef_finalize_ex(
    holo_base_msg_common_PointXYZRGBSeqTypeDef* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_common_PointXYZRGBSeqTypeDef_finalize_w_params(
    holo_base_msg_common_PointXYZRGBSeqTypeDef* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_PointXYZRGBSeqTypeDef_finalize_optional_members(
    holo_base_msg_common_PointXYZRGBSeqTypeDef* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_PointXYZRGBSeqTypeDef_copy(
    holo_base_msg_common_PointXYZRGBSeqTypeDef* dst, const holo_base_msg_common_PointXYZRGBSeqTypeDef* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_common_PointCloudGeneralTYPENAME;
}

struct holo_base_msg_common_PointCloudGeneralSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_common_PointCloudGeneralTypeSupport;
class holo_base_msg_common_PointCloudGeneralDataWriter;
class holo_base_msg_common_PointCloudGeneralDataReader;
#endif
class holo_base_msg_common_PointCloudGeneral
{
public:
    typedef struct holo_base_msg_common_PointCloudGeneralSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_common_PointCloudGeneralTypeSupport TypeSupport;
    typedef holo_base_msg_common_PointCloudGeneralDataWriter  DataWriter;
    typedef holo_base_msg_common_PointCloudGeneralDataReader  DataReader;
#endif

    holo_base_msg_common_Timestamp             timestamp;
    DDS_UnsignedLongLong                       width;
    DDS_UnsignedLongLong                       height;
    DDS_Boolean                                is_dense;
    holo_base_msg_geometry_Pose3f              pose;
    holo_base_msg_common_PointXYZRGBSeqTypeDef point_list;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_PointCloudGeneral_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_PointCloudGeneral_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_PointCloudGeneral_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PointCloudGeneral
#define TSeq holo_base_msg_common_PointCloudGeneralSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PointCloudGeneral
#define TSeq holo_base_msg_common_PointCloudGeneralSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_PointCloudGeneral* holo_base_msg_common_PointCloudGeneral_create();

NDDSUSERDllExport extern void
holo_base_msg_common_PointCloudGeneral_delete(holo_base_msg_common_PointCloudGeneral* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_common_PointCloudGeneral_initialize(holo_base_msg_common_PointCloudGeneral* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_PointCloudGeneral_initialize_ex(
    holo_base_msg_common_PointCloudGeneral* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_PointCloudGeneral_initialize_w_params(
    holo_base_msg_common_PointCloudGeneral* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_PointCloudGeneral_finalize(holo_base_msg_common_PointCloudGeneral* self);

NDDSUSERDllExport RTIBool
holo_base_msg_common_PointCloudGeneral_finalize_w_return(holo_base_msg_common_PointCloudGeneral* self);

NDDSUSERDllExport void holo_base_msg_common_PointCloudGeneral_finalize_ex(holo_base_msg_common_PointCloudGeneral* self,
                                                                          RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_common_PointCloudGeneral_finalize_w_params(
    holo_base_msg_common_PointCloudGeneral* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_PointCloudGeneral_finalize_optional_members(
    holo_base_msg_common_PointCloudGeneral* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_PointCloudGeneral_copy(
    holo_base_msg_common_PointCloudGeneral* dst, const holo_base_msg_common_PointCloudGeneral* src);

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

#endif /* PointCloudGeneral */
