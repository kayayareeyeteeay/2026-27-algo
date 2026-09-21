#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <string>

using namespace std;
class Vehicle {
    // TODO
    protected:
    string type;
    double kmh;
    int capacity;
public:
    Vehicle(string type, double kmh, int capacity) {
        this->type = type;
        this->kmh = kmh;
        this->capacity = capacity;
    }

    string getType() { return type; }
    double getKmh() { return kmh; }
    int getCapacity() { return capacity; }


    virtual double moveOn(int km) {
        this->kmh += km;
        return this->kmh;
    }
};

#endif /*VEHICLE_HPP*/
