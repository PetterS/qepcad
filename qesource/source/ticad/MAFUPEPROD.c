/*==========================================================================
                      B <- MAFUPEPROD(p,M,a,A);

Modular algebraic field univariate polynomial and element product.

Input
  p : a BETA-digit, p a prime.
  M : in Z/(p)[x].
  a : in Z/(p)[x]/(M).
  A : in (Z/(p)[x])/(M)[y].

Output
  B : in (Z/(p)[x])/(M)[y].  B = a * A.
==========================================================================*/
#include "qepcad.h"

Word MAFUPEPROD(Word p, Word M, Word a, Word A)
{
       Word B,Ap,e,ap,b;
  
Step1: /* a = 0 \/ A = 0 */
       if (a == 0 || A == 0) {
	 B = 0;
	 goto Return;
       }

Step2: /* Compute product. */
       Ap = A;
       B = NIL;
       do {
	 ADV2(Ap,&e,&ap,&Ap);
	 b = MAFPROD(p,M,a,ap);
	 if (b != 0)
	   B = COMP2(b,e,B);
       } while (Ap != NIL);
       if (B == NIL) 
	 B = 0;
       else
	 B = INV(B);

Return: /* Prepare for return. */
       return(B);
}
