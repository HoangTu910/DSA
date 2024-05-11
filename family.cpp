#include <iostream>
#include <string>
#include <queue>

using namespace std;

struct node{
	string name;
	int age;
	node* first_child;
	node* next_sibling;

	node(const string& _name, const int& _age) : name(_name), age(_age), first_child(NULL), next_sibling(NULL){} 
};

node* add_child(node* root, const string& name, const int& age){
	node* new_child = new node(name, age);
	if(root->first_child == NULL){
		root->first_child = new_child;
	}
	else{
		node* sibling = root->first_child;
		while(sibling->next_sibling != NULL){
			sibling = sibling->next_sibling;
		}
		sibling->next_sibling = new_child;
	}
	return new_child;
}

void traverse(node* root){
	if(root == NULL){
		return;
	}
	queue<node*> q;
	q.push(root);
	bool skip_parent = true;
	while(!q.empty()){
		int level_size = q.size();
		for(int i = 0; i < level_size; i++){
			node* current = q.front();
			q.pop();
			if(!skip_parent){
				cout << " + " << current->name << " - Tuoi: " << current->age << endl;
			}
			skip_parent = false;
			node* child = current->first_child;
			while(child != nullptr){
				q.push(child);
				child = child->next_sibling;
			}
		}
	}
	cout << endl;
}

node* search(node* root, const string& target){
	if(root == NULL){
		return NULL;
	}
	queue<node*> q;
	q.push(root);
	while(!q.empty()){
		int level_size = q.size();
		for(int i = 0; i < level_size; i++){
			node* current = q.front();
			q.pop();
			if(current->name == target){
				return current;
			}
			node* child = current->first_child;
			while(child != nullptr){
				q.push(child);
				child = child->next_sibling;
			}
		}
	}
	cout << endl;
	return NULL;
}

void add_member_func(node* root){
	string member_name;
	int member_age;
	if(root != NULL){
		cout << "Nhap ten thanh vien: ";
		getline(cin>>ws, member_name);
		cout << "Nhap tuoi thanh vien: ";
		cin >> member_age;
		add_child(root, member_name, member_age);
		return;
	}
	cout << "Khong tim thay root !" << endl;
	return;
}

void add_child_func(node* root){
	string parent_name;
	string child_name;
	int child_age;
	cout << "Nhap ten cha: ";
	getline(cin>>ws, parent_name);
	node* p = search(root, parent_name);
	if(p != NULL){
		cout << "Nhap ten con: ";
		getline(cin>>ws, child_name);
		cout << "Nhap tuoi con: ";
		cin >> child_age;
		add_child(p, child_name, child_age);
		return;
	}
	cout << "Khong tim thay cha !" << endl;
	return;
}

node* find_member(node* root){
	string member_name;
	cout << "Nhap ten thanh vien: ";
	getline(cin>>ws, member_name);
	node* p = search(root, member_name);
	if(p != NULL){
		cout << "Cha/Me: ";
		cout << p->name << " " << p->age << endl;
		cout << "Cac dua con/chau cua " << p->name << ": " << endl;
		traverse(p);
		return p;
	}
	cout << "Khong tim thay thanh vien !";
	return NULL;
}

node* findParent(node* root, const string& child_name) {
    if (root == nullptr || root->first_child == nullptr) {
        return nullptr;
    }
    
    queue<node*> q;
    q.push(root);
    
    while (!q.empty()) {
        int levelSize = q.size();
        
        for (int i = 0; i < levelSize; ++i) {
            node* current = q.front();
            q.pop();
            
            node* child = current->first_child;
            while (child != nullptr) {
                if (child->name == child_name) {
                    return current; 
                }
                q.push(child);
                child = child->next_sibling;
            }
        }
    }
    
    return nullptr;
}


void find_sibling(node* root, node* target){
    if (root == nullptr || target == nullptr)
        return;

    queue<node*> q;
    q.push(root);
    bool found = false;

    while (!q.empty() && !found) {
        int levelSize = q.size();

        for (int i = 0; i < levelSize; ++i) {
            node* current = q.front();
            q.pop();

            if (current->name == target->name) {
                found = true;
                break;
            }

            node* child = current->first_child;
            while (child != nullptr) {
                q.push(child);
                child = child->next_sibling;
            }
        }
    }

    if (!found) {
        cout << "Khong tim thay thanh vien!" << endl;
        return;
    }

    node* parent = nullptr;
    if (target == root) {
        cout << "Khong co anh chi em cho " << target->name << endl;
        return;
    } else {
        parent = findParent(root, target->name);
    }

    node* sibling = parent->first_child;
    while (sibling != nullptr) {
        if (sibling->name != target->name) {
            cout << " + " << sibling->name << " - Tuoi: " << sibling->age << endl;
        }
        sibling = sibling->next_sibling;
    }
    cout << endl;
}


int main(){
	node* root = new node("Ong to", 1000);
	char choice;
	do {
        cout << "Menu:" << endl;
        cout << "1. Them thanh vien" << endl;
        cout << "2. Them con" << endl;
        cout << "3. In thong tin thanh vien va cac con" << endl;
        cout << "0. Thoat" << endl;
        cout << "Chon chuc nang: ";
        cin >> choice;

        switch (choice) {
            case '1': {
            	cout << "Them thanh vien vao pha he: " << endl;
                add_member_func(root);
                break;
            }
            case '2': {
            	cout << "Them con vao thanh vien: " << endl;
                add_child_func(root);
                break;
            }
            case '3': {
            	cout << "Tim thanh vien: " << endl;
                node* find = find_member(root);
				cout << "Cac anh chi em cua "<< find->name << ": " << endl;
                find_sibling(root, find);
                break;
            }
            case '0':
                break;
            default:
                cout << "Lua chon khong hop le, vui long chon lai." << endl;
        }
    } while (choice != '0');

}
