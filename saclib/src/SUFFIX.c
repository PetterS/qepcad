/*======================================================================
                      Lp <- SUFFIX(L,b)

Suffix.

Inputs
  L  : a list (a1,...,an), n >= 0
  b  : object.

Outputs
  Lp  : the list (a1,...,an,b).  L is modified.
======================================================================*/
#include "saclib.h"

Word SUFFIX(L,b)
       Word L,b;
{
       Word Lp;
       /* hide algorithm */

Step1: /* Get it. */
       Lp = CONC(L,LIST1(b));

Return: /* Prepare for return. */
       return(Lp);
}
