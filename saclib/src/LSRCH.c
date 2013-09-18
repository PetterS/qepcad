/*===========================================================================
			      i <- LSRCH(a,A)

List search.

Input
  A : is a list (A_1,...,A_n) of objects.
  a : is an object. 
  
Output
  i : the least j, if any, such that a = A_j; otherwise 0.
===========================================================================*/
#include "saclib.h"

Word LSRCH(a,A)
       Word a,A;
{
       Word Ap,a1,i;

Step1: /* Search. */
       Ap = A; i = 1;
       while (Ap != NIL) {
	  ADV(Ap,&a1,&Ap);
	  if (EQUAL(a1,a))
	     goto Return;
	  i = i + 1; }
       i = 0;

Return: /* Prepare for return. */
       return(i);
}
