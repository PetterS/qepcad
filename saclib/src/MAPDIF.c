/*===========================================================================
			MAPDIF(m,A,B, C)

Modular array polynomial difference.

Inputs
  m : a BETA-digit.
  A,B : in Z/(m)[x], A and B are in array representation.
  C : an array at least as large as the larger of A nd B.

Side effects
  A - B is computed and put in C.
===========================================================================*/
#include "saclib.h"

void MAPDIF(m,A,B, C)
       Word m,*A,*B, *C;
{
       Word i,ap,bp,cp,dp,a,b,c;

Step1: /* Initialize. */
       ap = MAPDEG(A);
       bp = MAPDEG(B);
       MAPDEG(C) = 0;
       cp = maxm(ap,bp);
       for (i = 0; i <= cp; i++)
	  MAPCF(C,i) = 0;
       dp = minm(ap,bp);

Step2: /* Compute. */
       for (i = 0; i <= dp; i++) {
	  a = MAPCF(A,i);
	  b = MAPCF(B,i);
	  c = MDDIF(m,a,b);
	  MAPCF(C,i) = c; }
       if (ap > bp)
	  for (i = dp + 1; i <= ap; i++) {
	     a = MAPCF(A,i);
	     MAPCF(C,i) = a; }
       else
	  for (i = dp + 1; i <= bp; i++) {
	     b = MAPCF(B,i);
	     b = MDNEG(m,b);
	     MAPCF(C,i) = b; }

Step3: /* Determine degree. */
       i = cp;
       while (MAPCF(C,i) == 0 && i > 0)
	  i--;
       MAPDEG(C) = i;

Return: /* Prepare for return. */
       return;
}
