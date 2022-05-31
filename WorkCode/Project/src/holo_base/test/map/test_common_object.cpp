#include <iostream>
#include <gtest/gtest.h>
#include <holo/map/common_object.h>

TEST(TestMapCommonObject, MoveConstruct)
{
    holo::map::CommonObject   mapCommonObj, mapCommonObj2;
    mapCommonObj = std::move(mapCommonObj2);
    holo::map::CommonObject   mapCommonObj3(std::move(mapCommonObj2));
}

TEST(TestMapCommonObject, OperatorEqual)
{
    holo::map::CommonObject   mapCommonObj, mapCommonObj2;
    mapCommonObj = mapCommonObj2;
}

TEST(TestMapCommonObject, GetSerializedSize)
{
    holo::map::CommonObject   mapCommonObj;
    ASSERT_EQ(40, mapCommonObj.GetSerializedSize<4U>());
    ASSERT_EQ(40, mapCommonObj.GetSerializedSize<8U>());
}

TEST(TestMapCommonObject, SerializeAndDeserialize)
{
    srand(time(0));

    ::holo::uint32_t  i           = 0;
    ::holo::uint32_t  point_count = 0;
    ::holo::map::CommonObject input;
    ::holo::map::CommonObject output;
    input.SetObjectId(rand()%1024);
    input.SetObjectType(holo::map::ObjectType::TYPE_OVERHEAD_CROSSING);
    input.SetBottomPoint(holo::geometry::Point3d((holo::float64_t)(rand()%4096), (holo::float64_t)(rand()%4096), (holo::float64_t)(rand()%4096)));
    ::std::vector<::holo::geometry::Point3d>    vec_points;
    point_count                   = rand()%32;
    vec_points.resize(point_count);
    for (i = 0; i < point_count; ++i)
    {
        vec_points[i] = holo::geometry::Point3d((holo::float64_t)(rand()%4096), (holo::float64_t)(rand()%4096), (holo::float64_t)(rand()%4096));
    }
    input.SetOutLine(vec_points);

    uint8_t buf[2048];
    holo::serialization::Serializer<>          serializer(buf, 2048);

    serializer << input;
    ASSERT_EQ(input.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buf, serializer.GetSize());
    deserializer >> output;

    ASSERT_EQ(input.GetObjectId(), output.GetObjectId());
    ASSERT_EQ(input.GetObjectType(), output.GetObjectType());
    ASSERT_EQ(input.GetBottomPoint().GetX(), output.GetBottomPoint().GetX());
    ASSERT_EQ(input.GetBottomPoint().GetY(), output.GetBottomPoint().GetY());
    ASSERT_EQ(input.GetBottomPoint().GetZ(), output.GetBottomPoint().GetZ());
    ASSERT_EQ(input.GetOutLine().size(), output.GetOutLine().size());
    ASSERT_EQ((uint64_t)(point_count), output.GetOutLine().size());
    for (i = 0; i < point_count; ++i)
    {
        ASSERT_EQ(input.GetOutLine()[i].GetX(), output.GetOutLine()[i].GetX());
        ASSERT_EQ(input.GetOutLine()[i].GetY(), output.GetOutLine()[i].GetY());
        ASSERT_EQ(input.GetOutLine()[i].GetZ(), output.GetOutLine()[i].GetZ());
    }
}

TEST(TestMapCommonObject, Serialize_Deserialize_Serializer_Deserializer_4ByteAligned)
{
    srand(time(0));

    ::holo::uint32_t  i           = 0;
    ::holo::uint32_t  point_count = 0;
    ::holo::map::CommonObject input;
    ::holo::map::CommonObject output;
    input.SetObjectId(rand()%1024);
    input.SetObjectType(holo::map::ObjectType::TYPE_OVERHEAD_CROSSING);
    input.SetBottomPoint(holo::geometry::Point3d((holo::float64_t)(rand()%4096), (holo::float64_t)(rand()%4096), (holo::float64_t)(rand()%4096)));
    ::std::vector<::holo::geometry::Point3d>    vec_points;
    point_count                   = rand()%32;
    vec_points.resize(point_count);
    for (i = 0; i < point_count; ++i)
    {
        vec_points[i] = holo::geometry::Point3d((holo::float64_t)(rand()%4096), (holo::float64_t)(rand()%4096), (holo::float64_t)(rand()%4096));
    }
    input.SetOutLine(vec_points);

    static const uint32_t  SERIALIZATION_BUF_LEN = 2048;

    uint8_t buffer1[SERIALIZATION_BUF_LEN];
    uint8_t buffer2[SERIALIZATION_BUF_LEN];
    holo::serialization::Serializer<true, 4>                         serializer1(buffer1, SERIALIZATION_BUF_LEN);
    holo::serialization::Serializer<true, 4>                         serializer2(buffer2, SERIALIZATION_BUF_LEN);

    uint8_t buffer_short[32];
    holo::serialization::Serializer<true, 4>                         serializer_short(buffer_short, 32);

    uint32_t  serialization_result   = 0;
    uint32_t  deserialization_result = 0;
    uint32_t  expected_size          = input.GetSerializedSize();
    ASSERT_EQ(expected_size&3, 0);

    try {
        serialization_result = (serializer1 << input).GetSize();
    }
    catch (holo::serialization::SerializationBufferOverflowException& e)
    {
    }
    catch (...)
    {
        FAIL() << "serialization Unexpected exception caught";
    }
    holo::serialization::Deserializer<true, 4>   deserializer(buffer1, serializer1.GetSize());
    try {
        deserialization_result = (deserializer >> output).GetOffset();
    }
    catch (holo::serialization::DeserializationBufferUnderflowException& e)
    {
    }
    catch (...)
    {
        FAIL() << "deserialization Unexpected exception caught";
    }
    ASSERT_EQ(serialization_result&3, 0);
    ASSERT_EQ(serialization_result, expected_size);
    ASSERT_EQ(deserialization_result, deserialization_result);
    ASSERT_EQ(input.GetObjectId(), output.GetObjectId());
    ASSERT_EQ(input.GetObjectType(), output.GetObjectType());
    ASSERT_EQ(input.GetBottomPoint().GetX(), output.GetBottomPoint().GetX());
    ASSERT_EQ(input.GetBottomPoint().GetY(), output.GetBottomPoint().GetY());
    ASSERT_EQ(input.GetBottomPoint().GetZ(), output.GetBottomPoint().GetZ());
    ASSERT_EQ(input.GetOutLine().size(), output.GetOutLine().size());
    ASSERT_EQ((uint64_t)(point_count), output.GetOutLine().size());
    for (i = 0; i < point_count; ++i)
    {
        ASSERT_EQ(input.GetOutLine()[i].GetX(), output.GetOutLine()[i].GetX());
        ASSERT_EQ(input.GetOutLine()[i].GetY(), output.GetOutLine()[i].GetY());
        ASSERT_EQ(input.GetOutLine()[i].GetZ(), output.GetOutLine()[i].GetZ());
    }

    try {
        serialization_result = (serializer2 << output).GetSize();
    }
    catch (holo::serialization::SerializationBufferOverflowException& e)
    {
    }
    catch (...)
    {
        FAIL() << "serialization Unexpected exception caught";
    }
    ASSERT_TRUE(0 == memcmp(buffer1, buffer2, expected_size));


    EXPECT_THROW(serializer_short << input, holo::serialization::SerializationBufferOverflowException);
    holo::serialization::Deserializer<true, 4>    deserializer_short(buffer_short, serializer_short.GetSize());
    EXPECT_THROW(deserializer_short >> output, holo::serialization::DeserializationBufferUnderflowException);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
