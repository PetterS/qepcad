/*======================================================================
                      C <- IPSUB(r,A,i,B)

Integral polynomial substitution.

Inputs
  A  : in Z[x_1,...,x_r].
  r  : a BETA-digit, r >= 1, the number of variables.
  i  : a BETA-digit, 1 <= i <= r.
  B  : in Z[x_1,...,x_{i-1}].

Outputs
  C  : in Z[x_1,...x_{i-1},x_{i+1},...,x_r],
       C(x_1,...,x_{i-1},x_{i+1},...,x_r) =
       A(x_1,...,x_{i-1},B(x_1,...,x_{i-1}),x_{i+1},...,x_r),
       the result of substituting B(x_1,...,x_{i-1}) for x_i in 
       A(x_1,...,x_r).
======================================================================*/
#include "saclib.h"

Word IPSUB(r,A,i,B)
       Word r,A,i,B;
{
       Word A1,Ap,C,C1,e1,rp;

Step1: /* A = 0. */
       if (A == 0) {
          C = 0;
          goto Return; }

Step2: /* i = r. */
       if (i == r) {
          C = IPSMV(r,A,B);
          goto Return; }

Step3: /* i < r. */
       rp = r - 1;
       Ap = A;
       C = NIL;
       do {
          ADV2(Ap,&e1,&A1,&Ap);
          C1 = IPSUB(rp,A1,i,B);
          if (C1 != 0)
             C = COMP2(C1,e1,C); }
       while (!(Ap == NIL));
       C = INV(C);
       if (C == NIL)
          C = 0;

Return: /* Return C. */
       return(C);
}
