/*======================================================================
                     t <- SIGEQUALOL(A,B,L)

Sign equal on list.

inputs
 A : An array on 0's 1's and '-1's of length a.
 B : An array on 0's 1's and '-1's of length b.
 L : A list of non-negative BETA-Digits, each less than min(a,b).

outputs
 t : 1 if A[i] = B[i] for each i in L, and 0 otherwise.
======================================================================*/
#include "qepcad.h"


Word SIGEQUALOL(Word *A, Word *B, Word L)
{

Step1: /* The only step! */
      while ( (L != NIL) && (A[ FIRST(L) ] == B[ FIRST(L) ]) )
	L = RED(L);

Return:/* Return. */
      return (L == NIL);
}

