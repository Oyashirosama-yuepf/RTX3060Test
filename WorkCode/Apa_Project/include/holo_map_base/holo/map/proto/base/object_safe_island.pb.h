// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: holo/map/proto/base/object_safe_island.proto

#ifndef PROTOBUF_INCLUDED_holo_2fmap_2fproto_2fbase_2fobject_5fsafe_5fisland_2eproto
#define PROTOBUF_INCLUDED_holo_2fmap_2fproto_2fbase_2fobject_5fsafe_5fisland_2eproto

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
#include <google/protobuf/map.h>  // IWYU pragma: export
#include <google/protobuf/map_entry.h>
#include <google/protobuf/map_field_inl.h>
#include <google/protobuf/unknown_field_set.h>
#include "holo/map/proto/common/coordinate.pb.h"
#include "holo/map/proto/common/geo_polygon.pb.h"
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_holo_2fmap_2fproto_2fbase_2fobject_5fsafe_5fisland_2eproto 

namespace protobuf_holo_2fmap_2fproto_2fbase_2fobject_5fsafe_5fisland_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[2];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_holo_2fmap_2fproto_2fbase_2fobject_5fsafe_5fisland_2eproto
namespace holo {
namespace map {
namespace proto {
namespace base {
class ObjectSafeIsland;
class ObjectSafeIslandDefaultTypeInternal;
extern ObjectSafeIslandDefaultTypeInternal _ObjectSafeIsland_default_instance_;
class ObjectSafeIsland_ExtraGeometryEntry_DoNotUse;
class ObjectSafeIsland_ExtraGeometryEntry_DoNotUseDefaultTypeInternal;
extern ObjectSafeIsland_ExtraGeometryEntry_DoNotUseDefaultTypeInternal _ObjectSafeIsland_ExtraGeometryEntry_DoNotUse_default_instance_;
}  // namespace base
}  // namespace proto
}  // namespace map
}  // namespace holo
namespace google {
namespace protobuf {
template<> ::holo::map::proto::base::ObjectSafeIsland* Arena::CreateMaybeMessage<::holo::map::proto::base::ObjectSafeIsland>(Arena*);
template<> ::holo::map::proto::base::ObjectSafeIsland_ExtraGeometryEntry_DoNotUse* Arena::CreateMaybeMessage<::holo::map::proto::base::ObjectSafeIsland_ExtraGeometryEntry_DoNotUse>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace holo {
namespace map {
namespace proto {
namespace base {

// ===================================================================

class ObjectSafeIsland_ExtraGeometryEntry_DoNotUse : public ::google::protobuf::internal::MapEntry<ObjectSafeIsland_ExtraGeometryEntry_DoNotUse, 
    ::google::protobuf::uint32, ::holo::map::proto::common::GeoPolygon,
    ::google::protobuf::internal::WireFormatLite::TYPE_UINT32,
    ::google::protobuf::internal::WireFormatLite::TYPE_MESSAGE,
    0 > {
public:
  typedef ::google::protobuf::internal::MapEntry<ObjectSafeIsland_ExtraGeometryEntry_DoNotUse, 
    ::google::protobuf::uint32, ::holo::map::proto::common::GeoPolygon,
    ::google::protobuf::internal::WireFormatLite::TYPE_UINT32,
    ::google::protobuf::internal::WireFormatLite::TYPE_MESSAGE,
    0 > SuperType;
  ObjectSafeIsland_ExtraGeometryEntry_DoNotUse();
  ObjectSafeIsland_ExtraGeometryEntry_DoNotUse(::google::protobuf::Arena* arena);
  void MergeFrom(const ObjectSafeIsland_ExtraGeometryEntry_DoNotUse& other);
  static const ObjectSafeIsland_ExtraGeometryEntry_DoNotUse* internal_default_instance() { return reinterpret_cast<const ObjectSafeIsland_ExtraGeometryEntry_DoNotUse*>(&_ObjectSafeIsland_ExtraGeometryEntry_DoNotUse_default_instance_); }
  void MergeFrom(const ::google::protobuf::Message& other) final;
  ::google::protobuf::Metadata GetMetadata() const;
};

// -------------------------------------------------------------------

class ObjectSafeIsland : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:holo.map.proto.base.ObjectSafeIsland) */ {
 public:
  ObjectSafeIsland();
  virtual ~ObjectSafeIsland();

  ObjectSafeIsland(const ObjectSafeIsland& from);

  inline ObjectSafeIsland& operator=(const ObjectSafeIsland& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  ObjectSafeIsland(ObjectSafeIsland&& from) noexcept
    : ObjectSafeIsland() {
    *this = ::std::move(from);
  }

  inline ObjectSafeIsland& operator=(ObjectSafeIsland&& from) noexcept {
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
  static const ObjectSafeIsland& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ObjectSafeIsland* internal_default_instance() {
    return reinterpret_cast<const ObjectSafeIsland*>(
               &_ObjectSafeIsland_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(ObjectSafeIsland* other);
  friend void swap(ObjectSafeIsland& a, ObjectSafeIsland& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline ObjectSafeIsland* New() const final {
    return CreateMaybeMessage<ObjectSafeIsland>(NULL);
  }

  ObjectSafeIsland* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<ObjectSafeIsland>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const ObjectSafeIsland& from);
  void MergeFrom(const ObjectSafeIsland& from);
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
  void InternalSwap(ObjectSafeIsland* other);
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

  // repeated uint64 tile_ids = 10 [packed = true];
  int tile_ids_size() const;
  void clear_tile_ids();
  static const int kTileIdsFieldNumber = 10;
  ::google::protobuf::uint64 tile_ids(int index) const;
  void set_tile_ids(int index, ::google::protobuf::uint64 value);
  void add_tile_ids(::google::protobuf::uint64 value);
  const ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >&
      tile_ids() const;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >*
      mutable_tile_ids();

  // repeated uint64 associated_lane_ids = 11 [packed = true];
  int associated_lane_ids_size() const;
  void clear_associated_lane_ids();
  static const int kAssociatedLaneIdsFieldNumber = 11;
  ::google::protobuf::uint64 associated_lane_ids(int index) const;
  void set_associated_lane_ids(int index, ::google::protobuf::uint64 value);
  void add_associated_lane_ids(::google::protobuf::uint64 value);
  const ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >&
      associated_lane_ids() const;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >*
      mutable_associated_lane_ids();

  // repeated uint64 associated_lane_group_ids = 12 [packed = true];
  int associated_lane_group_ids_size() const;
  void clear_associated_lane_group_ids();
  static const int kAssociatedLaneGroupIdsFieldNumber = 12;
  ::google::protobuf::uint64 associated_lane_group_ids(int index) const;
  void set_associated_lane_group_ids(int index, ::google::protobuf::uint64 value);
  void add_associated_lane_group_ids(::google::protobuf::uint64 value);
  const ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >&
      associated_lane_group_ids() const;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >*
      mutable_associated_lane_group_ids();

  // map<uint32, .holo.map.proto.common.GeoPolygon> extra_geometry = 24;
  int extra_geometry_size() const;
  void clear_extra_geometry();
  static const int kExtraGeometryFieldNumber = 24;
  const ::google::protobuf::Map< ::google::protobuf::uint32, ::holo::map::proto::common::GeoPolygon >&
      extra_geometry() const;
  ::google::protobuf::Map< ::google::protobuf::uint32, ::holo::map::proto::common::GeoPolygon >*
      mutable_extra_geometry();

  // optional .holo.map.proto.common.GeoPolygon geometry = 23;
  bool has_geometry() const;
  void clear_geometry();
  static const int kGeometryFieldNumber = 23;
  private:
  const ::holo::map::proto::common::GeoPolygon& _internal_geometry() const;
  public:
  const ::holo::map::proto::common::GeoPolygon& geometry() const;
  ::holo::map::proto::common::GeoPolygon* release_geometry();
  ::holo::map::proto::common::GeoPolygon* mutable_geometry();
  void set_allocated_geometry(::holo::map::proto::common::GeoPolygon* geometry);

  // optional .holo.map.proto.common.Coordinate coordinate = 25;
  bool has_coordinate() const;
  void clear_coordinate();
  static const int kCoordinateFieldNumber = 25;
  private:
  const ::holo::map::proto::common::Coordinate& _internal_coordinate() const;
  public:
  const ::holo::map::proto::common::Coordinate& coordinate() const;
  ::holo::map::proto::common::Coordinate* release_coordinate();
  ::holo::map::proto::common::Coordinate* mutable_coordinate();
  void set_allocated_coordinate(::holo::map::proto::common::Coordinate* coordinate);

  // optional uint64 object_safe_island_id = 1;
  bool has_object_safe_island_id() const;
  void clear_object_safe_island_id();
  static const int kObjectSafeIslandIdFieldNumber = 1;
  ::google::protobuf::uint64 object_safe_island_id() const;
  void set_object_safe_island_id(::google::protobuf::uint64 value);

  // optional bool is_moveable = 2;
  bool has_is_moveable() const;
  void clear_is_moveable();
  static const int kIsMoveableFieldNumber = 2;
  bool is_moveable() const;
  void set_is_moveable(bool value);

  // optional bool is_passable = 3;
  bool has_is_passable() const;
  void clear_is_passable();
  static const int kIsPassableFieldNumber = 3;
  bool is_passable() const;
  void set_is_passable(bool value);

  // optional bool south_flag = 22;
  bool has_south_flag() const;
  void clear_south_flag();
  static const int kSouthFlagFieldNumber = 22;
  bool south_flag() const;
  void set_south_flag(bool value);

  // optional uint32 zone_id = 20;
  bool has_zone_id() const;
  void clear_zone_id();
  static const int kZoneIdFieldNumber = 20;
  ::google::protobuf::uint32 zone_id() const;
  void set_zone_id(::google::protobuf::uint32 value);

  // optional uint32 extra_zone_id = 21;
  bool has_extra_zone_id() const;
  void clear_extra_zone_id();
  static const int kExtraZoneIdFieldNumber = 21;
  ::google::protobuf::uint32 extra_zone_id() const;
  void set_extra_zone_id(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:holo.map.proto.base.ObjectSafeIsland)
 private:
  void set_has_object_safe_island_id();
  void clear_has_object_safe_island_id();
  void set_has_is_moveable();
  void clear_has_is_moveable();
  void set_has_is_passable();
  void clear_has_is_passable();
  void set_has_zone_id();
  void clear_has_zone_id();
  void set_has_extra_zone_id();
  void clear_has_extra_zone_id();
  void set_has_south_flag();
  void clear_has_south_flag();
  void set_has_geometry();
  void clear_has_geometry();
  void set_has_coordinate();
  void clear_has_coordinate();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint64 > tile_ids_;
  mutable int _tile_ids_cached_byte_size_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint64 > associated_lane_ids_;
  mutable int _associated_lane_ids_cached_byte_size_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint64 > associated_lane_group_ids_;
  mutable int _associated_lane_group_ids_cached_byte_size_;
  ::google::protobuf::internal::MapField<
      ObjectSafeIsland_ExtraGeometryEntry_DoNotUse,
      ::google::protobuf::uint32, ::holo::map::proto::common::GeoPolygon,
      ::google::protobuf::internal::WireFormatLite::TYPE_UINT32,
      ::google::protobuf::internal::WireFormatLite::TYPE_MESSAGE,
      0 > extra_geometry_;
  ::holo::map::proto::common::GeoPolygon* geometry_;
  ::holo::map::proto::common::Coordinate* coordinate_;
  ::google::protobuf::uint64 object_safe_island_id_;
  bool is_moveable_;
  bool is_passable_;
  bool south_flag_;
  ::google::protobuf::uint32 zone_id_;
  ::google::protobuf::uint32 extra_zone_id_;
  friend struct ::protobuf_holo_2fmap_2fproto_2fbase_2fobject_5fsafe_5fisland_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// ObjectSafeIsland

// optional uint64 object_safe_island_id = 1;
inline bool ObjectSafeIsland::has_object_safe_island_id() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ObjectSafeIsland::set_has_object_safe_island_id() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ObjectSafeIsland::clear_has_object_safe_island_id() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ObjectSafeIsland::clear_object_safe_island_id() {
  object_safe_island_id_ = GOOGLE_ULONGLONG(0);
  clear_has_object_safe_island_id();
}
inline ::google::protobuf::uint64 ObjectSafeIsland::object_safe_island_id() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.base.ObjectSafeIsland.object_safe_island_id)
  return object_safe_island_id_;
}
inline void ObjectSafeIsland::set_object_safe_island_id(::google::protobuf::uint64 value) {
  set_has_object_safe_island_id();
  object_safe_island_id_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.base.ObjectSafeIsland.object_safe_island_id)
}

// optional bool is_moveable = 2;
inline bool ObjectSafeIsland::has_is_moveable() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void ObjectSafeIsland::set_has_is_moveable() {
  _has_bits_[0] |= 0x00000008u;
}
inline void ObjectSafeIsland::clear_has_is_moveable() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void ObjectSafeIsland::clear_is_moveable() {
  is_moveable_ = false;
  clear_has_is_moveable();
}
inline bool ObjectSafeIsland::is_moveable() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.base.ObjectSafeIsland.is_moveable)
  return is_moveable_;
}
inline void ObjectSafeIsland::set_is_moveable(bool value) {
  set_has_is_moveable();
  is_moveable_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.base.ObjectSafeIsland.is_moveable)
}

// optional bool is_passable = 3;
inline bool ObjectSafeIsland::has_is_passable() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void ObjectSafeIsland::set_has_is_passable() {
  _has_bits_[0] |= 0x00000010u;
}
inline void ObjectSafeIsland::clear_has_is_passable() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void ObjectSafeIsland::clear_is_passable() {
  is_passable_ = false;
  clear_has_is_passable();
}
inline bool ObjectSafeIsland::is_passable() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.base.ObjectSafeIsland.is_passable)
  return is_passable_;
}
inline void ObjectSafeIsland::set_is_passable(bool value) {
  set_has_is_passable();
  is_passable_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.base.ObjectSafeIsland.is_passable)
}

// repeated uint64 tile_ids = 10 [packed = true];
inline int ObjectSafeIsland::tile_ids_size() const {
  return tile_ids_.size();
}
inline void ObjectSafeIsland::clear_tile_ids() {
  tile_ids_.Clear();
}
inline ::google::protobuf::uint64 ObjectSafeIsland::tile_ids(int index) const {
  // @@protoc_insertion_point(field_get:holo.map.proto.base.ObjectSafeIsland.tile_ids)
  return tile_ids_.Get(index);
}
inline void ObjectSafeIsland::set_tile_ids(int index, ::google::protobuf::uint64 value) {
  tile_ids_.Set(index, value);
  // @@protoc_insertion_point(field_set:holo.map.proto.base.ObjectSafeIsland.tile_ids)
}
inline void ObjectSafeIsland::add_tile_ids(::google::protobuf::uint64 value) {
  tile_ids_.Add(value);
  // @@protoc_insertion_point(field_add:holo.map.proto.base.ObjectSafeIsland.tile_ids)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >&
ObjectSafeIsland::tile_ids() const {
  // @@protoc_insertion_point(field_list:holo.map.proto.base.ObjectSafeIsland.tile_ids)
  return tile_ids_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >*
ObjectSafeIsland::mutable_tile_ids() {
  // @@protoc_insertion_point(field_mutable_list:holo.map.proto.base.ObjectSafeIsland.tile_ids)
  return &tile_ids_;
}

// repeated uint64 associated_lane_ids = 11 [packed = true];
inline int ObjectSafeIsland::associated_lane_ids_size() const {
  return associated_lane_ids_.size();
}
inline void ObjectSafeIsland::clear_associated_lane_ids() {
  associated_lane_ids_.Clear();
}
inline ::google::protobuf::uint64 ObjectSafeIsland::associated_lane_ids(int index) const {
  // @@protoc_insertion_point(field_get:holo.map.proto.base.ObjectSafeIsland.associated_lane_ids)
  return associated_lane_ids_.Get(index);
}
inline void ObjectSafeIsland::set_associated_lane_ids(int index, ::google::protobuf::uint64 value) {
  associated_lane_ids_.Set(index, value);
  // @@protoc_insertion_point(field_set:holo.map.proto.base.ObjectSafeIsland.associated_lane_ids)
}
inline void ObjectSafeIsland::add_associated_lane_ids(::google::protobuf::uint64 value) {
  associated_lane_ids_.Add(value);
  // @@protoc_insertion_point(field_add:holo.map.proto.base.ObjectSafeIsland.associated_lane_ids)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >&
ObjectSafeIsland::associated_lane_ids() const {
  // @@protoc_insertion_point(field_list:holo.map.proto.base.ObjectSafeIsland.associated_lane_ids)
  return associated_lane_ids_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >*
ObjectSafeIsland::mutable_associated_lane_ids() {
  // @@protoc_insertion_point(field_mutable_list:holo.map.proto.base.ObjectSafeIsland.associated_lane_ids)
  return &associated_lane_ids_;
}

// repeated uint64 associated_lane_group_ids = 12 [packed = true];
inline int ObjectSafeIsland::associated_lane_group_ids_size() const {
  return associated_lane_group_ids_.size();
}
inline void ObjectSafeIsland::clear_associated_lane_group_ids() {
  associated_lane_group_ids_.Clear();
}
inline ::google::protobuf::uint64 ObjectSafeIsland::associated_lane_group_ids(int index) const {
  // @@protoc_insertion_point(field_get:holo.map.proto.base.ObjectSafeIsland.associated_lane_group_ids)
  return associated_lane_group_ids_.Get(index);
}
inline void ObjectSafeIsland::set_associated_lane_group_ids(int index, ::google::protobuf::uint64 value) {
  associated_lane_group_ids_.Set(index, value);
  // @@protoc_insertion_point(field_set:holo.map.proto.base.ObjectSafeIsland.associated_lane_group_ids)
}
inline void ObjectSafeIsland::add_associated_lane_group_ids(::google::protobuf::uint64 value) {
  associated_lane_group_ids_.Add(value);
  // @@protoc_insertion_point(field_add:holo.map.proto.base.ObjectSafeIsland.associated_lane_group_ids)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >&
ObjectSafeIsland::associated_lane_group_ids() const {
  // @@protoc_insertion_point(field_list:holo.map.proto.base.ObjectSafeIsland.associated_lane_group_ids)
  return associated_lane_group_ids_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >*
ObjectSafeIsland::mutable_associated_lane_group_ids() {
  // @@protoc_insertion_point(field_mutable_list:holo.map.proto.base.ObjectSafeIsland.associated_lane_group_ids)
  return &associated_lane_group_ids_;
}

// optional uint32 zone_id = 20;
inline bool ObjectSafeIsland::has_zone_id() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void ObjectSafeIsland::set_has_zone_id() {
  _has_bits_[0] |= 0x00000040u;
}
inline void ObjectSafeIsland::clear_has_zone_id() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void ObjectSafeIsland::clear_zone_id() {
  zone_id_ = 0u;
  clear_has_zone_id();
}
inline ::google::protobuf::uint32 ObjectSafeIsland::zone_id() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.base.ObjectSafeIsland.zone_id)
  return zone_id_;
}
inline void ObjectSafeIsland::set_zone_id(::google::protobuf::uint32 value) {
  set_has_zone_id();
  zone_id_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.base.ObjectSafeIsland.zone_id)
}

// optional uint32 extra_zone_id = 21;
inline bool ObjectSafeIsland::has_extra_zone_id() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void ObjectSafeIsland::set_has_extra_zone_id() {
  _has_bits_[0] |= 0x00000080u;
}
inline void ObjectSafeIsland::clear_has_extra_zone_id() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void ObjectSafeIsland::clear_extra_zone_id() {
  extra_zone_id_ = 0u;
  clear_has_extra_zone_id();
}
inline ::google::protobuf::uint32 ObjectSafeIsland::extra_zone_id() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.base.ObjectSafeIsland.extra_zone_id)
  return extra_zone_id_;
}
inline void ObjectSafeIsland::set_extra_zone_id(::google::protobuf::uint32 value) {
  set_has_extra_zone_id();
  extra_zone_id_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.base.ObjectSafeIsland.extra_zone_id)
}

// optional bool south_flag = 22;
inline bool ObjectSafeIsland::has_south_flag() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void ObjectSafeIsland::set_has_south_flag() {
  _has_bits_[0] |= 0x00000020u;
}
inline void ObjectSafeIsland::clear_has_south_flag() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void ObjectSafeIsland::clear_south_flag() {
  south_flag_ = false;
  clear_has_south_flag();
}
inline bool ObjectSafeIsland::south_flag() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.base.ObjectSafeIsland.south_flag)
  return south_flag_;
}
inline void ObjectSafeIsland::set_south_flag(bool value) {
  set_has_south_flag();
  south_flag_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.base.ObjectSafeIsland.south_flag)
}

// optional .holo.map.proto.common.GeoPolygon geometry = 23;
inline bool ObjectSafeIsland::has_geometry() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ObjectSafeIsland::set_has_geometry() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ObjectSafeIsland::clear_has_geometry() {
  _has_bits_[0] &= ~0x00000001u;
}
inline const ::holo::map::proto::common::GeoPolygon& ObjectSafeIsland::_internal_geometry() const {
  return *geometry_;
}
inline const ::holo::map::proto::common::GeoPolygon& ObjectSafeIsland::geometry() const {
  const ::holo::map::proto::common::GeoPolygon* p = geometry_;
  // @@protoc_insertion_point(field_get:holo.map.proto.base.ObjectSafeIsland.geometry)
  return p != NULL ? *p : *reinterpret_cast<const ::holo::map::proto::common::GeoPolygon*>(
      &::holo::map::proto::common::_GeoPolygon_default_instance_);
}
inline ::holo::map::proto::common::GeoPolygon* ObjectSafeIsland::release_geometry() {
  // @@protoc_insertion_point(field_release:holo.map.proto.base.ObjectSafeIsland.geometry)
  clear_has_geometry();
  ::holo::map::proto::common::GeoPolygon* temp = geometry_;
  geometry_ = NULL;
  return temp;
}
inline ::holo::map::proto::common::GeoPolygon* ObjectSafeIsland::mutable_geometry() {
  set_has_geometry();
  if (geometry_ == NULL) {
    auto* p = CreateMaybeMessage<::holo::map::proto::common::GeoPolygon>(GetArenaNoVirtual());
    geometry_ = p;
  }
  // @@protoc_insertion_point(field_mutable:holo.map.proto.base.ObjectSafeIsland.geometry)
  return geometry_;
}
inline void ObjectSafeIsland::set_allocated_geometry(::holo::map::proto::common::GeoPolygon* geometry) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete reinterpret_cast< ::google::protobuf::MessageLite*>(geometry_);
  }
  if (geometry) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      geometry = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, geometry, submessage_arena);
    }
    set_has_geometry();
  } else {
    clear_has_geometry();
  }
  geometry_ = geometry;
  // @@protoc_insertion_point(field_set_allocated:holo.map.proto.base.ObjectSafeIsland.geometry)
}

// map<uint32, .holo.map.proto.common.GeoPolygon> extra_geometry = 24;
inline int ObjectSafeIsland::extra_geometry_size() const {
  return extra_geometry_.size();
}
inline const ::google::protobuf::Map< ::google::protobuf::uint32, ::holo::map::proto::common::GeoPolygon >&
ObjectSafeIsland::extra_geometry() const {
  // @@protoc_insertion_point(field_map:holo.map.proto.base.ObjectSafeIsland.extra_geometry)
  return extra_geometry_.GetMap();
}
inline ::google::protobuf::Map< ::google::protobuf::uint32, ::holo::map::proto::common::GeoPolygon >*
ObjectSafeIsland::mutable_extra_geometry() {
  // @@protoc_insertion_point(field_mutable_map:holo.map.proto.base.ObjectSafeIsland.extra_geometry)
  return extra_geometry_.MutableMap();
}

// optional .holo.map.proto.common.Coordinate coordinate = 25;
inline bool ObjectSafeIsland::has_coordinate() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ObjectSafeIsland::set_has_coordinate() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ObjectSafeIsland::clear_has_coordinate() {
  _has_bits_[0] &= ~0x00000002u;
}
inline const ::holo::map::proto::common::Coordinate& ObjectSafeIsland::_internal_coordinate() const {
  return *coordinate_;
}
inline const ::holo::map::proto::common::Coordinate& ObjectSafeIsland::coordinate() const {
  const ::holo::map::proto::common::Coordinate* p = coordinate_;
  // @@protoc_insertion_point(field_get:holo.map.proto.base.ObjectSafeIsland.coordinate)
  return p != NULL ? *p : *reinterpret_cast<const ::holo::map::proto::common::Coordinate*>(
      &::holo::map::proto::common::_Coordinate_default_instance_);
}
inline ::holo::map::proto::common::Coordinate* ObjectSafeIsland::release_coordinate() {
  // @@protoc_insertion_point(field_release:holo.map.proto.base.ObjectSafeIsland.coordinate)
  clear_has_coordinate();
  ::holo::map::proto::common::Coordinate* temp = coordinate_;
  coordinate_ = NULL;
  return temp;
}
inline ::holo::map::proto::common::Coordinate* ObjectSafeIsland::mutable_coordinate() {
  set_has_coordinate();
  if (coordinate_ == NULL) {
    auto* p = CreateMaybeMessage<::holo::map::proto::common::Coordinate>(GetArenaNoVirtual());
    coordinate_ = p;
  }
  // @@protoc_insertion_point(field_mutable:holo.map.proto.base.ObjectSafeIsland.coordinate)
  return coordinate_;
}
inline void ObjectSafeIsland::set_allocated_coordinate(::holo::map::proto::common::Coordinate* coordinate) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete reinterpret_cast< ::google::protobuf::MessageLite*>(coordinate_);
  }
  if (coordinate) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      coordinate = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, coordinate, submessage_arena);
    }
    set_has_coordinate();
  } else {
    clear_has_coordinate();
  }
  coordinate_ = coordinate;
  // @@protoc_insertion_point(field_set_allocated:holo.map.proto.base.ObjectSafeIsland.coordinate)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace base
}  // namespace proto
}  // namespace map
}  // namespace holo

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_holo_2fmap_2fproto_2fbase_2fobject_5fsafe_5fisland_2eproto