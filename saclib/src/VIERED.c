/*======================================================================
                      W <- VIERED(U,V,i)

Vector of integers, element reduction.

Inputs
 U,V : n-vectors over Z.
   i : a BETA-digit, 1 <= i <= n, Vi not zero.

Outputs
  W  : an n-vector over Z, W = U-qV, where q = [Ui/Vi].
======================================================================*/
#include "saclib.h"

Word VIERED(U,V,i)
       Word U,V,i;
{
       Word W,q,u,v;
       /* hide u,v; */

Step1: /* Compute. */
       u = LELTI(U,i);
       v = LELTI(V,i);
       q = IQ(u,v);
       if (q == 0)
         W = U;
       else
         {
         q = INEG(q);
         W = VISPR(q,V);
         W = VISUM(U,W);
         }

Return: /* Prepare for return. */
       return(W);
}
