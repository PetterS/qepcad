/*======================================================================
                      ADV3(L; a1,a2,a3,Lp)

Advance 3.

Inputs
  L  : a list of length 3 or more.

Outputs
  a1 : the first element of L.
  a2 : the second element of L.
  a3 : the third element of L.
  Lp : the third reductum of L.
======================================================================*/
#include "saclib.h"

void ADV3(L, a1_,a2_,a3_,Lp_)
       Word L, *a1_,*a2_,*a3_,*Lp_;
{
       Word Lp,a1,a2,a3;
       /* hide algorithm */

Step1: /* Advance three times. */
       ADV2(L,&a1,&a2,&Lp);
       ADV(Lp,&a3,&Lp);

Return: /* Prepare for return. */
       *a1_ = a1;
       *a2_ = a2;
       *a3_ = a3;
       *Lp_ = Lp;
       return;
}
