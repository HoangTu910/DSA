#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>

#define LH -1 //cay con trai cao hon
#define EH 0 //hai cay con bang nhau
#define RH 1 //cay con phai cao hon

using namespace std;

typedef struct tagAVLNode{
    char balFactor;
    int key;
    struct tagAVLNode* pLeft;
    struct tagAVLNode* pRigth;
} AVLNode;

typedef AVLNode *AVLTree;

void rotateLL(AVLTree &T){
    AVLNode *T1 = T->pLeft;
    T->pLeft = T1->pRigth;
    T1->pRigth = T;
    switch(T1->balFactor){
        case LH: T->balFactor = EH;
                T1->balFactor = EH;
                break;
        case EH: T->balFactor = LH;
                T1->balFactor = RH;
                break;
    }
    T = T1;
}

void rotateRR(AVLTree &T){
    AVLNode* T1 = T->pRigth;
    T->pRigth = T1->pLeft;
    T1->pLeft = T;
    switch(T1->balFactor){
        case RH: T->balFactor = EH;
                T1->balFactor = EH;
                break;
        case EH: T->balFactor = RH;
                T1->balFactor = LH;
                break;
    }
    T = T1;
}

void rotateLR(AVLTree &T){
    AVLNode* T1 = T->pLeft;
    AVLNode* T2 = T1->pRigth;
    T->pLeft = T2->pRigth;
    T2->pRigth = T;
    T1->pRigth = T2->pLeft;
    T2->pLeft = T1;
    switch(T2->balFactor){
        case LH: T->balFactor = RH;
                T1->balFactor = EH;
                break;
        case EH: T->balFactor = EH;
                T1->balFactor = EH;
                break;
        case RH: T->balFactor = EH;
                T1->balFactor = LH;
                break;
    }
    T2->balFactor = EH;
    T = T2;
}

void rotateRL(AVLTree &T){
    AVLNode* T1 = T->pRigth;
    AVLNode* T2 = T1->pLeft;
    T->pRigth = T2->pLeft;
    T2->pLeft = T;
    T1->pLeft = T2->pRigth;
    T2->pRigth = T1;
    switch(T2->balFactor){
        case RH: T->balFactor = LH;
                T1->balFactor = EH;
                break;
        case EH: T->balFactor = EH;
                T1->balFactor = EH;
                break;
        case LH: T->balFactor = EH;
                T1->balFactor = RH;
                break;
    }
    T2->balFactor = EH;
    T = T2;
}

int balanceLeft(AVLTree &T){
    AVLNode*T1 = T->pLeft;
    switch(T1->balFactor){
        case LH: rotateLL(T); return 2;
        case EH: rotateLL(T); return 1;
        case RH: rotateLR(T); return 2;
    }
    return 0;
}

int balanceRight(AVLTree &T){
    AVLNode* T1 = T->pRigth;
    switch(T1->balFactor){
        case LH: rotateRL(T); return 2;
        case EH: rotateRR(T); return 1;
        case RH: rotateRR(T); return 2;
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
                case RH: T->balFactor = EH;
                        return 1;
                case EH: T->balFactor = LH;
                        return 2;
                case LH: balanceLeft(T); return 1;
            }
        }
        else{
            res = insertNode(T->pRigth, x);
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
    T->pLeft = T->pRigth = NULL;
    return 2;
}

void createNode(AVLTree &T){
    srand(time(nullptr));
    int n;
    cout << "Nhap so node: ";
    cin >> n;
    for(int i = 0; i <= n; i++){
        int _rand = rand() % 100;
        insertNode(T, _rand);
    }
}

void addNode(AVLTree &T){
    srand(time(nullptr));
    int x = rand() % 100;
    insertNode(T, x);
    cout << "Da them node !" << endl;
}

void printTree(AVLTree root) {
    if (root == nullptr) return;

    queue<AVLNode*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size(); 
        while (levelSize > 0) {
            AVLNode* currentNode = q.front();
            q.pop();
            cout << currentNode->key << " ";

            if (currentNode->pLeft) q.push(currentNode->pLeft);
            if (currentNode->pRigth) q.push(currentNode->pRigth);

            levelSize--;
        }
        cout << endl; 
    }
}

int main(){
    AVLTree T;
    T = nullptr;
    createNode(T);
    printTree(T);
    addNode(T);
    printTree(T);
}