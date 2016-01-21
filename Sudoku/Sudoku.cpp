////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sudoku Using Backtracking+Forward_checking+MRV
// Design & Programming by Mojtaba Valipour @ CyberHands - JSU 
// 1.11.1393 - 21.01.2015
// Online CV: ir.linkedin.com/in/mojtabavalipour
// cyberhands.org	- CyberHands Research Team
// cpna.ir	- CyberPress News Agency
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Sudoku.cpp : main project file.

#include "stdafx.h"
#include <iostream>			//Printf and Functions that work with input/output stream
#include <list>

using namespace System;
using namespace std;

struct Var{					//Variable Data Type for Sudoku 
	int value = 0;
	list<int> Domain;
};


const int size = 9;			//Size of Sudoku Table n^2 * n^2 - n=3 is a standard sudoku
Var Sudoku[size][size];		//Sudoku Table

void Print_Sudoku(){		//Showing Table in Output for solving and debugging
	printf("\n");

	//Print First Line +---------------------------------+
	printf("+");
	for (int i = 0,j=0; i < size; i++){
		if (j>=3){
			printf(" ");
			j = 0;
		}
		printf("--");
		j++;
	}
	printf("-+\n");
	
	//Print values
	for (int i = 0, Sep_Counter_Row=0; i < size; i++){			//Rows Counter
		if (Sep_Counter_Row >= 3){
			Sep_Counter_Row = 0;
			//Print Separator Line +---------------------------------+
			printf("+");
			for (int i = 0, j = 0; i < size; i++){
				if (j >= 3){
					printf(" ");
					j = 0;
				}
				printf("--");
				j++;
			}
			printf("-+\n");
		}
		for (int j = 0,Sep_Counter_Col=0; j < size; j++){		//Column Counter
			if (Sep_Counter_Col >= 3){
				Sep_Counter_Col = 0;
				printf(" |");
			}
			printf(" %d",Sudoku[i][j].value);
			Sep_Counter_Col++;
		}
		printf("\n");
		Sep_Counter_Row++;
	}
	//Print End Line +---------------------------------+
	printf("+");
	for (int i = 0, j = 0; i < size; i++){
		if (j >= 3){
			printf(" ");
			j = 0;
		}
		printf("--");
		j++;
	}
	printf("-+");

	printf("\n");
}

//void Sudoku_Maker(){		//General Soduko Problem Generator
//
//}
void Assign_Cell(int i, int j, int value){			//Assign something fixed to cell
	Sudoku[i][j].value = value;
	Sudoku[i][j].Domain.clear();					//Clear everything in Domain
	Sudoku[i][j].Domain.push_back(value);
}
void Sudoku_One_Example(){			//Example acquired from my Mentor's class booklet(m_mousazadeh(at)yahoo(dot)com)
	for (int i = 0; i < size; i++){			//Add Domain 1,2,3,4,5,6,7,8,9 to all cell in Table                         
		for (int j = 0; j < size; j++){
			for (int k = 1; k <= size;k++)				
				Sudoku[i][j].Domain.push_back(k);
		}
	}

	//Example Number 2 - Harder
	//Assign_Cell(0, 5, 2);
	//Assign_Cell(1, 0, 5);
	//Assign_Cell(1, 2, 6);
	//Assign_Cell(1, 3, 7);
	//Assign_Cell(1, 8, 9);
	//Assign_Cell(2, 0, 1);
	//Assign_Cell(2, 3, 4);
	//Assign_Cell(2, 4, 9);
	//Assign_Cell(3, 0, 8);
	//Assign_Cell(3, 2, 1);
	//Assign_Cell(3, 7, 4);
	//Assign_Cell(4, 1, 2);
	//Assign_Cell(4, 2, 9);
	//Assign_Cell(4, 6, 5);
	//Assign_Cell(4, 7, 3);
	//Assign_Cell(5, 1, 7);
	//Assign_Cell(5, 6, 8);
	//Assign_Cell(5, 8, 6);
	//Assign_Cell(6, 4, 8);
	//Assign_Cell(6, 5, 9);
	//Assign_Cell(6, 8, 4);
	//Assign_Cell(7, 0, 9);
	//Assign_Cell(7, 5, 4);
	//Assign_Cell(7, 6, 6);
	//Assign_Cell(7, 8, 1);
	//Assign_Cell(8, 3, 5);

	//Example Number One
	Assign_Cell(0, 2, 3);
	Assign_Cell(0, 4, 2);
	Assign_Cell(0, 6, 6);
	Assign_Cell(1, 0, 9);
	Assign_Cell(1, 3, 3);
	Assign_Cell(1, 5, 5);
	Assign_Cell(1, 8, 1);
	Assign_Cell(2, 2, 1);
	Assign_Cell(2, 3, 8);
	Assign_Cell(2, 5, 6);
	Assign_Cell(2, 6, 4);
	Assign_Cell(3, 2, 8);
	Assign_Cell(3, 3, 1);
	Assign_Cell(3, 5, 2);
	Assign_Cell(3, 6, 9);
	Assign_Cell(4, 0, 7);
	Assign_Cell(4, 8, 8);
	Assign_Cell(5, 2, 6);
	Assign_Cell(5, 3, 7);
	Assign_Cell(5, 5, 8);
	Assign_Cell(5, 6, 2);
	Assign_Cell(6, 2, 2);
	Assign_Cell(6, 3, 6);
	Assign_Cell(6, 5, 9);
	Assign_Cell(6, 6, 5);
	Assign_Cell(7, 0, 8);
	Assign_Cell(7, 3, 2);
	Assign_Cell(7, 5, 3);
	Assign_Cell(7, 8, 9);
	Assign_Cell(8, 2, 5);
	Assign_Cell(8, 4, 1);
	Assign_Cell(8, 6, 3);
}		

int Select_Unassigned_Variable(){
	int result = -1;
	//Main Code of this functin is here
	//MRV Algorithm
	int i_best=0, j_best=0;
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size;j++){
			if (Sudoku[i][j].value == 0){		//Check if Unassigned block
				if (Sudoku[i][j].Domain.size() <= Sudoku[i_best][j_best].Domain.size()){
					i_best = i;
					j_best = j;
				}
			}
		}
	}
	result = i_best * 10 + j_best;
	return result;
}

bool is_Assignment_Complete(list<int> Assignments){
	bool result = false;
	//Main Code of this functin is here
	if (Assignments.size()==size*size){		//Means All block of tables is assigned to somethine else than 0
		return true;
	}
	return result;
}
bool is_Consistent(int value, int i, int j){			//Check if changes are satisficated constraints
	bool Result = true;
	//Main Code is here
	//Check if Satisfied Rows Constraints
	for (int k = 0; k < size; k++){
		if (k == j){
			continue;
		}
		if (Sudoku[i][k].value == value){
			return false;
		}
	}
	//Check if Satisfied Collumns Constraints
	for (int k = 0; k < size; k++){
		if (k == i){
			continue;
		}
		if (Sudoku[k][j].value == value){
			return false;
		}
	}
	//Check if Satisfied Box Constraints
	int box_number_i = i / 3;			//Determin which box our cell are there
	int box_number_j = j / 3;	
	int start_i = 3 * box_number_i;		//Determine the first index of our cell	in the box
	int start_j = 3 * box_number_j;
	int end_i = start_i + 2;			//Determine the end index of our cell in the box
	int end_j = start_j + 2;
	for (int i_temp = start_i; i_temp <=end_i ; i_temp++){
		for (int j_temp = start_j; j_temp <= end_j; j_temp++){
			if (i_temp == i && j_temp == j){
				continue;
			}
			if (Sudoku[i_temp][j_temp].value == value)
				return false;
		}
	}
	return Result;						//Return true because it is consistent
}
int condition = 0;
void ForwardChecking(int i, int j, int value){
	int box_number_i = i / 3;			//Determin which box our cell are there
	int box_number_j = j / 3;
	int start_i = 3 * box_number_i;		//Determine the first index of our cell	in the box
	int start_j = 3 * box_number_j;
	int end_i = start_i + 2;			//Determine the end index of our cell in the box
	int end_j = start_j + 2;
	for (int i_temp = start_i; i_temp <= end_i; i_temp++){
		for (int j_temp = start_j; j_temp <= end_j; j_temp++){
			if (i_temp == i && j_temp == j){			//Don't change the cell that change others
				continue;
			}
			if (Sudoku[i_temp][j_temp].value == 0){
				Sudoku[i_temp][j_temp].Domain.remove(value);
				Sudoku[i_temp][j_temp].Domain.sort();
			}
		}
	}
	////Change Domain of Collumns Cells
	//for (int k = 0; k < size; k++){
	//	if (k >= start_i && k <= end_i){
	//		continue;
	//	}
	//	if (k == i){			//Don't change the cell that change others
	//		continue;
	//	}
	//	if (Sudoku[k][j].value == 0){
	//		Sudoku[k][j].Domain.remove(value);
	//		Sudoku[k][j].Domain.sort();
	//		//printf("\ni=%d,j=%d,value=%d,Change in: %d\n", i, j, value, k * 10 + j);
	//	}
	//}
	////Change Domain of Rows Cells 
	//for (int k = 0; k < size; k++){
	//	if (k >= start_j && k <= end_j){
	//		continue;
	//	}
	//	if (k == j){			//Don't change the cell that change others
	//		continue;
	//	}
	//	if (Sudoku[i][k].value == 0){
	//		Sudoku[i][k].Domain.remove(value);
	//		Sudoku[i][k].Domain.sort();
	//	}
	//}
}
void ReverseForwardChecking(int i, int j, int value){
	//Change Domain of Rows Cells 
	for (int k = 0; k < size; k++){
		if (k == j){			//Don't change the cell that change others
			continue;
		}
		if (Sudoku[i][k].value == 0){
			Sudoku[i][k].Domain.remove(value);
			Sudoku[i][k].Domain.push_back(value);
		}
	}
	//Change Domain of Collumns Cells
	for (int k = 0; k < size; k++){
		if (k == i){			//Don't change the cell that change others
			continue;
		}
		if (Sudoku[k][j].value == 0){
			Sudoku[k][j].Domain.remove(value);
			Sudoku[k][j].Domain.push_back(value);
		}
	}
	//Change Domain of Box Cells
	int box_number_i = i / 3;			//Determin which box our cell are there
	int box_number_j = j / 3;
	int start_i = 3 * box_number_i;		//Determine the first index of our cell	in the box
	int start_j = 3 * box_number_j;
	int end_i = start_i + 2;			//Determine the end index of our cell in the box
	int end_j = start_j + 2;
	for (int i_temp = start_i; i_temp <= end_i; i_temp++){
		for (int j_temp = start_j; j_temp <= end_j; j_temp++){
			if (i_temp == i && j_temp == j){			//Don't change the cell that change others
				continue;
			}
			if (Sudoku[i_temp][j_temp].value == 0){
				Sudoku[i_temp][j_temp].Domain.remove(value);
				Sudoku[i_temp][j_temp].Domain.push_back(value);
			}
		}
	}
}
bool Backtrack(list<int> Assignments){			//Main Backtack Algoritm
		if (is_Assignment_Complete(Assignments) == true){
			Print_Sudoku();
			return true;	//For Finding more solutions
			//exit;			//For One Solution
		}
		int selected = Select_Unassigned_Variable();			//Strategy for choosing one unassigned Variable using MRV
		int i = selected / 10;
		int j = selected % 10;
		//printf("\ni=%d,j=%d,value=%d\n",i,j,Sudoku[i][j].value);		//For Debugging
		list<int>::iterator IT_Domain;
		IT_Domain = Sudoku[i][j].Domain.begin();
		list<int> Backup_Domain;
		for (int v = 0; v < Sudoku[i][j].Domain.size(); v++){					//Check Each Member of Domain
			int temp = *IT_Domain;
			if (is_Consistent(temp, i, j)){		//V is consistent
				Assignments.push_back(i * 10 + j); 
				//printf("\nij=%d, Value=%d\n",i*10+j,temp);
				Sudoku[i][j].value = temp;
				Backup_Domain.assign(Sudoku[i][j].Domain.begin(), Sudoku[i][j].Domain.end());			//Copy Domain
				//Reasoning such as forward checking will be here
				//bool is_Empty_Domain=
				ForwardChecking(i, j, temp);
				//if (!is_Empty_Domain){
				//	break;
				//}
				bool Result = false;
				Result = Backtrack(Assignments);
				if (Result == true){
					//Print_Sudoku(Sudoku_BackUP);				//For Debugging
					return Result;
				}
				//Restore Domain and Value before changes
				Assignments.remove(i * 10 + j);
				Sudoku[i][j].value = 0;
				Sudoku[i][j].Domain.assign(Backup_Domain.begin(), Backup_Domain.end());
				ReverseForwardChecking(i,j,temp);		//Recover Domain of Adjacency of our cell

			}
			if (IT_Domain != Sudoku[i][j].Domain.end()){
				IT_Domain++;
			}
			else{
				break;
			}
		}
	return false;
}
//bool Backtracking_search(list<int> Assignments, Var Sudoku[size][size]){
//	return Backtrack(Assignments,Sudoku);
//}
bool Sudoku_Agent(list<int> Assignments){		//Sudoku solver using Artificial Intelligence Algorithm such as Backtracking & MRV & Forward Checking
	return Backtrack(Assignments);
}
list<int>  Find_Assignments(list<int> Assignments){				//Assignemenets Finder for increasing generality and flexibility for future abilities in this program
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			if (Sudoku[i][j].value != 0){
				int Row_Col = i;
				Row_Col = Row_Col * 10 + j;
				Assignments.push_back(Row_Col);
			}
		}
	}
	return Assignments;
}
int main(array<System::String ^> ^args)
{
	Var Sudoku[size][size];
	printf("\nAn Example Sudoku Problem is\n");
	Sudoku_One_Example();
	Print_Sudoku();
	printf("\nSudoku Solving by Backtracking & MRV & Forward Checking\n");
	list<int> Assignments;
	Assignments=Find_Assignments(Assignments);
	bool Result = Sudoku_Agent(Assignments);
	//Print_Sudoku();
	printf("\nDesign & Programming by Mojtaba Valipour-CyberHands.org\n");
	system("PAUSE");
	return 0;
}
