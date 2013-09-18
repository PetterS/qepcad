/*==========================================================================
                    C <- MAFUPNR(p,M,A,B);

Modular algebraic field univariate polynomial natural remainder.

Input
  p : a BETA-digit, p a prime.
  M : in Z/(p)[x].
  A : in (Z/(p)[x])/(M)[y].
  B : in (Z/(p)[x])/(M)[y], ldcf(B) a unit in (Z/(p)[x])/(M).

Output
  C : in (Z/(p)[x])/(M)[y], the natural remainder of A and B.
==========================================================================*/
#include "qepcad.h"

Word MAFUPNR(Word p, Word M, Word A, Word B)
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
       C = DMAFUPNR(p,M,Ap,Bp);
       if (C != NIL)
	 C = PFDP(1,C);

Return: /* Prepare for return. */
       return(C);
}
