#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>

#define LH -1
#define EH 0
#define RH 1

using namespace std;

typedef struct tagAVLNode{
    char balFactor;
    int key;
    struct tagAVLNode* pLeft;
    struct tagAVLNode* pRight;
}AVLNode;

typedef AVLNode *AVLTree;

void Init(AVLNode* root){
    root = NULL;
}

void rotateLL(AVLTree &T){
    AVLNode* T1 = T->pLeft;
    T->pLeft = T->pRight;
    T1->pRight = T;
    switch(T1->balFactor){
        case LH: T->balFactor = EH;
                T1->balFactor = EH; break;
        case EH: T->balFactor = LH;
                T1->balFactor = RH; break;
    }
    T = T1;
}

void rotateRR(AVLTree &T){
    AVLNode* T1 = T->pRight;
    T->pRight = T1->pLeft;
    T1->pLeft = T;
    switch (T1->balFactor)
    {
        case RH: T->balFactor = EH;
                T1->balFactor = EH; break;
        case EH: T->balFactor = RH;
                T1->balFactor = LH; break;
    }
    T = T1;
}

void rotateLR(AVLTree &T){
    AVLNode* T1 = T->pLeft;
    AVLNode* T2 = T1->pRight;
    T->pLeft = T2->pRight;
    T2->pRight = T;  
    T1->pRight = T2->pLeft;
    T2->pLeft = T1;
    switch (T2->balFactor)
    {
        case LH: T->balFactor = RH;
                T1->balFactor = EH; break;
        case EH: T->balFactor = EH;
                T1->balFactor = EH; break;
        case RH: T->balFactor = EH;
                T1->balFactor = LH; break;
    }
    T2->balFactor = EH;
    T = T2;
}

void rotateRL(AVLTree &T){
    AVLNode* T1 = T->pRight;
    AVLNode* T2 = T1->pLeft;
    T->pRight = T2->pLeft;
    T2->pLeft = T;
    T1->pLeft = T2->pRight;
    T2->pRight = T1;
    switch(T2->balFactor){
        case RH: T->balFactor = LH;
                T1->balFactor = EH; break;
        case EH: T->balFactor = EH;
                T1->balFactor = EH; break;
        case LH: T->balFactor = EH;
                T1->balFactor = RH; break;
    }
    T2->balFactor = EH;
    T = T2;
}

int balanceRight(AVLTree &T){
    AVLNode* T1 = T->pRight;
    switch (T1->balFactor)
    {
        case LH: rotateRL(T); return 2;
        case EH: rotateRR(T); return 1;
        case RH: rotateRR(T); return 2;
    }
    return 0;
}

int balanceLeft(AVLTree &T){
    AVLNode* T1 = T->pLeft;
    switch(T1->balFactor){
        case LH: rotateLL(T); return 2;
        case EH: rotateLL(T); return 1;
        case RH: rotateLR(T); return 2;
    }
    return 0;
}

int insertNode(AVLTree &T, int x){
    int res;
    if(T){
        if(T->key == x) return 0;
        if(T->key > x){
            res = insertNode(T->pLeft, x);
            if(res < 2) return res;
            switch(T->balFactor){
                case RH: T->balFactor = EH; return 1;
                case EH: T->balFactor = LH; return 2;
                case LH: balanceLeft(T); return 1;
            }
        }
        else{
            res = insertNode(T->pRight, x);
            if(res < 2) return res;
            switch(T->balFactor){
                case LH: T->balFactor = EH; return 1;
                case EH: T->balFactor = RH; return 2;
                case RH: balanceRight(T); return 1;
            }
        }
    }
    T = new AVLNode;
    if(T == NULL) return -1;
    T->key = x; T->balFactor = EH;
    T->pLeft = T->pRight = NULL;
    return 2;
}


void createTree(AVLTree &T){
    int x, n;
    cout << "Nhap n = "; cin>>n;
    for(int i=1; i<=n; i++)
    {
        cout << "Nhap gia tri: "; 
        cin >> x;
        insertNode(T, x);
    }
}

void AVLType(AVLTree T) {
    if (T == nullptr) {
        cout << "Cay trong." << endl;
        return;
    }

    if (T->balFactor == EH) {
        cout << "Cay can bang" << endl;
    }
    else if (T->balFactor == LH) {
        if (T->pLeft != nullptr && T->pLeft->balFactor == LH) {
            cout << "Lech trai trai (LL)" << endl;
        } else if (T->pLeft != nullptr && T->pLeft->balFactor == RH) {
            cout << "Lech trai phai (LR)" << endl;
        } else {
            cout << "Lech trai (L)" << endl;
        }
    }
    else if (T->balFactor == RH) {
        if (T->pRight != nullptr && T->pRight->balFactor == RH) {
            cout << "Lech phai phai (RR)" << endl;
        } else if (T->pRight != nullptr && T->pRight->balFactor == LH) {
            cout << "Lech phai trai (RL)" << endl;
        } else {
            cout << "Lech phai (R)" << endl;
        }
    }
}

void printTree(AVLTree T) {
    if (T == NULL) {
        return;
    }

    queue<AVLNode*> currentLevel, nextLevel;
    currentLevel.push(T);

    while (!currentLevel.empty()) {
        AVLNode* current = currentLevel.front();
        currentLevel.pop();

        if (current) {
            cout << current->key << " ";
            nextLevel.push(current->pLeft);
            nextLevel.push(current->pRight);
        }

        if (currentLevel.empty()) {
            cout << endl;
            swap(currentLevel, nextLevel);
        }
    }
}

int searchStandFor(AVLTree &p,  AVLTree &q){
    int res;
    if(q->pLeft){
        res = searchStandFor(p, q->pLeft);
        if(res < 2) return res;
        switch(q->balFactor){
            case LH: q->balFactor = EH; return 2;
            case EH: q->balFactor = RH; return 1;
            case RH: return balanceRight(q);
        }
    }
    else{
        p->key = q->key;
        p = q;
        q = q->pRight;
        return 2;
    }   
}

int delNode(AVLTree &T, int x){
    int res;
    if(T == NULL) return 0;
    if(T->key > x){
        res = delNode (T->pLeft, x);
        if(res < 2) return res;
        switch(T->balFactor){
            case LH: T->balFactor = EH; return 2;
            case EH: T->balFactor = RH; return 1;
            case RH: return balanceRight(T);
        }
    }
    if(T->key < x){
        res == delNode(T->pRight, x);
        if(res < 2) return res;
        switch(T->balFactor){
            case RH: T->balFactor = EH; return 2;
            case EH: T->balFactor =  LH; return 1;
            case LH: return balanceLeft(T);
        }
    }
    else{
        AVLNode* p = T;
        if(T->pLeft == NULL){
            T = T->pRight; 
            res = 2;
        }
        else if(T->pRight == NULL){
            T =T->pLeft;
            res = 2;
        }
        else{
            res = searchStandFor(p, T->pRight);
            if(res < 2) return res;
            switch(T->balFactor){
                case RH: T->balFactor = EH; return 2;
                case EH:  T->balFactor = LH; return 1;
                case LH: return balanceLeft(T);
            }
        }
        delete p;
        return res;
    }
}

void addRandom(AVLTree &T){
    srand(time(0));
    int x = rand() % 101;
    insertNode(T, x);
}

int main(){
    AVLTree T;
    T = NULL;
    int select;
    do{
        cout << "1. Cai dat cay nhi phan." << endl;
        cout << "2. Them node co gia tri ngau nhien vao cay." << endl;
        cout << "3. Hien thi cay nhi phan" << endl;
        cout << "4. Xac dinh loai lech AVL" << endl;
        cout << "5. Xoa node theo khoa x" << endl;
        cout << "0. Thoat" << endl;
        cout << "Select: ";
        cin >> select;

        switch(select){
            case 1: createTree(T); break;
            case 2:
                addRandom(T);
                cout << "Cay sau khi da them: "  <<endl;
                printTree(T);
                cout << endl;
            break;
            case 3:
                printTree(T);
                cout << endl;
                break;
            case 4: 
                AVLType(T);
                cout << endl;
                break;
            case 5:
                int x;
                cout << "Nhap khoa x: ";
                cin >> x;
                delNode(T, x);
        }
    }while(select != 0);
}