#include "directedweightedgraph.h"
#include<iostream>
#include<cstdio>
#include<cstring>
#include <QCoreApplication>
#include "undirectedweightedgraph.h"
#include <queue>
#include<QDebug>
#include <stack>
#define MAX 100
DirectedWeightedGraph::DirectedWeightedGraph():UndirectedWeightedGraph()
{

}

DirectedWeightedGraph::~DirectedWeightedGraph()
{
    delete []cityMap;
    delete [] close_edge;
}

void DirectedWeightedGraph::CreatGraph()
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

                        m_pMatrix[i][j]  =u%2;
                         if(m_pMatrix[i][j] ==1 )
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

int DirectedWeightedGraph::deleteEdge(int from, int to)
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

        m_pWeightMatrix[from][to] = 100000;

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

int DirectedWeightedGraph::addEdge(int from, int to, int weight)
{
    if ((from < 0 || from > vexnum) && (to < 0 || to > vexnum)) {

          return  0;
       } else if (m_pMatrix[from][to] == 1) {

           return 1;
    }else {
        m_pMatrix[from][to] = 1;
        m_pWeightMatrix[from][to] = weight;

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
