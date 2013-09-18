/*===========================================================================
			    IPRODAP(A,n1,B,n2; n3)

Integer product - array multiplication in place.

Inputs
  n1,n2: non-negative beta-digits.
  A, B : arrays that contain non-negative integers A',B'
         of BETA-length n1, n2, respectively.
         Array A has length >= n1 + n2.

Effect : Array A contains the product A' * B'.

Outputs
  n3   : a non-negative BETA-digit. n3 is the BETA-length of A' * B'.
===========================================================================*/
#include "saclib.h"

void IPRODAP(A,n1,B,n2, n3_)
        Word *A,n1,*B,n2,*n3_;
{
        Word a,c,c0,c1,cp,i,j,k,n3;

Step1: /* A' = 0 or B' = 0. */
       if (n1 == 0 || n2 == 0) {
          n3 = 0;
          goto Return; }

Step2: /* Multiply by A[n1-1]. */
       i = n1 - 1;
       a = A[i];
       DPR(a,B[0],&cp,&A[i]);
       k = n1;
       for (j = 1; j < n2; j++) {
          DPR(a,B[j],&c1,&c0);
          c = c0 + cp;
          cp = c >> ZETA;
          A[k] = c & BETA1;
          cp = cp + c1;
          k++; }
       A[k] = cp;

Step3: /* Multiply by A[n1-2],...,A[0]. */
       while (i > 0) {
          k = i;
          i--;
          a = A[i];
          DPR(a,B[0],&cp,&A[i]);
          for (j = 1; j < n2; j++) {
             DPR(a,B[j],&c1,&c0);
             c = A[k] + c0 + cp;
             cp = c >> ZETA;
             A[k] = c & BETA1;
             cp = cp + c1;
             k++; }
          do {
             c = A[k] + cp;
             cp = c >> ZETA;
             A[k] = c & BETA1;
             k++; }
          while (cp != 0); }

Step4: /* Determine length of result. */
       n3 = n1 + n2 - 1;
       if (A[n3] != 0)
          n3++;

Return: /* Prepare for return. */
        *n3_ = n3;
	return;
}
