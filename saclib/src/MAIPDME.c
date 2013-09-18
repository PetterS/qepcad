/*===========================================================================
                              D <- MAIPDME(r,M)

Matrix of integral polynomials determinant, minors expansion method.

Inputs
   r : a non-negative beta digit.
   M : a square matrix over Z[x_1,...,x_r].  M is row-wise 
       represented as a list of lists of polynomials.

Output
   D : the determinant of M.
======================================================================*/
#include "saclib.h"

Word MAIPDME(r,M)
	BDigit r;
	Word M;
{
	BDigit c,cp,i,j,k,n,*C,t;
	Word **A,B,B1,B2,B3,D,L,Lp,Mp,M1,M11;

Step1: /* n = 1. */
	n = LENGTH(M);
	if (n == 1) {
	   D = FIRST(FIRST(M));
	   goto Return; }

Step2: /* Copy M into an array. */
	A = GETMATRIX(n,n);
	Mp = M;
	for (i = 0; i < n; i++) {
	   ADV(Mp,&M1,&Mp);
	   for (j = 0; j < n; j++) {
	      ADV(M1,&M11,&M1);
	      A[i][j] = M11; } }

Step3: /* Compute a list of the order 2 minors. */
	C = GETARRAY(2);
	C[0] = 0;
	C[1] = 1;
	L = NIL;
	while (C[0] >= 0) {
	   i = C[0];
	   j = C[1];
	   B1 = IPPROD(r,A[n-2][i],A[n-1][j]);
	   B2 = IPPROD(r,A[n-2][j],A[n-1][i]);
	   B = IPDIF(r,B1,B2);
	   c = CSFAM(2,C);
	   L = COMP2(B,c,L);
	   LEXNEXTC(n,2,C,&t); }
	L = INV(L);

Step4: /* For k = 3,...,n, compute a list of the order k minors. */
	for (k = 3; k <= n; k++) {
	   C = GETARRAY(k);
	   for (i = 0; i < k; i++)
	      C[i] = i;
	   Lp = NIL;
	   while (C[0] >= 0) {
	      c = CSFAM(k,C);
	      B = 0;
	      for (i = 0; i < k; i++) {
	         j = C[i];
	         B1 = A[n-k][j];
	         cp = c - (1 << j);
	         B2 = TLIL(cp,L);
	         B3 = IPPROD(r,B1,B2);
	         if (EVEN(i))
	            B = IPSUM(r,B,B3);
	         else
	            B = IPDIF(r,B,B3); }
	      Lp = COMP2(B,c,Lp);
	      LEXNEXTC(n,k,C,&t); }
	   L = INV(Lp); }
	D = SECOND(L);

Step5: /* Free the matrix A. */
	FREEMATRIX(A,n);

Return: /* Return D. */
	return(D);
}
