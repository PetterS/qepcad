/*======================================================================
                      B <- MMPEV(r,m,A,k,a)

Matrix of modular polynomials evaluation.

Inputs
  r : a BETA-digit, r >= 1.
  m : a BETA-digit, m > 0.
  A : a matrix over Z/(m)[X1,...,Xr].
  k : a BETA-digit, 1 <= k <= r.
  a : in Z/(m).

Outputs
  B : a matrix over Z/(m)[X1,...,X_{k-1},X_{k+1},...,Xr], where
      b_{i,j}(X1,...,X_{k-1},X_{k+1},...,Xr) =
      a_{i,j}(X1,...,X_{k-1},a,X_{k+1},...,Xr).
======================================================================*/
#include "saclib.h"

Word MMPEV(r,m,A,k,a)
       Word r,m,A,k,a;
{
       Word A1,A11,Ap,B,B1,B11;
       /* hide A1,A11,Ap; */

Step1: /* Compute. */
       Ap = A;
       B = NIL;
       do
         {
         ADV(Ap,&A1,&Ap);
         B1 = NIL;
         do
           {
           ADV(A1,&A11,&A1);
           B11 = MPEVAL(r,m,A11,k,a);
           B1 = COMP(B11,B1);
           }
         while (A1 != NIL);
         B1 = INV(B1);
         B = COMP(B1,B);
         }
       while (Ap != NIL);
       B = INV(B);

Return: /* Prepare for return. */
       return(B);
}
