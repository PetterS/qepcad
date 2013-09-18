/*===========================================================================
		       MMAPPROD(m,A,B,C)

Medium modulus array polynomial product.

Inputs
  m   : a medium BETA-digit.
  A,B : in Z/(m)[x] in array representation.
  C   : an array large enough to hold a polynomial of degree
        deg(A) + deg(B).

Side effects
  C is modified to contain A * B.
===========================================================================*/
#include "saclib.h"

void MMAPPROD(m,A,B,C)
       Word m,*A,*B,*C;
{
       Word b,d,e,i,k;

Step1: /* Get degrees. */  
       d = MAPDEG(A);
       e = MAPDEG(B);

Step2: /* A = 0 or B = 0. */
       if (MAPZERO(A) || MAPZERO(B)) {
	  MAPDEG(C) = 0;
	  MAPCF(C,0) = 0;
	  goto Return; }

Step3: /* Set deg(C) to m + n and coefficients of C to 0. */
       k = d + e;
       MAPDEG(C) = k;
       for (i = 0; i <= k; i++)
	  MAPCF(C,i) = 0;

Step4: /* Multiply-add loop. */
       for (i = 0; i <= e; i++) {
	  b = MAPCF(B,i);
	  MMAPMADD(m,A,b,i,C); }

Return: /* Prepare for return. */
       return;
}
