/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Control.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef Control_48527166_h
#define Control_48527166_h

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

extern const char* holo_base_msg_common_ControlCommandTYPENAME;
}

struct holo_base_msg_common_ControlCommandSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_common_ControlCommandTypeSupport;
class holo_base_msg_common_ControlCommandDataWriter;
class holo_base_msg_common_ControlCommandDataReader;
#endif
class holo_base_msg_common_ControlCommand
{
public:
    typedef struct holo_base_msg_common_ControlCommandSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_common_ControlCommandTypeSupport TypeSupport;
    typedef holo_base_msg_common_ControlCommandDataWriter  DataWriter;
    typedef holo_base_msg_common_ControlCommandDataReader  DataReader;
#endif

    holo_base_msg_common_Timestamp stamp;
    DDS_Float                      acceleration;
    DDS_Float                      front_wheel_angle;
    DDS_UnsignedShort              light_control_command;
    DDS_UnsignedShort              cockpit_control_command;
    DDS_Octet                      gear_control_command;
    DDS_Octet                      actuator_control_command;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_ControlCommand_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_ControlCommand_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_ControlCommand_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ControlCommand
#define TSeq holo_base_msg_common_ControlCommandSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ControlCommand
#define TSeq holo_base_msg_common_ControlCommandSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_ControlCommand* holo_base_msg_common_ControlCommand_create();

NDDSUSERDllExport extern void holo_base_msg_common_ControlCommand_delete(holo_base_msg_common_ControlCommand* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_ControlCommand_initialize(holo_base_msg_common_ControlCommand* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_ControlCommand_initialize_ex(holo_base_msg_common_ControlCommand* self,
                                                                            RTIBool allocatePointers,
                                                                            RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_ControlCommand_initialize_w_params(
    holo_base_msg_common_ControlCommand* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_ControlCommand_finalize(holo_base_msg_common_ControlCommand* self);

NDDSUSERDllExport RTIBool
holo_base_msg_common_ControlCommand_finalize_w_return(holo_base_msg_common_ControlCommand* self);

NDDSUSERDllExport void holo_base_msg_common_ControlCommand_finalize_ex(holo_base_msg_common_ControlCommand* self,
                                                                       RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_common_ControlCommand_finalize_w_params(
    holo_base_msg_common_ControlCommand* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_ControlCommand_finalize_optional_members(
    holo_base_msg_common_ControlCommand* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_ControlCommand_copy(holo_base_msg_common_ControlCommand*       dst,
                                                                   const holo_base_msg_common_ControlCommand* src);

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

#endif /* Control */
