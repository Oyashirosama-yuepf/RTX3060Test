/* -*- C++ -*- */
/* Generated by /home/holo/workspace/output/tda4_ubuntu-18.04/debug/host/bin/opendds_idl version 3.16 (ACE version 6.2a_p19) running on input file /home/holo/workspace/src/holo_base_msg/opendds_msg/message/holo_base_msg/numerics/Vector.idl */
#ifndef OPENDDS_IDL_GENERATED_VECTORTYPESUPPORTIMPL_H_KWVH7H
#define OPENDDS_IDL_GENERATED_VECTORTYPESUPPORTIMPL_H_KWVH7H
#include "VectorC.h"
#include "dds/DCPS/Definitions.h"
#include "dds/DdsDcpsC.h"
#include "dds/Version.h"
#if DDS_MAJOR_VERSION != 3 || DDS_MINOR_VERSION != 16 || DDS_MICRO_VERSION != 0
#error This file should be regenerated with opendds_idl
#endif
#include "dds/DCPS/Serializer.h"
#include "dds/DCPS/XTypes/TypeObject.h"
#include "holo_base_msg/core/TypesC.h"
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL



/* Begin MODULE: CORBA */


/* End MODULE: CORBA */


/* Begin MODULE: OpenDDS */


/* End MODULE: OpenDDS */


/* Begin MODULE: holo_base_msg */



/* Begin MODULE: core */



/* Begin TYPEDEF: bool_t */


/* End TYPEDEF: bool_t */


/* Begin TYPEDEF: char_t */


/* End TYPEDEF: char_t */


/* Begin TYPEDEF: _cxx_wchar_t */


/* End TYPEDEF: _cxx_wchar_t */


/* Begin TYPEDEF: int8_t */


/* End TYPEDEF: int8_t */


/* Begin TYPEDEF: uint8_t */


/* End TYPEDEF: uint8_t */


/* Begin TYPEDEF: int16_t */


/* End TYPEDEF: int16_t */


/* Begin TYPEDEF: uint16_t */


/* End TYPEDEF: uint16_t */


/* Begin TYPEDEF: int32_t */


/* End TYPEDEF: int32_t */


/* Begin TYPEDEF: uint32_t */


/* End TYPEDEF: uint32_t */


/* Begin TYPEDEF: int64_t */


/* End TYPEDEF: int64_t */


/* Begin TYPEDEF: uint64_t */


/* End TYPEDEF: uint64_t */


/* Begin TYPEDEF: float32_t */


/* End TYPEDEF: float32_t */


/* Begin TYPEDEF: float64_t */


/* End TYPEDEF: float64_t */


/* Begin TYPEDEF: BoolSequence */


/* End TYPEDEF: BoolSequence */


/* Begin TYPEDEF: CharSequence */


/* End TYPEDEF: CharSequence */


/* Begin TYPEDEF: WcharSequence */


/* End TYPEDEF: WcharSequence */


/* Begin TYPEDEF: Int8Sequence */


/* End TYPEDEF: Int8Sequence */


/* Begin TYPEDEF: Uint8Sequence */


/* End TYPEDEF: Uint8Sequence */


/* Begin TYPEDEF: Int16Sequence */


/* End TYPEDEF: Int16Sequence */


/* Begin TYPEDEF: Uint16Sequence */


/* End TYPEDEF: Uint16Sequence */


/* Begin TYPEDEF: Int32Sequence */


/* End TYPEDEF: Int32Sequence */


/* Begin TYPEDEF: Uint32Sequence */


/* End TYPEDEF: Uint32Sequence */


/* Begin TYPEDEF: Int64Sequence */


/* End TYPEDEF: Int64Sequence */


/* Begin TYPEDEF: Uint64Sequence */


/* End TYPEDEF: Uint64Sequence */


/* Begin TYPEDEF: Float32Sequence */


/* End TYPEDEF: Float32Sequence */


/* Begin TYPEDEF: Float64Sequence */


/* End TYPEDEF: Float64Sequence */

/* End MODULE: core */

/* End MODULE: holo_base_msg */


/* Begin MODULE: holo_base_msg */



/* Begin MODULE: numerics */



/* Begin TYPEDEF: Vectord */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::numerics::Vectord& seq);

bool operator<<(Serializer& strm, const holo_base_msg::numerics::Vectord& seq);

bool operator>>(Serializer& strm, holo_base_msg::numerics::Vectord& seq);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

bool gen_skip_over(Serializer& ser, holo_base_msg::numerics::Vectord*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_numerics_Vectord_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_numerics_Vectord_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_numerics_Vectord_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End TYPEDEF: Vectord */


/* Begin TYPEDEF: Vector2d */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void set_default(holo_base_msg::numerics::Vector2d_forany& arr);

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::numerics::Vector2d_forany& arr);

bool operator<<(Serializer& strm, const holo_base_msg::numerics::Vector2d_forany& arr);

bool operator>>(Serializer& strm, holo_base_msg::numerics::Vector2d_forany& arr);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

bool gen_skip_over(Serializer& ser, holo_base_msg::numerics::Vector2d_forany*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_numerics_Vector2d_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_numerics_Vector2d_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_numerics_Vector2d_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End TYPEDEF: Vector2d */


/* Begin TYPEDEF: Vector3d */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void set_default(holo_base_msg::numerics::Vector3d_forany& arr);

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::numerics::Vector3d_forany& arr);

bool operator<<(Serializer& strm, const holo_base_msg::numerics::Vector3d_forany& arr);

bool operator>>(Serializer& strm, holo_base_msg::numerics::Vector3d_forany& arr);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

bool gen_skip_over(Serializer& ser, holo_base_msg::numerics::Vector3d_forany*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_numerics_Vector3d_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_numerics_Vector3d_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_numerics_Vector3d_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End TYPEDEF: Vector3d */


/* Begin TYPEDEF: Vector4d */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void set_default(holo_base_msg::numerics::Vector4d_forany& arr);

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::numerics::Vector4d_forany& arr);

bool operator<<(Serializer& strm, const holo_base_msg::numerics::Vector4d_forany& arr);

bool operator>>(Serializer& strm, holo_base_msg::numerics::Vector4d_forany& arr);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

bool gen_skip_over(Serializer& ser, holo_base_msg::numerics::Vector4d_forany*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_numerics_Vector4d_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_numerics_Vector4d_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_numerics_Vector4d_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End TYPEDEF: Vector4d */


/* Begin TYPEDEF: Vector5d */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void set_default(holo_base_msg::numerics::Vector5d_forany& arr);

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::numerics::Vector5d_forany& arr);

bool operator<<(Serializer& strm, const holo_base_msg::numerics::Vector5d_forany& arr);

bool operator>>(Serializer& strm, holo_base_msg::numerics::Vector5d_forany& arr);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

bool gen_skip_over(Serializer& ser, holo_base_msg::numerics::Vector5d_forany*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_numerics_Vector5d_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_numerics_Vector5d_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_numerics_Vector5d_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End TYPEDEF: Vector5d */


/* Begin TYPEDEF: Vector6d */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void set_default(holo_base_msg::numerics::Vector6d_forany& arr);

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::numerics::Vector6d_forany& arr);

bool operator<<(Serializer& strm, const holo_base_msg::numerics::Vector6d_forany& arr);

bool operator>>(Serializer& strm, holo_base_msg::numerics::Vector6d_forany& arr);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

bool gen_skip_over(Serializer& ser, holo_base_msg::numerics::Vector6d_forany*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_numerics_Vector6d_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_numerics_Vector6d_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_numerics_Vector6d_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End TYPEDEF: Vector6d */


/* Begin TYPEDEF: Vector7d */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void set_default(holo_base_msg::numerics::Vector7d_forany& arr);

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::numerics::Vector7d_forany& arr);

bool operator<<(Serializer& strm, const holo_base_msg::numerics::Vector7d_forany& arr);

bool operator>>(Serializer& strm, holo_base_msg::numerics::Vector7d_forany& arr);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

bool gen_skip_over(Serializer& ser, holo_base_msg::numerics::Vector7d_forany*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_numerics_Vector7d_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_numerics_Vector7d_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_numerics_Vector7d_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End TYPEDEF: Vector7d */


/* Begin TYPEDEF: Vector8d */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void set_default(holo_base_msg::numerics::Vector8d_forany& arr);

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::numerics::Vector8d_forany& arr);

bool operator<<(Serializer& strm, const holo_base_msg::numerics::Vector8d_forany& arr);

bool operator>>(Serializer& strm, holo_base_msg::numerics::Vector8d_forany& arr);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

bool gen_skip_over(Serializer& ser, holo_base_msg::numerics::Vector8d_forany*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_numerics_Vector8d_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_numerics_Vector8d_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_numerics_Vector8d_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End TYPEDEF: Vector8d */


/* Begin TYPEDEF: Vectorf */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::numerics::Vectorf& seq);

bool operator<<(Serializer& strm, const holo_base_msg::numerics::Vectorf& seq);

bool operator>>(Serializer& strm, holo_base_msg::numerics::Vectorf& seq);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

bool gen_skip_over(Serializer& ser, holo_base_msg::numerics::Vectorf*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_numerics_Vectorf_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_numerics_Vectorf_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_numerics_Vectorf_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End TYPEDEF: Vectorf */


/* Begin TYPEDEF: Vector2f */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void set_default(holo_base_msg::numerics::Vector2f_forany& arr);

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::numerics::Vector2f_forany& arr);

bool operator<<(Serializer& strm, const holo_base_msg::numerics::Vector2f_forany& arr);

bool operator>>(Serializer& strm, holo_base_msg::numerics::Vector2f_forany& arr);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

bool gen_skip_over(Serializer& ser, holo_base_msg::numerics::Vector2f_forany*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_numerics_Vector2f_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_numerics_Vector2f_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_numerics_Vector2f_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End TYPEDEF: Vector2f */


/* Begin TYPEDEF: Vector3f */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void set_default(holo_base_msg::numerics::Vector3f_forany& arr);

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::numerics::Vector3f_forany& arr);

bool operator<<(Serializer& strm, const holo_base_msg::numerics::Vector3f_forany& arr);

bool operator>>(Serializer& strm, holo_base_msg::numerics::Vector3f_forany& arr);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

bool gen_skip_over(Serializer& ser, holo_base_msg::numerics::Vector3f_forany*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_numerics_Vector3f_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_numerics_Vector3f_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_numerics_Vector3f_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End TYPEDEF: Vector3f */


/* Begin TYPEDEF: Vector4f */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void set_default(holo_base_msg::numerics::Vector4f_forany& arr);

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::numerics::Vector4f_forany& arr);

bool operator<<(Serializer& strm, const holo_base_msg::numerics::Vector4f_forany& arr);

bool operator>>(Serializer& strm, holo_base_msg::numerics::Vector4f_forany& arr);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

bool gen_skip_over(Serializer& ser, holo_base_msg::numerics::Vector4f_forany*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_numerics_Vector4f_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_numerics_Vector4f_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_numerics_Vector4f_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End TYPEDEF: Vector4f */


/* Begin TYPEDEF: Vector5f */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void set_default(holo_base_msg::numerics::Vector5f_forany& arr);

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::numerics::Vector5f_forany& arr);

bool operator<<(Serializer& strm, const holo_base_msg::numerics::Vector5f_forany& arr);

bool operator>>(Serializer& strm, holo_base_msg::numerics::Vector5f_forany& arr);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

bool gen_skip_over(Serializer& ser, holo_base_msg::numerics::Vector5f_forany*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_numerics_Vector5f_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_numerics_Vector5f_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_numerics_Vector5f_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End TYPEDEF: Vector5f */


/* Begin TYPEDEF: Vector6f */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void set_default(holo_base_msg::numerics::Vector6f_forany& arr);

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::numerics::Vector6f_forany& arr);

bool operator<<(Serializer& strm, const holo_base_msg::numerics::Vector6f_forany& arr);

bool operator>>(Serializer& strm, holo_base_msg::numerics::Vector6f_forany& arr);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

bool gen_skip_over(Serializer& ser, holo_base_msg::numerics::Vector6f_forany*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_numerics_Vector6f_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_numerics_Vector6f_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_numerics_Vector6f_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End TYPEDEF: Vector6f */


/* Begin TYPEDEF: Vector7f */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void set_default(holo_base_msg::numerics::Vector7f_forany& arr);

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::numerics::Vector7f_forany& arr);

bool operator<<(Serializer& strm, const holo_base_msg::numerics::Vector7f_forany& arr);

bool operator>>(Serializer& strm, holo_base_msg::numerics::Vector7f_forany& arr);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

bool gen_skip_over(Serializer& ser, holo_base_msg::numerics::Vector7f_forany*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_numerics_Vector7f_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_numerics_Vector7f_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_numerics_Vector7f_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End TYPEDEF: Vector7f */


/* Begin TYPEDEF: Vector8f */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void set_default(holo_base_msg::numerics::Vector8f_forany& arr);

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::numerics::Vector8f_forany& arr);

bool operator<<(Serializer& strm, const holo_base_msg::numerics::Vector8f_forany& arr);

bool operator>>(Serializer& strm, holo_base_msg::numerics::Vector8f_forany& arr);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

bool gen_skip_over(Serializer& ser, holo_base_msg::numerics::Vector8f_forany*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_numerics_Vector8f_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_numerics_Vector8f_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_numerics_Vector8f_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End TYPEDEF: Vector8f */

/* End MODULE: numerics */

/* End MODULE: holo_base_msg */
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif /* OPENDDS_IDL_GENERATED_VECTORTYPESUPPORTIMPL_H_KWVH7H */