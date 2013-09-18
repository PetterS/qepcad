/*======================================================================
                      s <- RNSIGN(R)

Rational number sign.  

Inputs
  R : a rational number.  

Outputs
  s : sign(R).
======================================================================*/
#include "saclib.h"

Word RNSIGN(R)
       Word R;
{
       Word s;
       /* hide algorithm */

Step1: /* Compute. */
       if (R == 0)
         s = 0;
       else
         s = ISIGNF(FIRST(R));

Return: /* Prepare for return. */
       return(s);
}
