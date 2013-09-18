/*======================================================================
                      L <- CCONC(L1,L2)

Constructive concatenation.

Inputs
 L1, L2  : lists.

Outputs
  L  : the concatenation of L1 and L2
       ( L is constructed, L1 and L2 are not destroyed ).
======================================================================*/
#include "saclib.h"

Word CCONC(L1,L2)
       Word L1,L2;
{
       Word L,Lp1;
       /* hide algorithm */

Step1: /* Is L1 or L2 null. */
       L = L2;
       if (L1 == NIL)
         goto Return;
       L = L1;
       if (L2 == NIL)
         goto Return;

Step2: /* Concatenate copy of L1. */
       Lp1 = CINV(L1);
       L = INV(Lp1);
       SRED(Lp1,L2);
       goto Return;

Return: /* Prepare for return. */
       return(L);
}
