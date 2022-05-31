/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Line.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef Line_1252162399_h
#define Line_1252162399_h

#ifndef rti_me_cpp_hxx
#include "rti_me_cpp.hxx"
#endif

#include "dds_c/dds_c_typecode.h"

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#include "holo_parking_msg/holo_base_msg/numerics/Vector.h"

extern "C" {

extern const char* holo_base_msg_geometry_Line2fTYPENAME;
}

struct holo_base_msg_geometry_Line2fSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_geometry_Line2fTypeSupport;
class holo_base_msg_geometry_Line2fDataWriter;
class holo_base_msg_geometry_Line2fDataReader;
#endif
class holo_base_msg_geometry_Line2f
{
public:
    typedef struct holo_base_msg_geometry_Line2fSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_geometry_Line2fTypeSupport TypeSupport;
    typedef holo_base_msg_geometry_Line2fDataWriter  DataWriter;
    typedef holo_base_msg_geometry_Line2fDataReader  DataReader;
#endif

    holo_base_msg_numerics_Vector3f cofficients;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_geometry_Line2f_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_geometry_Line2f_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_geometry_Line2f_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Line2f
#define TSeq holo_base_msg_geometry_Line2fSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Line2f
#define TSeq holo_base_msg_geometry_Line2fSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_geometry_Line2f* holo_base_msg_geometry_Line2f_create();

NDDSUSERDllExport extern void holo_base_msg_geometry_Line2f_delete(holo_base_msg_geometry_Line2f* sample);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Line2f_initialize(holo_base_msg_geometry_Line2f* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Line2f_initialize_ex(holo_base_msg_geometry_Line2f* self,
                                                                      RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Line2f_initialize_w_params(
    holo_base_msg_geometry_Line2f* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Line2f_finalize(holo_base_msg_geometry_Line2f* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Line2f_finalize_w_return(holo_base_msg_geometry_Line2f* self);

NDDSUSERDllExport void holo_base_msg_geometry_Line2f_finalize_ex(holo_base_msg_geometry_Line2f* self,
                                                                 RTIBool                        deletePointers);

NDDSUSERDllExport void holo_base_msg_geometry_Line2f_finalize_w_params(
    holo_base_msg_geometry_Line2f* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_geometry_Line2f_finalize_optional_members(holo_base_msg_geometry_Line2f* self,
                                                                               RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Line2f_copy(holo_base_msg_geometry_Line2f*       dst,
                                                             const holo_base_msg_geometry_Line2f* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_geometry_Line2dTYPENAME;
}

struct holo_base_msg_geometry_Line2dSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_geometry_Line2dTypeSupport;
class holo_base_msg_geometry_Line2dDataWriter;
class holo_base_msg_geometry_Line2dDataReader;
#endif
class holo_base_msg_geometry_Line2d
{
public:
    typedef struct holo_base_msg_geometry_Line2dSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_geometry_Line2dTypeSupport TypeSupport;
    typedef holo_base_msg_geometry_Line2dDataWriter  DataWriter;
    typedef holo_base_msg_geometry_Line2dDataReader  DataReader;
#endif

    holo_base_msg_numerics_Vector3d cofficients;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_geometry_Line2d_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_geometry_Line2d_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_geometry_Line2d_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Line2d
#define TSeq holo_base_msg_geometry_Line2dSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_geometry_Line2d
#define TSeq holo_base_msg_geometry_Line2dSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_geometry_Line2d* holo_base_msg_geometry_Line2d_create();

NDDSUSERDllExport extern void holo_base_msg_geometry_Line2d_delete(holo_base_msg_geometry_Line2d* sample);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Line2d_initialize(holo_base_msg_geometry_Line2d* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Line2d_initialize_ex(holo_base_msg_geometry_Line2d* self,
                                                                      RTIBool allocatePointers, RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Line2d_initialize_w_params(
    holo_base_msg_geometry_Line2d* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Line2d_finalize(holo_base_msg_geometry_Line2d* self);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Line2d_finalize_w_return(holo_base_msg_geometry_Line2d* self);

NDDSUSERDllExport void holo_base_msg_geometry_Line2d_finalize_ex(holo_base_msg_geometry_Line2d* self,
                                                                 RTIBool                        deletePointers);

NDDSUSERDllExport void holo_base_msg_geometry_Line2d_finalize_w_params(
    holo_base_msg_geometry_Line2d* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_geometry_Line2d_finalize_optional_members(holo_base_msg_geometry_Line2d* self,
                                                                               RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_geometry_Line2d_copy(holo_base_msg_geometry_Line2d*       dst,
                                                             const holo_base_msg_geometry_Line2d* src);

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

#endif /* Line */
