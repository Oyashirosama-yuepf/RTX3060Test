/* -*- C++ -*- */
/* Generated by /home/holo/workspace/output/tda4_ubuntu-18.04/debug/host/bin/opendds_idl version 3.16 (ACE version 6.2a_p19) running on input file /home/holo/workspace/src/holo_base_msg/opendds_msg/message/holo_base_msg/deprecated/Obstacle.idl */
#ifndef OPENDDS_IDL_GENERATED_OBSTACLETYPESUPPORTIMPL_H_7KCP3P
#define OPENDDS_IDL_GENERATED_OBSTACLETYPESUPPORTIMPL_H_7KCP3P
#include "ObstacleC.h"
#include "dds/DCPS/Definitions.h"
#include "dds/DdsDcpsC.h"
#include "dds/Version.h"
#if DDS_MAJOR_VERSION != 3 || DDS_MINOR_VERSION != 16 || DDS_MICRO_VERSION != 0
#error This file should be regenerated with opendds_idl
#endif
#include "ObstacleTypeSupportC.h"
#include "dds/DCPS/Serializer.h"
#include "dds/DCPS/TypeSupportImpl.h"
#include "dds/DCPS/ValueWriter.h"
#include "dds/DCPS/XTypes/TypeObject.h"
#include "holo_base_msg/common/CommonC.h"
#include "holo_base_msg/core/TypesC.h"
#include "holo_base_msg/geometry/BoxC.h"
#include "holo_base_msg/geometry/PointC.h"
#include "holo_base_msg/numerics/VectorC.h"
#include "holo_base_msg/obstacle/ObstacleSetC.h"
#include "holo_base_msg/vision/ImageObjectsC.h"
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL



/* Begin MODULE: CORBA */


/* End MODULE: CORBA */


/* Begin MODULE: OpenDDS */


/* End MODULE: OpenDDS */


/* Begin MODULE: holo_base_msg */



/* Begin MODULE: core */



/* Begin TYPEDEF: bool_t */


/* End TYPEDEF: bool_t */


/* Begin TYPEDEF: char_t */


/* End TYPEDEF: char_t */


/* Begin TYPEDEF: _cxx_wchar_t */


/* End TYPEDEF: _cxx_wchar_t */


/* Begin TYPEDEF: int8_t */


/* End TYPEDEF: int8_t */


/* Begin TYPEDEF: uint8_t */


/* End TYPEDEF: uint8_t */


/* Begin TYPEDEF: int16_t */


/* End TYPEDEF: int16_t */


/* Begin TYPEDEF: uint16_t */


/* End TYPEDEF: uint16_t */


/* Begin TYPEDEF: int32_t */


/* End TYPEDEF: int32_t */


/* Begin TYPEDEF: uint32_t */


/* End TYPEDEF: uint32_t */


/* Begin TYPEDEF: int64_t */


/* End TYPEDEF: int64_t */


/* Begin TYPEDEF: uint64_t */


/* End TYPEDEF: uint64_t */


/* Begin TYPEDEF: float32_t */


/* End TYPEDEF: float32_t */


/* Begin TYPEDEF: float64_t */


/* End TYPEDEF: float64_t */


/* Begin TYPEDEF: BoolSequence */


/* End TYPEDEF: BoolSequence */


/* Begin TYPEDEF: CharSequence */


/* End TYPEDEF: CharSequence */


/* Begin TYPEDEF: WcharSequence */


/* End TYPEDEF: WcharSequence */


/* Begin TYPEDEF: Int8Sequence */


/* End TYPEDEF: Int8Sequence */


/* Begin TYPEDEF: Uint8Sequence */


/* End TYPEDEF: Uint8Sequence */


/* Begin TYPEDEF: Int16Sequence */


/* End TYPEDEF: Int16Sequence */


/* Begin TYPEDEF: Uint16Sequence */


/* End TYPEDEF: Uint16Sequence */


/* Begin TYPEDEF: Int32Sequence */


/* End TYPEDEF: Int32Sequence */


/* Begin TYPEDEF: Uint32Sequence */


/* End TYPEDEF: Uint32Sequence */


/* Begin TYPEDEF: Int64Sequence */


/* End TYPEDEF: Int64Sequence */


/* Begin TYPEDEF: Uint64Sequence */


/* End TYPEDEF: Uint64Sequence */


/* Begin TYPEDEF: Float32Sequence */


/* End TYPEDEF: Float32Sequence */


/* Begin TYPEDEF: Float64Sequence */


/* End TYPEDEF: Float64Sequence */

/* End MODULE: core */

/* End MODULE: holo_base_msg */


/* Begin MODULE: holo_base_msg */



/* Begin MODULE: common */



/* Begin TYPEDEF: Coordinate */


/* End TYPEDEF: Coordinate */


/* Begin TYPEDEF: SensorId */


/* End TYPEDEF: SensorId */


/* Begin TYPEDEF: Classification */


/* End TYPEDEF: Classification */


/* Begin STRUCT: Duration */


/* End STRUCT: Duration */


/* Begin STRUCT: Timestamp */


/* End STRUCT: Timestamp */

/* End MODULE: common */

/* End MODULE: holo_base_msg */


/* Begin MODULE: holo_base_msg */



/* Begin MODULE: geometry */



/* Begin STRUCT: Rot2f */


/* End STRUCT: Rot2f */


/* Begin STRUCT: Rot2d */


/* End STRUCT: Rot2d */


/* Begin STRUCT: Rot3f */


/* End STRUCT: Rot3f */


/* Begin STRUCT: Rot3d */


/* End STRUCT: Rot3d */

/* End MODULE: geometry */

/* End MODULE: holo_base_msg */


/* Begin MODULE: holo_base_msg */



/* Begin MODULE: geometry */



/* Begin STRUCT: Point3f */


/* End STRUCT: Point3f */


/* Begin TYPEDEF: Point3fSequence */


/* End TYPEDEF: Point3fSequence */


/* Begin STRUCT: Point3d */


/* End STRUCT: Point3d */


/* Begin TYPEDEF: Point3dSequence */


/* End TYPEDEF: Point3dSequence */


/* Begin STRUCT: Point2f */


/* End STRUCT: Point2f */


/* Begin TYPEDEF: Point2fSequence */


/* End TYPEDEF: Point2fSequence */


/* Begin STRUCT: Point2d */


/* End STRUCT: Point2d */


/* Begin TYPEDEF: Point2dSequence */


/* End TYPEDEF: Point2dSequence */

/* End MODULE: geometry */

/* End MODULE: holo_base_msg */


/* Begin MODULE: holo_base_msg */



/* Begin MODULE: geometry */



/* Begin STRUCT: Pose3f */


/* End STRUCT: Pose3f */


/* Begin STRUCT: Pose3d */


/* End STRUCT: Pose3d */


/* Begin STRUCT: Pose2f */


/* End STRUCT: Pose2f */


/* Begin STRUCT: Pose2d */


/* End STRUCT: Pose2d */

/* End MODULE: geometry */

/* End MODULE: holo_base_msg */


/* Begin MODULE: holo_base_msg */



/* Begin MODULE: geometry */



/* Begin STRUCT: Box2f */


/* End STRUCT: Box2f */


/* Begin STRUCT: Box2d */


/* End STRUCT: Box2d */


/* Begin STRUCT: Box3f */


/* End STRUCT: Box3f */


/* Begin STRUCT: Box3d */


/* End STRUCT: Box3d */

/* End MODULE: geometry */

/* End MODULE: holo_base_msg */


/* Begin MODULE: holo_base_msg */



/* Begin MODULE: numerics */



/* Begin TYPEDEF: Vectord */


/* End TYPEDEF: Vectord */


/* Begin TYPEDEF: Vector2d */


/* End TYPEDEF: Vector2d */


/* Begin TYPEDEF: Vector3d */


/* End TYPEDEF: Vector3d */


/* Begin TYPEDEF: Vector4d */


/* End TYPEDEF: Vector4d */


/* Begin TYPEDEF: Vector5d */


/* End TYPEDEF: Vector5d */


/* Begin TYPEDEF: Vector6d */


/* End TYPEDEF: Vector6d */


/* Begin TYPEDEF: Vector7d */


/* End TYPEDEF: Vector7d */


/* Begin TYPEDEF: Vector8d */


/* End TYPEDEF: Vector8d */


/* Begin TYPEDEF: Vectorf */


/* End TYPEDEF: Vectorf */


/* Begin TYPEDEF: Vector2f */


/* End TYPEDEF: Vector2f */


/* Begin TYPEDEF: Vector3f */


/* End TYPEDEF: Vector3f */


/* Begin TYPEDEF: Vector4f */


/* End TYPEDEF: Vector4f */


/* Begin TYPEDEF: Vector5f */


/* End TYPEDEF: Vector5f */


/* Begin TYPEDEF: Vector6f */


/* End TYPEDEF: Vector6f */


/* Begin TYPEDEF: Vector7f */


/* End TYPEDEF: Vector7f */


/* Begin TYPEDEF: Vector8f */


/* End TYPEDEF: Vector8f */

/* End MODULE: numerics */

/* End MODULE: holo_base_msg */


/* Begin MODULE: holo_base_msg */



/* Begin MODULE: vision */



/* Begin STRUCT: KeyPoint2d */


/* End STRUCT: KeyPoint2d */


/* Begin TYPEDEF: KeyPoint2dSequence */


/* End TYPEDEF: KeyPoint2dSequence */


/* Begin STRUCT: KeyPoint2f */


/* End STRUCT: KeyPoint2f */


/* Begin TYPEDEF: KeyPoint2fSequence */


/* End TYPEDEF: KeyPoint2fSequence */


/* Begin STRUCT: ObjectKeyPoint2d */


/* End STRUCT: ObjectKeyPoint2d */


/* Begin TYPEDEF: ObjectKeyPoint2dSequence */


/* End TYPEDEF: ObjectKeyPoint2dSequence */


/* Begin STRUCT: ObjectKeyPoint2f */


/* End STRUCT: ObjectKeyPoint2f */


/* Begin TYPEDEF: ObjectKeyPoint2fSequence */


/* End TYPEDEF: ObjectKeyPoint2fSequence */


/* Begin STRUCT: ObjectPoint2d */


/* End STRUCT: ObjectPoint2d */


/* Begin TYPEDEF: ObjectPoint2dSequence */


/* End TYPEDEF: ObjectPoint2dSequence */


/* Begin STRUCT: ObjectPoint2f */


/* End STRUCT: ObjectPoint2f */


/* Begin TYPEDEF: ObjectPoint2fSequence */


/* End TYPEDEF: ObjectPoint2fSequence */


/* Begin STRUCT: ObjectPoint3d */


/* End STRUCT: ObjectPoint3d */


/* Begin TYPEDEF: ObjectPoint3dSequence */


/* End TYPEDEF: ObjectPoint3dSequence */


/* Begin STRUCT: ObjectPoint3f */


/* End STRUCT: ObjectPoint3f */


/* Begin TYPEDEF: ObjectPoint3fSequence */


/* End TYPEDEF: ObjectPoint3fSequence */


/* Begin STRUCT: ImageObjectsKeyPoint2d */


/* End STRUCT: ImageObjectsKeyPoint2d */


/* Begin STRUCT: ImageObjectsKeyPoint2f */


/* End STRUCT: ImageObjectsKeyPoint2f */


/* Begin STRUCT: ImageObjectsPoint2d */


/* End STRUCT: ImageObjectsPoint2d */


/* Begin STRUCT: ImageObjectsPoint2f */


/* End STRUCT: ImageObjectsPoint2f */


/* Begin STRUCT: ImageObjectsPoint3d */


/* End STRUCT: ImageObjectsPoint3d */


/* Begin STRUCT: ImageObjectsPoint3f */


/* End STRUCT: ImageObjectsPoint3f */

/* End MODULE: vision */

/* End MODULE: holo_base_msg */


/* Begin MODULE: holo_base_msg */



/* Begin MODULE: obstacle */



/* Begin TYPEDEF: CutInCutOut */


/* End TYPEDEF: CutInCutOut */


/* Begin TYPEDEF: MotionStatus */


/* End TYPEDEF: MotionStatus */


/* Begin TYPEDEF: PerceptionAbility */


/* End TYPEDEF: PerceptionAbility */


/* Begin STRUCT: ObstacleGeneral */


/* End STRUCT: ObstacleGeneral */


/* Begin TYPEDEF: ObstacleGeneralSequence */


/* End TYPEDEF: ObstacleGeneralSequence */


/* Begin STRUCT: ObstacleGeneralList */


/* End STRUCT: ObstacleGeneralList */


/* Begin STRUCT: ObstacleRadar */


/* End STRUCT: ObstacleRadar */


/* Begin TYPEDEF: ObstacleRadarSequence */


/* End TYPEDEF: ObstacleRadarSequence */


/* Begin STRUCT: ObstacleRadarList */


/* End STRUCT: ObstacleRadarList */


/* Begin STRUCT: ObstacleUss */


/* End STRUCT: ObstacleUss */


/* Begin TYPEDEF: ObstacleUssSequence */


/* End TYPEDEF: ObstacleUssSequence */


/* Begin STRUCT: ObstacleUssList */


/* End STRUCT: ObstacleUssList */


/* Begin STRUCT: ObstacleVision */


/* End STRUCT: ObstacleVision */


/* Begin TYPEDEF: ObstacleVisionSequence */


/* End TYPEDEF: ObstacleVisionSequence */


/* Begin STRUCT: ObstacleVisionList */


/* End STRUCT: ObstacleVisionList */

/* End MODULE: obstacle */

/* End MODULE: holo_base_msg */


/* Begin MODULE: holo_base_msg */



/* Begin MODULE: deprecated */



/* Begin MODULE: obstacle */



/* Begin STRUCT: ObstacleGeneralList */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void set_default(holo_base_msg::deprecated::obstacle::ObstacleGeneralList& stru);

void serialized_size(const Encoding& encoding, size_t& size, const holo_base_msg::deprecated::obstacle::ObstacleGeneralList& stru);

bool operator<<(Serializer& strm, const holo_base_msg::deprecated::obstacle::ObstacleGeneralList& stru);

bool operator>>(Serializer& strm, holo_base_msg::deprecated::obstacle::ObstacleGeneralList& stru);

void serialized_size(const Encoding& encoding, size_t& size, const NestedKeyOnly<const holo_base_msg::deprecated::obstacle::ObstacleGeneralList>& stru);

bool operator<<(Serializer& strm, const NestedKeyOnly<const holo_base_msg::deprecated::obstacle::ObstacleGeneralList>& stru);

bool operator>>(Serializer& strm, const NestedKeyOnly<holo_base_msg::deprecated::obstacle::ObstacleGeneralList>& stru);

template <>
struct MarshalTraits<holo_base_msg::deprecated::obstacle::ObstacleGeneralList> {
  static void representations_allowed_by_type(DDS::DataRepresentationIdSeq& seq)
  {
    seq.length(3);
    seq[0] = DDS::XCDR_DATA_REPRESENTATION;
    seq[1] = DDS::XCDR2_DATA_REPRESENTATION;
    seq[2] = DDS::XML_DATA_REPRESENTATION;
  }

  static SerializedSizeBound serialized_size_bound(const Encoding& encoding)
  {
    switch (encoding.kind()) {
    case Encoding::KIND_UNALIGNED_CDR:
      return SerializedSizeBound();
    case Encoding::KIND_XCDR1:
      return SerializedSizeBound();
    case Encoding::KIND_XCDR2:
      return SerializedSizeBound();
    default:
      OPENDDS_ASSERT(false);
      return SerializedSizeBound();
    }
  }

  static SerializedSizeBound key_only_serialized_size_bound(const Encoding& encoding)
  {
    switch (encoding.kind()) {
    case Encoding::KIND_UNALIGNED_CDR:
      return SerializedSizeBound(0);
    case Encoding::KIND_XCDR1:
      return SerializedSizeBound();
    case Encoding::KIND_XCDR2:
      return SerializedSizeBound();
    default:
      OPENDDS_ASSERT(false);
      return SerializedSizeBound();
    }
  }

  static bool to_message_block(ACE_Message_Block&, const holo_base_msg::deprecated::obstacle::ObstacleGeneralList&) { return false; }
  static bool from_message_block(holo_base_msg::deprecated::obstacle::ObstacleGeneralList&, const ACE_Message_Block&) { return false; }
  static Extensibility extensibility() { return APPENDABLE; }
  static Extensibility max_extensibility_level() { return APPENDABLE; }
};
void serialized_size(const Encoding& encoding, size_t& size, const KeyOnly<const holo_base_msg::deprecated::obstacle::ObstacleGeneralList> stru);

bool operator<<(Serializer& strm, KeyOnly<const holo_base_msg::deprecated::obstacle::ObstacleGeneralList> stru);

bool operator>>(Serializer& strm, KeyOnly<holo_base_msg::deprecated::obstacle::ObstacleGeneralList> stru);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace deprecated {
namespace obstacle {
/// This structure supports use of std::map with one or more keys.
struct  ObstacleGeneralList_OpenDDS_KeyLessThan {
  bool operator()(const holo_base_msg::deprecated::obstacle::ObstacleGeneralList&, const holo_base_msg::deprecated::obstacle::ObstacleGeneralList&) const
  {
    // With no keys, return false to allow use of
    // map with just one entry
    return false;
  }
};
}
}
}

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void vwrite(OpenDDS::DCPS::ValueWriter& value_writer, const holo_base_msg::deprecated::obstacle::ObstacleGeneralList& value);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace deprecated {
namespace obstacle {
class ObstacleGeneralListTypeSupportImpl;
}
}
}

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS {
namespace DCPS {
template <>
struct DDSTraits<holo_base_msg::deprecated::obstacle::ObstacleGeneralList> {
  typedef holo_base_msg::deprecated::obstacle::ObstacleGeneralList MessageType;
  typedef holo_base_msg::deprecated::obstacle::ObstacleGeneralListSeq MessageSequenceType;
  typedef holo_base_msg::deprecated::obstacle::ObstacleGeneralListTypeSupport TypeSupportType;
  typedef holo_base_msg::deprecated::obstacle::ObstacleGeneralListTypeSupportImpl TypeSupportTypeImpl;
  typedef holo_base_msg::deprecated::obstacle::ObstacleGeneralListDataWriter DataWriterType;
  typedef holo_base_msg::deprecated::obstacle::ObstacleGeneralListDataReader DataReaderType;
  typedef holo_base_msg::deprecated::obstacle::ObstacleGeneralList_OpenDDS_KeyLessThan LessThanType;
  typedef OpenDDS::DCPS::KeyOnly<const holo_base_msg::deprecated::obstacle::ObstacleGeneralList> KeyOnlyType;

  static const char* type_name() { return "holo_base_msg::deprecated::obstacle::ObstacleGeneralList"; }
  static bool gen_has_key() { return false; }
  static size_t key_count() { return 0; }
};
} // namespace DCPS
} // namespace OpenDDS
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace holo_base_msg {
namespace deprecated {
namespace obstacle {
class  ObstacleGeneralListTypeSupportImpl
  : public virtual OpenDDS::DCPS::LocalObject<ObstacleGeneralListTypeSupport>
  , public virtual OpenDDS::DCPS::TypeSupportImpl
{
public:
  typedef OpenDDS::DCPS::DDSTraits<ObstacleGeneralList> TraitsType;
  typedef OpenDDS::DCPS::MarshalTraits<ObstacleGeneralList> MarshalTraitsType;
  typedef ObstacleGeneralListTypeSupport TypeSupportType;
  typedef ObstacleGeneralListTypeSupport::_var_type _var_type;
  typedef ObstacleGeneralListTypeSupport::_ptr_type _ptr_type;

  ObstacleGeneralListTypeSupportImpl() {}
  virtual ~ObstacleGeneralListTypeSupportImpl() {}

  virtual ::DDS::DataWriter_ptr create_datawriter();
  virtual ::DDS::DataReader_ptr create_datareader();
#ifndef OPENDDS_NO_MULTI_TOPIC
  virtual ::DDS::DataReader_ptr create_multitopic_datareader();
#endif /* !OPENDDS_NO_MULTI_TOPIC */
#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
  virtual const OpenDDS::DCPS::MetaStruct& getMetaStructForType();
#endif /* !OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE */
  virtual bool has_dcps_key();
  const char* default_type_name() const;

  void representations_allowed_by_type(::DDS::DataRepresentationIdSeq& seq);

  virtual const OpenDDS::XTypes::TypeIdentifier& getMinimalTypeIdentifier() const;
  virtual const OpenDDS::XTypes::TypeMap& getMinimalTypeMap() const;

  virtual OpenDDS::DCPS::Extensibility getExtensibility() const;

  static ObstacleGeneralListTypeSupport::_ptr_type _narrow(CORBA::Object_ptr obj);
};
}
}
}

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

class MetaStruct;

template<typename T>
const MetaStruct& getMetaStruct();

template<>
const MetaStruct& getMetaStruct<holo_base_msg::deprecated::obstacle::ObstacleGeneralList>();
bool gen_skip_over(Serializer& ser, holo_base_msg::deprecated::obstacle::ObstacleGeneralList*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct holo_base_msg_deprecated_obstacle_ObstacleGeneralList_xtag {};
template<> const XTypes::TypeIdentifier & getMinimalTypeIdentifier<holo_base_msg_deprecated_obstacle_ObstacleGeneralList_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<holo_base_msg_deprecated_obstacle_ObstacleGeneralList_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End STRUCT: ObstacleGeneralList */

/* End MODULE: obstacle */

/* End MODULE: deprecated */

/* End MODULE: holo_base_msg */
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif /* OPENDDS_IDL_GENERATED_OBSTACLETYPESUPPORTIMPL_H_7KCP3P */