/*======================================================================
                      MPUCPP(r,p,A; a,Ab)

Modular polynomial univariate content and primitive part.

Inputs
  r : a BETA-digit, r >= 2.
  p : a BETA-digit, prime.
  A : in Z/(p)[X1,...,Xr].

Outputs
  a : in Z/(p)[X], the univariate content of A.
 Ab : in Z/(p)[X1,...,Xr], Ab = A/a if A non-zero and Ab = 0 otherwise.
======================================================================*/
#include "saclib.h"

void MPUCPP(r,p,A, a_,Ab_)
       Word r,p,A, *a_,*Ab_;
{
       Word Ab,a;
       /* hide Ab; */

Step1: /* Compute. */
       if (A == 0)
         {
         a = 0;
         Ab = 0;
         }
       else
         {
         a = MPUC(r,p,A);
         Ab = MPUQ(r,p,A,a);
         }

Return: /* Prepare for return. */
       *a_ = a;
       *Ab_ = Ab;
       return;
}
