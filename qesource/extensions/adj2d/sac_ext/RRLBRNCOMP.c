/*======================================================================
                       d <- RRLBRNCOMP(A,I,j,t)

Real root logarithmic binary rational number comparison.

Inputs
   A : a sqarefree univariate integral polynomial.
   I : an open logartihmic interval isolating a root of A.
   j : a logarithmic binary rational number.
   t : the trend of A in I, a value of 2 indicates trend unknown.

Output
   d : (A,I) defines a real number, d is -1 if (A,I) < j, 
       1 if (A,I) > j,  0 if (A,I) = j.

======================================================================*/
#include "sac_ext.h"

Word RRLBRNCOMP(Word A, Word I, Word j, Word t)
{
       Word i1,i2,d,s;

Step1: /* See if an easy decision can be made. */
       FIRST2(I,&i1,&i2);
       if (LBRNCOMP(j,i1) <= 0) {
	 d = 1;
	 goto Return; }
       if (LBRNCOMP(i2,j) <= 0) {
	 d = -1;
	 goto Return; }

Step2: /* Evaluate A at j. */
       s = IUPBRES(A,j);
       if (s == 0) {
	 d = 0;
	 goto Return;
       }

Step3: /* Compute trend if necessary. */
       if (t == 2)
	 t = IUPTSII(A,I);

Step4: /* Decide */
       if (t == s)
	 d = -1;
       else
	 d = 1;

Return: /* Prepare to return. */
       return d;
}
