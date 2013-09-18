/*======================================================================
                      B <- IPEMV(r,A,a)

Integral polynomial evaluation of main variable.

Inputs
   r : a BETA-digit, r >= 1, the number of variables.
   A : in Z[x_1,...,x_r].
   a : in Z.

Outputs                          
   B : in Z[x_1,...,x_{r-1}], B(x_1,...,x_{r-1})
       = A(x_1,...,x_{r-1},a).
======================================================================*/
#include "saclib.h"

Word IPEMV(r,A,a)
       Word r,A,a;
{
       Word A2,Ap,B,e1,e2,i,rp;

Step1: /* A = 0. */
       if (A == 0) {
          B = 0;
          goto Return; }

Step2: /* Apply Horner's method. */
       ADV2(A,&e1,&B,&Ap);
       rp = r - 1;
       while (Ap != NIL) {
          ADV2(Ap,&e2,&A2,&Ap);
          for (i = 1; i <= e1 - e2; i++)
            if (rp == 0)
               B = IPROD(a,B);
            else
               B = IPIP(rp,a,B);
          if (rp == 0)
             B = ISUM(B,A2);
          else
             B = IPSUM(rp,B,A2);
          e1 = e2; }
       for (i = 1; i <= e1; i++)
          if (rp == 0)
             B = IPROD(a,B);
          else
             B = IPIP(rp,a,B);

Return: /* Return B. */
       return(B);
}
