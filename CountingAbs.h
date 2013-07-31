#ifndef CountingAbs_h
#define CountingAbs_h

// virtual members
#include <iostream>

using namespace std;

class CountingAbs
{
	public: 
		//virtual int add(int a, int b)= 0;
		virtual int getAccessCountForLastOperation() = 0;
		// should I have a get accesstime method?
		
};

#endif
