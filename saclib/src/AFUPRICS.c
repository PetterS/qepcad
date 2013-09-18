/*======================================================================
                      L <- AFUPRICS(M,I,A)

Algebraic univariate polynomial real root isolation, coefficient
sign variation method.

Inputs
  M : in Z[x], the minimal polynomial for an algebraic number alpha.
  I : an acceptable isolating interval for alpha. 
  A : in Q(alpha)[x].

Outputs
  L : a list (I1,...,Ir) of strongly disjoint isolating intervals
      for all of the real roots of A.  Ij is a standard open or a
      one-point binary rational interval.  I1  <  I2 < ... < Ir.
======================================================================*/
#include "saclib.h"

Word AFUPRICS(M,I,A)
       Word M,I,A;
{
       Word Ab,L;

Step1: /* Compute similar polynomial in Z[alpha,x]. */
       Ab = AMPSAFP(1,A);

Step2: /* Isolate real roots. */
       L = AMUPRICS(M,I,Ab);

Return: /* Prepare for return. */
       return(L);
}
