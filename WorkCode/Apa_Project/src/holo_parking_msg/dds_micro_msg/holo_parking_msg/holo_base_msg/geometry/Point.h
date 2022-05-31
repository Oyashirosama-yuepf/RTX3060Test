/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Point.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef Point_727602850_h
#define Point_727602850_h

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

extern "C" {

extern const char* holo_base_msg_geometry_Point3fTYPENAME;
}

struct holo_base_msg_geometry_Point3fSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_geometry_Point3fTypeSupport;
class holo_base_msg_geometry_Point3fDataWriter;
class holo_base_msg_geometry_Point3fDataReader;
#endif
class holo_base_msg_geometry_Point3f
{
public:
    typedef struct holo_base_msg_geometry_Point3fSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_geometry_Point3fTypeSupport TypeSupport;
    typedef holo_base_msg_geometry_Point3fDataWriter  DataWriter;
    typedef holo_base_msg_geometry_Point3fDataReader  DataReader;
#endif

    DDS_Float x;
    DDS_Float y;
    DDS_Float z;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_geometry_Point3f_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_geometry_Point3f_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_geometry_Point3f_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point3f
#define TSeq holo_base_msg_geometry_Point3fSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point3f
#define TSeq holo_base_msg_geometry_Point3fSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_geometry_Point3f* holo_base_msg_geometry_Point3f_create();

NDDSUSERDllExport extern void holo_base_msg_geometry_Point3f_delete(holo_base_msg_geometry_Point3f* sample);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point3f_initialize(holo_base_msg_geometry_Point3f* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point3f_initialize_ex(holo_base_msg_geometry_Point3f* self,
                                                                       RTIBool                         allocatePointers,
                                                                       RTIBool                         allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point3f_initialize_w_params(
    holo_base_msg_geometry_Point3f* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point3f_finalize(holo_base_msg_geometry_Point3f* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point3f_finalize_w_return(holo_base_msg_geometry_Point3f* self);

NDDSUSERDllExport void holo_base_msg_geometry_Point3f_finalize_ex(holo_base_msg_geometry_Point3f* self,
                                                                  RTIBool                         deletePointers);

NDDSUSERDllExport void holo_base_msg_geometry_Point3f_finalize_w_params(
    holo_base_msg_geometry_Point3f* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_geometry_Point3f_finalize_optional_members(holo_base_msg_geometry_Point3f* self,
                                                                                RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point3f_copy(holo_base_msg_geometry_Point3f*       dst,
                                                              const holo_base_msg_geometry_Point3f* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef holo_base_msg_geometry_Point3fSeq holo_base_msg_geometry_Point3fSequence;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_geometry_Point3fSequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_geometry_Point3fSequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_geometry_Point3fSequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point3fSequence
#define TSeq holo_base_msg_geometry_Point3fSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point3fSequence
#define TSeq holo_base_msg_geometry_Point3fSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_geometry_Point3fSequence* holo_base_msg_geometry_Point3fSequence_create();

NDDSUSERDllExport extern void
holo_base_msg_geometry_Point3fSequence_delete(holo_base_msg_geometry_Point3fSequence* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_geometry_Point3fSequence_initialize(holo_base_msg_geometry_Point3fSequence* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point3fSequence_initialize_ex(
    holo_base_msg_geometry_Point3fSequence* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point3fSequence_initialize_w_params(
    holo_base_msg_geometry_Point3fSequence* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point3fSequence_finalize(holo_base_msg_geometry_Point3fSequence* self);

NDDSUSERDllExport RTIBool
holo_base_msg_geometry_Point3fSequence_finalize_w_return(holo_base_msg_geometry_Point3fSequence* self);

NDDSUSERDllExport void holo_base_msg_geometry_Point3fSequence_finalize_ex(holo_base_msg_geometry_Point3fSequence* self,
                                                                          RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_geometry_Point3fSequence_finalize_w_params(
    holo_base_msg_geometry_Point3fSequence* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_geometry_Point3fSequence_finalize_optional_members(
    holo_base_msg_geometry_Point3fSequence* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point3fSequence_copy(
    holo_base_msg_geometry_Point3fSequence* dst, const holo_base_msg_geometry_Point3fSequence* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_geometry_Point3dTYPENAME;
}

struct holo_base_msg_geometry_Point3dSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_geometry_Point3dTypeSupport;
class holo_base_msg_geometry_Point3dDataWriter;
class holo_base_msg_geometry_Point3dDataReader;
#endif
class holo_base_msg_geometry_Point3d
{
public:
    typedef struct holo_base_msg_geometry_Point3dSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_geometry_Point3dTypeSupport TypeSupport;
    typedef holo_base_msg_geometry_Point3dDataWriter  DataWriter;
    typedef holo_base_msg_geometry_Point3dDataReader  DataReader;
#endif

    DDS_Double x;
    DDS_Double y;
    DDS_Double z;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_geometry_Point3d_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_geometry_Point3d_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_geometry_Point3d_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point3d
#define TSeq holo_base_msg_geometry_Point3dSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point3d
#define TSeq holo_base_msg_geometry_Point3dSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_geometry_Point3d* holo_base_msg_geometry_Point3d_create();

NDDSUSERDllExport extern void holo_base_msg_geometry_Point3d_delete(holo_base_msg_geometry_Point3d* sample);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point3d_initialize(holo_base_msg_geometry_Point3d* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point3d_initialize_ex(holo_base_msg_geometry_Point3d* self,
                                                                       RTIBool                         allocatePointers,
                                                                       RTIBool                         allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point3d_initialize_w_params(
    holo_base_msg_geometry_Point3d* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point3d_finalize(holo_base_msg_geometry_Point3d* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point3d_finalize_w_return(holo_base_msg_geometry_Point3d* self);

NDDSUSERDllExport void holo_base_msg_geometry_Point3d_finalize_ex(holo_base_msg_geometry_Point3d* self,
                                                                  RTIBool                         deletePointers);

NDDSUSERDllExport void holo_base_msg_geometry_Point3d_finalize_w_params(
    holo_base_msg_geometry_Point3d* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_geometry_Point3d_finalize_optional_members(holo_base_msg_geometry_Point3d* self,
                                                                                RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point3d_copy(holo_base_msg_geometry_Point3d*       dst,
                                                              const holo_base_msg_geometry_Point3d* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef holo_base_msg_geometry_Point3dSeq holo_base_msg_geometry_Point3dSequence;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_geometry_Point3dSequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_geometry_Point3dSequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_geometry_Point3dSequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point3dSequence
#define TSeq holo_base_msg_geometry_Point3dSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point3dSequence
#define TSeq holo_base_msg_geometry_Point3dSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_geometry_Point3dSequence* holo_base_msg_geometry_Point3dSequence_create();

NDDSUSERDllExport extern void
holo_base_msg_geometry_Point3dSequence_delete(holo_base_msg_geometry_Point3dSequence* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_geometry_Point3dSequence_initialize(holo_base_msg_geometry_Point3dSequence* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point3dSequence_initialize_ex(
    holo_base_msg_geometry_Point3dSequence* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point3dSequence_initialize_w_params(
    holo_base_msg_geometry_Point3dSequence* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point3dSequence_finalize(holo_base_msg_geometry_Point3dSequence* self);

NDDSUSERDllExport RTIBool
holo_base_msg_geometry_Point3dSequence_finalize_w_return(holo_base_msg_geometry_Point3dSequence* self);

NDDSUSERDllExport void holo_base_msg_geometry_Point3dSequence_finalize_ex(holo_base_msg_geometry_Point3dSequence* self,
                                                                          RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_geometry_Point3dSequence_finalize_w_params(
    holo_base_msg_geometry_Point3dSequence* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_geometry_Point3dSequence_finalize_optional_members(
    holo_base_msg_geometry_Point3dSequence* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point3dSequence_copy(
    holo_base_msg_geometry_Point3dSequence* dst, const holo_base_msg_geometry_Point3dSequence* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_geometry_Point2fTYPENAME;
}

struct holo_base_msg_geometry_Point2fSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_geometry_Point2fTypeSupport;
class holo_base_msg_geometry_Point2fDataWriter;
class holo_base_msg_geometry_Point2fDataReader;
#endif
class holo_base_msg_geometry_Point2f
{
public:
    typedef struct holo_base_msg_geometry_Point2fSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_geometry_Point2fTypeSupport TypeSupport;
    typedef holo_base_msg_geometry_Point2fDataWriter  DataWriter;
    typedef holo_base_msg_geometry_Point2fDataReader  DataReader;
#endif

    DDS_Float x;
    DDS_Float y;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_geometry_Point2f_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_geometry_Point2f_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_geometry_Point2f_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point2f
#define TSeq holo_base_msg_geometry_Point2fSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point2f
#define TSeq holo_base_msg_geometry_Point2fSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_geometry_Point2f* holo_base_msg_geometry_Point2f_create();

NDDSUSERDllExport extern void holo_base_msg_geometry_Point2f_delete(holo_base_msg_geometry_Point2f* sample);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point2f_initialize(holo_base_msg_geometry_Point2f* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point2f_initialize_ex(holo_base_msg_geometry_Point2f* self,
                                                                       RTIBool                         allocatePointers,
                                                                       RTIBool                         allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point2f_initialize_w_params(
    holo_base_msg_geometry_Point2f* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point2f_finalize(holo_base_msg_geometry_Point2f* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point2f_finalize_w_return(holo_base_msg_geometry_Point2f* self);

NDDSUSERDllExport void holo_base_msg_geometry_Point2f_finalize_ex(holo_base_msg_geometry_Point2f* self,
                                                                  RTIBool                         deletePointers);

NDDSUSERDllExport void holo_base_msg_geometry_Point2f_finalize_w_params(
    holo_base_msg_geometry_Point2f* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_geometry_Point2f_finalize_optional_members(holo_base_msg_geometry_Point2f* self,
                                                                                RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point2f_copy(holo_base_msg_geometry_Point2f*       dst,
                                                              const holo_base_msg_geometry_Point2f* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef holo_base_msg_geometry_Point2fSeq holo_base_msg_geometry_Point2fSequence;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_geometry_Point2fSequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_geometry_Point2fSequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_geometry_Point2fSequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point2fSequence
#define TSeq holo_base_msg_geometry_Point2fSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point2fSequence
#define TSeq holo_base_msg_geometry_Point2fSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_geometry_Point2fSequence* holo_base_msg_geometry_Point2fSequence_create();

NDDSUSERDllExport extern void
holo_base_msg_geometry_Point2fSequence_delete(holo_base_msg_geometry_Point2fSequence* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_geometry_Point2fSequence_initialize(holo_base_msg_geometry_Point2fSequence* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point2fSequence_initialize_ex(
    holo_base_msg_geometry_Point2fSequence* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point2fSequence_initialize_w_params(
    holo_base_msg_geometry_Point2fSequence* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point2fSequence_finalize(holo_base_msg_geometry_Point2fSequence* self);

NDDSUSERDllExport RTIBool
holo_base_msg_geometry_Point2fSequence_finalize_w_return(holo_base_msg_geometry_Point2fSequence* self);

NDDSUSERDllExport void holo_base_msg_geometry_Point2fSequence_finalize_ex(holo_base_msg_geometry_Point2fSequence* self,
                                                                          RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_geometry_Point2fSequence_finalize_w_params(
    holo_base_msg_geometry_Point2fSequence* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_geometry_Point2fSequence_finalize_optional_members(
    holo_base_msg_geometry_Point2fSequence* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point2fSequence_copy(
    holo_base_msg_geometry_Point2fSequence* dst, const holo_base_msg_geometry_Point2fSequence* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_geometry_Point2dTYPENAME;
}

struct holo_base_msg_geometry_Point2dSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_geometry_Point2dTypeSupport;
class holo_base_msg_geometry_Point2dDataWriter;
class holo_base_msg_geometry_Point2dDataReader;
#endif
class holo_base_msg_geometry_Point2d
{
public:
    typedef struct holo_base_msg_geometry_Point2dSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_geometry_Point2dTypeSupport TypeSupport;
    typedef holo_base_msg_geometry_Point2dDataWriter  DataWriter;
    typedef holo_base_msg_geometry_Point2dDataReader  DataReader;
#endif

    DDS_Double x;
    DDS_Double y;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_geometry_Point2d_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_geometry_Point2d_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_geometry_Point2d_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point2d
#define TSeq holo_base_msg_geometry_Point2dSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point2d
#define TSeq holo_base_msg_geometry_Point2dSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_geometry_Point2d* holo_base_msg_geometry_Point2d_create();

NDDSUSERDllExport extern void holo_base_msg_geometry_Point2d_delete(holo_base_msg_geometry_Point2d* sample);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point2d_initialize(holo_base_msg_geometry_Point2d* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point2d_initialize_ex(holo_base_msg_geometry_Point2d* self,
                                                                       RTIBool                         allocatePointers,
                                                                       RTIBool                         allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point2d_initialize_w_params(
    holo_base_msg_geometry_Point2d* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point2d_finalize(holo_base_msg_geometry_Point2d* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point2d_finalize_w_return(holo_base_msg_geometry_Point2d* self);

NDDSUSERDllExport void holo_base_msg_geometry_Point2d_finalize_ex(holo_base_msg_geometry_Point2d* self,
                                                                  RTIBool                         deletePointers);

NDDSUSERDllExport void holo_base_msg_geometry_Point2d_finalize_w_params(
    holo_base_msg_geometry_Point2d* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_geometry_Point2d_finalize_optional_members(holo_base_msg_geometry_Point2d* self,
                                                                                RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point2d_copy(holo_base_msg_geometry_Point2d*       dst,
                                                              const holo_base_msg_geometry_Point2d* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef holo_base_msg_geometry_Point2dSeq holo_base_msg_geometry_Point2dSequence;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_geometry_Point2dSequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_geometry_Point2dSequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_geometry_Point2dSequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point2dSequence
#define TSeq holo_base_msg_geometry_Point2dSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Point2dSequence
#define TSeq holo_base_msg_geometry_Point2dSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_geometry_Point2dSequence* holo_base_msg_geometry_Point2dSequence_create();

NDDSUSERDllExport extern void
holo_base_msg_geometry_Point2dSequence_delete(holo_base_msg_geometry_Point2dSequence* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_geometry_Point2dSequence_initialize(holo_base_msg_geometry_Point2dSequence* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point2dSequence_initialize_ex(
    holo_base_msg_geometry_Point2dSequence* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point2dSequence_initialize_w_params(
    holo_base_msg_geometry_Point2dSequence* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point2dSequence_finalize(holo_base_msg_geometry_Point2dSequence* self);

NDDSUSERDllExport RTIBool
holo_base_msg_geometry_Point2dSequence_finalize_w_return(holo_base_msg_geometry_Point2dSequence* self);

NDDSUSERDllExport void holo_base_msg_geometry_Point2dSequence_finalize_ex(holo_base_msg_geometry_Point2dSequence* self,
                                                                          RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_geometry_Point2dSequence_finalize_w_params(
    holo_base_msg_geometry_Point2dSequence* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_geometry_Point2dSequence_finalize_optional_members(
    holo_base_msg_geometry_Point2dSequence* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Point2dSequence_copy(
    holo_base_msg_geometry_Point2dSequence* dst, const holo_base_msg_geometry_Point2dSequence* src);

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

#endif /* Point */
