/*************************************************************
 **
 **  Safe_Array.h
 **
 **  This gives a minimal "safe" array template class.  Safe
 **  here just means that bounds checking occurs.  Also, it
 **  cleans up after itself and other little niceties.  If an
 **  illegal operation does take place, this code just prints
 **  a message to cerr and core dumps for debugging purposes.
 **
 *************************************************************/
#ifndef _Safe_Array_
#define _Safe_Array_


#include <cstdlib>
#include <iostream>
using namespace std;

template<class T>
class Safe_Array
{
private:
  int n; //-- Length of array
  T*  A; //-- The actual array

public:

  Safe_Array(int k = 0)
  {    
    if (k < 0) {
      cerr << "Attempt to initialize array of negative length ... " 
	   << "dumpin' some core!" << endl;
      int j = 0;
      k /= k*j; }
    else if (k == 0) {
      n = 0;
      A = NULL; }
    else {
      n = k;
      A = new T[k]; }
    return;
  }

  ~Safe_Array()
  {
    if (A != NULL)
      delete [] A;
    return;
  }

  int empty()
  {
    return (n == 0);
  }

  int size()
  {
    return (n);
  }

  void allocate(int k)
  {
    if (n != 0) {
      cerr << "Can't `allocate' for a non-empty array ... "
	   << "dumpin' some core!" << endl;
      int j = 0;
      k /= k*j; }
    else {
      n = k;
      A = new T[k]; }
    return;
  }

  T& operator[](int i)
  {
    if (i < 0 || i >= n) {
      cerr << "Subscript out of bounds ... "
	   << "dumpin' some core!" << endl;
      int j = 0;
      i /= i*j; }

    return A[i];
  }

  Safe_Array<T>& operator=(Safe_Array<T>& R)
  {
    n = R.n;
    A = new T[ n ];
    for(int i = 0; i < n; i++)
      A[i] = R.A[i];
    return *this;
  }

};

#endif /* _Safe_Array_ */
