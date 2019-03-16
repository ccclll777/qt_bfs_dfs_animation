#include "widget.h"
#include "ui_widget.h"
#include "graph.h"
#include"directedgraph.h"
#include"undirectedweightedgraph.h"
#include"directedweightedgraph.h"
#include <QPainter>
#include <QString>
#include <fstream>
#include <sstream>  //string -> int
#include <typeinfo>
#include <QRect>
#include<QDebug>
#include<queue>
#include<QTimer>
#include<QTime>
#include<math.h>
#include<qmath.h>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);



    graph = new Graph();
    directedgraph = new DirectedGraph();
    undirectedweightedgraph = new  UndirectedWeightedGraph();
    directedweightedgraph = new DirectedWeightedGraph();

    is_traverse = false;
    is_create = false;
    is_traverse_bfs = false;
    is_traverse_dfs = false;
    is_isedge = false;
    is_indegrees = false;
    is_outdegrees = false;
    is_isconnect = false;
    is_labelconnect = false;
    is_undirectedgraph = false;
    is_directedgraph =false;
    is_undirectedweightedgraph= false;
    is_directedweightedgraph = false;
    is_prim = false;
    is_compare = false;
//    QFont ft;
//      ft.setPointSize(5);

//     ui->textBrowser->setFont(ft);
//    ui->textBrowser->setStyleSheet("font-size:30px;color:#00FFCC");

//    ui->textBrowser->setText( "欢迎进入图算法演示程序^_^\n请在屏幕右侧选择您要进行的操作^_^");
//    ui->textBrowser->adjustSize();
//      ui->textBrowser->setWordWrap(true);
//     ui->textBrowser->setGeometry(QRect(180, 200, 540, 540));
//    ui->textBrowser->setAlignment(Qt::AlignTop);



}

Widget::~Widget()
{
    delete ui;
}


void Widget::paintEvent(QPaintEvent *)
{

    int r = 10; //半径
    QPainter painter(this);

    //修改背景颜色
    painter.setBrush(Qt::white);
    painter.drawRect(0, 0, this->width(), this->height());
    //无向图的操作
    if (is_create&&is_undirectedgraph)
    {

        //绘制基本路线
        painter.setPen(QPen(Qt::green,2));
        painter.drawLines(graph->line);

    //绘制地图
    painter.setPen(QPen(Qt::black,2));
    QPoint o;
    QString qname;

    for (int i = 0; i < graph->vexnum; ++i)
    {
        painter.drawEllipse(graph->cityMap[i].pos, r, r);
        o = graph->cityMap[i].pos;
        QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
        qname = QString(QString::fromLocal8Bit(graph->cityMap[i].name.c_str()));
        painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));

    }

    //绘制左上角的提示信息
    QPen pen;
    pen.setBrush(QBrush(Qt::red));//设置笔刷
    QVector<qreal> dashes0;
    qreal space0 = 10;
    dashes0 << 5 << space0 << 5 <<space0;
    pen.setDashPattern(dashes0);
    pen.setWidth(2);

    painter.setPen(QPen(Qt::green, 2));
    painter.drawLine(QPoint(10, 60), QPoint(80, 60));
    painter.setPen(QPen(Qt::black, 1));

   string  str = "路线";
    painter.drawText(QPoint(90, 60), QString(QString::fromLocal8Bit(str.c_str())));





    }

    if (is_traverse_bfs&&is_undirectedgraph)
    {   QPen pen;
        pen.setBrush(QBrush(Qt::blue));//设置笔刷
        QVector<qreal> dashes0;
        qreal space0 = 10;
        dashes0 << 5 << space0 << 5 <<space0;
        pen.setDashPattern(dashes0);
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawLine(QPoint(10, 20), QPoint(80, 20));

        painter.setPen(QPen(Qt::black, 1));

        string str = "BFS路线";
        painter.drawText(QPoint(90, 20), QString(QString::fromLocal8Bit(str.c_str())));


        //绘制路线
            QPen pen_bfs;
            pen_bfs.setBrush(QBrush(Qt::blue));
            QVector<qreal> dashes2;
            qreal space2 = 12;
            dashes2 << 5 << space2 << 5 <<space2;
            pen_bfs.setDashPattern(dashes2);
            pen_bfs.setWidth(2);
            painter.setPen(pen_bfs);

//            painter.drawLines(line_bfs2);

            for(int i = 0 ; i< line_bfs2.size() ; i++)
                    {
                        float x1 = line_bfs2[i].x1();       //lastPoint 起点

                        float y1 = line_bfs2[i].y1();

                        float x2 = line_bfs2[i].x2();  //endPoint 终点

                        float y2 = line_bfs2[i].y2();
//                        float x0 = (x1+x2)/2;
//                        float y0 = (y1+y2)/2;
                        float x0 = (2*x1)/3 + x2/3;
                        float y0 = (2*y1)/3 + y2/3;

                        float l = 10.0;                   //箭头的那长度

                        float a = 0.5;                       //箭头与线段角度


                                            float x3 = x0 - l * cos(atan2((y0 - y1) , (x0 - x1)) - a);

                                            float y3 = y0 - l * sin(atan2((y0 - y1) , (x0 - x1)) - a);

                                            float x4 = x0 - l * sin(atan2((x0 - x1) , (y0 - y1)) - a);

                                            float y4 = y0 - l * cos(atan2((x0 - x1) , (y0 - y1)) - a);


                        painter.drawLine(x0,y0,x3,y3);

                        painter.drawLine(x0,y0,x4,y4);

                        painter.drawLine(line_bfs2[i].p1(),line_bfs2[i].p2());


                    }

        //绘制点
        QPoint o;
        QString qname;


//        Map temp_map = point_bfs2.back();
        painter.setPen(Qt::blue);
        for (int i = 0; i < point_bfs2.size(); ++i)
        {
            painter.drawEllipse(point_bfs2[i].pos, r, r);
            o = point_bfs2[i].pos;
            QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
            qname = QString(QString::fromLocal8Bit(point_bfs2[i].name.c_str()));
            painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));


        }
       if(!graph->points_bfs_light.empty())
       {
           Map temp_map = graph->points_bfs_light[0];
           QPen temp_pen;
           temp_pen.setWidth(5);
           temp_pen.setColor(Qt::blue);
           painter.setPen(temp_pen);
           painter.drawEllipse(temp_map.pos, r, r);
           o = temp_map.pos;
           QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
           qname = QString(QString::fromLocal8Bit(temp_map.name.c_str()));
           painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
           graph->points_bfs_light.erase(graph->points_bfs_light.begin());
           qDebug()<< qname;
       }


       painter.setPen(QPen(Qt::black, 1));

       str = "此时BFS选中的顶点（队首的顶点）";
       painter.drawText(QPoint(200, 20), QString(QString::fromLocal8Bit(str.c_str())));
           QPen temp_pen2;
           temp_pen2.setWidth(3);
           temp_pen2.setColor(Qt::blue);
           painter.setPen(temp_pen2);
           painter.drawEllipse(QPoint(170, 15), 6, 6);




}
    if(is_traverse_dfs&&is_undirectedgraph)
    {
        QPen pen;
        pen.setBrush(QBrush(Qt::red));//设置笔刷
        QVector<qreal> dashes0;
        qreal space0 = 10;
        dashes0 << 5 << space0 << 5 <<space0;
        pen.setDashPattern(dashes0);
        pen.setWidth(2);
//        painter.setPen(pen);
//        painter.drawLine(QPoint(10, 100), QPoint(80, 100));
        pen.setBrush(Qt::red);
        painter.setPen(pen);
        painter.drawLine(QPoint(10, 40), QPoint(80, 40));
//        painter.setPen(QPen(Qt::green, 2));
//        painter.drawLine(QPoint(10, 140), QPoint(80, 140));
        painter.setPen(QPen(Qt::black, 1));
        string str("DFS路线");
        painter.drawText(QPoint(90, 40), QString(QString::fromLocal8Bit(str.c_str())) );


                        QPen pen_dfs;
                        pen_dfs.setBrush(QBrush(Qt::red));//设置笔刷
                        QVector<qreal> dashes;
                        qreal space = 12;
                        dashes << 5 << space << 5 <<space;
                        pen_dfs.setDashPattern(dashes);
                        pen_dfs.setWidth(2);
                        painter.setPen(pen_dfs);
//                        painter.drawLines(line_dfs2);

                        for(int i = 0 ; i< line_dfs2.size() ; i++)
                                {
                                    float x1 = line_dfs2[i].x1();       //lastPoint 起点

                                    float y1 = line_dfs2[i].y1();

                                    float x2 = line_dfs2[i].x2();  //endPoint 终点

                                    float y2 = line_dfs2[i].y2();
//                                    float x0 = (x1+x2)/2;
//                                    float y0 = (y1+y2)/2;
                                    float x0 = (2*x1)/3 + x2/3;
                                    float y0 = (2*y1)/3 + y2/3;

                                    float l = 10.0;                   //箭头的那长度

                                    float a = 0.5;                       //箭头与线段角度


                                    float x3 = x0 - l * cos(atan2((y0 - y1) , (x0 - x1)) - a);

                                     float y3 = y0 - l * sin(atan2((y0 - y1) , (x0 - x1)) - a);

                                     float x4 = x0 - l * sin(atan2((x0 - x1) , (y0 - y1)) - a);

                                     float y4 = y0 - l * cos(atan2((x0 - x1) , (y0 - y1)) - a);


                                    painter.drawLine(x0,y0,x3,y3);

                                    painter.drawLine(x0,y0,x4,y4);

                                    painter.drawLine(line_dfs2[i].p1(),line_dfs2[i].p2());


                                }


                        QPoint o;
                        QString qname;
                        if(!graph->points_dfs_light.empty())
                        {
                            Map temp_map = graph->points_dfs_light[0];
                            QPen temp_pen;
                            temp_pen.setWidth(5);
                            temp_pen.setColor(Qt::red);
                            painter.setPen(temp_pen);
                            painter.drawEllipse(temp_map.pos, r, r);
                            o = temp_map.pos;
                            QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                            qname = QString(QString::fromLocal8Bit(temp_map.name.c_str()));
                            painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                            graph->points_dfs_light.erase(graph->points_dfs_light.begin());
                        }
                        painter.setPen(Qt::red);

                        for (int i = 0; i < point_dfs2.size(); ++i)
                        {
                            painter.drawEllipse(point_dfs2[i].pos, r, r);
                            o = point_dfs2[i].pos;
                            QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                            qname = QString(QString::fromLocal8Bit(point_dfs2[i].name.c_str()));
                            painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                            qDebug()<<i;

                        }
                        painter.setPen(QPen(Qt::black, 1));
                        str = "此时DFS选中的顶点（栈顶的顶点）";
                        painter.drawText(QPoint(200, 40), QString(QString::fromLocal8Bit(str.c_str())) );

                        QPen temp_pen2;
                        temp_pen2.setWidth(3);
                        temp_pen2.setColor(Qt::red);
                        painter.setPen(temp_pen2);
                        painter.drawEllipse(QPoint(170, 35), 6, 6);




    }

    if(is_isedge&&is_undirectedgraph)//判断边是否存在
    {
        QPen pen;
        pen.setBrush(QBrush(Qt::red));//设置笔刷

        pen.setWidth(2);

        pen.setBrush(Qt::blue);
        painter.setPen(pen);
        painter.drawLine(QPoint(10, 40), QPoint(80, 40));
        painter.setPen(QPen(Qt::black, 1));
        string str("表示存在这条边");
        painter.drawText(QPoint(90, 40), QString(QString::fromLocal8Bit(str.c_str())) );


        painter.setPen(QPen(Qt::blue,2));
        painter.drawLine(isedge_line);
        painter.setPen(QPen(Qt::black,2));
        QPoint o;
        QString qname;

        for (int i = 0; i < graph->vexnum; ++i)
        {
            painter.drawEllipse(graph->cityMap[i].pos, r, r);
            o = graph->cityMap[i].pos;
            QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
            qname = QString(QString::fromLocal8Bit(graph->cityMap[i].name.c_str()));
            painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));

        }
        is_isedge = false;
    }
    if(is_indegrees&&is_undirectedgraph)//计算顶点入度
    {
        QPen pen;
        pen.setBrush(QBrush(Qt::red));//设置笔刷

        pen.setWidth(2);

        pen.setBrush(Qt::blue);
        painter.setPen(pen);
        painter.drawLine(QPoint(10, 40), QPoint(80, 40));

        painter.setPen(QPen(Qt::black, 1));
        string str("表示进入边");
        painter.drawText(QPoint(90, 40), QString(QString::fromLocal8Bit(str.c_str())) );


        painter.setPen(QPen(Qt::blue,2));
        painter.drawLines(graph->line_indegrees);
        painter.setPen(QPen(Qt::black,2));
        QPoint o;
        QString qname;

        for (int i = 0; i < graph->vexnum; ++i)
        {
            painter.drawEllipse(graph->cityMap[i].pos, r, r);
            o = graph->cityMap[i].pos;
            QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
            qname = QString(QString::fromLocal8Bit(graph->cityMap[i].name.c_str()));
            painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));

        }
        is_indegrees = false;
    }
    if(is_outdegrees&&is_undirectedgraph)
    {
        QPen pen;
        pen.setBrush(QBrush(Qt::red));//设置笔刷

        pen.setWidth(2);

        pen.setBrush(Qt::red);
        painter.setPen(pen);
        painter.drawLine(QPoint(10, 120), QPoint(80, 120));

        painter.setPen(QPen(Qt::black, 1));
        string str("表示出边");
        painter.drawText(QPoint(90, 120), QString(QString::fromLocal8Bit(str.c_str())) );


        painter.setPen(QPen(Qt::red,2));
        painter.drawLines(graph->line_outdegrees);
        painter.setPen(QPen(Qt::black,2));
        QPoint o;
        QString qname;

        for (int i = 0; i < graph->vexnum; ++i)
        {
            painter.drawEllipse(graph->cityMap[i].pos, r, r);
            o = graph->cityMap[i].pos;
            QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
            qname = QString(QString::fromLocal8Bit(graph->cityMap[i].name.c_str()));
            painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));

        }
        is_outdegrees = false;
    }
    if(is_isconnect&&is_undirectedgraph)
    {
        QPen pen;
        pen.setBrush(QBrush(Qt::red));//设置笔刷

        pen.setWidth(2);

        pen.setBrush(Qt::blue);
        painter.setPen(pen);
        painter.drawLine(QPoint(10, 120), QPoint(80, 120));

        painter.setPen(QPen(Qt::black, 1));
        string str("表示可以连通的边");
        painter.drawText(QPoint(90, 120), QString(QString::fromLocal8Bit(str.c_str())) );

        painter.setPen(QPen(Qt::black, 1));
        str = "表示可以连通的顶点";
        painter.drawText(QPoint(230, 120), QString(QString::fromLocal8Bit(str.c_str())) );
        QPen temp_pen2;
        temp_pen2.setWidth(3);
        temp_pen2.setColor(Qt::blue);
        painter.setPen(temp_pen2);
        painter.drawEllipse(QPoint(210, 115), 6, 6);



        //绘制路线

                    QPen pen_bfs;
                    pen_bfs.setBrush(QBrush(Qt::blue));

                    pen_bfs.setWidth(2);
                    painter.setPen(pen_bfs);

                   painter.drawLines(graph->line_bfs);
                   QPoint o;
                    QString qname;
                   painter.setPen(Qt::blue);

                   for (int i = 0; i < graph->points_isconnect.size(); ++i)
                   {
                       painter.drawEllipse(graph->points_isconnect[i].pos, r, r);
                       o = graph->points_isconnect[i].pos;
                       QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                       qname = QString(QString::fromLocal8Bit(graph->points_isconnect[i].name.c_str()));
                       painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                       qDebug()<<i;

                   }
                   is_isconnect = false;
    }
    if( is_labelconnect&&is_undirectedgraph)// 连通构件标记
    {
        QPoint o;
         QString qname;
        for(int i = 0 ; i < Label_map_connect.size() ; i++)
        {
            if(Label_map_connect[i].label_c == 1)
            {

                QPen temp_pen2;
                temp_pen2.setWidth(3);
                temp_pen2.setColor(Qt::blue);
                painter.setPen(temp_pen2);

                 painter.drawEllipse(Label_map_connect[i].pos, r, r);
                 o = Label_map_connect[i].pos;
                 QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                 qname = QString(QString::fromLocal8Bit(Label_map_connect[i].name.c_str()));
                 painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
            }
            if(Label_map_connect[i].label_c == 2)
            {
                QPen temp_pen2;
                temp_pen2.setWidth(3);
                temp_pen2.setColor(Qt::red);
                painter.setPen(temp_pen2);
                painter.drawEllipse(Label_map_connect[i].pos, r, r);
                o = Label_map_connect[i].pos;
                QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                qname = QString(QString::fromLocal8Bit(Label_map_connect[i].name.c_str()));
                painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
            }
            if(Label_map_connect[i].label_c == 3)
            {
                QPen temp_pen2;
                temp_pen2.setWidth(3);
                temp_pen2.setColor(Qt::cyan);
                painter.setPen(temp_pen2);
                painter.drawEllipse(Label_map_connect[i].pos, r, r);
                o = Label_map_connect[i].pos;
                QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                qname = QString(QString::fromLocal8Bit(Label_map_connect[i].name.c_str()));
                painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
            }
        }
        QPen pen;
        pen.setBrush(QBrush(Qt::red));//设置笔刷

        pen.setWidth(2);

        pen.setBrush(Qt::blue);
         painter.setPen(QPen(Qt::black, 1));
        string str = "表示不同的连通分支";
        painter.drawText(QPoint(70, 120), QString(QString::fromLocal8Bit(str.c_str())) );
        QPen temp_pen2;
        temp_pen2.setWidth(3);
        temp_pen2.setColor(Qt::blue);
        painter.setPen(temp_pen2);
        painter.drawEllipse(QPoint(50, 115), 6, 6);
        temp_pen2.setWidth(3);
        temp_pen2.setColor(Qt::cyan);
        painter.setPen(temp_pen2);
        painter.drawEllipse(QPoint(30, 115), 6, 6);
        temp_pen2.setWidth(3);
        temp_pen2.setColor(Qt::red);
        painter.setPen(temp_pen2);
        painter.drawEllipse(QPoint(10, 115), 6, 6);

    }

     //有向图操作
     if (is_create&&is_directedgraph)
     {
         //绘制基本路线
         qDebug()<<"is_create&&is_directedgraph";
         painter.setPen(QPen(Qt::green,2));
         for(int i = 0 ; i< directedgraph->line.size() ; i++)
                 {
                     float x1 = directedgraph->line[i].x1();       //lastPoint 起点

                     float y1 = directedgraph->line[i].y1();

                     float x2 = directedgraph->line[i].x2();  //endPoint 终点

                     float y2 = directedgraph->line[i].y2();
//                     float x0 = (x1+x2)/2;
//                     float y0 = (y1+y2)/2;
                     float x0 = (2*x1)/3 + x2/3;
                     float y0 = (2*y1)/3 + y2/3;
                     float l = 10.0;                   //箭头的那长度

                     float a = 0.5;                       //箭头与线段角度


                                         float x3 = x0 - l * cos(atan2((y0 - y1) , (x0 - x1)) - a);

                                         float y3 = y0 - l * sin(atan2((y0 - y1) , (x0 - x1)) - a);

                                         float x4 = x0 - l * sin(atan2((x0 - x1) , (y0 - y1)) - a);

                                         float y4 = y0 - l * cos(atan2((x0 - x1) , (y0 - y1)) - a);


                     painter.drawLine(x0,y0,x3,y3);

                     painter.drawLine(x0,y0,x4,y4);

                     painter.drawLine(directedgraph->line[i].p1(),directedgraph->line[i].p2());


                 }


     //绘制地图
     painter.setPen(QPen(Qt::black,2));
     QPoint o;
     QString qname;

     for (int i = 0; i <directedgraph->vexnum; ++i)
     {
         painter.drawEllipse(directedgraph->cityMap[i].pos, r, r);
         o = directedgraph->cityMap[i].pos;
         QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
         qname = QString(QString::fromLocal8Bit(directedgraph->cityMap[i].name.c_str()));
         painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));

     }

     //绘制左上角的提示信息
     QPen pen;
     pen.setBrush(QBrush(Qt::red));//设置笔刷
     QVector<qreal> dashes0;
     qreal space0 = 10;
     dashes0 << 5 << space0 << 5 <<space0;
     pen.setDashPattern(dashes0);
     pen.setWidth(2);

     painter.setPen(QPen(Qt::green, 2));
     painter.drawLine(QPoint(10, 60), QPoint(80, 60));
     painter.setPen(QPen(Qt::black, 1));

    string  str = "路线";
     painter.drawText(QPoint(90, 60), QString(QString::fromLocal8Bit(str.c_str())));

     }
    if (is_traverse_bfs&&is_directedgraph)
 {
     QPen pen;
             pen.setBrush(QBrush(Qt::blue));//设置笔刷
             QVector<qreal> dashes0;
             qreal space0 = 10;
             dashes0 << 5 << space0 << 5 <<space0;
             pen.setDashPattern(dashes0);
             pen.setWidth(2);
             painter.setPen(pen);
             painter.drawLine(QPoint(10, 20), QPoint(80, 20));

             painter.setPen(QPen(Qt::black, 1));

             string str = "BFS路线";
             painter.drawText(QPoint(90, 20), QString(QString::fromLocal8Bit(str.c_str())));


             //绘制路线
                 QPen pen_bfs;
                 pen_bfs.setBrush(QBrush(Qt::blue));
                 QVector<qreal> dashes2;
                 qreal space2 = 12;
                 dashes2 << 5 << space2 << 5 <<space2;
                 pen_bfs.setDashPattern(dashes2);
                 pen_bfs.setWidth(2);
                 painter.setPen(pen_bfs);

     //            painter.drawLines(line_bfs2);

                 for(int i = 0 ; i< line_bfs2.size() ; i++)
                         {
                             float x1 = line_bfs2[i].x1();       //lastPoint 起点

                             float y1 = line_bfs2[i].y1();

                             float x2 = line_bfs2[i].x2();  //endPoint 终点

                             float y2 = line_bfs2[i].y2();
//                             float x0 = (x1+x2)/2;
//                             float y0 = (y1+y2)/2;
                             float x0 = (2*x1)/3 + x2/3;
                             float y0 = (2*y1)/3 + y2/3;

                             float l = 10.0;                   //箭头的那长度

                             float a = 0.5;                       //箭头与线段角度


                                                 float x3 = x0 - l * cos(atan2((y0 - y1) , (x0 - x1)) - a);

                                                 float y3 = y0 - l * sin(atan2((y0 - y1) , (x0 - x1)) - a);

                                                 float x4 = x0 - l * sin(atan2((x0 - x1) , (y0 - y1)) - a);

                                                 float y4 = y0 - l * cos(atan2((x0 - x1) , (y0 - y1)) - a);


                             painter.drawLine(x0,y0,x3,y3);

                             painter.drawLine(x0,y0,x4,y4);

                             painter.drawLine(line_bfs2[i].p1(),line_bfs2[i].p2());


                         }

             //绘制点
             QPoint o;
             QString qname;


     //        Map temp_map = point_bfs2.back();
             painter.setPen(Qt::blue);
             for (int i = 0; i < point_bfs2.size(); ++i)
             {
                 painter.drawEllipse(point_bfs2[i].pos, r, r);
                 o = point_bfs2[i].pos;
                 QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                 qname = QString(QString::fromLocal8Bit(point_bfs2[i].name.c_str()));
                 painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));


             }
            if(!directedgraph->points_bfs_light.empty())
            {
                Map temp_map = directedgraph->points_bfs_light[0];
                QPen temp_pen;
                temp_pen.setWidth(5);
                temp_pen.setColor(Qt::blue);
                painter.setPen(temp_pen);
                painter.drawEllipse(temp_map.pos, r, r);
                o = temp_map.pos;
                QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                qname = QString(QString::fromLocal8Bit(temp_map.name.c_str()));
                painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                directedgraph->points_bfs_light.erase(directedgraph->points_bfs_light.begin());
                qDebug()<< qname;
            }


            painter.setPen(QPen(Qt::black, 1));

            str = "此时BFS选中的顶点（队首的顶点）";
            painter.drawText(QPoint(200, 20), QString(QString::fromLocal8Bit(str.c_str())));
                QPen temp_pen2;
                temp_pen2.setWidth(3);
                temp_pen2.setColor(Qt::blue);
                painter.setPen(temp_pen2);
                painter.drawEllipse(QPoint(170, 15), 6, 6);


 }
    if(is_traverse_dfs&&is_directedgraph)
    {
        QPen pen;
        pen.setBrush(QBrush(Qt::red));//设置笔刷
        QVector<qreal> dashes0;
        qreal space0 = 10;
        dashes0 << 5 << space0 << 5 <<space0;
        pen.setDashPattern(dashes0);
        pen.setWidth(2);
//        painter.setPen(pen);
//        painter.drawLine(QPoint(10, 100), QPoint(80, 100));
        pen.setBrush(Qt::red);
        painter.setPen(pen);
        painter.drawLine(QPoint(10, 40), QPoint(80, 40));
//        painter.setPen(QPen(Qt::green, 2));
//        painter.drawLine(QPoint(10, 140), QPoint(80, 140));
        painter.setPen(QPen(Qt::black, 1));
        string str("DFS路线");
        painter.drawText(QPoint(90, 40), QString(QString::fromLocal8Bit(str.c_str())) );


                        QPen pen_dfs;
                        pen_dfs.setBrush(QBrush(Qt::red));//设置笔刷
                        QVector<qreal> dashes;
                        qreal space = 12;
                        dashes << 5 << space << 5 <<space;
                        pen_dfs.setDashPattern(dashes);
                        pen_dfs.setWidth(2);
                        painter.setPen(pen_dfs);
//                        painter.drawLines(line_dfs2);

                        for(int i = 0 ; i< line_dfs2.size() ; i++)
                                {
                                    float x1 = line_dfs2[i].x1();       //lastPoint 起点

                                    float y1 = line_dfs2[i].y1();

                                    float x2 = line_dfs2[i].x2();  //endPoint 终点

                                    float y2 = line_dfs2[i].y2();
//                                    float x0 = (x1+x2)/2;
//                                    float y0 = (y1+y2)/2;
                                    float x0 = (2*x1)/3 + x2/3;
                                    float y0 = (2*y1)/3 + y2/3;

                                    float l = 10.0;                   //箭头的那长度

                                    float a = 0.5;                       //箭头与线段角度


                                    float x3 = x0 - l * cos(atan2((y0 - y1) , (x0 - x1)) - a);

                                     float y3 = y0 - l * sin(atan2((y0 - y1) , (x0 - x1)) - a);

                                     float x4 = x0 - l * sin(atan2((x0 - x1) , (y0 - y1)) - a);

                                     float y4 = y0 - l * cos(atan2((x0 - x1) , (y0 - y1)) - a);


                                    painter.drawLine(x0,y0,x3,y3);

                                    painter.drawLine(x0,y0,x4,y4);

                                    painter.drawLine(line_dfs2[i].p1(),line_dfs2[i].p2());


                                }


                        QPoint o;
                        QString qname;
                        if(!directedgraph->points_dfs_light.empty())
                        {
                            Map temp_map = directedgraph->points_dfs_light[0];
                            QPen temp_pen;
                            temp_pen.setWidth(5);
                            temp_pen.setColor(Qt::red);
                            painter.setPen(temp_pen);
                            painter.drawEllipse(temp_map.pos, r, r);
                            o = temp_map.pos;
                            QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                            qname = QString(QString::fromLocal8Bit(temp_map.name.c_str()));
                            painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                            directedgraph->points_dfs_light.erase(directedgraph->points_dfs_light.begin());
                        }
                        painter.setPen(Qt::red);

                        for (int i = 0; i < point_dfs2.size(); ++i)
                        {
                            painter.drawEllipse(point_dfs2[i].pos, r, r);
                            o = point_dfs2[i].pos;
                            QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                            qname = QString(QString::fromLocal8Bit(point_dfs2[i].name.c_str()));
                            painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                            qDebug()<<i;

                        }
                        painter.setPen(QPen(Qt::black, 1));
                        str = "此时DFS选中的顶点（栈顶的顶点）";
                        painter.drawText(QPoint(200, 40), QString(QString::fromLocal8Bit(str.c_str())) );

                        QPen temp_pen2;
                        temp_pen2.setWidth(3);
                        temp_pen2.setColor(Qt::red);
                        painter.setPen(temp_pen2);
                        painter.drawEllipse(QPoint(170, 35), 6, 6);
    if(is_isedge&&is_directedgraph)
    {
        QPen pen;
        pen.setBrush(QBrush(Qt::red));//设置笔刷

        pen.setWidth(2);

        pen.setBrush(Qt::blue);
        painter.setPen(pen);
        painter.drawLine(QPoint(10,40), QPoint(80, 40));

        painter.setPen(QPen(Qt::black, 1));
        string str("表示存在这条边");
        painter.drawText(QPoint(90, 40), QString(QString::fromLocal8Bit(str.c_str())) );


        painter.setPen(QPen(Qt::blue,2));
        painter.drawLine(isedge_line);
        painter.setPen(QPen(Qt::black,2));
        QPoint o;
        QString qname;

        for (int i = 0; i < directedgraph->vexnum; ++i)
        {
            painter.drawEllipse(directedgraph->cityMap[i].pos, r, r);
            o = directedgraph->cityMap[i].pos;
            QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
            qname = QString(QString::fromLocal8Bit(directedgraph->cityMap[i].name.c_str()));
            painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));

        }
        is_isedge = false;
    }
    }
    if(is_isedge&&is_directedgraph)
    {
        QPen pen;
        pen.setBrush(QBrush(Qt::red));//设置笔刷

        pen.setWidth(2);

        pen.setBrush(Qt::blue);
        painter.setPen(pen);
        painter.drawLine(QPoint(10, 40), QPoint(80, 40));

        painter.setPen(QPen(Qt::black, 1));
        string str("表示存在这条边");
        painter.drawText(QPoint(90, 40), QString(QString::fromLocal8Bit(str.c_str())) );


        painter.setPen(QPen(Qt::blue,2));
//        painter.drawLine(isedge_line);
            float x1 = isedge_line.x1();       //lastPoint 起点
            float y1 = isedge_line.y1();
            float x2 = isedge_line.x2();  //endPoint 终点
            float y2 =isedge_line.y2();
//            float x0 = (x1+x2)/2;
//            float y0 = (y1+y2)/2;
            float x0 = (2*x1)/3 + x2/3;
            float y0 = (2*y1)/3 + y2/3;
            float l = 10.0;                   //箭头的那长度
            float a = 0.5;                       //箭头与线段角度
            float x3 = x0 - l * cos(atan2((y0 - y1) , (x0 - x1)) - a);
            float y3 = y0 - l * sin(atan2((y0 - y1) , (x0 - x1)) - a);
            float x4 = x0 - l * sin(atan2((x0 - x1) , (y0 - y1)) - a);
            float y4 = y0 - l * cos(atan2((x0 - x1) , (y0 - y1)) - a);
            painter.drawLine(x0,y0,x3,y3);
            painter.drawLine(x0,y0,x4,y4);
            painter.drawLine(isedge_line.p1(),isedge_line.p2());
            painter.setPen(QPen(Qt::black,2));
        QPoint o;
        QString qname;

        for (int i = 0; i < directedgraph->vexnum; ++i)
        {
            painter.drawEllipse(directedgraph->cityMap[i].pos, r, r);
            o = directedgraph->cityMap[i].pos;
            QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
            qname = QString(QString::fromLocal8Bit(directedgraph->cityMap[i].name.c_str()));
            painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));

        }
        is_isedge = false;
    }
    if(is_indegrees&&is_directedgraph)
    {
        QPen pen;
        pen.setBrush(QBrush(Qt::red));//设置笔刷

        pen.setWidth(2);

        pen.setBrush(Qt::blue);
        painter.setPen(pen);
        painter.drawLine(QPoint(10, 40), QPoint(80,40));

        painter.setPen(QPen(Qt::black, 1));
        string str("表示进入边");
        painter.drawText(QPoint(90, 40), QString(QString::fromLocal8Bit(str.c_str())) );


        painter.setPen(QPen(Qt::blue,2));
        for(int i = 0 ; i< directedgraph->line_indegrees.size() ; i++)
                {
                    float x1 = directedgraph->line_indegrees[i].x1();       //lastPoint 起点

                    float y1 = directedgraph->line_indegrees[i].y1();

                    float x2 = directedgraph->line_indegrees[i].x2();  //endPoint 终点

                    float y2 =directedgraph->line_indegrees[i].y2();
//                    float x0 = (x1+x2)/2;
//                    float y0 = (y1+y2)/2;
                    float x0 = (2*x1)/3 + x2/3;
                    float y0 = (2*y1)/3 + y2/3;
                    float l = 10.0;                   //箭头的那长度

                    float a = 0.5;                       //箭头与线段角度


                                        float x3 = x0 - l * cos(atan2((y0 - y1) , (x0 - x1)) - a);

                                        float y3 = y0 - l * sin(atan2((y0 - y1) , (x0 - x1)) - a);

                                        float x4 = x0 - l * sin(atan2((x0 - x1) , (y0 - y1)) - a);

                                        float y4 = y0 - l * cos(atan2((x0 - x1) , (y0 - y1)) - a);


                    painter.drawLine(x0,y0,x3,y3);

                    painter.drawLine(x0,y0,x4,y4);

                    painter.drawLine(directedgraph->line_indegrees[i].p1(),directedgraph->line_indegrees[i].p2());


                }
//        painter.drawLines(directedgraph->line_indegrees);
        painter.setPen(QPen(Qt::black,2));
        QPoint o;
        QString qname;

        for (int i = 0; i < directedgraph->vexnum; ++i)
        {
            painter.drawEllipse(directedgraph->cityMap[i].pos, r, r);
            o = directedgraph->cityMap[i].pos;
            QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
            qname = QString(QString::fromLocal8Bit(directedgraph->cityMap[i].name.c_str()));
            painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));

        }
        is_indegrees = false;
    }
    if(is_outdegrees&&is_directedgraph)
    {
        QPen pen;
        pen.setBrush(QBrush(Qt::red));//设置笔刷

        pen.setWidth(2);

        pen.setBrush(Qt::red);
        painter.setPen(pen);
        painter.drawLine(QPoint(10,40), QPoint(80, 40));

        painter.setPen(QPen(Qt::black, 1));
        string str("表示出边");
        painter.drawText(QPoint(90, 40), QString(QString::fromLocal8Bit(str.c_str())) );


        painter.setPen(QPen(Qt::red,2));
//        painter.drawLines(directedgraph->line_outdegrees);
        for(int i = 0 ; i< directedgraph->line_outdegrees.size() ; i++)
                {
                    float x1 = directedgraph->line_outdegrees[i].x1();       //lastPoint 起点
                    float y1 =directedgraph->line_outdegrees[i].y1();
                    float x2 =directedgraph->line_outdegrees[i].x2();  //endPoint 终点
                    float y2 =directedgraph->line_outdegrees[i].y2();
//                    float x0 = (x1+x2)/2;
//                    float y0 = (y1+y2)/2;
                    float x0 = (2*x1)/3 + x2/3;
                    float y0 = (2*y1)/3 + y2/3;
                    float l = 10.0;                   //箭头的那长度
                    float a = 0.5;                       //箭头与线段角度
                    float x3 = x0 - l * cos(atan2((y0 - y1) , (x0 - x1)) - a);
                     float y3 = y0 - l * sin(atan2((y0 - y1) , (x0 - x1)) - a);
                    float x4 = x0 - l * sin(atan2((x0 - x1) , (y0 - y1)) - a);
                    float y4 = y0 - l * cos(atan2((x0 - x1) , (y0 - y1)) - a);
                    painter.drawLine(x0,y0,x3,y3);
                    painter.drawLine(x0,y0,x4,y4);
                    painter.drawLine(directedgraph->line_outdegrees[i].p1(),directedgraph->line_outdegrees[i].p2());


                }
        painter.setPen(QPen(Qt::black,2));
        QPoint o;
        QString qname;

        for (int i = 0; i < directedgraph->vexnum; ++i)
        {
            painter.drawEllipse(directedgraph->cityMap[i].pos, r, r);
            o = directedgraph->cityMap[i].pos;
            QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
            qname = QString(QString::fromLocal8Bit(directedgraph->cityMap[i].name.c_str()));
            painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));

        }
        is_outdegrees = false;
    }
    if(is_isconnect&&is_directedgraph)
     {
         QPen pen;
         pen.setBrush(QBrush(Qt::red));//设置笔刷

         pen.setWidth(2);

         pen.setBrush(Qt::blue);
         painter.setPen(pen);
         painter.drawLine(QPoint(10, 40), QPoint(80, 40));

         painter.setPen(QPen(Qt::black, 1));
         string str("表示可以连通的边");
         painter.drawText(QPoint(90, 40), QString(QString::fromLocal8Bit(str.c_str())) );

         painter.setPen(QPen(Qt::black, 1));
         str = "表示可以连通的顶点";
         painter.drawText(QPoint(230, 40), QString(QString::fromLocal8Bit(str.c_str())) );
         QPen temp_pen2;
         temp_pen2.setWidth(3);
         temp_pen2.setColor(Qt::blue);
         painter.setPen(temp_pen2);
         painter.drawEllipse(QPoint(210, 35), 6, 6);



         //绘制路线

                     QPen pen_bfs;
                     pen_bfs.setBrush(QBrush(Qt::blue));

                     pen_bfs.setWidth(2);
                     painter.setPen(pen_bfs);

//                    painter.drawLines(directedgraph->line_bfs);
                    for(int i = 0 ; i< directedgraph->line_bfs.size() ; i++)
                            {
                                float x1 = directedgraph->line_bfs[i].x1();       //lastPoint 起点

                                float y1 = directedgraph->line_bfs[i].y1();

                                float x2 = directedgraph->line_bfs[i].x2();  //endPoint 终点

                                float y2 = directedgraph->line_bfs[i].y2();
//                                float x0 = (x1+x2)/2;
//                                float y0 = (y1+y2)/2;
                                float x0 = (2*x1)/3 + x2/3;
                                float y0 = (2*y1)/3 + y2/3;
                                float l = 10.0;                   //箭头的那长度

                                float a = 0.5;                       //箭头与线段角度


                                float x3 = x0 - l * cos(atan2((y0 - y1) , (x0 - x1)) - a);

                                 float y3 = y0 - l * sin(atan2((y0 - y1) , (x0 - x1)) - a);

                                 float x4 = x0 - l * sin(atan2((x0 - x1) , (y0 - y1)) - a);

                                 float y4 = y0 - l * cos(atan2((x0 - x1) , (y0 - y1)) - a);


                                painter.drawLine(x0,y0,x3,y3);

                                painter.drawLine(x0,y0,x4,y4);

                                painter.drawLine(directedgraph->line_bfs[i].p1(),directedgraph->line_bfs[i].p2());


                            }

                    QPoint o;
                     QString qname;
                    painter.setPen(Qt::blue);

                    for (int i = 0; i < directedgraph->points_isconnect.size(); ++i)
                    {
                        painter.drawEllipse(directedgraph->points_isconnect[i].pos, r, r);
                        o = directedgraph->points_isconnect[i].pos;
                        QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                        qname = QString(QString::fromLocal8Bit(directedgraph->points_isconnect[i].name.c_str()));
                        painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                        qDebug()<<i;

                    }
                    is_isconnect = false;
     }
    if( is_labelconnect&&is_directedgraph)
    {
        QPoint o;
         QString qname;
        for(int i = 0 ; i < Label_map_connect.size() ; i++)
        {
            if(Label_map_connect[i].label_c == 1)
            {

                QPen temp_pen2;
                temp_pen2.setWidth(3);
                temp_pen2.setColor(Qt::blue);
                painter.setPen(temp_pen2);

                 painter.drawEllipse(Label_map_connect[i].pos, r, r);
                 o = Label_map_connect[i].pos;
                 QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                 qname = QString(QString::fromLocal8Bit(Label_map_connect[i].name.c_str()));
                 painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
            }
            if(Label_map_connect[i].label_c == 2)
            {
                QPen temp_pen2;
                temp_pen2.setWidth(3);
                temp_pen2.setColor(Qt::red);
                painter.setPen(temp_pen2);
                painter.drawEllipse(Label_map_connect[i].pos, r, r);
                o = Label_map_connect[i].pos;
                QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                qname = QString(QString::fromLocal8Bit(Label_map_connect[i].name.c_str()));
                painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
            }
            if(Label_map_connect[i].label_c == 3)
            {
                QPen temp_pen2;
                temp_pen2.setWidth(3);
                temp_pen2.setColor(Qt::cyan);
                painter.setPen(temp_pen2);
                painter.drawEllipse(Label_map_connect[i].pos, r, r);
                o = Label_map_connect[i].pos;
                QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                qname = QString(QString::fromLocal8Bit(Label_map_connect[i].name.c_str()));
                painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
            }
        }
        QPen pen;
        pen.setBrush(QBrush(Qt::red));//设置笔刷

        pen.setWidth(2);

        pen.setBrush(Qt::blue);
         painter.setPen(QPen(Qt::black, 1));
        string str = "表示不同的连通分支";
        painter.drawText(QPoint(70, 40), QString(QString::fromLocal8Bit(str.c_str())) );
        QPen temp_pen2;
        temp_pen2.setWidth(3);
        temp_pen2.setColor(Qt::blue);
        painter.setPen(temp_pen2);
        painter.drawEllipse(QPoint(50, 35), 6, 6);
        temp_pen2.setWidth(3);
        temp_pen2.setColor(Qt::cyan);
        painter.setPen(temp_pen2);
        painter.drawEllipse(QPoint(30, 35), 6, 6);
        temp_pen2.setWidth(3);
        temp_pen2.setColor(Qt::red);
        painter.setPen(temp_pen2);
        painter.drawEllipse(QPoint(10, 35), 6, 6);
    }
    //无向带权
    if(is_create&&is_undirectedweightedgraph)
    {
        //绘制基本路线
        painter.setPen(QPen(Qt::green,2));
        painter.drawLines(undirectedweightedgraph->line);

    //绘制地图
    painter.setPen(QPen(Qt::black,2));
    QPoint o;
    QString qname;

    for (int i = 0; i < undirectedweightedgraph->vexnum; ++i)
    {
        painter.drawEllipse(undirectedweightedgraph->cityMap[i].pos, r, r);
        o = undirectedweightedgraph->cityMap[i].pos;
        QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
        qname = QString(QString::fromLocal8Bit(undirectedweightedgraph->cityMap[i].name.c_str()));
        painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));

    }
    qDebug()<< undirectedweightedgraph->points_edge.size();
     painter.setPen(QPen(Qt::cyan,2));
    for (int i = 0; i < undirectedweightedgraph->points_edge.size(); ++i)
    {

        painter.drawRect(undirectedweightedgraph->points_edge[i].location.rx(),undirectedweightedgraph->points_edge[i].location.ry(), 13, 13);

        o = undirectedweightedgraph->points_edge[i].location;
        QRect rect(o.x(), o.y(), 2*7, 2*7);
        qname = QString(QString::fromLocal8Bit(undirectedweightedgraph->points_edge[i].weight.c_str()));
        painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));

    }

    //绘制左上角的提示信息
    QPen pen;
    pen.setBrush(QBrush(Qt::red));//设置笔刷
    QVector<qreal> dashes0;
    qreal space0 = 10;
    dashes0 << 5 << space0 << 5 <<space0;
    pen.setDashPattern(dashes0);
    pen.setWidth(2);

    painter.setPen(QPen(Qt::green, 2));
    painter.drawLine(QPoint(10, 60), QPoint(80, 60));
    painter.setPen(QPen(Qt::black, 1));

   string  str = "路线";
    painter.drawText(QPoint(90, 60), QString(QString::fromLocal8Bit(str.c_str())));

    QPen temp_pen2;
    temp_pen2.setWidth(2);
    temp_pen2.setColor(Qt::cyan);
    painter.setPen(temp_pen2);

    painter.drawRect(60, 75, 13, 13);
    painter.setPen(QPen(Qt::black, 1));
    str = "边的权重";
    painter.drawText(QPoint(90, 80), QString(QString::fromLocal8Bit(str.c_str())));


    }
    if(is_traverse_dfs&&is_undirectedweightedgraph)
    {
        QPen pen;
        pen.setBrush(QBrush(Qt::red));//设置笔刷
        QVector<qreal> dashes0;
        qreal space0 = 10;
        dashes0 << 5 << space0 << 5 <<space0;
        pen.setDashPattern(dashes0);
        pen.setWidth(2);
//        painter.setPen(pen);
//        painter.drawLine(QPoint(10, 100), QPoint(80, 100));
        pen.setBrush(Qt::red);
        painter.setPen(pen);
        painter.drawLine(QPoint(10, 40), QPoint(80, 40));
//        painter.setPen(QPen(Qt::green, 2));
//        painter.drawLine(QPoint(10, 140), QPoint(80, 140));
        painter.setPen(QPen(Qt::black, 1));
        string str("DFS路线");
        painter.drawText(QPoint(90, 40), QString(QString::fromLocal8Bit(str.c_str())) );
                        QPen pen_dfs;

//                        painter.drawLines(line_dfs2);
                        QPoint o;
                        QString qname;
                        for(int i = 0 ; i< line_dfs2.size() ; i++)
                                {
                            pen_dfs.setBrush(QBrush(Qt::red));//设置笔刷
                            QVector<qreal> dashes;
                            qreal space = 12;
                            dashes << 5 << space << 5 <<space;
                            pen_dfs.setDashPattern(dashes);
                            pen_dfs.setWidth(2);
                            painter.setPen(pen_dfs);
                                    float x1 = line_dfs2[i].x1();       //lastPoint 起点
                                    float y1 = line_dfs2[i].y1();
                                    float x2 = line_dfs2[i].x2();  //endPoint 终点
                                    float y2 = line_dfs2[i].y2();
//                                    float x0 = (x1+x2)/2;
//                                    float y0 = (y1+y2)/2;
                                    float x0 = (2*x1)/3 + x2/3;
                                    float y0 = (2*y1)/3 + y2/3;
                                    float l = 10.0;                   //箭头的那长度
                                    float a = 0.5;                       //箭头与线段角度
                                    float x3 = x0 - l * cos(atan2((y0 - y1) , (x0 - x1)) - a);
                                     float y3 = y0 - l * sin(atan2((y0 - y1) , (x0 - x1)) - a);
                                     float x4 = x0 - l * sin(atan2((x0 - x1) , (y0 - y1)) - a);
                                     float y4 = y0 - l * cos(atan2((x0 - x1) , (y0 - y1)) - a);
                                    painter.drawLine(x0,y0,x3,y3);
                                    painter.drawLine(x0,y0,x4,y4);
                                    painter.drawLine(line_dfs2[i].p1(),line_dfs2[i].p2());
                                    for (int j = 0; j < undirectedweightedgraph->points_edge.size(); ++j)
                                    {
                                        QPen temp_pen;
                                        temp_pen.setBrush(Qt::red);

                                        painter.setPen(temp_pen);
                                        if(undirectedweightedgraph->cityMap[undirectedweightedgraph->points_edge[j].from].pos == line_dfs2[i].p1() &&
                                            undirectedweightedgraph->cityMap[undirectedweightedgraph->points_edge[j].to].pos == line_dfs2[i].p2()    )
                                        {
                                        painter.drawRect(undirectedweightedgraph->points_edge[j].location.rx(),undirectedweightedgraph->points_edge[j].location.ry(), 13, 13);

                                        o = undirectedweightedgraph->points_edge[j].location;
                                        QRect rect(o.x(), o.y(), 2*7, 2*7);
                                        qname = QString(QString::fromLocal8Bit(undirectedweightedgraph->points_edge[j].weight.c_str()));
                                        painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                                        }
                                        if(undirectedweightedgraph->cityMap[undirectedweightedgraph->points_edge[j].from].pos == line_dfs2[i].p2() &&
                                            undirectedweightedgraph->cityMap[undirectedweightedgraph->points_edge[j].to].pos == line_dfs2[i].p1()    )
                                        {
                                        painter.drawRect(undirectedweightedgraph->points_edge[j].location.rx(),undirectedweightedgraph->points_edge[j].location.ry(), 13, 13);

                                        o = undirectedweightedgraph->points_edge[j].location;
                                        QRect rect(o.x(), o.y(), 2*7, 2*7);
                                        qname = QString(QString::fromLocal8Bit(undirectedweightedgraph->points_edge[j].weight.c_str()));
                                        painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                                        }

                                    }
                                }

                        if(!undirectedweightedgraph->points_dfs_light.empty())
                        {
                            Map temp_map = undirectedweightedgraph->points_dfs_light[0];
                            QPen temp_pen;
                            temp_pen.setWidth(5);
                            temp_pen.setColor(Qt::red);
                            painter.setPen(temp_pen);
                            painter.drawEllipse(temp_map.pos, r, r);
                            o = temp_map.pos;
                            QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                            qname = QString(QString::fromLocal8Bit(temp_map.name.c_str()));
                            painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                            undirectedweightedgraph->points_dfs_light.erase(undirectedweightedgraph->points_dfs_light.begin());
                        }
                        painter.setPen(Qt::red);

                        for (int i = 0; i < point_dfs2.size(); ++i)
                        {
                            painter.drawEllipse(point_dfs2[i].pos, r, r);
                            o = point_dfs2[i].pos;
                            QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                            qname = QString(QString::fromLocal8Bit(point_dfs2[i].name.c_str()));
                            painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));



                        }
                        painter.setPen(QPen(Qt::black, 1));
                        str = "此时DFS选中的顶点（栈顶的顶点）";
                        painter.drawText(QPoint(200, 40), QString(QString::fromLocal8Bit(str.c_str())) );

                        QPen temp_pen2;
                        temp_pen2.setWidth(3);
                        temp_pen2.setColor(Qt::red);
                        painter.setPen(temp_pen2);
                        painter.drawEllipse(QPoint(170, 35), 6, 6);

    }
    if (is_traverse_bfs&&is_undirectedweightedgraph)
    {
        QPen pen;
               pen.setBrush(QBrush(Qt::blue));//设置笔刷
               QVector<qreal> dashes0;
               qreal space0 = 10;
               dashes0 << 5 << space0 << 5 <<space0;
               pen.setDashPattern(dashes0);
               pen.setWidth(2);
               painter.setPen(pen);
               painter.drawLine(QPoint(10, 20), QPoint(80, 20));

               painter.setPen(QPen(Qt::black, 1));

               string str = "BFS路线";
               painter.drawText(QPoint(90, 20), QString(QString::fromLocal8Bit(str.c_str())));


               //绘制路线
                   QPen pen_bfs;
                   pen_bfs.setBrush(QBrush(Qt::blue));
                   QVector<qreal> dashes2;
                   qreal space2 = 12;
                   dashes2 << 5 << space2 << 5 <<space2;
                   pen_bfs.setDashPattern(dashes2);
                   pen_bfs.setWidth(2);
                   painter.setPen(pen_bfs);

       //            painter.drawLines(line_bfs2);
                   QPoint o;
                   QString qname;
                   for(int i = 0 ; i< line_bfs2.size() ; i++)
                           { pen_bfs.setBrush(QBrush(Qt::blue));
                        QVector<qreal> dashes2;
                        qreal space2 = 12;
                        dashes2 << 5 << space2 << 5 <<space2;
                         pen_bfs.setDashPattern(dashes2);
                        pen_bfs.setWidth(2);
                        painter.setPen(pen_bfs);
                               float x1 = line_bfs2[i].x1();       //lastPoint 起点

                               float y1 = line_bfs2[i].y1();

                               float x2 = line_bfs2[i].x2();  //endPoint 终点

                               float y2 = line_bfs2[i].y2();
       //                        float x0 = (x1+x2)/2;
       //                        float y0 = (y1+y2)/2;
                               float x0 = (2*x1)/3 + x2/3;
                               float y0 = (2*y1)/3 + y2/3;

                               float l = 10.0;                   //箭头的那长度

                               float a = 0.5;                       //箭头与线段角度


                                                   float x3 = x0 - l * cos(atan2((y0 - y1) , (x0 - x1)) - a);

                                                   float y3 = y0 - l * sin(atan2((y0 - y1) , (x0 - x1)) - a);

                                                   float x4 = x0 - l * sin(atan2((x0 - x1) , (y0 - y1)) - a);

                                                   float y4 = y0 - l * cos(atan2((x0 - x1) , (y0 - y1)) - a);


                               painter.drawLine(x0,y0,x3,y3);

                               painter.drawLine(x0,y0,x4,y4);

                               painter.drawLine(line_bfs2[i].p1(),line_bfs2[i].p2());
                               for (int j = 0; j < undirectedweightedgraph->points_edge.size(); ++j)
                               {
                                   QPen temp_pen;
                                   temp_pen.setBrush(Qt::blue);

                                   painter.setPen(temp_pen);
                                   if(undirectedweightedgraph->cityMap[undirectedweightedgraph->points_edge[j].from].pos == line_bfs2[i].p1() &&
                                       undirectedweightedgraph->cityMap[undirectedweightedgraph->points_edge[j].to].pos == line_bfs2[i].p2()    )
                                   {
                                   painter.drawRect(undirectedweightedgraph->points_edge[j].location.rx(),undirectedweightedgraph->points_edge[j].location.ry(), 13, 13);

                                   o = undirectedweightedgraph->points_edge[j].location;
                                   QRect rect(o.x(), o.y(), 2*7, 2*7);
                                   qname = QString(QString::fromLocal8Bit(undirectedweightedgraph->points_edge[j].weight.c_str()));
                                   painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                                   }
                                   if(undirectedweightedgraph->cityMap[undirectedweightedgraph->points_edge[j].from].pos == line_bfs2[i].p2() &&
                                       undirectedweightedgraph->cityMap[undirectedweightedgraph->points_edge[j].to].pos == line_bfs2[i].p1()    )
                                   {
                                   painter.drawRect(undirectedweightedgraph->points_edge[j].location.rx(),undirectedweightedgraph->points_edge[j].location.ry(), 13, 13);

                                   o = undirectedweightedgraph->points_edge[j].location;
                                   QRect rect(o.x(), o.y(), 2*7, 2*7);
                                   qname = QString(QString::fromLocal8Bit(undirectedweightedgraph->points_edge[j].weight.c_str()));
                                   painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                                   }

                               }

                           }

               //绘制点



       //        Map temp_map = point_bfs2.back();
               painter.setPen(Qt::blue);
               for (int i = 0; i < point_bfs2.size(); ++i)
               {
                   painter.drawEllipse(point_bfs2[i].pos, r, r);
                   o = point_bfs2[i].pos;
                   QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                   qname = QString(QString::fromLocal8Bit(point_bfs2[i].name.c_str()));
                   painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));


               }
              if(!undirectedweightedgraph->points_bfs_light.empty())
              {
                  Map temp_map = undirectedweightedgraph->points_bfs_light[0];
                  QPen temp_pen;
                  temp_pen.setWidth(5);
                  temp_pen.setColor(Qt::blue);
                  painter.setPen(temp_pen);
                  painter.drawEllipse(temp_map.pos, r, r);
                  o = temp_map.pos;
                  QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                  qname = QString(QString::fromLocal8Bit(temp_map.name.c_str()));
                  painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                  undirectedweightedgraph->points_bfs_light.erase(undirectedweightedgraph->points_bfs_light.begin());
                  qDebug()<< qname;
              }


              painter.setPen(QPen(Qt::black, 1));

              str = "此时BFS选中的顶点（队首的顶点）";
              painter.drawText(QPoint(200, 20), QString(QString::fromLocal8Bit(str.c_str())));
                  QPen temp_pen2;
                  temp_pen2.setWidth(3);
                  temp_pen2.setColor(Qt::blue);
                  painter.setPen(temp_pen2);
                  painter.drawEllipse(QPoint(170, 15), 6, 6);

    }
    if(is_isedge&&is_undirectedweightedgraph)
    {
        QPen pen;
        pen.setBrush(QBrush(Qt::red));//设置笔刷

        pen.setWidth(2);

        pen.setBrush(Qt::blue);
        painter.setPen(pen);
        painter.drawLine(QPoint(10, 40), QPoint(80, 40));
        painter.setPen(QPen(Qt::black, 1));
        string str("表示存在这条边");
        painter.drawText(QPoint(90, 40), QString(QString::fromLocal8Bit(str.c_str())) );


        painter.setPen(QPen(Qt::blue,2));
        painter.drawLine(isedge_line);
        QPoint o;
        QString qname;
        for (int j = 0; j < undirectedweightedgraph->points_edge.size(); ++j)
        {
            QPen temp_pen;
            temp_pen.setBrush(Qt::blue);

            painter.setPen(temp_pen);
            if(undirectedweightedgraph->cityMap[undirectedweightedgraph->points_edge[j].from].pos == isedge_line.p1() &&
                undirectedweightedgraph->cityMap[undirectedweightedgraph->points_edge[j].to].pos == isedge_line.p2()    )
            {
            painter.drawRect(undirectedweightedgraph->points_edge[j].location.rx(),undirectedweightedgraph->points_edge[j].location.ry(), 13, 13);

            o = undirectedweightedgraph->points_edge[j].location;
            QRect rect(o.x(), o.y(), 2*7, 2*7);
            qname = QString(QString::fromLocal8Bit(undirectedweightedgraph->points_edge[j].weight.c_str()));
            painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
            }
            if(undirectedweightedgraph->cityMap[undirectedweightedgraph->points_edge[j].from].pos == isedge_line.p2() &&
                undirectedweightedgraph->cityMap[undirectedweightedgraph->points_edge[j].to].pos == isedge_line.p1()    )
            {
            painter.drawRect(undirectedweightedgraph->points_edge[j].location.rx(),undirectedweightedgraph->points_edge[j].location.ry(), 13, 13);

            o = undirectedweightedgraph->points_edge[j].location;
            QRect rect(o.x(), o.y(), 2*7, 2*7);
            qname = QString(QString::fromLocal8Bit(undirectedweightedgraph->points_edge[j].weight.c_str()));
            painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
            }

        }
        painter.setPen(QPen(Qt::black,2));
        for (int i = 0; i < undirectedweightedgraph->vexnum; ++i)
        {
            painter.drawEllipse(undirectedweightedgraph->cityMap[i].pos, r, r);
            o = undirectedweightedgraph->cityMap[i].pos;
            QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
            qname = QString(QString::fromLocal8Bit(undirectedweightedgraph->cityMap[i].name.c_str()));
            painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));

        }
        is_isedge = false;
    }
    if(is_indegrees&&is_undirectedweightedgraph)
    {
        QPen pen;
        pen.setBrush(QBrush(Qt::red));//设置笔刷

        pen.setWidth(2);

        pen.setBrush(Qt::blue);
        painter.setPen(pen);
        painter.drawLine(QPoint(10, 40), QPoint(80, 40));

        painter.setPen(QPen(Qt::black, 1));
        string str("表示进入边");
        painter.drawText(QPoint(90, 40), QString(QString::fromLocal8Bit(str.c_str())) );


        painter.setPen(QPen(Qt::blue,2));
        painter.drawLines(undirectedweightedgraph->line_indegrees);
        QPoint o;
        QString qname;

        for(int i = 0 ; i< undirectedweightedgraph->line_indegrees.size() ; i++)
        {
            for (int j = 0; j < undirectedweightedgraph->points_edge.size(); ++j)
            {
                QPen temp_pen;
                temp_pen.setBrush(Qt::blue);

                painter.setPen(temp_pen);
                if(undirectedweightedgraph->cityMap[undirectedweightedgraph->points_edge[j].from].pos == undirectedweightedgraph->line_indegrees[i].p1() &&
                    undirectedweightedgraph->cityMap[undirectedweightedgraph->points_edge[j].to].pos == undirectedweightedgraph->line_indegrees[i].p2()    )
                {
                painter.drawRect(undirectedweightedgraph->points_edge[j].location.rx(),undirectedweightedgraph->points_edge[j].location.ry(), 13, 13);

                o = undirectedweightedgraph->points_edge[j].location;
                QRect rect(o.x(), o.y(), 2*7, 2*7);
                qname = QString(QString::fromLocal8Bit(undirectedweightedgraph->points_edge[j].weight.c_str()));
                painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                }
                if(undirectedweightedgraph->cityMap[undirectedweightedgraph->points_edge[j].from].pos == undirectedweightedgraph->line_indegrees[i].p2() &&
                    undirectedweightedgraph->cityMap[undirectedweightedgraph->points_edge[j].to].pos == undirectedweightedgraph->line_indegrees[i].p1()    )
                {
                painter.drawRect(undirectedweightedgraph->points_edge[j].location.rx(),undirectedweightedgraph->points_edge[j].location.ry(), 13, 13);

                o = undirectedweightedgraph->points_edge[j].location;
                QRect rect(o.x(), o.y(), 2*7, 2*7);
                qname = QString(QString::fromLocal8Bit(undirectedweightedgraph->points_edge[j].weight.c_str()));
                painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                }

            }
        }
        painter.setPen(QPen(Qt::black,2));

        for (int i = 0; i < undirectedweightedgraph->vexnum; ++i)
        {
            painter.drawEllipse(undirectedweightedgraph->cityMap[i].pos, r, r);
            o = undirectedweightedgraph->cityMap[i].pos;
            QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
            qname = QString(QString::fromLocal8Bit(undirectedweightedgraph->cityMap[i].name.c_str()));
            painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));

        }

        is_indegrees = false;
    }
    if(is_outdegrees&&is_undirectedweightedgraph)
    {
        QPen pen;
        pen.setBrush(QBrush(Qt::red));//设置笔刷

        pen.setWidth(2);

        pen.setBrush(Qt::red);
        painter.setPen(pen);
        painter.drawLine(QPoint(10, 40), QPoint(80, 40));

        painter.setPen(QPen(Qt::black, 1));
        string str("表示出边");
        painter.drawText(QPoint(90, 40), QString(QString::fromLocal8Bit(str.c_str())) );


        painter.setPen(QPen(Qt::red,2));
        painter.drawLines(undirectedweightedgraph->line_outdegrees);
        QPoint o;
        QString qname;
        qDebug()<<"7777";
        for(int i = 0 ; i< undirectedweightedgraph->line_outdegrees.size() ; i++)
        {
            for (int j = 0; j < undirectedweightedgraph->points_edge.size(); ++j)
            {
                QPen temp_pen;
                temp_pen.setBrush(Qt::red);

                painter.setPen(temp_pen);
                if(undirectedweightedgraph->cityMap[undirectedweightedgraph->points_edge[j].from].pos == undirectedweightedgraph->line_outdegrees[i].p1() &&
                    undirectedweightedgraph->cityMap[undirectedweightedgraph->points_edge[j].to].pos == undirectedweightedgraph->line_outdegrees[i].p2()    )
                {
                painter.drawRect(undirectedweightedgraph->points_edge[j].location.rx(),undirectedweightedgraph->points_edge[j].location.ry(), 13, 13);

                o = undirectedweightedgraph->points_edge[j].location;
                QRect rect(o.x(), o.y(), 2*7, 2*7);
                qname = QString(QString::fromLocal8Bit(undirectedweightedgraph->points_edge[j].weight.c_str()));
                painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                }
                if(undirectedweightedgraph->cityMap[undirectedweightedgraph->points_edge[j].from].pos == undirectedweightedgraph->line_outdegrees[i].p2() &&
                    undirectedweightedgraph->cityMap[undirectedweightedgraph->points_edge[j].to].pos == undirectedweightedgraph->line_outdegrees[i].p1()    )
                {
                painter.drawRect(undirectedweightedgraph->points_edge[j].location.rx(),undirectedweightedgraph->points_edge[j].location.ry(), 13, 13);

                o = undirectedweightedgraph->points_edge[j].location;
                QRect rect(o.x(), o.y(), 2*7, 2*7);
                qname = QString(QString::fromLocal8Bit(undirectedweightedgraph->points_edge[j].weight.c_str()));
                painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                }

            }
        }
        qDebug()<<"8888";
        painter.setPen(QPen(Qt::black,2));


        for (int i = 0; i < undirectedweightedgraph->vexnum; ++i)
        {
            painter.drawEllipse(undirectedweightedgraph->cityMap[i].pos, r, r);
            o = undirectedweightedgraph->cityMap[i].pos;
            QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
            qname = QString(QString::fromLocal8Bit(undirectedweightedgraph->cityMap[i].name.c_str()));
            painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));

        }
        is_outdegrees = false;
    }
    if(is_isconnect&&is_undirectedweightedgraph)
    {
        QPen pen;
        pen.setBrush(QBrush(Qt::red));//设置笔刷

        pen.setWidth(2);

        pen.setBrush(Qt::blue);
        painter.setPen(pen);
        painter.drawLine(QPoint(10, 40), QPoint(80, 40));

        painter.setPen(QPen(Qt::black, 1));
        string str("表示可以连通的边");
        painter.drawText(QPoint(90, 40), QString(QString::fromLocal8Bit(str.c_str())) );

        painter.setPen(QPen(Qt::black, 1));
        str = "表示可以连通的顶点";
        painter.drawText(QPoint(230, 40), QString(QString::fromLocal8Bit(str.c_str())) );
        QPen temp_pen2;
        temp_pen2.setWidth(3);
        temp_pen2.setColor(Qt::blue);
        painter.setPen(temp_pen2);
        painter.drawEllipse(QPoint(210, 35), 6, 6);



        //绘制路线

                    QPen pen_bfs;
                    pen_bfs.setBrush(QBrush(Qt::blue));

                    pen_bfs.setWidth(2);
                    painter.setPen(pen_bfs);

                   painter.drawLines(undirectedweightedgraph->line_bfs);
                   QPoint o;
                   QString qname;
                   for(int i = 0 ; i< undirectedweightedgraph->line_bfs.size() ; i++)
                   {
                       for (int j = 0; j < undirectedweightedgraph->points_edge.size(); ++j)
                       {
                           QPen temp_pen;
                           temp_pen.setBrush(Qt::blue);

                           painter.setPen(temp_pen);
                           if(undirectedweightedgraph->cityMap[undirectedweightedgraph->points_edge[j].from].pos == undirectedweightedgraph->line_bfs[i].p1() &&
                               undirectedweightedgraph->cityMap[undirectedweightedgraph->points_edge[j].to].pos == undirectedweightedgraph->line_bfs[i].p2()    )
                           {
                           painter.drawRect(undirectedweightedgraph->points_edge[j].location.rx(),undirectedweightedgraph->points_edge[j].location.ry(), 13, 13);

                           o = undirectedweightedgraph->points_edge[j].location;
                           QRect rect(o.x(), o.y(), 2*7, 2*7);
                           qname = QString(QString::fromLocal8Bit(undirectedweightedgraph->points_edge[j].weight.c_str()));
                           painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                           }
                           if(undirectedweightedgraph->cityMap[undirectedweightedgraph->points_edge[j].from].pos == undirectedweightedgraph->line_bfs[i].p2() &&
                               undirectedweightedgraph->cityMap[undirectedweightedgraph->points_edge[j].to].pos == undirectedweightedgraph->line_bfs[i].p1()    )
                           {
                           painter.drawRect(undirectedweightedgraph->points_edge[j].location.rx(),undirectedweightedgraph->points_edge[j].location.ry(), 13, 13);

                           o = undirectedweightedgraph->points_edge[j].location;
                           QRect rect(o.x(), o.y(), 2*7, 2*7);
                           qname = QString(QString::fromLocal8Bit(undirectedweightedgraph->points_edge[j].weight.c_str()));
                           painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                           }

                       }
                   }
                   painter.setPen(Qt::blue);

                   for (int i = 0; i < undirectedweightedgraph->points_isconnect.size(); ++i)
                   {
                       painter.drawEllipse(undirectedweightedgraph->points_isconnect[i].pos, r, r);
                       o = undirectedweightedgraph->points_isconnect[i].pos;
                       QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                       qname = QString(QString::fromLocal8Bit(undirectedweightedgraph->points_isconnect[i].name.c_str()));
                       painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                       qDebug()<<i;

                   }
                   is_isconnect = false;
    }
    if(is_labelconnect&&is_undirectedweightedgraph)
    {
        QPoint o;
         QString qname;
        for(int i = 0 ; i < Label_map_connect.size() ; i++)
        {
            if(Label_map_connect[i].label_c == 1)
            {

                QPen temp_pen2;
                temp_pen2.setWidth(3);
                temp_pen2.setColor(Qt::blue);
                painter.setPen(temp_pen2);

                 painter.drawEllipse(Label_map_connect[i].pos, r, r);
                 o = Label_map_connect[i].pos;
                 QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                 qname = QString(QString::fromLocal8Bit(Label_map_connect[i].name.c_str()));
                 painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
            }
            if(Label_map_connect[i].label_c == 2)
            {
                QPen temp_pen2;
                temp_pen2.setWidth(3);
                temp_pen2.setColor(Qt::red);
                painter.setPen(temp_pen2);
                painter.drawEllipse(Label_map_connect[i].pos, r, r);
                o = Label_map_connect[i].pos;
                QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                qname = QString(QString::fromLocal8Bit(Label_map_connect[i].name.c_str()));
                painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
            }
            if(Label_map_connect[i].label_c == 3)
            {
                QPen temp_pen2;
                temp_pen2.setWidth(3);
                temp_pen2.setColor(Qt::cyan);
                painter.setPen(temp_pen2);
                painter.drawEllipse(Label_map_connect[i].pos, r, r);
                o = Label_map_connect[i].pos;
                QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                qname = QString(QString::fromLocal8Bit(Label_map_connect[i].name.c_str()));
                painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
            }
        }
        QPen pen;
        pen.setBrush(QBrush(Qt::red));//设置笔刷

        pen.setWidth(2);

        pen.setBrush(Qt::blue);
         painter.setPen(QPen(Qt::black, 1));
        string str = "表示不同的连通分支";
        painter.drawText(QPoint(70, 40), QString(QString::fromLocal8Bit(str.c_str())) );
        QPen temp_pen2;
        temp_pen2.setWidth(3);
        temp_pen2.setColor(Qt::blue);
        painter.setPen(temp_pen2);
        painter.drawEllipse(QPoint(50, 35), 6, 6);
        temp_pen2.setWidth(3);
        temp_pen2.setColor(Qt::cyan);
        painter.setPen(temp_pen2);
        painter.drawEllipse(QPoint(30, 35), 6, 6);
        temp_pen2.setWidth(3);
        temp_pen2.setColor(Qt::red);
        painter.setPen(temp_pen2);
        painter.drawEllipse(QPoint(10, 35), 6, 6);
    }
    if(is_prim&&is_undirectedweightedgraph)
    {
        QPen pen;
               pen.setBrush(QBrush(Qt::blue));//设置笔刷
               QVector<qreal> dashes0;
               qreal space0 = 10;
               dashes0 << 5 << space0 << 5 <<space0;
               pen.setDashPattern(dashes0);
               pen.setWidth(2);
               painter.setPen(pen);
               painter.drawLine(QPoint(10, 20), QPoint(80, 20));

               painter.setPen(QPen(Qt::black, 1));

               string str = "最小生成树路线";
               painter.drawText(QPoint(90, 20), QString(QString::fromLocal8Bit(str.c_str())));


               //绘制路线
                   QPen pen_prim;
                   pen_prim.setBrush(QBrush(Qt::blue));

                   pen_prim.setWidth(2);
                   painter.setPen(pen_prim);

//                   painter.drawLines(undirectedweightedgraph->line_prim);
                   QPoint o;
                   QString qname;
                   for(int i = 0 ; i< line_prim2.size() ; i++)
                           { pen_prim.setBrush(QBrush(Qt::blue));

                        pen_prim.setWidth(2);
                        painter.setPen(pen_prim);
                               painter.drawLine(line_prim2[i].p1(),line_prim2[i].p2());
                               for (int j = 0; j < undirectedweightedgraph->points_edge.size(); ++j)
                               {
                                   QPen temp_pen;
                                   temp_pen.setBrush(Qt::blue);

                                   painter.setPen(temp_pen);
                                   if(undirectedweightedgraph->cityMap[undirectedweightedgraph->points_edge[j].from].pos == line_prim2[i].p1() &&
                                       undirectedweightedgraph->cityMap[undirectedweightedgraph->points_edge[j].to].pos == line_prim2[i].p2()    )
                                   {
                                   painter.drawRect(undirectedweightedgraph->points_edge[j].location.rx(),undirectedweightedgraph->points_edge[j].location.ry(), 13, 13);

                                   o = undirectedweightedgraph->points_edge[j].location;
                                   QRect rect(o.x(), o.y(), 2*7, 2*7);
                                   qname = QString(QString::fromLocal8Bit(undirectedweightedgraph->points_edge[j].weight.c_str()));
                                   painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                                   }
                                   if(undirectedweightedgraph->cityMap[undirectedweightedgraph->points_edge[j].from].pos == line_prim2[i].p2() &&
                                       undirectedweightedgraph->cityMap[undirectedweightedgraph->points_edge[j].to].pos == line_prim2[i].p1()    )
                                   {
                                   painter.drawRect(undirectedweightedgraph->points_edge[j].location.rx(),undirectedweightedgraph->points_edge[j].location.ry(), 13, 13);

                                   o = undirectedweightedgraph->points_edge[j].location;
                                   QRect rect(o.x(), o.y(), 2*7, 2*7);
                                   qname = QString(QString::fromLocal8Bit(undirectedweightedgraph->points_edge[j].weight.c_str()));
                                   painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                                   }

                               }

                           }

               //绘制点



       //        Map temp_map = point_bfs2.back();
               painter.setPen(Qt::blue);
               for (int i = 0; i < point_prim2.size(); ++i)
               {
                   painter.drawEllipse(point_prim2[i].pos, r, r);
                   o = point_prim2[i].pos;
                   QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                   qname = QString(QString::fromLocal8Bit(point_prim2[i].name.c_str()));
                   painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));


               }

               if(!undirectedweightedgraph->line_prim_light.empty())
               {

                   QPen temp_pen;
                   temp_pen.setWidth(3);
                   temp_pen.setColor(Qt::blue);
                   painter.setPen(temp_pen);
                   painter.drawLine(undirectedweightedgraph->line_prim_light[0]);
                   undirectedweightedgraph->line_prim_light.erase(undirectedweightedgraph->line_prim_light.begin());

               }

              painter.setPen(QPen(Qt::black, 1));

                 str = "已经加入集合的顶点";
              painter.drawText(QPoint(200, 60), QString(QString::fromLocal8Bit(str.c_str())));
                  QPen temp_pen2;
                  temp_pen2.setWidth(2);
                  temp_pen2.setColor(Qt::blue);
                  painter.setPen(temp_pen2);
                  painter.drawEllipse(QPoint(170, 55), 6, 6);
    }

    //有向带权
    if(is_create&&is_directedweightedgraph)
    {
        //绘制基本路线
        painter.setPen(QPen(Qt::green,2));
//        painter.drawLines(directedweightedgraph->line);
        for(int i = 0 ; i< directedweightedgraph->line.size() ; i++)
                {
                    float x1 = directedweightedgraph->line[i].x1();       //lastPoint 起点
                    float y1 = directedweightedgraph->line[i].y1();
                    float x2 = directedweightedgraph->line[i].x2();  //endPoint 终点
                    float y2 = directedweightedgraph->line[i].y2();
                    float x0 = (2*x1)/3 + x2/3;
                    float y0 = (2*y1)/3 + y2/3;
                    float l = 10.0;                   //箭头的那长度
                    float a = 0.5;                       //箭头与线段角度
                  float x3 = x0 - l * cos(atan2((y0 - y1) , (x0 - x1)) - a);
                  float y3 = y0 - l * sin(atan2((y0 - y1) , (x0 - x1)) - a);
                  float x4 = x0 - l * sin(atan2((x0 - x1) , (y0 - y1)) - a);
                   float y4 = y0 - l * cos(atan2((x0 - x1) , (y0 - y1)) - a);
                    painter.drawLine(x0,y0,x3,y3);
                    painter.drawLine(x0,y0,x4,y4);
                    painter.drawLine(directedweightedgraph->line[i].p1(),directedweightedgraph->line[i].p2());

                }

    //绘制地图
    painter.setPen(QPen(Qt::black,2));
    QPoint o;
    QString qname;

    for (int i = 0; i < directedweightedgraph->vexnum; ++i)
    {
        painter.drawEllipse(directedweightedgraph->cityMap[i].pos, r, r);
        o = directedweightedgraph->cityMap[i].pos;
        QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
        qname = QString(QString::fromLocal8Bit(directedweightedgraph->cityMap[i].name.c_str()));
        painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));

    }

     painter.setPen(QPen(Qt::cyan,2));
    for (int i = 0; i < directedweightedgraph->points_edge.size(); ++i)
    {
        painter.drawRect(directedweightedgraph->points_edge[i].location.rx(),directedweightedgraph->points_edge[i].location.ry(), 13, 13);
        o = directedweightedgraph->points_edge[i].location;
        QRect rect(o.x(), o.y(), 2*7, 2*7);
        qname = QString(QString::fromLocal8Bit(directedweightedgraph->points_edge[i].weight.c_str()));
        painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));

    }
    //绘制左上角的提示信息
    QPen pen;
    pen.setBrush(QBrush(Qt::red));//设置笔刷
    QVector<qreal> dashes0;
    qreal space0 = 10;
    dashes0 << 5 << space0 << 5 <<space0;
    pen.setDashPattern(dashes0);
    pen.setWidth(2);
    painter.setPen(QPen(Qt::green, 2));
    painter.drawLine(QPoint(10, 60), QPoint(80, 60));
    painter.setPen(QPen(Qt::black, 1));
   string  str = "路线";
    painter.drawText(QPoint(90, 60), QString(QString::fromLocal8Bit(str.c_str())));
    QPen temp_pen2;
    temp_pen2.setWidth(2);
    temp_pen2.setColor(Qt::cyan);
    painter.setPen(temp_pen2);

    painter.drawRect(60, 75, 13, 13);
    painter.setPen(QPen(Qt::black, 1));
    str = "边的权重";
    painter.drawText(QPoint(90, 80), QString(QString::fromLocal8Bit(str.c_str())));
    }
    if(is_traverse_bfs&&is_directedweightedgraph)
    {
        QPen pen;
               pen.setBrush(QBrush(Qt::blue));//设置笔刷
               QVector<qreal> dashes0;
               qreal space0 = 10;
               dashes0 << 5 << space0 << 5 <<space0;
               pen.setDashPattern(dashes0);
               pen.setWidth(2);
               painter.setPen(pen);
               painter.drawLine(QPoint(10, 20), QPoint(80, 20));
               painter.setPen(QPen(Qt::black, 1));
               string str = "BFS路线";
               painter.drawText(QPoint(90, 20), QString(QString::fromLocal8Bit(str.c_str())));
               //绘制路线
                   QPen pen_bfs;
                   pen_bfs.setBrush(QBrush(Qt::blue));
                   QVector<qreal> dashes2;
                   qreal space2 = 12;
                   dashes2 << 5 << space2 << 5 <<space2;
                   pen_bfs.setDashPattern(dashes2);
                   pen_bfs.setWidth(2);
                   painter.setPen(pen_bfs);
       //            painter.drawLines(line_bfs2);
                   QPoint o;
                   QString qname;
                   for(int i = 0 ; i< line_bfs2.size() ; i++)
                           { pen_bfs.setBrush(QBrush(Qt::blue));
                        QVector<qreal> dashes2;
                        qreal space2 = 12;
                        dashes2 << 5 << space2 << 5 <<space2;
                         pen_bfs.setDashPattern(dashes2);
                        pen_bfs.setWidth(2);
                        painter.setPen(pen_bfs);
                               float x1 = line_bfs2[i].x1();       //lastPoint 起点
                               float y1 = line_bfs2[i].y1();
                               float x2 = line_bfs2[i].x2();  //endPoint 终点
                               float y2 = line_bfs2[i].y2();
                               float x0 = (2*x1)/3 + x2/3;
                               float y0 = (2*y1)/3 + y2/3;
                               float l = 10.0;                   //箭头的那长度
                              float a = 0.5;                       //箭头与线段角
                               float x3 = x0 - l * cos(atan2((y0 - y1) , (x0 - x1)) - a);
                               float y3 = y0 - l * sin(atan2((y0 - y1) , (x0 - x1)) - a);
                               float x4 = x0 - l * sin(atan2((x0 - x1) , (y0 - y1)) - a);
                               float y4 = y0 - l * cos(atan2((x0 - x1) , (y0 - y1)) - a);
                               painter.drawLine(x0,y0,x3,y3);
                               painter.drawLine(x0,y0,x4,y4);
                              painter.drawLine(line_bfs2[i].p1(),line_bfs2[i].p2());
                               for (int j = 0; j < directedweightedgraph->points_edge.size(); ++j)
                               {
                                   QPen temp_pen;
                                   temp_pen.setBrush(Qt::blue);
                                   painter.setPen(temp_pen);
                                   if(directedweightedgraph->cityMap[directedweightedgraph->points_edge[j].from].pos == line_bfs2[i].p1() &&
                                       directedweightedgraph->cityMap[directedweightedgraph->points_edge[j].to].pos == line_bfs2[i].p2()    )
                                   {
                                   painter.drawRect(directedweightedgraph->points_edge[j].location.rx(),directedweightedgraph->points_edge[j].location.ry(), 13, 13);
                                   o = directedweightedgraph->points_edge[j].location;
                                   QRect rect(o.x(), o.y(), 2*7, 2*7);
                                   qname = QString(QString::fromLocal8Bit(directedweightedgraph->points_edge[j].weight.c_str()));
                                   painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                                   }
                                   if(directedweightedgraph->cityMap[directedweightedgraph->points_edge[j].from].pos == line_bfs2[i].p2() &&
                                       directedweightedgraph->cityMap[directedweightedgraph->points_edge[j].to].pos == line_bfs2[i].p1()    )
                                   {
                                   painter.drawRect(directedweightedgraph->points_edge[j].location.rx(),directedweightedgraph->points_edge[j].location.ry(), 13, 13);

                                   o = directedweightedgraph->points_edge[j].location;
                                   QRect rect(o.x(), o.y(), 2*7, 2*7);
                                   qname = QString(QString::fromLocal8Bit(directedweightedgraph->points_edge[j].weight.c_str()));
                                   painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                                   }
                               }

                           }
               //绘制点
               painter.setPen(Qt::blue);
               for (int i = 0; i < point_bfs2.size(); ++i)
               {
                   painter.drawEllipse(point_bfs2[i].pos, r, r);
                   o = point_bfs2[i].pos;
                   QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                   qname = QString(QString::fromLocal8Bit(point_bfs2[i].name.c_str()));
                   painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
               }
              if(!directedweightedgraph->points_bfs_light.empty())
              {
                  Map temp_map = directedweightedgraph->points_bfs_light[0];
                  QPen temp_pen;
                  temp_pen.setWidth(5);
                  temp_pen.setColor(Qt::blue);
                  painter.setPen(temp_pen);
                  painter.drawEllipse(temp_map.pos, r, r);
                  o = temp_map.pos;
                  QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                  qname = QString(QString::fromLocal8Bit(temp_map.name.c_str()));
                  painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                  directedweightedgraph->points_bfs_light.erase(directedweightedgraph->points_bfs_light.begin());
                  qDebug()<< qname;
              }
              painter.setPen(QPen(Qt::black, 1));
              str = "此时BFS选中的顶点（队首的顶点）";
              painter.drawText(QPoint(200, 20), QString(QString::fromLocal8Bit(str.c_str())));
                  QPen temp_pen2;
                  temp_pen2.setWidth(3);
                  temp_pen2.setColor(Qt::blue);
                  painter.setPen(temp_pen2);
                  painter.drawEllipse(QPoint(170, 15), 6, 6);

    }
    if(is_traverse_dfs&&is_directedweightedgraph)
    {
        QPen pen;
        pen.setBrush(QBrush(Qt::red));//设置笔刷
        QVector<qreal> dashes0;
        qreal space0 = 10;
        dashes0 << 5 << space0 << 5 <<space0;
        pen.setDashPattern(dashes0);
        pen.setWidth(2);
//        painter.setPen(pen);
//        painter.drawLine(QPoint(10, 100), QPoint(80, 100));
        pen.setBrush(Qt::red);
        painter.setPen(pen);
        painter.drawLine(QPoint(10, 40), QPoint(80, 40));
//        painter.setPen(QPen(Qt::green, 2));
//        painter.drawLine(QPoint(10, 140), QPoint(80, 140));
        painter.setPen(QPen(Qt::black, 1));
        string str("DFS路线");
        painter.drawText(QPoint(90, 40), QString(QString::fromLocal8Bit(str.c_str())) );
                        QPen pen_dfs;

//                        painter.drawLines(line_dfs2);
                        QPoint o;
                        QString qname;
                        for(int i = 0 ; i< line_dfs2.size() ; i++)
                                {
                            pen_dfs.setBrush(QBrush(Qt::red));//设置笔刷
                            QVector<qreal> dashes;
                            qreal space = 12;
                            dashes << 5 << space << 5 <<space;
                            pen_dfs.setDashPattern(dashes);
                            pen_dfs.setWidth(2);
                            painter.setPen(pen_dfs);
                                    float x1 = line_dfs2[i].x1();       //lastPoint 起点
                                    float y1 = line_dfs2[i].y1();
                                    float x2 = line_dfs2[i].x2();  //endPoint 终点
                                    float y2 = line_dfs2[i].y2();

                                    float x0 = (2*x1)/3 + x2/3;
                                    float y0 = (2*y1)/3 + y2/3;
                                    float l = 10.0;                   //箭头的那长度
                                    float a = 0.5;                       //箭头与线段角度
                                    float x3 = x0 - l * cos(atan2((y0 - y1) , (x0 - x1)) - a);
                                     float y3 = y0 - l * sin(atan2((y0 - y1) , (x0 - x1)) - a);
                                     float x4 = x0 - l * sin(atan2((x0 - x1) , (y0 - y1)) - a);
                                     float y4 = y0 - l * cos(atan2((x0 - x1) , (y0 - y1)) - a);
                                    painter.drawLine(x0,y0,x3,y3);
                                    painter.drawLine(x0,y0,x4,y4);
                                    painter.drawLine(line_dfs2[i].p1(),line_dfs2[i].p2());
                                    for (int j = 0; j < directedweightedgraph->points_edge.size(); ++j)
                                    {
                                        QPen temp_pen;
                                        temp_pen.setBrush(Qt::red);

                                        painter.setPen(temp_pen);
                                        if(directedweightedgraph->cityMap[directedweightedgraph->points_edge[j].from].pos == line_dfs2[i].p1() &&
                                            directedweightedgraph->cityMap[directedweightedgraph->points_edge[j].to].pos == line_dfs2[i].p2()    )
                                        {
                                        painter.drawRect(directedweightedgraph->points_edge[j].location.rx(),directedweightedgraph->points_edge[j].location.ry(), 13, 13);

                                        o = directedweightedgraph->points_edge[j].location;
                                        QRect rect(o.x(), o.y(), 2*7, 2*7);
                                        qname = QString(QString::fromLocal8Bit(directedweightedgraph->points_edge[j].weight.c_str()));
                                        painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                                        }
                                        if(directedweightedgraph->cityMap[directedweightedgraph->points_edge[j].from].pos == line_dfs2[i].p2() &&
                                            directedweightedgraph->cityMap[directedweightedgraph->points_edge[j].to].pos == line_dfs2[i].p1()    )
                                        {
                                        painter.drawRect(directedweightedgraph->points_edge[j].location.rx(),directedweightedgraph->points_edge[j].location.ry(), 13, 13);

                                        o = directedweightedgraph->points_edge[j].location;
                                        QRect rect(o.x(), o.y(), 2*7, 2*7);
                                        qname = QString(QString::fromLocal8Bit(directedweightedgraph->points_edge[j].weight.c_str()));
                                        painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                                        }

                                    }
                                }

                        if(!directedweightedgraph->points_dfs_light.empty())
                        {
                            Map temp_map = directedweightedgraph->points_dfs_light[0];
                            QPen temp_pen;
                            temp_pen.setWidth(5);
                            temp_pen.setColor(Qt::red);
                            painter.setPen(temp_pen);
                            painter.drawEllipse(temp_map.pos, r, r);
                            o = temp_map.pos;
                            QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                            qname = QString(QString::fromLocal8Bit(temp_map.name.c_str()));
                            painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                            directedweightedgraph->points_dfs_light.erase(directedweightedgraph->points_dfs_light.begin());
                        }
                        painter.setPen(Qt::red);

                        for (int i = 0; i < point_dfs2.size(); ++i)
                        {
                            painter.drawEllipse(point_dfs2[i].pos, r, r);
                            o = point_dfs2[i].pos;
                            QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                            qname = QString(QString::fromLocal8Bit(point_dfs2[i].name.c_str()));
                            painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));



                        }
                        painter.setPen(QPen(Qt::black, 1));
                        str = "此时DFS选中的顶点（栈顶的顶点）";
                        painter.drawText(QPoint(200, 40), QString(QString::fromLocal8Bit(str.c_str())) );

                        QPen temp_pen2;
                        temp_pen2.setWidth(3);
                        temp_pen2.setColor(Qt::red);
                        painter.setPen(temp_pen2);
                        painter.drawEllipse(QPoint(170, 35), 6, 6);
    }
    if(is_isedge&&is_directedweightedgraph)
    {
        QPen pen;
        pen.setBrush(QBrush(Qt::red));//设置笔刷

        pen.setWidth(2);

        pen.setBrush(Qt::blue);
        painter.setPen(pen);
        painter.drawLine(QPoint(10, 40), QPoint(80, 40));

        painter.setPen(QPen(Qt::black, 1));
        string str("表示存在这条边");
        painter.drawText(QPoint(90, 40), QString(QString::fromLocal8Bit(str.c_str())) );
            painter.setPen(QPen(Qt::blue,2));
            QPoint o;
            QString qname;
//        painter.drawLine(isedge_line);
            float x1 = isedge_line.x1();       //lastPoint 起点
            float y1 = isedge_line.y1();
            float x2 = isedge_line.x2();  //endPoint 终点
            float y2 =isedge_line.y2();
//            float x0 = (x1+x2)/2;
//            float y0 = (y1+y2)/2;
            float x0 = (2*x1)/3 + x2/3;
            float y0 = (2*y1)/3 + y2/3;
            float l = 10.0;                   //箭头的那长度
            float a = 0.5;                       //箭头与线段角度
            float x3 = x0 - l * cos(atan2((y0 - y1) , (x0 - x1)) - a);
            float y3 = y0 - l * sin(atan2((y0 - y1) , (x0 - x1)) - a);
            float x4 = x0 - l * sin(atan2((x0 - x1) , (y0 - y1)) - a);
            float y4 = y0 - l * cos(atan2((x0 - x1) , (y0 - y1)) - a);
            painter.drawLine(x0,y0,x3,y3);
            painter.drawLine(x0,y0,x4,y4);
            painter.drawLine(isedge_line.p1(),isedge_line.p2());
            //绘制权重
             painter.drawRect(isedge_weight.location.rx(),isedge_weight.location.ry(), 13, 13);
             o =isedge_weight.location;
             QRect rect(o.x(), o.y(), 2*7, 2*7);
             qname = QString(QString::fromLocal8Bit(isedge_weight.weight.c_str()));
             painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
            painter.setPen(QPen(Qt::black,2));

            for (int j = 0; j < directedweightedgraph->points_edge.size(); ++j)
            {
                QPen temp_pen;
                temp_pen.setBrush(Qt::blue);

                painter.setPen(temp_pen);
                if(directedweightedgraph->cityMap[directedweightedgraph->points_edge[j].from].pos == isedge_line.p1() &&
                    directedweightedgraph->cityMap[directedweightedgraph->points_edge[j].to].pos == isedge_line.p2()    )
                {
                painter.drawRect(directedweightedgraph->points_edge[j].location.rx(),directedweightedgraph->points_edge[j].location.ry(), 13, 13);

                o = directedweightedgraph->points_edge[j].location;
                QRect rect(o.x(), o.y(), 2*7, 2*7);
                qname = QString(QString::fromLocal8Bit(directedweightedgraph->points_edge[j].weight.c_str()));
                painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                }
                if(directedweightedgraph->cityMap[directedweightedgraph->points_edge[j].from].pos == isedge_line.p2() &&
                    directedweightedgraph->cityMap[directedweightedgraph->points_edge[j].to].pos == isedge_line.p1()    )
                {
                painter.drawRect(directedweightedgraph->points_edge[j].location.rx(),directedweightedgraph->points_edge[j].location.ry(), 13, 13);

                o = directedweightedgraph->points_edge[j].location;
                QRect rect(o.x(), o.y(), 2*7, 2*7);
                qname = QString(QString::fromLocal8Bit(directedweightedgraph->points_edge[j].weight.c_str()));
                painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                }

            }

        //绘制顶点
              painter.setPen(QPen(Qt::black,2));
        for (int i = 0; i < directedweightedgraph->vexnum; ++i)
        {
            painter.drawEllipse(directedweightedgraph->cityMap[i].pos, r, r);
            o = directedweightedgraph->cityMap[i].pos;
            QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
            qname = QString(QString::fromLocal8Bit(directedweightedgraph->cityMap[i].name.c_str()));
            painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));

        }
        is_isedge = false;
    }
    if(is_indegrees&&is_directedweightedgraph)
    {
        QPen pen;
        pen.setBrush(QBrush(Qt::red));//设置笔刷

        pen.setWidth(2);

        pen.setBrush(Qt::blue);
        painter.setPen(pen);
        painter.drawLine(QPoint(10, 40), QPoint(80, 40));

        painter.setPen(QPen(Qt::black, 1));
        string str("表示进入边");
        painter.drawText(QPoint(90, 40), QString(QString::fromLocal8Bit(str.c_str())) );


        painter.setPen(QPen(Qt::blue,2));
        painter.drawLines(directedweightedgraph->line_indegrees);
        for(int i = 0 ; i< directedweightedgraph->line_indegrees.size() ; i++)
                {
                    float x1 = directedweightedgraph->line_indegrees[i].x1();       //lastPoint 起点
                    float y1 = directedweightedgraph->line_indegrees[i].y1();
                    float x2 = directedweightedgraph->line_indegrees[i].x2();  //endPoint 终点
                   float y2 =directedweightedgraph->line_indegrees[i].y2();
                    float x0 = (2*x1)/3 + x2/3;
                    float y0 = (2*y1)/3 + y2/3;
                    float l = 10.0;                   //箭头的那长度
                    float a = 0.5;                       //箭头与线段角度
                    float x3 = x0 - l * cos(atan2((y0 - y1) , (x0 - x1)) - a);
                     float y3 = y0 - l * sin(atan2((y0 - y1) , (x0 - x1)) - a);
                  float x4 = x0 - l * sin(atan2((x0 - x1) , (y0 - y1)) - a);
                     float y4 = y0 - l * cos(atan2((x0 - x1) , (y0 - y1)) - a);
                    painter.drawLine(x0,y0,x3,y3);
                    painter.drawLine(x0,y0,x4,y4);
                    painter.drawLine(directedweightedgraph->line_indegrees[i].p1(),directedweightedgraph->line_indegrees[i].p2());
                }
        QPoint o;
        QString qname;
        for(int i = 0 ; i< directedweightedgraph->line_indegrees.size() ; i++)
        {
            for (int j = 0; j < directedweightedgraph->points_edge.size(); ++j)
            {
                QPen temp_pen;
                temp_pen.setBrush(Qt::blue);
                painter.setPen(temp_pen);
                if(directedweightedgraph->cityMap[directedweightedgraph->points_edge[j].from].pos == directedweightedgraph->line_indegrees[i].p1() &&
                    directedweightedgraph->cityMap[directedweightedgraph->points_edge[j].to].pos == directedweightedgraph->line_indegrees[i].p2()    )
                {
                painter.drawRect(directedweightedgraph->points_edge[j].location.rx(),directedweightedgraph->points_edge[j].location.ry(), 13, 13);

                o = directedweightedgraph->points_edge[j].location;
                QRect rect(o.x(), o.y(), 2*7, 2*7);
                qname = QString(QString::fromLocal8Bit(directedweightedgraph->points_edge[j].weight.c_str()));
                painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                }
                if(directedweightedgraph->cityMap[directedweightedgraph->points_edge[j].from].pos == directedweightedgraph->line_indegrees[i].p2() &&
                    directedweightedgraph->cityMap[directedweightedgraph->points_edge[j].to].pos == directedweightedgraph->line_indegrees[i].p1()    )
                {
                painter.drawRect(directedweightedgraph->points_edge[j].location.rx(),directedweightedgraph->points_edge[j].location.ry(), 13, 13);

                o = directedweightedgraph->points_edge[j].location;
                QRect rect(o.x(), o.y(), 2*7, 2*7);
                qname = QString(QString::fromLocal8Bit(directedweightedgraph->points_edge[j].weight.c_str()));
                painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                }

            }
        }
        painter.setPen(QPen(Qt::black,2));

        for (int i = 0; i < directedweightedgraph->vexnum; ++i)
        {
            painter.drawEllipse(directedweightedgraph->cityMap[i].pos, r, r);
            o = directedweightedgraph->cityMap[i].pos;
            QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
            qname = QString(QString::fromLocal8Bit(directedweightedgraph->cityMap[i].name.c_str()));
            painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));

        }

        is_indegrees = false;
    }

    if(is_outdegrees&&is_directedweightedgraph)
    {
        QPen pen;
        pen.setBrush(QBrush(Qt::red));//设置笔刷

        pen.setWidth(2);

        pen.setBrush(Qt::red);
        painter.setPen(pen);
        painter.drawLine(QPoint(10, 40), QPoint(80, 40));

        painter.setPen(QPen(Qt::black, 1));
        string str("表示出边");
        painter.drawText(QPoint(90, 40), QString(QString::fromLocal8Bit(str.c_str())) );


        painter.setPen(QPen(Qt::red,2));
//        painter.drawLines(directedweightedgraph->line_outdegrees);
        for(int i = 0 ; i< directedweightedgraph->line_outdegrees.size() ; i++)
                {
                    float x1 = directedweightedgraph->line_outdegrees[i].x1();       //lastPoint 起点
                    float y1 =directedweightedgraph->line_outdegrees[i].y1();
                    float x2 =directedweightedgraph->line_outdegrees[i].x2();  //endPoint 终点
                    float y2 =directedweightedgraph->line_outdegrees[i].y2();
//                    float x0 = (x1+x2)/2;
//                    float y0 = (y1+y2)/2;
                    float x0 = (2*x1)/3 + x2/3;
                    float y0 = (2*y1)/3 + y2/3;
                    float l = 10.0;                   //箭头的那长度
                    float a = 0.5;                       //箭头与线段角度
                    float x3 = x0 - l * cos(atan2((y0 - y1) , (x0 - x1)) - a);
                     float y3 = y0 - l * sin(atan2((y0 - y1) , (x0 - x1)) - a);
                    float x4 = x0 - l * sin(atan2((x0 - x1) , (y0 - y1)) - a);
                    float y4 = y0 - l * cos(atan2((x0 - x1) , (y0 - y1)) - a);
                    painter.drawLine(x0,y0,x3,y3);
                    painter.drawLine(x0,y0,x4,y4);
                    painter.drawLine(directedweightedgraph->line_outdegrees[i].p1(),directedweightedgraph->line_outdegrees[i].p2());


                }
        QPoint o;
        QString qname;

        for(int i = 0 ; i< directedweightedgraph->line_outdegrees.size() ; i++)
        {
            for (int j = 0; j < directedweightedgraph->points_edge.size(); ++j)
            {
                QPen temp_pen;
                temp_pen.setBrush(Qt::red);

                painter.setPen(temp_pen);
                if(directedweightedgraph->cityMap[directedweightedgraph->points_edge[j].from].pos == directedweightedgraph->line_outdegrees[i].p1() &&
                    directedweightedgraph->cityMap[directedweightedgraph->points_edge[j].to].pos == directedweightedgraph->line_outdegrees[i].p2()    )
                {
                painter.drawRect(directedweightedgraph->points_edge[j].location.rx(),directedweightedgraph->points_edge[j].location.ry(), 13, 13);

                o = directedweightedgraph->points_edge[j].location;
                QRect rect(o.x(), o.y(), 2*7, 2*7);
                qname = QString(QString::fromLocal8Bit(directedweightedgraph->points_edge[j].weight.c_str()));
                painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                }
                if(directedweightedgraph->cityMap[directedweightedgraph->points_edge[j].from].pos == directedweightedgraph->line_outdegrees[i].p2() &&
                    directedweightedgraph->cityMap[directedweightedgraph->points_edge[j].to].pos == directedweightedgraph->line_outdegrees[i].p1()    )
                {
                painter.drawRect(directedweightedgraph->points_edge[j].location.rx(),directedweightedgraph->points_edge[j].location.ry(), 13, 13);

                o = directedweightedgraph->points_edge[j].location;
                QRect rect(o.x(), o.y(), 2*7, 2*7);
                qname = QString(QString::fromLocal8Bit(directedweightedgraph->points_edge[j].weight.c_str()));
                painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                }

            }
        }

        painter.setPen(QPen(Qt::black,2));


        for (int i = 0; i < directedweightedgraph->vexnum; ++i)
        {
            painter.drawEllipse(directedweightedgraph->cityMap[i].pos, r, r);
            o = directedweightedgraph->cityMap[i].pos;
            QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
            qname = QString(QString::fromLocal8Bit(directedweightedgraph->cityMap[i].name.c_str()));
            painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));

        }
        is_outdegrees = false;
    }
    if(is_isconnect&&is_directedweightedgraph)
    {
        QPen pen;
        pen.setBrush(QBrush(Qt::red));//设置笔
        pen.setWidth(2);
        pen.setBrush(Qt::blue);
        painter.setPen(pen);
        painter.drawLine(QPoint(10, 40), QPoint(80, 40));
        painter.setPen(QPen(Qt::black, 1));
        string str("表示可以连通的边");
        painter.drawText(QPoint(90, 40), QString(QString::fromLocal8Bit(str.c_str())) );
        painter.setPen(QPen(Qt::black, 1));
        str = "表示可以连通的顶点";
        painter.drawText(QPoint(230, 40), QString(QString::fromLocal8Bit(str.c_str())) );
        QPen temp_pen2;
        temp_pen2.setWidth(3);
        temp_pen2.setColor(Qt::blue);
        painter.setPen(temp_pen2);
        painter.drawEllipse(QPoint(210, 35), 6, 6);
        //绘制路线
                   QPen pen_bfs;
                    pen_bfs.setBrush(QBrush(Qt::blue));
                    pen_bfs.setWidth(2);
                    painter.setPen(pen_bfs);
//                   painter.drawLines(directedweightedgraph->line_bfs);
                    for(int i = 0 ; i< directedweightedgraph->line_bfs.size() ; i++)
                            {
                                float x1 = directedweightedgraph->line_bfs[i].x1();       //lastPoint 起点
                                float y1 = directedweightedgraph->line_bfs[i].y1();
                                float x2 = directedweightedgraph->line_bfs[i].x2();  //endPoint 终点
                                float y2 = directedweightedgraph->line_bfs[i].y2();
                                float x0 = (2*x1)/3 + x2/3;
                                float y0 = (2*y1)/3 + y2/3;
                                float l = 10.0;                   //箭头的那长度
                                float a = 0.5;                       //箭头与线段角
                               float x3 = x0 - l * cos(atan2((y0 - y1) , (x0 - x1)) - a);
                                float y3 = y0 - l * sin(atan2((y0 - y1) , (x0 - x1)) - a);
                                 float x4 = x0 - l * sin(atan2((x0 - x1) , (y0 - y1)) - a);
                                 float y4 = y0 - l * cos(atan2((x0 - x1) , (y0 - y1)) - a);
                                painter.drawLine(x0,y0,x3,y3);
                                painter.drawLine(x0,y0,x4,y4);
                                painter.drawLine(directedweightedgraph->line_bfs[i].p1(),directedweightedgraph->line_bfs[i].p2());
                            }
                   QPoint o;
                   QString qname;
                   for(int i = 0 ; i< directedweightedgraph->line_bfs.size() ; i++)
                   {
                       for (int j = 0; j < directedweightedgraph->points_edge.size(); ++j)
                       {
                           QPen temp_pen;
                           temp_pen.setBrush(Qt::blue);

                           painter.setPen(temp_pen);
                           if(directedweightedgraph->cityMap[directedweightedgraph->points_edge[j].from].pos == directedweightedgraph->line_bfs[i].p1() &&
                               directedweightedgraph->cityMap[directedweightedgraph->points_edge[j].to].pos == directedweightedgraph->line_bfs[i].p2()    )
                           {
                           painter.drawRect(directedweightedgraph->points_edge[j].location.rx(),directedweightedgraph->points_edge[j].location.ry(), 13, 13);

                           o = directedweightedgraph->points_edge[j].location;
                           QRect rect(o.x(), o.y(), 2*7, 2*7);
                           qname = QString(QString::fromLocal8Bit(directedweightedgraph->points_edge[j].weight.c_str()));
                           painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                           }
                           if(directedweightedgraph->cityMap[directedweightedgraph->points_edge[j].from].pos == directedweightedgraph->line_bfs[i].p2() &&
                               directedweightedgraph->cityMap[directedweightedgraph->points_edge[j].to].pos == directedweightedgraph->line_bfs[i].p1()    )
                           {
                           painter.drawRect(directedweightedgraph->points_edge[j].location.rx(),directedweightedgraph->points_edge[j].location.ry(), 13, 13);

                           o = directedweightedgraph->points_edge[j].location;
                           QRect rect(o.x(), o.y(), 2*7, 2*7);
                           qname = QString(QString::fromLocal8Bit(directedweightedgraph->points_edge[j].weight.c_str()));
                           painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                           }

                       }
                   }
                   painter.setPen(Qt::blue);

                   for (int i = 0; i < directedweightedgraph->points_isconnect.size(); ++i)
                   {
                       painter.drawEllipse(directedweightedgraph->points_isconnect[i].pos, r, r);
                       o = directedweightedgraph->points_isconnect[i].pos;
                       QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                       qname = QString(QString::fromLocal8Bit(directedweightedgraph->points_isconnect[i].name.c_str()));
                       painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                       qDebug()<<i;

                   }
                   is_isconnect = false;
    }
    if(is_labelconnect&&is_directedweightedgraph)
    {
        QPoint o;
         QString qname;
        for(int i = 0 ; i < Label_map_connect.size() ; i++)
        {
            if(Label_map_connect[i].label_c == 1)
            {

                QPen temp_pen2;
                temp_pen2.setWidth(3);
                temp_pen2.setColor(Qt::blue);
                painter.setPen(temp_pen2);

                 painter.drawEllipse(Label_map_connect[i].pos, r, r);
                 o = Label_map_connect[i].pos;
                 QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                 qname = QString(QString::fromLocal8Bit(Label_map_connect[i].name.c_str()));
                 painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
            }
            if(Label_map_connect[i].label_c == 2)
            {
                QPen temp_pen2;
                temp_pen2.setWidth(3);
                temp_pen2.setColor(Qt::red);
                painter.setPen(temp_pen2);
                painter.drawEllipse(Label_map_connect[i].pos, r, r);
                o = Label_map_connect[i].pos;
                QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                qname = QString(QString::fromLocal8Bit(Label_map_connect[i].name.c_str()));
                painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
            }
            if(Label_map_connect[i].label_c == 3)
            {
                QPen temp_pen2;
                temp_pen2.setWidth(3);
                temp_pen2.setColor(Qt::cyan);
                painter.setPen(temp_pen2);
                painter.drawEllipse(Label_map_connect[i].pos, r, r);
                o = Label_map_connect[i].pos;
                QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                qname = QString(QString::fromLocal8Bit(Label_map_connect[i].name.c_str()));
                painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
            }
        }
        QPen pen;
        pen.setBrush(QBrush(Qt::red));//设置笔刷

        pen.setWidth(2);

        pen.setBrush(Qt::blue);
         painter.setPen(QPen(Qt::black, 1));
        string str = "表示不同的连通分支";
        painter.drawText(QPoint(70, 40), QString(QString::fromLocal8Bit(str.c_str())) );
        QPen temp_pen2;
        temp_pen2.setWidth(3);
        temp_pen2.setColor(Qt::blue);
        painter.setPen(temp_pen2);
        painter.drawEllipse(QPoint(50, 35), 6, 6);
        temp_pen2.setWidth(3);
        temp_pen2.setColor(Qt::cyan);
        painter.setPen(temp_pen2);
        painter.drawEllipse(QPoint(30, 35), 6, 6);
        temp_pen2.setWidth(3);
        temp_pen2.setColor(Qt::red);
        painter.setPen(temp_pen2);
        painter.drawEllipse(QPoint(10, 35), 6, 6);
    }
    if(is_prim&&is_directedweightedgraph)
    {
        QPen pen;
               pen.setBrush(QBrush(Qt::blue));//设置笔刷
               QVector<qreal> dashes0;
               qreal space0 = 10;
               dashes0 << 5 << space0 << 5 <<space0;
               pen.setDashPattern(dashes0);
               pen.setWidth(2);
               painter.setPen(pen);
               painter.drawLine(QPoint(10, 20), QPoint(80, 20));
               painter.setPen(QPen(Qt::black, 1));
               string str = "最小生成树路线";
               painter.drawText(QPoint(90, 20), QString(QString::fromLocal8Bit(str.c_str())));
               //绘制路线
                   QPen pen_prim;
                   pen_prim.setBrush(QBrush(Qt::blue));
                   pen_prim.setWidth(2);
                   painter.setPen(pen_prim);
                   QPoint o;
                   QString qname;
                   for(int i = 0 ; i< line_prim2.size() ; i++)
                           { pen_prim.setBrush(QBrush(Qt::blue));
                       pen_prim.setWidth(2);
                        painter.setPen(pen_prim);
                       float x1 =line_prim2[i].x1();       //lastPoint 起点
                        float y1 = line_prim2[i].y1();
                       float x2 = line_prim2[i].x2();  //endPoint 终点
                        float y2 = line_prim2[i].y2();

                        float x0 = (2*x1)/3 + x2/3;
                        float y0 = (2*y1)/3 + y2/3;
                        float l = 10.0;                   //箭头的那长度
                        float a = 0.5;                       //箭头与线段角度
                           float x3 = x0 - l * cos(atan2((y0 - y1) , (x0 - x1)) - a);
                         float y3 = y0 - l * sin(atan2((y0 - y1) , (x0 - x1)) - a);
                          float x4 = x0 - l * sin(atan2((x0 - x1) , (y0 - y1)) - a);
                        float y4 = y0 - l * cos(atan2((x0 - x1) , (y0 - y1)) - a);
                        painter.drawLine(x0,y0,x3,y3);
                        painter.drawLine(x0,y0,x4,y4);
                        painter.drawLine(line_prim2[i].p1(),line_prim2[i].p2());
                              for (int j = 0; j < directedweightedgraph->points_edge.size(); ++j)
                               {
                                   QPen temp_pen;
                                   temp_pen.setBrush(Qt::blue);
                                  painter.setPen(temp_pen);
                                   if(directedweightedgraph->cityMap[directedweightedgraph->points_edge[j].from].pos == line_prim2[i].p1() &&
                                       directedweightedgraph->cityMap[directedweightedgraph->points_edge[j].to].pos == line_prim2[i].p2()    )
                                   {
                                   painter.drawRect(directedweightedgraph->points_edge[j].location.rx(),directedweightedgraph->points_edge[j].location.ry(), 13, 13);
                                   o = directedweightedgraph->points_edge[j].location;
                                   QRect rect(o.x(), o.y(), 2*7, 2*7);
                                   qname = QString(QString::fromLocal8Bit(directedweightedgraph->points_edge[j].weight.c_str()));
                                   painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                                   }
                                   if(directedweightedgraph->cityMap[directedweightedgraph->points_edge[j].from].pos == line_prim2[i].p2() &&
                                       directedweightedgraph->cityMap[directedweightedgraph->points_edge[j].to].pos == line_prim2[i].p1()    )
                                   {
                                   painter.drawRect(directedweightedgraph->points_edge[j].location.rx(),directedweightedgraph->points_edge[j].location.ry(), 13, 13);

                                   o = directedweightedgraph->points_edge[j].location;
                                   QRect rect(o.x(), o.y(), 2*7, 2*7);
                                   qname = QString(QString::fromLocal8Bit(directedweightedgraph->points_edge[j].weight.c_str()));
                                   painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));
                                   }

                               }

                           }

               //绘制点

               painter.setPen(Qt::blue);
               for (int i = 0; i < point_prim2.size(); ++i)
               {
                   painter.drawEllipse(point_prim2[i].pos, r, r);
                   o = point_prim2[i].pos;
                   QRect rect(o.x()-r, o.y()-r, 2*r, 2*r);
                   qname = QString(QString::fromLocal8Bit(point_prim2[i].name.c_str()));
                   painter.drawText(rect,qname,QTextOption(Qt::AlignCenter));


               }

               if(!directedweightedgraph->line_prim_light.empty())
               {

                   QPen temp_pen;
                   temp_pen.setWidth(3);
                   temp_pen.setColor(Qt::blue);
                   painter.setPen(temp_pen);
                   painter.drawLine(directedweightedgraph->line_prim_light[0]);
                   directedweightedgraph->line_prim_light.erase(directedweightedgraph->line_prim_light.begin());

               }

              painter.setPen(QPen(Qt::black, 1));

                 str = "已经加入集合的顶点";
              painter.drawText(QPoint(200, 60), QString(QString::fromLocal8Bit(str.c_str())));
                  QPen temp_pen2;
                  temp_pen2.setWidth(2);
                  temp_pen2.setColor(Qt::blue);
                  painter.setPen(temp_pen2);
                  painter.drawEllipse(QPoint(170, 55), 6, 6);
    }

    if(is_compare)
    {


        painter.setPen(QPen(Qt::red, 2));
        painter.drawLine(QPoint(10, 60), QPoint(80, 60));
        painter.setPen(QPen(Qt::black, 1));

        string  str = "递归dfs的运行时间走势";
  painter.drawText(QPoint(90, 60), QString(QString::fromLocal8Bit(str.c_str())));
        painter.setPen(QPen(Qt::black, 2));
        painter.drawLine(QPoint(10, 40), QPoint(80, 40));
        painter.setPen(QPen(Qt::black, 1));

          string str2 = "非递归dfs的运行时间走势";
         painter.drawText(QPoint(90, 40), QString(QString::fromLocal8Bit(str2.c_str())));
          str2 = "随机构造图中点的个数";
        painter.drawText(QPoint(525, 550), QString(QString::fromLocal8Bit(str2.c_str())));
        // 折线上的点
            painter.setRenderHint(QPainter::Antialiasing, true);
            painter.setPen(QPen(Qt::black, 2));
            QPainterPath path(graph->pointf_dfs[0]);

            for (int i = 1; i < graph->pointf_dfs.size(); ++i)
            {
                path.lineTo(graph->pointf_dfs[i]);
            }

            // 绘制 path
            painter.drawPath(path);
            // 绘制折线上的标记点
            painter.setPen(Qt::gray);
            int ellipse_size = 4;
            for (int i = 0; i < graph->pointf_dfs.size(); ++i) {
                painter.drawEllipse(graph->pointf_dfs[i], ellipse_size, ellipse_size);
                QString text = QString::number((500-graph->pointf_dfs[i].y())/1000000);
                QFontMetrics fm = painter.fontMetrics();
                int height_font = fm.height();
                int width_text = fm.width(text);
                QPointF textPos(graph->pointf_dfs[i].x()-(width_text/2), graph->pointf_dfs[i].y()-(ellipse_size/2)-(height_font/2));
                painter.drawText(textPos, text);
            }

            painter.setPen(QPen(Qt::red, 2));
            QPainterPath path2(graph->pointf_dfs_withrecursion[0]);

            for (int i = 1; i <graph->pointf_dfs_withrecursion.size(); ++i)
            {
                path2.lineTo (graph->pointf_dfs_withrecursion[i]);
            }
            // 绘制 path
            painter.drawPath(path2);
            // 绘制折线上的标记点
            painter.setPen(Qt::blue);

            for (int i = 0; i <  graph->pointf_dfs_withrecursion.size(); ++i) {
                painter.drawEllipse( graph->pointf_dfs_withrecursion[i], ellipse_size, ellipse_size);
                QString text2 = QString::number((500- graph->pointf_dfs_withrecursion[i].y())/1000000);
                QFontMetrics fm2 = painter.fontMetrics();
                int height_font2 = fm2.height();
                int width_text2 = fm2.width(text2);
                QPointF textPos2( graph->pointf_dfs_withrecursion[i].x()-(width_text2/2),  graph->pointf_dfs_withrecursion[i].y()-(ellipse_size/2)-(height_font2/2));
                painter.drawText(textPos2, text2);
            }
 painter.setPen(QPen(Qt::black, 2));
            painter.drawLine(50,140,50,500);  //绘制y轴
            painter.drawLine(50,500,525,500); //绘制x轴
            int i;
            int j = 20;
            for(i = 50;i<500;i+=50)//x zhou
            {
                 painter.drawLine(i+50,500,i+50,490); //绘制x轴上的点
                 painter.drawText(i+50,525,QString::number(j)); //绘制文本
                    j+=20;
            }




    }


    }


void Widget::on_pushButton_clicked()//dfs
{
     is_compare = false;
    ui->textBrowser->clear();
    QFont ft;
      ft.setPointSize(15);
     ui->textBrowser->setFont(ft);

     is_compare = false;
    if(is_undirectedgraph)
    {


        QString qinput;
        string output;
        QString qoutput;
        string input;
        int i;
        qinput = ui->lineEdit->text();
        input = string((const char *)qinput.toLocal8Bit());
        graph->dfs_str.clear();
        output.clear();
        output_dfs.clear();
        ui->textBrowser->setText("");
        graph->points_dfs.clear();
        graph->line_dfs.clear();
        line_dfs2.clear();
        point_dfs2.clear();
        i = graph->LocationVex(input);

        graph->DFS_Traverse(i);

        output_dfs.erase(0, output.length());

       output_dfs.append("\n深度优先遍历结果：\n");
        is_create = true;
        is_traverse_dfs = true;
        is_traverse_bfs = false;
      is_labelconnect =false;
        is_isedge = false;
        is_indegrees = false;
        is_outdegrees = false;
        is_isconnect = false;

        while(!graph->points_dfs.empty())
        {

            Map temp_map ;
            temp_map.pos = graph->points_dfs[0].pos;
            temp_map.name = graph->points_dfs[0].name;

           point_dfs2.push_back(temp_map);

           output_dfs.append( temp_map.name+"-->");

           qoutput_dfs
                   = QString(QString::fromLocal8Bit(output_dfs.c_str()));
           ui->textBrowser->setText(qoutput_dfs);
         //QLabel自动换行
         ui->textBrowser->adjustSize();
         ui->textBrowser->setGeometry(QRect(180, 500, 540, 280));
         ui->textBrowser->setAlignment(Qt::AlignTop);

         graph->points_dfs.erase(graph->points_dfs.begin());
            if(!graph->line_dfs.empty())
            {
                QLine temp_line = graph->line_dfs[0];
                line_dfs2.push_back(temp_line);
                graph->line_dfs.erase(graph->line_dfs.begin());


            }

            for(i = 0 ; i<200000 ; i++)
            {
                 qDebug()<<"1";
            }

           repaint();
            qApp->processEvents();
        }

        repaint();
     }
    if(is_directedgraph)
    {
        QString qinput;
        string output;
        QString qoutput;
        string input;
        int i;
        qinput = ui->lineEdit->text();
        input = string((const char *)qinput.toLocal8Bit());
        directedgraph->dfs_str.clear();
        output.clear();
        output_dfs.clear();
        ui->textBrowser->setText("");
        directedgraph->points_dfs.clear();
        directedgraph->line_dfs.clear();
        line_dfs2.clear();
        point_dfs2.clear();
        i = directedgraph->LocationVex(input);

        directedgraph->DFS_Traverse(i);

        output_dfs.erase(0, output.length());

       output_dfs.append("\n深度优先遍历结果：\n");
        is_create = true;
        is_traverse_dfs = true;
        is_traverse_bfs = false;
      is_labelconnect =false;
        is_isedge = false;
        is_indegrees = false;
        is_outdegrees = false;
        is_isconnect = false;

        while(!directedgraph->points_dfs.empty())
        {

            Map temp_map ;
            temp_map.pos = directedgraph->points_dfs[0].pos;
            temp_map.name = directedgraph->points_dfs[0].name;

           point_dfs2.push_back(temp_map);

           output_dfs.append( temp_map.name+"-->");

           qoutput_dfs
                   = QString(QString::fromLocal8Bit(output_dfs.c_str()));
           ui->textBrowser->setText(qoutput_dfs);
         //QLabel自动换行
         ui->textBrowser->adjustSize();
         ui->textBrowser->setGeometry(QRect(180, 500, 540, 280));
         ui->textBrowser->setAlignment(Qt::AlignTop);

         directedgraph->points_dfs.erase(directedgraph->points_dfs.begin());
            if(!directedgraph->line_dfs.empty())
            {
                QLine temp_line = directedgraph->line_dfs[0];
                line_dfs2.push_back(temp_line);
                directedgraph->line_dfs.erase(directedgraph->line_dfs.begin());


            }

            for(i = 0 ; i<200000 ; i++)
            {
                 qDebug()<<"1";
            }

           repaint();
            qApp->processEvents();
        }

        repaint();
    }
    if(is_undirectedweightedgraph)
    {
        QString qinput;
        string output;
        QString qoutput;
        string input;
        int i;
        qinput = ui->lineEdit->text();
        input = string((const char *)qinput.toLocal8Bit());
       undirectedweightedgraph->dfs_str.clear();
        output.clear();
        output_dfs.clear();
        ui->textBrowser->setText("");
        undirectedweightedgraph->points_dfs.clear();
        undirectedweightedgraph->line_dfs.clear();
        line_dfs2.clear();
        point_dfs2.clear();
        i = undirectedweightedgraph->LocationVex(input);

        undirectedweightedgraph->DFS_Traverse(i);

        output_dfs.erase(0, output.length());

       output_dfs.append("\n深度优先遍历结果：\n");
        is_create = true;
        is_traverse_dfs = true;
        is_traverse_bfs = false;
        is_labelconnect =false;
        is_isedge = false;
        is_indegrees = false;
        is_outdegrees = false;
        is_isconnect = false;

        while(!undirectedweightedgraph->points_dfs.empty())
        {

            Map temp_map ;
            temp_map.pos = undirectedweightedgraph->points_dfs[0].pos;
            temp_map.name = undirectedweightedgraph->points_dfs[0].name;

           point_dfs2.push_back(temp_map);

           output_dfs.append( temp_map.name+"-->");

           qoutput_dfs
                   = QString(QString::fromLocal8Bit(output_dfs.c_str()));
           ui->textBrowser->setText(qoutput_dfs);
         //QLabel自动换行
         ui->textBrowser->adjustSize();
         ui->textBrowser->setGeometry(QRect(180, 500, 540, 280));
         ui->textBrowser->setAlignment(Qt::AlignTop);

         undirectedweightedgraph->points_dfs.erase(undirectedweightedgraph->points_dfs.begin());
            if(!undirectedweightedgraph->line_dfs.empty())
            {
                QLine temp_line = undirectedweightedgraph->line_dfs[0];
                line_dfs2.push_back(temp_line);
                undirectedweightedgraph->line_dfs.erase(undirectedweightedgraph->line_dfs.begin());


            }

            for(i = 0 ; i<200000 ; i++)
            {
                 qDebug()<<"1";
            }

           repaint();
            qApp->processEvents();
        }

        repaint();
    }
    if(is_directedweightedgraph)
    {
        QString qinput;
        string output;
        QString qoutput;
        string input;
        int i;
        qinput = ui->lineEdit->text();
        input = string((const char *)qinput.toLocal8Bit());
        directedweightedgraph->dfs_str.clear();
        output.clear();
        output_dfs.clear();
        ui->textBrowser->setText("");
        directedweightedgraph->points_dfs.clear();
       directedweightedgraph->line_dfs.clear();
        line_dfs2.clear();
        point_dfs2.clear();
        i = directedweightedgraph->LocationVex(input);

       directedweightedgraph->DFS_Traverse(i);

        output_dfs.erase(0, output.length());

       output_dfs.append("\n深度优先遍历结果：\n");
        is_create = true;
        is_traverse_dfs = true;
        is_traverse_bfs = false;
      is_labelconnect =false;
        is_isedge = false;
        is_indegrees = false;
        is_outdegrees = false;
        is_isconnect = false;

        while(!directedweightedgraph->points_dfs.empty())
        {

            Map temp_map ;
            temp_map.pos = directedweightedgraph->points_dfs[0].pos;
            temp_map.name = directedweightedgraph->points_dfs[0].name;

           point_dfs2.push_back(temp_map);

           output_dfs.append( temp_map.name+"-->");

           qoutput_dfs
                   = QString(QString::fromLocal8Bit(output_dfs.c_str()));
           ui->textBrowser->setText(qoutput_dfs);
         //QLabel自动换行
         ui->textBrowser->adjustSize();
         ui->textBrowser->setGeometry(QRect(180, 500, 540, 280));
         ui->textBrowser->setAlignment(Qt::AlignTop);

         directedweightedgraph->points_dfs.erase(directedweightedgraph->points_dfs.begin());
            if(!directedweightedgraph->line_dfs.empty())
            {
                QLine temp_line = directedweightedgraph->line_dfs[0];
                line_dfs2.push_back(temp_line);
                directedweightedgraph->line_dfs.erase(directedweightedgraph->line_dfs.begin());


            }

            for(i = 0 ; i<200000 ; i++)
            {
                 qDebug()<<"1";
            }

           repaint();
            qApp->processEvents();
        }

        repaint();
    }
}

void Widget::on_pushButton_2_clicked()//bfs
{
    ui->textBrowser->clear();
    QFont ft;
      ft.setPointSize(15);
     ui->textBrowser->setFont(ft);
     is_compare = false;
    if(is_undirectedgraph)
    {
    QString qinput;
    string output;
    QString qoutput;
    string input;
    int i;

    qinput = ui->lineEdit->text();
    input = string((const char *)qinput.toLocal8Bit());
    graph->bfs_str.clear();

    output.clear();
    output_bfs.clear();
    ui->textBrowser->setText("");

    graph->points_bfs.clear();
    graph->line_bfs.clear();
    line_bfs2.clear();
    point_bfs2.clear();
     i = graph->LocationVex(input);
        start = i;

      graph->BFS_Traverse(i);

      output_bfs.erase(0, output.length());

     output_bfs.append("\n广度优先遍历结果：\n");

    is_create = true;
    is_traverse_bfs = true;
    is_traverse_dfs =false;
  is_labelconnect =false;
    is_isedge = false;
    is_indegrees = false;
    is_outdegrees = false;
    is_isconnect = false;

    while(!graph->points_bfs.empty())
    {

        Map temp_map ;
        temp_map.pos = graph->points_bfs[0].pos;
        temp_map.name = graph->points_bfs[0].name;

        point_bfs2.push_back(temp_map);
        output_bfs.append( temp_map.name+"-->");

        qoutput_bfs
                = QString(QString::fromLocal8Bit(output_bfs.c_str()));
        ui->textBrowser->setText(qoutput_bfs);
      //QLabel自动换行
      ui->textBrowser->adjustSize();
      ui->textBrowser->setGeometry(QRect(180, 500, 540, 280));
      ui->textBrowser->setAlignment(Qt::AlignTop);
     graph->points_bfs.erase(graph->points_bfs.begin());
        if(!graph->line_bfs.empty())
        {
            QLine temp_line = graph->line_bfs[0];
            line_bfs2.push_back(temp_line);
            graph->line_bfs.erase(graph->line_bfs.begin());

        }





           for(i = 0 ; i<200000 ; i++)
           {
                qDebug()<<"1";
           }

       repaint();
        qApp->processEvents();
    }


       repaint();
       }
    if(is_directedgraph)
    {
        QString qinput;
        string output;
        QString qoutput;
        string input;
        int i;

        qinput = ui->lineEdit->text();
        input = string((const char *)qinput.toLocal8Bit());
        directedgraph->bfs_str.clear();

        output.clear();
        output_bfs.clear();
        ui->textBrowser->setText("");

        graph->points_bfs.clear();
        graph->line_bfs.clear();
        line_bfs2.clear();
        point_bfs2.clear();
         i = directedgraph->LocationVex(input);
            start = i;

          directedgraph->BFS_Traverse(i);

          output_bfs.erase(0, output.length());

         output_bfs.append("\n广度优先遍历结果：\n");

        is_create = true;
        is_traverse_bfs = true;
        is_traverse_dfs =false;
        is_labelconnect =false;
        is_isedge = false;
        is_indegrees = false;
        is_outdegrees = false;
        is_isconnect = false;

        while(!directedgraph->points_bfs.empty())
        {

            Map temp_map ;
            temp_map.pos = directedgraph->points_bfs[0].pos;
            temp_map.name = directedgraph->points_bfs[0].name;

            point_bfs2.push_back(temp_map);
            output_bfs.append( temp_map.name+"-->");

            qoutput_bfs
                    = QString(QString::fromLocal8Bit(output_bfs.c_str()));
            ui->textBrowser->setText(qoutput_bfs);
          //QLabel自动换行
          ui->textBrowser->adjustSize();
          ui->textBrowser->setGeometry(QRect(180, 500, 540, 280));
          ui->textBrowser->setAlignment(Qt::AlignTop);
         directedgraph->points_bfs.erase(directedgraph->points_bfs.begin());
            if(!directedgraph->line_bfs.empty())
            {
                QLine temp_line = directedgraph->line_bfs[0];
                line_bfs2.push_back(temp_line);
               directedgraph->line_bfs.erase(directedgraph->line_bfs.begin());

            }





               for(i = 0 ; i<200000 ; i++)
               {
                    qDebug()<<"1";
               }

           repaint();
            qApp->processEvents();
        }

    //       timer_bfs->start(1000);
    //       qApp->processEvents();

           repaint();

    }
    if(is_undirectedweightedgraph)
    {
        QString qinput;
        string output;
        QString qoutput;
        string input;
        int i;

        qinput = ui->lineEdit->text();
        input = string((const char *)qinput.toLocal8Bit());
        undirectedweightedgraph->bfs_str.clear();

        output.clear();
        output_bfs.clear();
        ui->textBrowser->setText("");

        undirectedweightedgraph->points_bfs.clear();
        undirectedweightedgraph->line_bfs.clear();
        line_bfs2.clear();
        point_bfs2.clear();
         i = undirectedweightedgraph->LocationVex(input);
            start = i;

          undirectedweightedgraph->BFS_Traverse(i);

          output_bfs.erase(0, output.length());

         output_bfs.append("\n广度优先遍历结果：\n");

        is_create = true;
        is_traverse_bfs = true;
        is_traverse_dfs =false;
      is_labelconnect =false;
        is_isedge = false;
        is_indegrees = false;
        is_outdegrees = false;
        is_isconnect = false;

        while(!undirectedweightedgraph->points_bfs.empty())
        {

            Map temp_map ;
            temp_map.pos = undirectedweightedgraph->points_bfs[0].pos;
            temp_map.name = undirectedweightedgraph->points_bfs[0].name;

            point_bfs2.push_back(temp_map);
            output_bfs.append( temp_map.name+"-->");

            qoutput_bfs
                    = QString(QString::fromLocal8Bit(output_bfs.c_str()));
            ui->textBrowser->setText(qoutput_bfs);
          //QLabel自动换行
          ui->textBrowser->adjustSize();
          ui->textBrowser->setGeometry(QRect(180, 500, 540, 280));
          ui->textBrowser->setAlignment(Qt::AlignTop);
         undirectedweightedgraph->points_bfs.erase(undirectedweightedgraph->points_bfs.begin());
            if(!undirectedweightedgraph->line_bfs.empty())
            {
                QLine temp_line = undirectedweightedgraph->line_bfs[0];
                line_bfs2.push_back(temp_line);
                undirectedweightedgraph->line_bfs.erase(undirectedweightedgraph->line_bfs.begin());

            }





               for(i = 0 ; i<200000 ; i++)
               {
                    qDebug()<<"1";
               }

           repaint();
            qApp->processEvents();
        }

           repaint();
    }
    if(is_directedweightedgraph)
    {
        QString qinput;
        string output;
        QString qoutput;
        string input;
        int i;

        qinput = ui->lineEdit->text();
        input = string((const char *)qinput.toLocal8Bit());
       directedweightedgraph->bfs_str.clear();

        output.clear();
        output_bfs.clear();
        ui->textBrowser->setText("");

        directedweightedgraph->points_bfs.clear();
        directedweightedgraph->line_bfs.clear();
        line_bfs2.clear();
        point_bfs2.clear();
         i = directedweightedgraph->LocationVex(input);
            start = i;

          directedweightedgraph->BFS_Traverse(i);

          output_bfs.erase(0, output.length());

         output_bfs.append("\n广度优先遍历结果：\n");

        is_create = true;
        is_traverse_bfs = true;
        is_traverse_dfs =false;
      is_labelconnect =false;
        is_isedge = false;
        is_indegrees = false;
        is_outdegrees = false;
        is_isconnect = false;

        while(!directedweightedgraph->points_bfs.empty())
        {

            Map temp_map ;
            temp_map.pos = directedweightedgraph->points_bfs[0].pos;
            temp_map.name = directedweightedgraph->points_bfs[0].name;

            point_bfs2.push_back(temp_map);
            output_bfs.append( temp_map.name+"-->");

            qoutput_bfs
                    = QString(QString::fromLocal8Bit(output_bfs.c_str()));
            ui->textBrowser->setText(qoutput_bfs);
          //QLabel自动换行
          ui->textBrowser->adjustSize();
          ui->textBrowser->setGeometry(QRect(180, 500, 540, 280));
          ui->textBrowser->setAlignment(Qt::AlignTop);
        directedweightedgraph->points_bfs.erase(directedweightedgraph->points_bfs.begin());
            if(!directedweightedgraph->line_bfs.empty())
            {
                QLine temp_line = directedweightedgraph->line_bfs[0];
                line_bfs2.push_back(temp_line);
                directedweightedgraph->line_bfs.erase(directedweightedgraph->line_bfs.begin());

            }





               for(i = 0 ; i<200000 ; i++)
               {
                    qDebug()<<"1";
               }

           repaint();
            qApp->processEvents();
        }

           repaint();
    }
}


void Widget::on_pushButton_4_clicked()//无向图
{
     is_compare = false;
ui->textBrowser->clear();
    int vexnum ;
    QString qvexnum = ui->lineEdit_vex->text();

    string str_vexnum = string((const char *)qvexnum.toLocal8Bit());

    stringstream ss1(str_vexnum);


    ss1 >> vexnum;
    graph->vexnum = vexnum;
    graph->points.clear();
    graph->line.clear();
    graph->bfs_str.clear();
    graph->dfs_str.clear();
    graph->line_bfs.clear();
    graph->line_dfs.clear();
    point_bfs2.clear();
    point_dfs2.clear();
    line_bfs2.clear();
    line_dfs2.clear();
    graph->CreatGraph();
     is_compare = false;
    is_create = true;
    is_traverse_bfs = false;
    is_traverse_dfs = false;
    is_isedge = false;
    is_indegrees = false;
    is_outdegrees = false;
    is_isconnect = false;
    is_labelconnect =false;
    is_undirectedgraph = true;
    is_directedgraph = false;
    is_undirectedweightedgraph= false;
    is_directedweightedgraph = false;
   repaint();
}

void Widget::on_pushButton_add_edge_clicked()
{ui->textBrowser->clear();
    QFont ft;
      ft.setPointSize(15);
     ui->textBrowser->setFont(ft);
     is_compare = false;
   if(is_undirectedgraph)
   {
    QString qinput_from;
      QString qinput_to;
    string input_from;
     string input_to;
     int from,to;
     QString qis_add_edge_string;
     string is_add_edge_string;
    qinput_from = ui->lineEdit_add_from->text();
    qinput_to = ui->lineEdit_add_to->text();
    input_from = string((const char *)qinput_from.toLocal8Bit());
    input_to = string((const char *)qinput_to.toLocal8Bit());
     stringstream ss1(input_from);
     stringstream ss2( input_to);
     ss1>>from;
     ss2>>to;
     ui->lineEdit_add_from->clear();
     ui->lineEdit_add_to->clear();
     int i = graph->addEdge(from,to);
     if(i == 0)
     {
         is_add_edge_string = "您输入的边不符合规范";
           qis_add_edge_string
                   = QString(QString::fromLocal8Bit(is_add_edge_string.c_str()));
           ui->textBrowser->setText( qis_add_edge_string);
         //QLabel自动换行
         ui->textBrowser->adjustSize();
         ui->textBrowser->setGeometry(QRect(180, 500, 540, 280));
         ui->textBrowser->setAlignment(Qt::AlignTop);
         is_create = true;
         is_traverse_bfs = false;
         is_traverse_dfs = false;
         is_isedge = false;
         is_indegrees = false;
         is_outdegrees = false;
         is_isconnect = false;
         is_labelconnect =false;
        repaint();

     }
     if(i ==1)
     {
         is_add_edge_string = "从";
         is_add_edge_string.append(to_string(from));
         is_add_edge_string.append("-->");
          is_add_edge_string.append(to_string(to));
          is_add_edge_string.append("的路径已经存在");
          qis_add_edge_string
                  = QString(QString::fromLocal8Bit(is_add_edge_string.c_str()));
          ui->textBrowser->setText( qis_add_edge_string);
        //QLabel自动换行
        ui->textBrowser->adjustSize();
        ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
        ui->textBrowser->setAlignment(Qt::AlignTop);
        is_create = true;
        is_traverse_bfs = false;
        is_traverse_dfs = false;
        is_isedge = false;
        is_indegrees = false;
        is_outdegrees = false;
        is_isconnect = false;
        is_labelconnect =false;
       repaint();
     }
     if(i ==2)
     {
         is_add_edge_string = "边";
         is_add_edge_string.append(to_string(from));
         is_add_edge_string.append("-->");
          is_add_edge_string.append(to_string(to));
          is_add_edge_string.append("添加成功");
          qis_add_edge_string
                  = QString(QString::fromLocal8Bit(is_add_edge_string.c_str()));
          ui->textBrowser->setText( qis_add_edge_string);
        //QLabel自动换行
        ui->textBrowser->adjustSize();
        ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
        ui->textBrowser->setAlignment(Qt::AlignTop);
         is_create = true;
         is_traverse_bfs = false;
         is_traverse_dfs = false;
         is_isedge = false;
         is_indegrees = false;
         is_outdegrees = false;
         is_isconnect = false;
         is_labelconnect =false;
        repaint();
     }

   }
    if(is_directedgraph)
    {
        QString qis_add_edge_string;
        string is_add_edge_string;
        QString qinput_from;
          QString qinput_to;
        string input_from;
         string input_to;
         int from,to;
        qinput_from = ui->lineEdit_add_from->text();
        qinput_to = ui->lineEdit_add_to->text();
        input_from = string((const char *)qinput_from.toLocal8Bit());
        input_to = string((const char *)qinput_to.toLocal8Bit());
         stringstream ss1(input_from);
         stringstream ss2( input_to);
         ss1>>from;
         ss2>>to;
         ui->lineEdit_add_from->clear();
         ui->lineEdit_add_to->clear();
         int i = directedgraph->addEdge(from,to);
         if(i == 0)
         {
             is_add_edge_string = "您输入的边不符合规范";
               qis_add_edge_string
                       = QString(QString::fromLocal8Bit(is_add_edge_string.c_str()));
               ui->textBrowser->setText( qis_add_edge_string);
             //QLabel自动换行
             ui->textBrowser->adjustSize();
             ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
             ui->textBrowser->setAlignment(Qt::AlignTop);
             is_create = true;
             is_traverse_bfs = false;
             is_traverse_dfs = false;
             is_isedge = false;
             is_indegrees = false;
             is_outdegrees = false;
             is_isconnect = false;
             is_labelconnect =false;
            repaint();

         }
         if(i ==1)
         {
             is_add_edge_string = "从";
             is_add_edge_string.append(to_string(from));
             is_add_edge_string.append("-->");
              is_add_edge_string.append(to_string(to));
              is_add_edge_string.append("的路径已经存在");
              qis_add_edge_string
                      = QString(QString::fromLocal8Bit(is_add_edge_string.c_str()));
              ui->textBrowser->setText( qis_add_edge_string);
            //QLabel自动换行
            ui->textBrowser->adjustSize();
            ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
            ui->textBrowser->setAlignment(Qt::AlignTop);
            is_create = true;
            is_traverse_bfs = false;
            is_traverse_dfs = false;
            is_isedge = false;
            is_indegrees = false;
            is_outdegrees = false;
            is_isconnect = false;
            is_labelconnect =false;
           repaint();
         }
         if(i ==2)
         {
             is_add_edge_string = "边";
             is_add_edge_string.append(to_string(from));
             is_add_edge_string.append("-->");
              is_add_edge_string.append(to_string(to));
              is_add_edge_string.append("添加成功");
              qis_add_edge_string
                      = QString(QString::fromLocal8Bit(is_add_edge_string.c_str()));
              ui->textBrowser->setText( qis_add_edge_string);
            //QLabel自动换行
            ui->textBrowser->adjustSize();
            ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
            ui->textBrowser->setAlignment(Qt::AlignTop);
             is_create = true;
             is_traverse_bfs = false;
             is_traverse_dfs = false;
             is_isedge = false;
             is_indegrees = false;
             is_outdegrees = false;
             is_isconnect = false;
             is_labelconnect =false;
            repaint();
         }

    }
}

void Widget::on_pushButton_delete_edge_clicked()
{
    ui->textBrowser->clear();
    QFont ft;
    ft.setPointSize(15);
   ui->textBrowser->setFont(ft);

    is_compare = false;
     if(is_undirectedgraph)
     {
         QString qis_delete_edge_string;
         string is_delete_edge_string;
    QString qinput_from;
      QString qinput_to;
    string input_from;
     string input_to;
     int from,to;
    qinput_from = ui->lineEdit_del_from->text();
    qinput_to = ui->lineEdit_del_to->text();
    input_from = string((const char *)qinput_from.toLocal8Bit());
    input_to = string((const char *)qinput_to.toLocal8Bit());
     stringstream ss1(input_from);
     stringstream ss2( input_to);
     ss1>>from;
     ss2>>to;
     ui->lineEdit_del_from->clear();
     ui->lineEdit_del_to->clear();
     int i = graph->deleteEdge(from,to);
     if(i == 0)
     {
         is_delete_edge_string = "您输入的边不符合规范";
           qis_delete_edge_string
                   = QString(QString::fromLocal8Bit(is_delete_edge_string.c_str()));
           ui->textBrowser->setText( qis_delete_edge_string);
         //QLabel自动换行
         ui->textBrowser->adjustSize();
         ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
         ui->textBrowser->setAlignment(Qt::AlignTop);
         is_create = true;
         is_traverse_bfs = false;
         is_traverse_dfs = false;
         is_isedge = false;
         is_indegrees = false;
         is_outdegrees = false;
         is_isconnect = false;
         is_labelconnect =false;
        repaint();
     }
     if(i ==1)
     {
         is_delete_edge_string = "从";
         is_delete_edge_string.append(to_string(from));
         is_delete_edge_string.append("-->");
          is_delete_edge_string.append(to_string(to));
          is_delete_edge_string.append("的路径不存在");
          qis_delete_edge_string
                  = QString(QString::fromLocal8Bit(is_delete_edge_string.c_str()));
          ui->textBrowser->setText( qis_delete_edge_string);
        //QLabel自动换行
        ui->textBrowser->adjustSize();
        ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
        ui->textBrowser->setAlignment(Qt::AlignTop);
        is_create = true;
        is_traverse_bfs = false;
        is_traverse_dfs = false;
        is_isedge = false;
        is_indegrees = false;
        is_outdegrees = false;
        is_isconnect = false;
        is_labelconnect =false;
       repaint();
     }
     if(i ==2)
     {
         is_delete_edge_string = "边";
         is_delete_edge_string.append(to_string(from));
         is_delete_edge_string.append("-->");
          is_delete_edge_string.append(to_string(to));
          is_delete_edge_string.append("删除成功");
          qis_delete_edge_string
                  = QString(QString::fromLocal8Bit(is_delete_edge_string.c_str()));
          ui->textBrowser->setText( qis_delete_edge_string);
        //QLabel自动换行
        ui->textBrowser->adjustSize();
        ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
        ui->textBrowser->setAlignment(Qt::AlignTop);
         is_create = true;
         is_traverse_bfs = false;
         is_traverse_dfs = false;
         is_isedge = false;
         is_indegrees = false;
         is_outdegrees = false;
         is_isconnect = false;
         is_labelconnect =false;
        repaint();
     }


     }
     if(is_directedgraph)
     {
         qDebug()<<"is_directedweightedgraph";
         QString qis_delete_edge_string;
         string is_delete_edge_string;
         QString qinput_from;
           QString qinput_to;
         string input_from;
          string input_to;
          int from,to;
         qinput_from = ui->lineEdit_del_from->text();
         qinput_to = ui->lineEdit_del_to->text();
         input_from = string((const char *)qinput_from.toLocal8Bit());
         input_to = string((const char *)qinput_to.toLocal8Bit());
          stringstream ss1(input_from);
          stringstream ss2( input_to);
          ss1>>from;
          ss2>>to;
          ui->lineEdit_del_from->clear();
          ui->lineEdit_del_to->clear();
          int i =  directedgraph->deleteEdge(from,to);
          if(i == 0)
          {
              is_delete_edge_string = "您输入的边不符合规范";
                qis_delete_edge_string
                        = QString(QString::fromLocal8Bit(is_delete_edge_string.c_str()));
                ui->textBrowser->setText( qis_delete_edge_string);
              //QLabel自动换行
              ui->textBrowser->adjustSize();
              ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
              ui->textBrowser->setAlignment(Qt::AlignTop);
              is_create = true;
              is_traverse_bfs = false;
              is_traverse_dfs = false;
              is_isedge = false;
              is_indegrees = false;
              is_outdegrees = false;
              is_isconnect = false;
              is_labelconnect =false;

             repaint();
          }
          if(i ==1)
          {
              is_delete_edge_string = "从";
              is_delete_edge_string.append(to_string(from));
              is_delete_edge_string.append("-->");
               is_delete_edge_string.append(to_string(to));
               is_delete_edge_string.append("的路径不存在");
               qis_delete_edge_string
                       = QString(QString::fromLocal8Bit(is_delete_edge_string.c_str()));
               ui->textBrowser->setText( qis_delete_edge_string);
             //QLabel自动换行
             ui->textBrowser->adjustSize();
             ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
             ui->textBrowser->setAlignment(Qt::AlignTop);
             is_create = true;
             is_traverse_bfs = false;
             is_traverse_dfs = false;
             is_isedge = false;
             is_indegrees = false;
             is_outdegrees = false;
             is_isconnect = false;
             is_labelconnect =false;
            repaint();
          }
          if(i ==2)
          {
              is_delete_edge_string = "边";
              is_delete_edge_string.append(to_string(from));
              is_delete_edge_string.append("-->");
               is_delete_edge_string.append(to_string(to));
               is_delete_edge_string.append("删除成功");
               qis_delete_edge_string
                       = QString(QString::fromLocal8Bit(is_delete_edge_string.c_str()));
               ui->textBrowser->setText( qis_delete_edge_string);
             //QLabel自动换行
             ui->textBrowser->adjustSize();
             ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
             ui->textBrowser->setAlignment(Qt::AlignTop);
              is_create = true;
              is_traverse_bfs = false;
              is_traverse_dfs = false;
              is_isedge = false;
              is_indegrees = false;
              is_outdegrees = false;
              is_isconnect = false;
              is_labelconnect =false;
             repaint();
          }
     }
}

void Widget::on_pushButton_isedge_clicked()
{  ui->textBrowser->clear();
    QFont ft;
    ft.setPointSize(15);
   ui->textBrowser->setFont(ft);
    is_compare = false;
    if(is_undirectedgraph)
    {


    QString qinput_from;
      QString qinput_to;
    string input_from;
     string input_to;
     QString qis_edge_string;
     string is_edge_string;
     int from,to;
    qinput_from = ui->lineEdit_isedge_from->text();
    qinput_to = ui->lineEdit_isedge_to->text();
    input_from = string((const char *)qinput_from.toLocal8Bit());
    input_to = string((const char *)qinput_to.toLocal8Bit());
     stringstream ss1(input_from);
     stringstream ss2( input_to);
     ss1>>from;
     ss2>>to;
     ui->lineEdit_isedge_from->clear();
     ui->lineEdit_isedge_to->clear();

     bool is_edge = graph->isEdge(from,to);
     if(is_edge)
     {
         is_isedge = true;
         isedge_line.setLine(graph->cityMap[from].pos.rx(),graph->cityMap[from].pos.ry(),graph->cityMap[to].pos.rx(),graph->cityMap[to].pos.ry());
         is_edge_string = "边";
         is_edge_string.append(to_string(from));
         is_edge_string.append("-->");
          is_edge_string.append(to_string(to));
           is_edge_string.append("的路径存在");

           qis_edge_string
                   = QString(QString::fromLocal8Bit(is_edge_string.c_str()));
           ui->textBrowser->setText( qis_edge_string);
         //QLabel自动换行
         ui->textBrowser->adjustSize();
         ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
         ui->textBrowser->setAlignment(Qt::AlignTop);


     }
     else {
         is_edge_string = "边";
         is_edge_string.append(to_string(from));
         is_edge_string.append("-->");
          is_edge_string.append(to_string(to));
           is_edge_string.append("的路径不存在");

           qis_edge_string
                   = QString(QString::fromLocal8Bit(is_edge_string.c_str()));
           ui->textBrowser->setText( qis_edge_string);
         //QLabel自动换行
         ui->textBrowser->adjustSize();
         ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
         ui->textBrowser->setAlignment(Qt::AlignTop);
     }
     is_traverse_bfs = false;
     is_traverse_dfs = false;
    is_labelconnect =false;
     is_indegrees = false;
     is_outdegrees = false;
     is_isconnect = false;
     repaint();
     }
    if(is_directedgraph)
    {
        QString qinput_from;
          QString qinput_to;
        string input_from;
         string input_to;
         QString qis_edge_string;
         string is_edge_string;
         int from,to;
        qinput_from = ui->lineEdit_isedge_from->text();
        qinput_to = ui->lineEdit_isedge_to->text();
        input_from = string((const char *)qinput_from.toLocal8Bit());
        input_to = string((const char *)qinput_to.toLocal8Bit());
         stringstream ss1(input_from);
         stringstream ss2( input_to);
         ss1>>from;
         ss2>>to;
         ui->lineEdit_isedge_from->clear();
         ui->lineEdit_isedge_to->clear();

         bool is_edge = directedgraph->isEdge(from,to);
         if(is_edge)
         {
             is_isedge = true;

             isedge_line.setLine(directedgraph->cityMap[from].pos.rx(),directedgraph->cityMap[from].pos.ry(),directedgraph->cityMap[to].pos.rx(),directedgraph->cityMap[to].pos.ry());
             is_edge_string = "边";
             is_edge_string.append(to_string(from));
             is_edge_string.append("-->");
              is_edge_string.append(to_string(to));
               is_edge_string.append("的路径存在");

               qis_edge_string
                       = QString(QString::fromLocal8Bit(is_edge_string.c_str()));
               ui->textBrowser->setText( qis_edge_string);
             //QLabel自动换行
             ui->textBrowser->adjustSize();
             ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
             ui->textBrowser->setAlignment(Qt::AlignTop);


         }
         else {
             is_edge_string = "边";
             is_edge_string.append(to_string(from));
             is_edge_string.append("-->");
              is_edge_string.append(to_string(to));
               is_edge_string.append("的路径不存在");

               qis_edge_string
                       = QString(QString::fromLocal8Bit(is_edge_string.c_str()));
               ui->textBrowser->setText( qis_edge_string);
             //QLabel自动换行
             ui->textBrowser->adjustSize();
             ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
             ui->textBrowser->setAlignment(Qt::AlignTop);
         }
         is_traverse_bfs = false;
         is_traverse_dfs = false;
        is_labelconnect =false;
         is_indegrees = false;
         is_outdegrees = false;
         is_isconnect = false;
         repaint();
    }
    if(is_undirectedweightedgraph)
    {

        QString qinput_from;
          QString qinput_to;
        string input_from;
         string input_to;
         QString qis_edge_string;
         string is_edge_string;
         int from,to;
         is_create = true;
        qinput_from = ui->lineEdit_isedge_from->text();
        qinput_to = ui->lineEdit_isedge_to->text();
        input_from = string((const char *)qinput_from.toLocal8Bit());
        input_to = string((const char *)qinput_to.toLocal8Bit());
         stringstream ss1(input_from);
         stringstream ss2( input_to);
         ss1>>from;
         ss2>>to;
         ui->lineEdit_isedge_from->clear();
         ui->lineEdit_isedge_to->clear();

         bool is_edge = undirectedweightedgraph->isEdge(from,to);
         if(is_edge)
         {
             is_isedge = true;
             isedge_line.setLine(undirectedweightedgraph->cityMap[from].pos.rx(),undirectedweightedgraph->cityMap[from].pos.ry(),undirectedweightedgraph->cityMap[to].pos.rx(),undirectedweightedgraph->cityMap[to].pos.ry());
             is_edge_string = "边";
             is_edge_string.append(to_string(from));
             is_edge_string.append("-->");
              is_edge_string.append(to_string(to));
               is_edge_string.append("的路径存在");

               qis_edge_string
                       = QString(QString::fromLocal8Bit(is_edge_string.c_str()));
               ui->textBrowser->setText( qis_edge_string);
             //QLabel自动换行
             ui->textBrowser->adjustSize();
             ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
             ui->textBrowser->setAlignment(Qt::AlignTop);


         }
         else {
             is_edge_string = "边";
             is_edge_string.append(to_string(from));
             is_edge_string.append("-->");
              is_edge_string.append(to_string(to));
               is_edge_string.append("的路径不存在");

               qis_edge_string
                       = QString(QString::fromLocal8Bit(is_edge_string.c_str()));
               ui->textBrowser->setText( qis_edge_string);
             //QLabel自动换行
             ui->textBrowser->adjustSize();
             ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
             ui->textBrowser->setAlignment(Qt::AlignTop);
         }
            is_prim = false;
         is_traverse_bfs = false;
         is_traverse_dfs = false;
        is_labelconnect =false;
         is_indegrees = false;
         is_outdegrees = false;
         is_isconnect = false;
         repaint();
    }
     if(is_directedweightedgraph)
     {

         QString qinput_from;
           QString qinput_to;
         string input_from;
          string input_to;
          QString qis_edge_string;
          string is_edge_string;
          int from,to;
         qinput_from = ui->lineEdit_isedge_from->text();
         qinput_to = ui->lineEdit_isedge_to->text();
         input_from = string((const char *)qinput_from.toLocal8Bit());
         input_to = string((const char *)qinput_to.toLocal8Bit());
          stringstream ss1(input_from);
          stringstream ss2( input_to);
          ss1>>from;
          ss2>>to;
            is_create = true;
          ui->lineEdit_isedge_from->clear();
          ui->lineEdit_isedge_to->clear();

          bool is_edge = directedweightedgraph->isEdge(from,to);
          if(is_edge)
          {
              is_isedge = true;
              for(int i = 0 ; i< directedweightedgraph->points_edge.size();i++)
              {
                  if(directedweightedgraph->points_edge[i].from = from && directedweightedgraph->points_edge[i].to == to)
                  {
                      isedge_weight = directedweightedgraph->points_edge[i];
                  }
              }


              isedge_line.setLine(directedweightedgraph->cityMap[from].pos.rx(),directedweightedgraph->cityMap[from].pos.ry(),
                                  directedweightedgraph->cityMap[to].pos.rx(),directedweightedgraph->cityMap[to].pos.ry());
              is_edge_string = "边";
              is_edge_string.append(to_string(from));
              is_edge_string.append("-->");
               is_edge_string.append(to_string(to));
                is_edge_string.append("的路径存在");

                qis_edge_string
                        = QString(QString::fromLocal8Bit(is_edge_string.c_str()));
                ui->textBrowser->setText( qis_edge_string);
              //QLabel自动换行
              ui->textBrowser->adjustSize();
              ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
              ui->textBrowser->setAlignment(Qt::AlignTop);


          }
          else {
              is_edge_string = "边";
              is_edge_string.append(to_string(from));
              is_edge_string.append("-->");
               is_edge_string.append(to_string(to));
                is_edge_string.append("的路径不存在");

                qis_edge_string
                        = QString(QString::fromLocal8Bit(is_edge_string.c_str()));
                ui->textBrowser->setText( qis_edge_string);
              //QLabel自动换行
              ui->textBrowser->adjustSize();
              ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
              ui->textBrowser->setAlignment(Qt::AlignTop);
          }
             is_prim = false;
          is_create = true;
          is_traverse_bfs = false;
          is_traverse_dfs = false;
             is_labelconnect =false;
          is_indegrees = false;
          is_outdegrees = false;
          is_isconnect = false;
          repaint();
     }
}

void Widget::on_pushButton_indegrees_clicked()
{ ui->textBrowser->clear();
    QFont ft;
    ft.setPointSize(15);
   ui->textBrowser->setFont(ft);
    is_compare = false;
 if(is_undirectedgraph)
 {

      QString qinput_to;
    string input_to;
    QString qis_indegrees_string;
    string is_indegrees_string;

     int to;

    qinput_to = ui->lineEdit_indegrees->text();

    input_to = string((const char *)qinput_to.toLocal8Bit());

     stringstream ss2( input_to);

     ss2>>to;
    graph->line_indegrees.clear();
     ui->lineEdit_indegrees->clear();
     int sum = graph->inDegrees(to);


     is_indegrees_string = "顶点";
     is_indegrees_string.append(to_string(to));

       is_indegrees_string.append("的入度为：");
        is_indegrees_string.append(to_string(sum));
       qis_indegrees_string
               = QString(QString::fromLocal8Bit(is_indegrees_string.c_str()));
       ui->textBrowser->setText( qis_indegrees_string);
     //QLabel自动换行
     ui->textBrowser->adjustSize();
     ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
     ui->textBrowser->setAlignment(Qt::AlignTop);
    is_indegrees = true;
    is_traverse_bfs = false;
    is_traverse_dfs = false;
    is_isedge = false;
    is_outdegrees = false;
    is_isconnect = false;
    is_labelconnect =false;
        repaint();
}
    if(is_directedgraph)
    {

        QString qinput_to;
      string input_to;
      QString qis_indegrees_string;
      string is_indegrees_string;
        directedgraph->line_indegrees.clear();
       int to;

      qinput_to = ui->lineEdit_indegrees->text();

      input_to = string((const char *)qinput_to.toLocal8Bit());

       stringstream ss2( input_to);

       ss2>>to;

       ui->lineEdit_indegrees->clear();
       int sum = directedgraph->inDegrees(to);


       is_indegrees_string = "顶点";
       is_indegrees_string.append(to_string(to));

         is_indegrees_string.append("的入度为：");
          is_indegrees_string.append(to_string(sum));
         qis_indegrees_string
                 = QString(QString::fromLocal8Bit(is_indegrees_string.c_str()));
         ui->textBrowser->setText( qis_indegrees_string);
       //QLabel自动换行
       ui->textBrowser->adjustSize();
       ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
       ui->textBrowser->setAlignment(Qt::AlignTop);
      is_indegrees = true;
      is_traverse_bfs = false;
      is_traverse_dfs = false;
      is_isedge = false;
      is_outdegrees = false;
      is_isconnect = false;
      is_labelconnect =false;
          repaint();
    }
    if(is_undirectedweightedgraph)
    {

        QString qinput_to;
      string input_to;
      QString qis_indegrees_string;
      string is_indegrees_string;

       int to;

      qinput_to = ui->lineEdit_indegrees->text();

      input_to = string((const char *)qinput_to.toLocal8Bit());

       stringstream ss2( input_to);

       ss2>>to;
      undirectedweightedgraph->line_indegrees.clear();
       ui->lineEdit_indegrees->clear();
       int sum = undirectedweightedgraph->inDegrees(to);


       is_indegrees_string = "顶点";
       is_indegrees_string.append(to_string(to));

         is_indegrees_string.append("的入度为：");
          is_indegrees_string.append(to_string(sum));
         qis_indegrees_string
                 = QString(QString::fromLocal8Bit(is_indegrees_string.c_str()));
         ui->textBrowser->setText( qis_indegrees_string);
       //QLabel自动换行
       ui->textBrowser->adjustSize();
       ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
       ui->textBrowser->setAlignment(Qt::AlignTop);
       is_create = true;
      is_indegrees = true;
      is_traverse_bfs = false;
      is_traverse_dfs = false;
      is_isedge = false;
      is_outdegrees = false;
      is_isconnect = false;
      is_labelconnect =false;
          repaint();
    }
    if(is_directedweightedgraph)
    {
        QString qinput_to;
      string input_to;
      QString qis_indegrees_string;
      string is_indegrees_string;

       int to;

      qinput_to = ui->lineEdit_indegrees->text();

      input_to = string((const char *)qinput_to.toLocal8Bit());

       stringstream ss2( input_to);

       ss2>>to;
      directedweightedgraph->line_indegrees.clear();
       ui->lineEdit_indegrees->clear();
       int sum = directedweightedgraph->inDegrees(to);


       is_indegrees_string = "顶点";
       is_indegrees_string.append(to_string(to));

         is_indegrees_string.append("的入度为：");
          is_indegrees_string.append(to_string(sum));
         qis_indegrees_string
                 = QString(QString::fromLocal8Bit(is_indegrees_string.c_str()));
         ui->textBrowser->setText( qis_indegrees_string);
       //QLabel自动换行
       ui->textBrowser->adjustSize();
       ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
       ui->textBrowser->setAlignment(Qt::AlignTop);
       is_create = true;
      is_indegrees = true;
      is_traverse_bfs = false;
      is_traverse_dfs = false;
      is_isedge = false;
      is_outdegrees = false;
      is_isconnect = false;
      is_labelconnect =false;
          repaint();
    }
}

void Widget::on_pushButton_outdegrees_clicked()
{   ui->textBrowser->clear();
    QFont ft;
     ft.setPointSize(15);
    ui->textBrowser->setFont(ft);
    is_compare = false;
    if(is_undirectedgraph)
    {
        QString qinput_to;
      string input_to;
      QString qis_outdegrees_string;
      string is_outdegrees_string;

       int to;

      qinput_to = ui->lineEdit_outdegrees->text();

      input_to = string((const char *)qinput_to.toLocal8Bit());

       stringstream ss2( input_to);

       ss2>>to;
       graph->line_outdegrees.clear();
       ui->lineEdit_outdegrees->clear();
       int sum = graph->outDegrees(to);


       is_outdegrees_string = "顶点";
       is_outdegrees_string.append(to_string(to));

         is_outdegrees_string.append("的出度为：");
          is_outdegrees_string.append(to_string(sum));
         qis_outdegrees_string
                 = QString(QString::fromLocal8Bit(is_outdegrees_string.c_str()));
         ui->textBrowser->setText( qis_outdegrees_string);
       //QLabel自动换行
       ui->textBrowser->adjustSize();
       ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
       ui->textBrowser->setAlignment(Qt::AlignTop);
         is_outdegrees = true;
         is_traverse_bfs = false;
         is_traverse_dfs = false;
         is_isedge = false;
         is_indegrees = false;
        is_labelconnect =false;
         is_isconnect = false;
          repaint();
    }
    if(is_directedgraph)
    {
        QString qinput_to;
      string input_to;
      QString qis_outdegrees_string;
      string is_outdegrees_string;

       int to;

      qinput_to = ui->lineEdit_outdegrees->text();

      input_to = string((const char *)qinput_to.toLocal8Bit());

       stringstream ss2( input_to);

       ss2>>to;
       directedgraph->line_outdegrees.clear();
       ui->lineEdit_outdegrees->clear();
       int sum = directedgraph->outDegrees(to);


       is_outdegrees_string = "顶点";
       is_outdegrees_string.append(to_string(to));

         is_outdegrees_string.append("的出度为：");
          is_outdegrees_string.append(to_string(sum));
         qis_outdegrees_string
                 = QString(QString::fromLocal8Bit(is_outdegrees_string.c_str()));
         ui->textBrowser->setText( qis_outdegrees_string);
       //QLabel自动换行
       ui->textBrowser->adjustSize();
       ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
       ui->textBrowser->setAlignment(Qt::AlignTop);
         is_outdegrees = true;
         is_traverse_bfs = false;
         is_traverse_dfs = false;
         is_isedge = false;
         is_indegrees = false;
        is_labelconnect =false;
         is_isconnect = false;
          repaint();
    }
    if(is_undirectedweightedgraph)
    {
        QString qinput_to;
      string input_to;
      QString qis_outdegrees_string;
      string is_outdegrees_string;

       int to;

      qinput_to = ui->lineEdit_outdegrees->text();

      input_to = string((const char *)qinput_to.toLocal8Bit());

       stringstream ss2( input_to);

       ss2>>to;
       undirectedweightedgraph->line_outdegrees.clear();
       ui->lineEdit_outdegrees->clear();
       int sum = undirectedweightedgraph->outDegrees(to);


       is_outdegrees_string = "顶点";
       is_outdegrees_string.append(to_string(to));

         is_outdegrees_string.append("的出度为：");
          is_outdegrees_string.append(to_string(sum));
         qis_outdegrees_string
                 = QString(QString::fromLocal8Bit(is_outdegrees_string.c_str()));
         ui->textBrowser->setText( qis_outdegrees_string);
       //QLabel自动换行
       ui->textBrowser->adjustSize();
       ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
       ui->textBrowser->setAlignment(Qt::AlignTop);
       is_create = true;
          is_prim = false;
         is_outdegrees = true;
         is_traverse_bfs = false;
         is_traverse_dfs = false;
         is_isedge = false;
         is_indegrees = false;
        is_labelconnect =false;
         is_isconnect = false;
          repaint();
    }
    if(is_directedweightedgraph)
    {
        QString qinput_to;
      string input_to;
      QString qis_outdegrees_string;
      string is_outdegrees_string;

       int to;

      qinput_to = ui->lineEdit_outdegrees->text();

      input_to = string((const char *)qinput_to.toLocal8Bit());

       stringstream ss2( input_to);

       ss2>>to;
       directedweightedgraph->line_outdegrees.clear();
       ui->lineEdit_outdegrees->clear();
       int sum = directedweightedgraph->outDegrees(to);


       is_outdegrees_string = "顶点";
       is_outdegrees_string.append(to_string(to));

         is_outdegrees_string.append("的出度为：");
          is_outdegrees_string.append(to_string(sum));
         qis_outdegrees_string
                 = QString(QString::fromLocal8Bit(is_outdegrees_string.c_str()));
         ui->textBrowser->setText( qis_outdegrees_string);
       //QLabel自动换行
       ui->textBrowser->adjustSize();
       ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
       ui->textBrowser->setAlignment(Qt::AlignTop);
       is_create = true;
          is_prim = false;
         is_outdegrees = true;
         is_traverse_bfs = false;
         is_traverse_dfs = false;
         is_isedge = false;
         is_indegrees = false;
        is_labelconnect =false;
         is_isconnect = false;
          repaint();
    }
}

void Widget::on_pushButton_isconnect_clicked()
{ui->textBrowser->clear();
    QFont ft;
      ft.setPointSize(15);
     ui->textBrowser->setFont(ft);
     is_compare = false;
    if(is_undirectedgraph)
    {
    QString qis_isconnects_string;
    string is_isconnects_string;
    graph->line_bfs.clear();

    if(graph->isConnect())
    {
        is_isconnects_string = "此图是连通图";

          qis_isconnects_string
                  = QString(QString::fromLocal8Bit(is_isconnects_string.c_str()));
          ui->textBrowser->setText( qis_isconnects_string);
        //QLabel自动换行
        ui->textBrowser->adjustSize();
        ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
        ui->textBrowser->setAlignment(Qt::AlignTop);
        is_isconnect = true;
    }
    else {

        is_isconnects_string = "此图不是连通图";

          qis_isconnects_string
                  = QString(QString::fromLocal8Bit(is_isconnects_string.c_str()));
          ui->textBrowser->setText( qis_isconnects_string);
        //QLabel自动换行
        ui->textBrowser->adjustSize();
        ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
        ui->textBrowser->setAlignment(Qt::AlignTop);
        is_isconnect = true;
    }
    is_traverse_bfs = false;
    is_traverse_dfs =false;

    is_isedge = false;
    is_indegrees = false;
    is_outdegrees = false;
   is_labelconnect =false;
     repaint();
     }
    if(is_directedgraph)
    {
        QString qis_isconnects_string;
        string is_isconnects_string;
        directedgraph->line_bfs.clear();
        if(directedgraph->isConnect())
        {
            is_isconnects_string = "此图是连通图";

              qis_isconnects_string
                      = QString(QString::fromLocal8Bit(is_isconnects_string.c_str()));
              ui->textBrowser->setText( qis_isconnects_string);
            //QLabel自动换行
            ui->textBrowser->adjustSize();
            ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
            ui->textBrowser->setAlignment(Qt::AlignTop);
            is_isconnect = true;
        }
        else {

            is_isconnects_string = "此图不是连通图";

              qis_isconnects_string
                      = QString(QString::fromLocal8Bit(is_isconnects_string.c_str()));
              ui->textBrowser->setText( qis_isconnects_string);
            //QLabel自动换行
            ui->textBrowser->adjustSize();
            ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
            ui->textBrowser->setAlignment(Qt::AlignTop);
            is_isconnect = true;
        }
        is_traverse_bfs = false;
        is_traverse_dfs =false;

        is_isedge = false;
        is_indegrees = false;
        is_outdegrees = false;
        is_labelconnect =false;
         repaint();
    }
    if(is_undirectedweightedgraph)
    {
        QString qis_isconnects_string;
        string is_isconnects_string;
        undirectedweightedgraph->line_bfs.clear();
        is_create = true;
        if(undirectedweightedgraph->isConnect())
        {
            is_isconnects_string = "此图是连通图";

              qis_isconnects_string
                      = QString(QString::fromLocal8Bit(is_isconnects_string.c_str()));
              ui->textBrowser->setText( qis_isconnects_string);
            //QLabel自动换行
            ui->textBrowser->adjustSize();
            ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
            ui->textBrowser->setAlignment(Qt::AlignTop);
            is_isconnect = true;
        }
        else {

            is_isconnects_string = "此图不是连通图";

              qis_isconnects_string
                      = QString(QString::fromLocal8Bit(is_isconnects_string.c_str()));
              ui->textBrowser->setText( qis_isconnects_string);
            //QLabel自动换行
            ui->textBrowser->adjustSize();
            ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
            ui->textBrowser->setAlignment(Qt::AlignTop);
            is_isconnect = true;
        }
           is_prim = false;
        is_traverse_bfs = false;
        is_traverse_dfs =false;

        is_isedge = false;
        is_indegrees = false;
        is_outdegrees = false;
       is_labelconnect =false;
         repaint();
    }
    if(is_directedweightedgraph)
    {
        QString qis_isconnects_string;
        string is_isconnects_string;
        directedweightedgraph->line_bfs.clear();
        is_create = true;
        if(directedweightedgraph->isConnect())
        {
            is_isconnects_string = "此图是连通图";

              qis_isconnects_string
                      = QString(QString::fromLocal8Bit(is_isconnects_string.c_str()));
              ui->textBrowser->setText( qis_isconnects_string);
            //QLabel自动换行
            ui->textBrowser->adjustSize();
            ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
            ui->textBrowser->setAlignment(Qt::AlignTop);
            is_isconnect = true;
        }
        else {

            is_isconnects_string = "此图不是连通图";

              qis_isconnects_string
                      = QString(QString::fromLocal8Bit(is_isconnects_string.c_str()));
              ui->textBrowser->setText( qis_isconnects_string);
            //QLabel自动换行
            ui->textBrowser->adjustSize();
            ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
            ui->textBrowser->setAlignment(Qt::AlignTop);
            is_isconnect = true;
        }
           is_prim = false;
        is_traverse_bfs = false;
        is_traverse_dfs =false;

        is_isedge = false;
        is_indegrees = false;
        is_outdegrees = false;
       is_labelconnect =false;
         repaint();
    }
}

void Widget::on_pushButton_LabelComponents_clicked()
{ui->textBrowser->clear();
    QFont ft;
      ft.setPointSize(15);
     ui->textBrowser->setFont(ft);
     is_compare = false;
    if(is_undirectedgraph)
    {


    graph->LabelComponents();
     Label_Map temp_label_map;
    for(int i = 0 ; i < graph->vexnum ; i ++)
    {
        temp_label_map.label_c = graph->labelConnect[i];
        temp_label_map.name = to_string(i);
        temp_label_map.pos = graph->cityMap[i].pos;
        Label_map_connect.push_back(temp_label_map);
    }

    ui->textBrowser->clear();
    is_traverse_bfs = false;
    is_traverse_dfs = false;
    is_isedge = false;
    is_indegrees = false;
    is_outdegrees = false;
    is_isconnect = false;
    is_labelconnect =true;
     repaint();
     }
    if(is_directedgraph)
    {
        directedgraph->LabelComponents();
         Label_Map temp_label_map;
        for(int i = 0 ; i < directedgraph->vexnum ; i ++)
        {
            temp_label_map.label_c = directedgraph->labelConnect[i];
            temp_label_map.name = to_string(i);
            temp_label_map.pos = directedgraph->cityMap[i].pos;
            Label_map_connect.push_back(temp_label_map);
        }

        ui->textBrowser->clear();
        is_traverse_bfs = false;
        is_traverse_dfs = false;
        is_isedge = false;
        is_indegrees = false;
        is_outdegrees = false;
        is_isconnect = false;
        is_labelconnect =true;
         repaint();
    }
    if(is_undirectedweightedgraph)
    {
        undirectedweightedgraph->LabelComponents();
         Label_Map temp_label_map;
        for(int i = 0 ; i < undirectedweightedgraph->vexnum ; i ++)
        {
            temp_label_map.label_c = undirectedweightedgraph->labelConnect[i];
            temp_label_map.name = to_string(i);
            temp_label_map.pos = undirectedweightedgraph->cityMap[i].pos;
            Label_map_connect.push_back(temp_label_map);
        }

        ui->textBrowser->clear();
        is_create = true;
        is_traverse_bfs = false;
        is_traverse_dfs = false;
        is_isedge = false;
           is_prim = false;
        is_indegrees = false;
        is_outdegrees = false;
        is_isconnect = false;
        is_labelconnect =true;
         repaint();
    }
    if(is_directedweightedgraph)
    {
        directedweightedgraph->LabelComponents();
         Label_Map temp_label_map;
        for(int i = 0 ; i < directedweightedgraph->vexnum ; i ++)
        {
            temp_label_map.label_c = directedweightedgraph->labelConnect[i];
            temp_label_map.name = to_string(i);
            temp_label_map.pos = directedweightedgraph->cityMap[i].pos;
            Label_map_connect.push_back(temp_label_map);
        }

        ui->textBrowser->clear();
        is_create = true;
        is_traverse_bfs = false;
        is_traverse_dfs = false;
        is_isedge = false;
           is_prim = false;
        is_indegrees = false;
        is_outdegrees = false;
        is_isconnect = false;
        is_labelconnect =true;
         repaint();
    }
}

void Widget::on_pushButton_3_clicked()//有向图
{
    ui->textBrowser->clear();
    QFont ft;
      ft.setPointSize(15);
     ui->textBrowser->setFont(ft);
     is_compare = false;
    int vexnum ;
    QString qvexnum = ui->lineEdit_vex->text();

    string str_vexnum = string((const char *)qvexnum.toLocal8Bit());

    stringstream ss1(str_vexnum);


    ss1 >> vexnum;
    directedgraph->vexnum = vexnum;
    directedgraph->points.clear();
    directedgraph->line.clear();
    directedgraph->bfs_str.clear();
    directedgraph->dfs_str.clear();
    directedgraph->line_bfs.clear();
    directedgraph->line_dfs.clear();
    point_bfs2.clear();
    point_dfs2.clear();
    line_bfs2.clear();
    line_dfs2.clear();
    directedgraph->CreatGraph();
    is_create = true;
    is_traverse_bfs = false;
    is_traverse_dfs = false;
    is_isedge = false;
    is_indegrees = false;
    is_outdegrees = false;
    is_isconnect = false;
    is_labelconnect =false;
    is_undirectedgraph = false;
    is_directedgraph = true;
    is_undirectedweightedgraph= false;
    is_directedweightedgraph = false;
    qDebug()<<"  is_directedgraph = true;";
   repaint();
}



void Widget::on_pushButton_creat_undweight_clicked()
{ ui->textBrowser->clear();
    QFont ft;
    ft.setPointSize(15);
   ui->textBrowser->setFont(ft);
     is_compare = false;
    int vexnum ;
    QString qvexnum = ui->lineEdit_vex->text();

    string str_vexnum = string((const char *)qvexnum.toLocal8Bit());

    stringstream ss1(str_vexnum);


    ss1 >> vexnum;
   undirectedweightedgraph->vexnum = vexnum;
    undirectedweightedgraph->points.clear();
    undirectedweightedgraph->line.clear();
    undirectedweightedgraph->bfs_str.clear();
    undirectedweightedgraph->dfs_str.clear();
    undirectedweightedgraph->line_bfs.clear();
    undirectedweightedgraph->line_dfs.clear();
    undirectedweightedgraph->points_isconnect.clear();
    point_bfs2.clear();
    point_dfs2.clear();
    line_bfs2.clear();
    line_dfs2.clear();
    undirectedweightedgraph->CreatGraph();
    is_create = true;
    is_traverse_bfs = false;
    is_traverse_dfs = false;
    is_isedge = false;
    is_indegrees = false;
    is_outdegrees = false;
    is_isconnect = false;
    is_labelconnect =false;
    is_undirectedgraph = false;
    is_directedgraph = false;
    is_undirectedweightedgraph= true;
    is_directedweightedgraph = false;
    is_prim = false;
   repaint();
}

void Widget::on_pushButton_add_edge_weight_clicked()
{ui->textBrowser->clear();
    QFont ft;
      ft.setPointSize(15);
     ui->textBrowser->setFont(ft);
     is_compare = false;
    if(is_undirectedweightedgraph)
    {
        QString qinput_from;
         QString qinput_weight;
          QString qinput_to;
        string input_from;
         string input_to;
         string input_weight;
         int from,to,weight;
         QString qis_add_edge_string;
         string is_add_edge_string;
        qinput_from = ui->lineEdit_add_from_weight->text();
        qinput_to = ui->lineEdit_add_to_weight->text();
        qinput_weight = ui->lineEdit_add_weight->text();
        input_from = string((const char *)qinput_from.toLocal8Bit());
        input_to = string((const char *)qinput_to.toLocal8Bit());
        input_weight= string((const char *)qinput_weight.toLocal8Bit());
         stringstream ss1(input_from);
         stringstream ss2( input_to);
          stringstream ss3( input_weight);
         ss1>>from;
         ss2>>to;
         ss3>>weight;
         ui->lineEdit_add_from_weight->clear();
         ui->lineEdit_add_to_weight->clear();
         ui->lineEdit_add_weight->clear();
         int i = undirectedweightedgraph->addEdge(from,to,weight);
         if(i == 0)
         {
             is_add_edge_string = "您输入的边不符合规范";
               qis_add_edge_string
                       = QString(QString::fromLocal8Bit(is_add_edge_string.c_str()));
               ui->textBrowser->setText( qis_add_edge_string);
             //QLabel自动换行
             ui->textBrowser->adjustSize();
             ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
             ui->textBrowser->setAlignment(Qt::AlignTop);
             is_create = true;

             is_traverse_bfs = false;
             is_traverse_dfs = false;
             is_isedge = false;
             is_indegrees = false;
             is_outdegrees = false;
             is_isconnect = false;
             is_prim = false;
             is_labelconnect =false;
            repaint();

         }
         if(i ==1)
         {
             is_add_edge_string = "从";
             is_add_edge_string.append(to_string(from));
             is_add_edge_string.append("-->");
              is_add_edge_string.append(to_string(to));
              is_add_edge_string.append("的路径已经存在");
              qis_add_edge_string
                      = QString(QString::fromLocal8Bit(is_add_edge_string.c_str()));
              ui->textBrowser->setText( qis_add_edge_string);
            //QLabel自动换行
            ui->textBrowser->adjustSize();
            ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
            ui->textBrowser->setAlignment(Qt::AlignTop);
            is_create = true;
            is_traverse_bfs = false;
            is_traverse_dfs = false;
            is_isedge = false;
            is_indegrees = false;
            is_outdegrees = false;
            is_isconnect = false;
            is_labelconnect =false;
            is_prim = false;
           repaint();
         }
         if(i ==2)
         {
             is_add_edge_string = "边";
             is_add_edge_string.append(to_string(from));
             is_add_edge_string.append("-->");
              is_add_edge_string.append(to_string(to));
              is_add_edge_string.append("添加成功,权重为");
              is_add_edge_string.append(to_string(weight));
              qis_add_edge_string
                      = QString(QString::fromLocal8Bit(is_add_edge_string.c_str()));
              ui->textBrowser->setText( qis_add_edge_string);
            //QLabel自动换行
            ui->textBrowser->adjustSize();
            ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
            ui->textBrowser->setAlignment(Qt::AlignTop);
             is_create = true;
             is_traverse_bfs = false;
             is_traverse_dfs = false;
             is_isedge = false;
             is_indegrees = false;
             is_outdegrees = false;
             is_isconnect = false;
             is_labelconnect =false;
             is_prim = false;
            repaint();
         }
    }
    if(is_directedweightedgraph)
    {
        QString qinput_from;
         QString qinput_weight;
          QString qinput_to;
        string input_from;
         string input_to;
         string input_weight;
         int from,to,weight;
         QString qis_add_edge_string;
         string is_add_edge_string;
        qinput_from = ui->lineEdit_add_from_weight->text();
        qinput_to = ui->lineEdit_add_to_weight->text();
        qinput_weight = ui->lineEdit_add_weight->text();
        input_from = string((const char *)qinput_from.toLocal8Bit());
        input_to = string((const char *)qinput_to.toLocal8Bit());
        input_weight= string((const char *)qinput_weight.toLocal8Bit());
         stringstream ss1(input_from);
         stringstream ss2( input_to);
          stringstream ss3( input_weight);
         ss1>>from;
         ss2>>to;
         ss3>>weight;
         ui->lineEdit_add_from_weight->clear();
         ui->lineEdit_add_to_weight->clear();
         ui->lineEdit_add_weight->clear();
         int i = directedweightedgraph->addEdge(from,to,weight);
         if(i == 0)
         {
             is_add_edge_string = "您输入的边不符合规范";
               qis_add_edge_string
                       = QString(QString::fromLocal8Bit(is_add_edge_string.c_str()));
               ui->textBrowser->setText( qis_add_edge_string);
             //QLabel自动换行
             ui->textBrowser->adjustSize();
             ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
             ui->textBrowser->setAlignment(Qt::AlignTop);
             is_create = true;

             is_traverse_bfs = false;
             is_traverse_dfs = false;
             is_isedge = false;
             is_indegrees = false;
             is_outdegrees = false;
             is_isconnect = false;
             is_prim = false;
             is_labelconnect =false;
            repaint();

         }
         if(i ==1)
         {
             is_add_edge_string = "从";
             is_add_edge_string.append(to_string(from));
             is_add_edge_string.append("-->");
              is_add_edge_string.append(to_string(to));
              is_add_edge_string.append("的路径已经存在");
              qis_add_edge_string
                      = QString(QString::fromLocal8Bit(is_add_edge_string.c_str()));
              ui->textBrowser->setText( qis_add_edge_string);
            //QLabel自动换行
            ui->textBrowser->adjustSize();
            ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
            ui->textBrowser->setAlignment(Qt::AlignTop);
            is_create = true;
            is_traverse_bfs = false;
            is_traverse_dfs = false;
            is_isedge = false;
            is_indegrees = false;
            is_outdegrees = false;
            is_isconnect = false;
            is_labelconnect =false;
            is_prim = false;
           repaint();
         }
         if(i ==2)
         {
             is_add_edge_string = "边";
             is_add_edge_string.append(to_string(from));
             is_add_edge_string.append("-->");
              is_add_edge_string.append(to_string(to));
              is_add_edge_string.append("添加成功,权重为");
              is_add_edge_string.append(to_string(weight));
              qis_add_edge_string
                      = QString(QString::fromLocal8Bit(is_add_edge_string.c_str()));
              ui->textBrowser->setText( qis_add_edge_string);
            //QLabel自动换行
            ui->textBrowser->adjustSize();
            ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
            ui->textBrowser->setAlignment(Qt::AlignTop);
             is_create = true;
             is_traverse_bfs = false;
             is_traverse_dfs = false;
             is_isedge = false;
             is_indegrees = false;
             is_outdegrees = false;
             is_isconnect = false;
             is_labelconnect =false;
             is_prim = false;
            repaint();
         }
    }
}

void Widget::on_pushButton_delete_edge_weight_clicked()
{ui->textBrowser->clear();
    QFont ft;
      ft.setPointSize(15);
     ui->textBrowser->setFont(ft);
     is_compare = false;
    if(is_undirectedweightedgraph)
    {
        QString qis_delete_edge_string;
        string is_delete_edge_string;
   QString qinput_from;
     QString qinput_to;
   string input_from;
    string input_to;
    int from,to;
   qinput_from = ui->lineEdit_delete_from_weight->text();
   qinput_to = ui->lineEdit_delete_to_weight->text();
   input_from = string((const char *)qinput_from.toLocal8Bit());
   input_to = string((const char *)qinput_to.toLocal8Bit());
    stringstream ss1(input_from);
    stringstream ss2( input_to);
    ss1>>from;
    ss2>>to;
    ui->lineEdit_delete_from_weight->clear();
    ui->lineEdit_delete_to_weight->clear();
    int i = undirectedweightedgraph->deleteEdge(from,to);
    if(i == 0)
    {
        is_delete_edge_string = "您输入的边不符合规范";
          qis_delete_edge_string
                  = QString(QString::fromLocal8Bit(is_delete_edge_string.c_str()));
          ui->textBrowser->setText( qis_delete_edge_string);
        //QLabel自动换行
        ui->textBrowser->adjustSize();
        ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
        ui->textBrowser->setAlignment(Qt::AlignTop);
        is_create = true;
        is_prim = false;
        is_traverse_bfs = false;
        is_traverse_dfs = false;
        is_isedge = false;
        is_indegrees = false;
        is_outdegrees = false;
        is_isconnect = false;
        is_labelconnect =false;
       repaint();
    }

    if(i ==2)
    {
        is_delete_edge_string = "边";
        is_delete_edge_string.append(to_string(from));
        is_delete_edge_string.append("-->");
         is_delete_edge_string.append(to_string(to));
         is_delete_edge_string.append("删除成功");
         qis_delete_edge_string
                 = QString(QString::fromLocal8Bit(is_delete_edge_string.c_str()));
         ui->textBrowser->setText( qis_delete_edge_string);
       //QLabel自动换行
       ui->textBrowser->adjustSize();
       ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
       ui->textBrowser->setAlignment(Qt::AlignTop);
        is_create = true;
        is_traverse_bfs = false;
        is_traverse_dfs = false;
        is_isedge = false;
        is_indegrees = false;
        is_outdegrees = false;
        is_isconnect = false;
        is_labelconnect =false;
       repaint();
    }
    if(i ==1)
    {
        is_delete_edge_string = "从";
        is_delete_edge_string.append(to_string(from));
        is_delete_edge_string.append("-->");
         is_delete_edge_string.append(to_string(to));
         is_delete_edge_string.append("的路径不存在");
         qis_delete_edge_string
                 = QString(QString::fromLocal8Bit(is_delete_edge_string.c_str()));
         ui->textBrowser->setText( qis_delete_edge_string);
       //QLabel自动换行
       ui->textBrowser->adjustSize();
       ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
       ui->textBrowser->setAlignment(Qt::AlignTop);
       is_create = true;
       is_traverse_bfs = false;
       is_traverse_dfs = false;
       is_isedge = false;
       is_indegrees = false;
       is_outdegrees = false;
       is_isconnect = false;
       is_labelconnect =false;
      repaint();
    }

    }
    if(is_directedweightedgraph)
    {
        QString qis_delete_edge_string;
        string is_delete_edge_string;
   QString qinput_from;
     QString qinput_to;
   string input_from;
    string input_to;
    int from,to;
   qinput_from = ui->lineEdit_delete_from_weight->text();
   qinput_to = ui->lineEdit_delete_to_weight->text();
   input_from = string((const char *)qinput_from.toLocal8Bit());
   input_to = string((const char *)qinput_to.toLocal8Bit());
    stringstream ss1(input_from);
    stringstream ss2( input_to);
    ss1>>from;
    ss2>>to;
    ui->lineEdit_delete_from_weight->clear();
    ui->lineEdit_delete_to_weight->clear();
    int i = directedweightedgraph->deleteEdge(from,to);
    if(i == 0)
    {
        is_delete_edge_string = "您输入的边不符合规范";
          qis_delete_edge_string
                  = QString(QString::fromLocal8Bit(is_delete_edge_string.c_str()));
          ui->textBrowser->setText( qis_delete_edge_string);
        //QLabel自动换行
        ui->textBrowser->adjustSize();
        ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
        ui->textBrowser->setAlignment(Qt::AlignTop);
        is_create = true;
        is_prim = false;
        is_traverse_bfs = false;
        is_traverse_dfs = false;
        is_isedge = false;
        is_indegrees = false;
        is_outdegrees = false;
        is_isconnect = false;
        is_labelconnect =false;
       repaint();
    }

    if(i ==2)
    {
        is_delete_edge_string = "边";
        is_delete_edge_string.append(to_string(from));
        is_delete_edge_string.append("-->");
         is_delete_edge_string.append(to_string(to));
         is_delete_edge_string.append("删除成功");
         qis_delete_edge_string
                 = QString(QString::fromLocal8Bit(is_delete_edge_string.c_str()));
         ui->textBrowser->setText( qis_delete_edge_string);
       //QLabel自动换行
       ui->textBrowser->adjustSize();
       ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
       ui->textBrowser->setAlignment(Qt::AlignTop);
        is_create = true;
        is_traverse_bfs = false;
        is_traverse_dfs = false;
        is_isedge = false;
        is_indegrees = false;
        is_outdegrees = false;
        is_isconnect = false;
        is_labelconnect =false;
       repaint();
    }
    if(i ==1)
    {
        is_delete_edge_string = "从";
        is_delete_edge_string.append(to_string(from));
        is_delete_edge_string.append("-->");
         is_delete_edge_string.append(to_string(to));
         is_delete_edge_string.append("的路径不存在");
         qis_delete_edge_string
                 = QString(QString::fromLocal8Bit(is_delete_edge_string.c_str()));
         ui->textBrowser->setText( qis_delete_edge_string);
       //QLabel自动换行
       ui->textBrowser->adjustSize();
       ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
       ui->textBrowser->setAlignment(Qt::AlignTop);
       is_create = true;
       is_traverse_bfs = false;
       is_traverse_dfs = false;
       is_isedge = false;
       is_indegrees = false;
       is_outdegrees = false;
       is_isconnect = false;
       is_labelconnect =false;
      repaint();
    }
    }
}



void Widget::on_pushButton_prim_clicked()
{   ui->textBrowser->clear();
    QFont ft;
      ft.setPointSize(15);
     ui->textBrowser->setFont(ft);
     is_compare = false;
    if(is_undirectedweightedgraph)
    {
        QString qinput;
        string output;

        QString qoutput;
        string input;
        int i;

        qinput = ui->lineEdit_prim->text();
        input = string((const char *)qinput.toLocal8Bit());
        undirectedweightedgraph->line_prim.clear();
        undirectedweightedgraph->point_prim.clear();
        point_prim2.clear();
        line_prim2.clear();
        output.clear();
        output_prim.clear();
        ui->textBrowser->setText("");


         i = undirectedweightedgraph->LocationVex(input);
           int sum = undirectedweightedgraph->Prim(i);

           output_prim.erase(0, output.length());

          output_prim.append("\n最小生成树结果：\n");

        is_create = true;
        is_prim = true;
        is_traverse_bfs = false;
        is_traverse_dfs =false;
        is_labelconnect =false;
        is_isedge = false;
        is_indegrees = false;
        is_outdegrees = false;
        is_isconnect = false;
        qDebug()<<"undirectedweightedgraph->point_prim.size()";
        qDebug()<<undirectedweightedgraph->point_prim.size();
        while(!undirectedweightedgraph->point_prim.empty())
        {

            Map temp_map ;
            temp_map.pos = undirectedweightedgraph->point_prim[0].pos;
            temp_map.name = undirectedweightedgraph->point_prim[0].name;

           point_prim2.push_back(temp_map);

           output_prim.append( temp_map.name+"-->");

           qoutput_prim
                   = QString(QString::fromLocal8Bit( output_prim.c_str()));
           ui->textBrowser->setText( qoutput_prim);
         //QLabel自动换行
         ui->textBrowser->adjustSize();
         ui->textBrowser->setGeometry(QRect(180, 500, 540, 280));
         ui->textBrowser->setAlignment(Qt::AlignTop);
         qDebug()<<"undirectedweightedgraph->point_prim.size()";
           qDebug()<<undirectedweightedgraph->line_prim.size();
         undirectedweightedgraph->point_prim.erase(undirectedweightedgraph->point_prim.begin());
            if(!undirectedweightedgraph->line_prim.empty())
            {
                QLine temp_line = undirectedweightedgraph->line_prim[0];
               line_prim2.push_back(temp_line);
                undirectedweightedgraph->line_prim.erase(undirectedweightedgraph->line_prim.begin());


            }


            for(i = 0 ; i<200000 ; i++)
            {
                 qDebug()<<"1";
            }

           repaint();
            qApp->processEvents();

        }
         output_prim.append("\n");
         output_prim.append("最终耗费值为：");
          output_prim.append(to_string(sum));
          output_prim.append("\n");
        ui->textBrowser->setText(QString(QString::fromLocal8Bit(output_prim.c_str())));
      //QLabel自动换行
      ui->textBrowser->adjustSize();
      ui->textBrowser->setGeometry(QRect(180, 500, 540, 280));
      ui->textBrowser->setAlignment(Qt::AlignTop);
            is_create = false;

           repaint();
           qApp->processEvents();

    }
    if(is_directedweightedgraph)
    {
        QString qinput;
        string output;

        QString qoutput;
        string input;
        int i;

        qinput = ui->lineEdit_prim->text();
        input = string((const char *)qinput.toLocal8Bit());
        directedweightedgraph->line_prim.clear();
        directedweightedgraph->point_prim.clear();
        point_prim2.clear();
        line_prim2.clear();
        output.clear();
        output_prim.clear();
        ui->textBrowser->setText("");


         i = directedweightedgraph->LocationVex(input);
           int sum = directedweightedgraph->Prim(i);

           output_prim.erase(0, output.length());

          output_prim.append("\n最小生成树结果：\n");

        is_create = true;
        is_prim = true;
        is_traverse_bfs = false;
        is_traverse_dfs =false;
        is_labelconnect =false;
        is_isedge = false;
        is_indegrees = false;
        is_outdegrees = false;
        is_isconnect = false;

        while(!directedweightedgraph->point_prim.empty())
        {

            Map temp_map ;
            temp_map.pos = directedweightedgraph->point_prim[0].pos;
            temp_map.name = directedweightedgraph->point_prim[0].name;

           point_prim2.push_back(temp_map);

           output_prim.append( temp_map.name+"-->");

           qoutput_prim
                   = QString(QString::fromLocal8Bit( output_prim.c_str()));
           ui->textBrowser->setText( qoutput_prim);
         //QLabel自动换行
         ui->textBrowser->adjustSize();
         ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
         ui->textBrowser->setAlignment(Qt::AlignTop);

         directedweightedgraph->point_prim.erase(directedweightedgraph->point_prim.begin());
            if(!directedweightedgraph->line_prim.empty())
            {
                QLine temp_line = directedweightedgraph->line_prim[0];
               line_prim2.push_back(temp_line);
                directedweightedgraph->line_prim.erase(directedweightedgraph->line_prim.begin());


            }


            for(i = 0 ; i<200000 ; i++)
            {
                 qDebug()<<"1";
            }

           repaint();
            qApp->processEvents();

        }
         output_prim.append("\n");
         output_prim.append("最终耗费值为：");
          output_prim.append(to_string(sum));
          output_prim.append("\n");
        ui->textBrowser->setText(QString(QString::fromLocal8Bit(output_prim.c_str())));
      //QLabel自动换行
      ui->textBrowser->adjustSize();
      ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
      ui->textBrowser->setAlignment(Qt::AlignTop);
            is_create = false;

           repaint();
           qApp->processEvents();
    }

}



void Widget::on_pushButton_creat_dweight_clicked()
{ ui->textBrowser->clear();
    QFont ft;
      ft.setPointSize(15);
     ui->textBrowser->setFont(ft);
     is_compare = false;
    int vexnum ;
    QString qvexnum = ui->lineEdit_vex->text();

    string str_vexnum = string((const char *)qvexnum.toLocal8Bit());

    stringstream ss1(str_vexnum);


    ss1 >> vexnum;
    directedweightedgraph->vexnum = vexnum;
    directedweightedgraph->points.clear();
    directedweightedgraph->line.clear();
    directedweightedgraph->bfs_str.clear();
    directedweightedgraph->dfs_str.clear();
    directedweightedgraph->line_bfs.clear();
    directedweightedgraph->line_dfs.clear();
    directedweightedgraph->points_isconnect.clear();
    point_bfs2.clear();
    point_dfs2.clear();
    line_bfs2.clear();
    line_dfs2.clear();
    directedweightedgraph->CreatGraph();
    is_create = true;
    is_traverse_bfs = false;
    is_traverse_dfs = false;
    is_isedge = false;
    is_indegrees = false;
    is_outdegrees = false;
    is_isconnect = false;
    is_labelconnect =false;
    is_undirectedgraph = false;
    is_directedgraph = false;
    is_undirectedweightedgraph= false;
    is_directedweightedgraph = true;
    is_prim = false;
   repaint();
}
void  Widget::on_pushButton_compare_clicked()
{
//    ui->textBrowser->clear();
//    QFont ft;
//      ft.setPointSize(10);

//     ui->textBrowser->setFont(ft);
//    QString qinput;
//    string input;

//    graph->dfs_str.clear();
//    graph->dfs_str_recursion.clear();

//    qinput = ui->lineEdit_compare->text();
//    input = string((const char *)qinput.toLocal8Bit());
//    graph->count = atoi(input.c_str());
//    graph->Compare_DFS_DFSWithRecursion(atoi(input.c_str()));
    string dfs_str2;
//    string dfs_str_withrecursion2;
    QString qdfs_str;
//    QString qdfs_str_withrecursion;
//    dfs_str2.clear();
//    qdfs_str.clear();

//      dfs_str2.append("随机构建了");
//      dfs_str2.append(input);
//      dfs_str2.append("个顶点的图\n");
//    dfs_str2.append("非递归dfs的路径为：\n");
//    dfs_str2.append(graph->dfs_str);
//    dfs_str2.append("\n");
//    dfs_str2.append("非递归dfs用时为：");
//    dfs_str2.append(to_string(graph->totaltime_dfs));
//     dfs_str2.append("\n");



//     dfs_str2.append("\n递归dfs的路径为：\n");
//    dfs_str2.append(graph->dfs_str_recursion);
//   dfs_str2.append("\n");




    graph->pointf_dfs.clear();
    graph->pointf_dfs_withrecursion.clear();
    graph->compare_paint();
    is_traverse = false;
    is_create = false;
    is_traverse_bfs = false;
    is_traverse_dfs = false;
    is_isedge = false;
    is_indegrees = false;
    is_outdegrees = false;
    is_isconnect = false;
    is_labelconnect = false;
    is_undirectedgraph = false;
    is_directedgraph =false;
    is_undirectedweightedgraph= false;
    is_directedweightedgraph = false;
    is_prim = false;
    is_compare = true;
        dfs_str2.append("随机构造若干顶点的图，绘制出运行时间的曲线，可以明显看出递归的dfs的性能更好，并且随着点数的增加，递归dfs的性能越来越好");

         dfs_str2.append("\n");

        qdfs_str = QString(QString::fromLocal8Bit( dfs_str2.c_str()));
        ui->textBrowser->setText( qdfs_str);
        ui->textBrowser->adjustSize();
          ui->textBrowser->setWordWrap(true);
         ui->textBrowser->setGeometry(QRect(180, 600, 540, 280));
        ui->textBrowser->setAlignment(Qt::AlignTop);
        dfs_str2.clear();
        qdfs_str.clear();
    repaint();
}



