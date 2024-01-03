#pragma execution_character_set("utf-8")
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QComboBox>
#include <QGridLayout>
#include <QToolButton>
#include <QButtonGroup>
#include <QToolBar>

#include <QDebug>

#include "item/edge.h"
#include "item/chart_rect.h"
#include "item/chart_line.h"
#include "custom_class/drag_pushbutton.h";

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_scene = new graphics_scene;

    //--------------------------------------------------
    //    QPolygonF myPolygon;
    //    myPolygon << QPointF(0, 0) << QPointF(20, 0)
    //              << QPointF(20, 20) << QPointF(0,20)
    //              << QPointF(0,0);
    QPolygonF myPolygon1;
    myPolygon1 << QPointF(0,10) << QPointF(20,10);
    QPolygonF myPolygon2;
    myPolygon2 << QPointF(10,0) << QPointF(10,20);
    QPixmap pixmap(20, 20);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);

    QVector<qreal> dashes;//line style--
    qreal space = 2;
    dashes << 2 << space << 2 <<space;
    QPen pen(Qt::lightGray,1);
    pen.setDashPattern(dashes);
    pen.setWidth(1);

    painter.setPen(pen);
    //    painter.setPen(QPen(Qt::gray,0.8));
    painter.translate(0, 0);
   // painter.drawPolyline(myPolygon1);  // 设置网格 横线线
    //painter.drawPolyline(myPolygon2);// 设置网格 树线
    m_scene->setBackgroundBrush(pixmap);
    ui->graphicsView->setScene((m_scene));

//    connect(ui->btn_rect,&QPushButton::clicked,this,&MainWindow::slot_btn_rect);
//    connect(ui->btn_round_rect,&QPushButton::clicked,this,&MainWindow::slot_btn_round_rect);
//    connect(ui->btn_round,&QPushButton::clicked,this,&MainWindow::slot_btn_round);

//    connect(ui->btn_line,&QPushButton::clicked,this,&MainWindow::slot_btn_line);
//    connect(ui->btn_diamond,&QPushButton::clicked,this,&MainWindow::slot_btn_diamond);
   // connect(ui->btn_line,&QPushButton::clicked,this,&MainWindow::slot_btn_line);
   // connect(ui->btn_line,&QPushButton::clicked,this,&MainWindow::slot_btn_line);

    connect(ui->graphicsView,&graphics_view::pressLocate,this,&MainWindow::slot_view_mouse_clicked);
    connect(ui->graphicsView,&graphics_view::mousemove,this,&MainWindow::slot_view_mouse_move);

    init_drag_group_box();
    init_tool_bar();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_drag_group_box()
{

    QGridLayout* pLayout = new QGridLayout(ui->groupBox_chart);

    drag_pushbutton *button = new drag_pushbutton;
    button->setText("菱");
    button->setFixedSize(60, 60);
    button->m_chart_type=(int)EChartType::Conditional;
    pLayout->addWidget(button,0,0);


    button  = new drag_pushbutton;
    button->setText("rect");
    button->setFixedSize(60, 60);
    button->m_chart_type=(int)EChartType::type_chart_rect;
    pLayout->addWidget(button,0,1);

    button  = new drag_pushbutton;
    button->setText("圆");
    button->setFixedSize(60, 60);
    button->m_chart_type=(int)EChartType::Process;
    pLayout->addWidget(button,1,0);

    button  = new drag_pushbutton;
    button->setText("线");
    button->setFixedSize(60, 60);
    button->m_chart_type=(int)EChartType::type_chart_line;

    pLayout->addWidget(button,1,1);
    connect(button,&drag_pushbutton::clicked,this,&MainWindow::slot_btn_line);
   // ui->
//    connect(ui->btn_rect,&QPushButton::clicked,this,&MainWindow::slot_btn_rect);
//    connect(ui->btn_round_rect,&QPushButton::clicked,this,&MainWindow::slot_btn_round_rect);
//    connect(ui->btn_round,&QPushButton::clicked,this,&MainWindow::slot_btn_round);

//    connect(ui->btn_line,&QPushButton::clicked,this,&MainWindow::slot_btn_line);
    //    connect(ui->btn_diamond,&QPushButton::clicked,this,&MainWindow::slot_btn_diamond);
}

void MainWindow::init_tool_bar()
{
    QToolButton *pointerButton = new QToolButton;
    pointerButton->setCheckable(true);
    pointerButton->setChecked(true);
    pointerButton->setIcon(QIcon(":/images/pointer.png"));

    QToolButton *linePointerButton = new QToolButton;
    linePointerButton->setCheckable(true);
    linePointerButton->setIcon(QIcon(":/images/linepointer.png"));

    auto pointerTypeGroup = new QButtonGroup(this);
    pointerTypeGroup->addButton(pointerButton, int(ESceneMode::ESceneMode_move));
    pointerTypeGroup->addButton(linePointerButton, int(ESceneMode::ESceneMode_drawLine));
    connect(pointerTypeGroup, QOverload<int>::of(&QButtonGroup::buttonClicked),
            this, &MainWindow::slot_scene_mode_clicked);

    auto sceneScaleCombo = new QComboBox;
    QStringList scales;
    scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(2);
    connect(sceneScaleCombo, &QComboBox::currentTextChanged,
            this, &MainWindow::slot_sceneScaleChanged);

    QToolBar* pointerToolbar = this->addToolBar(tr("Pointer type"));
    pointerToolbar->addWidget(pointerButton);
    pointerToolbar->addWidget(linePointerButton);
    pointerToolbar->addWidget(sceneScaleCombo);

}

void MainWindow::slot_scene_mode_clicked(int id)
{
    m_scene->setMode(ESceneMode(id));
}

void MainWindow::slot_sceneScaleChanged(const QString &scale)
{

}

void MainWindow::slot_btn_rect()
{
    m_type=EChartType::Process;
    m_scene->set_draw_item_type(EChartType::Process);
}

void MainWindow::slot_btn_round_rect()
{
    m_type=EChartType::type_chart_rect;
    m_scene->set_draw_item_type(EChartType::type_chart_rect);
}

void MainWindow::slot_btn_round()
{
    m_type=EChartType::type_chart_line;
    m_scene->set_draw_item_type(EChartType::type_chart_line);
}

void MainWindow::slot_btn_line()
{
    m_type=11;
    m_lineFlag = true;
m_scene->set_draw_item_type(EChartType::Conditional);
}

void MainWindow::slot_btn_diamond()
{
    m_type=EChartType::Conditional;

}

void MainWindow::slot_view_mouse_clicked(QPoint point)
{
    addItem(point);
}

void MainWindow::slot_view_mouse_move(QPoint point)
{
    if (m_everyDraw)
    {
        if (m_everyLine)
        {
           m_everyLine->adjust(ui->graphicsView->mapToScene(point));
        }
        
    }
    if(m_pCur_line_Item)
    {
          //m_pCur_line_Item->setLine(m_clicked_pointF.x(),m_clicked_pointF.y(),ui->graphicsView->mapToScene(point).x(),ui->graphicsView->mapToScene(point).y());
    }
}

void MainWindow::addItem(QPoint point)
{

    //connect(item,SIGNAL(itemRightPress(Chip *,QPointF)),this,SLOT(drawLine(Chip *,QPointF)));//第二个节点被右击
}
void MainWindow::addPoint(QPoint point)//双击加转折点,划线存在
{

}
void MainWindow::everyTimeDraw(QPoint point)//实时划线
{

}

//------------------------------------------------------------------------------------------------------------
void MainWindow::setFirstItem(Chip *chip,QPointF point)//节点左键
{

}
void MainWindow::drawLine(Chip * chip,QPointF point)//节点右键，划线完成
{

}
void MainWindow::remove(Chip *)
{

}

void MainWindow::itemInfo(Chip *)
{

}
void MainWindow::remove(Edge *)
{
    qDebug()<<"--------------------remove(Edge *)";
}
