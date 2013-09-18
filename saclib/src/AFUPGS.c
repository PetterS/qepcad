/*===========================================================================
			      B <- AFUPGS(M,A)

Algebraic number field univariate polynomial greatest squarefree divisor.

Inputs
  M : in Z[x], the minimal polynomial for an algebraic number alpha.
  A : in Q(alpha)[x].

Outputs
  B : in Q(alpha)[x]. If A = 0 then B = 0 else B is the monic 
      associate of the greatest squarefree divisor of A.
===========================================================================*/
#include "saclib.h"

Word AFUPGS(M,A)
       Word M,A;
{
       Word B,Bp,C,D;

Step1: /* A equal 0. */
       if (A == 0) {
	  B = 0;
	  goto Return; }

Step2: /* A not equal 0. */
       B = AFPMON(1,M,A);
       if (PDEG(B) > 0) {
	  Bp = AFPDMV(1,M,B);
	  AFUPGC(M,B,Bp,&C,&B,&D); }

Return: /* Prepare for return. */
       return(B);
}
