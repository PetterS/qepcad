/*===========================================================================
			MAPPROD(m,A,B,C)

Modular array polynomial product.

Inputs
  m : a postive BETA-digit.
  A,B : in Z/(m)[x] in array representation.
  C : an array large enough to hold the product of A and B.

Side effects
  A * B is computed and put in C.
===========================================================================*/
#include "saclib.h"

void MAPPROD(m,A,B,C)
       Word m,*A,*B,*C;
{
       Word n1,n2,k,i;

Step1: /* A = 0 or B = 0. */
       if (MAPZERO(A) || MAPZERO(B)) {
	  MAPDEG(C) = 0;
	  MAPCF(C,0) = 0;
	  goto Return; }

Step2: /* Get degrees. */  
       n1 = MAPDEG(A);
       n2 = MAPDEG(B);

Step3: /* Set C == 0. */
       k = n1 + n2;
       MAPDEG(C) = k;
       for (i = 0; i <= k; i++)
	  MAPCF(C,i) = 0;

Step4: /* Multiply-add loop. */
       for (i = 0; i <= n2; i++)
	  MAPMADD(m,A,MAPCF(B,i),i,C);

Return: /* Prepare for return. */
       return;
}
