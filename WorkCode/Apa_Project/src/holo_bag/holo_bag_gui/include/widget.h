/**
 * @file widget.h
 * @author housixiu (housiixu1@holomatic.com)
 * @brief the header of the Widget
 * @version 0.1
 * @date 2020-12-22
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLO_BAG_GUI_WIDGET_H_
#define _HOLO_BAG_GUI_WIDGET_H_

#include <QWidget>
#include <iostream>

#include "signal_and_slot.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget* parent = 0);
    ~Widget();

private:
    std::shared_ptr<UI::Widget> ui;
};

#endif  // _HOLO_BAG_GUI_WIDGET_H_
