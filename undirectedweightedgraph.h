#ifndef UNDIRECTEDWEIGHTEDGRAPH_H
#define UNDIRECTEDWEIGHTEDGRAPH_H

#include "graph.h"
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include <queue>
#include <stack>
struct Edge
{
public:

        int from;
        int to;
        string weight;
        QPoint location;

};
class UndirectedWeightedGraph:public Graph
{
public:
    Assis_array *close_edge ;
    int m_pWeightMatrix[15][15];//带权图的权重矩阵
       UndirectedWeightedGraph();
       ~UndirectedWeightedGraph();
       void CreatGraph();//构造图
        int addEdge(int from ,int to,int weight);   //添加边以构造有向图，val表示权值，默认连通
       void getWeight(int form,int to );//获取这条边的权值
      int deleteEdge(int from,int to );   //无向图删除边，val表示权值，默认连通
        void printWeightMatrix();   //打印权重矩阵
        int Prim(int begin);//最小生成树
        QVector<Edge> points_edge;
        QVector<QLine> line_prim;
         QVector<QLine> line_prim_light;
        QVector<Map> point_prim;
};

#endif // UNDIRECTEDWEIGHTEDGRAPH_H
