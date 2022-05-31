/**
 * @file widget.cpp
 * @author housixiu (housiixu1@holomatic.com)
 * @brief the implement of the qt widget
 * @version 0.1
 * @date 2020-12-22
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLO_BAG_GUI_DATA_STORAGE_CPP_
#define _HOLO_BAG_GUI_DATA_STORAGE_CPP_

#include <include/widget.h>
#include <include/ui_widget.h>

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new UI::Widget)
{
    ui->SetUpUI(this);
    SignalAndSlots* signal_ = SignalAndSlots::Instance();
    signal_->Init(ui);
}

Widget::~Widget()
{
}
#endif //_HOLO_BAG_GUI_DATA_STORAGE_CPP_