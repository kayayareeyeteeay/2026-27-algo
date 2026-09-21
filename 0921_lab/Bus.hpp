#ifndef BUS_HPP
#define BUS_HPP

#include "Taxi.hpp"
#include <string>

class Bus : public Taxi {
    // TODO
public:
    static int ticketCost();
    explicit Bus(string type, int capacity, int kmCost, int consumption) : Taxi(type, capacity, kmCost, consumption) {};
    double carriage(int km);
    double carriage(int km, int member);
    double memberCost(int km, int member);
    double profit(int km, int member);
};

    // TODO

#endif /*BUS_HPP*/
