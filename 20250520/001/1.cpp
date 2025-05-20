#include <iostream>
using namespace std;

class Time {
private:
    int hours;
    int minutes;
    int seconds;

    void toReadable() {
        if (seconds >= 60) {
            minutes += seconds / 60;
            seconds = seconds % 60;
        }
        if (minutes >= 60) {
            hours += minutes / 60;
            minutes = minutes % 60;
        }
        if (hours >= 24) {
            hours = hours % 24;
        }
    }

public:
    // 1a: default constructor
    Time() : hours(0), minutes(0), seconds(0) {}

    // 1b: constructor with parameters
    Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {
        toReadable();
    }

    // 1c: OL plus operator (+)
    Time operator+(const Time& t) const {
        Time result;
        result.seconds = seconds + t.seconds;
        result.minutes = minutes + t.minutes;
        result.hours = hours + t.hours;
        result.toReadable();
        return result;
    }

    // 1d: OL comparison operator (>)
    bool operator>(const Time& t) const {
        int totalSeconds1 = hours * 3600 + minutes * 60 + seconds;
        int totalSeconds2 = t.hours * 3600 + t.minutes * 60 + t.seconds;
        return totalSeconds1 > totalSeconds2;
    }

    // 1e: OL assignment operator (=)
    Time& operator=(const Time& t) {
        if (this != &t) {
            hours = t.hours;
            minutes = t.minutes;
            seconds = t.seconds;
        }
        return *this;
    }

    // Utility to display time in HH:MM:SS format
    void display() const {
        cout << (hours < 10 ? "0" : "") << hours << ":"
             << (minutes < 10 ? "0" : "") << minutes << ":"
             << (seconds < 10 ? "0" : "") << seconds;
    }
};

int main() {
    Time timeDefault;          // 00:00:00
    Time time1(10, 45, 30);    // Not sure if you want arguments here or what?
    Time time2(5, 30, 50);

    // =
    timeDefault = time1;
    cout << "You assigned: ";
    timeDefault.display();
    cout << endl;

    // +
    Time sumTime = time1 + time2;
    cout << "Time1 + Time2 = ";
    sumTime.display();
    cout << endl;

    // >
    if (time1 > time2)
        cout << "Time1 is greater than Time2" << endl;
    else
        cout << "Time1 is less than or equal to Time2" << endl;

    return 0;
}