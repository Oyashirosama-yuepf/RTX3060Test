// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: holo/map/proto/common/multi_position.proto

#ifndef PROTOBUF_INCLUDED_holo_2fmap_2fproto_2fcommon_2fmulti_5fposition_2eproto
#define PROTOBUF_INCLUDED_holo_2fmap_2fproto_2fcommon_2fmulti_5fposition_2eproto

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
#include <google/protobuf/unknown_field_set.h>
#include "holo/map/proto/common/position.pb.h"
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_holo_2fmap_2fproto_2fcommon_2fmulti_5fposition_2eproto 

namespace protobuf_holo_2fmap_2fproto_2fcommon_2fmulti_5fposition_2eproto {
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
}  // namespace protobuf_holo_2fmap_2fproto_2fcommon_2fmulti_5fposition_2eproto
namespace holo {
namespace map {
namespace proto {
namespace common {
class MultiPosition;
class MultiPositionDefaultTypeInternal;
extern MultiPositionDefaultTypeInternal _MultiPosition_default_instance_;
}  // namespace common
}  // namespace proto
}  // namespace map
}  // namespace holo
namespace google {
namespace protobuf {
template<> ::holo::map::proto::common::MultiPosition* Arena::CreateMaybeMessage<::holo::map::proto::common::MultiPosition>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace holo {
namespace map {
namespace proto {
namespace common {

// ===================================================================

class MultiPosition : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:holo.map.proto.common.MultiPosition) */ {
 public:
  MultiPosition();
  virtual ~MultiPosition();

  MultiPosition(const MultiPosition& from);

  inline MultiPosition& operator=(const MultiPosition& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  MultiPosition(MultiPosition&& from) noexcept
    : MultiPosition() {
    *this = ::std::move(from);
  }

  inline MultiPosition& operator=(MultiPosition&& from) noexcept {
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
  static const MultiPosition& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const MultiPosition* internal_default_instance() {
    return reinterpret_cast<const MultiPosition*>(
               &_MultiPosition_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(MultiPosition* other);
  friend void swap(MultiPosition& a, MultiPosition& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline MultiPosition* New() const final {
    return CreateMaybeMessage<MultiPosition>(NULL);
  }

  MultiPosition* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<MultiPosition>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const MultiPosition& from);
  void MergeFrom(const MultiPosition& from);
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
  void InternalSwap(MultiPosition* other);
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

  // accessors -------------------------------------------------------

  // repeated .holo.map.proto.common.Position positions = 1;
  int positions_size() const;
  void clear_positions();
  static const int kPositionsFieldNumber = 1;
  ::holo::map::proto::common::Position* mutable_positions(int index);
  ::google::protobuf::RepeatedPtrField< ::holo::map::proto::common::Position >*
      mutable_positions();
  const ::holo::map::proto::common::Position& positions(int index) const;
  ::holo::map::proto::common::Position* add_positions();
  const ::google::protobuf::RepeatedPtrField< ::holo::map::proto::common::Position >&
      positions() const;

  // @@protoc_insertion_point(class_scope:holo.map.proto.common.MultiPosition)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::holo::map::proto::common::Position > positions_;
  friend struct ::protobuf_holo_2fmap_2fproto_2fcommon_2fmulti_5fposition_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// MultiPosition

// repeated .holo.map.proto.common.Position positions = 1;
inline int MultiPosition::positions_size() const {
  return positions_.size();
}
inline ::holo::map::proto::common::Position* MultiPosition::mutable_positions(int index) {
  // @@protoc_insertion_point(field_mutable:holo.map.proto.common.MultiPosition.positions)
  return positions_.Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField< ::holo::map::proto::common::Position >*
MultiPosition::mutable_positions() {
  // @@protoc_insertion_point(field_mutable_list:holo.map.proto.common.MultiPosition.positions)
  return &positions_;
}
inline const ::holo::map::proto::common::Position& MultiPosition::positions(int index) const {
  // @@protoc_insertion_point(field_get:holo.map.proto.common.MultiPosition.positions)
  return positions_.Get(index);
}
inline ::holo::map::proto::common::Position* MultiPosition::add_positions() {
  // @@protoc_insertion_point(field_add:holo.map.proto.common.MultiPosition.positions)
  return positions_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::holo::map::proto::common::Position >&
MultiPosition::positions() const {
  // @@protoc_insertion_point(field_list:holo.map.proto.common.MultiPosition.positions)
  return positions_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace common
}  // namespace proto
}  // namespace map
}  // namespace holo

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_holo_2fmap_2fproto_2fcommon_2fmulti_5fposition_2eproto
