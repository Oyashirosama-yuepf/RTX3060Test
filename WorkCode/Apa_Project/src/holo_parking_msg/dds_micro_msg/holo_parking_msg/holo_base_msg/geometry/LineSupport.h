/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Line.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef LineSupport_1252162399_h
#define LineSupport_1252162399_h

#include <stdlib.h>

/* Uses */
#include "Line.h"
/* Requires */
#include "LinePlugin.h"

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

DDS_TYPESUPPORT_CPP(holo_base_msg_geometry_Line2fTypeSupport, holo_base_msg_geometry_Line2f);
DDS_DATAWRITER_CPP(holo_base_msg_geometry_Line2fDataWriter, holo_base_msg_geometry_Line2f);

DDS_DATAREADER_CPP(holo_base_msg_geometry_Line2fDataReader, holo_base_msg_geometry_Line2f);

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

DDS_TYPESUPPORT_CPP(holo_base_msg_geometry_Line2dTypeSupport, holo_base_msg_geometry_Line2d);
DDS_DATAWRITER_CPP(holo_base_msg_geometry_Line2dDataWriter, holo_base_msg_geometry_Line2d);

DDS_DATAREADER_CPP(holo_base_msg_geometry_Line2dDataReader, holo_base_msg_geometry_Line2d);

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif  /* LineSupport_1252162399_h */

