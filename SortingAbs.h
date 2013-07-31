#ifndef SortingAbs_h
#define SortingAbs_h

#include <iostream>

using namespace std;

template<class T>
class SortingAbs{
	public:
		//virtual void reverse(T* first, T* last) = 0;
		virtual void reverse() = 0;
		//reverses the list
		virtual void insertionSort(int selection) = 0;
		// does insertion sort
};
#endif
/*
template <class BidirectionalIterator>
  void reverse (BidirectionalIterator first, BidirectionalIterator last)
{
  while ((first!=last)&&(first!=--last)) {
    std::iter_swap (first,last);
    ++first;
  }
}
*/