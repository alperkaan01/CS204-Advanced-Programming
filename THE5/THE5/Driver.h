#ifndef DRIVER_H
#define DRIVER_H

#include <iostream>
#include <string>
#include "Car.h"

using namespace std;

class Driver{

	private:

		Car & car; //object sharing by reference
		double Budget;

	public:
		
		//Constructor
		Driver::Driver(Car & sharedCar, const double& budget):car(sharedCar), Budget(budget){};
		
		//Member function
		void drive (int); //takes the kilometer(km) that the driver has driven --> increase the total distance that the car has travelled by this km --> reduce the fuel level of the car (0.25 dollar per km).
		void repairCar(string); //Accident types --> SMALL (-50 dollar from budget/ +5% insurance fee)-MEDIUM (-150 dollar from budget/ +10% insurance fee)-LARGE (-300 dollar from budget / +20% insurance fee)
		void display() const; //displays current budget of the driver
		void fullFuel(); //full the fuel of the car to its maximum level (300$) / budget - dollar that driver spend for full-filling

};


#endif