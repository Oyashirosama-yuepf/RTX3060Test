/* -*- C++ -*- */
/* Generated by /home/holo/workspace/output/tda4_ubuntu-18.04/debug/host/bin/opendds_idl version 3.16 (ACE version 6.2a_p19) running on input file /home/holo/workspace/src/holo_base_msg/opendds_msg/message/holo_base_msg/common/VehicleState.idl */
#ifndef OPENDDS_IDL_GENERATED_VEHICLESTATETYPESUPPORTIMPL_H_KAODX1
#define OPENDDS_IDL_GENERATED_VEHICLESTATETYPESUPPORTIMPL_H_KAODX1
#include "VehicleStateC.h"
#include "dds/DCPS/Definitions.h"
#include "dds/DdsDcpsC.h"
#include "dds/Version.h"
#if DDS_MAJOR_VERSION != 3 || DDS_MINOR_VERSION != 16 || DDS_MICRO_VERSION != 0
#error This file should be regenerated with opendds_idl
#endif
#include "VehicleStateTypeSupportC.h"
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



/* Begin STRUCT: ChassisState */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void set_default(holo_base_msg::common::ChassisState& stru);

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::common::ChassisState& stru);

bool operator<<(Serializer& strm, const holo_base_msg::common::ChassisState& stru);

bool operator>>(Serializer& strm, holo_base_msg::common::ChassisState& stru);

void serialized_size(const Encoding& encoding, size_t& size, const NestedKeyOnly<const holo_base_msg::common::ChassisState>& stru);

bool operator<<(Serializer& strm, const NestedKeyOnly<const holo_base_msg::common::ChassisState>& stru);

bool operator>>(Serializer& strm, const NestedKeyOnly<holo_base_msg::common::ChassisState>& stru);

template <>
struct MarshalTraits<holo_base_msg::common::ChassisState> {
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
      return SerializedSizeBound(75);
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

  static bool to_message_block(ACE_Message_Block&, const holo_base_msg::common::ChassisState&) { return false; }
  static bool from_message_block(holo_base_msg::common::ChassisState&, const ACE_Message_Block&) { return false; }
  static Extensibility extensibility() { return APPENDABLE; }
  static Extensibility max_extensibility_level() { return APPENDABLE; }
};
void serialized_size(const Encoding& encoding, size_t& size, const KeyOnly<const holo_base_msg::common::ChassisState> stru);

bool operator<<(Serializer& strm, KeyOnly<const holo_base_msg::common::ChassisState> stru);

bool operator>>(Serializer& strm, KeyOnly<holo_base_msg::common::ChassisState> stru);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
/// This structure supports use of std::map with one or more keys.
struct  ChassisState_OpenDDS_KeyLessThan {
  bool operator()(const holo_base_msg::common::ChassisState&, const holo_base_msg::common::ChassisState&) const
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

void vwrite(OpenDDS::DCPS::ValueWriter& value_writer, const holo_base_msg::common::ChassisState& value);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
class ChassisStateTypeSupportImpl;
}
}

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS {
namespace DCPS {
template <>
struct DDSTraits<holo_base_msg::common::ChassisState> {
  typedef holo_base_msg::common::ChassisState MessageType;
  typedef holo_base_msg::common::ChassisStateSeq MessageSequenceType;
  typedef holo_base_msg::common::ChassisStateTypeSupport TypeSupportType;
  typedef holo_base_msg::common::ChassisStateTypeSupportImpl TypeSupportTypeImpl;
  typedef holo_base_msg::common::ChassisStateDataWriter DataWriterType;
  typedef holo_base_msg::common::ChassisStateDataReader DataReaderType;
  typedef holo_base_msg::common::ChassisState_OpenDDS_KeyLessThan LessThanType;
  typedef OpenDDS::DCPS::KeyOnly<const holo_base_msg::common::ChassisState> KeyOnlyType;

  static const char* type_name() { return "holo_base_msg::common::ChassisState"; }
  static bool gen_has_key() { return false; }
  static size_t key_count() { return 0; }
};
} // namespace DCPS
} // namespace OpenDDS
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
class  ChassisStateTypeSupportImpl
  : public virtual OpenDDS::DCPS::LocalObject<ChassisStateTypeSupport>
  , public virtual OpenDDS::DCPS::TypeSupportImpl
{
public:
  typedef OpenDDS::DCPS::DDSTraits<ChassisState> TraitsType;
  typedef OpenDDS::DCPS::MarshalTraits<ChassisState> MarshalTraitsType;
  typedef ChassisStateTypeSupport TypeSupportType;
  typedef ChassisStateTypeSupport::_var_type _var_type;
  typedef ChassisStateTypeSupport::_ptr_type _ptr_type;

  ChassisStateTypeSupportImpl() {}
  virtual ~ChassisStateTypeSupportImpl() {}

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

  static ChassisStateTypeSupport::_ptr_type _narrow(CORBA::Object_ptr obj);
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
const MetaStruct& getMetaStruct<holo_base_msg::common::ChassisState>();
bool gen_skip_over(Serializer& ser, holo_base_msg::common::ChassisState*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_common_ChassisState_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_common_ChassisState_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_common_ChassisState_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End STRUCT: ChassisState */


/* Begin STRUCT: VehicleBodyState */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void set_default(holo_base_msg::common::VehicleBodyState& stru);

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::common::VehicleBodyState& stru);

bool operator<<(Serializer& strm, const holo_base_msg::common::VehicleBodyState& stru);

bool operator>>(Serializer& strm, holo_base_msg::common::VehicleBodyState& stru);

void serialized_size(const Encoding& encoding, size_t& size, const NestedKeyOnly<const holo_base_msg::common::VehicleBodyState>& stru);

bool operator<<(Serializer& strm, const NestedKeyOnly<const holo_base_msg::common::VehicleBodyState>& stru);

bool operator>>(Serializer& strm, const NestedKeyOnly<holo_base_msg::common::VehicleBodyState>& stru);

template <>
struct MarshalTraits<holo_base_msg::common::VehicleBodyState> {
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
      return SerializedSizeBound(32);
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

  static bool to_message_block(ACE_Message_Block&, const holo_base_msg::common::VehicleBodyState&) { return false; }
  static bool from_message_block(holo_base_msg::common::VehicleBodyState&, const ACE_Message_Block&) { return false; }
  static Extensibility extensibility() { return APPENDABLE; }
  static Extensibility max_extensibility_level() { return APPENDABLE; }
};
void serialized_size(const Encoding& encoding, size_t& size, const KeyOnly<const holo_base_msg::common::VehicleBodyState> stru);

bool operator<<(Serializer& strm, KeyOnly<const holo_base_msg::common::VehicleBodyState> stru);

bool operator>>(Serializer& strm, KeyOnly<holo_base_msg::common::VehicleBodyState> stru);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
/// This structure supports use of std::map with one or more keys.
struct  VehicleBodyState_OpenDDS_KeyLessThan {
  bool operator()(const holo_base_msg::common::VehicleBodyState&, const holo_base_msg::common::VehicleBodyState&) const
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

void vwrite(OpenDDS::DCPS::ValueWriter& value_writer, const holo_base_msg::common::VehicleBodyState& value);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
class VehicleBodyStateTypeSupportImpl;
}
}

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS {
namespace DCPS {
template <>
struct DDSTraits<holo_base_msg::common::VehicleBodyState> {
  typedef holo_base_msg::common::VehicleBodyState MessageType;
  typedef holo_base_msg::common::VehicleBodyStateSeq MessageSequenceType;
  typedef holo_base_msg::common::VehicleBodyStateTypeSupport TypeSupportType;
  typedef holo_base_msg::common::VehicleBodyStateTypeSupportImpl TypeSupportTypeImpl;
  typedef holo_base_msg::common::VehicleBodyStateDataWriter DataWriterType;
  typedef holo_base_msg::common::VehicleBodyStateDataReader DataReaderType;
  typedef holo_base_msg::common::VehicleBodyState_OpenDDS_KeyLessThan LessThanType;
  typedef OpenDDS::DCPS::KeyOnly<const holo_base_msg::common::VehicleBodyState> KeyOnlyType;

  static const char* type_name() { return "holo_base_msg::common::VehicleBodyState"; }
  static bool gen_has_key() { return false; }
  static size_t key_count() { return 0; }
};
} // namespace DCPS
} // namespace OpenDDS
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace common {
class  VehicleBodyStateTypeSupportImpl
  : public virtual OpenDDS::DCPS::LocalObject<VehicleBodyStateTypeSupport>
  , public virtual OpenDDS::DCPS::TypeSupportImpl
{
public:
  typedef OpenDDS::DCPS::DDSTraits<VehicleBodyState> TraitsType;
  typedef OpenDDS::DCPS::MarshalTraits<VehicleBodyState> MarshalTraitsType;
  typedef VehicleBodyStateTypeSupport TypeSupportType;
  typedef VehicleBodyStateTypeSupport::_var_type _var_type;
  typedef VehicleBodyStateTypeSupport::_ptr_type _ptr_type;

  VehicleBodyStateTypeSupportImpl() {}
  virtual ~VehicleBodyStateTypeSupportImpl() {}

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

  static VehicleBodyStateTypeSupport::_ptr_type _narrow(CORBA::Object_ptr obj);
};
}
}

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

template<>
const MetaStruct& getMetaStruct<holo_base_msg::common::VehicleBodyState>();
bool gen_skip_over(Serializer& ser, holo_base_msg::common::VehicleBodyState*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_common_VehicleBodyState_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_common_VehicleBodyState_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_common_VehicleBodyState_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End STRUCT: VehicleBodyState */

/* End MODULE: common */

/* End MODULE: holo_base_msg */
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif /* OPENDDS_IDL_GENERATED_VEHICLESTATETYPESUPPORTIMPL_H_KAODX1 */
