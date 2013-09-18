/*======================================================================
                      C <- MIDIF(M,A,B)

Modular integer difference.  

Inputs
  M   : a positive integer.  
  A,B : elements of Z_M.

Outputs
  C   : A - B.
======================================================================*/
#include "saclib.h"

Word MIDIF(M,A,B)
       Word M,A,B;
{
       Word C;

Step1: /* Compute. */
       C = IDIF(A,B);
       if (ISIGNF(C) < 0)
         C = ISUM(M,C);

Return: /* Prepare for return. */
       return(C);
}
