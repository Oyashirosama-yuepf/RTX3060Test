// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: holo/map/proto/common/geo_polygon.proto

#ifndef PROTOBUF_INCLUDED_holo_2fmap_2fproto_2fcommon_2fgeo_5fpolygon_2eproto
#define PROTOBUF_INCLUDED_holo_2fmap_2fproto_2fcommon_2fgeo_5fpolygon_2eproto

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
#include "holo/map/proto/common/geo_point.pb.h"
#include "holo/map/proto/common/geo_line.pb.h"
#include "holo/map/proto/common/geo_multi_line.pb.h"
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_holo_2fmap_2fproto_2fcommon_2fgeo_5fpolygon_2eproto 

namespace protobuf_holo_2fmap_2fproto_2fcommon_2fgeo_5fpolygon_2eproto {
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
}  // namespace protobuf_holo_2fmap_2fproto_2fcommon_2fgeo_5fpolygon_2eproto
namespace holo {
namespace map {
namespace proto {
namespace common {
class GeoPolygon;
class GeoPolygonDefaultTypeInternal;
extern GeoPolygonDefaultTypeInternal _GeoPolygon_default_instance_;
}  // namespace common
}  // namespace proto
}  // namespace map
}  // namespace holo
namespace google {
namespace protobuf {
template<> ::holo::map::proto::common::GeoPolygon* Arena::CreateMaybeMessage<::holo::map::proto::common::GeoPolygon>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace holo {
namespace map {
namespace proto {
namespace common {

// ===================================================================

class GeoPolygon : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:holo.map.proto.common.GeoPolygon) */ {
 public:
  GeoPolygon();
  virtual ~GeoPolygon();

  GeoPolygon(const GeoPolygon& from);

  inline GeoPolygon& operator=(const GeoPolygon& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  GeoPolygon(GeoPolygon&& from) noexcept
    : GeoPolygon() {
    *this = ::std::move(from);
  }

  inline GeoPolygon& operator=(GeoPolygon&& from) noexcept {
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
  static const GeoPolygon& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const GeoPolygon* internal_default_instance() {
    return reinterpret_cast<const GeoPolygon*>(
               &_GeoPolygon_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(GeoPolygon* other);
  friend void swap(GeoPolygon& a, GeoPolygon& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline GeoPolygon* New() const final {
    return CreateMaybeMessage<GeoPolygon>(NULL);
  }

  GeoPolygon* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<GeoPolygon>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const GeoPolygon& from);
  void MergeFrom(const GeoPolygon& from);
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
  void InternalSwap(GeoPolygon* other);
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

  // repeated .holo.map.proto.common.GeoPoint vertices = 1;
  int vertices_size() const;
  void clear_vertices();
  static const int kVerticesFieldNumber = 1;
  ::holo::map::proto::common::GeoPoint* mutable_vertices(int index);
  ::google::protobuf::RepeatedPtrField< ::holo::map::proto::common::GeoPoint >*
      mutable_vertices();
  const ::holo::map::proto::common::GeoPoint& vertices(int index) const;
  ::holo::map::proto::common::GeoPoint* add_vertices();
  const ::google::protobuf::RepeatedPtrField< ::holo::map::proto::common::GeoPoint >&
      vertices() const;

  // optional .holo.map.proto.common.GeoLine exterior_ring = 2;
  bool has_exterior_ring() const;
  void clear_exterior_ring();
  static const int kExteriorRingFieldNumber = 2;
  private:
  const ::holo::map::proto::common::GeoLine& _internal_exterior_ring() const;
  public:
  const ::holo::map::proto::common::GeoLine& exterior_ring() const;
  ::holo::map::proto::common::GeoLine* release_exterior_ring();
  ::holo::map::proto::common::GeoLine* mutable_exterior_ring();
  void set_allocated_exterior_ring(::holo::map::proto::common::GeoLine* exterior_ring);

  // optional .holo.map.proto.common.GeoMultiLine internal_rings = 3;
  bool has_internal_rings() const;
  void clear_internal_rings();
  static const int kInternalRingsFieldNumber = 3;
  private:
  const ::holo::map::proto::common::GeoMultiLine& _internal_internal_rings() const;
  public:
  const ::holo::map::proto::common::GeoMultiLine& internal_rings() const;
  ::holo::map::proto::common::GeoMultiLine* release_internal_rings();
  ::holo::map::proto::common::GeoMultiLine* mutable_internal_rings();
  void set_allocated_internal_rings(::holo::map::proto::common::GeoMultiLine* internal_rings);

  // @@protoc_insertion_point(class_scope:holo.map.proto.common.GeoPolygon)
 private:
  void set_has_exterior_ring();
  void clear_has_exterior_ring();
  void set_has_internal_rings();
  void clear_has_internal_rings();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::holo::map::proto::common::GeoPoint > vertices_;
  ::holo::map::proto::common::GeoLine* exterior_ring_;
  ::holo::map::proto::common::GeoMultiLine* internal_rings_;
  friend struct ::protobuf_holo_2fmap_2fproto_2fcommon_2fgeo_5fpolygon_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// GeoPolygon

// repeated .holo.map.proto.common.GeoPoint vertices = 1;
inline int GeoPolygon::vertices_size() const {
  return vertices_.size();
}
inline ::holo::map::proto::common::GeoPoint* GeoPolygon::mutable_vertices(int index) {
  // @@protoc_insertion_point(field_mutable:holo.map.proto.common.GeoPolygon.vertices)
  return vertices_.Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField< ::holo::map::proto::common::GeoPoint >*
GeoPolygon::mutable_vertices() {
  // @@protoc_insertion_point(field_mutable_list:holo.map.proto.common.GeoPolygon.vertices)
  return &vertices_;
}
inline const ::holo::map::proto::common::GeoPoint& GeoPolygon::vertices(int index) const {
  // @@protoc_insertion_point(field_get:holo.map.proto.common.GeoPolygon.vertices)
  return vertices_.Get(index);
}
inline ::holo::map::proto::common::GeoPoint* GeoPolygon::add_vertices() {
  // @@protoc_insertion_point(field_add:holo.map.proto.common.GeoPolygon.vertices)
  return vertices_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::holo::map::proto::common::GeoPoint >&
GeoPolygon::vertices() const {
  // @@protoc_insertion_point(field_list:holo.map.proto.common.GeoPolygon.vertices)
  return vertices_;
}

// optional .holo.map.proto.common.GeoLine exterior_ring = 2;
inline bool GeoPolygon::has_exterior_ring() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void GeoPolygon::set_has_exterior_ring() {
  _has_bits_[0] |= 0x00000001u;
}
inline void GeoPolygon::clear_has_exterior_ring() {
  _has_bits_[0] &= ~0x00000001u;
}
inline const ::holo::map::proto::common::GeoLine& GeoPolygon::_internal_exterior_ring() const {
  return *exterior_ring_;
}
inline const ::holo::map::proto::common::GeoLine& GeoPolygon::exterior_ring() const {
  const ::holo::map::proto::common::GeoLine* p = exterior_ring_;
  // @@protoc_insertion_point(field_get:holo.map.proto.common.GeoPolygon.exterior_ring)
  return p != NULL ? *p : *reinterpret_cast<const ::holo::map::proto::common::GeoLine*>(
      &::holo::map::proto::common::_GeoLine_default_instance_);
}
inline ::holo::map::proto::common::GeoLine* GeoPolygon::release_exterior_ring() {
  // @@protoc_insertion_point(field_release:holo.map.proto.common.GeoPolygon.exterior_ring)
  clear_has_exterior_ring();
  ::holo::map::proto::common::GeoLine* temp = exterior_ring_;
  exterior_ring_ = NULL;
  return temp;
}
inline ::holo::map::proto::common::GeoLine* GeoPolygon::mutable_exterior_ring() {
  set_has_exterior_ring();
  if (exterior_ring_ == NULL) {
    auto* p = CreateMaybeMessage<::holo::map::proto::common::GeoLine>(GetArenaNoVirtual());
    exterior_ring_ = p;
  }
  // @@protoc_insertion_point(field_mutable:holo.map.proto.common.GeoPolygon.exterior_ring)
  return exterior_ring_;
}
inline void GeoPolygon::set_allocated_exterior_ring(::holo::map::proto::common::GeoLine* exterior_ring) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete reinterpret_cast< ::google::protobuf::MessageLite*>(exterior_ring_);
  }
  if (exterior_ring) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      exterior_ring = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, exterior_ring, submessage_arena);
    }
    set_has_exterior_ring();
  } else {
    clear_has_exterior_ring();
  }
  exterior_ring_ = exterior_ring;
  // @@protoc_insertion_point(field_set_allocated:holo.map.proto.common.GeoPolygon.exterior_ring)
}

// optional .holo.map.proto.common.GeoMultiLine internal_rings = 3;
inline bool GeoPolygon::has_internal_rings() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void GeoPolygon::set_has_internal_rings() {
  _has_bits_[0] |= 0x00000002u;
}
inline void GeoPolygon::clear_has_internal_rings() {
  _has_bits_[0] &= ~0x00000002u;
}
inline const ::holo::map::proto::common::GeoMultiLine& GeoPolygon::_internal_internal_rings() const {
  return *internal_rings_;
}
inline const ::holo::map::proto::common::GeoMultiLine& GeoPolygon::internal_rings() const {
  const ::holo::map::proto::common::GeoMultiLine* p = internal_rings_;
  // @@protoc_insertion_point(field_get:holo.map.proto.common.GeoPolygon.internal_rings)
  return p != NULL ? *p : *reinterpret_cast<const ::holo::map::proto::common::GeoMultiLine*>(
      &::holo::map::proto::common::_GeoMultiLine_default_instance_);
}
inline ::holo::map::proto::common::GeoMultiLine* GeoPolygon::release_internal_rings() {
  // @@protoc_insertion_point(field_release:holo.map.proto.common.GeoPolygon.internal_rings)
  clear_has_internal_rings();
  ::holo::map::proto::common::GeoMultiLine* temp = internal_rings_;
  internal_rings_ = NULL;
  return temp;
}
inline ::holo::map::proto::common::GeoMultiLine* GeoPolygon::mutable_internal_rings() {
  set_has_internal_rings();
  if (internal_rings_ == NULL) {
    auto* p = CreateMaybeMessage<::holo::map::proto::common::GeoMultiLine>(GetArenaNoVirtual());
    internal_rings_ = p;
  }
  // @@protoc_insertion_point(field_mutable:holo.map.proto.common.GeoPolygon.internal_rings)
  return internal_rings_;
}
inline void GeoPolygon::set_allocated_internal_rings(::holo::map::proto::common::GeoMultiLine* internal_rings) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete reinterpret_cast< ::google::protobuf::MessageLite*>(internal_rings_);
  }
  if (internal_rings) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      internal_rings = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, internal_rings, submessage_arena);
    }
    set_has_internal_rings();
  } else {
    clear_has_internal_rings();
  }
  internal_rings_ = internal_rings;
  // @@protoc_insertion_point(field_set_allocated:holo.map.proto.common.GeoPolygon.internal_rings)
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

#endif  // PROTOBUF_INCLUDED_holo_2fmap_2fproto_2fcommon_2fgeo_5fpolygon_2eproto
