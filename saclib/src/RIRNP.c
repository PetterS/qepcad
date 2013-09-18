/*======================================================================
                      J <- RIRNP(I,c)

Rational interval rational number product.  

Inputs
  I : an interval with rational endpoints.  
  c : a rational number.  

Outputs
  J : an interval with rational endpoints, J = c I.
======================================================================*/
#include "saclib.h"

Word RIRNP(I,c)
       Word I,c;
{
       Word J,a,ap,b,bp;
       /* hide a,b; */

Step1: /* Compute. */
       FIRST2(I,&a,&b);
       ap = RNPROD(a,c);
       bp = RNPROD(b,c);
       if (RNSIGN(c) >= 0)
         J = LIST2(ap,bp);
       else
         J = LIST2(bp,ap);

Return: /* Prepare for return. */
       return(J);
}
