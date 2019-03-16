#include "directedgraph.h"
#include"graph.h"
#include <queue>
#include<stack>
#include <fstream>
#include <QCoreApplication>
#include<QDebug>
#define MAX 100


DirectedGraph::~DirectedGraph()
{
    delete []cityMap;
}

void DirectedGraph::CreatGraph()
{
    qDebug()<<"DirectedGraph::CreatGraph()";
    int a[] = {180,290,290,360,360,430,430,550};
    int b[] = {300,230,370,100,500,370,230,300};
    for(int i = 0 ; i< 8 ; i++)
    {
        for(int j = 0 ; j< 8 ; j++)
        {
            m_pMatrix[i][j] = 0;

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

               if(j>i&&count <10)
               {
                   int u = (double)rand() / (RAND_MAX + 1) * (0 - 10000) + 10000;

                   m_pMatrix[i][j]  = u%2;

                    if(m_pMatrix[i][j] ==1)
                    {
                        count++;
                    }
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
        }


    }


}
}

int DirectedGraph::addEdge(int from,int to)
{
    if ((from < 0 || from > vexnum) && (to < 0 || to > vexnum)) {

          return  0;
       } else if (m_pMatrix[from][to] == 1) {

           return 1;
    }else {
        m_pMatrix[from][to] = 1;
        QLine temp_line;
        temp_line.setLine(cityMap[from].pos.rx(),cityMap[from].pos.ry(),cityMap[to].pos.rx(),cityMap[to].pos.ry());
        line.push_back(temp_line);

        return 2;

}

}

int DirectedGraph::deleteEdge(int from,int to)
{


    if ((from < 0 || from > vexnum) && (to < 0 || to >  vexnum)) {

           return 0;
       } else if (m_pMatrix[from][to] == 0) {

           return 1;
       } else
    {
        m_pMatrix[from][to] = 0;
        line.clear();
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
                   }


               }


           }
           return 2;
    }


}

int DirectedGraph::inDegrees(int to)
{
    QLine temp_line;
   int sum = 0;
     for (int i = 0; i < vexnum; i++) {
         if (m_pMatrix[i][to] == 1&&to>i) {
             sum++;
             temp_line.setLine(cityMap[i].pos.rx(),cityMap[i].pos.ry(),cityMap[to].pos.rx(),cityMap[to].pos.ry());
             line_indegrees.push_back(temp_line);
         }
     }
     qDebug()<<" DirectedGraph::inDegrees";
     return sum;

}

int DirectedGraph::outDegrees(int from)
{
    int sum = 0;
     QLine temp_line;
       for(int i = 0 ; i< vexnum ; i++)
       {
           if(m_pMatrix[from][i] ==1&&i>from)
           {
               sum++;
               temp_line.setLine(cityMap[from].pos.rx(),cityMap[from].pos.ry(),cityMap[i].pos.rx(),cityMap[i].pos.ry());
               line_outdegrees.push_back(temp_line);
           }
       }
       qDebug()<<" DirectedGraph::outDegrees";
       return  sum;
}

void DirectedGraph::BFS_Traverse(int start_point_index)
{
    for (int i = 0; i < vexnum; ++i)
    {
        visited[i] = 0;
    }

    BFS(start_point_index);
}

void DirectedGraph::DFS_Traverse(int start_point_index)
{
    for (int i = 0; i < vexnum; ++i)
    {
        visited[i] = 0;
    }

    DFS(start_point_index);
}

void DirectedGraph::BFS(int i)
{
    visited[i] = 1;
    bfs_str.append(to_string(i) + "->");
    queue<int> q;
    q.push(i);
    int p;
    QPoint pos;
    QLine temp_line;
    Map temp_map,temp_map_light;

    temp_map.pos =cityMap[i].pos;
    temp_map.name = to_string(i);



    points_bfs.push_back(temp_map);


    while (!q.empty()) {
        p = q.front();
        q.pop();
        for(int j = 0 ; j < vexnum ; j++)
        {
            if(m_pMatrix[p][j] == 1 && visited[j] ==0&&j>p)
            {
                temp_map_light.pos = cityMap[p].pos;
                 temp_map_light.name = to_string(p);
                 points_bfs_light.push_back(temp_map_light);
                q.push(j);
                visited[j] = 1;
                 bfs_str.append(to_string(j) + "->");
//                temp_line.setLine(cityMap[p].pos.rx()-5,cityMap[p].pos.ry()-5,cityMap[j].pos.rx()-5,cityMap[j].pos.ry()-5);

                   temp_line.setLine(cityMap[p].pos.rx(),cityMap[p].pos.ry(),cityMap[j].pos.rx(),cityMap[j].pos.ry());
                   temp_map.pos =cityMap[j].pos;
                   temp_map.name = to_string(j);


                   points_bfs.push_back(temp_map);



                line_bfs.push_back(temp_line);

            }
        }
    }
}

void DirectedGraph::DFS(int i)
{
    stack<int> s;
       s.push(i);
      dfs_str.append(to_string(i) + "->");
          QLine temp_line;
          Map temp_map,temp_map_light;
          temp_map.pos =cityMap[i].pos;
          temp_map.name = to_string(i);
          points_dfs.push_back(temp_map);

//          temp_map_light = temp_map;
//          points_dfs_light.push_back(temp_map_light);
       visited[i] = 1;
       int w;
       bool flag;
       while (!s.empty()) {
           w = s.top();
           flag = false;
           for (int j = 0; j < vexnum; j++) {
               if (!visited[j] && m_pMatrix[w][j] == 1&&j>w) {
                   temp_map_light.pos =cityMap[w].pos;
                 temp_map_light.name = to_string(w);
               points_dfs_light.push_back(temp_map_light);

                   s.push(j);
                   dfs_str.append(to_string(j) + "->");
                   temp_line.setLine(cityMap[w].pos.rx(),cityMap[w].pos.ry(),cityMap[j].pos.rx(),cityMap[j].pos.ry());
                    line_dfs.push_back(temp_line);
                   visited[j] = 1;

                           temp_map.pos =cityMap[j].pos;
                           temp_map.name = to_string(j);
                           points_dfs.push_back(temp_map);

                   flag = true;
                   break;
               }
           }
           if (flag == false) {
               s.pop();
           }
       }
}

void DirectedGraph::LabelComponents()
{
    for(int i = 0 ; i<vexnum ; i++)
        {
            labelConnect[i] = 0;
        }
        int labelcount = 0;
        for(int i = 0 ; i<vexnum ; i++)
        {

            if(labelConnect[i] == 0)
            {
                labelcount++;
                queue<int> q;
                q.push(i);
                labelConnect[i] = labelcount;

                int w ;
                while (!q.empty())
                {
                    w = q.front();
                    q.pop();
                    for(int j = 0 ; j<vexnum ; j++)
                    {
                        if(m_pMatrix[w][j] != 0 && labelConnect[j] == 0&&j>w)
                        {
                            q.push(j);
                           labelConnect[j] = labelcount;

                        }


                    }
                }

            }
        }

}

