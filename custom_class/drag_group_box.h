#ifndef DRAG_GROUP_BOX_H
#define DRAG_GROUP_BOX_H

#include <QGroupBox>
#include <QPushButton>

class drag_group_box : public QGroupBox
{
    Q_OBJECT
public:
    drag_group_box(QWidget*parent=nullptr);

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
private:
    QPushButton *m_pBtn;
   // QGridLayout *pGridLayout;
};

#endif // DRAG_GROUP_BOX_H
