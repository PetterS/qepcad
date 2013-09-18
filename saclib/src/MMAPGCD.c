/*===========================================================================
		      C <- MMAPGCD(p,A,B)

Medium modulus array polynomial greatest common divisor.

Inputs
   p : a medium prime.
 A,B : in Z/(p)[x] in array representation.

Outputs
   C : in Z/(p)[x], C = gcd(A,B), C is in array representation.
===========================================================================*/
#include "saclib.h"

Word *MMAPGCD(p,A,B)
       Word p,*A,*B;
{
       Word *A1,*A2,*t,*C,m,n;

Step1: /* A = 0 or B = 0. */
       if (MAPZERO(A)) {
	  C = MMAPMON(p,B);
	  goto Return; }
       if (MAPZERO(B)) {
	  C = MMAPMON(p,A);
	  goto Return; }

Step2: /* General case. */
       m = MAPDEG(A);
       n = MAPDEG(B);
       if (m >= n) {
	  A1 = MMAPMON(p,A);
	  A2 = MMAPMON(p,B); }
       else {
	  A1 = MMAPMON(p,B);
	  A2 = MMAPMON(p,A); }
       do {
	  MMAPREM(p,A1,A2);
	  t = A1;
	  A1 = A2;
	  A2 = t; }
       while (!MAPZERO(A2));
       C = MMAPMON(p,A1);

Step3: /* Free arrays. */
       MAPFREE(A1);
       MAPFREE(A2);

Return: /* Prepare for return. */
       return(C);
}
