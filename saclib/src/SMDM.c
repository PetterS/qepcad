/*======================================================================
                      M <- SMDM(r,A,B,k)

Sylvester matrix degree matrix.

Inputs
   r : a beta digit, r >= 2.
   A, B : r-variate polynomials of positive degrees.
   k : a beta digit, 1 <= k < r.

Output
  M  : Let S be the Sylvester matrix of A and B.  M is the matrix of
       beta integers such that if S_{i,j} /= 0 then M_{i,j} is the
       degree in x_k of S_{i,j} and otherwise M_[i,j} is 
       -[beta/(m + n)] - 1, where m and n are the degrees of A and B
       in x_r.  M is represented as an arrray of arrays.
======================================================================*/
#include "saclib.h"

BDigit **SMDM(r,A,B,k)
        Word A,B;
	BDigit k,r;
{
	BDigit d,I,i,j,**M,m,n,q;
        Word Ap,Bp;

Step1: /* Get a matrix. */
	m = PDEG(A);
	n = PDEG(B);
	q = m + n;
	M = GETMATRIX(q,q);

Step2: /* Store I = -[beta/(m + n)] - 1 in triangular regions. */
	I = -(BETA/(m + n)) - 1;
	for (i = 1; i < n; i++) {
	   for (j = 0; j < i; j++)
	      M[i][j] = I; }
	for (i = n; i < m + n; i++) {
	   for (j = 0; j < i; j++)
	      M[i][j] = I; }
	for (i = 0; i < n - 1; i++) {
	   for (j = m + i + 1; j < m + n; j++)
	      M[i][j] = I; }
	for (i = n; i < m + n - 1; i++) {
	   for (j = i + 1; j < m + n; j++) 
              M[i][j] = I; }

Step3: /* Store degrees of coefficients of A and B. */
	Ap = A;
	for (j = m; j >= 0; j--) {
	   if (Ap != 0 && PDEG(Ap) == j) {
	      d = PDEGSV(r-1,PLDCF(Ap),k);
	      Ap = PRED(Ap); }
	   else
	      d = I;
	   for (i = 0; i < n; i++)
	      M[i][m-j+i] = d; }
	Bp = B;
	for (j = n; j >= 0; j--) {
	   if (Bp != 0 && PDEG(Bp) == j) {
              d = PDEGSV(r-1,PLDCF(Bp),k) ;
              Bp = PRED(Bp); }
           else
              d = I;
	   for (i = 0; i < m; i++)
	      M[n+i][n-j+i] = d; }

Return: /* Return M. */
	return(M);
}
