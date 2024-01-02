#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>

#include "chart_base.h"


chart_base::chart_base()
{

    this->m_color = Qt::white;

    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
    setFlag(ItemSendsGeometryChanges,true);//解决节点移动不能响应的问题

    m_selectedAction = new QAction(QStringLiteral("详情"),this);
    m_removeAction = new QAction(QStringLiteral("删除"),this);
    connect(m_removeAction,SIGNAL(triggered()),this,SLOT(slot_remove_Item()));
    connect(m_selectedAction,SIGNAL(triggered()),this,SLOT(slot_select_item()));
}

EChartType chart_base::chart_type()
{
    return  m_type;
}

void chart_base::slot_select_item()
{

}

void chart_base::slot_remove_Item()
{

}

void chart_base::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu *menu = new QMenu("123");
    menu->setStyleSheet("QMenu{background-color:rgb(180,200,252);color:rgb(0, 0, 0);font:10pt ""宋体"";}"
                        "QMenu::item:selected{background-color:#CCDAE7;}");
    menu->addAction(m_selectedAction);
    menu->addAction(m_removeAction);

    menu->exec(event->screenPos());
}




