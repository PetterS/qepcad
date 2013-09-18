/*======================================================================
                      C <- MIPIPR(r,M,D,A,B)

Modular integral polynomial mod ideal product.

Inputs
  D : a list (d1,...,d_{r-1}) of non-negative BETA-digits.
  r : a BETA-digit, r >= 1.
  M : in Z, M > 0.
  A,B : in Z/(M)[X1,...,X_{r-1},Y]/(X1^d1,...,X_{r-1}^d{r-1}).

Outputs
  C : in Z/(M)[X1,...,X_{r-1},Y]/(X1^d1,...,X_{r-1}^d{r-1}), C = A * B.
======================================================================*/
#include "saclib.h"

Word MIPIPR(r,M,D,A,B)
       Word r,M,D,A,B;
{
       Word C,Cp;

Step1: /* Compute. */
       Cp = IPIPR(r,D,A,B);
       C = MIPHOM(r,M,Cp);

Return: /* Prepare for return. */
       return(C);
}
