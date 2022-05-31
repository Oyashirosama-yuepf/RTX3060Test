/**
 * @file ui_widget.h
 * @author housixiu (housiixu1@holomatic.com)
 * @brief the header of the UIWidget
 * @version 0.1
 * @date 2020-12-22
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLO_BAG_GUI_UI_WIDGET_H_
#define _HOLO_BAG_GUI_UI_WIDGET_H_

#include <holo/core/types.h>
#include <holo/utils/holo_root.h>
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
#include <QDirModel>
#include <QtCore/QDebug>
#include <iostream>

#include "control_play.h"
#include "custom_slider.h"

QT_BEGIN_NAMESPACE
#define RATE_CHANGE 0.5

class UIWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief when press pause_
     * 
     * @param play_pause pause value
     */
    void OnPause(bool play_pause);

    /**
     * @brief when press rate_left
     * 
     * @param current_rate current rate value
     * @return holo::float32_t new rate value
     */
    holo::float32_t OnRateLeft(holo::float32_t current_rate);

    /**
     * @brief when press rate_right
     * 
     * @param current_rate current rate value
     * @return holo::float32_t new rate value
     */
    holo::float32_t OnRateRight(holo::float32_t current_rate);

    /**
     * @brief when press exit
     * 
     */
    void OnExit();

    /**
     * @brief load holobag file
     * 
     * @return std::string holobag path
     */
    std::string OnLoadFile();

    /**
     * @brief construct ui
     * 
     * @param widget_window ui window
     */
    void SetUpUI(QWidget* widget_window);

    /**
     * @brief set define value
     * 
     * @param Widget ui window
     */
    void RetranslateUI(QWidget* widget_window);

    CustomSlider* play_time_;
    QLabel*       start_time_;
    QLabel*       end_time_;
    QLabel*       current_time_;
    QPushButton*  pause_;
    QPushButton*  rate_left_;
    QPushButton*  rate_right_;
    QPushButton*  loading_;
    QPushButton*  exit_;

private:
    QWidget* widget_self_;
    QString  holo_root_config_;
};

namespace UI
{
class Widget : public UIWidget
{
public:
};
}  // namespace UI

QT_END_NAMESPACE

#endif  // _HOLO_BAG_GUI_UI_WIDGET_H_
