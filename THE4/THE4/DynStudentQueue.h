#ifndef DYNSTUDENTQUEUE_H
#define DYNSTUDENTQUEUE_H

//Original Document: "DynIntQueue.h"
//This header file is taken from the CS204 stack and queues materials
//The file is slightly modified and name was changed

#include <string>
using namespace std;

struct StudentNode
{
	//a node for storing student request information
	string serviceName, StudName;
	int id;
	StudentNode *next;

	StudentNode::StudentNode(){} //default constructor

	StudentNode::StudentNode(string name, string studName , int num, StudentNode *ptr = NULL) //constructor
	{
		serviceName = name;
		StudName = studName;
		id = num;
		next = ptr;
	}
};

class DynStudentQueue
{
private:
	// These track the front and rear of the queue.
	StudentNode *front; //modified --> student node pointers are used
	StudentNode *rear;	//modified --> student node pointers are used
public:
	// Constructor.
	DynStudentQueue();
	~DynStudentQueue(); //destructor
	
	// Member functions.
	void enqueue(StudentNode); //modified --> parameter converted into student node
	void dequeue(StudentNode &); //modified --> parameter converted into student node parameter
	bool isEmpty() const;     
	void clear();
};
#endif