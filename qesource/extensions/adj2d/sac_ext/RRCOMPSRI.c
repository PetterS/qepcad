/*======================================================================
             t <- RRCOMPSRI(A,i1,i2,B,j1,j2;i1s,i2s,j1s,j2s)

Real root comparison: save refined intervals.

Inputs
   A : a sqarefree univariate integral polynomial.
   i1,i2: (i1,i2) a standard logartihmic interval isolating a root of A.
   B : a sqarefree univariate integral polynomial, gcd(A,B) = 1.
   j1,j2: (j1,j2) a standard logartihmic interval isolating a root of B.

Note:  These isolating intervals are assumed to be open or one-point.

Note2: This is niave at the moment.  There are certainly better 
       strategies for refining.

Outputs                          
   t : 1 if the root of A in (i1,i2) is greater than the root of B in
       (j1,j2).  -1 if the root of B in (j1,j2) is greater than the
       root of A in (i1,i2).  Note: they can never be equal.
======================================================================*/
#include "sac_ext.h"

Word RRCOMPSRI(Word A, Word i1, Word i2, Word B, Word j1, Word j2, Word *i1s, Word *i2s, Word *j1s, Word *j2s)
{
       Word s,i,j,a,b,t;

Step1: /* Initial test for disjointness. */
       s = LBRNCOMP(i1,j2);
       if (s >= 0 || LBRNCOMP(j1,i2) >= 0)
	 goto Return;

Step2: /* Compute trends (opposites of trends actually). */
       a = LBRNSIGN(IUPLBREVAL(A,i1));
       b = LBRNSIGN(IUPLBREVAL(B,j1));

Step3: /* Bisect (i1,i2). */
       if (a == 0) goto Step4;
       i = LSIM(i1,i2);
       t = LBRNSIGN(IUPLBREVAL(A,i));
       if (t == 0) {
	 i1 = i; i2 = i; goto Step4; }
       if (t == a)
	 i1 = i;
       else
	 i2 = i;

Step4: /* Bisect (j1,j2). */
       if (b == 0) goto Step5;
       j = LSIM(j1,j2);
       t = LBRNSIGN(IUPLBREVAL(B,j));
       if (t == 0) {
	 j1 = j; j2 = j; goto Step5; }
       if (t == b)
	 j1 = j;
       else
	 j2 = j;

Step5: /* test for disjointness. */
       s = LBRNCOMP(i1,j2);
       if (s >= 0 || LBRNCOMP(j1,i2) >= 0)
	 goto Return;
       goto Step3;

Return: /* Prepare to return. */
       *i1s = i1; *i2s = i2;
       *j1s = j1; *j2s = j2;
       if (s >= 0)
	 return 1;
       else
	 return -1;
}
