/*===========================================================================
			 As <- IPCRA(M,m,mp,r,A,a)

Integral polynomial chinese remainder algorithm.

Inputs
  M  : in Z, M > 0.     
  m  : BETA-digit, m > 0, gcd(M,m)=1. 
  mp : in Z/(m), the inverse of M modulo m. 
  r  : a BETA-digit,r >= 0, the number of variables.
  A  : in Z'/(M)[x_1,...,x_r].  
  a  : in Z/(m) [x_1,...,x_r].

Outputs
  As : in Z'/(Ms)[x_1,...,x_r], where Ms = M * m. 
       As is the unique polynomial which is congruent
       to A modulo M and to a modulo m.
===========================================================================*/
#include "saclib.h"

Word IPCRA(M,m,mp,r,A,a)
       Word M,m,mp,r,A,a;
{
       Word A1,Ap,As,As1,E,Es,a1,ap,e,rp;

Step1: /* r=0. */
       if (r == 0) {
	  As = MIDCRA(M,m,mp,A,a);
	  goto Return; }

Step2: /* General case. */
       if (A == 0)
	  Ap = NIL;
       else
	  Ap = A;
       if (a == 0)
	  ap = NIL;
       else
	  ap = a;
       rp = r - 1;
       As = NIL;
       while (Ap != NIL || ap != NIL) {
	  if (Ap == NIL) {
	     A1 = 0;
	     ADV2(ap,&Es,&a1,&ap); }
	  else
	     if (ap == NIL) {
		a1 = 0;
		ADV2(Ap,&Es,&A1,&Ap); }
	     else {
		E = FIRST(Ap);
		e = FIRST(ap);
		if (E > e) {
		   ADV2(Ap,&Es,&A1,&Ap);
		   a1 = 0; }
		else
		   if (E < e) {
		      ADV2(ap,&Es,&a1,&ap);
		      A1 = 0; }
		   else {
		      ADV2(Ap,&Es,&A1,&Ap);
		      ADV2(ap,&Es,&a1,&ap); } }
	  if (rp == 0)
	     As1 = MIDCRA(M,m,mp,A1,a1);
	  else
	     As1 = IPCRA(M,m,mp,rp,A1,a1);
	  As = COMP2(As1,Es,As); }
       if (As == NIL)
	  As = 0;
       else
	  As = INV(As);

Return: /* Prepare for return. */
       return(As);
}
