#include <iostream>
#include <string>

using namespace std;

typedef struct node
{
    char data;
    node *link;
};

typedef struct stack
{
    node *top;
};

typedef struct queue
{
    node *front, *rear;
};

void Init_Queue(queue &q)
{
	q.front=q.rear= NULL; 
}

bool Empty_Queue(queue &q)
{ 
	if (q.front == NULL) return 1; 
	else return 0;
}

void EnQueue(queue& q, node* x) {
    if (x == nullptr) {
        return;  // Invalid node, cannot enqueue
    }

    if (q.front == nullptr) {
        q.front = q.rear = x;
    } else {
        q.rear->link = x;
        q.rear = x;
    }

    x->link = nullptr;
}

int size(queue &q){
    int count = 0;
    node* temp = q.front;
  
    while(temp != NULL){
        temp = temp->link;
        count++;
    }
  
    return count;
}

node* DeQueue(queue &q)
{	
	if (!Empty_Queue(q))
	{
		node *p=q.front;
		q.front=p->link;
		return p;
	}
} 

void Init(stack &top)
{
    top.top = NULL;
}

bool Empty(stack top)
{ 
	return top.top == NULL ? 1 : 0; // stack rỗng 
}

void Push(stack &top, node* x)
{	
	stack p;
	p.top = new node;
	if(p.top != NULL)
	{
        p.top->data=x->data;
        p.top->link=top.top;
        top = p;
	}
}

node* GetNode(char x) {
    node* p = new node;
    if (p == NULL) {
        cout << "Khong du bo nho";
        exit(1);
    }
    p->data = x;
    p->link = NULL;
    return p;
}

char Pop(stack &top)
{	
	if(!Empty(top))     
	{
		stack p = top;
		top.top = p.top->link;
		free(p.top);
        return p.top->data;
	}
}

int main(){
    string str = "({[]})";
    string que = "radar";
    stack st;
    queue q;
    Init_Queue(q);
    Init(st);
    bool check = true;
    //Kiem tra dau ngoac
    cout << "Kiem tra dau ngoac: ";
    for(int i = 0; i < str.length(); i++){
        if(str[i] == '{' || str[i] == '(' || str[i] == '['){
            Push(st, GetNode(str[i]));
        }
        else{
            if(!Empty(st)){
                if( str[i] == ')' && st.top->data == '(' ||
                    str[i] == '}' && st.top->data == '{' ||
                    str[i] == ']' && st.top->data == '['){
                    Pop(st);
                }
                else if(check){
                    cout << "False";
                    check = false;
                }
            }
            else if(check){
                cout << "False";
                check = false;
            }
        }
    }
    if(Empty(st) && check){
        cout << "True";
    }
    else if(check){
        cout << "False";
    }
    
    //Kiem tra palindrome
    cout << endl;
    cout << "Kiem tra palindrome: ";
    for(int i = que.length()-1; i >= 0; i--){
        EnQueue(q, GetNode(que[i]));
    }


    for(int i = 0; i < que.length() - 1; i++){
        if(!Empty_Queue(q)){
            if(que[i] != q.front->data){
                cout << "False";
                return 0;
            }
            DeQueue(q);
        }
    }
    cout << "True";
}