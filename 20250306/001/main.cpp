#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#include <algorithm>

struct ComplexNumber {
    double real;
    double imag;
    double magnitude;

    ComplexNumber(double r, double i) : real(r), imag(i) {
        magnitude = std::sqrt(r * r + i * i); // sqrt(r^2 + i^2)
    }

    bool operator<(const ComplexNumber& other) const {
        return magnitude > other.magnitude;
    }
};

int main() {
    std::ifstream inputFile("In.txt");
    if (!inputFile) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    int numberOfComplexNumbers;
    inputFile >> numberOfComplexNumbers;

    std::vector<ComplexNumber> complexNumbers;
    for (int i = 0; i < numberOfComplexNumbers; ++i) {
        double real, imag;
        inputFile >> real >> imag;
        complexNumbers.emplace_back(real, imag);
    }

    inputFile.close();

    std::sort(complexNumbers.begin(), complexNumbers.end());

    std::cout << "Top 5 complex numbers with the largest magnitude:" << std::endl;
    for (int i = 0; i < 5 && i < complexNumbers.size(); ++i) {
        std::cout << complexNumbers[i].real << " + " << complexNumbers[i].imag << "i" << std::endl;
    }

    return 0;
}
