#ifndef OPENDDS_MSG_COMMON_LANE_SCENE_TRAITS_H_
#define OPENDDS_MSG_COMMON_LANE_SCENE_TRAITS_H_

#include <holo/common/lane_scene.h>
#include <holo_base_msg/common/LaneSceneC.h>
#include <holo_base_msg/common/LaneSceneS.h>
#include <holo_base_msg/common/LaneSceneTypeSupportC.h>
#include <holo_base_msg/common/LaneSceneTypeSupportImpl.h>
#include <holo_base_msg/common/LaneSceneTypeSupportS.h>
#include <opendds_wrapper/traits.h>

namespace opendds_wrapper
{

template <>
struct DefaultMessageTraits<::holo_base_msg::common::LaneScene>
{
    using ValueType   = ::holo_base_msg::common::LaneScene;
    using MessageType = ::holo_base_msg::common::LaneScene;
};

template <>
struct DefaultMessageTraits<::holo::common::LaneScene>
{
    using ValueType   = ::holo::common::LaneScene;
    using MessageType = ::holo_base_msg::common::LaneScene;
};

template <>
struct DefaultConversionTraits<::holo::common::LaneScene>
{
    using ValueType   = ::holo::common::LaneScene;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.stamp.sec   = value.GetTimestamp().GetSec();
        message.stamp.nsec  = value.GetTimestamp().GetNsec();
        message.lane_group  = value.GetValue();
        
    }
    static void Convert(MessageType const& message, ValueType& value)
    {
        value.SetTimestamp(::holo::common::Timestamp{message.stamp.sec, message.stamp.nsec});
        value.SetValue(message.lane_group);
    }
};

}  // namespace opendds_wrapper

#endif
