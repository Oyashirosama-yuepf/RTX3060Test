/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ParkingSlot.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef ParkingSlotSupport_1960983127_h
#define ParkingSlotSupport_1960983127_h

#include <stdlib.h>

/* Uses */
#include "ParkingSlot.h"
/* Requires */
#include "ParkingSlotPlugin.h"

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

DDS_TYPESUPPORT_CPP(holo_base_msg_common_ParkingSlotfTypeSupport, holo_base_msg_common_ParkingSlotf);
DDS_DATAWRITER_CPP(holo_base_msg_common_ParkingSlotfDataWriter, holo_base_msg_common_ParkingSlotf);

DDS_DATAREADER_CPP(holo_base_msg_common_ParkingSlotfDataReader, holo_base_msg_common_ParkingSlotf);

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

DDS_TYPESUPPORT_CPP(holo_base_msg_common_ParkingSlotdTypeSupport, holo_base_msg_common_ParkingSlotd);
DDS_DATAWRITER_CPP(holo_base_msg_common_ParkingSlotdDataWriter, holo_base_msg_common_ParkingSlotd);

DDS_DATAREADER_CPP(holo_base_msg_common_ParkingSlotdDataReader, holo_base_msg_common_ParkingSlotd);

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

DDS_TYPESUPPORT_CPP(holo_base_msg_common_ParkingSlotFramefTypeSupport, holo_base_msg_common_ParkingSlotFramef);
DDS_DATAWRITER_CPP(holo_base_msg_common_ParkingSlotFramefDataWriter, holo_base_msg_common_ParkingSlotFramef);

DDS_DATAREADER_CPP(holo_base_msg_common_ParkingSlotFramefDataReader, holo_base_msg_common_ParkingSlotFramef);

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

DDS_TYPESUPPORT_CPP(holo_base_msg_common_ParkingSlotFramedTypeSupport, holo_base_msg_common_ParkingSlotFramed);
DDS_DATAWRITER_CPP(holo_base_msg_common_ParkingSlotFramedDataWriter, holo_base_msg_common_ParkingSlotFramed);

DDS_DATAREADER_CPP(holo_base_msg_common_ParkingSlotFramedDataReader, holo_base_msg_common_ParkingSlotFramed);

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif  /* ParkingSlotSupport_1960983127_h */

