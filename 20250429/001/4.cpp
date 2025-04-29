#include <iostream>
using namespace std;

// Base classes
class A1 {
public:
    A1() {
        cout << "Constructor of A1" << endl;
    }
};

class A2 {
public:
    A2() {
        cout << "Constructor of A2" << endl;
    }
};

class B1 {
public:
    B1() {
        cout << "Constructor of B1" << endl;
    }
};

class B2 {
public:
    B2() {
        cout << "Constructor of B2" << endl;
    }
};

// Intermediate classes
class C1 : public A1, public A2 {
public:
    C1() {
        cout << "Constructor of C1" << endl;
    }
};

class C2 : public B1, public B2 {
public:
    C2() {
        cout << "Constructor of C2" << endl;
    }
};

// Derived class
class D : public C1, public C2 {
public:
    D() {
        cout << "Constructor of D" << endl;
    }
};

int main() {
    D obj; // Creating an object of class D
    return 0;
}
