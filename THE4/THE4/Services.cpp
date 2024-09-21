#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Services.h"
#include "InstructorQueue.h"
#include "DynStudentQueue.h" 

using namespace std;
extern bool GLOBAL_TERMINATE; //taking global terminate variable from main.cpp


Services::Services()
{
	//Default constructor initializes some of the private variables
	servicesHead = nullptr;
	tailFuncNode = nullptr;
	tailCommandNode = nullptr;

}

functionNode * Services::getServiceHead() const{
	return servicesHead; //returns the head of the given list--> This is an accessor function since it does not change the feature of object
}

Services::~Services(){ 
	//Destructor
	//pre: there is an object from this class exist
	//post: the linked list information of this object is cleared
	//memory leakage is prevented
	functionNode *funcIterator = nullptr;
	if(servicesHead != NULL){
		funcIterator = servicesHead; //temporary head for deletion
		while(funcIterator != NULL){
			commandNode *commandIterator = funcIterator->commandNodes; //temporary iterator for command nodes
			while(commandIterator != NULL){
				commandNode *temp = commandIterator; //temporary iterator for temporary command iterators
				commandIterator = commandIterator->next;
				delete temp; //deleting the temp
			}
			servicesHead = servicesHead->next;
			delete funcIterator; //deleting previous head
			funcIterator = servicesHead;
		}
	}

	servicesHead = nullptr;
	tailFuncNode = nullptr;
	tailCommandNode = nullptr;
	instructorQueue.~InstructorQueue();
	studQueue.~DynStudentQueue();
	commonStack.~DynServiceStack();
}

void Services::addInputFile(const string &fileName)
{
	//(member function) for adding input files coming from user
	//pre: a filename given by user in main.cpp
	//post: if the file exists open the file and process data to add it in linked list structure in a given format
	ifstream file;
	file.open(fileName.c_str()); //opeining file with ifstream

	if(file.fail()){
		cout << "The file cannot be opened..." << endl;
		GLOBAL_TERMINATE = false; //if file cannot be opened terminate loop in main and return 0;
	}else{
		string line;
		bool terminate = false;
		while(getline(file, line)){ //reading file line by line
			if(line.at(line.length()-1) == ':'){ //looking whether it is a function or command
				line = line.substr(0, line.length()-1); //taking the function name by cutting the whole line
				if(servicesHead == NULL){
					functionNode *temp = new functionNode(line); //creating new function node with given line name
					servicesHead = temp;
					tailFuncNode = servicesHead; //tail is assigned to first element due to the first iteration 
				}else{
					tailFuncNode->next = new functionNode(line); //adding new func node to tail
					tailFuncNode = tailFuncNode->next; //carrying tail to newly assigned node
				}
			}else{ //if its a command
				line = line.substr(0, line.length()-1); //taking the command name by cutting whole line
				if(tailFuncNode->commandNodes == NULL){
					tailFuncNode->commandNodes = new commandNode(line); //adding first command node
					tailCommandNode = tailFuncNode->commandNodes;
				}else{
					tailCommandNode->next = new commandNode(line); //adding newly added command nodes to tail of commands
					tailCommandNode = tailCommandNode->next;
				}
			}
		}
	}
}

void Services::printInput() const{

	//Member function for printing the info of linked list (existing services)
	//pre: a linked list exist
	//post: displaying the information in the right format

	functionNode *funcIterator = servicesHead; //temporary iterator = private head

	while(funcIterator != nullptr){
		cout << funcIterator->name << ": " << endl;
		commandNode *commandIterator = funcIterator->commandNodes; //temporary iterator for command lines
		while(commandIterator != nullptr){
			cout << commandIterator->command; //printing current line's command information
			if(commandIterator->next != NULL){
				cout << ", ";
			}
			if(commandIterator->next == NULL){
				cout << ".";
			}
			commandIterator = commandIterator->next; //jumping to the next command node
		}
		cout << endl;
		funcIterator = funcIterator->next; //jumping to the next function node
	}
}

bool Services::isFuncExist(const string &funcName) const{
	//boolean member function for understanding whether given service exist in the list
	//pre: a service linked list exist
	//post: returns true if given function name exist in function nodes, otherwise return false
	functionNode *tempNode = servicesHead; // temp iterator for iterating over function nodes
	while(tempNode != NULL && tempNode->name != funcName){
		tempNode = tempNode->next; //looking for whether given function name exist in the function nodes
	}
	if(tempNode == NULL){ //if temporary iterator pointing to the end of the list the function cannot be found
		return false;
	}
	return true; //return true if the temp iterator stop at some point in between the head and nullptr
}

void Services::addInstructorRequest(){
	//member function for adding instructor requests to instructor queue
	//pre: there is a default instructor queue exist
	//post: adding given instructor info to the queue for processing
	string serviceFunc;
	cout << "Add a service (function) that the instructor wants to use: " << endl;
	cin >> serviceFunc;
	if(!isFuncExist(serviceFunc)){ //Looking whether the given service exist
		cout << "The requested service (function) does not exist." << endl;
		cout << "GOING BACK TO MAIN MENU" << endl;
	}else{
		string instructorName;
		int id;

		cout << "Give instructor's name: ";
		cin >> instructorName;
		cout << "Give instructor's ID (an int): ";
		cin >> id;
		instructorInfo info(serviceFunc, instructorName, id); //creating instructor info node --> a struct in InstructorQueue.h file
		instructorQueue.enqueue(info); //adding that info node to the instructor's queue
	}
}

void Services::addStudentRequest(){
	//member function for adding student requests to dynamic students' queue
	//pre: there is a default students' queue exist
	//post: adding given student info to the queue for processing
	string serviceFunc;
	cout << "Add a service (function) that the student wants to use: " << endl;
	cin >> serviceFunc;
	if(!isFuncExist(serviceFunc)){ //Looking whether given service exist
		cout << "The requested service (function) does not exist." << endl;
		cout << "GOING BACK TO MAIN MENU" << endl;
	}else{

		string studName;
		int studId;

		cout << "Give student's name: ";
		cin >> studName;
		cout << "Give student's ID (an int): ";
		cin >> studId;
		StudentNode info(serviceFunc, studName, studId); //creating student node with the struct structure generated in DynStudentQueue.h file
		studQueue.enqueue(info); //adding the student information to student's queue
	}
}

void Services::processARequest(string functionName)
{
	//A recursive function for processing requests in proper format (define, call, print)
	//pre: a function name given from another processARequest function
	//post: add the given information to common stack properly (according to the commands of define, call or print)
	//if the command is print than the stack is printed reversely without changing its' original information

	DynServiceStack temp; //temporary stack for preserving stack info while print option occurs
	functionNode *funcIterator = servicesHead;

	while(funcIterator != NULL && funcIterator->name != functionName){
		funcIterator = funcIterator->next; //iterate over function nodes up to the given function name
	}
	commandNode *commandIterator = funcIterator->commandNodes;


	while (commandIterator != NULL) //iterate on commands
	{
		//…
		string currentCommand, commandInfo;
		int indx = commandIterator->command.find(' ');
		currentCommand = commandIterator->command.substr(0, indx); //taking the command define, call or print
		commandInfo = commandIterator->command.substr(indx + 1); //taking the remaining part (x, y, z, a, b, c, stack ...)
		//cout << currentCommand << endl;
		//cout << commandInfo << endl;

		if(currentCommand == "define")
		{
			//process the define command
			string newStr = functionName + ": " + currentCommand + " " + commandInfo; //combining the service function info, current command & command info for simplifying the printing process
			commonStack.push(newStr); //pushing combined info to common stack
		}
		else if (currentCommand == "call")
		{
			// processing the call option
			cout << "Calling " << commandInfo << " from " << functionName << endl;
			// the recursion goes here --> calling copy of the same function and processing other service func.
			processARequest(commandInfo);
		}
		else{
			string tempStr; //temporary string for popping operation
			cout << "PRINTING THE STACK TRACE: " << endl;
			if(commonStack.isEmpty()){ //if the stack is empty
				cout << "The stack is empty" << endl;
			}else{
				while(!commonStack.isEmpty()){ //while the common stack is not empty
					commonStack.pop(tempStr);
					temp.push(tempStr); //preserving popped tempStr in temporary stack
				}
				while(!temp.isEmpty()){ //while the temporary stack is not empty
					temp.pop(tempStr);
					cout << tempStr << endl; //printing the popped information --> this print operation gives reverse order of common stack
					commonStack.push(tempStr); //pushing again the given informations to common stack properly
				}
			}
		}
		commandIterator = commandIterator->next;
	}// while
	//…
	// delete this function’s data from the top of the stack
	cout<<functionName<<" is finished. Clearing the stack from it's data... "
		<<endl;
	commonStack.clear(functionName);
	system("pause");
}

void Services::processARequest()
{

	//a member function for 
	//pre: a request exist
	//post: process the request in given format --> starting with isntructors and after instructors finish proceeds with students

	if (!instructorQueue.isEmpty()) //whether the instructors queue is empty or not
	{
		instructorInfo temp; //creating temporary instructor info node
		instructorQueue.dequeue(temp); //taking the first element from the instructors queue and assigning the information it includes to the temporary node variable
		cout << "Processing instructors queue..." << endl;
		cout << "Processing prof. " << temp.InstructorName << "'s request (with ID " << temp.id << ") of service (function): " << endl;
		cout << temp.ServiceName << endl; 
		//if instructors queue is not empty, process the next request 
		processARequest(temp.ServiceName); //processing given service function in another function with same name (but different arguments)
		if(commonStack.isEmpty()){
			cout << "The stack is empty." << endl;
		}
		cout<<"GOING BACK TO MAIN MENU"<<endl;
	}
	else if (!studQueue.isEmpty()) //whether the stundents queue is empty or not
	{
		StudentNode temp;
		studQueue.dequeue(temp); //again taking the first in element from queue and assigning its' information to temporary students node variable
		cout << "Instructors queue is empty. Proceeding with students queue..." << endl;
		cout << "Processing " << temp.StudName << "'s request (with ID " << temp.id << ") of service (function): " << endl;
		cout << temp.serviceName << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
		//if instructors queue is empty and student’s not
		//then process the next student request 
		processARequest(temp.serviceName); //processing given service function in another function with same name (but different arguments)
		if(commonStack.isEmpty()){ //if the common stack is empty --> private variable that holds service informations
			cout << "The stack is empty." << endl;
		}
		cout<<"GOING BACK TO MAIN MENU"<<endl;
	}
	else
	{
		// otherwise…
		cout <<"Both instructor's and student's queue is empty.\nNo request is processed."<<endl<< "GOING BACK TO MAIN MENU" << endl;
	}
}