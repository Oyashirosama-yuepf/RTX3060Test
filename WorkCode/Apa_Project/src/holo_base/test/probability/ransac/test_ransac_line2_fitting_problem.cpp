/*!
 * @file test_ransac_line2_fitting_problem
 * @brief unit test for fitting line2 by ransac
 * @author jiaxing.zhao
 * @date 2017-08-2
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notic.
 */

#include <gtest/gtest.h>

#include <holo/probability/ransac/ransac.h>
#include <holo/probability/ransac/ransac_line2_fitting_problem.h>

using namespace holo;
using Scalar      = float64_t;
using Point2Type  = holo::geometry::Point2T<Scalar>;
using AdapterType = RansacProblemDataContainerAdapterStdVectorT<Point2Type>;
using ProblemType = RansacLine2FittingProblemT<Scalar>;
using RansacType  = Ransac<ProblemType>;
using RansacProblemType = RansacProblemT<Point2Type>;

/*****************************************************************************/
TEST(RansacLine2, Simple)
{

    std::vector<Point2Type> ps;
    ps.reserve(13u);

    // inliers
    ps.push_back(Point2Type(-5, -5));
    ps.push_back(Point2Type(-4, -4));
    ps.push_back(Point2Type(-3, -3));
    ps.push_back(Point2Type(-2, -2));
    ps.push_back(Point2Type(-1, -1));
    ps.push_back(Point2Type(0, 0));
    ps.push_back(Point2Type(5, 5));
    ps.push_back(Point2Type(4, 4));
    ps.push_back(Point2Type(3, 3));
    ps.push_back(Point2Type(2, 2));
    ps.push_back(Point2Type(1, 1));

    // outlier
    ps.push_back(Point2Type(100, 0));
    ps.push_back(Point2Type(0, 100));

    // setup ransac adapter
    const AdapterType adapter(ps);

    // ground truth line
    const holo::geometry::Line2d gt(holo::geometry::Point2(1, 1), holo::geometry::Point2(-1, -1));

    // setup ransac problem
    const std::shared_ptr<ProblemType> problem(new ProblemType(adapter));

    // run ransac
    const RansacType::Parameters params(0.1);
    RansacType                   ransac(problem, params);

    const bool_t status = ransac.Compute();

    ASSERT_TRUE(status);
    ASSERT_TRUE(ransac.GetBestModel().IsEqual(gt));
    ASSERT_EQ(ransac.GetInliers().size(), 11u);
    ASSERT_TRUE(ransac.GetOptimizedModel().IsEqual(gt));
}

TEST(RansacLine2, MoveConstructor)
{

    std::vector<Point2Type> ps;
    ps.reserve(13u);

    // inliers
    ps.push_back(Point2Type(-5, -5));
    ps.push_back(Point2Type(-4, -4));
    ps.push_back(Point2Type(-3, -3));
    ps.push_back(Point2Type(-2, -2));
    ps.push_back(Point2Type(-1, -1));
    ps.push_back(Point2Type(0, 0));
    ps.push_back(Point2Type(5, 5));
    ps.push_back(Point2Type(4, 4));
    ps.push_back(Point2Type(3, 3));
    ps.push_back(Point2Type(2, 2));
    ps.push_back(Point2Type(1, 1));

    // outlier
    ps.push_back(Point2Type(100, 0));
    ps.push_back(Point2Type(0, 100));

    // setup ransac adapter
    const AdapterType adapter(std::move(ps));
}

TEST(RansacLine2FittingProblem, ComputeModel)
{
    std::vector<Point2Type> ps;
    ps.reserve(13u);

    // inliers
    ps.push_back(Point2Type(-5, -5));
    ps.push_back(Point2Type(-4, -4));
    ps.push_back(Point2Type(-3, -3));
    ps.push_back(Point2Type(-2, -2));
    ps.push_back(Point2Type(-1, -1));
    ps.push_back(Point2Type(0, 0));
    ps.push_back(Point2Type(5, 5));
    ps.push_back(Point2Type(4, 4));
    ps.push_back(Point2Type(3, 3));
    ps.push_back(Point2Type(2, 2));
    ps.push_back(Point2Type(1, 1));

    // outlier
    ps.push_back(Point2Type(100, 0));
    ps.push_back(Point2Type(0, 100));

    // setup ransac adapter
    const AdapterType adapter(ps);
    ProblemType problem(adapter);
    std::vector<uint64_t> indices;
    ProblemType::ModelType out;
    problem.ComputeModel(indices, out);
}

TEST(RansacLine2FittingProblem, ComputeModelException)
{
    std::vector<Point2Type> ps;
    const AdapterType adapter(ps);
    ProblemType problem(adapter);
    std::vector<uint64_t> indices;
    indices.push_back(0x01);
    indices.push_back(0x01);
    indices.push_back(0x01);

    ProblemType::ModelType out;
    problem.ComputeModel(indices, out);
}

TEST(RansacLine2FittingProblem, OptimizeModel)
{
    std::vector<Point2Type> ps;
    ps.reserve(13u);

    // inliers
    ps.push_back(Point2Type(-5, -5));
    ps.push_back(Point2Type(-4, -4));
    ps.push_back(Point2Type(-3, -3));
    ps.push_back(Point2Type(-2, -2));
    ps.push_back(Point2Type(-1, -1));
    ps.push_back(Point2Type(0, 0));
    ps.push_back(Point2Type(5, 5));
    ps.push_back(Point2Type(4, 4));
    ps.push_back(Point2Type(3, 3));
    ps.push_back(Point2Type(2, 2));
    ps.push_back(Point2Type(1, 1));

    // outlier
    ps.push_back(Point2Type(100, 0));
    ps.push_back(Point2Type(0, 100));

    // setup ransac adapter
    const AdapterType adapter(ps);
    ProblemType problem(adapter);
    std::vector<uint64_t> indices;
    ProblemType::ModelType out;
    problem.OptimizeModel(indices, out);
}

TEST(RansacProblem, Constructor)
{
    std::vector<Point2Type> ps;
    const AdapterType adapter(ps);
    ProblemType problem(adapter, false);
}

TEST(RansacProblem, SetIndices)
{
    std::vector<Point2Type> ps;
    const AdapterType adapter(ps);
    ProblemType problem(adapter);
    std::vector<uint64_t> indices;
    indices.push_back(0x01);
    indices.push_back(0x01);
    indices.push_back(0x01);

    ProblemType::ModelType out;
    problem.SetIndices(indices);
}

TEST(RansacProblem, DrawSamples)
{
    std::vector<Point2Type> ps;
    const AdapterType adapter(ps);
    ProblemType problem(adapter);
    std::vector<uint64_t> samples;
    samples.push_back(0x01);
    samples.push_back(0x01);
    samples.push_back(0x00);

    uint64_t iterations = 0;
    std::vector<uint64_t> indices;

    problem.SetIndices(indices);
    problem.DrawSamples(iterations ,samples);
}



/*****************************************************************************/
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
