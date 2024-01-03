#ifndef CHART_LINE_H
#define CHART_LINE_H

#include <QGraphicsLineItem>
#include <QGraphicsRectItem>

#include "magent_point.h"
#include "chart_define.h"

class QGraphicsTextItem;

class chart_line : public QGraphicsLineItem
{
    //Q_OBJECT
public:
   // chart_line(EChartType type,QGraphicsItem *parent = nullptr);
    chart_line(EChartType type, QGraphicsTextItem* text_item,QGraphicsItem *parent = nullptr);
    chart_line(EChartType type,QGraphicsItem *parent = nullptr);

    void updatePosition();
    void update_text_position();

    void set_start_magent_point(magent_point *start_magent_point);
    void set_end_magent_point(magent_point* end_magent_point);

    bool IsConnectSuccess();
private:
     EChartType m_type;
    magent_point *m_start_magent_point=nullptr;
    magent_point *m_end_magent_point= nullptr;
    QPointF *m_start_point;
    QPointF *m_end_point;

    QPointF m_move_start_point;
    QLineF originalLine;
    QGraphicsRectItem *leftRectItem;
    QGraphicsRectItem *rightRectItem;
    //QGraphicsRectItem leftRectItem;
   // QGraphicsRectItem rightRectItem;

    QGraphicsTextItem *m_text_item;
     QGraphicsRectItem *m_text_backgroud;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
};

#endif // CHART_LINE_H
