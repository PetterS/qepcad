/*======================================================================
                      s <- AFUPSR(M,I,A,c)

Algebraic number field univariate polynomial, sign at a rational
point.  

Inputs
  M : in Z[x], the minimal polynomial for an algebraic number alpha.
  I : an acceptable isolating interval for alpha.  
  A : in Q(alpha)[x].
  c : in Q. 

Outputs
  s : a BETA-digit, s = sign(A(c)).
======================================================================*/
#include "saclib.h"

Word AFUPSR(M,I,A,c)
       Word M,I,A,c;
{
       Word a,b,s;
       /* hide s; */

Step1: /* Compute the sign. */
       a = AFFRN(c);
       b = AFPEMV(1,M,A,a);
       s = AFSIGN(M,I,b);

Return: /* Prepare for return. */
       return(s);
}
