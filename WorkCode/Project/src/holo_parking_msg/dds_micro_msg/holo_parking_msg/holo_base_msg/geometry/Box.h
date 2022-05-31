/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Box.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef Box_1735834481_h
#define Box_1735834481_h

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

#include "holo_parking_msg/holo_base_msg/geometry/Pose.h"

extern "C" {

extern const char* holo_base_msg_geometry_Box2fTYPENAME;
}

struct holo_base_msg_geometry_Box2fSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_geometry_Box2fTypeSupport;
class holo_base_msg_geometry_Box2fDataWriter;
class holo_base_msg_geometry_Box2fDataReader;
#endif
class holo_base_msg_geometry_Box2f
{
public:
    typedef struct holo_base_msg_geometry_Box2fSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_geometry_Box2fTypeSupport TypeSupport;
    typedef holo_base_msg_geometry_Box2fDataWriter  DataWriter;
    typedef holo_base_msg_geometry_Box2fDataReader  DataReader;
#endif

    DDS_Float                     width;
    DDS_Float                     height;
    holo_base_msg_geometry_Pose2f pose;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_geometry_Box2f_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_geometry_Box2f_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_geometry_Box2f_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Box2f
#define TSeq holo_base_msg_geometry_Box2fSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Box2f
#define TSeq holo_base_msg_geometry_Box2fSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_geometry_Box2f* holo_base_msg_geometry_Box2f_create();

NDDSUSERDllExport extern void holo_base_msg_geometry_Box2f_delete(holo_base_msg_geometry_Box2f* sample);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Box2f_initialize(holo_base_msg_geometry_Box2f* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Box2f_initialize_ex(holo_base_msg_geometry_Box2f* self,
                                                                     RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Box2f_initialize_w_params(
    holo_base_msg_geometry_Box2f* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Box2f_finalize(holo_base_msg_geometry_Box2f* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Box2f_finalize_w_return(holo_base_msg_geometry_Box2f* self);

NDDSUSERDllExport void holo_base_msg_geometry_Box2f_finalize_ex(holo_base_msg_geometry_Box2f* self,
                                                                RTIBool                       deletePointers);

NDDSUSERDllExport void holo_base_msg_geometry_Box2f_finalize_w_params(
    holo_base_msg_geometry_Box2f* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_geometry_Box2f_finalize_optional_members(holo_base_msg_geometry_Box2f* self,
                                                                              RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Box2f_copy(holo_base_msg_geometry_Box2f*       dst,
                                                            const holo_base_msg_geometry_Box2f* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_geometry_Box2dTYPENAME;
}

struct holo_base_msg_geometry_Box2dSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_geometry_Box2dTypeSupport;
class holo_base_msg_geometry_Box2dDataWriter;
class holo_base_msg_geometry_Box2dDataReader;
#endif
class holo_base_msg_geometry_Box2d
{
public:
    typedef struct holo_base_msg_geometry_Box2dSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_geometry_Box2dTypeSupport TypeSupport;
    typedef holo_base_msg_geometry_Box2dDataWriter  DataWriter;
    typedef holo_base_msg_geometry_Box2dDataReader  DataReader;
#endif

    DDS_Double                    width;
    DDS_Double                    height;
    holo_base_msg_geometry_Pose2d pose;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_geometry_Box2d_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_geometry_Box2d_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_geometry_Box2d_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Box2d
#define TSeq holo_base_msg_geometry_Box2dSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Box2d
#define TSeq holo_base_msg_geometry_Box2dSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_geometry_Box2d* holo_base_msg_geometry_Box2d_create();

NDDSUSERDllExport extern void holo_base_msg_geometry_Box2d_delete(holo_base_msg_geometry_Box2d* sample);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Box2d_initialize(holo_base_msg_geometry_Box2d* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Box2d_initialize_ex(holo_base_msg_geometry_Box2d* self,
                                                                     RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Box2d_initialize_w_params(
    holo_base_msg_geometry_Box2d* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Box2d_finalize(holo_base_msg_geometry_Box2d* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Box2d_finalize_w_return(holo_base_msg_geometry_Box2d* self);

NDDSUSERDllExport void holo_base_msg_geometry_Box2d_finalize_ex(holo_base_msg_geometry_Box2d* self,
                                                                RTIBool                       deletePointers);

NDDSUSERDllExport void holo_base_msg_geometry_Box2d_finalize_w_params(
    holo_base_msg_geometry_Box2d* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_geometry_Box2d_finalize_optional_members(holo_base_msg_geometry_Box2d* self,
                                                                              RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Box2d_copy(holo_base_msg_geometry_Box2d*       dst,
                                                            const holo_base_msg_geometry_Box2d* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_geometry_Box3fTYPENAME;
}

struct holo_base_msg_geometry_Box3fSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_geometry_Box3fTypeSupport;
class holo_base_msg_geometry_Box3fDataWriter;
class holo_base_msg_geometry_Box3fDataReader;
#endif
class holo_base_msg_geometry_Box3f
{
public:
    typedef struct holo_base_msg_geometry_Box3fSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_geometry_Box3fTypeSupport TypeSupport;
    typedef holo_base_msg_geometry_Box3fDataWriter  DataWriter;
    typedef holo_base_msg_geometry_Box3fDataReader  DataReader;
#endif

    DDS_Float                     width;
    DDS_Float                     height;
    DDS_Float                     depth;
    holo_base_msg_geometry_Pose3f pose;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_geometry_Box3f_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_geometry_Box3f_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_geometry_Box3f_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Box3f
#define TSeq holo_base_msg_geometry_Box3fSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Box3f
#define TSeq holo_base_msg_geometry_Box3fSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_geometry_Box3f* holo_base_msg_geometry_Box3f_create();

NDDSUSERDllExport extern void holo_base_msg_geometry_Box3f_delete(holo_base_msg_geometry_Box3f* sample);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Box3f_initialize(holo_base_msg_geometry_Box3f* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Box3f_initialize_ex(holo_base_msg_geometry_Box3f* self,
                                                                     RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Box3f_initialize_w_params(
    holo_base_msg_geometry_Box3f* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Box3f_finalize(holo_base_msg_geometry_Box3f* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Box3f_finalize_w_return(holo_base_msg_geometry_Box3f* self);

NDDSUSERDllExport void holo_base_msg_geometry_Box3f_finalize_ex(holo_base_msg_geometry_Box3f* self,
                                                                RTIBool                       deletePointers);

NDDSUSERDllExport void holo_base_msg_geometry_Box3f_finalize_w_params(
    holo_base_msg_geometry_Box3f* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_geometry_Box3f_finalize_optional_members(holo_base_msg_geometry_Box3f* self,
                                                                              RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Box3f_copy(holo_base_msg_geometry_Box3f*       dst,
                                                            const holo_base_msg_geometry_Box3f* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_geometry_Box3dTYPENAME;
}

struct holo_base_msg_geometry_Box3dSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_geometry_Box3dTypeSupport;
class holo_base_msg_geometry_Box3dDataWriter;
class holo_base_msg_geometry_Box3dDataReader;
#endif
class holo_base_msg_geometry_Box3d
{
public:
    typedef struct holo_base_msg_geometry_Box3dSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_geometry_Box3dTypeSupport TypeSupport;
    typedef holo_base_msg_geometry_Box3dDataWriter  DataWriter;
    typedef holo_base_msg_geometry_Box3dDataReader  DataReader;
#endif

    DDS_Double                    width;
    DDS_Double                    height;
    DDS_Double                    depth;
    holo_base_msg_geometry_Pose3d pose;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_geometry_Box3d_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_geometry_Box3d_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_geometry_Box3d_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Box3d
#define TSeq holo_base_msg_geometry_Box3dSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Box3d
#define TSeq holo_base_msg_geometry_Box3dSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_geometry_Box3d* holo_base_msg_geometry_Box3d_create();

NDDSUSERDllExport extern void holo_base_msg_geometry_Box3d_delete(holo_base_msg_geometry_Box3d* sample);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Box3d_initialize(holo_base_msg_geometry_Box3d* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Box3d_initialize_ex(holo_base_msg_geometry_Box3d* self,
                                                                     RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Box3d_initialize_w_params(
    holo_base_msg_geometry_Box3d* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Box3d_finalize(holo_base_msg_geometry_Box3d* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Box3d_finalize_w_return(holo_base_msg_geometry_Box3d* self);

NDDSUSERDllExport void holo_base_msg_geometry_Box3d_finalize_ex(holo_base_msg_geometry_Box3d* self,
                                                                RTIBool                       deletePointers);

NDDSUSERDllExport void holo_base_msg_geometry_Box3d_finalize_w_params(
    holo_base_msg_geometry_Box3d* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_geometry_Box3d_finalize_optional_members(holo_base_msg_geometry_Box3d* self,
                                                                              RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Box3d_copy(holo_base_msg_geometry_Box3d*       dst,
                                                            const holo_base_msg_geometry_Box3d* src);

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

#endif /* Box */
