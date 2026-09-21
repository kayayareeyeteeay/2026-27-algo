#include <iostream>
#include "Car.hpp"
#include "Taxi.hpp"
#include "Bus.hpp"
#include "Bike.hpp"
#include "woodpecker.hpp"

TEST("Benzinar", 1){
    CHECK_EQ(250, Car::getCost(1));
    CHECK_EQ(250 * 70, Car::getCost(70));
}

TEST("Car test", 1){
    const std::string type = "BMW";
    const double consumption = 14; 
    const int capacity = 5;
    const int kmh = 10;

    Car bmw(type, consumption, capacity, kmh);

    CHECK_EQ(type, bmw.getType());
    CHECK_EQ(consumption, bmw.getConsumption());
    CHECK_EQ(capacity, bmw.getCapacity());
    CHECK_EQ(250, Car::petrolCost);
    // CHECK_EQ(250, bmw.petrolCost); // Ez mukodik, de ronda

    bmw.refuel(70);
    bmw.moveOn(12);
}

TEST("Taxi test", 1){
    const std::string type = "Audi";
    const double consumption = 11; 
    const int capacity = 4;
    const int kmh = 230;

	Taxi taxi(type, consumption, capacity, kmh);

    CHECK_EQ(type, taxi.getType());
    CHECK_EQ(consumption, taxi.getConsumption());
    CHECK_EQ(capacity, taxi.getCapacity());
    CHECK_EQ(250, Car::petrolCost);

	taxi.refuel(70);
	taxi.carriage(100);
    CHECK_EQ(8250, taxi.getPocket());
    CHECK_EQ(6437.5, taxi.memberCost(100, 4));
    CHECK_EQ(0, taxi.memberCost(100, 10));
}

TEST("Bus test", 1){
    const std::string type = "Man";
    const double consumption = 10; 
    const int capacity = 80;
    const int kmh = 250;

	Bus bus(type, consumption, capacity, kmh);
    
    CHECK_EQ(type, bus.getType());
    CHECK_EQ(consumption, bus.getConsumption());
    CHECK_EQ(capacity, bus.getCapacity());
    CHECK_EQ(250, Car::petrolCost);

	bus.refuel(70);
	bus.carriage(10, 80);

    CHECK_EQ(60000, bus.getPocket());
    CHECK_EQ(77250, bus.profit(10, 80));
    CHECK_EQ(1000, bus.memberCost(10, 80));
}

TEST("Bike test", 1){
    const std::string type = "Mountain Bike";
    Bike mBike(type,0,0);
    CHECK_EQ(type, mBike.getType());
    mBike.moveOn(120);
    CHECK_EQ(120, mBike.getKmh());
}

TEST("No dynamic binding", 1){
    /**
     * ITT NINCS DINAMIKUS KOTES!!!
     */
    std::string type = "Audi";
    double consumption = 11; 
    int capacity = 4;
    int kmh = 230;
	Taxi taxi(type, consumption, capacity, kmh);

	Car ta1 = taxi;
    CHECK_EQ(taxi.cost(11) != ta1.cost(11), true);
}

TEST("Dynamic binding", 1){
    std::string type = "Audi";
    double consumption = 11; 
    int capacity = 4;
    int kmh = 230;
	Taxi taxi(type, consumption, capacity, kmh);

	Car& taxi2 = taxi;
    CHECK_EQ(taxi2.cost(11), taxi.cost(11));
    
    int taxiPetrol = taxi.getPetrol();
    int taxi2Petrol = taxi2.getPetrol();
    CHECK_EQ(taxiPetrol, taxi2Petrol);

	taxi2.refuel(10); // itt a Car::refuel(double) metódus fog lefutni!
	CHECK_EQ(0, taxi.getPocket()); // nem változik a taxi pénze, pedig kéne...
    CHECK_EQ(taxi2Petrol + 10, taxi2.getPetrol());

	Car* a = new Taxi("Mercedes", 11, 2, 400);
	CHECK_EQ(42750, a->cost(100));

	delete a;
}

TEST("Dynamic binding 2", 1){
	Vehicle* vehicles[4];

	vehicles[0] = new Bike("Mountain Bike",0,0);
	vehicles[1] = new Car("BMW", 14, 5, 10);
	vehicles[2] = new Taxi("Audi", 11, 4, 230);
	vehicles[3] = new Bus("Man", 10, 80, 250);

	for (int i = 0; i < 3; i++) {
		vehicles[i]->moveOn(100);
	}

    for(Vehicle* v : vehicles){
        delete v;
    }
}

WOODPECKER_MAIN();
