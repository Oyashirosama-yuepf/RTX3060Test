// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: holo/map/proto/common/geo_point.proto

#ifndef PROTOBUF_INCLUDED_holo_2fmap_2fproto_2fcommon_2fgeo_5fpoint_2eproto
#define PROTOBUF_INCLUDED_holo_2fmap_2fproto_2fcommon_2fgeo_5fpoint_2eproto

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
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_holo_2fmap_2fproto_2fcommon_2fgeo_5fpoint_2eproto 

namespace protobuf_holo_2fmap_2fproto_2fcommon_2fgeo_5fpoint_2eproto {
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
}  // namespace protobuf_holo_2fmap_2fproto_2fcommon_2fgeo_5fpoint_2eproto
namespace holo {
namespace map {
namespace proto {
namespace common {
class GeoPoint;
class GeoPointDefaultTypeInternal;
extern GeoPointDefaultTypeInternal _GeoPoint_default_instance_;
}  // namespace common
}  // namespace proto
}  // namespace map
}  // namespace holo
namespace google {
namespace protobuf {
template<> ::holo::map::proto::common::GeoPoint* Arena::CreateMaybeMessage<::holo::map::proto::common::GeoPoint>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace holo {
namespace map {
namespace proto {
namespace common {

// ===================================================================

class GeoPoint : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:holo.map.proto.common.GeoPoint) */ {
 public:
  GeoPoint();
  virtual ~GeoPoint();

  GeoPoint(const GeoPoint& from);

  inline GeoPoint& operator=(const GeoPoint& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  GeoPoint(GeoPoint&& from) noexcept
    : GeoPoint() {
    *this = ::std::move(from);
  }

  inline GeoPoint& operator=(GeoPoint&& from) noexcept {
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
  static const GeoPoint& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const GeoPoint* internal_default_instance() {
    return reinterpret_cast<const GeoPoint*>(
               &_GeoPoint_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(GeoPoint* other);
  friend void swap(GeoPoint& a, GeoPoint& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline GeoPoint* New() const final {
    return CreateMaybeMessage<GeoPoint>(NULL);
  }

  GeoPoint* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<GeoPoint>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const GeoPoint& from);
  void MergeFrom(const GeoPoint& from);
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
  void InternalSwap(GeoPoint* other);
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

  // optional int64 height_cm = 3;
  bool has_height_cm() const;
  void clear_height_cm();
  static const int kHeightCmFieldNumber = 3;
  ::google::protobuf::int64 height_cm() const;
  void set_height_cm(::google::protobuf::int64 value);

  // optional double x = 4;
  bool has_x() const;
  void clear_x();
  static const int kXFieldNumber = 4;
  double x() const;
  void set_x(double value);

  // optional double y = 5;
  bool has_y() const;
  void clear_y();
  static const int kYFieldNumber = 5;
  double y() const;
  void set_y(double value);

  // @@protoc_insertion_point(class_scope:holo.map.proto.common.GeoPoint)
 private:
  void set_has_height_cm();
  void clear_has_height_cm();
  void set_has_x();
  void clear_has_x();
  void set_has_y();
  void clear_has_y();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::int64 height_cm_;
  double x_;
  double y_;
  friend struct ::protobuf_holo_2fmap_2fproto_2fcommon_2fgeo_5fpoint_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// GeoPoint

// optional int64 height_cm = 3;
inline bool GeoPoint::has_height_cm() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void GeoPoint::set_has_height_cm() {
  _has_bits_[0] |= 0x00000001u;
}
inline void GeoPoint::clear_has_height_cm() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void GeoPoint::clear_height_cm() {
  height_cm_ = GOOGLE_LONGLONG(0);
  clear_has_height_cm();
}
inline ::google::protobuf::int64 GeoPoint::height_cm() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.common.GeoPoint.height_cm)
  return height_cm_;
}
inline void GeoPoint::set_height_cm(::google::protobuf::int64 value) {
  set_has_height_cm();
  height_cm_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.common.GeoPoint.height_cm)
}

// optional double x = 4;
inline bool GeoPoint::has_x() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void GeoPoint::set_has_x() {
  _has_bits_[0] |= 0x00000002u;
}
inline void GeoPoint::clear_has_x() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void GeoPoint::clear_x() {
  x_ = 0;
  clear_has_x();
}
inline double GeoPoint::x() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.common.GeoPoint.x)
  return x_;
}
inline void GeoPoint::set_x(double value) {
  set_has_x();
  x_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.common.GeoPoint.x)
}

// optional double y = 5;
inline bool GeoPoint::has_y() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void GeoPoint::set_has_y() {
  _has_bits_[0] |= 0x00000004u;
}
inline void GeoPoint::clear_has_y() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void GeoPoint::clear_y() {
  y_ = 0;
  clear_has_y();
}
inline double GeoPoint::y() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.common.GeoPoint.y)
  return y_;
}
inline void GeoPoint::set_y(double value) {
  set_has_y();
  y_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.common.GeoPoint.y)
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

#endif  // PROTOBUF_INCLUDED_holo_2fmap_2fproto_2fcommon_2fgeo_5fpoint_2eproto