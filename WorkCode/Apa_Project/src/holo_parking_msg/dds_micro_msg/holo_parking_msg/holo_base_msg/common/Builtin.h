/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Builtin.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef Builtin_1564184277_h
#define Builtin_1564184277_h

#ifndef rti_me_cpp_hxx
#include "rti_me_cpp.hxx"
#endif

#include "dds_c/dds_c_typecode.h"

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

extern "C" {

    extern const char *opendds_wrapper_BuiltinTimestampTYPENAME;

}

struct opendds_wrapper_BuiltinTimestampSeq;
#ifndef NDDS_STANDALONE_TYPE
class opendds_wrapper_BuiltinTimestampTypeSupport;
class opendds_wrapper_BuiltinTimestampDataWriter;
class opendds_wrapper_BuiltinTimestampDataReader;
#endif
class opendds_wrapper_BuiltinTimestamp 
{
  public:
    typedef struct opendds_wrapper_BuiltinTimestampSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef opendds_wrapper_BuiltinTimestampTypeSupport TypeSupport;
    typedef opendds_wrapper_BuiltinTimestampDataWriter DataWriter;
    typedef opendds_wrapper_BuiltinTimestampDataReader DataReader;
    #endif

    DDS_UnsignedLong   sec ;
    DDS_UnsignedLong   nsec ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* opendds_wrapper_BuiltinTimestamp_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *opendds_wrapper_BuiltinTimestamp_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *opendds_wrapper_BuiltinTimestamp_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinTimestamp
#define TSeq opendds_wrapper_BuiltinTimestampSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinTimestamp
#define TSeq opendds_wrapper_BuiltinTimestampSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern opendds_wrapper_BuiltinTimestamp*
opendds_wrapper_BuiltinTimestamp_create();

NDDSUSERDllExport extern void
opendds_wrapper_BuiltinTimestamp_delete(opendds_wrapper_BuiltinTimestamp* sample);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinTimestamp_initialize(
    opendds_wrapper_BuiltinTimestamp* self);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinTimestamp_initialize_ex(
    opendds_wrapper_BuiltinTimestamp* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinTimestamp_initialize_w_params(
    opendds_wrapper_BuiltinTimestamp* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinTimestamp_finalize(
    opendds_wrapper_BuiltinTimestamp* self);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinTimestamp_finalize_w_return(
    opendds_wrapper_BuiltinTimestamp* self);

NDDSUSERDllExport
void opendds_wrapper_BuiltinTimestamp_finalize_ex(
    opendds_wrapper_BuiltinTimestamp* self,RTIBool deletePointers);

NDDSUSERDllExport
void opendds_wrapper_BuiltinTimestamp_finalize_w_params(
    opendds_wrapper_BuiltinTimestamp* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void opendds_wrapper_BuiltinTimestamp_finalize_optional_members(
    opendds_wrapper_BuiltinTimestamp* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinTimestamp_copy(
    opendds_wrapper_BuiltinTimestamp* dst,
    const opendds_wrapper_BuiltinTimestamp* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

    extern const char *opendds_wrapper_BuiltinUint8TYPENAME;

}

struct opendds_wrapper_BuiltinUint8Seq;
#ifndef NDDS_STANDALONE_TYPE
class opendds_wrapper_BuiltinUint8TypeSupport;
class opendds_wrapper_BuiltinUint8DataWriter;
class opendds_wrapper_BuiltinUint8DataReader;
#endif
class opendds_wrapper_BuiltinUint8 
{
  public:
    typedef struct opendds_wrapper_BuiltinUint8Seq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef opendds_wrapper_BuiltinUint8TypeSupport TypeSupport;
    typedef opendds_wrapper_BuiltinUint8DataWriter DataWriter;
    typedef opendds_wrapper_BuiltinUint8DataReader DataReader;
    #endif

    DDS_Octet   value ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* opendds_wrapper_BuiltinUint8_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *opendds_wrapper_BuiltinUint8_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *opendds_wrapper_BuiltinUint8_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinUint8
#define TSeq opendds_wrapper_BuiltinUint8Seq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinUint8
#define TSeq opendds_wrapper_BuiltinUint8Seq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern opendds_wrapper_BuiltinUint8*
opendds_wrapper_BuiltinUint8_create();

NDDSUSERDllExport extern void
opendds_wrapper_BuiltinUint8_delete(opendds_wrapper_BuiltinUint8* sample);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinUint8_initialize(
    opendds_wrapper_BuiltinUint8* self);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinUint8_initialize_ex(
    opendds_wrapper_BuiltinUint8* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinUint8_initialize_w_params(
    opendds_wrapper_BuiltinUint8* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinUint8_finalize(
    opendds_wrapper_BuiltinUint8* self);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinUint8_finalize_w_return(
    opendds_wrapper_BuiltinUint8* self);

NDDSUSERDllExport
void opendds_wrapper_BuiltinUint8_finalize_ex(
    opendds_wrapper_BuiltinUint8* self,RTIBool deletePointers);

NDDSUSERDllExport
void opendds_wrapper_BuiltinUint8_finalize_w_params(
    opendds_wrapper_BuiltinUint8* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void opendds_wrapper_BuiltinUint8_finalize_optional_members(
    opendds_wrapper_BuiltinUint8* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinUint8_copy(
    opendds_wrapper_BuiltinUint8* dst,
    const opendds_wrapper_BuiltinUint8* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

    extern const char *opendds_wrapper_BuiltinUint16TYPENAME;

}

struct opendds_wrapper_BuiltinUint16Seq;
#ifndef NDDS_STANDALONE_TYPE
class opendds_wrapper_BuiltinUint16TypeSupport;
class opendds_wrapper_BuiltinUint16DataWriter;
class opendds_wrapper_BuiltinUint16DataReader;
#endif
class opendds_wrapper_BuiltinUint16 
{
  public:
    typedef struct opendds_wrapper_BuiltinUint16Seq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef opendds_wrapper_BuiltinUint16TypeSupport TypeSupport;
    typedef opendds_wrapper_BuiltinUint16DataWriter DataWriter;
    typedef opendds_wrapper_BuiltinUint16DataReader DataReader;
    #endif

    DDS_UnsignedShort   value ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* opendds_wrapper_BuiltinUint16_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *opendds_wrapper_BuiltinUint16_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *opendds_wrapper_BuiltinUint16_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinUint16
#define TSeq opendds_wrapper_BuiltinUint16Seq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinUint16
#define TSeq opendds_wrapper_BuiltinUint16Seq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern opendds_wrapper_BuiltinUint16*
opendds_wrapper_BuiltinUint16_create();

NDDSUSERDllExport extern void
opendds_wrapper_BuiltinUint16_delete(opendds_wrapper_BuiltinUint16* sample);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinUint16_initialize(
    opendds_wrapper_BuiltinUint16* self);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinUint16_initialize_ex(
    opendds_wrapper_BuiltinUint16* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinUint16_initialize_w_params(
    opendds_wrapper_BuiltinUint16* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinUint16_finalize(
    opendds_wrapper_BuiltinUint16* self);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinUint16_finalize_w_return(
    opendds_wrapper_BuiltinUint16* self);

NDDSUSERDllExport
void opendds_wrapper_BuiltinUint16_finalize_ex(
    opendds_wrapper_BuiltinUint16* self,RTIBool deletePointers);

NDDSUSERDllExport
void opendds_wrapper_BuiltinUint16_finalize_w_params(
    opendds_wrapper_BuiltinUint16* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void opendds_wrapper_BuiltinUint16_finalize_optional_members(
    opendds_wrapper_BuiltinUint16* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinUint16_copy(
    opendds_wrapper_BuiltinUint16* dst,
    const opendds_wrapper_BuiltinUint16* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

    extern const char *opendds_wrapper_BuiltinUint32TYPENAME;

}

struct opendds_wrapper_BuiltinUint32Seq;
#ifndef NDDS_STANDALONE_TYPE
class opendds_wrapper_BuiltinUint32TypeSupport;
class opendds_wrapper_BuiltinUint32DataWriter;
class opendds_wrapper_BuiltinUint32DataReader;
#endif
class opendds_wrapper_BuiltinUint32 
{
  public:
    typedef struct opendds_wrapper_BuiltinUint32Seq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef opendds_wrapper_BuiltinUint32TypeSupport TypeSupport;
    typedef opendds_wrapper_BuiltinUint32DataWriter DataWriter;
    typedef opendds_wrapper_BuiltinUint32DataReader DataReader;
    #endif

    DDS_UnsignedLong   value ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* opendds_wrapper_BuiltinUint32_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *opendds_wrapper_BuiltinUint32_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *opendds_wrapper_BuiltinUint32_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinUint32
#define TSeq opendds_wrapper_BuiltinUint32Seq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinUint32
#define TSeq opendds_wrapper_BuiltinUint32Seq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern opendds_wrapper_BuiltinUint32*
opendds_wrapper_BuiltinUint32_create();

NDDSUSERDllExport extern void
opendds_wrapper_BuiltinUint32_delete(opendds_wrapper_BuiltinUint32* sample);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinUint32_initialize(
    opendds_wrapper_BuiltinUint32* self);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinUint32_initialize_ex(
    opendds_wrapper_BuiltinUint32* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinUint32_initialize_w_params(
    opendds_wrapper_BuiltinUint32* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinUint32_finalize(
    opendds_wrapper_BuiltinUint32* self);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinUint32_finalize_w_return(
    opendds_wrapper_BuiltinUint32* self);

NDDSUSERDllExport
void opendds_wrapper_BuiltinUint32_finalize_ex(
    opendds_wrapper_BuiltinUint32* self,RTIBool deletePointers);

NDDSUSERDllExport
void opendds_wrapper_BuiltinUint32_finalize_w_params(
    opendds_wrapper_BuiltinUint32* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void opendds_wrapper_BuiltinUint32_finalize_optional_members(
    opendds_wrapper_BuiltinUint32* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinUint32_copy(
    opendds_wrapper_BuiltinUint32* dst,
    const opendds_wrapper_BuiltinUint32* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

    extern const char *opendds_wrapper_BuiltinUint64TYPENAME;

}

struct opendds_wrapper_BuiltinUint64Seq;
#ifndef NDDS_STANDALONE_TYPE
class opendds_wrapper_BuiltinUint64TypeSupport;
class opendds_wrapper_BuiltinUint64DataWriter;
class opendds_wrapper_BuiltinUint64DataReader;
#endif
class opendds_wrapper_BuiltinUint64 
{
  public:
    typedef struct opendds_wrapper_BuiltinUint64Seq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef opendds_wrapper_BuiltinUint64TypeSupport TypeSupport;
    typedef opendds_wrapper_BuiltinUint64DataWriter DataWriter;
    typedef opendds_wrapper_BuiltinUint64DataReader DataReader;
    #endif

    DDS_UnsignedLongLong   value ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* opendds_wrapper_BuiltinUint64_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *opendds_wrapper_BuiltinUint64_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *opendds_wrapper_BuiltinUint64_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinUint64
#define TSeq opendds_wrapper_BuiltinUint64Seq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinUint64
#define TSeq opendds_wrapper_BuiltinUint64Seq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern opendds_wrapper_BuiltinUint64*
opendds_wrapper_BuiltinUint64_create();

NDDSUSERDllExport extern void
opendds_wrapper_BuiltinUint64_delete(opendds_wrapper_BuiltinUint64* sample);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinUint64_initialize(
    opendds_wrapper_BuiltinUint64* self);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinUint64_initialize_ex(
    opendds_wrapper_BuiltinUint64* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinUint64_initialize_w_params(
    opendds_wrapper_BuiltinUint64* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinUint64_finalize(
    opendds_wrapper_BuiltinUint64* self);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinUint64_finalize_w_return(
    opendds_wrapper_BuiltinUint64* self);

NDDSUSERDllExport
void opendds_wrapper_BuiltinUint64_finalize_ex(
    opendds_wrapper_BuiltinUint64* self,RTIBool deletePointers);

NDDSUSERDllExport
void opendds_wrapper_BuiltinUint64_finalize_w_params(
    opendds_wrapper_BuiltinUint64* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void opendds_wrapper_BuiltinUint64_finalize_optional_members(
    opendds_wrapper_BuiltinUint64* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinUint64_copy(
    opendds_wrapper_BuiltinUint64* dst,
    const opendds_wrapper_BuiltinUint64* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

    extern const char *opendds_wrapper_BuiltinFloat32TYPENAME;

}

struct opendds_wrapper_BuiltinFloat32Seq;
#ifndef NDDS_STANDALONE_TYPE
class opendds_wrapper_BuiltinFloat32TypeSupport;
class opendds_wrapper_BuiltinFloat32DataWriter;
class opendds_wrapper_BuiltinFloat32DataReader;
#endif
class opendds_wrapper_BuiltinFloat32 
{
  public:
    typedef struct opendds_wrapper_BuiltinFloat32Seq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef opendds_wrapper_BuiltinFloat32TypeSupport TypeSupport;
    typedef opendds_wrapper_BuiltinFloat32DataWriter DataWriter;
    typedef opendds_wrapper_BuiltinFloat32DataReader DataReader;
    #endif

    DDS_Float   value ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* opendds_wrapper_BuiltinFloat32_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *opendds_wrapper_BuiltinFloat32_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *opendds_wrapper_BuiltinFloat32_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinFloat32
#define TSeq opendds_wrapper_BuiltinFloat32Seq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinFloat32
#define TSeq opendds_wrapper_BuiltinFloat32Seq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern opendds_wrapper_BuiltinFloat32*
opendds_wrapper_BuiltinFloat32_create();

NDDSUSERDllExport extern void
opendds_wrapper_BuiltinFloat32_delete(opendds_wrapper_BuiltinFloat32* sample);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinFloat32_initialize(
    opendds_wrapper_BuiltinFloat32* self);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinFloat32_initialize_ex(
    opendds_wrapper_BuiltinFloat32* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinFloat32_initialize_w_params(
    opendds_wrapper_BuiltinFloat32* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinFloat32_finalize(
    opendds_wrapper_BuiltinFloat32* self);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinFloat32_finalize_w_return(
    opendds_wrapper_BuiltinFloat32* self);

NDDSUSERDllExport
void opendds_wrapper_BuiltinFloat32_finalize_ex(
    opendds_wrapper_BuiltinFloat32* self,RTIBool deletePointers);

NDDSUSERDllExport
void opendds_wrapper_BuiltinFloat32_finalize_w_params(
    opendds_wrapper_BuiltinFloat32* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void opendds_wrapper_BuiltinFloat32_finalize_optional_members(
    opendds_wrapper_BuiltinFloat32* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinFloat32_copy(
    opendds_wrapper_BuiltinFloat32* dst,
    const opendds_wrapper_BuiltinFloat32* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

    extern const char *opendds_wrapper_BuiltinFloat64TYPENAME;

}

struct opendds_wrapper_BuiltinFloat64Seq;
#ifndef NDDS_STANDALONE_TYPE
class opendds_wrapper_BuiltinFloat64TypeSupport;
class opendds_wrapper_BuiltinFloat64DataWriter;
class opendds_wrapper_BuiltinFloat64DataReader;
#endif
class opendds_wrapper_BuiltinFloat64 
{
  public:
    typedef struct opendds_wrapper_BuiltinFloat64Seq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef opendds_wrapper_BuiltinFloat64TypeSupport TypeSupport;
    typedef opendds_wrapper_BuiltinFloat64DataWriter DataWriter;
    typedef opendds_wrapper_BuiltinFloat64DataReader DataReader;
    #endif

    DDS_Double   value ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* opendds_wrapper_BuiltinFloat64_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *opendds_wrapper_BuiltinFloat64_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *opendds_wrapper_BuiltinFloat64_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinFloat64
#define TSeq opendds_wrapper_BuiltinFloat64Seq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinFloat64
#define TSeq opendds_wrapper_BuiltinFloat64Seq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern opendds_wrapper_BuiltinFloat64*
opendds_wrapper_BuiltinFloat64_create();

NDDSUSERDllExport extern void
opendds_wrapper_BuiltinFloat64_delete(opendds_wrapper_BuiltinFloat64* sample);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinFloat64_initialize(
    opendds_wrapper_BuiltinFloat64* self);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinFloat64_initialize_ex(
    opendds_wrapper_BuiltinFloat64* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinFloat64_initialize_w_params(
    opendds_wrapper_BuiltinFloat64* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinFloat64_finalize(
    opendds_wrapper_BuiltinFloat64* self);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinFloat64_finalize_w_return(
    opendds_wrapper_BuiltinFloat64* self);

NDDSUSERDllExport
void opendds_wrapper_BuiltinFloat64_finalize_ex(
    opendds_wrapper_BuiltinFloat64* self,RTIBool deletePointers);

NDDSUSERDllExport
void opendds_wrapper_BuiltinFloat64_finalize_w_params(
    opendds_wrapper_BuiltinFloat64* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void opendds_wrapper_BuiltinFloat64_finalize_optional_members(
    opendds_wrapper_BuiltinFloat64* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinFloat64_copy(
    opendds_wrapper_BuiltinFloat64* dst,
    const opendds_wrapper_BuiltinFloat64* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

    extern const char *opendds_wrapper_BuiltinStringTYPENAME;

}

struct opendds_wrapper_BuiltinStringSeq;
#ifndef NDDS_STANDALONE_TYPE
class opendds_wrapper_BuiltinStringTypeSupport;
class opendds_wrapper_BuiltinStringDataWriter;
class opendds_wrapper_BuiltinStringDataReader;
#endif
class opendds_wrapper_BuiltinString 
{
  public:
    typedef struct opendds_wrapper_BuiltinStringSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef opendds_wrapper_BuiltinStringTypeSupport TypeSupport;
    typedef opendds_wrapper_BuiltinStringDataWriter DataWriter;
    typedef opendds_wrapper_BuiltinStringDataReader DataReader;
    #endif

    DDS_String   value ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* opendds_wrapper_BuiltinString_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *opendds_wrapper_BuiltinString_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *opendds_wrapper_BuiltinString_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinString
#define TSeq opendds_wrapper_BuiltinStringSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinString
#define TSeq opendds_wrapper_BuiltinStringSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern opendds_wrapper_BuiltinString*
opendds_wrapper_BuiltinString_create();

NDDSUSERDllExport extern void
opendds_wrapper_BuiltinString_delete(opendds_wrapper_BuiltinString* sample);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinString_initialize(
    opendds_wrapper_BuiltinString* self);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinString_initialize_ex(
    opendds_wrapper_BuiltinString* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinString_initialize_w_params(
    opendds_wrapper_BuiltinString* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinString_finalize(
    opendds_wrapper_BuiltinString* self);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinString_finalize_w_return(
    opendds_wrapper_BuiltinString* self);

NDDSUSERDllExport
void opendds_wrapper_BuiltinString_finalize_ex(
    opendds_wrapper_BuiltinString* self,RTIBool deletePointers);

NDDSUSERDllExport
void opendds_wrapper_BuiltinString_finalize_w_params(
    opendds_wrapper_BuiltinString* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void opendds_wrapper_BuiltinString_finalize_optional_members(
    opendds_wrapper_BuiltinString* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinString_copy(
    opendds_wrapper_BuiltinString* dst,
    const opendds_wrapper_BuiltinString* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

typedef     DDS_OctetSeq  opendds_wrapper_OctetSequence ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* opendds_wrapper_OctetSequence_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *opendds_wrapper_OctetSequence_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *opendds_wrapper_OctetSequence_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_OctetSequence
#define TSeq opendds_wrapper_OctetSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_OctetSequence
#define TSeq opendds_wrapper_OctetSequenceSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern opendds_wrapper_OctetSequence*
opendds_wrapper_OctetSequence_create();

NDDSUSERDllExport extern void
opendds_wrapper_OctetSequence_delete(opendds_wrapper_OctetSequence* sample);

NDDSUSERDllExport
RTIBool opendds_wrapper_OctetSequence_initialize(
    opendds_wrapper_OctetSequence* self);

NDDSUSERDllExport
RTIBool opendds_wrapper_OctetSequence_initialize_ex(
    opendds_wrapper_OctetSequence* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool opendds_wrapper_OctetSequence_initialize_w_params(
    opendds_wrapper_OctetSequence* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool opendds_wrapper_OctetSequence_finalize(
    opendds_wrapper_OctetSequence* self);

NDDSUSERDllExport
RTIBool opendds_wrapper_OctetSequence_finalize_w_return(
    opendds_wrapper_OctetSequence* self);

NDDSUSERDllExport
void opendds_wrapper_OctetSequence_finalize_ex(
    opendds_wrapper_OctetSequence* self,RTIBool deletePointers);

NDDSUSERDllExport
void opendds_wrapper_OctetSequence_finalize_w_params(
    opendds_wrapper_OctetSequence* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void opendds_wrapper_OctetSequence_finalize_optional_members(
    opendds_wrapper_OctetSequence* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool opendds_wrapper_OctetSequence_copy(
    opendds_wrapper_OctetSequence* dst,
    const opendds_wrapper_OctetSequence* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern "C" {

    extern const char *opendds_wrapper_BuiltinBufferTYPENAME;

}

struct opendds_wrapper_BuiltinBufferSeq;
#ifndef NDDS_STANDALONE_TYPE
class opendds_wrapper_BuiltinBufferTypeSupport;
class opendds_wrapper_BuiltinBufferDataWriter;
class opendds_wrapper_BuiltinBufferDataReader;
#endif
class opendds_wrapper_BuiltinBuffer 
{
  public:
    typedef struct opendds_wrapper_BuiltinBufferSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef opendds_wrapper_BuiltinBufferTypeSupport TypeSupport;
    typedef opendds_wrapper_BuiltinBufferDataWriter DataWriter;
    typedef opendds_wrapper_BuiltinBufferDataReader DataReader;
    #endif

    opendds_wrapper_OctetSequence   value ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* opendds_wrapper_BuiltinBuffer_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *opendds_wrapper_BuiltinBuffer_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *opendds_wrapper_BuiltinBuffer_get_sample_access_info(void);
#endif

#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinBuffer
#define TSeq opendds_wrapper_BuiltinBufferSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>
#define REDA_SEQUENCE_USER_API
#define T opendds_wrapper_BuiltinBuffer
#define TSeq opendds_wrapper_BuiltinBufferSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#define REDA_SEQUENCE_USER_CPP
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern opendds_wrapper_BuiltinBuffer*
opendds_wrapper_BuiltinBuffer_create();

NDDSUSERDllExport extern void
opendds_wrapper_BuiltinBuffer_delete(opendds_wrapper_BuiltinBuffer* sample);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinBuffer_initialize(
    opendds_wrapper_BuiltinBuffer* self);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinBuffer_initialize_ex(
    opendds_wrapper_BuiltinBuffer* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinBuffer_initialize_w_params(
    opendds_wrapper_BuiltinBuffer* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinBuffer_finalize(
    opendds_wrapper_BuiltinBuffer* self);

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinBuffer_finalize_w_return(
    opendds_wrapper_BuiltinBuffer* self);

NDDSUSERDllExport
void opendds_wrapper_BuiltinBuffer_finalize_ex(
    opendds_wrapper_BuiltinBuffer* self,RTIBool deletePointers);

NDDSUSERDllExport
void opendds_wrapper_BuiltinBuffer_finalize_w_params(
    opendds_wrapper_BuiltinBuffer* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void opendds_wrapper_BuiltinBuffer_finalize_optional_members(
    opendds_wrapper_BuiltinBuffer* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool opendds_wrapper_BuiltinBuffer_copy(
    opendds_wrapper_BuiltinBuffer* dst,
    const opendds_wrapper_BuiltinBuffer* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
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

#endif /* Builtin */

