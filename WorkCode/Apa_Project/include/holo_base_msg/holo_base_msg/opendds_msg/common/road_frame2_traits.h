#ifndef OPENDDS_MSG_COMMON_ROAD_FRAME_TRAITS_H_
#define OPENDDS_MSG_COMMON_ROAD_FRAME_TRAITS_H_

#include <holo/geometry/curve.h>
#include <holo/common/road_frame2.h>
#include <holo/serialization/serialization.h>
#include <opendds_wrapper/builtin/BuiltinC.h>
#include <opendds_wrapper/builtin/BuiltinS.h>
#include <opendds_wrapper/builtin/BuiltinTypeSupportC.h>
#include <opendds_wrapper/builtin/BuiltinTypeSupportImpl.h>
#include <opendds_wrapper/builtin/BuiltinTypeSupportS.h>
#include <opendds_wrapper/traits.h>

namespace opendds_wrapper
{
/* RoadFrame2 traits */

template <typename Curve, size_t SIZE>
struct DefaultMessageTraits<::holo::common::RoadFrame<Curve,SIZE>>
{
    using ValueType   = ::holo::common::RoadFrame<Curve, SIZE>;
    using MessageType = ::opendds_wrapper::BuiltinBuffer;
};

template <typename Curve, size_t SIZE>
struct DefaultConversionTraits<::holo::common::RoadFrame<Curve,SIZE>>
{
    using ValueType   = ::holo::common::RoadFrame<Curve, SIZE>;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(ValueType const& value, MessageType& message)
    {
        size_t size = 0U;
        size_t capacity = value.GetSerializedSize();
        message.value.length(capacity);
        ::holo::serialization::Serializer<> ser(static_cast<::holo::uint8_t*>(&message.value[0U]), capacity, size);
        ser << value;
    }
    static void Convert(MessageType const& message, ValueType& value)
    {
        size_t size     = message.value.length();
        size_t capacity = size;
        ::holo::serialization::Deserializer<> des(const_cast<::holo::uint8_t*>(&message.value[0U]), capacity, size);
        des >> value;
    }
};

}  // namespace opendds_wrapper

#endif
