/*======================================================================
                      B <- MINEG(M,A)

Modular integer negation.  

Inputs
  M : a positive integer.  
  A : an element of Z_M.

Outpus
  B : -A.
======================================================================*/
#include "saclib.h"

Word MINEG(M,A)
       Word M,A;
{
       Word B;

Step1: /* Compute. */
       if (A == 0)
         B = 0;
       else
         B = IDIF(M,A);

Return: /* Prepare for return. */
       return(B);
}
