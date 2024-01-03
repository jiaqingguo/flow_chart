#include <QMouseEvent>
#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>

#include <QDebug>

#include "graphics_view.h"

graphics_view::graphics_view()
{
    setAcceptDrops(true);
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

void graphics_view::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasFormat("application/drag_widget"))
    {
        if (event->source() == this)
            event->accept();                // 接受事件，不再传递;
        else
            event->acceptProposedAction();  // 窗口部件接受拖放;
    }
    else
        event->ignore();                    // 忽略事件，继续传递;
}

void graphics_view::dragMoveEvent(QDragMoveEvent *event)
{
    if(event->mimeData()->hasFormat("application/drag_widget"))
    {
        if (event->source() == this)
            event->accept();                // 接受事件，不再传递;
        else
            event->acceptProposedAction();  // 窗口部件接受拖放;
    }
    else
        event->ignore();                    // 忽略事件，继续传递;
}

void graphics_view::dropEvent(QDropEvent *event)
{
    if(event->mimeData()->hasFormat("application/drag_widget"))
    {
        QByteArray itemData = event->mimeData()->data("application/drag_widget");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        int dropText;
        dataStream >> dropText ;
        qDebug()<<dropText;
        //QPushButton *pLabel = new QPushButton(dropText);
       // pGridLayout->addWidget(pLabel);
    }

    event->accept(); //接受事件，不再传递;
}





