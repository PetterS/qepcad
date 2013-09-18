/*======================================================================
                      k <- IPVCHT(A)

Integral polynomial variations after circle to half-plane 
transformation.


Inputs
  A : in Z[X], non-zero. Let n = deg(A), A'(x) = x^n A(1/x), B(x)=A'(x+1).

Outputs
  k : the number of sign variations in the coefficients of B.
======================================================================*/
#include "saclib.h"

Word IPVCHT(A)
       Word A;
{
       Word Ap,B,k;
       /* hide k; */

Step1: /* Compute. */
       Ap = PRT(A);
       B = IUPTR1(Ap);
       k = IUPVAR(B);

Return: /* Prepare for return. */
       return(k);
}
