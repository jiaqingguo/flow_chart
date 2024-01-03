#ifndef GRAPHICS_VIEW_H
#define GRAPHICS_VIEW_H

#include <QGraphicsView>

class graphics_view : public QGraphicsView
{
    Q_OBJECT
public:
    graphics_view();
    graphics_view(QWidget *parent = nullptr);
protected:
#ifndef QT_NO_WHEELEVENT
   // void wheelEvent(QWheelEvent *) Q_DECL_OVERRIDE;
#endif
     void mousePressEvent(QMouseEvent *);
     void mouseMoveEvent(QMouseEvent *event);
     void mouseDoubleClickEvent(QMouseEvent *event);

     // 拖动进入事件;
     void dragEnterEvent(QDragEnterEvent *event);
     // 拖动移动事件;
     void dragMoveEvent(QDragMoveEvent *event);

     // 拖动放下事件;
     void dropEvent(QDropEvent *event);
private:

signals:
    void pressLocate(QPoint);
    void mousemove(QPoint);
    void doubleClick(QPoint);
};

#endif // GRAPHICS_VIEW_H
