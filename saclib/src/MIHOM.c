/*======================================================================
                      As <- MIHOM(M,A)

Modular integer homomorphism.  

Inputs
  M  : a positive integer.  
  A  : an integer.  

Outpus
  As : h sub M(A).
======================================================================*/
#include "saclib.h"

Word MIHOM(M,A)
       Word M,A;
{
       Word As;

Step1: /* Compute. */
       As = IREM(A,M);
       if (ISIGNF(As) < 0)
         As = ISUM(M,As);

Return: /* Prepare for return. */
       return(As);
}
