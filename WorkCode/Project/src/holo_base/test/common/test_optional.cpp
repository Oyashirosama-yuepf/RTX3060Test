/*!
 * @brief unit test for optional class
 * @author duyanwei@holomatic.com
 * @date Sep 30, 2019
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <gtest/gtest.h>
#include <holo/common/optional.h>
#include <holo/geometry/point3.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OptionalT, IsValid)
{
    const holo::OptionalT<holo::geometry::Point3d> obj1;

    const holo::geometry::Point3d point(1.0, 2.0, 3.0);

    const holo::OptionalT<holo::geometry::Point3d> obj2(point);

    ASSERT_FALSE(obj1.IsValid());
    ASSERT_TRUE(obj2.IsValid());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OptionalT, GetData)
{
    const holo::OptionalT<holo::geometry::Point3d> obj1;

    const holo::geometry::Point3d point(1.0, 2.0, 3.0);

    const holo::OptionalT<holo::geometry::Point3d> obj2(point);

    // call data
    holo::bool_t flag = false;
    try
    {
        const holo::geometry::Point3d point = obj1.GetData();
        (void)point;
    }
    catch (const std::runtime_error& e)
    {
        flag = true;
    }

    // check results
    ASSERT_TRUE(flag);
    ASSERT_EQ(point, obj2.GetData());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OptionalT, OperatorBool)
{
    const holo::OptionalT<holo::geometry::Point3d> obj1;

    const holo::geometry::Point3d point(1.0, 2.0, 3.0);

    const holo::OptionalT<holo::geometry::Point3d> obj2(point);

    // check results
    ASSERT_FALSE(obj1);
    ASSERT_TRUE(obj2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OptionalT, Operator1)
{
    const holo::OptionalT<holo::geometry::Point3d> obj1;

    const holo::geometry::Point3d point(1.0, 2.0, 3.0);

    const holo::OptionalT<holo::geometry::Point3d> obj2(point);

    // check results
    ASSERT_TRUE(!obj1);
    ASSERT_FALSE(!obj2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OptionalT, Operator2)
{
    const holo::OptionalT<holo::geometry::Point3d> obj1;

    const holo::geometry::Point3d point(1.0, 2.0, 3.0);

    const holo::OptionalT<holo::geometry::Point3d> obj2(point);

    // call data
    holo::bool_t flag = false;
    try
    {
        const holo::geometry::Point3d point = *obj1;
        (void)point;
    }
    catch (const std::runtime_error& e)
    {
        flag = true;
    }

    // check results
    ASSERT_TRUE(flag);
    ASSERT_EQ(point, *obj2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OptionalT, Operator3)
{
    const holo::OptionalT<holo::geometry::Point3d> obj1;

    const holo::geometry::Point3d point(1.0, 2.0, 3.0);

    const holo::OptionalT<holo::geometry::Point3d> obj2(point);

    // call data
    holo::bool_t flag = false;
    try
    {
        const holo::float64_t x = obj1->GetX();
        const holo::float64_t y = obj1->GetY();
        const holo::float64_t z = obj1->GetZ();
        (void)x;
        (void)y;
        (void)z;
    }
    catch (const std::runtime_error& e)
    {
        flag = true;
    }

    // check results
    ASSERT_TRUE(flag);
    ASSERT_EQ(point.GetX(), obj2->GetX());
    ASSERT_EQ(point.GetY(), obj2->GetY());
    ASSERT_EQ(point.GetZ(), obj2->GetZ());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OptionalT, NoneType)
{
    const holo::OptionalT<holo::geometry::Point3d> obj1(holo::optional::none);
    const holo::OptionalT<holo::geometry::Point3d> obj2 = holo::optional::none;
    ASSERT_FALSE(obj1.IsValid());
    ASSERT_FALSE(obj2.IsValid());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OptionalT, MakeOptional)
{
    const holo::geometry::Point3d point(1.0, 2.0, 3.0);

    const holo::OptionalT<holo::geometry::Point3d> obj = holo::make_optional<holo::geometry::Point3d>(point);

    ASSERT_TRUE(obj.IsValid());
    ASSERT_EQ(point, *obj);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OptionalT, MakeOptional2)
{
    const holo::geometry::Point3d point(1.0, 2.0, 3.0);

    const holo::OptionalT<holo::geometry::Point3d> obj =
        holo::make_optional<holo::geometry::Point3d>(point.GetX(), point.GetY(), point.GetZ());

    ASSERT_TRUE(obj.IsValid());
    ASSERT_EQ(point, *obj);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
