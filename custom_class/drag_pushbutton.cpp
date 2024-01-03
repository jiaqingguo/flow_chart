#include "drag_pushbutton.h"

drag_pushbutton::drag_pushbutton(QWidget*parent)
{

}

void drag_pushbutton::mousePressEvent(QMouseEvent *event)
{

    QPushButton::mousePressEvent(event);
    QWidget::mousePressEvent(event);
}
