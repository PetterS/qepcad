/*======================================================================
                      L <- IPRIM(A)

Integral polynomial real root isolation, modified Uspensky method.

Inputs  
  A : in Z[X], non-zero, squarefree.

Outputs
  L : a list (I1,...,Ir) of strongly disjoint isolating intervals for
      all of the real roots of A with I1  <  I2 < ... < Ir. Each I_j is a
      standard open or a one-point binary rational interval.
======================================================================*/
#include "saclib.h"

Word IPRIM(A)
       Word A;
{
       Word L;

Step1: /* Compute. */
       L = IPRIMW(A);
       IPIIWS(A,L);

Return: /* Prepare for return. */
       return(L);
}
