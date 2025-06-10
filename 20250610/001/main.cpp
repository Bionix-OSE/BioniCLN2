#include <bits/stdc++.h>
using namespace std; 
// Reference: https://www.geeksforgeeks.org/farey-sequence/

class Fraction {
public:
    int x, y;

    // Constructor to initialize x and y in x/y
    Fraction(int x, int y)
        : x(x), y(y)
    {
    }
};

void Farey(int N) {
    vector<Fraction> sq;
    sq.push_back(Fraction(0, 1));
    sq.push_back(Fraction(1, 1));

    for (int i = 2; i <= N; ++i) {
        for (int j = 1; j < i; ++j) {
            if (__gcd(i, j) == 1) {
                sq.push_back(Fraction(j, i));
            }
        }
    }

    sort(sq.begin(), sq.end(), [](const Fraction& a, const Fraction& b) {
        return a.x * b.y < b.x * a.y;
    });

    for (const auto& frac : sq) {
        cout << frac.x << "/" << frac.y << " ";
    }
}

int main() {
    int N;
    cout << "Enter the degree of the Farey sequence you want to check: ";
    cin >> N;

    Farey(N);
    cout << endl;

    return 0;
}

// ~.~