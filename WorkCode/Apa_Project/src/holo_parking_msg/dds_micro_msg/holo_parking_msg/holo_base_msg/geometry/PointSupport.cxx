/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Point.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "PointSupport.h"

/*** SOURCE_BEGIN ***/

/* =========================================================================== */

/* Requires */
#define TTYPENAME   holo_base_msg_geometry_Point3fTYPENAME

/* 
holo_base_msg_geometry_Point3fDataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter holo_base_msg_geometry_Point3fDataWriter
#define TData       holo_base_msg_geometry_Point3f

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_geometry_Point3fDataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader holo_base_msg_geometry_Point3fDataReader
#define TDataSeq    holo_base_msg_geometry_Point3fSeq
#define TData       holo_base_msg_geometry_Point3f
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_geometry_Point3fTypeSupport

*/

#define TTypeSupport holo_base_msg_geometry_Point3fTypeSupport
#define TData        holo_base_msg_geometry_Point3f

static struct DDS_TypeProgramNode holo_base_msg_geometry_Point3f_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t holo_base_msg_geometry_Point3f_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_geometry_Point3f_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_geometry_Point3f_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
holo_base_msg_geometry_Point3fTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const holo_base_msg_geometry_Point3f *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &holo_base_msg_geometry_Point3f_gv_ProgramNode,
        holo_base_msg_geometry_Point3f_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,holo_base_msg_geometry_Point3fTypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        holo_base_msg_geometry_Point3f_gv_AutoRepresentation,
        holo_base_msg_geometry_Point3f_gv_XCDR1,
        holo_base_msg_geometry_Point3f_gv_XCDR2,
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
holo_base_msg_geometry_Point3fTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const holo_base_msg_geometry_Point3f *a_data)
{
    return holo_base_msg_geometry_Point3fTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
holo_base_msg_geometry_Point3fTypeSupport_deserialize_data_from_cdr_buffer(
    holo_base_msg_geometry_Point3f *a_data,
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
        &holo_base_msg_geometry_Point3f_gv_ProgramNode,
        holo_base_msg_geometry_Point3f_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    holo_base_msg_geometry_Point3fTypePlugin_get(),
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
#define TTYPENAME   holo_base_msg_geometry_Point3dTYPENAME

/* 
holo_base_msg_geometry_Point3dDataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter holo_base_msg_geometry_Point3dDataWriter
#define TData       holo_base_msg_geometry_Point3d

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_geometry_Point3dDataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader holo_base_msg_geometry_Point3dDataReader
#define TDataSeq    holo_base_msg_geometry_Point3dSeq
#define TData       holo_base_msg_geometry_Point3d
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_geometry_Point3dTypeSupport

*/

#define TTypeSupport holo_base_msg_geometry_Point3dTypeSupport
#define TData        holo_base_msg_geometry_Point3d

static struct DDS_TypeProgramNode holo_base_msg_geometry_Point3d_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t holo_base_msg_geometry_Point3d_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_geometry_Point3d_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_geometry_Point3d_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
holo_base_msg_geometry_Point3dTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const holo_base_msg_geometry_Point3d *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &holo_base_msg_geometry_Point3d_gv_ProgramNode,
        holo_base_msg_geometry_Point3d_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,holo_base_msg_geometry_Point3dTypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        holo_base_msg_geometry_Point3d_gv_AutoRepresentation,
        holo_base_msg_geometry_Point3d_gv_XCDR1,
        holo_base_msg_geometry_Point3d_gv_XCDR2,
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
holo_base_msg_geometry_Point3dTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const holo_base_msg_geometry_Point3d *a_data)
{
    return holo_base_msg_geometry_Point3dTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
holo_base_msg_geometry_Point3dTypeSupport_deserialize_data_from_cdr_buffer(
    holo_base_msg_geometry_Point3d *a_data,
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
        &holo_base_msg_geometry_Point3d_gv_ProgramNode,
        holo_base_msg_geometry_Point3d_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    holo_base_msg_geometry_Point3dTypePlugin_get(),
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
#define TTYPENAME   holo_base_msg_geometry_Point2fTYPENAME

/* 
holo_base_msg_geometry_Point2fDataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter holo_base_msg_geometry_Point2fDataWriter
#define TData       holo_base_msg_geometry_Point2f

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_geometry_Point2fDataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader holo_base_msg_geometry_Point2fDataReader
#define TDataSeq    holo_base_msg_geometry_Point2fSeq
#define TData       holo_base_msg_geometry_Point2f
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_geometry_Point2fTypeSupport

*/

#define TTypeSupport holo_base_msg_geometry_Point2fTypeSupport
#define TData        holo_base_msg_geometry_Point2f

static struct DDS_TypeProgramNode holo_base_msg_geometry_Point2f_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t holo_base_msg_geometry_Point2f_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_geometry_Point2f_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_geometry_Point2f_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
holo_base_msg_geometry_Point2fTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const holo_base_msg_geometry_Point2f *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &holo_base_msg_geometry_Point2f_gv_ProgramNode,
        holo_base_msg_geometry_Point2f_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,holo_base_msg_geometry_Point2fTypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        holo_base_msg_geometry_Point2f_gv_AutoRepresentation,
        holo_base_msg_geometry_Point2f_gv_XCDR1,
        holo_base_msg_geometry_Point2f_gv_XCDR2,
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
holo_base_msg_geometry_Point2fTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const holo_base_msg_geometry_Point2f *a_data)
{
    return holo_base_msg_geometry_Point2fTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
holo_base_msg_geometry_Point2fTypeSupport_deserialize_data_from_cdr_buffer(
    holo_base_msg_geometry_Point2f *a_data,
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
        &holo_base_msg_geometry_Point2f_gv_ProgramNode,
        holo_base_msg_geometry_Point2f_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    holo_base_msg_geometry_Point2fTypePlugin_get(),
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
#define TTYPENAME   holo_base_msg_geometry_Point2dTYPENAME

/* 
holo_base_msg_geometry_Point2dDataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter holo_base_msg_geometry_Point2dDataWriter
#define TData       holo_base_msg_geometry_Point2d

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_geometry_Point2dDataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader holo_base_msg_geometry_Point2dDataReader
#define TDataSeq    holo_base_msg_geometry_Point2dSeq
#define TData       holo_base_msg_geometry_Point2d
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_geometry_Point2dTypeSupport

*/

#define TTypeSupport holo_base_msg_geometry_Point2dTypeSupport
#define TData        holo_base_msg_geometry_Point2d

static struct DDS_TypeProgramNode holo_base_msg_geometry_Point2d_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t holo_base_msg_geometry_Point2d_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_geometry_Point2d_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_geometry_Point2d_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
holo_base_msg_geometry_Point2dTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const holo_base_msg_geometry_Point2d *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &holo_base_msg_geometry_Point2d_gv_ProgramNode,
        holo_base_msg_geometry_Point2d_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,holo_base_msg_geometry_Point2dTypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        holo_base_msg_geometry_Point2d_gv_AutoRepresentation,
        holo_base_msg_geometry_Point2d_gv_XCDR1,
        holo_base_msg_geometry_Point2d_gv_XCDR2,
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
holo_base_msg_geometry_Point2dTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const holo_base_msg_geometry_Point2d *a_data)
{
    return holo_base_msg_geometry_Point2dTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
holo_base_msg_geometry_Point2dTypeSupport_deserialize_data_from_cdr_buffer(
    holo_base_msg_geometry_Point2d *a_data,
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
        &holo_base_msg_geometry_Point2d_gv_ProgramNode,
        holo_base_msg_geometry_Point2d_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    holo_base_msg_geometry_Point2dTypePlugin_get(),
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

