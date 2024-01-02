#ifndef MAGENT_POINT_H
#define MAGENT_POINT_H

#include <QGraphicsEllipseItem>
#include "item/chart_define.h"

class chart_line;

class magent_point : public QGraphicsEllipseItem
{
public:
   // magent_point();
    magent_point(QGraphicsItem *parent = nullptr);

    QList<chart_line *> m_list_chart_line;

    void add_chart_line(chart_line *pLine);

    ///enum { Type = UserType + 2 };
    int type() const override { return m_type; }


    void updatePosition();

    EChartType m_type = EChartType::type_magent_point;

  protected:
      QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
       
};

#endif // MAGENT_POINT_H
