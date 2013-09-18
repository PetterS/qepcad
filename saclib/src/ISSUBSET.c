/*===========================================================================
			    t <- ISSUBSET(A,B)

Is subset?

Input
  A,B : ordered lists of BETA-digits.

Output
  t : t = 1 if A is a subset of B, otherwise t = 0.
===========================================================================*/
#include "saclib.h"

Word ISSUBSET(A,B)
       Word A,B;
{
       Word A1,Ap,B1,Bp,t;

Step1: /* Trivial Cases. */
       if (A == NIL) {
	  t = 1;
	  goto Return; }
       if (B == NIL) {
	  t = 0;
	  goto Return; }

Step2: /* General Case. */
       Ap = A;
       Bp = B;
       while (Ap != NIL && Bp != NIL) {
	  A1 = FIRST(Ap);
	  B1 = FIRST(Bp);
	  if (A1 < B1) {
	     t = 0;
	     goto Return; }
	  else
	     if (A1 == B1) {
		Ap = RED(Ap);
		Bp = RED(Bp); }
	     else
		Bp = RED(Bp); }
       if (Ap == NIL)
	  t = 1;
       else
	  t = 0;

Return: /* Prepare for return. */
       return(t);
}
