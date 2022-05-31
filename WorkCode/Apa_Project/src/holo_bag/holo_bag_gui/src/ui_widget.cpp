/**
 * @file ui_widget.cpp
 * @author housixiu (housiixu1@holomatic.com)
 * @brief the implement of the UIWidget
 * @version 0.1
 * @date 2020-12-22
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLO_BAG_UI_WIDGET_CPP
#define _HOLO_BAG_UI_WIDGET_CPP

#include <include/ui_widget.h>

void UIWidget::SetUpUI(QWidget* widget_window)
{
    holo_root_config_ =  QString::fromStdString(holo::GetHoloConfigRootDirectory());

    widget_self_ = widget_window;
    widget_window->setObjectName(QStringLiteral("HoloBagGUI"));
    widget_window->resize(370, 140);
    widget_window->setMinimumSize(QSize(370, 140));
    widget_window->setMaximumSize(QSize(370, 140));

    play_time_ = new CustomSlider(widget_window);
    play_time_->setObjectName(QStringLiteral("play_time"));
    play_time_->setGeometry(QRect(20, 20, 330, 20));
    play_time_->setOrientation(Qt::Horizontal);
    play_time_->setMinimum(0);
    play_time_->setMaximum(1000);
    play_time_->setSingleStep(0);

    start_time_ = new QLabel(widget_window);
    start_time_->setObjectName(QStringLiteral("start_time"));
    start_time_->setGeometry(QRect(10, 40, 65, 20));

    end_time_ = new QLabel(widget_window);
    end_time_->setObjectName(QStringLiteral("end_time"));
    end_time_->setGeometry(QRect(300, 40, 65, 20));

    current_time_ = new QLabel(widget_window);
    current_time_->setObjectName(QStringLiteral("start_time"));
    current_time_->setGeometry(QRect(155, 40, 65, 20));

    pause_ = new QPushButton(widget_window);
    pause_->setObjectName(QStringLiteral("pause"));
    pause_->setGeometry(QRect(160, 70, 50, 50));
    pause_->setIconSize(QSize(40, 40));
    QIcon icon;
    icon.addFile(holo_root_config_ + QObject::tr("/holo_bag/Resource/Icon/background_pause_start.png"));
    pause_->setIcon(icon);

    rate_left_ = new QPushButton(widget_window);
    rate_left_->setObjectName(QStringLiteral("rate_left"));
    rate_left_->setGeometry(QRect(90, 70, 50, 50));
    rate_left_->setIconSize(QSize(40, 40));
    rate_left_->setStyleSheet(
        "QPushButton{border-image: url(" + holo_root_config_ +
        "/holo_bag/Resource/Icon/background_rate_left.png);border:none;color:rgb(255, 255, 255);}");

    rate_right_ = new QPushButton(widget_window);
    rate_right_->setObjectName(QStringLiteral("rate_right"));
    rate_right_->setGeometry(QRect(230, 70, 50, 50));
    rate_right_->setIconSize(QSize(40, 40));
    rate_right_->setStyleSheet(
        "QPushButton{border-image: url(" + holo_root_config_ +
        "/holo_bag/Resource/Icon/background_rate_right.png);border:none;color:rgb(255, 255, 255);}");

    loading_ = new QPushButton(widget_window);
    loading_->setObjectName(QStringLiteral("loading"));
    loading_->setGeometry(QRect(20, 70, 50, 50));
    loading_->setIconSize(QSize(40, 40));
    loading_->setStyleSheet("QPushButton{border-image: url(" + holo_root_config_ +
                            "/holo_bag/Resource/Icon/background_add_file.png);border:none;color:rgb(255, 255, 255);}");

    exit_ = new QPushButton(widget_window);
    exit_->setObjectName(QStringLiteral("exit"));
    exit_->setGeometry(QRect(300, 70, 50, 50));
    exit_->setIconSize(QSize(40, 40));
    exit_->setStyleSheet("QPushButton{border-image: url(" + holo_root_config_ +
                         "/holo_bag/Resource/Icon/background_exit.png);border:none;color:rgb(255, 255, 255);}");

    RetranslateUI(widget_window);
}

void UIWidget::RetranslateUI(QWidget* widget_window)
{
    widget_window->setWindowTitle(QApplication::translate("Widget", "HoloBagGUI", Q_NULLPTR));
    start_time_->setText(QApplication::translate("Widget", "00:00:00", Q_NULLPTR));
    current_time_->setText(QApplication::translate("Widget", "00:00:00", Q_NULLPTR));
    end_time_->setText(QApplication::translate("Widget", "99:99:99", Q_NULLPTR));
    pause_->setText(QString());
    rate_left_->setText(QString());
    rate_right_->setText(QString());
    loading_->setText(QString());
    exit_->setText(QString());
}

void UIWidget::OnExit()
{
    widget_self_->close();
}

std::string UIWidget::OnLoadFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("open a file."), "/home/", tr("holobag(*.holobag)"));

    if (fileName.isEmpty())
    {
        std::cout << "No bag to choose" << std::endl;
        return "";
    }
    return fileName.toUtf8().constData();
}

void UIWidget::OnPause(bool play_pause)
{
    if(play_pause)
    {
        QIcon icon;
        icon.addFile(holo_root_config_ + QObject::tr("/holo_bag/Resource/Icon/background_pause_stop.png"));
        pause_->setIcon(icon);
    }
    else
    { 
        QIcon icon;
        icon.addFile(holo_root_config_ + QObject::tr("/holo_bag/Resource/Icon/background_pause_start.png"));
        pause_->setIcon(icon);
    }
}

holo::float32_t UIWidget::OnRateLeft(holo::float32_t current_rate)
{
    current_rate -= RATE_CHANGE;
    if (current_rate - 0.1 < 0 )
    {
        current_rate += RATE_CHANGE;
        std::cout<<"The min rate is 0.5"<<std::endl;
    }
    return current_rate;
}

holo::float32_t UIWidget::OnRateRight(holo::float32_t current_rate)
{
    current_rate += RATE_CHANGE;
    if (current_rate - 0.1 > 3 )
    {
        current_rate -= RATE_CHANGE;
        std::cout<<"The max rate is 3"<<std::endl;
    }
    return current_rate;
}


#endif //_HOLO_BAG_UI_WIDGET_CPP