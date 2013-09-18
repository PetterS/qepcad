/*======================================================================
                      B <- SMFMI(M,A)

Symmetric modular from modular integer.  

Inputs
  M : a positive integer.
  A : an element of Z_M.  

Outputs
  B : an element of Z'_M with B = A (modulo M).
======================================================================*/
#include "saclib.h"

Word SMFMI(M,A)
       Word M,A;
{
       Word B;

Step1: /* Compute. */
       B = IDIF(A,M);
       if (ICOMP(A,INEG(B)) <= 0)
         B = A;

Return: /* Prepare for return. */
       return(B);
}
