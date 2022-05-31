/**
 * @file signal_and_slots.cpp
 * @author housixiu (housiixu1@holomatic.com)
 * @brief the implement of the SignalAndSlots
 * @version 0.1
 * @date 2020-12-22
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLO_BAG_GUI_SIGNAL_AND_SLOT_CPP_
#define _HOLO_BAG_GUI_SIGNAL_AND_SLOT_CPP_

#include <include/signal_and_slot.h>

void UpdataTime(const holo::float64_t current_time)
{
    SignalAndSlots* play_time_ = SignalAndSlots::Instance();
    play_time_->UpdatePlayTime(current_time);
}

void EndPlay(const holo::float64_t end_time)
{
    ControlPlay* play_end_replay = ControlPlay::Instance();
    play_end_replay->QueuePop();
    play_end_replay->SetPause();

    SignalAndSlots* play_end = SignalAndSlots::Instance();
    play_end->PlayEnd();
    std::cout << "end time : " << end_time << std::endl;
}

void SignalAndSlots::Init(std::shared_ptr<UI::Widget> widget_window)
{
    widget_control_ = widget_window;
    ControlPlay* play_control_ = ControlPlay::Instance();
    play_control_->Init();
    CallbackType current_time_callback = std::bind(&UpdataTime, std::placeholders::_1);
    CallbackType end_time_callback     = std::bind(&EndPlay, std::placeholders::_1);
    play_control_->SetCallBack(current_time_callback, end_time_callback);

    initUISlots();
    initDataSlots();
}

void SignalAndSlots::initUISlots()
{
    QObject::connect(widget_control_->exit_, SIGNAL(clicked()), this, SLOT(OnExitSlots()));
    QObject::connect(widget_control_->loading_, SIGNAL(clicked()), this, SLOT(OnLoadFileSlots()));
    QObject::connect(widget_control_->pause_, SIGNAL(clicked()), this, SLOT(OnPauseSlots()));
    QObject::connect(widget_control_->rate_left_, SIGNAL(clicked()), this, SLOT(OnRateLeftSlots()));
    QObject::connect(widget_control_->rate_right_, SIGNAL(clicked()), this, SLOT(OnRateRightSlots()));
    QObject::connect(widget_control_->play_time_, SIGNAL(sliderPressed()), this, SLOT(OnTimeChangeSlots()));
    QObject::connect(widget_control_->play_time_, SIGNAL(sliderReleased()), this, SLOT(ReleaseTimeChangeSlots()));
}

void SignalAndSlots::initDataSlots()
{
    ControlPlay* play_control_ = ControlPlay::Instance();
    QObject::connect(play_control_, SIGNAL(ChangeDuration(holo::float64_t)), this, SLOT(ChangeEndTimeSlots(holo::float64_t)));
    QObject::connect(play_control_, SIGNAL(ChangePause(holo::bool_t)), this, SLOT(ChangePauseSlots(holo::bool_t)));
}

void SignalAndSlots::OnExitSlots()
{
    std::cout<<"exit slots\n";
    ControlPlay* play_control_ = ControlPlay::Instance();
    if (play_control_ != nullptr)
    {
        play_control_->SetStopFlag();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    widget_control_->OnExit();
}

void SignalAndSlots::OnPauseSlots()
{
    ControlPlay* play_control_ = ControlPlay::Instance();
    holo::bool_t current_pause = play_control_->GetPause();
    play_control_->SetPause();
    widget_control_->OnPause(current_pause);
}

void SignalAndSlots::OnRateLeftSlots()
{
    ControlPlay* play_control_ = ControlPlay::Instance();
    holo::float32_t current_rate = play_control_->GetRate();
    holo::float32_t change_rate  = widget_control_->OnRateLeft(current_rate);
    play_control_->SetRate(change_rate);
}

void SignalAndSlots::OnRateRightSlots()
{
    ControlPlay* play_control_ = ControlPlay::Instance();
    holo::float32_t current_rate = play_control_->GetRate();
    holo::float32_t change_rate  = widget_control_->OnRateRight(current_rate);
    play_control_->SetRate(change_rate);
}

void SignalAndSlots::OnLoadFileSlots()
{
    ControlPlay* play_control_ = ControlPlay::Instance();
    play_control_->SetStopFlag();

    std::string file_name;
    file_name = widget_control_->OnLoadFile();
    if (file_name.size() < 3)
    {
        return;
    }
    play_control_->play_data_.file_path_ = file_name;
    play_control_->LoadFile();
}

void SignalAndSlots::OnTimeChangeSlots()
{
    if_drag_ = false;
}

void SignalAndSlots::MoveForTimeChange(std::string& time)
{
    widget_control_->current_time_->setText(QApplication::translate("Widget", time.c_str(), Q_NULLPTR));
}

void SignalAndSlots::ReleaseTimeChangeSlots()
{
    ControlPlay* play_control_ = ControlPlay::Instance();
    play_control_->play_data_.skip_time_ = widget_control_->play_time_->value();
    play_control_->SetStopFlag();
    if_drag_ = true;
    play_control_->TimeChange();
}

void SignalAndSlots::ChangeEndTimeSlots(holo::float64_t duration)
{
    ControlPlay* play_control_ = ControlPlay::Instance();
    holo::float64_t start_timestamp = play_control_->play_data_.bag_start_time_;
    std::string     start_time      = convertTimestamp(start_timestamp);
    std::string     end_time        = convertTimestamp(start_timestamp + duration);
    widget_control_->start_time_->setText(QApplication::translate("Widget", start_time.c_str(), Q_NULLPTR));
    widget_control_->end_time_->setText(QApplication::translate("Widget", end_time.c_str(), Q_NULLPTR));
    widget_control_->play_time_->setMaximum(duration);
}

void SignalAndSlots::ChangePauseSlots(holo::bool_t pause)
{
    widget_control_->OnPause(pause);
}

void SignalAndSlots::UpdatePlayTime(holo::float64_t current_time)
{
    if (if_drag_)
    {
        std::string time = CurrentTime(current_time);
        widget_control_->current_time_->setText(QApplication::translate("Widget", time.c_str(), Q_NULLPTR));
        widget_control_->play_time_->setValue(current_time);
        delt_time = current_time;
    }
}

void SignalAndSlots::PlayEnd()
{
    widget_control_->play_time_->setValue(0);
    widget_control_->current_time_->setText(QApplication::translate("Widget", "00:00:00", Q_NULLPTR));
    widget_control_->OnPause(false);
}

std::string SignalAndSlots::convertTimestamp(const holo::float64_t& timestamp)
{
    std::time_t time(timestamp);
    std::tm*    tm;
    char        tmpbuf[12];
    tm = localtime(&time);
    strftime(tmpbuf, 12, "%R:%S", tm);
    return tmpbuf;
}

std::string SignalAndSlots::CurrentTime(holo::float64_t current_time)
{
    ControlPlay* play_control_ = ControlPlay::Instance();
    holo::float64_t start_timestamp = play_control_->play_data_.bag_start_time_;
    return convertTimestamp(start_timestamp + current_time);
}

#endif  //_HOLO_BAG_GUI_SIGNAL_AND_SLOT_CPP_