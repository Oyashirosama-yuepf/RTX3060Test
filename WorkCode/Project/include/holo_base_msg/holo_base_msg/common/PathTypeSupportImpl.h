/* -*- C++ -*- */
/* Generated by /home/holo/workspace/output/tda4_ubuntu-18.04/debug/host/bin/opendds_idl version 3.16 (ACE version 6.2a_p19) running on input file /home/holo/workspace/src/holo_base_msg/opendds_msg/message/holo_base_msg/common/Path.idl */
#ifndef OPENDDS_IDL_GENERATED_PATHTYPESUPPORTIMPL_H_FSLYFP
#define OPENDDS_IDL_GENERATED_PATHTYPESUPPORTIMPL_H_FSLYFP
#include "PathC.h"
#include "dds/DCPS/Definitions.h"
#include "dds/DdsDcpsC.h"
#include "dds/Version.h"
#if DDS_MAJOR_VERSION != 3 || DDS_MINOR_VERSION != 16 || DDS_MICRO_VERSION != 0
#error This file should be regenerated with opendds_idl
#endif
#include "PathTypeSupportC.h"
#include "dds/DCPS/Serializer.h"
#include "dds/DCPS/TypeSupportImpl.h"
#include "dds/DCPS/ValueWriter.h"
#include "dds/DCPS/XTypes/TypeObject.h"
#include "holo_base_msg/common/CommonC.h"
#include "holo_base_msg/core/TypesC.h"
#include "holo_base_msg/geometry/PointC.h"
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



/* Begin MODULE: common */



/* Begin TYPEDEF: Coordinate */


/* End TYPEDEF: Coordinate */


/* Begin TYPEDEF: SensorId */


/* End TYPEDEF: SensorId */


/* Begin TYPEDEF: Classification */


/* End TYPEDEF: Classification */


/* Begin STRUCT: Duration */


/* End STRUCT: Duration */


/* Begin STRUCT: Timestamp */


/* End STRUCT: Timestamp */

/* End MODULE: common */

/* End MODULE: holo_base_msg */


/* Begin MODULE: holo_base_msg */



/* Begin MODULE: geometry */



/* Begin STRUCT: Point3f */


/* End STRUCT: Point3f */


/* Begin TYPEDEF: Point3fSequence */


/* End TYPEDEF: Point3fSequence */


/* Begin STRUCT: Point3d */


/* End STRUCT: Point3d */


/* Begin TYPEDEF: Point3dSequence */


/* End TYPEDEF: Point3dSequence */


/* Begin STRUCT: Point2f */


/* End STRUCT: Point2f */


/* Begin TYPEDEF: Point2fSequence */


/* End TYPEDEF: Point2fSequence */


/* Begin STRUCT: Point2d */


/* End STRUCT: Point2d */


/* Begin TYPEDEF: Point2dSequence */


/* End TYPEDEF: Point2dSequence */

/* End MODULE: geometry */

/* End MODULE: holo_base_msg */


/* Begin MODULE: holo_base_msg */



/* Begin MODULE: common */



/* Begin STRUCT: PathPointf */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void set_default(holo_base_msg::common::PathPointf& stru);

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::common::PathPointf& stru);

bool operator<<(Serializer& strm, const holo_base_msg::common::PathPointf& stru);

bool operator>>(Serializer& strm, holo_base_msg::common::PathPointf& stru);

void serialized_size(const Encoding& encoding, size_t& size, const NestedKeyOnly<const holo_base_msg::common::PathPointf>& stru);

bool operator<<(Serializer& strm, const NestedKeyOnly<const holo_base_msg::common::PathPointf>& stru);

bool operator>>(Serializer& strm, const NestedKeyOnly<holo_base_msg::common::PathPointf>& stru);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void vwrite(OpenDDS::DCPS::ValueWriter& value_writer, const holo_base_msg::common::PathPointf& value);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

class MetaStruct;

template<typename T>
const MetaStruct& getMetaStruct();

template<>
const MetaStruct& getMetaStruct<holo_base_msg::common::PathPointf>();
bool gen_skip_over(Serializer& ser, holo_base_msg::common::PathPointf*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_common_PathPointf_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_common_PathPointf_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_common_PathPointf_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End STRUCT: PathPointf */


/* Begin STRUCT: PathPointd */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void set_default(holo_base_msg::common::PathPointd& stru);

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::common::PathPointd& stru);

bool operator<<(Serializer& strm, const holo_base_msg::common::PathPointd& stru);

bool operator>>(Serializer& strm, holo_base_msg::common::PathPointd& stru);

void serialized_size(const Encoding& encoding, size_t& size, const NestedKeyOnly<const holo_base_msg::common::PathPointd>& stru);

bool operator<<(Serializer& strm, const NestedKeyOnly<const holo_base_msg::common::PathPointd>& stru);

bool operator>>(Serializer& strm, const NestedKeyOnly<holo_base_msg::common::PathPointd>& stru);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void vwrite(OpenDDS::DCPS::ValueWriter& value_writer, const holo_base_msg::common::PathPointd& value);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

template<>
const MetaStruct& getMetaStruct<holo_base_msg::common::PathPointd>();
bool gen_skip_over(Serializer& ser, holo_base_msg::common::PathPointd*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_common_PathPointd_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_common_PathPointd_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_common_PathPointd_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End STRUCT: PathPointd */


/* Begin TYPEDEF: PathPointfSequence */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::common::PathPointfSequence& seq);

bool operator<<(Serializer& strm, const holo_base_msg::common::PathPointfSequence& seq);

bool operator>>(Serializer& strm, holo_base_msg::common::PathPointfSequence& seq);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

bool gen_skip_over(Serializer& ser, holo_base_msg::common::PathPointfSequence*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_common_PathPointfSequence_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_common_PathPointfSequence_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_common_PathPointfSequence_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End TYPEDEF: PathPointfSequence */


/* Begin TYPEDEF: PathPointdSequence */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::common::PathPointdSequence& seq);

bool operator<<(Serializer& strm, const holo_base_msg::common::PathPointdSequence& seq);

bool operator>>(Serializer& strm, holo_base_msg::common::PathPointdSequence& seq);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

bool gen_skip_over(Serializer& ser, holo_base_msg::common::PathPointdSequence*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_common_PathPointdSequence_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_common_PathPointdSequence_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_common_PathPointdSequence_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End TYPEDEF: PathPointdSequence */


/* Begin STRUCT: Pathf */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void set_default(holo_base_msg::common::Pathf& stru);

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::common::Pathf& stru);

bool operator<<(Serializer& strm, const holo_base_msg::common::Pathf& stru);

bool operator>>(Serializer& strm, holo_base_msg::common::Pathf& stru);

void serialized_size(const Encoding& encoding, size_t& size, const NestedKeyOnly<const holo_base_msg::common::Pathf>& stru);

bool operator<<(Serializer& strm, const NestedKeyOnly<const holo_base_msg::common::Pathf>& stru);

bool operator>>(Serializer& strm, const NestedKeyOnly<holo_base_msg::common::Pathf>& stru);

template <>
struct MarshalTraits<holo_base_msg::common::Pathf> {
  static void representations_allowed_by_type(DDS::DataRepresentationIdSeq& seq)
  {
    seq.length(3);
    seq[0] = DDS::XCDR_DATA_REPRESENTATION;
    seq[1] = DDS::XCDR2_DATA_REPRESENTATION;
    seq[2] = DDS::XML_DATA_REPRESENTATION;
  }

  static SerializedSizeBound serialized_size_bound(const Encoding& encoding)
  {
    switch (encoding.kind()) {
    case Encoding::KIND_UNALIGNED_CDR:
      return SerializedSizeBound();
    case Encoding::KIND_XCDR1:
      return SerializedSizeBound();
    case Encoding::KIND_XCDR2:
      return SerializedSizeBound();
    default:
      OPENDDS_ASSERT(false);
      return SerializedSizeBound();
    }
  }

  static SerializedSizeBound key_only_serialized_size_bound(const Encoding& encoding)
  {
    switch (encoding.kind()) {
    case Encoding::KIND_UNALIGNED_CDR:
      return SerializedSizeBound(0);
    case Encoding::KIND_XCDR1:
      return SerializedSizeBound();
    case Encoding::KIND_XCDR2:
      return SerializedSizeBound();
    default:
      OPENDDS_ASSERT(false);
      return SerializedSizeBound();
    }
  }

  static bool to_message_block(ACE_Message_Block&, const holo_base_msg::common::Pathf&) { return false; }
  static bool from_message_block(holo_base_msg::common::Pathf&, const ACE_Message_Block&) { return false; }
  static Extensibility extensibility() { return APPENDABLE; }
  static Extensibility max_extensibility_level() { return APPENDABLE; }
};
void serialized_size(const Encoding& encoding, size_t& size, const KeyOnly<const holo_base_msg::common::Pathf> stru);

bool operator<<(Serializer& strm, KeyOnly<const holo_base_msg::common::Pathf> stru);

bool operator>>(Serializer& strm, KeyOnly<holo_base_msg::common::Pathf> stru);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
/// This structure supports use of std::map with one or more keys.
struct  Pathf_OpenDDS_KeyLessThan {
  bool operator()(const holo_base_msg::common::Pathf&, const holo_base_msg::common::Pathf&) const
  {
    // With no keys, return false to allow use of
    // map with just one entry
    return false;
  }
};
}
}

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void vwrite(OpenDDS::DCPS::ValueWriter& value_writer, const holo_base_msg::common::Pathf& value);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
class PathfTypeSupportImpl;
}
}

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS {
namespace DCPS {
template <>
struct DDSTraits<holo_base_msg::common::Pathf> {
  typedef holo_base_msg::common::Pathf MessageType;
  typedef holo_base_msg::common::PathfSeq MessageSequenceType;
  typedef holo_base_msg::common::PathfTypeSupport TypeSupportType;
  typedef holo_base_msg::common::PathfTypeSupportImpl TypeSupportTypeImpl;
  typedef holo_base_msg::common::PathfDataWriter DataWriterType;
  typedef holo_base_msg::common::PathfDataReader DataReaderType;
  typedef holo_base_msg::common::Pathf_OpenDDS_KeyLessThan LessThanType;
  typedef OpenDDS::DCPS::KeyOnly<const holo_base_msg::common::Pathf> KeyOnlyType;

  static const char* type_name() { return "holo_base_msg::common::Pathf"; }
  static bool gen_has_key() { return false; }
  static size_t key_count() { return 0; }
};
} // namespace DCPS
} // namespace OpenDDS
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
class  PathfTypeSupportImpl
  : public virtual OpenDDS::DCPS::LocalObject<PathfTypeSupport>
  , public virtual OpenDDS::DCPS::TypeSupportImpl
{
public:
  typedef OpenDDS::DCPS::DDSTraits<Pathf> TraitsType;
  typedef OpenDDS::DCPS::MarshalTraits<Pathf> MarshalTraitsType;
  typedef PathfTypeSupport TypeSupportType;
  typedef PathfTypeSupport::_var_type _var_type;
  typedef PathfTypeSupport::_ptr_type _ptr_type;

  PathfTypeSupportImpl() {}
  virtual ~PathfTypeSupportImpl() {}

  virtual ::DDS::DataWriter_ptr create_datawriter();
  virtual ::DDS::DataReader_ptr create_datareader();
#ifndef OPENDDS_NO_MULTI_TOPIC
  virtual ::DDS::DataReader_ptr create_multitopic_datareader();
#endif /* !OPENDDS_NO_MULTI_TOPIC */
#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
  virtual const OpenDDS::DCPS::MetaStruct& getMetaStructForType();
#endif /* !OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE */
  virtual bool has_dcps_key();
  const char* default_type_name() const;

  void representations_allowed_by_type(::DDS::DataRepresentationIdSeq& seq);

  virtual const OpenDDS::XTypes::TypeIdentifier& getMinimalTypeIdentifier() const;
  virtual const OpenDDS::XTypes::TypeMap& getMinimalTypeMap() const;

  virtual OpenDDS::DCPS::Extensibility getExtensibility() const;

  static PathfTypeSupport::_ptr_type _narrow(CORBA::Object_ptr obj);
};
}
}

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

template<>
const MetaStruct& getMetaStruct<holo_base_msg::common::Pathf>();
bool gen_skip_over(Serializer& ser, holo_base_msg::common::Pathf*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_common_Pathf_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_common_Pathf_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_common_Pathf_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End STRUCT: Pathf */


/* Begin STRUCT: Pathd */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void set_default(holo_base_msg::common::Pathd& stru);

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::common::Pathd& stru);

bool operator<<(Serializer& strm, const holo_base_msg::common::Pathd& stru);

bool operator>>(Serializer& strm, holo_base_msg::common::Pathd& stru);

void serialized_size(const Encoding& encoding, size_t& size, const NestedKeyOnly<const holo_base_msg::common::Pathd>& stru);

bool operator<<(Serializer& strm, const NestedKeyOnly<const holo_base_msg::common::Pathd>& stru);

bool operator>>(Serializer& strm, const NestedKeyOnly<holo_base_msg::common::Pathd>& stru);

template <>
struct MarshalTraits<holo_base_msg::common::Pathd> {
  static void representations_allowed_by_type(DDS::DataRepresentationIdSeq& seq)
  {
    seq.length(3);
    seq[0] = DDS::XCDR_DATA_REPRESENTATION;
    seq[1] = DDS::XCDR2_DATA_REPRESENTATION;
    seq[2] = DDS::XML_DATA_REPRESENTATION;
  }

  static SerializedSizeBound serialized_size_bound(const Encoding& encoding)
  {
    switch (encoding.kind()) {
    case Encoding::KIND_UNALIGNED_CDR:
      return SerializedSizeBound();
    case Encoding::KIND_XCDR1:
      return SerializedSizeBound();
    case Encoding::KIND_XCDR2:
      return SerializedSizeBound();
    default:
      OPENDDS_ASSERT(false);
      return SerializedSizeBound();
    }
  }

  static SerializedSizeBound key_only_serialized_size_bound(const Encoding& encoding)
  {
    switch (encoding.kind()) {
    case Encoding::KIND_UNALIGNED_CDR:
      return SerializedSizeBound(0);
    case Encoding::KIND_XCDR1:
      return SerializedSizeBound();
    case Encoding::KIND_XCDR2:
      return SerializedSizeBound();
    default:
      OPENDDS_ASSERT(false);
      return SerializedSizeBound();
    }
  }

  static bool to_message_block(ACE_Message_Block&, const holo_base_msg::common::Pathd&) { return false; }
  static bool from_message_block(holo_base_msg::common::Pathd&, const ACE_Message_Block&) { return false; }
  static Extensibility extensibility() { return APPENDABLE; }
  static Extensibility max_extensibility_level() { return APPENDABLE; }
};
void serialized_size(const Encoding& encoding, size_t& size, const KeyOnly<const holo_base_msg::common::Pathd> stru);

bool operator<<(Serializer& strm, KeyOnly<const holo_base_msg::common::Pathd> stru);

bool operator>>(Serializer& strm, KeyOnly<holo_base_msg::common::Pathd> stru);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
/// This structure supports use of std::map with one or more keys.
struct  Pathd_OpenDDS_KeyLessThan {
  bool operator()(const holo_base_msg::common::Pathd&, const holo_base_msg::common::Pathd&) const
  {
    // With no keys, return false to allow use of
    // map with just one entry
    return false;
  }
};
}
}

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void vwrite(OpenDDS::DCPS::ValueWriter& value_writer, const holo_base_msg::common::Pathd& value);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
class PathdTypeSupportImpl;
}
}

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS {
namespace DCPS {
template <>
struct DDSTraits<holo_base_msg::common::Pathd> {
  typedef holo_base_msg::common::Pathd MessageType;
  typedef holo_base_msg::common::PathdSeq MessageSequenceType;
  typedef holo_base_msg::common::PathdTypeSupport TypeSupportType;
  typedef holo_base_msg::common::PathdTypeSupportImpl TypeSupportTypeImpl;
  typedef holo_base_msg::common::PathdDataWriter DataWriterType;
  typedef holo_base_msg::common::PathdDataReader DataReaderType;
  typedef holo_base_msg::common::Pathd_OpenDDS_KeyLessThan LessThanType;
  typedef OpenDDS::DCPS::KeyOnly<const holo_base_msg::common::Pathd> KeyOnlyType;

  static const char* type_name() { return "holo_base_msg::common::Pathd"; }
  static bool gen_has_key() { return false; }
  static size_t key_count() { return 0; }
};
} // namespace DCPS
} // namespace OpenDDS
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
class  PathdTypeSupportImpl
  : public virtual OpenDDS::DCPS::LocalObject<PathdTypeSupport>
  , public virtual OpenDDS::DCPS::TypeSupportImpl
{
public:
  typedef OpenDDS::DCPS::DDSTraits<Pathd> TraitsType;
  typedef OpenDDS::DCPS::MarshalTraits<Pathd> MarshalTraitsType;
  typedef PathdTypeSupport TypeSupportType;
  typedef PathdTypeSupport::_var_type _var_type;
  typedef PathdTypeSupport::_ptr_type _ptr_type;

  PathdTypeSupportImpl() {}
  virtual ~PathdTypeSupportImpl() {}

  virtual ::DDS::DataWriter_ptr create_datawriter();
  virtual ::DDS::DataReader_ptr create_datareader();
#ifndef OPENDDS_NO_MULTI_TOPIC
  virtual ::DDS::DataReader_ptr create_multitopic_datareader();
#endif /* !OPENDDS_NO_MULTI_TOPIC */
#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
  virtual const OpenDDS::DCPS::MetaStruct& getMetaStructForType();
#endif /* !OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE */
  virtual bool has_dcps_key();
  const char* default_type_name() const;

  void representations_allowed_by_type(::DDS::DataRepresentationIdSeq& seq);

  virtual const OpenDDS::XTypes::TypeIdentifier& getMinimalTypeIdentifier() const;
  virtual const OpenDDS::XTypes::TypeMap& getMinimalTypeMap() const;

  virtual OpenDDS::DCPS::Extensibility getExtensibility() const;

  static PathdTypeSupport::_ptr_type _narrow(CORBA::Object_ptr obj);
};
}
}

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

template<>
const MetaStruct& getMetaStruct<holo_base_msg::common::Pathd>();
bool gen_skip_over(Serializer& ser, holo_base_msg::common::Pathd*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_common_Pathd_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_common_Pathd_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_common_Pathd_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End STRUCT: Pathd */

/* End MODULE: common */

/* End MODULE: holo_base_msg */
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif /* OPENDDS_IDL_GENERATED_PATHTYPESUPPORTIMPL_H_FSLYFP */
