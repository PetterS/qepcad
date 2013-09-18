/*======================================================================
                           SIPEVAL(A,I,J)

Software interval polynomial evaluation.

Inputs
   A : a software interval polynomial.  Let p be its precision.
   I : a software interval of precision p.
   J : an array of (at least) 2 * p + 6 words.

Effect
   A software interval of precision p containing A(I) is placed in J.
======================================================================*/
#include "saclib.h"

void SIPEVAL(A,I,J)
       BDigit *A,*I,*J;
{
	BDigit i,*J1,*J2,n,p,q,s;

Step1: /* Apply Horner's method. */
	n = A[0];
	p = A[3];
	q = 2 * (p + 3);
	J1 = GETARRAY(q);
	J2 = GETARRAY(q);
	s = n * q + 1;
	SICOPY(A + s,J1);
	for (i = n - 1; i >= 0; i--) {
	   s = s - q;
	   SIPROD(J1,I,J2);
	   SISUM(J2,A + s,J1); }
	SICOPY(J1,J);
	FREEARRAY(J1);
	FREEARRAY(J2);

Return: /* Return. */
	return;
}
