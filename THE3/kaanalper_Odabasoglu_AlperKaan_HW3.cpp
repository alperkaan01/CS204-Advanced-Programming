#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct busStop {
	string busStopName;
	busStop *left;
	busStop *right;

	busStop::busStop()
	{}; //default constructor

	busStop::busStop(string name)
	{
		busStopName = name;
		left = NULL; //Left and right are default NULL
		right = NULL;
	} //Hand-written constructor taking the given name and assigning it to busStop nodes' info
};
struct busLine {
	string busLineName;
	busLine *next;
	busStop *busStops;

	busLine::busLine() //default constructor for Lines
	{};

	busLine::busLine(string name)
	{
		busLineName = name;
		next = NULL;  //next and busStops default NULL
		busStops = NULL;
	}; //assigning given parameter string to busLine name
};
busLine* head = nullptr;

bool BusStopFinder(string busStopName){
	//post: a global head exist for bus routes & a bus stop name taken as a parameter
	//pre: finds given bus stop
	bool isFound = false;
	busLine *headLine = head;
	while(headLine != NULL && !isFound){
		busStop *iterator = headLine->busStops; //iterator pointer iterates over given lines busStops
		while(iterator != NULL){
			if(iterator->busStopName == busStopName){ 
				isFound = true;
				return isFound; //if it finds the busStop it returns true
			}else{
				iterator = iterator->right;
			}
		}
		headLine = headLine->next;
	}
	return isFound; //returns false if it cannot find the given stop
}

void printBusLines(){
	//post: a global head exist
	//pre: printing the linked list information after initialization --> Displaying the busLine information
	busLine *ptr = head;
	busStop *currentS = NULL;
	cout << endl;
	while(ptr != NULL){
		cout << ptr->busLineName << ": ";
		currentS = ptr->busStops; //iterator on busStops
		while(currentS != NULL){
			cout << currentS->busStopName;  //printing busStop information (name) for corresponding line
			if(currentS ->right != NULL){
				cout << "<->";
			}
			currentS = currentS->right; //iterating over bus stops by using pointers
		}
		cout << endl;
		ptr = ptr->next;
	}
}

void printSpecificLine(string lineName, busLine *iterator){
	//post: a global head & given line exist. An iterator given for accessing the line and bus stop information
	//pre: displays specific line by accessing busStop informations in consecutive nodes
	cout << iterator->busLineName << ": ";
	busStop *temp = iterator->busStops;
	while(temp != NULL){
		cout << temp->busStopName; //a temporary pointer iterating over bus stops and printing them to console
		if(temp ->right != NULL){
			cout << "<->";
		}
		temp = temp->right;
	}
	cout << endl;
}

bool isEmpty(){
	//post: a global head exist
	//pre: returns true if the busLine is empty (no busStop exist in line) - returns false if its not empty
	if(head->busStops == NULL)
		return true;
	return false;
}

void printInfo(){
	//post: a global head exists
	//pre: without any parameters printing the information contained by the Lines
	cout << head->busLineName << ": ";
	busStop *iterator = head->busStops;
	while(iterator != NULL){
		cout << iterator->busStopName; //iterating over stops in given line and printing the info
		if(iterator ->right != NULL){
			cout << "<->";
		}
		iterator = iterator->right;
	}
}

void deleteHeadNodeInfo(busLine *tempHead){
	//post: a global head for linked list exist & a temporary head parameter is given
	//pre: deletes the information in the line node that head is pointing
	busStop *iterator = head->busStops;
	busLine *tempNext = head;
	bool terminate = false; //boolean variable for terminating the loop when the iterator iterates over all bus stops and equal to NULL
	while(iterator->right != NULL){
		iterator = iterator->right; //iterator iterates up to the most right edge of head lines bus stop nodes
	}
	while(!terminate){
		busStop *temp = iterator;
		iterator = temp ->left;
		delete temp; //it deletes the temps consecutively in the left directions
		if(iterator == NULL){
			terminate = true;
		}
	}
	head = tempHead->next; //in order not to lost the head info assigning it to next line node
	delete tempHead; //deleting the temporary head (the previous head line)
}

void addBusLine(){
	//post: a global head exist for pre-created linked list
	//pre: adds bus lines to the linked list if the line includes at least one bus stop
	bool terminateLine = false, terminateStop = false; //boolean variables for termination of loops
	string lineName, stopName, option;
	busLine *ptr = nullptr, *temphead = head, *iterator = NULL;
	busStop *currentS = NULL, *iteratorStop = NULL;

	cout << "Enter the name of the new bus line (0 for exit to main menu)." << endl;
	cin >> lineName; //Taking the lineName want to be added
	while(!terminateLine){
		iterator = head;
		while(iterator != NULL && iterator->busLineName != lineName){ //Looking for whether the given busLine exists before
			iterator = iterator->next;
		}if(iterator == NULL){ 
			if(lineName == "0"){ //if user enters 0 at the beginning exit to main
				//cout << "Exiting to main... (for testing)" << endl;
				terminateLine = true; //terminates the option and exiting to main
			}else{
				ptr = new busLine(lineName); //creating the new dynamically allocated node for adding the busLine
				ptr->next = head;
				head = ptr;
				cin.get();
				cin.clear();
				int count(0);
				bool isSame = true; //bool for controlling whether the bus stop name previously entered or not
				while(!terminateStop){
					if(isSame){
						cout <<	"Enter the name of the next bus stop (enter 0 to complete)" << endl;
						cin >> stopName;
					}
					if(stopName == "0"){ //if user gives bus stop name as "0" without giving any bus stop name the program gives appropriate message and stop
						if(isEmpty()){ //checking whether the line that is want to be added is empty or not
							cout << "You are not allowed to add an empty bus line" << endl;
							delete head; //deleting head and assigning it to temphead to deleting created line information
							head = temphead;
							terminateStop = true; //termination
							terminateLine = true;
						}else{
							cout << "The bus line information is shown below" << endl;
							printInfo(); //Prining line informations
							cout << endl;
							cout << "Are you sure? Enter (y/Y) for yes (n/N) for no?" << endl; //looking whether the user is sure about adding operation
							cin >> option;

							if(option == "Y" || option == "y"){ //if yes
								terminateStop = true;
								terminateLine = true;
								printBusLines(); //just print final version of linked-list
							}else{
								temphead = head;
								deleteHeadNodeInfo(temphead); //if the user is entering "no", just deletes the given head information 
								terminateStop = true;
								terminateLine = true;
							}
						}
					}else{
						iteratorStop = ptr->busStops;
						while(iteratorStop != NULL && iteratorStop->busStopName != stopName){ //Looking for whether given bus Stop exist or not
							iteratorStop = iteratorStop->right;
						}if(iteratorStop == NULL){ //if it does not exist
							if(count == 0){ //if its the first addition
								ptr->busStops = new busStop(stopName);
								currentS = ptr->busStops;
							}else{ //consecutive addition
								busStop *temp = new busStop(stopName);
								currentS->right = temp; //adding bus to the end of the doubly-linked-list in given line
								temp->left = currentS;
								currentS = temp;
							}
							isSame = true;
							count++;
						}else{ //if the given bus stop exist previously repeatedly asks for new bus stop name
							cout << "Bus stop already exists in the line" << endl;
							cout <<	"Enter the name of the next bus stop (enter 0 to complete)" << endl;
							cin >> stopName;
							isSame = false;
						}
						//cin.get();
					}
				}
			}
		}else{ //if the given busLine does not exist repeatedly asks for it
			cout << "Bus line already exists: enter a new one (0 for exit)" << endl;
			cin >> lineName;
		}
	}
	cin.get();
	cin.clear();
}

void addBusStop(){
	//post: a global head exist for linked list
	//pre: adds new bus stop to corresponding bus line after the given existing bus stop
	string lineName,newBusStop, prevBusStop;
	busLine *iterator = head;
	bool isTerminate = false;
	cout << "Enter the name of the bus line to insert a new bus stop (0 for main menu)" << endl;
	cin >> lineName; //Taking the line name for bus stop insertion
	while(!isTerminate){
		while(iterator != NULL && iterator->busLineName != lineName){
			iterator = iterator->next; //finding the given line by iteration
		}if(iterator == NULL){ //if given line does not exist terminate the process and go back to main
			isTerminate = true;
			cout << "Bus line cannot be found. Going back to previous menu." << endl;
		}else{
			cout << "The bus line information is shown below" << endl;
			printSpecificLine(lineName, iterator); //if given line information exists just printing out this lines' information
			cout << "Enter the name of the new bus stop" << endl;
			cin >> newBusStop; //new bus stop name
			busStop *busStopIterator = iterator->busStops;
			while(busStopIterator != NULL && busStopIterator->busStopName != newBusStop){
				busStopIterator = busStopIterator->right; //finding whether the bus stop exist or not by iteration
			}
			if(busStopIterator != NULL){ //it already exists if the iterator stay on a node
				isTerminate = true;
				cout << "Bus stop already exists. Going back to previous menu." << endl;
			}else{
				cout << "Enter the name of the previous bus stop to put the new one after it (0 to put the new one as the first bus stop)" << endl;
				cin >> prevBusStop; //taking previous bus stop name that the new node added after it
				if(prevBusStop == "0"){ //if previous bus stop name is taken '0' from the user --> just add busstop to beginning of list
					busStop *newStop = new busStop(newBusStop);
					newStop->right = iterator->busStops;
					iterator->busStops->left = newStop;
					iterator->busStops = newStop;
					isTerminate = true;
					printBusLines(); //displaying bus Line informations consecutively with another function call
				}else{ //if the given bus stop will be added to middle or end of the list
					bool TerminateStop = false;
					while(!TerminateStop){
						busStopIterator = iterator->busStops; //creating temporary iterator for bus stops
						while(busStopIterator != NULL && busStopIterator->busStopName != prevBusStop){
							busStopIterator = busStopIterator->right; //finding the previous bus stop
						}if(busStopIterator == NULL){ //controlling whether it is exist or not
							cout << "Bus stop does not exist. Typo? Enter again (0 for main menu)" << endl;
							cin >> prevBusStop; //if it does not exist continuously asking for right bus stop
						}else{
							//if the previous busStop exists than put it into the right place
							busStop *newStop = new busStop(newBusStop);
							if(busStopIterator->right == NULL){ //if we are adding the new bus node to the end of the list
								busStopIterator->right = newStop;
								newStop->left = busStopIterator;
							}else{ //if we are adding new stop to the middle of the list
								busStopIterator->right->left = newStop;
								newStop->right = busStopIterator->right;
								busStopIterator->right = newStop;
								newStop->left = busStopIterator;
							}
							isTerminate = true;
							TerminateStop = true;
							printBusLines(); //printing resulting bus lines 
						}
						//cin.get();
						//cin.ignore();
						//cin.clear();
					}
				}
			}
		}
	}
	cin.clear(); //clearing error flags
}

void deleteBusLine(){
	//post: a global head ezist for linked list
	//pre: deletes the given bus line if it exists
	string name;
	cout << "Enter the name of the bus line to delete" << endl;
	cin >> name; //taking the name of the bus line to delete
	busLine *iterator = head; //temporary iterator on lines
	busLine *temphead = head; //temporary iterator on lines
	while(iterator != NULL && iterator->busLineName != name){
		iterator = iterator->next; //looking for whether the bus line exists 
	}
	if(iterator == head){ //if the bus Line exists in the first stop (it is the first node of the list)
		deleteHeadNodeInfo(temphead); //deleting head and assigning head to next node
		printBusLines(); //print bus stop information
	}else{
		iterator = head;
		while(iterator->next != NULL && iterator->next->busLineName != name){
			iterator= iterator->next; //looking for whether the next node is the target one
		}
		busLine *temp = iterator; //creating a temporary pointer and equalize it to iterators' current spot
		iterator = iterator->next; //assigning temporary iterator pointer to next node
		if(iterator == NULL){ //controlling whether the pointer at the end of the list or not
			cout << "Bus line cannot be found. Going back to the previous (main) menu." << endl;
		}else{ //if it is not at the end
			temp->next = iterator->next; //skipping the line that will be deleted and update the linked list
			busStop *tempIterator = iterator->busStops; //before deleting the line we need to delete all bus stops its' including thats' why temporary iterator for bus stops is created
			bool terminate = false;
			while(tempIterator->right != NULL){
				tempIterator = tempIterator->right;
			}
			while(!terminate){
				busStop *tempStop = tempIterator;
				tempIterator = tempStop ->left; //deleting the bus stop nodes in the left direction
				delete tempStop;
				if(tempIterator == NULL){
					terminate = true; //if all bus stops are deleted and tempIterator is NULL terminate the loop
				}
			}
			delete iterator; //deleting the line node
			printBusLines(); //print new bus line information for the system
		}
	}
}

void deleteBusStop(){
	//post: a global head exists for iteration
	//pre: given bus stop will be deleted from given line if line and bus stop exists
	string lineName;
	cout << "Enter the name of the bus line to delete a new bus stop (0 for main menu)" << endl;
	cin >> lineName; //taking the name of the line from user
	busLine *iterator = head;
	while(iterator != NULL && iterator->busLineName != lineName){
		iterator = iterator->next; //iterator over lines for finding the corresponding node
	}
	if(iterator == NULL){ //if the line cannot be find and iterator pointer is at the end of the given list go to main
		cout <<	"Bus line cannot be found. Going back to previous (main) menu." << endl;
	}else{
		cout << "The bus line information is shown below" << endl;
		printSpecificLine(lineName, iterator); //printing specific line information for given line
		bool terminate = false; //bool for terminating loop
		string busStopName;
		cout << "Enter the name of the bus stop to delete (0 for main menu)" << endl;
		cin >> busStopName; //taking bus stop name
		while(!terminate){
			cin.get();
			cin.clear(); //clearing the error flags in console input
			busStop *tempStop = iterator->busStops;
			while(tempStop != NULL && tempStop->busStopName != busStopName){
				tempStop = tempStop->right; //looking for whether the bus stop exist in bus stop list
			}if(tempStop == NULL){ //if the bus stop does not exist just ask contiuously
				cout << "Bus stop cannot be found. Enter the name of the bus stop to delete (0 for main menu)" << endl;
				cin >> busStopName;
			}else{
				terminate = true; //if it exists go out of this loop
			}
		}
		busStop *tempStop = iterator->busStops; //temporary iterator for bus stops
		int counter(0); //counter for looking whether the given stop is at the beginning or not
		while(tempStop != NULL && tempStop->busStopName != busStopName){
			tempStop = tempStop->right; //iterating on bus stops in the right way up to finding the given stop
			counter++; //if the given stop at the beginning counter will stay at 0
		}
		if(counter == 0){ //if the bus stop located at the beginning
			if(tempStop->right == NULL){ //if there is just one node
				delete tempStop;
				iterator->busStops = nullptr;
			}else{ //if there is more than one node
				busStop *ptr = tempStop->right; //creating a pointer equal the 2nd node in list
				iterator->busStops = ptr; //equalizing lines pointer for bus stop to second node
				ptr->left = nullptr; //equalizing left pointer of second node to NULL
				delete tempStop; //deleting the corresponding bus stop
				printBusLines(); //printing last version
			}
		}else{
			if(tempStop->right == NULL){ //if the stop is at the end
				tempStop->left->right = tempStop->right; //just equalizing the previous node of last nodes' right pointer to NULL
				delete tempStop; //deleting the last node 
				printBusLines(); //displaying the information of it
			}else{
				tempStop->left->right = tempStop->right; //assigning left and right of previous and next node of target pointer's pointers to each other
				tempStop->right->left = tempStop->left;
				delete tempStop; //deleting target
				printBusLines(); //displaying the line information
			}
		}if(iterator->busStops == NULL){
			busLine *tempHead = head;
			if(head == iterator){ //delete head node when the bus stops are finished in a given line
				head = head->next;
				delete tempHead;
				printBusLines();
				terminate = true;
			}else{
				//delete a normal node
				tempHead = iterator;
				busLine *tempIterator = head;
				while(tempIterator->next != tempHead){
					tempIterator = tempIterator->next;
				}
				if(tempHead->next == NULL){
					tempIterator->next = NULL;
					delete tempHead;
					printBusLines();
					terminate = true;
				}else{
					tempIterator->next = tempHead->next;
					delete tempHead;
					printBusLines();
					terminate = true;
				}
			}
		}
	}
}

void pathfinder(){
	//post: a global head exist
	//pre: check whether there is a path exist between the given 2 bus stops

	string currentStop, targetStop; //current stop & the target stop taken from user
	cout << "Where are you now?" << endl;
	cin >> currentStop;
	cout << "Where do you want to go?" << endl;
	cin >> targetStop;
	if(!BusStopFinder(currentStop) || (!BusStopFinder(targetStop))){
		cout << "Bus stop does not exist in the table. Going back to previous menu." << endl;
	}else{
		if(targetStop == currentStop){ //if the user gives same input to current and target stop
			cout << "You are already at that bus stop" << endl; //Artrim hoca said that we can use this via whatsapp
		}else{
			busLine *headLine = head; //creating temp head for iteration
			string currentLine;
			int count = 0;
			bool isExist = false; //bool for termination
			while(headLine != NULL && !isExist){
				busStop *iterator = headLine->busStops;
				while(iterator != NULL && !isExist){
					if(iterator->busStopName == targetStop){ //if target stop detected just increment count for understanding it is detected before the current stops' position (we need to go left to reach that target)
						count++;
					}
					if(iterator->busStopName == currentStop){ //if we find the currentstop
						if(count > 0){ //if the target was detected before the current stop node
							busStop *iteratorClone = iterator;
							cout << "You can go there by " << headLine->busLineName << ": ";
							while(iteratorClone->busStopName != targetStop){
								cout << iteratorClone->busStopName << "->";
								iteratorClone = iteratorClone->left; //go left up to the target stop and print infos
							}
							cout << targetStop << endl; //last of all just print the target 
							isExist = true; //terminate loop
							count = 0;
						}else{ //if we could not detect the target before current stop
							busStop *iteratorClone = iterator;
							while(iteratorClone != NULL){
								if(iteratorClone->busStopName == targetStop){ //if the target detected at right place of current
									cout << "You can go there by " << headLine->busLineName << ": ";
									while(iterator->busStopName != targetStop){
										cout << iterator->busStopName << "->";
										iterator = iterator->right; //iterate to right up to target stop and print infos
									}
									cout << targetStop << endl;
									isExist = true; //termiante loop
								}
								iteratorClone = iteratorClone->right;
							}
						}
					}
					iterator = iterator->right; //iterates over all bus stops in given line
				}
				count = 0;
				headLine = headLine->next; //jumping to next line
			}
			if(!isExist){
				cout << "Sorry no path from " << currentStop <<" to " << targetStop << " could be found." << endl;
			}
		}
	}
}

void deleteLinkedList(){
	//post-condition: a global head & corresponding linked list exist
	//pre-condition: deleting whole list for prevention of memory leakage
	while(head != NULL){
		busLine *headLine = head; //a temporary head pointer pointing to global head
		busStop *temp = headLine ->busStops; //a temporary pointer pointing to initial busStop for corresponding line
		while(temp != NULL){
			busStop *ptr = temp;
			temp = ptr->right;
			delete ptr; //deleting corresponding busStop iteratively after shifting the temporary pointer
		}
		head = head->next; //assigning head to other line
		delete headLine; //deleting the line after jumping to other line
	}
}

void printMainMenu(){
	//Taken from the CS204 Homework 3 document
	//Prints the menu information
	cout << endl;
	cout <<"I***********************************************I"<<endl
		<<"I 0 - EXIT PROGRAM I"<<endl
		<<"I 1 - PRINT LINES I"<<endl
		<<"I 2 - ADD BUS LINE I"<<endl
		<<"I 3 - ADD BUS STOP I"<<endl
		<<"I 4 - DELETE BUS LINE I"<<endl
		<<"I 5 - DELETE BUS STOP I"<<endl
		<<"I 6 - PATH FINDER I"<<endl
		<<"I***********************************************I"<<endl
		<<">>";
	cout << endl;
}

bool consistencyCheck() {
	//Taken from the CS204 Homework 3 document 
	//post: a global head exist
	//pre: check whether the linked list include inconsistencies
	busLine* currBL = head; //a global variable
	while(currBL) {
		busStop* currBS = currBL->busStops;
		while(currBS) {
			busStop* rightBS = currBS->right;
			if(rightBS && rightBS->left != currBS) {
				cout << "Inconsistency for " << currBL->busLineName
					<< " " << currBS->busStopName << endl;
				return false;
			}
			currBS = currBS->right;
		}
		currBL = currBL->next;
	}
	return true;
}

void processMainMenu() {
	//Taken from the CS204 HW3 document
	//Processes the main menu options
	char input;
	do
	{
		if(!consistencyCheck()){
			cout << "There are inconsistencies. Exit." << endl;
			return;
		}
		printMainMenu();
		cout << "Please enter your option " << endl;
		cin >> input;
		switch (input) {
		case '0':
			cout << "Thanks for using our program" << endl;
			return;
		case '1':
			printBusLines();
			break;
		case '2':
			addBusLine();
			break;
		case '3':
			addBusStop();
			break;
		case '4':
			deleteBusLine();
			break;
		case '5':
			deleteBusStop();
			break;
		case '6':
			pathfinder();
			break;
		default:
			cout << "Invalid option: please enter again" << endl;
		} //switch
	} while(true);
}//processMainMenu

int main(){

	string fileName = "busLines.txt", line, busline, stop;
	ifstream file; //ifstream for file processing
	int count(0), iteration(0);
	busLine *tail = nullptr;

	file.open(fileName.c_str());

	while(getline(file, line)){ //getting lines from given file
		istringstream sStream(line); //parsing lines
		sStream >> busline;
		busline = busline.substr(0, busline.length()-1); //taking busLine names from txt
		if(count == 0){ //if the list is empty
			tail = new busLine(busline); //create new one
			head = tail;
		}else{
			busLine *tempLine = new busLine(busline); //create tempLine and add it after the previous line
			tail->next = tempLine;
			tail = tail->next;
		}
		busStop *currentStop = NULL;
		while(sStream >> stop){
			if(iteration == 0)
			{
				tail->busStops = new busStop(stop); //creating first bus stop node
				currentStop = tail->busStops;
			}else{
				busStop *temp = new busStop(stop); //adding consecutive bus stop nodes to first one
				currentStop->right = temp;
				temp -> left = currentStop;
				currentStop = temp;
			}
			iteration++;
		}
		count++;
		iteration = 0;
		sStream.get();
		sStream.clear(); //clearing the error flags for next iterations
	}


	processMainMenu(); //Menu options and executions
	deleteLinkedList(); //Preventing memory leakage by deleting the linked list

	return 0;
}