#include <iostream>
#include <chrono>
#include <cstdlib>
#include <algorithm>
#define MAX 100
using namespace std;

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
    int a[MAX] = {2,3,6,7,12,7,14,35,21,1};
    for(int i = 0; i < 10; i++){
        cout << a[i] << " ";
    } 
    cout << endl;
    MergeSortNatural(a, 10);
    for(int i = 0; i < 10; i++){
        cout << a[i] << " ";
    } 
}