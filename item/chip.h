#ifndef CHIP_H
#define CHIP_H

#include <QColor>
#include <QGraphicsItem>
#include <QAction>

class Edge;
class Chip : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    enum Types { Conditional, Process, IO, Point};//判断 处理 输入
    Chip(Types type,int w, int h);
    void addEdge(Edge *edge);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) Q_DECL_OVERRIDE;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
//    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;

private:
    Types m_type;
    int m_w;
    int m_h;
    QColor m_color;
    QVector<QPointF> stuff;

    QList<Edge *> edgeList;
private:
    QAction *m_selectedAction;
    QAction *m_removeAction;
private slots:
    void slotSelectItem();
    void slotRemoveItem();

signals:
    void itemPress(Chip *,QPointF);
    void itemRightPress(Chip *,QPointF);

    void remove(Chip *);
    void itemInfo(Chip *);
};

#endif // CHIP_H
