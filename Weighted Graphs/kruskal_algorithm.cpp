#include <iostream>
#include <algorithm>
#include "graph_structure.cpp"

using namespace std;

const int MAXINT = 1e4;
int parent[MAXV+1];

struct edge_pair{
    int x;
    int y;
    int weight;
};

bool weight_compare(edge_pair a, edge_pair b){
    return (a.weight < b.weight);
}

void to_edge_array(graph *g, edge_pair *e){
    int k=0;
    for (int i=0; i<g->nedges; i++){
        edgenode *p=g->edges[i];
        while (p != NULL){
            e[k].x = i;
            e[k].y = p->y;
            e[k++].weight = p->weight;
            p = p->next;
        }
    }
}

struct my_set_union{
    int p[MAXV+1];
    int size[MAXV+1];
    int n;
};

void my_set_union_init(my_set_union *s, int n){
    int i;

    for (i=0; i<n; i++){
        s->p[i] = i;
        s->size[i] = 0;
    }
    s->n = n;
}

int find(my_set_union *s, int x){
    if (s->p[x] == x) return x;
    else return find(s, s->p[x]);
}

void union_sets(my_set_union *s, int s1, int s2){
    int r1, r2;
    r1 = find(s, s1);
    r2 = find(s, s2);

    if (r1 == r2) return;

    if (s->size[r1] >= s->size[r2]){
        s->size[r1] = s->size[r1] + s->size[r2];
        s->p[r2] = r1;
    } else {
        s->size[r2] = s->size[r1] + s->size[r2];
        s->p[r1] = r2; 
    }
}

bool same_component(my_set_union *s, int s1, int s2){
    return find(s, s1) == find(s, s2);
}

void kruskal(graph *g){
    int i;
    my_set_union s;
    edge_pair e[MAXV+1];
    
    my_set_union_init(&s, g->nvertices);

    to_edge_array(g, e);
    sort(e, e+g->nedges, weight_compare);
    for (int i=0; i<g->nedges; i++){
        if (!same_component(&s, e[i].x, e[i].y)){
            printf("Edge (%d, %d, weight=%d) in MST\n", e[i].x, e[i].y, e[i].weight);
            union_sets(&s, e[i].x, e[i].y);
        }
    }



}

int main(){
    graph *g = create_graph();
    kruskal(g);
}