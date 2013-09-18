/*======================================================================
                      t <- IUPTSII(A,I)

Integral univariate polynomial trend in standard isolating interval.

Inputs
  A : a squarefree primitive integral polynomial
  I : an open or one-point standard interval isolating a root of A.

Outputs
  t : the trend of A in I, i.e. the sign of A' at the root of A in I.
======================================================================*/
#include "sac_ext.h"

Word IUPTSII(Word A, Word I)
{
       Word i1,i2,Ap,t,a;
  
Step1: /* One-point interval. */
       FIRST2(I,&i1,&i2);
       if (LBRNCOMP(i1,i2) == 0) {
	 Ap = IPDER(1,A,1);
	 t = IUPBRES(Ap,i2);
       goto Return; }

Step2: /* Open interval. */
       t = IUPBRES(A,i2);
       if (t == 0) {
	 Ap = IPDER(1,A,1);
	 t = -IUPBRES(Ap,i2); }
       
Return: /* Prepare to return. */
       return t; 
}
