// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: centerNet.proto

#ifndef PROTOBUF_INCLUDED_centerNet_2eproto
#define PROTOBUF_INCLUDED_centerNet_2eproto

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
#include "tensor_rt.pb.h"
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_centerNet_2eproto 

namespace protobuf_centerNet_2eproto {
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
}  // namespace protobuf_centerNet_2eproto
namespace holo {
namespace perception {
class CenterNetConfig;
class CenterNetConfigDefaultTypeInternal;
extern CenterNetConfigDefaultTypeInternal _CenterNetConfig_default_instance_;
}  // namespace perception
}  // namespace holo
namespace google {
namespace protobuf {
template<> ::holo::perception::CenterNetConfig* Arena::CreateMaybeMessage<::holo::perception::CenterNetConfig>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace holo {
namespace perception {

// ===================================================================

class CenterNetConfig : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:holo.perception.CenterNetConfig) */ {
 public:
  CenterNetConfig();
  virtual ~CenterNetConfig();

  CenterNetConfig(const CenterNetConfig& from);

  inline CenterNetConfig& operator=(const CenterNetConfig& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  CenterNetConfig(CenterNetConfig&& from) noexcept
    : CenterNetConfig() {
    *this = ::std::move(from);
  }

  inline CenterNetConfig& operator=(CenterNetConfig&& from) noexcept {
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
  static const CenterNetConfig& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const CenterNetConfig* internal_default_instance() {
    return reinterpret_cast<const CenterNetConfig*>(
               &_CenterNetConfig_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(CenterNetConfig* other);
  friend void swap(CenterNetConfig& a, CenterNetConfig& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline CenterNetConfig* New() const final {
    return CreateMaybeMessage<CenterNetConfig>(NULL);
  }

  CenterNetConfig* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<CenterNetConfig>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const CenterNetConfig& from);
  void MergeFrom(const CenterNetConfig& from);
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
  void InternalSwap(CenterNetConfig* other);
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

  // optional .holo.perception.TensorRTConfig tensor_rt_config = 1;
  bool has_tensor_rt_config() const;
  void clear_tensor_rt_config();
  static const int kTensorRtConfigFieldNumber = 1;
  private:
  const ::holo::perception::TensorRTConfig& _internal_tensor_rt_config() const;
  public:
  const ::holo::perception::TensorRTConfig& tensor_rt_config() const;
  ::holo::perception::TensorRTConfig* release_tensor_rt_config();
  ::holo::perception::TensorRTConfig* mutable_tensor_rt_config();
  void set_allocated_tensor_rt_config(::holo::perception::TensorRTConfig* tensor_rt_config);

  // optional float score_threshold = 2;
  bool has_score_threshold() const;
  void clear_score_threshold();
  static const int kScoreThresholdFieldNumber = 2;
  float score_threshold() const;
  void set_score_threshold(float value);

  // optional int32 image_height = 3;
  bool has_image_height() const;
  void clear_image_height();
  static const int kImageHeightFieldNumber = 3;
  ::google::protobuf::int32 image_height() const;
  void set_image_height(::google::protobuf::int32 value);

  // optional int32 image_width = 4;
  bool has_image_width() const;
  void clear_image_width();
  static const int kImageWidthFieldNumber = 4;
  ::google::protobuf::int32 image_width() const;
  void set_image_width(::google::protobuf::int32 value);

  // optional int32 down_ratio = 5;
  bool has_down_ratio() const;
  void clear_down_ratio();
  static const int kDownRatioFieldNumber = 5;
  ::google::protobuf::int32 down_ratio() const;
  void set_down_ratio(::google::protobuf::int32 value);

  // optional float score_threshold_kp = 6;
  bool has_score_threshold_kp() const;
  void clear_score_threshold_kp();
  static const int kScoreThresholdKpFieldNumber = 6;
  float score_threshold_kp() const;
  void set_score_threshold_kp(float value);

  // @@protoc_insertion_point(class_scope:holo.perception.CenterNetConfig)
 private:
  void set_has_tensor_rt_config();
  void clear_has_tensor_rt_config();
  void set_has_score_threshold();
  void clear_has_score_threshold();
  void set_has_image_height();
  void clear_has_image_height();
  void set_has_image_width();
  void clear_has_image_width();
  void set_has_down_ratio();
  void clear_has_down_ratio();
  void set_has_score_threshold_kp();
  void clear_has_score_threshold_kp();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::holo::perception::TensorRTConfig* tensor_rt_config_;
  float score_threshold_;
  ::google::protobuf::int32 image_height_;
  ::google::protobuf::int32 image_width_;
  ::google::protobuf::int32 down_ratio_;
  float score_threshold_kp_;
  friend struct ::protobuf_centerNet_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// CenterNetConfig

// optional .holo.perception.TensorRTConfig tensor_rt_config = 1;
inline bool CenterNetConfig::has_tensor_rt_config() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void CenterNetConfig::set_has_tensor_rt_config() {
  _has_bits_[0] |= 0x00000001u;
}
inline void CenterNetConfig::clear_has_tensor_rt_config() {
  _has_bits_[0] &= ~0x00000001u;
}
inline const ::holo::perception::TensorRTConfig& CenterNetConfig::_internal_tensor_rt_config() const {
  return *tensor_rt_config_;
}
inline const ::holo::perception::TensorRTConfig& CenterNetConfig::tensor_rt_config() const {
  const ::holo::perception::TensorRTConfig* p = tensor_rt_config_;
  // @@protoc_insertion_point(field_get:holo.perception.CenterNetConfig.tensor_rt_config)
  return p != NULL ? *p : *reinterpret_cast<const ::holo::perception::TensorRTConfig*>(
      &::holo::perception::_TensorRTConfig_default_instance_);
}
inline ::holo::perception::TensorRTConfig* CenterNetConfig::release_tensor_rt_config() {
  // @@protoc_insertion_point(field_release:holo.perception.CenterNetConfig.tensor_rt_config)
  clear_has_tensor_rt_config();
  ::holo::perception::TensorRTConfig* temp = tensor_rt_config_;
  tensor_rt_config_ = NULL;
  return temp;
}
inline ::holo::perception::TensorRTConfig* CenterNetConfig::mutable_tensor_rt_config() {
  set_has_tensor_rt_config();
  if (tensor_rt_config_ == NULL) {
    auto* p = CreateMaybeMessage<::holo::perception::TensorRTConfig>(GetArenaNoVirtual());
    tensor_rt_config_ = p;
  }
  // @@protoc_insertion_point(field_mutable:holo.perception.CenterNetConfig.tensor_rt_config)
  return tensor_rt_config_;
}
inline void CenterNetConfig::set_allocated_tensor_rt_config(::holo::perception::TensorRTConfig* tensor_rt_config) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete reinterpret_cast< ::google::protobuf::MessageLite*>(tensor_rt_config_);
  }
  if (tensor_rt_config) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      tensor_rt_config = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, tensor_rt_config, submessage_arena);
    }
    set_has_tensor_rt_config();
  } else {
    clear_has_tensor_rt_config();
  }
  tensor_rt_config_ = tensor_rt_config;
  // @@protoc_insertion_point(field_set_allocated:holo.perception.CenterNetConfig.tensor_rt_config)
}

// optional float score_threshold = 2;
inline bool CenterNetConfig::has_score_threshold() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void CenterNetConfig::set_has_score_threshold() {
  _has_bits_[0] |= 0x00000002u;
}
inline void CenterNetConfig::clear_has_score_threshold() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void CenterNetConfig::clear_score_threshold() {
  score_threshold_ = 0;
  clear_has_score_threshold();
}
inline float CenterNetConfig::score_threshold() const {
  // @@protoc_insertion_point(field_get:holo.perception.CenterNetConfig.score_threshold)
  return score_threshold_;
}
inline void CenterNetConfig::set_score_threshold(float value) {
  set_has_score_threshold();
  score_threshold_ = value;
  // @@protoc_insertion_point(field_set:holo.perception.CenterNetConfig.score_threshold)
}

// optional int32 image_height = 3;
inline bool CenterNetConfig::has_image_height() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void CenterNetConfig::set_has_image_height() {
  _has_bits_[0] |= 0x00000004u;
}
inline void CenterNetConfig::clear_has_image_height() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void CenterNetConfig::clear_image_height() {
  image_height_ = 0;
  clear_has_image_height();
}
inline ::google::protobuf::int32 CenterNetConfig::image_height() const {
  // @@protoc_insertion_point(field_get:holo.perception.CenterNetConfig.image_height)
  return image_height_;
}
inline void CenterNetConfig::set_image_height(::google::protobuf::int32 value) {
  set_has_image_height();
  image_height_ = value;
  // @@protoc_insertion_point(field_set:holo.perception.CenterNetConfig.image_height)
}

// optional int32 image_width = 4;
inline bool CenterNetConfig::has_image_width() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void CenterNetConfig::set_has_image_width() {
  _has_bits_[0] |= 0x00000008u;
}
inline void CenterNetConfig::clear_has_image_width() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void CenterNetConfig::clear_image_width() {
  image_width_ = 0;
  clear_has_image_width();
}
inline ::google::protobuf::int32 CenterNetConfig::image_width() const {
  // @@protoc_insertion_point(field_get:holo.perception.CenterNetConfig.image_width)
  return image_width_;
}
inline void CenterNetConfig::set_image_width(::google::protobuf::int32 value) {
  set_has_image_width();
  image_width_ = value;
  // @@protoc_insertion_point(field_set:holo.perception.CenterNetConfig.image_width)
}

// optional int32 down_ratio = 5;
inline bool CenterNetConfig::has_down_ratio() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void CenterNetConfig::set_has_down_ratio() {
  _has_bits_[0] |= 0x00000010u;
}
inline void CenterNetConfig::clear_has_down_ratio() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void CenterNetConfig::clear_down_ratio() {
  down_ratio_ = 0;
  clear_has_down_ratio();
}
inline ::google::protobuf::int32 CenterNetConfig::down_ratio() const {
  // @@protoc_insertion_point(field_get:holo.perception.CenterNetConfig.down_ratio)
  return down_ratio_;
}
inline void CenterNetConfig::set_down_ratio(::google::protobuf::int32 value) {
  set_has_down_ratio();
  down_ratio_ = value;
  // @@protoc_insertion_point(field_set:holo.perception.CenterNetConfig.down_ratio)
}

// optional float score_threshold_kp = 6;
inline bool CenterNetConfig::has_score_threshold_kp() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void CenterNetConfig::set_has_score_threshold_kp() {
  _has_bits_[0] |= 0x00000020u;
}
inline void CenterNetConfig::clear_has_score_threshold_kp() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void CenterNetConfig::clear_score_threshold_kp() {
  score_threshold_kp_ = 0;
  clear_has_score_threshold_kp();
}
inline float CenterNetConfig::score_threshold_kp() const {
  // @@protoc_insertion_point(field_get:holo.perception.CenterNetConfig.score_threshold_kp)
  return score_threshold_kp_;
}
inline void CenterNetConfig::set_score_threshold_kp(float value) {
  set_has_score_threshold_kp();
  score_threshold_kp_ = value;
  // @@protoc_insertion_point(field_set:holo.perception.CenterNetConfig.score_threshold_kp)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace perception
}  // namespace holo

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_centerNet_2eproto
