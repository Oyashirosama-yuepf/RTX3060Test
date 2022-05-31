/* -*- C++ -*- */
/* Generated by /home/holo/workspace/output/tda4_ubuntu-18.04/debug/host/bin/opendds_idl version 3.16 (ACE version 6.2a_p19) running on input file /home/holo/workspace/src/holo_base_msg/opendds_msg/message/holo_base_msg/common/Gnss.idl */
#ifndef OPENDDS_IDL_GENERATED_GNSSTYPESUPPORTIMPL_H_9USI78
#define OPENDDS_IDL_GENERATED_GNSSTYPESUPPORTIMPL_H_9USI78
#include "GnssC.h"
#include "dds/DCPS/Definitions.h"
#include "dds/DdsDcpsC.h"
#include "dds/Version.h"
#if DDS_MAJOR_VERSION != 3 || DDS_MINOR_VERSION != 16 || DDS_MICRO_VERSION != 0
#error This file should be regenerated with opendds_idl
#endif
#include "GnssTypeSupportC.h"
#include "dds/DCPS/Serializer.h"
#include "dds/DCPS/TypeSupportImpl.h"
#include "dds/DCPS/ValueWriter.h"
#include "dds/DCPS/XTypes/TypeObject.h"
#include "holo_base_msg/common/CommonC.h"
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



/* Begin MODULE: common */



/* Begin STRUCT: GnssPvt */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void set_default(holo_base_msg::common::GnssPvt& stru);

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::common::GnssPvt& stru);

bool operator<<(Serializer& strm, const holo_base_msg::common::GnssPvt& stru);

bool operator>>(Serializer& strm, holo_base_msg::common::GnssPvt& stru);

void serialized_size(const Encoding& encoding, size_t& size, const NestedKeyOnly<const holo_base_msg::common::GnssPvt>& stru);

bool operator<<(Serializer& strm, const NestedKeyOnly<const holo_base_msg::common::GnssPvt>& stru);

bool operator>>(Serializer& strm, const NestedKeyOnly<holo_base_msg::common::GnssPvt>& stru);

template <>
struct MarshalTraits<holo_base_msg::common::GnssPvt> {
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
      return SerializedSizeBound(112);
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

  static bool to_message_block(ACE_Message_Block&, const holo_base_msg::common::GnssPvt&) { return false; }
  static bool from_message_block(holo_base_msg::common::GnssPvt&, const ACE_Message_Block&) { return false; }
  static Extensibility extensibility() { return APPENDABLE; }
  static Extensibility max_extensibility_level() { return APPENDABLE; }
};
void serialized_size(const Encoding& encoding, size_t& size, const KeyOnly<const holo_base_msg::common::GnssPvt> stru);

bool operator<<(Serializer& strm, KeyOnly<const holo_base_msg::common::GnssPvt> stru);

bool operator>>(Serializer& strm, KeyOnly<holo_base_msg::common::GnssPvt> stru);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
/// This structure supports use of std::map with one or more keys.
struct  GnssPvt_OpenDDS_KeyLessThan {
  bool operator()(const holo_base_msg::common::GnssPvt&, const holo_base_msg::common::GnssPvt&) const
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

void vwrite(OpenDDS::DCPS::ValueWriter& value_writer, const holo_base_msg::common::GnssPvt& value);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
class GnssPvtTypeSupportImpl;
}
}

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS {
namespace DCPS {
template <>
struct DDSTraits<holo_base_msg::common::GnssPvt> {
  typedef holo_base_msg::common::GnssPvt MessageType;
  typedef holo_base_msg::common::GnssPvtSeq MessageSequenceType;
  typedef holo_base_msg::common::GnssPvtTypeSupport TypeSupportType;
  typedef holo_base_msg::common::GnssPvtTypeSupportImpl TypeSupportTypeImpl;
  typedef holo_base_msg::common::GnssPvtDataWriter DataWriterType;
  typedef holo_base_msg::common::GnssPvtDataReader DataReaderType;
  typedef holo_base_msg::common::GnssPvt_OpenDDS_KeyLessThan LessThanType;
  typedef OpenDDS::DCPS::KeyOnly<const holo_base_msg::common::GnssPvt> KeyOnlyType;

  static const char* type_name() { return "holo_base_msg::common::GnssPvt"; }
  static bool gen_has_key() { return false; }
  static size_t key_count() { return 0; }
};
} // namespace DCPS
} // namespace OpenDDS
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
class  GnssPvtTypeSupportImpl
  : public virtual OpenDDS::DCPS::LocalObject<GnssPvtTypeSupport>
  , public virtual OpenDDS::DCPS::TypeSupportImpl
{
public:
  typedef OpenDDS::DCPS::DDSTraits<GnssPvt> TraitsType;
  typedef OpenDDS::DCPS::MarshalTraits<GnssPvt> MarshalTraitsType;
  typedef GnssPvtTypeSupport TypeSupportType;
  typedef GnssPvtTypeSupport::_var_type _var_type;
  typedef GnssPvtTypeSupport::_ptr_type _ptr_type;

  GnssPvtTypeSupportImpl() {}
  virtual ~GnssPvtTypeSupportImpl() {}

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

  static GnssPvtTypeSupport::_ptr_type _narrow(CORBA::Object_ptr obj);
};
}
}

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

class MetaStruct;

template<typename T>
const MetaStruct& getMetaStruct();

template<>
const MetaStruct& getMetaStruct<holo_base_msg::common::GnssPvt>();
bool gen_skip_over(Serializer& ser, holo_base_msg::common::GnssPvt*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_common_GnssPvt_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_common_GnssPvt_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_common_GnssPvt_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End STRUCT: GnssPvt */


/* Begin TYPEDEF: GnssPositionStatus */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_common_GnssPositionStatus_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_common_GnssPositionStatus_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_common_GnssPositionStatus_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End TYPEDEF: GnssPositionStatus */


/* Begin STRUCT: GnssPosition */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void set_default(holo_base_msg::common::GnssPosition& stru);

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::common::GnssPosition& stru);

bool operator<<(Serializer& strm, const holo_base_msg::common::GnssPosition& stru);

bool operator>>(Serializer& strm, holo_base_msg::common::GnssPosition& stru);

void serialized_size(const Encoding& encoding, size_t& size, const NestedKeyOnly<const holo_base_msg::common::GnssPosition>& stru);

bool operator<<(Serializer& strm, const NestedKeyOnly<const holo_base_msg::common::GnssPosition>& stru);

bool operator>>(Serializer& strm, const NestedKeyOnly<holo_base_msg::common::GnssPosition>& stru);

template <>
struct MarshalTraits<holo_base_msg::common::GnssPosition> {
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
      return SerializedSizeBound(64);
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

  static bool to_message_block(ACE_Message_Block&, const holo_base_msg::common::GnssPosition&) { return false; }
  static bool from_message_block(holo_base_msg::common::GnssPosition&, const ACE_Message_Block&) { return false; }
  static Extensibility extensibility() { return APPENDABLE; }
  static Extensibility max_extensibility_level() { return APPENDABLE; }
};
void serialized_size(const Encoding& encoding, size_t& size, const KeyOnly<const holo_base_msg::common::GnssPosition> stru);

bool operator<<(Serializer& strm, KeyOnly<const holo_base_msg::common::GnssPosition> stru);

bool operator>>(Serializer& strm, KeyOnly<holo_base_msg::common::GnssPosition> stru);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
/// This structure supports use of std::map with one or more keys.
struct  GnssPosition_OpenDDS_KeyLessThan {
  bool operator()(const holo_base_msg::common::GnssPosition&, const holo_base_msg::common::GnssPosition&) const
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

void vwrite(OpenDDS::DCPS::ValueWriter& value_writer, const holo_base_msg::common::GnssPosition& value);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
class GnssPositionTypeSupportImpl;
}
}

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS {
namespace DCPS {
template <>
struct DDSTraits<holo_base_msg::common::GnssPosition> {
  typedef holo_base_msg::common::GnssPosition MessageType;
  typedef holo_base_msg::common::GnssPositionSeq MessageSequenceType;
  typedef holo_base_msg::common::GnssPositionTypeSupport TypeSupportType;
  typedef holo_base_msg::common::GnssPositionTypeSupportImpl TypeSupportTypeImpl;
  typedef holo_base_msg::common::GnssPositionDataWriter DataWriterType;
  typedef holo_base_msg::common::GnssPositionDataReader DataReaderType;
  typedef holo_base_msg::common::GnssPosition_OpenDDS_KeyLessThan LessThanType;
  typedef OpenDDS::DCPS::KeyOnly<const holo_base_msg::common::GnssPosition> KeyOnlyType;

  static const char* type_name() { return "holo_base_msg::common::GnssPosition"; }
  static bool gen_has_key() { return false; }
  static size_t key_count() { return 0; }
};
} // namespace DCPS
} // namespace OpenDDS
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
class  GnssPositionTypeSupportImpl
  : public virtual OpenDDS::DCPS::LocalObject<GnssPositionTypeSupport>
  , public virtual OpenDDS::DCPS::TypeSupportImpl
{
public:
  typedef OpenDDS::DCPS::DDSTraits<GnssPosition> TraitsType;
  typedef OpenDDS::DCPS::MarshalTraits<GnssPosition> MarshalTraitsType;
  typedef GnssPositionTypeSupport TypeSupportType;
  typedef GnssPositionTypeSupport::_var_type _var_type;
  typedef GnssPositionTypeSupport::_ptr_type _ptr_type;

  GnssPositionTypeSupportImpl() {}
  virtual ~GnssPositionTypeSupportImpl() {}

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

  static GnssPositionTypeSupport::_ptr_type _narrow(CORBA::Object_ptr obj);
};
}
}

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

template<>
const MetaStruct& getMetaStruct<holo_base_msg::common::GnssPosition>();
bool gen_skip_over(Serializer& ser, holo_base_msg::common::GnssPosition*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_common_GnssPosition_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_common_GnssPosition_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_common_GnssPosition_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End STRUCT: GnssPosition */


/* Begin STRUCT: RawBlock */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void set_default(holo_base_msg::common::RawBlock& stru);

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::common::RawBlock& stru);

bool operator<<(Serializer& strm, const holo_base_msg::common::RawBlock& stru);

bool operator>>(Serializer& strm, holo_base_msg::common::RawBlock& stru);

void serialized_size(const Encoding& encoding, size_t& size, const NestedKeyOnly<const holo_base_msg::common::RawBlock>& stru);

bool operator<<(Serializer& strm, const NestedKeyOnly<const holo_base_msg::common::RawBlock>& stru);

bool operator>>(Serializer& strm, const NestedKeyOnly<holo_base_msg::common::RawBlock>& stru);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void vwrite(OpenDDS::DCPS::ValueWriter& value_writer, const holo_base_msg::common::RawBlock& value);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

template<>
const MetaStruct& getMetaStruct<holo_base_msg::common::RawBlock>();
bool gen_skip_over(Serializer& ser, holo_base_msg::common::RawBlock*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_common_RawBlock_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_common_RawBlock_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_common_RawBlock_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End STRUCT: RawBlock */


/* Begin TYPEDEF: RawBlockSequence */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::common::RawBlockSequence& seq);

bool operator<<(Serializer& strm, const holo_base_msg::common::RawBlockSequence& seq);

bool operator>>(Serializer& strm, holo_base_msg::common::RawBlockSequence& seq);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

bool gen_skip_over(Serializer& ser, holo_base_msg::common::RawBlockSequence*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_common_RawBlockSequence_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_common_RawBlockSequence_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_common_RawBlockSequence_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End TYPEDEF: RawBlockSequence */


/* Begin STRUCT: GnssRawMeasurement */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void set_default(holo_base_msg::common::GnssRawMeasurement& stru);

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::common::GnssRawMeasurement& stru);

bool operator<<(Serializer& strm, const holo_base_msg::common::GnssRawMeasurement& stru);

bool operator>>(Serializer& strm, holo_base_msg::common::GnssRawMeasurement& stru);

void serialized_size(const Encoding& encoding, size_t& size, const NestedKeyOnly<const holo_base_msg::common::GnssRawMeasurement>& stru);

bool operator<<(Serializer& strm, const NestedKeyOnly<const holo_base_msg::common::GnssRawMeasurement>& stru);

bool operator>>(Serializer& strm, const NestedKeyOnly<holo_base_msg::common::GnssRawMeasurement>& stru);

template <>
struct MarshalTraits<holo_base_msg::common::GnssRawMeasurement> {
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

  static bool to_message_block(ACE_Message_Block&, const holo_base_msg::common::GnssRawMeasurement&) { return false; }
  static bool from_message_block(holo_base_msg::common::GnssRawMeasurement&, const ACE_Message_Block&) { return false; }
  static Extensibility extensibility() { return APPENDABLE; }
  static Extensibility max_extensibility_level() { return APPENDABLE; }
};
void serialized_size(const Encoding& encoding, size_t& size, const KeyOnly<const holo_base_msg::common::GnssRawMeasurement> stru);

bool operator<<(Serializer& strm, KeyOnly<const holo_base_msg::common::GnssRawMeasurement> stru);

bool operator>>(Serializer& strm, KeyOnly<holo_base_msg::common::GnssRawMeasurement> stru);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
/// This structure supports use of std::map with one or more keys.
struct  GnssRawMeasurement_OpenDDS_KeyLessThan {
  bool operator()(const holo_base_msg::common::GnssRawMeasurement&, const holo_base_msg::common::GnssRawMeasurement&) const
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

void vwrite(OpenDDS::DCPS::ValueWriter& value_writer, const holo_base_msg::common::GnssRawMeasurement& value);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
class GnssRawMeasurementTypeSupportImpl;
}
}

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS {
namespace DCPS {
template <>
struct DDSTraits<holo_base_msg::common::GnssRawMeasurement> {
  typedef holo_base_msg::common::GnssRawMeasurement MessageType;
  typedef holo_base_msg::common::GnssRawMeasurementSeq MessageSequenceType;
  typedef holo_base_msg::common::GnssRawMeasurementTypeSupport TypeSupportType;
  typedef holo_base_msg::common::GnssRawMeasurementTypeSupportImpl TypeSupportTypeImpl;
  typedef holo_base_msg::common::GnssRawMeasurementDataWriter DataWriterType;
  typedef holo_base_msg::common::GnssRawMeasurementDataReader DataReaderType;
  typedef holo_base_msg::common::GnssRawMeasurement_OpenDDS_KeyLessThan LessThanType;
  typedef OpenDDS::DCPS::KeyOnly<const holo_base_msg::common::GnssRawMeasurement> KeyOnlyType;

  static const char* type_name() { return "holo_base_msg::common::GnssRawMeasurement"; }
  static bool gen_has_key() { return false; }
  static size_t key_count() { return 0; }
};
} // namespace DCPS
} // namespace OpenDDS
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
class  GnssRawMeasurementTypeSupportImpl
  : public virtual OpenDDS::DCPS::LocalObject<GnssRawMeasurementTypeSupport>
  , public virtual OpenDDS::DCPS::TypeSupportImpl
{
public:
  typedef OpenDDS::DCPS::DDSTraits<GnssRawMeasurement> TraitsType;
  typedef OpenDDS::DCPS::MarshalTraits<GnssRawMeasurement> MarshalTraitsType;
  typedef GnssRawMeasurementTypeSupport TypeSupportType;
  typedef GnssRawMeasurementTypeSupport::_var_type _var_type;
  typedef GnssRawMeasurementTypeSupport::_ptr_type _ptr_type;

  GnssRawMeasurementTypeSupportImpl() {}
  virtual ~GnssRawMeasurementTypeSupportImpl() {}

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

  static GnssRawMeasurementTypeSupport::_ptr_type _narrow(CORBA::Object_ptr obj);
};
}
}

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

template<>
const MetaStruct& getMetaStruct<holo_base_msg::common::GnssRawMeasurement>();
bool gen_skip_over(Serializer& ser, holo_base_msg::common::GnssRawMeasurement*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_common_GnssRawMeasurement_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_common_GnssRawMeasurement_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_common_GnssRawMeasurement_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End STRUCT: GnssRawMeasurement */

/* End MODULE: common */

/* End MODULE: holo_base_msg */
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif /* OPENDDS_IDL_GENERATED_GNSSTYPESUPPORTIMPL_H_9USI78 */