/**
 * @file custom_slider.cpp
 * @author housixiu (housiixu1@holomatic.com)
 * @brief the implement of the CustomSlider
 * @version 0.1
 * @date 2020-12-22
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLO_BAG_GUI_CUSTOM_SLIDER_CPP_
#define _HOLO_BAG_GUI_CUSTOM_SLIDER_CPP_

#include <QPalette>

#include <include/custom_slider.h>
#include <include/signal_and_slot.h>

CustomSlider::CustomSlider(QWidget* parent) : QSlider(parent)
{
}

CustomSlider::~CustomSlider()
{
}

void CustomSlider::mousePressEvent(QMouseEvent* event)
{
    QSlider::mousePressEvent(event);
}

void CustomSlider::mouseReleaseEvent(QMouseEvent* event)
{
    QSlider::mouseReleaseEvent(event);
}

void CustomSlider::mouseMoveEvent(QMouseEvent* event)
{
    SignalAndSlots* signal = SignalAndSlots::Instance();
    std::string time = signal->CurrentTime(this->value());
    signal->MoveForTimeChange(time);
    QSlider::mouseMoveEvent(event);
}

#endif  //_HOLO_BAG_GUI_CUSTOM_SLIDER_CPP_