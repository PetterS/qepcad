/*======================================================================
                           v <- SIPVCHT(A)

Software interval polynomial, variations after circle to half-plane 
transformation.

Input
    A : a software interval polynomial of positive degree.

Output
    v :  A BETA-digit, either 0, 1, 2 or -1.  Let B(x) = x^n A(1/x), 
         C(x) = B(x + 1).
	 If the sign sequence implies that var = 0, v = 0;
	 If the sign sequence implies that var = 1, v = 1;
	 If the sign sequence implies that var >= 2, v = 2;
	 If the sign sequence implies none of the above, v = NIL.
======================================================================*/
#include "saclib.h"

BDigit  SIPVCHT(A)
        BDigit *A;
{
	BDigit *b,*B,*Bp,i,j,m,M,n,p,q2,S,s,t,T,v;

Step1: /* Get arrays. */
	n = A[0];
	p = A[3];
	q2 = p + p + 6;
	b = GETARRAY(q2);
	S = (n + 1) * q2 + 1;
	B = GETARRAY(S);

Step2: /* Compute B(x). */
	SIPR(A,B);

Step3: /* Initialize count variables. */
	t = 0;
	T = 0;
	m = 0;
	M = 0;
	i = 0;

Step4: /* Compute next coefficient of C and its sign. */
	Bp = B + S - q2;
	for (j = n - i; j >= 1; j--) {
	   SISUM(Bp,Bp - q2,b);
	   SICOPY(b,Bp - q2);
	   Bp = Bp - q2; }
	s = SISIGN(Bp);

Step5: /* Update count variables. */
	if (s == NIL) {
	   M = M + 1;
	   T = -T; }
	else if (s != 0) {
	   if (s == - t)
	      m = m + 1;
	   if (s == - T)
	      M = M + 1;
	   t = s;
	   T = s; }

Step6: /* Finished? */
	if (m >= 2) {
	   v = 2;
	   goto Step8; }
	i = i + 1;
	if (i <= n)
	   goto Step4;
	   
Step7: /* Determine value of v. */
	if (m == M)
	   v = m;
	else
	   v = NIL;

Step8: /* Free arrays. */
	FREEARRAY(B);
	FREEARRAY(b);

Return: /* Return v. */
	return(v);
}
