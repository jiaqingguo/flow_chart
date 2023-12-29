#include "edge.h"
#include "chip.h"

#include <math.h>
#include <QDebug>
#include <QPainter>
#include <QApplication>
#include <QMenu>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

Edge::Edge(Chip *sourceNode, Chip *destNode,bool pointflag,QPointF pointStart,QPointF pointEnd)
    : arrowSize(10)
{
    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptedMouseButtons(0);
    m_pointFlag = pointflag;

    m_pointStart = pointStart;//偏移量
    m_pointEnd = pointEnd;//偏移量
    source = sourceNode;
    dest = destNode;
    source->addEdge(this);
    dest->addEdge(this);
    adjust();

    m_removeAction = new QAction(QStringLiteral("删除"),this);
    connect(m_removeAction,SIGNAL(triggered()),this,SLOT(slotRemoveItem()));
}
void Edge::adjust()
{
    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    //    qreal length = line.length();

    prepareGeometryChange();

    sourcePoint = line.p1();
    destPoint = line.p2();
    //    sourcePoint = mapFromItem(source, 0, 0);
    //    destPoint = mapFromItem(dest, 0, 0);
}

QRectF Edge::boundingRect() const
{
    if (!source || !dest)
        return QRectF();
    qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize) / 2.0;
    return QRectF(sourcePoint+m_pointStart, QSizeF((destPoint+m_pointEnd).x() - (sourcePoint+m_pointStart).x(),
                                                   (destPoint+m_pointEnd).y() - (sourcePoint+m_pointStart).y()))
            .normalized().adjusted(-extra, -extra, extra, extra);
}
void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
        return;
    QLineF line(sourcePoint+m_pointStart,destPoint+m_pointEnd);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    update();
    painter->drawLine(line);

    // Draw the arrows
    if(m_pointFlag)//
        return;
    double angle = ::acos(line.dx() / line.length());
    if (line.dy() >= 0)
        angle = TwoPi - angle;
    QPointF destArrowP1 = destPoint+m_pointEnd + QPointF(sin(angle - Pi / 3) * arrowSize,
                                                         cos(angle - Pi / 3) * arrowSize);
    QPointF destArrowP2 = destPoint+m_pointEnd + QPointF(sin(angle - Pi + Pi / 3) * arrowSize,
                                                         cos(angle - Pi + Pi / 3) * arrowSize);
    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(QLineF(destArrowP1,destPoint+m_pointEnd));
    painter->drawLine(QLineF(destArrowP2,destPoint+m_pointEnd));
    //    painter->setBrush(Qt::black);
    //    painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
}
void Edge::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"-----move__----------";
    if (event->modifiers() & Qt::ShiftModifier) {
        update();
        return;
    }
    QGraphicsItem::mouseMoveEvent(event);
}
void Edge::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{

    QMenu *menu = new QMenu("123");
    menu->setStyleSheet("QMenu{background-color:rgb(180,200,252);color:rgb(0, 0, 0);font:10pt ""宋体"";}"
                        "QMenu::item:selected{background-color:#CCDAE7;}");
    menu->addAction(m_removeAction);

    menu->exec(event->screenPos());
}
void Edge::slotRemoveItem()
{
    emit remove(this);
    qDebug()<<">>--------------------slotRemoveItem";
}
