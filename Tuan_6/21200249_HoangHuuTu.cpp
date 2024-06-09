#include <iostream>

using namespace std;

typedef struct NODE
{
    int data;
    NODE* left;
    NODE* right;
} Node;

typedef struct NODE* TREE;
TREE T;

void Init(Node* root)
{
	 root = NULL;
}

Node* GetNode (int x)
{
	Node* p = new Node;
	if (p != NULL)
	{
		p->left = NULL;
		p->right = NULL;
		p->data = x;
	}
	return (p);
} 

int InsertTree(TREE &T , int x)
{
    if(T != NULL)
    {
        if(T->data == x)  
            return 0;
        if(T->data > x) 
            return InsertTree(T->left, x);
        else   
            return InsertTree(T->right, x);
    }
    else
    {
        T = new Node;
        if(T == NULL) return -1;
        T->data=x;
        T->left=T->right=NULL;
        return 1;
    }
}

void CreateTree(TREE &T)
{
    int x, n;
    cout << "Nhap n = "; cin>>n;
    for(int i=1; i<=n; i++)
    {
        cout << "Nhap gia tri: "; 
        cin >> x;
        InsertTree(T, x);
    }
}

void NLR(TREE T)
{
    if (T!=NULL)
    {
        cout<<T->data<<" ";
        NLR(T->left);
        NLR(T->right);
    }
}

void LNR(TREE T)
{
    if (T!=NULL)
    {
        LNR(T->left);
        cout << T->data << " ";
        LNR(T->right);
    }
}

void LRN(TREE T)
{
    if (T!=NULL)
    {
        LRN(T->left);
        LRN(T->right);
        cout << T->data << " ";
    }
}

NODE* searchNode(TREE T,  int x)
{  
	NODE *p = T;
	while (p != NULL)
	{
		if(x == p->data) return p;
		else    
			if(x < p->data) p = p->left;
			else p = p->right;
	}
	return NULL;
}

void searchStandFor(TREE &p, TREE &q)
{
	if(q->left)
		  searchStandFor(p, q->left);
	else	
	{
		p->data = q->data;
	 	p  = q;
	  	q  = q->right;
	}
}


int delNode(TREE &T, int X)
{	
	if(T== NULL)	return 0;
	if(T->data > X)	return delNode(T->left, X);
	if(T->data < X)	return delNode(T->right, X);
	//T->Key == X
	Node* p = T;
	if(T->left == NULL)
		T = T->right;
	else{
        if(T->right == NULL) 
        T = T->left;
        else // T có đủ 2 con
        searchStandFor(p, T->right);
        delete p;
    }
    return 1;
}

int main(){
    int select;
    T = NULL;
    do{
        cout << "1. Cai dat cay nhi phan." << endl;
        cout << "2. Them node vao cay." << endl;
        cout << "3. Xoa mot node ra khoi cay." << endl;
        cout << "4. In duong di cua cac cay theo NLR, LNR, LRN" << endl;
        cout << "0. Thoat" << endl;
        cout << "Select: ";
        cin >> select;

        switch(select){
            case 1: CreateTree(T); break;
            case 2:
                int x;
                cout << "Nhap gia tri: ";
                cin >> x;
                InsertTree(T, x);
                cout << "Cay sau khi da them: ";
                NLR(T);
                cout << endl;
            break;
            case 3:
                int y;
                cout << "Nhap node muon xoa: ";
                cin >> y;
                delNode(T, y);
                cout << "Cay sau khi da xoa: " << endl;
                NLR(T);
            break;
            case 4: 
                cout << "NLR: ";
                NLR(T);
                cout << "\nLNR: ";
                LNR(T);
                cout << "\nLRN: ";
                LRN(T);
                cout << endl;
            break;
        }
    }while(select != 0);

    return 0;
}



