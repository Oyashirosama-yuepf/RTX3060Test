// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: holo/map/proto/navigation/routing_graph.proto

#ifndef PROTOBUF_INCLUDED_holo_2fmap_2fproto_2fnavigation_2frouting_5fgraph_2eproto
#define PROTOBUF_INCLUDED_holo_2fmap_2fproto_2fnavigation_2frouting_5fgraph_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_protobuf_holo_2fmap_2fproto_2fnavigation_2frouting_5fgraph_2eproto 

namespace protobuf_holo_2fmap_2fproto_2fnavigation_2frouting_5fgraph_2eproto {
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
}  // namespace protobuf_holo_2fmap_2fproto_2fnavigation_2frouting_5fgraph_2eproto
namespace holo {
namespace map {
namespace proto {
namespace navigation {
class RoutingGraph;
class RoutingGraphDefaultTypeInternal;
extern RoutingGraphDefaultTypeInternal _RoutingGraph_default_instance_;
}  // namespace navigation
}  // namespace proto
}  // namespace map
}  // namespace holo
namespace google {
namespace protobuf {
template<> ::holo::map::proto::navigation::RoutingGraph* Arena::CreateMaybeMessage<::holo::map::proto::navigation::RoutingGraph>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace holo {
namespace map {
namespace proto {
namespace navigation {

enum RoutingGraph_Type {
  RoutingGraph_Type_TYPE_UNDEFINED = 0,
  RoutingGraph_Type_TYPE_LINK = 1,
  RoutingGraph_Type_TYPE_LANE = 2
};
bool RoutingGraph_Type_IsValid(int value);
const RoutingGraph_Type RoutingGraph_Type_Type_MIN = RoutingGraph_Type_TYPE_UNDEFINED;
const RoutingGraph_Type RoutingGraph_Type_Type_MAX = RoutingGraph_Type_TYPE_LANE;
const int RoutingGraph_Type_Type_ARRAYSIZE = RoutingGraph_Type_Type_MAX + 1;

const ::google::protobuf::EnumDescriptor* RoutingGraph_Type_descriptor();
inline const ::std::string& RoutingGraph_Type_Name(RoutingGraph_Type value) {
  return ::google::protobuf::internal::NameOfEnum(
    RoutingGraph_Type_descriptor(), value);
}
inline bool RoutingGraph_Type_Parse(
    const ::std::string& name, RoutingGraph_Type* value) {
  return ::google::protobuf::internal::ParseNamedEnum<RoutingGraph_Type>(
    RoutingGraph_Type_descriptor(), name, value);
}
// ===================================================================

class RoutingGraph : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:holo.map.proto.navigation.RoutingGraph) */ {
 public:
  RoutingGraph();
  virtual ~RoutingGraph();

  RoutingGraph(const RoutingGraph& from);

  inline RoutingGraph& operator=(const RoutingGraph& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  RoutingGraph(RoutingGraph&& from) noexcept
    : RoutingGraph() {
    *this = ::std::move(from);
  }

  inline RoutingGraph& operator=(RoutingGraph&& from) noexcept {
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
  static const RoutingGraph& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const RoutingGraph* internal_default_instance() {
    return reinterpret_cast<const RoutingGraph*>(
               &_RoutingGraph_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(RoutingGraph* other);
  friend void swap(RoutingGraph& a, RoutingGraph& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline RoutingGraph* New() const final {
    return CreateMaybeMessage<RoutingGraph>(NULL);
  }

  RoutingGraph* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<RoutingGraph>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const RoutingGraph& from);
  void MergeFrom(const RoutingGraph& from);
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
  void InternalSwap(RoutingGraph* other);
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

  typedef RoutingGraph_Type Type;
  static const Type TYPE_UNDEFINED =
    RoutingGraph_Type_TYPE_UNDEFINED;
  static const Type TYPE_LINK =
    RoutingGraph_Type_TYPE_LINK;
  static const Type TYPE_LANE =
    RoutingGraph_Type_TYPE_LANE;
  static inline bool Type_IsValid(int value) {
    return RoutingGraph_Type_IsValid(value);
  }
  static const Type Type_MIN =
    RoutingGraph_Type_Type_MIN;
  static const Type Type_MAX =
    RoutingGraph_Type_Type_MAX;
  static const int Type_ARRAYSIZE =
    RoutingGraph_Type_Type_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Type_descriptor() {
    return RoutingGraph_Type_descriptor();
  }
  static inline const ::std::string& Type_Name(Type value) {
    return RoutingGraph_Type_Name(value);
  }
  static inline bool Type_Parse(const ::std::string& name,
      Type* value) {
    return RoutingGraph_Type_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // repeated uint64 routing_node_ids = 2 [packed = true];
  int routing_node_ids_size() const;
  void clear_routing_node_ids();
  static const int kRoutingNodeIdsFieldNumber = 2;
  ::google::protobuf::uint64 routing_node_ids(int index) const;
  void set_routing_node_ids(int index, ::google::protobuf::uint64 value);
  void add_routing_node_ids(::google::protobuf::uint64 value);
  const ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >&
      routing_node_ids() const;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >*
      mutable_routing_node_ids();

  // repeated uint64 routing_edge_ids = 3 [packed = true];
  int routing_edge_ids_size() const;
  void clear_routing_edge_ids();
  static const int kRoutingEdgeIdsFieldNumber = 3;
  ::google::protobuf::uint64 routing_edge_ids(int index) const;
  void set_routing_edge_ids(int index, ::google::protobuf::uint64 value);
  void add_routing_edge_ids(::google::protobuf::uint64 value);
  const ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >&
      routing_edge_ids() const;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >*
      mutable_routing_edge_ids();

  // optional uint64 routing_graph_id = 1;
  bool has_routing_graph_id() const;
  void clear_routing_graph_id();
  static const int kRoutingGraphIdFieldNumber = 1;
  ::google::protobuf::uint64 routing_graph_id() const;
  void set_routing_graph_id(::google::protobuf::uint64 value);

  // optional .holo.map.proto.navigation.RoutingGraph.Type type = 4;
  bool has_type() const;
  void clear_type();
  static const int kTypeFieldNumber = 4;
  ::holo::map::proto::navigation::RoutingGraph_Type type() const;
  void set_type(::holo::map::proto::navigation::RoutingGraph_Type value);

  // @@protoc_insertion_point(class_scope:holo.map.proto.navigation.RoutingGraph)
 private:
  void set_has_routing_graph_id();
  void clear_has_routing_graph_id();
  void set_has_type();
  void clear_has_type();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint64 > routing_node_ids_;
  mutable int _routing_node_ids_cached_byte_size_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint64 > routing_edge_ids_;
  mutable int _routing_edge_ids_cached_byte_size_;
  ::google::protobuf::uint64 routing_graph_id_;
  int type_;
  friend struct ::protobuf_holo_2fmap_2fproto_2fnavigation_2frouting_5fgraph_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// RoutingGraph

// optional uint64 routing_graph_id = 1;
inline bool RoutingGraph::has_routing_graph_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void RoutingGraph::set_has_routing_graph_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void RoutingGraph::clear_has_routing_graph_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void RoutingGraph::clear_routing_graph_id() {
  routing_graph_id_ = GOOGLE_ULONGLONG(0);
  clear_has_routing_graph_id();
}
inline ::google::protobuf::uint64 RoutingGraph::routing_graph_id() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.navigation.RoutingGraph.routing_graph_id)
  return routing_graph_id_;
}
inline void RoutingGraph::set_routing_graph_id(::google::protobuf::uint64 value) {
  set_has_routing_graph_id();
  routing_graph_id_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.navigation.RoutingGraph.routing_graph_id)
}

// repeated uint64 routing_node_ids = 2 [packed = true];
inline int RoutingGraph::routing_node_ids_size() const {
  return routing_node_ids_.size();
}
inline void RoutingGraph::clear_routing_node_ids() {
  routing_node_ids_.Clear();
}
inline ::google::protobuf::uint64 RoutingGraph::routing_node_ids(int index) const {
  // @@protoc_insertion_point(field_get:holo.map.proto.navigation.RoutingGraph.routing_node_ids)
  return routing_node_ids_.Get(index);
}
inline void RoutingGraph::set_routing_node_ids(int index, ::google::protobuf::uint64 value) {
  routing_node_ids_.Set(index, value);
  // @@protoc_insertion_point(field_set:holo.map.proto.navigation.RoutingGraph.routing_node_ids)
}
inline void RoutingGraph::add_routing_node_ids(::google::protobuf::uint64 value) {
  routing_node_ids_.Add(value);
  // @@protoc_insertion_point(field_add:holo.map.proto.navigation.RoutingGraph.routing_node_ids)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >&
RoutingGraph::routing_node_ids() const {
  // @@protoc_insertion_point(field_list:holo.map.proto.navigation.RoutingGraph.routing_node_ids)
  return routing_node_ids_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >*
RoutingGraph::mutable_routing_node_ids() {
  // @@protoc_insertion_point(field_mutable_list:holo.map.proto.navigation.RoutingGraph.routing_node_ids)
  return &routing_node_ids_;
}

// repeated uint64 routing_edge_ids = 3 [packed = true];
inline int RoutingGraph::routing_edge_ids_size() const {
  return routing_edge_ids_.size();
}
inline void RoutingGraph::clear_routing_edge_ids() {
  routing_edge_ids_.Clear();
}
inline ::google::protobuf::uint64 RoutingGraph::routing_edge_ids(int index) const {
  // @@protoc_insertion_point(field_get:holo.map.proto.navigation.RoutingGraph.routing_edge_ids)
  return routing_edge_ids_.Get(index);
}
inline void RoutingGraph::set_routing_edge_ids(int index, ::google::protobuf::uint64 value) {
  routing_edge_ids_.Set(index, value);
  // @@protoc_insertion_point(field_set:holo.map.proto.navigation.RoutingGraph.routing_edge_ids)
}
inline void RoutingGraph::add_routing_edge_ids(::google::protobuf::uint64 value) {
  routing_edge_ids_.Add(value);
  // @@protoc_insertion_point(field_add:holo.map.proto.navigation.RoutingGraph.routing_edge_ids)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >&
RoutingGraph::routing_edge_ids() const {
  // @@protoc_insertion_point(field_list:holo.map.proto.navigation.RoutingGraph.routing_edge_ids)
  return routing_edge_ids_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >*
RoutingGraph::mutable_routing_edge_ids() {
  // @@protoc_insertion_point(field_mutable_list:holo.map.proto.navigation.RoutingGraph.routing_edge_ids)
  return &routing_edge_ids_;
}

// optional .holo.map.proto.navigation.RoutingGraph.Type type = 4;
inline bool RoutingGraph::has_type() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void RoutingGraph::set_has_type() {
  _has_bits_[0] |= 0x00000002u;
}
inline void RoutingGraph::clear_has_type() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void RoutingGraph::clear_type() {
  type_ = 0;
  clear_has_type();
}
inline ::holo::map::proto::navigation::RoutingGraph_Type RoutingGraph::type() const {
  // @@protoc_insertion_point(field_get:holo.map.proto.navigation.RoutingGraph.type)
  return static_cast< ::holo::map::proto::navigation::RoutingGraph_Type >(type_);
}
inline void RoutingGraph::set_type(::holo::map::proto::navigation::RoutingGraph_Type value) {
  assert(::holo::map::proto::navigation::RoutingGraph_Type_IsValid(value));
  set_has_type();
  type_ = value;
  // @@protoc_insertion_point(field_set:holo.map.proto.navigation.RoutingGraph.type)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace navigation
}  // namespace proto
}  // namespace map
}  // namespace holo

namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::holo::map::proto::navigation::RoutingGraph_Type> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::holo::map::proto::navigation::RoutingGraph_Type>() {
  return ::holo::map::proto::navigation::RoutingGraph_Type_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_holo_2fmap_2fproto_2fnavigation_2frouting_5fgraph_2eproto