/*======================================================================
                      B <- MAIPHM(r,m,A)

Matrix of integral polynomials homomorphism.

Inputs
  r : a BETA-digit, r >= 0.
  m : a BETA-digit, m > 0.
  A : a matrix over Z[X1,...,Xr].

Outputs
  B : a matrixover Z/(m)[X1,...,Xr], B = A (mod (m)).
======================================================================*/
#include "saclib.h"

Word MAIPHM(r,m,A)
       Word r,m,A;
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
           B11 = MPHOM(r,m,A11);
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
