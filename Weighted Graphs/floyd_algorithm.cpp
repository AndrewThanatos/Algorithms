#include <iostream>
#include <fstream>


const int MAXV = 100;
const int MAXINT = 1e6;
using namespace std;

struct adjacency_matrix{
    int weight[MAXV+1][MAXV+1];
    int nvertices;
};

void adjacency_matrix_init(adjacency_matrix *g){
    for (int i=0; i<MAXV+1; i++)
        for (int j=0; j<MAXV+1; j++)
            g->weight[i][j] = MAXINT;
    g->nvertices = 0;
}


adjacency_matrix *create_graph(adjacency_matrix *g){
    adjacency_matrix_init(g);
    ifstream data("input.txt");

    data >> g->nvertices;

    for (int i=0; i<g->nvertices; i++){
        int edges;
        data >> edges;
        for (int j=0; j<edges; j++){
            int vertix, weight;
            data >> vertix >> weight;
            g->weight[i][vertix] = weight;
            g->weight[vertix][i] = weight;
        }
    }
    return g;

}

void floyd(adjacency_matrix *g){
    int i, j;
    int k;
    int through_k;

    for (k=0; k<g->nvertices; k++)
        for (i=0; i<g->nvertices; i++)
            for (int j=0; j<g->nvertices; j++){
                through_k = g->weight[i][k] + g->weight[k][j];
                if (through_k < g->weight[i][j])
                    g->weight[i][j] = through_k;
            }
}


int main(){
    adjacency_matrix g;
    create_graph(&g);
    floyd(&g);
    for (int i=0; i<g.nvertices; i++){
        for (int j=0; j<g.nvertices; j++)
            cout << g.weight[i][j] << " ";
        cout << endl;
    }
}