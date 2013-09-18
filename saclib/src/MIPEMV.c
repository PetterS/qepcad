/*===========================================================================
		      B <- MIPEMV(r,M,A,a)

Modular integral polynomial evaluation of main variable.

Inputs
  A : in Z/(M)[x_1,...,x_r].
  r : a BETA-digit, r >= 1, the number of variables.
  M : in Z.
  a : in Z/(M).

Outputs
  B : in Z/(M)[x_1,...,x_{r-1}].  B(x_1,...,x_{r-1}) = A(x_1,...,x_{r-1},a).
===========================================================================*/
#include "saclib.h"

Word MIPEMV(r,M,A,a)
       Word r,M,A,a;
{
       Word Ap,B,a1,e1,e2,i,rp;

Step1: /* A = 0. */
       if (A == 0) {
	  B = 0;
	  goto Return; }

Step2: /* Apply Horners method. */
       ADV(A,&e1,&Ap);
       B = 0;
       rp = r - 1;
       do {
	  ADV(Ap,&a1,&Ap);
	  if (rp == 0)
	     B = MISUM(M,B,a1);
	  else
	     B = MIPSUM(rp,M,B,a1);
	  if (Ap != NIL)
	     ADV(Ap,&e2,&Ap);
	  else
	     e2 = 0;
	  for (i = 1; i <= e1 - e2; i++)
	     if (rp == 0)
		B = MIPROD(M,a,B);
	     else
		B = MIPMIP(rp,M,a,B);
	  e1 = e2; }
       while (Ap != NIL);

Return: /* Prepare for return. */
       return(B);
}
