#include <QMouseEvent>
#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>

#include <QDebug>

#include "graphics_view.h"
#include "item/chart_rect.h"

graphics_view::graphics_view()
{
    setAcceptDrops(true);
}

graphics_view::graphics_view(QWidget *parent)
{

}

void graphics_view::create_chart_item(const EChartType type, const QPointF pos)
{

        switch (type)
        {
            case EChartType::type_chart_rect:
            {
                chart_rect* pItem = new chart_rect(EChartType::type_chart_rect);

                this->scene()->addItem(pItem);
                pItem->setPos(pos);

                break;
            }
            case EChartType::type_chart_diamond:
            {
                chart_rect* pItem = new chart_rect(EChartType::type_chart_rect);
                 pItem->setRotation(45);
                this->scene()->addItem(pItem);
                pItem->setPos(pos);
                  break;
            }


            default:
            {
                 break;
            }
//
        }


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

    QGraphicsView::mousePressEvent(event);
}
void graphics_view::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
}
void graphics_view::mouseDoubleClickEvent(QMouseEvent *event)
{
    //    qDebug()<<"------------------GraphicsView::mouseDoubleClickEvent";

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

        event->pos();
        create_chart_item(EChartType(dropText),mapToScene(event->pos()));

    }

    event->accept(); //接受事件，不再传递;
}





