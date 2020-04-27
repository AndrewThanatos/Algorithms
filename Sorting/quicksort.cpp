#include <iostream>
#include <algorithm>

using namespace std;

int partition(float s[], int l, int h){
    int firsthigh = l;
    for (int i=l; i<h; i++)
        if (s[i] < s[h]){
            swap(s[i], s[firsthigh]);
            firsthigh++;
        } 
    swap(s[firsthigh], s[h]);
    return firsthigh;
}


void quicksort(float s[], int l, int h){
    if (l < h){
        int p = partition(s, l, h);
        quicksort(s, l, p-1);
        quicksort(s, p+1, h);
    }
}


int main(){
    float a[10] = {5, 2, 3, -1, 4, 2, 9, 5, 6, 3};
    quicksort(a, 0, 9);
    for (int i=0; i<10; i++)
        cout << a[i] << " ";
    cout << endl;
}