#include <iostream>
#include <string>
#include "InstructorQueue.h"
using namespace std;

//Original Document: "IntQueue.cpp"
//This .cpp file is taken from the CS204 stack and queues materials
//The file is slightly modified and name was changed

//*****************************************************
// Default Constructor - creates a queue with size 10 *                                     
// with given number of elements					  *
// This function does not exist in original document  *
// --> it is added									  *
//*****************************************************

InstructorQueue::InstructorQueue()
{
	int s = 10;
	queueArray = new instructorInfo[s];
	queueSize = s;
	front = -1;
	rear = -1;
	numItems = 0;

}

//*****************************************
// Constructor - creates an empty queue   *
// with given number of elements          *
// taken from "IntQueue.cpp"              *
//*****************************************

InstructorQueue::InstructorQueue(int s)
{
	queueArray = new instructorInfo[s];
	queueSize = s;
	front = -1;
	rear = -1;
	numItems = 0;
}


//destructor --> added
InstructorQueue::~InstructorQueue()
{

	delete [] queueArray;
	queueArray = nullptr;
	clear();

}

//********************************************
// Function enqueue inserts the value in num *
// at the rear of the queue.                 *
//parameter modified as instructorInfo node  *
//********************************************

void InstructorQueue::enqueue(instructorInfo info)
{
	if (isFull())
    { 
		cout << "The queue is full. ";// << info.InstructorName << " not enqueued\n";
    }
	else
	{
		// Calculate the new rear position circularly.
		rear = (rear + 1) % queueSize;
		// Insert new item.
		queueArray[rear] = info;
		// Update item count.
		numItems++;
		cout << "Prof. " << info.InstructorName << "'s service request of " << info.ServiceName << " has been put in the instructor's queue." << endl; //displaying instructor request info
		cout << "Waiting to be served...";
	}
}

//**********************************************
// Function dequeue removes the value at the   *
// front of the queue, and copies it into info. *
//parameter modified as instructorInfo node  *
//**********************************************
void InstructorQueue::dequeue(instructorInfo &info)
{
	if (isEmpty())
	{
       cout << "Attempting to dequeue on empty queue, exiting program...\n";
       exit(1);
    }
	else
	{
		// Move front.
		front = (front + 1) % queueSize;
		// Retrieve the front item.
		info = queueArray[front];
		// Update item count.
		numItems--;
	}
}

//*********************************************
// Function isEmpty returns true if the queue *
// is empty, and false otherwise.             *
// taken from "IntQueue.cpp"                  *
//*********************************************
bool InstructorQueue::isEmpty() const
{
	if (numItems > 0)
		return false;
	else
		return true;	
}

//********************************************
// Function isFull returns true if the queue *
// is full, and false otherwise.             *
// taken from "IntQueue.cpp"                 *
//********************************************
bool InstructorQueue::isFull() const
{
	if (numItems < queueSize)
		return false;
	else
		return true;
}

//*******************************************
// Function clear resets the front and rear *
// indices, and sets numItems to 0.         *
// taken from "IntQueue.cpp"                *
//*******************************************
void InstructorQueue::clear()
{
	front =  - 1;
	rear =  - 1;
	numItems = 0;
	/*#ifdef _DEBUG
		cout << "queue cleared\n";
	#endif*/
}