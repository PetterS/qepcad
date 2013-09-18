/*===========================================================================
			      PADV(A; e,a,Ap)

Polynomial advance.

Input
  A : in R[x], where R is a ring.

Outputs
  e : a BETA-digit, the degree of A.
  a : in R, the leading coefficient of A.
  Ap : in R[x], the reductum of A.
===========================================================================*/
#include "saclib.h"

void PADV(A,e_,a_,Ap_)
       Word A,*e_,*a_,*Ap_;
{
       Word e,a,Ap;

Step1: /* Compute. */
       if (A == 0) {
	  e = 0;
	  a = 0;
	  Ap = 0; }
       else {
	  ADV2(A,&e,&a,&Ap);
	  if (Ap == NIL)
	     Ap = 0; }

Return: /* Prepare for return. */
       *e_ = e;
       *a_ = a;
       *Ap_ = Ap;
       return;
}
