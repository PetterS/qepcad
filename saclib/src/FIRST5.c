/*===========================================================================
			 FIRST5(L; a1,a2,a3,a4,a5)

First 5.

Inputs
  L  : list of length 5 or more.

Outputs
  a1, a2, a3, a4, a5 : the first five elements of L.
===========================================================================*/
#include "saclib.h"

void FIRST5(L, a1_,a2_,a3_,a4_,a5_)
       Word L, *a1_,*a2_,*a3_,*a4_,*a5_;
{
       Word Lp,a1,a2,a3,a4,a5;

Step1: /* Compute. */
       ADV3(L,&a1,&a2,&a3,&Lp);
       ADV2(Lp,&a4,&a5,&Lp);

Return: /* Prepare for return. */
       *a1_ = a1;
       *a2_ = a2;
       *a3_ = a3;
       *a4_ = a4;
       *a5_ = a5;
       return;
}
