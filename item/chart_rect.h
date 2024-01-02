#ifndef CHART_RECT_H
#define CHART_RECT_H

#include <QGraphicsRectItem>
#include <QSet>

#include "chart_define.h"
#include "magent_point.h"

class chart_rect : public QGraphicsRectItem
{
    //Q_OBJECT
public:
  //  chart_rect(EChartType type);
    chart_rect(EChartType type,QGraphicsItem *parent = nullptr);
    void addMagnetPoint(magent_point *point);
    QSet<magent_point *> magnetPoints() const { return m_magnetPoints; }

    magent_point* get_magent_point_by_scenePos(const QPointF &scenePos);

  //  enum { Type = UserType + 1 };
    int type() const override { return Type; }


       QSet<magent_point *> m_magnetPoints;
       EChartType m_type;


protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;
};

#endif // CHART_RECT_H
