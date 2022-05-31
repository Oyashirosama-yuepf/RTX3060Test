/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Builtin.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef BuiltinSupport_1564184277_h
#define BuiltinSupport_1564184277_h

#include <stdlib.h>

/* Uses */
#include "Builtin.h"
/* Requires */
#include "BuiltinPlugin.h"

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

DDS_TYPESUPPORT_CPP(opendds_wrapper_BuiltinTimestampTypeSupport, opendds_wrapper_BuiltinTimestamp);
DDS_DATAWRITER_CPP(opendds_wrapper_BuiltinTimestampDataWriter, opendds_wrapper_BuiltinTimestamp);

DDS_DATAREADER_CPP(opendds_wrapper_BuiltinTimestampDataReader, opendds_wrapper_BuiltinTimestamp);

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

DDS_TYPESUPPORT_CPP(opendds_wrapper_BuiltinUint8TypeSupport, opendds_wrapper_BuiltinUint8);
DDS_DATAWRITER_CPP(opendds_wrapper_BuiltinUint8DataWriter, opendds_wrapper_BuiltinUint8);

DDS_DATAREADER_CPP(opendds_wrapper_BuiltinUint8DataReader, opendds_wrapper_BuiltinUint8);

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

DDS_TYPESUPPORT_CPP(opendds_wrapper_BuiltinUint16TypeSupport, opendds_wrapper_BuiltinUint16);
DDS_DATAWRITER_CPP(opendds_wrapper_BuiltinUint16DataWriter, opendds_wrapper_BuiltinUint16);

DDS_DATAREADER_CPP(opendds_wrapper_BuiltinUint16DataReader, opendds_wrapper_BuiltinUint16);

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

DDS_TYPESUPPORT_CPP(opendds_wrapper_BuiltinUint32TypeSupport, opendds_wrapper_BuiltinUint32);
DDS_DATAWRITER_CPP(opendds_wrapper_BuiltinUint32DataWriter, opendds_wrapper_BuiltinUint32);

DDS_DATAREADER_CPP(opendds_wrapper_BuiltinUint32DataReader, opendds_wrapper_BuiltinUint32);

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

DDS_TYPESUPPORT_CPP(opendds_wrapper_BuiltinUint64TypeSupport, opendds_wrapper_BuiltinUint64);
DDS_DATAWRITER_CPP(opendds_wrapper_BuiltinUint64DataWriter, opendds_wrapper_BuiltinUint64);

DDS_DATAREADER_CPP(opendds_wrapper_BuiltinUint64DataReader, opendds_wrapper_BuiltinUint64);

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

DDS_TYPESUPPORT_CPP(opendds_wrapper_BuiltinFloat32TypeSupport, opendds_wrapper_BuiltinFloat32);
DDS_DATAWRITER_CPP(opendds_wrapper_BuiltinFloat32DataWriter, opendds_wrapper_BuiltinFloat32);

DDS_DATAREADER_CPP(opendds_wrapper_BuiltinFloat32DataReader, opendds_wrapper_BuiltinFloat32);

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

DDS_TYPESUPPORT_CPP(opendds_wrapper_BuiltinFloat64TypeSupport, opendds_wrapper_BuiltinFloat64);
DDS_DATAWRITER_CPP(opendds_wrapper_BuiltinFloat64DataWriter, opendds_wrapper_BuiltinFloat64);

DDS_DATAREADER_CPP(opendds_wrapper_BuiltinFloat64DataReader, opendds_wrapper_BuiltinFloat64);

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

DDS_TYPESUPPORT_CPP(opendds_wrapper_BuiltinStringTypeSupport, opendds_wrapper_BuiltinString);
DDS_DATAWRITER_CPP(opendds_wrapper_BuiltinStringDataWriter, opendds_wrapper_BuiltinString);

DDS_DATAREADER_CPP(opendds_wrapper_BuiltinStringDataReader, opendds_wrapper_BuiltinString);

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

DDS_TYPESUPPORT_CPP(opendds_wrapper_BuiltinBufferTypeSupport, opendds_wrapper_BuiltinBuffer);
DDS_DATAWRITER_CPP(opendds_wrapper_BuiltinBufferDataWriter, opendds_wrapper_BuiltinBuffer);

DDS_DATAREADER_CPP(opendds_wrapper_BuiltinBufferDataReader, opendds_wrapper_BuiltinBuffer);

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif  /* BuiltinSupport_1564184277_h */

