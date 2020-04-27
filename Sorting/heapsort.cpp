#include <iostream>
using namespace std;

const int PQ_SIZE=36;

struct priority_queue{
    float q[PQ_SIZE + 1];
    int n; 
};


void pq_swap(priority_queue *q, int a, int b){
    float c = q->q[a];
    q->q[a] = q->q[b];
    q->q[b] = c;
}

int pq_parent(int n){
    if (n == 1) return (-1);
    else return ((int) n/2);
}

int pq_young_child(int n){
    return (n*2);
}

void bubble_up(priority_queue *q, int p){
    if (pq_parent(p) == -1) return;
    if (q->q[pq_parent(p)] < q->q[p]){
        pq_swap(q, pq_parent(p), p);
        bubble_up(q, pq_parent(p));
    }
}

void pq_init(priority_queue *q){

    q->n = 0;
}

void pq_insert(priority_queue *q, int x){
    if (q->n >= PQ_SIZE)
        printf("Warning: priority queue overflow insert x=%d\n",x);
    else {
        q->n += 1;
        q->q[q->n] = x;
        bubble_up(q, q->n);
    }
}

void make_heap(priority_queue *q, float s[], int n){
    pq_init(q);
    for (int i=0; i<n; i++) pq_insert(q, s[i]);
}

void bubble_down(priority_queue *q, int p){
    int c = pq_young_child(p);
    int index_min = p;

    for (int i=0; i<=1; i++)
        if (c+i <= q->n)
            if (q->q[c+i] > q->q[index_min]) index_min = c+i;

    if (index_min != p){
        pq_swap(q, index_min, p);
        bubble_down(q, index_min);
    }
}



float extract_max(priority_queue *q){
    int min = -1;

    if (q->n <= 0) printf("Warning: empty priority queue.\n");
    else {
        min = q->q[1];
        q->q[1] = q->q[q->n];
        q->n -= 1;
        bubble_down(q, 1);
    }
    return min;
}

void heapsort(float *s, int n){
    priority_queue q;
    pq_init(&q);

    make_heap(&q, s, n);

    for (int i=0; i<n; i++)
        s[i] = extract_max(&q);
}


int main(){
    float arr[] = {1, 2, 3, 4, 5, 6, 4, 8, 6, 0};
    heapsort(&arr[0], 10);

    for (int i=0; i<10; i++)
        cout << arr[i] << " ";

}