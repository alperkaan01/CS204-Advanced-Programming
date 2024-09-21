#include <iostream>
#include <string>
#include "Driver.h"
#include "Car.h"

using namespace std;

//takes the kilometer(km) that the driver has driven 
//--> increase the total distance that the car has travelled by this km 
//--> reduce the fuel level of the car (0.25 dollar per km).
void Driver::drive (int km)
{
	car.increaseDistance(km);
	car.reduceFuel(km * 0.25);
}


//Accident types 
//--> SMALL (-50 dollar from budget/ +5% insurance fee)
//-MEDIUM (-150 dollar from budget/ +10% insurance fee)
//-LARGE (-300 dollar from budget / +20% insurance fee)

void Driver::repairCar(string accident)
{
	double amount;

	if(accident == "SMALL"){
		amount = 50;
		Budget -= amount;
		car.changeFee(5);
	}else if(accident == "MEDIUM"){
		amount = 150;
		Budget -= amount;
		car.changeFee(10);
	}else{ //accident == LARGE
		amount = 300;
		Budget -= amount;
		car.changeFee(20);
	}

	cout << amount << "$ is reduced from the driver's budget because of the " << accident << " accident" << endl
		<< "Yearly insurance fee is increased to " << car.getCurrentFee() << " because of the " << accident << " accident" << endl;
}


//displays current budget of the driver

void Driver::display() const
{
	cout << "Driver Budget: " << Budget << endl;
}



//full the fuel of the car to its maximum level (300$)
//budget - dollar that driver spend for full-filling

void Driver::fullFuel()
{
	double amount = 300 - car.getCurrentFuel();
	
	car.increaseFuel(amount);
	Budget -= amount;

	cout << endl << "Fuel is full" << endl << endl;

}