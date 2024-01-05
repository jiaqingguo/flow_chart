#ifndef GRAPHICS_SCENE_H
#define GRAPHICS_SCENE_H

#include <QGraphicsScene>
#include "item/chart_define.h"

class chart_line;
class GraphicsItemChange;
class magent_point;

class graphics_scene : public QGraphicsScene
{
    Q_OBJECT
public:
    graphics_scene();
    
     void setMode(const ESceneMode& mode);
private:
     ESceneMode m_mode=ESceneMode::ESceneMode_move;

     QPointF m_clicked_pointF;
     chart_line *m_pCur_line_Item=nullptr;
     magent_point* m_pStart_magent_point=nullptr; // 开始的磁力点;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;


};

#endif // GRAPHICS_SCENE_H
