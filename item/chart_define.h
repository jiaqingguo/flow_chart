#ifndef CHART_DEFINE_H
#define CHART_DEFINE_H

enum EChartType
{
    tpye_null,
    Conditional,
    Process,
    IO,
    Point,
    line,
    type_chart_rect,
    type_chart_diamond,
    type_chart_line,
    type_magent_point,

};

enum ESceneMode
{
    ESceneMode_move,
    ESceneMode_drawLine,
};

enum EItemDataType
{
    EItemDataType_ID,
    EItemDataType_ChartType,
    EItemDataType_MagentOfRcetID,  // 磁力点所属矩形ID;
};

struct st_chart_based
{

};

#endif // CHART_DEFINE_H

