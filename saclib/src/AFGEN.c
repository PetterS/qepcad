/*===========================================================================
			       a <- AFGEN()

Algebraic number field generator.

Output
  a : in Q(alpha).  If alpha is any irrational algebraic number, a is
      the representation of alpha as an element of the algebraic number
      field Q(alpha).
===========================================================================*/
#include "saclib.h"

Word AFGEN()
{
       Word a;

Step1: /* Construct. */
       a = LIST2(RNINT(1),PMON(1,1));

Return: /* Prepare for return. */
       return(a);
}
