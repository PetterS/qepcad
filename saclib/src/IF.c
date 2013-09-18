/*======================================================================
                           IF(I,p,d,A)

Integer to floating.

Inputs
   I : an integer.
   p : a beta digit, the desired precision.
   d : -1, 0 or +1, the rounding direction.
	-1 : down
	 0 : nearest (mantissa even in case of a tie)
	+1 : up
   A :  an array of size at least p + 3.

Effect
   The specified p-precision software floating point number is placed
   in A.
========================================================================*/
#include "saclib.h"

void IF(I,p,d,A)
	Word I;
	BDigit p,d,*A;
{
	BDigit a,b,e,i,k,m,M,n,s,t;
        Word J;

Step1: /* I = 0. */
        if (I == 0) {
           A[0] = 0;
           A[1] = 0;
           A[2] = p;
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
        n = ZETA - PDLOG2(A[p + 2]);
        if (n > 0)
           ILSA(A + 2,p + 1,n);
        e = (p + 2 - k) * ZETA - n;

Step5:/* Exact conversion. */
        m = LENGTH(J);
        if (m > 0)
           e = e + m * ZETA;
	A[0] = e;
        A[1] = s;
        t = 0;
        while (t == 0 && J != NIL) {
           t = FIRST(J);
           if (t == 0)
              J = RED(J); }
        if (t == 0 && A[2] == 0)
	   goto Step8;

Step6: /* Decide whether to round up absolute value. */
	if (d == s)
	   goto Step7;
	else if (d == -s)
	   goto Step8;
	else {
	   M = BETA1 >> n;
	   b = A[2] & M;
	   b = b << (ZETA - n);
	   if (b > BETA2)
	      goto Step7;
	   else if (b < BETA2)
	      goto Step8;
	   else if (t != 0)
	      goto Step7;
	   else {
	      b = A[3] & 1;
	      if (b == 1)
	         goto Step7;
	      else
	         goto Step8; } }

Step7: /* Round up absolute value. */
	t = 1;
        i = 3;
        while (t > 0 && i < p + 3) {
           A[i] = A[i] + 1;
           if (A[i] == BETA)
              A[1] = 0;
           else
              t = 0;
           i = i + 1; }
        if (A[p + 2] == 0) {
           A[p + 2] = BETA2;
           A[0] = e + 1; }

Step8: /* Store precision. */
	A[2] = p;

Return: /* return. */
	return;
}
