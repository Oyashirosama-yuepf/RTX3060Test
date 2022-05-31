/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Rot.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef RotSupport_1247671481_h
#define RotSupport_1247671481_h

#include <stdlib.h>

/* Uses */
#include "Rot.h"
/* Requires */
#include "RotPlugin.h"

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

DDS_TYPESUPPORT_CPP(holo_base_msg_geometry_Rot2fTypeSupport, holo_base_msg_geometry_Rot2f);
DDS_DATAWRITER_CPP(holo_base_msg_geometry_Rot2fDataWriter, holo_base_msg_geometry_Rot2f);

DDS_DATAREADER_CPP(holo_base_msg_geometry_Rot2fDataReader, holo_base_msg_geometry_Rot2f);

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

DDS_TYPESUPPORT_CPP(holo_base_msg_geometry_Rot2dTypeSupport, holo_base_msg_geometry_Rot2d);
DDS_DATAWRITER_CPP(holo_base_msg_geometry_Rot2dDataWriter, holo_base_msg_geometry_Rot2d);

DDS_DATAREADER_CPP(holo_base_msg_geometry_Rot2dDataReader, holo_base_msg_geometry_Rot2d);

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

DDS_TYPESUPPORT_CPP(holo_base_msg_geometry_Rot3fTypeSupport, holo_base_msg_geometry_Rot3f);
DDS_DATAWRITER_CPP(holo_base_msg_geometry_Rot3fDataWriter, holo_base_msg_geometry_Rot3f);

DDS_DATAREADER_CPP(holo_base_msg_geometry_Rot3fDataReader, holo_base_msg_geometry_Rot3f);

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

DDS_TYPESUPPORT_CPP(holo_base_msg_geometry_Rot3dTypeSupport, holo_base_msg_geometry_Rot3d);
DDS_DATAWRITER_CPP(holo_base_msg_geometry_Rot3dDataWriter, holo_base_msg_geometry_Rot3d);

DDS_DATAREADER_CPP(holo_base_msg_geometry_Rot3dDataReader, holo_base_msg_geometry_Rot3d);

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif  /* RotSupport_1247671481_h */

