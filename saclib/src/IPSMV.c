/*======================================================================
                      C <- IPSMV(r,A,B)

Integral polynomial substitution for main variable.


Inputs
   r  : a BETA-digit, r >= 1, the number of variables.
   A  : in Z[x_1,...,x_r].
   B  : in Z[x_1,...x_{r-1}].

Outputs
   C  : in Z[x_1,...x_{r-1}], C(x_1,...,x_{r-1})  
        = A(x_1,...,x_{r-1},B(x_1,...,x_{r-1})).
======================================================================*/
#include "saclib.h"

Word IPSMV(r,A,B)
       Word r,A,B;
{
       Word A2,Ap,C,e1,e2,i,rp;

Step1: /* A = 0. */
       if (A == 0) {
          C = 0;
          goto Return; }

Step2: /* r = 1. */
       if (r == 1) {
          C = IPEMV(r,A,B);
          goto Return; }

Step3: /* Apply Horners method. */
       rp = r - 1;
       ADV2(A,&e1,&C,&Ap);
       while (Ap != NIL) {
          ADV2(Ap,&e2,&A2,&Ap);
          for (i = 1; i <= e1 - e2; i++)
             C = IPPROD(rp,C,B);
          C = IPSUM(rp,C,A2);
          e1 = e2; }
       for (i = 1; i <= e1; i++)
          C = IPPROD(rp,C,B);

Return: /* Return C. */
       return(C);
}
