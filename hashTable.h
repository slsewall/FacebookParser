// hash table using linear open addressing and division
// implements dictionary methods other than erase

#ifndef hashTable_
#define hashTable_



#include <iostream>
#include "hash.h"  // mapping functions from string to nonnegative integer
#include "myExceptions.h"
#include <vector>
#include "Person.h"
#include <string>
#include "CountingAbs.h"

using namespace std;

template<class string, class E>
class hashTable
{
   public:
   
   int accessCount;
      hashTable(int theDivisor = 1001);
      ~hashTable(){delete [] table;}
		
      bool empty() const {return dSize == 0;}
      int size() const {return dSize;}
      pair<const string, E>* find(const string&);
      void insert(const pair<const string, Person>&);
      void output(ostream& out) const;
	  int getAccessCountForLastOperation() {return accessCount;}

   protected:
      int search(const string&);
      pair<const string, E>** table;  // hash table
      hash<string> hashIt;              // maps type string to nonnegative integer
      int dSize;                 // number of pairs in dictionary
      int divisor;               // hash function divisor
	  
};

template<class string, class E>
hashTable<string,E>::hashTable(int theDivisor)
{
	accessCount = 0;
   divisor = theDivisor;
   dSize = 0;
   // allocate and initialize hash table array
   table = new pair<const string, E>* [divisor];
   for (int i = 0; i < divisor; i++)
      table[i] = NULL;
}

template<class string, class E>
int hashTable<string,E>::search(const string& thestringey)
{// Search an open addressed hash table for a pair with key thestringey.
 // Return location of matching pair if found, otherwise return
 // location where a pair with key thestringey may be inserted
 // provided the hash table is not full.
   int i = hashIt(thestringey) % divisor;  // home bucket
   int j = i;    // start at home bucket
   do
   {
	accessCount++;
      if ((table[j] == NULL) || (table[j]->first == thestringey)){
         return j;
		}
      j = (j + 1) % divisor;  // next bucket
	  
   } while (j != i);          // returned to home bucket?
	
   return j;  // table full
}

template<class string, class E>
pair<const string,E>* hashTable<string,E>::find(const string& thestringey)
{
	// Return pointer to matching pair.
	// Return NULL if no matching pair.
	// search the table
	accessCount = 0;
	int b = search(thestringey);
	accessCount++;
   // see if a match was found at table[b]
   if (table[b] == NULL || table[b]->first != thestringey)
      return NULL;           // no match
	
   return table[b];  // matching pair
}

template<class string, class E>
void hashTable<string,E>::insert(const pair<const string, Person>& thePair)
{// Insert thePair into the dictionary. Overwrite existing
 // pair, if any, with same key.
 // Throw hashTableFull exception in case table is full.
   // search the table for a matching pair
   int b = search(thePair.first);
   // check if matching pair found
   if (table[b] == NULL)
   {
		vector<Person> fri; //E is Vector
		fri.push_back(thePair.second);
      // no matching pair and table not full
	  pair<string, E> temp;
	  //string re = thePair.first;
	  //temp.first = re;
	  temp.first = thePair.first;
	  temp.second = fri;
      table[b] = new pair<const string, E> (temp);
      dSize++;
   }
   else
   {// check if duplicate or table full
      if (table[b]->first == thePair.first)
      {// duplicate, change table[b]->second
         table[b]->second.push_back(thePair.second); //
		 dSize++;
      }
      else{ // table is full
		throw hashTableFull();
		 }
   }
}

template<class string, class E>
void hashTable<string,E>::output(ostream& out) const
{// Insert the hash table into the stream out.
   for (int i = 0; i < divisor; i++)
      if (table[i] == NULL)
         cout << "NULL" << endl;
      else
         cout << table[i]->first << " " << endl;
}

// overload <<
template <class string, class E>
ostream& operator<<(ostream& out, const hashTable<string,E>& x)
   {return out;}

#endif
