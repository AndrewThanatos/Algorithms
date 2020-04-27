#include <iostream>

using namespace std;

struct stack{
    float *m = new float[1];
    int n;
    int size;
};

void resize(stack *q, float size)
{
    q->size = (int)(q->size * size);
    float *new_m = new float[(int)(q->size)];
    for (int i = 0; i < q->size; i++) new_m[i] = q->m[i];  
    delete [] q->m;
    q->m = new_m;
}

float show_last(stack *q){
    return q->m[q->n-1];
}

bool stack_empty(stack *q){
    return !q->n ? true:false;
}

void delete_stack(stack *q){
    delete [] q->m;
}

float get_last(stack *q){
    if (stack_empty(q)){
        cout << "stack is empty";
        return -1;
    }
    if (q->n * 2 < q->size) resize(q, 0.5);

    return q->m[--q->n];
}

void stack_add(stack *q, float elem){
    if (q->n==q->size) resize(q, 2);
    q->m[q->n++] = elem;
}

void stack_init(stack *q){
    q->n = 0;
    q->size = 1;
}
