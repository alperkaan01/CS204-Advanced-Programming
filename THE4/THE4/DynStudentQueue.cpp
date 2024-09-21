#include <iostream>
#include "DynStudentQueue.h"
#include <string>
using namespace std;

//Original Document: "DynIntQueue.cpp"
//This .cpp file is taken from the CS204 stack and queues materials
//The file is slightly modified and name was changed

//************************************************
// Default Constructor. Generates an empty queue *
//************************************************
DynStudentQueue::DynStudentQueue() //same with original document (only the name changed)
{
	front = NULL;
	rear = NULL;   
	/*#ifdef _DEBUG
		cout << "An empty queue has been created\n";
	#endif*/
}

DynStudentQueue::~DynStudentQueue() //destructor added
{
	this->clear();
	/*#ifdef _DEBUG
		cout << "An empty queue has been created\n";
	#endif*/
}

//********************************************
// Function enqueue inserts the value in num *
// at the rear of the queue.                 *
//parameter modified as student node         *
//********************************************
void DynStudentQueue::enqueue(StudentNode info)
{       
	if (isEmpty())   //if the queue is empty
	{	//make it the first element
		front = new StudentNode(info.serviceName, info.StudName, info.id); //front points to dynamically allocated student node
		rear = front; //rear assigned to front
	}
	else  //if the queue is not empty
	{	//add it after rear
		rear->next = new StudentNode(info.serviceName, info.StudName, info.id); //rear points to new dynamically allocated student node
		rear = rear->next; //rear assigned to rear->next
	} 

	cout << info.StudName << "'s service request of " << info.serviceName << " has been put in the student's queue." << endl; //displaying student node request info
	cout << "Waiting to be served...";
}

//**********************************************
// Function dequeue removes the value at the   *
// front of the queue, and copies it into num. *
//parameter modified as student node           *
//**********************************************
void DynStudentQueue::dequeue(StudentNode &info)
{
	StudentNode *temp; //temporary student node pointer for dequeue operation
	if (isEmpty())
	{
		cout << "Attempting to dequeue on empty queue, exiting program...\n";
		exit(1);
	}
	else //if the queue is not empty
	{	//return front's value, advance front and delete old front
		info.id = front->id; //taking the first elements id and assigning it to dequeued referance parameters' id
		info.serviceName = front->serviceName; //taking the first elements service function and assigning it to dequeued referance parameters' service function
		info.StudName = front->StudName; //taking the first elements student name and assigning it to dequeued referance parameters' student name
		temp = front;
		front = front->next; //assigning front to next node
		delete temp; //deleting previous front
	}
}

//*********************************************
// Function isEmpty returns true if the queue *
// is empty, and false otherwise.             *
// taken from "DynIntQueue.cpp"               *
//*********************************************
bool DynStudentQueue::isEmpty() const
{
	if (front == NULL)
		return true;
	else 
		return false;
}

//********************************************
// Function clear dequeues all the elements  *
// in the queue.                             *
// taken from "DynIntQueue.cpp"              *
//********************************************
void DynStudentQueue::clear()
{
	StudentNode temp;   // Dummy variable for dequeue

	while(!isEmpty())
		dequeue(temp); //delete all elements
	
	front = nullptr;
	rear = nullptr;

	/*#ifdef _DEBUG
		cout << "queue cleared\n";
	#endif*/
}