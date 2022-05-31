/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Matrix.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef Matrix_41037854_h
#define Matrix_41037854_h

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

typedef DDS_DoubleSeq holo_base_msg_numerics_MatrixdData;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_numerics_MatrixdData_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_numerics_MatrixdData_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_numerics_MatrixdData_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_MatrixdData
#define TSeq holo_base_msg_numerics_MatrixdDataSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_MatrixdData
#define TSeq holo_base_msg_numerics_MatrixdDataSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_numerics_MatrixdData* holo_base_msg_numerics_MatrixdData_create();

NDDSUSERDllExport extern void holo_base_msg_numerics_MatrixdData_delete(holo_base_msg_numerics_MatrixdData* sample);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_MatrixdData_initialize(holo_base_msg_numerics_MatrixdData* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_MatrixdData_initialize_ex(holo_base_msg_numerics_MatrixdData* self,
                                                                           RTIBool allocatePointers,
                                                                           RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_MatrixdData_initialize_w_params(
    holo_base_msg_numerics_MatrixdData* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_MatrixdData_finalize(holo_base_msg_numerics_MatrixdData* self);

NDDSUSERDllExport RTIBool
holo_base_msg_numerics_MatrixdData_finalize_w_return(holo_base_msg_numerics_MatrixdData* self);

NDDSUSERDllExport void holo_base_msg_numerics_MatrixdData_finalize_ex(holo_base_msg_numerics_MatrixdData* self,
                                                                      RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_numerics_MatrixdData_finalize_w_params(
    holo_base_msg_numerics_MatrixdData* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_numerics_MatrixdData_finalize_optional_members(
    holo_base_msg_numerics_MatrixdData* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_MatrixdData_copy(holo_base_msg_numerics_MatrixdData*       dst,
                                                                  const holo_base_msg_numerics_MatrixdData* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_numerics_MatrixdTYPENAME;
}

struct holo_base_msg_numerics_MatrixdSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_numerics_MatrixdTypeSupport;
class holo_base_msg_numerics_MatrixdDataWriter;
class holo_base_msg_numerics_MatrixdDataReader;
#endif
class holo_base_msg_numerics_Matrixd
{
public:
    typedef struct holo_base_msg_numerics_MatrixdSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_numerics_MatrixdTypeSupport TypeSupport;
    typedef holo_base_msg_numerics_MatrixdDataWriter  DataWriter;
    typedef holo_base_msg_numerics_MatrixdDataReader  DataReader;
#endif

    DDS_Long                           rows;
    DDS_Long                           cols;
    holo_base_msg_numerics_MatrixdData data;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_numerics_Matrixd_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_numerics_Matrixd_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_numerics_Matrixd_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrixd
#define TSeq holo_base_msg_numerics_MatrixdSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrixd
#define TSeq holo_base_msg_numerics_MatrixdSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_numerics_Matrixd* holo_base_msg_numerics_Matrixd_create();

NDDSUSERDllExport extern void holo_base_msg_numerics_Matrixd_delete(holo_base_msg_numerics_Matrixd* sample);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrixd_initialize(holo_base_msg_numerics_Matrixd* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrixd_initialize_ex(holo_base_msg_numerics_Matrixd* self,
                                                                       RTIBool                         allocatePointers,
                                                                       RTIBool                         allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrixd_initialize_w_params(
    holo_base_msg_numerics_Matrixd* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrixd_finalize(holo_base_msg_numerics_Matrixd* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrixd_finalize_w_return(holo_base_msg_numerics_Matrixd* self);

NDDSUSERDllExport void holo_base_msg_numerics_Matrixd_finalize_ex(holo_base_msg_numerics_Matrixd* self,
                                                                  RTIBool                         deletePointers);

NDDSUSERDllExport void holo_base_msg_numerics_Matrixd_finalize_w_params(
    holo_base_msg_numerics_Matrixd* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_numerics_Matrixd_finalize_optional_members(holo_base_msg_numerics_Matrixd* self,
                                                                                RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrixd_copy(holo_base_msg_numerics_Matrixd*       dst,
                                                              const holo_base_msg_numerics_Matrixd* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_Double holo_base_msg_numerics_Matrix22d[2][2];
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_numerics_Matrix22d_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_numerics_Matrix22d_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_numerics_Matrix22d_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix22d
#define TSeq holo_base_msg_numerics_Matrix22dSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix22d
#define TSeq holo_base_msg_numerics_Matrix22dSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_numerics_Matrix22d* holo_base_msg_numerics_Matrix22d_create();

NDDSUSERDllExport extern void holo_base_msg_numerics_Matrix22d_delete(holo_base_msg_numerics_Matrix22d* sample);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix22d_initialize(holo_base_msg_numerics_Matrix22d* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix22d_initialize_ex(holo_base_msg_numerics_Matrix22d* self,
                                                                         RTIBool allocatePointers,
                                                                         RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix22d_initialize_w_params(
    holo_base_msg_numerics_Matrix22d* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix22d_finalize(holo_base_msg_numerics_Matrix22d* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix22d_finalize_w_return(holo_base_msg_numerics_Matrix22d* self);

NDDSUSERDllExport void holo_base_msg_numerics_Matrix22d_finalize_ex(holo_base_msg_numerics_Matrix22d* self,
                                                                    RTIBool                           deletePointers);

NDDSUSERDllExport void holo_base_msg_numerics_Matrix22d_finalize_w_params(
    holo_base_msg_numerics_Matrix22d* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_numerics_Matrix22d_finalize_optional_members(
    holo_base_msg_numerics_Matrix22d* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix22d_copy(holo_base_msg_numerics_Matrix22d*       dst,
                                                                const holo_base_msg_numerics_Matrix22d* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_Double holo_base_msg_numerics_Matrix33d[3][3];
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_numerics_Matrix33d_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_numerics_Matrix33d_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_numerics_Matrix33d_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix33d
#define TSeq holo_base_msg_numerics_Matrix33dSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix33d
#define TSeq holo_base_msg_numerics_Matrix33dSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_numerics_Matrix33d* holo_base_msg_numerics_Matrix33d_create();

NDDSUSERDllExport extern void holo_base_msg_numerics_Matrix33d_delete(holo_base_msg_numerics_Matrix33d* sample);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix33d_initialize(holo_base_msg_numerics_Matrix33d* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix33d_initialize_ex(holo_base_msg_numerics_Matrix33d* self,
                                                                         RTIBool allocatePointers,
                                                                         RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix33d_initialize_w_params(
    holo_base_msg_numerics_Matrix33d* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix33d_finalize(holo_base_msg_numerics_Matrix33d* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix33d_finalize_w_return(holo_base_msg_numerics_Matrix33d* self);

NDDSUSERDllExport void holo_base_msg_numerics_Matrix33d_finalize_ex(holo_base_msg_numerics_Matrix33d* self,
                                                                    RTIBool                           deletePointers);

NDDSUSERDllExport void holo_base_msg_numerics_Matrix33d_finalize_w_params(
    holo_base_msg_numerics_Matrix33d* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_numerics_Matrix33d_finalize_optional_members(
    holo_base_msg_numerics_Matrix33d* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix33d_copy(holo_base_msg_numerics_Matrix33d*       dst,
                                                                const holo_base_msg_numerics_Matrix33d* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_Double holo_base_msg_numerics_Matrix44d[4][4];
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_numerics_Matrix44d_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_numerics_Matrix44d_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_numerics_Matrix44d_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix44d
#define TSeq holo_base_msg_numerics_Matrix44dSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix44d
#define TSeq holo_base_msg_numerics_Matrix44dSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_numerics_Matrix44d* holo_base_msg_numerics_Matrix44d_create();

NDDSUSERDllExport extern void holo_base_msg_numerics_Matrix44d_delete(holo_base_msg_numerics_Matrix44d* sample);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix44d_initialize(holo_base_msg_numerics_Matrix44d* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix44d_initialize_ex(holo_base_msg_numerics_Matrix44d* self,
                                                                         RTIBool allocatePointers,
                                                                         RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix44d_initialize_w_params(
    holo_base_msg_numerics_Matrix44d* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix44d_finalize(holo_base_msg_numerics_Matrix44d* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix44d_finalize_w_return(holo_base_msg_numerics_Matrix44d* self);

NDDSUSERDllExport void holo_base_msg_numerics_Matrix44d_finalize_ex(holo_base_msg_numerics_Matrix44d* self,
                                                                    RTIBool                           deletePointers);

NDDSUSERDllExport void holo_base_msg_numerics_Matrix44d_finalize_w_params(
    holo_base_msg_numerics_Matrix44d* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_numerics_Matrix44d_finalize_optional_members(
    holo_base_msg_numerics_Matrix44d* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix44d_copy(holo_base_msg_numerics_Matrix44d*       dst,
                                                                const holo_base_msg_numerics_Matrix44d* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_Double holo_base_msg_numerics_Matrix55d[5][5];
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_numerics_Matrix55d_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_numerics_Matrix55d_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_numerics_Matrix55d_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix55d
#define TSeq holo_base_msg_numerics_Matrix55dSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix55d
#define TSeq holo_base_msg_numerics_Matrix55dSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_numerics_Matrix55d* holo_base_msg_numerics_Matrix55d_create();

NDDSUSERDllExport extern void holo_base_msg_numerics_Matrix55d_delete(holo_base_msg_numerics_Matrix55d* sample);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix55d_initialize(holo_base_msg_numerics_Matrix55d* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix55d_initialize_ex(holo_base_msg_numerics_Matrix55d* self,
                                                                         RTIBool allocatePointers,
                                                                         RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix55d_initialize_w_params(
    holo_base_msg_numerics_Matrix55d* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix55d_finalize(holo_base_msg_numerics_Matrix55d* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix55d_finalize_w_return(holo_base_msg_numerics_Matrix55d* self);

NDDSUSERDllExport void holo_base_msg_numerics_Matrix55d_finalize_ex(holo_base_msg_numerics_Matrix55d* self,
                                                                    RTIBool                           deletePointers);

NDDSUSERDllExport void holo_base_msg_numerics_Matrix55d_finalize_w_params(
    holo_base_msg_numerics_Matrix55d* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_numerics_Matrix55d_finalize_optional_members(
    holo_base_msg_numerics_Matrix55d* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix55d_copy(holo_base_msg_numerics_Matrix55d*       dst,
                                                                const holo_base_msg_numerics_Matrix55d* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_Double holo_base_msg_numerics_Matrix66d[6][6];
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_numerics_Matrix66d_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_numerics_Matrix66d_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_numerics_Matrix66d_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix66d
#define TSeq holo_base_msg_numerics_Matrix66dSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix66d
#define TSeq holo_base_msg_numerics_Matrix66dSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_numerics_Matrix66d* holo_base_msg_numerics_Matrix66d_create();

NDDSUSERDllExport extern void holo_base_msg_numerics_Matrix66d_delete(holo_base_msg_numerics_Matrix66d* sample);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix66d_initialize(holo_base_msg_numerics_Matrix66d* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix66d_initialize_ex(holo_base_msg_numerics_Matrix66d* self,
                                                                         RTIBool allocatePointers,
                                                                         RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix66d_initialize_w_params(
    holo_base_msg_numerics_Matrix66d* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix66d_finalize(holo_base_msg_numerics_Matrix66d* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix66d_finalize_w_return(holo_base_msg_numerics_Matrix66d* self);

NDDSUSERDllExport void holo_base_msg_numerics_Matrix66d_finalize_ex(holo_base_msg_numerics_Matrix66d* self,
                                                                    RTIBool                           deletePointers);

NDDSUSERDllExport void holo_base_msg_numerics_Matrix66d_finalize_w_params(
    holo_base_msg_numerics_Matrix66d* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_numerics_Matrix66d_finalize_optional_members(
    holo_base_msg_numerics_Matrix66d* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix66d_copy(holo_base_msg_numerics_Matrix66d*       dst,
                                                                const holo_base_msg_numerics_Matrix66d* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_FloatSeq holo_base_msg_numerics_MatrixfData;
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_numerics_MatrixfData_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_numerics_MatrixfData_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_numerics_MatrixfData_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_MatrixfData
#define TSeq holo_base_msg_numerics_MatrixfDataSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_MatrixfData
#define TSeq holo_base_msg_numerics_MatrixfDataSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_numerics_MatrixfData* holo_base_msg_numerics_MatrixfData_create();

NDDSUSERDllExport extern void holo_base_msg_numerics_MatrixfData_delete(holo_base_msg_numerics_MatrixfData* sample);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_MatrixfData_initialize(holo_base_msg_numerics_MatrixfData* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_MatrixfData_initialize_ex(holo_base_msg_numerics_MatrixfData* self,
                                                                           RTIBool allocatePointers,
                                                                           RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_MatrixfData_initialize_w_params(
    holo_base_msg_numerics_MatrixfData* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_MatrixfData_finalize(holo_base_msg_numerics_MatrixfData* self);

NDDSUSERDllExport RTIBool
holo_base_msg_numerics_MatrixfData_finalize_w_return(holo_base_msg_numerics_MatrixfData* self);

NDDSUSERDllExport void holo_base_msg_numerics_MatrixfData_finalize_ex(holo_base_msg_numerics_MatrixfData* self,
                                                                      RTIBool deletePointers);

NDDSUSERDllExport void holo_base_msg_numerics_MatrixfData_finalize_w_params(
    holo_base_msg_numerics_MatrixfData* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_numerics_MatrixfData_finalize_optional_members(
    holo_base_msg_numerics_MatrixfData* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_MatrixfData_copy(holo_base_msg_numerics_MatrixfData*       dst,
                                                                  const holo_base_msg_numerics_MatrixfData* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

extern const char* holo_base_msg_numerics_MatrixfTYPENAME;
}

struct holo_base_msg_numerics_MatrixfSeq;
#ifndef NDDS_STANDALONE_TYPE
class holo_base_msg_numerics_MatrixfTypeSupport;
class holo_base_msg_numerics_MatrixfDataWriter;
class holo_base_msg_numerics_MatrixfDataReader;
#endif
class holo_base_msg_numerics_Matrixf
{
public:
    typedef struct holo_base_msg_numerics_MatrixfSeq Seq;
#ifndef NDDS_STANDALONE_TYPE
    typedef holo_base_msg_numerics_MatrixfTypeSupport TypeSupport;
    typedef holo_base_msg_numerics_MatrixfDataWriter  DataWriter;
    typedef holo_base_msg_numerics_MatrixfDataReader  DataReader;
#endif

    DDS_Long                           rows;
    DDS_Long                           cols;
    holo_base_msg_numerics_MatrixfData data;
};
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_numerics_Matrixf_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_numerics_Matrixf_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_numerics_Matrixf_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrixf
#define TSeq holo_base_msg_numerics_MatrixfSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrixf
#define TSeq holo_base_msg_numerics_MatrixfSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_numerics_Matrixf* holo_base_msg_numerics_Matrixf_create();

NDDSUSERDllExport extern void holo_base_msg_numerics_Matrixf_delete(holo_base_msg_numerics_Matrixf* sample);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrixf_initialize(holo_base_msg_numerics_Matrixf* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrixf_initialize_ex(holo_base_msg_numerics_Matrixf* self,
                                                                       RTIBool                         allocatePointers,
                                                                       RTIBool                         allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrixf_initialize_w_params(
    holo_base_msg_numerics_Matrixf* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrixf_finalize(holo_base_msg_numerics_Matrixf* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrixf_finalize_w_return(holo_base_msg_numerics_Matrixf* self);

NDDSUSERDllExport void holo_base_msg_numerics_Matrixf_finalize_ex(holo_base_msg_numerics_Matrixf* self,
                                                                  RTIBool                         deletePointers);

NDDSUSERDllExport void holo_base_msg_numerics_Matrixf_finalize_w_params(
    holo_base_msg_numerics_Matrixf* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_numerics_Matrixf_finalize_optional_members(holo_base_msg_numerics_Matrixf* self,
                                                                                RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrixf_copy(holo_base_msg_numerics_Matrixf*       dst,
                                                              const holo_base_msg_numerics_Matrixf* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_Float holo_base_msg_numerics_Matrix22f[2][2];
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_numerics_Matrix22f_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_numerics_Matrix22f_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_numerics_Matrix22f_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix22f
#define TSeq holo_base_msg_numerics_Matrix22fSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix22f
#define TSeq holo_base_msg_numerics_Matrix22fSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_numerics_Matrix22f* holo_base_msg_numerics_Matrix22f_create();

NDDSUSERDllExport extern void holo_base_msg_numerics_Matrix22f_delete(holo_base_msg_numerics_Matrix22f* sample);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix22f_initialize(holo_base_msg_numerics_Matrix22f* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix22f_initialize_ex(holo_base_msg_numerics_Matrix22f* self,
                                                                         RTIBool allocatePointers,
                                                                         RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix22f_initialize_w_params(
    holo_base_msg_numerics_Matrix22f* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix22f_finalize(holo_base_msg_numerics_Matrix22f* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix22f_finalize_w_return(holo_base_msg_numerics_Matrix22f* self);

NDDSUSERDllExport void holo_base_msg_numerics_Matrix22f_finalize_ex(holo_base_msg_numerics_Matrix22f* self,
                                                                    RTIBool                           deletePointers);

NDDSUSERDllExport void holo_base_msg_numerics_Matrix22f_finalize_w_params(
    holo_base_msg_numerics_Matrix22f* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_numerics_Matrix22f_finalize_optional_members(
    holo_base_msg_numerics_Matrix22f* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix22f_copy(holo_base_msg_numerics_Matrix22f*       dst,
                                                                const holo_base_msg_numerics_Matrix22f* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_Float holo_base_msg_numerics_Matrix33f[3][3];
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_numerics_Matrix33f_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_numerics_Matrix33f_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_numerics_Matrix33f_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix33f
#define TSeq holo_base_msg_numerics_Matrix33fSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix33f
#define TSeq holo_base_msg_numerics_Matrix33fSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_numerics_Matrix33f* holo_base_msg_numerics_Matrix33f_create();

NDDSUSERDllExport extern void holo_base_msg_numerics_Matrix33f_delete(holo_base_msg_numerics_Matrix33f* sample);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix33f_initialize(holo_base_msg_numerics_Matrix33f* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix33f_initialize_ex(holo_base_msg_numerics_Matrix33f* self,
                                                                         RTIBool allocatePointers,
                                                                         RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix33f_initialize_w_params(
    holo_base_msg_numerics_Matrix33f* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix33f_finalize(holo_base_msg_numerics_Matrix33f* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix33f_finalize_w_return(holo_base_msg_numerics_Matrix33f* self);

NDDSUSERDllExport void holo_base_msg_numerics_Matrix33f_finalize_ex(holo_base_msg_numerics_Matrix33f* self,
                                                                    RTIBool                           deletePointers);

NDDSUSERDllExport void holo_base_msg_numerics_Matrix33f_finalize_w_params(
    holo_base_msg_numerics_Matrix33f* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_numerics_Matrix33f_finalize_optional_members(
    holo_base_msg_numerics_Matrix33f* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix33f_copy(holo_base_msg_numerics_Matrix33f*       dst,
                                                                const holo_base_msg_numerics_Matrix33f* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_Float holo_base_msg_numerics_Matrix44f[4][4];
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_numerics_Matrix44f_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_numerics_Matrix44f_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_numerics_Matrix44f_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix44f
#define TSeq holo_base_msg_numerics_Matrix44fSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix44f
#define TSeq holo_base_msg_numerics_Matrix44fSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_numerics_Matrix44f* holo_base_msg_numerics_Matrix44f_create();

NDDSUSERDllExport extern void holo_base_msg_numerics_Matrix44f_delete(holo_base_msg_numerics_Matrix44f* sample);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix44f_initialize(holo_base_msg_numerics_Matrix44f* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix44f_initialize_ex(holo_base_msg_numerics_Matrix44f* self,
                                                                         RTIBool allocatePointers,
                                                                         RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix44f_initialize_w_params(
    holo_base_msg_numerics_Matrix44f* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix44f_finalize(holo_base_msg_numerics_Matrix44f* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix44f_finalize_w_return(holo_base_msg_numerics_Matrix44f* self);

NDDSUSERDllExport void holo_base_msg_numerics_Matrix44f_finalize_ex(holo_base_msg_numerics_Matrix44f* self,
                                                                    RTIBool                           deletePointers);

NDDSUSERDllExport void holo_base_msg_numerics_Matrix44f_finalize_w_params(
    holo_base_msg_numerics_Matrix44f* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_numerics_Matrix44f_finalize_optional_members(
    holo_base_msg_numerics_Matrix44f* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix44f_copy(holo_base_msg_numerics_Matrix44f*       dst,
                                                                const holo_base_msg_numerics_Matrix44f* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_Float holo_base_msg_numerics_Matrix55f[5][5];
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_numerics_Matrix55f_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_numerics_Matrix55f_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_numerics_Matrix55f_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix55f
#define TSeq holo_base_msg_numerics_Matrix55fSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix55f
#define TSeq holo_base_msg_numerics_Matrix55fSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_numerics_Matrix55f* holo_base_msg_numerics_Matrix55f_create();

NDDSUSERDllExport extern void holo_base_msg_numerics_Matrix55f_delete(holo_base_msg_numerics_Matrix55f* sample);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix55f_initialize(holo_base_msg_numerics_Matrix55f* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix55f_initialize_ex(holo_base_msg_numerics_Matrix55f* self,
                                                                         RTIBool allocatePointers,
                                                                         RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix55f_initialize_w_params(
    holo_base_msg_numerics_Matrix55f* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix55f_finalize(holo_base_msg_numerics_Matrix55f* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix55f_finalize_w_return(holo_base_msg_numerics_Matrix55f* self);

NDDSUSERDllExport void holo_base_msg_numerics_Matrix55f_finalize_ex(holo_base_msg_numerics_Matrix55f* self,
                                                                    RTIBool                           deletePointers);

NDDSUSERDllExport void holo_base_msg_numerics_Matrix55f_finalize_w_params(
    holo_base_msg_numerics_Matrix55f* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_numerics_Matrix55f_finalize_optional_members(
    holo_base_msg_numerics_Matrix55f* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix55f_copy(holo_base_msg_numerics_Matrix55f*       dst,
                                                                const holo_base_msg_numerics_Matrix55f* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef DDS_Float holo_base_msg_numerics_Matrix66f[6][6];
#if (defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
 */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* holo_base_msg_numerics_Matrix66f_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin* holo_base_msg_numerics_Matrix66f_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo* holo_base_msg_numerics_Matrix66f_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix66f
#define TSeq holo_base_msg_numerics_Matrix66fSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T holo_base_msg_numerics_Matrix66f
#define TSeq holo_base_msg_numerics_Matrix66fSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern holo_base_msg_numerics_Matrix66f* holo_base_msg_numerics_Matrix66f_create();

NDDSUSERDllExport extern void holo_base_msg_numerics_Matrix66f_delete(holo_base_msg_numerics_Matrix66f* sample);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix66f_initialize(holo_base_msg_numerics_Matrix66f* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix66f_initialize_ex(holo_base_msg_numerics_Matrix66f* self,
                                                                         RTIBool allocatePointers,
                                                                         RTIBool allocateMemory);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix66f_initialize_w_params(
    holo_base_msg_numerics_Matrix66f* self, const struct DDS_TypeAllocationParams_t* allocParams);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix66f_finalize(holo_base_msg_numerics_Matrix66f* self);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix66f_finalize_w_return(holo_base_msg_numerics_Matrix66f* self);

NDDSUSERDllExport void holo_base_msg_numerics_Matrix66f_finalize_ex(holo_base_msg_numerics_Matrix66f* self,
                                                                    RTIBool                           deletePointers);

NDDSUSERDllExport void holo_base_msg_numerics_Matrix66f_finalize_w_params(
    holo_base_msg_numerics_Matrix66f* self, const struct DDS_TypeDeallocationParams_t* deallocParams);

NDDSUSERDllExport void holo_base_msg_numerics_Matrix66f_finalize_optional_members(
    holo_base_msg_numerics_Matrix66f* self, RTIBool deletePointers);

NDDSUSERDllExport RTIBool holo_base_msg_numerics_Matrix66f_copy(holo_base_msg_numerics_Matrix66f*       dst,
                                                                const holo_base_msg_numerics_Matrix66f* src);

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

#endif /* Matrix */
