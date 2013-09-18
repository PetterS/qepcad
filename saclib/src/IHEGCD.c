/*===========================================================================
			      IHEGCD(A,B; C,V)

Integer half-extended greatest common divisor.  

Inputs
  A, B : in Z.

Outputs
  C    : gcd(A,B).  
  V    : If A /= 0, B*V=C(mod A), with abs(V) <= abs(A)/2C.  
         If A=0, V=sign(B).
===========================================================================*/
#include "saclib.h"

void IHEGCD(A,B, C_,V_)
       Word A,B, *C_,*V_;
{
       Word A1,A2,A3,A4,C,Q,V,V1,V2,V3,V4,a,b,h,m1,m2,s,u1,u2,v1,v2;

Step1: /* Compute absolute values and compare, and prepare v1, v2. */
       A1 = IABSF(A);
       s = ISIGNF(B);
       if (s < 0)
	  A2 = INEG(B);
       else
	  A2 = B;
       if (ICOMP(A1,A2) < 0) {
	  A3 = A1;
	  A1 = A2;
	  A2 = A3;
	  V1 = s;
	  V2 = 0; }
       else {
	  V1 = 0;
	  V2 = s; }

Step2: /* Compute remainder and cosequence. */
       while (A2 != 0) {
	  if (A1 < BETA) {
	     DEGCD(A1,A2,&C,&u1,&v1);
	     V = IDIPR2(V1,V2,u1,v1);
	     goto Return; }
	  m1 = ILOG2(A1);
	  m2 = ILOG2(A2);
	  if (m1 - m2 >= ZETA / 2) {
	     IQR(A1,A2,&Q,&A4);
	     A3 = A2;
	     V3 = V2;
	     V4 = IDIF(V1,IPROD(V2,Q)); }
	  else {
	     h = m1 - ZETA;
	     a = ITRUNC(A1,h);
	     b = ITRUNC(A2,h);
	     DPCC(a,b,&u1,&u2,&v1,&v2);
	     if (v1 == 0) {
		IQR(A1,A2,&Q,&A4);
		A3 = A2;
		V3 = V2;
		V4 = IDIF(V1,IPROD(V2,Q)); }
	     else {
		A3 = ILCOMB(A1,A2,u1,v1);
		A4 = ILCOMB(A1,A2,u2,v2);
		V3 = IDIPR2(V1,V2,u1,v1);
		V4 = IDIPR2(V1,V2,u2,v2); } }
	  A1 = A3;
	  A2 = A4;
	  V1 = V3;
	  V2 = V4; }
       C = A1;
       V = V1;

Return: /* Prepare for return. */
       *C_ = C;
       *V_ = V;
       return;
}
