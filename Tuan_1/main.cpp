#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

struct Student{
    char studentName[20];
    unsigned int studentID;
    float GPA;
};

Student initStudent(Student &student){
    cout << "Nhap ho ten: ";
    (cin>>ws).getline(student.studentName, sizeof(student.studentName)+1);
    cout << "Nhap ma so sinh vien: ";
    cin >> student.studentID;
    cout << "Nhap diem trung binh: ";
    cin >> student.GPA;
    return student;
}

void initStudentArray(vector<Student> &studentVector){
    int n;
    cout << "Nhap so luong sinh vien: ";
    cin >> n;
    for(int i = 0; i < n; i++){
        Student student = initStudent(student);;
        studentVector.push_back(student);
    }
}

void showSortStudent(vector<Student> &studentVector){
    cout << "--Sap theo GPA--" << endl;
    for(int i = 0; i < studentVector.size(); i++){
        cout << studentVector[i].studentID << " " << studentVector[i].GPA << " " << studentVector[i].studentName << endl;
    }
}

void showReadStudent(vector<Student> &studentVector){
    cout << "--Du lieu doc tu File--" << endl;
    for(int i = 0; i < studentVector.size(); i++){
        cout << studentVector[i].studentID << " " << studentVector[i].GPA << " " << studentVector[i].studentName << endl;
    }
}

void writeMultiStudent(string filename, vector<Student> &studentVector){
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Khong mo duoc file." << endl;
    }

    file << studentVector.size() << endl;
    for(int i = 0; i < studentVector.size(); i++){
        file << studentVector[i].studentID << " ";
        file << studentVector[i].GPA << " ";
        file << studentVector[i].studentName << " ";
        file << endl;
    }
    file.close();
}


void readMultiStudent(string filename, vector<Student> &studentVector){
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Khong mo duoc file." << endl;
    }

    string line;
    getline(file, line);
    while(getline(file, line)){
        stringstream ss(line);
        Student student;
        string field;
        string name;
        getline(ss, field, ' '); 
        student.studentID = stoi(field);
        getline(ss, field, ' '); 
        student.GPA = stof(field);
        getline(ss, field);
        strcpy(student.studentName, field.c_str());
        studentVector.push_back(student);
    }
    file.close();
}

void Swap(Student &a, Student &b){
    Student temp = a;
    a = b;
    b = temp;
}

void InterchangeSort(vector<Student>& studentVector)
{	
	for (int i = 0 ; i<studentVector.size() ; i++)
		for (int j =i+1; j < studentVector.size() ; j++)
		   if(studentVector[j].GPA< studentVector[i].GPA) 
			Swap(studentVector[i], studentVector[j]);
}

Student linearSearch(vector<Student>& studentVector, int x){
    int n = studentVector.size();
    int i = 0;
    studentVector[n].studentID = x;
    while(studentVector[i].studentID != x) i++;
    if(i < n) return studentVector[i];
}

void showFindStudent(vector<Student>& studentVector){
    int id;
    cout << "Nhap ID: ";
    cin >> id;
    Student student = linearSearch(studentVector, id);
    cout << "Sinh vien tim kiem" << endl;
    cout << "Ho ten: " << student.studentName << endl;
    cout << "MSSV: " << student.studentID << endl;
    cout << "GPA: " << student.GPA << endl;
}


int main(){
    vector<Student> student;
    vector<Student> studentGetFromFile;
    initStudentArray(student);
    writeMultiStudent("data.txt", student);
    readMultiStudent("data.txt", studentGetFromFile);
    showReadStudent(studentGetFromFile);
    InterchangeSort(studentGetFromFile);
    showSortStudent(studentGetFromFile);
    showFindStudent(studentGetFromFile);
}

