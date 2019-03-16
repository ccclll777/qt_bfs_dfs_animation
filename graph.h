#ifndef GRAPH_H
#define GRAPH_H


#include <string>
#include <iostream>
#include <QVector>
#include <QPoint>
#include<QLine>
#define MAX 100
using namespace  std;

//顶点结点
struct Map
{
public:

        std::string name;
        QPoint pos;

};
struct Label_Map
{
public:

        std::string name;
        QPoint pos;
        int label_c;

};
//作为记录边的信息，这些边都是达到end的所有边中，权重最小的那个  Prim算法中使用
struct Assis_array {
    int start; //边的终点
    int end;  //边的起点
    int weight;  //边的权重
};

class Graph
{
public:

    int vexnum; //定点数目
    int edgenum; //边数目
    int visited[MAX];
    int m_pMatrix[MAX][MAX];//图的邻接矩阵
     double totaltime_dfs,  totaltime_dfs_withrecursion;
     QVector<QPointF> pointf_dfs;
       QVector<QPointF> pointf_dfs_withrecursion;
    QVector<QPoint> points;
    QVector<Map> points_bfs;
    QVector<Map> points_dfs;
     QVector<Map> points_isconnect;
    QVector<QLine> line;
    QVector<QLine> line_bfs;
    QVector<QLine> line_dfs;
    QVector<Map> points_bfs_light;
    QVector<Map> points_dfs_light;
    QVector<QLine> line_indegrees;
    QVector<QLine> line_outdegrees;
    string dfs_str;
    string bfs_str;
    string dfs_str_recursion;
    Map * cityMap;
    int randedge[300][300];
     int  labelConnect[15];
     int  randedge_label[300];
     int count;
    Graph();
    ~Graph();
    void CreatGraph();
    int LocationVex(string name);
//    bool SearchEdge(string v1, string v2);
    void BFS_Traverse(int start_point_index);
    void DFS_Traverse(int start_point_index);
    void DFS_Traverse_Recursion(int start_point_index);
    void BFS(int i);
    void DFS(int i);
    void DFS_Recursion(int i);
    int addEdge(int from,int to);   //添加边以构造有向图，val表示权值，默认连通
   int deleteEdge( int from,int to);   //无向图删除边，val表示权值，默认连通
    bool isEdge(int from,int to);// 判断边是否存在
    bool isConnect();//判断图是否连通
    int inDegrees(int to);//计算顶点的入度
    int outDegrees(int from);//计算顶点的出度
     void  LabelComponents();//连用构件标记
     void Compare_DFS_DFSWithRecursion(int nodeIndex);
     void Compare_DFS(int nodeIndex);
     void Compare_DFSWithRecursion(int nodeIndex);
     void compare_paint();
};
#endif // GRAPH_H
