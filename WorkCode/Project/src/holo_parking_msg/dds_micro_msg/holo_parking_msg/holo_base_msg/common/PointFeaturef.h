/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from PointFeaturef.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef PointFeaturef_1361043412_h
#define PointFeaturef_1361043412_h

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

typedef DDS_FloatSeq holo_base_msg_common_DescriptorType;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_DescriptorType_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_DescriptorType_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_DescriptorType_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_DescriptorType
#define TSeq holo_base_msg_common_DescriptorTypeSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_DescriptorType
#define TSeq holo_base_msg_common_DescriptorTypeSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_DescriptorType* holo_base_msg_common_DescriptorType_create();

NDDSUSERDllExport extern void holo_base_msg_common_DescriptorType_delete(holo_base_msg_common_DescriptorType* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_DescriptorType_initialize(holo_base_msg_common_DescriptorType* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_DescriptorType_initialize_ex(holo_base_msg_common_DescriptorType* self,
                                                                            RTIBool allocatePointers,
                                                                            RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_DescriptorType_initialize_w_params(
    holo_base_msg_common_DescriptorType* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_DescriptorType_finalize(holo_base_msg_common_DescriptorType* self);

NDDSUSERDllExport RTIBool
holo_base_msg_common_DescriptorType_finalize_w_return(holo_base_msg_common_DescriptorType* self);

NDDSUSERDllExport void holo_base_msg_common_DescriptorType_finalize_ex(holo_base_msg_common_DescriptorType* self,
                                                                       RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_common_DescriptorType_finalize_w_params(
    holo_base_msg_common_DescriptorType* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_DescriptorType_finalize_optional_members(
    holo_base_msg_common_DescriptorType* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_DescriptorType_copy(holo_base_msg_common_DescriptorType*       dst,
                                                                   const holo_base_msg_common_DescriptorType* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_common_PointFeaturefTYPENAME;
}

struct holo_base_msg_common_PointFeaturefSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_common_PointFeaturefTypeSupport;
class holo_base_msg_common_PointFeaturefDataWriter;
class holo_base_msg_common_PointFeaturefDataReader;
#endif
class holo_base_msg_common_PointFeaturef
{
public:
    typedef struct holo_base_msg_common_PointFeaturefSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_common_PointFeaturefTypeSupport TypeSupport;
    typedef holo_base_msg_common_PointFeaturefDataWriter  DataWriter;
    typedef holo_base_msg_common_PointFeaturefDataReader  DataReader;
#endif

    DDS_Float                           x;
    DDS_Float                           y;
    holo_base_msg_common_DescriptorType descriptor;
    DDS_Float                           confidence;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_PointFeaturef_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_PointFeaturef_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_PointFeaturef_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PointFeaturef
#define TSeq holo_base_msg_common_PointFeaturefSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PointFeaturef
#define TSeq holo_base_msg_common_PointFeaturefSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_PointFeaturef* holo_base_msg_common_PointFeaturef_create();

NDDSUSERDllExport extern void holo_base_msg_common_PointFeaturef_delete(holo_base_msg_common_PointFeaturef* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_PointFeaturef_initialize(holo_base_msg_common_PointFeaturef* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_PointFeaturef_initialize_ex(holo_base_msg_common_PointFeaturef* self,
                                                                           RTIBool allocatePointers,
                                                                           RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_PointFeaturef_initialize_w_params(
    holo_base_msg_common_PointFeaturef* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_PointFeaturef_finalize(holo_base_msg_common_PointFeaturef* self);

NDDSUSERDllExport RTIBool
holo_base_msg_common_PointFeaturef_finalize_w_return(holo_base_msg_common_PointFeaturef* self);

NDDSUSERDllExport void holo_base_msg_common_PointFeaturef_finalize_ex(holo_base_msg_common_PointFeaturef* self,
                                                                      RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_common_PointFeaturef_finalize_w_params(
    holo_base_msg_common_PointFeaturef* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_PointFeaturef_finalize_optional_members(
    holo_base_msg_common_PointFeaturef* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_PointFeaturef_copy(holo_base_msg_common_PointFeaturef*       dst,
                                                                  const holo_base_msg_common_PointFeaturef* src);

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

#endif /* PointFeaturef */
