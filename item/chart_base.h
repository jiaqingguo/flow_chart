#ifndef CHART_BASE_H
#define CHART_BASE_H

#include <QObject>
#include <QGraphicsItem>


class chart_base : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    chart_base();
};

#endif // CHART_BASE_H
