#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include "graph.h"
#include"directedgraph.h"
#include"undirectedweightedgraph.h"
#include"directedweightedgraph.h"


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    Graph * graph;
    DirectedGraph *directedgraph;
    UndirectedWeightedGraph *undirectedweightedgraph;
    DirectedWeightedGraph *directedweightedgraph;
//     QTimer *timer_dfs;
    //    QTimer *timer_bfs = new QTimer(this);
    //     connect( timer_bfs, SIGNAL(timeout()), myObject, SLOT(update()) );
    //    timer_bfs->start( 3000, TRUE ); // 3秒单触发定时器
//    QTimer *timer_prim;
//    QTimer* timer_compare;
    int point_dfs_size;
    int point_bfs_size;

    QVector<Map> point_bfs2;
     QVector<Map>  point_dfs2;
     QVector<Map> point_bfs2_light;
     QVector<Map>  point_dfs2_light;
    int start;
    QVector<QLine> line_bfs2;
      QVector<QLine> line_dfs2;
         QVector<Map> point_prim2;
          QVector<QLine> line_prim2;
      QLine isedge_line;
      Edge isedge_weight;
    QVector<Label_Map> Label_map_connect;   
    bool is_create;
        bool is_traverse;
        bool is_traverse_bfs;
        bool is_traverse_dfs;
        bool is_isedge;
        bool is_indegrees;
        bool is_outdegrees;
        bool is_isconnect;
        bool is_labelconnect;

        bool is_undirectedgraph;
        bool is_directedgraph;
         bool is_undirectedweightedgraph;
         bool is_directedweightedgraph;
        bool is_prim;
        bool is_compare;
          QString qoutput_bfs;
          string output_bfs;
          QString qoutput_dfs;
          string output_dfs;
          QString qoutput_prim;
          string output_prim;
        void paintEvent(QPaintEvent *);
private slots:
        void on_pushButton_clicked();
        void on_pushButton_2_clicked();
        void on_pushButton_4_clicked();
        void on_pushButton_add_edge_clicked();
        void on_pushButton_delete_edge_clicked();
        void on_pushButton_isedge_clicked();
        void on_pushButton_indegrees_clicked();
        void on_pushButton_outdegrees_clicked();
        void on_pushButton_isconnect_clicked();
        void on_pushButton_LabelComponents_clicked();
        void on_pushButton_3_clicked();
        void on_pushButton_creat_undweight_clicked();
        void on_pushButton_add_edge_weight_clicked();
        void on_pushButton_delete_edge_weight_clicked();
        void on_pushButton_prim_clicked();
        void on_pushButton_creat_dweight_clicked();
        void on_pushButton_compare_clicked();





private:
    Ui::Widget *ui;

};

#endif // WIDGET_H
