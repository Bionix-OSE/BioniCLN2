#include <iostream>
#include <string>
using namespace std;

class Animal {
protected:
	string name;
	int age;

public:
	void set_value(string n, int a) {
		name = n;
		age = a;
	}
	
	void display() {
		cout << "Name: " << name << "\nAge: " << age << " years" << endl;
	}
};

class Zebra : public Animal {
public:
	void display() {
		Animal::display();
		cout << "Origin: Native to Africa." << endl;
	}
};

class Dolphin : public Animal {
public:
	void display() {
		Animal::display();
		cout << "Origin: Commonly found in oceans worldwide." << endl;
	}
};

int main() {
	Zebra z;
	Dolphin d;
	
	z.set_value("Marty", 5);
	d.set_value("Flipper", 8);
	
	cout << "Zebra:" << endl;
	z.display();
	cout << "\nDolphin:" << endl;
	d.display();
	
	return 0;
}
