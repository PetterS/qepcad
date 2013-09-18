/*===========================================================================
			      a <- PCOEFF(A,i)

Polynomial coefficient.

Inputs
  A : a polynomial in r variables, r >= 1;
  i : a non-negative BETA-digit.

Output
  a : the coefficient of x^i in A, where x is the main variable.
===========================================================================*/
#include "saclib.h"

Word PCOEFF(A,i)
       Word A,i;
{
       Word Ap,e,a;

Step1: /* A = 0. */
       if (A == 0) {
	  a = 0;
	  goto Return; }

Step2: /* Search. */  
       Ap = A; 
       e = -1;
       do {
	  e = PDEG(Ap);
	  if (e <= i)
	     goto Step3;
	  else
	     Ap = PRED(Ap); }
       while (Ap != 0);

Step3: /* Pluck coefficient. */  
       if (e == i)
	 a = SECOND(Ap);
       else
	 a = 0;
       
Return: /*Prepare for return. */
       return(a);
}
