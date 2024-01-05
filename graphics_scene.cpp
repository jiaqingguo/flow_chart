#include <QGraphicsSceneMouseEvent>

#include <QDebug>

#include "graphics_scene.h"
#include "item/chart_rect.h"
#include "item/chart_line.h"
#include "magent_point.h"



graphics_scene::graphics_scene()
{
    // 接受放置事件;
    //setAcceptDrops(true);
}


void graphics_scene::setMode(const ESceneMode &mode)
{
    m_mode =mode;
}

void graphics_scene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    qDebug()<<"graphics_scene::mousePressEvent----------"<<mouseEvent->pos().x()<<mouseEvent->pos().y();
    if (mouseEvent->button() != Qt::LeftButton)
        return;
    if(m_mode== ESceneMode::ESceneMode_drawLine)
    {
        QGraphicsItem *pItem =nullptr;
        pItem = itemAt(mouseEvent->scenePos(),QTransform());

        m_pCur_line_Item = nullptr;

        m_pCur_line_Item = new chart_line(EChartType::type_chart_line);
        m_pStart_magent_point = dynamic_cast<magent_point*>(pItem);
        if(m_pStart_magent_point)
        {
           // m_pCur_line_Item->set_start_magent_point(pMagent_point);
        }


        addItem(m_pCur_line_Item);
        m_clicked_pointF =mouseEvent->scenePos();
        m_pCur_line_Item->setLine(m_clicked_pointF.x(),m_clicked_pointF.y(),m_clicked_pointF.x(),m_clicked_pointF.y());
    }


    QGraphicsScene::mousePressEvent(mouseEvent);
}

void graphics_scene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

    if (m_mode== ESceneMode::ESceneMode_drawLine  && m_pCur_line_Item)
    {
       m_pCur_line_Item->setLine(m_clicked_pointF.x(),m_clicked_pointF.y(),mouseEvent->scenePos().x(),mouseEvent->scenePos().y()); 
    }
    else
    {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}

void graphics_scene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (m_mode== ESceneMode::ESceneMode_drawLine && m_pCur_line_Item)
    {

        QList<QGraphicsItem*> items=this->items(mouseEvent->scenePos()/*,Qt::IntersectsItemShape*/);

        for (auto &item : items)
        {
            magent_point* pEndMagent_point = dynamic_cast<magent_point*>(item);
            if(pEndMagent_point && m_pStart_magent_point)
            {
                qDebug() << "set_end_magent_point---------";
                m_pCur_line_Item->set_start_magent_point(m_pStart_magent_point);
                m_pCur_line_Item->set_end_magent_point(pEndMagent_point);
            }
        }

        // 删除没有链接的线;
        if (!m_pCur_line_Item->IsConnectSuccess())
        {
            removeItem(m_pCur_line_Item);
            delete m_pCur_line_Item;
        }
        m_pCur_line_Item= nullptr;
    }


    m_pStart_magent_point = nullptr;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}


