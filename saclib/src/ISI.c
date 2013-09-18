/*======================================================================
                           ISI(I,p,A)

Integer to software interval.

Inputs
   I : an integer.
   p : a beta digit, the desired precision.
   A :  an array of size at least 2 p + 6.

Effect
   The smallest p-precision software floating point interval containing
   I is placed in A.
======================================================================*/
#include "saclib.h"

void ISI(I,p,A)
       Word I;
       BDigit p,*A;
{
	BDigit a,*B,*C,e,i,k,m,n,s,t;
	Word J;

Step1: /* I = 0. */
	if (I == 0) {
	   A[0] = 0;
	   A[1] = 0;
	   A[2] = p;
	   A[p + 3] = 0;
	   A[p + 4] = 0;
	   A[p + 5] = p;
	   goto Return; }

Step2: /* Invert the list for I. */
	if (I < BETA)
	   J = LIST1(I);
	else
	   J = CINV(I);

Step3: /* Put the leading p + 1 digits in an array B. */
	s = SIGN(FIRST(J));
	B = GETARRAY(p + 1);
	k = p;
	while (J != NIL && k >= 0) {
	   ADV(J, &a,&J);
	   B[k] = ABS(a);
	   k = k - 1; }
	if (k >= 0) {
           for (i = k; i >= 0; i--) 
              B[i] = 0; }

Step4: /* Normalize. */
	n = ZETA - PDLOG2(B[p]);
	if (n > 0)
	   ILSA(B,p + 1,n);
	e = (p - k) * ZETA - n;

Step5:/* Exact conversion. */
	m = LENGTH(J);
	if (m > 0)
	   e = e + m * ZETA;
	A[0] = e;
        A[1] = s;
        A[2] = p;
	A[p + 3] = e;
	A[p + 4] = s;
	A[p + 5] = p;
	t = 0;
	while (t == 0 && J != NIL) {
	   t = FIRST(J);
	   if (t == 0)
	      J = RED(J); }
	if (t == 0 && B[0] == 0) {
	   AWCOPY(B + 1,p,A + 3);
	   AWCOPY(B + 1,p,A + p + 6);
	   goto Step7; }

Step6: /* Round. */
	C = GETARRAY(p);
	AWCOPY(B + 1,p,C);
	t = 1;
        i = 1;
        while (t > 0 && i <= p) {
           B[i] = B[i] + 1;
           if (B[i] == BETA)
              B[i] = 0;
           else
              t = 0;
           i = i + 1; }
        if (B[p] == 0) {
           B[p] = BETA2;
	   e = e + 1; }
	if (s > 0) {
	   AWCOPY(B + 1,p,A + p + 6);
           AWCOPY(C,p,A + 3);
           A[p + 3] = e; }
	else {
	   AWCOPY(B + 1,p,A + 3);
           AWCOPY(C,p,A + p + 6);
           A[0] = e; }
	FREEARRAY(C);

Step7: /* Free array B. */
	FREEARRAY(B);

Return: /* return. */
       return;
}
