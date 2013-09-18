/*===========================================================================
			  ISLCOMB(A,m,B,v,s; mp)

Integer special linear combination.

Inputs
   A, B : arrays containing integers A' and B', with A having length
          at least max(m,n) + 2.
   m, n : the lengths in BETA-digits of A' and B', respectively.
   v    : a BETA-digit.
   s : the sign of A'' = A' + v * B'.

Outputs
   mp : The length in BETA-digits of A''.

Side effects
   A'' replaces A' in A.
===========================================================================*/
#include "saclib.h"

void ISLCOMB(A,m,B,n,v,s, mp_)
       Word *A,m,*B,n,v,s, *mp_;
{
       Word a,b,b0,b1,c0,c1,i,k,mp;

Step1: /* Multiply and add. */
       c1 = 0;
       k = maxm(m,n);

       for (i = 0; i < k; i++) {
	  if (i < m)
	     a = A[i];
	  else
	     a = 0;
	  if (i < n)
	     b = B[i];
	  else
	     b = 0;

	  DPR(v,b,&b1,&b0);
	  c0 = a + b0 + c1;
	  c1 = b1;

	  if (s > 0) {
	     while (c0 <= 0) {
		c0 += BETA;
		c1--; }
	     while (c0 >= BETA) {
		c0 -= BETA;
		c1++; } }
	  else {
	     while (c0 > 0) {
		c0 -= BETA;
		c1++; }
	     while (c0 <= -BETA) {
		c0 += BETA;
		c1--; } }
	  A[i] = c0; }

       if (absm(c1) >= BETA) {
	  if (s > 0) {
	     A[k] = c1 - BETA;
	     A[k+1] = 1; }
	  else {
	     A[k] = c1 + BETA;
	     A[k+1] = -1; }
	  mp = k + 2; }
       else {
	  A[k] = c1;
	  mp = k + 1; }
	  
Step2: /* Determine lengths. */
       while (mp > 0 && A[mp-1] == 0)
	  mp--;

Return: /* Prepare for return. */
       *mp_ = mp;
       return;
}
