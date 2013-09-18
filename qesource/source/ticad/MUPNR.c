/*==========================================================================
                       C <- MUPNR(p,A,B)

Modular univariate polynomial natural remainder.

Inputs
  p : a BETA-digit, p a prime.
  A : in Z/(p)[x].
  B : in Z/(p)[x].

Output
  C : in Z/(p)[x], the natural remainder of A and B.
==========================================================================*/
#include "qepcad.h"

Word MUPNR(Word p, Word A, Word B)
{
       Word C,Ap,Bp;

Step1: /* deg(A) < deg(B) */
       if (PDEG(A) < PDEG(B)) {
	 C = A;
	 goto Return;
       }

Step2: /* Compute remainder. */
       Ap = DPFP(1,A);
       Bp = DPFP(1,B);
       C = DMUPNR(p,Ap,Bp);
       C = PFDP(1,C);

Return: /* Prepare for return. */
       return(C);
}
