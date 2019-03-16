#ifndef DIRECTEDWEIGHTEDGRAPH_H
#define DIRECTEDWEIGHTEDGRAPH_H

#include"undirectedweightedgraph.h"
class DirectedWeightedGraph:public UndirectedWeightedGraph
{
public:
    DirectedWeightedGraph();
     ~DirectedWeightedGraph();
    void CreatGraph();//构造图
  int deleteEdge(int from,int to );   //无向图删除边，val表示权值，默认连通
       void getWeight();//获取权重
 int addEdge(int from ,int to,int weight);   //添加边以构造有向图，val表示权值，默认连通
};

#endif // DIRECTEDWEIGHTEDGRAPH_H
