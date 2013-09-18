/*======================================================================
                      AADV(L; a,Lp)

Arithmetic advance.

Inputs
  L  : list.

Outputs
  a  : if L = () then a = 0,   otherwise a  = FIRST(L).
  Lp : if L = () then Lp = (), otherwise Lp = RED(L).
======================================================================*/
#include "saclib.h"

void AADV(L, a_,Lp_)
       Word L, *a_,*Lp_;
{
       Word Lp,a;
       /* hide algorithm */

Step1: /* Advance. */
       if (L != NIL)
         ADV(L,&a,&Lp);
       else
         {
         a = 0;
         Lp = NIL;
         }

Return: /* Prepare for return. */
       *a_ = a;
       *Lp_ = Lp;
       return;
}
