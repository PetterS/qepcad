/*======================================================================
                      k <- SIPPRB(A)

Software interval polynomial positive root bound.

Inputs
   A : a software integral polynomial of positive degree such that A[n]
       does not contain zero.

Output
   k : If all nonzero coefficients of A have the same sign, then A
       has no positive roots and k = NIL.  Otherwise k is a positive
       integer such that for all i, 1 <= i <= n, if -a_{n-i} / a_n < 0,
       then  2 |-a_{n-i} / a_n|^{1/i} <=  k, a BETA-digit such that all
       positive roots are less than 2^k.
======================================================================*/
#include "saclib.h"

Word SIPPRB(A)
	BDigit *A;
{
	BDigit d,e,f,i,j,n,p,q,q1,q2,r,S,s,t;
        Word k;

Step1: /* Compute sizes. */
	n = A[0];
	p = A[3];
	q1 = p + 3;
	q2 = q1 + q1;
	S = n * q2 + 1;

Step2: /* Branch on sign of leading coefficient. */
        k = NIL;
        s = A[S+1];
        if (s < 0)
           goto Step4;

Step3: /* A[n] > 0, process terms. */
	e = A[S];
	for (i = n - 1; i >= 0; i--) {
	   S = S - q2; 
	   t = A[S+1];
	   if (t < 0) {
	      f = A[S];
	      j = n - i;
	      d = f - e + 1;
	      QREM(d,j,&q,&r);
              if (r > 0)
                 q = q + 1;
	      if (k == NIL || q > k)
                 k = q; } }
        if (k != NIL)
           k = k + 1;
        goto Return;

Step4: /* A[n] < 0, process terms. */
	S = S + q1;
	e = A[S];
	for (i = n - 1; i >= 0; i--) {
	   S = S - q2;
	   t = A[S+1];
	   if (t > 0) {
              f = A[S];
	      j = n - i;
              d = f - e + 1;
              QREM(d,j,&q,&r);
              if (r > 0)
	         q = q + 1;
              if (k == NIL || q > k)
                 k = q; } }
        if (k != NIL)
           k = k + 1;

Return: /* Return k. */
        return(k);
}
