#include <iostream>
#include <string>   //for using string operations
#include <vector>   //for keeping the ids in node 
#include <fstream>  //for file operations
#include <sstream>  //istringstream

using namespace std;

void insert(vector<int> & a, int newnum){  		
	//This function was taken from CS201 Slides --> Vectors slide Selection Sort vectors.pptx
	// NOT const vector
	// pre: a[0] <= … <= a[a.size()-1], a is sorted
	// post: newnum inserted into a, a still sorted
	int count = a.size();  // size before insertion
	a.push_back(newnum);   // increase size –newnum is inserted at the
	// end but inserted value is not important
	int loc = count;      // start searching insertion loc from end

	while (loc > 0 && a[loc-1] > newnum){    
		a[loc] = a[loc-1]; 
		loc--;        // shift right until the proper insertion cell
	}
	a[loc] = newnum;  //actual insertion 
}

struct courseNode
{
	//This struct holds the information about the code of the course, name of the course, the id list of the course & the next nodes pointer
	//2 constructor, 1 default, 1 for the given informations 
	string courseCode, courseName;
	vector<int> studentsAttendingIDs;
	courseNode * next;

	courseNode::courseNode()
	{
	};

	courseNode::courseNode(string code, string name, int id, courseNode *ptr)
	{
		courseCode = code;
		courseName = name;
		insert(studentsAttendingIDs, id);
		next = ptr;
	};
};

int bsearch(const vector<int>& list, const int& key){
	//This function was taken from CS201 Slides --> Vectors slide Selection Sort vectors.pptx nd modified a little bit
	// pre: list.size() == # elements in list
	// post: returns index of key in list, -1 if key not found
	int low = 0;                   // leftmost possible entry
	int high = list.size()-1;      // rightmost possible entry
	int mid;                       // middle of current range

	while (low <= high){   
		mid = (low + high)/2;
		if (list[mid] == key)       // found key, exit search
			return mid;
		else if (list[mid] < key)   // key in upper half
			low = mid + 1;
		else                        // key in lower half
			high = mid - 1;
	}
	return -1;                      // not in list
} 

void AddToSorted(courseNode *&head ,string code, string name, int id){
	//This function was taken from CS204 power point slides which is 2.2-pointers-linkedlist.pptx and modified
	//pre-condition: a head exist and defined
	//post-condition: adds a new node with respect to the given name to linked list and assign new head with referance parameter --> Updates head if it changes 
	courseNode *  ptr = head;   // loop variable

	// if new node should be first, handle this case and return  
	// in this case, we return address of new node since it is new head  
	if (head == NULL || name < head->courseName)        
	{   
		courseNode * temp = new courseNode(code, name, id , head);  //node to be inserted 
		head = temp;
	}else{
		while (ptr->next != NULL && ptr->next->courseName < name)
		{    
			ptr = ptr->next;
		} // postcondition: new node to be inserted just after the node ptr points

		//now insert new node with newkey after where ptr points to
		courseNode * temp = new courseNode(code, name, id , ptr->next);  //node to be inserted 
		ptr->next = temp;
	}
}

void Options(){
	//A function for displaying options to be selected by the user 
	cout << endl;
	cout << "Please select one of the choices:" << endl; 
	cout << "1. Add to List" << endl;
	cout << "2. Drop from List" << endl;
	cout << "3. Display List" << endl;
	cout << "4. Finish Add/Drop and Exit" << endl;
}

void PrintSort(courseNode *head){
	//post-condition: a linked list exist with a given parameter head
	//pre-condition: displaying the list starting from the given head ending at the NULL part
	//This fuction is for the 3rd option
	courseNode *ptr = head;
	while(ptr != NULL){
		//if(count > 0){
		cout << ptr->courseCode << " " << ptr->courseName << ":";
		for(int i = 0 ;i < ptr->studentsAttendingIDs.size(); i++){
			cout << " " << ptr->studentsAttendingIDs[i];
		}
		cout << endl;
		//}
		if(ptr != NULL)
			ptr = ptr->next;  //after printing appropriate informations about current node jumping the next node
	}
}

void deleteList(courseNode *&head){
	//This function is taken from the 2.2-pointers-linkedlists.pptx slide of the CS204 and modified a bit
	//post-condition: A list with at least one element exist
	//pre-condition: Delete the list from beginning to end to prevent memory leakege
	courseNode *ptr = head;
	while(ptr != NULL){
		ptr = ptr->next; //assigning ptr to next node of head
		delete head;  //deleting the head
		head = ptr;   //assigning head to ptr
	}
}

void remove(vector<int> & a, int pos){ 
	//This piece of code was taken from CS201 vectors.pptx slide
	// pre: a is sorted
	// post: original a[pos] removed, a is still sorted
	int k, lastIndex = a.size()-1;
	for (k=pos; k < lastIndex; k++)
		a[k] = a[k+1]; 
	// shift all elements on the right of pos one cell left
	a.pop_back();  // remove the last element of the array
}

void DeleteOneNode (courseNode * toBeDeleted, courseNode * & head, int &count)
	//This function was taken from CS204 power point slides which is 2.2-pointers-linkedlist.pptx and modified a bit
	/* pre: toBeDeleted points to the node to be deleted from the list
	post: deletes the node pointed by toBeDeleted, updates head if changes, if the deleted node is at the beggining count incremented and passes
	as a referance to PrintLastList function*/
{
	courseNode * temp;
	count = 0;
	if (toBeDeleted == head)  //if the node to be deleted is the first node
	{     head = head->next;
	delete toBeDeleted;
	count++; //if count is incremented, it means that the head is at the beggining and in that situation the PrintLastList function behaves differently
	}
	else  //if the node to be deleted is in the middle or at the end
	{     temp = head;
	while (temp->next != toBeDeleted)
		temp = temp->next;
	//after while, ptr points to the node just before toBeDeleted

	//connect the previous node to the next node and delete
	temp->next = toBeDeleted->next;
	delete toBeDeleted;
	}
}

void AddToList(courseNode *head){
	//pre-condition: a linked exist with a given head (constructed in main function) & all the id vectors sorted in nodes
	//post-condition: if given course does not exist create a new node and add it in the alphabetical order according to it's name
	//post-condition: if given course exist look whether course id assigned before or not, if it was not in the id list of given node of course insert it with respect to the sorted order in vector (insertion sort)
	string courseCode, courseName, line;
	int id; 
	cout << "Give the student ID and the course names and course codes that he/she wants to add:" << endl;
	while(getline(cin, line)){ //getting the user input of whole line
		istringstream sStream(line);  //using string stream to parse the input
		while(sStream >> courseCode >> courseName){
			while(sStream >> id){
				courseNode *ptr = head;
				while(ptr != NULL && ptr->courseCode != courseCode){ //checking whether given course node exist
					ptr = ptr->next;
				}
				if(ptr == NULL){ //if the given course does not exist it is added with AddtoSorted() function --> definition of AddtoSorted is above
					AddToSorted(head, courseCode, courseName, id);
					cout << courseCode << " does not exist in the list of Courses. It is added up." << endl;
					cout << "Student with id " << id << " is enrolled to " << courseCode << "." << endl;
				}else{
					if(ptr->courseCode == courseCode){ //if the course is exist in linked list
						if(bsearch(ptr->studentsAttendingIDs, id) != -1){ //if the id is exist in vector of ids 
							cout << "Student with id " << id << " already is enrolled to " << courseCode << ". No action taken." << endl;
						}else{ //if the id is not found in vector of student ids
							insert(ptr->studentsAttendingIDs, id); //inserting it with insertion sort
							cout << "Student with id " << id << " is enrolled to " << courseCode << "." << endl;
						} 
					}
				}
			}
			//Clearing the error flags
			sStream.get();
			sStream.clear();
		}
	}
}

void DropFromList(courseNode *head){
	//pre-condition: a linked exist with a given head (constructed in main function) & all the id vectors sorted in nodes
	//post-condition: if given course does not exist gives appropriate message 
	//post-condition: if given course exist look whether course id assigned before or not, if it was not in the id list of given node of course delete it with respect to the sorted order in vector (remove() function above)
	//post-condition: if the given course exist and the id was not assigned before, this function will give an appropriate warming message
	string courseCode, courseName, line;
	int id;
	cout << "Give the student ID and the course names and course codes that he/she wants to drop:" << endl;
	while(getline(cin, line)){ //getting the user input of whole line
		istringstream sStream(line); //using string stream to parse the input
		while(sStream >> courseCode >> courseName){
			while(sStream >> id){
				courseNode *ptr = head;
				while(ptr != NULL && ptr->courseCode != courseCode){ //checking whether given course node exist or not 
					ptr = ptr->next;
				}
				if(ptr == NULL){ //if course node does not exist
					cout << "The " << courseCode << " course is not in the list, thus student with id " << id << " can't be dropped" << endl;
				}else{
					if(ptr->courseCode == courseCode){
						if(bsearch(ptr->studentsAttendingIDs, id) == -1){ //if the student id does not exist in vector
							cout << "Student with id " << id << " is not enrolled to " << courseCode << ", thus he can't drop that course." << endl; 
						}else{
							int indx;
							for(int i = 0 ; i < ptr->studentsAttendingIDs.size(); i++){
								if(ptr->studentsAttendingIDs[i] == id){
									indx = i; //finding the index of id in vector
								}
							}
							remove(ptr->studentsAttendingIDs, indx);  //Deleting the given id
							cout << "Student with id " << id << " has dropped " << courseCode << "." <<endl;
						}
					}
				}
			}
			//Clearing error flags
			sStream.get();
			sStream.clear();
		}
	}
}

void DisplayList(courseNode *head){
	//pre-condition: a linked list exist with given head
	//post-condition: Prints given list --> Option 3 
	cout << "The current list of course and the students attending them:" << endl;
	PrintSort(head);
}

void PrintLastList(courseNode *&head){
	//pre-condition: a head of linked list defined 
	//post-condition: displays the informations in lists
	//post-condition: if there is less than 3 students in a course (studentsAttendingIDs.size() < 3) deletes that specific course with DeleteOneNode() function above and displays appropriate message
	courseNode *ptr = head;
	int count = 0; //This count is used for controlling whether the first element will be deleted or not
	while(ptr != NULL){
		cout << ptr->courseCode << " " << ptr->courseName;
		if(ptr->studentsAttendingIDs.size() > 2){ //if given course has at least 3 students
			cout << ":";
			for(int i = 0 ;i < ptr->studentsAttendingIDs.size(); i++){
				cout << " " << ptr->studentsAttendingIDs[i];
			}
			cout << endl;
		}else{ //Given course has less than 3 students
			for(int i = 0 ;i < ptr->studentsAttendingIDs.size(); i++){
				cout << " " << ptr->studentsAttendingIDs[i];
			}
			cout << " -> This course will be closed" << endl;
			DeleteOneNode(ptr, head, count); //Deleting the course
			ptr = head; //assigning ptr to new head
		}
		if(count == 0){ //if count is more than 0 that means that the first element in list is deleted thats' why ptr will not be assigned to next node since if it assigns next node, next course information will be lost
			if(ptr != NULL)
				ptr = ptr->next;
		}
		count = 0;
	}
}

void TerminateAddDrop(courseNode *&head){
	//post: takes a defined head of linked list
	//pre: displays the last list for option 4, update head if it changes & send it to main function
	cout << "The add/drop period is finished. Printing the final list of courses and students attending them." << endl;
	cout << "NOTE: Courses with less than 3 students will be closed this semester." << endl;
	PrintLastList(head);
}

int main(){

	ifstream CourseFile;
	string fileName;

	//opening the file --> initial condition
	cout << "Please enter file name: " << endl;
	cin >> fileName;
	CourseFile.open(fileName.c_str());

	if(CourseFile.fail()){ //if the file cannot be opened
		cout << "Cannot be opened" << endl; //Control
	}else{
		cout << "Successfully opened file coursesAndStudents.txt" << endl;
		string line;
		int LineNum = 0;
		courseNode *head = NULL;
		while(getline(CourseFile, line)){ //reading the lines from list
			string courseName, courseCode;
			istringstream sLine(line); //parse it with string stream
			int id;
			if(LineNum == 0){ //initial creation of linked list
				sLine >> courseCode >> courseName >> id;
				AddToSorted(head, courseCode, courseName, id); //create linked lists' first element with given informations
				LineNum++;
			}else{
				courseNode *ptr;
				ptr = head;
				sLine >> courseCode >> courseName >> id;
				while(ptr != NULL && ptr->courseCode != courseCode){ //checking whether the course read from file has a node on list
					ptr = ptr->next;
				}if(ptr != NULL && ptr->courseCode == courseCode){ //if course exist in linked list
					insert(ptr->studentsAttendingIDs, id); //insertion sort (inserting given id to sorted vector without deteriorating the sort order)
				}else if(ptr == NULL){ //if course does not exist in file
					AddToSorted(head, courseCode, courseName, id);  //add that course without violating the sorting order with respect to course names
				} 
			}
			//Clearing the error flags
			sLine.get();
			sLine.clear();
		}
		cout << "The linked list is created." << endl;
		cout << "The initial list is: " << endl;
		PrintSort(head); //Printing intial linked list

		int option;
		//Taking the option 1-2-3-4
		do{
			Options();
			cin >> option;
			if(option == 1){
				AddToList(head); //Adding given inputs to list
			}else if(option == 2){
				DropFromList(head); //Drop given ids from list
			}else if(option == 3){
				DisplayList(head); //prints list
			}else{ //option == 4
				TerminateAddDrop(head); //Terminates the period with displaying last situation 
			}
			//Clearing accumulated error flags in console input
			cin.get();
			cin.clear();
		}while(option != 4);

		deleteList(head); //Delete whole list for preventing memory leakege

	}
	return 0;
}