#ifndef DRAG_PUSHBUTTON_H
#define DRAG_PUSHBUTTON_H

#include <QPushButton>

class drag_pushbutton : public QPushButton
{
    Q_OBJECT
public:
    drag_pushbutton(QWidget*parent=nullptr);

    int m_chart_type=-1;
protected:
    // 鼠标点击事件;
     void mousePressEvent(QMouseEvent * event);


};

#endif // DRAG_PUSHBUTTON_H
