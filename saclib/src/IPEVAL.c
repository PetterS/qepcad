/*======================================================================
                      B <- IPEVAL(r,A,i,a)

Integral polynomial evaluation.

Inputs
   r : a BETA-digit, r >= 1, the number of variables.
   A : in Z[x_1,...x_r].
   i : in Z, 1 <= i <= r.
   a : in Z.

Outputs
  B  : in Z[x_1,...,x_{i-1},x_{i+1},...,x_r],
       B(x_1,...,x_{i-1},x_{i+1},...,x_r) = 
       = A(x_1,...,x_{i-1},a,x_{i+1},...,x_r).
======================================================================*/
#include "saclib.h"

Word IPEVAL(r,A,i,a)
       Word r,A,i,a;
{
       Word A1,Ap,B,B1,e1,rp;

Step1: /* A = 0. */
       if (A == 0) {
          B = 0;
          goto Return; }

Step2: /* i = r. */
       if (i == r) {
          B = IPEMV(r,A,a);
          goto Return; }

Step3: /* i < r. */
       rp = r - 1;
       Ap = A;
       B = NIL;
       do {
          ADV2(Ap,&e1,&A1,&Ap);
          B1 = IPEVAL(rp,A1,i,a);
          if (B1 != 0)
             B = COMP2(B1,e1,B); }
       while (Ap != NIL);
       B = INV(B);
       if (B == NIL)
          B = 0;

Return: /* Return B. */
       return(B);
}
