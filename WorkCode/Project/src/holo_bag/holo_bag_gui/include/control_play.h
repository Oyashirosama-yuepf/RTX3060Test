/**
 * @file control_play.h
 * @author housixiu (housiixu1@holomatic.com)
 * @brief the header of the ControlPlay
 * @version 0.1
 * @date 2020-12-22
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLO_BAG_GUI_CONTROL_PLAY_H_
#define _HOLO_BAG_GUI_CONTROL_PLAY_H_

#include <QWidget>
#include <iostream>
#include <mutex>
#include <thread>

#include "data_storage.h"
#include "holo_replay.h"

class ControlPlay : public QWidget
{
    Q_OBJECT

using CallbackType = holo_cmw::HoloReplay::CallbackType;

signals:
    /**
     * @brief signals for change ui time
     * 
     * @param duration time change duration
     */
    void ChangeDuration(holo::float64_t duration);

    /**
     * @brief signals for change ui pause
     * 
     * @param pause time change duration
     */
    void ChangePause(holo::bool_t pause);

public slots:
    /**
     * @brief Set the Stop Flag , stop play
     * 
     */
    void SetStopFlag();

public:
    /**
     * @brief get object instance
     * 
     * @return ControlPlay* 
     */
    static ControlPlay* Instance()
    {
        static ControlPlay instance;
        return &instance;
    }

    /**
     * @brief construct HoloReplay
     * 
     */
    void Init();

    /**
     * @brief Get the pause value
     * 
     * @return holo::bool_t 
     */
    holo::bool_t GetPause();

    /**
     * @brief Get the rate value
     * 
     * @return holo::float32_t 
     */
    holo::float32_t GetRate();

    /**
     * @brief Get the skip_time value
     * 
     * @return holo::float64_t 
     */
    holo::float64_t GetSkipTime();

    /**
     * @brief Set the pause 
     * 
     */
    void SetPause();

    /**
     * @brief Set the rate value
     * 
     * @param current_rate current rate
     */
    void SetRate(holo::float32_t current_rate);

    /**
     * @brief load holobag file
     * 
     */
    void LoadFile();

    /**
     * @brief rate decrease
     * 
     */
    void RateLeft();

    /**
     * @brief rate increase
     * 
     */
    void RateRight();

    /**
     * @brief change play time
     * 
     */
    void TimeChange();

    /**
     * @brief Set the set_start_flag, open play
     * 
     */
    void SetStartFlag();

    /**
     * @brief Set the Call Back 
     * 
     * @param current_time_callback use to update time
     * @param end_time_callback use to end play
     */
    void SetCallBack(CallbackType& current_time_callback, CallbackType& end_time_callback);
    
    /**
     * @brief release resources in the queue
     * 
     */
    void QueuePop();

    DataStorage play_data_;

private:
    /**
     * @brief holobag play
     * 
     */
    void play();

private:
    std::shared_ptr<holo_cmw::HoloReplay> replay_;
    std::future<void>                     future_play_;
};

#endif  //_HOLO_BAG_GUI_CONTROL_PLAY_H_