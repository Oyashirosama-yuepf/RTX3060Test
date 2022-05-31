/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from AppStatus.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "AppStatusSupport.h"

/*** SOURCE_BEGIN ***/

/* =========================================================================== */

/* Requires */
#define TTYPENAME   holo_base_msg_common_AppStatusTYPENAME

/* 
holo_base_msg_common_AppStatusDataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter holo_base_msg_common_AppStatusDataWriter
#define TData       holo_base_msg_common_AppStatus

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_common_AppStatusDataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader holo_base_msg_common_AppStatusDataReader
#define TDataSeq    holo_base_msg_common_AppStatusSeq
#define TData       holo_base_msg_common_AppStatus
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_common_AppStatusTypeSupport

*/

#define TTypeSupport holo_base_msg_common_AppStatusTypeSupport
#define TData        holo_base_msg_common_AppStatus

static struct DDS_TypeProgramNode holo_base_msg_common_AppStatus_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t holo_base_msg_common_AppStatus_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_common_AppStatus_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_common_AppStatus_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
holo_base_msg_common_AppStatusTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const holo_base_msg_common_AppStatus *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &holo_base_msg_common_AppStatus_gv_ProgramNode,
        holo_base_msg_common_AppStatus_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,holo_base_msg_common_AppStatusTypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        holo_base_msg_common_AppStatus_gv_AutoRepresentation,
        holo_base_msg_common_AppStatus_gv_XCDR1,
        holo_base_msg_common_AppStatus_gv_XCDR2,
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
holo_base_msg_common_AppStatusTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const holo_base_msg_common_AppStatus *a_data)
{
    return holo_base_msg_common_AppStatusTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
holo_base_msg_common_AppStatusTypeSupport_deserialize_data_from_cdr_buffer(
    holo_base_msg_common_AppStatus *a_data,
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
        &holo_base_msg_common_AppStatus_gv_ProgramNode,
        holo_base_msg_common_AppStatus_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    holo_base_msg_common_AppStatusTypePlugin_get(),
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

