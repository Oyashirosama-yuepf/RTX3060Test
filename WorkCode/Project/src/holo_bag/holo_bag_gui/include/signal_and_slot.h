/**
 * @file signal_and_slots.h
 * @author housixiu (housiixu1@holomatic.com)
 * @brief the header of the SignalAndSlots
 * @version 0.1
 * @date 2020-12-22
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLO_BAG_GUI_SIGNAL_AND_SLOT_H_
#define _HOLO_BAG_GUI_SIGNAL_AND_SLOT_H_

#include <holo/core/types.h>
#include <QFileDialog>
#include <QLabel>
#include <QtCore/QDebug>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

#include "control_play.h"
#include "ui_widget.h"

class SignalAndSlots : public QWidget
{
    Q_OBJECT

using CallbackType = holo_cmw::HoloReplay::CallbackType;

public:
    /**
     * @brief get object instance
     * 
     * @return SignalAndSlots* 
     */
    static SignalAndSlots* Instance()
    {
        static SignalAndSlots instance;
        return &instance;
    }

    /**
     * @brief construct widget_control_ 
     * 
     * @param widget_window current window
     */
    void Init(std::shared_ptr<UI::Widget> widget_window);

    /**
     * @brief according current_time update
     * 
     * @param current_time current time
     */
    void UpdatePlayTime(holo::float64_t current_time);

    /**
     * @brief when play end
     * 
     */
    void PlayEnd();

    /**
     * @brief when move QSlider to update current time
     * 
     * @param time current time
     */
    void MoveForTimeChange(std::string& time);

    /**
     * @brief holo::float64_t -> string 
     * 
     * @param current_time timestamp
     * @return std::string show time, like: 00:00:00
     */
    std::string CurrentTime(holo::float64_t current_time);

public slots:
    /**
     * @brief slot ui to data, when press exit_
     * 
     */
    void OnExitSlots();

    /**
     * @brief slot ui to data, when press pause_
     * 
     */
    void OnPauseSlots();

    /**
     * @brief slot ui to data, when press rate_left_
     * 
     */
    void OnRateLeftSlots();

    /**
     * @brief slot ui to data, when press rate_right_
     * 
     */
    void OnRateRightSlots();

    /**
     * @brief slot ui to data, when press loading_
     * 
     */
    void OnLoadFileSlots();

    /**
     * @brief slot ui to data, when press QSlide
     * 
     */
    void OnTimeChangeSlots();

    /**
     * @brief slot ui to data, when release QSlide_
     * 
     */
    void ReleaseTimeChangeSlots();

    /**
     * @brief slot data to ui, reset time
     * 
     * @param duration change time
     */
    void ChangeEndTimeSlots(holo::float64_t duration);

    /**
     * @brief slot data to ui, change pause_ ui
     * 
     * @param pause pause value
     */
    void ChangePauseSlots(holo::bool_t pause);

private:
    /**
     * @brief ui for data signals and slots connect
     * 
     */
    void initUISlots();

    /**
     * @brief data for ui signal and slots connect
     * 
     */
    void initDataSlots();

    /**
     * @brief holo::float64_t to string time
     * 
     * @param timestamp 
     * @return std::string show time, like: 00:00:00
     */
    std::string convertTimestamp(const holo::float64_t& timestamp); 

    bool                        if_drag_      = true;
    int                         delt_time     = 0;
    std::shared_ptr<UI::Widget> widget_control_;
};

#endif  //_HOLO_BAG_GUI_SIGNAL_AND_SLOT_H_