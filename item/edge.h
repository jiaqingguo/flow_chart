#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>
#include <QAction>
#include <QGraphicsSceneContextMenuEvent>

class Chip;

//! [0]
class Edge :public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Edge(Chip *sourceNode, Chip *destNode,bool pointflag,QPointF,QPointF);
    void adjust();

protected:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
private:
    Chip *source, *dest;

    QPointF sourcePoint;
    QPointF destPoint;

    qreal arrowSize;

    bool m_pointFlag;

    QPointF m_pointStart;//偏移量
    QPointF m_pointEnd;

    QAction *m_removeAction;
signals:
    void remove(Edge *);
private slots:
    void slotRemoveItem();
};
//! [0]

#endif // EDGE_H
