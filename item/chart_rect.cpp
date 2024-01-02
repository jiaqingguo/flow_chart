#include <QGraphicsItem>

#include <QDebug>

#include "chart_rect.h"

//chart_rect::chart_rect(EChartType type)
//{
//    m_type=type;
//}

chart_rect::chart_rect(EChartType type,QGraphicsItem *parent) : QGraphicsRectItem(parent),m_type(type)
{

    setRect(0, 0, 100, 100);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setFlag(QGraphicsItem::ItemIsMovable);

    // Create magnet points on each side of the rect
    qreal halfWidth = rect().width() / 2;
    qreal halfHeight = rect().height() / 2;

    magent_point *pmagent_point =new magent_point(this);
    pmagent_point->setPos(halfWidth, 0);
    addMagnetPoint(pmagent_point);

    pmagent_point =new magent_point(this);
    pmagent_point->setPos(100, halfHeight); // Right
    addMagnetPoint(pmagent_point);

    pmagent_point =new magent_point(this);
    pmagent_point->setPos(halfWidth, 100); // Bottom
    addMagnetPoint(pmagent_point);

    pmagent_point =new magent_point(this);
    pmagent_point->setPos(0, halfHeight); // Left
    addMagnetPoint(pmagent_point);
    //scene.addItem(pmagent_point);
   // addMagnetPoint(pmagent_point->setPos(halfWidth, 0)); // Top
    //addMagnetPoint(new magent_point(this))->setPos(100, halfHeight); // Right
   // addMagnetPoint(new magent_point(this))->setPos(halfWidth, 100); // Bottom
//    addMagnetPoint(new magent_point(this))->setPos(0, halfHeight); // Left
}

void chart_rect::addMagnetPoint(magent_point *point)
{
    point->setRect(-8, -8, 16, 16);
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
}

QVariant chart_rect::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
   /* for(auto & magnetPoint  : m_magnetPoints)
    {
        magnetPoint->updatePosition();
    }*/
    switch (change)
    {
    case ItemPositionHasChanged:
        for (auto& magnetPoint : m_magnetPoints)
        {
            magnetPoint->updatePosition();
        }
        break;
    default:
        break;
    };
    return QGraphicsRectItem::itemChange(change, value);
}
