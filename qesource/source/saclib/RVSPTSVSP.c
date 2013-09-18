/*======================================================================
                      Q <- RVSPTSVSP(r,P,s)

r-variate saclib polynomial to s-variate saclib pol

Inputs:
   r : a BDigit
   P : a saclib polynomial in variables x_1,...,x_r
   s : a BDigit , s >= t
Ouputs:
   Q : the rep of P as a poly in x_1,...,x_s
======================================================================*/
#include "qepcad.h"

Word RVSPTSVSP(BDigit r, Word P, BDigit s)
{
  Word Q,t;
  Q = P;
  for(t = r; s > t; t++)
    Q = LIST2(0,Q);
  return Q;
}
