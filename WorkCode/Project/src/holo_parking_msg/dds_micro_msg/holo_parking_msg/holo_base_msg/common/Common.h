/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Common.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef Common_1118136791_h
#define Common_1118136791_h

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

typedef DDS_UnsignedLong holo_base_msg_common_Coordinate;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_Coordinate_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_Coordinate_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_Coordinate_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Coordinate
#define TSeq holo_base_msg_common_CoordinateSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Coordinate
#define TSeq holo_base_msg_common_CoordinateSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_Coordinate* holo_base_msg_common_Coordinate_create();

NDDSUSERDllExport extern void holo_base_msg_common_Coordinate_delete(holo_base_msg_common_Coordinate* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_Coordinate_initialize(holo_base_msg_common_Coordinate* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_Coordinate_initialize_ex(holo_base_msg_common_Coordinate* self,
                                                                        RTIBool allocatePointers,
                                                                        RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_Coordinate_initialize_w_params(
    holo_base_msg_common_Coordinate* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_Coordinate_finalize(holo_base_msg_common_Coordinate* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_Coordinate_finalize_w_return(holo_base_msg_common_Coordinate* self);

NDDSUSERDllExport void holo_base_msg_common_Coordinate_finalize_ex(holo_base_msg_common_Coordinate* self,
                                                                   RTIBool                          deletePointers);

NDDSUSERDllExport void holo_base_msg_common_Coordinate_finalize_w_params(
    holo_base_msg_common_Coordinate* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_Coordinate_finalize_optional_members(holo_base_msg_common_Coordinate* self,
                                                                                 RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_Coordinate_copy(holo_base_msg_common_Coordinate*       dst,
                                                               const holo_base_msg_common_Coordinate* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_UnsignedLong holo_base_msg_common_SensorId;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_SensorId_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_SensorId_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_SensorId_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_SensorId
#define TSeq holo_base_msg_common_SensorIdSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_SensorId
#define TSeq holo_base_msg_common_SensorIdSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_SensorId* holo_base_msg_common_SensorId_create();

NDDSUSERDllExport extern void holo_base_msg_common_SensorId_delete(holo_base_msg_common_SensorId* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_SensorId_initialize(holo_base_msg_common_SensorId* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_SensorId_initialize_ex(holo_base_msg_common_SensorId* self,
                                                                      RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_SensorId_initialize_w_params(
    holo_base_msg_common_SensorId* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_SensorId_finalize(holo_base_msg_common_SensorId* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_SensorId_finalize_w_return(holo_base_msg_common_SensorId* self);

NDDSUSERDllExport void holo_base_msg_common_SensorId_finalize_ex(holo_base_msg_common_SensorId* self,
                                                                 RTIBool                        deletePointers);

NDDSUSERDllExport void holo_base_msg_common_SensorId_finalize_w_params(
    holo_base_msg_common_SensorId* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_SensorId_finalize_optional_members(holo_base_msg_common_SensorId* self,
                                                                               RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_SensorId_copy(holo_base_msg_common_SensorId*       dst,
                                                             const holo_base_msg_common_SensorId* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_UnsignedLong holo_base_msg_common_Classification;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_Classification_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_Classification_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_Classification_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Classification
#define TSeq holo_base_msg_common_ClassificationSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Classification
#define TSeq holo_base_msg_common_ClassificationSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_Classification* holo_base_msg_common_Classification_create();

NDDSUSERDllExport extern void holo_base_msg_common_Classification_delete(holo_base_msg_common_Classification* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_Classification_initialize(holo_base_msg_common_Classification* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_Classification_initialize_ex(holo_base_msg_common_Classification* self,
                                                                            RTIBool allocatePointers,
                                                                            RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_Classification_initialize_w_params(
    holo_base_msg_common_Classification* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_Classification_finalize(holo_base_msg_common_Classification* self);

NDDSUSERDllExport RTIBool
holo_base_msg_common_Classification_finalize_w_return(holo_base_msg_common_Classification* self);

NDDSUSERDllExport void holo_base_msg_common_Classification_finalize_ex(holo_base_msg_common_Classification* self,
                                                                       RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_common_Classification_finalize_w_params(
    holo_base_msg_common_Classification* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_Classification_finalize_optional_members(
    holo_base_msg_common_Classification* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_Classification_copy(holo_base_msg_common_Classification*       dst,
                                                                   const holo_base_msg_common_Classification* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_common_DurationTYPENAME;
}

struct holo_base_msg_common_DurationSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_common_DurationTypeSupport;
class holo_base_msg_common_DurationDataWriter;
class holo_base_msg_common_DurationDataReader;
#endif
class holo_base_msg_common_Duration
{
public:
    typedef struct holo_base_msg_common_DurationSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_common_DurationTypeSupport TypeSupport;
    typedef holo_base_msg_common_DurationDataWriter  DataWriter;
    typedef holo_base_msg_common_DurationDataReader  DataReader;
#endif

    DDS_Long         sec;
    DDS_UnsignedLong nsec;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_Duration_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_Duration_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_Duration_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Duration
#define TSeq holo_base_msg_common_DurationSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Duration
#define TSeq holo_base_msg_common_DurationSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_Duration* holo_base_msg_common_Duration_create();

NDDSUSERDllExport extern void holo_base_msg_common_Duration_delete(holo_base_msg_common_Duration* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_Duration_initialize(holo_base_msg_common_Duration* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_Duration_initialize_ex(holo_base_msg_common_Duration* self,
                                                                      RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_Duration_initialize_w_params(
    holo_base_msg_common_Duration* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_Duration_finalize(holo_base_msg_common_Duration* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_Duration_finalize_w_return(holo_base_msg_common_Duration* self);

NDDSUSERDllExport void holo_base_msg_common_Duration_finalize_ex(holo_base_msg_common_Duration* self,
                                                                 RTIBool                        deletePointers);

NDDSUSERDllExport void holo_base_msg_common_Duration_finalize_w_params(
    holo_base_msg_common_Duration* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_Duration_finalize_optional_members(holo_base_msg_common_Duration* self,
                                                                               RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_Duration_copy(holo_base_msg_common_Duration*       dst,
                                                             const holo_base_msg_common_Duration* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_common_TimestampTYPENAME;
}

struct holo_base_msg_common_TimestampSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_common_TimestampTypeSupport;
class holo_base_msg_common_TimestampDataWriter;
class holo_base_msg_common_TimestampDataReader;
#endif
class holo_base_msg_common_Timestamp
{
public:
    typedef struct holo_base_msg_common_TimestampSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_common_TimestampTypeSupport TypeSupport;
    typedef holo_base_msg_common_TimestampDataWriter  DataWriter;
    typedef holo_base_msg_common_TimestampDataReader  DataReader;
#endif

    DDS_UnsignedLong sec;
    DDS_UnsignedLong nsec;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_Timestamp_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_Timestamp_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_Timestamp_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Timestamp
#define TSeq holo_base_msg_common_TimestampSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_Timestamp
#define TSeq holo_base_msg_common_TimestampSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_Timestamp* holo_base_msg_common_Timestamp_create();

NDDSUSERDllExport extern void holo_base_msg_common_Timestamp_delete(holo_base_msg_common_Timestamp* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_Timestamp_initialize(holo_base_msg_common_Timestamp* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_Timestamp_initialize_ex(holo_base_msg_common_Timestamp* self,
                                                                       RTIBool                         allocatePointers,
                                                                       RTIBool                         allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_Timestamp_initialize_w_params(
    holo_base_msg_common_Timestamp* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_Timestamp_finalize(holo_base_msg_common_Timestamp* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_Timestamp_finalize_w_return(holo_base_msg_common_Timestamp* self);

NDDSUSERDllExport void holo_base_msg_common_Timestamp_finalize_ex(holo_base_msg_common_Timestamp* self,
                                                                  RTIBool                         deletePointers);

NDDSUSERDllExport void holo_base_msg_common_Timestamp_finalize_w_params(
    holo_base_msg_common_Timestamp* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_Timestamp_finalize_optional_members(holo_base_msg_common_Timestamp* self,
                                                                                RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_Timestamp_copy(holo_base_msg_common_Timestamp*       dst,
                                                              const holo_base_msg_common_Timestamp* src);

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

#endif /* Common */
