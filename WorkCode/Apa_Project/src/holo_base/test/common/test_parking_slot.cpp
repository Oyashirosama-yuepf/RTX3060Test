/*!
 * @file test_parking_slot.cpp
 * @brief parking slot unit test
 * @author duyanwei@holomatic.com
 * @date 2021-03-24
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <gtest/gtest.h>

#include <holo/common/parking_slot.h>

using namespace holo;
using namespace holo::common;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ParkingSlot, GetSerializedSize)
{
    ParkingSlot ps;
    ASSERT_EQ(224u, ps.GetSerializedSize<4U>());
    ASSERT_EQ(232u, ps.GetSerializedSize<8U>());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ParkingSlot, SerializeDeserialize)
{
    ParkingSlot in, out;
    {
        in.id                         = 10u;
        in.is_valid                   = true;
        in.type                       = ParkingSlot::Type::ANGLE;
        in.position                   = ParkingSlot::Position::BACK;
        in.status                     = ParkingSlot::Status::FREE;
        in.width                      = 12.0;
        in.height                     = 5.0;
        in.angle                      = 0.7;
        in.confidence                 = 0.9;
        in.is_rear_vertex_available   = true;
        in.vertices[0]                = geometry::Point3(1.0, 2.0, 3.0);
        in.vertices[1]                = geometry::Point3(1.1, 2.1, 3.1);
        in.vertices[2]                = geometry::Point3(1.2, 2.2, 3.2);
        in.vertices[3]                = geometry::Point3(1.3, 2.3, 3.3);
        in.is_center_vertex_available = true;
        in.center_vertex              = geometry::Point3(0.1, -0.2, 0.3);
        in.is_stopper_available       = true;
        in.stopper_vertices[0]        = geometry::Point3(5.0, 5.1, 5.2);
        in.stopper_vertices[1]        = geometry::Point3(6.0, 6.1, 6.2);
    }

    uint8_t                           buffer[512];
    holo::serialization::Serializer<> serializer(buffer, 512);
    serializer << in;
    ASSERT_EQ(in.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> out;

    // check result
    ASSERT_EQ(out.id, in.id);
    ASSERT_EQ(out.is_valid, in.is_valid);
    ASSERT_EQ(out.type, in.type);
    ASSERT_EQ(out.position, in.position);
    ASSERT_EQ(out.status, in.status);
    ASSERT_EQ(out.width, in.width);
    ASSERT_EQ(out.height, in.height);
    ASSERT_EQ(out.angle, in.angle);
    ASSERT_EQ(out.confidence, in.confidence);
    ASSERT_EQ(out.is_rear_vertex_available, in.is_rear_vertex_available);
    ASSERT_EQ(out.vertices[0], in.vertices[0]);
    ASSERT_EQ(out.vertices[1], in.vertices[1]);
    ASSERT_EQ(out.vertices[2], in.vertices[2]);
    ASSERT_EQ(out.vertices[3], in.vertices[3]);
    ASSERT_EQ(out.is_center_vertex_available, in.is_center_vertex_available);
    ASSERT_EQ(out.center_vertex, in.center_vertex);
    ASSERT_EQ(out.is_stopper_available, in.is_stopper_available);
    ASSERT_EQ(out.stopper_vertices[0], in.stopper_vertices[0]);
    ASSERT_EQ(out.stopper_vertices[1], in.stopper_vertices[1]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ParkingSlotFrame, GetSerializedSize)
{
    ParkingSlotFrame frame;
    frame.resize(10);
    ASSERT_EQ(2256u, frame.GetSerializedSize<4U>());
    ASSERT_EQ(2336u, frame.GetSerializedSize<8U>());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ParkingSlotFrame, SerializeDeserialize)
{
    ParkingSlotFrame in, out;

    size_t const num = 10u;

    for (size_t i = 0u; i < num; ++i)
    {
        ParkingSlot ps;
        ps.id                         = i;
        ps.is_valid                   = true;
        ps.type                       = ParkingSlot::Type::ANGLE;
        ps.position                   = ParkingSlot::Position::BACK;
        ps.status                     = ParkingSlot::Status::FREE;
        ps.width                      = 2.0 * i;
        ps.height                     = 2.5 * i;
        ps.angle                      = 0.7 * i;
        ps.confidence                 = 0.9 * i;
        ps.is_rear_vertex_available   = true;
        ps.vertices[0]                = geometry::Point3(1.0 * i, 2.0 * i, 3.0 * i);
        ps.vertices[1]                = geometry::Point3(1.1 * i, 2.1 * i, 3.1 * i);
        ps.vertices[2]                = geometry::Point3(1.2 * i, 2.2 * i, 3.2 * i);
        ps.vertices[3]                = geometry::Point3(1.3 * i, 2.3 * i, 3.3 * i);
        ps.is_center_vertex_available = true;
        ps.center_vertex              = geometry::Point3(0.1 * i, -0.2 * i, 0.3 * i);
        ps.is_stopper_available       = true;
        ps.stopper_vertices[0]        = geometry::Point3(5.0 * i, 5.1 * i, 5.2 * i);
        ps.stopper_vertices[1]        = geometry::Point3(6.0 * i, 6.1 * i, 6.2 * i);

        in.push_back(ps);
    }

    uint8_t                           buffer[4096];
    holo::serialization::Serializer<> serializer(buffer, 4096);
    serializer << in;
    ASSERT_EQ(in.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> out;

    // check result
    ASSERT_EQ(out.GetTimestamp(), in.GetTimestamp());
    ASSERT_EQ(out.GetCoordinate(), in.GetCoordinate());
    ASSERT_EQ(out.size(), in.size());

    for (size_t i = 0u; i < in.size(); ++i)
    {
        ParkingSlot const& in_ps  = in.at(i);
        ParkingSlot const& out_ps = out.at(i);
        ASSERT_EQ(out_ps.id, in_ps.id);
        ASSERT_EQ(out_ps.is_valid, in_ps.is_valid);
        ASSERT_EQ(out_ps.type, in_ps.type);
        ASSERT_EQ(out_ps.position, in_ps.position);
        ASSERT_EQ(out_ps.status, in_ps.status);
        ASSERT_EQ(out_ps.width, in_ps.width);
        ASSERT_EQ(out_ps.height, in_ps.height);
        ASSERT_EQ(out_ps.angle, in_ps.angle);
        ASSERT_EQ(out_ps.confidence, in_ps.confidence);
        ASSERT_EQ(out_ps.is_rear_vertex_available, in_ps.is_rear_vertex_available);
        ASSERT_EQ(out_ps.vertices[0], in_ps.vertices[0]);
        ASSERT_EQ(out_ps.vertices[1], in_ps.vertices[1]);
        ASSERT_EQ(out_ps.vertices[2], in_ps.vertices[2]);
        ASSERT_EQ(out_ps.vertices[3], in_ps.vertices[3]);
        ASSERT_EQ(out_ps.is_center_vertex_available, in_ps.is_center_vertex_available);
        ASSERT_EQ(out_ps.center_vertex, in_ps.center_vertex);
        ASSERT_EQ(out_ps.is_stopper_available, in_ps.is_stopper_available);
        ASSERT_EQ(out_ps.stopper_vertices[0], in_ps.stopper_vertices[0]);
        ASSERT_EQ(out_ps.stopper_vertices[1], in_ps.stopper_vertices[1]);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}