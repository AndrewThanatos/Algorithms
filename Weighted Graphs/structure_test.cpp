#include <iostream>
#include <fstream>

const int MAXV = 10;

using namespace std;

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

int main(){
    graph g = *create_graph();
    cout << g.nvertices << " " << g.nedges << "\n----------\n";
    edgenode *p;
    for (int i=0; i<g.nvertices; i++){
        p = g.edges[i];
        while (p != NULL){
            cout << p->y << ' ' << p->weight << ' ';
            p = p->next;
        }
        cout << '\n';
    }
}