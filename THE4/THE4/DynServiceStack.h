#ifndef DYNSERVICESTACK_H
#define DYNSERVICESTACK_H

//Original Document: "DynIntStack.h"
//This header file is taken from the CS204 stack and queues materials
//The file is slightly modified and name was changed

#include <string>
using namespace std;

struct StackNode
{
	string value; //string variable added instead of int
	StackNode *next; //same pointer with previous document's node "DynServicesStack.h"
};

class DynServiceStack
{
private:
	StackNode *top; //same pointer with previous document's node "DynServicesStack.h"

public:
	
	DynServiceStack(void);
	~DynServiceStack()
	{}; //destructor


	void push(const string &); //const string referance parameter added
	void pop(string &); //string referance parameter added
	bool isEmpty(void);
	void clear(const string &); //New member function for clearing ending functions in processARequest();
};


#endif