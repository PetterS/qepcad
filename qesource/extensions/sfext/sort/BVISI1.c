/*======================================================================
                      BVISI1(A,n)

BETA-digit vector insertion sort indexed from 1.

Inputs
A : An array of pointers to m vectors of n BETA-digits, indexed 1 to n.
m : A positive BETA-digit.
n : A positive BETA-digit.
Side Effects
    Rearranges the pointers in A so that the vectors to which they point
    are in sorted order.
  ======================================================================*/
#include "qepcad.h"

extern Word BVCI1(Word *u_,Word *v_,Word n);

void BVISI1(Word **A, Word m, Word n)
{
       Word i,j;
       Word *e;

       for(i = 2; i <= m; i++) {
	 e = A[i];
	 for(j = i-1; (j > 0) && (BVCI1(e,A[j],n) < 0); j--)
	   A[j+1] = A[j];
	 A[j+1] = e;
       }

       return;
}
