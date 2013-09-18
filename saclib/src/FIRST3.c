/*======================================================================
                      FIRST3(L; a1,a2,a3)

First 3.

Inputs
  L  : list of length 3 or more.

Outputs
  a1, a2, a3  : the first three elements of L.
======================================================================*/
#include "saclib.h"

void FIRST3(L, a1_,a2_,a3_)
       Word L, *a1_,*a2_,*a3_;
{
       Word Lp,a1,a2,a3;
       /* hide algorithm */

Step1: /* Get them. */
       ADV2(L,&a1,&a2,&Lp);
       a3 = FIRST(Lp);

Return: /* Prepare for return. */
       *a1_ = a1;
       *a2_ = a2;
       *a3_ = a3;
       return;
}
