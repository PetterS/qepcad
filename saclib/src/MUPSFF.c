/*======================================================================
                      L <- MUPSFF(p,A)

Modular univariate polynomial squarefree factorization.

Inputs
  p : a BETA-digit, prime.
  A : in Z/(p)[X], A is monic and of positive degree.

Outputs
  L : a list ((i1,A1),...,(ir,Ar)) with i1 < i2 < ... < ir, Aj a monic
      squarefree factor of A of positive degree for 1 <= j <= r,
      gcd(Ai,Aj) = 1 if i not equal j, and A = A1^i1 * A2^i2 * ... * Ar^ir.
======================================================================*/
#include "saclib.h"

Word MUPSFF(p,A)
       Word p,A;
{
       Word A1,Ap,B,Bp,C,D,L,L1,Lp,M,M1,Mp,e,j;
       /* hide Bp,L1,M1,Mp,e,j; */

Step1: /* Initialize. */
       Lp = NIL;
       Ap = MUPDER(p,A);
       if (Ap == 0)
         {
         B = A;
         goto Step3;
         }
       B = MUPGCD(p,A,Ap);
       C = MPQ(1,p,A,B);
       j = 1;

Step2: /* Compute Aj with j not divisible by p. */
       D = MUPGCD(p,B,C);
       A1 = MPQ(1,p,C,D);
       if (FIRST(A1) > 0)
         Lp = COMP(LIST2(j,A1),Lp);
       if (FIRST(D) > 0)
         {
         C = D;
         B = MPQ(1,p,B,C);
         j = j + 1;
         goto Step2;
         }

Step3: /* Compute Aj with j divisible by p. */
       if (FIRST(B) == 0)
         {
         L = INV(Lp);
         goto Return;
         }
       Bp = NIL;
       do
         {
         ADV2(B,&e,&A1,&B);
         e = e / p;
         Bp = COMP2(A1,e,Bp);
         }
       while (!(B == NIL));
       B = INV(Bp);
       M = MUPSFF(p,B);
       Mp = M;
       do
         {
         ADV(Mp,&M1,&Mp);
         e = p * FIRST(M1);
         SFIRST(M1,e);
         }
       while (!(Mp == NIL));
       M = INV(M);

Step4: /* Merge. */
       L = NIL;
       while (Lp != NIL && M != NIL)
         {
         if (FIRST(FIRST(Lp)) > FIRST(FIRST(M)))
           ADV(Lp,&L1,&Lp);
         else
           ADV(M,&L1,&M);
         L = COMP(L1,L);
         }
       if (M == NIL)
         Lp = INV(Lp);
       else
         Lp = INV(M);
       L = CONC(Lp,L);

Return: /* Prepare for return. */
       return(L);
}
