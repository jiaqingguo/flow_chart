#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>
#include <QWidget>
#include <QDebug>

#include "drag_group_box.h"
#include "drag_pushbutton.h"

drag_group_box::drag_group_box(QWidget *parent)
{
    setAttribute(Qt::WA_StyledBackground, true);

    // 接受放置事件;
    setAcceptDrops(true);
}

void drag_group_box::mousePressEvent(QMouseEvent *event)
{
    drag_pushbutton *child = static_cast<drag_pushbutton*>(childAt(event->pos()));
    if (!child)
        return;


    int type = child->m_chart_type;

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << type;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/drag_widget", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    Qt::DropAction aa = drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);
    qDebug()<<"DropAction"<<aa;
    if (aa == Qt::MoveAction)
    {
        qDebug()<<"删除lable:";
        child->close();
    }

}

 // 拖动进入事件;
void drag_group_box::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata"))
    {
        if (event->source() == this)
            event->accept();                // 接受事件，不再传递;
        else
            event->acceptProposedAction();  // 窗口部件接受拖放;
    }
    else if(event->mimeData()->hasFormat("application/CTableWidget"))
    {
        if (event->source() == this)
            event->accept();                // 接受事件，不再传递;
        else
            event->acceptProposedAction();  // 窗口部件接受拖放;
    }
    else if(event->mimeData()->hasFormat("application/drag_group_box"))
    {
        if (event->source() == this)
            event->accept();                // 接受事件，不再传递;
        else
            event->acceptProposedAction();  // 窗口部件接受拖放;
    }
    else
        event->ignore();                    // 忽略事件，继续传递;
}

// 拖动移动事件;
void drag_group_box::dragMoveEvent(QDragMoveEvent *event)
{
   if (event->mimeData()->hasFormat("application/x-dnditemdata"))
   {
       if (event->source() == this)
           event->accept();               // 接受事件，不再传递;
       else
           event->acceptProposedAction(); // 窗口部件接受拖放;
   }
   else if(event->mimeData()->hasFormat("application/CTableWidget"))
   {
       if (event->source() == this)
           event->accept();                // 接受事件，不再传递;
       else
           event->acceptProposedAction();  // 窗口部件接受拖放;
   }
   else if(event->mimeData()->hasFormat("application/drag_group_box"))
   {
       if (event->source() == this)
           event->accept();                // 接受事件，不再传递;
       else
           event->acceptProposedAction();  // 窗口部件接受拖放;
   }
   else
       event->ignore();		 // 忽略事件，接续传递;
}

// 拖动离开事件;
void drag_group_box::dragLeaveEvent(QDragLeaveEvent *event)
{
    QWidget::dragLeaveEvent(event);
}

// 拖动放下事件;
void drag_group_box::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata"))
    {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QString dropText;
        dataStream >> dropText ;
        QPushButton *pLabel = new QPushButton(dropText);
       // pGridLayout->addWidget(pLabel);
    }
    else if(event->mimeData()->hasFormat("application/CTableWidget"))
    {
        QByteArray itemData = event->mimeData()->data("application/CTableWidget");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QString dropText;
        dataStream >> dropText ;
        QPushButton *pLabel = new QPushButton(dropText);
       // pGridLayout->addWidget(pLabel);
    }

    event->accept(); //接受事件，不再传递;
}
