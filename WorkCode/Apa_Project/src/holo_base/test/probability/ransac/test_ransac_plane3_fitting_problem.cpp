/*!
 * @file unit test for fitting plane3 by ransac
 * @brief unit test for fitting plane3 by ransac
 * @author jiaxing.zhao
 * @date 2017-08-9
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notic.
 */

#include <gtest/gtest.h>
#include <holo/probability/ransac/ransac.h>
#include <holo/probability/ransac/ransac_plane3_fitting_problem.h>

using namespace holo;
using ScalarType      = float32_t;
using Point3Type  = holo::geometry::Point3T<ScalarType>;
using AdapterType = RansacProblemDataContainerAdapterStdVectorT<Point3Type>;
using ProblemType = RansacPlane3FittingProblemT<ScalarType>;
using RansacType  = Ransac<ProblemType>;
using RansacProblemType = RansacProblemT<Point3Type>;

/*****************************************************************************/
TEST(RansacPlane3, Simple)
{
    std::vector<Point3Type> pl;

    // inliers
    pl.push_back(Point3Type(1, 1, 0));
    pl.push_back(Point3Type(1, -1, 0));
    pl.push_back(Point3Type(-1, 1, 0));
    pl.push_back(Point3Type(-1, -1, 0));
    pl.push_back(Point3Type(2, 2, 0));
    pl.push_back(Point3Type(2, -2, 0));
    pl.push_back(Point3Type(-2, 2, 0));
    pl.push_back(Point3Type(-2, -2, 0));
    pl.push_back(Point3Type(3, 3, 0));
    pl.push_back(Point3Type(3, -3, 0));
    pl.push_back(Point3Type(-3, 3, 0));
    pl.push_back(Point3Type(-3, -3, 0));

    // outliers
    pl.push_back(Point3Type(10, 10, 10));
    pl.push_back(Point3Type(-10, -10, -10));
    pl.push_back(Point3Type(10, -10, 10));

    // setup ransac adapter
    AdapterType adapter(pl);

    // ground truth plane
    holo::geometry::Plane3f gt(Point3Type(1, 1, 0), Point3Type(1, -1, 0), Point3Type(-1, 1, 0));

    // setup ransac problem
    std::shared_ptr<ProblemType> problem(new ProblemType(adapter));

    // run ransac
    RansacType::Parameters params(0.1);
    RansacType       ransac(problem, params);

    const bool_t status = ransac.Compute();

    ASSERT_TRUE(status);
    ASSERT_TRUE(ransac.GetBestModel().IsEqual(gt));
    ASSERT_EQ(ransac.GetInliers().size(), 12u);
    ASSERT_TRUE(ransac.GetOptimizedModel().IsEqual(gt));
}

/*****************************************************************************/
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
