//#include <QColor>
#include <QBrush>

#include "magent_point.h"
#include "item/chart_line.h"

//magent_point::magent_point()
//{

//}

magent_point::magent_point(QGraphicsItem *parent) : QGraphicsEllipseItem(parent)
{
    setBrush(Qt::blue);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setZValue(3);
}

void magent_point::add_chart_line(chart_line *pLine)
{
    m_list_chart_line.push_back(pLine);
}

void magent_point::updatePosition()
{
    // This method would be called by CustomItem when it moves to update the position of the magnet points
    foreach(chart_line * line, m_list_chart_line)
    {
        line->updatePosition();
        //   edge->adjust();
    }
}

QVariant magent_point::itemChange(GraphicsItemChange change, const QVariant &value)
{
//    if (change == QGraphicsItem::ItemScenePositionHasChanged)
   // {
        // Update connected lines here
   // }
    switch (change)
    {
    //case ItemPositionHasChanged:
    case ItemScenePositionHasChanged:
        foreach (chart_line *line, m_list_chart_line)
        {
            line->updatePosition();
         //   edge->adjust();
        }
        break;
    default:
        break;
    };
    update();
    return QGraphicsEllipseItem::itemChange(change, value);
}
