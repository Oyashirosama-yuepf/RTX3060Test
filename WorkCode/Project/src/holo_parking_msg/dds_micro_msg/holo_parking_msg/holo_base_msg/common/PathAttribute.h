/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from PathAttribute.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef PathAttribute_995605_h
#define PathAttribute_995605_h

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

extern "C" {

extern const char* holo_base_msg_common_PathAttributeTYPENAME;
}

struct holo_base_msg_common_PathAttributeSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_common_PathAttributeTypeSupport;
class holo_base_msg_common_PathAttributeDataWriter;
class holo_base_msg_common_PathAttributeDataReader;
#endif
class holo_base_msg_common_PathAttribute
{
public:
    typedef struct holo_base_msg_common_PathAttributeSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_common_PathAttributeTypeSupport TypeSupport;
    typedef holo_base_msg_common_PathAttributeDataWriter  DataWriter;
    typedef holo_base_msg_common_PathAttributeDataReader  DataReader;
#endif

    holo_base_msg_common_Timestamp timestamp;
    DDS_Octet                      path_gear;
    DDS_Octet                      path_id;
    DDS_Octet                      path_type;
    DDS_Octet                      path_size;
    DDS_Octet                      plan_complete;
    DDS_Octet                      plan_error;
    DDS_Float                      path_len;
    DDS_Float                      remain_path_len;
    DDS_Octet                      brk_flag;
    DDS_Float                      brk_dist;
    DDS_Float                      speed_limit;
    DDS_Octet                      lamp_req;
    DDS_Octet                      read_file_status;
    DDS_Float                      ref_lat_error;
    DDS_Float                      ref_heading_error;
    DDS_Float                      road_curvature;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_PathAttribute_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_PathAttribute_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_PathAttribute_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PathAttribute
#define TSeq holo_base_msg_common_PathAttributeSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_PathAttribute
#define TSeq holo_base_msg_common_PathAttributeSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_PathAttribute* holo_base_msg_common_PathAttribute_create();

NDDSUSERDllExport extern void holo_base_msg_common_PathAttribute_delete(holo_base_msg_common_PathAttribute* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_PathAttribute_initialize(holo_base_msg_common_PathAttribute* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_PathAttribute_initialize_ex(holo_base_msg_common_PathAttribute* self,
                                                                           RTIBool allocatePointers,
                                                                           RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_PathAttribute_initialize_w_params(
    holo_base_msg_common_PathAttribute* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_PathAttribute_finalize(holo_base_msg_common_PathAttribute* self);

NDDSUSERDllExport RTIBool
holo_base_msg_common_PathAttribute_finalize_w_return(holo_base_msg_common_PathAttribute* self);

NDDSUSERDllExport void holo_base_msg_common_PathAttribute_finalize_ex(holo_base_msg_common_PathAttribute* self,
                                                                      RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_common_PathAttribute_finalize_w_params(
    holo_base_msg_common_PathAttribute* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_PathAttribute_finalize_optional_members(
    holo_base_msg_common_PathAttribute* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_PathAttribute_copy(holo_base_msg_common_PathAttribute*       dst,
                                                                  const holo_base_msg_common_PathAttribute* src);

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

#endif /* PathAttribute */
