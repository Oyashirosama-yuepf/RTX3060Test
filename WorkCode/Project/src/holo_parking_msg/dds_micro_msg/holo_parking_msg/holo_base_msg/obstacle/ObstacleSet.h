/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ObstacleSet.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef ObstacleSet_406046225_h
#define ObstacleSet_406046225_h

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

#include "holo_parking_msg/holo_base_msg/geometry/Box.h"

#include "holo_parking_msg/holo_base_msg/geometry/Point.h"

#include "holo_parking_msg/holo_base_msg/numerics/Vector.h"

#include "holo_parking_msg/holo_base_msg/vision/ImageObjects.h"

typedef DDS_Octet holo_base_msg_obstacle_CutInCutOut;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_obstacle_CutInCutOut_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_obstacle_CutInCutOut_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_obstacle_CutInCutOut_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_CutInCutOut
#define TSeq holo_base_msg_obstacle_CutInCutOutSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_CutInCutOut
#define TSeq holo_base_msg_obstacle_CutInCutOutSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_obstacle_CutInCutOut* holo_base_msg_obstacle_CutInCutOut_create();

NDDSUSERDllExport extern void holo_base_msg_obstacle_CutInCutOut_delete(holo_base_msg_obstacle_CutInCutOut* sample);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_CutInCutOut_initialize(holo_base_msg_obstacle_CutInCutOut* self);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_CutInCutOut_initialize_ex(holo_base_msg_obstacle_CutInCutOut* self,
                                                                           RTIBool allocatePointers,
                                                                           RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_CutInCutOut_initialize_w_params(
    holo_base_msg_obstacle_CutInCutOut* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_CutInCutOut_finalize(holo_base_msg_obstacle_CutInCutOut* self);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_CutInCutOut_finalize_w_return(holo_base_msg_obstacle_CutInCutOut* self);

NDDSUSERDllExport void holo_base_msg_obstacle_CutInCutOut_finalize_ex(holo_base_msg_obstacle_CutInCutOut* self,
                                                                      RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_obstacle_CutInCutOut_finalize_w_params(
    holo_base_msg_obstacle_CutInCutOut* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_obstacle_CutInCutOut_finalize_optional_members(
    holo_base_msg_obstacle_CutInCutOut* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_CutInCutOut_copy(holo_base_msg_obstacle_CutInCutOut*       dst,
                                                                  const holo_base_msg_obstacle_CutInCutOut* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_Octet holo_base_msg_obstacle_MotionStatus;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_obstacle_MotionStatus_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_obstacle_MotionStatus_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_obstacle_MotionStatus_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_MotionStatus
#define TSeq holo_base_msg_obstacle_MotionStatusSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_MotionStatus
#define TSeq holo_base_msg_obstacle_MotionStatusSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_obstacle_MotionStatus* holo_base_msg_obstacle_MotionStatus_create();

NDDSUSERDllExport extern void holo_base_msg_obstacle_MotionStatus_delete(holo_base_msg_obstacle_MotionStatus* sample);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_MotionStatus_initialize(holo_base_msg_obstacle_MotionStatus* self);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_MotionStatus_initialize_ex(holo_base_msg_obstacle_MotionStatus* self,
                                                                            RTIBool allocatePointers,
                                                                            RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_MotionStatus_initialize_w_params(
    holo_base_msg_obstacle_MotionStatus* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_MotionStatus_finalize(holo_base_msg_obstacle_MotionStatus* self);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_MotionStatus_finalize_w_return(holo_base_msg_obstacle_MotionStatus* self);

NDDSUSERDllExport void holo_base_msg_obstacle_MotionStatus_finalize_ex(holo_base_msg_obstacle_MotionStatus* self,
                                                                       RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_obstacle_MotionStatus_finalize_w_params(
    holo_base_msg_obstacle_MotionStatus* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_obstacle_MotionStatus_finalize_optional_members(
    holo_base_msg_obstacle_MotionStatus* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_MotionStatus_copy(holo_base_msg_obstacle_MotionStatus*       dst,
                                                                   const holo_base_msg_obstacle_MotionStatus* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_UnsignedLong holo_base_msg_obstacle_PerceptionAbility;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_obstacle_PerceptionAbility_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_obstacle_PerceptionAbility_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_obstacle_PerceptionAbility_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_PerceptionAbility
#define TSeq holo_base_msg_obstacle_PerceptionAbilitySeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_PerceptionAbility
#define TSeq holo_base_msg_obstacle_PerceptionAbilitySeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_obstacle_PerceptionAbility* holo_base_msg_obstacle_PerceptionAbility_create();

NDDSUSERDllExport extern void
holo_base_msg_obstacle_PerceptionAbility_delete(holo_base_msg_obstacle_PerceptionAbility* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_PerceptionAbility_initialize(holo_base_msg_obstacle_PerceptionAbility* self);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_PerceptionAbility_initialize_ex(
    holo_base_msg_obstacle_PerceptionAbility* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_PerceptionAbility_initialize_w_params(
    holo_base_msg_obstacle_PerceptionAbility* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_PerceptionAbility_finalize(holo_base_msg_obstacle_PerceptionAbility* self);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_PerceptionAbility_finalize_w_return(holo_base_msg_obstacle_PerceptionAbility* self);

NDDSUSERDllExport void holo_base_msg_obstacle_PerceptionAbility_finalize_ex(
    holo_base_msg_obstacle_PerceptionAbility* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_obstacle_PerceptionAbility_finalize_w_params(
    holo_base_msg_obstacle_PerceptionAbility* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_obstacle_PerceptionAbility_finalize_optional_members(
    holo_base_msg_obstacle_PerceptionAbility* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_PerceptionAbility_copy(
    holo_base_msg_obstacle_PerceptionAbility* dst, const holo_base_msg_obstacle_PerceptionAbility* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_obstacle_ObstacleGeneralTYPENAME;
}

struct holo_base_msg_obstacle_ObstacleGeneralSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_obstacle_ObstacleGeneralTypeSupport;
class holo_base_msg_obstacle_ObstacleGeneralDataWriter;
class holo_base_msg_obstacle_ObstacleGeneralDataReader;
#endif
class holo_base_msg_obstacle_ObstacleGeneral
{
public:
    typedef struct holo_base_msg_obstacle_ObstacleGeneralSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_obstacle_ObstacleGeneralTypeSupport TypeSupport;
    typedef holo_base_msg_obstacle_ObstacleGeneralDataWriter  DataWriter;
    typedef holo_base_msg_obstacle_ObstacleGeneralDataReader  DataReader;
#endif

    holo_base_msg_common_Timestamp         stamp;
    DDS_UnsignedLong                       coord;
    DDS_UnsignedLong                       obstacle_id;
    DDS_UnsignedLong                       sensor_id;
    DDS_UnsignedLong                       classification;
    DDS_Float                              obstacle_exist_score;
    holo_base_msg_geometry_Point3f         position;
    holo_base_msg_numerics_Vector3f        relative_velocity;
    holo_base_msg_numerics_Vector3f        absolute_velocity;
    holo_base_msg_numerics_Vector3f        acceleration;
    DDS_Octet                              motion_status;
    holo_base_msg_geometry_Box3f           bounding_box3;
    DDS_Octet                              cut_in_cut_out;
    holo_base_msg_geometry_Point3fSequence contour_points;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_obstacle_ObstacleGeneral_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_obstacle_ObstacleGeneral_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_obstacle_ObstacleGeneral_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleGeneral
#define TSeq holo_base_msg_obstacle_ObstacleGeneralSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleGeneral
#define TSeq holo_base_msg_obstacle_ObstacleGeneralSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_obstacle_ObstacleGeneral* holo_base_msg_obstacle_ObstacleGeneral_create();

NDDSUSERDllExport extern void
holo_base_msg_obstacle_ObstacleGeneral_delete(holo_base_msg_obstacle_ObstacleGeneral* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_ObstacleGeneral_initialize(holo_base_msg_obstacle_ObstacleGeneral* self);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleGeneral_initialize_ex(
    holo_base_msg_obstacle_ObstacleGeneral* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleGeneral_initialize_w_params(
    holo_base_msg_obstacle_ObstacleGeneral* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleGeneral_finalize(holo_base_msg_obstacle_ObstacleGeneral* self);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_ObstacleGeneral_finalize_w_return(holo_base_msg_obstacle_ObstacleGeneral* self);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleGeneral_finalize_ex(holo_base_msg_obstacle_ObstacleGeneral* self,
                                                                          RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleGeneral_finalize_w_params(
    holo_base_msg_obstacle_ObstacleGeneral* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleGeneral_finalize_optional_members(
    holo_base_msg_obstacle_ObstacleGeneral* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleGeneral_copy(
    holo_base_msg_obstacle_ObstacleGeneral* dst, const holo_base_msg_obstacle_ObstacleGeneral* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef holo_base_msg_obstacle_ObstacleGeneralSeq holo_base_msg_obstacle_ObstacleGeneralSequence;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_obstacle_ObstacleGeneralSequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_obstacle_ObstacleGeneralSequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_obstacle_ObstacleGeneralSequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleGeneralSequence
#define TSeq holo_base_msg_obstacle_ObstacleGeneralSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleGeneralSequence
#define TSeq holo_base_msg_obstacle_ObstacleGeneralSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_obstacle_ObstacleGeneralSequence*
holo_base_msg_obstacle_ObstacleGeneralSequence_create();

NDDSUSERDllExport extern void
holo_base_msg_obstacle_ObstacleGeneralSequence_delete(holo_base_msg_obstacle_ObstacleGeneralSequence* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_ObstacleGeneralSequence_initialize(holo_base_msg_obstacle_ObstacleGeneralSequence* self);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleGeneralSequence_initialize_ex(
    holo_base_msg_obstacle_ObstacleGeneralSequence* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleGeneralSequence_initialize_w_params(
    holo_base_msg_obstacle_ObstacleGeneralSequence* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_ObstacleGeneralSequence_finalize(holo_base_msg_obstacle_ObstacleGeneralSequence* self);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_ObstacleGeneralSequence_finalize_w_return(holo_base_msg_obstacle_ObstacleGeneralSequence* self);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleGeneralSequence_finalize_ex(
    holo_base_msg_obstacle_ObstacleGeneralSequence* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleGeneralSequence_finalize_w_params(
    holo_base_msg_obstacle_ObstacleGeneralSequence* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleGeneralSequence_finalize_optional_members(
    holo_base_msg_obstacle_ObstacleGeneralSequence* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleGeneralSequence_copy(
    holo_base_msg_obstacle_ObstacleGeneralSequence* dst, const holo_base_msg_obstacle_ObstacleGeneralSequence* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_obstacle_ObstacleGeneralListTYPENAME;
}

struct holo_base_msg_obstacle_ObstacleGeneralListSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_obstacle_ObstacleGeneralListTypeSupport;
class holo_base_msg_obstacle_ObstacleGeneralListDataWriter;
class holo_base_msg_obstacle_ObstacleGeneralListDataReader;
#endif
class holo_base_msg_obstacle_ObstacleGeneralList
{
public:
    typedef struct holo_base_msg_obstacle_ObstacleGeneralListSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_obstacle_ObstacleGeneralListTypeSupport TypeSupport;
    typedef holo_base_msg_obstacle_ObstacleGeneralListDataWriter  DataWriter;
    typedef holo_base_msg_obstacle_ObstacleGeneralListDataReader  DataReader;
#endif

    holo_base_msg_common_Timestamp                 stamp;
    DDS_UnsignedLong                               coord;
    DDS_UnsignedLong                               sensor_id;
    DDS_UnsignedLong                               perception_ability;
    holo_base_msg_obstacle_ObstacleGeneralSequence obstacles;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_obstacle_ObstacleGeneralList_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_obstacle_ObstacleGeneralList_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_obstacle_ObstacleGeneralList_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleGeneralList
#define TSeq holo_base_msg_obstacle_ObstacleGeneralListSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleGeneralList
#define TSeq holo_base_msg_obstacle_ObstacleGeneralListSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_obstacle_ObstacleGeneralList*
holo_base_msg_obstacle_ObstacleGeneralList_create();

NDDSUSERDllExport extern void
holo_base_msg_obstacle_ObstacleGeneralList_delete(holo_base_msg_obstacle_ObstacleGeneralList* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_ObstacleGeneralList_initialize(holo_base_msg_obstacle_ObstacleGeneralList* self);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleGeneralList_initialize_ex(
    holo_base_msg_obstacle_ObstacleGeneralList* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleGeneralList_initialize_w_params(
    holo_base_msg_obstacle_ObstacleGeneralList* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_ObstacleGeneralList_finalize(holo_base_msg_obstacle_ObstacleGeneralList* self);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_ObstacleGeneralList_finalize_w_return(holo_base_msg_obstacle_ObstacleGeneralList* self);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleGeneralList_finalize_ex(
    holo_base_msg_obstacle_ObstacleGeneralList* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleGeneralList_finalize_w_params(
    holo_base_msg_obstacle_ObstacleGeneralList* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleGeneralList_finalize_optional_members(
    holo_base_msg_obstacle_ObstacleGeneralList* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleGeneralList_copy(
    holo_base_msg_obstacle_ObstacleGeneralList* dst, const holo_base_msg_obstacle_ObstacleGeneralList* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_obstacle_ObstacleRadarTYPENAME;
}

struct holo_base_msg_obstacle_ObstacleRadarSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_obstacle_ObstacleRadarTypeSupport;
class holo_base_msg_obstacle_ObstacleRadarDataWriter;
class holo_base_msg_obstacle_ObstacleRadarDataReader;
#endif
class holo_base_msg_obstacle_ObstacleRadar
{
public:
    typedef struct holo_base_msg_obstacle_ObstacleRadarSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_obstacle_ObstacleRadarTypeSupport TypeSupport;
    typedef holo_base_msg_obstacle_ObstacleRadarDataWriter  DataWriter;
    typedef holo_base_msg_obstacle_ObstacleRadarDataReader  DataReader;
#endif

    holo_base_msg_common_Timestamp  stamp;
    DDS_UnsignedLong                coord;
    DDS_UnsignedLong                obstacle_id;
    DDS_UnsignedLong                sensor_id;
    DDS_UnsignedLong                classification;
    DDS_Float                       obstacle_exist_score;
    holo_base_msg_geometry_Point3f  position;
    holo_base_msg_geometry_Point3f  position_sigma;
    holo_base_msg_numerics_Vector3f relative_velocity;
    holo_base_msg_numerics_Vector3f relative_velocity_sigma;
    holo_base_msg_numerics_Vector3f acceleration;
    holo_base_msg_numerics_Vector3f acceleration_sigma;
    DDS_Octet                       motion_status;
    holo_base_msg_numerics_Vector3f shape;
    DDS_Float                       obstacle_rcs;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_obstacle_ObstacleRadar_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_obstacle_ObstacleRadar_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_obstacle_ObstacleRadar_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleRadar
#define TSeq holo_base_msg_obstacle_ObstacleRadarSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleRadar
#define TSeq holo_base_msg_obstacle_ObstacleRadarSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_obstacle_ObstacleRadar* holo_base_msg_obstacle_ObstacleRadar_create();

NDDSUSERDllExport extern void holo_base_msg_obstacle_ObstacleRadar_delete(holo_base_msg_obstacle_ObstacleRadar* sample);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleRadar_initialize(holo_base_msg_obstacle_ObstacleRadar* self);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleRadar_initialize_ex(holo_base_msg_obstacle_ObstacleRadar* self,
                                                                             RTIBool allocatePointers,
                                                                             RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleRadar_initialize_w_params(
    holo_base_msg_obstacle_ObstacleRadar* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleRadar_finalize(holo_base_msg_obstacle_ObstacleRadar* self);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_ObstacleRadar_finalize_w_return(holo_base_msg_obstacle_ObstacleRadar* self);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleRadar_finalize_ex(holo_base_msg_obstacle_ObstacleRadar* self,
                                                                        RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleRadar_finalize_w_params(
    holo_base_msg_obstacle_ObstacleRadar* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleRadar_finalize_optional_members(
    holo_base_msg_obstacle_ObstacleRadar* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleRadar_copy(holo_base_msg_obstacle_ObstacleRadar*       dst,
                                                                    const holo_base_msg_obstacle_ObstacleRadar* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef holo_base_msg_obstacle_ObstacleRadarSeq holo_base_msg_obstacle_ObstacleRadarSequence;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_obstacle_ObstacleRadarSequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_obstacle_ObstacleRadarSequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_obstacle_ObstacleRadarSequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleRadarSequence
#define TSeq holo_base_msg_obstacle_ObstacleRadarSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleRadarSequence
#define TSeq holo_base_msg_obstacle_ObstacleRadarSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_obstacle_ObstacleRadarSequence*
holo_base_msg_obstacle_ObstacleRadarSequence_create();

NDDSUSERDllExport extern void
holo_base_msg_obstacle_ObstacleRadarSequence_delete(holo_base_msg_obstacle_ObstacleRadarSequence* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_ObstacleRadarSequence_initialize(holo_base_msg_obstacle_ObstacleRadarSequence* self);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleRadarSequence_initialize_ex(
    holo_base_msg_obstacle_ObstacleRadarSequence* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleRadarSequence_initialize_w_params(
    holo_base_msg_obstacle_ObstacleRadarSequence* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_ObstacleRadarSequence_finalize(holo_base_msg_obstacle_ObstacleRadarSequence* self);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_ObstacleRadarSequence_finalize_w_return(holo_base_msg_obstacle_ObstacleRadarSequence* self);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleRadarSequence_finalize_ex(
    holo_base_msg_obstacle_ObstacleRadarSequence* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleRadarSequence_finalize_w_params(
    holo_base_msg_obstacle_ObstacleRadarSequence* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleRadarSequence_finalize_optional_members(
    holo_base_msg_obstacle_ObstacleRadarSequence* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleRadarSequence_copy(
    holo_base_msg_obstacle_ObstacleRadarSequence* dst, const holo_base_msg_obstacle_ObstacleRadarSequence* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_obstacle_ObstacleRadarListTYPENAME;
}

struct holo_base_msg_obstacle_ObstacleRadarListSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_obstacle_ObstacleRadarListTypeSupport;
class holo_base_msg_obstacle_ObstacleRadarListDataWriter;
class holo_base_msg_obstacle_ObstacleRadarListDataReader;
#endif
class holo_base_msg_obstacle_ObstacleRadarList
{
public:
    typedef struct holo_base_msg_obstacle_ObstacleRadarListSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_obstacle_ObstacleRadarListTypeSupport TypeSupport;
    typedef holo_base_msg_obstacle_ObstacleRadarListDataWriter  DataWriter;
    typedef holo_base_msg_obstacle_ObstacleRadarListDataReader  DataReader;
#endif

    holo_base_msg_common_Timestamp               stamp;
    DDS_UnsignedLong                             coord;
    DDS_UnsignedLong                             sensor_id;
    DDS_UnsignedLong                             perception_ability;
    holo_base_msg_obstacle_ObstacleRadarSequence obstacles;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_obstacle_ObstacleRadarList_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_obstacle_ObstacleRadarList_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_obstacle_ObstacleRadarList_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleRadarList
#define TSeq holo_base_msg_obstacle_ObstacleRadarListSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleRadarList
#define TSeq holo_base_msg_obstacle_ObstacleRadarListSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_obstacle_ObstacleRadarList* holo_base_msg_obstacle_ObstacleRadarList_create();

NDDSUSERDllExport extern void
holo_base_msg_obstacle_ObstacleRadarList_delete(holo_base_msg_obstacle_ObstacleRadarList* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_ObstacleRadarList_initialize(holo_base_msg_obstacle_ObstacleRadarList* self);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleRadarList_initialize_ex(
    holo_base_msg_obstacle_ObstacleRadarList* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleRadarList_initialize_w_params(
    holo_base_msg_obstacle_ObstacleRadarList* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_ObstacleRadarList_finalize(holo_base_msg_obstacle_ObstacleRadarList* self);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_ObstacleRadarList_finalize_w_return(holo_base_msg_obstacle_ObstacleRadarList* self);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleRadarList_finalize_ex(
    holo_base_msg_obstacle_ObstacleRadarList* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleRadarList_finalize_w_params(
    holo_base_msg_obstacle_ObstacleRadarList* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleRadarList_finalize_optional_members(
    holo_base_msg_obstacle_ObstacleRadarList* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleRadarList_copy(
    holo_base_msg_obstacle_ObstacleRadarList* dst, const holo_base_msg_obstacle_ObstacleRadarList* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_obstacle_ObstacleUssTYPENAME;
}

struct holo_base_msg_obstacle_ObstacleUssSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_obstacle_ObstacleUssTypeSupport;
class holo_base_msg_obstacle_ObstacleUssDataWriter;
class holo_base_msg_obstacle_ObstacleUssDataReader;
#endif
class holo_base_msg_obstacle_ObstacleUss
{
public:
    typedef struct holo_base_msg_obstacle_ObstacleUssSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_obstacle_ObstacleUssTypeSupport TypeSupport;
    typedef holo_base_msg_obstacle_ObstacleUssDataWriter  DataWriter;
    typedef holo_base_msg_obstacle_ObstacleUssDataReader  DataReader;
#endif

    holo_base_msg_common_Timestamp stamp;
    DDS_UnsignedLong               coord;
    DDS_UnsignedLong               obstacle_id;
    DDS_UnsignedLong               sensor_id;
    DDS_UnsignedLong               classification;
    DDS_Float                      obstacle_exist_score;
    holo_base_msg_geometry_Point3f position;
    holo_base_msg_geometry_Point3f position_sigma;
    DDS_Float                      fov;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_obstacle_ObstacleUss_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_obstacle_ObstacleUss_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_obstacle_ObstacleUss_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleUss
#define TSeq holo_base_msg_obstacle_ObstacleUssSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleUss
#define TSeq holo_base_msg_obstacle_ObstacleUssSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_obstacle_ObstacleUss* holo_base_msg_obstacle_ObstacleUss_create();

NDDSUSERDllExport extern void holo_base_msg_obstacle_ObstacleUss_delete(holo_base_msg_obstacle_ObstacleUss* sample);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleUss_initialize(holo_base_msg_obstacle_ObstacleUss* self);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleUss_initialize_ex(holo_base_msg_obstacle_ObstacleUss* self,
                                                                           RTIBool allocatePointers,
                                                                           RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleUss_initialize_w_params(
    holo_base_msg_obstacle_ObstacleUss* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleUss_finalize(holo_base_msg_obstacle_ObstacleUss* self);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_ObstacleUss_finalize_w_return(holo_base_msg_obstacle_ObstacleUss* self);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleUss_finalize_ex(holo_base_msg_obstacle_ObstacleUss* self,
                                                                      RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleUss_finalize_w_params(
    holo_base_msg_obstacle_ObstacleUss* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleUss_finalize_optional_members(
    holo_base_msg_obstacle_ObstacleUss* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleUss_copy(holo_base_msg_obstacle_ObstacleUss*       dst,
                                                                  const holo_base_msg_obstacle_ObstacleUss* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef holo_base_msg_obstacle_ObstacleUssSeq holo_base_msg_obstacle_ObstacleUssSequence;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_obstacle_ObstacleUssSequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_obstacle_ObstacleUssSequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_obstacle_ObstacleUssSequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleUssSequence
#define TSeq holo_base_msg_obstacle_ObstacleUssSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleUssSequence
#define TSeq holo_base_msg_obstacle_ObstacleUssSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_obstacle_ObstacleUssSequence*
holo_base_msg_obstacle_ObstacleUssSequence_create();

NDDSUSERDllExport extern void
holo_base_msg_obstacle_ObstacleUssSequence_delete(holo_base_msg_obstacle_ObstacleUssSequence* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_ObstacleUssSequence_initialize(holo_base_msg_obstacle_ObstacleUssSequence* self);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleUssSequence_initialize_ex(
    holo_base_msg_obstacle_ObstacleUssSequence* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleUssSequence_initialize_w_params(
    holo_base_msg_obstacle_ObstacleUssSequence* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_ObstacleUssSequence_finalize(holo_base_msg_obstacle_ObstacleUssSequence* self);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_ObstacleUssSequence_finalize_w_return(holo_base_msg_obstacle_ObstacleUssSequence* self);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleUssSequence_finalize_ex(
    holo_base_msg_obstacle_ObstacleUssSequence* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleUssSequence_finalize_w_params(
    holo_base_msg_obstacle_ObstacleUssSequence* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleUssSequence_finalize_optional_members(
    holo_base_msg_obstacle_ObstacleUssSequence* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleUssSequence_copy(
    holo_base_msg_obstacle_ObstacleUssSequence* dst, const holo_base_msg_obstacle_ObstacleUssSequence* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_obstacle_ObstacleUssListTYPENAME;
}

struct holo_base_msg_obstacle_ObstacleUssListSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_obstacle_ObstacleUssListTypeSupport;
class holo_base_msg_obstacle_ObstacleUssListDataWriter;
class holo_base_msg_obstacle_ObstacleUssListDataReader;
#endif
class holo_base_msg_obstacle_ObstacleUssList
{
public:
    typedef struct holo_base_msg_obstacle_ObstacleUssListSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_obstacle_ObstacleUssListTypeSupport TypeSupport;
    typedef holo_base_msg_obstacle_ObstacleUssListDataWriter  DataWriter;
    typedef holo_base_msg_obstacle_ObstacleUssListDataReader  DataReader;
#endif

    holo_base_msg_common_Timestamp             stamp;
    DDS_UnsignedLong                           coord;
    DDS_UnsignedLong                           sensor_id;
    DDS_UnsignedLong                           perception_ability;
    holo_base_msg_obstacle_ObstacleUssSequence obstacles;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_obstacle_ObstacleUssList_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_obstacle_ObstacleUssList_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_obstacle_ObstacleUssList_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleUssList
#define TSeq holo_base_msg_obstacle_ObstacleUssListSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleUssList
#define TSeq holo_base_msg_obstacle_ObstacleUssListSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_obstacle_ObstacleUssList* holo_base_msg_obstacle_ObstacleUssList_create();

NDDSUSERDllExport extern void
holo_base_msg_obstacle_ObstacleUssList_delete(holo_base_msg_obstacle_ObstacleUssList* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_ObstacleUssList_initialize(holo_base_msg_obstacle_ObstacleUssList* self);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleUssList_initialize_ex(
    holo_base_msg_obstacle_ObstacleUssList* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleUssList_initialize_w_params(
    holo_base_msg_obstacle_ObstacleUssList* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleUssList_finalize(holo_base_msg_obstacle_ObstacleUssList* self);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_ObstacleUssList_finalize_w_return(holo_base_msg_obstacle_ObstacleUssList* self);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleUssList_finalize_ex(holo_base_msg_obstacle_ObstacleUssList* self,
                                                                          RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleUssList_finalize_w_params(
    holo_base_msg_obstacle_ObstacleUssList* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleUssList_finalize_optional_members(
    holo_base_msg_obstacle_ObstacleUssList* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleUssList_copy(
    holo_base_msg_obstacle_ObstacleUssList* dst, const holo_base_msg_obstacle_ObstacleUssList* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_obstacle_ObstacleVisionTYPENAME;
}

struct holo_base_msg_obstacle_ObstacleVisionSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_obstacle_ObstacleVisionTypeSupport;
class holo_base_msg_obstacle_ObstacleVisionDataWriter;
class holo_base_msg_obstacle_ObstacleVisionDataReader;
#endif
class holo_base_msg_obstacle_ObstacleVision
{
public:
    typedef struct holo_base_msg_obstacle_ObstacleVisionSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_obstacle_ObstacleVisionTypeSupport TypeSupport;
    typedef holo_base_msg_obstacle_ObstacleVisionDataWriter  DataWriter;
    typedef holo_base_msg_obstacle_ObstacleVisionDataReader  DataReader;
#endif

    holo_base_msg_common_Timestamp          stamp;
    DDS_UnsignedLong                        coord;
    DDS_UnsignedLong                        obstacle_id;
    DDS_UnsignedLong                        sensor_id;
    DDS_UnsignedLong                        classification;
    DDS_Float                               obstacle_exist_score;
    holo_base_msg_geometry_Point3f          position;
    holo_base_msg_geometry_Point3f          position_sigma;
    holo_base_msg_numerics_Vector3f         relative_velocity;
    holo_base_msg_numerics_Vector3f         relative_velocity_sigma;
    holo_base_msg_numerics_Vector3f         acceleration;
    holo_base_msg_numerics_Vector3f         acceleration_sigma;
    DDS_Octet                               motion_status;
    holo_base_msg_geometry_Box2f            bounding_box2;
    holo_base_msg_geometry_Box3f            bounding_box3;
    DDS_Octet                               cut_in_cut_out;
    holo_base_msg_vision_KeyPoint2fSequence key_points;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_obstacle_ObstacleVision_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_obstacle_ObstacleVision_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_obstacle_ObstacleVision_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleVision
#define TSeq holo_base_msg_obstacle_ObstacleVisionSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleVision
#define TSeq holo_base_msg_obstacle_ObstacleVisionSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_obstacle_ObstacleVision* holo_base_msg_obstacle_ObstacleVision_create();

NDDSUSERDllExport extern void
holo_base_msg_obstacle_ObstacleVision_delete(holo_base_msg_obstacle_ObstacleVision* sample);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleVision_initialize(holo_base_msg_obstacle_ObstacleVision* self);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleVision_initialize_ex(
    holo_base_msg_obstacle_ObstacleVision* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleVision_initialize_w_params(
    holo_base_msg_obstacle_ObstacleVision* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleVision_finalize(holo_base_msg_obstacle_ObstacleVision* self);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_ObstacleVision_finalize_w_return(holo_base_msg_obstacle_ObstacleVision* self);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleVision_finalize_ex(holo_base_msg_obstacle_ObstacleVision* self,
                                                                         RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleVision_finalize_w_params(
    holo_base_msg_obstacle_ObstacleVision* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleVision_finalize_optional_members(
    holo_base_msg_obstacle_ObstacleVision* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleVision_copy(holo_base_msg_obstacle_ObstacleVision*       dst,
                                                                     const holo_base_msg_obstacle_ObstacleVision* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef holo_base_msg_obstacle_ObstacleVisionSeq holo_base_msg_obstacle_ObstacleVisionSequence;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_obstacle_ObstacleVisionSequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_obstacle_ObstacleVisionSequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_obstacle_ObstacleVisionSequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleVisionSequence
#define TSeq holo_base_msg_obstacle_ObstacleVisionSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleVisionSequence
#define TSeq holo_base_msg_obstacle_ObstacleVisionSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_obstacle_ObstacleVisionSequence*
holo_base_msg_obstacle_ObstacleVisionSequence_create();

NDDSUSERDllExport extern void
holo_base_msg_obstacle_ObstacleVisionSequence_delete(holo_base_msg_obstacle_ObstacleVisionSequence* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_ObstacleVisionSequence_initialize(holo_base_msg_obstacle_ObstacleVisionSequence* self);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleVisionSequence_initialize_ex(
    holo_base_msg_obstacle_ObstacleVisionSequence* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleVisionSequence_initialize_w_params(
    holo_base_msg_obstacle_ObstacleVisionSequence* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_ObstacleVisionSequence_finalize(holo_base_msg_obstacle_ObstacleVisionSequence* self);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_ObstacleVisionSequence_finalize_w_return(holo_base_msg_obstacle_ObstacleVisionSequence* self);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleVisionSequence_finalize_ex(
    holo_base_msg_obstacle_ObstacleVisionSequence* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleVisionSequence_finalize_w_params(
    holo_base_msg_obstacle_ObstacleVisionSequence* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleVisionSequence_finalize_optional_members(
    holo_base_msg_obstacle_ObstacleVisionSequence* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleVisionSequence_copy(
    holo_base_msg_obstacle_ObstacleVisionSequence* dst, const holo_base_msg_obstacle_ObstacleVisionSequence* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_obstacle_ObstacleVisionListTYPENAME;
}

struct holo_base_msg_obstacle_ObstacleVisionListSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_obstacle_ObstacleVisionListTypeSupport;
class holo_base_msg_obstacle_ObstacleVisionListDataWriter;
class holo_base_msg_obstacle_ObstacleVisionListDataReader;
#endif
class holo_base_msg_obstacle_ObstacleVisionList
{
public:
    typedef struct holo_base_msg_obstacle_ObstacleVisionListSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_obstacle_ObstacleVisionListTypeSupport TypeSupport;
    typedef holo_base_msg_obstacle_ObstacleVisionListDataWriter  DataWriter;
    typedef holo_base_msg_obstacle_ObstacleVisionListDataReader  DataReader;
#endif

    holo_base_msg_common_Timestamp                stamp;
    DDS_UnsignedLong                              coord;
    DDS_UnsignedLong                              sensor_id;
    DDS_UnsignedLong                              perception_ability;
    holo_base_msg_obstacle_ObstacleVisionSequence obstacles;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_obstacle_ObstacleVisionList_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_obstacle_ObstacleVisionList_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_obstacle_ObstacleVisionList_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleVisionList
#define TSeq holo_base_msg_obstacle_ObstacleVisionListSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_obstacle_ObstacleVisionList
#define TSeq holo_base_msg_obstacle_ObstacleVisionListSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_obstacle_ObstacleVisionList* holo_base_msg_obstacle_ObstacleVisionList_create();

NDDSUSERDllExport extern void
holo_base_msg_obstacle_ObstacleVisionList_delete(holo_base_msg_obstacle_ObstacleVisionList* sample);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_ObstacleVisionList_initialize(holo_base_msg_obstacle_ObstacleVisionList* self);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleVisionList_initialize_ex(
    holo_base_msg_obstacle_ObstacleVisionList* self, RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleVisionList_initialize_w_params(
    holo_base_msg_obstacle_ObstacleVisionList* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_ObstacleVisionList_finalize(holo_base_msg_obstacle_ObstacleVisionList* self);

NDDSUSERDllExport RTIBool
holo_base_msg_obstacle_ObstacleVisionList_finalize_w_return(holo_base_msg_obstacle_ObstacleVisionList* self);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleVisionList_finalize_ex(
    holo_base_msg_obstacle_ObstacleVisionList* self, RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleVisionList_finalize_w_params(
    holo_base_msg_obstacle_ObstacleVisionList* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_obstacle_ObstacleVisionList_finalize_optional_members(
    holo_base_msg_obstacle_ObstacleVisionList* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_obstacle_ObstacleVisionList_copy(
    holo_base_msg_obstacle_ObstacleVisionList* dst, const holo_base_msg_obstacle_ObstacleVisionList* src);

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

#endif /* ObstacleSet */
