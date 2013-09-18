/*======================================================================
		       b <- IUPBREV(A,a)

Integral univariate polynomial binary rational evaluation.

Inputs
  A : in Z[x].
  a : a logarithmic binary rational number. 

Outputs
  b : b = A(a), a logarithmic binary rational number.
======================================================================*/
#include "saclib.h"

Word IUPBREV(A,a)
       Word A,a;
{
       Word b,c,d,h,k,n;

Step1: /* A = 0. */
       if (A == 0) {
	  b = 0;
	  goto Return; }

Step2: /* Let a = c / 2^k. */
       if (a == 0) {
	  c = 0;
	  k = 0; }
       else
	  FIRST2(a,&c,&k);

Step3: /* If k <= 0 apply IUPEVAL, otherwise IUPBEI. */
       if (k <= 0) {
	  if (k < 0)
	     c = IMP2(c,-k);
	  d = IUPEVAL(A,c); }
       else
	  d = IUPBEI(A,c,k);

Step4: /* Put result in logarithmic representation. */
       if (d == 0)
	  b = 0;
       else {
	  h = IORD2(d);
	  d = IDP2(d,h);
	  if (k <= 0)
	     b = LIST2(d,-h);
	  else {
	     n = PDEG(A);
	     b = LIST2(d,n * k - h); } }

Return: /* Return s. */
       return(b);
}
