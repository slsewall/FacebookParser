#include <iostream>
#include "Person.h"
#include <string>

using namespace std;

Person::Person(){
	birthDay = "None";
	firstName = "None";
	lastName = "None";
	homeTown = "None";
}

Person::Person(string bD, string fN, string lN, string hT)
{
	this->birthDay = bD;
	this->firstName = fN;
	this->lastName = lN;
	this->homeTown = hT;
	
}

string Person::getBirthDay()
{
		return birthDay;
}
string Person::getFirstName()
{
		return firstName;
}
string Person::getLastName()
{
		return lastName;
}
string Person::getHomeTown()
{
		return homeTown;
}

int Person::Compare(Person& d, int selection){
	if(selection == 1){
		return lastName.compare(d.lastName);
	}
	else if(selection == 2){
		return birthDay.compare(d.birthDay);
	} 
	else if(selection == 3){
		return homeTown.compare(d.homeTown);
	}
	else{
		return -1;
	}
}


ostream& operator<<(ostream& out, const Person& x)
	{return out;}
