/*==========================================================================
		      B <- FRAPMON(p,M,A)

Finite ring array polynomial monic.

Input
  p : a BETA-digit, p a prime.
  M : in Z/(p)[x], M is in array representation.
  A : in (Z/(p)[x])/(M)[y], A is in array representation.

Output
  B : in (Z/(p)[x])/(M)[y].  If A = 0, then B = 0.  If A is non-zero 
      and ldcf(A) is a unit in (Z/(p)[x])/(M), then B is the monic 
      polynomial similar to A.  Otherwise deg(B) = -1.
      B is in array representation.
==========================================================================*/
#include "saclib.h"

Word **FRAPMON(p,M,A)
       Word p,*M,**A;
{
       Word **B,d,*a,*ap,i;
  
Step1: /* A = 0 */
       if (FRAPZERO(A)) {
	  B = FRAPFMD(0,MAPDEG(M));
	  goto Return; }

Step2: /* Compute inverse of leading coefficient. */
       a = FRAPLDCF(A);
       ap = FREINV(p,M,a);

Step3: /* Leading coefficient is not a unit. */
       if (MAPDEG(ap) < 0)  {
	  B = FRAPFMD(0,MAPDEG(M));
	  FRAPDEG(B) = -1;
          goto Step6; }
       
Step4: /* Initialize result. */
       d = FRAPDEG(A);
       B = FRAPGET(d,MAPDEG(M));
       FRAPDEG(B) = d;
       a = FRAPLDCF(B);
       MAPDEG(a) = 0;
       MAPLDCF(a) = 1;

Step5: /* Multiply. */
       for (i = 0; i < d; i++)
	  FREPROD(p,M,FRAPCF(A,i),ap,FRAPCF(B,i));

Step6: /* Free array. */
       MAPFREE(ap);

Return: /* Prepare for return. */
       return(B);
}
