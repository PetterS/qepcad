/*======================================================================
                      ADV4(L; a1,a2,a3,a4,Lp)

Advance 4.

Inputs
  L  : a list of length 4 or more.

Outputs
  a1 : the first  element of L.
  a2 : the second element of L.
  a3 : the third  element of L.
  a4 : the fourth element of L.
  Lp : the fourth reductum of L.
======================================================================*/
#include "saclib.h"

void ADV4(L, a1_,a2_,a3_,a4_,Lp_)
       Word L, *a1_,*a2_,*a3_,*a4_,*Lp_;
{
       Word Lp,a1,a2,a3,a4;
       /* hide algorithm */

Step1: /* Advance four times. */
       ADV(L,&a1,&Lp);
       ADV(Lp,&a2,&Lp);
       ADV(Lp,&a3,&Lp);
       ADV(Lp,&a4,&Lp);

Return: /* Prepare for return. */
       *a1_ = a1;
       *a2_ = a2;
       *a3_ = a3;
       *a4_ = a4;
       *Lp_ = Lp;
       return;
}
