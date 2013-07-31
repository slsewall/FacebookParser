// this is the header file for the Person class
#ifndef Person_
#define Person_

#include <string>

using namespace std;
class Person
{
public: 
	string birthDay;
	string firstName;
	string lastName;
	string homeTown;
	Person *next;
	Person();
	Person(string bD, string fN, string lN, string hT);
	string getBirthDay();
	string getFirstName();
	string getLastName();
	string getHomeTown();
	int Compare(Person& d, int selection);
	friend ostream& operator<<(ostream& out, const Person& x);
	
};



#endif