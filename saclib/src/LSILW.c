/*======================================================================
                         w <- LSILW(I)

Logarithmic standard interval - logarithm of width.

Inputs
   I    : an open logarithmic standard interval.

Outputs
   w    : a BETA-integer. Width(I) = 2^w.
======================================================================*/
#include "saclib.h"

Word LSILW(I)
       Word I;
{
       Word a,b,k,l,w;

Step1: /* Consider three cases. */
       FIRST2(I,&a,&b);
       if (a == 0)
          w = -SECOND(b);
       else {
          if (b == 0)
             w = -SECOND(a);
          else {
             k = SECOND(a);
             l = SECOND(b);
             w = -maxm(k,l); } }

Return: /* Prepare for return. */
        return(w);
}
