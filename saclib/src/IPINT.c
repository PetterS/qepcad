/*===========================================================================
                      B <- IPINT(r,A,b)

Integral polynomial integration.

Inputs
  A : in Z[x_1,...,x_r], such that the integral of A
      with respect to its main variable is an  
      integral polynomial.
  r : a BETA-digit, r >= 1, the number of variables.
  b : in Z[x_1,...,x_{r-1}].

Outputs
  B : in Z[x_1,...,x_r],the integral of A with respect to its
      main variable, such that B(x_1,...,x_{r-1},0) = b.
===========================================================================*/
#include "saclib.h"

Word IPINT(r,A,b)
       Word r,A,b;
{
       Word Ap,B,a,c,e,rp;

Step1: /* Compute. */
       Ap = A;
       B = NIL;
       rp = r - 1;
       do {
	  ADV2(Ap,&e,&a,&Ap);
	  e = e + 1;
	  if (r == 1)
	     c = IEQ(a,e);
	  else
	     c = IPIQ(rp,a,e);
	  B = COMP2(c,e,B); }
       while (Ap != NIL);
       if (b != 0)
	  B = COMP2(b,0,B);
       B = INV(B);

Return: /* Prepare for return. */
       return(B);
}
