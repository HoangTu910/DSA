#include <iostream>

using namespace std;

typedef struct NODE{
    int data;
    NODE* left;
    NODE* right;
} NODE;

typedef struct NODE* TREE;
TREE T;

int insertTree(TREE &T, int x){
    if(T != NULL){
        if(T->data == x) {
            return 0;
        }
        if(T->data > x){
            return insertTree(T->left, x);
        }
        else{
            return insertTree(T->right, x);
        }
    }
    else{
        T = new NODE;
        if(T == NULL) return -1;
        T->data = x;
        T->left = T->right = NULL;
        return 1;
    }
}

void createTree(TREE &T){
    int x, n;
    cout << "Nhap so luong node: ";
    cin >> n;
    for(int i = 0; i < n; i++){
        cout << "Nhap x: ";
        cin >> x;
        insertTree(T, x);
    }
}

void NLR(TREE T){
    if(T != NULL){
        cout << T->data << " ";
        NLR(T->left);
        NLR(T->right);
    }
}

void LNR(TREE T){
    if(T != NULL){
        LNR(T->left);
        cout << T->data << " ";
        LNR(T->right);
    }
}

void LRN(TREE T){
    if(T != NULL){
        LRN(T->left);
        LRN(T->right);
        cout << T->data << " ";
    }
}

void searchStandFor(TREE &p, TREE &q){
    if(q->left){
        searchStandFor(p, q->left);
    }
    else{
        p->data = q->data;
        p = q;
        q = q->right;
    }
}

int delNode(TREE &T, int x){
    if(T == NULL) return 0;
    if(T->data > x) return delNode(T->left, x);
    if(T->data < x) return delNode(T->right, x);
    NODE* p = T;
    if(T->left == NULL){
        T = T->right;
    }
    else{
        if(T->right == NULL){
            T = T->left;
        }
        else{
            searchStandFor(p, T->right);
            delete p;
        }
    }
    return 1;
}

int main(){
    T = NULL;
    int x;
    createTree(T);
    LNR(T); cout << endl;
    LRN(T); cout << endl;
    NLR(T); cout << endl;
    cout << "Nhap gia tri: ";
    cin >> x;
    insertTree(T, x);
    LNR(T); cout << endl;
    LRN(T); cout << endl;
    NLR(T); cout << endl;
    cout << "Chon node muon xoa: ";
    cin >> x;
    delNode(T, x);
    LNR(T); cout << endl;
    LRN(T); cout << endl;
    NLR(T); cout << endl;
}