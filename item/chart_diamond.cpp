#include <QPainter>
#include <QGraphicsSceneHoverEvent>
#include <QCursor>

#include <QDebug>

#include "chart_diamond.h"
#include "magent_point.h"

chart_diamond::chart_diamond()
{
    this->setData(int(EItemDataType::EItemDataType_ChartType),int(m_type));
    m_rect =QRectF(-50, -50, 100, 100);
    // 设置图形项可以被选择和移动
    setFlags(QGraphicsItem::ItemIsMovable);

    setAcceptHoverEvents(true);

    initMagentPoints();

}

chart_diamond::chart_diamond(qreal width, qreal height) : m_width(width), m_height(height)
{
    this->setData(2,int(m_type));
    // 设置图形项可以被选择和移动
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);

}

void chart_diamond::initMagentPoints()
{
    QRectF rect = boundingRect();

        // 菱形顶点
        QPointF top(rect.center().x(), rect.top());
        QPointF bottom(rect.center().x(), rect.bottom());
        QPointF left(rect.left(), rect.center().y());
        QPointF right(rect.right(), rect.center().y());

        // 边的中点
        QPointF topMid = midPoint(top, right);
        QPointF rightMid = midPoint(right, bottom);
        QPointF bottomMid = midPoint(bottom, left);
        QPointF leftMid = midPoint(left, top);

        // 固定圆圈大小，假设为 16x16 像素
        qreal circleDiameter = 16.0;
        qreal circleRadius = circleDiameter / 2.0; // 圆圈的半径
        qDebug()<<"circleRadius:"<<circleRadius;

        // 创建磁力点圆圈，确保圆圈中心位于菱形边的中点
        m_pTopMagentPoint = new magent_point(
            topMid.x() - circleRadius, topMid.y() - circleRadius,
            circleDiameter, circleDiameter, this);

        m_pRightMagentPoint = new magent_point(
            rightMid.x() - circleRadius, rightMid.y() - circleRadius,
            circleDiameter, circleDiameter, this);

        m_pButtomMagentPoint = new magent_point(
            bottomMid.x() - circleRadius, bottomMid.y() - circleRadius,
            circleDiameter, circleDiameter, this);

        m_pLeftMagentPoint = new magent_point(
            leftMid.x() - circleRadius, leftMid.y() - circleRadius,
            circleDiameter, circleDiameter, this);

}

void chart_diamond::updateMagentPointsPos()
{
    QRectF rect = boundingRect(); // 获取自定义的边界矩形

        // 计算菱形四个角的坐标
        QPointF top(rect.center().x(), rect.top());
        QPointF right(rect.right(), rect.center().y());
        QPointF bottom(rect.center().x(), rect.bottom());
        QPointF left(rect.left(), rect.center().y());

        // 计算每条边的中点坐标
        QPointF midPointTop = (top + left) / 2.0;
        QPointF midPointRight = (top + right) / 2.0;
        QPointF midPointBottom = (bottom + right) / 2.0;
        QPointF midPointLeft = (bottom + left) / 2.0;

        // 假设磁力点图形元素是 chart_diamond 的子项
       // qreal magnetWidth = m_pTopMagentPoint->boundingRect()->rw;  // 磁力点的宽度
       // qreal magnetHeight = 10; // 磁力点的高度
        qreal magnetWidth = m_pTopMagentPoint->boundingRect().width();
        qreal magnetHeight = m_pTopMagentPoint->boundingRect().height();

        // 更新磁力点图形元素的位置，确保磁力点的中心位于中点
        m_pTopMagentPoint->setPos(midPointTop.x() - magnetWidth / 2, midPointTop.y() - magnetHeight / 2);
        m_pRightMagentPoint->setPos(midPointRight.x() - magnetWidth / 2, midPointRight.y() - magnetHeight / 2);
        m_pButtomMagentPoint->setPos(midPointBottom.x() - magnetWidth / 2, midPointBottom.y() - magnetHeight / 2);
        m_pLeftMagentPoint->setPos(midPointLeft.x() - magnetWidth / 2, midPointLeft.y() - magnetHeight / 2);

        // 如果磁力点不是子项，则需要使用 mapToScene 或类似方法将局部坐标转换为场景坐标

        // 最后，确保调用 update()
        update();

       // 如果你需要将磁力点作为图形对象在场景中移动，你可以使用setPos()方法
//       // 例如，如果磁力点是 QGraphicsEllipseItem 类型的对象
//       m_pTopMagentPoint->setPos(m_TopMagnetPoint - QPointF(0, m_pTopMagentPoint->boundingRect().height() / 2));
//       m_pRightMagentPoint->setPos(m_RightMagnetPoint - QPointF(m_pRightMagentPoint->boundingRect().width() / 2, 0));
//       m_pButtomMagentPoint->setPos(m_BottomMagnetPoint - QPointF(0, m_pButtomMagentPoint->boundingRect().height() / 2));
//       m_pLeftMagentPoint->setPos(m_LeftMagnetPoint - QPointF(m_pLeftMagentPoint->boundingRect().width() / 2, 0));

}
void chart_diamond::setBoundingRect(QRectF rectF)
{
    m_rect = rectF;
}

QRectF chart_diamond::boundingRect() const
{
    return m_rect;
}



void chart_diamond::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    m_showRect = true;
    update();
}

void chart_diamond::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    m_showRect = false;
    update();
}

void chart_diamond::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QRectF rect = boundingRect();
    qreal gripSize = 10.0; // 设置一个方便抓取的大小
    QPointF pos = event->pos();

    if (QRectF(rect.topLeft(), QSizeF(gripSize, gripSize)).contains(pos) ||
        QRectF(rect.bottomRight(), QSizeF(-gripSize, -gripSize)).contains(pos))
    {
        setCursor(Qt::SizeFDiagCursor); // 左上角和右下角
    }
    else if (QRectF(rect.topRight(), QSizeF(-gripSize, gripSize)).contains(pos) ||
               QRectF(rect.bottomLeft(), QSizeF(gripSize, -gripSize)).contains(pos))
    {
        setCursor(Qt::SizeBDiagCursor); // 右上角和左下角
    }
    else
    {
        setCursor(Qt::ArrowCursor); // 除角落外的其他区域
    }
}

void chart_diamond::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    m_resizeHandle = None;
    //QRectF rect = boundingRect();
    QRectF rect = m_rect;
    qreal gripSize = 10.0;
    QPointF pos = event->pos();

    // 检查是否点击了角落的区域
    if (QRectF(rect.topLeft(), QSizeF(gripSize, gripSize)).contains(pos))
    {
        m_resizeHandle = TopLeft;
    }
    else if (QRectF(rect.topRight(), QSizeF(-gripSize, gripSize)).contains(pos))
    {
        m_resizeHandle = TopRight;
    }
    else if (QRectF(rect.bottomLeft(), QSizeF(gripSize, -gripSize)).contains(pos))
    {
        m_resizeHandle = BottomLeft;
    }
    else if (QRectF(rect.bottomRight(), QSizeF(-gripSize, -gripSize)).contains(pos))
    {
        m_resizeHandle = BottomRight;
    }

    if (m_resizeHandle != None)
    {
        // 鼠标按下时，保存当前位置和图形项的原始矩形框
        m_resizeStartPos = event->scenePos();
        m_originalRect = rect;
    }

    QGraphicsItem::mousePressEvent(event);
}

void chart_diamond::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_resizeHandle != None)
    {
        QPointF movement = event->scenePos() - m_resizeStartPos;
        QRectF newRect = m_originalRect;

        switch (m_resizeHandle)
        {
            case TopLeft:
                newRect.setTopLeft(newRect.topLeft() + movement);
                break;
            case TopRight:
                newRect.setTopRight(newRect.topRight() + movement);
                break;
            case BottomLeft:
                newRect.setBottomLeft(newRect.bottomLeft() + movement);
                break;
            case BottomRight:
                newRect.setBottomRight(newRect.bottomRight() + movement);
                break;
            default:
                break;
        }

        // 防止矩形翻转
        if (newRect.width() < 10.0 || newRect.height() < 10.0)
            return;

        // 更新图形项的矩形框
        prepareGeometryChange();
        //
        auto diamondRect =newRect.normalized();

        setBoundingRect(newRect.normalized());
        //this->setRect(diamondRect.x(),diamondRect.y(),diamondRect.width(),diamondRect.height());
        update();

        // 如果有必要，更新磁力点的位置
        //updateMagentPointsPos();
    }
    else
    {
        QGraphicsItem::mouseMoveEvent(event);
    }
}

void chart_diamond::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // 完成拉伸后的清理工作
    m_resizeHandle = None;
    QGraphicsItem::mouseReleaseEvent(event);
}


// 绘制菱形
void chart_diamond::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    //QRectF rect = boundingRect();
    QRectF rect = m_rect;
    qreal radius = rect.width() / 2.0;
    qDebug()<<" paint radius:"<<radius;
   // 菱形顶点;
   QPointF top(rect.center().x(), rect.top());
   QPointF bottom(rect.center().x(), rect.bottom());
   QPointF left(rect.left(), rect.center().y());
   QPointF right(rect.right(), rect.center().y());

   // 绘制菱形
   painter->drawLine(top, right);   // 上到右
   painter->drawLine(right, bottom); // 右到下
   painter->drawLine(bottom, left);  // 下到左
   painter->drawLine(left, top);     // 左到上


   if (m_showRect)
   {

          QPen pen(Qt::DashLine);
          painter->setPen(pen);
          painter->drawRect(rect); // 绘制边界框

          // 绘制四个角落的拉伸手柄，可选
          qreal gripSize = 10.0;
          painter->drawRect(QRectF(rect.topLeft(), QSizeF(gripSize, gripSize)));
          painter->drawRect(QRectF(rect.topRight(), QSizeF(-gripSize, gripSize)));
          painter->drawRect(QRectF(rect.bottomLeft(), QSizeF(gripSize, -gripSize)));
          painter->drawRect(QRectF(rect.bottomRight(), QSizeF(-gripSize, -gripSize)));

          // 根据顶点位置，计算每条边的中点
//          QPointF topEdgeMidpoint = (top + right) / 2;
//          QPointF rightEdgeMidpoint = (right + bottom) / 2;
//          QPointF bottomEdgeMidpoint = (bottom + left) / 2;
//          QPointF leftEdgeMidpoint = (left + top) / 2;

//          // 更新磁力点的位置
//          m_pTopMagentPoint->setPos(topEdgeMidpoint);
//          m_pRightMagentPoint->setPos(rightEdgeMidpoint);
//          m_pButtomMagentPoint->setPos(bottomEdgeMidpoint);
//          m_pLeftMagentPoint->setPos(leftEdgeMidpoint);
      }

   // 假设菱形是由其四个顶点定义的
//      QPointF topVertex = ...;   // 菱形顶部顶点
//      QPointF rightVertex = ...; // 菱形右侧顶点
//      QPointF bottomVertex = ...; // 菱形底部顶点
//      QPointF leftVertex = ...;  // 菱形左侧顶点


   // updateMagentPointsPos();

}
