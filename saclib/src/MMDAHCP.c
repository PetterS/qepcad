/*===========================================================================
                          C <- MMDAHCP(p,A,n)

Matrix of modular digits array representation Hessenberg form -
characteristic polynomial.  (A matrix is in Hessenberg form if
its entries below the first diagonal are all zero.)

Input
  p : a BETA-digit, prime.
  A : a square matrix in array representation over Z/(p) - Hessenberg form.
  n : a positive BETA-digit, the order of A.

Output
  C : in Z/(p)[X], C = det(A-X*I), the characteristic polynomial of A.

Remarks
  The submatrices (a_{i,j}) 0<=i,j<=k of A are again Hessenberg matrices;
  their determinants are computed by expansion along the last column.
===========================================================================*/
#include "saclib.h"

Word MMDAHCP(p,A,n)
       BDigit p;
       Word **A;
       BDigit n;
{
       BDigit b,bp,bs,f,j,k,s;
       Word B,Bp,C,c,D,F,L,Lp;

Step1: /* Initialize. */
       C = MPDIF(1,p,PMON(A[0][0],0),PMON(1,1));
       if (n == 1)
	 goto Return;
       L = LIST2(C,PMON(1,0));
       B = NIL;

Step2: /* Loop on order of square submatrix at the top left. */
       k = 1;

Step3: /* Products of lower diagonal elements.*/
       bs = A[k][k-1];
       Bp = NIL;
       while (B != NIL) {
	 ADV(B,&b,&B);
	 bp = MDPROD(p,bs,b);
	 Bp = COMP(bp,Bp); }
       B = INV(Bp);
       B = COMP(bs,B);

Step4: /* Characteristic polynomial of submatrix.*/
       Lp = L;
       ADV(Lp,&C,&Lp);
       D = MPDIF(1,p,PMON(A[k][k],0),PMON(1,1));
       C = MPPROD(1,p,D,C);
       Bp = B;
       s = -1;
       for (j = k-1; j >= 0; j--) {
	 ADV(Lp,&c,&Lp);
	 ADV(Bp,&b,&Bp);
	 f = MDPROD(p,A[j][k],b);
	 F = MPMDP(1,p,f,c);
	 if (s < 0)
	   C = MPDIF(1,p,C,F);
	 else
	   C = MPSUM(1,p,C,F);
	 s = -s; }
       L = COMP(C,L);

Step5: /* Loop back. */
       if (k<n-1) {
	 k++;
	 goto Step3; }

Return: /* Prepare for return. */
        return(C);
}
