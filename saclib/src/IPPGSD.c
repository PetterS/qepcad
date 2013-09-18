/*======================================================================
                      B <- IPPGSD(r,A)

Integral polynomial primitive greatest squarefree divisor.

Inputs
  r : a BETA-digit, r > 0.
  A : in Z[X1,...,Xr].

Outputs
  B : in Z[X1,...,Xr], 
      if A is non-zero then 
        B is the greatest squarefree divisor of the primitive part of A. 
      Otherwise, 
        B = 0.
======================================================================*/
#include "saclib.h"

Word IPPGSD(r,A)
       Word r,A;
{
       Word B,Bp,C,D;
       /* hide C,D; */

Step1: /* A equal 0. */
       if (A == 0)
         {
         B = 0;
         goto Return;
         }

Step2: /* A not equal 0. */
       B = IPPP(r,A);
       if (FIRST(B) > 0)
         {
         Bp = IPDMV(r,B);
         IPGCDC(r,B,Bp,&C,&B,&D);
         }

Return: /* Prepare for return. */
       return(B);
}
