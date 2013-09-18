/*======================================================================
                      ANCOMPSRI(M,N,f,i1,i2,j1,j2;c,i1s,i2s,j1s,j2s)


Algebraic number comparison, save refined intervals.

Inputs
      M : A primitive sqaurefree univariate integral polynomial.
      N : A primitive sqaurefree univariate integral polynomial.
      f : A flag which, if set to one, tells the function that
          the two algebraic numbers are known to be unequal.  With 
	  this knowledge unneccesary gcd computations may be avoided.
      I : A logarithmic binary rational isolating interval for a root of M.
      J : A logarithmic binary rational isolating interval for a root of N.
Note : The isolating intervals may be open or closed.
Outputs
      c : c = 1 if (M,I) > (N,J), c = 0 if (M,I) = (N,J), c = -1
          if (M,I) < (N,J).
      Is: Refined logarithmic binary rational interval for I.
      Js: Refined logarithmic binary rational interval for J.
======================================================================*/
#include "sac_ext.h"

void ANCOMPSRI(Word M, Word N, Word f, Word I_, Word J_, Word *c_, Word *i1s, Word *i2s, Word *j1s, Word *j2s)
{
       Word I,J,C,d1,d2,s1,s2,c,t,tM,tN;

Step1: /* Initialization. */
       tM = 0;
       tN = 0;
       

Step2: /* Is decision possible? */
       t = LBRNCOMP(i1,j2);
       
	 goto Step5;
       
Step3: /* */
       tM = LBRNSIGN(IUPLBREVAL(M,SECOND(I)));
       tN = LBRNSIGN(IUPLBREVAL(N,SECOND(I)));

Step4: /* Refine isolating intervals. */
       if (
       goto Step3;

Step5: /* Make decision. */
       if (t)
	 c = 1;
       else
	 c = -1;

Return: /* Return. */
       *Is = I;
       *Js = J;
       *c_ = c;
}
