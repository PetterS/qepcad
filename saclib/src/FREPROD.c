/*=========================================================================
		       FREPROD(p,M,A,B,C)

Finite ring element product.

Inputs
  p : a medium prime.
  M : in Z/(p)[x], M is in array representation.
  A,B : in Z/(p)[x]/(M), A and B are in array representation.
  C : a pointer to an array large enough to hold
      an element of Z/(p)[x]/(M).

Output
  C : in Z/(p)[x]/(M), C = A*B, C is in array representation.
=========================================================================*/
#include "saclib.h"

void FREPROD(p,M,A,B,C)
       Word p,*M,*A,*B,*C;
{
       Word *T;
       
Step1: /* Get temporary array for product. */
       T = MAPGET(MAPDEG(A)+MAPDEG(B));
       
Step2: /* Compute product. */
       MMAPPROD(p,A,B,T);
       MMAPREM(p,T,M);
       
Step3: /* Assign result to C. */
       MAPASSIGN(T,C);

Step4: /* Free temporary array. */
       MAPFREE(T);

Return: /* Prepare for return. */
       return;
}
