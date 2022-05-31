/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_app_status.cpp
 * @brief Unit test for AppStatus object.
 * @author GuoGuangchao(guoguangchao@holomatic.com)
 * @date 2020-04-29
 */

#include <gtest/gtest.h>
#include <holo/common/app_status.h>
#include <memory>
#include <vector>

using holo::common::AppStatus;

TEST(AppStatus, ConstructByNodeIdAndStatus)
{
    holo::common::Timestamp timestamp(12345, 67890);
    AppStatus       as(timestamp, 0xA1);
    as.push_back(0);
    ASSERT_EQ(as.GetTimestamp().GetSec(), 12345);
    ASSERT_EQ(as.GetTimestamp().GetNsec(), 67890);
    ASSERT_EQ(as.GetNodeId(), 0xA1);
    ASSERT_EQ(as[0], 0);
}

TEST(AppStatus, ConstructCopy)
{
    holo::common::Timestamp timestamp(12345, 67890);
    AppStatus       as0(timestamp, 0xA1);
    as0.push_back(0);
    as0.push_back(1);
    AppStatus as1(as0);
    ASSERT_EQ(as1.GetTimestamp().GetSec(), 12345);
    ASSERT_EQ(as1.GetTimestamp().GetNsec(), 67890);
    ASSERT_EQ(as1.GetNodeId(), 0xA1);
    ASSERT_EQ(as1[0], 0);
    ASSERT_EQ(as1[1], 1);
}

TEST(AppStatus, ConstructAssignOperator)
{
    holo::common::Timestamp timestamp(12345, 67890);
    AppStatus       as0(timestamp, 0xA1);
    as0.push_back(0);
    as0.push_back(1);
    AppStatus as1 = as0;
    ASSERT_EQ(as1.GetTimestamp().GetSec(), 12345);
    ASSERT_EQ(as1.GetTimestamp().GetNsec(), 67890);
    ASSERT_EQ(as1.GetNodeId(), 0xA1);
    ASSERT_EQ(as1[0], 0);
    ASSERT_EQ(as1[1], 1);
}

TEST(AppStatus, SetTimestamp)
{
    AppStatus       as(holo::common::Timestamp(0, 0), 0xa1);
    holo::common::Timestamp timestamp1(12345, 67890);
    as.SetTimestamp(timestamp1);
    ASSERT_EQ(as.GetTimestamp().GetSec(), 12345);
    ASSERT_EQ(as.GetTimestamp().GetNsec(), 67890);
    holo::common::Timestamp timestamp2(44444, 55555);
    as.SetTimestamp(timestamp2);
    ASSERT_EQ(as.GetTimestamp().GetSec(), 44444);
    ASSERT_EQ(as.GetTimestamp().GetNsec(), 55555);
}

TEST(AppStatus, SetNodeId)
{
    AppStatus as(holo::common::Timestamp(0, 0), 0xa1);
    as.SetNodeId(0xA1);
    ASSERT_EQ(as.GetNodeId(), 0xA1);
    as.SetNodeId(0x1A);
    ASSERT_EQ(as.GetNodeId(), 0x1A);
}

TEST(AppStatus, SerializeDeserialize)
{
    AppStatus status = {0x01, 0x02, 0x03, 0x04};
    AppStatus dst;
    status.SetTimestamp({100, 200});
    status.SetNodeId(10);

    uint8_t buffer[1024];
    holo::serialization::Serializer<>          ser(buffer, 1024);
    ser << status;

    ASSERT_EQ(ser.GetSize(), status.GetSerializedSize());

    holo::serialization::Deserializer<> des(buffer, ser.GetSize());
    des >> dst;
    
    EXPECT_EQ(status.GetTimestamp(), dst.GetTimestamp());
    EXPECT_EQ(status.GetNodeId(), dst.GetNodeId());
    ASSERT_EQ(status.size(), dst.size());
    for(size_t i = 0U; i < status.size(); ++i)
    {
        EXPECT_EQ(status[i], dst[i]);
    }

}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
