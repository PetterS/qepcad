/*======================================================================
                      IPCPP(r,A; C,Ab)

Integral polynomial content and primitive part.

Inputs
  r : a BETA-digit, r > 0.
  A : in Z[X1,...,Xr].

Outputs
  C : in Z[X1,...,X_{r-1}], the content of A.
 Ab : in Z[X1,...,Xr], the primitive part of A.
======================================================================*/
#include "saclib.h"

void IPCPP(r,A, C_,Ab_)
       Word r,A, *C_,*Ab_;
{
       Word Ab,C,s;
       /* hide algorithm */

Step1: /* Compute. */
       IPSCPP(r,A,&s,&C,&Ab);

Return: /* Prepare for return. */
       *C_ = C;
       *Ab_ = Ab;
       return;
}
