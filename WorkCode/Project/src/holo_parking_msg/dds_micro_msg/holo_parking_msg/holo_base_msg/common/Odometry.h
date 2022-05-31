/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Odometry.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef Odometry_1402263134_h
#define Odometry_1402263134_h

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

#include "holo_parking_msg/holo_base_msg/geometry/Pose.h"

#include "holo_parking_msg/holo_base_msg/numerics/Vector.h"

#include "holo_parking_msg/holo_base_msg/numerics/Matrix.h"

typedef DDS_UnsignedShort holo_base_msg_common_OdometrySource;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_OdometrySource_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_OdometrySource_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_OdometrySource_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_OdometrySource
#define TSeq holo_base_msg_common_OdometrySourceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_OdometrySource
#define TSeq holo_base_msg_common_OdometrySourceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_OdometrySource* holo_base_msg_common_OdometrySource_create();

NDDSUSERDllExport extern void holo_base_msg_common_OdometrySource_delete(holo_base_msg_common_OdometrySource* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_OdometrySource_initialize(holo_base_msg_common_OdometrySource* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_OdometrySource_initialize_ex(holo_base_msg_common_OdometrySource* self,
                                                                            RTIBool allocatePointers,
                                                                            RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_OdometrySource_initialize_w_params(
    holo_base_msg_common_OdometrySource* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_OdometrySource_finalize(holo_base_msg_common_OdometrySource* self);

NDDSUSERDllExport RTIBool
holo_base_msg_common_OdometrySource_finalize_w_return(holo_base_msg_common_OdometrySource* self);

NDDSUSERDllExport void holo_base_msg_common_OdometrySource_finalize_ex(holo_base_msg_common_OdometrySource* self,
                                                                       RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_common_OdometrySource_finalize_w_params(
    holo_base_msg_common_OdometrySource* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_OdometrySource_finalize_optional_members(
    holo_base_msg_common_OdometrySource* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_OdometrySource_copy(holo_base_msg_common_OdometrySource*       dst,
                                                                   const holo_base_msg_common_OdometrySource* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_UnsignedShort holo_base_msg_common_OdometryStatus;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_OdometryStatus_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_OdometryStatus_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_OdometryStatus_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_OdometryStatus
#define TSeq holo_base_msg_common_OdometryStatusSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_OdometryStatus
#define TSeq holo_base_msg_common_OdometryStatusSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_OdometryStatus* holo_base_msg_common_OdometryStatus_create();

NDDSUSERDllExport extern void holo_base_msg_common_OdometryStatus_delete(holo_base_msg_common_OdometryStatus* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_OdometryStatus_initialize(holo_base_msg_common_OdometryStatus* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_OdometryStatus_initialize_ex(holo_base_msg_common_OdometryStatus* self,
                                                                            RTIBool allocatePointers,
                                                                            RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_OdometryStatus_initialize_w_params(
    holo_base_msg_common_OdometryStatus* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_OdometryStatus_finalize(holo_base_msg_common_OdometryStatus* self);

NDDSUSERDllExport RTIBool
holo_base_msg_common_OdometryStatus_finalize_w_return(holo_base_msg_common_OdometryStatus* self);

NDDSUSERDllExport void holo_base_msg_common_OdometryStatus_finalize_ex(holo_base_msg_common_OdometryStatus* self,
                                                                       RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_common_OdometryStatus_finalize_w_params(
    holo_base_msg_common_OdometryStatus* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_OdometryStatus_finalize_optional_members(
    holo_base_msg_common_OdometryStatus* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_OdometryStatus_copy(holo_base_msg_common_OdometryStatus*       dst,
                                                                   const holo_base_msg_common_OdometryStatus* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_common_OdometryfTYPENAME;
}

struct holo_base_msg_common_OdometryfSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_common_OdometryfTypeSupport;
class holo_base_msg_common_OdometryfDataWriter;
class holo_base_msg_common_OdometryfDataReader;
#endif
class holo_base_msg_common_Odometryf
{
public:
    typedef struct holo_base_msg_common_OdometryfSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_common_OdometryfTypeSupport TypeSupport;
    typedef holo_base_msg_common_OdometryfDataWriter  DataWriter;
    typedef holo_base_msg_common_OdometryfDataReader  DataReader;
#endif

    holo_base_msg_common_Timestamp   stamp;
    DDS_UnsignedLong                 coord;
    DDS_UnsignedLong                 child_coord;
    DDS_UnsignedShort                status;
    DDS_UnsignedShort                source;
    DDS_UnsignedLong                 precision;
    holo_base_msg_geometry_Pose3f    pose;
    holo_base_msg_numerics_Vector6f  velocity;
    holo_base_msg_numerics_Matrix66f pose_covariance;
    holo_base_msg_numerics_Matrix66f velocity_covariance;
    holo_base_msg_numerics_Vector3f  linear_acceleration;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_Odometryf_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_Odometryf_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_Odometryf_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Odometryf
#define TSeq holo_base_msg_common_OdometryfSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Odometryf
#define TSeq holo_base_msg_common_OdometryfSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_Odometryf* holo_base_msg_common_Odometryf_create();

NDDSUSERDllExport extern void holo_base_msg_common_Odometryf_delete(holo_base_msg_common_Odometryf* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_Odometryf_initialize(holo_base_msg_common_Odometryf* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_Odometryf_initialize_ex(holo_base_msg_common_Odometryf* self,
                                                                       RTIBool                         allocatePointers,
                                                                       RTIBool                         allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_Odometryf_initialize_w_params(
    holo_base_msg_common_Odometryf* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_Odometryf_finalize(holo_base_msg_common_Odometryf* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_Odometryf_finalize_w_return(holo_base_msg_common_Odometryf* self);

NDDSUSERDllExport void holo_base_msg_common_Odometryf_finalize_ex(holo_base_msg_common_Odometryf* self,
                                                                  RTIBool                         deletePointers);

NDDSUSERDllExport void holo_base_msg_common_Odometryf_finalize_w_params(
    holo_base_msg_common_Odometryf* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_Odometryf_finalize_optional_members(holo_base_msg_common_Odometryf* self,
                                                                                RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_Odometryf_copy(holo_base_msg_common_Odometryf*       dst,
                                                              const holo_base_msg_common_Odometryf* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_common_OdometrydTYPENAME;
}

struct holo_base_msg_common_OdometrydSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_common_OdometrydTypeSupport;
class holo_base_msg_common_OdometrydDataWriter;
class holo_base_msg_common_OdometrydDataReader;
#endif
class holo_base_msg_common_Odometryd
{
public:
    typedef struct holo_base_msg_common_OdometrydSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_common_OdometrydTypeSupport TypeSupport;
    typedef holo_base_msg_common_OdometrydDataWriter  DataWriter;
    typedef holo_base_msg_common_OdometrydDataReader  DataReader;
#endif

    holo_base_msg_common_Timestamp   stamp;
    DDS_UnsignedLong                 coord;
    DDS_UnsignedLong                 child_coord;
    DDS_UnsignedShort                status;
    DDS_UnsignedShort                source;
    DDS_UnsignedLong                 precision;
    holo_base_msg_geometry_Pose3d    pose;
    holo_base_msg_numerics_Vector6d  velocity;
    holo_base_msg_numerics_Matrix66d pose_covariance;
    holo_base_msg_numerics_Matrix66d velocity_covariance;
    holo_base_msg_numerics_Vector3d  linear_acceleration;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_Odometryd_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_Odometryd_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_Odometryd_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Odometryd
#define TSeq holo_base_msg_common_OdometrydSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Odometryd
#define TSeq holo_base_msg_common_OdometrydSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_Odometryd* holo_base_msg_common_Odometryd_create();

NDDSUSERDllExport extern void holo_base_msg_common_Odometryd_delete(holo_base_msg_common_Odometryd* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_Odometryd_initialize(holo_base_msg_common_Odometryd* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_Odometryd_initialize_ex(holo_base_msg_common_Odometryd* self,
                                                                       RTIBool                         allocatePointers,
                                                                       RTIBool                         allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_Odometryd_initialize_w_params(
    holo_base_msg_common_Odometryd* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_Odometryd_finalize(holo_base_msg_common_Odometryd* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_Odometryd_finalize_w_return(holo_base_msg_common_Odometryd* self);

NDDSUSERDllExport void holo_base_msg_common_Odometryd_finalize_ex(holo_base_msg_common_Odometryd* self,
                                                                  RTIBool                         deletePointers);

NDDSUSERDllExport void holo_base_msg_common_Odometryd_finalize_w_params(
    holo_base_msg_common_Odometryd* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_Odometryd_finalize_optional_members(holo_base_msg_common_Odometryd* self,
                                                                                RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_Odometryd_copy(holo_base_msg_common_Odometryd*       dst,
                                                              const holo_base_msg_common_Odometryd* src);

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

#endif /* Odometry */
