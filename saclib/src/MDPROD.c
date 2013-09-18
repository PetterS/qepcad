/*======================================================================
                      c <- MDPROD(m,a,b)

Modular digit product.  

Inputs
  m   : a positive BETA-integer.  
  a,b : elements of Z_m.  

Otuputs
  c   : a * b.
======================================================================*/
#include "saclib.h"

Word MDPROD(m,a,b)
       Word m,a,b;
{
       Word c,c0,c1,q;

Step1: /* Compute. */
       DPR(a,b,&c1,&c0);
       DQR(c1,c0,m,&q,&c);

Return: /* Prepare for return. */
       return(c);
}
