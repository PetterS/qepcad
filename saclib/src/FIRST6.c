/*===========================================================================
		       FIRST6(L; a1,a2,a3,a4,a5,a6)

First 6.

Inputs
  L  : list of length 6 or more.

Outputs
  a1, a2, a3, a4, a5, a6 : the first six elements of L.
===========================================================================*/
#include "saclib.h"

void FIRST6(L, a1_,a2_,a3_,a4_,a5_,a6_)
       Word L, *a1_,*a2_,*a3_,*a4_,*a5_,*a6_;
{
       Word Lp,a1,a2,a3,a4,a5,a6;

Step1: /* Compute. */
       ADV3(L,&a1,&a2,&a3,&Lp);
       ADV3(Lp,&a4,&a5,&a6,&Lp);

Return: /* Prepare for return. */
       *a1_ = a1;
       *a2_ = a2;
       *a3_ = a3;
       *a4_ = a4;
       *a5_ = a5;
       *a6_ = a6;
       return;
}
