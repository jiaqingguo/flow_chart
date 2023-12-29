#include "chip.h"

#include <QtWidgets>
#include <QDebug>
#include "edge.h"

Chip::Chip(Types type,int w, int h)
{
    m_type = type;
    this->m_w = w;
    this->m_h = h;
    this->m_color = Qt::white;
    //    setZValue((w + h) % 2);

    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
    setFlag(ItemSendsGeometryChanges,true);//解决节点移动不能响应的问题

    m_selectedAction = new QAction(QStringLiteral("详情"),this);
    m_removeAction = new QAction(QStringLiteral("删除"),this);
    connect(m_removeAction,SIGNAL(triggered()),this,SLOT(slotRemoveItem()));
    connect(m_selectedAction,SIGNAL(triggered()),this,SLOT(slotSelectItem()));
}

QRectF Chip::boundingRect() const
{
    if(m_type == Point)
        return QRectF(0, 0, 3, 3);
    else
        return QRectF(0, 0, 110, 70);
}

QPainterPath Chip::shape() const
{
    QPainterPath path;
    if(m_type == Point)
        path.addRect(1, 1, 1, 1);
    else
        path.addRect(14, 14, 82, 42);
    return path;
}

void Chip::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    if(m_type == Point)
    {
        painter->drawEllipse(0,0,1,1);
        return;
    }
    QColor fillColor = (option->state & QStyle::State_Selected) ? m_color.dark(150) : m_color;
    if (option->state & QStyle::State_MouseOver)
        fillColor = fillColor.light(50);

    QPen oldPen = painter->pen();
    QPen pen = oldPen;
    int width = 0;
    if (option->state & QStyle::State_Selected)
        width += 2;

    pen.setWidth(width);
    QBrush b = painter->brush();
    painter->setBrush(QBrush(fillColor.dark(option->state & QStyle::State_Sunken ? 120 : 100)));

    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    QPolygonF myPolygon;
    switch (m_type) {
    case Conditional://菱形
        myPolygon << QPointF(14, 34) << QPointF(54, 14)
                  << QPointF(94, 34) << QPointF(54, 54)
                  << QPointF(14, 34);
        painter->drawConvexPolygon(myPolygon);
        painter->setBrush(b);
        painter->drawRect(14,32,6,4);
        painter->drawRect(88,32,6,4);
        qDebug() << "菱形paint:" << data(0).toInt();
        painter->drawRect(51,14,6,4);
        painter->drawRect(51,50,6,4);
        break;
    case Process://矩形
        painter->drawRect(QRect(14, 14, 80, 40));//矩形
        painter->setBrush(b);
        painter->drawRect(14,30,4,6);
        painter->drawRect(90,30,4,6);
        painter->drawRect(51,14,6,4);
        painter->drawRect(51,50,6,4);
        break;
    case IO:
        myPolygon << QPointF(14, 14) << QPointF(84, 14)
                  << QPointF(94, 54) << QPointF(24, 54)
                  << QPointF(14, 14);
        painter->drawConvexPolygon(myPolygon);
        painter->setBrush(b);
        painter->drawRect(19,30,4,6);
        painter->drawRect(85,30,4,6);

        painter->drawRect(51,14,6,4);
        painter->drawRect(51,50,6,4);
        break;
    default:
        break;
    }
    // Draw text
    //    if (lod >= 2) {
    //        QFont font("Times", 10);
    //        font.setStyleStrategy(QFont::ForceOutline);
    //        painter->setFont(font);
    //        painter->save();
    //        painter->scale(0.1, 0.1);
    //        painter->drawText(170, 180, QString("Model: VSC-2000 (Very Small Chip) at %1x%2").arg(x).arg(y));
    //        painter->drawText(170, 200, QString("Serial number: DLWR-WEER-123L-ZZ33-SDSJ"));
    //        painter->drawText(170, 220, QString("Manufacturer: Chip Manufacturer"));
    //        painter->restore();
    //    }
}

void Chip::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"-----press";
    int x = event->pos().x();
    int y = event->pos().y();
    switch (m_type) {
    case Conditional://菱形
        if((x>=14 && x<=20 && y>=32 && y<=36)||(x>=88&&x<=94 && y>=32&&y <= 36)||
                (x>=51&&x<=57 && y>=14&&y <= 18)||(x>=51&&x<=57 && y>=50&&y <= 54))
        {
            if(event->button() == Qt::LeftButton)
                emit itemPress(this,event->pos());
//            else if(event->button() == Qt::RightButton)
//                emit itemRightPress(this,event->pos());
        }
        break;
    case Process://矩形
        if((x>=14 && x<=20 && y>=30 && y<=36)||(x>=90&&x<=94 && y>=30&&y <= 36)||
                (x>=51&&x<=57 && y>=14&&y <= 18)||(x>=51&&x<=57 && y>=50&&y <= 54))
        {
            if(event->button() == Qt::LeftButton)
                emit itemPress(this,event->pos());
//            else if(event->button() == Qt::RightButton)
//                emit itemRightPress(this,event->pos());
        }
        break;
    case IO:
        if((x>=19 && x<=23 && y>=30 && y<=36)||(x>=85&&x<=89 && y>=30&&y <= 36)||
                (x>=51&&x<=57 && y>=14&&y <= 18)||(x>=51&&x<=57 && y>=50&&y <= 54))
        {
            if(event->button() == Qt::LeftButton)
                emit itemPress(this,event->pos());
//            else if(event->button() == Qt::RightButton)
//                emit itemRightPress(this,event->pos());
        }
        break;
    default:
        break;
    }
    QGraphicsItem::mousePressEvent(event);
    update();
}

void Chip::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
   // qDebug()<<"-----move";
    if (event->modifiers() & Qt::ShiftModifier) {
        stuff << event->pos();
        update();
        return;
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void Chip::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //    qDebug()<<"-----release";
    //    if(event->button() == Qt::LeftButton)
    //        emit itemPress(this,event->pos());
    //    else if(event->button() == Qt::RightButton)
    //        emit itemRightPress(this,event->pos());
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}
//void Chip::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)//会被view消息覆盖
//{
//    emit itemDoublePress(this);
//    QGraphicsItem::mouseDoubleClickEvent(event);
//    update();
//}
QVariant Chip::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        foreach (Edge *edge, edgeList)
            edge->adjust();
        break;
    default:
        break;
    };
    update();
    return QGraphicsItem::itemChange(change, value);
}
void Chip::addEdge(Edge *edge)
{
    edgeList << edge;
}
void Chip ::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{

    QMenu *menu = new QMenu("123");
    menu->setStyleSheet("QMenu{background-color:rgb(180,200,252);color:rgb(0, 0, 0);font:10pt ""宋体"";}"
                        "QMenu::item:selected{background-color:#CCDAE7;}");
    menu->addAction(m_selectedAction);
    menu->addAction(m_removeAction);

    menu->exec(event->screenPos());
}
void Chip::slotSelectItem()
{
    emit itemInfo(this);
    qDebug()<<">>--------------------slotSelectItem";
}
void Chip::slotRemoveItem()
{
    emit remove(this);
    qDebug()<<">>--------------------slotRemoveItem";
}
