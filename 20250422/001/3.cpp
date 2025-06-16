#include <iostream>
#include <string>
using namespace std;

class Student {
protected:
	string name;
	int age;
	string major;
	int myear;
	
public:
	void set_value(string n, int a, string m, int my) {
		name = n;
		age = a;
		major = m;
		myear = my;
	}
	
	void display() {
		cout << "Name: " << name << "\nAge: " << age << "\Major: " << major << "\nYear of major: " << myear << endl;
	}
};
