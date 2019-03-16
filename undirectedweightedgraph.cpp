#include "undirectedweightedgraph.h"
#include<iostream>
#include<cstdio>
#include<cstring>
#include <QCoreApplication>
#include "graph.h"
#include <queue>
#include<QDebug>
#include <stack>
#define MAX 100
UndirectedWeightedGraph::UndirectedWeightedGraph():Graph()
{
    close_edge = new Assis_array[vexnum + 1];
}

UndirectedWeightedGraph::~UndirectedWeightedGraph()
{
    delete []cityMap;
    delete [] close_edge;
}

void UndirectedWeightedGraph::CreatGraph()
{

    points_edge.clear();
    int a[] = {180,290,290,360,360,430,430,550};
    int b[] = {300,230,370,100,500,370,230,300};
    for(int i = 0 ; i< 8 ; i++)
    {
        for(int j = 0 ; j< 8 ; j++)
        {
            m_pMatrix[i][j] = 0;
            m_pWeightMatrix[i][j] = 100000;

        }
    }
        int count = 0;
    srand(time(NULL));
       for (int i = 0; i < 8; i++)
       {
           for(int j = 7 ; j>=0 ; j--)
           {
                   if(j==i)
                   {
                        m_pMatrix[i][j]  = 0;


                   }

                   if(j>i&&count < 8)
                   {
                       int u = (double)rand() / (RAND_MAX + 1) * (0 - 10000) + 10000;

                       m_pMatrix[i][j]  = u%2;
                        m_pMatrix[j][i]  = u%2;
                        if(m_pMatrix[i][j] ==1 && m_pMatrix[j][i]  ==1)
                        {
                            count++;
                        }

                   }




           }


       }
       for(int i = 0 ; i < 8 ; i++)
       {
           for(int j = 0 ; j< 8 ; j++)
           {
               if(m_pMatrix[i][j] == 1 && j>i)
               {
                    int u = (double)rand() / (RAND_MAX + 1) * (0 - 10000) + 10000;
                    m_pWeightMatrix[i][j] = u%15;
                    m_pWeightMatrix[j][i] = u%15;
               }
           }
       }

    QString qpath;
    string path;
    qpath = QCoreApplication::applicationDirPath();
    path = string((const char *)qpath.toLocal8Bit());
    int x, y;

    for (int i = 0; i < vexnum; ++i)
    {

        x = a[i];
        y = b[i];
        cityMap[i].pos.setX(x);
        cityMap[i].pos.setY(y);
        cityMap[i].name = to_string(i);
    }
    Edge temp_edge;

//    for(int i = 0 ; i<vexnum ; i++)
//    {
//        for(int j = 0 ; j < vexnum ; j++)
//        {
//            if(m_pMatrix[i][j] == 1 && j>i)
//            {
//                  qDebug()<<"m_pMatrix[i][j] == 1 && j>i";
//                temp_edge.from = i;
//                temp_edge.to = j;
//                temp_edge.weight = to_string(m_pWeightMatrix[i][j]);
//                float x0 = cityMap[i].pos.rx()/3 + (2*cityMap[j].pos.rx())/3;
//                float y0 = cityMap[i].pos.ry()/3 + (2*cityMap[j].pos.ry())/3;
//                temp_edge.location = QPoint(x0,y0);
//                points_edge.push_back(temp_edge);

//            }
//        }
//    }
 string v1, v2;
    //头插法
 QLine temp_line;
    for (int i = 0; i < vexnum; ++i)
    {
            //points 为了画路线
        for (int j = 0; j < vexnum; ++j)
        {
            if(j>i&&m_pMatrix[i][j] == 1)
            {
                temp_line.setLine(cityMap[i].pos.rx(),cityMap[i].pos.ry(),cityMap[j].pos.rx(),cityMap[j].pos.ry());
                line.push_back(temp_line);
                temp_edge.from = i;
                temp_edge.to = j;
                temp_edge.weight = to_string(m_pWeightMatrix[i][j]);
                float x0 = cityMap[i].pos.rx()/3 + (2*cityMap[j].pos.rx())/3;
                float y0 = cityMap[i].pos.ry()/3 + (2*cityMap[j].pos.ry())/3;
                temp_edge.location = QPoint(x0,y0);
                points_edge.push_back(temp_edge);

            }


        }


    }

}

int UndirectedWeightedGraph::addEdge(int from, int to, int weight)
{
    if ((from < 0 || from > vexnum) && (to < 0 || to > vexnum)) {

          return  0;
       } else if (m_pMatrix[from][to] == 1) {

           return 1;
    }else {
        m_pMatrix[from][to] = 1;
        m_pMatrix[to][from] = 1;
        m_pWeightMatrix[from][to] = weight;
        m_pWeightMatrix[to][from] = weight;
        QLine temp_line;
        temp_line.setLine(cityMap[from].pos.rx(),cityMap[from].pos.ry(),cityMap[to].pos.rx(),cityMap[to].pos.ry());
        line.push_back(temp_line);
         Edge temp_edge;
         temp_edge.from = from;
         temp_edge.to = to;
         temp_edge.weight = to_string(weight);
         float x0 = cityMap[from].pos.rx()/3 + (2*cityMap[to].pos.rx())/3;
         float y0 = cityMap[from].pos.ry()/3 + (2*cityMap[to].pos.ry())/3;
         temp_edge.location = QPoint(x0,y0);
         points_edge.push_back(temp_edge);
        return 2;

}



}

int UndirectedWeightedGraph::deleteEdge(int from, int to)
{
    if ((from < 0 || from > vexnum) && (to < 0 || to >  vexnum))
    {

           return 0;
       }
    if (m_pMatrix[from][to] == 0)
    {

           return 1;
       }
    if(m_pMatrix[from][to] == 1)
    {
        m_pMatrix[from][to] = 0;
        m_pMatrix[to][from] = 0;
        m_pWeightMatrix[from][to] = 100000;
        m_pWeightMatrix[to][from] = 100000;
        line.clear();
         points_edge.clear();
        QLine temp_line;
        Edge temp_edge;
           for (int i = 0; i < vexnum; ++i)
           {
                   //points 为了画路线
               for (int j = 0; j < vexnum; ++j)
               {
                   if(j>i&&m_pMatrix[i][j] == 1)
                   {
                       temp_line.setLine(cityMap[i].pos.rx(),cityMap[i].pos.ry(),cityMap[j].pos.rx(),cityMap[j].pos.ry());
                       line.push_back(temp_line);

                       temp_edge.from = i;
                       temp_edge.to = j;
                       temp_edge.weight = to_string(m_pWeightMatrix[i][j]);
                       float x0 = cityMap[i].pos.rx()/3 + (2*cityMap[j].pos.rx())/3;
                       float y0 = cityMap[i].pos.ry()/3 + (2*cityMap[j].pos.ry())/3;
                       temp_edge.location = QPoint(x0,y0);
                       points_edge.push_back(temp_edge);
                   }


               }


           }
    return 2;



       }


}

int UndirectedWeightedGraph::Prim(int begin)
{
    int sum = 0;
       //进行close_edge的初始化，更加开始起点进行初始化
       for (int j = 0; j < vexnum; j++)
       {
           if(j != begin)
           {
               close_edge[j].start = begin;
               close_edge[j].end = j;
               close_edge[j].weight = m_pWeightMatrix[begin][j];
           }



       }
       //把起点的close_edge中的值设置为-1，代表已经加入到集合U了

       close_edge[begin].weight = -1;
       Map temp_point;
       temp_point.name = to_string(begin);
       temp_point.pos  = cityMap[begin].pos;
       point_prim.push_back(temp_point);
       //访问剩下的顶点，并加入依次加入到集合U
       int index = 0;
       for(int j = 0 ; j<vexnum -1 ; j++)
       {
           int k;
           int min = 100000;
           //寻找数组close_edge中权重最小的那个边
           for( k = 0 ; k<vexnum; k ++)
           {
               if(close_edge[k].weight != -1)
               {
                   if(close_edge[k].weight <min)
                   {
                       min = close_edge[k].weight;
                       index = k;
                   }
               }
           }
           //将权重最小的那条边的终点也加入到集合U
           sum += close_edge[index].weight;
           close_edge[index].weight = -1;
           temp_point.name = to_string(index);
           temp_point.pos  = cityMap[index].pos;
           point_prim.push_back(temp_point);
           QLine temp_line;
           temp_line.setP1(cityMap[close_edge[index].start].pos);
           temp_line.setP2(cityMap[close_edge[index].end].pos) ;
           line_prim.push_back(temp_line);
           line_prim_light.push_back(temp_line);

           //更新我们的close_edge数组。
           for( k = 0 ; k< vexnum ; k++)
           {
               if(m_pWeightMatrix[close_edge[index].end][k] < close_edge[k].weight)
               {
                   close_edge[k].weight = m_pWeightMatrix[close_edge[index].end][k];
                   close_edge[k].start = close_edge[index].end;
                   close_edge[k].end  = k;
               }
           }
       }

    return  sum;
}

