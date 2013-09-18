/*======================================================================
                      B <- PMPMV(A,k)

Polynomial multiplication by power of main variable.

Inputs
  A : in R[X1,...,Xr], R ring, r >= 0.
  k : a BETA-digit, k >= -order(A).

Outputs
  B : in R[X1,...,Xr], B(X1,...,Xr) = A(X1,...,Xr) * Xr^k.
======================================================================*/
#include "saclib.h"

Word PMPMV(A,k)
       Word A,k;
{
       Word Ap,B,a,e;
       /* hide Ap,a,e; */

Step1: /* A = 0 or k = 0. */
       if (A == 0 || k == 0)
         {
         B = A;
         goto Return;
         }

Step2: /* General case. */
       B = NIL;
       Ap = A;
       do
         {
         ADV2(Ap,&e,&a,&Ap);
         B = COMP2(a,e + k,B);
         }
       while (!(Ap == NIL));
       B = INV(B);

Return: /* Prepare for return. */
       return(B);
}
