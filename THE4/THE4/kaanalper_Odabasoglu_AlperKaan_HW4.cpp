#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include "Services.h"

using namespace std;

bool GLOBAL_TERMINATE; //Global variable for terminating loop according to the case of another document


int main(){

	Services testService; //creating an object from the Services class
	string openFile, inputFile; //creating 2 string for opening the given input files
	GLOBAL_TERMINATE = true; //initializing the global variable

	cout << "If you want to open a service (function) defining file," << endl;
	cout << "then press (Y/y) for 'yes', otherwise press any single key" << endl;
	cin >> openFile;

	while((openFile == "Y" || openFile == "y") && GLOBAL_TERMINATE){
		cout << "Enter the input file name: ";
		cin >> inputFile;
		testService.addInputFile(inputFile); //calling add input file for adding given information to linked list
		if(GLOBAL_TERMINATE){ //Terminating loop if the file cannot be opened in another document
			cout << "Do you want to open another service defining file?" << endl;
			cout << "Press (Y/y) for 'yes', otherwise press anykey" << endl;
			cin >> openFile;
		}else{
			return 0;
		}
	}

	if(testService.getServiceHead() == NULL){ //Looking for whether there is services exist or not by taking the private variable as a return value
		cout << "No service found..." << endl;
	}else{
		//Main menu
		cout << "-------------------------------------------------------------------" << endl;
		cout << "PRINTING AVAILABLE SERVICES (FUNCTIONS) TO BE CHOSEN FROM THE USERS" << endl;
		cout << "-------------------------------------------------------------------" << endl << endl;

		testService.printInput(); //prints the available services (member function)

		while (true){
			cout << endl;
			cout<<"**********************************************************************"<<endl
				<<"**************** 0 - EXIT PROGRAM			 *************"<<endl
				<<"**************** 1 - ADD AN INSTRUCTOR SERVICE REQUEST	 *************"<<endl
				<<"**************** 2 - ADD A STUDENT SERVICE REQUEST	 *************"<<endl
				<<"**************** 3 - SERVE (PROCESS) A REQUEST		 *************"<<endl
				<<"**********************************************************************"<<endl;
			cout << endl;
			int option;
			cout << "Pick an option from above (int number from 0 to 3): ";
			cin>>option; //choosing one of the three options
			switch (option)
			{
			case 0:
				cout<<"PROGRAM EXITING ... "<<endl;
				system("pause");
				testService.~Services();
				exit(0);
			case 1:
				testService.addInstructorRequest(); //if the option is 1 program waits for service demanded by the instructor (member function)
				break;
			case 2:
				testService.addStudentRequest(); //if the option is 2 program waits for service demanded by the student (member function)
				break;
			case 3:
				testService.processARequest(); //if the option is 3 program process the requests starting with instructors (member function)
				break;
			default:
				cout<<"INVALID OPTION!!! Try again"<<endl;
			}//switch
		}//while (true)
	}


	return 0;
}