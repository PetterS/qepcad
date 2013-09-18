/*===========================================================================
			     B <- IUPBHT(A,k)

Integral univariate polynomial binary homothetic transformation.

Inputs
  A : in Z[X], A non-zero.
  k : a BETA-digit.

Outputs
  B : in Z[X], B(X) = 2^(-h) * A(2^k*X),
      where h is uniquely determined so that B is an
      integral polynomial not divisible by 2.
===========================================================================*/
#include "saclib.h"

Word IUPBHT(A,k)
       Word A,k;
{
       Word Ap,B,a,b,e,h,m,n;

Step1: /* Compute h. */
       Ap = A;
       h = BETA;
       do {
	  ADV2(Ap,&e,&a,&Ap);
	  m = IORD2(a);
	  n = k * e + m;
	  if (n < h)
	     h = n; }
       while (Ap != NIL);

Step2: /* Compute B. */
       Ap = A;
       B = NIL;
       do {
	  ADV2(Ap,&e,&a,&Ap);
	  b = ITRUNC(a,h - k * e);
	  B = COMP2(b,e,B); }
       while (Ap != NIL);
       B = INV(B);

Return: /* Prepare for return. */
       return(B);
}
