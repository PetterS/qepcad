/*======================================================================
                      L <- LBIM(L1,L2)

List of BETA-integers merge.

Inputs
  L1, L2  : lists of BETA-integers in non-decreasing order.

Outputs
  L       : a list obtained by merging L1 and L2.
            L1 and L2 are modified to produce L.
======================================================================*/
#include "saclib.h"

Word LBIM(L1,L2)
       Word L1,L2;
{
       Word L,Lp,Lp1,Lp2,a1,a2;
       /* hide algorithm */

Step1: /* L1 or L2 null. */
       if (L1 == NIL)
         {
         L = L2;
         goto Return;
         }
       if (L2 == NIL)
         {
         L = L1;
         goto Return;
         }

Step2: /* Initialize. */
       Lp1 = L1;
       Lp2 = L2;
       a1 = FIRST(L1);
       a2 = FIRST(L2);
       if (a1 > a2)
         {
         L = L2;
         Lp = L2;
         Lp2 = RED(L2);
         goto Step4;
         }
       else
         {
         L = L1;
         Lp = L1;
         Lp1 = RED(L1);
         }

Step3: /* LAST element from L1. */
       if (Lp1 == NIL)
         goto Step5;
       a1 = FIRST(Lp1);
       if (a1 <= a2)
         {
         Lp = Lp1;
         Lp1 = RED(Lp1);
         goto Step3;
         }
       else
         {
         SRED(Lp,Lp2);
         Lp = Lp2;
         Lp2 = RED(Lp2);
         }

Step4: /* LAST element from L2. */
       if (Lp2 == NIL)
         goto Step5;
       a2 = FIRST(Lp2);
       if (a1 <= a2)
         {
         SRED(Lp,Lp1);
         Lp = Lp1;
         Lp1 = RED(Lp1);
         goto Step3;
         }
       else
         {
         Lp = Lp2;
         Lp2 = RED(Lp2);
         goto Step4;
         }

Step5: /* Left over. */
       if (Lp1 == NIL)
         SRED(Lp,Lp2);
       else
         SRED(Lp,Lp1);

Return: /* Prepare for return. */
       return(L);
}
