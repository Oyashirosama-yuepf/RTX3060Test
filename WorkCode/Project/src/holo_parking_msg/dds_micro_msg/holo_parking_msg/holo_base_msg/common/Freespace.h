/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Freespace.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef Freespace_1959326732_h
#define Freespace_1959326732_h

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

#include "holo_parking_msg/holo_base_msg/geometry/Point.h"

#include "holo_parking_msg/holo_base_msg/core/Types.h"

extern "C" {

extern const char* holo_base_msg_common_freespace3f_SegmentInfoTYPENAME;
}

struct holo_base_msg_common_freespace3f_SegmentInfoSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_common_freespace3f_SegmentInfoTypeSupport;
class holo_base_msg_common_freespace3f_SegmentInfoDataWriter;
class holo_base_msg_common_freespace3f_SegmentInfoDataReader;
#endif
class holo_base_msg_common_freespace3f_SegmentInfo
{
public:
    typedef struct holo_base_msg_common_freespace3f_SegmentInfoSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_common_freespace3f_SegmentInfoTypeSupport TypeSupport;
    typedef holo_base_msg_common_freespace3f_SegmentInfoDataWriter  DataWriter;
    typedef holo_base_msg_common_freespace3f_SegmentInfoDataReader  DataReader;
#endif

    DDS_UnsignedLong start;
    DDS_UnsignedLong end;
    DDS_UnsignedLong type;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_freespace3f_SegmentInfo_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_freespace3f_SegmentInfo_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_freespace3f_SegmentInfo_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_freespace3f_SegmentInfo
#define TSeq holo_base_msg_common_freespace3f_SegmentInfoSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_freespace3f_SegmentInfo
#define TSeq holo_base_msg_common_freespace3f_SegmentInfoSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_freespace3f_SegmentInfo*
holo_base_msg_common_freespace3f_SegmentInfo_create();

NDDSUSERDllExport extern void
holo_base_msg_common_freespace3f_SegmentInfo_delete(holo_base_msg_common_freespace3f_SegmentInfo* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_common_freespace3f_SegmentInfo_initialize(holo_base_msg_common_freespace3f_SegmentInfo* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_freespace3f_SegmentInfo_initialize_ex(
    holo_base_msg_common_freespace3f_SegmentInfo* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_freespace3f_SegmentInfo_initialize_w_params(
    holo_base_msg_common_freespace3f_SegmentInfo* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_common_freespace3f_SegmentInfo_finalize(holo_base_msg_common_freespace3f_SegmentInfo* self);

NDDSUSERDllExport RTIBool
holo_base_msg_common_freespace3f_SegmentInfo_finalize_w_return(holo_base_msg_common_freespace3f_SegmentInfo* self);

NDDSUSERDllExport void holo_base_msg_common_freespace3f_SegmentInfo_finalize_ex(
    holo_base_msg_common_freespace3f_SegmentInfo* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_common_freespace3f_SegmentInfo_finalize_w_params(
    holo_base_msg_common_freespace3f_SegmentInfo* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_freespace3f_SegmentInfo_finalize_optional_members(
    holo_base_msg_common_freespace3f_SegmentInfo* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_freespace3f_SegmentInfo_copy(
    holo_base_msg_common_freespace3f_SegmentInfo* dst, const holo_base_msg_common_freespace3f_SegmentInfo* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_common_freespace3f_FreespaceInteriorTYPENAME;
}

struct holo_base_msg_common_freespace3f_FreespaceInteriorSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_common_freespace3f_FreespaceInteriorTypeSupport;
class holo_base_msg_common_freespace3f_FreespaceInteriorDataWriter;
class holo_base_msg_common_freespace3f_FreespaceInteriorDataReader;
#endif
class holo_base_msg_common_freespace3f_FreespaceInterior
{
public:
    typedef struct holo_base_msg_common_freespace3f_FreespaceInteriorSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_common_freespace3f_FreespaceInteriorTypeSupport TypeSupport;
    typedef holo_base_msg_common_freespace3f_FreespaceInteriorDataWriter  DataWriter;
    typedef holo_base_msg_common_freespace3f_FreespaceInteriorDataReader  DataReader;
#endif

    holo_base_msg_geometry_Point3fSeq               points;
    holo_base_msg_common_freespace3f_SegmentInfoSeq boundaries;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_freespace3f_FreespaceInterior_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_freespace3f_FreespaceInterior_get_type_plugin_info(void);
NDDSUSERDllExport                    RTIXCdrSampleAccessInfo*
                                     holo_base_msg_common_freespace3f_FreespaceInterior_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_freespace3f_FreespaceInterior
#define TSeq holo_base_msg_common_freespace3f_FreespaceInteriorSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_freespace3f_FreespaceInterior
#define TSeq holo_base_msg_common_freespace3f_FreespaceInteriorSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_freespace3f_FreespaceInterior*
holo_base_msg_common_freespace3f_FreespaceInterior_create();

NDDSUSERDllExport extern void
holo_base_msg_common_freespace3f_FreespaceInterior_delete(holo_base_msg_common_freespace3f_FreespaceInterior* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_common_freespace3f_FreespaceInterior_initialize(holo_base_msg_common_freespace3f_FreespaceInterior* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_freespace3f_FreespaceInterior_initialize_ex(
    holo_base_msg_common_freespace3f_FreespaceInterior* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_freespace3f_FreespaceInterior_initialize_w_params(
    holo_base_msg_common_freespace3f_FreespaceInterior* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_common_freespace3f_FreespaceInterior_finalize(holo_base_msg_common_freespace3f_FreespaceInterior* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_freespace3f_FreespaceInterior_finalize_w_return(
    holo_base_msg_common_freespace3f_FreespaceInterior* self);

NDDSUSERDllExport void holo_base_msg_common_freespace3f_FreespaceInterior_finalize_ex(
    holo_base_msg_common_freespace3f_FreespaceInterior* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_common_freespace3f_FreespaceInterior_finalize_w_params(
    holo_base_msg_common_freespace3f_FreespaceInterior* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_freespace3f_FreespaceInterior_finalize_optional_members(
    holo_base_msg_common_freespace3f_FreespaceInterior* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool
holo_base_msg_common_freespace3f_FreespaceInterior_copy(holo_base_msg_common_freespace3f_FreespaceInterior*       dst,
                                                        const holo_base_msg_common_freespace3f_FreespaceInterior* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_common_freespace3f_FreespaceExteriorTYPENAME;
}

struct holo_base_msg_common_freespace3f_FreespaceExteriorSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_common_freespace3f_FreespaceExteriorTypeSupport;
class holo_base_msg_common_freespace3f_FreespaceExteriorDataWriter;
class holo_base_msg_common_freespace3f_FreespaceExteriorDataReader;
#endif
class holo_base_msg_common_freespace3f_FreespaceExterior
{
public:
    typedef struct holo_base_msg_common_freespace3f_FreespaceExteriorSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_common_freespace3f_FreespaceExteriorTypeSupport TypeSupport;
    typedef holo_base_msg_common_freespace3f_FreespaceExteriorDataWriter  DataWriter;
    typedef holo_base_msg_common_freespace3f_FreespaceExteriorDataReader  DataReader;
#endif

    holo_base_msg_geometry_Point3fSeq                     points;
    holo_base_msg_common_freespace3f_SegmentInfoSeq       boundaries;
    holo_base_msg_common_freespace3f_FreespaceInteriorSeq interiors;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_freespace3f_FreespaceExterior_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_freespace3f_FreespaceExterior_get_type_plugin_info(void);
NDDSUSERDllExport                    RTIXCdrSampleAccessInfo*
                                     holo_base_msg_common_freespace3f_FreespaceExterior_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_freespace3f_FreespaceExterior
#define TSeq holo_base_msg_common_freespace3f_FreespaceExteriorSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_freespace3f_FreespaceExterior
#define TSeq holo_base_msg_common_freespace3f_FreespaceExteriorSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_freespace3f_FreespaceExterior*
holo_base_msg_common_freespace3f_FreespaceExterior_create();

NDDSUSERDllExport extern void
holo_base_msg_common_freespace3f_FreespaceExterior_delete(holo_base_msg_common_freespace3f_FreespaceExterior* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_common_freespace3f_FreespaceExterior_initialize(holo_base_msg_common_freespace3f_FreespaceExterior* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_freespace3f_FreespaceExterior_initialize_ex(
    holo_base_msg_common_freespace3f_FreespaceExterior* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_freespace3f_FreespaceExterior_initialize_w_params(
    holo_base_msg_common_freespace3f_FreespaceExterior* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_common_freespace3f_FreespaceExterior_finalize(holo_base_msg_common_freespace3f_FreespaceExterior* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_freespace3f_FreespaceExterior_finalize_w_return(
    holo_base_msg_common_freespace3f_FreespaceExterior* self);

NDDSUSERDllExport void holo_base_msg_common_freespace3f_FreespaceExterior_finalize_ex(
    holo_base_msg_common_freespace3f_FreespaceExterior* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_common_freespace3f_FreespaceExterior_finalize_w_params(
    holo_base_msg_common_freespace3f_FreespaceExterior* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_freespace3f_FreespaceExterior_finalize_optional_members(
    holo_base_msg_common_freespace3f_FreespaceExterior* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool
holo_base_msg_common_freespace3f_FreespaceExterior_copy(holo_base_msg_common_freespace3f_FreespaceExterior*       dst,
                                                        const holo_base_msg_common_freespace3f_FreespaceExterior* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_common_freespace3f_FreespaceTYPENAME;
}

struct holo_base_msg_common_freespace3f_FreespaceSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_common_freespace3f_FreespaceTypeSupport;
class holo_base_msg_common_freespace3f_FreespaceDataWriter;
class holo_base_msg_common_freespace3f_FreespaceDataReader;
#endif
class holo_base_msg_common_freespace3f_Freespace
{
public:
    typedef struct holo_base_msg_common_freespace3f_FreespaceSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_common_freespace3f_FreespaceTypeSupport TypeSupport;
    typedef holo_base_msg_common_freespace3f_FreespaceDataWriter  DataWriter;
    typedef holo_base_msg_common_freespace3f_FreespaceDataReader  DataReader;
#endif

    holo_base_msg_common_freespace3f_FreespaceExteriorSeq exteriors;
    holo_base_msg_common_Timestamp                        stamp;
    DDS_UnsignedLong                                      coordinate;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_freespace3f_Freespace_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_freespace3f_Freespace_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_freespace3f_Freespace_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_freespace3f_Freespace
#define TSeq holo_base_msg_common_freespace3f_FreespaceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_freespace3f_Freespace
#define TSeq holo_base_msg_common_freespace3f_FreespaceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_freespace3f_Freespace*
holo_base_msg_common_freespace3f_Freespace_create();

NDDSUSERDllExport extern void
holo_base_msg_common_freespace3f_Freespace_delete(holo_base_msg_common_freespace3f_Freespace* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_common_freespace3f_Freespace_initialize(holo_base_msg_common_freespace3f_Freespace* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_freespace3f_Freespace_initialize_ex(
    holo_base_msg_common_freespace3f_Freespace* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_freespace3f_Freespace_initialize_w_params(
    holo_base_msg_common_freespace3f_Freespace* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_common_freespace3f_Freespace_finalize(holo_base_msg_common_freespace3f_Freespace* self);

NDDSUSERDllExport RTIBool
holo_base_msg_common_freespace3f_Freespace_finalize_w_return(holo_base_msg_common_freespace3f_Freespace* self);

NDDSUSERDllExport void holo_base_msg_common_freespace3f_Freespace_finalize_ex(
    holo_base_msg_common_freespace3f_Freespace* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_common_freespace3f_Freespace_finalize_w_params(
    holo_base_msg_common_freespace3f_Freespace* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_freespace3f_Freespace_finalize_optional_members(
    holo_base_msg_common_freespace3f_Freespace* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_freespace3f_Freespace_copy(
    holo_base_msg_common_freespace3f_Freespace* dst, const holo_base_msg_common_freespace3f_Freespace* src);

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

#endif /* Freespace */
