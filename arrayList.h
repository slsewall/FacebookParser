// array implementation of a linear list
// derives from abstract class linearList just to make sure
// all methods of the ADT are implemented
// USES STL ALGORITHMS TO SIMPLIFY CODE

#ifndef arrayList_
#define arrayList_

#include<iostream>
#include<sstream>
#include<string>
#include<algorithm>
#include<iterator>
#include<ostream>
#include "linearList.h"
#include "myExceptions.h"
#include "changeLength1D.h"
#include "SortingAbs.h"
#include "CountingAbs.h"

using namespace std;

template<class T>
class arrayList : public linearList<T>, SortingAbs<T>, CountingAbs
{
   public:
      // constructor, copy constructor and destructor
      arrayList(int initialCapacity = 10);
      arrayList(const arrayList<T>&);
      ~arrayList() {delete [] element;}

      // ADT methods
      bool empty() const {return listSize == 0;}
      int size() const {return listSize;}
      T& get(int theIndex) const;
      int indexOf(const T& theElement) const;
      void erase(int theIndex);
      void insert(int theIndex, const T& theElement);
      void output(ostream& out) const;
	// Methods from Sorting Abs
	  //void reverse(T* first, T* last);
	  void reverse();
	  void insertionSort(int selection);
	  void insertS(T n,int i, int selec);
	  // from counting
	  int getAccessCountForLastOperation() {return accessCount;}
      // additional method
      int capacity() const {return arrayLength;}

   protected:
      void checkIndex(int theIndex) const;
            // throw illegalIndex if theIndex invalid
      T* element;            // 1D array to hold list elements
      int arrayLength;       // capacity of the 1D array
      int listSize;          // number of elements in list
	  int accessCount;
};

template<class T>
arrayList<T>::arrayList(int initialCapacity)
{// Constructor.
   if (initialCapacity < 1)
   {ostringstream s;
    s << "Initial capacity = " << initialCapacity << " Must be > 0";
    throw illegalParameterValue(s.str());
   }
   arrayLength = initialCapacity;
   element = new T[arrayLength];
   listSize = 0;
}

template<class T>
arrayList<T>::arrayList(const arrayList<T>& theList)
{// Copy constructor.
   arrayLength = theList.arrayLength;
   listSize = theList.listSize;
   element = new T[arrayLength];
   copy(theList.element, theList.element + listSize, element);
}

template<class T>
void arrayList<T>::checkIndex(int theIndex) const
{// Verify that theIndex is between 0 and listSize - 1.
   if (theIndex < 0 || theIndex >= listSize)
   {ostringstream s;
    s << "index = " << theIndex << " size = " << listSize;
    throw illegalIndex(s.str());
   }

}

template<class T>
T& arrayList<T>::get(int theIndex) const
{// Return element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
   checkIndex(theIndex);
   return element[theIndex];
}

template<class T>
int arrayList<T>::indexOf(const T& theElement) const
{// Return index of first occurrence of theElement.
 // Return -1 if theElement not in list.
	return -1;/*
   // search for theElement
   int theIndex = (int) (find(element, element + listSize, theElement)
                         - element);

   // check if theElement was found
   if (theIndex == listSize)
     // not found
     return -1;
   else return theIndex;*/
 }

template<class T>
void arrayList<T>::erase(int theIndex)
{// Delete the element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
   checkIndex(theIndex);

   // valid index, shift elements with higher index
   copy(element + theIndex + 1, element + listSize,
                                element + theIndex);

   element[--listSize].~T(); // invoke destructor
}

template<class T>
void arrayList<T>::insert(int theIndex, const T& theElement)
{// Insert theElement so that its index is theIndex.
   if (theIndex < 0 || theIndex > listSize)
   {// invalid index
      ostringstream s;
      s << "index = " << theIndex << " size = " << listSize;
      throw illegalIndex(s.str());
   }

   // valid index, make sure we have space
   if (listSize == arrayLength)
      {// no space, double capacity
         changeLength1D(element, arrayLength, 2 * arrayLength);
         arrayLength *= 2;
      }

   // shift elements right one position
   copy_backward(element + theIndex, element + listSize,
                 element + listSize + 1);

   element[theIndex] = theElement;

   listSize++;
}

template<class T>
void arrayList<T>::output(ostream& out) const
{// Put the list into the stream out.
   copy(element, element + listSize, ostream_iterator<T>(cout, "  "));
}


template<class T>
void arrayList<T>::reverse(){
	accessCount = 0;
	T temp; //temporary person value
	int dex; // ending index
	for(int ii = arrayLength- listSize; ii < (arrayLength/2); ii++){
		temp = element[ii]; //setting the temperary person value to the low index value
		dex = arrayLength - ii - 1; // setting the ending index
		element[ii] = element[dex]; //setting the low index element to the higher index element
		element[dex] = temp; //setting the higher index element to the lower index element
		accessCount += 3;
    }

}
//template <class T> void swap ( T& a, T& b )

template<class T>
void arrayList<T>::insertionSort(int selection)
{// Sort a[0:n-1] using the insertion sort method.
	accessCount = 0;
	
	for (int i = 1; i < listSize; i++)
	{
		T t = element[i];
		accessCount++;
		insertS(t, i, selection );
	}
}
template<class T>
void arrayList<T>::insertS(T n,int i, int selec){
	int q;
	for(q = i -1; ((q >= 0)&&(n.Compare(element[q], selec) < 0)); q--){
		accessCount++;
		element[q+1]=element[q];
		}
	element[q+1]= n;
	accessCount++;
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const arrayList<T>& x)
   {x.output(out); return out;}


#endif
