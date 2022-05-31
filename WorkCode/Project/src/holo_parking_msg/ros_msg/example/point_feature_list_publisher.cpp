/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point_feature_list_subscriber.cpp
 * @brief an example to publish a PointFeaturePtrListf message through ROS
 * @author lifeng(lifeng@holomaitc.com)
 * @date 2021-01-08
 */

#include <holo_parking_msg/ros_msg/vision/point_feature_list_traits.h>
#include <ros_wrapper/ros_bus.h>

using BusType = ros_wrapper::RosBus;

int main(int argc, char** argv)
{
    BusType::Initialize(argc, argv, "point_feature_list_publisher");
    BusType bus(0, "Data");
    auto    writer = bus.AddWriter<holo::parking::vision::PointFeaturePtrListf,
                                BusType::DefaultConversionTraitsType<holo::parking::vision::PointFeaturePtrListf> >(
        "point_feature_list");

    size_t i = 0U;
    while (BusType::IsRunning())
    {
        holo::parking::vision::PointFeaturePtrListf point_feature_list;
        point_feature_list.SetTimestamp(holo::Timestamp{static_cast<uint32_t>(i), static_cast<uint32_t>(i)});
        point_feature_list.SetSensorId(123456);

        // create descriptor
        holo::parking::vision::PointFeaturef::DescriptorType desc;
        desc.reserve(256);

        for (size_t i = 0; i < 256; i++)
        {
            desc.emplace_back(i);
        }

        // create point features
        holo::parking::vision::PointFeaturePtrListf::PointFeaturePtrListType feature_list;
        feature_list.reserve(100);

        for (size_t i = 0; i < 100; i++)
        {
            holo::parking::vision::PointFeaturef::Point2Type pt(i, i);
            feature_list.emplace_back(std::make_shared<holo::parking::vision::PointFeaturef>(pt, desc, 0.666));
        }

        point_feature_list.SetPointFeatureList(feature_list);

        writer.Write(point_feature_list);
        sleep(1);
        ++i;
    }
    return 0;
}
