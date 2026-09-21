#ifndef CAR_HPP
#define CAR_HPP

#include "Vehicle.hpp"
#include <iostream>
#include <string>

class Car : public Vehicle {
    // TODO
private:
    double consumption;
    double petrol;





public:
    static int petrolCost;
    static int getCost(double litre) {
        return litre*petrolCost;
    }
    explicit Car(string type, double kmh, int capacity, int consumption) : Vehicle(type, kmh, capacity) {};
    virtual void refuel(double litre) {
        petrol+=litre;
    };
    virtual double cost(double km) const {
        return (km/100.00)*consumption*petrolCost;
    };
    double moveOn(int km);
    double getConsumption() { return consumption; }
    double getPetrol() { return petrol; }

};

    // TODO

#endif /*CAR_HPP*/
