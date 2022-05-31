/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ImageObjects.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef ImageObjects_1109333664_h
#define ImageObjects_1109333664_h

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

#include "holo_parking_msg/holo_base_msg/core/Types.h"

#include "holo_parking_msg/holo_base_msg/common/Common.h"

#include "holo_parking_msg/holo_base_msg/geometry/Point.h"

extern "C" {

extern const char* holo_base_msg_vision_KeyPoint2dTYPENAME;
}

struct holo_base_msg_vision_KeyPoint2dSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_vision_KeyPoint2dTypeSupport;
class holo_base_msg_vision_KeyPoint2dDataWriter;
class holo_base_msg_vision_KeyPoint2dDataReader;
#endif
class holo_base_msg_vision_KeyPoint2d
{
public:
    typedef struct holo_base_msg_vision_KeyPoint2dSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_vision_KeyPoint2dTypeSupport TypeSupport;
    typedef holo_base_msg_vision_KeyPoint2dDataWriter  DataWriter;
    typedef holo_base_msg_vision_KeyPoint2dDataReader  DataReader;
#endif

    DDS_Double  x;
    DDS_Double  y;
    DDS_Float   confidence;
    DDS_Boolean visibility;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_vision_KeyPoint2d_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_vision_KeyPoint2d_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_vision_KeyPoint2d_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_KeyPoint2d
#define TSeq holo_base_msg_vision_KeyPoint2dSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_KeyPoint2d
#define TSeq holo_base_msg_vision_KeyPoint2dSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_vision_KeyPoint2d* holo_base_msg_vision_KeyPoint2d_create();

NDDSUSERDllExport extern void holo_base_msg_vision_KeyPoint2d_delete(holo_base_msg_vision_KeyPoint2d* sample);

NDDSUSERDllExport RTIBool holo_base_msg_vision_KeyPoint2d_initialize(holo_base_msg_vision_KeyPoint2d* self);

NDDSUSERDllExport RTIBool holo_base_msg_vision_KeyPoint2d_initialize_ex(holo_base_msg_vision_KeyPoint2d* self,
                                                                        RTIBool allocatePointers,
                                                                        RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_vision_KeyPoint2d_initialize_w_params(
    holo_base_msg_vision_KeyPoint2d* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_vision_KeyPoint2d_finalize(holo_base_msg_vision_KeyPoint2d* self);

NDDSUSERDllExport RTIBool holo_base_msg_vision_KeyPoint2d_finalize_w_return(holo_base_msg_vision_KeyPoint2d* self);

NDDSUSERDllExport void holo_base_msg_vision_KeyPoint2d_finalize_ex(holo_base_msg_vision_KeyPoint2d* self,
                                                                   RTIBool                          deletePointers);

NDDSUSERDllExport void holo_base_msg_vision_KeyPoint2d_finalize_w_params(
    holo_base_msg_vision_KeyPoint2d* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_vision_KeyPoint2d_finalize_optional_members(holo_base_msg_vision_KeyPoint2d* self,
                                                                                 RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_vision_KeyPoint2d_copy(holo_base_msg_vision_KeyPoint2d*       dst,
                                                               const holo_base_msg_vision_KeyPoint2d* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef holo_base_msg_vision_KeyPoint2dSeq holo_base_msg_vision_KeyPoint2dSequence;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_vision_KeyPoint2dSequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_vision_KeyPoint2dSequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_vision_KeyPoint2dSequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_KeyPoint2dSequence
#define TSeq holo_base_msg_vision_KeyPoint2dSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_KeyPoint2dSequence
#define TSeq holo_base_msg_vision_KeyPoint2dSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_vision_KeyPoint2dSequence* holo_base_msg_vision_KeyPoint2dSequence_create();

NDDSUSERDllExport extern void
holo_base_msg_vision_KeyPoint2dSequence_delete(holo_base_msg_vision_KeyPoint2dSequence* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_KeyPoint2dSequence_initialize(holo_base_msg_vision_KeyPoint2dSequence* self);

NDDSUSERDllExport RTIBool holo_base_msg_vision_KeyPoint2dSequence_initialize_ex(
    holo_base_msg_vision_KeyPoint2dSequence* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_vision_KeyPoint2dSequence_initialize_w_params(
    holo_base_msg_vision_KeyPoint2dSequence* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_KeyPoint2dSequence_finalize(holo_base_msg_vision_KeyPoint2dSequence* self);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_KeyPoint2dSequence_finalize_w_return(holo_base_msg_vision_KeyPoint2dSequence* self);

NDDSUSERDllExport void holo_base_msg_vision_KeyPoint2dSequence_finalize_ex(
    holo_base_msg_vision_KeyPoint2dSequence* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_vision_KeyPoint2dSequence_finalize_w_params(
    holo_base_msg_vision_KeyPoint2dSequence* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_vision_KeyPoint2dSequence_finalize_optional_members(
    holo_base_msg_vision_KeyPoint2dSequence* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_vision_KeyPoint2dSequence_copy(
    holo_base_msg_vision_KeyPoint2dSequence* dst, const holo_base_msg_vision_KeyPoint2dSequence* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_vision_KeyPoint2fTYPENAME;
}

struct holo_base_msg_vision_KeyPoint2fSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_vision_KeyPoint2fTypeSupport;
class holo_base_msg_vision_KeyPoint2fDataWriter;
class holo_base_msg_vision_KeyPoint2fDataReader;
#endif
class holo_base_msg_vision_KeyPoint2f
{
public:
    typedef struct holo_base_msg_vision_KeyPoint2fSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_vision_KeyPoint2fTypeSupport TypeSupport;
    typedef holo_base_msg_vision_KeyPoint2fDataWriter  DataWriter;
    typedef holo_base_msg_vision_KeyPoint2fDataReader  DataReader;
#endif

    DDS_Float   x;
    DDS_Float   y;
    DDS_Float   confidence;
    DDS_Boolean visibility;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_vision_KeyPoint2f_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_vision_KeyPoint2f_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_vision_KeyPoint2f_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_KeyPoint2f
#define TSeq holo_base_msg_vision_KeyPoint2fSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_KeyPoint2f
#define TSeq holo_base_msg_vision_KeyPoint2fSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_vision_KeyPoint2f* holo_base_msg_vision_KeyPoint2f_create();

NDDSUSERDllExport extern void holo_base_msg_vision_KeyPoint2f_delete(holo_base_msg_vision_KeyPoint2f* sample);

NDDSUSERDllExport RTIBool holo_base_msg_vision_KeyPoint2f_initialize(holo_base_msg_vision_KeyPoint2f* self);

NDDSUSERDllExport RTIBool holo_base_msg_vision_KeyPoint2f_initialize_ex(holo_base_msg_vision_KeyPoint2f* self,
                                                                        RTIBool allocatePointers,
                                                                        RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_vision_KeyPoint2f_initialize_w_params(
    holo_base_msg_vision_KeyPoint2f* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_vision_KeyPoint2f_finalize(holo_base_msg_vision_KeyPoint2f* self);

NDDSUSERDllExport RTIBool holo_base_msg_vision_KeyPoint2f_finalize_w_return(holo_base_msg_vision_KeyPoint2f* self);

NDDSUSERDllExport void holo_base_msg_vision_KeyPoint2f_finalize_ex(holo_base_msg_vision_KeyPoint2f* self,
                                                                   RTIBool                          deletePointers);

NDDSUSERDllExport void holo_base_msg_vision_KeyPoint2f_finalize_w_params(
    holo_base_msg_vision_KeyPoint2f* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_vision_KeyPoint2f_finalize_optional_members(holo_base_msg_vision_KeyPoint2f* self,
                                                                                 RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_vision_KeyPoint2f_copy(holo_base_msg_vision_KeyPoint2f*       dst,
                                                               const holo_base_msg_vision_KeyPoint2f* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef holo_base_msg_vision_KeyPoint2fSeq holo_base_msg_vision_KeyPoint2fSequence;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_vision_KeyPoint2fSequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_vision_KeyPoint2fSequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_vision_KeyPoint2fSequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_KeyPoint2fSequence
#define TSeq holo_base_msg_vision_KeyPoint2fSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_KeyPoint2fSequence
#define TSeq holo_base_msg_vision_KeyPoint2fSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_vision_KeyPoint2fSequence* holo_base_msg_vision_KeyPoint2fSequence_create();

NDDSUSERDllExport extern void
holo_base_msg_vision_KeyPoint2fSequence_delete(holo_base_msg_vision_KeyPoint2fSequence* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_KeyPoint2fSequence_initialize(holo_base_msg_vision_KeyPoint2fSequence* self);

NDDSUSERDllExport RTIBool holo_base_msg_vision_KeyPoint2fSequence_initialize_ex(
    holo_base_msg_vision_KeyPoint2fSequence* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_vision_KeyPoint2fSequence_initialize_w_params(
    holo_base_msg_vision_KeyPoint2fSequence* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_KeyPoint2fSequence_finalize(holo_base_msg_vision_KeyPoint2fSequence* self);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_KeyPoint2fSequence_finalize_w_return(holo_base_msg_vision_KeyPoint2fSequence* self);

NDDSUSERDllExport void holo_base_msg_vision_KeyPoint2fSequence_finalize_ex(
    holo_base_msg_vision_KeyPoint2fSequence* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_vision_KeyPoint2fSequence_finalize_w_params(
    holo_base_msg_vision_KeyPoint2fSequence* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_vision_KeyPoint2fSequence_finalize_optional_members(
    holo_base_msg_vision_KeyPoint2fSequence* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_vision_KeyPoint2fSequence_copy(
    holo_base_msg_vision_KeyPoint2fSequence* dst, const holo_base_msg_vision_KeyPoint2fSequence* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_vision_ObjectKeyPoint2dTYPENAME;
}

struct holo_base_msg_vision_ObjectKeyPoint2dSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_vision_ObjectKeyPoint2dTypeSupport;
class holo_base_msg_vision_ObjectKeyPoint2dDataWriter;
class holo_base_msg_vision_ObjectKeyPoint2dDataReader;
#endif
class holo_base_msg_vision_ObjectKeyPoint2d
{
public:
    typedef struct holo_base_msg_vision_ObjectKeyPoint2dSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_vision_ObjectKeyPoint2dTypeSupport TypeSupport;
    typedef holo_base_msg_vision_ObjectKeyPoint2dDataWriter  DataWriter;
    typedef holo_base_msg_vision_ObjectKeyPoint2dDataReader  DataReader;
#endif

    holo_base_msg_vision_KeyPoint2dSequence points;
    DDS_UnsignedLong                        category;
    DDS_Float                               confidence;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_vision_ObjectKeyPoint2d_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_vision_ObjectKeyPoint2d_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_vision_ObjectKeyPoint2d_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectKeyPoint2d
#define TSeq holo_base_msg_vision_ObjectKeyPoint2dSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectKeyPoint2d
#define TSeq holo_base_msg_vision_ObjectKeyPoint2dSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_vision_ObjectKeyPoint2d* holo_base_msg_vision_ObjectKeyPoint2d_create();

NDDSUSERDllExport extern void
holo_base_msg_vision_ObjectKeyPoint2d_delete(holo_base_msg_vision_ObjectKeyPoint2d* sample);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectKeyPoint2d_initialize(holo_base_msg_vision_ObjectKeyPoint2d* self);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectKeyPoint2d_initialize_ex(
    holo_base_msg_vision_ObjectKeyPoint2d* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectKeyPoint2d_initialize_w_params(
    holo_base_msg_vision_ObjectKeyPoint2d* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectKeyPoint2d_finalize(holo_base_msg_vision_ObjectKeyPoint2d* self);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ObjectKeyPoint2d_finalize_w_return(holo_base_msg_vision_ObjectKeyPoint2d* self);

NDDSUSERDllExport void holo_base_msg_vision_ObjectKeyPoint2d_finalize_ex(holo_base_msg_vision_ObjectKeyPoint2d* self,
                                                                         RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_vision_ObjectKeyPoint2d_finalize_w_params(
    holo_base_msg_vision_ObjectKeyPoint2d* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_vision_ObjectKeyPoint2d_finalize_optional_members(
    holo_base_msg_vision_ObjectKeyPoint2d* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectKeyPoint2d_copy(holo_base_msg_vision_ObjectKeyPoint2d*       dst,
                                                                     const holo_base_msg_vision_ObjectKeyPoint2d* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef holo_base_msg_vision_ObjectKeyPoint2dSeq holo_base_msg_vision_ObjectKeyPoint2dSequence;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_vision_ObjectKeyPoint2dSequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_vision_ObjectKeyPoint2dSequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_vision_ObjectKeyPoint2dSequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectKeyPoint2dSequence
#define TSeq holo_base_msg_vision_ObjectKeyPoint2dSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectKeyPoint2dSequence
#define TSeq holo_base_msg_vision_ObjectKeyPoint2dSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_vision_ObjectKeyPoint2dSequence*
holo_base_msg_vision_ObjectKeyPoint2dSequence_create();

NDDSUSERDllExport extern void
holo_base_msg_vision_ObjectKeyPoint2dSequence_delete(holo_base_msg_vision_ObjectKeyPoint2dSequence* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ObjectKeyPoint2dSequence_initialize(holo_base_msg_vision_ObjectKeyPoint2dSequence* self);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectKeyPoint2dSequence_initialize_ex(
    holo_base_msg_vision_ObjectKeyPoint2dSequence* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectKeyPoint2dSequence_initialize_w_params(
    holo_base_msg_vision_ObjectKeyPoint2dSequence* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ObjectKeyPoint2dSequence_finalize(holo_base_msg_vision_ObjectKeyPoint2dSequence* self);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ObjectKeyPoint2dSequence_finalize_w_return(holo_base_msg_vision_ObjectKeyPoint2dSequence* self);

NDDSUSERDllExport void holo_base_msg_vision_ObjectKeyPoint2dSequence_finalize_ex(
    holo_base_msg_vision_ObjectKeyPoint2dSequence* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_vision_ObjectKeyPoint2dSequence_finalize_w_params(
    holo_base_msg_vision_ObjectKeyPoint2dSequence* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_vision_ObjectKeyPoint2dSequence_finalize_optional_members(
    holo_base_msg_vision_ObjectKeyPoint2dSequence* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectKeyPoint2dSequence_copy(
    holo_base_msg_vision_ObjectKeyPoint2dSequence* dst, const holo_base_msg_vision_ObjectKeyPoint2dSequence* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_vision_ObjectKeyPoint2fTYPENAME;
}

struct holo_base_msg_vision_ObjectKeyPoint2fSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_vision_ObjectKeyPoint2fTypeSupport;
class holo_base_msg_vision_ObjectKeyPoint2fDataWriter;
class holo_base_msg_vision_ObjectKeyPoint2fDataReader;
#endif
class holo_base_msg_vision_ObjectKeyPoint2f
{
public:
    typedef struct holo_base_msg_vision_ObjectKeyPoint2fSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_vision_ObjectKeyPoint2fTypeSupport TypeSupport;
    typedef holo_base_msg_vision_ObjectKeyPoint2fDataWriter  DataWriter;
    typedef holo_base_msg_vision_ObjectKeyPoint2fDataReader  DataReader;
#endif

    holo_base_msg_vision_KeyPoint2fSequence points;
    DDS_UnsignedLong                        category;
    DDS_Float                               confidence;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_vision_ObjectKeyPoint2f_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_vision_ObjectKeyPoint2f_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_vision_ObjectKeyPoint2f_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectKeyPoint2f
#define TSeq holo_base_msg_vision_ObjectKeyPoint2fSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectKeyPoint2f
#define TSeq holo_base_msg_vision_ObjectKeyPoint2fSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_vision_ObjectKeyPoint2f* holo_base_msg_vision_ObjectKeyPoint2f_create();

NDDSUSERDllExport extern void
holo_base_msg_vision_ObjectKeyPoint2f_delete(holo_base_msg_vision_ObjectKeyPoint2f* sample);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectKeyPoint2f_initialize(holo_base_msg_vision_ObjectKeyPoint2f* self);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectKeyPoint2f_initialize_ex(
    holo_base_msg_vision_ObjectKeyPoint2f* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectKeyPoint2f_initialize_w_params(
    holo_base_msg_vision_ObjectKeyPoint2f* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectKeyPoint2f_finalize(holo_base_msg_vision_ObjectKeyPoint2f* self);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ObjectKeyPoint2f_finalize_w_return(holo_base_msg_vision_ObjectKeyPoint2f* self);

NDDSUSERDllExport void holo_base_msg_vision_ObjectKeyPoint2f_finalize_ex(holo_base_msg_vision_ObjectKeyPoint2f* self,
                                                                         RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_vision_ObjectKeyPoint2f_finalize_w_params(
    holo_base_msg_vision_ObjectKeyPoint2f* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_vision_ObjectKeyPoint2f_finalize_optional_members(
    holo_base_msg_vision_ObjectKeyPoint2f* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectKeyPoint2f_copy(holo_base_msg_vision_ObjectKeyPoint2f*       dst,
                                                                     const holo_base_msg_vision_ObjectKeyPoint2f* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef holo_base_msg_vision_ObjectKeyPoint2fSeq holo_base_msg_vision_ObjectKeyPoint2fSequence;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_vision_ObjectKeyPoint2fSequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_vision_ObjectKeyPoint2fSequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_vision_ObjectKeyPoint2fSequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectKeyPoint2fSequence
#define TSeq holo_base_msg_vision_ObjectKeyPoint2fSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectKeyPoint2fSequence
#define TSeq holo_base_msg_vision_ObjectKeyPoint2fSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_vision_ObjectKeyPoint2fSequence*
holo_base_msg_vision_ObjectKeyPoint2fSequence_create();

NDDSUSERDllExport extern void
holo_base_msg_vision_ObjectKeyPoint2fSequence_delete(holo_base_msg_vision_ObjectKeyPoint2fSequence* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ObjectKeyPoint2fSequence_initialize(holo_base_msg_vision_ObjectKeyPoint2fSequence* self);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectKeyPoint2fSequence_initialize_ex(
    holo_base_msg_vision_ObjectKeyPoint2fSequence* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectKeyPoint2fSequence_initialize_w_params(
    holo_base_msg_vision_ObjectKeyPoint2fSequence* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ObjectKeyPoint2fSequence_finalize(holo_base_msg_vision_ObjectKeyPoint2fSequence* self);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ObjectKeyPoint2fSequence_finalize_w_return(holo_base_msg_vision_ObjectKeyPoint2fSequence* self);

NDDSUSERDllExport void holo_base_msg_vision_ObjectKeyPoint2fSequence_finalize_ex(
    holo_base_msg_vision_ObjectKeyPoint2fSequence* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_vision_ObjectKeyPoint2fSequence_finalize_w_params(
    holo_base_msg_vision_ObjectKeyPoint2fSequence* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_vision_ObjectKeyPoint2fSequence_finalize_optional_members(
    holo_base_msg_vision_ObjectKeyPoint2fSequence* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectKeyPoint2fSequence_copy(
    holo_base_msg_vision_ObjectKeyPoint2fSequence* dst, const holo_base_msg_vision_ObjectKeyPoint2fSequence* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_vision_ObjectPoint2dTYPENAME;
}

struct holo_base_msg_vision_ObjectPoint2dSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_vision_ObjectPoint2dTypeSupport;
class holo_base_msg_vision_ObjectPoint2dDataWriter;
class holo_base_msg_vision_ObjectPoint2dDataReader;
#endif
class holo_base_msg_vision_ObjectPoint2d
{
public:
    typedef struct holo_base_msg_vision_ObjectPoint2dSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_vision_ObjectPoint2dTypeSupport TypeSupport;
    typedef holo_base_msg_vision_ObjectPoint2dDataWriter  DataWriter;
    typedef holo_base_msg_vision_ObjectPoint2dDataReader  DataReader;
#endif

    holo_base_msg_geometry_Point2dSequence points;
    DDS_UnsignedLong                       category;
    DDS_Float                              confidence;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_vision_ObjectPoint2d_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_vision_ObjectPoint2d_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_vision_ObjectPoint2d_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint2d
#define TSeq holo_base_msg_vision_ObjectPoint2dSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint2d
#define TSeq holo_base_msg_vision_ObjectPoint2dSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_vision_ObjectPoint2d* holo_base_msg_vision_ObjectPoint2d_create();

NDDSUSERDllExport extern void holo_base_msg_vision_ObjectPoint2d_delete(holo_base_msg_vision_ObjectPoint2d* sample);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint2d_initialize(holo_base_msg_vision_ObjectPoint2d* self);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint2d_initialize_ex(holo_base_msg_vision_ObjectPoint2d* self,
                                                                           RTIBool allocatePointers,
                                                                           RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint2d_initialize_w_params(
    holo_base_msg_vision_ObjectPoint2d* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint2d_finalize(holo_base_msg_vision_ObjectPoint2d* self);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ObjectPoint2d_finalize_w_return(holo_base_msg_vision_ObjectPoint2d* self);

NDDSUSERDllExport void holo_base_msg_vision_ObjectPoint2d_finalize_ex(holo_base_msg_vision_ObjectPoint2d* self,
                                                                      RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_vision_ObjectPoint2d_finalize_w_params(
    holo_base_msg_vision_ObjectPoint2d* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_vision_ObjectPoint2d_finalize_optional_members(
    holo_base_msg_vision_ObjectPoint2d* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint2d_copy(holo_base_msg_vision_ObjectPoint2d*       dst,
                                                                  const holo_base_msg_vision_ObjectPoint2d* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef holo_base_msg_vision_ObjectPoint2dSeq holo_base_msg_vision_ObjectPoint2dSequence;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_vision_ObjectPoint2dSequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_vision_ObjectPoint2dSequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_vision_ObjectPoint2dSequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint2dSequence
#define TSeq holo_base_msg_vision_ObjectPoint2dSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint2dSequence
#define TSeq holo_base_msg_vision_ObjectPoint2dSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_vision_ObjectPoint2dSequence*
holo_base_msg_vision_ObjectPoint2dSequence_create();

NDDSUSERDllExport extern void
holo_base_msg_vision_ObjectPoint2dSequence_delete(holo_base_msg_vision_ObjectPoint2dSequence* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ObjectPoint2dSequence_initialize(holo_base_msg_vision_ObjectPoint2dSequence* self);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint2dSequence_initialize_ex(
    holo_base_msg_vision_ObjectPoint2dSequence* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint2dSequence_initialize_w_params(
    holo_base_msg_vision_ObjectPoint2dSequence* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ObjectPoint2dSequence_finalize(holo_base_msg_vision_ObjectPoint2dSequence* self);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ObjectPoint2dSequence_finalize_w_return(holo_base_msg_vision_ObjectPoint2dSequence* self);

NDDSUSERDllExport void holo_base_msg_vision_ObjectPoint2dSequence_finalize_ex(
    holo_base_msg_vision_ObjectPoint2dSequence* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_vision_ObjectPoint2dSequence_finalize_w_params(
    holo_base_msg_vision_ObjectPoint2dSequence* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_vision_ObjectPoint2dSequence_finalize_optional_members(
    holo_base_msg_vision_ObjectPoint2dSequence* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint2dSequence_copy(
    holo_base_msg_vision_ObjectPoint2dSequence* dst, const holo_base_msg_vision_ObjectPoint2dSequence* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_vision_ObjectPoint2fTYPENAME;
}

struct holo_base_msg_vision_ObjectPoint2fSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_vision_ObjectPoint2fTypeSupport;
class holo_base_msg_vision_ObjectPoint2fDataWriter;
class holo_base_msg_vision_ObjectPoint2fDataReader;
#endif
class holo_base_msg_vision_ObjectPoint2f
{
public:
    typedef struct holo_base_msg_vision_ObjectPoint2fSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_vision_ObjectPoint2fTypeSupport TypeSupport;
    typedef holo_base_msg_vision_ObjectPoint2fDataWriter  DataWriter;
    typedef holo_base_msg_vision_ObjectPoint2fDataReader  DataReader;
#endif

    holo_base_msg_geometry_Point2fSequence points;
    DDS_UnsignedLong                       category;
    DDS_Float                              confidence;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_vision_ObjectPoint2f_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_vision_ObjectPoint2f_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_vision_ObjectPoint2f_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint2f
#define TSeq holo_base_msg_vision_ObjectPoint2fSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint2f
#define TSeq holo_base_msg_vision_ObjectPoint2fSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_vision_ObjectPoint2f* holo_base_msg_vision_ObjectPoint2f_create();

NDDSUSERDllExport extern void holo_base_msg_vision_ObjectPoint2f_delete(holo_base_msg_vision_ObjectPoint2f* sample);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint2f_initialize(holo_base_msg_vision_ObjectPoint2f* self);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint2f_initialize_ex(holo_base_msg_vision_ObjectPoint2f* self,
                                                                           RTIBool allocatePointers,
                                                                           RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint2f_initialize_w_params(
    holo_base_msg_vision_ObjectPoint2f* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint2f_finalize(holo_base_msg_vision_ObjectPoint2f* self);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ObjectPoint2f_finalize_w_return(holo_base_msg_vision_ObjectPoint2f* self);

NDDSUSERDllExport void holo_base_msg_vision_ObjectPoint2f_finalize_ex(holo_base_msg_vision_ObjectPoint2f* self,
                                                                      RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_vision_ObjectPoint2f_finalize_w_params(
    holo_base_msg_vision_ObjectPoint2f* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_vision_ObjectPoint2f_finalize_optional_members(
    holo_base_msg_vision_ObjectPoint2f* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint2f_copy(holo_base_msg_vision_ObjectPoint2f*       dst,
                                                                  const holo_base_msg_vision_ObjectPoint2f* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef holo_base_msg_vision_ObjectPoint2fSeq holo_base_msg_vision_ObjectPoint2fSequence;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_vision_ObjectPoint2fSequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_vision_ObjectPoint2fSequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_vision_ObjectPoint2fSequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint2fSequence
#define TSeq holo_base_msg_vision_ObjectPoint2fSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint2fSequence
#define TSeq holo_base_msg_vision_ObjectPoint2fSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_vision_ObjectPoint2fSequence*
holo_base_msg_vision_ObjectPoint2fSequence_create();

NDDSUSERDllExport extern void
holo_base_msg_vision_ObjectPoint2fSequence_delete(holo_base_msg_vision_ObjectPoint2fSequence* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ObjectPoint2fSequence_initialize(holo_base_msg_vision_ObjectPoint2fSequence* self);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint2fSequence_initialize_ex(
    holo_base_msg_vision_ObjectPoint2fSequence* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint2fSequence_initialize_w_params(
    holo_base_msg_vision_ObjectPoint2fSequence* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ObjectPoint2fSequence_finalize(holo_base_msg_vision_ObjectPoint2fSequence* self);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ObjectPoint2fSequence_finalize_w_return(holo_base_msg_vision_ObjectPoint2fSequence* self);

NDDSUSERDllExport void holo_base_msg_vision_ObjectPoint2fSequence_finalize_ex(
    holo_base_msg_vision_ObjectPoint2fSequence* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_vision_ObjectPoint2fSequence_finalize_w_params(
    holo_base_msg_vision_ObjectPoint2fSequence* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_vision_ObjectPoint2fSequence_finalize_optional_members(
    holo_base_msg_vision_ObjectPoint2fSequence* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint2fSequence_copy(
    holo_base_msg_vision_ObjectPoint2fSequence* dst, const holo_base_msg_vision_ObjectPoint2fSequence* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_vision_ObjectPoint3dTYPENAME;
}

struct holo_base_msg_vision_ObjectPoint3dSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_vision_ObjectPoint3dTypeSupport;
class holo_base_msg_vision_ObjectPoint3dDataWriter;
class holo_base_msg_vision_ObjectPoint3dDataReader;
#endif
class holo_base_msg_vision_ObjectPoint3d
{
public:
    typedef struct holo_base_msg_vision_ObjectPoint3dSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_vision_ObjectPoint3dTypeSupport TypeSupport;
    typedef holo_base_msg_vision_ObjectPoint3dDataWriter  DataWriter;
    typedef holo_base_msg_vision_ObjectPoint3dDataReader  DataReader;
#endif

    holo_base_msg_geometry_Point3dSequence points;
    DDS_UnsignedLong                       category;
    DDS_Float                              confidence;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_vision_ObjectPoint3d_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_vision_ObjectPoint3d_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_vision_ObjectPoint3d_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint3d
#define TSeq holo_base_msg_vision_ObjectPoint3dSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint3d
#define TSeq holo_base_msg_vision_ObjectPoint3dSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_vision_ObjectPoint3d* holo_base_msg_vision_ObjectPoint3d_create();

NDDSUSERDllExport extern void holo_base_msg_vision_ObjectPoint3d_delete(holo_base_msg_vision_ObjectPoint3d* sample);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint3d_initialize(holo_base_msg_vision_ObjectPoint3d* self);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint3d_initialize_ex(holo_base_msg_vision_ObjectPoint3d* self,
                                                                           RTIBool allocatePointers,
                                                                           RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint3d_initialize_w_params(
    holo_base_msg_vision_ObjectPoint3d* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint3d_finalize(holo_base_msg_vision_ObjectPoint3d* self);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ObjectPoint3d_finalize_w_return(holo_base_msg_vision_ObjectPoint3d* self);

NDDSUSERDllExport void holo_base_msg_vision_ObjectPoint3d_finalize_ex(holo_base_msg_vision_ObjectPoint3d* self,
                                                                      RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_vision_ObjectPoint3d_finalize_w_params(
    holo_base_msg_vision_ObjectPoint3d* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_vision_ObjectPoint3d_finalize_optional_members(
    holo_base_msg_vision_ObjectPoint3d* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint3d_copy(holo_base_msg_vision_ObjectPoint3d*       dst,
                                                                  const holo_base_msg_vision_ObjectPoint3d* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef holo_base_msg_vision_ObjectPoint3dSeq holo_base_msg_vision_ObjectPoint3dSequence;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_vision_ObjectPoint3dSequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_vision_ObjectPoint3dSequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_vision_ObjectPoint3dSequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint3dSequence
#define TSeq holo_base_msg_vision_ObjectPoint3dSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint3dSequence
#define TSeq holo_base_msg_vision_ObjectPoint3dSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_vision_ObjectPoint3dSequence*
holo_base_msg_vision_ObjectPoint3dSequence_create();

NDDSUSERDllExport extern void
holo_base_msg_vision_ObjectPoint3dSequence_delete(holo_base_msg_vision_ObjectPoint3dSequence* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ObjectPoint3dSequence_initialize(holo_base_msg_vision_ObjectPoint3dSequence* self);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint3dSequence_initialize_ex(
    holo_base_msg_vision_ObjectPoint3dSequence* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint3dSequence_initialize_w_params(
    holo_base_msg_vision_ObjectPoint3dSequence* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ObjectPoint3dSequence_finalize(holo_base_msg_vision_ObjectPoint3dSequence* self);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ObjectPoint3dSequence_finalize_w_return(holo_base_msg_vision_ObjectPoint3dSequence* self);

NDDSUSERDllExport void holo_base_msg_vision_ObjectPoint3dSequence_finalize_ex(
    holo_base_msg_vision_ObjectPoint3dSequence* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_vision_ObjectPoint3dSequence_finalize_w_params(
    holo_base_msg_vision_ObjectPoint3dSequence* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_vision_ObjectPoint3dSequence_finalize_optional_members(
    holo_base_msg_vision_ObjectPoint3dSequence* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint3dSequence_copy(
    holo_base_msg_vision_ObjectPoint3dSequence* dst, const holo_base_msg_vision_ObjectPoint3dSequence* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_vision_ObjectPoint3fTYPENAME;
}

struct holo_base_msg_vision_ObjectPoint3fSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_vision_ObjectPoint3fTypeSupport;
class holo_base_msg_vision_ObjectPoint3fDataWriter;
class holo_base_msg_vision_ObjectPoint3fDataReader;
#endif
class holo_base_msg_vision_ObjectPoint3f
{
public:
    typedef struct holo_base_msg_vision_ObjectPoint3fSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_vision_ObjectPoint3fTypeSupport TypeSupport;
    typedef holo_base_msg_vision_ObjectPoint3fDataWriter  DataWriter;
    typedef holo_base_msg_vision_ObjectPoint3fDataReader  DataReader;
#endif

    holo_base_msg_geometry_Point3fSequence points;
    DDS_UnsignedLong                       category;
    DDS_Float                              confidence;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_vision_ObjectPoint3f_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_vision_ObjectPoint3f_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_vision_ObjectPoint3f_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint3f
#define TSeq holo_base_msg_vision_ObjectPoint3fSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint3f
#define TSeq holo_base_msg_vision_ObjectPoint3fSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_vision_ObjectPoint3f* holo_base_msg_vision_ObjectPoint3f_create();

NDDSUSERDllExport extern void holo_base_msg_vision_ObjectPoint3f_delete(holo_base_msg_vision_ObjectPoint3f* sample);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint3f_initialize(holo_base_msg_vision_ObjectPoint3f* self);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint3f_initialize_ex(holo_base_msg_vision_ObjectPoint3f* self,
                                                                           RTIBool allocatePointers,
                                                                           RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint3f_initialize_w_params(
    holo_base_msg_vision_ObjectPoint3f* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint3f_finalize(holo_base_msg_vision_ObjectPoint3f* self);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ObjectPoint3f_finalize_w_return(holo_base_msg_vision_ObjectPoint3f* self);

NDDSUSERDllExport void holo_base_msg_vision_ObjectPoint3f_finalize_ex(holo_base_msg_vision_ObjectPoint3f* self,
                                                                      RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_vision_ObjectPoint3f_finalize_w_params(
    holo_base_msg_vision_ObjectPoint3f* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_vision_ObjectPoint3f_finalize_optional_members(
    holo_base_msg_vision_ObjectPoint3f* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint3f_copy(holo_base_msg_vision_ObjectPoint3f*       dst,
                                                                  const holo_base_msg_vision_ObjectPoint3f* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef holo_base_msg_vision_ObjectPoint3fSeq holo_base_msg_vision_ObjectPoint3fSequence;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_vision_ObjectPoint3fSequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_vision_ObjectPoint3fSequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_vision_ObjectPoint3fSequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint3fSequence
#define TSeq holo_base_msg_vision_ObjectPoint3fSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ObjectPoint3fSequence
#define TSeq holo_base_msg_vision_ObjectPoint3fSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_vision_ObjectPoint3fSequence*
holo_base_msg_vision_ObjectPoint3fSequence_create();

NDDSUSERDllExport extern void
holo_base_msg_vision_ObjectPoint3fSequence_delete(holo_base_msg_vision_ObjectPoint3fSequence* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ObjectPoint3fSequence_initialize(holo_base_msg_vision_ObjectPoint3fSequence* self);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint3fSequence_initialize_ex(
    holo_base_msg_vision_ObjectPoint3fSequence* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint3fSequence_initialize_w_params(
    holo_base_msg_vision_ObjectPoint3fSequence* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ObjectPoint3fSequence_finalize(holo_base_msg_vision_ObjectPoint3fSequence* self);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ObjectPoint3fSequence_finalize_w_return(holo_base_msg_vision_ObjectPoint3fSequence* self);

NDDSUSERDllExport void holo_base_msg_vision_ObjectPoint3fSequence_finalize_ex(
    holo_base_msg_vision_ObjectPoint3fSequence* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_vision_ObjectPoint3fSequence_finalize_w_params(
    holo_base_msg_vision_ObjectPoint3fSequence* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_vision_ObjectPoint3fSequence_finalize_optional_members(
    holo_base_msg_vision_ObjectPoint3fSequence* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ObjectPoint3fSequence_copy(
    holo_base_msg_vision_ObjectPoint3fSequence* dst, const holo_base_msg_vision_ObjectPoint3fSequence* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_vision_ImageObjectsKeyPoint2dTYPENAME;
}

struct holo_base_msg_vision_ImageObjectsKeyPoint2dSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_vision_ImageObjectsKeyPoint2dTypeSupport;
class holo_base_msg_vision_ImageObjectsKeyPoint2dDataWriter;
class holo_base_msg_vision_ImageObjectsKeyPoint2dDataReader;
#endif
class holo_base_msg_vision_ImageObjectsKeyPoint2d
{
public:
    typedef struct holo_base_msg_vision_ImageObjectsKeyPoint2dSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_vision_ImageObjectsKeyPoint2dTypeSupport TypeSupport;
    typedef holo_base_msg_vision_ImageObjectsKeyPoint2dDataWriter  DataWriter;
    typedef holo_base_msg_vision_ImageObjectsKeyPoint2dDataReader  DataReader;
#endif

    holo_base_msg_common_Timestamp                stamp;
    DDS_UnsignedLong                              sensor_id;
    holo_base_msg_vision_ObjectKeyPoint2dSequence objects;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_vision_ImageObjectsKeyPoint2d_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_vision_ImageObjectsKeyPoint2d_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_vision_ImageObjectsKeyPoint2d_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ImageObjectsKeyPoint2d
#define TSeq holo_base_msg_vision_ImageObjectsKeyPoint2dSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ImageObjectsKeyPoint2d
#define TSeq holo_base_msg_vision_ImageObjectsKeyPoint2dSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_vision_ImageObjectsKeyPoint2d*
holo_base_msg_vision_ImageObjectsKeyPoint2d_create();

NDDSUSERDllExport extern void
holo_base_msg_vision_ImageObjectsKeyPoint2d_delete(holo_base_msg_vision_ImageObjectsKeyPoint2d* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ImageObjectsKeyPoint2d_initialize(holo_base_msg_vision_ImageObjectsKeyPoint2d* self);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ImageObjectsKeyPoint2d_initialize_ex(
    holo_base_msg_vision_ImageObjectsKeyPoint2d* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ImageObjectsKeyPoint2d_initialize_w_params(
    holo_base_msg_vision_ImageObjectsKeyPoint2d* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ImageObjectsKeyPoint2d_finalize(holo_base_msg_vision_ImageObjectsKeyPoint2d* self);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ImageObjectsKeyPoint2d_finalize_w_return(holo_base_msg_vision_ImageObjectsKeyPoint2d* self);

NDDSUSERDllExport void holo_base_msg_vision_ImageObjectsKeyPoint2d_finalize_ex(
    holo_base_msg_vision_ImageObjectsKeyPoint2d* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_vision_ImageObjectsKeyPoint2d_finalize_w_params(
    holo_base_msg_vision_ImageObjectsKeyPoint2d* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_vision_ImageObjectsKeyPoint2d_finalize_optional_members(
    holo_base_msg_vision_ImageObjectsKeyPoint2d* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ImageObjectsKeyPoint2d_copy(
    holo_base_msg_vision_ImageObjectsKeyPoint2d* dst, const holo_base_msg_vision_ImageObjectsKeyPoint2d* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_vision_ImageObjectsKeyPoint2fTYPENAME;
}

struct holo_base_msg_vision_ImageObjectsKeyPoint2fSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_vision_ImageObjectsKeyPoint2fTypeSupport;
class holo_base_msg_vision_ImageObjectsKeyPoint2fDataWriter;
class holo_base_msg_vision_ImageObjectsKeyPoint2fDataReader;
#endif
class holo_base_msg_vision_ImageObjectsKeyPoint2f
{
public:
    typedef struct holo_base_msg_vision_ImageObjectsKeyPoint2fSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_vision_ImageObjectsKeyPoint2fTypeSupport TypeSupport;
    typedef holo_base_msg_vision_ImageObjectsKeyPoint2fDataWriter  DataWriter;
    typedef holo_base_msg_vision_ImageObjectsKeyPoint2fDataReader  DataReader;
#endif

    holo_base_msg_common_Timestamp                stamp;
    DDS_UnsignedLong                              sensor_id;
    holo_base_msg_vision_ObjectKeyPoint2fSequence objects;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_vision_ImageObjectsKeyPoint2f_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_vision_ImageObjectsKeyPoint2f_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_vision_ImageObjectsKeyPoint2f_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ImageObjectsKeyPoint2f
#define TSeq holo_base_msg_vision_ImageObjectsKeyPoint2fSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ImageObjectsKeyPoint2f
#define TSeq holo_base_msg_vision_ImageObjectsKeyPoint2fSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_vision_ImageObjectsKeyPoint2f*
holo_base_msg_vision_ImageObjectsKeyPoint2f_create();

NDDSUSERDllExport extern void
holo_base_msg_vision_ImageObjectsKeyPoint2f_delete(holo_base_msg_vision_ImageObjectsKeyPoint2f* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ImageObjectsKeyPoint2f_initialize(holo_base_msg_vision_ImageObjectsKeyPoint2f* self);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ImageObjectsKeyPoint2f_initialize_ex(
    holo_base_msg_vision_ImageObjectsKeyPoint2f* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ImageObjectsKeyPoint2f_initialize_w_params(
    holo_base_msg_vision_ImageObjectsKeyPoint2f* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ImageObjectsKeyPoint2f_finalize(holo_base_msg_vision_ImageObjectsKeyPoint2f* self);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ImageObjectsKeyPoint2f_finalize_w_return(holo_base_msg_vision_ImageObjectsKeyPoint2f* self);

NDDSUSERDllExport void holo_base_msg_vision_ImageObjectsKeyPoint2f_finalize_ex(
    holo_base_msg_vision_ImageObjectsKeyPoint2f* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_vision_ImageObjectsKeyPoint2f_finalize_w_params(
    holo_base_msg_vision_ImageObjectsKeyPoint2f* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_vision_ImageObjectsKeyPoint2f_finalize_optional_members(
    holo_base_msg_vision_ImageObjectsKeyPoint2f* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ImageObjectsKeyPoint2f_copy(
    holo_base_msg_vision_ImageObjectsKeyPoint2f* dst, const holo_base_msg_vision_ImageObjectsKeyPoint2f* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_vision_ImageObjectsPoint2dTYPENAME;
}

struct holo_base_msg_vision_ImageObjectsPoint2dSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_vision_ImageObjectsPoint2dTypeSupport;
class holo_base_msg_vision_ImageObjectsPoint2dDataWriter;
class holo_base_msg_vision_ImageObjectsPoint2dDataReader;
#endif
class holo_base_msg_vision_ImageObjectsPoint2d
{
public:
    typedef struct holo_base_msg_vision_ImageObjectsPoint2dSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_vision_ImageObjectsPoint2dTypeSupport TypeSupport;
    typedef holo_base_msg_vision_ImageObjectsPoint2dDataWriter  DataWriter;
    typedef holo_base_msg_vision_ImageObjectsPoint2dDataReader  DataReader;
#endif

    holo_base_msg_common_Timestamp             stamp;
    DDS_UnsignedLong                           sensor_id;
    holo_base_msg_vision_ObjectPoint2dSequence objects;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_vision_ImageObjectsPoint2d_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_vision_ImageObjectsPoint2d_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_vision_ImageObjectsPoint2d_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ImageObjectsPoint2d
#define TSeq holo_base_msg_vision_ImageObjectsPoint2dSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ImageObjectsPoint2d
#define TSeq holo_base_msg_vision_ImageObjectsPoint2dSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_vision_ImageObjectsPoint2d* holo_base_msg_vision_ImageObjectsPoint2d_create();

NDDSUSERDllExport extern void
holo_base_msg_vision_ImageObjectsPoint2d_delete(holo_base_msg_vision_ImageObjectsPoint2d* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ImageObjectsPoint2d_initialize(holo_base_msg_vision_ImageObjectsPoint2d* self);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ImageObjectsPoint2d_initialize_ex(
    holo_base_msg_vision_ImageObjectsPoint2d* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ImageObjectsPoint2d_initialize_w_params(
    holo_base_msg_vision_ImageObjectsPoint2d* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ImageObjectsPoint2d_finalize(holo_base_msg_vision_ImageObjectsPoint2d* self);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ImageObjectsPoint2d_finalize_w_return(holo_base_msg_vision_ImageObjectsPoint2d* self);

NDDSUSERDllExport void holo_base_msg_vision_ImageObjectsPoint2d_finalize_ex(
    holo_base_msg_vision_ImageObjectsPoint2d* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_vision_ImageObjectsPoint2d_finalize_w_params(
    holo_base_msg_vision_ImageObjectsPoint2d* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_vision_ImageObjectsPoint2d_finalize_optional_members(
    holo_base_msg_vision_ImageObjectsPoint2d* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ImageObjectsPoint2d_copy(
    holo_base_msg_vision_ImageObjectsPoint2d* dst, const holo_base_msg_vision_ImageObjectsPoint2d* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_vision_ImageObjectsPoint2fTYPENAME;
}

struct holo_base_msg_vision_ImageObjectsPoint2fSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_vision_ImageObjectsPoint2fTypeSupport;
class holo_base_msg_vision_ImageObjectsPoint2fDataWriter;
class holo_base_msg_vision_ImageObjectsPoint2fDataReader;
#endif
class holo_base_msg_vision_ImageObjectsPoint2f
{
public:
    typedef struct holo_base_msg_vision_ImageObjectsPoint2fSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_vision_ImageObjectsPoint2fTypeSupport TypeSupport;
    typedef holo_base_msg_vision_ImageObjectsPoint2fDataWriter  DataWriter;
    typedef holo_base_msg_vision_ImageObjectsPoint2fDataReader  DataReader;
#endif

    holo_base_msg_common_Timestamp             stamp;
    DDS_UnsignedLong                           sensor_id;
    holo_base_msg_vision_ObjectPoint2fSequence objects;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_vision_ImageObjectsPoint2f_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_vision_ImageObjectsPoint2f_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_vision_ImageObjectsPoint2f_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ImageObjectsPoint2f
#define TSeq holo_base_msg_vision_ImageObjectsPoint2fSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ImageObjectsPoint2f
#define TSeq holo_base_msg_vision_ImageObjectsPoint2fSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_vision_ImageObjectsPoint2f* holo_base_msg_vision_ImageObjectsPoint2f_create();

NDDSUSERDllExport extern void
holo_base_msg_vision_ImageObjectsPoint2f_delete(holo_base_msg_vision_ImageObjectsPoint2f* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ImageObjectsPoint2f_initialize(holo_base_msg_vision_ImageObjectsPoint2f* self);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ImageObjectsPoint2f_initialize_ex(
    holo_base_msg_vision_ImageObjectsPoint2f* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ImageObjectsPoint2f_initialize_w_params(
    holo_base_msg_vision_ImageObjectsPoint2f* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ImageObjectsPoint2f_finalize(holo_base_msg_vision_ImageObjectsPoint2f* self);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ImageObjectsPoint2f_finalize_w_return(holo_base_msg_vision_ImageObjectsPoint2f* self);

NDDSUSERDllExport void holo_base_msg_vision_ImageObjectsPoint2f_finalize_ex(
    holo_base_msg_vision_ImageObjectsPoint2f* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_vision_ImageObjectsPoint2f_finalize_w_params(
    holo_base_msg_vision_ImageObjectsPoint2f* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_vision_ImageObjectsPoint2f_finalize_optional_members(
    holo_base_msg_vision_ImageObjectsPoint2f* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ImageObjectsPoint2f_copy(
    holo_base_msg_vision_ImageObjectsPoint2f* dst, const holo_base_msg_vision_ImageObjectsPoint2f* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_vision_ImageObjectsPoint3dTYPENAME;
}

struct holo_base_msg_vision_ImageObjectsPoint3dSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_vision_ImageObjectsPoint3dTypeSupport;
class holo_base_msg_vision_ImageObjectsPoint3dDataWriter;
class holo_base_msg_vision_ImageObjectsPoint3dDataReader;
#endif
class holo_base_msg_vision_ImageObjectsPoint3d
{
public:
    typedef struct holo_base_msg_vision_ImageObjectsPoint3dSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_vision_ImageObjectsPoint3dTypeSupport TypeSupport;
    typedef holo_base_msg_vision_ImageObjectsPoint3dDataWriter  DataWriter;
    typedef holo_base_msg_vision_ImageObjectsPoint3dDataReader  DataReader;
#endif

    holo_base_msg_common_Timestamp             stamp;
    DDS_UnsignedLong                           sensor_id;
    holo_base_msg_vision_ObjectPoint3dSequence objects;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_vision_ImageObjectsPoint3d_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_vision_ImageObjectsPoint3d_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_vision_ImageObjectsPoint3d_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ImageObjectsPoint3d
#define TSeq holo_base_msg_vision_ImageObjectsPoint3dSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ImageObjectsPoint3d
#define TSeq holo_base_msg_vision_ImageObjectsPoint3dSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_vision_ImageObjectsPoint3d* holo_base_msg_vision_ImageObjectsPoint3d_create();

NDDSUSERDllExport extern void
holo_base_msg_vision_ImageObjectsPoint3d_delete(holo_base_msg_vision_ImageObjectsPoint3d* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ImageObjectsPoint3d_initialize(holo_base_msg_vision_ImageObjectsPoint3d* self);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ImageObjectsPoint3d_initialize_ex(
    holo_base_msg_vision_ImageObjectsPoint3d* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ImageObjectsPoint3d_initialize_w_params(
    holo_base_msg_vision_ImageObjectsPoint3d* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ImageObjectsPoint3d_finalize(holo_base_msg_vision_ImageObjectsPoint3d* self);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ImageObjectsPoint3d_finalize_w_return(holo_base_msg_vision_ImageObjectsPoint3d* self);

NDDSUSERDllExport void holo_base_msg_vision_ImageObjectsPoint3d_finalize_ex(
    holo_base_msg_vision_ImageObjectsPoint3d* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_vision_ImageObjectsPoint3d_finalize_w_params(
    holo_base_msg_vision_ImageObjectsPoint3d* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_vision_ImageObjectsPoint3d_finalize_optional_members(
    holo_base_msg_vision_ImageObjectsPoint3d* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ImageObjectsPoint3d_copy(
    holo_base_msg_vision_ImageObjectsPoint3d* dst, const holo_base_msg_vision_ImageObjectsPoint3d* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_vision_ImageObjectsPoint3fTYPENAME;
}

struct holo_base_msg_vision_ImageObjectsPoint3fSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_vision_ImageObjectsPoint3fTypeSupport;
class holo_base_msg_vision_ImageObjectsPoint3fDataWriter;
class holo_base_msg_vision_ImageObjectsPoint3fDataReader;
#endif
class holo_base_msg_vision_ImageObjectsPoint3f
{
public:
    typedef struct holo_base_msg_vision_ImageObjectsPoint3fSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_vision_ImageObjectsPoint3fTypeSupport TypeSupport;
    typedef holo_base_msg_vision_ImageObjectsPoint3fDataWriter  DataWriter;
    typedef holo_base_msg_vision_ImageObjectsPoint3fDataReader  DataReader;
#endif

    holo_base_msg_common_Timestamp             stamp;
    DDS_UnsignedLong                           sensor_id;
    holo_base_msg_vision_ObjectPoint3fSequence objects;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_vision_ImageObjectsPoint3f_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_vision_ImageObjectsPoint3f_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_vision_ImageObjectsPoint3f_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ImageObjectsPoint3f
#define TSeq holo_base_msg_vision_ImageObjectsPoint3fSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_vision_ImageObjectsPoint3f
#define TSeq holo_base_msg_vision_ImageObjectsPoint3fSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_vision_ImageObjectsPoint3f* holo_base_msg_vision_ImageObjectsPoint3f_create();

NDDSUSERDllExport extern void
holo_base_msg_vision_ImageObjectsPoint3f_delete(holo_base_msg_vision_ImageObjectsPoint3f* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ImageObjectsPoint3f_initialize(holo_base_msg_vision_ImageObjectsPoint3f* self);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ImageObjectsPoint3f_initialize_ex(
    holo_base_msg_vision_ImageObjectsPoint3f* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ImageObjectsPoint3f_initialize_w_params(
    holo_base_msg_vision_ImageObjectsPoint3f* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ImageObjectsPoint3f_finalize(holo_base_msg_vision_ImageObjectsPoint3f* self);

NDDSUSERDllExport RTIBool
holo_base_msg_vision_ImageObjectsPoint3f_finalize_w_return(holo_base_msg_vision_ImageObjectsPoint3f* self);

NDDSUSERDllExport void holo_base_msg_vision_ImageObjectsPoint3f_finalize_ex(
    holo_base_msg_vision_ImageObjectsPoint3f* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_vision_ImageObjectsPoint3f_finalize_w_params(
    holo_base_msg_vision_ImageObjectsPoint3f* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_vision_ImageObjectsPoint3f_finalize_optional_members(
    holo_base_msg_vision_ImageObjectsPoint3f* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_vision_ImageObjectsPoint3f_copy(
    holo_base_msg_vision_ImageObjectsPoint3f* dst, const holo_base_msg_vision_ImageObjectsPoint3f* src);

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

#endif /* ImageObjects */
