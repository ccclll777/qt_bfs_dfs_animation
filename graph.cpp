    #include "graph.h"
#include <queue>
#include<stack>
#include <fstream>
#include <QCoreApplication>
#include<QDebug>
#define MAX 100
//辅助变量，记录该顶点是否被访问过



Graph::Graph()
{
       vexnum = 15;
       edgenum = 15;

       cityMap = new Map[MAX];

       //    int a[] = {200,300,400,500,250,400,500,200,300,400,500,250,350,450};
       //    int b[] = {50,75,75,50,160,185,160,250,290,290,250,350,380,350};
       //    int a[] = {90,180,180,260,260,300,410,460,460,540,540,630};
       //    int b[] = {350,300,400,200,500,350,350,500,200,400,300,350};
       //        int a[] = {160,270,270,360,360,450,450,570};
       //        int b[] = {350,300,400,200,500,400,300,350};
}

Graph::~Graph()
{
    delete []cityMap;
}

void Graph::CreatGraph()
{
//图的顶点坐标
    int a[] = {180,290,290,360,360,430,430,550};
    int b[] = {300,230,370,100,500,370,230,300};
    //对矩阵进行初始化操作
    for(int i = 0 ; i< 8 ; i++)
    {
        for(int j = 0 ; j< 8 ; j++)
        {
            m_pMatrix[i][j] = 0;

        }
    }
        int count = 0;
        //随机出图的边
    srand(time(NULL));
       for (int i = 0; i < 8; i++)
       {
           for(int j = 7 ; j>=0 ; j--)
           {
                   if(j==i)
                   {
                        m_pMatrix[i][j]  = 0;  }

                   if(j>i&&count < 10)
                   {
                       int u = (double)rand() / (RAND_MAX + 1) * (0 - 10000) + 10000;
                       m_pMatrix[i][j]  =  u%2;
                        m_pMatrix[j][i]  =  u%2;
                        if(m_pMatrix[i][j] ==1 && m_pMatrix[j][i]  ==1)
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
    //初始化顶点坐标
    for (int i = 0; i < vexnum; ++i)
    {

        x = a[i];
        y = b[i];
        cityMap[i].pos.setX(x);
        cityMap[i].pos.setY(y);
        cityMap[i].name = to_string(i);
    }
 string v1, v2;
 QLine temp_line;
 //初始化边的坐标，以便绘图
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
//返回顶点在数组中的索引
int Graph::LocationVex(string name)
{
    for (int i = 0; i < vexnum; ++i)
    {
        if (cityMap[i].name.compare(name) == 0)
            return i;
        else if (cityMap[i].name.substr(0, 2).compare(name) == 0)
            return i;
    }

    return -1;
}
//广度优先遍历
void Graph::BFS_Traverse(int start_point_index)
{
    for (int i = 0; i < vexnum; ++i)
    {
        visited[i] = 0;
    }

    BFS(start_point_index);
}

void Graph::BFS(int i)
{
    visited[i] = 1;
   // std::cout << adjMulList[i].name + " ";
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
            if(m_pMatrix[p][j] == 1 && visited[j] ==0)
            {
                temp_map_light.pos = cityMap[p].pos;
                 temp_map_light.name = to_string(p);
                 points_bfs_light.push_back(temp_map_light);
                q.push(j);
                visited[j] = 1;
                 bfs_str.append(to_string(j) + "->");
                   temp_line.setLine(cityMap[p].pos.rx(),cityMap[p].pos.ry(),cityMap[j].pos.rx(),cityMap[j].pos.ry());
                   temp_map.pos =cityMap[j].pos;
                   temp_map.name = to_string(j);
                   points_bfs.push_back(temp_map);
                line_bfs.push_back(temp_line);

            }
        }
    }
}
////深度优先遍历
void Graph::DFS_Traverse(int start_point_index)
{
    for (int i = 0; i < vexnum; ++i)
    {
        visited[i] = 0;
    }

    DFS(start_point_index);
}
void Graph::DFS(int i)
{
    stack<int> s;
       s.push(i);
      dfs_str.append(to_string(i) + "->");
          QLine temp_line;
          Map temp_map,temp_map_light;
          temp_map.pos =cityMap[i].pos;
          temp_map.name = to_string(i);
          points_dfs.push_back(temp_map);
       visited[i] = 1;
       int w;
       bool flag;
       while (!s.empty()) {
           w = s.top();
           flag = false;
           for (int j = 0; j < vexnum; j++) {
               if (!visited[j] && m_pMatrix[w][j] == 1) {
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
int Graph::addEdge(int from,int to)
{
    if ((from < 0 || from > vexnum) && (to < 0 || to > vexnum)) {

          return  0;
       } else if (m_pMatrix[from][to] == 1) {

           return 1;
    }else {
        m_pMatrix[from][to] = 1;
        m_pMatrix[to][from] = 1;
        QLine temp_line;
        temp_line.setLine(cityMap[from].pos.rx(),cityMap[from].pos.ry(),cityMap[to].pos.rx(),cityMap[to].pos.ry());
        line.push_back(temp_line);
        return 2;
}
}

int Graph::deleteEdge(int from,int to)
{
    if ((from < 0 || from > vexnum) && (to < 0 || to >  vexnum)) {

           return 0;
       } else if (m_pMatrix[from][to] == 0) {

           return 1;
       } else {
        m_pMatrix[from][to] = 0;
        m_pMatrix[to][from] = 0;
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

bool Graph::isEdge(int from, int to)
{
    if(m_pMatrix[from][to] ==1)
    {
        return true;
    }
    else {
        {
            return false;
        }
    }

}
bool Graph::isConnect()
{
        BFS_Traverse(1);
        bool flag = true;
        Map temp_map;
       for (int i = 0; i < vexnum; i++) {
           if (!visited[i]) {

               flag = false;

           }
           else {
               temp_map.pos =cityMap[i].pos;
               temp_map.name = to_string(i);
               points_isconnect.push_back(temp_map);
           }
       }
       return flag;
}
int Graph::inDegrees(int to)
{
     QLine temp_line;
    int sum = 0;
      for (int i = 0; i < vexnum; i++) {
          if (m_pMatrix[i][to] == 1) {
              sum++;
              temp_line.setLine(cityMap[i].pos.rx(),cityMap[i].pos.ry(),cityMap[to].pos.rx(),cityMap[to].pos.ry());
              line_indegrees.push_back(temp_line);
          }
      }
       qDebug()<<" Graph::inDegrees";
      return sum;
}

int Graph::outDegrees(int from)
{
    int sum = 0;
     QLine temp_line;
       for(int i = 0 ; i< vexnum ; i++)
       {
           if(m_pMatrix[from][i] ==1)
           {
               sum++;
               temp_line.setLine(cityMap[from].pos.rx(),cityMap[from].pos.ry(),cityMap[i].pos.rx(),cityMap[i].pos.ry());
               line_outdegrees.push_back(temp_line);
           }
       }
            return  sum;
}
void Graph::LabelComponents()
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
                        if(m_pMatrix[w][j] != 0 && labelConnect[j] == 0)
                        {
                            q.push(j);
                           labelConnect[j] = labelcount;
                        }
                    }
                }

            }
        }
}
void Graph::Compare_DFS_DFSWithRecursion(int sum)
{
    int nodeIndex = 1;
    srand(time(NULL));
        for (int i = 0; i < sum; i++)
        {
            for(int j = 0 ; j< sum ; j++)
            {

                int u = (double)rand() / (RAND_MAX + 1) * (0 - 10000) + 10000;
                randedge[i][j] = u%2;
            }
       }
        clock_t start1,finish1;
          start1=clock();
           for (int i = 0; i < sum; i++) {
               randedge_label[i] = 0;
           }
           Compare_DFSWithRecursion(nodeIndex);
           finish1=clock();
           totaltime_dfs_withrecursion=(double)(finish1-start1)/CLOCKS_PER_SEC;
            clock_t start2,finish2;

           start2=clock();
           Compare_DFS(nodeIndex);
           finish2=clock();
           totaltime_dfs=(double)(finish2-start2)/CLOCKS_PER_SEC;
}
void Graph::Compare_DFS(int nodeIndex)
{
    for (int i = 0; i < count; i++) {
          randedge_label[i] = 0;
      }
      stack<int> s;
      s.push(nodeIndex);
      dfs_str.append(to_string(nodeIndex));
      dfs_str.append("-->");
      randedge_label[nodeIndex] = 1;
      int w;
      bool flag;
      while (!s.empty()) {
          w = s.top();
          flag = false;
          for (int i = 1; i < count; i++) {
              if (!randedge_label[i] && randedge[w][i] == 1) {
                  s.push(i);
                  dfs_str.append(to_string(i));
                  dfs_str.append("-->");
                  randedge_label[i] = 1;
                  flag = true;
                  break;
              }
          }
          if (flag == false) {
              s.pop();
          }
      }
}
void Graph::Compare_DFSWithRecursion(int nodeIndex)
{
    randedge_label[nodeIndex] = 1;
    dfs_str_recursion.append(to_string(nodeIndex));
    dfs_str_recursion.append("-->");
       for (int i = 1; i < count; i++) {
           if (!randedge_label[i] && randedge[nodeIndex][i] == 1) {
               Compare_DFSWithRecursion(i);
           }

       }
}

void Graph::compare_paint()
{
    int nodeIndex = 1;
    count = 20;
    QPointF temp_qpointf;
    for(int i = 2 ; i< 10 ; i++)
    {
        srand(time(NULL));
            for (int i = 0; i < count; i++)
            {
                for(int j = 0 ; j< count ; j++)
                {

                    int u = (double)rand() / (RAND_MAX + 1) * (0 - 10000) + 10000;
                    randedge[i][j] = u%2;
                }
           }
            clock_t start1,finish1;
              start1=clock();
               for (int i = 0; i < count; i++) {
                   randedge_label[i] = 0;
               }
               Compare_DFSWithRecursion(nodeIndex);
               finish1=clock();
               totaltime_dfs_withrecursion=(double)(finish1-start1)/CLOCKS_PER_SEC;
               count+=20;
               pointf_dfs_withrecursion.push_back(QPointF(50*i, 500-totaltime_dfs_withrecursion*1000000));



               clock_t start2,finish2;

              start2=clock();
              Compare_DFS(nodeIndex);
              finish2=clock();
              totaltime_dfs=(double)(finish2-start2)/CLOCKS_PER_SEC;
               pointf_dfs.push_back(QPointF(50*i, 500-totaltime_dfs*1000000));
               qDebug()<<totaltime_dfs;
    }



}


