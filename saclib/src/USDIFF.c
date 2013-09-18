/*===========================================================================
			     C <- USDIFF(A,B)

Unordered set difference.

Inputs
  A,B : unordered lists of objects.
        (A, B represent sets of objects.)

Outputs
  C : an unordered list representing the difference of the sets A and B.
===========================================================================*/
#include "saclib.h"

Word USDIFF(A,B)
       Word A,B;
{
       Word Ap,C,a;

Step1: /* Compute. */
       Ap = A;
       C = NIL;
       while (Ap != NIL) {
	  ADV(Ap,&a,&Ap);
	  if (MEMBER(a,B) == 0)
	     C = COMP(a,C); }

Return: /* Prepare for return. */
       return(C);
}
