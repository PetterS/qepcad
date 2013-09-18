/*======================================================================
                      L <- AFUPSF(M,A)

Algebraic number field univariate polynomial squarefree factorization.

Inputs
  M : in Z[x], the minimal polynomial for an algebraic number alpha.
  A : in  Q(alpha)[x]. deg(A) > 0 and A is monic.

Outputs
  L : a list ((e1,A1),...,(ek,Ak)), where A = A1^e1 * A2^e2 * .... * Ak^ek 
      is the squarefree factorization of A, with 1 <= e1 < e2 < ... < ek 
      and each Ai a monic squarefree polynomial of positive degree.
======================================================================*/
#include "saclib.h"

Word AFUPSF(M,A)
       Word M,A;
{
       Word Ap,B,Bp,C,Cp,D,L,j;
       /* hide j; */

Step1: /* Initialize. */
       L = NIL;
       Ap = AFPDMV(1,M,A);
       AFUPGC(M,A,Ap,&B,&C,&Cp);
       j = 1;

Step2: /* Compute factors. */
       while (PDEG(B) > 0)
         {
         AFUPGC(M,B,C,&D,&Bp,&Cp);
         if (PDEG(Cp) > 0)
           L = COMP(LIST2(j,Cp),L);
         B = Bp;
         C = D;
         j = j + 1;
         }

Step3: /* Finish. */
       L = COMP(LIST2(j,C),L);
       L = INV(L);

Return: /* Prepare for return. */
       return(L);
}
