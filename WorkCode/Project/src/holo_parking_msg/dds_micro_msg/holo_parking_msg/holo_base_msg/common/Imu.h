/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Imu.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef Imu_701605691_h
#define Imu_701605691_h

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

#include "holo_parking_msg/holo_base_msg/numerics/Vector.h"

typedef DDS_UnsignedLong holo_base_msg_common_ImuStatus;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_ImuStatus_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_ImuStatus_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_ImuStatus_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ImuStatus
#define TSeq holo_base_msg_common_ImuStatusSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ImuStatus
#define TSeq holo_base_msg_common_ImuStatusSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_ImuStatus* holo_base_msg_common_ImuStatus_create();

NDDSUSERDllExport extern void holo_base_msg_common_ImuStatus_delete(holo_base_msg_common_ImuStatus* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_ImuStatus_initialize(holo_base_msg_common_ImuStatus* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_ImuStatus_initialize_ex(holo_base_msg_common_ImuStatus* self,
                                                                       RTIBool                         allocatePointers,
                                                                       RTIBool                         allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_ImuStatus_initialize_w_params(
    holo_base_msg_common_ImuStatus* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_ImuStatus_finalize(holo_base_msg_common_ImuStatus* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_ImuStatus_finalize_w_return(holo_base_msg_common_ImuStatus* self);

NDDSUSERDllExport void holo_base_msg_common_ImuStatus_finalize_ex(holo_base_msg_common_ImuStatus* self,
                                                                  RTIBool                         deletePointers);

NDDSUSERDllExport void holo_base_msg_common_ImuStatus_finalize_w_params(
    holo_base_msg_common_ImuStatus* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_ImuStatus_finalize_optional_members(holo_base_msg_common_ImuStatus* self,
                                                                                RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_ImuStatus_copy(holo_base_msg_common_ImuStatus*       dst,
                                                              const holo_base_msg_common_ImuStatus* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_common_ImufTYPENAME;
}

struct holo_base_msg_common_ImufSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_common_ImufTypeSupport;
class holo_base_msg_common_ImufDataWriter;
class holo_base_msg_common_ImufDataReader;
#endif
class holo_base_msg_common_Imuf
{
public:
    typedef struct holo_base_msg_common_ImufSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_common_ImufTypeSupport TypeSupport;
    typedef holo_base_msg_common_ImufDataWriter  DataWriter;
    typedef holo_base_msg_common_ImufDataReader  DataReader;
#endif

    holo_base_msg_common_Timestamp  stamp;
    DDS_UnsignedLong                coord;
    holo_base_msg_numerics_Vector3f angular_velocity;
    holo_base_msg_numerics_Vector3f linear_acceleration;
    DDS_UnsignedLong                status;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_Imuf_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_Imuf_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_Imuf_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Imuf
#define TSeq holo_base_msg_common_ImufSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Imuf
#define TSeq holo_base_msg_common_ImufSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_Imuf* holo_base_msg_common_Imuf_create();

NDDSUSERDllExport extern void holo_base_msg_common_Imuf_delete(holo_base_msg_common_Imuf* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_Imuf_initialize(holo_base_msg_common_Imuf* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_Imuf_initialize_ex(holo_base_msg_common_Imuf* self,
                                                                  RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_Imuf_initialize_w_params(
    holo_base_msg_common_Imuf* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_Imuf_finalize(holo_base_msg_common_Imuf* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_Imuf_finalize_w_return(holo_base_msg_common_Imuf* self);

NDDSUSERDllExport void holo_base_msg_common_Imuf_finalize_ex(holo_base_msg_common_Imuf* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_common_Imuf_finalize_w_params(
    holo_base_msg_common_Imuf* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_Imuf_finalize_optional_members(holo_base_msg_common_Imuf* self,
                                                                           RTIBool                    deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_Imuf_copy(holo_base_msg_common_Imuf*       dst,
                                                         const holo_base_msg_common_Imuf* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_common_ImudTYPENAME;
}

struct holo_base_msg_common_ImudSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_common_ImudTypeSupport;
class holo_base_msg_common_ImudDataWriter;
class holo_base_msg_common_ImudDataReader;
#endif
class holo_base_msg_common_Imud
{
public:
    typedef struct holo_base_msg_common_ImudSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_common_ImudTypeSupport TypeSupport;
    typedef holo_base_msg_common_ImudDataWriter  DataWriter;
    typedef holo_base_msg_common_ImudDataReader  DataReader;
#endif

    holo_base_msg_common_Timestamp  stamp;
    DDS_UnsignedLong                coord;
    holo_base_msg_numerics_Vector3d angular_velocity;
    holo_base_msg_numerics_Vector3d linear_acceleration;
    DDS_UnsignedLong                status;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_Imud_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_Imud_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_Imud_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Imud
#define TSeq holo_base_msg_common_ImudSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Imud
#define TSeq holo_base_msg_common_ImudSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_Imud* holo_base_msg_common_Imud_create();

NDDSUSERDllExport extern void holo_base_msg_common_Imud_delete(holo_base_msg_common_Imud* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_Imud_initialize(holo_base_msg_common_Imud* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_Imud_initialize_ex(holo_base_msg_common_Imud* self,
                                                                  RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_Imud_initialize_w_params(
    holo_base_msg_common_Imud* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_Imud_finalize(holo_base_msg_common_Imud* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_Imud_finalize_w_return(holo_base_msg_common_Imud* self);

NDDSUSERDllExport void holo_base_msg_common_Imud_finalize_ex(holo_base_msg_common_Imud* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_common_Imud_finalize_w_params(
    holo_base_msg_common_Imud* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_Imud_finalize_optional_members(holo_base_msg_common_Imud* self,
                                                                           RTIBool                    deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_Imud_copy(holo_base_msg_common_Imud*       dst,
                                                         const holo_base_msg_common_Imud* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_common_ImuBiasfTYPENAME;
}

struct holo_base_msg_common_ImuBiasfSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_common_ImuBiasfTypeSupport;
class holo_base_msg_common_ImuBiasfDataWriter;
class holo_base_msg_common_ImuBiasfDataReader;
#endif
class holo_base_msg_common_ImuBiasf
{
public:
    typedef struct holo_base_msg_common_ImuBiasfSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_common_ImuBiasfTypeSupport TypeSupport;
    typedef holo_base_msg_common_ImuBiasfDataWriter  DataWriter;
    typedef holo_base_msg_common_ImuBiasfDataReader  DataReader;
#endif

    holo_base_msg_common_Timestamp  stamp;
    DDS_UnsignedLong                coord;
    holo_base_msg_numerics_Vector3f angular_velocity_bias;
    holo_base_msg_numerics_Vector3f linear_acceleration_bias;
    holo_base_msg_numerics_Vector3f angular_velocity_bias_cov;
    holo_base_msg_numerics_Vector3f linear_acceleration_bias_cov;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_ImuBiasf_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_ImuBiasf_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_ImuBiasf_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ImuBiasf
#define TSeq holo_base_msg_common_ImuBiasfSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ImuBiasf
#define TSeq holo_base_msg_common_ImuBiasfSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_ImuBiasf* holo_base_msg_common_ImuBiasf_create();

NDDSUSERDllExport extern void holo_base_msg_common_ImuBiasf_delete(holo_base_msg_common_ImuBiasf* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_ImuBiasf_initialize(holo_base_msg_common_ImuBiasf* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_ImuBiasf_initialize_ex(holo_base_msg_common_ImuBiasf* self,
                                                                      RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_ImuBiasf_initialize_w_params(
    holo_base_msg_common_ImuBiasf* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_ImuBiasf_finalize(holo_base_msg_common_ImuBiasf* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_ImuBiasf_finalize_w_return(holo_base_msg_common_ImuBiasf* self);

NDDSUSERDllExport void holo_base_msg_common_ImuBiasf_finalize_ex(holo_base_msg_common_ImuBiasf* self,
                                                                 RTIBool                        deletePointers);

NDDSUSERDllExport void holo_base_msg_common_ImuBiasf_finalize_w_params(
    holo_base_msg_common_ImuBiasf* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_ImuBiasf_finalize_optional_members(holo_base_msg_common_ImuBiasf* self,
                                                                               RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_ImuBiasf_copy(holo_base_msg_common_ImuBiasf*       dst,
                                                             const holo_base_msg_common_ImuBiasf* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_common_ImuBiasdTYPENAME;
}

struct holo_base_msg_common_ImuBiasdSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_common_ImuBiasdTypeSupport;
class holo_base_msg_common_ImuBiasdDataWriter;
class holo_base_msg_common_ImuBiasdDataReader;
#endif
class holo_base_msg_common_ImuBiasd
{
public:
    typedef struct holo_base_msg_common_ImuBiasdSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_common_ImuBiasdTypeSupport TypeSupport;
    typedef holo_base_msg_common_ImuBiasdDataWriter  DataWriter;
    typedef holo_base_msg_common_ImuBiasdDataReader  DataReader;
#endif

    holo_base_msg_common_Timestamp  stamp;
    DDS_UnsignedLong                coord;
    holo_base_msg_numerics_Vector3d angular_velocity_bias;
    holo_base_msg_numerics_Vector3d linear_acceleration_bias;
    holo_base_msg_numerics_Vector3d angular_velocity_bias_cov;
    holo_base_msg_numerics_Vector3d linear_acceleration_bias_cov;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_ImuBiasd_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_ImuBiasd_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_ImuBiasd_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ImuBiasd
#define TSeq holo_base_msg_common_ImuBiasdSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ImuBiasd
#define TSeq holo_base_msg_common_ImuBiasdSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_ImuBiasd* holo_base_msg_common_ImuBiasd_create();

NDDSUSERDllExport extern void holo_base_msg_common_ImuBiasd_delete(holo_base_msg_common_ImuBiasd* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_ImuBiasd_initialize(holo_base_msg_common_ImuBiasd* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_ImuBiasd_initialize_ex(holo_base_msg_common_ImuBiasd* self,
                                                                      RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_ImuBiasd_initialize_w_params(
    holo_base_msg_common_ImuBiasd* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_ImuBiasd_finalize(holo_base_msg_common_ImuBiasd* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_ImuBiasd_finalize_w_return(holo_base_msg_common_ImuBiasd* self);

NDDSUSERDllExport void holo_base_msg_common_ImuBiasd_finalize_ex(holo_base_msg_common_ImuBiasd* self,
                                                                 RTIBool                        deletePointers);

NDDSUSERDllExport void holo_base_msg_common_ImuBiasd_finalize_w_params(
    holo_base_msg_common_ImuBiasd* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_ImuBiasd_finalize_optional_members(holo_base_msg_common_ImuBiasd* self,
                                                                               RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_ImuBiasd_copy(holo_base_msg_common_ImuBiasd*       dst,
                                                             const holo_base_msg_common_ImuBiasd* src);

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

#endif /* Imu */
