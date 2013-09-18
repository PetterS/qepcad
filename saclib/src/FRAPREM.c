/*==========================================================================
			FRAPREM(p,M,A,B)

Finite ring array polynomial remainder.

Inputs
  p : a BETA-digit, p a prime.
  M : in Z/(p)[x], M in array representation.
  A, B : in (Z/(p)[x])/(M)[y], A, B non-zero.
         A and B are in array representation.

Side effects
  A is modified.  If the leading coefficient is invertible or
  deg(A) < deg(B), then A will contain the remainder of A modulo B.
  Otherwise, deg(A) = -1.
==========================================================================*/
#include "saclib.h"

void FRAPREM(p,M,A,B)
       Word p,*M,**A,**B;
{
       Word n,m,*bp,k,*a,*q,*r,j;

Step1: /* deg(B) = 0. */
       n = FRAPDEG(B);
       if (n == 0) {
	  FRAPDEG(A) = 0;
	  a = FRAPLDCF(A);
	  MAPDEG(a) = 0;
	  MAPLDCF(a) = 0;
	  goto Return; }

Step2: /* deg(A) < deg(B). */
       m = FRAPDEG(A);
       if (m < n)
	  goto Return;

Step3: /* Get temporary arrays. */
       q = MAPGET(MAPDEG(M)-1);
       r = MAPGET(MAPDEG(M)-1);
       
Step4: /* Invert leading coefficient, if possible. */
       bp = FREINV(p,M,FRAPLDCF(B));
       if (MAPDEG(bp) < 0) {
	  FRAPDEG(A) = -1;
	  goto Step7; }

Step5: /* Compute remainder. */
       for (k = m-n; k >= 0; k--) {
	  a = FRAPCF(A,n+k);
	  FREPROD(p,M,a,bp,q);
	  if (!MAPZERO(q))
	     for (j = n+k-1; j >= k; j--) {
		FREPROD(p,M,q,FRAPCF(B,j-k),r);
		MAPIDIF(p,FRAPCF(A,j),r); } }

Step6: /* Determine degree of remainder. */
       j = n - 1;
       while (MAPZERO(FRAPCF(A,j)) && j > 0)
	  j--;
       FRAPDEG(A) = j;
       
Step7: /* Free arrays. */
       MAPFREE(bp);
       MAPFREE(q);
       MAPFREE(r);

Return: /* Prepare for return. */
       return;
}
