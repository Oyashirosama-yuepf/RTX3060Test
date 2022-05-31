/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Point.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef PointSupport_727602850_h
#define PointSupport_727602850_h

#include <stdlib.h>

/* Uses */
#include "Point.h"
/* Requires */
#include "PointPlugin.h"

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

DDS_TYPESUPPORT_CPP(holo_base_msg_geometry_Point3fTypeSupport, holo_base_msg_geometry_Point3f);
DDS_DATAWRITER_CPP(holo_base_msg_geometry_Point3fDataWriter, holo_base_msg_geometry_Point3f);

DDS_DATAREADER_CPP(holo_base_msg_geometry_Point3fDataReader, holo_base_msg_geometry_Point3f);

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

DDS_TYPESUPPORT_CPP(holo_base_msg_geometry_Point3dTypeSupport, holo_base_msg_geometry_Point3d);
DDS_DATAWRITER_CPP(holo_base_msg_geometry_Point3dDataWriter, holo_base_msg_geometry_Point3d);

DDS_DATAREADER_CPP(holo_base_msg_geometry_Point3dDataReader, holo_base_msg_geometry_Point3d);

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

DDS_TYPESUPPORT_CPP(holo_base_msg_geometry_Point2fTypeSupport, holo_base_msg_geometry_Point2f);
DDS_DATAWRITER_CPP(holo_base_msg_geometry_Point2fDataWriter, holo_base_msg_geometry_Point2f);

DDS_DATAREADER_CPP(holo_base_msg_geometry_Point2fDataReader, holo_base_msg_geometry_Point2f);

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

DDS_TYPESUPPORT_CPP(holo_base_msg_geometry_Point2dTypeSupport, holo_base_msg_geometry_Point2d);
DDS_DATAWRITER_CPP(holo_base_msg_geometry_Point2dDataWriter, holo_base_msg_geometry_Point2d);

DDS_DATAREADER_CPP(holo_base_msg_geometry_Point2dDataReader, holo_base_msg_geometry_Point2d);

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif  /* PointSupport_727602850_h */

