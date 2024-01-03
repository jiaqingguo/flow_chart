#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>

#include <QDebug>

#include "drag_widget.h"


drag_widget::drag_widget(QWidget *parent)
{
   // pGridLayout= new QGridLayout(this);
    setAttribute(Qt::WA_StyledBackground, true);

    // 接受放置事件;
    setAcceptDrops(true);
}

void drag_widget::mousePressEvent(QMouseEvent *event)
{
    QPushButton *child = static_cast<QPushButton*>(childAt(event->pos()));
    if (!child)
        return;

    QString strText = child->text();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << strText;

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
void drag_widget::dragEnterEvent(QDragEnterEvent *event)
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
    else if(event->mimeData()->hasFormat("application/drag_widget"))
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
void drag_widget::dragMoveEvent(QDragMoveEvent *event)
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
   else if(event->mimeData()->hasFormat("application/drag_widget"))
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
void drag_widget::dragLeaveEvent(QDragLeaveEvent *event)
{
    QWidget::dragLeaveEvent(event);
}

// 拖动放下事件;
void drag_widget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata"))
    {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QString dropText;
        dataStream >> dropText ;
        QPushButton *pLabel = new QPushButton(dropText);
        //pGridLayout->addWidget(pLabel);
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

// 在父控件（例如主窗口）中安装事件过滤器
//pushbutton->installEventFilter(this);
// pushbutton-。
//bool drag_widget::eventFilter(QObject *watched, QEvent *event)
//{
//    if ( event->type() == QEvent::MouseButtonPress)
//    {
//
//        // 尝试将object转换为QPushButton类型
//        QPushButton *button = qobject_cast<QPushButton *>(watched);
//        if (button)
//        {
//            // 转换成功，object是QPushButton
//            qDebug() << "QPushButton clicked!";
//            return true; // 表示事件已处理
//        }
//     }
//
//       // 调用基类的事件过滤器方法
//    QWidget::eventFilter(watched,event);
//}
