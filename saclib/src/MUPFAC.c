/*===========================================================================
			F <- MUPFAC(p,A)

Modular univariate polynomial factorization.

Inputs
  p : a medium prime.
  A : in Z/(p)[x].  A is squarefree and deg(A) >= 2.

Output
  F : a list of the distinct monic irreducible factors of A.
===========================================================================*/
#include "saclib.h"

Word MUPFAC(p,A)
       Word p,A;
{
       Word Ap,B1,F,G,G1,b,d,f;

Step1: /* Make monic. */
       Ap = MPMON(1,p,A);

Step2: /* Distinct-degree factorization. */
       G = MMPDDF(p,Ap);

Step3: /* Split equal-degree factors. */
       F = NIL;
       while (G != NIL) {
          ADV(G,&G1,&G);
          ADV2(G1,&f,&b,&G1);
          d = PDEG(b);
          if (d > f) { /* split equal degree factors */
             B1 = MMPFBL(p,b,f);
             F = CONC(B1,F); }
          else
             F = COMP(b,F); }

Return: /* Prepare for return. */
       return(F);
}
