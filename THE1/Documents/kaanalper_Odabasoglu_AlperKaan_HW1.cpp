#include <iostream>
#include <string>
#include <iomanip> //for setw
#include <vector>
#include "randgen.h" //Random distribution
#include "strutils.h" //to use tostring();

using namespace std;

//Predeclaration of functions --> The bodies are in the below part of the main
vector<vector<string> > XmatrixCreator(const int &, const int &); //The purpose of this function is to create a matrix consist of just X 
vector<vector<string> > RandomDistribution(const int &, const int &, const int &); //The purpose of this function is distributing the bombs randomly
void Print(vector<vector<string> > &); //The purpose of this function is to display the given matrixes for testing 
vector<vector<string> > countingBomb(vector<vector<string> > &,vector<vector<string> > &, string, vector<vector<string> > &, int, int); //This function is the framework for the bombloop function. The aim is to find adjacent bomb counts and display it on multidimensional matrixes
void PrintPressOne(vector<vector<string> > &,vector<vector<string> > &, int, int); //This function aims to print the press option 1 --> it should temporarily display on screen thats' why I wrote it in another print mechanism
void bombLoop(int, int, vector<vector<string> > &, int, int,vector<vector<string> > &, string, int, int); //This function is the body of counting bomb function--> Created to avoid from repeated codes
void fillingMatrix(int , int, vector<vector<string> >&, vector<vector<string> >& , string , int); // This function is just fill multiple matrixes with given press options
void SingleRowCol(vector<vector<string> > &, vector<vector<string> > &, string, int, int); //This function calculates the adjacent bomb counts for single row || single column matrixes
void countingFuncForSingleRow(int ,int, int, int, int, string, vector<vector<string> > &, vector<vector<string> > &); //This function is the body for single row (row # = 1)
void countingFuncForSingleCol(int, int, int, int, int, string, vector<vector<string> > &, vector<vector<string> > &); //This function is the body for single col (col # = 1)

//Written by Alper Kaan Odabasoglu / email: kaanalper@sabanciuniv.edu

int main(){

	//Declarations
	int rows, cols, numBomb, counter(0), c1 , c2; //defining coordinates, # of bombs,counter for bombs, rows & cols 
	string press; //Taking press as a string to easily control whether it is between 1 - 2 and 3
	vector<vector<string> > xMatrix,tempMat, finalMatrix; //our multiple matrixes that holds the X's , and final products
	bool gameFinish(true); //This is a boolean value for terminating press option part

	//main flow of the program (assigning values to variables)
	cout << "Give the dimensions of the matrix: ";
	cin >> rows >> cols;  //taking the # of rows & cols
	xMatrix = XmatrixCreator(rows, cols); //generating the 'X' matrix

	cout << "How many bombs: ";  //# of bombs
	cin >> numBomb;
	while(numBomb > ((rows*cols) - 1) || numBomb < 1){  //checking the condition of bomb #'s 
		if(numBomb > ((rows*cols) - 1)){
			cout << "The number of bombs can not be greater than the whole number of cells minus one. Please give the number of bombs again: ";
			cin >> numBomb;
		}else{
			cout << "The number of bombs could not be less than one. Please give the number of bombs again: ";
			cin >> numBomb;
		}
	}
	int win = (rows * cols) - numBomb; //At the end this integer is used to control whether there is an unopened cell with including bomb

	cout<<endl;
	Print(xMatrix); //Testing Print function
	cout << endl; //DELETE


	vector<vector<string> > RandMat;
	RandMat = RandomDistribution(rows, cols, numBomb);
	tempMat =  RandMat;
	finalMatrix = RandMat;
	//Print(RandMat);//Testing Print function

	//MENU of the PRESS OPTIONS
	while(gameFinish){  //I used a boolean to control whether the loop will work or not
		cout << "Press: " << endl;
		cout << "1. If you want to find out the surrounding of a cell" << endl;
		cout << "2. If you want to open the cell" << endl;
		cout << "3. If you want to exit." << endl;

		cin >> press; //taking the press option 1 2 or 3

		while(press != "3" && press != "1" && press != "2"){  //Loop for correction for the PRESS OPTION
			cout << "Your input is wrong. Please select one of the options: 1, 2 or 3." << endl;
			cin >> press;
		}
		if(rows != 1 && cols != 1) //if the matrix has multiple axes countingBomb function will be called
			countingBomb(RandMat, tempMat,press, finalMatrix, rows, cols);
		else
			SingleRowCol(RandMat, finalMatrix, press, rows, cols); //otherwise SingleRowCol will be called --> if the rows = 1 || cols = 1


		//cout << endl;
		//Print(RandMat); //CONTROLING RANDOM DISTRIBUTION & THE CORRECTNESS OF # DISTRIBUTION IN CELLS 
		//cout << endl;
		//Print(finalMatrix);

		if(press == "1"){  // First option - take the coordinates 
			cout << "Give the coordinates: ";
			cin >> c1 >> c2;
			while(c1 > rows - 1 || c2> cols - 1 || c1 < 0 || c2 < 0){
				cout << "It is out of range. Please give a valid coordinates: ";
				cin >> c1 >> c2;
			}
			cout << endl;
			cout << "Displaying the surrounding of " << "(" << c1 << "," << c2 << ")" << ": " << endl;
			PrintPressOne(finalMatrix,xMatrix, c1 , c2); //Displaying the coordinates for the first option (function call)
			cout << endl;
			cout << "Around " << "(" << c1 << "," << c2 << ")" << " you have " << finalMatrix[c1][c2] << " bomb(s)" << endl;
			cout << endl;
		}else if(press == "2"){
			cout << "Give the coordinates: ";
			cin >> c1 >> c2;
			while(c1 > rows - 1 || c2> cols - 1 || c1 < 0 || c2 < 0){
				cout << "It is out of range. Please give a valid coordinates: ";
				cin >> c1 >> c2;
			}
			cout << endl;
			cout << "Opening cell " << "(" << c1 << "," << c2 << "):" << endl;
			xMatrix[c1][c2] = RandMat[c1][c2]; //changing the given coordinates with opened cell at X matrix (initial state)
			Print(xMatrix);
			cout << endl;
			if(RandMat[c1][c2] == "B"){ //if the coordinates open a cell with bomb
				cout << "Unfortunately, you stepped on a mine" << endl;
				cout << "Arrangement of mines:" << endl;
				Print(RandMat); //displaying the general distribution of bombs and the numbers in neighbooring cells 
				cout << endl;
				cout << ">>>>> Game Over! <<<<<" << endl;
				gameFinish = false;  //changing the value to terminate the loop 
			}else{
				counter++;
				if(counter == win){ //if the total count of opened cells == total # of cells - # of bombs the game will be terminated/ won 
					cout << "Congratulations! All the non-mined cells opened successfully" << endl;
					cout << "You won!" << endl;
					cout << ">>>>> Game Over! <<<<<" << endl;
					gameFinish = false; //changing the value to terminate the loop
				}
			}
		}else{ //OPTION 3 was PRESSED --> DIRECT TERMINATION
			cout << "Program exiting ..." << endl;
			gameFinish = false; //changing the value to terminate the loop
		}	
	}
	return 0;
}

vector<vector<string> > XmatrixCreator(const int &rows, const int &cols){
	vector<vector<string> > matrix(rows, vector<string>(cols, "X"));
	return matrix;
} //function for creating the initial X matrix

void Print(vector<vector<string> > &mat){
	for(int i = 0 ; i < mat.size() ; i++){
		for(int j = 0 ; j < mat[0].size(); j++){
			if(j == 0)
				cout << mat[i][j];
			else
				cout << setw(4) << mat[i][j];
		}
		cout << endl;  
	}
} //function for printing the given matrixes

vector<vector<string> > RandomDistribution(const int &rows, const int &cols, const int &nrMines){
	vector<vector<string> > matrix(rows, vector<string>(cols));
	RandGen x, y;
	int c1 , c2, bombNum(nrMines);

	do{
		c1 = x.RandInt(rows); //random selection for coordinates c1 / c2 
		c2 = x.RandInt(cols);
		if(matrix[c1][c2] != "B"){ //if the random cell does not include bomb just add a bomb to that random cell and do this for all bombs
			matrix[c1][c2] ="B";
			bombNum--;
		}

	}while(bombNum > 0);

	return matrix;
} // function for randomly distributing the bombs

vector<vector<string> > countingBomb(vector<vector<string> > &mat, vector<vector<string> > &tempMat, string press, vector<vector<string> > &finalMatrix, int rows, int cols){

	int count(0), stepNum(0);
	for(int i = 0 ; i < mat.size() ; i++){ 
		for(int j = 0  ; j < mat[0].size() ; j++){
			if(press != "1"){ //if press is not one 
				if(mat[i][j] != "B") //don't care about Bomb cells and look at neighboring cells
					bombLoop(i , j, mat, stepNum, count, finalMatrix, press, rows, cols); //body of this function is below it calculate the bomb # in neighboring cells
			}else{ //Press == 1
				bombLoop(i, j , tempMat, stepNum, count, finalMatrix, press, rows, cols);
			}
		}
	}
	return mat;
} // function for counting the neighboorhood bombs -- This function can also be written as void

void PrintPressOne(vector<vector<string> > &mat, vector<vector<string> > &xMat, int c1 , int c2){
	for(int x = 0; x< mat.size() ; x++){
		for(int y = 0; y< mat[0].size(); y++){
			if(y == 0){
				if(x == c1 && y == c2){
					cout <<mat[c1][c2];
				}else{
					cout << xMat[x][y];
				}
			}else{ //y != 0
				if(x == c1 && y == c2){
					cout << setw(4) << mat[c1][c2];
				}else{
					cout << setw(4) << xMat[x][y];
				}
			}
		}
		cout << endl;
	}
} // Print function for option 1 //This function displays multiple axis matrixes

void bombLoop(int i, int j, vector<vector<string> > &mat, int stepNum, int count, vector<vector<string> > &finalMatrix, string press, int rows, int cols){
	//In this function the loop is turning around each cell and find how much bomb exist in neighboring cells
	int x(i) , y(j);  //2 NEW variable for hold the initial coordinates
	if((x >= 0) && ( x < mat.size()) && (y >= 0) && (y < mat[0].size())){
		//mechanism should work like this: 2 DOWN 2 LEFT 2 UP 2 RIGHT
		//(0,0) --> (0,1), (1,1) --> (1,0), (1,-1) == -1 cannot happen thats' why this function should terminate the first step at that point
		if((x == 0) || y == 0 || x == mat.size()-1 || y == mat[0].size()-1){  //EDGES && L R U D
			count = 0;
			stepNum = 0; 
			if(x == 0 && y == 0){ //CONTROLING THE EDGES --> In edges only 3 neighboring cell taken into account for instance for this case (0,0) --> (1,0), (0,1) & (1,1) is taken into account
				stepNum = 0;
				y = y+1;
				while(stepNum < 2){
					if(mat[x][y] == "B") //If there is a bomb in given cell 
						count++; //Increment bomb count for that cell
					stepNum++; //the incremention DETERMINES how much CELL should be take into acount in particular way
					x++; //Increase given axes like this for particular loop at every step and use this combination for each adjacent cells
				}
				x--; //In some states we decrement the our axis in order to stay on neighboring cells
				stepNum = 0;
				while(stepNum < 1){  //Same algorithm above works for below parts as well
					y--;
					if(mat[x][y] == "B")
						count++;
					stepNum++;
				}
				fillingMatrix(i, j, mat, finalMatrix,press, count);
			}else if(x == 0 && y == mat[0].size() - 1){ //Right edge
				y = y-1;
				stepNum = 0;
				while(stepNum < 2){
					if(mat[x][y] == "B")
						count++;
					stepNum++;
					x++;
				}
				x--;
				stepNum = 0;
				while(stepNum < 1){
					y++;
					if(mat[x][y] == "B")
						count++;
					stepNum++;
				}
				fillingMatrix(i, j, mat, finalMatrix,press, count);
			}else if(x == mat.size() -1 && y == 0){ //Left bottom edge
				x = x-1;
				stepNum = 0;
				while(stepNum < 2){
					if(mat[x][y] == "B")
						count++;
					stepNum++;
					y++;
				}
				y--;
				stepNum = 0;
				while(stepNum < 1){
					x++;
					if(mat[x][y] == "B")
						count++;
					stepNum++;
				}
				fillingMatrix(i, j, mat, finalMatrix,press, count);
			}else if(x == mat.size() -1 && y == mat[0].size() - 1){ //Right bottom edge
				x = x-1;
				stepNum = 0;
				while(stepNum < 2){
					if(mat[x][y] == "B")
						count++;
					stepNum++;
					y--;
				}
				stepNum = 0;
				y++;
				while(stepNum < 1){
					x++;
					if(mat[x][y] == "B")
						count++;
					stepNum++;
				}
				fillingMatrix(i, j, mat, finalMatrix,press, count);
			}else{ // CALCULATE THE # OF BOMBS AT THE LEFT RIGHT BOTTOM AND UPPER PARTS EXCEPT EDGES
				if(x == 0){
					stepNum = 0;
					y = y+1;
					while(stepNum < 2){
						if(mat[x][y] == "B")
							count++;
						stepNum++;
						x++;
					}
					x--;
					stepNum = 0;
					while(stepNum < 2){
						y--;
						if(mat[x][y] == "B")
							count++;
						stepNum++;
					}
					stepNum = 0;
					while(stepNum < 1){
						x--;
						if(mat[x][y] == "B")
							count++;
						stepNum++;
					}
					fillingMatrix(i, j, mat, finalMatrix,press, count);
				}else if(y == 0){
					stepNum = 0;
					x = x-1;
					while(stepNum<2){
						if(mat[x][y] == "B")
							count++;
						stepNum++;
						y++;
					}
					y--;
					stepNum = 0;
					while(stepNum < 2){
						x++;
						if(mat[x][y] == "B")
							count++;
						stepNum++;
					}
					stepNum = 0;
					while(stepNum < 1){
						y--;
						if(mat[x][y] == "B")
							count++;
						stepNum++;
					}
					fillingMatrix(i, j, mat, finalMatrix,press, count);
				}else if(x == mat.size() - 1){
					y = y-1;
					while(stepNum < 2){
						if(mat[x][y] == "B")
							count++;
						stepNum++;
						x--;
					}
					stepNum= 0;
					x++;
					while(stepNum < 2){
						y++;
						if(mat[x][y] == "B")
							count++;
						stepNum++;
					}
					stepNum= 0;
					while(stepNum < 1){
						x++;
						if(mat[x][y] == "B")
							count++;
						stepNum++;
					}
					fillingMatrix(i, j, mat, finalMatrix,press, count);
				}else{  //y = mat[0].size() - 1
					x = x -1;
					while(stepNum < 2){
						if(mat[x][y] == "B")
							count++;
						stepNum++;
						y--;
					}
					y++;
					stepNum = 0;
					while(stepNum < 2){
						x++;
						if(mat[x][y] == "B")
							count++;
						stepNum++;
					}
					stepNum = 0;
					while(stepNum < 1){
						y++;
						if(mat[x][y] == "B")
							count++;
						stepNum++;
					}
					fillingMatrix(i, j, mat, finalMatrix,press, count);
				}
			}
		}else{ //middle part of matrix  *****WORKING****** ----> THE INNER PARTS
			count = 0;
			stepNum = 0;
			y = y+1;
			while(x < mat.size() && stepNum < 2){
				if(mat[x][y] == "B")
					count++;
				stepNum++;
				x++;
			}
			x--;
			stepNum = 0;
			while(y > 0 && stepNum < 2){
				y--;
				if(mat[x][y] == "B")
					count++;
				stepNum++;
			}
			stepNum = 0;
			while(x > 0 && stepNum < 2){
				x--;
				if(mat[x][y] == "B")
					count++;
				stepNum++;
			}
			stepNum = 0;
			while(y < mat[0].size() && stepNum < 2){
				y++;
				if(mat[x][y] == "B")
					count++;
				stepNum++;
			}
			stepNum = 0;
			fillingMatrix(i, j, mat, finalMatrix,press, count);
		}
	}
} //most important function that calculating the total number of bombs in the neigboors of cells and assigning counts to these cells

void fillingMatrix(int i , int j, vector<vector<string> >&mat, vector<vector<string> >&finalMat , string press, int count){
	if(press == "1"){
		finalMat[i][j] = tostring(count);
	}else{
		mat[i][j] = tostring(count);
	}
}  // This function fills the matrixes in the bombloop function according to the press option

void SingleRowCol(vector<vector<string> > &mat , vector<vector<string> > &finalMat, string press, int row, int col){
	int count(0);
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			if(row == 1){
				if(press != "1"){  //if press is not one 
					if(mat[i][j] != "B"){ //Again just ignore bombs and count cells not including bomb
						countingFuncForSingleRow(j, i, count, row, col, press, mat, finalMat); //This function counting the number of bombs in adjacent cells for single row matrixes--> Body of this function is below
					}
				}else{ //press is 1
					countingFuncForSingleRow(j, i, count, row, col, press, mat, finalMat);
				}
			}else if(col == 1){
				if(press != "1"){
					if(mat[i][j] != "B"){
						countingFuncForSingleCol(i, j, count, row, col, press, mat, finalMat); //This function counting the number of bombs in adjacent cells for single column matrixes--> Body of this function is below
					}
				}else{ //if press option is 1
					countingFuncForSingleCol(i, j, count, row, col, press, mat, finalMat);
				}
			}
		}
	}
}

void countingFuncForSingleRow(int j,int i, int count, int row, int col,string press, vector<vector<string> > &mat, vector<vector<string> > &finalMat){
	if(j == 0){ //Left edge
		if(mat[i][j+1] == "B"){ //looks for consecutive cells 
			count++;
		}
		fillingMatrix(i, j, mat, finalMat,press, count);
		count = 0;
	}else if(j == col - 1){ //Right edge
		if(mat[i][j-1] == "B"){ //looks for consecutive cells (i.e. previous one for this case)
			count++;
		}
		fillingMatrix(i, j, mat, finalMat,press, count);
		count = 0;
	}else{ //middle part of single row
		if(mat[i][j+1] == "B"){ //Looks for consecutive parts and if there is a bomb
			count++;  //increment the count of bombs
		}if(mat[i][j-1] == "B"){
			count++; //increment the #
		}
		fillingMatrix(i, j, mat, finalMat,press, count); //This function fills the matrixes with given counts as it did in bombLoop function
		count = 0; //equalize count to 0 for successive operations
	}
} //This one calculate the # of bombs in neighboring cells for the matrixes with single row (row # = 1)

void countingFuncForSingleCol(int i,int j, int count, int row, int col,string press, vector<vector<string> > &mat, vector<vector<string> > &finalMat){
	if(i == 0){ //Upper edge
		if(mat[i+1][j] == "B"){ //Look for the consecutive parts of matrix
			count++; //Increment accordingly 
		}
		fillingMatrix(i, j, mat, finalMat,press, count);
		count = 0;
	}else if(i == row - 1){ //Lower edge
		if(mat[i-1][j] == "B"){
			count++;
		}
		fillingMatrix(i, j, mat, finalMat,press, count);
		count = 0;
	}else{ // middle part of the single col matrix
		if(mat[i+1][j] == "B"){
			count++;
		}if(mat[i-1][j] == "B"){
			count++;
		}
		fillingMatrix(i, j, mat, finalMat,press, count);
		count = 0;
	}
}