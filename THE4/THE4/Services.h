#ifndef SERVICES_H
	#define SERVICES_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "InstructorQueue.h"
#include "DynStudentQueue.h"
#include "DynServiceStack.h"

using namespace std;

struct commandNode{ 
	//a command node struct
	string command;
	commandNode *next; //pointer for next command nodes

	commandNode::commandNode() 
	{
		//default constructor
		next = nullptr;
	}

	commandNode::commandNode(string info){ 
	//constructor
		command = info;
		next = nullptr;
	}
};

struct functionNode{ 
	//a function node struct --> function_1, function_2, function_3 ...
	string name;
	functionNode *next; //pointer for next function node
	commandNode* commandNodes; //pointer for next command node
	
	
	functionNode::functionNode(){ 
		//default constructor for functionNode
		next = nullptr;
		commandNodes = nullptr;
	}

	functionNode::functionNode(string info){
		//constructor
		name = info;
		next = nullptr;
		commandNodes = nullptr;
	}
};


class Services {
	
	private:
		functionNode *servicesHead; //a head for linked list structure (services list)
		functionNode *tailFuncNode; //tail for function node assingment operation --> input file reading
		commandNode *tailCommandNode; //tail for the command assignment operation --> input file reading
		InstructorQueue instructorQueue; //a queue for holding instructor request 
		DynStudentQueue studQueue; //a queue for holding student request 
		DynServiceStack commonStack; //a common stack for holding service informations
	public:
		
		Services(); //default constructor
		~Services(); //destructor


		//Mutators
		void addInputFile(const string &); //processing input files and adding service info to linked list
		void addInstructorRequest(); //add instructor request to instructor queue
		void addStudentRequest(); //add student request to students queue
		void processARequest(string); //process a request (recursively)
		void processARequest(); //another process a request calling the previous function with proper service function
		
		
		//Accessors
		functionNode * getServiceHead() const; // returning private servicesHead
		void printInput() const; // prints the linked list structure
		bool isFuncExist(const string &) const; // look whether a service func exist in linked list or not

};

#endif