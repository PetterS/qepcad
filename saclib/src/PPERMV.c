/*===========================================================================
			    B <- PPERMV(r,A,P)

Polynomial permutation of variables.

Inputs
  A : in R[x_1,...,x_r], R ring.
  r : a BETA-digit, r >= 0.
  P : a list (P1,...,Pr) whose elements are the BETA-digits 1 through r.

Outputs
  B : B(x_P1,...,x_Pr) = A(x_1,...,x_r).
===========================================================================*/
#include "saclib.h"

Word PPERMV(r,A,P)
       Word r,A,P;
{
       Word Ap,B,Bp,a,d,dp,t;

Step1: /* A = 0. */
       if (A == 0) {
	  B = 0;
	  goto Return; }
       
Step2: /* Convert A to distributive representation and reorder. */
       Ap = DIPFP(r,A);
       Bp = NIL;
       do {
	  ADV2(Ap,&a,&d,&Ap);
	  dp = CINV(d);
	  dp = LPERM(dp,P);
	  dp = INV(dp);
	  DIPINS(a,dp,Bp,&t,&Bp); }
       while (Ap != NIL);

Step3: /* Convert back to recursive representation. */
       B = PFDIP(r,Bp);

Return: /* Prepare for return. */
       return(B);
}
