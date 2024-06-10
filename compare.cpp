#include <iostream>
#include <chrono>
#include <cstdlib>
#include <algorithm>

using namespace std;
using namespace std::chrono;

#define MAX 1000000


void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1; 

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++; 
            swap(arr[i], arr[j]); 
        }
    }
    swap(arr[i + 1], arr[high]); 
    return i + 1; 
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

void Merge(int a[], int nb, int nc, int k, int b[], int c[]){
    int p, pb, pc, ib, ic, kb, kc;
    p = pb = pc = 0;
    ib = ic = 0;
    while ((0 < nb) && (0 < nc)) {
        kb = min(k, nb); kc = min(k, nc);
        if (b[pb + ib] <= c[pc + ic]) {
        a[p++] = b[pb + ib];
        ib++;
        if (ib == kb) {
           for (; ic < kc; ic++)
               a[p++] = c[pc + ic];
           pb += kb; pc += kc;
           ib = ic = 0;
           nb -= kb; nc -= kc;
        }
     }
     else {
    a[p++] = c[pc + ic];
    ic++;
    if (ic == kc) {
       for (; ib < kb; ib++)
          a[p++] = b[pb + ib];
       pb += kb; pc += kc;
       ib = ic = 0;
       nb -= kb; nc -= kc;
    }
  }
}
}


void Distribute(int a[], int n, int &pb, int &pc, int k, int b[], int c[]){
    int i, p;
    p = pb = pc = 0;
    while(p < n){
        for(i = 0; (p < n) && (i < k); i++){
            b[pb++] = a[p++];
        }
        for(i = 0; (p < n) && (i < k); i++){
            c[pc++] = a[p++];
        }
    }
}

void DistributeNatural(int a[], int n, int &pb, int &pc, int &r, int b[], int c[], int k){
    int p;
    p = pb = pc = 0;
    r = 0; 
    while (p < n) {
        for (int i = 0; (p < n) && (i < k); i++) { 
            if (r % 2 == 0)
                b[pb++] = a[p++];
            else
                c[pc++] = a[p++];
        }
        r++; 
    }
}

void MergeSort(int a[], int n){
    int* b = new int[MAX];
    int* c = new int[MAX];
    int p, pc, pb;
    int i, k = 1;
    do {
        Distribute(a, n, pb, pc, k, b, c);
        Merge(a, pb, pc, k, b, c);
        k = k * 2;
    }while(k < n);
    delete[] b;
    delete[] c;
}


void MergeSortNatural(int a[], int n){
    int* b = new int[MAX];
    int* c = new int[MAX];
    int p, pc, pb, r;
    int i, k = 1;
    do {
        DistributeNatural(a, n, pb, pc, r, b, c, k);
        Merge(a, pb, pc, k, b, c);
        k = k * 2;
    }while(k < n);
    delete[] b;
    delete[] c;
}

int main(){
    int* a_merge = new int[MAX];
    int* b_merge_natural = new int[MAX];
    int* c_quick = new int[MAX];
    for (int i = 0; i < MAX; i++) {
        a_merge[i] = b_merge_natural[i] = c_quick[i] = rand();
    }
    
    auto start = high_resolution_clock::now();
    MergeSort(a_merge, MAX);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Thoi gian tron truc tiep: " << duration.count() << " milliseconds" << endl;

    start = high_resolution_clock::now();
    MergeSortNatural(b_merge_natural, MAX);
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    cout << "Thoi gian tron tu nhien: " << duration.count() << " milliseconds" << endl;

    start = high_resolution_clock::now();
    quickSort(c_quick, 0, MAX - 1);
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    cout << "Thoi gian Quick Sort: " << duration.count() << " milliseconds" << endl;
    delete[] a_merge;
    delete[] b_merge_natural;
    delete[] c_quick;
}