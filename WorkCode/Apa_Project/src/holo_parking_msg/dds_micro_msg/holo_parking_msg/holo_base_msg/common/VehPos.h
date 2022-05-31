/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from VehPos.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef VehPos_250448227_h
#define VehPos_250448227_h

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

extern "C" {

extern const char* holo_base_msg_common_VehPosX3VTYPENAME;
}

struct holo_base_msg_common_VehPosX3VSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_common_VehPosX3VTypeSupport;
class holo_base_msg_common_VehPosX3VDataWriter;
class holo_base_msg_common_VehPosX3VDataReader;
#endif
class holo_base_msg_common_VehPosX3V
{
public:
    typedef struct holo_base_msg_common_VehPosX3VSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_common_VehPosX3VTypeSupport TypeSupport;
    typedef holo_base_msg_common_VehPosX3VDataWriter  DataWriter;
    typedef holo_base_msg_common_VehPosX3VDataReader  DataReader;
#endif

    DDS_Float curv;
    DDS_Float vehPos_X;
    DDS_Float vehPos_Y;
    DDS_Float vehPos_Yaw;
    DDS_Float vehPosPred_X;
    DDS_Float vehPosPred_Y;
    DDS_Float vehPosPred_Yaw;
    DDS_Octet vehStatus;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_VehPosX3V_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_VehPosX3V_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_VehPosX3V_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_VehPosX3V
#define TSeq holo_base_msg_common_VehPosX3VSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_VehPosX3V
#define TSeq holo_base_msg_common_VehPosX3VSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_VehPosX3V* holo_base_msg_common_VehPosX3V_create();

NDDSUSERDllExport extern void holo_base_msg_common_VehPosX3V_delete(holo_base_msg_common_VehPosX3V* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_VehPosX3V_initialize(holo_base_msg_common_VehPosX3V* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_VehPosX3V_initialize_ex(holo_base_msg_common_VehPosX3V* self,
                                                                       RTIBool                         allocatePointers,
                                                                       RTIBool                         allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_VehPosX3V_initialize_w_params(
    holo_base_msg_common_VehPosX3V* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_VehPosX3V_finalize(holo_base_msg_common_VehPosX3V* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_VehPosX3V_finalize_w_return(holo_base_msg_common_VehPosX3V* self);

NDDSUSERDllExport void holo_base_msg_common_VehPosX3V_finalize_ex(holo_base_msg_common_VehPosX3V* self,
                                                                  RTIBool                         deletePointers);

NDDSUSERDllExport void holo_base_msg_common_VehPosX3V_finalize_w_params(
    holo_base_msg_common_VehPosX3V* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_VehPosX3V_finalize_optional_members(holo_base_msg_common_VehPosX3V* self,
                                                                                RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_VehPosX3V_copy(holo_base_msg_common_VehPosX3V*       dst,
                                                              const holo_base_msg_common_VehPosX3V* src);

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

#endif /* VehPos */
