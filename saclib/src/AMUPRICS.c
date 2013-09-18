/*======================================================================
                      L <- AMUPRICS(M,I,A)

Algebraic module univariate polynomial real root isolation, 
coefficient sign variation method.

Inputs
  M : in Z[X], the minimal polynomial for an algebraic number alpha.
  I : an acceptable isolating interval for alpha. 
  A : in Z[alpha,X].

Outputs
  L : a list (I1,...,Ir) of strongly disjoint isolating intervals
      for all of the real roots of A.  Ij is a standard open or a
      one-point binary rational interval.  I1  <  I2 < ... < Ir.
======================================================================*/
#include "saclib.h"

Word AMUPRICS(M,I,A)
       Word M,I,A;
{
       Word L,Is;

Step1: /* Isolate roots. */
       AMUPRICSW(M,I,A,&L,&Is);

Step2: /* Make strongly disjoint. */
       AMUPIIWS(M,Is,A,L);

Return: /* Prepare for return. */
       return(L);
}
