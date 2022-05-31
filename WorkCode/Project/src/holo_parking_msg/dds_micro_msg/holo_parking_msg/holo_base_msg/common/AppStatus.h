/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from AppStatus.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef AppStatus_1768679987_h
#define AppStatus_1768679987_h

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

#include "holo_parking_msg/holo_base_msg/common/Common.h"

extern "C" {

extern const char* holo_base_msg_common_AppStatusTYPENAME;
}

struct holo_base_msg_common_AppStatusSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_common_AppStatusTypeSupport;
class holo_base_msg_common_AppStatusDataWriter;
class holo_base_msg_common_AppStatusDataReader;
#endif
class holo_base_msg_common_AppStatus
{
public:
    typedef struct holo_base_msg_common_AppStatusSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_common_AppStatusTypeSupport TypeSupport;
    typedef holo_base_msg_common_AppStatusDataWriter  DataWriter;
    typedef holo_base_msg_common_AppStatusDataReader  DataReader;
#endif

    holo_base_msg_common_Timestamp   stamp;
    DDS_Octet                        nodeid;
    holo_base_msg_core_Uint8Sequence status_codes;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_AppStatus_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_AppStatus_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_AppStatus_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_AppStatus
#define TSeq holo_base_msg_common_AppStatusSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_AppStatus
#define TSeq holo_base_msg_common_AppStatusSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_AppStatus* holo_base_msg_common_AppStatus_create();

NDDSUSERDllExport extern void holo_base_msg_common_AppStatus_delete(holo_base_msg_common_AppStatus* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_AppStatus_initialize(holo_base_msg_common_AppStatus* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_AppStatus_initialize_ex(holo_base_msg_common_AppStatus* self,
                                                                       RTIBool                         allocatePointers,
                                                                       RTIBool                         allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_AppStatus_initialize_w_params(
    holo_base_msg_common_AppStatus* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_AppStatus_finalize(holo_base_msg_common_AppStatus* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_AppStatus_finalize_w_return(holo_base_msg_common_AppStatus* self);

NDDSUSERDllExport void holo_base_msg_common_AppStatus_finalize_ex(holo_base_msg_common_AppStatus* self,
                                                                  RTIBool                         deletePointers);

NDDSUSERDllExport void holo_base_msg_common_AppStatus_finalize_w_params(
    holo_base_msg_common_AppStatus* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_AppStatus_finalize_optional_members(holo_base_msg_common_AppStatus* self,
                                                                                RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_AppStatus_copy(holo_base_msg_common_AppStatus*       dst,
                                                              const holo_base_msg_common_AppStatus* src);

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

#endif /* AppStatus */
