#ifndef TAXI_HPP
#define TAXI_HPP

#include "Car.hpp"
#include <string>

class Taxi : public Car {
    // TODO

private:
    double pocket;
    double kmhCost;

public:
    explicit Taxi(string type, double kmh, int capacity, double consumption) : Car(type,kmh, capacity, consumption) {};
    virtual double cost(double km);
    virtual void refuel(double litre);
    double carriage(double km);
    double memberCost(double km, double member);
    double getKmCost();
    double getPocket();

};

#endif /*TAXI_HPP*/
