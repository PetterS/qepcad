/*===========================================================================
			      B <- ITRUNC(A,n)

Integer truncation.  

Inputs
  A : in Z.
  n : a BETA-integer.

Outputs          
  B : integral part of A/2^n.
===========================================================================*/
#include "saclib.h"

Word ITRUNC(A,n)
       Word A,n;
{
       Word B;

Step1: /* A=0 or n=0. */
       B = A;
       if (A == 0 || n == 0)
	  goto Return;

Step2: /* n > 0. */
       if (n > 0) {
	  B = IDP2(A,n);
	  goto Return; }

Step3: /* n < 0. */
       B = IMP2(A,- n);

Return: /* Prepare for return. */
       return(B);
}
