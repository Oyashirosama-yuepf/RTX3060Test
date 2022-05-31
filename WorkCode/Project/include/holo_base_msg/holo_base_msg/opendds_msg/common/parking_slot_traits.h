/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_slot_traits.h
 * @brief This header file defines trait for parking slot traits.
 * @author Yanwei. Du (duyanwei@holomatic.com)
 * @date 2021-03-24
 */

#ifndef HOLO_BASE_MSG_OPENDDS_MSG_PARKING_SLOT_TRAITS_H_
#define HOLO_BASE_MSG_OPENDDS_MSG_PARKING_SLOT_TRAITS_H_

#include <holo/common/parking_slot.h>

#include <opendds_wrapper/traits.h>

#include <holo_base_msg/common/ParkingSlotC.h>
#include <holo_base_msg/common/ParkingSlotS.h>
#include <holo_base_msg/common/ParkingSlotTypeSupportC.h>
#include <holo_base_msg/common/ParkingSlotTypeSupportImpl.h>
#include <holo_base_msg/common/ParkingSlotTypeSupportS.h>
#include <holo_base_msg/opendds_msg/geometry/point_traits.h>

namespace opendds_wrapper
{
/* ParkingSlot traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::common::ParkingSlotFramef>
{
    using ValueType   = ::holo_base_msg::common::ParkingSlotFramef;
    using MessageType = ::holo_base_msg::common::ParkingSlotFramef;
};

template <>
struct DefaultMessageTraits<::holo::common::ParkingSlotFrameT<::holo::float32_t>>
{
    using ValueType   = ::holo::common::ParkingSlotFrameT<::holo::float32_t>;
    using MessageType = ::holo_base_msg::common::ParkingSlotFramef;
};

template <>
struct DefaultMessageTraits<::holo_base_msg::common::ParkingSlotFramed>
{
    using ValueType   = ::holo_base_msg::common::ParkingSlotFramed;
    using MessageType = ::holo_base_msg::common::ParkingSlotFramed;
};

template <>
struct DefaultMessageTraits<::holo::common::ParkingSlotFrameT<::holo::float64_t>>
{
    using ValueType   = ::holo::common::ParkingSlotFrameT<::holo::float64_t>;
    using MessageType = ::holo_base_msg::common::ParkingSlotFramed;
};

template <typename T>
struct DefaultConversionTraits<::holo::common::ParkingSlotFrameT<T>>
{
    using ValueType   = ::holo::common::ParkingSlotFrameT<T>;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.stamp.sec  = value.GetTimestamp().GetSec();
        message.stamp.nsec = value.GetTimestamp().GetNsec();
        message.coord      = static_cast<::holo::uint32_t>(value.GetCoordinate());
        message.point_list.length(value.size());
        for (size_t idx = 0; idx < value.size(); idx++)
        {
            message.point_list[idx].id                       = value[idx].id;
            message.point_list[idx].is_valid                 = value[idx].is_valid;
            message.point_list[idx].type                     = static_cast<::holo::uint32_t>(value[idx].type);
            message.point_list[idx].position                 = static_cast<::holo::uint32_t>(value[idx].position);
            message.point_list[idx].status                   = static_cast<::holo::uint32_t>(value[idx].status);
            message.point_list[idx].width                    = value[idx].width;
            message.point_list[idx].height                   = value[idx].height;
            message.point_list[idx].angle                    = value[idx].angle;
            message.point_list[idx].confidence               = value[idx].confidence;
            message.point_list[idx].is_rear_vertex_available = value[idx].is_rear_vertex_available;
            message.point_list[idx].vertices.length(ValueType::ParkingSlotType::VERTEX_NUM);
            for (size_t j = 0; j < ValueType::ParkingSlotType::VERTEX_NUM; j++)
            {
                DefaultConversionTraits<typename ValueType::ParkingSlotType::Point3Type>::Convert(
                    value[idx].vertices[j], message.point_list[idx].vertices[j]);
            }
            message.point_list[idx].is_center_vertex_available = value[idx].is_center_vertex_available;
            message.point_list[idx].center_vertex.x            = value[idx].center_vertex.GetX();
            message.point_list[idx].center_vertex.y            = value[idx].center_vertex.GetY();
            message.point_list[idx].center_vertex.z            = value[idx].center_vertex.GetZ();
            message.point_list[idx].is_stopper_available       = value[idx].is_stopper_available;
            message.point_list[idx].stopper_vertices.length(ValueType::ParkingSlotType::STOPPER_VERTEX_NUM);
            for (size_t j = 0; j < ValueType::ParkingSlotType::STOPPER_VERTEX_NUM; j++)
            {
                DefaultConversionTraits<typename ValueType::ParkingSlotType::Point3Type>::Convert(
                    value[idx].stopper_vertices[j], message.point_list[idx].stopper_vertices[j]);
            }
        }
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        value.SetTimestamp(::holo::common::Timestamp{message.stamp.sec, message.stamp.nsec});
        value.SetCoordinate(static_cast<::holo::common::Coordinate>(message.coord));
        value.clear();
        value.reserve(message.point_list.length());
        for (size_t idx = 0; idx < message.point_list.length(); idx++)
        {
            ::holo::common::ParkingSlotT<T> parking_slot;

            parking_slot.id       = message.point_list[idx].id;
            parking_slot.is_valid = message.point_list[idx].is_valid;
            parking_slot.type = static_cast<typename ValueType::ParkingSlotType::Type>(message.point_list[idx].type);
            parking_slot.position =
                static_cast<typename ValueType::ParkingSlotType::Position>(message.point_list[idx].position);
            parking_slot.status =
                static_cast<typename ValueType::ParkingSlotType::Status>(message.point_list[idx].status);
            parking_slot.width                    = message.point_list[idx].width;
            parking_slot.height                   = message.point_list[idx].height;
            parking_slot.angle                    = message.point_list[idx].angle;
            parking_slot.confidence               = message.point_list[idx].confidence;
            parking_slot.is_rear_vertex_available = message.point_list[idx].is_rear_vertex_available;
            for (size_t j = 0; j < ValueType::ParkingSlotType::VERTEX_NUM; j++)
            {
                DefaultConversionTraits<typename ValueType::ParkingSlotType::Point3Type>::Convert(
                    message.point_list[idx].vertices[j], parking_slot.vertices[j]);
            }
            parking_slot.is_center_vertex_available = message.point_list[idx].is_center_vertex_available;
            parking_slot.center_vertex.SetX(message.point_list[idx].center_vertex.x);
            parking_slot.center_vertex.SetY(message.point_list[idx].center_vertex.y);
            parking_slot.center_vertex.SetZ(message.point_list[idx].center_vertex.z);
            parking_slot.is_stopper_available = message.point_list[idx].is_stopper_available;
            for (size_t j = 0; j < ValueType::ParkingSlotType::STOPPER_VERTEX_NUM; j++)
            {
                DefaultConversionTraits<typename ValueType::ParkingSlotType::Point3Type>::Convert(
                    message.point_list[idx].stopper_vertices[j], parking_slot.stopper_vertices[j]);
            }
            value.push_back(parking_slot);
        }
    }
};

}  // namespace opendds_wrapper

#endif
