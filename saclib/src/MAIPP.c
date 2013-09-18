/*======================================================================
                      C <- MAIPP(r,A,B)

Matrix of integral polynomials product.

Inputs
   r : a BETA-digit, r >= 0.
 A,B : matrices over Z[X1,...,Xr] for which the matrix product A*B
       is defined.

Outputs
  C  : a matrix over Z[X1,...,Xr], C = A*B.
======================================================================*/
#include "saclib.h"

Word MAIPP(r,A,B)
       Word r,A,B;
{
       Word A1,A11,Ap,Ap1,B1,B11,Bp,Bs,C,C1,C11;
       /* hide A1,A11,Ap,Ap1,B1,B11; */

Step1: /* Compute. */
       C = NIL;
       Ap = A;
       do
         {
         ADV(Ap,&A1,&Ap);
         Bp = B;
         C1 = NIL;
         do
           {
           C11 = 0;
           Bs = NIL;
           Ap1 = A1;
           do
             {
             ADV(Ap1,&A11,&Ap1);
             ADV(Bp,&B1,&Bp);
             ADV(B1,&B11,&B1);
             C11 = IPSUM(r,C11,IPPROD(r,A11,B11));
             Bs = COMP(B1,Bs);
             }
           while (Bp != NIL);
           Bp = INV(Bs);
           C1 = COMP(C11,C1);
           }
         while (FIRST(Bp) != NIL);
         C1 = INV(C1);
         C = COMP(C1,C);
         }
       while (Ap != NIL);
       C = INV(C);

Return: /* Prepare for return. */
       return(C);
}
