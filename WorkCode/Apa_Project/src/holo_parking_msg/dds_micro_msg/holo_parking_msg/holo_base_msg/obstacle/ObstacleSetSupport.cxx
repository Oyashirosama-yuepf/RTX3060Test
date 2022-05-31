/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ObstacleSet.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "ObstacleSetSupport.h"

/*** SOURCE_BEGIN ***/

/* =========================================================================== */

/* Requires */
#define TTYPENAME   holo_base_msg_obstacle_ObstacleGeneralTYPENAME

/* 
holo_base_msg_obstacle_ObstacleGeneralDataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter holo_base_msg_obstacle_ObstacleGeneralDataWriter
#define TData       holo_base_msg_obstacle_ObstacleGeneral

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_obstacle_ObstacleGeneralDataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader holo_base_msg_obstacle_ObstacleGeneralDataReader
#define TDataSeq    holo_base_msg_obstacle_ObstacleGeneralSeq
#define TData       holo_base_msg_obstacle_ObstacleGeneral
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_obstacle_ObstacleGeneralTypeSupport

*/

#define TTypeSupport holo_base_msg_obstacle_ObstacleGeneralTypeSupport
#define TData        holo_base_msg_obstacle_ObstacleGeneral

static struct DDS_TypeProgramNode holo_base_msg_obstacle_ObstacleGeneral_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t holo_base_msg_obstacle_ObstacleGeneral_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_obstacle_ObstacleGeneral_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_obstacle_ObstacleGeneral_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
holo_base_msg_obstacle_ObstacleGeneralTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const holo_base_msg_obstacle_ObstacleGeneral *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &holo_base_msg_obstacle_ObstacleGeneral_gv_ProgramNode,
        holo_base_msg_obstacle_ObstacleGeneral_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,holo_base_msg_obstacle_ObstacleGeneralTypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        holo_base_msg_obstacle_ObstacleGeneral_gv_AutoRepresentation,
        holo_base_msg_obstacle_ObstacleGeneral_gv_XCDR1,
        holo_base_msg_obstacle_ObstacleGeneral_gv_XCDR2,
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
holo_base_msg_obstacle_ObstacleGeneralTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const holo_base_msg_obstacle_ObstacleGeneral *a_data)
{
    return holo_base_msg_obstacle_ObstacleGeneralTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
holo_base_msg_obstacle_ObstacleGeneralTypeSupport_deserialize_data_from_cdr_buffer(
    holo_base_msg_obstacle_ObstacleGeneral *a_data,
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
        &holo_base_msg_obstacle_ObstacleGeneral_gv_ProgramNode,
        holo_base_msg_obstacle_ObstacleGeneral_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    holo_base_msg_obstacle_ObstacleGeneralTypePlugin_get(),
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
#define TTYPENAME   holo_base_msg_obstacle_ObstacleGeneralListTYPENAME

/* 
holo_base_msg_obstacle_ObstacleGeneralListDataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter holo_base_msg_obstacle_ObstacleGeneralListDataWriter
#define TData       holo_base_msg_obstacle_ObstacleGeneralList

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_obstacle_ObstacleGeneralListDataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader holo_base_msg_obstacle_ObstacleGeneralListDataReader
#define TDataSeq    holo_base_msg_obstacle_ObstacleGeneralListSeq
#define TData       holo_base_msg_obstacle_ObstacleGeneralList
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_obstacle_ObstacleGeneralListTypeSupport

*/

#define TTypeSupport holo_base_msg_obstacle_ObstacleGeneralListTypeSupport
#define TData        holo_base_msg_obstacle_ObstacleGeneralList

static struct DDS_TypeProgramNode holo_base_msg_obstacle_ObstacleGeneralList_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t holo_base_msg_obstacle_ObstacleGeneralList_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_obstacle_ObstacleGeneralList_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_obstacle_ObstacleGeneralList_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
holo_base_msg_obstacle_ObstacleGeneralListTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const holo_base_msg_obstacle_ObstacleGeneralList *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &holo_base_msg_obstacle_ObstacleGeneralList_gv_ProgramNode,
        holo_base_msg_obstacle_ObstacleGeneralList_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,holo_base_msg_obstacle_ObstacleGeneralListTypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        holo_base_msg_obstacle_ObstacleGeneralList_gv_AutoRepresentation,
        holo_base_msg_obstacle_ObstacleGeneralList_gv_XCDR1,
        holo_base_msg_obstacle_ObstacleGeneralList_gv_XCDR2,
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
holo_base_msg_obstacle_ObstacleGeneralListTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const holo_base_msg_obstacle_ObstacleGeneralList *a_data)
{
    return holo_base_msg_obstacle_ObstacleGeneralListTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
holo_base_msg_obstacle_ObstacleGeneralListTypeSupport_deserialize_data_from_cdr_buffer(
    holo_base_msg_obstacle_ObstacleGeneralList *a_data,
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
        &holo_base_msg_obstacle_ObstacleGeneralList_gv_ProgramNode,
        holo_base_msg_obstacle_ObstacleGeneralList_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    holo_base_msg_obstacle_ObstacleGeneralListTypePlugin_get(),
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
#define TTYPENAME   holo_base_msg_obstacle_ObstacleRadarTYPENAME

/* 
holo_base_msg_obstacle_ObstacleRadarDataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter holo_base_msg_obstacle_ObstacleRadarDataWriter
#define TData       holo_base_msg_obstacle_ObstacleRadar

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_obstacle_ObstacleRadarDataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader holo_base_msg_obstacle_ObstacleRadarDataReader
#define TDataSeq    holo_base_msg_obstacle_ObstacleRadarSeq
#define TData       holo_base_msg_obstacle_ObstacleRadar
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_obstacle_ObstacleRadarTypeSupport

*/

#define TTypeSupport holo_base_msg_obstacle_ObstacleRadarTypeSupport
#define TData        holo_base_msg_obstacle_ObstacleRadar

static struct DDS_TypeProgramNode holo_base_msg_obstacle_ObstacleRadar_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t holo_base_msg_obstacle_ObstacleRadar_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_obstacle_ObstacleRadar_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_obstacle_ObstacleRadar_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
holo_base_msg_obstacle_ObstacleRadarTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const holo_base_msg_obstacle_ObstacleRadar *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &holo_base_msg_obstacle_ObstacleRadar_gv_ProgramNode,
        holo_base_msg_obstacle_ObstacleRadar_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,holo_base_msg_obstacle_ObstacleRadarTypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        holo_base_msg_obstacle_ObstacleRadar_gv_AutoRepresentation,
        holo_base_msg_obstacle_ObstacleRadar_gv_XCDR1,
        holo_base_msg_obstacle_ObstacleRadar_gv_XCDR2,
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
holo_base_msg_obstacle_ObstacleRadarTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const holo_base_msg_obstacle_ObstacleRadar *a_data)
{
    return holo_base_msg_obstacle_ObstacleRadarTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
holo_base_msg_obstacle_ObstacleRadarTypeSupport_deserialize_data_from_cdr_buffer(
    holo_base_msg_obstacle_ObstacleRadar *a_data,
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
        &holo_base_msg_obstacle_ObstacleRadar_gv_ProgramNode,
        holo_base_msg_obstacle_ObstacleRadar_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    holo_base_msg_obstacle_ObstacleRadarTypePlugin_get(),
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
#define TTYPENAME   holo_base_msg_obstacle_ObstacleRadarListTYPENAME

/* 
holo_base_msg_obstacle_ObstacleRadarListDataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter holo_base_msg_obstacle_ObstacleRadarListDataWriter
#define TData       holo_base_msg_obstacle_ObstacleRadarList

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_obstacle_ObstacleRadarListDataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader holo_base_msg_obstacle_ObstacleRadarListDataReader
#define TDataSeq    holo_base_msg_obstacle_ObstacleRadarListSeq
#define TData       holo_base_msg_obstacle_ObstacleRadarList
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_obstacle_ObstacleRadarListTypeSupport

*/

#define TTypeSupport holo_base_msg_obstacle_ObstacleRadarListTypeSupport
#define TData        holo_base_msg_obstacle_ObstacleRadarList

static struct DDS_TypeProgramNode holo_base_msg_obstacle_ObstacleRadarList_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t holo_base_msg_obstacle_ObstacleRadarList_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_obstacle_ObstacleRadarList_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_obstacle_ObstacleRadarList_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
holo_base_msg_obstacle_ObstacleRadarListTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const holo_base_msg_obstacle_ObstacleRadarList *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &holo_base_msg_obstacle_ObstacleRadarList_gv_ProgramNode,
        holo_base_msg_obstacle_ObstacleRadarList_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,holo_base_msg_obstacle_ObstacleRadarListTypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        holo_base_msg_obstacle_ObstacleRadarList_gv_AutoRepresentation,
        holo_base_msg_obstacle_ObstacleRadarList_gv_XCDR1,
        holo_base_msg_obstacle_ObstacleRadarList_gv_XCDR2,
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
holo_base_msg_obstacle_ObstacleRadarListTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const holo_base_msg_obstacle_ObstacleRadarList *a_data)
{
    return holo_base_msg_obstacle_ObstacleRadarListTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
holo_base_msg_obstacle_ObstacleRadarListTypeSupport_deserialize_data_from_cdr_buffer(
    holo_base_msg_obstacle_ObstacleRadarList *a_data,
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
        &holo_base_msg_obstacle_ObstacleRadarList_gv_ProgramNode,
        holo_base_msg_obstacle_ObstacleRadarList_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    holo_base_msg_obstacle_ObstacleRadarListTypePlugin_get(),
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
#define TTYPENAME   holo_base_msg_obstacle_ObstacleUssTYPENAME

/* 
holo_base_msg_obstacle_ObstacleUssDataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter holo_base_msg_obstacle_ObstacleUssDataWriter
#define TData       holo_base_msg_obstacle_ObstacleUss

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_obstacle_ObstacleUssDataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader holo_base_msg_obstacle_ObstacleUssDataReader
#define TDataSeq    holo_base_msg_obstacle_ObstacleUssSeq
#define TData       holo_base_msg_obstacle_ObstacleUss
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_obstacle_ObstacleUssTypeSupport

*/

#define TTypeSupport holo_base_msg_obstacle_ObstacleUssTypeSupport
#define TData        holo_base_msg_obstacle_ObstacleUss

static struct DDS_TypeProgramNode holo_base_msg_obstacle_ObstacleUss_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t holo_base_msg_obstacle_ObstacleUss_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_obstacle_ObstacleUss_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_obstacle_ObstacleUss_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
holo_base_msg_obstacle_ObstacleUssTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const holo_base_msg_obstacle_ObstacleUss *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &holo_base_msg_obstacle_ObstacleUss_gv_ProgramNode,
        holo_base_msg_obstacle_ObstacleUss_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,holo_base_msg_obstacle_ObstacleUssTypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        holo_base_msg_obstacle_ObstacleUss_gv_AutoRepresentation,
        holo_base_msg_obstacle_ObstacleUss_gv_XCDR1,
        holo_base_msg_obstacle_ObstacleUss_gv_XCDR2,
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
holo_base_msg_obstacle_ObstacleUssTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const holo_base_msg_obstacle_ObstacleUss *a_data)
{
    return holo_base_msg_obstacle_ObstacleUssTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
holo_base_msg_obstacle_ObstacleUssTypeSupport_deserialize_data_from_cdr_buffer(
    holo_base_msg_obstacle_ObstacleUss *a_data,
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
        &holo_base_msg_obstacle_ObstacleUss_gv_ProgramNode,
        holo_base_msg_obstacle_ObstacleUss_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    holo_base_msg_obstacle_ObstacleUssTypePlugin_get(),
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
#define TTYPENAME   holo_base_msg_obstacle_ObstacleUssListTYPENAME

/* 
holo_base_msg_obstacle_ObstacleUssListDataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter holo_base_msg_obstacle_ObstacleUssListDataWriter
#define TData       holo_base_msg_obstacle_ObstacleUssList

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_obstacle_ObstacleUssListDataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader holo_base_msg_obstacle_ObstacleUssListDataReader
#define TDataSeq    holo_base_msg_obstacle_ObstacleUssListSeq
#define TData       holo_base_msg_obstacle_ObstacleUssList
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_obstacle_ObstacleUssListTypeSupport

*/

#define TTypeSupport holo_base_msg_obstacle_ObstacleUssListTypeSupport
#define TData        holo_base_msg_obstacle_ObstacleUssList

static struct DDS_TypeProgramNode holo_base_msg_obstacle_ObstacleUssList_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t holo_base_msg_obstacle_ObstacleUssList_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_obstacle_ObstacleUssList_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_obstacle_ObstacleUssList_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
holo_base_msg_obstacle_ObstacleUssListTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const holo_base_msg_obstacle_ObstacleUssList *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &holo_base_msg_obstacle_ObstacleUssList_gv_ProgramNode,
        holo_base_msg_obstacle_ObstacleUssList_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,holo_base_msg_obstacle_ObstacleUssListTypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        holo_base_msg_obstacle_ObstacleUssList_gv_AutoRepresentation,
        holo_base_msg_obstacle_ObstacleUssList_gv_XCDR1,
        holo_base_msg_obstacle_ObstacleUssList_gv_XCDR2,
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
holo_base_msg_obstacle_ObstacleUssListTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const holo_base_msg_obstacle_ObstacleUssList *a_data)
{
    return holo_base_msg_obstacle_ObstacleUssListTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
holo_base_msg_obstacle_ObstacleUssListTypeSupport_deserialize_data_from_cdr_buffer(
    holo_base_msg_obstacle_ObstacleUssList *a_data,
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
        &holo_base_msg_obstacle_ObstacleUssList_gv_ProgramNode,
        holo_base_msg_obstacle_ObstacleUssList_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    holo_base_msg_obstacle_ObstacleUssListTypePlugin_get(),
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
#define TTYPENAME   holo_base_msg_obstacle_ObstacleVisionTYPENAME

/* 
holo_base_msg_obstacle_ObstacleVisionDataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter holo_base_msg_obstacle_ObstacleVisionDataWriter
#define TData       holo_base_msg_obstacle_ObstacleVision

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_obstacle_ObstacleVisionDataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader holo_base_msg_obstacle_ObstacleVisionDataReader
#define TDataSeq    holo_base_msg_obstacle_ObstacleVisionSeq
#define TData       holo_base_msg_obstacle_ObstacleVision
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_obstacle_ObstacleVisionTypeSupport

*/

#define TTypeSupport holo_base_msg_obstacle_ObstacleVisionTypeSupport
#define TData        holo_base_msg_obstacle_ObstacleVision

static struct DDS_TypeProgramNode holo_base_msg_obstacle_ObstacleVision_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t holo_base_msg_obstacle_ObstacleVision_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_obstacle_ObstacleVision_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_obstacle_ObstacleVision_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
holo_base_msg_obstacle_ObstacleVisionTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const holo_base_msg_obstacle_ObstacleVision *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &holo_base_msg_obstacle_ObstacleVision_gv_ProgramNode,
        holo_base_msg_obstacle_ObstacleVision_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,holo_base_msg_obstacle_ObstacleVisionTypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        holo_base_msg_obstacle_ObstacleVision_gv_AutoRepresentation,
        holo_base_msg_obstacle_ObstacleVision_gv_XCDR1,
        holo_base_msg_obstacle_ObstacleVision_gv_XCDR2,
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
holo_base_msg_obstacle_ObstacleVisionTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const holo_base_msg_obstacle_ObstacleVision *a_data)
{
    return holo_base_msg_obstacle_ObstacleVisionTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
holo_base_msg_obstacle_ObstacleVisionTypeSupport_deserialize_data_from_cdr_buffer(
    holo_base_msg_obstacle_ObstacleVision *a_data,
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
        &holo_base_msg_obstacle_ObstacleVision_gv_ProgramNode,
        holo_base_msg_obstacle_ObstacleVision_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    holo_base_msg_obstacle_ObstacleVisionTypePlugin_get(),
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
#define TTYPENAME   holo_base_msg_obstacle_ObstacleVisionListTYPENAME

/* 
holo_base_msg_obstacle_ObstacleVisionListDataWriter (DDSDataWriter)   
*/

/* Defines */
#define TDataWriter holo_base_msg_obstacle_ObstacleVisionListDataWriter
#define TData       holo_base_msg_obstacle_ObstacleVisionList

#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatawriter_gen.hxx"
#endif

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_obstacle_ObstacleVisionListDataReader (DDSDataReader)   
*/

/* Defines */
#define TDataReader holo_base_msg_obstacle_ObstacleVisionListDataReader
#define TDataSeq    holo_base_msg_obstacle_ObstacleVisionListSeq
#define TData       holo_base_msg_obstacle_ObstacleVisionList
#ifdef __cplusplus
#include "dds_cpp/dds_cpp_tdatareader_gen.hxx"
#endif
#undef TDataReader
#undef TDataSeq
#undef TData

/* =========================================================================== */
/* 
holo_base_msg_obstacle_ObstacleVisionListTypeSupport

*/

#define TTypeSupport holo_base_msg_obstacle_ObstacleVisionListTypeSupport
#define TData        holo_base_msg_obstacle_ObstacleVisionList

static struct DDS_TypeProgramNode holo_base_msg_obstacle_ObstacleVisionList_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t holo_base_msg_obstacle_ObstacleVisionList_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_obstacle_ObstacleVisionList_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t holo_base_msg_obstacle_ObstacleVisionList_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t 
holo_base_msg_obstacle_ObstacleVisionListTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,                                
    unsigned int *length,                        
    const holo_base_msg_obstacle_ObstacleVisionList *a_data,                         
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        &holo_base_msg_obstacle_ObstacleVisionList_gv_ProgramNode,
        holo_base_msg_obstacle_ObstacleVisionList_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,holo_base_msg_obstacle_ObstacleVisionListTypePlugin_get(),
    programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        holo_base_msg_obstacle_ObstacleVisionList_gv_AutoRepresentation,
        holo_base_msg_obstacle_ObstacleVisionList_gv_XCDR1,
        holo_base_msg_obstacle_ObstacleVisionList_gv_XCDR2,
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
holo_base_msg_obstacle_ObstacleVisionListTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const holo_base_msg_obstacle_ObstacleVisionList *a_data)
{
    return holo_base_msg_obstacle_ObstacleVisionListTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,length,a_data,DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t 
holo_base_msg_obstacle_ObstacleVisionListTypeSupport_deserialize_data_from_cdr_buffer(
    holo_base_msg_obstacle_ObstacleVisionList *a_data,
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
        &holo_base_msg_obstacle_ObstacleVisionList_gv_ProgramNode,
        holo_base_msg_obstacle_ObstacleVisionList_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    DDS_TypePlugin_initialize_static(&tp,
    holo_base_msg_obstacle_ObstacleVisionListTypePlugin_get(),
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

