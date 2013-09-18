/*======================================================================
                      FIRST2(L; a,b)

First 2.

Inputs
  L  : list of length 2 or more.

Outputs
  a, b  : the first two elements of L.
======================================================================*/
#include "saclib.h"

void FIRST2(L, a_,b_)
       Word L, *a_,*b_;
{
       Word Lp,a,b;
       /* hide algorithm */

Step1: /* Get them. */
       ADV(L,&a,&Lp);
       b = FIRST(Lp);

Return: /* Prepare for return. */
       *a_ = a;
       *b_ = b;
       return;
}
