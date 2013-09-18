/*======================================================================
                      Ap <- MPMON(r,m,A)

Modular polynomial monic.

Inputs
  r : a BETA-digit, r >= 1, the number of variables;
  m : a positive BETA-digit;
  A : in Z/(m)[X1,...,Xr] and lbcf(A) is a unit in Z/(m).

Outputs
  Ap : in Z/(m)[X1,...,Xr].
       If A is non-zero then Ap is the polynomial similar to A
       with lbcf(Ap)=1.  If A=0 then Ap=0.
======================================================================*/
#include "saclib.h"

Word MPMON(r,m,A)
       Word r,m,A;
{
       Word Ap,a,ap;
       /* hide algorithm */

Step1: /* A=0. */
       if (A == 0)
         {
         Ap = 0;
         goto Return;
         }

Step2: /* A non-zero. */
       a = PLBCF(r,A);
       ap = MDINV(m,a);
       Ap = MPMDP(r,m,ap,A);

Return: /* Prepare for return. */
       return(Ap);
}
