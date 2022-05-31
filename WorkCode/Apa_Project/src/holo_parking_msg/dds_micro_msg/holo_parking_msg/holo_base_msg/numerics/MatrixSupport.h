/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Matrix.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef MatrixSupport_41037854_h
#define MatrixSupport_41037854_h

#include <stdlib.h>

/* Uses */
#include "Matrix.h"
/* Requires */
#include "MatrixPlugin.h"

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)

/* If we're building on Windows, explicitly import the superclasses of
* the types declared below.
*/
class __declspec(dllimport) DDSDataWriter;
class __declspec(dllimport) DDSDataWriter_impl;
class __declspec(dllimport) DDSDataReader;
class __declspec(dllimport) DDSDataReader_impl;

#endif

/* ========================================================================== */
/**
Uses:     T
Defines:  TTypeSupport, TDataWriter, TDataReader*/

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

DDS_TYPESUPPORT_CPP(holo_base_msg_numerics_MatrixdTypeSupport, holo_base_msg_numerics_Matrixd);
DDS_DATAWRITER_CPP(holo_base_msg_numerics_MatrixdDataWriter, holo_base_msg_numerics_Matrixd);

DDS_DATAREADER_CPP(holo_base_msg_numerics_MatrixdDataReader, holo_base_msg_numerics_Matrixd);

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

/* ========================================================================== */
/**
Uses:     T
Defines:  TTypeSupport, TDataWriter, TDataReader*/

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

DDS_TYPESUPPORT_CPP(holo_base_msg_numerics_MatrixfTypeSupport, holo_base_msg_numerics_Matrixf);
DDS_DATAWRITER_CPP(holo_base_msg_numerics_MatrixfDataWriter, holo_base_msg_numerics_Matrixf);

DDS_DATAREADER_CPP(holo_base_msg_numerics_MatrixfDataReader, holo_base_msg_numerics_Matrixf);

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif  /* MatrixSupport_41037854_h */

