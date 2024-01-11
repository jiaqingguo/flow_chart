#include <QGraphicsItem>
#include <QGraphicsSceneHoverEvent>
#include <QCursor>
#include <QPainter>
#include <QDebug>

#include "chart_rect.h"

chart_rect::chart_rect(EChartType type,QGraphicsItem *parent) : QGraphicsRectItem(parent),m_type(type)
{
    setAcceptHoverEvents(true); // 开启鼠标悬停;
    setRect(0, 0, 100, 100);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setFlag(QGraphicsItem::ItemIsMovable);

    // Create magnet points on each side of the rect
    qreal halfWidth = rect().width() / 2;
    qreal halfHeight = rect().height() / 2;

    m_pTopMagentPoint =new magent_point(this);
    m_pTopMagentPoint->setPos(halfWidth, 0);
    addMagnetPoint(m_pTopMagentPoint);

    m_pRightMagentPoint =new magent_point(this);
    m_pRightMagentPoint->setPos(100, halfHeight); // Right
    addMagnetPoint(m_pRightMagentPoint);

    m_pButtomMagentPoint =new magent_point(this);
    m_pButtomMagentPoint->setPos(halfWidth, 100); // Bottom
    addMagnetPoint(m_pButtomMagentPoint);

    m_pLeftMagentPoint =new magent_point(this);
    m_pLeftMagentPoint->setPos(0, halfHeight); // Left
    addMagnetPoint(m_pLeftMagentPoint);

}

void chart_rect::addMagnetPoint(magent_point *point)
{
  //  point->setRect(-8, -8, 16, 16);
    m_magnetPoints.insert(point);
}

magent_point *chart_rect::get_magent_point_by_scenePos(const QPointF &scenePos)
{
    for(auto & magnetPoint  : m_magnetPoints)
    {
        if(magnetPoint->contains(scenePos))
        {
            return magnetPoint;
        }
    }
    return nullptr;
}

QVariant chart_rect::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    switch (change)
    {
    case ItemPositionHasChanged:
        updateConnectLinePos();
        break;
    default:
        break;
    };
    return QGraphicsRectItem::itemChange(change, value);
}

void chart_rect::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if (topLeftHandle.contains(event->pos()))
    {
        setCursor(Qt::SizeFDiagCursor);
    }
    else if (bottomRightHandle.contains(event->pos()))
    {
        setCursor(Qt::SizeFDiagCursor);
    }
    else if (topRightHandle.contains(event->pos()))
    {
        setCursor(Qt::SizeBDiagCursor);
    }
    else if (bottomLeftHandle.contains(event->pos()))
    {
        setCursor(Qt::SizeBDiagCursor);
    }
    else
    {
        setCursor(Qt::ArrowCursor);
    }

}

void chart_rect::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    if (topLeftHandle.contains(event->pos()))
    {
      resizingTopLeft = true;
    }
    else if (bottomRightHandle.contains(event->pos()))
    {
      resizingBottomRight = true;
    }
    else if (topRightHandle.contains(event->pos()))
    {
      resizingTopRight = true;
    }
    else if (bottomLeftHandle.contains(event->pos()))
    {
      resizingBottomLeft = true;
    }
    QGraphicsRectItem::mousePressEvent(event);
}

void chart_rect::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPoint delta = event->pos().toPoint() - event->lastPos().toPoint();

    if (resizingTopLeft)
    {
       QRectF newRect = rect().translated(delta.x(), delta.y());
       newRect.setBottomRight(rect().bottomRight());
       setRect(newRect.normalized());
    }
    else if (resizingBottomRight)
    {
       QRectF newRect = rect();
       newRect.setBottomRight(rect().bottomRight() + delta);
       setRect(newRect.normalized());
    }
    else if (resizingTopRight)
    {
       QRectF newRect = rect();
       newRect.setTopRight(rect().topRight() + QPoint(delta.x(), delta.y()));
       setRect(newRect.normalized());
    }
    else if (resizingBottomLeft)
    {
       QRectF newRect = rect();
       newRect.setBottomLeft(rect().bottomLeft() + QPoint(delta.x(), delta.y()));
       setRect(newRect.normalized());
    }
    else
    {
       QGraphicsRectItem::mouseMoveEvent(event);
    }

}

void chart_rect::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    resizingTopLeft = false;
    resizingBottomRight = false;
    resizingTopRight = false;
    resizingBottomLeft = false;
    QGraphicsRectItem::mouseReleaseEvent(event);
}

void chart_rect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
   painter->setPen(QPen(Qt::black, 2));
   QGraphicsRectItem::paint(painter, option, widget);

   topLeftHandle = QRectF(rect().topLeft(), QSizeF(handleSize, handleSize));
   bottomRightHandle = QRectF(rect().bottomRight() - QPointF(handleSize, handleSize), QSizeF(handleSize, handleSize));
   topRightHandle = QRectF(rect().topRight() + QPointF(-handleSize, 0), QSizeF(handleSize, handleSize));
   bottomLeftHandle = QRectF(rect().bottomLeft() + QPointF(0, -handleSize), QSizeF(handleSize, handleSize));

    updateMagentPointPos();
    updateConnectLinePos();
}


bool chart_rect::isInResizeArea(const QPointF &pos)
{
    QRectF resizeArea = rect().adjusted(-HandleSize, -HandleSize, HandleSize, HandleSize);
    mouseOverTopLeft = QRectF(rect().topLeft(), QSizeF(HandleSize, HandleSize)).contains(pos);
    mouseOverBottomRight = QRectF(rect().bottomRight() - QPointF(HandleSize, HandleSize), QSizeF(HandleSize, HandleSize)).contains(pos);
    // Continue for other corners
    return resizeArea.contains(pos);
}

void chart_rect::updateMagentPointPos()
{
    // 绘制磁力点;
    QRectF r = rect();
    // 上边中点椭圆
    m_pTopMagentPoint->setPos(r.left() + r.width() / 2, r.top());
    // 右边中点椭圆
    m_pRightMagentPoint->setPos(r.right(), r.top() + r.height() / 2);
    // 下边中点椭圆
    m_pButtomMagentPoint->setPos(r.left() + r.width() / 2, r.bottom());
    // 左边中点椭圆
    m_pLeftMagentPoint->setPos(r.left(), r.top() + r.height() / 2);
}

void chart_rect::updateConnectLinePos()
{
    for (auto& magnetPoint : m_magnetPoints)
    {
        magnetPoint->updatePosition();
    }
}
