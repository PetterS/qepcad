/*======================================================================
                      s <- AMUPBES(M,I,A,c)

Algebraic module univariate polynomial, binary rational
evaluation of sign.

Inputs
  M : in Z[X], the minimal polynomial for an algebraic number alpha.
  I : an acceptable isolating interval for alpha.  
  A : in Z[alpha,X].
  c : A binary rational number. 

Outputs
  s : a BETA-digit, s = sign(A(c)).
======================================================================*/
#include "saclib.h"

Word AMUPBES(M,I,A,c)
       Word M,I,A,c;
{
       Word a,b,s;
       /* hide s; */

Step1: /* Compute the sign. */
       b = IPBREI(2,A,2,c);
       s = AMSIGN(M,I,b);

Return: /* Prepare for return. */
       return(s);
}
