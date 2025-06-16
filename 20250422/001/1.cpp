#include <iostream>
using namespace std;

class Mother {
public:
	void display() {
		cout << "Hi I'm the mother." << endl;
	}
};

class Daughter : public Mother {
public:
	void display() {
		cout << "And I'm her daughter." << endl;
	}
};

int main() {
	Daughter dt;
	dt.display(); // Calls the overridden display() method from the Daughter class
	return 0;
}
