

#include <QDebug>
#include "item/edge.h"


#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_scene = new QGraphicsScene;

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

    connect(ui->btn_rect,&QPushButton::clicked,this,&MainWindow::slot_btn_rect);
    connect(ui->btn_round_rect,&QPushButton::clicked,this,&MainWindow::slot_btn_round_rect);
    connect(ui->btn_round,&QPushButton::clicked,this,&MainWindow::slot_btn_round);

    connect(ui->btn_line,&QPushButton::clicked,this,&MainWindow::slot_btn_line);
    connect(ui->btn_diamond,&QPushButton::clicked,this,&MainWindow::slot_btn_diamond);
   // connect(ui->btn_line,&QPushButton::clicked,this,&MainWindow::slot_btn_line);
   // connect(ui->btn_line,&QPushButton::clicked,this,&MainWindow::slot_btn_line);

    connect(ui->graphicsView,&graphics_view::pressLocate,this,&MainWindow::slot_view_mouse_clicked);
    connect(ui->graphicsView,&graphics_view::mousemove,this,&MainWindow::slot_view_mouse_move);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_btn_rect()
{
    m_type=1;
}

void MainWindow::slot_btn_round_rect()
{

}

void MainWindow::slot_btn_round()
{

}

void MainWindow::slot_btn_line()
{
 m_type=11;
 m_lineFlag = true;
}

void MainWindow::slot_btn_diamond()
{
    m_type=0;
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
           //m_everyLine->adjust(ui->graphicsView->mapToScene(point));
        }
        
    }
}

void MainWindow::addItem(QPoint point)
{
    Chip *item = NULL;
    TItemData data;
    if(m_itemFlag)
    {
        switch (m_type) {
        case 0:
            item = new Chip(Chip::Conditional,0,0);
            break;
        case 1:
            item = new Chip(Chip::Process,0,0);
            break;
        case 2:
            item = new Chip(Chip::IO,0,0);
            break;
        default:
            return;
        }
        if(item)
        {
            m_scene->addItem(item);
            item->setData(0,numofItem);
            item->setPos( ui->graphicsView->mapToScene(point)/*+QPointF(-54,-34)*/);
            connect(item,SIGNAL(itemPress(Chip *,QPointF)),this,SLOT(setFirstItem(Chip *,QPointF)));//第一个节点被单击
            connect(item,SIGNAL(remove(Chip*)),this,SLOT(remove(Chip*)));
            connect(item,SIGNAL(itemInfo(Chip*)),this,SLOT(itemInfo(Chip*)));

            data.item = m_type;
            data.pos =  ui->graphicsView->mapToScene(point);
            data.numItem = numofItem;
            itemData.push_back(data);

            numofItem++;
        }
    }
    //connect(item,SIGNAL(itemRightPress(Chip *,QPointF)),this,SLOT(drawLine(Chip *,QPointF)));//第二个节点被右击
}
void MainWindow::addPoint(QPoint point)//双击加转折点,划线存在
{
   /* TItemData data;
    TLineData data_;
    if(m_lineFlag && m_firstPressChip)
    {
        Chip *item = new Chip(Chip::Point,0,0);
        m_scene->addItem(item);
        item->setData(0,numofItem);
        item->setPos(ui->graphicsView->mapToScene(point));

        data.item = 3;
        data.pos = ui->graphicsView->mapToScene(point);
        data.numItem = numofItem;
        itemData.push_back(data);

        numofItem++;

        Edge *line = new Edge(m_firstPressChip,item,true,m_firstPoint,QPointF(0,0));
        m_scene->addItem(line);
        line->setData(0,numofLine);
        connect(line,SIGNAL(remove(Edge*)),this,SLOT(remove(Edge*)));

        data_.turning = 1;
        data_.startOffset = m_firstPoint;
        data_.endOffset = QPointF(0,0);
        data_.numItem1 = m_firstPressChip->data(0).toString().toInt();
        data_.numItem2 = item->data(0).toString().toInt();
        data_.numLine = numofLine;
        lineData.push_back(data_);

        numofLine++;

        m_firstPressChip = item;
        m_firstPoint = QPointF(0,0);

        if(m_everyLine)
        {
            delete m_everyLine;
            m_everyLine = NULL;
        }
        m_everyLine = new AutoLine(m_firstPressChip,QPointF(0,0));
        m_scene->addItem(m_everyLine);
    }*/
}
void MainWindow::everyTimeDraw(QPoint point)//实时划线
{
//    if(m_everyDraw)
//    {
//        m_everyLine->adjust(ui->graphicsView->mapToScene(point));
//    }
}

//------------------------------------------------------------------------------------------------------------
void MainWindow::setFirstItem(Chip *chip,QPointF point)//节点左键
{
    qDebug()<<"setFirstItem()----start";
    TLineData data_;
    if(m_lineFlag)
    {
        //qDebug()<<"setFirstItem"<<(int)chip;
        if(!m_firstPressChip)//第一个点为空，设置起点
        {
            if(!m_everyDraw)
            {
                m_firstPressChip = chip;
                m_firstPoint = point;
            }

            m_everyDraw = true;

            if(m_everyLine)
            {
                delete m_everyLine;
                m_everyLine = NULL;
            }
            m_everyLine = new AutoLine(m_firstPressChip,m_firstPoint);
            m_scene->addItem(m_everyLine);
        }
        else//设置终点
        {
            m_everyDraw = false;
            if(m_everyLine)
            {
                delete m_everyLine;
                m_everyLine = NULL;
            }
            Edge *line = new Edge(m_firstPressChip,chip,false,m_firstPoint,point);
            m_scene->addItem(line);
            line->setData(0,numofLine);
            connect(line,SIGNAL(remove(Edge*)),this,SLOT(remove(Edge*)));

            data_.turning = 0;
            data_.startOffset = m_firstPoint;
            data_.endOffset = point;
            data_.numItem1 = m_firstPressChip->data(0).toString().toInt();
            data_.numItem2 = chip->data(0).toString().toInt();
            data_.numLine = numofLine;
           // lineData.push_back(data_);


            numofLine++;
            m_firstPressChip = NULL;
        }
    }
}
void MainWindow::drawLine(Chip * chip,QPointF point)//节点右键，划线完成
{

}
void MainWindow::remove(Chip *)
{

}

void MainWindow::itemInfo(Chip *)
{
   // m_AttributeWidget->addView(1,80,40,"details");
   // qDebug()<<"--------------------itemInfo(Chip *)";
}
void MainWindow::remove(Edge *)
{
    qDebug()<<"--------------------remove(Edge *)";
}
