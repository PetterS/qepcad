/*==========================================================================
                      B <- MAFUPMON(p,M,A);

Modular algebraic field univariate polynomial monic.

Input
  p : a BETA-digit, p a prime.
  M : in Z/(p)[x].
  A : in (Z/(p)[x])/(M)[y].

Output
  B : in (Z/(p)[x])/(M)[y].  If A = 0 then B = 0.  If A is non-zero 
      and ldcf(A) is a unit in (Z/(p)[x])/(M) then B is the monic 
      polynomial similar to A.  Otherwise B = NIL.
==========================================================================*/
#include "qepcad.h"

Word MAFUPMON(Word p, Word M, Word A)
{
       Word B,d,Ap,a,ap,r;
  
Step1: /* A = 0 */
       if (A == 0) {
	 B = 0;
	 goto Return;
       }

Step2: /* Compute inverse of leading coefficient and multiply. */
       a = PLDCF(A);
       ap = MAFINV(p,M,a);
       if (ap == NIL)
	 B = NIL;
       else {
	 d = PDEG(A);
	 Ap = PRED(A);
	 if (Ap != 0) {
	   B = MAFUPEPROD(p,M,ap,Ap);
	   B = COMP2(d,PMON(1,0),B);
	 } else 
	   B = PMON(PMON(1,0),d);
       }

Return: /* Prepare for return. */
       return(B);
}
