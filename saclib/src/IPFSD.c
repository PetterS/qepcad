/*===========================================================================
                         L <- IPFSD(r,A)

Integral polynomial factorization, second derivative.

Inputs
  A : in Z[X1,...,Xr], positive, primitive, deg(A) > 0.
  r : a BETA-digit, r >= 1.

Outputs
  L : a list (A1,...,Ak) where k >= 1, Ai in Z[X1,...,Xr], 
      positive, primitive, 0 < deg(Ai) <=2 or gcd(Ai,A''i)=1 
      (where A''i is the second derivative of Ai).  
      A = A1 +...+Ak.
===========================================================================*/
#include "saclib.h"

Word IPFSD(r,A)
       Word r,A;
{
       Word B,B1,B2,Bpp,C,L,S,n;

Step1: /* Compute. */
       L = NIL;
       S = LIST1(A);
       do {
         ADV(S,&B,&S);
         n = PDEG(B);
         if (n <= 2)
           L = COMP(B,L);
         else {
           Bpp = IPHDMV(r,B,2);
           IPGCDC(r,B,Bpp,&C,&B1,&B2);
           if (IPONE(r,C) == 1)
             L = COMP(B,L);
           else
             S = COMP2(B1,C,S); } }
       while (S != NIL);

Return: /* Prepare for return. */
       return(L);
}
