/*===========================================================================
			 MMAPREM(m,A,B)

Medium modulus array polynomial remainder.  

Inputs
  m : a medium prime.
  A,B : in Z/(p)[x], A and B are in array representation.

Side effect
  A is replaced by the remainder of A with respect to B.
===========================================================================*/
#include "saclib.h"

void MMAPREM(m,A,B)
       Word m,*A,*B;
{
       Word a,ap,d,e,k,*Bp;

Step1: /* Get degrees. */  
       d = MAPDEG(A);
       e = MAPDEG(B);
       
Step2: /* deg(B) = 0. */
       if (e == 0) {
	  MAPDEG(A) = 0;
	  MAPCF(A,0) = 0;
	  goto Return; }

Step3: /* Is B monic? */
       if (MAPLDCF(B) == 1)
	  Bp = B;
       else
	  Bp = MMAPMON(m,B);

Step4: /* Subtraction loop. */
       while (d >= e) { 
	  a = MAPLDCF(A);
	  k = d - e;
	  ap = MDNEG(m,a); 
	  MMAPMADD(m,Bp,ap,k,A);
	  while (MAPCF(A,d) == 0 && d > 0) 
	     d--;
	  MAPDEG(A) = d; }

Step5: /* Free array. */
       if (B != Bp)
	  MAPFREE(Bp);

Return: /* Prepare for return. */
       return;
}
