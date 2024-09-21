#include <iostream>
#include <string>
#include "Car.h"

using namespace std;


void Car::reduceFuel(const double &amount) //reduces initial fuel with the given amount
{
	initialFuel -= amount;
}



void Car::increaseFuel(const double &amount) //increases initial fuel with the given amount
{
	initialFuel += amount;
}



void Car::changeFee(const double &amount) //changes fee according to the accidents that drivers encounter
{
	insuranceFee += (insuranceFee * ((amount) / 100));
}



void Car::increaseDistance(const double &amount) //increases distance with given amount
{
	totalDistance += amount;
}


double Car::getCurrentFuel() const //returns fuel level of car
{
	return initialFuel;
}

double Car::getCurrentFee() const //returns insurance fee of car
{
	return insuranceFee;
}

double Car::getCurrentDistance() const //returns distance covered by car
{
	return totalDistance;
}

//display the fuel level, insurance fee and the total distance that the car has travelled so far
void Car::display() const
{
	cout << "Fuel Level: " << initialFuel << endl;
	cout << "Insurance Fee: " << insuranceFee << endl;
	cout << "Total distance that the car has travelled: " << totalDistance << endl;
}