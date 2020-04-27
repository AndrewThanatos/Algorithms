#include <iostream>
#include "stack.cpp"


using namespace std;

void merge(float s[], int low, int middle, int high){
    stack left_stack, right_stack;
    stack_init(&left_stack);
    stack_init(&right_stack);
    int i;
    for (i=middle; i>=low; i--) stack_add(&left_stack, s[i]);
    for (i=high; i>=middle+1; i--) stack_add(&right_stack, s[i]);

    // Can be deleted or commented
    // cout some information
    cout << "-----------------\n";
    cout << "Left stack -> ";
    for (int i=0; i<left_stack.n; i++) cout << left_stack.m[i] << " ";
    cout << endl;
    cout << "Right stack -> ";
    for (int i=0; i<right_stack.n; i++) cout << right_stack.m[i] << " ";
    cout << endl;


    i=low;
    while (!stack_empty(&left_stack) && !stack_empty(&right_stack)){
        if (show_last(&left_stack) <= show_last(&right_stack)){
            s[i++] = get_last(&left_stack);
        } else s[i++] = get_last(&right_stack);
    }

    while (!stack_empty(&left_stack)) s[i++] = get_last(&left_stack);
    while (!stack_empty(&right_stack)) s[i++] = get_last(&right_stack);

    // Can be deleted or commented
    // cout some information
    cout << "Array S -> ";
    for (int i=low; i<=high; i++) cout << s[i] << " ";
    cout << endl;
}

void mergesort(float s[], int low, int high){
    if (low < high){
        int middle = (low + high) / 2;
        mergesort(s, low, middle);
        mergesort(s, middle+1, high);
        merge(s, low, middle, high);
    }
}


int main(){
    float a[10] = {5, 2, 3, -1, 5, 6, 7, 8, 5, 0};
    mergesort(a, 0, 9);
    for (int i=0; i<10; i++)
        cout << a[i] << " ";
    cout << endl;
}