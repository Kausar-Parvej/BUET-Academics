#include<iostream>
#include<cstring>
#include<string.h>

using namespace std;


class Student
{
    char *name;
    int id;
    float credit;
    float cgpa;

public:
    Student(char ch1[], int num, float cred, float cgp)
    {
        name=(char*) malloc((strlen(ch1)+1)*sizeof(char));
        strcpy(name,ch1);

        id=num;
        credit=cred;
        cgpa=cgp;
    }

    Student(const Student &ob)
    {
        name=(char*) malloc((strlen(ob.name)+1)*sizeof(char));
        strcpy(name,ob.name);

        id=ob.id;
        credit=ob.credit;
        cgpa=ob.cgpa;
    }

    ~Student()
    {
        free(name);
    }

    void showInfo()
    {
        cout<<"Name: "<<name<<", Id: "<<id<<", Credit Completed: "<<credit<<", Cgpa: "<<cgpa<<endl;
    }

    void change(char ch2[])
    {
        free(name);
        name=(char*) malloc((strlen(ch2)+1)*sizeof(char));
        strcpy(name,ch2);

    }

    void change(int num)
    {
        id=num;
    }

    void addTermResult(float cred, float cgp)
    {
        cgpa=(cgpa*credit + cgp*cred)/(credit+cred);
        credit+=cred;
    }
};

class Batch
{
    Student *stu;
    int k;

public:
    Batch()
    {
        stu=(Student*) malloc(1200*sizeof(Student));
        k=0;
    }

    ~Batch()
    {
        free(stu);
    }

    void addStudent(Student &obb)
    {
        stu[k]=obb;
        k++;
    }

    void showAllStudents()
    {
        for(int j=0; j<k; j++)
            stu[j].showInfo();
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
