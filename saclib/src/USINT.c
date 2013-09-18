/*===========================================================================
			      C <- USINT(A,B)

Unordered set intersection.

Inputs
  A,B : unordered lists of objects.
        (A, B represent sets of objects.)

Outputs
  C : an unordered list representing the intersection of the sets A and B.
===========================================================================*/
#include "saclib.h"

Word USINT(A,B)
       Word A,B;
{
       Word Ap,C,a;

Step1: /* Compute. */
       Ap = A;
       C = NIL;
       while (Ap != NIL) {
	  ADV(Ap,&a,&Ap);
	  if (MEMBER(a,B) == 1)
	     C = COMP(a,C); }

Return: /* Prepare for return. */
       return(C);
}
