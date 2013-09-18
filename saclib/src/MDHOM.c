/*======================================================================
                      b <- MDHOM(m,A)

Modular digit homomorphism.  

Inputs
  m : a positive BETA-integer.  
  A : an integer.  

Outpus
  b : the image of A under the homomorphism h sub m.
======================================================================*/
#include "saclib.h"

Word MDHOM(m,A)
       Word m,A;
{
       Word Q,b;
       /* hide algorithm */

Step1: /* Compute. */
       IDQR(A,m,&Q,&b);
       if (b < 0)
         b = b + m;

Return: /* Prepare for return. */
       return(b);
}
