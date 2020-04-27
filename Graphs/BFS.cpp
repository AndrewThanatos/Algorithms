#include <iostream>
#include <queue>
#include <vector>
#include <fstream>

using namespace std;
const int MAXV = 10;

bool prosessed[MAXV + 1];
bool discovered[MAXV + 1];
int parent[MAXV + 1];


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

void find_path(int start, int end){
    if (start == end || end == -1) printf("\n%d", start);
    else {
        find_path(start, parent[end]);
        printf("\n%d", end);
    }
}


void initialize_search(graph *g){
    for (int i=0; i<g->n; i++){
        prosessed[i] = false;
        discovered[i] = false;
        parent[i] = -1;
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

void bfs(graph *g, int start){
    queue<int> q;

    start--;
    q.push(start);
    discovered[start] = true;

    while (!q.empty()){
        int v = q.front();
        q.pop();
        process_vertex_early(v);
        prosessed[v] = true;

        for (int i=0; i<g->arr[v].size(); i++){
            int y = g->arr[v][i];

            if (!prosessed[y]) process_edge(v, y);

            if (!discovered[y]){
                new_discover(y);
                q.push(y);
                parent[y] = v;
                discovered[y] = true;
            }
        }
        process_vertex_late(v);
    }
    

}



int main(){
    graph g;
    create_graph(&g);
    initialize_search(&g);
    bfs(&g, 5);
    
    find_path(4, 6);
}