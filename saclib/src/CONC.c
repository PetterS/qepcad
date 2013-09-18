/*======================================================================
                      L <- CONC(L1,L2)

Concatenation.

Inputs
  L1, L2  : lists

Outputs
  L  : the concatenation of L1 and L2
       ( The list L1 is modified ).
======================================================================*/
#include "saclib.h"

Word CONC(L1,L2)
       Word L1,L2;
{
       Word L,Lp;
       /* hide algorithm */

Step1: /* L1 null. */
       L = L2;
       if (L1 == NIL)
         goto Return;

Step2: /* L2 null. */
       L = L1;
       if (L2 == NIL)
         goto Return;

Step3: /* L1 and L2 non-null. */
       Lp = LASTCELL(L1);
       SRED(Lp,L2);

Return: /* Prepare for return. */
       return(L);
}
