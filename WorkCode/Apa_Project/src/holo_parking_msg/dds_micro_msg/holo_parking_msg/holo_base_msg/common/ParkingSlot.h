/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ParkingSlot.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef ParkingSlot_1960983127_h
#define ParkingSlot_1960983127_h

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

extern const char* holo_base_msg_common_ParkingSlotfTYPENAME;
}

struct holo_base_msg_common_ParkingSlotfSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_common_ParkingSlotfTypeSupport;
class holo_base_msg_common_ParkingSlotfDataWriter;
class holo_base_msg_common_ParkingSlotfDataReader;
#endif
class holo_base_msg_common_ParkingSlotf
{
public:
    typedef struct holo_base_msg_common_ParkingSlotfSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_common_ParkingSlotfTypeSupport TypeSupport;
    typedef holo_base_msg_common_ParkingSlotfDataWriter  DataWriter;
    typedef holo_base_msg_common_ParkingSlotfDataReader  DataReader;
#endif

    DDS_UnsignedLongLong                   id;
    DDS_Boolean                            is_valid;
    DDS_UnsignedLong                       type;
    DDS_UnsignedLong                       position;
    DDS_UnsignedLong                       status;
    DDS_Float                              width;
    DDS_Float                              height;
    DDS_Float                              angle;
    DDS_Float                              confidence;
    DDS_Boolean                            is_rear_vertex_available;
    holo_base_msg_geometry_Point3fSequence vertices;
    DDS_Boolean                            is_center_vertex_available;
    holo_base_msg_geometry_Point3f         center_vertex;
    DDS_Boolean                            is_stopper_available;
    holo_base_msg_geometry_Point3fSequence stopper_vertices;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_ParkingSlotf_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_ParkingSlotf_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_ParkingSlotf_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ParkingSlotf
#define TSeq holo_base_msg_common_ParkingSlotfSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ParkingSlotf
#define TSeq holo_base_msg_common_ParkingSlotfSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_ParkingSlotf* holo_base_msg_common_ParkingSlotf_create();

NDDSUSERDllExport extern void holo_base_msg_common_ParkingSlotf_delete(holo_base_msg_common_ParkingSlotf* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_ParkingSlotf_initialize(holo_base_msg_common_ParkingSlotf* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_ParkingSlotf_initialize_ex(holo_base_msg_common_ParkingSlotf* self,
                                                                          RTIBool allocatePointers,
                                                                          RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_ParkingSlotf_initialize_w_params(
    holo_base_msg_common_ParkingSlotf* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_ParkingSlotf_finalize(holo_base_msg_common_ParkingSlotf* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_ParkingSlotf_finalize_w_return(holo_base_msg_common_ParkingSlotf* self);

NDDSUSERDllExport void holo_base_msg_common_ParkingSlotf_finalize_ex(holo_base_msg_common_ParkingSlotf* self,
                                                                     RTIBool                            deletePointers);

NDDSUSERDllExport void holo_base_msg_common_ParkingSlotf_finalize_w_params(
    holo_base_msg_common_ParkingSlotf* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_ParkingSlotf_finalize_optional_members(
    holo_base_msg_common_ParkingSlotf* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_ParkingSlotf_copy(holo_base_msg_common_ParkingSlotf*       dst,
                                                                 const holo_base_msg_common_ParkingSlotf* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef holo_base_msg_common_ParkingSlotfSeq holo_base_msg_common_ParkingSlotfSequence;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_ParkingSlotfSequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_ParkingSlotfSequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_ParkingSlotfSequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ParkingSlotfSequence
#define TSeq holo_base_msg_common_ParkingSlotfSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ParkingSlotfSequence
#define TSeq holo_base_msg_common_ParkingSlotfSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_ParkingSlotfSequence* holo_base_msg_common_ParkingSlotfSequence_create();

NDDSUSERDllExport extern void
holo_base_msg_common_ParkingSlotfSequence_delete(holo_base_msg_common_ParkingSlotfSequence* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_common_ParkingSlotfSequence_initialize(holo_base_msg_common_ParkingSlotfSequence* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_ParkingSlotfSequence_initialize_ex(
    holo_base_msg_common_ParkingSlotfSequence* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_ParkingSlotfSequence_initialize_w_params(
    holo_base_msg_common_ParkingSlotfSequence* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_common_ParkingSlotfSequence_finalize(holo_base_msg_common_ParkingSlotfSequence* self);

NDDSUSERDllExport RTIBool
holo_base_msg_common_ParkingSlotfSequence_finalize_w_return(holo_base_msg_common_ParkingSlotfSequence* self);

NDDSUSERDllExport void holo_base_msg_common_ParkingSlotfSequence_finalize_ex(
    holo_base_msg_common_ParkingSlotfSequence* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_common_ParkingSlotfSequence_finalize_w_params(
    holo_base_msg_common_ParkingSlotfSequence* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_ParkingSlotfSequence_finalize_optional_members(
    holo_base_msg_common_ParkingSlotfSequence* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_ParkingSlotfSequence_copy(
    holo_base_msg_common_ParkingSlotfSequence* dst, const holo_base_msg_common_ParkingSlotfSequence* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_common_ParkingSlotdTYPENAME;
}

struct holo_base_msg_common_ParkingSlotdSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_common_ParkingSlotdTypeSupport;
class holo_base_msg_common_ParkingSlotdDataWriter;
class holo_base_msg_common_ParkingSlotdDataReader;
#endif
class holo_base_msg_common_ParkingSlotd
{
public:
    typedef struct holo_base_msg_common_ParkingSlotdSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_common_ParkingSlotdTypeSupport TypeSupport;
    typedef holo_base_msg_common_ParkingSlotdDataWriter  DataWriter;
    typedef holo_base_msg_common_ParkingSlotdDataReader  DataReader;
#endif

    DDS_UnsignedLongLong                   id;
    DDS_Boolean                            is_valid;
    DDS_UnsignedLong                       type;
    DDS_UnsignedLong                       position;
    DDS_UnsignedLong                       status;
    DDS_Double                             width;
    DDS_Double                             height;
    DDS_Double                             angle;
    DDS_Double                             confidence;
    DDS_Boolean                            is_rear_vertex_available;
    holo_base_msg_geometry_Point3dSequence vertices;
    DDS_Boolean                            is_center_vertex_available;
    holo_base_msg_geometry_Point3d         center_vertex;
    DDS_Boolean                            is_stopper_available;
    holo_base_msg_geometry_Point3dSequence stopper_vertices;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_ParkingSlotd_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_ParkingSlotd_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_ParkingSlotd_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ParkingSlotd
#define TSeq holo_base_msg_common_ParkingSlotdSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ParkingSlotd
#define TSeq holo_base_msg_common_ParkingSlotdSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_ParkingSlotd* holo_base_msg_common_ParkingSlotd_create();

NDDSUSERDllExport extern void holo_base_msg_common_ParkingSlotd_delete(holo_base_msg_common_ParkingSlotd* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_ParkingSlotd_initialize(holo_base_msg_common_ParkingSlotd* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_ParkingSlotd_initialize_ex(holo_base_msg_common_ParkingSlotd* self,
                                                                          RTIBool allocatePointers,
                                                                          RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_ParkingSlotd_initialize_w_params(
    holo_base_msg_common_ParkingSlotd* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_ParkingSlotd_finalize(holo_base_msg_common_ParkingSlotd* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_ParkingSlotd_finalize_w_return(holo_base_msg_common_ParkingSlotd* self);

NDDSUSERDllExport void holo_base_msg_common_ParkingSlotd_finalize_ex(holo_base_msg_common_ParkingSlotd* self,
                                                                     RTIBool                            deletePointers);

NDDSUSERDllExport void holo_base_msg_common_ParkingSlotd_finalize_w_params(
    holo_base_msg_common_ParkingSlotd* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_ParkingSlotd_finalize_optional_members(
    holo_base_msg_common_ParkingSlotd* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_ParkingSlotd_copy(holo_base_msg_common_ParkingSlotd*       dst,
                                                                 const holo_base_msg_common_ParkingSlotd* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef holo_base_msg_common_ParkingSlotdSeq holo_base_msg_common_ParkingSlotdSequence;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_ParkingSlotdSequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_ParkingSlotdSequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_ParkingSlotdSequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ParkingSlotdSequence
#define TSeq holo_base_msg_common_ParkingSlotdSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ParkingSlotdSequence
#define TSeq holo_base_msg_common_ParkingSlotdSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_ParkingSlotdSequence* holo_base_msg_common_ParkingSlotdSequence_create();

NDDSUSERDllExport extern void
holo_base_msg_common_ParkingSlotdSequence_delete(holo_base_msg_common_ParkingSlotdSequence* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_common_ParkingSlotdSequence_initialize(holo_base_msg_common_ParkingSlotdSequence* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_ParkingSlotdSequence_initialize_ex(
    holo_base_msg_common_ParkingSlotdSequence* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_ParkingSlotdSequence_initialize_w_params(
    holo_base_msg_common_ParkingSlotdSequence* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_common_ParkingSlotdSequence_finalize(holo_base_msg_common_ParkingSlotdSequence* self);

NDDSUSERDllExport RTIBool
holo_base_msg_common_ParkingSlotdSequence_finalize_w_return(holo_base_msg_common_ParkingSlotdSequence* self);

NDDSUSERDllExport void holo_base_msg_common_ParkingSlotdSequence_finalize_ex(
    holo_base_msg_common_ParkingSlotdSequence* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_common_ParkingSlotdSequence_finalize_w_params(
    holo_base_msg_common_ParkingSlotdSequence* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_ParkingSlotdSequence_finalize_optional_members(
    holo_base_msg_common_ParkingSlotdSequence* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_ParkingSlotdSequence_copy(
    holo_base_msg_common_ParkingSlotdSequence* dst, const holo_base_msg_common_ParkingSlotdSequence* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_common_ParkingSlotFramefTYPENAME;
}

struct holo_base_msg_common_ParkingSlotFramefSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_common_ParkingSlotFramefTypeSupport;
class holo_base_msg_common_ParkingSlotFramefDataWriter;
class holo_base_msg_common_ParkingSlotFramefDataReader;
#endif
class holo_base_msg_common_ParkingSlotFramef
{
public:
    typedef struct holo_base_msg_common_ParkingSlotFramefSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_common_ParkingSlotFramefTypeSupport TypeSupport;
    typedef holo_base_msg_common_ParkingSlotFramefDataWriter  DataWriter;
    typedef holo_base_msg_common_ParkingSlotFramefDataReader  DataReader;
#endif

    holo_base_msg_common_Timestamp            stamp;
    DDS_UnsignedLong                          coord;
    holo_base_msg_common_ParkingSlotfSequence point_list;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_ParkingSlotFramef_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_ParkingSlotFramef_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_ParkingSlotFramef_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ParkingSlotFramef
#define TSeq holo_base_msg_common_ParkingSlotFramefSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ParkingSlotFramef
#define TSeq holo_base_msg_common_ParkingSlotFramefSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_ParkingSlotFramef* holo_base_msg_common_ParkingSlotFramef_create();

NDDSUSERDllExport extern void
holo_base_msg_common_ParkingSlotFramef_delete(holo_base_msg_common_ParkingSlotFramef* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_common_ParkingSlotFramef_initialize(holo_base_msg_common_ParkingSlotFramef* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_ParkingSlotFramef_initialize_ex(
    holo_base_msg_common_ParkingSlotFramef* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_ParkingSlotFramef_initialize_w_params(
    holo_base_msg_common_ParkingSlotFramef* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_ParkingSlotFramef_finalize(holo_base_msg_common_ParkingSlotFramef* self);

NDDSUSERDllExport RTIBool
holo_base_msg_common_ParkingSlotFramef_finalize_w_return(holo_base_msg_common_ParkingSlotFramef* self);

NDDSUSERDllExport void holo_base_msg_common_ParkingSlotFramef_finalize_ex(holo_base_msg_common_ParkingSlotFramef* self,
                                                                          RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_common_ParkingSlotFramef_finalize_w_params(
    holo_base_msg_common_ParkingSlotFramef* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_ParkingSlotFramef_finalize_optional_members(
    holo_base_msg_common_ParkingSlotFramef* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_ParkingSlotFramef_copy(
    holo_base_msg_common_ParkingSlotFramef* dst, const holo_base_msg_common_ParkingSlotFramef* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_common_ParkingSlotFramedTYPENAME;
}

struct holo_base_msg_common_ParkingSlotFramedSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_common_ParkingSlotFramedTypeSupport;
class holo_base_msg_common_ParkingSlotFramedDataWriter;
class holo_base_msg_common_ParkingSlotFramedDataReader;
#endif
class holo_base_msg_common_ParkingSlotFramed
{
public:
    typedef struct holo_base_msg_common_ParkingSlotFramedSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_common_ParkingSlotFramedTypeSupport TypeSupport;
    typedef holo_base_msg_common_ParkingSlotFramedDataWriter  DataWriter;
    typedef holo_base_msg_common_ParkingSlotFramedDataReader  DataReader;
#endif

    holo_base_msg_common_Timestamp            stamp;
    DDS_UnsignedLong                          coord;
    holo_base_msg_common_ParkingSlotdSequence point_list;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_ParkingSlotFramed_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_ParkingSlotFramed_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_ParkingSlotFramed_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ParkingSlotFramed
#define TSeq holo_base_msg_common_ParkingSlotFramedSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ParkingSlotFramed
#define TSeq holo_base_msg_common_ParkingSlotFramedSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_ParkingSlotFramed* holo_base_msg_common_ParkingSlotFramed_create();

NDDSUSERDllExport extern void
holo_base_msg_common_ParkingSlotFramed_delete(holo_base_msg_common_ParkingSlotFramed* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_common_ParkingSlotFramed_initialize(holo_base_msg_common_ParkingSlotFramed* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_ParkingSlotFramed_initialize_ex(
    holo_base_msg_common_ParkingSlotFramed* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_ParkingSlotFramed_initialize_w_params(
    holo_base_msg_common_ParkingSlotFramed* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_ParkingSlotFramed_finalize(holo_base_msg_common_ParkingSlotFramed* self);

NDDSUSERDllExport RTIBool
holo_base_msg_common_ParkingSlotFramed_finalize_w_return(holo_base_msg_common_ParkingSlotFramed* self);

NDDSUSERDllExport void holo_base_msg_common_ParkingSlotFramed_finalize_ex(holo_base_msg_common_ParkingSlotFramed* self,
                                                                          RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_common_ParkingSlotFramed_finalize_w_params(
    holo_base_msg_common_ParkingSlotFramed* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_ParkingSlotFramed_finalize_optional_members(
    holo_base_msg_common_ParkingSlotFramed* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_ParkingSlotFramed_copy(
    holo_base_msg_common_ParkingSlotFramed* dst, const holo_base_msg_common_ParkingSlotFramed* src);

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

#endif /* ParkingSlot */
