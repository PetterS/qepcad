/*======================================================================
                      s <- HISIGN(I)

Hardware interval sign.

Inputs
   I : a hardware interval.

Outputs
   s :  If 0 is not in I then s = sign(I). Otherwise s = NIL.
======================================================================*/
#include "saclib.h"

Word HISIGN(I)
       interval I;
{
       Word s;

Step1: /* Determine sign. */
       if (I.left > 0)
          s = 1;
       else if (I.right < 0)
          s = -1;
       else if (I.left == 0 && I.right == 0)
          s = 0;
       else
          s = NIL;

Return: /* Return s. */
       return(s);
}
