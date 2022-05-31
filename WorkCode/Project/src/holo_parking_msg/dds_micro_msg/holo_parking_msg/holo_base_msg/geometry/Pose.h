/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Pose.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef Pose_806669959_h
#define Pose_806669959_h

#ifndef rti_me_cpp_hxx
#include "rti_me_cpp.hxx"
#endif

#include "dds_c/dds_c_typecode.h"

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#include "holo_parking_msg/holo_base_msg/geometry/Rot.h"

#include "holo_parking_msg/holo_base_msg/geometry/Point.h"

extern "C" {

extern const char* holo_base_msg_geometry_Pose3fTYPENAME;
}

struct holo_base_msg_geometry_Pose3fSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_geometry_Pose3fTypeSupport;
class holo_base_msg_geometry_Pose3fDataWriter;
class holo_base_msg_geometry_Pose3fDataReader;
#endif
class holo_base_msg_geometry_Pose3f
{
public:
    typedef struct holo_base_msg_geometry_Pose3fSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_geometry_Pose3fTypeSupport TypeSupport;
    typedef holo_base_msg_geometry_Pose3fDataWriter  DataWriter;
    typedef holo_base_msg_geometry_Pose3fDataReader  DataReader;
#endif

    holo_base_msg_geometry_Rot3f   rotation;
    holo_base_msg_geometry_Point3f translation;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_geometry_Pose3f_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_geometry_Pose3f_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_geometry_Pose3f_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Pose3f
#define TSeq holo_base_msg_geometry_Pose3fSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Pose3f
#define TSeq holo_base_msg_geometry_Pose3fSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_geometry_Pose3f* holo_base_msg_geometry_Pose3f_create();

NDDSUSERDllExport extern void holo_base_msg_geometry_Pose3f_delete(holo_base_msg_geometry_Pose3f* sample);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Pose3f_initialize(holo_base_msg_geometry_Pose3f* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Pose3f_initialize_ex(holo_base_msg_geometry_Pose3f* self,
                                                                      RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Pose3f_initialize_w_params(
    holo_base_msg_geometry_Pose3f* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Pose3f_finalize(holo_base_msg_geometry_Pose3f* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Pose3f_finalize_w_return(holo_base_msg_geometry_Pose3f* self);

NDDSUSERDllExport void holo_base_msg_geometry_Pose3f_finalize_ex(holo_base_msg_geometry_Pose3f* self,
                                                                 RTIBool                        deletePointers);

NDDSUSERDllExport void holo_base_msg_geometry_Pose3f_finalize_w_params(
    holo_base_msg_geometry_Pose3f* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_geometry_Pose3f_finalize_optional_members(holo_base_msg_geometry_Pose3f* self,
                                                                               RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Pose3f_copy(holo_base_msg_geometry_Pose3f*       dst,
                                                             const holo_base_msg_geometry_Pose3f* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_geometry_Pose3dTYPENAME;
}

struct holo_base_msg_geometry_Pose3dSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_geometry_Pose3dTypeSupport;
class holo_base_msg_geometry_Pose3dDataWriter;
class holo_base_msg_geometry_Pose3dDataReader;
#endif
class holo_base_msg_geometry_Pose3d
{
public:
    typedef struct holo_base_msg_geometry_Pose3dSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_geometry_Pose3dTypeSupport TypeSupport;
    typedef holo_base_msg_geometry_Pose3dDataWriter  DataWriter;
    typedef holo_base_msg_geometry_Pose3dDataReader  DataReader;
#endif

    holo_base_msg_geometry_Rot3d   rotation;
    holo_base_msg_geometry_Point3d translation;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_geometry_Pose3d_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_geometry_Pose3d_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_geometry_Pose3d_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Pose3d
#define TSeq holo_base_msg_geometry_Pose3dSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Pose3d
#define TSeq holo_base_msg_geometry_Pose3dSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_geometry_Pose3d* holo_base_msg_geometry_Pose3d_create();

NDDSUSERDllExport extern void holo_base_msg_geometry_Pose3d_delete(holo_base_msg_geometry_Pose3d* sample);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Pose3d_initialize(holo_base_msg_geometry_Pose3d* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Pose3d_initialize_ex(holo_base_msg_geometry_Pose3d* self,
                                                                      RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Pose3d_initialize_w_params(
    holo_base_msg_geometry_Pose3d* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Pose3d_finalize(holo_base_msg_geometry_Pose3d* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Pose3d_finalize_w_return(holo_base_msg_geometry_Pose3d* self);

NDDSUSERDllExport void holo_base_msg_geometry_Pose3d_finalize_ex(holo_base_msg_geometry_Pose3d* self,
                                                                 RTIBool                        deletePointers);

NDDSUSERDllExport void holo_base_msg_geometry_Pose3d_finalize_w_params(
    holo_base_msg_geometry_Pose3d* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_geometry_Pose3d_finalize_optional_members(holo_base_msg_geometry_Pose3d* self,
                                                                               RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Pose3d_copy(holo_base_msg_geometry_Pose3d*       dst,
                                                             const holo_base_msg_geometry_Pose3d* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_geometry_Pose2fTYPENAME;
}

struct holo_base_msg_geometry_Pose2fSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_geometry_Pose2fTypeSupport;
class holo_base_msg_geometry_Pose2fDataWriter;
class holo_base_msg_geometry_Pose2fDataReader;
#endif
class holo_base_msg_geometry_Pose2f
{
public:
    typedef struct holo_base_msg_geometry_Pose2fSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_geometry_Pose2fTypeSupport TypeSupport;
    typedef holo_base_msg_geometry_Pose2fDataWriter  DataWriter;
    typedef holo_base_msg_geometry_Pose2fDataReader  DataReader;
#endif

    holo_base_msg_geometry_Rot2f   rotation;
    holo_base_msg_geometry_Point2f translation;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_geometry_Pose2f_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_geometry_Pose2f_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_geometry_Pose2f_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Pose2f
#define TSeq holo_base_msg_geometry_Pose2fSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Pose2f
#define TSeq holo_base_msg_geometry_Pose2fSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_geometry_Pose2f* holo_base_msg_geometry_Pose2f_create();

NDDSUSERDllExport extern void holo_base_msg_geometry_Pose2f_delete(holo_base_msg_geometry_Pose2f* sample);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Pose2f_initialize(holo_base_msg_geometry_Pose2f* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Pose2f_initialize_ex(holo_base_msg_geometry_Pose2f* self,
                                                                      RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Pose2f_initialize_w_params(
    holo_base_msg_geometry_Pose2f* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Pose2f_finalize(holo_base_msg_geometry_Pose2f* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Pose2f_finalize_w_return(holo_base_msg_geometry_Pose2f* self);

NDDSUSERDllExport void holo_base_msg_geometry_Pose2f_finalize_ex(holo_base_msg_geometry_Pose2f* self,
                                                                 RTIBool                        deletePointers);

NDDSUSERDllExport void holo_base_msg_geometry_Pose2f_finalize_w_params(
    holo_base_msg_geometry_Pose2f* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_geometry_Pose2f_finalize_optional_members(holo_base_msg_geometry_Pose2f* self,
                                                                               RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Pose2f_copy(holo_base_msg_geometry_Pose2f*       dst,
                                                             const holo_base_msg_geometry_Pose2f* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_geometry_Pose2dTYPENAME;
}

struct holo_base_msg_geometry_Pose2dSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_geometry_Pose2dTypeSupport;
class holo_base_msg_geometry_Pose2dDataWriter;
class holo_base_msg_geometry_Pose2dDataReader;
#endif
class holo_base_msg_geometry_Pose2d
{
public:
    typedef struct holo_base_msg_geometry_Pose2dSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_geometry_Pose2dTypeSupport TypeSupport;
    typedef holo_base_msg_geometry_Pose2dDataWriter  DataWriter;
    typedef holo_base_msg_geometry_Pose2dDataReader  DataReader;
#endif

    holo_base_msg_geometry_Rot2d   rotation;
    holo_base_msg_geometry_Point2d translation;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_geometry_Pose2d_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_geometry_Pose2d_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_geometry_Pose2d_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Pose2d
#define TSeq holo_base_msg_geometry_Pose2dSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Pose2d
#define TSeq holo_base_msg_geometry_Pose2dSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_geometry_Pose2d* holo_base_msg_geometry_Pose2d_create();

NDDSUSERDllExport extern void holo_base_msg_geometry_Pose2d_delete(holo_base_msg_geometry_Pose2d* sample);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Pose2d_initialize(holo_base_msg_geometry_Pose2d* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Pose2d_initialize_ex(holo_base_msg_geometry_Pose2d* self,
                                                                      RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Pose2d_initialize_w_params(
    holo_base_msg_geometry_Pose2d* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Pose2d_finalize(holo_base_msg_geometry_Pose2d* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Pose2d_finalize_w_return(holo_base_msg_geometry_Pose2d* self);

NDDSUSERDllExport void holo_base_msg_geometry_Pose2d_finalize_ex(holo_base_msg_geometry_Pose2d* self,
                                                                 RTIBool                        deletePointers);

NDDSUSERDllExport void holo_base_msg_geometry_Pose2d_finalize_w_params(
    holo_base_msg_geometry_Pose2d* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_geometry_Pose2d_finalize_optional_members(holo_base_msg_geometry_Pose2d* self,
                                                                               RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Pose2d_copy(holo_base_msg_geometry_Pose2d*       dst,
                                                             const holo_base_msg_geometry_Pose2d* src);

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

#endif /* Pose */
