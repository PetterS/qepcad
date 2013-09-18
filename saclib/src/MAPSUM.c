/*===========================================================================
			MAPSUM(m,A,B,C)

Modular array polynomial sum.

Inputs
  m : a BETA-digit.
  A,B : in Z/(m)[x] in array representation.
  C : an array large enough to hold A + B.

Side effects
  A + B is computed and put in C.
===========================================================================*/
#include "saclib.h"

void MAPSUM(m,A,B,C)
       Word m,*A,*B,*C;
{
       Word i,n,k,c,dmax,dmin;

Step1: /* Initialize. */
       n = MAPDEG(A);
       k = MAPDEG(B);
       i = 1;
       if (n > k) {
	  dmax = n;
	  dmin = k; }
       else {
	  dmax = k;
	  dmin = n; }
       MAPDEG(C) = 0;
       for (i = 0; i <= dmax; i++)
	  MAPCF(C,i) = 0;

Step2: /* Compute. */
       for (i = 0; i <= dmin; i++) {
	  c = MDSUM(m,MAPCF(A,i),MAPCF(B,i));
	  MAPCF(C,i) = c; }
       while (i <= n) {
          MAPCF(C,i) = MAPCF(A,i);
          i++; }
       while (i <= k) {
          MAPCF(C,i) = MAPCF(B,i);
          i++; }

Step3: /* Determine degree. */
       i = dmax;
       while (MAPCF(C,i) == 0 && i > 0)
	  i--;
       MAPDEG(C) = i;

Return: /* Prepare for return. */
       return;
}
