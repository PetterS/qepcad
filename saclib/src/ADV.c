/*======================================================================
<macro>               ADV(L; a,Lp)

Advance.

Inputs
  L  : a non-empty list.

Outputs
  a  : FIRST(L).
  Lp : RED(L).
======================================================================*/
#ifndef NO_SACLIB_MACROS
#define NO_SACLIB_MACROS
#endif
#include "saclib.h"

void ADV(L, a_,Lp_)
       Word L, *a_,*Lp_;
{
       Word Lp,a;
       /* hide algorithm */

Step1: /* Advance. */
       a = FIRST(L);
       Lp = RED(L);

Return: /* Prepare for return. */
       *a_ = a;
       *Lp_ = Lp;
       return;
}
