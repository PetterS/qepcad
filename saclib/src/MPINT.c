/*===========================================================================
			As <- MPINT(p,B,b,bp,r,A,A1)

Modular polynomial interpolation.

Inputs
  p  : a prime BETA-digit.
  B  : in Z/(p)[x_1].
  b  : in Z/(p), such that B(b) /= 0.
  bp : in Z/(p), such that bp = B(b)^(-1).
  r  : a BETA-digit, r >= 1.
  A  : in Z/(p)[x_1,...,x_r] with A = 0 or the degree
       of A in x_1 less than the degree of B.
  A1 : in Z/(p)[x_2,...,x_r].

Outputs
  As : in Z/(p)[x_1,...,x_r], the unique polynomial
       such that As(x_1,...,x_r) is congruent to  
       A(x_1,...,x_r) modulo B(x_1), 
       As(b,x_2,...,x_r) = A1(x_2,...,x_r) and 
       the degree of As in x_1 is less than or equal
       to the degree of B.
===========================================================================*/
#include "saclib.h"

Word MPINT(p,B,b,bp,r,A,A1)
       Word p,B,b,bp,r,A,A1;
{
       Word Ap,Ap1,As,a,a1,as,c,d,e,e1,es,n,rp;

Step1: /* Deg(B) = 0. */
       n = PDEG(B);
       if (n == 0) {
	  As = PINV(r - 1,A1,1);
	  goto Return; }

Step2: /* r = 1. */
       if (r == 1) {
	  a = MPEMV(1,p,A,b);
	  d = MDDIF(p,A1,a);
	  if (d == 0)
	     As = A;
	  else {
	     c = MDPROD(p,d,bp);
	     As = MPSUM(1,p,MPMDP(1,p,c,B),A); }
	  goto Return; }

Step3: /* r > 1. */
       As = NIL;
       rp = r - 1;
       if (A == 0)
	  Ap = NIL;
       else
	  Ap = A;
       if (A1 == 0)
	  Ap1 = NIL;
       else
	  Ap1 = A1;
       while (Ap != NIL || Ap1 != NIL) {
	  if (Ap == NIL) {
	     a = 0;
	     ADV2(Ap1,&es,&a1,&Ap1); }
	  else
	     if (Ap1 == NIL) {
		a1 = 0;
		ADV2(Ap,&es,&a,&Ap); }
	     else {
		e = PDEG(Ap);
		e1 = PDEG(Ap1);
		es = MAX(e,e1);
		a = 0;
		a1 = 0;
		if (e == es)
		   ADV2(Ap,&e,&a,&Ap);
		if (e1 == es)
		   ADV2(Ap1,&e1,&a1,&Ap1); }
	  as = MPINT(p,B,b,bp,rp,a,a1);
	  As = COMP2(as,es,As); }
       if (As == NIL)
	  As = 0;
       else
	  As = INV(As);

Return: /* Prepare for return. */
       return(As);
}
