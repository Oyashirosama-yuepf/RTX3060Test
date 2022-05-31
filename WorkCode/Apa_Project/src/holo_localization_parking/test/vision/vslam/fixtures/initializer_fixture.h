/*!
 * \brief generate initializer data for unit test in vslam
 * \author Binbin. Wang, wangbinbin@holomatic.com
 * \date Dec-18-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <gtest/gtest.h>

#define private public
#include <holo/localization/vision/vslam/common_types.h>
#include <holo/localization/vision/vslam/initializer.h>
#include <holo/localization/vision/vslam/tracker.h>

using namespace holo::localization::vision::vslam;

///////////////////////////////////////////////////////////////////////////////
/**
 * @brief test fixture class to generate test data
 */
class InitializerTest : public ::testing::Test
{
public:
    /**
     * @brief Construct a new Initializer Test object
     */
    InitializerTest()
      : camera_parameters_(CameraParameters::Example())
      , camera_index_(0)
      , initializer_(Initializer::Parameters::Example(), camera_parameters_)
    {
    }

    /**
     * @brief Destroy the Initializer Test object
     */
    virtual ~InitializerTest()
    {
    }

    virtual void SetUp() override
    {
    }

    virtual void TearDown() override
    {
    }

protected:
    CameraParameters::Ptr camera_parameters_;
    uint16_t              camera_index_;
    Initializer           initializer_;
};  // InitializerTest
