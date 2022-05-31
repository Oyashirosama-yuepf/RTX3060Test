/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_point_type.cpp
 * @brief Unit test for point cloud point types.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-11-02
 */

#include <gtest/gtest.h>

#include <holo/core/types.h>
#include <holo/geometry/point3.h>
#include <holo/numerics/vector.h>
#include <holo/point_cloud/point_type.h>
#include <vector>

/* Unit test for PointBase */

using ScalarType = holo::float32_t;
using Timestamp  = holo::common::Timestamp;

template <typename T>
class TestPointBase : public holo::point_cloud::details::PointBase<T>
{
public:
    using ScalarType = T;
    using Base       = holo::point_cloud::details::PointBase<ScalarType>;

    TestPointBase() noexcept = default;

    TestPointBase(ScalarType x, ScalarType y, ScalarType z) noexcept : Base{x, y, z}
    {
    }

    TestPointBase(std::initializer_list<ScalarType> il) noexcept : Base{il}
    {
    }

    template <size_t ALIGN>
    size_t GetSerializedSize() const noexcept
    {
        return Base::template GetSerializedSize<ALIGN>();
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        Base::template Serialize(serializer);
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        Base::template Deserialize(deserializer);
    }
};

template <typename T>
class TestPointBase2 : public holo::point_cloud::details::PointBase<T>
{
public:
    using ScalarType = T;
    using Base       = holo::point_cloud::details::PointBase<ScalarType>;

    TestPointBase2(ScalarType x, ScalarType y, ScalarType z) noexcept : Base{x, y, z}
    {
    }
};

/**
 * @brief Test PointBase()
 */
TEST(PointBase, DefaultConstructor)
{
    TestPointBase<ScalarType> pt;
    ASSERT_EQ(static_cast<ScalarType>(0), pt[0]);
    ASSERT_EQ(static_cast<ScalarType>(0), pt[1]);
    ASSERT_EQ(static_cast<ScalarType>(0), pt[2]);
}

/**
 * @brief Test PointBase(initializer_list)
 */
TEST(PointBase, ConstructorInitializerList)
{
    TestPointBase<ScalarType> pt{1, 2, 3, 1, 2, 3};
    // ASSERT_EQ(static_cast<ScalarType>(0), pt[0]);
    // ASSERT_EQ(static_cast<ScalarType>(0), pt[1]);
    // ASSERT_EQ(static_cast<ScalarType>(0), pt[2]);
}

/**
 * @brief Test PointBase(ScalarType x, ScalarType y, ScalarType z)
 */
TEST(PointBase, ConstructWithXYZValues)
{
    TestPointBase<ScalarType> pt{1, 2, 3};
    ASSERT_EQ(static_cast<ScalarType>(1), pt[0]);
    ASSERT_EQ(static_cast<ScalarType>(2), pt[1]);
    ASSERT_EQ(static_cast<ScalarType>(3), pt[2]);
}

/**
 * @brief Test PointBase::operator[](size_t index) element access
 */
TEST(PointBase, BracketOperator_1)
{
    TestPointBase<ScalarType> pt{1, 2, 3};
    ASSERT_EQ(static_cast<ScalarType>(1), pt[0]);
    ASSERT_EQ(static_cast<ScalarType>(2), pt[1]);
    ASSERT_EQ(static_cast<ScalarType>(3), pt[2]);
}

/**
 * @brief Test PointBase::operator[](size_t index) element modification
 */
TEST(PointBase, BracketOperator_2)
{
    TestPointBase<ScalarType> pt{1, 2, 3};
    pt[0] = 2;
    pt[1] = 3;
    pt[2] = 4;
    ASSERT_EQ(static_cast<ScalarType>(2), pt[0]);
    ASSERT_EQ(static_cast<ScalarType>(3), pt[1]);
    ASSERT_EQ(static_cast<ScalarType>(4), pt[2]);
}

/**
 * @brief Test PointBase::operator[](size_t index) const element access
 */
TEST(PointBase, BracketOperator_3)
{
    TestPointBase<ScalarType> const pt{1, 2, 3};
    ASSERT_EQ(static_cast<ScalarType>(1), pt[0]);
    ASSERT_EQ(static_cast<ScalarType>(2), pt[1]);
    ASSERT_EQ(static_cast<ScalarType>(3), pt[2]);
}

/**
 * @brief Test PointBase::at(size_t index) element access
 */
TEST(PointBase, at_1)
{
    TestPointBase<ScalarType> pt{1, 2, 3};
    ASSERT_EQ(static_cast<ScalarType>(1), pt.at(0));
    ASSERT_EQ(static_cast<ScalarType>(2), pt.at(1));
    ASSERT_EQ(static_cast<ScalarType>(3), pt.at(2));
}

/**
 * @brief Test PointBase::at(size_t index) element modification
 */
TEST(PointBase, at_2)
{
    TestPointBase<ScalarType> pt{1, 2, 3};
    pt.at(0) = 2;
    pt.at(1) = 3;
    pt.at(2) = 4;
    ASSERT_EQ(static_cast<ScalarType>(2), pt.at(0));
    ASSERT_EQ(static_cast<ScalarType>(3), pt.at(1));
    ASSERT_EQ(static_cast<ScalarType>(4), pt.at(2));
}

/**
 * @brief Test PointBase::at(size_t index) const element access
 */
TEST(PointBase, at_3)
{
    TestPointBase<ScalarType> const pt{1, 2, 3};
    ASSERT_EQ(static_cast<ScalarType>(1), pt.at(0));
    ASSERT_EQ(static_cast<ScalarType>(2), pt.at(1));
    ASSERT_EQ(static_cast<ScalarType>(3), pt.at(2));
}

/**
 * @brief Test PointBase::at(size_t index) element access out of range
 */
TEST(PointBase, at_4)
{
    TestPointBase<ScalarType> pt{1, 2, 3};
    EXPECT_THROW(pt.at(3), holo::exception::OutOfRangeException);
}

/**
 * @brief Test PointBase::at(size_t index) const element access out of range
 */
TEST(PointBase, at_5)
{
    TestPointBase<ScalarType> const pt{1, 2, 3};
    EXPECT_THROW(pt.at(3), holo::exception::OutOfRangeException);
}

/**
 * @brief Test PointBase::SetX(ScalarType value)
 */
TEST(PointBase, SetX)
{
    TestPointBase<ScalarType> pt{1, 2, 3};
    pt.SetX(static_cast<ScalarType>(10));
    ASSERT_EQ(static_cast<ScalarType>(10), pt[0]);
}

/**
 * @brief Test PointBase::SetY(ScalarType value)
 */
TEST(PointBase, SetY)
{
    TestPointBase<ScalarType> pt{1, 2, 3};
    pt.SetY(static_cast<ScalarType>(10));
    ASSERT_EQ(static_cast<ScalarType>(10), pt[1]);
}

/**
 * @brief Test PointBase::SetZ(ScalarType value)
 */
TEST(PointBase, SetZ)
{
    TestPointBase<ScalarType> pt{1, 2, 3};
    pt.SetZ(static_cast<ScalarType>(10));
    ASSERT_EQ(static_cast<ScalarType>(10), pt[2]);
}

/**
 * @brief Test PointBase::Set(ScalarType x, ScalarType y, ScalarType z)
 */
TEST(PointBase, SetWithXYZValues)
{
    TestPointBase<ScalarType> pt{1, 2, 3};
    pt.Set(static_cast<ScalarType>(10), static_cast<ScalarType>(11), static_cast<ScalarType>(12));
    ASSERT_EQ(static_cast<ScalarType>(10), pt[0]);
    ASSERT_EQ(static_cast<ScalarType>(11), pt[1]);
    ASSERT_EQ(static_cast<ScalarType>(12), pt[2]);
}

/**
 * @brief Test PointBase::Set(InputType const& value) and InputType = holo::geometry::Point3T
 */
TEST(PointBase, SetWithPoint3Type)
{
    TestPointBase<ScalarType>           pt;
    holo::geometry::Point3T<ScalarType> value{10, 20, 30};
    pt.Set(value);
    ASSERT_EQ(static_cast<ScalarType>(10), pt[0]);
    ASSERT_EQ(static_cast<ScalarType>(20), pt[1]);
    ASSERT_EQ(static_cast<ScalarType>(30), pt[2]);
}

/**
 * @brief Test PointBase::Set(InputType const& value) and InputType = holo::Vector3T
 */
TEST(PointBase, SetWithVector3Type)
{
    TestPointBase<ScalarType>  pt;
    holo::numerics::Vector3T<ScalarType> value{10, 20, 30};
    pt.Set(value);
    ASSERT_EQ(static_cast<ScalarType>(10), pt[0]);
    ASSERT_EQ(static_cast<ScalarType>(20), pt[1]);
    ASSERT_EQ(static_cast<ScalarType>(30), pt[2]);
}

/**
 * @brief Test PointBase::Set(InputType const& value) and InputType = class derived from PointBase
 */
TEST(PointBase, SetWithPointBase)
{
    TestPointBase<ScalarType>  pt;
    TestPointBase2<ScalarType> pt2{10, 20, 30};

    pt.Set(pt2);

    ASSERT_EQ(static_cast<ScalarType>(10), pt[0]);
    ASSERT_EQ(static_cast<ScalarType>(20), pt[1]);
    ASSERT_EQ(static_cast<ScalarType>(30), pt[2]);
}

/**
 * @brief Test PointBase::Set(InputType const& value) and InputType = std::vector
 */
TEST(PointBase, SetWithStdVector)
{
    TestPointBase<ScalarType> pt;
    std::vector<ScalarType>   pt2{10, 20, 30};

    pt.Set(pt2);

    ASSERT_EQ(static_cast<ScalarType>(10), pt[0]);
    ASSERT_EQ(static_cast<ScalarType>(20), pt[1]);
    ASSERT_EQ(static_cast<ScalarType>(30), pt[2]);
}

/**
 * @brief Test PointBase::GetX()
 */
TEST(PointBase, GetX)
{
    TestPointBase<ScalarType> pt{1, 2, 3};
    ASSERT_EQ(static_cast<ScalarType>(1), pt.GetX());
}

/**
 * @brief Test PointBase::GetY()
 */
TEST(PointBase, GetY)
{
    TestPointBase<ScalarType> pt{1, 2, 3};
    ASSERT_EQ(static_cast<ScalarType>(2), pt.GetY());
}

/**
 * @brief Test PointBase::GetZ()
 */
TEST(PointBase, GetZ)
{
    TestPointBase<ScalarType> pt{1, 2, 3};
    ASSERT_EQ(static_cast<ScalarType>(3), pt.GetZ());
}

/**
 * @brief Test template <typename OutputType> OutputType PointBase::Get() with OutputType = holo::geometry::Point3T
 */
TEST(PointBase, GetPoint3T)
{
    TestPointBase<ScalarType> pt{1, 2, 3};

    holo::geometry::Point3T<ScalarType> value = pt.Get<holo::geometry::Point3T<ScalarType>>();

    ASSERT_EQ(static_cast<ScalarType>(1), value[0]);
    ASSERT_EQ(static_cast<ScalarType>(2), value[1]);
    ASSERT_EQ(static_cast<ScalarType>(3), value[2]);
}

/**
 * @brief Test template <typename OutputType> OutputType PointBase::Get() with OutputType = holo::Vector3T
 */
TEST(PointBase, GetVector3T)
{
    TestPointBase<ScalarType> pt{1, 2, 3};

    holo::numerics::Vector3T<ScalarType> value = pt.Get<holo::numerics::Vector3T<ScalarType>>();

    ASSERT_EQ(static_cast<ScalarType>(1), value[0]);
    ASSERT_EQ(static_cast<ScalarType>(2), value[1]);
    ASSERT_EQ(static_cast<ScalarType>(3), value[2]);
}

/**
 * @brief Test template <typename OutputType> OutputType PointBase::Get() with OutputType = class derived from PointBase
 */
TEST(PointBase, GetPointBase)
{
    TestPointBase<ScalarType> pt{1, 2, 3};

    TestPointBase2<ScalarType> value = pt.Get<TestPointBase2<ScalarType>>();

    ASSERT_EQ(static_cast<ScalarType>(1), value[0]);
    ASSERT_EQ(static_cast<ScalarType>(2), value[1]);
    ASSERT_EQ(static_cast<ScalarType>(3), value[2]);
}

TEST(PointBase, As)
{
    TestPointBase<ScalarType> pt{1, 2, 3};
    holo::numerics::Vector3d  v = pt.As<holo::numerics::Vector3d>();
    EXPECT_EQ(1.0, v(0));
    EXPECT_EQ(2.0, v(1));
    EXPECT_EQ(3.0, v(2));
    holo::numerics::Vector2d v2 = pt.As<holo::numerics::Vector2d>();
    EXPECT_EQ(1.0, v2(0));
    EXPECT_EQ(2.0, v2(1));
}

/**
 * @brief Test template <typename OutputType> OutputType PointBase::Get() with OutputType = std::vector
 */
TEST(PointBase, GetStdVector)
{
    TestPointBase<ScalarType> pt{1, 2, 3};

    std::vector<ScalarType> value = pt.Get<std::vector<ScalarType>>();

    ASSERT_EQ(static_cast<ScalarType>(1), value[0]);
    ASSERT_EQ(static_cast<ScalarType>(2), value[1]);
    ASSERT_EQ(static_cast<ScalarType>(3), value[2]);
}

/**
 * @brief Test PointBase::GetSerializedSize
 */
TEST(PointBase, GetSerializedSize)
{
    TestPointBase<ScalarType> pt;

    ASSERT_EQ(12U, pt.GetSerializedSize<4U>());
    ASSERT_EQ(16U, pt.GetSerializedSize<8U>());
}

/**
 * @brief Test PointBase::Serialize and Deserialize
 */
TEST(PointBase, SerializeAndDeserialize)
{
    TestPointBase<ScalarType>          pt1{1, 2, 3};
    uint8_t buffer[1024];
    holo::serialization::Serializer<>           serializer(buffer, 1024);
    serializer << pt1;

    ASSERT_EQ(pt1.GetSerializedSize<4U>(), serializer.GetSize());
    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    TestPointBase<ScalarType>   pt2;
    deserializer >> pt2;

    ASSERT_EQ(pt1[0], pt2[0]);
    ASSERT_EQ(pt1[1], pt2[1]);
    ASSERT_EQ(pt1[2], pt2[2]);
}

template <typename T>
using PointXYZIRSt = holo::point_cloud::PointXYZIRSt<T>;

/**
 * @brief Test PointXYZIRSt::PointXYZIRSt()
 */
TEST(PointXYZIRSt, DefaultConstructor)
{
    PointXYZIRSt<ScalarType> pt;
    ASSERT_EQ(static_cast<ScalarType>(0), pt[0]);
    ASSERT_EQ(static_cast<ScalarType>(0), pt[1]);
    ASSERT_EQ(static_cast<ScalarType>(0), pt[2]);
}

/**
 * @brief Test PointXYZIRSt::PointXYZIRSt(InputType pt, ScalarType intensity, uint32_t ring, Timestamp stamp)
 * InputType = Point3
 */
TEST(PointXYZIRSt, ConstructWithPoint3IRSt)
{
    holo::geometry::Point3T<ScalarType> value{1, 2, 3};
    PointXYZIRSt<ScalarType>            pt{value, 10, 20, {100, 200}};

    ASSERT_EQ(static_cast<ScalarType>(1), pt[0]);
    ASSERT_EQ(static_cast<ScalarType>(2), pt[1]);
    ASSERT_EQ(static_cast<ScalarType>(3), pt[2]);
    ASSERT_EQ(static_cast<ScalarType>(10), pt.GetIntensity());
    ASSERT_EQ(20U, pt.GetRing());
    ASSERT_EQ(100U, pt.GetTimestamp().GetSec());
    ASSERT_EQ(200U, pt.GetTimestamp().GetNsec());
}

/**
 * @brief Test PointXYZIRSt::PointXYZIRSt(InputType pt, ScalarType intensity, uint32_t ring, Timestamp stamp)
 * InputType = Vector3
 */
TEST(PointXYZIRSt, ConstructWithVector3IRSt)
{
    holo::numerics::Vector3T<ScalarType> value{1, 2, 3};
    PointXYZIRSt<ScalarType>   pt{value, 10, 20, {100, 200}};

    ASSERT_EQ(static_cast<ScalarType>(1), pt[0]);
    ASSERT_EQ(static_cast<ScalarType>(2), pt[1]);
    ASSERT_EQ(static_cast<ScalarType>(3), pt[2]);
    ASSERT_EQ(static_cast<ScalarType>(10), pt.GetIntensity());
    ASSERT_EQ(20U, pt.GetRing());
    ASSERT_EQ(100U, pt.GetTimestamp().GetSec());
    ASSERT_EQ(200U, pt.GetTimestamp().GetNsec());
}

/**
 * @brief Test PointXYZIRSt::PointXYZIRSt(InputType pt, ScalarType intensity, uint32_t ring, Timestamp stamp)
 * InputType = class derived from PointBase
 */
TEST(PointXYZIRSt, ConstructWithPointBaseIRSt)
{
    TestPointBase2<ScalarType> value{1, 2, 3};
    PointXYZIRSt<ScalarType>   pt{value, 10, 20, {100, 200}};

    ASSERT_EQ(static_cast<ScalarType>(1), pt[0]);
    ASSERT_EQ(static_cast<ScalarType>(2), pt[1]);
    ASSERT_EQ(static_cast<ScalarType>(3), pt[2]);
    ASSERT_EQ(static_cast<ScalarType>(10), pt.GetIntensity());
    ASSERT_EQ(20U, pt.GetRing());
    ASSERT_EQ(100U, pt.GetTimestamp().GetSec());
    ASSERT_EQ(200U, pt.GetTimestamp().GetNsec());
}

/**
 * @brief Test PointXYZIRSt::PointXYZIRSt(InputType pt, ScalarType intensity, uint32_t ring, Timestamp stamp)
 * InputType = std::vector
 */
TEST(PointXYZIRSt, ConstructWithStdVectorIRSt)
{
    TestPointBase2<ScalarType> value{1, 2, 3};
    PointXYZIRSt<ScalarType>   pt{value, 10, 20, {100, 200}};

    ASSERT_EQ(static_cast<ScalarType>(1), pt[0]);
    ASSERT_EQ(static_cast<ScalarType>(2), pt[1]);
    ASSERT_EQ(static_cast<ScalarType>(3), pt[2]);
    ASSERT_EQ(static_cast<ScalarType>(10), pt.GetIntensity());
    ASSERT_EQ(20U, pt.GetRing());
    ASSERT_EQ(100U, pt.GetTimestamp().GetSec());
    ASSERT_EQ(200U, pt.GetTimestamp().GetNsec());
}

/**
 * @brief Test PointXYZIRSt::PointXYZIRSt(std::initializer_list<ScalarType>, ScalarType intensity, uint32_t ring,
 * Timestamp stamp)
 */
TEST(PointXYZIRSt, ConstructWithInitializerListIRSt)
{
    PointXYZIRSt<ScalarType> pt{{1, 2, 3}, 10, 20, {100, 200}};

    ASSERT_EQ(static_cast<ScalarType>(1), pt[0]);
    ASSERT_EQ(static_cast<ScalarType>(2), pt[1]);
    ASSERT_EQ(static_cast<ScalarType>(3), pt[2]);
    ASSERT_EQ(static_cast<ScalarType>(10), pt.GetIntensity());
    ASSERT_EQ(20U, pt.GetRing());
    ASSERT_EQ(100U, pt.GetTimestamp().GetSec());
    ASSERT_EQ(200U, pt.GetTimestamp().GetNsec());
}

/**
 * @brief Test PointXYZIRSt::operator+(PointXYZIRSt const& rhs)
 */
TEST(PointXYZIRSt, OperatorPlus)
{
    PointXYZIRSt<ScalarType> pt1 = {{1, 2, 3}, 4, 5, {6, 7}};
    PointXYZIRSt<ScalarType> pt2 = {{3, 2, 1}, 4, 5, {6, 7}};
    PointXYZIRSt<ScalarType> pt3 = pt1 + pt2;

    ASSERT_EQ(static_cast<ScalarType>(4), pt3[0]);
    ASSERT_EQ(static_cast<ScalarType>(4), pt3[1]);
    ASSERT_EQ(static_cast<ScalarType>(4), pt3[2]);
    ASSERT_EQ(static_cast<ScalarType>(8), pt3.GetIntensity());

    ASSERT_EQ(5U, pt3.GetRing());
    ASSERT_EQ((Timestamp{6, 7}), pt3.GetTimestamp());
}

/**
 * @brief Test PointXYZIRSt::operator+=(PointXYZIRSt const& rhs)
 */
TEST(PointXYZIRSt, OperatorPlusEqual)
{
    PointXYZIRSt<ScalarType> pt1 = {{1, 2, 3}, 4, 5, {6, 7}};
    PointXYZIRSt<ScalarType> pt2 = {{3, 2, 1}, 4, 5, {6, 7}};
    pt1 += pt2;

    ASSERT_EQ(static_cast<ScalarType>(4), pt1[0]);
    ASSERT_EQ(static_cast<ScalarType>(4), pt1[1]);
    ASSERT_EQ(static_cast<ScalarType>(4), pt1[2]);
    ASSERT_EQ(static_cast<ScalarType>(8), pt1.GetIntensity());

    ASSERT_EQ(5U, pt1.GetRing());
    ASSERT_EQ((Timestamp{6, 7}), pt1.GetTimestamp());
}

/**
 * @brief Test PointXYZIRSt::operator-(PointXYZIRSt const& rhs)
 */
TEST(PointXYZIRSt, OperatorSubstract)
{
    PointXYZIRSt<ScalarType> pt1 = {{1, 2, 3}, 4, 5, {6, 7}};
    PointXYZIRSt<ScalarType> pt2 = {{3, 2, 1}, 4, 5, {6, 7}};
    PointXYZIRSt<ScalarType> pt3 = pt1 - pt2;

    ASSERT_EQ(static_cast<ScalarType>(-2), pt3[0]);
    ASSERT_EQ(static_cast<ScalarType>(0), pt3[1]);
    ASSERT_EQ(static_cast<ScalarType>(2), pt3[2]);
    ASSERT_EQ(static_cast<ScalarType>(0), pt3.GetIntensity());

    ASSERT_EQ(5U, pt3.GetRing());
    ASSERT_EQ((Timestamp{6, 7}), pt3.GetTimestamp());
}

/**
 * @brief Test PointXYZIRSt::operator-=(PointXYZIRSt const& rhs)
 */
TEST(PointXYZIRSt, OperatorSubstractEqual)
{
    PointXYZIRSt<ScalarType> pt1 = {{1, 2, 3}, 4, 5, {6, 7}};
    PointXYZIRSt<ScalarType> pt2 = {{3, 2, 1}, 4, 5, {6, 7}};
    pt1 -= pt2;

    ASSERT_EQ(static_cast<ScalarType>(-2), pt1[0]);
    ASSERT_EQ(static_cast<ScalarType>(0), pt1[1]);
    ASSERT_EQ(static_cast<ScalarType>(2), pt1[2]);
    ASSERT_EQ(static_cast<ScalarType>(0), pt1.GetIntensity());

    ASSERT_EQ(5U, pt1.GetRing());
    ASSERT_EQ((Timestamp{6, 7}), pt1.GetTimestamp());
}

/**
 * @brief Test PointXYZIRSt::operator*(ScalarType rhs)
 */
TEST(PointXYZIRSt, OperatorMuliply_1)
{
    PointXYZIRSt<ScalarType> pt1 = {{1, 2, 3}, 4, 5, {6, 7}};
    PointXYZIRSt<ScalarType> pt2 = pt1 * 10;

    ASSERT_EQ(static_cast<ScalarType>(10), pt2[0]);
    ASSERT_EQ(static_cast<ScalarType>(20), pt2[1]);
    ASSERT_EQ(static_cast<ScalarType>(30), pt2[2]);
    ASSERT_EQ(static_cast<ScalarType>(40), pt2.GetIntensity());

    ASSERT_EQ(5U, pt2.GetRing());
    ASSERT_EQ((Timestamp{6, 7}), pt2.GetTimestamp());
}

/**
 * @brief Test PointXYZIRSt::operator*=(ScalarType rhs)
 */
TEST(PointXYZIRSt, OperatorMuliplyEqual)
{
    PointXYZIRSt<ScalarType> pt1 = {{1, 2, 3}, 4, 5, {6, 7}};
    pt1 *= 10;

    ASSERT_EQ(static_cast<ScalarType>(10), pt1[0]);
    ASSERT_EQ(static_cast<ScalarType>(20), pt1[1]);
    ASSERT_EQ(static_cast<ScalarType>(30), pt1[2]);
    ASSERT_EQ(static_cast<ScalarType>(40), pt1.GetIntensity());

    ASSERT_EQ(5U, pt1.GetRing());
    ASSERT_EQ((Timestamp{6, 7}), pt1.GetTimestamp());
}

/**
 * @brief Test friend PointXYZIRSt::operator*(ScalarType lhs, PointXYZIRSt const& rhs)
 */
TEST(PointXYZIRSt, OperatorScalarMuliplyPoint)
{
    PointXYZIRSt<ScalarType> pt1 = {{1, 2, 3}, 4, 5, {6, 7}};
    PointXYZIRSt<ScalarType> pt2 = 10 * pt1;

    ASSERT_EQ(static_cast<ScalarType>(10), pt2[0]);
    ASSERT_EQ(static_cast<ScalarType>(20), pt2[1]);
    ASSERT_EQ(static_cast<ScalarType>(30), pt2[2]);
    ASSERT_EQ(static_cast<ScalarType>(40), pt2.GetIntensity());

    ASSERT_EQ(5U, pt2.GetRing());
    ASSERT_EQ((Timestamp{6, 7}), pt2.GetTimestamp());
}

/**
 * @brief Test PointXYZIRSt::operator/(ScalarType rhs)
 */
TEST(PointXYZIRSt, OperatorDivision)
{
    PointXYZIRSt<ScalarType> pt1 = {{10, 20, 30}, 40, 5, {6, 7}};
    PointXYZIRSt<ScalarType> pt2 = pt1 / 10;

    ASSERT_EQ(static_cast<ScalarType>(1), pt2[0]);
    ASSERT_EQ(static_cast<ScalarType>(2), pt2[1]);
    ASSERT_EQ(static_cast<ScalarType>(3), pt2[2]);
    ASSERT_EQ(static_cast<ScalarType>(4), pt2.GetIntensity());

    ASSERT_EQ(5U, pt2.GetRing());
    ASSERT_EQ((Timestamp{6, 7}), pt2.GetTimestamp());
}

/**
 * @brief Test friend PointXYZIRSt::operator*(ScalarType lhs, PointXYZIRSt const& rhs)
 */
TEST(PointXYZIRSt, OperatorMuliply_2)
{
    PointXYZIRSt<ScalarType> pt1 = {{10, 20, 30}, 40, 5, {6, 7}};
    pt1 /= 10;

    ASSERT_EQ(static_cast<ScalarType>(1), pt1[0]);
    ASSERT_EQ(static_cast<ScalarType>(2), pt1[1]);
    ASSERT_EQ(static_cast<ScalarType>(3), pt1[2]);
    ASSERT_EQ(static_cast<ScalarType>(4), pt1.GetIntensity());

    ASSERT_EQ(5U, pt1.GetRing());
    ASSERT_EQ((Timestamp{6, 7}), pt1.GetTimestamp());
}

/**
 * @brief Test SetIntensity(ScalarType value) and GetIntensity()
 */
TEST(PointXYZIRSt, GetSetIntensity)
{
    PointXYZIRSt<ScalarType> pt1 = {{1, 2, 3}, 4, 5, {6, 7}};

    ASSERT_EQ(static_cast<ScalarType>(4), pt1.GetIntensity());
    pt1.SetIntensity(static_cast<ScalarType>(40));
    ASSERT_EQ(static_cast<ScalarType>(40), pt1.GetIntensity());
}

/**
 * @brief Test SetRing(ScalarType value) and GetRing()
 */
TEST(PointXYZIRSt, GetSetRing)
{
    PointXYZIRSt<ScalarType> pt1 = {{1, 2, 3}, 4, 5, {6, 7}};

    ASSERT_EQ(5U, pt1.GetRing());
    pt1.SetRing(50U);
    ASSERT_EQ(50U, pt1.GetRing());
}

/**
 * @brief Test SetTimestamp(ScalarType value) and GetTimestamp()
 */
TEST(PointXYZIRSt, GetSetTimestamp)
{
    PointXYZIRSt<ScalarType> pt1 = {{1, 2, 3}, 4, 5, {6, 7}};

    ASSERT_EQ((Timestamp{6, 7}), pt1.GetTimestamp());
    pt1.SetTimestamp(Timestamp{60, 70});
    ASSERT_EQ((Timestamp{60, 70}), pt1.GetTimestamp());
}

/**
 * @brief Test PointXYZIRSt::GetSerializedSize
 */
TEST(PointXYZIRSt, GetSerializedSize)
{
    PointXYZIRSt<ScalarType> pt;

    ASSERT_EQ(28U, pt.GetSerializedSize<4U>());
    ASSERT_EQ(32U, pt.GetSerializedSize<8U>());
}

/**
 * @brief Test PointXYZIRSt::Serialize and Deserialize
 */
TEST(PointXYZIRSt, SerializeAndDeserialize)
{
    PointXYZIRSt<ScalarType>           pt1{{1, 2, 3}, 4, 5, {6, 7}};
    uint8_t buffer[1024];
    holo::serialization::Serializer<>          serializer(buffer, 1024);
    serializer << pt1;

    ASSERT_EQ(pt1.GetSerializedSize(), serializer.GetSize());
    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    PointXYZIRSt<ScalarType>    pt2;
    deserializer >> pt2;

    ASSERT_EQ(pt1[0], pt2[0]);
    ASSERT_EQ(pt1[1], pt2[1]);
    ASSERT_EQ(pt1[2], pt2[2]);
    ASSERT_EQ(pt1.GetIntensity(), pt2.GetIntensity());
    ASSERT_EQ(pt1.GetRing(), pt2.GetRing());
    ASSERT_EQ(pt1.GetTimestamp(), pt2.GetTimestamp());
}

template <typename T>
using PointXYZIRRgbSt = holo::point_cloud::PointXYZIRRgbSt<T>;

/**
 * @brief Test PointXYZIRRgbSt::PointXYZIRRgbSt()
 */
TEST(PointXYZIRRgbSt, DefaultConstructor)
{
    PointXYZIRRgbSt<ScalarType> pt;
    ASSERT_EQ(static_cast<ScalarType>(0), pt[0]);
    ASSERT_EQ(static_cast<ScalarType>(0), pt[1]);
    ASSERT_EQ(static_cast<ScalarType>(0), pt[2]);
}

/**
 * @brief Test PointXYZIRRgbSt::PointXYZIRRgbSt(InputType pt, ScalarType intensity, uint32_t ring, Timestamp stamp,
 * std::array(uint8_t ,3) rgb) InputType = Point3
 */
TEST(PointXYZIRRgbSt, ConstructWithPoint3IRRGBSt)
{
    holo::geometry::Point3T<ScalarType> value{1, 2, 3};
    PointXYZIRRgbSt<ScalarType>         pt{value, 10, 20, {10, 20, 30}, {100, 200}};

    ASSERT_EQ(static_cast<ScalarType>(1), pt[0]);
    ASSERT_EQ(static_cast<ScalarType>(2), pt[1]);
    ASSERT_EQ(static_cast<ScalarType>(3), pt[2]);
    ASSERT_EQ(static_cast<ScalarType>(10), pt.GetIntensity());
    ASSERT_EQ(20U, pt.GetRing());
    ASSERT_EQ(10U, pt.GetRgb()[0]);
    ASSERT_EQ(20U, pt.GetRgb()[1]);
    ASSERT_EQ(30U, pt.GetRgb()[2]);
    ASSERT_EQ(100U, pt.GetTimestamp().GetSec());
    ASSERT_EQ(200U, pt.GetTimestamp().GetNsec());
}

/**
 * @brief Test PointXYZIRRgbSt::operator+(PointXYZIRRgbSt const& rhs)
 */
TEST(PointXYZIRRgbSt, OperatorPlus)
{
    PointXYZIRRgbSt<ScalarType> pt1 = {{1, 2, 3}, 4, 5, {10U, 20U, 30U}, {6, 7}};
    PointXYZIRRgbSt<ScalarType> pt2 = {{3, 2, 1}, 4, 5, {10U, 20U, 30U}, {6, 7}};
    PointXYZIRRgbSt<ScalarType> pt3 = pt1 + pt2;

    ASSERT_EQ(static_cast<ScalarType>(4), pt3[0]);
    ASSERT_EQ(static_cast<ScalarType>(4), pt3[1]);
    ASSERT_EQ(static_cast<ScalarType>(4), pt3[2]);
    ASSERT_EQ(static_cast<ScalarType>(8), pt3.GetIntensity());

    ASSERT_EQ(5U, pt3.GetRing());
    ASSERT_EQ(10U, pt3.GetRgb()[0]);
    ASSERT_EQ(20U, pt3.GetRgb()[1]);
    ASSERT_EQ(30U, pt3.GetRgb()[2]);
    ASSERT_EQ((Timestamp{6, 7}), pt3.GetTimestamp());
}

/**
 * @brief Test PointXYZIRRgbSt::operator+=(PointXYZIRRgbSt const& rhs)
 */
TEST(PointXYZIRRgbSt, OperatorPlusEqual)
{
    PointXYZIRRgbSt<ScalarType> pt1 = {{1, 2, 3}, 4, 5, {10U, 20U, 30U}, {6, 7}};
    PointXYZIRRgbSt<ScalarType> pt2 = {{3, 2, 1}, 4, 5, {10U, 20U, 30U}, {6, 7}};
    pt1 += pt2;

    ASSERT_EQ(static_cast<ScalarType>(4), pt1[0]);
    ASSERT_EQ(static_cast<ScalarType>(4), pt1[1]);
    ASSERT_EQ(static_cast<ScalarType>(4), pt1[2]);
    ASSERT_EQ(static_cast<ScalarType>(8), pt1.GetIntensity());

    ASSERT_EQ(5U, pt1.GetRing());
    ASSERT_EQ(10U, pt1.GetRgb()[0]);
    ASSERT_EQ(20U, pt1.GetRgb()[1]);
    ASSERT_EQ(30U, pt1.GetRgb()[2]);
    ASSERT_EQ((Timestamp{6, 7}), pt1.GetTimestamp());
}

/**
 * @brief Test PointXYZIRRgbSt::operator-(PointXYZIRRgbSt const& rhs)
 */
TEST(PointXYZIRRgbSt, OperatorSubstract)
{
    PointXYZIRRgbSt<ScalarType> pt1 = {{1, 2, 3}, 4, 5, {10U, 20U, 30U}, {6, 7}};
    PointXYZIRRgbSt<ScalarType> pt2 = {{3, 2, 1}, 4, 5, {10U, 20U, 30U}, {6, 7}};
    PointXYZIRRgbSt<ScalarType> pt3 = pt1 - pt2;

    ASSERT_EQ(static_cast<ScalarType>(-2), pt3[0]);
    ASSERT_EQ(static_cast<ScalarType>(0), pt3[1]);
    ASSERT_EQ(static_cast<ScalarType>(2), pt3[2]);
    ASSERT_EQ(static_cast<ScalarType>(0), pt3.GetIntensity());
    ASSERT_EQ(5U, pt3.GetRing());
    ASSERT_EQ(10U, pt3.GetRgb()[0]);
    ASSERT_EQ(20U, pt3.GetRgb()[1]);
    ASSERT_EQ(30U, pt3.GetRgb()[2]);
    ASSERT_EQ((Timestamp{6, 7}), pt3.GetTimestamp());
}

/**
 * @brief Test PointXYZIRRgbSt::operator-=(PointXYZIRRgbSt const& rhs)
 */
TEST(PointXYZIRRgbSt, OperatorSubstractEqual)
{
    PointXYZIRRgbSt<ScalarType> pt1 = {{1, 2, 3}, 4, 5, {10U, 20U, 30U}, {6, 7}};
    PointXYZIRRgbSt<ScalarType> pt2 = {{3, 2, 1}, 4, 5, {10U, 20U, 30U}, {6, 7}};
    pt1 -= pt2;

    ASSERT_EQ(static_cast<ScalarType>(-2), pt1[0]);
    ASSERT_EQ(static_cast<ScalarType>(0), pt1[1]);
    ASSERT_EQ(static_cast<ScalarType>(2), pt1[2]);
    ASSERT_EQ(static_cast<ScalarType>(0), pt1.GetIntensity());

    ASSERT_EQ(5U, pt1.GetRing());
    ASSERT_EQ(10U, pt1.GetRgb()[0]);
    ASSERT_EQ(20U, pt1.GetRgb()[1]);
    ASSERT_EQ(30U, pt1.GetRgb()[2]);
    ASSERT_EQ((Timestamp{6, 7}), pt1.GetTimestamp());
}

/**
 * @brief Test PointXYZIRRgbSt::operator*(ScalarType rhs)
 */
TEST(PointXYZIRRgbSt, OperatorMuliply_1)
{
    PointXYZIRRgbSt<ScalarType> pt1 = {{1, 2, 3}, 4, 5, {10U, 20U, 30U}, {6, 7}};
    PointXYZIRRgbSt<ScalarType> pt2 = pt1 * 10;

    ASSERT_EQ(static_cast<ScalarType>(10), pt2[0]);
    ASSERT_EQ(static_cast<ScalarType>(20), pt2[1]);
    ASSERT_EQ(static_cast<ScalarType>(30), pt2[2]);
    ASSERT_EQ(static_cast<ScalarType>(40), pt2.GetIntensity());

    ASSERT_EQ(5U, pt2.GetRing());
    ASSERT_EQ(10U, pt2.GetRgb()[0]);
    ASSERT_EQ(20U, pt2.GetRgb()[1]);
    ASSERT_EQ(30U, pt2.GetRgb()[2]);
    ASSERT_EQ((Timestamp{6, 7}), pt2.GetTimestamp());
}

/**
 * @brief Test PointXYZIRRgbSt::operator*=(ScalarType rhs)
 */
TEST(PointXYZIRRgbSt, OperatorMuliplyEqual)
{
    PointXYZIRRgbSt<ScalarType> pt1 = {{1, 2, 3}, 4, 5, {10U, 20U, 30U}, {6, 7}};
    pt1 *= 10;

    ASSERT_EQ(static_cast<ScalarType>(10), pt1[0]);
    ASSERT_EQ(static_cast<ScalarType>(20), pt1[1]);
    ASSERT_EQ(static_cast<ScalarType>(30), pt1[2]);
    ASSERT_EQ(static_cast<ScalarType>(40), pt1.GetIntensity());

    ASSERT_EQ(5U, pt1.GetRing());
    ASSERT_EQ(10U, pt1.GetRgb()[0]);
    ASSERT_EQ(20U, pt1.GetRgb()[1]);
    ASSERT_EQ(30U, pt1.GetRgb()[2]);
    ASSERT_EQ((Timestamp{6, 7}), pt1.GetTimestamp());
}

/**
 * @brief Test friend PointXYZIRRgbSt::operator*(ScalarType lhs, PointXYZIRRgbSt const& rhs)
 */
TEST(PointXYZIRRgbSt, OperatorScalarMuliplyPoint)
{
    PointXYZIRRgbSt<ScalarType> pt1 = {{1, 2, 3}, 4, 5, {10U, 20U, 30U}, {6, 7}};
    PointXYZIRRgbSt<ScalarType> pt2 = 10 * pt1;

    ASSERT_EQ(static_cast<ScalarType>(10), pt2[0]);
    ASSERT_EQ(static_cast<ScalarType>(20), pt2[1]);
    ASSERT_EQ(static_cast<ScalarType>(30), pt2[2]);
    ASSERT_EQ(static_cast<ScalarType>(40), pt2.GetIntensity());

    ASSERT_EQ(5U, pt2.GetRing());
    ASSERT_EQ(10U, pt2.GetRgb()[0]);
    ASSERT_EQ(20U, pt2.GetRgb()[1]);
    ASSERT_EQ(30U, pt2.GetRgb()[2]);
    ASSERT_EQ((Timestamp{6, 7}), pt2.GetTimestamp());
}

/**
 * @brief Test PointXYZIRRgbSt::operator/(ScalarType rhs)
 */
TEST(PointXYZIRRgbSt, OperatorDivision)
{
    PointXYZIRRgbSt<ScalarType> pt1 = {{10, 20, 30}, 40, 5, {10U, 20U, 30U}, {6, 7}};
    PointXYZIRRgbSt<ScalarType> pt2 = pt1 / 10;

    ASSERT_EQ(static_cast<ScalarType>(1), pt2[0]);
    ASSERT_EQ(static_cast<ScalarType>(2), pt2[1]);
    ASSERT_EQ(static_cast<ScalarType>(3), pt2[2]);
    ASSERT_EQ(static_cast<ScalarType>(4), pt2.GetIntensity());

    ASSERT_EQ(5U, pt2.GetRing());
    ASSERT_EQ(10U, pt2.GetRgb()[0]);
    ASSERT_EQ(20U, pt2.GetRgb()[1]);
    ASSERT_EQ(30U, pt2.GetRgb()[2]);
    ASSERT_EQ((Timestamp{6, 7}), pt2.GetTimestamp());
}

/**
 * @brief Test friend PointXYZIRRgbSt::operator*(ScalarType lhs, PointXYZIRRgbSt const& rhs)
 */
TEST(PointXYZIRRgbSt, OperatorMuliply_2)
{
    PointXYZIRRgbSt<ScalarType> pt1 = {{10, 20, 30}, 40, 5, {10U, 20U, 30U}, {6, 7}};
    pt1 /= 10;

    ASSERT_EQ(static_cast<ScalarType>(1), pt1[0]);
    ASSERT_EQ(static_cast<ScalarType>(2), pt1[1]);
    ASSERT_EQ(static_cast<ScalarType>(3), pt1[2]);
    ASSERT_EQ(static_cast<ScalarType>(4), pt1.GetIntensity());
    ASSERT_EQ(5U, pt1.GetRing());
    ASSERT_EQ(10U, pt1.GetRgb()[0]);
    ASSERT_EQ(20U, pt1.GetRgb()[1]);
    ASSERT_EQ(30U, pt1.GetRgb()[2]);
    ASSERT_EQ((Timestamp{6, 7}), pt1.GetTimestamp());
}

/**
 * @brief Test SetIntensity(ScalarType value) and GetIntensity()
 */
TEST(PointXYZIRRgbSt, GetSetIntensity)
{
    PointXYZIRRgbSt<ScalarType> pt1 = {{1, 2, 3}, 4, 5, {10U, 20U, 30U}, {6, 7}};

    ASSERT_EQ(static_cast<ScalarType>(4), pt1.GetIntensity());
    pt1.SetIntensity(static_cast<ScalarType>(40));
    ASSERT_EQ(static_cast<ScalarType>(40), pt1.GetIntensity());
}

/**
 * @brief Test SetRing(ScalarType value) and GetRing()
 */
TEST(PointXYZIRRgbSt, GetSetRing)
{
    PointXYZIRRgbSt<ScalarType> pt1 = {{1, 2, 3}, 4, 5, {10U, 20U, 30U}, {6, 7}};

    ASSERT_EQ(5U, pt1.GetRing());
    pt1.SetRing(50U);
    ASSERT_EQ(50U, pt1.GetRing());
}

/**
 * @brief Test SetTimestamp(ScalarType value) and GetTimestamp()
 */
TEST(PointXYZIRRgbSt, GetSetTimestamp)
{
    PointXYZIRRgbSt<ScalarType> pt1 = {{1, 2, 3}, 4, 5, {10U, 20U, 30U}, {6, 7}};

    ASSERT_EQ((Timestamp{6, 7}), pt1.GetTimestamp());
    pt1.SetTimestamp(Timestamp{60, 70});
    ASSERT_EQ((Timestamp{60, 70}), pt1.GetTimestamp());
}

/**
 * @brief Test SetRgb(std::array<uint8_t, 3> value) and GetRgb()
 */
TEST(PointXYZIRRgbSt, GetRgb)
{
    PointXYZIRRgbSt<ScalarType> pt1 = {{1, 2, 3}, 4, 5, {10U, 20U, 30U}, {6, 7}};

    ASSERT_EQ(10U, pt1.GetRgb()[0]);
    ASSERT_EQ(20U, pt1.GetRgb()[1]);
    ASSERT_EQ(30U, pt1.GetRgb()[2]);

    pt1.SetRgb({50, 60, 70});
    ASSERT_EQ(50, pt1.GetRgb()[0]);
    ASSERT_EQ(60, pt1.GetRgb()[1]);
    ASSERT_EQ(70, pt1.GetRgb()[2]);
}

/**
 * @brief Test PointXYZIRRgbSt::GetSerializedSize
 */
TEST(PointXYZIRRgbSt, GetSerializedSize)
{
    PointXYZIRRgbSt<ScalarType> pt;

    ASSERT_EQ(32U, pt.GetSerializedSize<4U>());
    ASSERT_EQ(40U, pt.GetSerializedSize<8U>());
}

/**
 * @brief Test PointXYZIRRgbSt::Serialize and Deserialize
 */
TEST(PointXYZIRRgbSt, SerializeAndDeserialize)
{
    PointXYZIRRgbSt<ScalarType>        pt1{{1, 2, 3}, 4, 5, {10U, 20U, 30U}, {6, 7}};
    uint8_t buffer[1024] = {0};
    holo::serialization::Serializer<>          serializer(buffer, 1024);
    serializer << pt1;

    ASSERT_EQ(pt1.GetSerializedSize(), serializer.GetSize());
    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    PointXYZIRRgbSt<ScalarType> pt2;
    deserializer >> pt2;

    ASSERT_EQ(pt1[0], pt2[0]);
    ASSERT_EQ(pt1[1], pt2[1]);
    ASSERT_EQ(pt1[2], pt2[2]);
    ASSERT_EQ(pt1.GetIntensity(), pt2.GetIntensity());
    ASSERT_EQ(pt1.GetRing(), pt2.GetRing());
    ASSERT_EQ(10, pt2.GetRgb()[0]);
    ASSERT_EQ(20, pt2.GetRgb()[1]);
    ASSERT_EQ(30, pt2.GetRgb()[2]);
    ASSERT_EQ(pt1.GetTimestamp(), pt2.GetTimestamp());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
