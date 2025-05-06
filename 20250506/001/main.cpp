#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

class Shape {
public:
    virtual std::string info() = 0; // The execrise didn't ask for this, just for debugging ig
    virtual float computeArea() = 0;
};

class Triangle : public Shape {
private:
    float x1, y1, x2, y2, x3, y3;

public:
    Triangle(float x1, float y1, float x2, float y2, float x3, float y3) : x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3) {}
    std::string info() override {
        std::ostringstream i;
        i << x1 << " " <<  y1 << " " << x2 << " " << y2 << " " << x3 << " " << y3;
        return i.str();
    }
    float computeArea() override {
        return 0.5f * std::abs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
    }
};

class Rectangle : public Shape {
private:
    float x1, y1, x2, y2;

public:
    Rectangle(float x1, float y1, float x2, float y2): x1(x1), y1(y1), x2(x2), y2(y2) {}
    std::string info() override {
        std::ostringstream i;
        i << x1 << " " <<  y1 << " " << x2 << " " << y2;
        return i.str();
    }
    float computeArea() override {
        return std::abs(x2 - x1) * std::abs(y2 - y1);
    }
};

class Square : public Shape {
private:
    float x1, y1, x2, y2;

public:
    Square(float x1, float y1, float x2, float y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
    std::string info() override {
        std::ostringstream i;
        i << x1 << " " <<  y1 << " " << x2 << " " << y2;
        return i.str();
    }
    float computeArea() override {
        float side = std::abs(x2 - x1);
        return side * side;
    }
};

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }
    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    std::ifstream inFile(inputFile);
    if (!inFile) {
        std::cerr << "E: Could not open " << inputFile << std::endl;
        return 1;
    }
    std::ofstream outFile(outputFile);
    if (!outFile) {
        std::cerr << "E: Could not write to " << outputFile << std::endl;
        return 1;
    }

    int numShapes;
    inFile >> numShapes;
    std::vector<std::pair<Shape *, float>> shapes;

    for (int i = 0; i < numShapes; ++i) {
        char type;
        inFile >> type;

        if (type == 't') {
            float x1, y1, x2, y2, x3, y3;
            inFile >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
            Shape *triangle = new Triangle(x1, y1, x2, y2, x3, y3);
            shapes.emplace_back(triangle, triangle->computeArea());
        } else if (type == 'r') {
            float x1, y1, x2, y2;
            inFile >> x1 >> y1 >> x2 >> y2;
            Shape *rectangle = new Rectangle(x1, y1, x2, y2);
            shapes.emplace_back(rectangle, rectangle->computeArea());
        } else if (type == 's') {
            float x1, y1, x2, y2;
            inFile >> x1 >> y1 >> x2 >> y2;
            Shape *square = new Square(x1, y1, x2, y2);
            shapes.emplace_back(square, square->computeArea());
        }
    }

    std::sort(shapes.begin(), shapes.end(), [](const auto &a, const auto &b) {
        return a.second > b.second;
    });

    outFile << shapes.size() << std::endl;
    for (const auto &shapePair : shapes) {
        Shape *shape = shapePair.first;
        float area = shapePair.second;

        if (dynamic_cast<Triangle *>(shape)) {
            Triangle *triangle = dynamic_cast<Triangle *>(shape);
            outFile << "t " << triangle->info() << " -> " << area << std::endl;
        } else if (dynamic_cast<Rectangle *>(shape)) {
            Rectangle *rectangle = dynamic_cast<Rectangle *>(shape);
            outFile << "r " << rectangle->info() << " -> " << area << std::endl;
        } else if (dynamic_cast<Square *>(shape)) {
            Square *square = dynamic_cast<Square *>(shape);
            outFile << "s " << square->info() << " -> " << area << std::endl;
        }
    }

    // Clean up
    for (auto &shapePair : shapes) {
        delete shapePair.first;
    }

    return 0;
}
