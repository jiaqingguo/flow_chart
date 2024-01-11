#ifndef CHART_DIAMOND_H
#define CHART_DIAMOND_H

#include <QGraphicsItem>
#include "item/chart_define.h"

class magent_point;

class chart_diamond : public QGraphicsItem
{
public:
    chart_diamond();
    // 构造函数可以接受菱形的尺寸作为参数
    chart_diamond(qreal width, qreal height);



private:
    qreal m_width;   // 菱形的宽
    qreal m_height;  // 菱形的高

    QRectF m_rect;
    EChartType m_type=EChartType::type_chart_diamond;

    magent_point *m_pTopMagentPoint     =nullptr;
    magent_point *m_pLeftMagentPoint    =nullptr;
    magent_point *m_pRightMagentPoint    =nullptr;
    magent_point *m_pButtomMagentPoint   =nullptr;
      bool m_showRect; // 标记是否显示边界框


      enum ResizeHandle { None, TopLeft, TopRight, BottomLeft, BottomRight };
          ResizeHandle m_resizeHandle;
          QPointF m_resizeStartPos;
          QRectF m_originalRect;

private:
    void initMagentPoints();
    void updateMagentPointsPos();
    QPointF midPoint(const QPointF& p1, const QPointF& p2) const {
        return QPointF((p1.x() + p2.x()) / 2.0, (p1.y() + p2.y()) / 2.0);
    }

    void setBoundingRect(QRectF rectF);


protected:
    // 实现 boundingRect() 方法，返回菱形的边界框
    QRectF boundingRect() const override ;

protected:
    // 事件处理函数
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;


    void mousePressEvent(QGraphicsSceneMouseEvent *event) override ;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override ;

    // 绘制菱形
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override ;

};

#endif // CHART_DIAMOND_H
