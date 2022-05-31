/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from PointFeaturefList.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef PointFeaturefList_564303241_h
#define PointFeaturefList_564303241_h

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

#include "holo_parking_msg/holo_base_msg/common/PointFeaturef.h"

typedef holo_base_msg_common_PointFeaturefSeq holo_base_msg_common_PointFeaturefVector;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_PointFeaturefVector_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_PointFeaturefVector_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_PointFeaturefVector_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PointFeaturefVector
#define TSeq holo_base_msg_common_PointFeaturefVectorSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PointFeaturefVector
#define TSeq holo_base_msg_common_PointFeaturefVectorSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_PointFeaturefVector* holo_base_msg_common_PointFeaturefVector_create();

NDDSUSERDllExport extern void
holo_base_msg_common_PointFeaturefVector_delete(holo_base_msg_common_PointFeaturefVector* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_common_PointFeaturefVector_initialize(holo_base_msg_common_PointFeaturefVector* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_PointFeaturefVector_initialize_ex(
    holo_base_msg_common_PointFeaturefVector* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_PointFeaturefVector_initialize_w_params(
    holo_base_msg_common_PointFeaturefVector* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_common_PointFeaturefVector_finalize(holo_base_msg_common_PointFeaturefVector* self);

NDDSUSERDllExport RTIBool
holo_base_msg_common_PointFeaturefVector_finalize_w_return(holo_base_msg_common_PointFeaturefVector* self);

NDDSUSERDllExport void holo_base_msg_common_PointFeaturefVector_finalize_ex(
    holo_base_msg_common_PointFeaturefVector* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_common_PointFeaturefVector_finalize_w_params(
    holo_base_msg_common_PointFeaturefVector* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_PointFeaturefVector_finalize_optional_members(
    holo_base_msg_common_PointFeaturefVector* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_PointFeaturefVector_copy(
    holo_base_msg_common_PointFeaturefVector* dst, const holo_base_msg_common_PointFeaturefVector* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_common_PointFeaturefListTYPENAME;
}

struct holo_base_msg_common_PointFeaturefListSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_common_PointFeaturefListTypeSupport;
class holo_base_msg_common_PointFeaturefListDataWriter;
class holo_base_msg_common_PointFeaturefListDataReader;
#endif
class holo_base_msg_common_PointFeaturefList
{
public:
    typedef struct holo_base_msg_common_PointFeaturefListSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_common_PointFeaturefListTypeSupport TypeSupport;
    typedef holo_base_msg_common_PointFeaturefListDataWriter  DataWriter;
    typedef holo_base_msg_common_PointFeaturefListDataReader  DataReader;
#endif

    holo_base_msg_common_Timestamp           stamp;
    DDS_UnsignedLong                         sensor_id;
    holo_base_msg_common_PointFeaturefVector point_feature_list;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_PointFeaturefList_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_PointFeaturefList_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_PointFeaturefList_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PointFeaturefList
#define TSeq holo_base_msg_common_PointFeaturefListSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PointFeaturefList
#define TSeq holo_base_msg_common_PointFeaturefListSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_PointFeaturefList* holo_base_msg_common_PointFeaturefList_create();

NDDSUSERDllExport extern void
holo_base_msg_common_PointFeaturefList_delete(holo_base_msg_common_PointFeaturefList* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_common_PointFeaturefList_initialize(holo_base_msg_common_PointFeaturefList* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_PointFeaturefList_initialize_ex(
    holo_base_msg_common_PointFeaturefList* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_PointFeaturefList_initialize_w_params(
    holo_base_msg_common_PointFeaturefList* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_PointFeaturefList_finalize(holo_base_msg_common_PointFeaturefList* self);

NDDSUSERDllExport RTIBool
holo_base_msg_common_PointFeaturefList_finalize_w_return(holo_base_msg_common_PointFeaturefList* self);

NDDSUSERDllExport void holo_base_msg_common_PointFeaturefList_finalize_ex(holo_base_msg_common_PointFeaturefList* self,
                                                                          RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_common_PointFeaturefList_finalize_w_params(
    holo_base_msg_common_PointFeaturefList* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_PointFeaturefList_finalize_optional_members(
    holo_base_msg_common_PointFeaturefList* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_PointFeaturefList_copy(
    holo_base_msg_common_PointFeaturefList* dst, const holo_base_msg_common_PointFeaturefList* src);

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

#endif /* PointFeaturefList */
