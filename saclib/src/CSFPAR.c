/*======================================================================
                      C <- CSFPAR(L)

Characteristic set from partition.

Inputs
  L : a list of non-negative BETA-digits (l1,...,ln).

Outputs
  C : a characteristic set, with j belonging to C if and only if 
      there is a subset I of the integers from 1 to n such that
      the sum of all li with i in I equals j.
======================================================================*/
#include "saclib.h"

Word CSFPAR(L)
       Word L;
{
       Word C,D,Lp,l;
       /* hide Lp,l; */

Step1: /* Compute. */
       C = 1;
       Lp = L;
       while (Lp != NIL)
         {
         ADV(Lp,&l,&Lp);
         D = IMP2(C,l);
         C = CSUN(C,D);
         }

Return: /* Prepare for return. */
       return(C);
}
