/*======================================================================
                      C <- MISUM(M,A,B)

Modular integer sum.  

Inputs
  M   : a positive integer.  
  A,B : elements of Z_M.

Outputs
  C   : A + B.
======================================================================*/
#include "saclib.h"

Word MISUM(M,A,B)
       Word M,A,B;
{
       Word C,Cp;

Step1: /* Compute. */
       C = ISUM(A,B);
       Cp = IDIF(C,M);
       if (ISIGNF(Cp) >= 0)
         C = Cp;

Return: /* Prepare for return. */
       return(C);
}
