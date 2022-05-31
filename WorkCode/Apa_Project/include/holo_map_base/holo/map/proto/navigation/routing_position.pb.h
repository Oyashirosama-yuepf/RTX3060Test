// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: holo/map/proto/navigation/routing_position.proto

#ifndef PROTOBUF_INCLUDED_holo_2fmap_2fproto_2fnavigation_2frouting_5fposition_2eproto
#define PROTOBUF_INCLUDED_holo_2fmap_2fproto_2fnavigation_2frouting_5fposition_2eproto

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
#include "holo/map/proto/common/coordinate.pb.h"
#include "holo/map/proto/common/geo_point.pb.h"
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_holo_2fmap_2fproto_2fnavigation_2frouting_5fposition_2eproto 

namespace protobuf_holo_2fmap_2fproto_2fnavigation_2frouting_5fposition_2eproto {
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
}  // namespace protobuf_holo_2fmap_2fproto_2fnavigation_2frouting_5fposition_2eproto
namespace holo {
namespace map {
namespace proto {
namespace navigation {
class RoutingPosition;
class RoutingPositionDefaultTypeInternal;
extern RoutingPositionDefaultTypeInternal _RoutingPosition_default_instance_;
}  // namespace navigation
}  // namespace proto
}  // namespace map
}  // namespace holo
namespace google {
namespace protobuf {
template<> ::holo::map::proto::navigation::RoutingPosition* Arena::CreateMaybeMessage<::holo::map::proto::navigation::RoutingPosition>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace holo {
namespace map {
namespace proto {
namespace navigation {

// ===================================================================

class RoutingPosition : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:holo.map.proto.navigation.RoutingPosition) */ {
 public:
  RoutingPosition();
  virtual ~RoutingPosition();

  RoutingPosition(const RoutingPosition& from);

  inline RoutingPosition& operator=(const RoutingPosition& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  RoutingPosition(RoutingPosition&& from) noexcept
    : RoutingPosition() {
    *this = ::std::move(from);
  }

  inline RoutingPosition& operator=(RoutingPosition&& from) noexcept {
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
  static const RoutingPosition& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const RoutingPosition* internal_default_instance() {
    return reinterpret_cast<const RoutingPosition*>(
               &_RoutingPosition_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(RoutingPosition* other);
  friend void swap(RoutingPosition& a, RoutingPosition& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline RoutingPosition* New() const final {
    return CreateMaybeMessage<RoutingPosition>(NULL);
  }

  RoutingPosition* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<RoutingPosition>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const RoutingPosition& from);
  void MergeFrom(const RoutingPosition& from);
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
  void InternalSwap(RoutingPosition* other);
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

  // optional .holo.map.proto.common.Coordinate coordinate = 1;
  bool has_coordinate() const;
  void clear_coordinate();
  static const int kCoordinateFieldNumber = 1;
  private:
  const ::holo::map::proto::common::Coordinate& _internal_coordinate() const;
  public:
  const ::holo::map::proto::common::Coordinate& coordinate() const;
  ::holo::map::proto::common::Coordinate* release_coordinate();
  ::holo::map::proto::common::Coordinate* mutable_coordinate();
  void set_allocated_coordinate(::holo::map::proto::common::Coordinate* coordinate);

  // optional .holo.map.proto.common.GeoPoint pos_position = 4;
  bool has_pos_position() const;
  void clear_pos_position();
  static const int kPosPositionFieldNumber = 4;
  private:
  const ::holo::map::proto::common::GeoPoint& _internal_pos_position() const;
  public:
  const ::holo::map::proto::common::GeoPoint& pos_position() const;
  ::holo::map::proto::common::GeoPoint* release_pos_position();
  ::holo::map::proto::common::GeoPoint* mutable_pos_position();
  void set_allocated_pos_position(::holo::map::proto::common::GeoPoint* pos_position);

  // optional uint32 pos_zone_id = 2;
  bool has_pos_zone_id() const;
  void clear_pos_zone_id();
  static const int kPosZoneIdFieldNumber = 2;
  ::google::protobuf::uint32 pos_zone_id() const;
  void set_pos_zone_id(::google::protobuf::uint32 value);

  // optional bool pos_south_flag = 3;
  bool has_pos_south_flag() const;
  void clear_pos_south_flag();
  static const int kPosSouthFlagFieldNumber = 3;
  bool pos_south_flag() const;
  void set_pos_south_flag(bool value);

  // optional uint64 poi_id = 5;
  bool has_poi_id() const;
  void clear_poi_id();
  static const int kPoiIdFieldNumber = 5;
  ::google::protobuf::uint64 poi_id() const;
  void set_poi_id(::google::protobuf::uint64 value);

  // optional uint64 link_id = 10;
  bool has_link_id() const;
  void clear_link_id();
  static const int kLinkIdFieldNumber = 10;
  ::google::protobuf::uint64 link_id() const;
  void set_link_id(::google::protobuf::uint64 value);

  // optional uint32 distance_cm = 20;
  bool has_distance_cm() const;
  void clear_distance_cm();
  static const int kDistanceCmFieldNumber = 20;
  ::google::protobuf::uint32 distance_cm() const;
  void set_distance_cm(::google::protobuf::uint32 value);

  // optional uint64 object_parking_floor_id = 11;
  bool has_object_parking_floor_id() const;
  void clear_object_parking_floor_id();
  static const int kObjectParkingFloorIdFieldNumber = 11;
  ::google::protobuf::uint64 object_parking_floor_id() const;
  void set_object_parking_floor_id(::google::protobuf::uint64 value);

  // optional uint64 object_parking_lot_id = 12;
  bool has_object_parking_lot_id() const;
  void clear_object_parking_lot_id();
  static const int kObjectParkingLotIdFieldNumber = 12;
  ::google::protobuf::uint64 object_parking_lot_id() const;
  void set_object_parking_lot_id(::google::protobuf::uint64 value);

  // @@protoc_insertion_point(class_scope:holo.map.proto.navigation.RoutingPosition)
 private:
  void set_has_coordinate();
  void clear_has_coordinate();
  void set_has_pos_zone_id();
  void clear_has_pos_zone_id();
  void set_has_pos_south_flag();
  void clear_has_pos_south_flag();
  void set_has_pos_position();
  void clear_has_pos_position();
  void set_has_poi_id();
  void clear_has_poi_id();
  void set_has_link_id();
  void clear_has_link_id();
  void set_has_object_parking_floor_id();
  void clear_has_object_parking_floor_id();
  void set_has_object_parking_lot_id();
  void clear_has_object_parking_lot_id();
  void set_has_distance_cm();
  void clear_has_distance_cm();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::holo::map::proto::common::Coordinate* coordinate_;
  ::holo::map::proto::common::GeoPoint* pos_position_;
  ::google::protobuf::uint32 pos_zone_id_;
  bool pos_south_flag_;
  ::google::protobuf::uint64 poi_id_;
  ::google::protobuf::uint64 link_id_;
  ::google::protobuf::uint32 distance_cm_;
  ::google::protobuf::uint64 object_parking_floor_id_;
  ::google::protobuf::uint64 object_parking_lot_id_;
  friend struct ::protobuf_holo_2fmap_2fproto_2fnavigation_2frouting_5fposition_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// RoutingPosition

// optional .holo.map.proto.common.Coordinate coordinate = 1;
inline bool RoutingPosition::has_coordinate() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void RoutingPosition::set_has_coordinate() {
  _has_bits_[0] |= 0x00000001u;
}
inline void RoutingPosition::clear_has_coordinate() {
  _has_bits_[0] &= ~0x00000001u;
}
inline const ::holo::map::proto::common::Coordinate& RoutingPosition::_internal_coordinate() const {
  return *coordinate_;
}
inline const ::holo::map::proto::common::Coordinate& RoutingPosition::coordinate() const {
  const ::holo::map::proto::common::Coordinate* p = coordinate_;
  // @@protoc_insertion_point(field_get:holo.map.proto.navigation.RoutingPosition.coordinate)
  return p != NULL ? *p : *reinterpret_cast<const ::holo::map::proto::common::Coordinate*>(
      &::holo::map::proto::common::_Coordinate_default_instance_);
}
inline ::holo::map::proto::common::Coordinate* RoutingPosition::release_coordinate() {
  // @@protoc_insertion_point(field_release:holo.map.proto.navigation.RoutingPosition.coordinate)
  clear_has_coordinate();
  ::holo::map::proto::common::Coordinate* temp = coordinate_;
  coordinate_ = NULL;
  return temp;
}
inline ::holo::map::proto::common::Coordinate* RoutingPosition::mutable_coordinate() {
  set_has_coordinate();
  if (coordinate_ == NULL) {
    auto* p = CreateMaybeMessage<::holo::map::proto::common::Coordinate>(GetArenaNoVirtual());
    coordinate_ = p;
  }
  // @@protoc_insertion_point(field_mutable:holo.map.proto.navigation.RoutingPosition.coordinate)
  return coordinate_;
}
inline void RoutingPosition::set_allocated_coordinate(::holo::map::proto::common::Coordinate* coordinate) {
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
  // @@protoc_insertion_point(field_set_allocated:holo.map.proto.navigation.RoutingPosition.coordinate)
}

// optional uint32 pos_zone_id = 2;
inline bool RoutingPosition::has_pos_zone_id() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void RoutingPosition::set_has_pos_zone_id() {
  _has_bits_[0] |= 0x00000004u;
}
inline void RoutingPosition::clear_has_pos_zone_id() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void RoutingPosition::clear_pos_zone_id() {
  pos_zone_id_ = 0u;
  clear_has_pos_zone_id();
}
inline ::google::protobuf::uint32 RoutingPosition::pos_zone_id() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.navigation.RoutingPosition.pos_zone_id)
  return pos_zone_id_;
}
inline void RoutingPosition::set_pos_zone_id(::google::protobuf::uint32 value) {
  set_has_pos_zone_id();
  pos_zone_id_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.navigation.RoutingPosition.pos_zone_id)
}

// optional bool pos_south_flag = 3;
inline bool RoutingPosition::has_pos_south_flag() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void RoutingPosition::set_has_pos_south_flag() {
  _has_bits_[0] |= 0x00000008u;
}
inline void RoutingPosition::clear_has_pos_south_flag() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void RoutingPosition::clear_pos_south_flag() {
  pos_south_flag_ = false;
  clear_has_pos_south_flag();
}
inline bool RoutingPosition::pos_south_flag() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.navigation.RoutingPosition.pos_south_flag)
  return pos_south_flag_;
}
inline void RoutingPosition::set_pos_south_flag(bool value) {
  set_has_pos_south_flag();
  pos_south_flag_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.navigation.RoutingPosition.pos_south_flag)
}

// optional .holo.map.proto.common.GeoPoint pos_position = 4;
inline bool RoutingPosition::has_pos_position() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void RoutingPosition::set_has_pos_position() {
  _has_bits_[0] |= 0x00000002u;
}
inline void RoutingPosition::clear_has_pos_position() {
  _has_bits_[0] &= ~0x00000002u;
}
inline const ::holo::map::proto::common::GeoPoint& RoutingPosition::_internal_pos_position() const {
  return *pos_position_;
}
inline const ::holo::map::proto::common::GeoPoint& RoutingPosition::pos_position() const {
  const ::holo::map::proto::common::GeoPoint* p = pos_position_;
  // @@protoc_insertion_point(field_get:holo.map.proto.navigation.RoutingPosition.pos_position)
  return p != NULL ? *p : *reinterpret_cast<const ::holo::map::proto::common::GeoPoint*>(
      &::holo::map::proto::common::_GeoPoint_default_instance_);
}
inline ::holo::map::proto::common::GeoPoint* RoutingPosition::release_pos_position() {
  // @@protoc_insertion_point(field_release:holo.map.proto.navigation.RoutingPosition.pos_position)
  clear_has_pos_position();
  ::holo::map::proto::common::GeoPoint* temp = pos_position_;
  pos_position_ = NULL;
  return temp;
}
inline ::holo::map::proto::common::GeoPoint* RoutingPosition::mutable_pos_position() {
  set_has_pos_position();
  if (pos_position_ == NULL) {
    auto* p = CreateMaybeMessage<::holo::map::proto::common::GeoPoint>(GetArenaNoVirtual());
    pos_position_ = p;
  }
  // @@protoc_insertion_point(field_mutable:holo.map.proto.navigation.RoutingPosition.pos_position)
  return pos_position_;
}
inline void RoutingPosition::set_allocated_pos_position(::holo::map::proto::common::GeoPoint* pos_position) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete reinterpret_cast< ::google::protobuf::MessageLite*>(pos_position_);
  }
  if (pos_position) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      pos_position = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, pos_position, submessage_arena);
    }
    set_has_pos_position();
  } else {
    clear_has_pos_position();
  }
  pos_position_ = pos_position;
  // @@protoc_insertion_point(field_set_allocated:holo.map.proto.navigation.RoutingPosition.pos_position)
}

// optional uint64 poi_id = 5;
inline bool RoutingPosition::has_poi_id() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void RoutingPosition::set_has_poi_id() {
  _has_bits_[0] |= 0x00000010u;
}
inline void RoutingPosition::clear_has_poi_id() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void RoutingPosition::clear_poi_id() {
  poi_id_ = GOOGLE_ULONGLONG(0);
  clear_has_poi_id();
}
inline ::google::protobuf::uint64 RoutingPosition::poi_id() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.navigation.RoutingPosition.poi_id)
  return poi_id_;
}
inline void RoutingPosition::set_poi_id(::google::protobuf::uint64 value) {
  set_has_poi_id();
  poi_id_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.navigation.RoutingPosition.poi_id)
}

// optional uint64 link_id = 10;
inline bool RoutingPosition::has_link_id() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void RoutingPosition::set_has_link_id() {
  _has_bits_[0] |= 0x00000020u;
}
inline void RoutingPosition::clear_has_link_id() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void RoutingPosition::clear_link_id() {
  link_id_ = GOOGLE_ULONGLONG(0);
  clear_has_link_id();
}
inline ::google::protobuf::uint64 RoutingPosition::link_id() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.navigation.RoutingPosition.link_id)
  return link_id_;
}
inline void RoutingPosition::set_link_id(::google::protobuf::uint64 value) {
  set_has_link_id();
  link_id_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.navigation.RoutingPosition.link_id)
}

// optional uint64 object_parking_floor_id = 11;
inline bool RoutingPosition::has_object_parking_floor_id() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void RoutingPosition::set_has_object_parking_floor_id() {
  _has_bits_[0] |= 0x00000080u;
}
inline void RoutingPosition::clear_has_object_parking_floor_id() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void RoutingPosition::clear_object_parking_floor_id() {
  object_parking_floor_id_ = GOOGLE_ULONGLONG(0);
  clear_has_object_parking_floor_id();
}
inline ::google::protobuf::uint64 RoutingPosition::object_parking_floor_id() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.navigation.RoutingPosition.object_parking_floor_id)
  return object_parking_floor_id_;
}
inline void RoutingPosition::set_object_parking_floor_id(::google::protobuf::uint64 value) {
  set_has_object_parking_floor_id();
  object_parking_floor_id_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.navigation.RoutingPosition.object_parking_floor_id)
}

// optional uint64 object_parking_lot_id = 12;
inline bool RoutingPosition::has_object_parking_lot_id() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void RoutingPosition::set_has_object_parking_lot_id() {
  _has_bits_[0] |= 0x00000100u;
}
inline void RoutingPosition::clear_has_object_parking_lot_id() {
  _has_bits_[0] &= ~0x00000100u;
}
inline void RoutingPosition::clear_object_parking_lot_id() {
  object_parking_lot_id_ = GOOGLE_ULONGLONG(0);
  clear_has_object_parking_lot_id();
}
inline ::google::protobuf::uint64 RoutingPosition::object_parking_lot_id() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.navigation.RoutingPosition.object_parking_lot_id)
  return object_parking_lot_id_;
}
inline void RoutingPosition::set_object_parking_lot_id(::google::protobuf::uint64 value) {
  set_has_object_parking_lot_id();
  object_parking_lot_id_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.navigation.RoutingPosition.object_parking_lot_id)
}

// optional uint32 distance_cm = 20;
inline bool RoutingPosition::has_distance_cm() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void RoutingPosition::set_has_distance_cm() {
  _has_bits_[0] |= 0x00000040u;
}
inline void RoutingPosition::clear_has_distance_cm() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void RoutingPosition::clear_distance_cm() {
  distance_cm_ = 0u;
  clear_has_distance_cm();
}
inline ::google::protobuf::uint32 RoutingPosition::distance_cm() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.navigation.RoutingPosition.distance_cm)
  return distance_cm_;
}
inline void RoutingPosition::set_distance_cm(::google::protobuf::uint32 value) {
  set_has_distance_cm();
  distance_cm_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.navigation.RoutingPosition.distance_cm)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace navigation
}  // namespace proto
}  // namespace map
}  // namespace holo

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_holo_2fmap_2fproto_2fnavigation_2frouting_5fposition_2eproto