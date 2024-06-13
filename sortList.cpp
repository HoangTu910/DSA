#include <iostream>
#include <cstring>

using namespace std;

typedef struct sinhvien {
    char hoTen[20];
    char mssv[10];
    float diemTongKet[5];
    float diemTrungBinh = 0;
} sv;

typedef struct Node {
    sv data;
    Node *prev;
    Node *next;
} Node;

typedef struct List {
    Node *first;
    Node *last;
} List;

Node *getNode(sv x) {
    Node *p = new Node;
    if (p == NULL) return NULL;
    p->data = x;
    p->prev = NULL;
    p->next = NULL;
    return p;
}

Node *insertNode(List &l, sv x) {
    Node *new_ele = getNode(x);
    if (new_ele == NULL) return NULL;
    if (l.first == NULL) {
        l.first = new_ele;
        l.last = new_ele;
    } else {
        new_ele->next = l.first;
        l.first->prev = new_ele;
        l.first = new_ele;
    }
    return new_ele;
}

void removeLast(List &l) {
    if (l.last != NULL) {
        Node *p = l.last;
        l.last = l.last->prev;
        if (l.last != NULL) {
            l.last->next = NULL;
        } else {
            l.first = NULL;
        }
        delete p;
    }
}

Node* findNode(List &l, const char *mssv) {
    Node *p = l.first;
    while (p != NULL) {
        if (strcmp(mssv, p->data.mssv) == 0) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

void printList(List l) {
    Node *p = l.first;
    while (p != NULL) {
        cout << "Ho ten: " << p->data.hoTen << endl;
        cout << "MSSV: " << p->data.mssv << endl;
        cout << "Diem tong ket: ";
        for (int i = 0; i < 5; i++) {
            cout << p->data.diemTongKet[i] << " ";
        }
        cout << endl;
        cout << "Diem trung binh: " << p->data.diemTrungBinh << endl;
        p = p->next;
    }
}

void createList(List &l) {
    int n;
    sv sinhvien;
    cout << "Nhap so luong sinh vien: ";
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; i++) {
        float dtb = 0;
        cout << "Nhap ho ten sv " << i + 1 << ": ";
        cin.getline(sinhvien.hoTen, 20);
        cout << "Nhap mssv: ";
        cin.getline(sinhvien.mssv, 10);
        for (int j = 0; j < 5; j++) {
            cout << "Nhap diem mon thu " << j + 1 << ": ";
            cin >> sinhvien.diemTongKet[j];
            dtb += sinhvien.diemTongKet[j];
        }
        sinhvien.diemTrungBinh = dtb / 5;
        insertNode(l, sinhvien);
        cin.ignore();
    }
}

// void insertionSort(List &l){
//     if(l.first == NULL || l.first->next == NULL){
//         return;
//     }
//     Node *current = l.first->next;
//     while(current != NULL){
//         sv currentData = current->data;
//         Node *sortedNode = current->prev;
//         while(sortedNode != NULL && sortedNode->data.diemTrungBinh > currentData.diemTrungBinh){
//             sortedNode->next->data = sortedNode->data;
//             sortedNode = sortedNode->prev;
//         }
//         if(sortedNode == NULL){
//             l.first->data = currentData;
//         }
//         else{
//             sortedNode->next->data = currentData;
//         }
//         current = current->next;
//     }
// }

void insertionSort(List &l){
    if(l.first == NULL || l.first->next == NULL){
        return;
    }
    Node *currentNode = l.first;
    while(currentNode != NULL){
        sv currentData = currentNode->data;
        Node *sortedNode = currentNode->prev;
        while(sortedNode != NULL && sortedNode->data.diemTrungBinh > currentData.diemTrungBinh){
            sortedNode->next->data = sortedNode->data;
            sortedNode = sortedNode->prev;
        }
        if(sortedNode == NULL){
            l.first->data = currentData;
        }
        else{
            sortedNode->next->data = currentData;
        }
        currentNode = currentNode->next;
    }
}

// void addLast(List &l, Node* new_ele){
//     if(l.first == NULL){
//         l.first = new_ele;
//         l.last = new_ele;
//     }
//     else{
//         new_ele->next = l.first;
//         l.first->prev = new_ele;
//         l.first = new_ele;
//     }
// }

void addLast(List &l, Node *new_ele){
    if(l.first == NULL){
        l.first = new_ele;
        l.last = l.first;
    }
    else{
        l.last->next = new_ele;
        new_ele->prev = l.last;
        l.last = new_ele;
    }
}


void initList(List &l){
    l.first = l.last = NULL;
}

int getMaxElement(List l){
    Node *current = l.first;
    int max = current->data.diemTrungBinh;
    for(current = l.first; current; current = current->next){
        if(current->data.diemTrungBinh > max){
            max = current->data.diemTrungBinh;
        }
    }
    return max;
}

int getNumDigit(int k){
    int digit = 0;
    while(k > 0){
        digit++;
        k /= 10;
    }
    return digit;
}

int getDigit(int number, int k){
    while(k--){
        number /= 10;
    }
    return number % 10;
}

void listRadixSort(List &l){
    List bucket[10];
    int digitValue, digitIndex, maxVal, numDigit;
    maxVal = getMaxElement(l);
    numDigit = getNumDigit(maxVal);
    for(int i = 0; i < 10; i++){
        initList(bucket[i]);
    }
    for(digitIndex = 0; digitIndex < numDigit; ++digitIndex){
        for(int i = 0; i < 10; i++){
            initList(bucket[i]);
        }
        Node *current;
        while(l.first!= NULL){
            current = l.first;
            l.first = current->next;
            current->next = NULL;
            digitValue = getDigit(current->data.diemTrungBinh, digitIndex);
            addLast(bucket[digitValue], current);
        }
        l.first = NULL;
        for(int i = 0; i < 10; i++){
            if(bucket[i].first != NULL){
                if(l.first == NULL){
                    l.first = bucket[i].first;
                    l.last = bucket[i].last;
                }
                else{
                    l.last->next = bucket[i].first;
                    l.last = bucket[i].last;
                }
            }
        }
    }
}

// Node* Merge(Node* bList, Node* cList) {
//     Node* mergedHead = nullptr;
//     Node* mergedTail = nullptr;

//     while (bList && cList) {
//         Node* temp;
//         if (bList->data.diemTrungBinh <= cList->data.diemTrungBinh) {
//             temp = bList;
//             bList = bList->next;
//         } else {
//             temp = cList;
//             cList = cList->next;
//         }

//         if (!mergedHead) {
//             mergedHead = temp;
//             mergedHead->prev = nullptr;
//         } else {
//             mergedTail->next = temp;
//             temp->prev = mergedTail;
//         }
//         mergedTail = temp;
//     }

//     while (bList) {
//         if (!mergedHead) {
//             mergedHead = bList;
//             bList->prev = nullptr;
//         } else {
//             mergedTail->next = bList;
//             bList->prev = mergedTail;
//         }
//         mergedTail = bList;
//         bList = bList->next;
//     }

//     while (cList) {
//         if (!mergedHead) {
//             mergedHead = cList;
//             cList->prev = nullptr;
//         } else {
//             mergedTail->next = cList;
//             cList->prev = mergedTail;
//         }
//         mergedTail = cList;
//         cList = cList->next;
//     }

//     if (mergedTail) {
//         mergedTail->next = nullptr;
//     }

//     return mergedHead;
// }

// void Distribute(Node* source, Node*& bList, Node*& cList, int segmentSize) {
//     Node* current = source;
//     bList = cList = nullptr;
//     Node* bTail = nullptr;
//     Node* cTail = nullptr;

//     while (current) {
//         int count = 0;
//         while (current && count < segmentSize) {
//             if (!bList) {
//                 bList = current;
//             } else {
//                 bTail->next = current;
//                 current->prev = bTail;
//             }
//             bTail = current;
//             current = current->next;
//             count++;
//         }
//         if (bTail) bTail->next = nullptr;

//         count = 0;
//         while (current && count < segmentSize) {
//             if (!cList) {
//                 cList = current;
//             } else {
//                 cTail->next = current;
//                 current->prev = cTail;
//             }
//             cTail = current;
//             current = current->next;
//             count++;
//         }
//         if (cTail) cTail->next = nullptr;
//     }
// }

// void MergeSort(Node*& head) {
//     if (!head || !head->next) return;

//     Node* bList = nullptr;
//     Node* cList = nullptr;
//     int segmentSize = 1;

//     while (true) {
//         Distribute(head, bList, cList, segmentSize);

//         if (!cList) break;

//         head = Merge(bList, cList);
//         segmentSize *= 2;
//     }
// }
void listQSort(List &l){
    Node *pivot, *current;
    List lessList, greaterList;
    if(l.first == l.last) return;

    lessList.first = lessList.last = NULL;
    greaterList.first = greaterList.last = NULL;

    pivot = l.first;
    l.first = pivot->next;

    while(l.first != NULL){
        current = l.first;
        l.first = current->next;
        current->next = NULL;

        if(current->data.diemTrungBinh <= pivot->data.diemTrungBinh){
            addLast(lessList, current);
        }
        else{
            addLast(greaterList, current);
        }
    } 

    listQSort(lessList);
    listQSort(greaterList);


    if(lessList.first != NULL){
        l.first = lessList.first;
        lessList.last->next = pivot;
    }
    else{
        l.first = pivot;
    }

    pivot->next = greaterList.first;

    if(greaterList.first != NULL){
        l.last = greaterList.last;
        greaterList.first->prev = pivot;
    }
    else{
        l.last = pivot;
    }
}


int main(){
    List l;
    char f[10];
    l.first = l.last = NULL;
    createList(l);
    printList(l);
    // cin.ignore();
    // cout << "Tim: ";
    // cin.getline(f, 10);
    // if(findNode(l, f) != NULL){
    //     cout << "Tim thay !" << endl;
    // }
    cout << "Sau khi sort" << endl;
    //insertionSort(l);
    //listRadixSort(l);
    //listMergeSort(l);
    listQSort(l);
    printList(l);
    // removeLast(l);
    // printList(l);
}
