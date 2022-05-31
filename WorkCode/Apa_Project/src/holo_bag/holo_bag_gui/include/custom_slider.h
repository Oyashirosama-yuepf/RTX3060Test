/**
 * @file custom_slider.h
 * @author housixiu (housiixu1@holomatic.com)
 * @brief the header of the CustomSlider
 * @version 0.1
 * @date 2020-12-22
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLO_BAG_GUI_CUSTOM_SLIDER_H_
#define _HOLO_BAG_GUI_CUSTOM_SLIDER_H_

#include <QLabel>
#include <QMouseEvent>
#include <QSlider>

class CustomSlider : public QSlider
{
public:
    CustomSlider(QWidget *parent=0);
    ~CustomSlider();
 
protected:
    /**
     * @brief mouse press event
     * 
     * @param event mouse event
     */
    virtual void mousePressEvent(QMouseEvent *event);

    /**
     * @brief mouse release event
     * 
     * @param event mouse event
     */
    virtual void mouseReleaseEvent(QMouseEvent *event);

    /**
     * @brief mouse move event
     * 
     * @param event mouse event
     */
    virtual void mouseMoveEvent(QMouseEvent *event);

};



#endif //_HOLO_BAG_GUI_CUSTOM_SLIDER_H_