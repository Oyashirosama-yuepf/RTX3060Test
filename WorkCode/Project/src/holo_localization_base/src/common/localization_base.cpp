/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file localization_base.cpp
 * @brief define localization base
 * @author duyanwei@holomatic.com
 * @date 2019-12-04
 */

#include <unistd.h>

#include <holo/os/tictoc_timer.h>
#include <holo/os/timer.h>

#include <holo/localization/common/localization_base.h>

namespace holo
{
namespace localization
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LocalizationBase::LocalizationBase() noexcept : state_(State::WAIT), status_(Status::PAUSE)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LocalizationBase::~LocalizationBase() noexcept
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocalizationBase::Spin()
{
    status_ = Status::SPIN;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocalizationBase::Pause()
{
    status_ = Status::PAUSE;

    while (checkState())
    {
        (void)usleep(1e3);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocalizationBase::Stop()
{
    status_ = Status::STOP;

    while (checkState())
    {
        (void)usleep(1e3);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t LocalizationBase::checkState() const
{
    return state_ == State::RUN;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocalizationBase::threadFunc(const Scalar frequency)
{
    // timer to control loop rate
    Timer timer((holo::float32_t)frequency);

    // tictoc timer to record estimation speed
    TicTocTimer tic_toc_timer;

    while (GetStatus() != Status::STOP)
    {
        timer.Start();
        tic_toc_timer.Tic();

        if (GetStatus() == Status::PAUSE)
        {
            state_ = State::IDLE;
            (void)usleep(1e3);
            continue;
        }

        /// run main algorithm if state is ready and precondition is met
        if (state_ >= State::READY && checkPreCondition())
        {
            /// advance the state to run
            if (state_ != State::RUN)
            {
                DLOG(INFO) << "advance the localization state to run";
                state_ = State::RUN;
            }

            /// run estimation core
            run();

            /// run post processing
            (void)postProcess();

            DLOG(INFO) << "Localization --- processed one measurement took " << tic_toc_timer.Elapsed() << "seconds";
            timer.Stop();
        }
        else
        {
            // wait to ready
            (void)usleep(1e3);
        }

        /// diagnostics system and publish diagnostic message
        diagnosticSystem();
    }

    state_ = State::IDLE;
    LOG(INFO) << "Localization --- localization finished";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t LocalizationBase::checkPreCondition()
{
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t LocalizationBase::postProcess()
{
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocalizationBase::diagnosticSystem()
{
}

}  // namespace localization
}  // namespace holo
