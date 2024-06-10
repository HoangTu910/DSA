#include<iostream>
#include <string>
#include <algorithm>
using namespace std;

struct ky_tu
{
    char c;
    int freq = 0;
};

void Swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

void SwapChar(char &a, char &b){
    char temp = a;
    a = b;
    b = temp;
}

void Shift(int a[], int l, int r, ky_tu* ky_tu) {
    int i, j;
    i = l; j = 2 * i;
    while (j <= r){
        if ((j < r) && (a[j] < a[j + 1])) j++;
        if (a[j] <= a[i]) break;
        else {
            Swap(a[i], a[j]);
            SwapChar(ky_tu[i].c, ky_tu[j].c); 
            i = j; j = 2 * i;
        }
    }
}

void CreateHeap(int a[], int n, ky_tu* ky_tu){
    int l;
    l = (n - 1) / 2;
    while (l >= 0) {
        Shift(a, l, n - 1, ky_tu);
        l--;
    }
}


void heapSort(int a[], int n, ky_tu* ky_tu){
    int r = n - 1;
    CreateHeap(a, n, ky_tu);
    while (r > 0) {     
        Swap(a[0], a[r]);
        SwapChar(ky_tu[0].c, ky_tu[r].c);
        r--;
        Shift(a, 0, r, ky_tu);
    }
}


void ShellSort(ky_tu* ky_tu, int N, unsigned int h[], int k) 
{
    int step, i, j;
    int xn, x1, len, pos;
    for (step = 0; step < k; step ++) {
        len = h[step];
        for (i = len; i < N; i++) {
            x1 = ky_tu[i].freq;
            xn = ky_tu[i].c;
            pos = i - len;
            while ((x1 < ky_tu[pos].freq) && (pos >= 0)) { 
                ky_tu[pos + len].freq = ky_tu[pos].freq; 
                ky_tu[pos + len].c = ky_tu[pos].c; 
                pos = pos - len;
            }
            ky_tu[pos + len].freq = x1;
            ky_tu[pos + len].c = xn;
        }   
    }
}

void tao_mang_asii(int *a, ky_tu *ky_tu, int n){
    for(int i = 0; i < n; i++){
        a[i] = int(ky_tu[i].c);
    }
}

void dem_tan_suat(ky_tu *ky_tu, string arr, int n, int n_size){
    for(int i = 0; i < n_size; i++){
        ky_tu[i].freq = 0;
        for(int j = 0; j < n; j++){
            if(ky_tu[i].c == arr[j]){
                ky_tu[i].freq++;
            } 
        }
    }
}

void xoa_lap(ky_tu *ky_tu, int n, int &n_size){
    int index = 0;   
    for (int i = 0; i < n; i++) {
        int j;  
        for (j = 0; j < i; j++) {
            if (ky_tu[i].c == ky_tu[j].c){
                break;
            }    
        } 
        if (j == i){
            ky_tu[index++].c = ky_tu[i].c;
        }  
    }
    ky_tu[index].c = '\0'; 
}


int main(){
    string chuoi;
    cout << "Nhap chuoi: ";
    getline(cin, chuoi);
    chuoi.erase(remove(chuoi.begin(), chuoi.end(), ' '), chuoi.end());
    int n = chuoi.size();
    int n_static = chuoi.size();
    ky_tu kytu[20];
    int asciiArr[20];
    int freqArr[20];
    string fullArr;
    const int k = 3;
    unsigned int h[k] = {5, 3, 1};

    for(int i = 0; i < n; i++){
        kytu[i].c = chuoi[i];
        fullArr[i] = chuoi[i];
    }
    cout << endl;
    xoa_lap(kytu, n, n);
    
    n = 0;
    for(int i = 0; kytu[i].c != '\0'; i++){
        n++;
    }
    for(int i = 0; i < n; i++){
        kytu[i].freq = 0;
    }

    tao_mang_asii(asciiArr, kytu, n);
    for(int i = 0; i < n; i++){
        kytu[i].freq = 0;
        for(int j = 0; j < n_static; j++){
            if(kytu[i].c == fullArr[j]){
                kytu[i].freq++;
            } 
        }
    }
    heapSort(asciiArr, n, kytu);
    for(int i = 0; i < n; i++){
        cout << kytu[i].c << " ";
    }
    cout << endl;

    
    for(int i = 0; i < n; i++){
        kytu[i].freq = 0;
        for(int j = 0; j < n_static; j++){
            if(kytu[i].c == fullArr[j]){
                kytu[i].freq++;
            } 
        }
    }


    ShellSort(kytu, n, h, k);
    for(int i = 0; i < n; i++){
        cout << kytu[i].c << " ";
    }
    cout << endl;
    for(int i = 0; i < n; i++){
        cout << kytu[i].freq << " ";
    }
    cout << endl;
}
