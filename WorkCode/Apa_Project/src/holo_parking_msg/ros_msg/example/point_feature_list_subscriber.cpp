/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point_feature_list_subscriber.cpp
 * @brief an example to subscribe a PointFeaturePtrListf message from ROS
 * @author lifeng(lifeng@holomaitc.com)
 * @date 2021-01-08
 */

#include <holo_parking_msg/ros_msg/vision/point_feature_list_traits.h>
#include <ros_wrapper/ros_bus.h>

using BusType = ros_wrapper::RosBus;

void PointFeatureListCallback(holo::parking::vision::PointFeaturePtrListf const& value)
{
    std::cout << "PointFeaturePtrListf sample received" << std::endl;
    std::cout << "Timestamp: " << value.GetTimestamp().GetSec() << "." << value.GetTimestamp().GetNsec() << std::endl;
}

int main(int argc, char** argv)
{
    BusType::Initialize(argc, argv, "point_feature_list_subscriber");
    BusType bus(0, "Data");

    auto reader = bus.AddReader<holo::parking::vision::PointFeaturePtrListf,
                                BusType::DefaultConversionTraitsType<holo::parking::vision::PointFeaturePtrListf> >(
        "point_feature_list");
    reader.SetOnDataAvailableCallback(PointFeatureListCallback);

    BusType::AsyncSpin(1);
    while (BusType::IsRunning())
    {
        sleep(1);
    }
    return 0;
}
