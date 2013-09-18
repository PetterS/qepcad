/*======================================================================
                      L <- IPSFSD(r,A)

Integral squarefree factorization, second derivative.

Inputs
  A : in Z[X1,...,Xr], positive, deg(A) > 0.
  r : a BETA-digit, r > 0.

Outputs
  L : a list ((e1,A1),...,(ek,Ak)) where pp(A) = A1^e1*...*Ak^ek.
      The Ai are pairwise relatively prime squarefree positive polynomials
      with deg(Ai) > 0, deg(Ai) = 1 or gcd(Ai,A''i) = 1 for all i where
      A''i is the second derivative of Ai.
      The ei are positive BETA-digits, e1 <= e2 <= ... <= ek.
======================================================================*/
#include "saclib.h"

Word IPSFSD(r,A)
       Word r,A;
{
       Word A1,Ab,L,L1,Lb,P,e;
       /* hide e; */

Step1: /* Compute primitive part. */
       Ab = IPPP(r,A);

Step2: /* Squarefree factorization. */
       Lb = IPSF(r,Ab);

Step3: /* Apply IPFSD. */
       L = NIL;
       Lb = INV(Lb);
       do
         {
         ADV(Lb,&P,&Lb);
         FIRST2(P,&e,&A1);
         L1 = IPFSD(r,A1);
         while (L1 != NIL)
           {
           ADV(L1,&A1,&L1);
           P = LIST2(e,A1);
           L = COMP(P,L);
           }
         }
       while (!(Lb == NIL));

Return: /* Prepare for return. */
       return(L);
}
