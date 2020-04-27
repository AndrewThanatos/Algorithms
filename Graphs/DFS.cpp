#include <iostream>
#include <queue>
#include <vector>
#include <fstream>

using namespace std;
const int MAXV = 10;

bool prosessed[MAXV + 1];
bool discovered[MAXV + 1];
int entry_run_time[MAXV + 1];
int parent[MAXV + 1];
int exit_run_time[MAXV + 1];
int run_time = 0;


struct graph{
    vector <vector <int>> arr;
    int n;
};

void create_graph(graph *g){
    int n;
    int k;
    int i;

    ifstream data("input.txt");
    data >> n;
    g->n = n;
    for (i=0; i<n; i++){
        data >> k;
        vector <int> row;
        g->arr.push_back(row);
        for (int j=0; j<k; j++){
            int input;
            data >> input;
            g->arr[i].push_back(input);
        }
    } 
}


void initialize_search(graph *g){
    for (int i=0; i<g->n; i++){
        prosessed[i] = false;
        discovered[i] = false;
        exit_run_time[i] = -1;
        entry_run_time[i] = -1;
        parent[i] = -1;
        run_time = 0;
    }
}

void process_vertex_early(int v){
    printf("Processed vertex %d\n", v);
}

void process_edge(int v, int y){
    printf("Processed edge (%d %d)\n", v, y);
}

void process_vertex_late(int v){
    printf("\n");
}

void new_discover(int y){
    printf("New discovered vertex %d\n", y);
}

void dfs(graph *g, int v){
    discovered[v] = true;
    run_time = run_time + 1;
    entry_run_time[v] = run_time;

    process_vertex_early(v);

    for (int i=0; i<g->arr[v].size(); i++){
        int y = g->arr[v][i];
        if (!discovered[y]){
            parent[y] = v;
            process_edge(v, y);
            dfs(g, y);
        } else if (!prosessed[y]){
            process_edge(v, y);
        }
    }
    process_vertex_late(v);

    run_time = run_time + 1;
    exit_run_time[v] = run_time;
    prosessed[v] = true;

}



int main(){
    graph g;
    create_graph(&g);
    initialize_search(&g);
    dfs(&g, 5);
}