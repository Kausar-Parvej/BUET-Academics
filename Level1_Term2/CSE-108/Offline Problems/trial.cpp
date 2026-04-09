#include<bits/stdc++.h>

using namespace std;

class Student
{
    char *name;
    int id;
    float credit;
    float cgpa;

public:
    Student();
    Student(string s, int n, float cr, float cg)
    {
        name=(char*) malloc(s.size()*sizeof(char));
        for(int i=0; i<=s.size(); i++)
            name[i]=s[i];

        id=n;
        credit=cr;
        cgpa=cg;
    }

    ~Student()
    {
        free(name);
    }

    void showInfo()
    {
        cout<<"Name: ";
        for(int i=0; i<strlen(name); i++)
            cout<<name[i];
        cout<<", Id: "<<id<<", Credit Completed: "<<credit<<", Cgpa: "<<cgpa<<endl;
    }

    void change(string s2)
    {
        free(name);
        name=(char*) malloc(s2.size()*sizeof(char));
        for(int i=0; i<=s2.size(); i++)
            name[i]=s2[i];

    }

    void change(int n)
    {
        id=n;
    }

    void addTermResult(float cr, float cg)
    {
        cgpa=(cgpa*credit + cg*cr)/(credit+cr);
        credit+=cr;
    }
};

class Batch
{
    Student *students;
    int i;

public:
    Batch()
    {
        students=(Student*) malloc(1200*sizeof(Student));
        i=0;
    }

    ~Batch()
    {
        free(students);
    }

    void addStudent(Student obb)
    {
        students[i]=obb;
        i++;
    }

    void showAllStudents()
    {
        for(int j=0; j<i; j++)
            students[j].showInfo();
    }

};

int main()
{
// Part 1
    /*A student class holds the information of the
    student name, id, credit earned so far, and
    cumulative gpa (cgpa)*/
    /*The name of a student is stored using malloc,
    which will be freed during destruction*/
    Student s1("Tamim Iqbal", 1905131, 39, 3.56);
    Student s2("Liton Das", 1905150, 39, 3.52);
    s1.showInfo();
    cout<<"Changing the name of s1"<<endl;
    /*During changing the name, you should reallocate
    memory of the new name and free the previously
    allocated memory*/
    s1.change("Tamim Iqbal Khan");
    s1.showInfo();
    cout<<"Changing the id of s2"<<endl;
    s2.change(1905149);
    s2.showInfo();
    cout<<"Adding a term result of s1"<<endl;
    /*The first argument of addTermResult is the credit
    earned in a term and second one is the gpa obtained
    in that term*/
    s1.addTermResult(19, 3.85);
    s1.showInfo();
// Part 2
    /*Batch contains a list of students*/
    /*During construction, a Batch object allocates dynamic
    memory for 1200 students using malloc. The memory will
    be freed during destruction*/
    Batch b;
    b.addStudent(s1);
    b.addStudent(s2);
    cout<<"Printing the list of students of the batch b"<<endl;
    b.showAllStudents();

    return 0;
}
