#include <iostream>
#include <iomanip>
#include <chrono>
#define MAX 10

using namespace std;
using namespace std::chrono;

void Swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

void interChangeSort(int a[], int n){
    int  i, j;
	for (i = 0 ; i<n-1 ; i++){
		for (j =i+1; j < n ; j++){
		   if(a[j]< a[i]) 
			Swap(a[i],a[j]);
        }
    }
}


void selectionSort(int a[], int n){
    int min; 
	for (int  i=0; i<n-1 ; i++){
		min = i; 
		for(int j = i+1; j < n ; j++){
	   	    if (a[j] < a[min]) min = j;
        }
		if (min != i) Swap(a[min], a[i]);
	}
}

void selectionSortMax(int a[], int n){
    int max; 
	for (int  i=0; i<n-1 ; i++){
		max = i; 
		for(int j = i+1; j < n ; j++){
	   	    if (a[j] > a[max]) max = j;
        }
		if (max != i) Swap(a[max], a[i]);
	}
}

void insertionSort(int a[], int n){
    int pos, x;
	for(int i=1 ; i<n ; i++) {	
        x = a[i]; pos=i-1;
		while(pos>=0 && a[pos]>x){
            a[pos+1] = a[pos];
			pos--;
		}
		a[pos+1]=x;
	}

}

void bubbleSort(int a[], int n){
    int i, j;
	for (i = 0 ; i<n-1 ; i++){
		for (j =n-1; j>i ; j --){
		   if(a[j]< a[j-1])
           Swap(a[j], a[j-1]);
        }
    }
}


void quickSort(int a[], int left, int right) {
    int i, j, x;
    if (left < right) {
        x = a[(left + right) / 2];
        i = left;
        j = right;
        do {
            while (a[i] < x) i++;
            while (a[j] > x) j--;
            if (i <= j) {
                Swap(a[i], a[j]);
                i++;
                j--;
            }
        } while (i <= j);
        if (left < j) quickSort(a, left, j);
        if (i < right) quickSort(a, i, right);
    }
}


void Shift(int a[], int l, int r) {
    int i, j;
    i = l; j = 2 * i;
    while (j <= r){
        if ((j < r) && (a[j] < a[j + 1])) j++;
        if (a[j] <= a[i]) break;
        else {
            Swap(a[i], a[j]); 
            i = j; j = 2 * i;
        }
    }
}

void CreateHeap(int a[], int n){
    int l;
    l = (n - 1) / 2;
    while (l >= 0) {
        Shift(a, l, n - 1);
        l--;
    }
}


void heapSort(int a[]){
    int r = MAX - 1;
    CreateHeap(a, MAX);
    while (r > 0) {     
        Swap(a[0], a[r]);
        r--;
        Shift(a, 0, r);
    }
}


void ShellSort(int a[], int N, unsigned int h[], int k) 
{
    int step, i, j;
    int x, len, pos;
    for (step = 0; step < k; step ++) {
        len = h[step];
        for (i = len; i < N; i++) {
            x = a[i];
            pos = i - len;
            while ((x < a[pos]) && (pos >= 0)) { 
                a[pos + len] = a[pos];
                pos = pos - len;
            }
            a[pos + len] = x;
        }
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


void radixSort(int a[], int n)
{
	int i, b[MAX], m = a[0], exp = 1;
	for (i = 0; i < n; i++){
		if (a[i] > m)
			m = a[i];
	}
	while (m / exp > 0){
		int bucket[10] ={  0 };
		for (i = 0; i < n; i++)
			bucket[a[i] / exp % 10]++;
		for (i = 1; i < 10; i++)
			bucket[i] += bucket[i - 1];
		for (i = n - 1; i >= 0; i--)
			b[--bucket[a[i] / exp % 10]] = a[i];
		for (i = 0; i < n; i++)
			a[i] = b[i];
		exp *= 10;
	}
}


void print(int a[], int n){
    for(int i = 0; i < n; i++){
        cout << a[i] << " ";
    }
    cout << endl;
}


void printLine(int n){
    for(int i = 0; i < n; i++){
        cout << "-";
    }
    cout << endl;
}
int main(){
    // int n = 10;
    // const int k = 3;
    // unsigned int h[k] = {5, 3, 1};
    // int select;
    // auto start = high_resolution_clock::now();
    // auto stop = high_resolution_clock::now();
    // duration<double, std::milli> elapsed;
    // do{
    //     int a[100] = {5, 2, 8, 9, 1, 3, 7, 6, 4, 10};
    //     printLine(51);
    //     cout << setw(50) << left << "|1 --> Inter Change sort" << "|" <<  endl;
    //     cout << setw(50) << left << "|2 --> Selection sort" << "|" << endl;
    //     cout << setw(50) << left << "|3 --> Insertion sort" << "|" << endl;
    //     cout << setw(50) << left << "|4 --> Bubble sort" << "|" << endl;
    //     cout << setw(50) << left << "|5 --> Quick sort" << "|" << endl;
    //     cout << setw(50) << left << "|6 --> Heap sort" << "|" << endl;
    //     cout << setw(50) << left << "|7 --> Shell sort" << "|" << endl;
    //     cout << setw(50) << left << "|8 --> Merge sort" << "|" << endl;
    //     cout << setw(50) << left << "|9 --> Natural Merge sort" << "|" << endl;
    //     cout << setw(50) << left << "|10 --> Radix sort" << "|" << endl;
    //     cout << setw(50) << left << "|11 --> Selection sort max" << "|" << endl;
    //     cout << setw(50) << left << "|99 --> Quit" << "|" << endl;
    //     printLine(51);
    //     cout << "Mang a chua sort: ";
    //     print(a, n);
    //     cout << "Nhap d: ";
    //     cin >> select;
    //     switch(select){
    //         case 1: 
    //             cout << "Interchange Sort: ";
    //             start = high_resolution_clock::now();
    //             interChangeSort(a, n); 
    //             stop = high_resolution_clock::now();
    //             elapsed = stop - start;
    //             cout << "Time: " << elapsed.count() << " milliseconds" << endl;
    //             break;
    //         case 2: 
    //             cout << "Selection Sort: "; 
    //             start = high_resolution_clock::now();
    //             selectionSort(a, n); 
    //             stop = high_resolution_clock::now();
    //             elapsed = stop - start;
    //             cout << "Time: " << elapsed.count() << " milliseconds" << endl;
    //             break;
    //         case 3: 
    //             cout << "Insertion Sort: "; 
    //             start = high_resolution_clock::now();
    //             insertionSort(a, n); 
    //             stop = high_resolution_clock::now();
    //             elapsed = stop - start;
    //             cout << "Time: " << elapsed.count() << " milliseconds" << endl;
    //             break;
    //         case 4: 
    //             cout << "Bubble Sort: "; 
    //             start = high_resolution_clock::now();
    //             bubbleSort(a, n); 
    //             stop = high_resolution_clock::now();
    //             elapsed = stop - start;
    //             cout << "Time: " << elapsed.count() << " milliseconds" << endl;
    //             break;
    //         case 5: 
    //             cout << "Quick Sort: "; 
    //             start = high_resolution_clock::now();
    //             quickSort(a, 0, n - 1); 
    //             stop = high_resolution_clock::now();
    //             elapsed = stop - start;
    //             cout << "Time: " << elapsed.count() << " milliseconds" << endl;
    //             break;
    //         case 6: 
    //             cout << "Heap Sort: "; 
    //             start = high_resolution_clock::now();
    //             heapSort(a); 
    //             stop = high_resolution_clock::now();
    //             elapsed = stop - start;
    //             cout << "Time: " << elapsed.count() << " milliseconds" << endl;
    //             break;
    //         case 7: 
    //             cout << "Shell Sort: "; 
    //             start = high_resolution_clock::now();
    //             ShellSort(a, n, h, k); 
    //             stop = high_resolution_clock::now();
    //             elapsed = stop - start;
    //             cout << "Time: " << elapsed.count() << " milliseconds" << endl;
    //             break;
    //         case 8: 
    //             cout << "Merge Sort: "; 
    //             start = high_resolution_clock::now();
    //             MergeSort(a, n); 
    //             stop = high_resolution_clock::now();
    //             elapsed = stop - start;
    //             cout << "Time: " << elapsed.count() << " milliseconds" << endl;
    //             break;
    //         case 9: 
    //             cout << "Natural Merge Sort: "; 
    //             start = high_resolution_clock::now();
    //             MergeSortNatural(a, n); 
    //             stop = high_resolution_clock::now();
    //             elapsed = stop - start;
    //             cout << "Time: " << elapsed.count() << " milliseconds" << endl;
    //             break;
    //         case 10: 
    //             cout << "Radix Sort: "; 
    //             start = high_resolution_clock::now();
    //             radixSort(a, n); 
    //             stop = high_resolution_clock::now();
    //             elapsed = stop - start;
    //             cout << "Time: " << elapsed.count() << " milliseconds" << endl;
    //             break;
    //         case 11: 
    //             cout << "Selection Sort (max): "; 
    //             start = high_resolution_clock::now();
    //             selectionSortMax(a, n); 
    //             stop = high_resolution_clock::now();
    //             elapsed = stop - start;
    //             cout << "Time: " << elapsed.count() << " milliseconds" << endl;
    //             break;
    //         case 99: 
    //             break;
    //         default:
    //             cout << "Gia tri khong hop le !";
    //     }
    //     print(a, n);
    // }while(select != 99);
    char c = 'd';
    cout << int(c);
} 