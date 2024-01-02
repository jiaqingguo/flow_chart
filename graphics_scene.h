#ifndef GRAPHICS_SCENE_H
#define GRAPHICS_SCENE_H

#include <QGraphicsScene>
#include "item/chart_define.h"

class chart_line;
class GraphicsItemChange;

class graphics_scene : public QGraphicsScene
{
    Q_OBJECT
public:
    graphics_scene();

    // enum Mode { InsertItem, InsertLine, InsertText, MoveItem };
     void set_draw_item_type(EChartType type);

private:
     EChartType m_draw_item_type=EChartType::type_chart_rect;

     bool m_bDraw =true;
     QPointF m_clicked_pointF;
     chart_line *m_pCur_line_Item;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

};

#endif // GRAPHICS_SCENE_H
