/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_camera_cover.h
 * @brief Unit test for class CamerasCoverMessage
 * @author chengxiang(chengxiang@holomaitc.com)
 * @date 2021-08-04
 */
#include <gtest/gtest.h>
#include <dds_micro_wrapper/traits.h>
#include <holo/parking/surrounding/camera_dirty.h>
#include <holo/serialization/serializer.h>

using CamerasDirtyVecortType  = holo::parking::surroundings::CamerasDirtyContainer;
using CameraDirtyType         = CamerasDirtyVecortType::value_type;

TEST(CamerasDirtyContainer, DefaultConstructor)
{
    CamerasDirtyVecortType dirtyInfo;

    ASSERT_EQ(dirtyInfo.GetTimestamp(), holo::common::Timestamp());
    ASSERT_EQ(dirtyInfo.size(), size_t(0));
}

TEST(CamerasDirtyContainer, GetterAndSetter)
{
    uint8_t cameraSize = 5;
    CamerasDirtyVecortType camerasMessage;

    holo::common::Timestamp timestamp(123456789, 1213);
    camerasMessage.SetTimestamp(timestamp);
    holo::common::Timestamp subTimestamp(1234567, 1357);
    for (uint8_t i = 0; i < cameraSize; i++)
    {
        CameraDirtyType camera;
        camera.SetTimestamp(subTimestamp);
        camera.SetCameraId(CameraDirtyType::CameraId(i + 1));

        camera.push_back(static_cast<uint8_t>(CameraDirtyType::CLEAR));
        camera.push_back(static_cast<uint8_t>(CameraDirtyType::DIRTY));
        camera.push_back(static_cast<uint8_t>(CameraDirtyType::TRANSPARENT));
        camera.push_back(static_cast<uint8_t>(CameraDirtyType::TRANSLUCENT));
        camerasMessage.push_back(camera);
    }
    // check results
    ASSERT_EQ(camerasMessage.GetTimestamp(), timestamp);
    ASSERT_EQ(camerasMessage.size(), cameraSize);

    uint8_t idx = 0;
    for (auto iter = camerasMessage.cbegin();
         iter != camerasMessage.cend(); iter++, idx++)
    {
        ASSERT_EQ(iter->GetTimestamp(), subTimestamp);
        ASSERT_EQ(iter->GetCameraId(), CameraDirtyType::CameraId(idx + 1));
        // ASSERT_EQ(iter->GetCoverDegrees(), CameraCover::TRANSPARENT);
    }
}

TEST(CamerasDirtyContainer, ConvertTrait)
{
    /// < prepare test data.
    CamerasDirtyVecortType camerasMessage;
    camerasMessage.SetTimestamp(holo::common::Timestamp(12345, 11223));

    uint8_t cameraSize = 5;
    holo::common::Timestamp subTimestamp(1234567, 1357);
    for (uint8_t i = 0; i < cameraSize; i++)
    {
        CameraDirtyType camera;
        camera.SetTimestamp(subTimestamp);
        camera.SetCameraId(CameraDirtyType::CameraId(i + 1));

        camera.push_back(static_cast<uint8_t>(CameraDirtyType::CLEAR));
        camera.push_back(static_cast<uint8_t>(CameraDirtyType::DIRTY));
        camera.push_back(static_cast<uint8_t>(CameraDirtyType::TRANSPARENT));
        camera.push_back(static_cast<uint8_t>(CameraDirtyType::TRANSLUCENT));

        camerasMessage.push_back(camera);
    }

    /// < Test use default serialization convert traits convert message, do data translations
    using BuiltinBufferTraits = dds_micro_wrapper::SerializationTraits<CamerasDirtyVecortType>;
    dds_micro_wrapper_BuiltinBuffer buffer;
    CamerasDirtyVecortType outputMessage;
    BuiltinBufferTraits::Convert( camerasMessage, buffer);
    BuiltinBufferTraits::Convert( buffer, outputMessage);

    /// < Check translate result
    ASSERT_EQ(camerasMessage.GetTimestamp(), outputMessage.GetTimestamp());
    ASSERT_EQ(outputMessage.GetTimestamp() , holo::common::Timestamp(12345, 11223));
    ASSERT_EQ(camerasMessage.size(), outputMessage.size());
    ASSERT_EQ(outputMessage.size(), 5);

    for (size_t idx = 0; idx < outputMessage.size(); idx++)
    {
        ASSERT_EQ( camerasMessage.at(idx), outputMessage.at(idx) );
        ASSERT_EQ( camerasMessage.at(idx).GetCameraId() , outputMessage.at(idx).GetCameraId() );
        ASSERT_EQ( camerasMessage.at(idx).GetTimestamp(), outputMessage.at(idx).GetTimestamp() );

        ASSERT_EQ( outputMessage.at(idx).size(), 4);
        ASSERT_EQ( camerasMessage.at(idx).size(), outputMessage.at(idx).size());
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
