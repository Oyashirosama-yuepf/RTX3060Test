/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Freespace.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef FreespaceSupport_1959326732_h
#define FreespaceSupport_1959326732_h

#include <stdlib.h>

/* Uses */
#include "Freespace.h"
/* Requires */
#include "FreespacePlugin.h"

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

DDS_TYPESUPPORT_CPP(holo_base_msg_common_freespace3f_SegmentInfoTypeSupport, holo_base_msg_common_freespace3f_SegmentInfo);
DDS_DATAWRITER_CPP(holo_base_msg_common_freespace3f_SegmentInfoDataWriter, holo_base_msg_common_freespace3f_SegmentInfo);

DDS_DATAREADER_CPP(holo_base_msg_common_freespace3f_SegmentInfoDataReader, holo_base_msg_common_freespace3f_SegmentInfo);

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

DDS_TYPESUPPORT_CPP(holo_base_msg_common_freespace3f_FreespaceInteriorTypeSupport, holo_base_msg_common_freespace3f_FreespaceInterior);
DDS_DATAWRITER_CPP(holo_base_msg_common_freespace3f_FreespaceInteriorDataWriter, holo_base_msg_common_freespace3f_FreespaceInterior);

DDS_DATAREADER_CPP(holo_base_msg_common_freespace3f_FreespaceInteriorDataReader, holo_base_msg_common_freespace3f_FreespaceInterior);

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

DDS_TYPESUPPORT_CPP(holo_base_msg_common_freespace3f_FreespaceExteriorTypeSupport, holo_base_msg_common_freespace3f_FreespaceExterior);
DDS_DATAWRITER_CPP(holo_base_msg_common_freespace3f_FreespaceExteriorDataWriter, holo_base_msg_common_freespace3f_FreespaceExterior);

DDS_DATAREADER_CPP(holo_base_msg_common_freespace3f_FreespaceExteriorDataReader, holo_base_msg_common_freespace3f_FreespaceExterior);

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

DDS_TYPESUPPORT_CPP(holo_base_msg_common_freespace3f_FreespaceTypeSupport, holo_base_msg_common_freespace3f_Freespace);
DDS_DATAWRITER_CPP(holo_base_msg_common_freespace3f_FreespaceDataWriter, holo_base_msg_common_freespace3f_Freespace);

DDS_DATAREADER_CPP(holo_base_msg_common_freespace3f_FreespaceDataReader, holo_base_msg_common_freespace3f_Freespace);

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif  /* FreespaceSupport_1959326732_h */

