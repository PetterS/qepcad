/*======================================================================
                      IPICPP(r,A; a,Ab)

Integral polynomial integer content and primitive part.

Inputs
  r : a BETA-digit, r > 0.
  A : in Z[X1,...,Xr].

Outputs
  a : in Z, the integer content of A.
 Ab : in Z[X1,...,Xr], Ab = A/a if A is non-zero and Ab = 0 otherwise.
======================================================================*/
#include "saclib.h"

void IPICPP(r,A, a_,Ab_)
       Word r,A, *a_,*Ab_;
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
         a = IPIC(r,A);
         Ab = IPIQ(r,A,a);
         }

Return: /* Prepare for return. */
       *a_ = a;
       *Ab_ = Ab;
       return;
}
