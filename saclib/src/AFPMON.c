/*======================================================================
                      Ap <- AFPMON(r,M,A)

Algebraic number field polynomial monic.  

Inputs
  r  : a BETA-digit, r >= 0.
  M  : in Z[x], the minimal polynomial of an algebraic number alpha.
  A  : in Q(alpha)[X1,...,Xr]. 

Outputs
  Ap : in Q(alpha)[X1,...,Xr]. If A = 0 then Ap = 0, otherwise
       Ap is the monic associate of A.
======================================================================*/
#include "saclib.h"

Word AFPMON(r,M,A)
       Word r,M,A;
{
       Word Ap,a,ap;

Step1: /* A equal 0. */
       if (A == 0)
         {
         Ap = 0;
         goto Return;
         }

Step2: /* A not equal 0. */
       a = PLBCF(r,A);
       ap = AFINV(M,a);
       Ap = AFPAFP(r,M,ap,A);

Return: /* Prepare for return. */
       return(Ap);
}
