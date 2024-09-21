#ifndef INSTRUCTORQUEUE_H
#define INSTRUCTORQUEUE_H

//Original Document: "IntQueue.h"
//This header file is taken from the CS204 stack and queues materials
//The file is slightly modified and name was changed

#include <string>
using namespace std;

struct instructorInfo{ 
	//modified node for storing given service and instructor information
	
	string ServiceName;
	string InstructorName;
	int id;

	instructorInfo::instructorInfo() //Default constructor
	{}

	instructorInfo::instructorInfo(string sName, string iName, int iId) //constructor
	{
		ServiceName = sName;
		InstructorName = iName;
		id = iId;
	}
};

class InstructorQueue
{
private:
	instructorInfo *queueArray; //modified, instead of integer queue instructor node queue is used
	int queueSize;  //capacity of queue
	int front;
	int rear;
	int numItems;  //# of elements currently in the queue
public:
	
	
	InstructorQueue(); //default constructor --> added
	InstructorQueue(int);  //constructor, parameter is capacity
  	~InstructorQueue(); //destructor
	
	void enqueue(instructorInfo);   //enqueues the given instructorInfo node --> modified --> in original document it takes an integer parameter
  	void dequeue(instructorInfo &); //dequeues the given instructorInfo node as a referance --> modified --> in original document it takes an integer parameter
  	bool isEmpty() const; //same with the original document
  	bool isFull() const; //same with the original document
  	void clear();  //removes all elements --> same with original document
};
#endif