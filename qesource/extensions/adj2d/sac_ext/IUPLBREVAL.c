/*======================================================================
                       b <- IUPLBREVAL(A,a)

Integral univariate polynomial logarithmic binary rational evaluation.

Inputs
   A : a univariate integral polynomial.
   a : a logarithmic binary rational number

Outputs                          
   b : the logarithmic binary rational number  A(a).
======================================================================*/
#include "sac_ext.h"

Word IUPLBREVAL(Word A, Word a)
{
       Word b,c,k,N;

Step1: /* Special Cases. */
       if (A == 0 || FIRST(A) == 0 || a == 0) {
	 b = ILBRN(PCFE(A,0));
	 goto Return; }

Step2: /* Call IUPBEI. */
       FIRST2(a,&c,&k);
       if (k >= 0) {
	 N = IUPBEI(A,c,k);
	 b = LBRNFIE(N,-k*PDEG(A)); }
       else {
	 N = IUPEVAL(A,IMP2(c,-k));
	 b = LBRNFIE(N,0); }
       
Return: /* Prepare to return. */
       return b;
}
