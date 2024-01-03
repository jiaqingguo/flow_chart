#ifndef DRAG_WIDGET_H
#define DRAG_WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>


class drag_widget : public QWidget
{
    Q_OBJECT
public:
    drag_widget(QWidget*parent=nullptr);

protected:
      // 鼠标点击事件;
      void mousePressEvent(QMouseEvent * event);
      // 拖动进入事件;
      void dragEnterEvent(QDragEnterEvent *event);
      // 拖动移动事件;
      void dragMoveEvent(QDragMoveEvent *event);
      // 拖动离开事件;
      void dragLeaveEvent(QDragLeaveEvent *event);
      // 拖动放下事件;
      void dropEvent(QDropEvent *event);
     // bool eventFilter(QObject *watched, QEvent *event);
private:
    QPushButton *m_pBtn;
    //QGridLayout *pGridLayout;
};

#endif // DRAG_WIDGET_H
