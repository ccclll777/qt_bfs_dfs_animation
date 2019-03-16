#ifndef DIRECTEDGRAPH_H
#define DIRECTEDGRAPH_H


#include "graph.h"
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include <queue>
#include <stack>
using namespace std;
class DirectedGraph: public Graph
{
public:
    DirectedGraph():Graph()
       {

       }
       ~DirectedGraph();
      void CreatGraph();//构造图
        int addEdge(int from,int to);   //添加边以构造有向图，val表示权值，默认连通
       int deleteEdge(int from,int to);   //无向图删除边，val表示权值，默认连通
        int inDegrees(int to);//计算顶点的入度
        int outDegrees(int from);//计算顶点的出度
        void BFS_Traverse(int start_point_index);
        void DFS_Traverse(int start_point_index);
        void DFS_Traverse_Recursion(int start_point_index);
        void BFS(int i);
        void DFS(int i);
        void DFS_Recursion(int i);
         void  LabelComponents();//连用构件标记

};

#endif // DIRECTEDGRAPH_H
