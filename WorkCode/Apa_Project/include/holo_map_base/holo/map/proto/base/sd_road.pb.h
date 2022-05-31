// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: holo/map/proto/base/sd_road.proto

#ifndef PROTOBUF_INCLUDED_holo_2fmap_2fproto_2fbase_2fsd_5froad_2eproto
#define PROTOBUF_INCLUDED_holo_2fmap_2fproto_2fbase_2fsd_5froad_2eproto

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
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
#include "holo/map/proto/common/coordinate.pb.h"
#include "holo/map/proto/common/geo_line.pb.h"
#include "holo/map/proto/common/geo_point.pb.h"
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_holo_2fmap_2fproto_2fbase_2fsd_5froad_2eproto 

namespace protobuf_holo_2fmap_2fproto_2fbase_2fsd_5froad_2eproto {
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
}  // namespace protobuf_holo_2fmap_2fproto_2fbase_2fsd_5froad_2eproto
namespace holo {
namespace map {
namespace proto {
namespace base {
class SdRoad;
class SdRoadDefaultTypeInternal;
extern SdRoadDefaultTypeInternal _SdRoad_default_instance_;
class SdRoad_ExtraGeometryPointsEntry_DoNotUse;
class SdRoad_ExtraGeometryPointsEntry_DoNotUseDefaultTypeInternal;
extern SdRoad_ExtraGeometryPointsEntry_DoNotUseDefaultTypeInternal _SdRoad_ExtraGeometryPointsEntry_DoNotUse_default_instance_;
}  // namespace base
}  // namespace proto
}  // namespace map
}  // namespace holo
namespace google {
namespace protobuf {
template<> ::holo::map::proto::base::SdRoad* Arena::CreateMaybeMessage<::holo::map::proto::base::SdRoad>(Arena*);
template<> ::holo::map::proto::base::SdRoad_ExtraGeometryPointsEntry_DoNotUse* Arena::CreateMaybeMessage<::holo::map::proto::base::SdRoad_ExtraGeometryPointsEntry_DoNotUse>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace holo {
namespace map {
namespace proto {
namespace base {

enum SdRoad_SdRoadType {
  SdRoad_SdRoadType_SD_ROAD_TYPE_UNKNOWN = 0
};
bool SdRoad_SdRoadType_IsValid(int value);
const SdRoad_SdRoadType SdRoad_SdRoadType_SdRoadType_MIN = SdRoad_SdRoadType_SD_ROAD_TYPE_UNKNOWN;
const SdRoad_SdRoadType SdRoad_SdRoadType_SdRoadType_MAX = SdRoad_SdRoadType_SD_ROAD_TYPE_UNKNOWN;
const int SdRoad_SdRoadType_SdRoadType_ARRAYSIZE = SdRoad_SdRoadType_SdRoadType_MAX + 1;

const ::google::protobuf::EnumDescriptor* SdRoad_SdRoadType_descriptor();
inline const ::std::string& SdRoad_SdRoadType_Name(SdRoad_SdRoadType value) {
  return ::google::protobuf::internal::NameOfEnum(
    SdRoad_SdRoadType_descriptor(), value);
}
inline bool SdRoad_SdRoadType_Parse(
    const ::std::string& name, SdRoad_SdRoadType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<SdRoad_SdRoadType>(
    SdRoad_SdRoadType_descriptor(), name, value);
}
enum SdRoad_SdRoadClass {
  SdRoad_SdRoadClass_SD_ROAD_CLASS_UNKNOWN = 0
};
bool SdRoad_SdRoadClass_IsValid(int value);
const SdRoad_SdRoadClass SdRoad_SdRoadClass_SdRoadClass_MIN = SdRoad_SdRoadClass_SD_ROAD_CLASS_UNKNOWN;
const SdRoad_SdRoadClass SdRoad_SdRoadClass_SdRoadClass_MAX = SdRoad_SdRoadClass_SD_ROAD_CLASS_UNKNOWN;
const int SdRoad_SdRoadClass_SdRoadClass_ARRAYSIZE = SdRoad_SdRoadClass_SdRoadClass_MAX + 1;

const ::google::protobuf::EnumDescriptor* SdRoad_SdRoadClass_descriptor();
inline const ::std::string& SdRoad_SdRoadClass_Name(SdRoad_SdRoadClass value) {
  return ::google::protobuf::internal::NameOfEnum(
    SdRoad_SdRoadClass_descriptor(), value);
}
inline bool SdRoad_SdRoadClass_Parse(
    const ::std::string& name, SdRoad_SdRoadClass* value) {
  return ::google::protobuf::internal::ParseNamedEnum<SdRoad_SdRoadClass>(
    SdRoad_SdRoadClass_descriptor(), name, value);
}
enum SdRoad_SdRoadDirection {
  SdRoad_SdRoadDirection_SD_ROAD_DIRECTION_UNDEFINED = 0,
  SdRoad_SdRoadDirection_SD_ROAD_DIRECTION_BIDIRECTIONAL = 1,
  SdRoad_SdRoadDirection_SD_ROAD_DIRECTION_POSITIVE_DIRECTION = 2,
  SdRoad_SdRoadDirection_SD_ROAD_DIRECTION_NEGATIVE_DIRECTION = 3
};
bool SdRoad_SdRoadDirection_IsValid(int value);
const SdRoad_SdRoadDirection SdRoad_SdRoadDirection_SdRoadDirection_MIN = SdRoad_SdRoadDirection_SD_ROAD_DIRECTION_UNDEFINED;
const SdRoad_SdRoadDirection SdRoad_SdRoadDirection_SdRoadDirection_MAX = SdRoad_SdRoadDirection_SD_ROAD_DIRECTION_NEGATIVE_DIRECTION;
const int SdRoad_SdRoadDirection_SdRoadDirection_ARRAYSIZE = SdRoad_SdRoadDirection_SdRoadDirection_MAX + 1;

const ::google::protobuf::EnumDescriptor* SdRoad_SdRoadDirection_descriptor();
inline const ::std::string& SdRoad_SdRoadDirection_Name(SdRoad_SdRoadDirection value) {
  return ::google::protobuf::internal::NameOfEnum(
    SdRoad_SdRoadDirection_descriptor(), value);
}
inline bool SdRoad_SdRoadDirection_Parse(
    const ::std::string& name, SdRoad_SdRoadDirection* value) {
  return ::google::protobuf::internal::ParseNamedEnum<SdRoad_SdRoadDirection>(
    SdRoad_SdRoadDirection_descriptor(), name, value);
}
// ===================================================================

class SdRoad_ExtraGeometryPointsEntry_DoNotUse : public ::google::protobuf::internal::MapEntry<SdRoad_ExtraGeometryPointsEntry_DoNotUse, 
    ::google::protobuf::uint32, ::holo::map::proto::common::GeoLine,
    ::google::protobuf::internal::WireFormatLite::TYPE_UINT32,
    ::google::protobuf::internal::WireFormatLite::TYPE_MESSAGE,
    0 > {
public:
  typedef ::google::protobuf::internal::MapEntry<SdRoad_ExtraGeometryPointsEntry_DoNotUse, 
    ::google::protobuf::uint32, ::holo::map::proto::common::GeoLine,
    ::google::protobuf::internal::WireFormatLite::TYPE_UINT32,
    ::google::protobuf::internal::WireFormatLite::TYPE_MESSAGE,
    0 > SuperType;
  SdRoad_ExtraGeometryPointsEntry_DoNotUse();
  SdRoad_ExtraGeometryPointsEntry_DoNotUse(::google::protobuf::Arena* arena);
  void MergeFrom(const SdRoad_ExtraGeometryPointsEntry_DoNotUse& other);
  static const SdRoad_ExtraGeometryPointsEntry_DoNotUse* internal_default_instance() { return reinterpret_cast<const SdRoad_ExtraGeometryPointsEntry_DoNotUse*>(&_SdRoad_ExtraGeometryPointsEntry_DoNotUse_default_instance_); }
  void MergeFrom(const ::google::protobuf::Message& other) final;
  ::google::protobuf::Metadata GetMetadata() const;
};

// -------------------------------------------------------------------

class SdRoad : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:holo.map.proto.base.SdRoad) */ {
 public:
  SdRoad();
  virtual ~SdRoad();

  SdRoad(const SdRoad& from);

  inline SdRoad& operator=(const SdRoad& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  SdRoad(SdRoad&& from) noexcept
    : SdRoad() {
    *this = ::std::move(from);
  }

  inline SdRoad& operator=(SdRoad&& from) noexcept {
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
  static const SdRoad& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const SdRoad* internal_default_instance() {
    return reinterpret_cast<const SdRoad*>(
               &_SdRoad_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(SdRoad* other);
  friend void swap(SdRoad& a, SdRoad& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline SdRoad* New() const final {
    return CreateMaybeMessage<SdRoad>(NULL);
  }

  SdRoad* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<SdRoad>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const SdRoad& from);
  void MergeFrom(const SdRoad& from);
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
  void InternalSwap(SdRoad* other);
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


  typedef SdRoad_SdRoadType SdRoadType;
  static const SdRoadType SD_ROAD_TYPE_UNKNOWN =
    SdRoad_SdRoadType_SD_ROAD_TYPE_UNKNOWN;
  static inline bool SdRoadType_IsValid(int value) {
    return SdRoad_SdRoadType_IsValid(value);
  }
  static const SdRoadType SdRoadType_MIN =
    SdRoad_SdRoadType_SdRoadType_MIN;
  static const SdRoadType SdRoadType_MAX =
    SdRoad_SdRoadType_SdRoadType_MAX;
  static const int SdRoadType_ARRAYSIZE =
    SdRoad_SdRoadType_SdRoadType_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  SdRoadType_descriptor() {
    return SdRoad_SdRoadType_descriptor();
  }
  static inline const ::std::string& SdRoadType_Name(SdRoadType value) {
    return SdRoad_SdRoadType_Name(value);
  }
  static inline bool SdRoadType_Parse(const ::std::string& name,
      SdRoadType* value) {
    return SdRoad_SdRoadType_Parse(name, value);
  }

  typedef SdRoad_SdRoadClass SdRoadClass;
  static const SdRoadClass SD_ROAD_CLASS_UNKNOWN =
    SdRoad_SdRoadClass_SD_ROAD_CLASS_UNKNOWN;
  static inline bool SdRoadClass_IsValid(int value) {
    return SdRoad_SdRoadClass_IsValid(value);
  }
  static const SdRoadClass SdRoadClass_MIN =
    SdRoad_SdRoadClass_SdRoadClass_MIN;
  static const SdRoadClass SdRoadClass_MAX =
    SdRoad_SdRoadClass_SdRoadClass_MAX;
  static const int SdRoadClass_ARRAYSIZE =
    SdRoad_SdRoadClass_SdRoadClass_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  SdRoadClass_descriptor() {
    return SdRoad_SdRoadClass_descriptor();
  }
  static inline const ::std::string& SdRoadClass_Name(SdRoadClass value) {
    return SdRoad_SdRoadClass_Name(value);
  }
  static inline bool SdRoadClass_Parse(const ::std::string& name,
      SdRoadClass* value) {
    return SdRoad_SdRoadClass_Parse(name, value);
  }

  typedef SdRoad_SdRoadDirection SdRoadDirection;
  static const SdRoadDirection SD_ROAD_DIRECTION_UNDEFINED =
    SdRoad_SdRoadDirection_SD_ROAD_DIRECTION_UNDEFINED;
  static const SdRoadDirection SD_ROAD_DIRECTION_BIDIRECTIONAL =
    SdRoad_SdRoadDirection_SD_ROAD_DIRECTION_BIDIRECTIONAL;
  static const SdRoadDirection SD_ROAD_DIRECTION_POSITIVE_DIRECTION =
    SdRoad_SdRoadDirection_SD_ROAD_DIRECTION_POSITIVE_DIRECTION;
  static const SdRoadDirection SD_ROAD_DIRECTION_NEGATIVE_DIRECTION =
    SdRoad_SdRoadDirection_SD_ROAD_DIRECTION_NEGATIVE_DIRECTION;
  static inline bool SdRoadDirection_IsValid(int value) {
    return SdRoad_SdRoadDirection_IsValid(value);
  }
  static const SdRoadDirection SdRoadDirection_MIN =
    SdRoad_SdRoadDirection_SdRoadDirection_MIN;
  static const SdRoadDirection SdRoadDirection_MAX =
    SdRoad_SdRoadDirection_SdRoadDirection_MAX;
  static const int SdRoadDirection_ARRAYSIZE =
    SdRoad_SdRoadDirection_SdRoadDirection_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  SdRoadDirection_descriptor() {
    return SdRoad_SdRoadDirection_descriptor();
  }
  static inline const ::std::string& SdRoadDirection_Name(SdRoadDirection value) {
    return SdRoad_SdRoadDirection_Name(value);
  }
  static inline bool SdRoadDirection_Parse(const ::std::string& name,
      SdRoadDirection* value) {
    return SdRoad_SdRoadDirection_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // repeated uint64 tile_ids = 40 [packed = true];
  int tile_ids_size() const;
  void clear_tile_ids();
  static const int kTileIdsFieldNumber = 40;
  ::google::protobuf::uint64 tile_ids(int index) const;
  void set_tile_ids(int index, ::google::protobuf::uint64 value);
  void add_tile_ids(::google::protobuf::uint64 value);
  const ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >&
      tile_ids() const;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >*
      mutable_tile_ids();

  // repeated .holo.map.proto.common.GeoPoint geometry_points = 54;
  int geometry_points_size() const;
  void clear_geometry_points();
  static const int kGeometryPointsFieldNumber = 54;
  ::holo::map::proto::common::GeoPoint* mutable_geometry_points(int index);
  ::google::protobuf::RepeatedPtrField< ::holo::map::proto::common::GeoPoint >*
      mutable_geometry_points();
  const ::holo::map::proto::common::GeoPoint& geometry_points(int index) const;
  ::holo::map::proto::common::GeoPoint* add_geometry_points();
  const ::google::protobuf::RepeatedPtrField< ::holo::map::proto::common::GeoPoint >&
      geometry_points() const;

  // map<uint32, .holo.map.proto.common.GeoLine> extra_geometry_points = 55;
  int extra_geometry_points_size() const;
  void clear_extra_geometry_points();
  static const int kExtraGeometryPointsFieldNumber = 55;
  const ::google::protobuf::Map< ::google::protobuf::uint32, ::holo::map::proto::common::GeoLine >&
      extra_geometry_points() const;
  ::google::protobuf::Map< ::google::protobuf::uint32, ::holo::map::proto::common::GeoLine >*
      mutable_extra_geometry_points();

  // optional .holo.map.proto.common.Coordinate coordinate = 50;
  bool has_coordinate() const;
  void clear_coordinate();
  static const int kCoordinateFieldNumber = 50;
  private:
  const ::holo::map::proto::common::Coordinate& _internal_coordinate() const;
  public:
  const ::holo::map::proto::common::Coordinate& coordinate() const;
  ::holo::map::proto::common::Coordinate* release_coordinate();
  ::holo::map::proto::common::Coordinate* mutable_coordinate();
  void set_allocated_coordinate(::holo::map::proto::common::Coordinate* coordinate);

  // optional uint64 sd_road_id = 1;
  bool has_sd_road_id() const;
  void clear_sd_road_id();
  static const int kSdRoadIdFieldNumber = 1;
  ::google::protobuf::uint64 sd_road_id() const;
  void set_sd_road_id(::google::protobuf::uint64 value);

  // optional .holo.map.proto.base.SdRoad.SdRoadType sd_road_type = 2;
  bool has_sd_road_type() const;
  void clear_sd_road_type();
  static const int kSdRoadTypeFieldNumber = 2;
  ::holo::map::proto::base::SdRoad_SdRoadType sd_road_type() const;
  void set_sd_road_type(::holo::map::proto::base::SdRoad_SdRoadType value);

  // optional .holo.map.proto.base.SdRoad.SdRoadClass sd_road_class = 3;
  bool has_sd_road_class() const;
  void clear_sd_road_class();
  static const int kSdRoadClassFieldNumber = 3;
  ::holo::map::proto::base::SdRoad_SdRoadClass sd_road_class() const;
  void set_sd_road_class(::holo::map::proto::base::SdRoad_SdRoadClass value);

  // optional .holo.map.proto.base.SdRoad.SdRoadDirection sd_road_direction = 4;
  bool has_sd_road_direction() const;
  void clear_sd_road_direction();
  static const int kSdRoadDirectionFieldNumber = 4;
  ::holo::map::proto::base::SdRoad_SdRoadDirection sd_road_direction() const;
  void set_sd_road_direction(::holo::map::proto::base::SdRoad_SdRoadDirection value);

  // optional uint32 length_cm = 10;
  bool has_length_cm() const;
  void clear_length_cm();
  static const int kLengthCmFieldNumber = 10;
  ::google::protobuf::uint32 length_cm() const;
  void set_length_cm(::google::protobuf::uint32 value);

  // optional uint32 start_lane_number = 11;
  bool has_start_lane_number() const;
  void clear_start_lane_number();
  static const int kStartLaneNumberFieldNumber = 11;
  ::google::protobuf::uint32 start_lane_number() const;
  void set_start_lane_number(::google::protobuf::uint32 value);

  // optional uint32 end_lane_number = 12;
  bool has_end_lane_number() const;
  void clear_end_lane_number();
  static const int kEndLaneNumberFieldNumber = 12;
  ::google::protobuf::uint32 end_lane_number() const;
  void set_end_lane_number(::google::protobuf::uint32 value);

  // optional uint64 start_node_id = 13;
  bool has_start_node_id() const;
  void clear_start_node_id();
  static const int kStartNodeIdFieldNumber = 13;
  ::google::protobuf::uint64 start_node_id() const;
  void set_start_node_id(::google::protobuf::uint64 value);

  // optional uint64 end_node_id = 14;
  bool has_end_node_id() const;
  void clear_end_node_id();
  static const int kEndNodeIdFieldNumber = 14;
  ::google::protobuf::uint64 end_node_id() const;
  void set_end_node_id(::google::protobuf::uint64 value);

  // optional bool south_flag = 53;
  bool has_south_flag() const;
  void clear_south_flag();
  static const int kSouthFlagFieldNumber = 53;
  bool south_flag() const;
  void set_south_flag(bool value);

  // optional uint32 zone_id = 51;
  bool has_zone_id() const;
  void clear_zone_id();
  static const int kZoneIdFieldNumber = 51;
  ::google::protobuf::uint32 zone_id() const;
  void set_zone_id(::google::protobuf::uint32 value);

  // optional uint32 extra_zone_id = 52;
  bool has_extra_zone_id() const;
  void clear_extra_zone_id();
  static const int kExtraZoneIdFieldNumber = 52;
  ::google::protobuf::uint32 extra_zone_id() const;
  void set_extra_zone_id(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:holo.map.proto.base.SdRoad)
 private:
  void set_has_sd_road_id();
  void clear_has_sd_road_id();
  void set_has_sd_road_type();
  void clear_has_sd_road_type();
  void set_has_sd_road_class();
  void clear_has_sd_road_class();
  void set_has_sd_road_direction();
  void clear_has_sd_road_direction();
  void set_has_length_cm();
  void clear_has_length_cm();
  void set_has_start_lane_number();
  void clear_has_start_lane_number();
  void set_has_end_lane_number();
  void clear_has_end_lane_number();
  void set_has_start_node_id();
  void clear_has_start_node_id();
  void set_has_end_node_id();
  void clear_has_end_node_id();
  void set_has_coordinate();
  void clear_has_coordinate();
  void set_has_zone_id();
  void clear_has_zone_id();
  void set_has_extra_zone_id();
  void clear_has_extra_zone_id();
  void set_has_south_flag();
  void clear_has_south_flag();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint64 > tile_ids_;
  mutable int _tile_ids_cached_byte_size_;
  ::google::protobuf::RepeatedPtrField< ::holo::map::proto::common::GeoPoint > geometry_points_;
  ::google::protobuf::internal::MapField<
      SdRoad_ExtraGeometryPointsEntry_DoNotUse,
      ::google::protobuf::uint32, ::holo::map::proto::common::GeoLine,
      ::google::protobuf::internal::WireFormatLite::TYPE_UINT32,
      ::google::protobuf::internal::WireFormatLite::TYPE_MESSAGE,
      0 > extra_geometry_points_;
  ::holo::map::proto::common::Coordinate* coordinate_;
  ::google::protobuf::uint64 sd_road_id_;
  int sd_road_type_;
  int sd_road_class_;
  int sd_road_direction_;
  ::google::protobuf::uint32 length_cm_;
  ::google::protobuf::uint32 start_lane_number_;
  ::google::protobuf::uint32 end_lane_number_;
  ::google::protobuf::uint64 start_node_id_;
  ::google::protobuf::uint64 end_node_id_;
  bool south_flag_;
  ::google::protobuf::uint32 zone_id_;
  ::google::protobuf::uint32 extra_zone_id_;
  friend struct ::protobuf_holo_2fmap_2fproto_2fbase_2fsd_5froad_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// SdRoad

// optional uint64 sd_road_id = 1;
inline bool SdRoad::has_sd_road_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void SdRoad::set_has_sd_road_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void SdRoad::clear_has_sd_road_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void SdRoad::clear_sd_road_id() {
  sd_road_id_ = GOOGLE_ULONGLONG(0);
  clear_has_sd_road_id();
}
inline ::google::protobuf::uint64 SdRoad::sd_road_id() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.base.SdRoad.sd_road_id)
  return sd_road_id_;
}
inline void SdRoad::set_sd_road_id(::google::protobuf::uint64 value) {
  set_has_sd_road_id();
  sd_road_id_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.base.SdRoad.sd_road_id)
}

// optional .holo.map.proto.base.SdRoad.SdRoadType sd_road_type = 2;
inline bool SdRoad::has_sd_road_type() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void SdRoad::set_has_sd_road_type() {
  _has_bits_[0] |= 0x00000004u;
}
inline void SdRoad::clear_has_sd_road_type() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void SdRoad::clear_sd_road_type() {
  sd_road_type_ = 0;
  clear_has_sd_road_type();
}
inline ::holo::map::proto::base::SdRoad_SdRoadType SdRoad::sd_road_type() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.base.SdRoad.sd_road_type)
  return static_cast< ::holo::map::proto::base::SdRoad_SdRoadType >(sd_road_type_);
}
inline void SdRoad::set_sd_road_type(::holo::map::proto::base::SdRoad_SdRoadType value) {
  assert(::holo::map::proto::base::SdRoad_SdRoadType_IsValid(value));
  set_has_sd_road_type();
  sd_road_type_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.base.SdRoad.sd_road_type)
}

// optional .holo.map.proto.base.SdRoad.SdRoadClass sd_road_class = 3;
inline bool SdRoad::has_sd_road_class() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void SdRoad::set_has_sd_road_class() {
  _has_bits_[0] |= 0x00000008u;
}
inline void SdRoad::clear_has_sd_road_class() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void SdRoad::clear_sd_road_class() {
  sd_road_class_ = 0;
  clear_has_sd_road_class();
}
inline ::holo::map::proto::base::SdRoad_SdRoadClass SdRoad::sd_road_class() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.base.SdRoad.sd_road_class)
  return static_cast< ::holo::map::proto::base::SdRoad_SdRoadClass >(sd_road_class_);
}
inline void SdRoad::set_sd_road_class(::holo::map::proto::base::SdRoad_SdRoadClass value) {
  assert(::holo::map::proto::base::SdRoad_SdRoadClass_IsValid(value));
  set_has_sd_road_class();
  sd_road_class_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.base.SdRoad.sd_road_class)
}

// optional .holo.map.proto.base.SdRoad.SdRoadDirection sd_road_direction = 4;
inline bool SdRoad::has_sd_road_direction() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void SdRoad::set_has_sd_road_direction() {
  _has_bits_[0] |= 0x00000010u;
}
inline void SdRoad::clear_has_sd_road_direction() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void SdRoad::clear_sd_road_direction() {
  sd_road_direction_ = 0;
  clear_has_sd_road_direction();
}
inline ::holo::map::proto::base::SdRoad_SdRoadDirection SdRoad::sd_road_direction() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.base.SdRoad.sd_road_direction)
  return static_cast< ::holo::map::proto::base::SdRoad_SdRoadDirection >(sd_road_direction_);
}
inline void SdRoad::set_sd_road_direction(::holo::map::proto::base::SdRoad_SdRoadDirection value) {
  assert(::holo::map::proto::base::SdRoad_SdRoadDirection_IsValid(value));
  set_has_sd_road_direction();
  sd_road_direction_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.base.SdRoad.sd_road_direction)
}

// optional uint32 length_cm = 10;
inline bool SdRoad::has_length_cm() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void SdRoad::set_has_length_cm() {
  _has_bits_[0] |= 0x00000020u;
}
inline void SdRoad::clear_has_length_cm() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void SdRoad::clear_length_cm() {
  length_cm_ = 0u;
  clear_has_length_cm();
}
inline ::google::protobuf::uint32 SdRoad::length_cm() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.base.SdRoad.length_cm)
  return length_cm_;
}
inline void SdRoad::set_length_cm(::google::protobuf::uint32 value) {
  set_has_length_cm();
  length_cm_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.base.SdRoad.length_cm)
}

// optional uint32 start_lane_number = 11;
inline bool SdRoad::has_start_lane_number() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void SdRoad::set_has_start_lane_number() {
  _has_bits_[0] |= 0x00000040u;
}
inline void SdRoad::clear_has_start_lane_number() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void SdRoad::clear_start_lane_number() {
  start_lane_number_ = 0u;
  clear_has_start_lane_number();
}
inline ::google::protobuf::uint32 SdRoad::start_lane_number() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.base.SdRoad.start_lane_number)
  return start_lane_number_;
}
inline void SdRoad::set_start_lane_number(::google::protobuf::uint32 value) {
  set_has_start_lane_number();
  start_lane_number_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.base.SdRoad.start_lane_number)
}

// optional uint32 end_lane_number = 12;
inline bool SdRoad::has_end_lane_number() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void SdRoad::set_has_end_lane_number() {
  _has_bits_[0] |= 0x00000080u;
}
inline void SdRoad::clear_has_end_lane_number() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void SdRoad::clear_end_lane_number() {
  end_lane_number_ = 0u;
  clear_has_end_lane_number();
}
inline ::google::protobuf::uint32 SdRoad::end_lane_number() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.base.SdRoad.end_lane_number)
  return end_lane_number_;
}
inline void SdRoad::set_end_lane_number(::google::protobuf::uint32 value) {
  set_has_end_lane_number();
  end_lane_number_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.base.SdRoad.end_lane_number)
}

// optional uint64 start_node_id = 13;
inline bool SdRoad::has_start_node_id() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void SdRoad::set_has_start_node_id() {
  _has_bits_[0] |= 0x00000100u;
}
inline void SdRoad::clear_has_start_node_id() {
  _has_bits_[0] &= ~0x00000100u;
}
inline void SdRoad::clear_start_node_id() {
  start_node_id_ = GOOGLE_ULONGLONG(0);
  clear_has_start_node_id();
}
inline ::google::protobuf::uint64 SdRoad::start_node_id() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.base.SdRoad.start_node_id)
  return start_node_id_;
}
inline void SdRoad::set_start_node_id(::google::protobuf::uint64 value) {
  set_has_start_node_id();
  start_node_id_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.base.SdRoad.start_node_id)
}

// optional uint64 end_node_id = 14;
inline bool SdRoad::has_end_node_id() const {
  return (_has_bits_[0] & 0x00000200u) != 0;
}
inline void SdRoad::set_has_end_node_id() {
  _has_bits_[0] |= 0x00000200u;
}
inline void SdRoad::clear_has_end_node_id() {
  _has_bits_[0] &= ~0x00000200u;
}
inline void SdRoad::clear_end_node_id() {
  end_node_id_ = GOOGLE_ULONGLONG(0);
  clear_has_end_node_id();
}
inline ::google::protobuf::uint64 SdRoad::end_node_id() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.base.SdRoad.end_node_id)
  return end_node_id_;
}
inline void SdRoad::set_end_node_id(::google::protobuf::uint64 value) {
  set_has_end_node_id();
  end_node_id_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.base.SdRoad.end_node_id)
}

// repeated uint64 tile_ids = 40 [packed = true];
inline int SdRoad::tile_ids_size() const {
  return tile_ids_.size();
}
inline void SdRoad::clear_tile_ids() {
  tile_ids_.Clear();
}
inline ::google::protobuf::uint64 SdRoad::tile_ids(int index) const {
  // @@protoc_insertion_point(field_get:holo.map.proto.base.SdRoad.tile_ids)
  return tile_ids_.Get(index);
}
inline void SdRoad::set_tile_ids(int index, ::google::protobuf::uint64 value) {
  tile_ids_.Set(index, value);
  // @@protoc_insertion_point(field_set:holo.map.proto.base.SdRoad.tile_ids)
}
inline void SdRoad::add_tile_ids(::google::protobuf::uint64 value) {
  tile_ids_.Add(value);
  // @@protoc_insertion_point(field_add:holo.map.proto.base.SdRoad.tile_ids)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >&
SdRoad::tile_ids() const {
  // @@protoc_insertion_point(field_list:holo.map.proto.base.SdRoad.tile_ids)
  return tile_ids_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >*
SdRoad::mutable_tile_ids() {
  // @@protoc_insertion_point(field_mutable_list:holo.map.proto.base.SdRoad.tile_ids)
  return &tile_ids_;
}

// optional .holo.map.proto.common.Coordinate coordinate = 50;
inline bool SdRoad::has_coordinate() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SdRoad::set_has_coordinate() {
  _has_bits_[0] |= 0x00000001u;
}
inline void SdRoad::clear_has_coordinate() {
  _has_bits_[0] &= ~0x00000001u;
}
inline const ::holo::map::proto::common::Coordinate& SdRoad::_internal_coordinate() const {
  return *coordinate_;
}
inline const ::holo::map::proto::common::Coordinate& SdRoad::coordinate() const {
  const ::holo::map::proto::common::Coordinate* p = coordinate_;
  // @@protoc_insertion_point(field_get:holo.map.proto.base.SdRoad.coordinate)
  return p != NULL ? *p : *reinterpret_cast<const ::holo::map::proto::common::Coordinate*>(
      &::holo::map::proto::common::_Coordinate_default_instance_);
}
inline ::holo::map::proto::common::Coordinate* SdRoad::release_coordinate() {
  // @@protoc_insertion_point(field_release:holo.map.proto.base.SdRoad.coordinate)
  clear_has_coordinate();
  ::holo::map::proto::common::Coordinate* temp = coordinate_;
  coordinate_ = NULL;
  return temp;
}
inline ::holo::map::proto::common::Coordinate* SdRoad::mutable_coordinate() {
  set_has_coordinate();
  if (coordinate_ == NULL) {
    auto* p = CreateMaybeMessage<::holo::map::proto::common::Coordinate>(GetArenaNoVirtual());
    coordinate_ = p;
  }
  // @@protoc_insertion_point(field_mutable:holo.map.proto.base.SdRoad.coordinate)
  return coordinate_;
}
inline void SdRoad::set_allocated_coordinate(::holo::map::proto::common::Coordinate* coordinate) {
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
  // @@protoc_insertion_point(field_set_allocated:holo.map.proto.base.SdRoad.coordinate)
}

// optional uint32 zone_id = 51;
inline bool SdRoad::has_zone_id() const {
  return (_has_bits_[0] & 0x00000800u) != 0;
}
inline void SdRoad::set_has_zone_id() {
  _has_bits_[0] |= 0x00000800u;
}
inline void SdRoad::clear_has_zone_id() {
  _has_bits_[0] &= ~0x00000800u;
}
inline void SdRoad::clear_zone_id() {
  zone_id_ = 0u;
  clear_has_zone_id();
}
inline ::google::protobuf::uint32 SdRoad::zone_id() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.base.SdRoad.zone_id)
  return zone_id_;
}
inline void SdRoad::set_zone_id(::google::protobuf::uint32 value) {
  set_has_zone_id();
  zone_id_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.base.SdRoad.zone_id)
}

// optional uint32 extra_zone_id = 52;
inline bool SdRoad::has_extra_zone_id() const {
  return (_has_bits_[0] & 0x00001000u) != 0;
}
inline void SdRoad::set_has_extra_zone_id() {
  _has_bits_[0] |= 0x00001000u;
}
inline void SdRoad::clear_has_extra_zone_id() {
  _has_bits_[0] &= ~0x00001000u;
}
inline void SdRoad::clear_extra_zone_id() {
  extra_zone_id_ = 0u;
  clear_has_extra_zone_id();
}
inline ::google::protobuf::uint32 SdRoad::extra_zone_id() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.base.SdRoad.extra_zone_id)
  return extra_zone_id_;
}
inline void SdRoad::set_extra_zone_id(::google::protobuf::uint32 value) {
  set_has_extra_zone_id();
  extra_zone_id_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.base.SdRoad.extra_zone_id)
}

// optional bool south_flag = 53;
inline bool SdRoad::has_south_flag() const {
  return (_has_bits_[0] & 0x00000400u) != 0;
}
inline void SdRoad::set_has_south_flag() {
  _has_bits_[0] |= 0x00000400u;
}
inline void SdRoad::clear_has_south_flag() {
  _has_bits_[0] &= ~0x00000400u;
}
inline void SdRoad::clear_south_flag() {
  south_flag_ = false;
  clear_has_south_flag();
}
inline bool SdRoad::south_flag() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.base.SdRoad.south_flag)
  return south_flag_;
}
inline void SdRoad::set_south_flag(bool value) {
  set_has_south_flag();
  south_flag_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.base.SdRoad.south_flag)
}

// repeated .holo.map.proto.common.GeoPoint geometry_points = 54;
inline int SdRoad::geometry_points_size() const {
  return geometry_points_.size();
}
inline ::holo::map::proto::common::GeoPoint* SdRoad::mutable_geometry_points(int index) {
  // @@protoc_insertion_point(field_mutable:holo.map.proto.base.SdRoad.geometry_points)
  return geometry_points_.Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField< ::holo::map::proto::common::GeoPoint >*
SdRoad::mutable_geometry_points() {
  // @@protoc_insertion_point(field_mutable_list:holo.map.proto.base.SdRoad.geometry_points)
  return &geometry_points_;
}
inline const ::holo::map::proto::common::GeoPoint& SdRoad::geometry_points(int index) const {
  // @@protoc_insertion_point(field_get:holo.map.proto.base.SdRoad.geometry_points)
  return geometry_points_.Get(index);
}
inline ::holo::map::proto::common::GeoPoint* SdRoad::add_geometry_points() {
  // @@protoc_insertion_point(field_add:holo.map.proto.base.SdRoad.geometry_points)
  return geometry_points_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::holo::map::proto::common::GeoPoint >&
SdRoad::geometry_points() const {
  // @@protoc_insertion_point(field_list:holo.map.proto.base.SdRoad.geometry_points)
  return geometry_points_;
}

// map<uint32, .holo.map.proto.common.GeoLine> extra_geometry_points = 55;
inline int SdRoad::extra_geometry_points_size() const {
  return extra_geometry_points_.size();
}
inline const ::google::protobuf::Map< ::google::protobuf::uint32, ::holo::map::proto::common::GeoLine >&
SdRoad::extra_geometry_points() const {
  // @@protoc_insertion_point(field_map:holo.map.proto.base.SdRoad.extra_geometry_points)
  return extra_geometry_points_.GetMap();
}
inline ::google::protobuf::Map< ::google::protobuf::uint32, ::holo::map::proto::common::GeoLine >*
SdRoad::mutable_extra_geometry_points() {
  // @@protoc_insertion_point(field_mutable_map:holo.map.proto.base.SdRoad.extra_geometry_points)
  return extra_geometry_points_.MutableMap();
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

namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::holo::map::proto::base::SdRoad_SdRoadType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::holo::map::proto::base::SdRoad_SdRoadType>() {
  return ::holo::map::proto::base::SdRoad_SdRoadType_descriptor();
}
template <> struct is_proto_enum< ::holo::map::proto::base::SdRoad_SdRoadClass> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::holo::map::proto::base::SdRoad_SdRoadClass>() {
  return ::holo::map::proto::base::SdRoad_SdRoadClass_descriptor();
}
template <> struct is_proto_enum< ::holo::map::proto::base::SdRoad_SdRoadDirection> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::holo::map::proto::base::SdRoad_SdRoadDirection>() {
  return ::holo::map::proto::base::SdRoad_SdRoadDirection_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_holo_2fmap_2fproto_2fbase_2fsd_5froad_2eproto