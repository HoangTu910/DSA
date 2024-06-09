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

node* find_mid(node* head){
    node* slow = head;
    node* fast = head->next; 
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}


node* merge(node* half1, node* half2){
    node* dummy = new node;
    node* tail = dummy;
    while(half1 && half2){
        if(half1->data < half2->data){
            tail->next = half1;
            half1 = half1->next;
        }
        else{
            tail->next = half2;
            half2 = half2->next;
        }
        tail = tail->next;
    }
    if(half1){
        tail->next = half1;
    }
    if(half2){
        tail->next = half2;
    }
    return dummy->next;
}


node* merge_sort(node* head){
    if(!head || !head->next){
        return head;
    }
    node* left = head;
    node* right = find_mid(head);
    node* temp = right->next;
    right->next = NULL;
    right = temp;
    left = merge_sort(left);
    right = merge_sort(right);
    node *ans = merge(left, right);
    return ans;
}

void RemoveAfter(DList& l, node* q) {
  node* p;
  if (q != NULL) {
    p = q->next;
    if (p != NULL) {
      q->next = p->next;
      if (p == l.last) l.last = q; 
      else p->next->prev = q;
    delete p;
   }
  }
}


void remove_duplicate(DList &l, node* head){
    node* current = head;
    while (current != nullptr && current->next != nullptr) {
        if (current->data == current->next->data) {
            node* duplicate = current->next;  
            current->next = duplicate->next;  
            if (duplicate->next != nullptr) {
                duplicate->next->prev = current;  
            }
            delete duplicate;  
        } else {
            current = current->next;  
        }
    }
}

void RemoveBefore(DList& l, node* q) {
  node* p;
  if (q != NULL) {
    p = q->prev;
    if (p != NULL) {
      q->prev = p->prev;
      if (p == l.first){
        l.first = q;
      } 
      else p->prev->next = q;
    delete p;
    }
  }
}

void remove_higher(DList &l, node* head, int higher){
    node* current = head;
    while (current != nullptr) {
        if (current->data > higher) {
            if (current == head) {
                head = current->next;
                if (head != nullptr) {
                    head->prev = nullptr;
                }
                delete current;
                current = head;
            } else {
                node* previous = current->prev;
                previous->next = current->next;
                if (current->next != nullptr) {
                    current->next->prev = previous;
                }
                node* temp = current;
                current = current->next;
                delete temp;
            }
        } else {
            current = current->next;
        }
    }
}

int main() {
    DList l;
    l.first = l.last = NULL;
    node* head = l.first;
    Create_List_Last(l);
    cout << "Ban dau: " << endl;
    Output(l);
    cout << "Xoa duplicate:" << endl;
    l.first = merge_sort(l.first);
    remove_duplicate(l, l.first);
    Output(l);
    remove_higher(l, l.first, 5);
    Output(l);
    return 0;
}