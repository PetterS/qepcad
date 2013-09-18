/*======================================================================
                      FIRST4(L; a1,a2,a3,a4)

First 4.

Inputs
  L : list of length 4 or more.

Outputs
  a1, a2, a3, a4  : the first four elements of L.
======================================================================*/
#include "saclib.h"

void FIRST4(L, a1_,a2_,a3_,a4_)
       Word L, *a1_,*a2_,*a3_,*a4_;
{
       Word Lp,a1,a2,a3,a4;
       /* hide algorithm */

Step1: /* Get them. */
       ADV(L,&a1,&Lp);
       ADV(Lp,&a2,&Lp);
       ADV(Lp,&a3,&Lp);
       a4 = FIRST(Lp);

Return: /* Prepare for return. */
       *a1_ = a1;
       *a2_ = a2;
       *a3_ = a3;
       *a4_ = a4;
       return;
}
