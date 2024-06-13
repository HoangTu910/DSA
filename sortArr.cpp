#include <iostream>
#include <algorithm>

using namespace std;

#define MAX 10
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define debug(v) do { \
    for(int i = 0; i < MAX; i++) \
        cout << v[i] << " "; \
} while(0)

//Heap Sort
void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

void Shift(int a[], int start, int end){
    int rootIndex = start;
    int childIndex = rootIndex * 2 + 1;
    while(childIndex <= end){
        if(childIndex < end && a[childIndex] < a[childIndex+1]) childIndex++;
        if(a[rootIndex] > a[childIndex]) break;
        swap(a[rootIndex], a[childIndex]);
        rootIndex = childIndex;
        childIndex = rootIndex * 2 + 1;
    }
}

void createHeap(int a[], int n=MAX){
    int start = (n-1)/2;
    while(start >= 0){
        Shift(a, start, n-1);
        start--;
    }
}

void heapSort(int a[], int n=MAX){
    createHeap(a, n);
    int end = n - 1;
    while(end > 0){
        swap(a[0], a[end]);
        end--;
        Shift(a, 0, end);
    }
}   

void shellSort(int a[], int n, unsigned int h[], int k){
    for(int gapIndex = 0; gapIndex < k; gapIndex++){
        int gap = h[gapIndex];
        for(int i = gap; i < n; i++){
            int temp = a[i];
            int pos = i - gap;
            while(pos >= 0 && a[pos] > temp){
                a[pos + gap] = a[pos];
                pos -= gap; 
            }
            a[pos+gap] = temp;
        }
    }
}

void radixSort(int a[], int n=MAX){
    int output[1000], maxVal = 0, exp = 1;
    for(int i = 0; i < n; i++){
        if(a[i] > maxVal){
            maxVal = a[i];
        }
    }
    while(maxVal / exp > 0){
        int countArr[10] = {0};
        for(int i = 0; i < n; i++){
            int digit = (a[i] / exp) % 10;
            countArr[digit]++;
        }
        for(int i = 1; i < n ;i++){
            countArr[i] += countArr[i-1];
        }
        for(int i = n-1; i >=0; i--){
            int digit = (a[i] / exp) % 10;
            int index = --countArr[digit];
            output[index] = a[i];
        }
        for(int i = 0; i < n; i++){
            a[i] = output[i];
        }
        exp *= 10;
    }
}

void Merge(int a[], int nb, int nc, int k, int b[], int c[]){
    int mergeIndex = 0, indexB = 0, indexC = 0;
    int pB = 0, pC = 0;
    while((nb > 0) && (nc > 0)){
        int kb = min(k, nb);
        int kc = min(k, nc);
        if(b[indexB + pB] <= c[indexC + pC]){
            a[mergeIndex++] = b[indexB + pB];
            indexB++;
            if(indexB >= kb){
                for(; indexC < kc; indexC++){
                    a[mergeIndex++] = c[indexC + pC];
                }
                pB += kb;
                pC += kc;
                indexB = indexC = 0;
                nb -= kb;
                nc -= kc;
            }
        }
        else{
            a[mergeIndex++] = c[indexC + pC];
            indexC++;
            if(indexC >= kc){
                for(; indexB < kb; indexB++){
                    a[mergeIndex++] = b[indexB + pB];
                }
                pB += kb;
                pC += kc;
                indexB = indexC = 0;
                nb -= kb;
                nc -= kc;
            }
        }
    }
}   

void Distribute(int a[], int n, int &pb, int &pc, int k, int b[], int c[]){
    int p;
    p = pb = pc = 0;
    while(p < n){
        for(int i = 0; (p < n) && (i < k); i++){
            b[pb++] = a[p++];
        }
        for(int i = 0; (p < n) && (i < k) ; i++){
            c[pc++] = a[p++];
        }
    }
}

void MergeSort(int a[], int n=MAX){
    int k = 1;
    int pb, pc, b[100], c[100];
    do{
        Distribute(a, n, pb, pc, k, b, c);
        Merge(a, pb, pc, k, b, c);
        k *= 2;
    } while(k < n);
}

int main(){
    int a[MAX] = {4,5,7,8,1,2,3,0,6,9};
    int arr[MAX] = {4231,5421,7522,8113,1213,2422,3647,0,612,9222};
    unsigned int h[3] = {5,3,1};
    int k = 3;
    debug(a);
    //heapSort(a);
    //shellSort(a, MAX, h, k);
    //radixSort(arr);
    MergeSort(a);
    cout << endl;
    debug(a);

}
