#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QInputDialog>

#include <QPen>
#include <QPoint>

#include "chart_line.h"

//chart_line::chart_line(EChartType type, QGraphicsItem *parent)
//{

//}
chart_line::chart_line(EChartType type, QGraphicsItem *parent)
{
     setZValue(1);
    m_type= type;
    m_text_item = new QGraphicsTextItem(this);

    //setLine(QPointF(100,100),QPointF(100,100));

    // 创建QPen对象并设置线条宽度和颜色
       QPen pen;
       pen.setWidth(5); // 设置线条宽度为2个像素
       pen.setColor(Qt::red); // 设置线条颜色为红色

       setPen(pen); // 设置直线的线条

       m_text_item->setFlag(QGraphicsItem::ItemIsMovable, false);
       m_text_item->setFlag(QGraphicsItem::ItemIsSelectable, false);
       m_text_item->setZValue(this->zValue() + 1);
       // 设置文本背景为不透明的白色
       // 创建背景矩形项
          m_text_backgroud = new QGraphicsRectItem(m_text_item->boundingRect(),this);
          m_text_backgroud->setBrush(Qt::white);
           m_text_backgroud->setPen(Qt::NoPen); // 设置为无边框
         // m_text_backgroud->setPos(m_text_item->pos());
       
}

chart_line::chart_line(EChartType type, QGraphicsTextItem* text_item,QGraphicsItem *parent)
{
     setZValue(1);
    m_type= type;
    m_text_item = text_item;

    //setLine(QPointF(100,100),QPointF(100,100));

    // 创建QPen对象并设置线条宽度和颜色
       QPen pen;
       pen.setWidth(5); // 设置线条宽度为2个像素
       pen.setColor(Qt::red); // 设置线条颜色为红色

       setPen(pen); // 设置直线的线条

       m_text_item->setFlag(QGraphicsItem::ItemIsMovable, false);
       m_text_item->setFlag(QGraphicsItem::ItemIsSelectable, false);
       m_text_item->setZValue(this->zValue() + 1);
       // 设置文本背景为不透明的白色
       // 创建背景矩形项
          m_text_backgroud = new QGraphicsRectItem(m_text_item->boundingRect(),this);
          m_text_backgroud->setBrush(Qt::white);
           m_text_backgroud->setPen(Qt::NoPen); // 设置为无边框
         // m_text_backgroud->setPos(m_text_item->pos());

}


void chart_line::updatePosition()
{

//    if (!source || !dest)
//        return;

//    prepareGeometryChange();//用于在修改图形项的几何形状之前进行准备。这个函数的主要目的是为了通知系统，图形项的几何形状将要发生变化，以便系统能够在必要时进行相应的调整。

//    sourcePoint = mapFromItem(source, 0, 0);
//    destPoint = point;
    if (m_start_magent_point && m_end_magent_point)
    {


        QLineF line(mapFromItem(m_start_magent_point, 0, 0), mapFromItem(m_end_magent_point, 0, 0));
        setLine(line);
        update_text_position();
    }
}

void chart_line::update_text_position()
{
    if(m_text_item)
    {
      QPointF center = (line().p1() + line().p2()) / 2;
      m_text_item->setPos(center - QPointF(m_text_item->boundingRect().width() / 2, m_text_item->boundingRect().height() / 2));
      m_text_item->setZValue(this->zValue() + 1);
      m_text_backgroud->setPos(m_text_item->pos());
      m_text_backgroud->setRect(m_text_item->boundingRect());
    }
}

void chart_line::set_start_magent_point(magent_point *start_magent_point)
{
    if(start_magent_point)
    {
        m_start_magent_point = start_magent_point;
        m_start_magent_point->add_chart_line(this);
    }

}

void chart_line::set_end_magent_point(magent_point *end_magent_point)
{
    if(end_magent_point)
    {
        m_end_magent_point = end_magent_point;
        m_end_magent_point->add_chart_line(this);
    }
}

bool chart_line::IsConnectSuccess()
{
    if(m_end_magent_point && m_start_magent_point)
    {
        return true;
    }
    return false;
}

void chart_line::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
       // 记录鼠标按下时的位置
       m_move_start_point= event->scenePos();
        originalLine = line();
       // 创建两个矩形用于处理两边的拖动
       qreal x1 = originalLine.x1() - 5;
       qreal x2 = originalLine.x2() - 5;
       qreal y1 = originalLine.y1() - 5;
       qreal y2 = originalLine.y2() - 5;

       //leftRectItem = new QGraphicsRectItem(x1, y1, 10, 10, this);
      // rightRectItem = new QGraphicsRectItem(x2, y2, 10, 10, this);
      // leftRectItem->setFlag(QGraphicsItem::ItemIsMovable, true);
       //rightRectItem->setFlag(QGraphicsItem::ItemIsMovable, true);
    }
    QGraphicsLineItem::mousePressEvent(event);
}

void chart_line::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        // 计算鼠标移动的距离
        QPointF delta = event->scenePos() - m_move_start_point;
        // 更新线条的位置和长度
        qreal x1 = originalLine.x1() + delta.x();
        qreal y1 = originalLine.y1() + delta.y();
        qreal x2 = originalLine.x2() + delta.x();
        qreal y2 = originalLine.y2() + delta.y();
         update();
        setLine(x1, y1, x2, y2);
       // leftRectItem->setRect(x1 - 5, y1 - 5, 10, 10);
       // rightRectItem->setRect(x2 - 5, y2 - 5, 10, 10);
        // 将起点磁力点的坐标转换为连接线坐标系中的点
         QPointF startMapped = mapFromItem(leftRectItem, 0, 0);
               // 将终点磁力点的坐标转换为连接线坐标系中的点
         QPointF endMapped = mapFromItem(rightRectItem, 0, 0);

               update();
        // 更新矩形的位置
              // setLine(startMapped.x(),startMapped.y(), endMapped.x(),endMapped.y());
                // setLine(m_move_start_point.x(),m_move_start_point.y(), event->scenePos().x(),event->scenePos().y());

    }
    QGraphicsLineItem::mouseMoveEvent(event);
}

void chart_line::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
           {
               // 判断鼠标双击位置是否在中间位置
               QPointF center = (line().p1() + line().p2()) / 2;
               if (QRectF(center - QPointF(50, 25), QSizeF(100, 50)).contains(event->pos()))
               {
                   // 弹出输入对话框
                   bool ok;
                   QString text = QInputDialog::getText(nullptr, "输入文字", "请输入文字:", QLineEdit::Normal, "", &ok);
                   if (ok && !text.isEmpty())
                   {

                       if (m_text_item)
                       {
                           m_text_item->setPlainText(text);
                           m_text_item->setPos(center - QPointF(m_text_item->boundingRect().width() / 2, m_text_item->boundingRect().height() / 2));
                          m_text_backgroud->setPos(m_text_item->pos());
                          m_text_backgroud->setRect(m_text_item->boundingRect());
                       }
                    

                   }
                   else
                   {
                        m_text_item->hide();
                        m_text_backgroud->hide();
                   }

               }
           }
           QGraphicsLineItem::mouseDoubleClickEvent(event);
}
