#include <QMouseEvent>

#include <QDebug>

#include "graphics_view.h"

graphics_view::graphics_view()
{

}

graphics_view::graphics_view(QWidget *parent)
{

}

const QString qstrStyleSheet("QToolButton{border-radius:4px; background-color: white;}"
                             "QToolButton:hover{border-radius:4px; border: 1px solid transparent; background-color: transparent;}"
                             "QToolButton::menu-indicator{image: None;}");

#ifndef QT_NO_WHEELEVENT
//void graphics_view::wheelEvent(QWheelEvent *e)
//{
//    if (e->modifiers() & Qt::ControlModifier) {
//        if (e->delta() > 0)
//            view->zoomIn(6);
//        else
//            view->zoomOut(6);
//        e->accept();
//    } else {
//        QGraphicsView::wheelEvent(e);
//    }
//}
#endif
void graphics_view::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"GraphicsView::mousePressEvent----------"<<event->pos().x()<<event->pos().y();
    //m_View->mapToScene(m_View->mapFromParent(QPoint(e->x(),e->y()))

            // 获取点击位置的 item
    // 获取鼠标点击位置的视图坐标
       QPointF viewPos = event->pos();

       // 将视图坐标映射到场景坐标
       QPointF scenePos = mapToScene(viewPos.toPoint());

       // 获取鼠标点击位置对应的 item
       QGraphicsItem* clickedItem = scene()->itemAt(scenePos, QTransform());

      //  emit pressLocate(QPoint(event->pos().x(),event->pos().y()));
//       if (clickedItem) {
//           qDebug() << "Clicked on item:" << clickedItem;
//           // 在这里可以对点击到的 item 进行操作
//       } else {

//           //创建新item qDebug() << "Clicked on empty space";
//           emit pressLocate(QPoint(event->pos().x(),event->pos().y()));
//            update();
//       }

    QGraphicsView::mousePressEvent(event);
}
void graphics_view::mouseMoveEvent(QMouseEvent *event)
{
    //    qDebug()<<"----------GraphicsView::mouseMoveEvent"<<event->pos().x()<<event->pos().y();
   // emit mousemove(QPoint(event->pos().x(),event->pos().y()));
    update();
    QGraphicsView::mouseMoveEvent(event);
}
void graphics_view::mouseDoubleClickEvent(QMouseEvent *event)
{
    //    qDebug()<<"------------------GraphicsView::mouseDoubleClickEvent";
    emit doubleClick(QPoint(event->pos().x(),event->pos().y()));
    update();
    QGraphicsView::mouseDoubleClickEvent(event);
}
