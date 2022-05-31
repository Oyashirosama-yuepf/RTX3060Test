/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point_feature_list_traits.cpp
 * @brief This file implement function of PointFeaturePtrListTraits.
 * @author lifeng(lifeng@holomaitc.com)
 * @date 2021-01-08
 */

#include <holo_parking_msg/opendds_msg/vision/point_feature_list_traits.h>

namespace opendds_wrapper
{
void DefaultConversionTraits<::holo::parking::vision::PointFeaturef>::Convert(ValueType const& value,
                                                                              MessageType&     message)
{
    message.x          = value.GetPointPosition().GetX();
    message.y          = value.GetPointPosition().GetY();
    message.confidence = static_cast<holo::float32_t>(value.GetConfidence());
    const auto& desc   = value.GetDescriptor();
    message.descriptor.length(value.GetDescriptorDimension());

    for (size_t i = 0u; i < value.GetDescriptorDimension(); ++i)
    {
        message.descriptor[i] = desc.at(i);
    }
}

void DefaultConversionTraits<::holo::parking::vision::PointFeaturef>::Convert(MessageType const& message,
                                                                              ValueType&         value)
{
    ValueType::Point2Type     position(message.x, message.y);
    ValueType::ScalarType     confidence = static_cast<ValueType::ScalarType>(message.confidence);
    ValueType::DescriptorType desc;
    desc.reserve(message.descriptor.length());

    for (size_t i = 0; i < message.descriptor.length(); ++i)
    {
        desc.emplace_back(message.descriptor[i]);
    }

    value = ValueType(position, desc, confidence);
}
}  // namespace opendds_wrapper
