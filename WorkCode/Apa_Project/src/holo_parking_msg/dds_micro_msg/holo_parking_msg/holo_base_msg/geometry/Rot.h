/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Rot.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef Rot_1247671481_h
#define Rot_1247671481_h

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

extern const char* holo_base_msg_geometry_Rot2fTYPENAME;
}

struct holo_base_msg_geometry_Rot2fSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_geometry_Rot2fTypeSupport;
class holo_base_msg_geometry_Rot2fDataWriter;
class holo_base_msg_geometry_Rot2fDataReader;
#endif
class holo_base_msg_geometry_Rot2f
{
public:
    typedef struct holo_base_msg_geometry_Rot2fSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_geometry_Rot2fTypeSupport TypeSupport;
    typedef holo_base_msg_geometry_Rot2fDataWriter  DataWriter;
    typedef holo_base_msg_geometry_Rot2fDataReader  DataReader;
#endif

    DDS_Float theta;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_geometry_Rot2f_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_geometry_Rot2f_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_geometry_Rot2f_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Rot2f
#define TSeq holo_base_msg_geometry_Rot2fSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Rot2f
#define TSeq holo_base_msg_geometry_Rot2fSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_geometry_Rot2f* holo_base_msg_geometry_Rot2f_create();

NDDSUSERDllExport extern void holo_base_msg_geometry_Rot2f_delete(holo_base_msg_geometry_Rot2f* sample);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Rot2f_initialize(holo_base_msg_geometry_Rot2f* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Rot2f_initialize_ex(holo_base_msg_geometry_Rot2f* self,
                                                                     RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Rot2f_initialize_w_params(
    holo_base_msg_geometry_Rot2f* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Rot2f_finalize(holo_base_msg_geometry_Rot2f* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Rot2f_finalize_w_return(holo_base_msg_geometry_Rot2f* self);

NDDSUSERDllExport void holo_base_msg_geometry_Rot2f_finalize_ex(holo_base_msg_geometry_Rot2f* self,
                                                                RTIBool                       deletePointers);

NDDSUSERDllExport void holo_base_msg_geometry_Rot2f_finalize_w_params(
    holo_base_msg_geometry_Rot2f* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_geometry_Rot2f_finalize_optional_members(holo_base_msg_geometry_Rot2f* self,
                                                                              RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Rot2f_copy(holo_base_msg_geometry_Rot2f*       dst,
                                                            const holo_base_msg_geometry_Rot2f* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_geometry_Rot2dTYPENAME;
}

struct holo_base_msg_geometry_Rot2dSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_geometry_Rot2dTypeSupport;
class holo_base_msg_geometry_Rot2dDataWriter;
class holo_base_msg_geometry_Rot2dDataReader;
#endif
class holo_base_msg_geometry_Rot2d
{
public:
    typedef struct holo_base_msg_geometry_Rot2dSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_geometry_Rot2dTypeSupport TypeSupport;
    typedef holo_base_msg_geometry_Rot2dDataWriter  DataWriter;
    typedef holo_base_msg_geometry_Rot2dDataReader  DataReader;
#endif

    DDS_Double theta;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_geometry_Rot2d_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_geometry_Rot2d_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_geometry_Rot2d_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Rot2d
#define TSeq holo_base_msg_geometry_Rot2dSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Rot2d
#define TSeq holo_base_msg_geometry_Rot2dSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_geometry_Rot2d* holo_base_msg_geometry_Rot2d_create();

NDDSUSERDllExport extern void holo_base_msg_geometry_Rot2d_delete(holo_base_msg_geometry_Rot2d* sample);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Rot2d_initialize(holo_base_msg_geometry_Rot2d* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Rot2d_initialize_ex(holo_base_msg_geometry_Rot2d* self,
                                                                     RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Rot2d_initialize_w_params(
    holo_base_msg_geometry_Rot2d* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Rot2d_finalize(holo_base_msg_geometry_Rot2d* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Rot2d_finalize_w_return(holo_base_msg_geometry_Rot2d* self);

NDDSUSERDllExport void holo_base_msg_geometry_Rot2d_finalize_ex(holo_base_msg_geometry_Rot2d* self,
                                                                RTIBool                       deletePointers);

NDDSUSERDllExport void holo_base_msg_geometry_Rot2d_finalize_w_params(
    holo_base_msg_geometry_Rot2d* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_geometry_Rot2d_finalize_optional_members(holo_base_msg_geometry_Rot2d* self,
                                                                              RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Rot2d_copy(holo_base_msg_geometry_Rot2d*       dst,
                                                            const holo_base_msg_geometry_Rot2d* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_geometry_Rot3fTYPENAME;
}

struct holo_base_msg_geometry_Rot3fSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_geometry_Rot3fTypeSupport;
class holo_base_msg_geometry_Rot3fDataWriter;
class holo_base_msg_geometry_Rot3fDataReader;
#endif
class holo_base_msg_geometry_Rot3f
{
public:
    typedef struct holo_base_msg_geometry_Rot3fSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_geometry_Rot3fTypeSupport TypeSupport;
    typedef holo_base_msg_geometry_Rot3fDataWriter  DataWriter;
    typedef holo_base_msg_geometry_Rot3fDataReader  DataReader;
#endif

    DDS_Float x;
    DDS_Float y;
    DDS_Float z;
    DDS_Float w;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_geometry_Rot3f_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_geometry_Rot3f_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_geometry_Rot3f_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Rot3f
#define TSeq holo_base_msg_geometry_Rot3fSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Rot3f
#define TSeq holo_base_msg_geometry_Rot3fSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_geometry_Rot3f* holo_base_msg_geometry_Rot3f_create();

NDDSUSERDllExport extern void holo_base_msg_geometry_Rot3f_delete(holo_base_msg_geometry_Rot3f* sample);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Rot3f_initialize(holo_base_msg_geometry_Rot3f* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Rot3f_initialize_ex(holo_base_msg_geometry_Rot3f* self,
                                                                     RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Rot3f_initialize_w_params(
    holo_base_msg_geometry_Rot3f* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Rot3f_finalize(holo_base_msg_geometry_Rot3f* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Rot3f_finalize_w_return(holo_base_msg_geometry_Rot3f* self);

NDDSUSERDllExport void holo_base_msg_geometry_Rot3f_finalize_ex(holo_base_msg_geometry_Rot3f* self,
                                                                RTIBool                       deletePointers);

NDDSUSERDllExport void holo_base_msg_geometry_Rot3f_finalize_w_params(
    holo_base_msg_geometry_Rot3f* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_geometry_Rot3f_finalize_optional_members(holo_base_msg_geometry_Rot3f* self,
                                                                              RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Rot3f_copy(holo_base_msg_geometry_Rot3f*       dst,
                                                            const holo_base_msg_geometry_Rot3f* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_geometry_Rot3dTYPENAME;
}

struct holo_base_msg_geometry_Rot3dSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_geometry_Rot3dTypeSupport;
class holo_base_msg_geometry_Rot3dDataWriter;
class holo_base_msg_geometry_Rot3dDataReader;
#endif
class holo_base_msg_geometry_Rot3d
{
public:
    typedef struct holo_base_msg_geometry_Rot3dSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_geometry_Rot3dTypeSupport TypeSupport;
    typedef holo_base_msg_geometry_Rot3dDataWriter  DataWriter;
    typedef holo_base_msg_geometry_Rot3dDataReader  DataReader;
#endif

    DDS_Double x;
    DDS_Double y;
    DDS_Double z;
    DDS_Double w;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_geometry_Rot3d_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_geometry_Rot3d_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_geometry_Rot3d_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Rot3d
#define TSeq holo_base_msg_geometry_Rot3dSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Rot3d
#define TSeq holo_base_msg_geometry_Rot3dSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_geometry_Rot3d* holo_base_msg_geometry_Rot3d_create();

NDDSUSERDllExport extern void holo_base_msg_geometry_Rot3d_delete(holo_base_msg_geometry_Rot3d* sample);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Rot3d_initialize(holo_base_msg_geometry_Rot3d* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Rot3d_initialize_ex(holo_base_msg_geometry_Rot3d* self,
                                                                     RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Rot3d_initialize_w_params(
    holo_base_msg_geometry_Rot3d* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Rot3d_finalize(holo_base_msg_geometry_Rot3d* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Rot3d_finalize_w_return(holo_base_msg_geometry_Rot3d* self);

NDDSUSERDllExport void holo_base_msg_geometry_Rot3d_finalize_ex(holo_base_msg_geometry_Rot3d* self,
                                                                RTIBool                       deletePointers);

NDDSUSERDllExport void holo_base_msg_geometry_Rot3d_finalize_w_params(
    holo_base_msg_geometry_Rot3d* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_geometry_Rot3d_finalize_optional_members(holo_base_msg_geometry_Rot3d* self,
                                                                              RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Rot3d_copy(holo_base_msg_geometry_Rot3d*       dst,
                                                            const holo_base_msg_geometry_Rot3d* src);

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

#endif /* Rot */
