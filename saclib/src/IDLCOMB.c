/*===========================================================================
		  IDLCOMB(A,m,B,n,u1,v1,u2,v2,s,t; mp,np)

Integer double linear combination.

Inputs
   A, B : arrays containing integers A' and B', |A'| >= |B'|, with
          A and B having lengths of at least m + 2.
   m, n : the lengths in BETA-digits of A' and B', respectively.
   u1, v1, u2, v2:  BETA-digits.
   s, t : the signs of the integers A'' and B'', respectively (see below).

Outputs
   mp, np : The lengths in BETA-digits of A'' = u1 * A' + v1 * B' and
            B'' = u2 * A' + v2 * B', respectively.

Side effects
   A'' replaces A' in A and B'' replaces B' in B.
===========================================================================*/
#include "saclib.h"

void IDLCOMB(A,m,B,n,u1,v1,u2,v2,s,t, mp_,np_)
       Word *A,m,*B,n,u1,v1,u2,v2,s,t, *mp_,*np_;
{
       Word a,a0,a1,b,b0,b1,c0,c1,d0,d1,i,mp,np;

Step1: /* Multiply and add. */
       c1 = 0;
       d1 = 0;

       for (i = 0; i < m; i++) {
	  a = A[i];
	  if (i < n)
	     b = B[i];
	  else
	     b = 0;

	  DPR(a,u1,&a1,&a0);
	  DPR(b,v1,&b1,&b0);
	  c0 = a0 + b0 + c1;
	  c1 = a1 + b1;

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
	  A[i] = c0;

	  DPR(a,u2,&a1,&a0);
	  DPR(b,v2,&b1,&b0);
	  d0 = a0 + b0 + d1;
	  d1 = a1 + b1;

	  if (t > 0) {
	     while (d0 <= 0) {
		d0 += BETA;
		d1--; }
	     while (d0 >= BETA) {
		d0 -= BETA;
		d1++; } }
	  else {
	     while (d0 > 0) {
		d0 -= BETA;
		d1++; }
	     while (d0 <= -BETA) {
		d0 += BETA;
		d1--; } }
	  B[i] = d0; }

       if (absm(c1) >= BETA) {
	  if (s > 0) {
	     A[m] = c1 - BETA;
	     A[m+1] = 1; }
	  else {
	     A[m] = c1 + BETA;
	     A[m+1] = -1; }
	  mp = m + 2; }
       else {
	  A[m] = c1;
	  mp = m + 1; }
	  
       if (absm(d1) >= BETA) {
	  if (t > 0) {
	     B[m] = d1 - BETA;
	     B[m+1] = 1; }
	  else {
	     B[m] = d1 + BETA;
	     B[m+1] = -1; }
	  np = m + 2; }
       else {
	  B[m] = d1;
	  np = m + 1; }

Step2: /* Determine lengths. */
       while (mp > 0 && A[mp-1] == 0)
          mp--;
       while (np > 0 && B[np-1] == 0)
	  np--;

Return: /* Prepare for return. */
       *mp_ = mp;
       *np_ = np;
       return;
}
