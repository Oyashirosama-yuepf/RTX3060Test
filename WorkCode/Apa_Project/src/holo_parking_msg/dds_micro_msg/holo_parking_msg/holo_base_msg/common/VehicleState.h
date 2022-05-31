/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from VehicleState.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef VehicleState_157436955_h
#define VehicleState_157436955_h

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

extern const char* holo_base_msg_common_ChassisStateTYPENAME;
}

struct holo_base_msg_common_ChassisStateSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_common_ChassisStateTypeSupport;
class holo_base_msg_common_ChassisStateDataWriter;
class holo_base_msg_common_ChassisStateDataReader;
#endif
class holo_base_msg_common_ChassisState
{
public:
    typedef struct holo_base_msg_common_ChassisStateSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_common_ChassisStateTypeSupport TypeSupport;
    typedef holo_base_msg_common_ChassisStateDataWriter  DataWriter;
    typedef holo_base_msg_common_ChassisStateDataReader  DataReader;
#endif

    holo_base_msg_common_Timestamp stamp;
    DDS_Float                      vehicle_speed;
    DDS_Float                      front_left_wheel_speed;
    DDS_Float                      front_right_wheel_speed;
    DDS_Float                      rear_left_wheel_speed;
    DDS_Float                      rear_right_wheel_speed;
    DDS_Float                      lon_acceleration;
    DDS_Float                      lat_acceleration;
    DDS_Float                      yaw_rate;
    DDS_Float                      front_wheel_angle;
    DDS_Float                      longitudinal_control_value;
    DDS_Octet                      energy_source_level;
    DDS_Octet                      gear_pos;
    DDS_Octet                      gear_level;
    DDS_UnsignedLong               state_flags;
    DDS_UnsignedLong               invalid_flags;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_ChassisState_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_ChassisState_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_ChassisState_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ChassisState
#define TSeq holo_base_msg_common_ChassisStateSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_ChassisState
#define TSeq holo_base_msg_common_ChassisStateSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_ChassisState* holo_base_msg_common_ChassisState_create();

NDDSUSERDllExport extern void holo_base_msg_common_ChassisState_delete(holo_base_msg_common_ChassisState* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_ChassisState_initialize(holo_base_msg_common_ChassisState* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_ChassisState_initialize_ex(holo_base_msg_common_ChassisState* self,
                                                                          RTIBool allocatePointers,
                                                                          RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_ChassisState_initialize_w_params(
    holo_base_msg_common_ChassisState* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_ChassisState_finalize(holo_base_msg_common_ChassisState* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_ChassisState_finalize_w_return(holo_base_msg_common_ChassisState* self);

NDDSUSERDllExport void holo_base_msg_common_ChassisState_finalize_ex(holo_base_msg_common_ChassisState* self,
                                                                     RTIBool                            deletePointers);

NDDSUSERDllExport void holo_base_msg_common_ChassisState_finalize_w_params(
    holo_base_msg_common_ChassisState* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_ChassisState_finalize_optional_members(
    holo_base_msg_common_ChassisState* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_ChassisState_copy(holo_base_msg_common_ChassisState*       dst,
                                                                 const holo_base_msg_common_ChassisState* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_common_VehicleBodyStateTYPENAME;
}

struct holo_base_msg_common_VehicleBodyStateSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_common_VehicleBodyStateTypeSupport;
class holo_base_msg_common_VehicleBodyStateDataWriter;
class holo_base_msg_common_VehicleBodyStateDataReader;
#endif
class holo_base_msg_common_VehicleBodyState
{
public:
    typedef struct holo_base_msg_common_VehicleBodyStateSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_common_VehicleBodyStateTypeSupport TypeSupport;
    typedef holo_base_msg_common_VehicleBodyStateDataWriter  DataWriter;
    typedef holo_base_msg_common_VehicleBodyStateDataReader  DataReader;
#endif

    holo_base_msg_common_Timestamp stamp;
    DDS_Float                      front_left_tire_pressure;
    DDS_Float                      front_right_tire_pressure;
    DDS_Float                      rear_left_tire_pressure;
    DDS_Float                      rear_right_tire_pressure;
    DDS_UnsignedLong               state_flags;
    DDS_UnsignedLong               invalid_flags;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_common_VehicleBodyState_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_common_VehicleBodyState_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_common_VehicleBodyState_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_VehicleBodyState
#define TSeq holo_base_msg_common_VehicleBodyStateSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_common_VehicleBodyState
#define TSeq holo_base_msg_common_VehicleBodyStateSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_common_VehicleBodyState* holo_base_msg_common_VehicleBodyState_create();

NDDSUSERDllExport extern void
holo_base_msg_common_VehicleBodyState_delete(holo_base_msg_common_VehicleBodyState* sample);

NDDSUSERDllExport RTIBool holo_base_msg_common_VehicleBodyState_initialize(holo_base_msg_common_VehicleBodyState* self);

NDDSUSERDllExport RTIBool holo_base_msg_common_VehicleBodyState_initialize_ex(
    holo_base_msg_common_VehicleBodyState* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_common_VehicleBodyState_initialize_w_params(
    holo_base_msg_common_VehicleBodyState* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_common_VehicleBodyState_finalize(holo_base_msg_common_VehicleBodyState* self);

NDDSUSERDllExport RTIBool
holo_base_msg_common_VehicleBodyState_finalize_w_return(holo_base_msg_common_VehicleBodyState* self);

NDDSUSERDllExport void holo_base_msg_common_VehicleBodyState_finalize_ex(holo_base_msg_common_VehicleBodyState* self,
                                                                         RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_common_VehicleBodyState_finalize_w_params(
    holo_base_msg_common_VehicleBodyState* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_common_VehicleBodyState_finalize_optional_members(
    holo_base_msg_common_VehicleBodyState* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_common_VehicleBodyState_copy(holo_base_msg_common_VehicleBodyState*       dst,
                                                                     const holo_base_msg_common_VehicleBodyState* src);

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

#endif /* VehicleState */
