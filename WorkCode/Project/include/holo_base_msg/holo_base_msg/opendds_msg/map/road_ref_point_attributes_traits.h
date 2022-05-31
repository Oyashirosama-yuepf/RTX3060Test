#ifndef HOLO_BASE_MSG_OPENDDS_MSG_MAP_ROAD_REF_POINT_ATTRIBUTES_TRAITS_H_
#define HOLO_BASE_MSG_OPENDDS_MSG_MAP_ROAD_REF_POINT_ATTRIBUTES_TRAITS_H_

#include <holo/map/road_ref_point_attributes.h>
#include <holo/serialization/serialization.h>
#include <opendds_wrapper/builtin/BuiltinC.h>
#include <opendds_wrapper/builtin/BuiltinS.h>
#include <opendds_wrapper/builtin/BuiltinTypeSupportC.h>
#include <opendds_wrapper/builtin/BuiltinTypeSupportImpl.h>
#include <opendds_wrapper/builtin/BuiltinTypeSupportS.h>
#include <opendds_wrapper/traits.h>

namespace opendds_wrapper
{
template <typename T, size_t SIZE>
struct DefaultMessageTraits<::holo::map::RoadRefPointAttributes<T, SIZE>>
{
    using ValueType   = ::holo::map::RoadRefPointAttributes<T, SIZE>;
    using MessageType = ::opendds_wrapper::BuiltinBuffer;
};

template <typename T, size_t SIZE>
struct DefaultConversionTraits<::holo::map::RoadRefPointAttributes<T, SIZE>>
{
    using ValueType   = ::holo::map::RoadRefPointAttributes<T, SIZE>;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(ValueType const& value, MessageType& message)
    {
        size_t size     = 0U;
        size_t capacity = value.GetSerializedSize();
        message.value.length(capacity);
        ::holo::serialization::Serializer<> ser(static_cast<::holo::uint8_t*>(&message.value[0U]), capacity, size);
        ser << value;
    }
    static void Convert(MessageType const& message, ValueType& value)
    {
        size_t                        size     = message.value.length();
        size_t                        capacity = size;
        ::holo::serialization::Deserializer<> des(const_cast<::holo::uint8_t*>(&message.value[0U]), capacity, size);
        des >> value;
    }
};

}  // namespace opendds_wrapper

#endif
