/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Builtin.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "BuiltinSupport.h"

/*** SOURCE_BEGIN ***/

/* =========================================================================== */

/* Requires */
#define TTYPENAME   opendds_wrapper_BuiltinTimestampTYPENAME

/* 
opendds_wrapper_BuiltinTimestampDataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter opendds_wrapper_BuiltinTimestampDataWriter
#define TData       opendds_wrapper_BuiltinTimestamp

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
opendds_wrapper_BuiltinTimestampDataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader opendds_wrapper_BuiltinTimestampDataReader
#define TDataSeq    opendds_wrapper_BuiltinTimestampSeq
#define TData       opendds_wrapper_BuiltinTimestamp
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
opendds_wrapper_BuiltinTimestampTypeSupport

*/

#define TTypeSupport opendds_wrapper_BuiltinTimestampTypeSupport
#define TData        opendds_wrapper_BuiltinTimestamp

static struct DDS_TypeProgramNode opendds_wrapper_BuiltinTimestamp_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t opendds_wrapper_BuiltinTimestamp_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t opendds_wrapper_BuiltinTimestamp_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t opendds_wrapper_BuiltinTimestamp_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
opendds_wrapper_BuiltinTimestampTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const opendds_wrapper_BuiltinTimestamp *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &opendds_wrapper_BuiltinTimestamp_gv_ProgramNode,
        opendds_wrapper_BuiltinTimestamp_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,opendds_wrapper_BuiltinTimestampTypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        opendds_wrapper_BuiltinTimestamp_gv_AutoRepresentation,
        opendds_wrapper_BuiltinTimestamp_gv_XCDR1,
        opendds_wrapper_BuiltinTimestamp_gv_XCDR2,
        &encapsulation))
    {
        return DDS_RETCODE_ERROR;
    }

    return XCDR_Interpreter_serialized_sample_to_buffer(&tp,
    buffer,
    length,
    (const void *)a_data,
    representation,
    encapsulation);
}

DDS_ReturnCode_t 
opendds_wrapper_BuiltinTimestampTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const opendds_wrapper_BuiltinTimestamp *a_data)
{
    return opendds_wrapper_BuiltinTimestampTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
opendds_wrapper_BuiltinTimestampTypeSupport_deserialize_data_from_cdr_buffer(
    opendds_wrapper_BuiltinTimestamp *a_data,
    const char *buffer,
    unsigned int length)
{
    struct CDR_Stream_t stream;
    struct DDS_TypePlugin tp;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    if (!CDR_Stream_initialize_w_buffer(&stream,buffer,length))
    {
        return DDS_RETCODE_ERROR;
    }

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &opendds_wrapper_BuiltinTimestamp_gv_ProgramNode,
        opendds_wrapper_BuiltinTimestamp_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    opendds_wrapper_BuiltinTimestampTypePlugin_get(),
    programs);

    if (!XCDR_Interpreter_deserialize(&tp,a_data,&stream,RTI_TRUE,RTI_TRUE,0))
    {
        return DDS_RETCODE_ERROR;
    }

    return DDS_RETCODE_OK;
}

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_ttypesupport_gen.hxx"
#endif

#undef TTypeSupport
#undef TData

#undef TTYPENAME

/* =========================================================================== */

/* Requires */
#define TTYPENAME   opendds_wrapper_BuiltinUint8TYPENAME

/* 
opendds_wrapper_BuiltinUint8DataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter opendds_wrapper_BuiltinUint8DataWriter
#define TData       opendds_wrapper_BuiltinUint8

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
opendds_wrapper_BuiltinUint8DataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader opendds_wrapper_BuiltinUint8DataReader
#define TDataSeq    opendds_wrapper_BuiltinUint8Seq
#define TData       opendds_wrapper_BuiltinUint8
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
opendds_wrapper_BuiltinUint8TypeSupport

*/

#define TTypeSupport opendds_wrapper_BuiltinUint8TypeSupport
#define TData        opendds_wrapper_BuiltinUint8

static struct DDS_TypeProgramNode opendds_wrapper_BuiltinUint8_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t opendds_wrapper_BuiltinUint8_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t opendds_wrapper_BuiltinUint8_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t opendds_wrapper_BuiltinUint8_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
opendds_wrapper_BuiltinUint8TypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const opendds_wrapper_BuiltinUint8 *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &opendds_wrapper_BuiltinUint8_gv_ProgramNode,
        opendds_wrapper_BuiltinUint8_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,opendds_wrapper_BuiltinUint8TypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        opendds_wrapper_BuiltinUint8_gv_AutoRepresentation,
        opendds_wrapper_BuiltinUint8_gv_XCDR1,
        opendds_wrapper_BuiltinUint8_gv_XCDR2,
        &encapsulation))
    {
        return DDS_RETCODE_ERROR;
    }

    return XCDR_Interpreter_serialized_sample_to_buffer(&tp,
    buffer,
    length,
    (const void *)a_data,
    representation,
    encapsulation);
}

DDS_ReturnCode_t 
opendds_wrapper_BuiltinUint8TypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const opendds_wrapper_BuiltinUint8 *a_data)
{
    return opendds_wrapper_BuiltinUint8TypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
opendds_wrapper_BuiltinUint8TypeSupport_deserialize_data_from_cdr_buffer(
    opendds_wrapper_BuiltinUint8 *a_data,
    const char *buffer,
    unsigned int length)
{
    struct CDR_Stream_t stream;
    struct DDS_TypePlugin tp;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    if (!CDR_Stream_initialize_w_buffer(&stream,buffer,length))
    {
        return DDS_RETCODE_ERROR;
    }

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &opendds_wrapper_BuiltinUint8_gv_ProgramNode,
        opendds_wrapper_BuiltinUint8_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    opendds_wrapper_BuiltinUint8TypePlugin_get(),
    programs);

    if (!XCDR_Interpreter_deserialize(&tp,a_data,&stream,RTI_TRUE,RTI_TRUE,0))
    {
        return DDS_RETCODE_ERROR;
    }

    return DDS_RETCODE_OK;
}

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_ttypesupport_gen.hxx"
#endif

#undef TTypeSupport
#undef TData

#undef TTYPENAME

/* =========================================================================== */

/* Requires */
#define TTYPENAME   opendds_wrapper_BuiltinUint16TYPENAME

/* 
opendds_wrapper_BuiltinUint16DataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter opendds_wrapper_BuiltinUint16DataWriter
#define TData       opendds_wrapper_BuiltinUint16

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
opendds_wrapper_BuiltinUint16DataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader opendds_wrapper_BuiltinUint16DataReader
#define TDataSeq    opendds_wrapper_BuiltinUint16Seq
#define TData       opendds_wrapper_BuiltinUint16
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
opendds_wrapper_BuiltinUint16TypeSupport

*/

#define TTypeSupport opendds_wrapper_BuiltinUint16TypeSupport
#define TData        opendds_wrapper_BuiltinUint16

static struct DDS_TypeProgramNode opendds_wrapper_BuiltinUint16_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t opendds_wrapper_BuiltinUint16_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t opendds_wrapper_BuiltinUint16_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t opendds_wrapper_BuiltinUint16_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
opendds_wrapper_BuiltinUint16TypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const opendds_wrapper_BuiltinUint16 *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &opendds_wrapper_BuiltinUint16_gv_ProgramNode,
        opendds_wrapper_BuiltinUint16_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,opendds_wrapper_BuiltinUint16TypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        opendds_wrapper_BuiltinUint16_gv_AutoRepresentation,
        opendds_wrapper_BuiltinUint16_gv_XCDR1,
        opendds_wrapper_BuiltinUint16_gv_XCDR2,
        &encapsulation))
    {
        return DDS_RETCODE_ERROR;
    }

    return XCDR_Interpreter_serialized_sample_to_buffer(&tp,
    buffer,
    length,
    (const void *)a_data,
    representation,
    encapsulation);
}

DDS_ReturnCode_t 
opendds_wrapper_BuiltinUint16TypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const opendds_wrapper_BuiltinUint16 *a_data)
{
    return opendds_wrapper_BuiltinUint16TypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
opendds_wrapper_BuiltinUint16TypeSupport_deserialize_data_from_cdr_buffer(
    opendds_wrapper_BuiltinUint16 *a_data,
    const char *buffer,
    unsigned int length)
{
    struct CDR_Stream_t stream;
    struct DDS_TypePlugin tp;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    if (!CDR_Stream_initialize_w_buffer(&stream,buffer,length))
    {
        return DDS_RETCODE_ERROR;
    }

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &opendds_wrapper_BuiltinUint16_gv_ProgramNode,
        opendds_wrapper_BuiltinUint16_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    opendds_wrapper_BuiltinUint16TypePlugin_get(),
    programs);

    if (!XCDR_Interpreter_deserialize(&tp,a_data,&stream,RTI_TRUE,RTI_TRUE,0))
    {
        return DDS_RETCODE_ERROR;
    }

    return DDS_RETCODE_OK;
}

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_ttypesupport_gen.hxx"
#endif

#undef TTypeSupport
#undef TData

#undef TTYPENAME

/* =========================================================================== */

/* Requires */
#define TTYPENAME   opendds_wrapper_BuiltinUint32TYPENAME

/* 
opendds_wrapper_BuiltinUint32DataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter opendds_wrapper_BuiltinUint32DataWriter
#define TData       opendds_wrapper_BuiltinUint32

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
opendds_wrapper_BuiltinUint32DataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader opendds_wrapper_BuiltinUint32DataReader
#define TDataSeq    opendds_wrapper_BuiltinUint32Seq
#define TData       opendds_wrapper_BuiltinUint32
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
opendds_wrapper_BuiltinUint32TypeSupport

*/

#define TTypeSupport opendds_wrapper_BuiltinUint32TypeSupport
#define TData        opendds_wrapper_BuiltinUint32

static struct DDS_TypeProgramNode opendds_wrapper_BuiltinUint32_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t opendds_wrapper_BuiltinUint32_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t opendds_wrapper_BuiltinUint32_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t opendds_wrapper_BuiltinUint32_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
opendds_wrapper_BuiltinUint32TypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const opendds_wrapper_BuiltinUint32 *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &opendds_wrapper_BuiltinUint32_gv_ProgramNode,
        opendds_wrapper_BuiltinUint32_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,opendds_wrapper_BuiltinUint32TypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        opendds_wrapper_BuiltinUint32_gv_AutoRepresentation,
        opendds_wrapper_BuiltinUint32_gv_XCDR1,
        opendds_wrapper_BuiltinUint32_gv_XCDR2,
        &encapsulation))
    {
        return DDS_RETCODE_ERROR;
    }

    return XCDR_Interpreter_serialized_sample_to_buffer(&tp,
    buffer,
    length,
    (const void *)a_data,
    representation,
    encapsulation);
}

DDS_ReturnCode_t 
opendds_wrapper_BuiltinUint32TypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const opendds_wrapper_BuiltinUint32 *a_data)
{
    return opendds_wrapper_BuiltinUint32TypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
opendds_wrapper_BuiltinUint32TypeSupport_deserialize_data_from_cdr_buffer(
    opendds_wrapper_BuiltinUint32 *a_data,
    const char *buffer,
    unsigned int length)
{
    struct CDR_Stream_t stream;
    struct DDS_TypePlugin tp;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    if (!CDR_Stream_initialize_w_buffer(&stream,buffer,length))
    {
        return DDS_RETCODE_ERROR;
    }

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &opendds_wrapper_BuiltinUint32_gv_ProgramNode,
        opendds_wrapper_BuiltinUint32_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    opendds_wrapper_BuiltinUint32TypePlugin_get(),
    programs);

    if (!XCDR_Interpreter_deserialize(&tp,a_data,&stream,RTI_TRUE,RTI_TRUE,0))
    {
        return DDS_RETCODE_ERROR;
    }

    return DDS_RETCODE_OK;
}

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_ttypesupport_gen.hxx"
#endif

#undef TTypeSupport
#undef TData

#undef TTYPENAME

/* =========================================================================== */

/* Requires */
#define TTYPENAME   opendds_wrapper_BuiltinUint64TYPENAME

/* 
opendds_wrapper_BuiltinUint64DataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter opendds_wrapper_BuiltinUint64DataWriter
#define TData       opendds_wrapper_BuiltinUint64

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
opendds_wrapper_BuiltinUint64DataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader opendds_wrapper_BuiltinUint64DataReader
#define TDataSeq    opendds_wrapper_BuiltinUint64Seq
#define TData       opendds_wrapper_BuiltinUint64
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
opendds_wrapper_BuiltinUint64TypeSupport

*/

#define TTypeSupport opendds_wrapper_BuiltinUint64TypeSupport
#define TData        opendds_wrapper_BuiltinUint64

static struct DDS_TypeProgramNode opendds_wrapper_BuiltinUint64_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t opendds_wrapper_BuiltinUint64_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t opendds_wrapper_BuiltinUint64_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t opendds_wrapper_BuiltinUint64_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
opendds_wrapper_BuiltinUint64TypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const opendds_wrapper_BuiltinUint64 *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &opendds_wrapper_BuiltinUint64_gv_ProgramNode,
        opendds_wrapper_BuiltinUint64_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,opendds_wrapper_BuiltinUint64TypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        opendds_wrapper_BuiltinUint64_gv_AutoRepresentation,
        opendds_wrapper_BuiltinUint64_gv_XCDR1,
        opendds_wrapper_BuiltinUint64_gv_XCDR2,
        &encapsulation))
    {
        return DDS_RETCODE_ERROR;
    }

    return XCDR_Interpreter_serialized_sample_to_buffer(&tp,
    buffer,
    length,
    (const void *)a_data,
    representation,
    encapsulation);
}

DDS_ReturnCode_t 
opendds_wrapper_BuiltinUint64TypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const opendds_wrapper_BuiltinUint64 *a_data)
{
    return opendds_wrapper_BuiltinUint64TypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
opendds_wrapper_BuiltinUint64TypeSupport_deserialize_data_from_cdr_buffer(
    opendds_wrapper_BuiltinUint64 *a_data,
    const char *buffer,
    unsigned int length)
{
    struct CDR_Stream_t stream;
    struct DDS_TypePlugin tp;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    if (!CDR_Stream_initialize_w_buffer(&stream,buffer,length))
    {
        return DDS_RETCODE_ERROR;
    }

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &opendds_wrapper_BuiltinUint64_gv_ProgramNode,
        opendds_wrapper_BuiltinUint64_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    opendds_wrapper_BuiltinUint64TypePlugin_get(),
    programs);

    if (!XCDR_Interpreter_deserialize(&tp,a_data,&stream,RTI_TRUE,RTI_TRUE,0))
    {
        return DDS_RETCODE_ERROR;
    }

    return DDS_RETCODE_OK;
}

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_ttypesupport_gen.hxx"
#endif

#undef TTypeSupport
#undef TData

#undef TTYPENAME

/* =========================================================================== */

/* Requires */
#define TTYPENAME   opendds_wrapper_BuiltinFloat32TYPENAME

/* 
opendds_wrapper_BuiltinFloat32DataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter opendds_wrapper_BuiltinFloat32DataWriter
#define TData       opendds_wrapper_BuiltinFloat32

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
opendds_wrapper_BuiltinFloat32DataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader opendds_wrapper_BuiltinFloat32DataReader
#define TDataSeq    opendds_wrapper_BuiltinFloat32Seq
#define TData       opendds_wrapper_BuiltinFloat32
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
opendds_wrapper_BuiltinFloat32TypeSupport

*/

#define TTypeSupport opendds_wrapper_BuiltinFloat32TypeSupport
#define TData        opendds_wrapper_BuiltinFloat32

static struct DDS_TypeProgramNode opendds_wrapper_BuiltinFloat32_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t opendds_wrapper_BuiltinFloat32_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t opendds_wrapper_BuiltinFloat32_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t opendds_wrapper_BuiltinFloat32_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
opendds_wrapper_BuiltinFloat32TypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const opendds_wrapper_BuiltinFloat32 *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &opendds_wrapper_BuiltinFloat32_gv_ProgramNode,
        opendds_wrapper_BuiltinFloat32_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,opendds_wrapper_BuiltinFloat32TypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        opendds_wrapper_BuiltinFloat32_gv_AutoRepresentation,
        opendds_wrapper_BuiltinFloat32_gv_XCDR1,
        opendds_wrapper_BuiltinFloat32_gv_XCDR2,
        &encapsulation))
    {
        return DDS_RETCODE_ERROR;
    }

    return XCDR_Interpreter_serialized_sample_to_buffer(&tp,
    buffer,
    length,
    (const void *)a_data,
    representation,
    encapsulation);
}

DDS_ReturnCode_t 
opendds_wrapper_BuiltinFloat32TypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const opendds_wrapper_BuiltinFloat32 *a_data)
{
    return opendds_wrapper_BuiltinFloat32TypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
opendds_wrapper_BuiltinFloat32TypeSupport_deserialize_data_from_cdr_buffer(
    opendds_wrapper_BuiltinFloat32 *a_data,
    const char *buffer,
    unsigned int length)
{
    struct CDR_Stream_t stream;
    struct DDS_TypePlugin tp;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    if (!CDR_Stream_initialize_w_buffer(&stream,buffer,length))
    {
        return DDS_RETCODE_ERROR;
    }

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &opendds_wrapper_BuiltinFloat32_gv_ProgramNode,
        opendds_wrapper_BuiltinFloat32_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    opendds_wrapper_BuiltinFloat32TypePlugin_get(),
    programs);

    if (!XCDR_Interpreter_deserialize(&tp,a_data,&stream,RTI_TRUE,RTI_TRUE,0))
    {
        return DDS_RETCODE_ERROR;
    }

    return DDS_RETCODE_OK;
}

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_ttypesupport_gen.hxx"
#endif

#undef TTypeSupport
#undef TData

#undef TTYPENAME

/* =========================================================================== */

/* Requires */
#define TTYPENAME   opendds_wrapper_BuiltinFloat64TYPENAME

/* 
opendds_wrapper_BuiltinFloat64DataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter opendds_wrapper_BuiltinFloat64DataWriter
#define TData       opendds_wrapper_BuiltinFloat64

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
opendds_wrapper_BuiltinFloat64DataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader opendds_wrapper_BuiltinFloat64DataReader
#define TDataSeq    opendds_wrapper_BuiltinFloat64Seq
#define TData       opendds_wrapper_BuiltinFloat64
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
opendds_wrapper_BuiltinFloat64TypeSupport

*/

#define TTypeSupport opendds_wrapper_BuiltinFloat64TypeSupport
#define TData        opendds_wrapper_BuiltinFloat64

static struct DDS_TypeProgramNode opendds_wrapper_BuiltinFloat64_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t opendds_wrapper_BuiltinFloat64_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t opendds_wrapper_BuiltinFloat64_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t opendds_wrapper_BuiltinFloat64_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
opendds_wrapper_BuiltinFloat64TypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const opendds_wrapper_BuiltinFloat64 *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &opendds_wrapper_BuiltinFloat64_gv_ProgramNode,
        opendds_wrapper_BuiltinFloat64_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,opendds_wrapper_BuiltinFloat64TypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        opendds_wrapper_BuiltinFloat64_gv_AutoRepresentation,
        opendds_wrapper_BuiltinFloat64_gv_XCDR1,
        opendds_wrapper_BuiltinFloat64_gv_XCDR2,
        &encapsulation))
    {
        return DDS_RETCODE_ERROR;
    }

    return XCDR_Interpreter_serialized_sample_to_buffer(&tp,
    buffer,
    length,
    (const void *)a_data,
    representation,
    encapsulation);
}

DDS_ReturnCode_t 
opendds_wrapper_BuiltinFloat64TypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const opendds_wrapper_BuiltinFloat64 *a_data)
{
    return opendds_wrapper_BuiltinFloat64TypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
opendds_wrapper_BuiltinFloat64TypeSupport_deserialize_data_from_cdr_buffer(
    opendds_wrapper_BuiltinFloat64 *a_data,
    const char *buffer,
    unsigned int length)
{
    struct CDR_Stream_t stream;
    struct DDS_TypePlugin tp;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    if (!CDR_Stream_initialize_w_buffer(&stream,buffer,length))
    {
        return DDS_RETCODE_ERROR;
    }

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &opendds_wrapper_BuiltinFloat64_gv_ProgramNode,
        opendds_wrapper_BuiltinFloat64_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    opendds_wrapper_BuiltinFloat64TypePlugin_get(),
    programs);

    if (!XCDR_Interpreter_deserialize(&tp,a_data,&stream,RTI_TRUE,RTI_TRUE,0))
    {
        return DDS_RETCODE_ERROR;
    }

    return DDS_RETCODE_OK;
}

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_ttypesupport_gen.hxx"
#endif

#undef TTypeSupport
#undef TData

#undef TTYPENAME

/* =========================================================================== */

/* Requires */
#define TTYPENAME   opendds_wrapper_BuiltinStringTYPENAME

/* 
opendds_wrapper_BuiltinStringDataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter opendds_wrapper_BuiltinStringDataWriter
#define TData       opendds_wrapper_BuiltinString

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
opendds_wrapper_BuiltinStringDataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader opendds_wrapper_BuiltinStringDataReader
#define TDataSeq    opendds_wrapper_BuiltinStringSeq
#define TData       opendds_wrapper_BuiltinString
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
opendds_wrapper_BuiltinStringTypeSupport

*/

#define TTypeSupport opendds_wrapper_BuiltinStringTypeSupport
#define TData        opendds_wrapper_BuiltinString

static struct DDS_TypeProgramNode opendds_wrapper_BuiltinString_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t opendds_wrapper_BuiltinString_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t opendds_wrapper_BuiltinString_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t opendds_wrapper_BuiltinString_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
opendds_wrapper_BuiltinStringTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const opendds_wrapper_BuiltinString *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &opendds_wrapper_BuiltinString_gv_ProgramNode,
        opendds_wrapper_BuiltinString_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,opendds_wrapper_BuiltinStringTypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        opendds_wrapper_BuiltinString_gv_AutoRepresentation,
        opendds_wrapper_BuiltinString_gv_XCDR1,
        opendds_wrapper_BuiltinString_gv_XCDR2,
        &encapsulation))
    {
        return DDS_RETCODE_ERROR;
    }

    return XCDR_Interpreter_serialized_sample_to_buffer(&tp,
    buffer,
    length,
    (const void *)a_data,
    representation,
    encapsulation);
}

DDS_ReturnCode_t 
opendds_wrapper_BuiltinStringTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const opendds_wrapper_BuiltinString *a_data)
{
    return opendds_wrapper_BuiltinStringTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
opendds_wrapper_BuiltinStringTypeSupport_deserialize_data_from_cdr_buffer(
    opendds_wrapper_BuiltinString *a_data,
    const char *buffer,
    unsigned int length)
{
    struct CDR_Stream_t stream;
    struct DDS_TypePlugin tp;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    if (!CDR_Stream_initialize_w_buffer(&stream,buffer,length))
    {
        return DDS_RETCODE_ERROR;
    }

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &opendds_wrapper_BuiltinString_gv_ProgramNode,
        opendds_wrapper_BuiltinString_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    opendds_wrapper_BuiltinStringTypePlugin_get(),
    programs);

    if (!XCDR_Interpreter_deserialize(&tp,a_data,&stream,RTI_TRUE,RTI_TRUE,0))
    {
        return DDS_RETCODE_ERROR;
    }

    return DDS_RETCODE_OK;
}

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_ttypesupport_gen.hxx"
#endif

#undef TTypeSupport
#undef TData

#undef TTYPENAME

/* =========================================================================== */

/* Requires */
#define TTYPENAME   opendds_wrapper_BuiltinBufferTYPENAME

/* 
opendds_wrapper_BuiltinBufferDataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter opendds_wrapper_BuiltinBufferDataWriter
#define TData       opendds_wrapper_BuiltinBuffer

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
opendds_wrapper_BuiltinBufferDataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader opendds_wrapper_BuiltinBufferDataReader
#define TDataSeq    opendds_wrapper_BuiltinBufferSeq
#define TData       opendds_wrapper_BuiltinBuffer
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
opendds_wrapper_BuiltinBufferTypeSupport

*/

#define TTypeSupport opendds_wrapper_BuiltinBufferTypeSupport
#define TData        opendds_wrapper_BuiltinBuffer

static struct DDS_TypeProgramNode opendds_wrapper_BuiltinBuffer_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t opendds_wrapper_BuiltinBuffer_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t opendds_wrapper_BuiltinBuffer_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t opendds_wrapper_BuiltinBuffer_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
opendds_wrapper_BuiltinBufferTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const opendds_wrapper_BuiltinBuffer *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &opendds_wrapper_BuiltinBuffer_gv_ProgramNode,
        opendds_wrapper_BuiltinBuffer_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,opendds_wrapper_BuiltinBufferTypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        opendds_wrapper_BuiltinBuffer_gv_AutoRepresentation,
        opendds_wrapper_BuiltinBuffer_gv_XCDR1,
        opendds_wrapper_BuiltinBuffer_gv_XCDR2,
        &encapsulation))
    {
        return DDS_RETCODE_ERROR;
    }

    return XCDR_Interpreter_serialized_sample_to_buffer(&tp,
    buffer,
    length,
    (const void *)a_data,
    representation,
    encapsulation);
}

DDS_ReturnCode_t 
opendds_wrapper_BuiltinBufferTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const opendds_wrapper_BuiltinBuffer *a_data)
{
    return opendds_wrapper_BuiltinBufferTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
opendds_wrapper_BuiltinBufferTypeSupport_deserialize_data_from_cdr_buffer(
    opendds_wrapper_BuiltinBuffer *a_data,
    const char *buffer,
    unsigned int length)
{
    struct CDR_Stream_t stream;
    struct DDS_TypePlugin tp;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    if (!CDR_Stream_initialize_w_buffer(&stream,buffer,length))
    {
        return DDS_RETCODE_ERROR;
    }

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &opendds_wrapper_BuiltinBuffer_gv_ProgramNode,
        opendds_wrapper_BuiltinBuffer_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    opendds_wrapper_BuiltinBufferTypePlugin_get(),
    programs);

    if (!XCDR_Interpreter_deserialize(&tp,a_data,&stream,RTI_TRUE,RTI_TRUE,0))
    {
        return DDS_RETCODE_ERROR;
    }

    return DDS_RETCODE_OK;
}

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_ttypesupport_gen.hxx"
#endif

#undef TTypeSupport
#undef TData

#undef TTYPENAME

