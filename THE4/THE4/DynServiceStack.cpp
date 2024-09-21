#include <iostream>
#include "DynServiceStack.h"
using namespace std;

//Original document: "DynIntStack.cpp"
//This .cpp file is taken from the CS204 week 5 materials (stack and queues)
//The file slightly modified according to the changes in header file (DynServiceStack.h)

//************************************************
// Constructor to generate an empty stack.       *
//************************************************
DynServiceStack::DynServiceStack() //This part is same with the original document --> Directly taken from CS204 week 5 materials --> (DynIntStack.cpp)
{
	top = NULL; 
}

//************************************************
// Member function push pushes the argument onto *
// the stack.                                    *
//************************************************
void DynServiceStack::push(const string & value) //In original document there is an int value --> modified and added const string reference parameter
{
	StackNode *newNode;

	// Allocate a new node & store Num
	newNode = new StackNode;
	newNode->value = value;

	// If there are no nodes in the list
	// make newNode the first node
	if (isEmpty())
	{
		top = newNode;
		newNode->next = NULL;
	}
	else	// Otherwise, insert NewNode before top
	{
		newNode->next = top;
		top = newNode;
	}
}

//****************************************************
// Member function pop pops the value at the top     *
// of the stack off, and copies it into the variable *
// passed as an argument.                            *
//****************************************************
void DynServiceStack::pop(string &value) //In original document there is an int value --> modified and added string reference parameter
{
	StackNode *temp;

	if (isEmpty())
	{
		cout << "The stack is empty.\n";
	}
	else	// pop value off top of stack
	{
		value = top->value;
		temp = top->next;
		delete top; //deleting top after popping out the value
		top = temp;
	}
}

//****************************************************
// Member funciton isEmpty returns true if the stack *
// is empty, or false otherwise.                     *
//****************************************************
bool DynServiceStack::isEmpty(void) //This part is same with the original document --> Directly taken from CS204 week 5 materials --> (DynIntStack.cpp)
{
	bool status;

	if (top == NULL)
		status = true;
	else
		status = false;

	return status;
}



//****************************************************
// Member funciton clear clears the stack with popping
//all elements out of the stack                      *
//****************************************************

void DynServiceStack::clear(const string & funcName) //This function does not exist in the original document
{
	//pre: a dynamic linked list structure exist
	//post: deletes the dynamic linked list structure for given function name
	string temp;
	string tempStr;
	bool terminate = false;

	while(!isEmpty() && !terminate){
		pop(temp);
		tempStr = temp.substr(0, temp.find(':')); //taking the current function name
		
		if(tempStr != funcName){ //in recursive call if the finished function totally cleared next element will not be popped and the loop will be termianted
			push(temp);
			terminate = true;
		}
	}
}