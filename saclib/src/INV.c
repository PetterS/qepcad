/*======================================================================
                      M <- INV(L)

Inverse.

Inputs
  L : a list.

Outputs
  M : the inverse of L.

Side effects
  The list L is transformed into M.
======================================================================*/
#include "saclib.h"

Word INV(L)
       Word L;
{
       Word M,Mp,Mpp;
       /* hide algorithm */

Step1: /* Construct. */
       M = NIL;
       Mp = L;
       while (Mp != NIL)
         {
         Mpp = RED(Mp);
         SRED(Mp,M);
         M = Mp;
         Mp = Mpp;
         }

Return: /* Prepare for return. */
       return(M);
}
