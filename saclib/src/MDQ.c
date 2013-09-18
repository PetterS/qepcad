/*======================================================================
                      c <- MDQ(m,a,b)

Modular digit quotient.  

Inputs
  m   : a positive BETA-integer.  
  a,b : elements of Z_m.  b is a unit.  

Outputs
  c   : a/b.
======================================================================*/
#include "saclib.h"

Word MDQ(m,a,b)
       Word m,a,b;
{
       Word c;
       /* hide algorithm */

Step1: /* Compute. */
       c = MDPROD(m,a,MDINV(m,b));

Return: /* Prepare for return. */
       return(c);
}
