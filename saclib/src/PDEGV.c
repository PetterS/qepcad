/*===========================================================================
			      V <- PDEGV(r,A)

Polynomial degree vector.

Inputs
  r : a BETA-digit, r >= 1.
  A : in R[x_1,...,x_r], R a ring.

Outputs
  V : the list (v_r,...,v_1) where v_i is the degree of A in x_i.
===========================================================================*/
#include "saclib.h"

Word PDEGV(r,A)
       Word r,A;
{
       Word A1,Ap,V,V1,i,n,rp;

Step1: /* A = 0. */
       if (A == 0) {
	  V = NIL;
	  for (i = 1; i <= r; i++)
	     V = COMP(0,V);
	  goto Return; }

Step2: /* r = 1. */
       n = PDEG(A);
       if (r == 1) {
	  V = LIST1(n);
	  goto Return; }

Step3: /* r > 1. */
       rp = r - 1;
       A1 = PLDCF(A);
       V = PDEGV(rp,A1);
       Ap = PRED(A);
       while (Ap != 0) {
	  A1 = PLDCF(Ap);
	  V1 = PDEGV(rp,A1);
	  V = VMAX(V,V1);
	  Ap = PRED(Ap); }
       V = COMP(n,V);

Return: /* Prepare for return. */
       return(V);
}
