/*======================================================================
                      ADV2(L; a,b,Lp)

Advance 2.

Inputs
  L   : a list of length 2 or more.

Outputs
  a   : the first element of L.
  b   : the second element of L. 
  Lp  : the second reductum of L;  Lp = RED(RED(L)).
======================================================================*/
#include "saclib.h"

void ADV2(L, a_,b_,Lp_)
       Word L, *a_,*b_,*Lp_;
{
       Word Lp,a,b;
       /* hide algorithm */

Step1: /* Advance twice. */
       ADV(L,&a,&Lp);
       ADV(Lp,&b,&Lp);

Return: /* Prepare for return. */
       *a_ = a;
       *b_ = b;
       *Lp_ = Lp;
       return;
}
