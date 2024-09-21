#ifndef CAR_H
	#define CAR_H


#include <iostream>
#include <string>

using namespace std;

class Car{

	private:

		double initialFuel;
		double insuranceFee;
		double totalDistance;

	public:

		//Constructors
		Car::Car(double fuel, double fee, double distance):initialFuel(fuel),insuranceFee(fee), totalDistance(distance){};

		//Member functions
		//Mutators
		void reduceFuel(const double &); //reduces fuel in given amount
		void increaseFuel(const double &); //increases fuel in given amount
		void changeFee(const double &); //changes the fee by given amount
		void increaseDistance(const double &); //increases distance by given amount

		//Accessors
		void display() const;  //display the fuel level, insurance fee and the total distance that the car has travelled so far
		double getCurrentFuel() const; //returns current fuel level of car
		double getCurrentFee() const; //returns current insurance fee of car
		double getCurrentDistance() const; //returns current distance covered by car
};


#endif