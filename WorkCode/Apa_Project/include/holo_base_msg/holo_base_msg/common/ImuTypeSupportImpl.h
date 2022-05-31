/* -*- C++ -*- */
/* Generated by /home/holo/workspace/output/tda4_ubuntu-18.04/debug/host/bin/opendds_idl version 3.16 (ACE version 6.2a_p19) running on input file /home/holo/workspace/src/holo_base_msg/opendds_msg/message/holo_base_msg/common/Imu.idl */
#ifndef OPENDDS_IDL_GENERATED_IMUTYPESUPPORTIMPL_H_Q787XY
#define OPENDDS_IDL_GENERATED_IMUTYPESUPPORTIMPL_H_Q787XY
#include "ImuC.h"
#include "dds/DCPS/Definitions.h"
#include "dds/DdsDcpsC.h"
#include "dds/Version.h"
#if DDS_MAJOR_VERSION != 3 || DDS_MINOR_VERSION != 16 || DDS_MICRO_VERSION != 0
#error This file should be regenerated with opendds_idl
#endif
#include "ImuTypeSupportC.h"
#include "dds/DCPS/Serializer.h"
#include "dds/DCPS/TypeSupportImpl.h"
#include "dds/DCPS/ValueWriter.h"
#include "dds/DCPS/XTypes/TypeObject.h"
#include "holo_base_msg/common/CommonC.h"
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



/* Begin TYPEDEF: ImuStatus */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_common_ImuStatus_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_common_ImuStatus_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_common_ImuStatus_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End TYPEDEF: ImuStatus */


/* Begin STRUCT: Imuf */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void set_default(holo_base_msg::common::Imuf& stru);

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::common::Imuf& stru);

bool operator<<(Serializer& strm, const holo_base_msg::common::Imuf& stru);

bool operator>>(Serializer& strm, holo_base_msg::common::Imuf& stru);

void serialized_size(const Encoding& encoding, size_t& size, const NestedKeyOnly<const holo_base_msg::common::Imuf>& stru);

bool operator<<(Serializer& strm, const NestedKeyOnly<const holo_base_msg::common::Imuf>& stru);

bool operator>>(Serializer& strm, const NestedKeyOnly<holo_base_msg::common::Imuf>& stru);

template <>
struct MarshalTraits<holo_base_msg::common::Imuf> {
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
      return SerializedSizeBound(40);
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

  static bool to_message_block(ACE_Message_Block&, const holo_base_msg::common::Imuf&) { return false; }
  static bool from_message_block(holo_base_msg::common::Imuf&, const ACE_Message_Block&) { return false; }
  static Extensibility extensibility() { return APPENDABLE; }
  static Extensibility max_extensibility_level() { return APPENDABLE; }
};
void serialized_size(const Encoding& encoding, size_t& size, const KeyOnly<const holo_base_msg::common::Imuf> stru);

bool operator<<(Serializer& strm, KeyOnly<const holo_base_msg::common::Imuf> stru);

bool operator>>(Serializer& strm, KeyOnly<holo_base_msg::common::Imuf> stru);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
/// This structure supports use of std::map with one or more keys.
struct  Imuf_OpenDDS_KeyLessThan {
  bool operator()(const holo_base_msg::common::Imuf&, const holo_base_msg::common::Imuf&) const
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

void vwrite(OpenDDS::DCPS::ValueWriter& value_writer, const holo_base_msg::common::Imuf& value);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
class ImufTypeSupportImpl;
}
}

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS {
namespace DCPS {
template <>
struct DDSTraits<holo_base_msg::common::Imuf> {
  typedef holo_base_msg::common::Imuf MessageType;
  typedef holo_base_msg::common::ImufSeq MessageSequenceType;
  typedef holo_base_msg::common::ImufTypeSupport TypeSupportType;
  typedef holo_base_msg::common::ImufTypeSupportImpl TypeSupportTypeImpl;
  typedef holo_base_msg::common::ImufDataWriter DataWriterType;
  typedef holo_base_msg::common::ImufDataReader DataReaderType;
  typedef holo_base_msg::common::Imuf_OpenDDS_KeyLessThan LessThanType;
  typedef OpenDDS::DCPS::KeyOnly<const holo_base_msg::common::Imuf> KeyOnlyType;

  static const char* type_name() { return "holo_base_msg::common::Imuf"; }
  static bool gen_has_key() { return false; }
  static size_t key_count() { return 0; }
};
} // namespace DCPS
} // namespace OpenDDS
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
class  ImufTypeSupportImpl
  : public virtual OpenDDS::DCPS::LocalObject<ImufTypeSupport>
  , public virtual OpenDDS::DCPS::TypeSupportImpl
{
public:
  typedef OpenDDS::DCPS::DDSTraits<Imuf> TraitsType;
  typedef OpenDDS::DCPS::MarshalTraits<Imuf> MarshalTraitsType;
  typedef ImufTypeSupport TypeSupportType;
  typedef ImufTypeSupport::_var_type _var_type;
  typedef ImufTypeSupport::_ptr_type _ptr_type;

  ImufTypeSupportImpl() {}
  virtual ~ImufTypeSupportImpl() {}

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

  static ImufTypeSupport::_ptr_type _narrow(CORBA::Object_ptr obj);
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
const MetaStruct& getMetaStruct<holo_base_msg::common::Imuf>();
bool gen_skip_over(Serializer& ser, holo_base_msg::common::Imuf*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_common_Imuf_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_common_Imuf_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_common_Imuf_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End STRUCT: Imuf */


/* Begin STRUCT: Imud */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void set_default(holo_base_msg::common::Imud& stru);

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::common::Imud& stru);

bool operator<<(Serializer& strm, const holo_base_msg::common::Imud& stru);

bool operator>>(Serializer& strm, holo_base_msg::common::Imud& stru);

void serialized_size(const Encoding& encoding, size_t& size, const NestedKeyOnly<const holo_base_msg::common::Imud>& stru);

bool operator<<(Serializer& strm, const NestedKeyOnly<const holo_base_msg::common::Imud>& stru);

bool operator>>(Serializer& strm, const NestedKeyOnly<holo_base_msg::common::Imud>& stru);

template <>
struct MarshalTraits<holo_base_msg::common::Imud> {
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

  static bool to_message_block(ACE_Message_Block&, const holo_base_msg::common::Imud&) { return false; }
  static bool from_message_block(holo_base_msg::common::Imud&, const ACE_Message_Block&) { return false; }
  static Extensibility extensibility() { return APPENDABLE; }
  static Extensibility max_extensibility_level() { return APPENDABLE; }
};
void serialized_size(const Encoding& encoding, size_t& size, const KeyOnly<const holo_base_msg::common::Imud> stru);

bool operator<<(Serializer& strm, KeyOnly<const holo_base_msg::common::Imud> stru);

bool operator>>(Serializer& strm, KeyOnly<holo_base_msg::common::Imud> stru);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
/// This structure supports use of std::map with one or more keys.
struct  Imud_OpenDDS_KeyLessThan {
  bool operator()(const holo_base_msg::common::Imud&, const holo_base_msg::common::Imud&) const
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

void vwrite(OpenDDS::DCPS::ValueWriter& value_writer, const holo_base_msg::common::Imud& value);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
class ImudTypeSupportImpl;
}
}

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS {
namespace DCPS {
template <>
struct DDSTraits<holo_base_msg::common::Imud> {
  typedef holo_base_msg::common::Imud MessageType;
  typedef holo_base_msg::common::ImudSeq MessageSequenceType;
  typedef holo_base_msg::common::ImudTypeSupport TypeSupportType;
  typedef holo_base_msg::common::ImudTypeSupportImpl TypeSupportTypeImpl;
  typedef holo_base_msg::common::ImudDataWriter DataWriterType;
  typedef holo_base_msg::common::ImudDataReader DataReaderType;
  typedef holo_base_msg::common::Imud_OpenDDS_KeyLessThan LessThanType;
  typedef OpenDDS::DCPS::KeyOnly<const holo_base_msg::common::Imud> KeyOnlyType;

  static const char* type_name() { return "holo_base_msg::common::Imud"; }
  static bool gen_has_key() { return false; }
  static size_t key_count() { return 0; }
};
} // namespace DCPS
} // namespace OpenDDS
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
class  ImudTypeSupportImpl
  : public virtual OpenDDS::DCPS::LocalObject<ImudTypeSupport>
  , public virtual OpenDDS::DCPS::TypeSupportImpl
{
public:
  typedef OpenDDS::DCPS::DDSTraits<Imud> TraitsType;
  typedef OpenDDS::DCPS::MarshalTraits<Imud> MarshalTraitsType;
  typedef ImudTypeSupport TypeSupportType;
  typedef ImudTypeSupport::_var_type _var_type;
  typedef ImudTypeSupport::_ptr_type _ptr_type;

  ImudTypeSupportImpl() {}
  virtual ~ImudTypeSupportImpl() {}

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

  static ImudTypeSupport::_ptr_type _narrow(CORBA::Object_ptr obj);
};
}
}

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

template<>
const MetaStruct& getMetaStruct<holo_base_msg::common::Imud>();
bool gen_skip_over(Serializer& ser, holo_base_msg::common::Imud*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_common_Imud_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_common_Imud_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_common_Imud_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End STRUCT: Imud */


/* Begin STRUCT: ImuBiasf */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void set_default(holo_base_msg::common::ImuBiasf& stru);

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::common::ImuBiasf& stru);

bool operator<<(Serializer& strm, const holo_base_msg::common::ImuBiasf& stru);

bool operator>>(Serializer& strm, holo_base_msg::common::ImuBiasf& stru);

void serialized_size(const Encoding& encoding, size_t& size, const NestedKeyOnly<const holo_base_msg::common::ImuBiasf>& stru);

bool operator<<(Serializer& strm, const NestedKeyOnly<const holo_base_msg::common::ImuBiasf>& stru);

bool operator>>(Serializer& strm, const NestedKeyOnly<holo_base_msg::common::ImuBiasf>& stru);

template <>
struct MarshalTraits<holo_base_msg::common::ImuBiasf> {
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
      return SerializedSizeBound(60);
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

  static bool to_message_block(ACE_Message_Block&, const holo_base_msg::common::ImuBiasf&) { return false; }
  static bool from_message_block(holo_base_msg::common::ImuBiasf&, const ACE_Message_Block&) { return false; }
  static Extensibility extensibility() { return APPENDABLE; }
  static Extensibility max_extensibility_level() { return APPENDABLE; }
};
void serialized_size(const Encoding& encoding, size_t& size, const KeyOnly<const holo_base_msg::common::ImuBiasf> stru);

bool operator<<(Serializer& strm, KeyOnly<const holo_base_msg::common::ImuBiasf> stru);

bool operator>>(Serializer& strm, KeyOnly<holo_base_msg::common::ImuBiasf> stru);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
/// This structure supports use of std::map with one or more keys.
struct  ImuBiasf_OpenDDS_KeyLessThan {
  bool operator()(const holo_base_msg::common::ImuBiasf&, const holo_base_msg::common::ImuBiasf&) const
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

void vwrite(OpenDDS::DCPS::ValueWriter& value_writer, const holo_base_msg::common::ImuBiasf& value);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
class ImuBiasfTypeSupportImpl;
}
}

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS {
namespace DCPS {
template <>
struct DDSTraits<holo_base_msg::common::ImuBiasf> {
  typedef holo_base_msg::common::ImuBiasf MessageType;
  typedef holo_base_msg::common::ImuBiasfSeq MessageSequenceType;
  typedef holo_base_msg::common::ImuBiasfTypeSupport TypeSupportType;
  typedef holo_base_msg::common::ImuBiasfTypeSupportImpl TypeSupportTypeImpl;
  typedef holo_base_msg::common::ImuBiasfDataWriter DataWriterType;
  typedef holo_base_msg::common::ImuBiasfDataReader DataReaderType;
  typedef holo_base_msg::common::ImuBiasf_OpenDDS_KeyLessThan LessThanType;
  typedef OpenDDS::DCPS::KeyOnly<const holo_base_msg::common::ImuBiasf> KeyOnlyType;

  static const char* type_name() { return "holo_base_msg::common::ImuBiasf"; }
  static bool gen_has_key() { return false; }
  static size_t key_count() { return 0; }
};
} // namespace DCPS
} // namespace OpenDDS
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
class  ImuBiasfTypeSupportImpl
  : public virtual OpenDDS::DCPS::LocalObject<ImuBiasfTypeSupport>
  , public virtual OpenDDS::DCPS::TypeSupportImpl
{
public:
  typedef OpenDDS::DCPS::DDSTraits<ImuBiasf> TraitsType;
  typedef OpenDDS::DCPS::MarshalTraits<ImuBiasf> MarshalTraitsType;
  typedef ImuBiasfTypeSupport TypeSupportType;
  typedef ImuBiasfTypeSupport::_var_type _var_type;
  typedef ImuBiasfTypeSupport::_ptr_type _ptr_type;

  ImuBiasfTypeSupportImpl() {}
  virtual ~ImuBiasfTypeSupportImpl() {}

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

  static ImuBiasfTypeSupport::_ptr_type _narrow(CORBA::Object_ptr obj);
};
}
}

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

template<>
const MetaStruct& getMetaStruct<holo_base_msg::common::ImuBiasf>();
bool gen_skip_over(Serializer& ser, holo_base_msg::common::ImuBiasf*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_common_ImuBiasf_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_common_ImuBiasf_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_common_ImuBiasf_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End STRUCT: ImuBiasf */


/* Begin STRUCT: ImuBiasd */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void set_default(holo_base_msg::common::ImuBiasd& stru);

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::common::ImuBiasd& stru);

bool operator<<(Serializer& strm, const holo_base_msg::common::ImuBiasd& stru);

bool operator>>(Serializer& strm, holo_base_msg::common::ImuBiasd& stru);

void serialized_size(const Encoding& encoding, size_t& size, const NestedKeyOnly<const holo_base_msg::common::ImuBiasd>& stru);

bool operator<<(Serializer& strm, const NestedKeyOnly<const holo_base_msg::common::ImuBiasd>& stru);

bool operator>>(Serializer& strm, const NestedKeyOnly<holo_base_msg::common::ImuBiasd>& stru);

template <>
struct MarshalTraits<holo_base_msg::common::ImuBiasd> {
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
      return SerializedSizeBound(108);
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

  static bool to_message_block(ACE_Message_Block&, const holo_base_msg::common::ImuBiasd&) { return false; }
  static bool from_message_block(holo_base_msg::common::ImuBiasd&, const ACE_Message_Block&) { return false; }
  static Extensibility extensibility() { return APPENDABLE; }
  static Extensibility max_extensibility_level() { return APPENDABLE; }
};
void serialized_size(const Encoding& encoding, size_t& size, const KeyOnly<const holo_base_msg::common::ImuBiasd> stru);

bool operator<<(Serializer& strm, KeyOnly<const holo_base_msg::common::ImuBiasd> stru);

bool operator>>(Serializer& strm, KeyOnly<holo_base_msg::common::ImuBiasd> stru);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
/// This structure supports use of std::map with one or more keys.
struct  ImuBiasd_OpenDDS_KeyLessThan {
  bool operator()(const holo_base_msg::common::ImuBiasd&, const holo_base_msg::common::ImuBiasd&) const
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

void vwrite(OpenDDS::DCPS::ValueWriter& value_writer, const holo_base_msg::common::ImuBiasd& value);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
class ImuBiasdTypeSupportImpl;
}
}

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS {
namespace DCPS {
template <>
struct DDSTraits<holo_base_msg::common::ImuBiasd> {
  typedef holo_base_msg::common::ImuBiasd MessageType;
  typedef holo_base_msg::common::ImuBiasdSeq MessageSequenceType;
  typedef holo_base_msg::common::ImuBiasdTypeSupport TypeSupportType;
  typedef holo_base_msg::common::ImuBiasdTypeSupportImpl TypeSupportTypeImpl;
  typedef holo_base_msg::common::ImuBiasdDataWriter DataWriterType;
  typedef holo_base_msg::common::ImuBiasdDataReader DataReaderType;
  typedef holo_base_msg::common::ImuBiasd_OpenDDS_KeyLessThan LessThanType;
  typedef OpenDDS::DCPS::KeyOnly<const holo_base_msg::common::ImuBiasd> KeyOnlyType;

  static const char* type_name() { return "holo_base_msg::common::ImuBiasd"; }
  static bool gen_has_key() { return false; }
  static size_t key_count() { return 0; }
};
} // namespace DCPS
} // namespace OpenDDS
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
class  ImuBiasdTypeSupportImpl
  : public virtual OpenDDS::DCPS::LocalObject<ImuBiasdTypeSupport>
  , public virtual OpenDDS::DCPS::TypeSupportImpl
{
public:
  typedef OpenDDS::DCPS::DDSTraits<ImuBiasd> TraitsType;
  typedef OpenDDS::DCPS::MarshalTraits<ImuBiasd> MarshalTraitsType;
  typedef ImuBiasdTypeSupport TypeSupportType;
  typedef ImuBiasdTypeSupport::_var_type _var_type;
  typedef ImuBiasdTypeSupport::_ptr_type _ptr_type;

  ImuBiasdTypeSupportImpl() {}
  virtual ~ImuBiasdTypeSupportImpl() {}

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

  static ImuBiasdTypeSupport::_ptr_type _narrow(CORBA::Object_ptr obj);
};
}
}

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

template<>
const MetaStruct& getMetaStruct<holo_base_msg::common::ImuBiasd>();
bool gen_skip_over(Serializer& ser, holo_base_msg::common::ImuBiasd*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_common_ImuBiasd_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_common_ImuBiasd_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_common_ImuBiasd_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End STRUCT: ImuBiasd */

/* End MODULE: common */

/* End MODULE: holo_base_msg */
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif /* OPENDDS_IDL_GENERATED_IMUTYPESUPPORTIMPL_H_Q787XY */