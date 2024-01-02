#ifndef CHART_BASE_H
#define CHART_BASE_H

#include <QObject>
#include <QGraphicsItem>
#include <QAction>

#include "item/chart_define.h"

class chart_base : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    chart_base();

    EChartType chart_type();

    EChartType m_type;
    int m_w;
    int m_h;
    QColor m_color;
    QAction *m_selectedAction;
    QAction *m_removeAction;

private slots:
    void slot_select_item();
    void slot_remove_Item();
protected:

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
};

#endif // CHART_BASE_H
