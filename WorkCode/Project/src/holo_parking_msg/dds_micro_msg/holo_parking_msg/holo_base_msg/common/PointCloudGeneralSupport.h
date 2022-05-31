/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from PointCloudGeneral.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef PointCloudGeneralSupport_963373545_h
#define PointCloudGeneralSupport_963373545_h

#include <stdlib.h>

/* Uses */
#include "PointCloudGeneral.h"
/* Requires */
#include "PointCloudGeneralPlugin.h"

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

DDS_TYPESUPPORT_CPP(holo_base_msg_common_PointXYZRGBTypeSupport, holo_base_msg_common_PointXYZRGB);
DDS_DATAWRITER_CPP(holo_base_msg_common_PointXYZRGBDataWriter, holo_base_msg_common_PointXYZRGB);

DDS_DATAREADER_CPP(holo_base_msg_common_PointXYZRGBDataReader, holo_base_msg_common_PointXYZRGB);

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

DDS_TYPESUPPORT_CPP(holo_base_msg_common_PointCloudGeneralTypeSupport, holo_base_msg_common_PointCloudGeneral);
DDS_DATAWRITER_CPP(holo_base_msg_common_PointCloudGeneralDataWriter, holo_base_msg_common_PointCloudGeneral);

DDS_DATAREADER_CPP(holo_base_msg_common_PointCloudGeneralDataReader, holo_base_msg_common_PointCloudGeneral);

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif  /* PointCloudGeneralSupport_963373545_h */

