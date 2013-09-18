/*======================================================================
                      L <- IPSF(r,A)

Integral polynomial squarefree factorization.

Inputs
  r : a BETA-digit, r > 0.
  A : in Z[X1,...,Xr], A primitive and of positive degree.

Outputs
  L : a list ((e1,A1),...,(ek,Ak)) where A = A1^e1 * A2^e2 * ... * Ak^ek
      is the squarefree factorization of A in which 1 <= e1 < ... < ek
      and each Ai is a positive squarefree polynomial of positive
      degree.
======================================================================*/
#include "saclib.h"

Word IPSF(r,A)
       Word r,A;
{
       Word Ap,B,Bp,C,Cp,D,L,j;
       /* hide j; */

Step1: /* Initialize. */
       L = NIL;
       Ap = IPDMV(r,A);
       IPGCDC(r,A,Ap,&B,&C,&Cp);
       j = 1;

Step2: /* Compute factors. */
       while (PDEG(B) > 0)
         {
         IPGCDC(r,B,C,&D,&Bp,&Cp);
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
