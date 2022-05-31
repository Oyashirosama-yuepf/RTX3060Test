/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Path.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef Path_1297920848_h
#define Path_1297920848_h

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

#include "holo_parking_msg/holo_base_msg/geometry/Point.h"

extern "C" {

extern const char* holo_base_msg_common_PathPointfTYPENAME;
}

struct holo_base_msg_common_PathPointfSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_common_PathPointfTypeSupport;
class holo_base_msg_common_PathPointfDataWriter;
class holo_base_msg_common_PathPointfDataReader;
#endif
class holo_base_msg_common_PathPointf
{
public:
    typedef struct holo_base_msg_common_PathPointfSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_common_PathPointfTypeSupport TypeSupport;
    typedef holo_base_msg_common_PathPointfDataWriter  DataWriter;
    typedef holo_base_msg_common_PathPointfDataReader  DataReader;
#endif

    holo_base_msg_geometry_Point3f point;
    DDS_Float                      theta;
    DDS_Float                      curvature;
    DDS_Float                      speed;
    DDS_Float                      acceleration;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_PathPointf_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_PathPointf_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_PathPointf_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PathPointf
#define TSeq holo_base_msg_common_PathPointfSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PathPointf
#define TSeq holo_base_msg_common_PathPointfSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_PathPointf* holo_base_msg_common_PathPointf_create();

NDDSUSERDllExport extern void holo_base_msg_common_PathPointf_delete(holo_base_msg_common_PathPointf* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_PathPointf_initialize(holo_base_msg_common_PathPointf* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_PathPointf_initialize_ex(holo_base_msg_common_PathPointf* self,
                                                                        RTIBool allocatePointers,
                                                                        RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_PathPointf_initialize_w_params(
    holo_base_msg_common_PathPointf* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_PathPointf_finalize(holo_base_msg_common_PathPointf* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_PathPointf_finalize_w_return(holo_base_msg_common_PathPointf* self);

NDDSUSERDllExport void holo_base_msg_common_PathPointf_finalize_ex(holo_base_msg_common_PathPointf* self,
                                                                   RTIBool                          deletePointers);

NDDSUSERDllExport void holo_base_msg_common_PathPointf_finalize_w_params(
    holo_base_msg_common_PathPointf* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_PathPointf_finalize_optional_members(holo_base_msg_common_PathPointf* self,
                                                                                 RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_PathPointf_copy(holo_base_msg_common_PathPointf*       dst,
                                                               const holo_base_msg_common_PathPointf* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_common_PathPointdTYPENAME;
}

struct holo_base_msg_common_PathPointdSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_common_PathPointdTypeSupport;
class holo_base_msg_common_PathPointdDataWriter;
class holo_base_msg_common_PathPointdDataReader;
#endif
class holo_base_msg_common_PathPointd
{
public:
    typedef struct holo_base_msg_common_PathPointdSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_common_PathPointdTypeSupport TypeSupport;
    typedef holo_base_msg_common_PathPointdDataWriter  DataWriter;
    typedef holo_base_msg_common_PathPointdDataReader  DataReader;
#endif

    holo_base_msg_geometry_Point3d point;
    DDS_Double                     theta;
    DDS_Double                     curvature;
    DDS_Double                     speed;
    DDS_Double                     acceleration;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_PathPointd_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_PathPointd_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_PathPointd_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PathPointd
#define TSeq holo_base_msg_common_PathPointdSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PathPointd
#define TSeq holo_base_msg_common_PathPointdSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_PathPointd* holo_base_msg_common_PathPointd_create();

NDDSUSERDllExport extern void holo_base_msg_common_PathPointd_delete(holo_base_msg_common_PathPointd* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_PathPointd_initialize(holo_base_msg_common_PathPointd* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_PathPointd_initialize_ex(holo_base_msg_common_PathPointd* self,
                                                                        RTIBool allocatePointers,
                                                                        RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_PathPointd_initialize_w_params(
    holo_base_msg_common_PathPointd* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_PathPointd_finalize(holo_base_msg_common_PathPointd* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_PathPointd_finalize_w_return(holo_base_msg_common_PathPointd* self);

NDDSUSERDllExport void holo_base_msg_common_PathPointd_finalize_ex(holo_base_msg_common_PathPointd* self,
                                                                   RTIBool                          deletePointers);

NDDSUSERDllExport void holo_base_msg_common_PathPointd_finalize_w_params(
    holo_base_msg_common_PathPointd* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_PathPointd_finalize_optional_members(holo_base_msg_common_PathPointd* self,
                                                                                 RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_PathPointd_copy(holo_base_msg_common_PathPointd*       dst,
                                                               const holo_base_msg_common_PathPointd* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef holo_base_msg_common_PathPointfSeq holo_base_msg_common_PathPointfSequence;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_PathPointfSequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_PathPointfSequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_PathPointfSequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PathPointfSequence
#define TSeq holo_base_msg_common_PathPointfSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PathPointfSequence
#define TSeq holo_base_msg_common_PathPointfSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_PathPointfSequence* holo_base_msg_common_PathPointfSequence_create();

NDDSUSERDllExport extern void
holo_base_msg_common_PathPointfSequence_delete(holo_base_msg_common_PathPointfSequence* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_common_PathPointfSequence_initialize(holo_base_msg_common_PathPointfSequence* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_PathPointfSequence_initialize_ex(
    holo_base_msg_common_PathPointfSequence* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_PathPointfSequence_initialize_w_params(
    holo_base_msg_common_PathPointfSequence* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_common_PathPointfSequence_finalize(holo_base_msg_common_PathPointfSequence* self);

NDDSUSERDllExport RTIBool
holo_base_msg_common_PathPointfSequence_finalize_w_return(holo_base_msg_common_PathPointfSequence* self);

NDDSUSERDllExport void holo_base_msg_common_PathPointfSequence_finalize_ex(
    holo_base_msg_common_PathPointfSequence* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_common_PathPointfSequence_finalize_w_params(
    holo_base_msg_common_PathPointfSequence* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_PathPointfSequence_finalize_optional_members(
    holo_base_msg_common_PathPointfSequence* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_PathPointfSequence_copy(
    holo_base_msg_common_PathPointfSequence* dst, const holo_base_msg_common_PathPointfSequence* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef holo_base_msg_common_PathPointdSeq holo_base_msg_common_PathPointdSequence;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_PathPointdSequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_PathPointdSequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_PathPointdSequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PathPointdSequence
#define TSeq holo_base_msg_common_PathPointdSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PathPointdSequence
#define TSeq holo_base_msg_common_PathPointdSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_PathPointdSequence* holo_base_msg_common_PathPointdSequence_create();

NDDSUSERDllExport extern void
holo_base_msg_common_PathPointdSequence_delete(holo_base_msg_common_PathPointdSequence* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_common_PathPointdSequence_initialize(holo_base_msg_common_PathPointdSequence* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_PathPointdSequence_initialize_ex(
    holo_base_msg_common_PathPointdSequence* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_PathPointdSequence_initialize_w_params(
    holo_base_msg_common_PathPointdSequence* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_common_PathPointdSequence_finalize(holo_base_msg_common_PathPointdSequence* self);

NDDSUSERDllExport RTIBool
holo_base_msg_common_PathPointdSequence_finalize_w_return(holo_base_msg_common_PathPointdSequence* self);

NDDSUSERDllExport void holo_base_msg_common_PathPointdSequence_finalize_ex(
    holo_base_msg_common_PathPointdSequence* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_common_PathPointdSequence_finalize_w_params(
    holo_base_msg_common_PathPointdSequence* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_PathPointdSequence_finalize_optional_members(
    holo_base_msg_common_PathPointdSequence* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_PathPointdSequence_copy(
    holo_base_msg_common_PathPointdSequence* dst, const holo_base_msg_common_PathPointdSequence* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_common_PathfTYPENAME;
}

struct holo_base_msg_common_PathfSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_common_PathfTypeSupport;
class holo_base_msg_common_PathfDataWriter;
class holo_base_msg_common_PathfDataReader;
#endif
class holo_base_msg_common_Pathf
{
public:
    typedef struct holo_base_msg_common_PathfSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_common_PathfTypeSupport TypeSupport;
    typedef holo_base_msg_common_PathfDataWriter  DataWriter;
    typedef holo_base_msg_common_PathfDataReader  DataReader;
#endif

    holo_base_msg_common_Timestamp          stamp;
    DDS_UnsignedLong                        coord;
    holo_base_msg_common_PathPointfSequence point_list;
    DDS_UnsignedLong                        valid_value;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_Pathf_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_Pathf_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_Pathf_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Pathf
#define TSeq holo_base_msg_common_PathfSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Pathf
#define TSeq holo_base_msg_common_PathfSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_Pathf* holo_base_msg_common_Pathf_create();

NDDSUSERDllExport extern void holo_base_msg_common_Pathf_delete(holo_base_msg_common_Pathf* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_Pathf_initialize(holo_base_msg_common_Pathf* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_Pathf_initialize_ex(holo_base_msg_common_Pathf* self,
                                                                   RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_Pathf_initialize_w_params(
    holo_base_msg_common_Pathf* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_Pathf_finalize(holo_base_msg_common_Pathf* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_Pathf_finalize_w_return(holo_base_msg_common_Pathf* self);

NDDSUSERDllExport void holo_base_msg_common_Pathf_finalize_ex(holo_base_msg_common_Pathf* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_common_Pathf_finalize_w_params(
    holo_base_msg_common_Pathf* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_Pathf_finalize_optional_members(holo_base_msg_common_Pathf* self,
                                                                            RTIBool                     deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_Pathf_copy(holo_base_msg_common_Pathf*       dst,
                                                          const holo_base_msg_common_Pathf* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_common_PathdTYPENAME;
}

struct holo_base_msg_common_PathdSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_common_PathdTypeSupport;
class holo_base_msg_common_PathdDataWriter;
class holo_base_msg_common_PathdDataReader;
#endif
class holo_base_msg_common_Pathd
{
public:
    typedef struct holo_base_msg_common_PathdSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_common_PathdTypeSupport TypeSupport;
    typedef holo_base_msg_common_PathdDataWriter  DataWriter;
    typedef holo_base_msg_common_PathdDataReader  DataReader;
#endif

    holo_base_msg_common_Timestamp          stamp;
    DDS_UnsignedLong                        coord;
    holo_base_msg_common_PathPointdSequence point_list;
    DDS_UnsignedLong                        valid_value;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_Pathd_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_Pathd_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_Pathd_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Pathd
#define TSeq holo_base_msg_common_PathdSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Pathd
#define TSeq holo_base_msg_common_PathdSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_Pathd* holo_base_msg_common_Pathd_create();

NDDSUSERDllExport extern void holo_base_msg_common_Pathd_delete(holo_base_msg_common_Pathd* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_Pathd_initialize(holo_base_msg_common_Pathd* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_Pathd_initialize_ex(holo_base_msg_common_Pathd* self,
                                                                   RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_Pathd_initialize_w_params(
    holo_base_msg_common_Pathd* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_Pathd_finalize(holo_base_msg_common_Pathd* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_Pathd_finalize_w_return(holo_base_msg_common_Pathd* self);

NDDSUSERDllExport void holo_base_msg_common_Pathd_finalize_ex(holo_base_msg_common_Pathd* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_common_Pathd_finalize_w_params(
    holo_base_msg_common_Pathd* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_Pathd_finalize_optional_members(holo_base_msg_common_Pathd* self,
                                                                            RTIBool                     deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_Pathd_copy(holo_base_msg_common_Pathd*       dst,
                                                          const holo_base_msg_common_Pathd* src);

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

#endif /* Path */
