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

void graphics_scene::set_draw_item_type(EChartType type)
{
    m_draw_item_type =type;

}

void graphics_scene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;
    if(m_bDraw)
    {
        QGraphicsItem *pItem =nullptr;
        pItem = itemAt(mouseEvent->scenePos(),QTransform());

        m_pCur_line_Item = nullptr;
        switch (m_draw_item_type)
        {

            case EChartType::type_chart_rect:

                if(pItem==nullptr)
                {
                    pItem = new chart_rect(EChartType::type_chart_rect);

                    addItem(pItem);
                    pItem->setPos(mouseEvent->scenePos());
                }

                break;
            case EChartType::type_chart_line:
                 QGraphicsTextItem *text_item = new QGraphicsTextItem;
                  addItem(text_item);
                m_pCur_line_Item = new chart_line(EChartType::type_chart_line,text_item);
                magent_point* pMagent_point = dynamic_cast<magent_point*>(pItem);
                if(pMagent_point)
                {
                    m_pCur_line_Item->set_start_magent_point(pMagent_point);
                }

                // operstionWidget* pOperstionWidget = dynamic_cast<operstionWidget*>(pWidget);
                addItem(m_pCur_line_Item);
                m_clicked_pointF =mouseEvent->scenePos();
                m_pCur_line_Item->setLine(m_clicked_pointF.x(),m_clicked_pointF.y(),m_clicked_pointF.x(),m_clicked_pointF.y());
                 // qDebug()<<"chart_line create ";
                 break;
     //  default:
          // return;
        }
    }


    QGraphicsScene::mousePressEvent(mouseEvent);
}

void graphics_scene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

    if (m_bDraw && m_draw_item_type == EChartType::type_chart_line )
    {
        if(m_pCur_line_Item)
        {
            /* auto pItem = itemAt(mouseEvent->scenePos(),QTransform());
             magent_point* pMagent_point = dynamic_cast<magent_point*>(pItem);
             if(pMagent_point)
             {
                 qDebug() << "set_end_magent_point---------";
                 m_pCur_line_Item->set_end_magent_point(pMagent_point);
             }*/
          
             m_pCur_line_Item->setLine(m_clicked_pointF.x(),m_clicked_pointF.y(),mouseEvent->scenePos().x(),mouseEvent->scenePos().y());
        }
    }
    else
    {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}

void graphics_scene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (m_draw_item_type == EChartType::type_chart_line  &&  m_pCur_line_Item != nullptr)
    {
        auto pItem = itemAt(mouseEvent->scenePos(), QTransform());
         QList<QGraphicsItem*> items=this->items(mouseEvent->scenePos()/*,Qt::IntersectsItemShape*/);
        auto pchart_rect = dynamic_cast<chart_rect*>(pItem);
        auto Line_itenm = dynamic_cast<chart_line*>(pItem);
        magent_point* pMagent_point = dynamic_cast<magent_point*>(pItem);
        for (auto &item : items)
        {
            magent_point* pMagent_point = dynamic_cast<magent_point*>(item);
            if(pMagent_point)
            {
                qDebug() << "set_end_magent_point---------";
                m_pCur_line_Item->set_end_magent_point(pMagent_point);

            }
         }
//            if (pchart_rect)
//            {
//                magent_point* pMagent_point = pchart_rect->get_magent_point_by_scenePos(pchart_rect->mapFromScene(mouseEvent->scenePos()));
//                if (pMagent_point != nullptr)
//                {
//                    qDebug() << "set_end_magent_point---------";
//                    m_pCur_line_Item->set_end_magent_point(pMagent_point);
//                }
//            }
          
        /*{
            qDebug() << "set_end_magent_point---------";
            m_pCur_line_Item->set_end_magent_point(pMagent_point);
        }*/

       // m_bDraw =false;
        m_pCur_line_Item= nullptr;
    }

    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}


