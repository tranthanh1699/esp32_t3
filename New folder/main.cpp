#include <iostream> 
using namespace std; 

class Persion
{
private:
    string name; 
    int age; 
    int id; 
public:
    Persion(string name, int age, int id)
    {
        this->name = name; 
        this->age = age; 
        this->id = id; 
    }
    ~Persion()
    {

    }
    virtual void display_name()
    {
        cout << "Persion name: " << name << endl; 
    }
    
    virtual void display_age() 
    {
        cout << "Persion Age: " << age << endl; 
    }
    
    virtual void display_id()
    {
        cout << "Persion ID: " << id << endl; 
    }

};

class Student : public Persion
{
private:    
    string name; 
    int age; 
    int id; 
public:
    Student(string name, int age, int id)
    {
        this->name = name; 
        this->age = age; 
        this->id = id; 
    }
    ~Student()
    {

    }
    void display_name()
    {
        cout << "Student name: " << name << endl; 
    }
    
    void display_age() 
    {
        cout << "Student Age: " << age << endl; 
    }
    
    void display_id()
    {
        cout << "Student ID: " << id << endl; 
    }
};

int main()
{
    cout << "Hello" << endl; 
    Persion * p = new Persion("Thanh", 22, 11223344); 
    p->display_name(); 
    p->display_age(); 
    p->display_id(); 

    // Student thanh("Thanh", 2323, 243021423); 

    // p = &thanh; 

    // p->display_name(); 
    // p->display_age(); 
    // p->display_id(); 
    return 0; 
}