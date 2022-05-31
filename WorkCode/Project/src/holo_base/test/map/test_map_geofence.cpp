/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_map_geofence.cpp
 * @brief Unit test for map geofence
 * @author lisong(lisong@holomaitc.com)
 * @date "2020-03-09"
 */

#include <gtest/gtest.h>

#include <holo/map/geofence.h>

using holo::map::Geofence;
using holo::map::Geofences;

TEST(TestMapGeofence, TestDefaultConstructor)
{
    Geofence map_geofence;

    EXPECT_EQ(map_geofence.GetId(), 0UL);
    EXPECT_EQ(map_geofence.GetFunction(), Geofence::Function::UNKNOWN);
    EXPECT_EQ(map_geofence.GetStartDistance(), 0);
    EXPECT_EQ(map_geofence.GetEndDistance(), 0);
}

TEST(TestMapGeofence, TestSetters)
{
    Geofence map_geofence;
    map_geofence.SetId(20200309UL);
    map_geofence.SetFunction(Geofence::Function::HSA);
    map_geofence.SetStartDistance(100);
    map_geofence.SetEndDistance(200);

    EXPECT_EQ(map_geofence.GetId(), 20200309UL);
    EXPECT_EQ(map_geofence.GetFunction(), Geofence::Function::HSA);
    EXPECT_EQ(map_geofence.GetStartDistance(), 100);
    EXPECT_EQ(map_geofence.GetEndDistance(), 200);
}

static holo::bool_t operator==(const Geofence& left, const Geofence& right)
{
    if (&left == &right)
    {
        return true;
    }

    return (left.GetId() == right.GetId()) && (left.GetFunction() == right.GetFunction()) &&
           (left.GetStartDistance() == right.GetStartDistance()) && (left.GetEndDistance() == right.GetEndDistance());
}

static holo::bool_t operator==(const std::vector<Geofence>& left, const std::vector<Geofence>& right)
{
    if (&left == &right)
    {
        return true;
    }

    if (left.size() != right.size())
    {
        return false;
    }

    for (std::size_t idx = 0UL; idx < left.size(); ++idx)
    {
        if (!(left.at(idx) == right.at(idx)))
        {
            return false;
        }
    }
    return true;
}

TEST(TestMapGeofences, TestDefaultConstructor)
{
    Geofences             map_geofences;
    holo::common::Timestamp       time_stamp;
    std::vector<Geofence> geofences;

    EXPECT_TRUE(map_geofences.GetTimestamp() == time_stamp);
    EXPECT_TRUE(map_geofences.GetGeofences() == geofences);
}

TEST(TestMapGeofences, TestSetters)
{
    Geofences       map_geofences;
    holo::common::Timestamp time_stamp(1u, 1u);
    Geofence        map_geofence;
    map_geofence.SetId(20200309UL);
    map_geofence.SetFunction(Geofence::Function::HSA);
    map_geofence.SetStartDistance(100);
    map_geofence.SetEndDistance(200);
    std::vector<Geofence> geofences{map_geofence};

    map_geofences.SetTimestamp(time_stamp);
    map_geofences.SetGeofences(geofences);

    EXPECT_TRUE(map_geofences.GetTimestamp() == time_stamp);
    EXPECT_TRUE(map_geofences.GetGeofences() == geofences);
}

static holo::bool_t operator==(const Geofences& left, const Geofences& right)
{
    if (&left == &right)
    {
        return true;
    }

    return (left.GetTimestamp() == right.GetTimestamp()) && (left.GetGeofences() == right.GetGeofences());
}

TEST(TestMapGeofences, TestCopyConstructor)
{
    Geofences       old_map_geofences;
    holo::common::Timestamp time_stamp(1u, 1u);
    Geofence        map_geofence;
    map_geofence.SetId(20200309UL);
    map_geofence.SetFunction(Geofence::Function::HSA);
    map_geofence.SetStartDistance(100);
    map_geofence.SetEndDistance(200);
    std::vector<Geofence> geofences{map_geofence};

    old_map_geofences.SetTimestamp(time_stamp);
    old_map_geofences.SetGeofences(geofences);

    Geofences new_map_geofences(old_map_geofences);

    EXPECT_TRUE(old_map_geofences == new_map_geofences);
}

TEST(TestMapGeofences, TestMoveConstructor)
{
    Geofences       old_map_geofences;
    holo::common::Timestamp time_stamp(1u, 1u);
    Geofence        map_geofence;
    map_geofence.SetId(20200309UL);
    map_geofence.SetFunction(Geofence::Function::HSA);
    map_geofence.SetStartDistance(100);
    map_geofence.SetEndDistance(200);
    std::vector<Geofence> geofences{map_geofence};

    old_map_geofences.SetTimestamp(time_stamp);
    old_map_geofences.SetGeofences(geofences);

    Geofences temp_map_geofences(old_map_geofences);
    Geofences new_map_geofences(std::move(temp_map_geofences));

    EXPECT_TRUE(old_map_geofences == new_map_geofences);
}

TEST(TestMapGeofences, TestCopyAssignment)
{
    Geofences       old_map_geofences;
    holo::common::Timestamp time_stamp(1u, 1u);
    Geofence        map_geofence;
    map_geofence.SetId(20200309UL);
    map_geofence.SetFunction(Geofence::Function::HSA);
    map_geofence.SetStartDistance(100);
    map_geofence.SetEndDistance(200);
    std::vector<Geofence> geofences{map_geofence};

    old_map_geofences.SetTimestamp(time_stamp);
    old_map_geofences.SetGeofences(geofences);

    Geofences new_map_geofences;

    EXPECT_FALSE(old_map_geofences == new_map_geofences);
    new_map_geofences = old_map_geofences;
    EXPECT_TRUE(old_map_geofences == new_map_geofences);
}

TEST(TestMapGeofences, TestMoveAssignment)
{
    Geofences       old_map_geofences;
    holo::common::Timestamp time_stamp(1u, 1u);
    Geofence        map_geofence;
    map_geofence.SetId(20200309UL);
    map_geofence.SetFunction(Geofence::Function::HSA);
    map_geofence.SetStartDistance(100);
    map_geofence.SetEndDistance(200);
    std::vector<Geofence> geofences{map_geofence};

    old_map_geofences.SetTimestamp(time_stamp);
    old_map_geofences.SetGeofences(geofences);

    Geofences new_map_geofences;

    EXPECT_FALSE(old_map_geofences == new_map_geofences);
    Geofences temp_map_geofences(old_map_geofences);
    new_map_geofences = std::move(temp_map_geofences);
    EXPECT_TRUE(old_map_geofences == new_map_geofences);
}

TEST(TestMapGeofences, GetSerializedSize)
{
    Geofences       geofences;
    ASSERT_EQ(12, geofences.GetSerializedSize<4U>());
    ASSERT_EQ(16, geofences.GetSerializedSize<8U>());
}

TEST(TestMapGeofences, SerializeAndDeserialize)
{
    Geofences       geofences_input, geofences_output;
    Geofence        map_geofence;

    holo::common::Timestamp time_stamp(1u, 1u);
    map_geofence.SetId(20200309UL);
    map_geofence.SetFunction(Geofence::Function::HSA);
    map_geofence.SetStartDistance(100);
    map_geofence.SetEndDistance(200);
    std::vector<Geofence> geofences;
    geofences.push_back(map_geofence);

    map_geofence.SetId(2020111111UL);
    map_geofence.SetFunction(Geofence::Function::HSA);
    map_geofence.SetStartDistance(150);
    map_geofence.SetEndDistance(250);
    geofences.push_back(map_geofence);

    geofences_input.SetTimestamp(time_stamp);
    geofences_input.SetGeofences(geofences);

    uint8_t buffer[1280];
    holo::serialization::Serializer<>          serializer(buffer, 1280);
    serializer << geofences_input;
    ASSERT_EQ(geofences_input.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> geofences_output;

    EXPECT_EQ(geofences_input.GetTimestamp(), geofences_output.GetTimestamp());
    EXPECT_EQ(geofences_input.GetGeofences().size(), geofences_output.GetGeofences().size());

    for (std::size_t idx = 0UL; idx < geofences_output.GetGeofences().size(); ++idx)
    {
        EXPECT_EQ(geofences_input.GetGeofences().at(idx).GetId(), geofences_output.GetGeofences().at(idx).GetId());
        EXPECT_EQ(geofences_input.GetGeofences().at(idx).GetFunction(), geofences_output.GetGeofences().at(idx).GetFunction());
        EXPECT_EQ(geofences_input.GetGeofences().at(idx).GetStartDistance(), geofences_output.GetGeofences().at(idx).GetStartDistance());
        EXPECT_EQ(geofences_input.GetGeofences().at(idx).GetEndDistance(), geofences_output.GetGeofences().at(idx).GetEndDistance());
    }
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
