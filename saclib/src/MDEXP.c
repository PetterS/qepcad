/*======================================================================
                      b <- MDEXP(m,a,n)

Modular digit exponentiation.  

Inputs
  m : a positive BETA-integer.
  a : an element of Z/(m). 
  n : a non-negative BETA-integer. 


Outputs
  b : a^n.
======================================================================*/
#include "saclib.h"

Word MDEXP(m,a,n)
       Word m,a,n;
{
       Word b,c,np;
       /* hide algorithm */

Step1: /* b = 0. */
       if (a == 0 && n > 0)
         {
         b = 0;
         goto Return;
         }

Step2: /* b /= 0. */
       b = 1;
       c = a;
       np = n;
       while (np != 0)
         {
         if (ODD(np))
           b = MDPROD(m,b,c);
         c = MDPROD(m,c,c);
         np = np / 2;
         }

Return: /* Prepare for return. */
       return(b);
}
