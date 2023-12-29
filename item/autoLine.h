#ifndef AUTOLINE_H
#define AUTOLINE_H

#include <QGraphicsItem>
#include <QAction>
#include <QGraphicsSceneContextMenuEvent>

class Chip;

//! [0]
class AutoLine :public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    AutoLine(Chip *sourceNode,QPointF);
    void adjust(QPointF);

protected:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
private:
    Chip *source, *dest;

    QPointF sourcePoint;
    QPointF destPoint;

    qreal arrowSize;

    QPointF m_pointStart;//偏移量

};
//! [0]

#endif // EDGE_H
