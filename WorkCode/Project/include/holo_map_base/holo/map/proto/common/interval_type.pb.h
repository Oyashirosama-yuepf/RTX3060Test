// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: holo/map/proto/common/interval_type.proto

#ifndef PROTOBUF_INCLUDED_holo_2fmap_2fproto_2fcommon_2finterval_5ftype_2eproto
#define PROTOBUF_INCLUDED_holo_2fmap_2fproto_2fcommon_2finterval_5ftype_2eproto

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
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_holo_2fmap_2fproto_2fcommon_2finterval_5ftype_2eproto 

namespace protobuf_holo_2fmap_2fproto_2fcommon_2finterval_5ftype_2eproto {
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
}  // namespace protobuf_holo_2fmap_2fproto_2fcommon_2finterval_5ftype_2eproto
namespace holo {
namespace map {
namespace proto {
namespace common {
class IntervalType;
class IntervalTypeDefaultTypeInternal;
extern IntervalTypeDefaultTypeInternal _IntervalType_default_instance_;
}  // namespace common
}  // namespace proto
}  // namespace map
}  // namespace holo
namespace google {
namespace protobuf {
template<> ::holo::map::proto::common::IntervalType* Arena::CreateMaybeMessage<::holo::map::proto::common::IntervalType>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace holo {
namespace map {
namespace proto {
namespace common {

enum IntervalType_Type {
  IntervalType_Type_TYPE_UNDEFINED = 0,
  IntervalType_Type_TYPE_INVALID = 1,
  IntervalType_Type_TYPE_INDEX = 2,
  IntervalType_Type_TYPE_PERCENT = 3,
  IntervalType_Type_TYPE_DISTANCE = 4,
  IntervalType_Type_TYPE_AT_TAIL = 5,
  IntervalType_Type_TYPE_AT_HEAD = 6
};
bool IntervalType_Type_IsValid(int value);
const IntervalType_Type IntervalType_Type_Type_MIN = IntervalType_Type_TYPE_UNDEFINED;
const IntervalType_Type IntervalType_Type_Type_MAX = IntervalType_Type_TYPE_AT_HEAD;
const int IntervalType_Type_Type_ARRAYSIZE = IntervalType_Type_Type_MAX + 1;

const ::google::protobuf::EnumDescriptor* IntervalType_Type_descriptor();
inline const ::std::string& IntervalType_Type_Name(IntervalType_Type value) {
  return ::google::protobuf::internal::NameOfEnum(
    IntervalType_Type_descriptor(), value);
}
inline bool IntervalType_Type_Parse(
    const ::std::string& name, IntervalType_Type* value) {
  return ::google::protobuf::internal::ParseNamedEnum<IntervalType_Type>(
    IntervalType_Type_descriptor(), name, value);
}
// ===================================================================

class IntervalType : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:holo.map.proto.common.IntervalType) */ {
 public:
  IntervalType();
  virtual ~IntervalType();

  IntervalType(const IntervalType& from);

  inline IntervalType& operator=(const IntervalType& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  IntervalType(IntervalType&& from) noexcept
    : IntervalType() {
    *this = ::std::move(from);
  }

  inline IntervalType& operator=(IntervalType&& from) noexcept {
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
  static const IntervalType& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const IntervalType* internal_default_instance() {
    return reinterpret_cast<const IntervalType*>(
               &_IntervalType_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(IntervalType* other);
  friend void swap(IntervalType& a, IntervalType& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline IntervalType* New() const final {
    return CreateMaybeMessage<IntervalType>(NULL);
  }

  IntervalType* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<IntervalType>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const IntervalType& from);
  void MergeFrom(const IntervalType& from);
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
  void InternalSwap(IntervalType* other);
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

  typedef IntervalType_Type Type;
  static const Type TYPE_UNDEFINED =
    IntervalType_Type_TYPE_UNDEFINED;
  static const Type TYPE_INVALID =
    IntervalType_Type_TYPE_INVALID;
  static const Type TYPE_INDEX =
    IntervalType_Type_TYPE_INDEX;
  static const Type TYPE_PERCENT =
    IntervalType_Type_TYPE_PERCENT;
  static const Type TYPE_DISTANCE =
    IntervalType_Type_TYPE_DISTANCE;
  static const Type TYPE_AT_TAIL =
    IntervalType_Type_TYPE_AT_TAIL;
  static const Type TYPE_AT_HEAD =
    IntervalType_Type_TYPE_AT_HEAD;
  static inline bool Type_IsValid(int value) {
    return IntervalType_Type_IsValid(value);
  }
  static const Type Type_MIN =
    IntervalType_Type_Type_MIN;
  static const Type Type_MAX =
    IntervalType_Type_Type_MAX;
  static const int Type_ARRAYSIZE =
    IntervalType_Type_Type_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Type_descriptor() {
    return IntervalType_Type_descriptor();
  }
  static inline const ::std::string& Type_Name(Type value) {
    return IntervalType_Type_Name(value);
  }
  static inline bool Type_Parse(const ::std::string& name,
      Type* value) {
    return IntervalType_Type_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // optional .holo.map.proto.common.IntervalType.Type type = 1;
  bool has_type() const;
  void clear_type();
  static const int kTypeFieldNumber = 1;
  ::holo::map::proto::common::IntervalType_Type type() const;
  void set_type(::holo::map::proto::common::IntervalType_Type value);

  // @@protoc_insertion_point(class_scope:holo.map.proto.common.IntervalType)
 private:
  void set_has_type();
  void clear_has_type();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  int type_;
  friend struct ::protobuf_holo_2fmap_2fproto_2fcommon_2finterval_5ftype_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// IntervalType

// optional .holo.map.proto.common.IntervalType.Type type = 1;
inline bool IntervalType::has_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void IntervalType::set_has_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void IntervalType::clear_has_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void IntervalType::clear_type() {
  type_ = 0;
  clear_has_type();
}
inline ::holo::map::proto::common::IntervalType_Type IntervalType::type() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.common.IntervalType.type)
  return static_cast< ::holo::map::proto::common::IntervalType_Type >(type_);
}
inline void IntervalType::set_type(::holo::map::proto::common::IntervalType_Type value) {
  assert(::holo::map::proto::common::IntervalType_Type_IsValid(value));
  set_has_type();
  type_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.common.IntervalType.type)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace common
}  // namespace proto
}  // namespace map
}  // namespace holo

namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::holo::map::proto::common::IntervalType_Type> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::holo::map::proto::common::IntervalType_Type>() {
  return ::holo::map::proto::common::IntervalType_Type_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_holo_2fmap_2fproto_2fcommon_2finterval_5ftype_2eproto
