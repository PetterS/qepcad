/*======================================================================
                      GIS(A,m,C)

General insertion sort.

Inputs
A : An array of pointers to m words.
m : A positive BETA-digit.
C : A pointer to a function of two arguments returning type Word.
Side Effects
    Rearranges the values in A so that they are in sorted order.
  ======================================================================*/
#include "mysort.h"


void GIS(Word *A, Word m, Word (*C)(Word,Word))
{
       Word i,j;
       Word e;

       for(i = 1; i < m; i++) {
	 e = A[i];
	 for(j = i-1; (j >= 0) && (C(e,A[j]) < 0); j--)
	   A[j+1] = A[j];
	 A[j+1] = e;
       }

       return;
}
