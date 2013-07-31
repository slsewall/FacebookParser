#include "json.h"

#include <iostream>
#include <fstream>
#include <streambuf>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <time.h>
#include <string>
#include <vector>
#include "Person.h"
#include "arrayList.h"
#include "chain.h"
#include "linearList.h"
#include "hashTable.h"

using namespace std;

int main(int argc, char* argv[]) {
	//time_t elapsedTime, startTime;
	clock_t initialT;
	bool tActive = false;
	string fileName = "facebook.txt";
	int selectionNumber = 0; //data type, 1 is arraylist, 2 is chain, 3 is hashtable 
	int selectionTwo = 0; // sort type 
	int selectionThree = 0; //criteria for sorting
	int dexArg = 4;
	if (argc > 1){
		fileName = argv[1];
		selectionNumber = atoi(argv[2]);
		selectionTwo = atoi(argv[3]);
	}
	else{
	cout << "Please enter a filename: " << endl;
	cin >> fileName;
	cout << endl;
	cout << "Please choose a data structure:" << endl;
	cout << "	1. Arraylist" << endl << "	2. Chain" << endl <<"	3. Hashtable" << endl; 
	//Both of your list structures should extend an abstract class that includes reverse, and insertion sort.
	cin >> selectionNumber;
	cout << endl;
	}
	ifstream t(fileName.c_str());	
	//t.open(fileName.c_str());
	//double tTi;
	string str((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());
	
	json_value data = * json_parse(str.c_str());
	
	json_value *list = data.u.object.values[0].value;
	int length = list->u.array.length;
	int ij = 0;
	string tBir = "Temp";
	string tFir = "Temp";
	string tLast = "Temp";
	string tHometown = "Temp";
	json_value **array = data.u.object.values[0].value->u.array.values;
	if(selectionNumber == 1){ //Arraylist
		arrayList<Person> p(1);
		for (int i = 0; i < length; i++) { //this should be going through the length of the whole document I guess?
			for (int j = 0; (j<(array[i]->u.object.length)); j++) {
				if (!strcmp(array[i]->u.object.values[j].name, "birthday")) {
					//cout << "Birthday: " << array[i]->u.object.values[j].value->u.string.ptr;
					tBir = array[i]->u.object.values[j].value->u.string.ptr;
				} else if (!strcmp(array[i]->u.object.values[j].name, "first_name") && array[i]->u.object.values[j].value->type != json_null) {
					//cout << " Name: " << array[i]->u.object.values[j].value->u.string.ptr;
					tFir = array[i]->u.object.values[j].value->u.string.ptr;
				} else if (!strcmp(array[i]->u.object.values[j].name, "last_name") && array[i]->u.object.values[j].value->type != json_null) {
					//cout << " " << array[i]->u.object.values[j].value->u.string.ptr;
					tLast = array[i]->u.object.values[j].value->u.string.ptr;
				} else if (!strcmp(array[i]->u.object.values[j].name, "hometown") && array[i]->u.object.values[j].value->type != json_null) {
					for(int k = 0; k < (array[i]->u.object.values[j].value->u.object.length); k++){
						if (!strcmp(array[i]->u.object.values[j].value->u.object.values[k].name, "name") && array[i]->u.object.values[j].value->u.object.values[k].value->type != json_null) {
							//cout << " Hometown: " << array[i]->u.object.values[j].value->u.object.values[k].value->u.string.ptr;
							tHometown = array[i]->u.object.values[j].value->u.object.values[k].value->u.string.ptr;
						}
					}
					
				}
				if((tHometown.compare("Temp") != 0)&&(tBir.compare("Temp") != 0)&&(tFir.compare("Temp") != 0)&&(tLast.compare("Temp") != 0)){
					Person xyz(tBir, tFir, tLast, tHometown);
					p.insert(0, xyz);
					tBir = "Temp";
					tFir = "Temp";
					tLast = "Temp";
					tHometown = "Temp";
				}
			}
			
		}
		if(argc < 2){
		cout << "Please choose a criteria:" << endl;
		cout << "	1. Name" << endl << "	2. Birthday" << endl <<"	3. Location" << endl;
		cin >> selectionTwo;
		}
		bool activeLoop= true;
		while(activeLoop){
			if(argc > 1){
				selectionThree = atoi(argv[dexArg]);
				dexArg++;
				if(argc < dexArg){
					return 0;
					}
			}
			else if(argc < 2){	
			cout << endl << "Please choose a command: " << endl << "	1. Reverse List" << endl << " 	2. Sort using insertion sort" << endl << "	3. Print out number of accesses and execution time for last operation" << endl << "	4. Print out list" << endl << "	5. Exit" << endl;
			cin >> selectionThree; 
			}
			if(selectionThree == 1){
				//time (&startTime);
				initialT = clock();		
				for(int x = 0; x < 101; x++){
					p.reverse();
				}
				initialT = (clock() - initialT)/101;
				tActive = true;
				//tTi = difftime(elapsedTime, startTime);
				
			} else if(selectionThree == 2){
				//time (&startTime);
				initialT = clock();
				for(int x = 0; x < 101; x++){
					p.insertionSort(selectionTwo);
					}
				initialT = (clock() - initialT)/101;				
				//time (&elapsedTime);
				tActive = true;
				//tTi = difftime(elapsedTime, startTime);
			}
			else if(selectionThree == 3){
				//print out number of accesses + execution time of last operation
				if(tActive){
					cout << "Access Count: " << p.getAccessCountForLastOperation() << " execution time in seconds: " << setprecision (30) << ((float)initialT)/CLOCKS_PER_SEC << endl;
				}
				else{
					cout << "Time and Access Count are not availible until an operation has been executed. Please execute an operation." << endl;
				}
			}
			else if(selectionThree == 4){
				//print out 
				if(selectionTwo ==1){
					for(int ii = 1; ii < p.size(); ii++){
						cout << p.get(ii).getFirstName() << " " << p.get(ii).getLastName() << endl;
					}
				}
				else if(selectionTwo == 2){
					for(int ii = 1; ii < p.size(); ii++){
						cout << p.get(ii).getFirstName() << " " << p.get(ii).getLastName() << " (" << p.get(ii).getBirthDay() << ")" << endl;
					}
				}
				else{
					for(int ii = 1; ii < p.size(); ii++){
						cout << p.get(ii).getFirstName() << " " << p.get(ii).getLastName() << " (" << p.get(ii).getHomeTown() << ")" << endl;
					}
				}
			}
			else if(selectionThree == 5)
			{
				activeLoop = false;
				return 0;
			}
			else{ cout << "invalid entry, try again" << endl; }
		}
	}
	else if(selectionNumber == 2){    
		chain<Person> ch(1);
	//This is the Chain
		for (int i = 0; i < length; i++) { //this should be going through the length of the whole document I guess?
			for (int j = 0; j < array[i]->u.object.length; j++) {
				if (!strcmp(array[i]->u.object.values[j].name, "birthday")) {
					//cout << "Birthday: " << array[i]->u.object.values[j].value->u.string.ptr;
					tBir = array[i]->u.object.values[j].value->u.string.ptr;
				} else if (!strcmp(array[i]->u.object.values[j].name, "first_name") && array[i]->u.object.values[j].value->type != json_null) {
					//cout << " Name: " << array[i]->u.object.values[j].value->u.string.ptr;
					tFir = array[i]->u.object.values[j].value->u.string.ptr;
				} else if (!strcmp(array[i]->u.object.values[j].name, "last_name") && array[i]->u.object.values[j].value->type != json_null) {
					//cout << " " << array[i]->u.object.values[j].value->u.string.ptr;
					tLast = array[i]->u.object.values[j].value->u.string.ptr;
				} else if (!strcmp(array[i]->u.object.values[j].name, "hometown") && array[i]->u.object.values[j].value->type != json_null) {
					for(int k = 0; k < (array[i]->u.object.values[j].value->u.object.length); k++){
						if (!strcmp(array[i]->u.object.values[j].value->u.object.values[k].name, "name") && array[i]->u.object.values[j].value->u.object.values[k].value->type != json_null) {
							//cout << " Hometown: " << array[i]->u.object.values[j].value->u.object.values[k].value->u.string.ptr;
							tHometown = array[i]->u.object.values[j].value->u.object.values[k].value->u.string.ptr;
						}
					}
					
				}
			}
			if((tHometown.compare("Temp") != 0)&&(tBir.compare("Temp") != 0)&&(tFir.compare("Temp") != 0)&&(tLast.compare("Temp") != 0)){
				Person xyz(tBir, tFir, tLast, tHometown);
				ch.insert(0, xyz);
				tBir = "Temp";
				tFir = "Temp";
				tLast = "Temp";
				tHometown = "Temp";
			}
		}
		if(argc < 2){
			cout << "Please choose a criteria:" << endl;
			cout << "	1. Name" << endl << "	2. Birthday" << endl <<"	3. Location" << endl;
			cin >> selectionTwo;
			cout << endl;
			}
		bool activeLoop= true;
		while(activeLoop){
			if(argc > 1){
				selectionThree = atoi(argv[dexArg]);
				dexArg++;
				if(argc < dexArg){
					return 0;
					}
			}
			else if(argc < 2){
				cout << endl << "Please choose a command: " << endl << "	1. Reverse List" << endl << " 	2. Sort using insertion sort" << endl << "	3. Print out number of accesses and execution time for last operation" << endl << "	4. Print out list" << endl << "	5. Exit" << endl;
				cin >> selectionThree; 
			}
			if(selectionThree == 1){
				initialT = clock();
				for(int x = 0; x < 101; x++){
					ch.reverse();
				}
				initialT = (clock() - initialT)/101;	
				tActive = true;
			} else if(selectionThree == 2){
				initialT = clock();	
				for(int x = 0; x < 101; x++){
					ch.insertionSort(selectionTwo);
				}
				initialT = (clock() - initialT)/101;
				tActive = true;
			}
			else if(selectionThree == 3){
				//print out number of accesses + execution time of last operation
				if(tActive){
					cout << "Access Count: " << ch.getAccessCountForLastOperation() << " execution time in seconds: " << setprecision (15) << ((float)initialT)/CLOCKS_PER_SEC<< endl;
				}
				else{
					cout << "Time and Access Count are not availible until an operation has been executed. Please execute an operation." << endl;
				}
			}
			else if(selectionThree == 4){
				//print out 
				ch.printChain(cout, selectionTwo);
			}
			else if(selectionThree == 5)
			{
				activeLoop = false;
				return 0;
			}
			else{ cout << "invalid entry, try again" << endl; }
		}
	}
	else if(selectionNumber == 3){    //This is the Hashtable
		
		hashTable<string, vector<Person> > z(1001);
		pair<string, Person> pai;
		if(argc < 2){
			cout << "Please choose a criteria:" << endl;
			cout << "	1. Name" << endl << "	2. Birthday" << endl <<"	3. Location" << endl;
			cin >> selectionTwo;
			cout << endl;
			}
		for (int i = 0; i < length; i++) { //this should be going through the length of the whole document I guess?
			for (int j = 0; j < array[i]->u.object.length; j++) {
				if (!strcmp(array[i]->u.object.values[j].name, "birthday")) {
					//cout << "Birthday: " << array[i]->u.object.values[j].value->u.string.ptr;
					tBir = array[i]->u.object.values[j].value->u.string.ptr;
				} else if (!strcmp(array[i]->u.object.values[j].name, "first_name") && array[i]->u.object.values[j].value->type != json_null) {
					//cout << " Name: " << array[i]->u.object.values[j].value->u.string.ptr;
					tFir = array[i]->u.object.values[j].value->u.string.ptr;
				} else if (!strcmp(array[i]->u.object.values[j].name, "last_name") && array[i]->u.object.values[j].value->type != json_null) {
					//cout << " " << array[i]->u.object.values[j].value->u.string.ptr;
					tLast = array[i]->u.object.values[j].value->u.string.ptr;
				} else if (!strcmp(array[i]->u.object.values[j].name, "hometown") && array[i]->u.object.values[j].value->type != json_null) {
					for(int k = 0; k < (array[i]->u.object.values[j].value->u.object.length); k++){
						if (!strcmp(array[i]->u.object.values[j].value->u.object.values[k].name, "name") && array[i]->u.object.values[j].value->u.object.values[k].value->type != json_null) {
							//cout << " Hometown: " << array[i]->u.object.values[j].value->u.object.values[k].value->u.string.ptr;
							tHometown = array[i]->u.object.values[j].value->u.object.values[k].value->u.string.ptr;
						}
					}
					
				}
			}
			if((tHometown.compare("Temp") != 0)&&(tBir.compare("Temp") != 0)&&(tFir.compare("Temp") != 0)&&(tLast.compare("Temp") != 0)){
				Person xyz(tBir, tFir, tLast, tHometown);				
				//vector<Person> fri;
				//fri.push_back(xyz);
				if(selectionTwo == 1){ //name
					pai.first = tLast;
				}
				else if(selectionTwo == 2){ // birthday
					pai.first = tBir;
				}
				else if(selectionTwo == 3){ // location
					pai.first = tHometown;
				}
				pai.second = xyz;
				z.insert(pai);
				tBir = "Temp";
				tFir = "Temp";
				tLast = "Temp";
				tHometown = "Temp";
			}
		}
		string selectionFour;
		if(argc > 1){
			selectionFour = argv[4];
		}
		else{
			cin.clear();
			cin.sync();
			cout << "Enter a value for the selected criteria: " << endl;
			getline(cin, selectionFour);
			getline(cin, selectionFour);
		}
		initialT = clock();	
		vector<Person> printing = z.find(selectionFour)->second;
		initialT = (clock() - initialT);
		if(printing.empty() == false){
		
			for(int o = 0; o < printing.size(); o++){
				Person tempP = printing.at(o);
				cout << tempP.getFirstName() << " " << tempP.getLastName() << endl;
			}
			cout << "Access Count: " << z.getAccessCountForLastOperation() << " execution time in seconds: " << setprecision (15) << ((float)initialT)/CLOCKS_PER_SEC<< endl;
		}
		
	}
	else{
		cout << "Your selection was not valid" << endl;
	}
	
	
	return 0;
}
