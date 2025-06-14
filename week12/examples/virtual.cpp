#include <iostream>
#include <string>
using namespace std;

class Person
{
  public:
    string name;
    Person(string n): name(n){}
    void print()
    {
        cout << "Name: " << name << endl;
    }
};

class Person2
{
  public:
    string name;
    Person2(string n): name(n){}
    virtual void print() = 0; 
    //virtual function equal to 0 means it is a pure virtual function
    //A class with at least one pure virtual function is called an abstract class
    //A class with no pure virtual function is called a concrete class
};

class Student: public Person
{
  public:
    string id;
    Student(string n, string i): Person(n), id(i){}
    void print() 
    {
        cout << "Name: " << name;
        cout << ". ID: " << id << endl;
    }
};

/****
 * This function is determined for all objects printed
 * ***/
void printObjectInfo(Person & p)
{
    //It call the print by the base class.
    //if print() is not a virtual function, 
    //different output if its destructor is not virtual
    p.print();
}

int main()
{
    {
        Student stu("yu", "2019");
        printObjectInfo(stu);  
    }

    {
        Person * p = new Student("xue", "2020");
        p->print(); //if print() is not a virtual function, different output
        delete p; //if its destructor is not virtual
    }

    // { //if you want to call a function in the base class
    //     Student stu("li", "2021");
    //     stu.Person::print();

    //     Person * p = new Student("xue", "2020");
    //     p->Person::print(); 
    //     delete p; 
    // }

    return 0;
}