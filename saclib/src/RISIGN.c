/*======================================================================
                      s <- RISIGN(I)

Rational interval sign.

Inputs
  I : a rational interval.  I = (a1,a2).

Outputs
  s : integer.  If 0 not in I or I is a one-point interval then s = sign(a1)
                else s = NIL.
======================================================================*/
#include "saclib.h"

Word RISIGN(I)
       Word I;
{
       Word s;
       Word a1,a2;

Step1: /* Get endpoints of I and J. */
       FIRST2(I,&a1,&a2);

Step2: /* I = 0. */
       if (a1 == 0 && a2 == 0)
         {
         s = 0;
         goto Return;
         }

STEP3: /* Check if 0 in I. */
       if (RNSIGN(a1) > 0)
         s = 1;
       else
         if (RNSIGN(a2) < 0)
           s = -1;
         else
           s = NIL;

Return:
       return(s);
}
