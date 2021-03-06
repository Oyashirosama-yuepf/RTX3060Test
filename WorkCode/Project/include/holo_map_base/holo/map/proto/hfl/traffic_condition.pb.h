// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: holo/map/proto/hfl/traffic_condition.proto

#ifndef PROTOBUF_INCLUDED_holo_2fmap_2fproto_2fhfl_2ftraffic_5fcondition_2eproto
#define PROTOBUF_INCLUDED_holo_2fmap_2fproto_2fhfl_2ftraffic_5fcondition_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
#include "holo/map/proto/common/interval_float64.pb.h"
#include "holo/map/proto/common/interval_type.pb.h"
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_holo_2fmap_2fproto_2fhfl_2ftraffic_5fcondition_2eproto 

namespace protobuf_holo_2fmap_2fproto_2fhfl_2ftraffic_5fcondition_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[1];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_holo_2fmap_2fproto_2fhfl_2ftraffic_5fcondition_2eproto
namespace holo {
namespace map {
namespace proto {
namespace hfl {
class TrafficCondition;
class TrafficConditionDefaultTypeInternal;
extern TrafficConditionDefaultTypeInternal _TrafficCondition_default_instance_;
}  // namespace hfl
}  // namespace proto
}  // namespace map
}  // namespace holo
namespace google {
namespace protobuf {
template<> ::holo::map::proto::hfl::TrafficCondition* Arena::CreateMaybeMessage<::holo::map::proto::hfl::TrafficCondition>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace holo {
namespace map {
namespace proto {
namespace hfl {

enum TrafficCondition_TrafficType {
  TrafficCondition_TrafficType_TRAFFIC_TYPE_UNDEFINED = 0,
  TrafficCondition_TrafficType_TRAFFIC_TYPE_TRAFFIC_ACCIDENT = 1,
  TrafficCondition_TrafficType_TRAFFIC_TYPE_TRAFFIC_JAM = 2,
  TrafficCondition_TrafficType_TRAFFIC_TYPE_TRAFFIC_RULES = 3,
  TrafficCondition_TrafficType_TRAFFIC_TYPE_OTHERS = 4
};
bool TrafficCondition_TrafficType_IsValid(int value);
const TrafficCondition_TrafficType TrafficCondition_TrafficType_TrafficType_MIN = TrafficCondition_TrafficType_TRAFFIC_TYPE_UNDEFINED;
const TrafficCondition_TrafficType TrafficCondition_TrafficType_TrafficType_MAX = TrafficCondition_TrafficType_TRAFFIC_TYPE_OTHERS;
const int TrafficCondition_TrafficType_TrafficType_ARRAYSIZE = TrafficCondition_TrafficType_TrafficType_MAX + 1;

const ::google::protobuf::EnumDescriptor* TrafficCondition_TrafficType_descriptor();
inline const ::std::string& TrafficCondition_TrafficType_Name(TrafficCondition_TrafficType value) {
  return ::google::protobuf::internal::NameOfEnum(
    TrafficCondition_TrafficType_descriptor(), value);
}
inline bool TrafficCondition_TrafficType_Parse(
    const ::std::string& name, TrafficCondition_TrafficType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<TrafficCondition_TrafficType>(
    TrafficCondition_TrafficType_descriptor(), name, value);
}
// ===================================================================

class TrafficCondition : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:holo.map.proto.hfl.TrafficCondition) */ {
 public:
  TrafficCondition();
  virtual ~TrafficCondition();

  TrafficCondition(const TrafficCondition& from);

  inline TrafficCondition& operator=(const TrafficCondition& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  TrafficCondition(TrafficCondition&& from) noexcept
    : TrafficCondition() {
    *this = ::std::move(from);
  }

  inline TrafficCondition& operator=(TrafficCondition&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const TrafficCondition& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const TrafficCondition* internal_default_instance() {
    return reinterpret_cast<const TrafficCondition*>(
               &_TrafficCondition_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(TrafficCondition* other);
  friend void swap(TrafficCondition& a, TrafficCondition& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline TrafficCondition* New() const final {
    return CreateMaybeMessage<TrafficCondition>(NULL);
  }

  TrafficCondition* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<TrafficCondition>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const TrafficCondition& from);
  void MergeFrom(const TrafficCondition& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(TrafficCondition* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  typedef TrafficCondition_TrafficType TrafficType;
  static const TrafficType TRAFFIC_TYPE_UNDEFINED =
    TrafficCondition_TrafficType_TRAFFIC_TYPE_UNDEFINED;
  static const TrafficType TRAFFIC_TYPE_TRAFFIC_ACCIDENT =
    TrafficCondition_TrafficType_TRAFFIC_TYPE_TRAFFIC_ACCIDENT;
  static const TrafficType TRAFFIC_TYPE_TRAFFIC_JAM =
    TrafficCondition_TrafficType_TRAFFIC_TYPE_TRAFFIC_JAM;
  static const TrafficType TRAFFIC_TYPE_TRAFFIC_RULES =
    TrafficCondition_TrafficType_TRAFFIC_TYPE_TRAFFIC_RULES;
  static const TrafficType TRAFFIC_TYPE_OTHERS =
    TrafficCondition_TrafficType_TRAFFIC_TYPE_OTHERS;
  static inline bool TrafficType_IsValid(int value) {
    return TrafficCondition_TrafficType_IsValid(value);
  }
  static const TrafficType TrafficType_MIN =
    TrafficCondition_TrafficType_TrafficType_MIN;
  static const TrafficType TrafficType_MAX =
    TrafficCondition_TrafficType_TrafficType_MAX;
  static const int TrafficType_ARRAYSIZE =
    TrafficCondition_TrafficType_TrafficType_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  TrafficType_descriptor() {
    return TrafficCondition_TrafficType_descriptor();
  }
  static inline const ::std::string& TrafficType_Name(TrafficType value) {
    return TrafficCondition_TrafficType_Name(value);
  }
  static inline bool TrafficType_Parse(const ::std::string& name,
      TrafficType* value) {
    return TrafficCondition_TrafficType_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // repeated .holo.map.proto.common.IntervalFloat64 traffic_pos = 3;
  int traffic_pos_size() const;
  void clear_traffic_pos();
  static const int kTrafficPosFieldNumber = 3;
  ::holo::map::proto::common::IntervalFloat64* mutable_traffic_pos(int index);
  ::google::protobuf::RepeatedPtrField< ::holo::map::proto::common::IntervalFloat64 >*
      mutable_traffic_pos();
  const ::holo::map::proto::common::IntervalFloat64& traffic_pos(int index) const;
  ::holo::map::proto::common::IntervalFloat64* add_traffic_pos();
  const ::google::protobuf::RepeatedPtrField< ::holo::map::proto::common::IntervalFloat64 >&
      traffic_pos() const;

  // repeated .holo.map.proto.common.IntervalFloat64 exist_timestamp = 6;
  int exist_timestamp_size() const;
  void clear_exist_timestamp();
  static const int kExistTimestampFieldNumber = 6;
  ::holo::map::proto::common::IntervalFloat64* mutable_exist_timestamp(int index);
  ::google::protobuf::RepeatedPtrField< ::holo::map::proto::common::IntervalFloat64 >*
      mutable_exist_timestamp();
  const ::holo::map::proto::common::IntervalFloat64& exist_timestamp(int index) const;
  ::holo::map::proto::common::IntervalFloat64* add_exist_timestamp();
  const ::google::protobuf::RepeatedPtrField< ::holo::map::proto::common::IntervalFloat64 >&
      exist_timestamp() const;

  // optional .holo.map.proto.common.IntervalType traffic_pos_type = 4;
  bool has_traffic_pos_type() const;
  void clear_traffic_pos_type();
  static const int kTrafficPosTypeFieldNumber = 4;
  private:
  const ::holo::map::proto::common::IntervalType& _internal_traffic_pos_type() const;
  public:
  const ::holo::map::proto::common::IntervalType& traffic_pos_type() const;
  ::holo::map::proto::common::IntervalType* release_traffic_pos_type();
  ::holo::map::proto::common::IntervalType* mutable_traffic_pos_type();
  void set_allocated_traffic_pos_type(::holo::map::proto::common::IntervalType* traffic_pos_type);

  // optional uint64 traffic_condition_id = 1;
  bool has_traffic_condition_id() const;
  void clear_traffic_condition_id();
  static const int kTrafficConditionIdFieldNumber = 1;
  ::google::protobuf::uint64 traffic_condition_id() const;
  void set_traffic_condition_id(::google::protobuf::uint64 value);

  // optional .holo.map.proto.hfl.TrafficCondition.TrafficType traffic_type = 2;
  bool has_traffic_type() const;
  void clear_traffic_type();
  static const int kTrafficTypeFieldNumber = 2;
  ::holo::map::proto::hfl::TrafficCondition_TrafficType traffic_type() const;
  void set_traffic_type(::holo::map::proto::hfl::TrafficCondition_TrafficType value);

  // optional uint32 width_cm = 5;
  bool has_width_cm() const;
  void clear_width_cm();
  static const int kWidthCmFieldNumber = 5;
  ::google::protobuf::uint32 width_cm() const;
  void set_width_cm(::google::protobuf::uint32 value);

  // optional uint64 create_timestamp = 7;
  bool has_create_timestamp() const;
  void clear_create_timestamp();
  static const int kCreateTimestampFieldNumber = 7;
  ::google::protobuf::uint64 create_timestamp() const;
  void set_create_timestamp(::google::protobuf::uint64 value);

  // optional uint64 update_timestamp = 8;
  bool has_update_timestamp() const;
  void clear_update_timestamp();
  static const int kUpdateTimestampFieldNumber = 8;
  ::google::protobuf::uint64 update_timestamp() const;
  void set_update_timestamp(::google::protobuf::uint64 value);

  // @@protoc_insertion_point(class_scope:holo.map.proto.hfl.TrafficCondition)
 private:
  void set_has_traffic_condition_id();
  void clear_has_traffic_condition_id();
  void set_has_traffic_type();
  void clear_has_traffic_type();
  void set_has_traffic_pos_type();
  void clear_has_traffic_pos_type();
  void set_has_width_cm();
  void clear_has_width_cm();
  void set_has_create_timestamp();
  void clear_has_create_timestamp();
  void set_has_update_timestamp();
  void clear_has_update_timestamp();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::holo::map::proto::common::IntervalFloat64 > traffic_pos_;
  ::google::protobuf::RepeatedPtrField< ::holo::map::proto::common::IntervalFloat64 > exist_timestamp_;
  ::holo::map::proto::common::IntervalType* traffic_pos_type_;
  ::google::protobuf::uint64 traffic_condition_id_;
  int traffic_type_;
  ::google::protobuf::uint32 width_cm_;
  ::google::protobuf::uint64 create_timestamp_;
  ::google::protobuf::uint64 update_timestamp_;
  friend struct ::protobuf_holo_2fmap_2fproto_2fhfl_2ftraffic_5fcondition_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// TrafficCondition

// optional uint64 traffic_condition_id = 1;
inline bool TrafficCondition::has_traffic_condition_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TrafficCondition::set_has_traffic_condition_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TrafficCondition::clear_has_traffic_condition_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TrafficCondition::clear_traffic_condition_id() {
  traffic_condition_id_ = GOOGLE_ULONGLONG(0);
  clear_has_traffic_condition_id();
}
inline ::google::protobuf::uint64 TrafficCondition::traffic_condition_id() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.hfl.TrafficCondition.traffic_condition_id)
  return traffic_condition_id_;
}
inline void TrafficCondition::set_traffic_condition_id(::google::protobuf::uint64 value) {
  set_has_traffic_condition_id();
  traffic_condition_id_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.hfl.TrafficCondition.traffic_condition_id)
}

// optional .holo.map.proto.hfl.TrafficCondition.TrafficType traffic_type = 2;
inline bool TrafficCondition::has_traffic_type() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void TrafficCondition::set_has_traffic_type() {
  _has_bits_[0] |= 0x00000004u;
}
inline void TrafficCondition::clear_has_traffic_type() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void TrafficCondition::clear_traffic_type() {
  traffic_type_ = 0;
  clear_has_traffic_type();
}
inline ::holo::map::proto::hfl::TrafficCondition_TrafficType TrafficCondition::traffic_type() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.hfl.TrafficCondition.traffic_type)
  return static_cast< ::holo::map::proto::hfl::TrafficCondition_TrafficType >(traffic_type_);
}
inline void TrafficCondition::set_traffic_type(::holo::map::proto::hfl::TrafficCondition_TrafficType value) {
  assert(::holo::map::proto::hfl::TrafficCondition_TrafficType_IsValid(value));
  set_has_traffic_type();
  traffic_type_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.hfl.TrafficCondition.traffic_type)
}

// repeated .holo.map.proto.common.IntervalFloat64 traffic_pos = 3;
inline int TrafficCondition::traffic_pos_size() const {
  return traffic_pos_.size();
}
inline ::holo::map::proto::common::IntervalFloat64* TrafficCondition::mutable_traffic_pos(int index) {
  // @@protoc_insertion_point(field_mutable:holo.map.proto.hfl.TrafficCondition.traffic_pos)
  return traffic_pos_.Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField< ::holo::map::proto::common::IntervalFloat64 >*
TrafficCondition::mutable_traffic_pos() {
  // @@protoc_insertion_point(field_mutable_list:holo.map.proto.hfl.TrafficCondition.traffic_pos)
  return &traffic_pos_;
}
inline const ::holo::map::proto::common::IntervalFloat64& TrafficCondition::traffic_pos(int index) const {
  // @@protoc_insertion_point(field_get:holo.map.proto.hfl.TrafficCondition.traffic_pos)
  return traffic_pos_.Get(index);
}
inline ::holo::map::proto::common::IntervalFloat64* TrafficCondition::add_traffic_pos() {
  // @@protoc_insertion_point(field_add:holo.map.proto.hfl.TrafficCondition.traffic_pos)
  return traffic_pos_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::holo::map::proto::common::IntervalFloat64 >&
TrafficCondition::traffic_pos() const {
  // @@protoc_insertion_point(field_list:holo.map.proto.hfl.TrafficCondition.traffic_pos)
  return traffic_pos_;
}

// optional .holo.map.proto.common.IntervalType traffic_pos_type = 4;
inline bool TrafficCondition::has_traffic_pos_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TrafficCondition::set_has_traffic_pos_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TrafficCondition::clear_has_traffic_pos_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline const ::holo::map::proto::common::IntervalType& TrafficCondition::_internal_traffic_pos_type() const {
  return *traffic_pos_type_;
}
inline const ::holo::map::proto::common::IntervalType& TrafficCondition::traffic_pos_type() const {
  const ::holo::map::proto::common::IntervalType* p = traffic_pos_type_;
  // @@protoc_insertion_point(field_get:holo.map.proto.hfl.TrafficCondition.traffic_pos_type)
  return p != NULL ? *p : *reinterpret_cast<const ::holo::map::proto::common::IntervalType*>(
      &::holo::map::proto::common::_IntervalType_default_instance_);
}
inline ::holo::map::proto::common::IntervalType* TrafficCondition::release_traffic_pos_type() {
  // @@protoc_insertion_point(field_release:holo.map.proto.hfl.TrafficCondition.traffic_pos_type)
  clear_has_traffic_pos_type();
  ::holo::map::proto::common::IntervalType* temp = traffic_pos_type_;
  traffic_pos_type_ = NULL;
  return temp;
}
inline ::holo::map::proto::common::IntervalType* TrafficCondition::mutable_traffic_pos_type() {
  set_has_traffic_pos_type();
  if (traffic_pos_type_ == NULL) {
    auto* p = CreateMaybeMessage<::holo::map::proto::common::IntervalType>(GetArenaNoVirtual());
    traffic_pos_type_ = p;
  }
  // @@protoc_insertion_point(field_mutable:holo.map.proto.hfl.TrafficCondition.traffic_pos_type)
  return traffic_pos_type_;
}
inline void TrafficCondition::set_allocated_traffic_pos_type(::holo::map::proto::common::IntervalType* traffic_pos_type) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete reinterpret_cast< ::google::protobuf::MessageLite*>(traffic_pos_type_);
  }
  if (traffic_pos_type) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      traffic_pos_type = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, traffic_pos_type, submessage_arena);
    }
    set_has_traffic_pos_type();
  } else {
    clear_has_traffic_pos_type();
  }
  traffic_pos_type_ = traffic_pos_type;
  // @@protoc_insertion_point(field_set_allocated:holo.map.proto.hfl.TrafficCondition.traffic_pos_type)
}

// optional uint32 width_cm = 5;
inline bool TrafficCondition::has_width_cm() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void TrafficCondition::set_has_width_cm() {
  _has_bits_[0] |= 0x00000008u;
}
inline void TrafficCondition::clear_has_width_cm() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void TrafficCondition::clear_width_cm() {
  width_cm_ = 0u;
  clear_has_width_cm();
}
inline ::google::protobuf::uint32 TrafficCondition::width_cm() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.hfl.TrafficCondition.width_cm)
  return width_cm_;
}
inline void TrafficCondition::set_width_cm(::google::protobuf::uint32 value) {
  set_has_width_cm();
  width_cm_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.hfl.TrafficCondition.width_cm)
}

// repeated .holo.map.proto.common.IntervalFloat64 exist_timestamp = 6;
inline int TrafficCondition::exist_timestamp_size() const {
  return exist_timestamp_.size();
}
inline ::holo::map::proto::common::IntervalFloat64* TrafficCondition::mutable_exist_timestamp(int index) {
  // @@protoc_insertion_point(field_mutable:holo.map.proto.hfl.TrafficCondition.exist_timestamp)
  return exist_timestamp_.Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField< ::holo::map::proto::common::IntervalFloat64 >*
TrafficCondition::mutable_exist_timestamp() {
  // @@protoc_insertion_point(field_mutable_list:holo.map.proto.hfl.TrafficCondition.exist_timestamp)
  return &exist_timestamp_;
}
inline const ::holo::map::proto::common::IntervalFloat64& TrafficCondition::exist_timestamp(int index) const {
  // @@protoc_insertion_point(field_get:holo.map.proto.hfl.TrafficCondition.exist_timestamp)
  return exist_timestamp_.Get(index);
}
inline ::holo::map::proto::common::IntervalFloat64* TrafficCondition::add_exist_timestamp() {
  // @@protoc_insertion_point(field_add:holo.map.proto.hfl.TrafficCondition.exist_timestamp)
  return exist_timestamp_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::holo::map::proto::common::IntervalFloat64 >&
TrafficCondition::exist_timestamp() const {
  // @@protoc_insertion_point(field_list:holo.map.proto.hfl.TrafficCondition.exist_timestamp)
  return exist_timestamp_;
}

// optional uint64 create_timestamp = 7;
inline bool TrafficCondition::has_create_timestamp() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void TrafficCondition::set_has_create_timestamp() {
  _has_bits_[0] |= 0x00000010u;
}
inline void TrafficCondition::clear_has_create_timestamp() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void TrafficCondition::clear_create_timestamp() {
  create_timestamp_ = GOOGLE_ULONGLONG(0);
  clear_has_create_timestamp();
}
inline ::google::protobuf::uint64 TrafficCondition::create_timestamp() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.hfl.TrafficCondition.create_timestamp)
  return create_timestamp_;
}
inline void TrafficCondition::set_create_timestamp(::google::protobuf::uint64 value) {
  set_has_create_timestamp();
  create_timestamp_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.hfl.TrafficCondition.create_timestamp)
}

// optional uint64 update_timestamp = 8;
inline bool TrafficCondition::has_update_timestamp() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void TrafficCondition::set_has_update_timestamp() {
  _has_bits_[0] |= 0x00000020u;
}
inline void TrafficCondition::clear_has_update_timestamp() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void TrafficCondition::clear_update_timestamp() {
  update_timestamp_ = GOOGLE_ULONGLONG(0);
  clear_has_update_timestamp();
}
inline ::google::protobuf::uint64 TrafficCondition::update_timestamp() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.hfl.TrafficCondition.update_timestamp)
  return update_timestamp_;
}
inline void TrafficCondition::set_update_timestamp(::google::protobuf::uint64 value) {
  set_has_update_timestamp();
  update_timestamp_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.hfl.TrafficCondition.update_timestamp)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace hfl
}  // namespace proto
}  // namespace map
}  // namespace holo

namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::holo::map::proto::hfl::TrafficCondition_TrafficType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::holo::map::proto::hfl::TrafficCondition_TrafficType>() {
  return ::holo::map::proto::hfl::TrafficCondition_TrafficType_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_holo_2fmap_2fproto_2fhfl_2ftraffic_5fcondition_2eproto
