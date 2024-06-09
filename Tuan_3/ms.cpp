#include <iostream>
using namespace std;

struct node {
    int data;
    node* prev;
    node* next;
};

struct DList {
    node* first;
    node* last;
};

node* GetNode(int x) {
    node* p = new node;
    if (p == NULL) {
        cout << "Khong du bo nho";
        exit(1);
    }
    p->data = x;
    p->prev = NULL;
    p->next = NULL;
    return p;
}



void add_node(DList& l, int x) {
    node* new_ele = GetNode(x);
    if (new_ele == NULL) {
        return;
    }
    if (l.first == NULL) {
        l.first = new_ele;
        l.last = l.first;
    } else {
        new_ele->prev = l.last;
        l.last->next = new_ele;
        l.last = new_ele;
    }
}

void Output(DList l) {
    node* p = l.first;
    while (p != NULL) {
        cout << p->data << "\t";
        p = p->next;
    }
    cout << endl;
}

void init_list(DList& l) {
    l.first = l.last = NULL;
}

void Create_List_Last(DList& l) {
    int n, in;
    cout << "Nhap so phan tu: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> in;
        add_node(l, in);
    }
}

// node* find_mid(node* head){
//     node* slow = head;
//     node* fast = head->next; 
//     while (fast && fast->next) {
//         slow = slow->next;
//         fast = fast->next->next;
//     }
//     return slow;
// }


// node* merge(node* half1, node* half2){
//     node* dummy = new node;
//     node* tail = dummy;
//     while(half1 && half2){
//         if(half1->data < half2->data){
//             tail->next = half1;
//             half1 = half1->next;
//         }
//         else{
//             tail->next = half2;
//             half2 = half2->next;
//         }
//         tail = tail->next;
//     }
//     if(half1){
//         tail->next = half1;
//     }
//     if(half2){
//         tail->next = half2;
//     }
//     return dummy->next;
// }

void AddLast(DList& l, node* new_ele) {
    if (l.first == NULL) {
        l.first = new_ele;
        l.last = l.first;
    } else {
        l.last->next = new_ele;
        new_ele->prev = l.last;
        l.last = new_ele;
    }
}


void DistributeList(DList &l, DList &l1, DList &l2){
    node *p;
    do{
        p = l.first;
        l.first = p->next;
        p->next = NULL;
        AddLast(l1, p);
    }while((l.first) && (p->data <= l.first->data));
    if(l.first){
        DistributeList(l, l2, l1);
    }
    else{
        l.first = NULL;
    }
}

void MergeList(DList &l, DList &l1, DList &l2){
    node *p;
    while((l1.first) && (l2.first)){
        if(l1.first->data <= l2.first->data){
            p = l1.first;
            l1.first = p->next;
        }
        else{
            p = l2.first;
            l2.first = p->next;
        }
        p->next = NULL;
        AddLast(l, p);
    };
    if(l1.first){
        l.last->next = l1.first;
        l.last = l1.last;
    }
    else if(l2.first){
        l.last->next = l2.first;
        l.last = l2.last;
    }
}

void merge_sort(DList &l){
    DList l1, l2;
    if(l.first == l.last || l.first == NULL) return;
    cout << "TEST" << endl;
    init_list(l1);
    init_list(l2);
    DistributeList(l, l1, l2);
    merge_sort(l1);
    merge_sort(l2); 
    MergeList(l, l1, l2);
}

void insertion_sort(DList& l) {
    if (l.first == nullptr || l.first->next == nullptr) {
        return;
    }

    node* i = l.first->next;

    while (i != nullptr) {
        int x = i->data;
        node* j = i->prev;

        while (j != nullptr && j->data > x) {
            j->next->data = j->data;
            j = j->prev;
        }

        if (j == nullptr) {
            l.first->data = x;
        } else {
            j->next->data = x;
        }

        i = i->next;
    }
}

// node* merge_sort(node* head){
//     if(!head || !head->next){
//         return head;
//     }
//     node* left = head;
//     node* right = find_mid(head);
//     node* temp = right->next;
//     right->next = NULL;
//     right = temp;
//     left = merge_sort(left);
//     right = merge_sort(right);
//     node *ans = merge(left, right);
//     return ans;
// }

int main() {
    DList l;
    l.first = l.last = NULL;
    node* head = l.first;
    Create_List_Last(l);
    cout << "Ban dau:" << endl;
    Output(l);
    merge_sort(l);
    //insertion_sort(l);
    cout << "Sap xep:" << endl;
    Output(l);
    return 0;
}
