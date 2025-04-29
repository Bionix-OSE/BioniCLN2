#include <iostream>
using namespace std;

// Base class
class Shape {
public:
    virtual void display() {};
};

// The shapes
class Rectangle : public Shape {
public:
    void display() override {
        cout << "This is a rectangle." << endl;
    }
};
class Triangle : public Shape {
public:
    void display() override {
        cout << "This is a triangle." << endl;
    }
};

int main() {
    // Instantiate objects
    Shape s;
    Rectangle rec;
    Triangle tri;

    // Call display methods
    s.display();
    rec.display();
    tri.display();

    return 0;
}