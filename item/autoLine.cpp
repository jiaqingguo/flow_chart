#include "autoLine.h"
#include "chip.h"

#include <math.h>
#include <QDebug>
#include <QPainter>
#include <QApplication>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;
AutoLine::AutoLine(Chip *sourceNode,QPointF point)
    : arrowSize(10)
{
    setAcceptedMouseButtons(0);
    source = sourceNode;
    m_pointStart = point;

//    adjust(mapFromItem(source, 0, 0));
}
void AutoLine::adjust(QPointF point)
{
    if (!source || !dest)
        return;

    prepareGeometryChange();//用于在修改图形项的几何形状之前进行准备。这个函数的主要目的是为了通知系统，图形项的几何形状将要发生变化，以便系统能够在必要时进行相应的调整。

    sourcePoint = mapFromItem(source, 0, 0);
    destPoint = point;
}

QRectF AutoLine::boundingRect() const
{
    if (!source || !dest)
        return QRectF();
    qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize) / 2.0;
    return QRectF(sourcePoint+m_pointStart, QSizeF(destPoint.x() - (sourcePoint+m_pointStart).x(),destPoint.y() - (sourcePoint+m_pointStart).y()))
            .normalized().adjusted(-extra, -extra, extra, extra);
}
void AutoLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
        return;
    QLineF line(sourcePoint+m_pointStart,destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);


    double angle = ::acos(line.dx() / line.length());
    if (line.dy() >= 0)
        angle = TwoPi - angle;
    QPointF destArrowP1 = destPoint + QPointF(sin(angle - Pi / 3) * arrowSize,
                                                         cos(angle - Pi / 3) * arrowSize);
    QPointF destArrowP2 = destPoint + QPointF(sin(angle - Pi + Pi / 3) * arrowSize,
                                                         cos(angle - Pi + Pi / 3) * arrowSize);
    painter->drawLine(QLineF(destArrowP1,destPoint));
    painter->drawLine(QLineF(destArrowP2,destPoint));
    qDebug() << "AutoLine::paint()  ";
    qDebug() << destArrowP1 << destArrowP1;
    qDebug() << destArrowP2 << destPoint;
}
