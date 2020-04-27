#include <iostream>
#include <fstream>

using namespace std;

const int MAXV = 100;

struct edgenode{
    int y;
    int weight;
    struct edgenode *next;
};

struct graph{
    edgenode *edges[MAXV+1];
    int degree[MAXV+1];
    int nvertices;
    int nedges;
    int directed;
};

graph *create_graph(){
    int nvertices=0;
    int nedges=0;
    int directed = 0;
    graph *g;
    g = new graph;

    ifstream data("input.txt");
    data >> nvertices;
    g->nvertices = nvertices;
    for (int i=0; i<nvertices; i++){
        edgenode *root;
        edgenode *nextnode;
        root = new edgenode;
        data >> g->degree[i];
        data >> root->y >> root->weight;
        nextnode = root;
        nedges += g->degree[i];
        for (int j=1; j<g->degree[i]; j++){
            nextnode->next = new edgenode;
            nextnode = nextnode->next;
            data >> nextnode->y >> nextnode->weight;
        }
        g->edges[i] = root;
    }
    g->nedges = nedges;
    g->directed = directed;
    return g;
}

