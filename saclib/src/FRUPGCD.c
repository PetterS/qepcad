/*==========================================================================
		     C <- FRUPGCD(p,M,A,B);

Finite ring univariate polynomial gcd.

Input
  p : a medium prime.
  M : in Z/(p)[x].
  A,B : in (Z/(p)[x])/(M)[y], A, B are non-zero.

Output
  C : in (Z/(p)[x])/(M)[y].  If the leading coefficient of the
      last non-zero element S in the natural prs of A and B is
      invertible in (Z/(p)[x])/(M), then C is the monic associate
      of S.  Otherwise C = NIL.
==========================================================================*/
#include "saclib.h"

Word FRUPGCD(p,M,A,B)
       Word p,M,A,B;
{
       Word C,**Cp,**A1,**A2,*Mp,**t;

Step1: /* Initialize. */
       if (PDEG(A) > PDEG(B)) {
	  A1 = FRUPCR(A,PDEG(M));
	  A2 = FRUPCR(B,PDEG(M)); }
       else {
	  A1 = FRUPCR(B,PDEG(M));
	  A2 = FRUPCR(A,PDEG(M)); }
       Mp = MAPFMUP(M);

Step2: /* Compute natural prs. */
       do {
	  FRAPREM(p,Mp,A1,A2);
	  t = A1;
	  A1 = A2;
	  A2 = t; }
       while (!FRAPZERO(A2) && (FRAPDEG(A2) >= 0));

Step3: /* Make gcd monic. */
       if (FRAPDEG(A2) >= 0)  {
	  Cp = FRAPMON(p,Mp,A1);
	  C = FRAPCR(Cp);
	  FRAPFREE(Cp); }
       else
	  C = NIL;

Step4: /* Free arrays. */
       FRAPFREE(A1);
       FRAPFREE(A2);
       MAPFREE(Mp);
       
Return: /* Prepare for return. */
       return(C);
}
