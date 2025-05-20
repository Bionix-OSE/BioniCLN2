#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

class Complex {
private:
    double real;
    double imag;
public:
    // Just like ex1, default constructor
    Complex() : real(0), imag(0) {}

    Complex(double r, double i) : real(r), imag(i) {}

    // =
    Complex& operator=(const Complex &other) {
        if (this != &other) {
            real = other.real;
            imag = other.imag;
        }
        return *this;
    }

    // > (using modulus)
    bool operator>(const Complex &other) const {
        double m1 = std::sqrt(real * real + imag * imag);
        double m2 = std::sqrt(other.real * other.real + other.imag * other.imag);
        return m1 > m2;
    }

    // Final assembly
    double modulus() const {
        return std::sqrt(real * real + imag * imag);
    }

    // Final of final assembly LOL (this one is for printing)
    friend std::ostream& operator<<(std::ostream &os, const Complex &c) {
        os << "(" << c.real << (c.imag >= 0 ? " + " : " - ") << std::abs(c.imag) << "i)";
        return os;
    }
};

int main() {
    int count; // Assume the exercise mean user input? (implementing file IO is okay but meh)
    std::cout << "How many complex numbers are there?: ";
    std::cin >> count;

    std::vector<Complex> numbers;
    std::cout << "Enter the complex numbers in this format - a,b (in a + bi), each pair separated by a space:" << std::endl;
    for (int i = 0; i < count; ++i) {
        double r, im;
        char comma;
        std::cin >> r >> comma >> im;
        numbers.push_back(Complex(r, im));
    }

    // Time to sort.
    std::sort(numbers.begin(), numbers.end(), [](const Complex &a, const Complex &b) {
        return a > b;
    });

    std::cout << "What you just entered, but in decreasing order of modulus:" << std::endl;
    for (const auto &c : numbers) {
        std::cout << c << " |modulus| = " << c.modulus() << std::endl;
    }

    return 0;
}