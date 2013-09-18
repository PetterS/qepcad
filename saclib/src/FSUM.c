/*======================================================================
                        FSUM(A,B,d,C)

Floating-point sum.

Inputs
 
   A, B : floating-point numbers.
   d : a sign (rounding direction).
   C : an array large enough for the sum.

Output
   C : a floating-point number approximating the sum of A and B,
       rounded according to IEEE standards.  If A and B are both
       non-zero, the precision of C is the maximum of the precisions
       of A and B. If A = 0, C = B and C has the same precision as B;
       if B = 0, C = A and C has the same precision as A.
======================================================================*/
#include "saclib.h"

void FSUM(A,B,d,C)
	Word *A,*B;
        BDigit d;
	Word *C;
{
        Word *Ap,*Bp,*D;
	BDigit i,p,q;

Step1: /* A or B zero. */
	if (A[1] == 0) {
	   FCOPY(B,C);
	   goto Return; }
	if (B[1] == 0) {
	   FCOPY(A,C);
	   goto Return; }

Step2: /* Make precisions equal. */
	Ap = A;
	Bp = B;
	p = A[2];
	q = B[2];
	if (p != q) {
	  if (p < q) {
	    D = GETARRAY(q+3);
	    Ap = D;
	    Ap[0] = A[0];
	    Ap[1] = A[1];
	    Ap[2] = q;
	    for (i=3; i<=q-p+2; i++)
	      Ap[i] = 0;
	    for (i=q-p+3; i<=q+2; i++)
	      Ap[i] = A[i-(q-p)]; }
	  else {
	    D = GETARRAY(p+3);
	    Bp = D;
	    Bp[0] = B[0];
	    Bp[1] = B[1];
	    Bp[2] = p;
	    for (i=3; i<=p-q+2; i++)
	      Bp[i] = 0;
	    for (i=p-q+3; i<=p+2; i++)
	      Bp[i] = B[i-(p-q)]; } }

Step3: /* Branch according to case. */
	if (Ap[0] == Bp[0]) {
	  if (Ap[1] == Bp[1])
	     FSUMSESS(Ap,Bp,d,C);
	   else
	     FSUMSEOS(Ap,Bp,d,C);
	}
	else {
	  if (Ap[1] == Bp[1])
	    FSUMDESS(Ap,Bp,d,C); 
	  else if (Ap[0] - Bp[0] == 1)
	    FSUMDEOS1(Ap,Bp,d,C);
	  else if (Bp[0] - Ap[0] == 1)
	    FSUMDEOS1(Bp,Ap,d,C);
	  else if (Ap[0] - Bp[0] > 0)
	    FSUMDEOS2(Ap,Bp,d,C);
	  else
	    FSUMDEOS2(Bp,Ap,d,C);
	}

Step4: /* Release array. */
	if (p != q)
	  FREEARRAY(D);

Return: /* Return. */
	return; 
}
