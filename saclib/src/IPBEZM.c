/*=======================================================================
                         M <- IPBEZM(r,A,B)

Integral polynomial Bezout matrix.

Inputs
   r : a positive beta-digit.
   A, B : integral polynomials in r variables with deg(A) >= deg(B) >= 1.

Output
   M : the Bezout matrix of A and B, a square matrix of order deg(A),
       represented row-wise as a list of lists.
=======================================================================*/
#include "saclib.h"

Word IPBEZM(r,A,B)
	BDigit r;
	Word A,B;
{
	BDigit a,b,e,k,m,n;
	Word Ab,Ap,Bb,Bp,C,D,E,L,L2,Lp,M;
	Word V;

Step1: /* Get the degrees, m and n. */
	m = PDEG(A);
	n = PDEG(B);

Step2: /* Compute the n Bezout polynomials. */
	L = NIL;
	for (k = 1; k <= n; k++) {
	   Ap = A;
	   while (Ap != 0 && PDEG(Ap) > m - k)
	      Ap = PRED(Ap);
	   Bp = B;
	   Bb = NIL;
	   while (Bp != NIL && FIRST(Bp) > n - k) {
	      ADV2(Bp,&e,&b,&Bp);
	      Bb = COMP2(b,e - n + k - 1,Bb); }
	   Bb = INV(Bb);
	   C = IPPROD(r,Ap,Bb);
	   Bp = B;
	   while (Bp != 0 && PDEG(Bp) > n - k)
	      Bp = PRED(Bp);
	   Bp = PMPMV(Bp,m - n);
	   Ap = A;
	   Ab = NIL;
	   while (Ap != NIL && FIRST(Ap) > m - k) {
	      ADV2(Ap,&e,&a,&Ap);
	      Ab = COMP2(a,e - m + k - 1,Ab); }
	   Ab = INV(Ab);
	   D = IPPROD(r,Bp,Ab);
	   E = IPDIF(r,D,C);
	   L = COMP(E,L); }

Step3: /* Append the m - n multiples of B. */
	L2 = NIL;
	for (k = m - n - 1; k >= 0; k--) {
	   E = PMPMV(B,k);
	   L2 = COMP(E,L2); }
	L2 = INV(L2);
	L = CONC(L,L2);

Step4: /* Make a matrix of the polynomial coefficients. */
	M = MCPMV(m,L);

Return: /* Return M. */
	return(M);
}
