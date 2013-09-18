/*======================================================================
                      BVIS(A,n)

BETA-digit vector insertion sort.

Inputs
A : An array of pointers to m vectors of n BETA-digits.
m : A positive BETA-digit.
n : A positive BETA-digit.
Side Effects
    Rearranges the pointers in A so that the vectors to which they point
    are in sorted order.
  ======================================================================*/
#include "qepcad.h"

extern Word BVC(Word *u_,Word *v_,Word n);

void BVIS(Word **A, Word m, Word n)
{
       Word i,j;
       Word *e;

       for(i = 1; i < m; i++) {
	 e = A[i];
	 for(j = i-1; (j >= 0) && (BVC(e,A[j],n) < 0); j--)
	   A[j+1] = A[j];
	 A[j+1] = e;
       }

       return;
}
