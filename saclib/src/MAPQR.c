/*===========================================================================
			 MAPQR(m,A,B,Q)

Modular array polynomial quotient and remainder.

Inputs
  m : a postive BETA-digit.
  A,B : in Z/(m)[x], non-zero and in array representation.
        The leading coefficient of B is a unit in Z/(m).
  Q : an array large enough to contain the quotient of A divided by B.

Side effects
  The quotient of A divided by B is computed in put in Q.
  The remainder of A divided by B is put into the array A.
===========================================================================*/
#include "saclib.h"

void MAPQR(m,A,B,Q)
       Word m,*A,*B,*Q;
{
       Word n1,n2,a,bp,q,k,i;

Step1: /* deg(B) = 0 or deg(A) < deg(B). */
       n1 = MAPDEG(A);
       n2 = MAPDEG(B);
       if (n1 < n2) {
	 MAPDEG(Q) = 0;
	 MAPCF(Q,0) = 0;
	 goto Return; }
       if (n2 == 0) {
	  bp = MDINV(m,MAPLDCF(B));
	  for (i = 0; i <= n1; i++) {
	     q = MDPROD(m,bp,MAPCF(A,i));
	     MAPCF(Q,i) = q; }
	  MAPDEG(Q) = n1;
	  MAPDEG(A) = 0;
	  MAPCF(A,0) = 0;
	  goto Return; }

Step2: /* deg(B) > 0, compute quotient and remainder. */
       bp = MDINV(m,MAPLDCF(B));
       for (k = n1 - n2; k >= 0; k--) {
	  q = MDPROD(m,MAPCF(A,n2 + k),bp);
	  MAPCF(Q,k) = q;
	  if (q != 0) 
	     for (i = n2 + k - 1; i >= k; i--) {
		a = MDPROD(m,MAPCF(Q,k),MAPCF(B,i - k));
		a = MDDIF(m,MAPCF(A,i),a);
		MAPCF(A,i) = a; } }

Step3: /* Determine degree of remainder. */
       i = n2 - 1;
       while (MAPCF(A,i) == 0 && i > 0)
	  i--;
       MAPDEG(A) = i;

Step4: /* Determine degree of quotient. */
       i = n1 - n2;
       while(MAPCF(Q,i) == 0 && i > 0)
	  i--;
       MAPDEG(Q) = i;

Return: /* Prepare for return. */
       return;
}
