/*===========================================================================
			MMAPQR(p,A,B,Q)

Medium modulus array polynomial quotient and remainder.

Inputs
  m : a medium BETA-digit.
  A,B : in Z/(m)[x], A and B are in array representation.
        A, B non-zero, and ldcf(B) is a unit.
  Q : an array large enough to contain the quotient of A modulo B.

Side effects
  The quotient of A modulo B is computed and put in Q.
  The remainder of A modulo B is put into the array A.
===========================================================================*/
#include "saclib.h"

void MMAPQR(m,A,B,Q)
       Word m,*A,*B,*Q;
{
       Word a,b,bp,c,d,e,i,k,q;

Step1: /* deg(B) = 0. */
       d = MAPDEG(A);
       e = MAPDEG(B);
       b = MAPLDCF(B);
       if (e == 0) {
	  bp = MDINV(m,b);
	  for (i = 0; i <= d; i++) {
	     q = (MAPCF(A,i) * bp) % m;
	     MAPCF(Q,i) = q; }
	  MAPDEG(Q) = d;
	  MAPDEG(A) = 0;
	  MAPCF(A,0) = 0;
	  goto Return; }

Step2: /* deg(A) < deg(B) */
       if (d < e) {
	  MAPDEG(Q) = 0;
	  MAPCF(Q,0) = 0;
	  goto Return; }

Step3: /* deg(A) >= deg(B) > 0, compute quotient and remainder. */
       k = d - e + 2;
       bp = MDINV(m,b);
       for (k = d - e; k >= 0; k--) {
	  q = (bp * MAPCF(A,e+k)) % m;
	  MAPCF(Q,k) = q;
	  if (q != 0)
	     for (i = e + k - 1; i >= k; i--) {
		c = (q * MAPCF(B,i-k)) % m;
		a = MAPCF(A,i);
		a = MDDIF(m,a,c);
		MAPCF(A,i) = a; } }
       MAPDEG(Q) = d - e;

Step4: /* Determine degree of remainder. */
       i = e - 1;
       while (MAPCF(A,i) == 0 && i > 0)
	  i--;
       MAPDEG(A) = i;

Return: /* Prepare for return. */
       return;
}
