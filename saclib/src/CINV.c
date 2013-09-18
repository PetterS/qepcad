/*======================================================================
                      M <- CINV(L)

Constructive inverse.

Inputs
  L : a list.

Outputs
  M : a list, the inverse of L. M is constructed using COMP.
======================================================================*/
#include "saclib.h"

Word CINV(L)
       Word L;
{
       Word Lp,M,a;
       /* hide Lp,a; */

Step1: /* Construct. */
       M = NIL;
       Lp = L;
       while (Lp != NIL)
         {
         ADV(Lp,&a,&Lp);
         M = COMP(a,M);
         }
       goto Return;

Return: /* Prepare for return. */
       return(M);
}
