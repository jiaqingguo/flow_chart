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

    int type() const override { return m_type; }
private:
    QSet<magent_point *> m_magnetPoints;
    EChartType m_type;

    magent_point *m_pTopMagentPoint     =nullptr;
    magent_point *m_pLeftMagentPoint  =nullptr;
    magent_point *m_pRightMagentPoint    =nullptr;
    magent_point *m_pButtomMagentPoint =nullptr;

    bool resizing = false;
    bool mouseOverTopLeft = false;
    bool mouseOverBottomRight = false;
    int HandleSize = 8;


     static const int handleSize = 8;

    bool resizingTopLeft = false;
      bool resizingBottomRight = false;
      bool resizingTopRight = false;
      bool resizingBottomLeft = false;

      QRectF topLeftHandle;
      QRectF bottomRightHandle;
      QRectF topRightHandle;
      QRectF bottomLeftHandle;
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

protected:
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override ;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override ;


    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override ;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override ;

private:
    bool isInResizeArea(const QPointF &pos) ;

    void  updateMagentPointPos();

    // 更细连接线;
    void updateConnectLinePos();
};

#endif // CHART_RECT_H
