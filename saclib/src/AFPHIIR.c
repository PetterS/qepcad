/*======================================================================
                           L <- AFPHIIR(n,I,A,k)

Algebraic field polynomial hardware interval isolation and
refinement.

Inputs
   n : a positive beta-digit.
   I : a hardware interval containing an algebraic number \alpha
       of degree n.
   A : a univariate polynomial of positive degree over the
       algebraic number field Q(\alpha).  Each nonzero coefficient
       of A is represented by a pair (r,a) where r is a
       rational number and a is an integral polynomial of
       degree less than n,
   k : a beta-digit.

Output
   L : either 0 or a list of isolating intervals for the real
       roots of A.  A(x) is converted to a hardware interval
       polynomial B(x) using I.  If the real roots of B(x)
       cannot be isolated L = 0, a failure condition.  
       Otherwise L is a list of logarithmic binary rational
       intervals for A(x).  Each interval is either a one-point
       interval, an interval of width 1 / 2^k, or wider in
       case width 1 / 2^k can not be achieved using hardware
       interval airthmetic.

Remark
   AFPHIIR is floating-point overflow-underflow protected.
======================================================================*/
#include "saclib.h"

Word AFPHIIR(n,I,A,k)
	BDigit n;
	interval I;
	Word A;
	BDigit k;
{
	interval *B,Jp,K;
	BDigit h,j,m,t,T,u,s;
	Word J,Kp,L,Lp,w;

Step1: /* Convert A to an interval polynomial B. */
	AFPHIP(I,A,&B,&T);
	if (T == 0) {
	   L = 0;
	   goto Return; }

Step2: /* Isolate the roots of B. */
	m = PDEG(A);
	HIPRRID(m,B,&L,&s);
	if (L == 0)
	   goto Return;
	   
Step3: /* Determine the trend of the first interval. */
	if (B[m].left > 0) {
	   if (EVEN(m))
	      t = -1;
	   else
	      t = +1; }
	else {
	   if (EVEN(m))
	      t = +1;
	   else
	      t = -1; }

Step4: /* Refine the isolating intervals. */
	Lp = L;
	while (Lp != NIL) {
	   J = FIRST(Lp);
	   w = LBRIW(J);
	   if (w != 0) {
	      h = SECOND(w);
	      if (h < k) {
	         LBRIHI(J,&Jp,&u);
	         if (u == 0) {
	            L = 0;
	            goto Return; }
	         HIPIR(m,B,Jp,t,h,k,&K,&j);
	         Kp = HILBRI(K);
	         SFIRST(Lp,Kp); } }
	   Lp = RED(Lp);
	   t = - t; }

Return: /* Return L. */
	return(L);
}
