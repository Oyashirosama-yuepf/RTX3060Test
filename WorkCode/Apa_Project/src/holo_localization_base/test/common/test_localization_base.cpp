/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_localization_base.cpp
 * @brief localization base unit test
 * @author duyanwei@holomatic.com
 * @date 2019-12-04
 */

#include <functional>
#include <thread>

#include <gtest/gtest.h>

#include <holo/localization/common/localization_base.h>

namespace holo
{
namespace localization
{
/**
 * @brief define TestLocalizationBase
 *
 * @details public methods in LocalizationBase are inherited naturally, other methods need to be derived before
 *          testing
 *
 */
class TestLocalizationBase : public LocalizationBase
{
public:
    using Base = LocalizationBase;

    /**
     * @brief constructor
     *
     */
    TestLocalizationBase() noexcept : Base(), frequency_(1000.0f)
    {
    }

    /**
     * @brief destructor
     *
     */
    virtual ~TestLocalizationBase() noexcept
    {
        if (thread_)
        {
            thread_->join();
            thread_ = nullptr;
        }
    }

    /**
     * @brief start main loop
     *
     * @throw std::bad_alloc if initialization fails
     */
    void LaunchRun()
    {
        // start main thread
        thread_ = std::make_shared<std::thread>(
            std::bind(&TestLocalizationBase::threadFunc, this, std::placeholders::_1), frequency_);

        // toggle state to ready
        Base::state_ = State::READY;
    }

    /**
     * @brief change state
     */
    void ChangeState(const Base::State new_state)
    {
        Base::state_ = new_state;
    }

    /**
     * @brief get status
     */
    virtual Status GetStatus() const override
    {
        return Base::GetStatus();
    }

    /**
     * @brief check state
     *
     * @return bool_t
     */
    virtual bool_t checkState() const override
    {
        return Base::checkState();
    }

    /**
     * @brief check pre condition
     */
    virtual bool_t checkPreCondition() override
    {
        return Base::checkPreCondition();
    }

    /**
     * @brief call run function
     *
     */
    virtual void run() override
    {
        // do nothing
    }

    /**
     * @brief post process
     */
    virtual bool_t postProcess()
    {
        return Base::postProcess();
    }

    /**
     * @brief diagnostics system and publish diagnostic message
     */
    virtual void diagnosticSystem()
    {
        Base::diagnosticSystem();
    }

private:
    const Scalar                 frequency_;  ///< frequency
    std::shared_ptr<std::thread> thread_;     ///< thread

};  // class TestLocalizationBase

}  // namespace localization
}  // namespace holo

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(LocalizationBase, ConstructorAndDestructor)
{
    // construct localization base
    holo::localization::TestLocalizationBase* loc = new holo::localization::TestLocalizationBase();

    // check pre condidtion
    ASSERT_TRUE(loc->checkPreCondition());

    // check internal state
    ASSERT_FALSE(loc->checkState());  // WAIT

    // check status
    ASSERT_EQ(holo::localization::LocalizationBase::Status::PAUSE, loc->GetStatus());

    // check post process
    ASSERT_TRUE(loc->postProcess());

    // call destructor
    delete loc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(LocalizationBase, MainLoop)
{
    /**
     * @brief main steps: construct -> start -> spin -> pause -> spin -> stop
     */

    // @step 1: construct localization base
    holo::localization::TestLocalizationBase loc;

    // check state and status
    ASSERT_FALSE(loc.checkState());  // WAIT
    ASSERT_EQ(holo::localization::LocalizationBase::Status::PAUSE, loc.GetStatus());

    // @step 2: launch main loop
    loc.LaunchRun();

    // check state and status
    ASSERT_EQ(holo::localization::LocalizationBase::Status::PAUSE, loc.GetStatus());

    // @step 3: spin main loop
    loc.Spin();
    loc.ChangeState(holo::localization::LocalizationBase::State::WAIT);
    usleep(1e4);  // waitting, run for a while
    loc.ChangeState(holo::localization::LocalizationBase::State::READY);
    usleep(1e4);  // waitting, run for a while

    // check state and status
    ASSERT_EQ(holo::localization::LocalizationBase::Status::SPIN, loc.GetStatus());

    // @step 4: pause main loop
    loc.Pause();
    usleep(1e4);  // waitting, run for a while

    // check state and status
    ASSERT_FALSE(loc.checkState());  // IDLE
    ASSERT_EQ(holo::localization::LocalizationBase::Status::PAUSE, loc.GetStatus());

    // @step 5: spin main loop
    loc.Spin();
    usleep(1e4);  // waitting, run for a while

    // check state and status
    ASSERT_EQ(holo::localization::LocalizationBase::Status::SPIN, loc.GetStatus());

    // @step 6: stop main loop
    loc.Stop();

    // check state and status
    ASSERT_FALSE(loc.checkState());  // IDLE
    ASSERT_EQ(holo::localization::LocalizationBase::Status::STOP, loc.GetStatus());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
