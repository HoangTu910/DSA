#include <iostream>
#include <vector>

using namespace std;

struct MaHang{
    unsigned int id;
    unsigned int so_luong;
    float don_gia;
};

void print(vector<MaHang> a){
        for(int i = 0; i < a.size(); i++){
            cout << "ID san pham: " << a[i].id << endl;
            cout << "So luong san pham: " << a[i].so_luong << endl;
            cout << "Don gia san pham: " << a[i].don_gia << endl;
            cout << "========================" << endl;
        }
    }

void radixSort(vector<MaHang> &a)
{
    int n = a.size();
    vector<MaHang> b(n);
	int i, m = a[0].id, exp = 1;
	for (i = 0; i < n; i++){
		if (a[i].id > m)
			m = a[i].id;
	}
	while (m / exp > 0){
		int bucket[10] = { 0 };
		for (i = 0; i < n; i++)
			bucket[a[i].id / exp % 10]++;
		for (i = 1; i < 10; i++)
			bucket[i] += bucket[i - 1];
		for (i = n - 1; i >= 0; i--)
			b[--bucket[a[i].id / exp % 10]].id = a[i].id;
		for (i = 0; i < n; i++)
			a[i].id = b[i].id;
		exp *= 10;
	}
}

void Swap(float &a, float &b){
    float temp = a;
    a = b;
    b = temp;
}

void quickSortMid(vector<MaHang> &a, int left, int right) {
    int i, j;
    float x;
    if (left < right) {
        x = a[(left + right) / 2].don_gia;
        i = left;
        j = right;
        do {
            while (a[i].don_gia < x) i++;
            while (a[j].don_gia > x) j--;
            if (i <= j) {
                Swap(a[i].don_gia, a[j].don_gia);
                i++;
                j--;
            }
        } while (i <= j);
        if (left < j) quickSortMid(a, left, j);
        if (i < right) quickSortMid(a, i, right);
    }
}

void quickSortStart(vector<MaHang> &a, int left, int right) {
    int i, j;
    float x;
    if (left < right) {
        x = a[left].don_gia;
        i = left;
        j = right;
        do {
            while (a[i].don_gia < x) i++;
            while (a[j].don_gia > x) j--;
            if (i <= j) {
                Swap(a[i].don_gia, a[j].don_gia);
                i++;
                j--;
            }
        } while (i <= j);
        if (left < j) quickSortStart(a, left, j);
        if (i < right) quickSortStart(a, i, right);
    }
}

int main(){
    vector<MaHang> maHang = {
        {123, 10, 50.5},
        {456, 5, 20.0},
        {789, 15, 70.0},
        {101, 12, 30.0},
        {107, 18, 80.0}
    };
    radixSort(maHang);
    cout << "Radix Sort" << endl;
    print(maHang);
    cout << "Quick Sort" << endl;
    quickSortStart(maHang, 0, maHang.size()-1);
    print(maHang);
}