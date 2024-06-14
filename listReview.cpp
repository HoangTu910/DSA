#include <iostream>
#include <cstring>

using namespace std;

typedef struct sinhVien{
    char hoTen[20];
    char mssv[10];
    float diemThi[5];
    float dtb;
} sv;

typedef struct Node{
    sv data;
    Node *prev;
    Node *next;
} Node;

typedef struct List {
    Node *first;
    Node *last;
} List;

Node* getNode(sv x){
    Node *p = new Node;
    if(p == NULL){
        cout << "ERROR" << endl;
        return NULL;
    } 
    p->data = x;
    p->next = NULL;
    p->prev = NULL;
    return p;
}

void addFirst(List &l, Node *new_node){
    if(l.first == NULL){
        l.first = new_node;
        l.last = new_node;
    }
    else{
        new_node->next = l.first;
        l.first->prev = new_node;
        l.first = new_node;
    }
}

void addLast(List &l, Node *new_node){
    if(l.first == NULL){
        l.first = new_node;
        l.last = new_node;
    }
    else{
        l.last->next = new_node;
        new_node->prev = l.last;
        l.last = new_node;
    }
}

Node* insertNode(List &l, sv x){
    Node *p = getNode(x);
    if(p == NULL){
        cout << "Khong du bo nho !" << endl;
        return NULL;
    }
    addFirst(l, p);
    return p;
}

void createList(List &l){
    int n;
    sv s;
    cout << "Nhap N: ";
    cin >> n;
    for(int i = 0; i < n; i++){
        float _dtb = 0;
        cin.ignore();
        cout << "Ho ten: ";
        cin.getline(s.hoTen, 20);
        cout << "MSSV: ";
        cin.getline(s.mssv, 20);
        for(int j = 0; j < 5; j++){
            cout << "Diem mon thu " << j+1 << ": ";
            cin >> s.diemThi[j];
            _dtb += s.diemThi[j];
        }
        s.dtb = _dtb/5;
        insertNode(l, s);
    }
}


void printList(List &l){
    Node *p = l.first;
    while(p != NULL){
        cout << p->data.hoTen << endl;
        cout << p->data.mssv << endl;
        for(int i = 0; i < 5; i++){
            cout << p->data.diemThi[i] << " ";
        }
        cout << endl;
        cout << "DTB: " << p->data.dtb << endl;
        p = p->next;
    }
}

void removeLast(List &l){
    if(l.last != NULL){
        Node *p = l.last;
        l.last = l.last->prev;
        if(l.last != NULL){
            l.last->next = NULL;
        }
        else{
            l.first = NULL;
        }
        delete p;
    }
}

// void listInsertionSort(List &l){
//     if(l.first == NULL || l.first->next == NULL) return;
//     Node *currentNode = l.first;
//     while(currentNode){
//         sv currentData = currentNode->data;
//         Node *sortedNode = currentNode->prev;
//         while(sortedNode != NULL && sortedNode->data.dtb > currentData.dtb){
//             sortedNode->next->data = sortedNode->data;
//             sortedNode = sortedNode->prev;
//         }
//         if(sortedNode == NULL){
//             l.first->data = currentData;
//         }
//         else{
//             sortedNode->next->data = currentData;
//         }
//         currentNode = currentNode->next;
//     }
// }

void listInsertionSort(List &l){
    if(l.first == NULL || l.first->next == NULL) return;
    Node *currentNode = l.first->next;
    
    while(currentNode){
        sv currentData = currentNode->data;
        Node *sortedNode = currentNode->prev;
        while(sortedNode != NULL && sortedNode->data.dtb > currentData.dtb){
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

void initList(List &l){
    l.first = l.last = NULL;
}

int getMax(List l){
    int max = l.first->data.dtb;
    Node *current = l.first;
    for(current = l.first; current; current = current->next){
        if(current->data.dtb > max){
            max = current->data.dtb;
        }
    }
    return max;
}

int getDigit(int num, int k){
    while(k--){
        num /= 10;
    }
    return num % 10;
}

int getNumDigit(int num){
    int count = 0;
    while(num > 0){
        count++;
        num /= 10;
    }
    return count;
}

void listRadixSort(List &l){
    int maxVal, numDigit;
    maxVal = getMax(l);
    numDigit = getNumDigit(maxVal);
    List counterArr[10];
    for(int i = 0; i < 10; i++){
        initList(counterArr[i]);
    }
    Node *current;
    for(int digitIndex = 0; digitIndex < numDigit; ++digitIndex){
        for(int i = 0; i < 10; i++){
            initList(counterArr[i]);
        }
        while(l.first != NULL){
            current = l.first;
            l.first = current->next;
            current->next = NULL;
            int digitVal = getDigit(current->data.dtb, digitIndex);
            addLast(counterArr[digitVal], current);
        }
        l.first = NULL;
        for(int i = 0; i < 10; i++){
            if(counterArr[i].first != NULL){
                if(l.first == NULL){
                    l.first = counterArr[i].first;
                    l.last = counterArr[i].last;
                }
                else{
                    l.last->next = counterArr[i].first;
                    l.last = counterArr[i].last;
                }
            }
        }
    }
}

void listQSort(List &l){
    Node *pivot, *current;
    List lessList, greaterList;
    if(l.first == l.last) return;
    initList(lessList);
    initList(greaterList);
    pivot = l.first;
    l.first = pivot->next;

    while(l.first != NULL){
        current = l.first;
        l.first = current->next;
        current->next = NULL;

        if(current->data.dtb < pivot->data.dtb){
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
    l.first = l.last = NULL;
    createList(l);
    printList(l);
    cout << "=============Sort=============" << endl;
    //listInsertionSort(l);
    //listRadixSort(l);   
    listQSort(l);
    printList(l);
}
