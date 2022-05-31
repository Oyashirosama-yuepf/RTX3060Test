/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Pose.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef PoseSupport_806669959_h
#define PoseSupport_806669959_h

#include <stdlib.h>

/* Uses */
#include "Pose.h"
/* Requires */
#include "PosePlugin.h"

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

DDS_TYPESUPPORT_CPP(holo_base_msg_geometry_Pose3fTypeSupport, holo_base_msg_geometry_Pose3f);
DDS_DATAWRITER_CPP(holo_base_msg_geometry_Pose3fDataWriter, holo_base_msg_geometry_Pose3f);

DDS_DATAREADER_CPP(holo_base_msg_geometry_Pose3fDataReader, holo_base_msg_geometry_Pose3f);

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

DDS_TYPESUPPORT_CPP(holo_base_msg_geometry_Pose3dTypeSupport, holo_base_msg_geometry_Pose3d);
DDS_DATAWRITER_CPP(holo_base_msg_geometry_Pose3dDataWriter, holo_base_msg_geometry_Pose3d);

DDS_DATAREADER_CPP(holo_base_msg_geometry_Pose3dDataReader, holo_base_msg_geometry_Pose3d);

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

DDS_TYPESUPPORT_CPP(holo_base_msg_geometry_Pose2fTypeSupport, holo_base_msg_geometry_Pose2f);
DDS_DATAWRITER_CPP(holo_base_msg_geometry_Pose2fDataWriter, holo_base_msg_geometry_Pose2f);

DDS_DATAREADER_CPP(holo_base_msg_geometry_Pose2fDataReader, holo_base_msg_geometry_Pose2f);

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

DDS_TYPESUPPORT_CPP(holo_base_msg_geometry_Pose2dTypeSupport, holo_base_msg_geometry_Pose2d);
DDS_DATAWRITER_CPP(holo_base_msg_geometry_Pose2dDataWriter, holo_base_msg_geometry_Pose2d);

DDS_DATAREADER_CPP(holo_base_msg_geometry_Pose2dDataReader, holo_base_msg_geometry_Pose2d);

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif  /* PoseSupport_806669959_h */

