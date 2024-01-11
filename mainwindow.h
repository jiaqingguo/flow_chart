#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "graphics_scene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class chart_line;
//class QPointF;

typedef struct tagItemData
{
    int item;//形状-----别的数值表示该点是删除的点
    QPointF pos;//节点
    int numItem;//节点编号
} TItemData;
typedef struct tagLineData
{
    int turning ;//1表示线终点是点，0表示终点，----其他数值表示该线是删除了的线
    QPointF startOffset;
    QPointF endOffset;
    int numItem1;//起点的编号
    int numItem2;//终点的编号
    int numLine;//线的编号
} TLineData;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void init_drag_group_box();

    void init_tool_bar();
private slots:
    void slot_scene_mode_clicked(int id);
    void slot_sceneScaleChanged(const QString &scale);
    void slot_btn_rect();
    void slot_btn_round_rect();
    void slot_btn_round();
    void slot_btn_line();
    void slot_btn_diamond();
   // void slot_btn_rect();

    void slot_view_mouse_clicked(QPoint point);
    void slot_view_mouse_move(QPoint point);
private slots:
    //-----视图传的消息槽
    void addItem(QPoint point);
    void everyTimeDraw(QPoint point);
    void addPoint(QPoint point);

private:
     graphics_scene * m_scene;
      bool m_lineFlag;      // 是否划线;

      bool m_everyDraw=false;
      QPointF m_firstPoint;

      bool m_itemFlag =true;  // 是 item还是line
      int numofItem=0;//节点的编号---0 1 2 3 ...存储的值
      int numofLine=0;//节点的编号---0 1 2 3 ...存储的值
      int m_type =0;
      std::vector<TItemData> itemData;
      std::vector<TLineData> lineData;

      QPointF m_clicked_pointF;
      chart_line *m_pCur_line_Item;

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
