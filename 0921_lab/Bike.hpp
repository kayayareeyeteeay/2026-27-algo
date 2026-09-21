#ifndef BIKE_HPP
#define BIKE_HPP

#include "Vehicle.hpp"
#include <iostream>

class Bike : public Vehicle {
    // TODO
public:
    explicit Bike(string type, double kmh, int capacity) : Vehicle(type, kmh, 1) {}




    double moveOn(int km) override {
        return Vehicle::moveOn(km);
    };

};

#endif /*BIKE_HPP*/
