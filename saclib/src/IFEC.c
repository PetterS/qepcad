/*======================================================================
                           t <- IFEC(I,p,A)

Integer to floating, exact conversion.

Inputs
   I : an integer.
   p : a positive beta digit, the desired precision.
   A :  an array of size at least p + 3.

Output
   t : 0 or 1.

Effect
   If t = 0, I could not be exactly converted to a p-precision software 
   float and the content of A is undefined.  If t = 1, the p-precision
   software float equal to I is placed in A.
========================================================================*/
#include "saclib.h"

BDigit IFEC(I,p,A)
	Word I;
	BDigit p,*A;
{
	BDigit a,e,i,k,n,s,t;
        Word J;

Step1: /* I = 0. */
        if (I == 0) {
           A[0] = 0;
           A[1] = 0;
           A[2] = p;
	   t = 1;
	   goto Return; }

Step2: /* Invert the list for I. */
	if (I < BETA)
           J = LIST1(I);
        else
           J = CINV(I);

Step3: /* Put the leading p + 1 digits in array A. */
        s = SIGN(FIRST(J));
        k = p + 2;
        while (J != NIL && k >= 2) {
           ADV(J, &a,&J);
           A[k] = ABS(a);
           k = k - 1; }
        for (i = k; i >= 2; i--)
           A[i] = 0;

Step4: /* Normalize. */
        n = ZETA - PDLOG2(A[p+2]);
        if (n > 0)
           ILSA(A + 2,p + 1,n);
        e = (p + 2 - k) * ZETA - n;

Step5:/* Exact conversion? */
	t = 0;
	if (A[2] != 0 )
	   goto Return;
	while (J != NIL) {
	   a = FIRST(J);
	   if (a != 0)
	      goto Return;
	   e = e + ZETA;
	   J = RED(J); }
	t = 1;
	A[0] = e;
	A[1] = s;
	A[2] = p;

Return: /* Return t. */
	return(t);
}
