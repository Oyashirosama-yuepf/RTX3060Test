/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ImageObjects.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "ImageObjectsSupport.h"

/*** SOURCE_BEGIN ***/

/* =========================================================================== */

/* Requires */
#define TTYPENAME   holo_base_msg_vision_KeyPoint2dTYPENAME

/* 
holo_base_msg_vision_KeyPoint2dDataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter holo_base_msg_vision_KeyPoint2dDataWriter
#define TData       holo_base_msg_vision_KeyPoint2d

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_vision_KeyPoint2dDataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader holo_base_msg_vision_KeyPoint2dDataReader
#define TDataSeq    holo_base_msg_vision_KeyPoint2dSeq
#define TData       holo_base_msg_vision_KeyPoint2d
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_vision_KeyPoint2dTypeSupport

*/

#define TTypeSupport holo_base_msg_vision_KeyPoint2dTypeSupport
#define TData        holo_base_msg_vision_KeyPoint2d

static struct DDS_TypeProgramNode holo_base_msg_vision_KeyPoint2d_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t holo_base_msg_vision_KeyPoint2d_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_vision_KeyPoint2d_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_vision_KeyPoint2d_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
holo_base_msg_vision_KeyPoint2dTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const holo_base_msg_vision_KeyPoint2d *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &holo_base_msg_vision_KeyPoint2d_gv_ProgramNode,
        holo_base_msg_vision_KeyPoint2d_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,holo_base_msg_vision_KeyPoint2dTypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        holo_base_msg_vision_KeyPoint2d_gv_AutoRepresentation,
        holo_base_msg_vision_KeyPoint2d_gv_XCDR1,
        holo_base_msg_vision_KeyPoint2d_gv_XCDR2,
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
holo_base_msg_vision_KeyPoint2dTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const holo_base_msg_vision_KeyPoint2d *a_data)
{
    return holo_base_msg_vision_KeyPoint2dTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
holo_base_msg_vision_KeyPoint2dTypeSupport_deserialize_data_from_cdr_buffer(
    holo_base_msg_vision_KeyPoint2d *a_data,
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
        &holo_base_msg_vision_KeyPoint2d_gv_ProgramNode,
        holo_base_msg_vision_KeyPoint2d_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    holo_base_msg_vision_KeyPoint2dTypePlugin_get(),
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
#define TTYPENAME   holo_base_msg_vision_KeyPoint2fTYPENAME

/* 
holo_base_msg_vision_KeyPoint2fDataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter holo_base_msg_vision_KeyPoint2fDataWriter
#define TData       holo_base_msg_vision_KeyPoint2f

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_vision_KeyPoint2fDataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader holo_base_msg_vision_KeyPoint2fDataReader
#define TDataSeq    holo_base_msg_vision_KeyPoint2fSeq
#define TData       holo_base_msg_vision_KeyPoint2f
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_vision_KeyPoint2fTypeSupport

*/

#define TTypeSupport holo_base_msg_vision_KeyPoint2fTypeSupport
#define TData        holo_base_msg_vision_KeyPoint2f

static struct DDS_TypeProgramNode holo_base_msg_vision_KeyPoint2f_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t holo_base_msg_vision_KeyPoint2f_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_vision_KeyPoint2f_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_vision_KeyPoint2f_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
holo_base_msg_vision_KeyPoint2fTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const holo_base_msg_vision_KeyPoint2f *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &holo_base_msg_vision_KeyPoint2f_gv_ProgramNode,
        holo_base_msg_vision_KeyPoint2f_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,holo_base_msg_vision_KeyPoint2fTypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        holo_base_msg_vision_KeyPoint2f_gv_AutoRepresentation,
        holo_base_msg_vision_KeyPoint2f_gv_XCDR1,
        holo_base_msg_vision_KeyPoint2f_gv_XCDR2,
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
holo_base_msg_vision_KeyPoint2fTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const holo_base_msg_vision_KeyPoint2f *a_data)
{
    return holo_base_msg_vision_KeyPoint2fTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
holo_base_msg_vision_KeyPoint2fTypeSupport_deserialize_data_from_cdr_buffer(
    holo_base_msg_vision_KeyPoint2f *a_data,
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
        &holo_base_msg_vision_KeyPoint2f_gv_ProgramNode,
        holo_base_msg_vision_KeyPoint2f_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    holo_base_msg_vision_KeyPoint2fTypePlugin_get(),
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
#define TTYPENAME   holo_base_msg_vision_ObjectKeyPoint2dTYPENAME

/* 
holo_base_msg_vision_ObjectKeyPoint2dDataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter holo_base_msg_vision_ObjectKeyPoint2dDataWriter
#define TData       holo_base_msg_vision_ObjectKeyPoint2d

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_vision_ObjectKeyPoint2dDataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader holo_base_msg_vision_ObjectKeyPoint2dDataReader
#define TDataSeq    holo_base_msg_vision_ObjectKeyPoint2dSeq
#define TData       holo_base_msg_vision_ObjectKeyPoint2d
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_vision_ObjectKeyPoint2dTypeSupport

*/

#define TTypeSupport holo_base_msg_vision_ObjectKeyPoint2dTypeSupport
#define TData        holo_base_msg_vision_ObjectKeyPoint2d

static struct DDS_TypeProgramNode holo_base_msg_vision_ObjectKeyPoint2d_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t holo_base_msg_vision_ObjectKeyPoint2d_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_vision_ObjectKeyPoint2d_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_vision_ObjectKeyPoint2d_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
holo_base_msg_vision_ObjectKeyPoint2dTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const holo_base_msg_vision_ObjectKeyPoint2d *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &holo_base_msg_vision_ObjectKeyPoint2d_gv_ProgramNode,
        holo_base_msg_vision_ObjectKeyPoint2d_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,holo_base_msg_vision_ObjectKeyPoint2dTypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        holo_base_msg_vision_ObjectKeyPoint2d_gv_AutoRepresentation,
        holo_base_msg_vision_ObjectKeyPoint2d_gv_XCDR1,
        holo_base_msg_vision_ObjectKeyPoint2d_gv_XCDR2,
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
holo_base_msg_vision_ObjectKeyPoint2dTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const holo_base_msg_vision_ObjectKeyPoint2d *a_data)
{
    return holo_base_msg_vision_ObjectKeyPoint2dTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
holo_base_msg_vision_ObjectKeyPoint2dTypeSupport_deserialize_data_from_cdr_buffer(
    holo_base_msg_vision_ObjectKeyPoint2d *a_data,
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
        &holo_base_msg_vision_ObjectKeyPoint2d_gv_ProgramNode,
        holo_base_msg_vision_ObjectKeyPoint2d_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    holo_base_msg_vision_ObjectKeyPoint2dTypePlugin_get(),
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
#define TTYPENAME   holo_base_msg_vision_ObjectKeyPoint2fTYPENAME

/* 
holo_base_msg_vision_ObjectKeyPoint2fDataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter holo_base_msg_vision_ObjectKeyPoint2fDataWriter
#define TData       holo_base_msg_vision_ObjectKeyPoint2f

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_vision_ObjectKeyPoint2fDataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader holo_base_msg_vision_ObjectKeyPoint2fDataReader
#define TDataSeq    holo_base_msg_vision_ObjectKeyPoint2fSeq
#define TData       holo_base_msg_vision_ObjectKeyPoint2f
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_vision_ObjectKeyPoint2fTypeSupport

*/

#define TTypeSupport holo_base_msg_vision_ObjectKeyPoint2fTypeSupport
#define TData        holo_base_msg_vision_ObjectKeyPoint2f

static struct DDS_TypeProgramNode holo_base_msg_vision_ObjectKeyPoint2f_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t holo_base_msg_vision_ObjectKeyPoint2f_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_vision_ObjectKeyPoint2f_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_vision_ObjectKeyPoint2f_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
holo_base_msg_vision_ObjectKeyPoint2fTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const holo_base_msg_vision_ObjectKeyPoint2f *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &holo_base_msg_vision_ObjectKeyPoint2f_gv_ProgramNode,
        holo_base_msg_vision_ObjectKeyPoint2f_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,holo_base_msg_vision_ObjectKeyPoint2fTypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        holo_base_msg_vision_ObjectKeyPoint2f_gv_AutoRepresentation,
        holo_base_msg_vision_ObjectKeyPoint2f_gv_XCDR1,
        holo_base_msg_vision_ObjectKeyPoint2f_gv_XCDR2,
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
holo_base_msg_vision_ObjectKeyPoint2fTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const holo_base_msg_vision_ObjectKeyPoint2f *a_data)
{
    return holo_base_msg_vision_ObjectKeyPoint2fTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
holo_base_msg_vision_ObjectKeyPoint2fTypeSupport_deserialize_data_from_cdr_buffer(
    holo_base_msg_vision_ObjectKeyPoint2f *a_data,
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
        &holo_base_msg_vision_ObjectKeyPoint2f_gv_ProgramNode,
        holo_base_msg_vision_ObjectKeyPoint2f_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    holo_base_msg_vision_ObjectKeyPoint2fTypePlugin_get(),
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
#define TTYPENAME   holo_base_msg_vision_ObjectPoint2dTYPENAME

/* 
holo_base_msg_vision_ObjectPoint2dDataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter holo_base_msg_vision_ObjectPoint2dDataWriter
#define TData       holo_base_msg_vision_ObjectPoint2d

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_vision_ObjectPoint2dDataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader holo_base_msg_vision_ObjectPoint2dDataReader
#define TDataSeq    holo_base_msg_vision_ObjectPoint2dSeq
#define TData       holo_base_msg_vision_ObjectPoint2d
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_vision_ObjectPoint2dTypeSupport

*/

#define TTypeSupport holo_base_msg_vision_ObjectPoint2dTypeSupport
#define TData        holo_base_msg_vision_ObjectPoint2d

static struct DDS_TypeProgramNode holo_base_msg_vision_ObjectPoint2d_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t holo_base_msg_vision_ObjectPoint2d_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_vision_ObjectPoint2d_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_vision_ObjectPoint2d_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
holo_base_msg_vision_ObjectPoint2dTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const holo_base_msg_vision_ObjectPoint2d *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &holo_base_msg_vision_ObjectPoint2d_gv_ProgramNode,
        holo_base_msg_vision_ObjectPoint2d_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,holo_base_msg_vision_ObjectPoint2dTypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        holo_base_msg_vision_ObjectPoint2d_gv_AutoRepresentation,
        holo_base_msg_vision_ObjectPoint2d_gv_XCDR1,
        holo_base_msg_vision_ObjectPoint2d_gv_XCDR2,
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
holo_base_msg_vision_ObjectPoint2dTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const holo_base_msg_vision_ObjectPoint2d *a_data)
{
    return holo_base_msg_vision_ObjectPoint2dTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
holo_base_msg_vision_ObjectPoint2dTypeSupport_deserialize_data_from_cdr_buffer(
    holo_base_msg_vision_ObjectPoint2d *a_data,
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
        &holo_base_msg_vision_ObjectPoint2d_gv_ProgramNode,
        holo_base_msg_vision_ObjectPoint2d_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    holo_base_msg_vision_ObjectPoint2dTypePlugin_get(),
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
#define TTYPENAME   holo_base_msg_vision_ObjectPoint2fTYPENAME

/* 
holo_base_msg_vision_ObjectPoint2fDataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter holo_base_msg_vision_ObjectPoint2fDataWriter
#define TData       holo_base_msg_vision_ObjectPoint2f

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_vision_ObjectPoint2fDataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader holo_base_msg_vision_ObjectPoint2fDataReader
#define TDataSeq    holo_base_msg_vision_ObjectPoint2fSeq
#define TData       holo_base_msg_vision_ObjectPoint2f
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_vision_ObjectPoint2fTypeSupport

*/

#define TTypeSupport holo_base_msg_vision_ObjectPoint2fTypeSupport
#define TData        holo_base_msg_vision_ObjectPoint2f

static struct DDS_TypeProgramNode holo_base_msg_vision_ObjectPoint2f_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t holo_base_msg_vision_ObjectPoint2f_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_vision_ObjectPoint2f_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_vision_ObjectPoint2f_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
holo_base_msg_vision_ObjectPoint2fTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const holo_base_msg_vision_ObjectPoint2f *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &holo_base_msg_vision_ObjectPoint2f_gv_ProgramNode,
        holo_base_msg_vision_ObjectPoint2f_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,holo_base_msg_vision_ObjectPoint2fTypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        holo_base_msg_vision_ObjectPoint2f_gv_AutoRepresentation,
        holo_base_msg_vision_ObjectPoint2f_gv_XCDR1,
        holo_base_msg_vision_ObjectPoint2f_gv_XCDR2,
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
holo_base_msg_vision_ObjectPoint2fTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const holo_base_msg_vision_ObjectPoint2f *a_data)
{
    return holo_base_msg_vision_ObjectPoint2fTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
holo_base_msg_vision_ObjectPoint2fTypeSupport_deserialize_data_from_cdr_buffer(
    holo_base_msg_vision_ObjectPoint2f *a_data,
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
        &holo_base_msg_vision_ObjectPoint2f_gv_ProgramNode,
        holo_base_msg_vision_ObjectPoint2f_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    holo_base_msg_vision_ObjectPoint2fTypePlugin_get(),
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
#define TTYPENAME   holo_base_msg_vision_ObjectPoint3dTYPENAME

/* 
holo_base_msg_vision_ObjectPoint3dDataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter holo_base_msg_vision_ObjectPoint3dDataWriter
#define TData       holo_base_msg_vision_ObjectPoint3d

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_vision_ObjectPoint3dDataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader holo_base_msg_vision_ObjectPoint3dDataReader
#define TDataSeq    holo_base_msg_vision_ObjectPoint3dSeq
#define TData       holo_base_msg_vision_ObjectPoint3d
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_vision_ObjectPoint3dTypeSupport

*/

#define TTypeSupport holo_base_msg_vision_ObjectPoint3dTypeSupport
#define TData        holo_base_msg_vision_ObjectPoint3d

static struct DDS_TypeProgramNode holo_base_msg_vision_ObjectPoint3d_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t holo_base_msg_vision_ObjectPoint3d_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_vision_ObjectPoint3d_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_vision_ObjectPoint3d_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
holo_base_msg_vision_ObjectPoint3dTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const holo_base_msg_vision_ObjectPoint3d *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &holo_base_msg_vision_ObjectPoint3d_gv_ProgramNode,
        holo_base_msg_vision_ObjectPoint3d_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,holo_base_msg_vision_ObjectPoint3dTypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        holo_base_msg_vision_ObjectPoint3d_gv_AutoRepresentation,
        holo_base_msg_vision_ObjectPoint3d_gv_XCDR1,
        holo_base_msg_vision_ObjectPoint3d_gv_XCDR2,
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
holo_base_msg_vision_ObjectPoint3dTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const holo_base_msg_vision_ObjectPoint3d *a_data)
{
    return holo_base_msg_vision_ObjectPoint3dTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
holo_base_msg_vision_ObjectPoint3dTypeSupport_deserialize_data_from_cdr_buffer(
    holo_base_msg_vision_ObjectPoint3d *a_data,
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
        &holo_base_msg_vision_ObjectPoint3d_gv_ProgramNode,
        holo_base_msg_vision_ObjectPoint3d_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    holo_base_msg_vision_ObjectPoint3dTypePlugin_get(),
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
#define TTYPENAME   holo_base_msg_vision_ObjectPoint3fTYPENAME

/* 
holo_base_msg_vision_ObjectPoint3fDataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter holo_base_msg_vision_ObjectPoint3fDataWriter
#define TData       holo_base_msg_vision_ObjectPoint3f

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_vision_ObjectPoint3fDataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader holo_base_msg_vision_ObjectPoint3fDataReader
#define TDataSeq    holo_base_msg_vision_ObjectPoint3fSeq
#define TData       holo_base_msg_vision_ObjectPoint3f
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_vision_ObjectPoint3fTypeSupport

*/

#define TTypeSupport holo_base_msg_vision_ObjectPoint3fTypeSupport
#define TData        holo_base_msg_vision_ObjectPoint3f

static struct DDS_TypeProgramNode holo_base_msg_vision_ObjectPoint3f_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t holo_base_msg_vision_ObjectPoint3f_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_vision_ObjectPoint3f_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_vision_ObjectPoint3f_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
holo_base_msg_vision_ObjectPoint3fTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const holo_base_msg_vision_ObjectPoint3f *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &holo_base_msg_vision_ObjectPoint3f_gv_ProgramNode,
        holo_base_msg_vision_ObjectPoint3f_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,holo_base_msg_vision_ObjectPoint3fTypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        holo_base_msg_vision_ObjectPoint3f_gv_AutoRepresentation,
        holo_base_msg_vision_ObjectPoint3f_gv_XCDR1,
        holo_base_msg_vision_ObjectPoint3f_gv_XCDR2,
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
holo_base_msg_vision_ObjectPoint3fTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const holo_base_msg_vision_ObjectPoint3f *a_data)
{
    return holo_base_msg_vision_ObjectPoint3fTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
holo_base_msg_vision_ObjectPoint3fTypeSupport_deserialize_data_from_cdr_buffer(
    holo_base_msg_vision_ObjectPoint3f *a_data,
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
        &holo_base_msg_vision_ObjectPoint3f_gv_ProgramNode,
        holo_base_msg_vision_ObjectPoint3f_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    holo_base_msg_vision_ObjectPoint3fTypePlugin_get(),
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
#define TTYPENAME   holo_base_msg_vision_ImageObjectsKeyPoint2dTYPENAME

/* 
holo_base_msg_vision_ImageObjectsKeyPoint2dDataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter holo_base_msg_vision_ImageObjectsKeyPoint2dDataWriter
#define TData       holo_base_msg_vision_ImageObjectsKeyPoint2d

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_vision_ImageObjectsKeyPoint2dDataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader holo_base_msg_vision_ImageObjectsKeyPoint2dDataReader
#define TDataSeq    holo_base_msg_vision_ImageObjectsKeyPoint2dSeq
#define TData       holo_base_msg_vision_ImageObjectsKeyPoint2d
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_vision_ImageObjectsKeyPoint2dTypeSupport

*/

#define TTypeSupport holo_base_msg_vision_ImageObjectsKeyPoint2dTypeSupport
#define TData        holo_base_msg_vision_ImageObjectsKeyPoint2d

static struct DDS_TypeProgramNode holo_base_msg_vision_ImageObjectsKeyPoint2d_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t holo_base_msg_vision_ImageObjectsKeyPoint2d_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_vision_ImageObjectsKeyPoint2d_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_vision_ImageObjectsKeyPoint2d_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
holo_base_msg_vision_ImageObjectsKeyPoint2dTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const holo_base_msg_vision_ImageObjectsKeyPoint2d *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &holo_base_msg_vision_ImageObjectsKeyPoint2d_gv_ProgramNode,
        holo_base_msg_vision_ImageObjectsKeyPoint2d_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,holo_base_msg_vision_ImageObjectsKeyPoint2dTypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        holo_base_msg_vision_ImageObjectsKeyPoint2d_gv_AutoRepresentation,
        holo_base_msg_vision_ImageObjectsKeyPoint2d_gv_XCDR1,
        holo_base_msg_vision_ImageObjectsKeyPoint2d_gv_XCDR2,
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
holo_base_msg_vision_ImageObjectsKeyPoint2dTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const holo_base_msg_vision_ImageObjectsKeyPoint2d *a_data)
{
    return holo_base_msg_vision_ImageObjectsKeyPoint2dTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
holo_base_msg_vision_ImageObjectsKeyPoint2dTypeSupport_deserialize_data_from_cdr_buffer(
    holo_base_msg_vision_ImageObjectsKeyPoint2d *a_data,
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
        &holo_base_msg_vision_ImageObjectsKeyPoint2d_gv_ProgramNode,
        holo_base_msg_vision_ImageObjectsKeyPoint2d_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    holo_base_msg_vision_ImageObjectsKeyPoint2dTypePlugin_get(),
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
#define TTYPENAME   holo_base_msg_vision_ImageObjectsKeyPoint2fTYPENAME

/* 
holo_base_msg_vision_ImageObjectsKeyPoint2fDataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter holo_base_msg_vision_ImageObjectsKeyPoint2fDataWriter
#define TData       holo_base_msg_vision_ImageObjectsKeyPoint2f

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_vision_ImageObjectsKeyPoint2fDataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader holo_base_msg_vision_ImageObjectsKeyPoint2fDataReader
#define TDataSeq    holo_base_msg_vision_ImageObjectsKeyPoint2fSeq
#define TData       holo_base_msg_vision_ImageObjectsKeyPoint2f
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_vision_ImageObjectsKeyPoint2fTypeSupport

*/

#define TTypeSupport holo_base_msg_vision_ImageObjectsKeyPoint2fTypeSupport
#define TData        holo_base_msg_vision_ImageObjectsKeyPoint2f

static struct DDS_TypeProgramNode holo_base_msg_vision_ImageObjectsKeyPoint2f_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t holo_base_msg_vision_ImageObjectsKeyPoint2f_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_vision_ImageObjectsKeyPoint2f_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_vision_ImageObjectsKeyPoint2f_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
holo_base_msg_vision_ImageObjectsKeyPoint2fTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const holo_base_msg_vision_ImageObjectsKeyPoint2f *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &holo_base_msg_vision_ImageObjectsKeyPoint2f_gv_ProgramNode,
        holo_base_msg_vision_ImageObjectsKeyPoint2f_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,holo_base_msg_vision_ImageObjectsKeyPoint2fTypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        holo_base_msg_vision_ImageObjectsKeyPoint2f_gv_AutoRepresentation,
        holo_base_msg_vision_ImageObjectsKeyPoint2f_gv_XCDR1,
        holo_base_msg_vision_ImageObjectsKeyPoint2f_gv_XCDR2,
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
holo_base_msg_vision_ImageObjectsKeyPoint2fTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const holo_base_msg_vision_ImageObjectsKeyPoint2f *a_data)
{
    return holo_base_msg_vision_ImageObjectsKeyPoint2fTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
holo_base_msg_vision_ImageObjectsKeyPoint2fTypeSupport_deserialize_data_from_cdr_buffer(
    holo_base_msg_vision_ImageObjectsKeyPoint2f *a_data,
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
        &holo_base_msg_vision_ImageObjectsKeyPoint2f_gv_ProgramNode,
        holo_base_msg_vision_ImageObjectsKeyPoint2f_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    holo_base_msg_vision_ImageObjectsKeyPoint2fTypePlugin_get(),
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
#define TTYPENAME   holo_base_msg_vision_ImageObjectsPoint2dTYPENAME

/* 
holo_base_msg_vision_ImageObjectsPoint2dDataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter holo_base_msg_vision_ImageObjectsPoint2dDataWriter
#define TData       holo_base_msg_vision_ImageObjectsPoint2d

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_vision_ImageObjectsPoint2dDataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader holo_base_msg_vision_ImageObjectsPoint2dDataReader
#define TDataSeq    holo_base_msg_vision_ImageObjectsPoint2dSeq
#define TData       holo_base_msg_vision_ImageObjectsPoint2d
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_vision_ImageObjectsPoint2dTypeSupport

*/

#define TTypeSupport holo_base_msg_vision_ImageObjectsPoint2dTypeSupport
#define TData        holo_base_msg_vision_ImageObjectsPoint2d

static struct DDS_TypeProgramNode holo_base_msg_vision_ImageObjectsPoint2d_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t holo_base_msg_vision_ImageObjectsPoint2d_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_vision_ImageObjectsPoint2d_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_vision_ImageObjectsPoint2d_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
holo_base_msg_vision_ImageObjectsPoint2dTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const holo_base_msg_vision_ImageObjectsPoint2d *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &holo_base_msg_vision_ImageObjectsPoint2d_gv_ProgramNode,
        holo_base_msg_vision_ImageObjectsPoint2d_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,holo_base_msg_vision_ImageObjectsPoint2dTypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        holo_base_msg_vision_ImageObjectsPoint2d_gv_AutoRepresentation,
        holo_base_msg_vision_ImageObjectsPoint2d_gv_XCDR1,
        holo_base_msg_vision_ImageObjectsPoint2d_gv_XCDR2,
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
holo_base_msg_vision_ImageObjectsPoint2dTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const holo_base_msg_vision_ImageObjectsPoint2d *a_data)
{
    return holo_base_msg_vision_ImageObjectsPoint2dTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
holo_base_msg_vision_ImageObjectsPoint2dTypeSupport_deserialize_data_from_cdr_buffer(
    holo_base_msg_vision_ImageObjectsPoint2d *a_data,
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
        &holo_base_msg_vision_ImageObjectsPoint2d_gv_ProgramNode,
        holo_base_msg_vision_ImageObjectsPoint2d_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    holo_base_msg_vision_ImageObjectsPoint2dTypePlugin_get(),
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
#define TTYPENAME   holo_base_msg_vision_ImageObjectsPoint2fTYPENAME

/* 
holo_base_msg_vision_ImageObjectsPoint2fDataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter holo_base_msg_vision_ImageObjectsPoint2fDataWriter
#define TData       holo_base_msg_vision_ImageObjectsPoint2f

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_vision_ImageObjectsPoint2fDataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader holo_base_msg_vision_ImageObjectsPoint2fDataReader
#define TDataSeq    holo_base_msg_vision_ImageObjectsPoint2fSeq
#define TData       holo_base_msg_vision_ImageObjectsPoint2f
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_vision_ImageObjectsPoint2fTypeSupport

*/

#define TTypeSupport holo_base_msg_vision_ImageObjectsPoint2fTypeSupport
#define TData        holo_base_msg_vision_ImageObjectsPoint2f

static struct DDS_TypeProgramNode holo_base_msg_vision_ImageObjectsPoint2f_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t holo_base_msg_vision_ImageObjectsPoint2f_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_vision_ImageObjectsPoint2f_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_vision_ImageObjectsPoint2f_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
holo_base_msg_vision_ImageObjectsPoint2fTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const holo_base_msg_vision_ImageObjectsPoint2f *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &holo_base_msg_vision_ImageObjectsPoint2f_gv_ProgramNode,
        holo_base_msg_vision_ImageObjectsPoint2f_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,holo_base_msg_vision_ImageObjectsPoint2fTypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        holo_base_msg_vision_ImageObjectsPoint2f_gv_AutoRepresentation,
        holo_base_msg_vision_ImageObjectsPoint2f_gv_XCDR1,
        holo_base_msg_vision_ImageObjectsPoint2f_gv_XCDR2,
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
holo_base_msg_vision_ImageObjectsPoint2fTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const holo_base_msg_vision_ImageObjectsPoint2f *a_data)
{
    return holo_base_msg_vision_ImageObjectsPoint2fTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
holo_base_msg_vision_ImageObjectsPoint2fTypeSupport_deserialize_data_from_cdr_buffer(
    holo_base_msg_vision_ImageObjectsPoint2f *a_data,
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
        &holo_base_msg_vision_ImageObjectsPoint2f_gv_ProgramNode,
        holo_base_msg_vision_ImageObjectsPoint2f_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    holo_base_msg_vision_ImageObjectsPoint2fTypePlugin_get(),
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
#define TTYPENAME   holo_base_msg_vision_ImageObjectsPoint3dTYPENAME

/* 
holo_base_msg_vision_ImageObjectsPoint3dDataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter holo_base_msg_vision_ImageObjectsPoint3dDataWriter
#define TData       holo_base_msg_vision_ImageObjectsPoint3d

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_vision_ImageObjectsPoint3dDataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader holo_base_msg_vision_ImageObjectsPoint3dDataReader
#define TDataSeq    holo_base_msg_vision_ImageObjectsPoint3dSeq
#define TData       holo_base_msg_vision_ImageObjectsPoint3d
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_vision_ImageObjectsPoint3dTypeSupport

*/

#define TTypeSupport holo_base_msg_vision_ImageObjectsPoint3dTypeSupport
#define TData        holo_base_msg_vision_ImageObjectsPoint3d

static struct DDS_TypeProgramNode holo_base_msg_vision_ImageObjectsPoint3d_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t holo_base_msg_vision_ImageObjectsPoint3d_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_vision_ImageObjectsPoint3d_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_vision_ImageObjectsPoint3d_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
holo_base_msg_vision_ImageObjectsPoint3dTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const holo_base_msg_vision_ImageObjectsPoint3d *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &holo_base_msg_vision_ImageObjectsPoint3d_gv_ProgramNode,
        holo_base_msg_vision_ImageObjectsPoint3d_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,holo_base_msg_vision_ImageObjectsPoint3dTypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        holo_base_msg_vision_ImageObjectsPoint3d_gv_AutoRepresentation,
        holo_base_msg_vision_ImageObjectsPoint3d_gv_XCDR1,
        holo_base_msg_vision_ImageObjectsPoint3d_gv_XCDR2,
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
holo_base_msg_vision_ImageObjectsPoint3dTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const holo_base_msg_vision_ImageObjectsPoint3d *a_data)
{
    return holo_base_msg_vision_ImageObjectsPoint3dTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
holo_base_msg_vision_ImageObjectsPoint3dTypeSupport_deserialize_data_from_cdr_buffer(
    holo_base_msg_vision_ImageObjectsPoint3d *a_data,
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
        &holo_base_msg_vision_ImageObjectsPoint3d_gv_ProgramNode,
        holo_base_msg_vision_ImageObjectsPoint3d_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    holo_base_msg_vision_ImageObjectsPoint3dTypePlugin_get(),
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
#define TTYPENAME   holo_base_msg_vision_ImageObjectsPoint3fTYPENAME

/* 
holo_base_msg_vision_ImageObjectsPoint3fDataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter holo_base_msg_vision_ImageObjectsPoint3fDataWriter
#define TData       holo_base_msg_vision_ImageObjectsPoint3f

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_vision_ImageObjectsPoint3fDataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader holo_base_msg_vision_ImageObjectsPoint3fDataReader
#define TDataSeq    holo_base_msg_vision_ImageObjectsPoint3fSeq
#define TData       holo_base_msg_vision_ImageObjectsPoint3f
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_vision_ImageObjectsPoint3fTypeSupport

*/

#define TTypeSupport holo_base_msg_vision_ImageObjectsPoint3fTypeSupport
#define TData        holo_base_msg_vision_ImageObjectsPoint3f

static struct DDS_TypeProgramNode holo_base_msg_vision_ImageObjectsPoint3f_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t holo_base_msg_vision_ImageObjectsPoint3f_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_vision_ImageObjectsPoint3f_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_vision_ImageObjectsPoint3f_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
holo_base_msg_vision_ImageObjectsPoint3fTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const holo_base_msg_vision_ImageObjectsPoint3f *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &holo_base_msg_vision_ImageObjectsPoint3f_gv_ProgramNode,
        holo_base_msg_vision_ImageObjectsPoint3f_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,holo_base_msg_vision_ImageObjectsPoint3fTypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        holo_base_msg_vision_ImageObjectsPoint3f_gv_AutoRepresentation,
        holo_base_msg_vision_ImageObjectsPoint3f_gv_XCDR1,
        holo_base_msg_vision_ImageObjectsPoint3f_gv_XCDR2,
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
holo_base_msg_vision_ImageObjectsPoint3fTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const holo_base_msg_vision_ImageObjectsPoint3f *a_data)
{
    return holo_base_msg_vision_ImageObjectsPoint3fTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
holo_base_msg_vision_ImageObjectsPoint3fTypeSupport_deserialize_data_from_cdr_buffer(
    holo_base_msg_vision_ImageObjectsPoint3f *a_data,
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
        &holo_base_msg_vision_ImageObjectsPoint3f_gv_ProgramNode,
        holo_base_msg_vision_ImageObjectsPoint3f_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    holo_base_msg_vision_ImageObjectsPoint3fTypePlugin_get(),
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

