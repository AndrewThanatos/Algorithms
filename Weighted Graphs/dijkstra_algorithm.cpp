#include <iostream>
#include "graph_structure.cpp"

using namespace std;

const int MAXINT = 1e4;
int parent[MAXV+1];

void dijkstra(graph *g, int start){
    int i;
    edgenode *p;
    int distance[MAXV + 1];
    bool intree[MAXV + 1];
    int v;
    int w;
    int weight;
    int dist;

    for (i=0; i<g->nvertices; i++){
        intree[i] = false;
        distance[i] = MAXINT;
        parent[i] = -1;
    }

    distance[start] = 0;
    v = start;
    
    while (!intree[v]){
        cout << v << '\n';
        intree[v] = true;
        p = g->edges[v];
        while (p != NULL){
            w = p->y;
            weight =p->weight;
            if ((distance[w] > distance[v]+weight)){
                distance[w] = distance[v]+weight;
                parent[w] = v;
            }
            p = p->next;
        }

        v = 0;
        dist = MAXINT;
        for (int i=0; i<g->nvertices; i++){
            if ((!intree[i]) && (distance[i] < dist)){
                dist = distance[i];
                v = i;
            }
        }
    }


}

int main(){
    graph *g = create_graph();
    dijkstra(g, 0);
    for (int i=0; i<g->nvertices; i++)
        cout << parent[i] << " ";
}