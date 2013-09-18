/*===========================================================================
                         B <- IUPQS(A)

Integral univariate polynomial quotient substitution.  

Inputs
  A : a univariate integral polynomial.  

Outputs
  B : a bivariate integral polynomial.
      B(X,Y) = (Y^n)*A(X/Y) where n is the degree of A.
===========================================================================*/
#include "saclib.h"

Word IUPQS(A)
       Word A;
{
       Word Ap,a,B,e,n;

Step1: /* A=0. */
       if (A == 0) {
	  B = 0;
	  goto Return; }

Step2: /* A/=0. */
       n = PDEG(A);
       Ap = A;
       B = NIL;
       do {
	  ADV2(Ap,&e,&a,&Ap);
	  B = COMP2(n - e,LIST2(e,a),B); }
       while (Ap != NIL);

Return: /* Prepare for return. */
       return(B);
}
