/**
 * @file control_play.cpp
 * @author housixiu (housiixu1@holomatic.com)
 * @brief the implement of the ControlPlay
 * @version 0.1
 * @date 2020-12-22
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLO_BAG_GUI_CONTROL_PLAY_CPP_
#define _HOLO_BAG_GUI_CONTROL_PLAY_CPP_

#include <include/control_play.h>
#include <include/signal_and_slot.h>

holo::bool_t ControlPlay::GetPause()
{
    Init();
    play_data_.pause_ = replay_->GetPause();
    return play_data_.pause_;
}

holo::float32_t ControlPlay::GetRate()
{
    Init();
    play_data_.rate_= replay_->GetRate();
    return play_data_.rate_;
}

holo::float64_t ControlPlay::GetSkipTime()
{
    return play_data_.skip_time_;
}

void ControlPlay::SetPause()
{
    Init();
    play_data_.pause_ = !(play_data_.pause_);
    replay_->SetPause(play_data_.pause_);
}

void ControlPlay::SetRate(holo::float32_t current_rate)
{
    Init();
    play_data_.rate_ = current_rate;
    replay_->SetRate(play_data_.rate_);
}


void ControlPlay::LoadFile()
{
    if (play_data_.file_path_.size() < 3)
    {
        return;
    }
    
    Init();
    QueuePop();
    SetStopFlag();
    
    replay_->SetUp(play_data_.config_path_, play_data_.file_path_);
    play_data_.bag_duration_ = replay_->GetBagDuration();
    play_data_.bag_start_time_ = replay_->GetBagStartTime();
    emit ChangeDuration(play_data_.bag_duration_);

    play_data_.pause_ = true;
    replay_->SetPause(play_data_.pause_);
    emit ChangePause(!play_data_.pause_);

    play_data_.skip_time_ = 0;
    replay_->SetSkipTime(0);
    replay_->SetUserOptions(0, 0, 0);
    
    SetStartFlag();
    future_play_ = std::async(std::launch::async, [this]() { play(); });
}

void ControlPlay::RateLeft()
{
    Init();
    QueuePop();
    replay_->SetRate(play_data_.rate_);
}

void ControlPlay::RateRight()
{
    Init();
    QueuePop();
    replay_->SetRate(play_data_.rate_);
}

void ControlPlay::TimeChange()
{
    if (play_data_.file_path_.size() < 3)
    {
        return;
    }

    Init();
    SetStopFlag();
    QueuePop();

    replay_->SetPause(1);
    emit ChangePause(!play_data_.pause_);

    replay_->SetUp(play_data_.config_path_, play_data_.file_path_);
    replay_->SetUserOptions(play_data_.skip_time_, 0, 0);

    SetStartFlag();
    future_play_ = std::async(std::launch::async, [this]() { play(); });
    
}

void ControlPlay::SetStopFlag()
{
    if (replay_ == nullptr)
    {
        return;
    }
    replay_->SetStopFlag();
}

void ControlPlay::Init()
{
    if (replay_ == nullptr)
    {
        replay_ = std::shared_ptr<holo_cmw::HoloReplay>(
            new holo_cmw::HoloReplay(play_data_.argc, play_data_.argv, play_data_.node_name_));
    }
}

void ControlPlay::play()
{
    future_play_.wait_for(std::chrono::seconds(0));
    replay_->Play();
}

void ControlPlay::SetCallBack(CallbackType& current_time_callback, CallbackType& end_time_callback)
{
    Init();
    replay_->SetTimeCallback(current_time_callback);
    replay_->SetEndCallback(end_time_callback);
}

void ControlPlay::QueuePop()
{
    Init();
    replay_->QueuePop();
}

void ControlPlay::SetStartFlag()
{
    Init();
    replay_->SetStartFlag();
}

#endif