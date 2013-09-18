/*======================================================================
                      b <- IPFCB(V)

Integral polynomial factor coefficient bound.

Inputs
  V  : the degree vector of a non-zero integral
       polynomial A.

Outputs
  b  : in Z, b >= 0, such that if B1*...*Bk | A
       then the product of the infinity norms  
       of the Bi is less than or equal to 2^b times
       the infinity norm of A.
       Gelfonds bound is used.
======================================================================*/
#include "saclib.h"

Word IPFCB(V)
       Word V;
{
       Word Vp,b,n,n1,p;
       /* hide Vp,b,n,n1; */

Step1: /* Compute. */
       n = 0;
       p = 1;
       Vp = V;
       do
         {
         ADV(Vp,&n1,&Vp);
         if (n1 > 0)
           {
           n = n + n1 + n1 - 1;
           p = IPROD(p,n1 + 1);
           }
         }
       while (!(Vp == NIL));
       n = n + ILOG2(p);
       b = (n + 1) / 2;

Return: /* Prepare for return. */
       return(b);
}
