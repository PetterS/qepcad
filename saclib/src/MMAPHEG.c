/*===========================================================================
		      MMAPHEG(p,A,B, C,V)

Medium modulus array polynomial half-extended greatest common divisor.

Inputs
   p : a medium prime.
 A,B : in Z/(p)[x], A and B are in array representation.
   C : an array large enough to hold gcd(A,B).
   V : an array of size at least deg(A/gcd(A,B))+2.

Side effects
  gcd(A,B) is computed and put in C.  Let Vp be the polynomial
  in Z/(p)[x] such there exists Up in Z/(p)[x] such that A U + B V = C.
  If deg(A/C) > 0, then deg(Vp) < deg(A/C).  If deg(A/C) = 0,
  then deg(Vp) = 0.  If B = 0, then Vp = 0.  Vp is computed and put in V.
===========================================================================*/
#include "saclib.h"

void MMAPHEG(p,A,B, C,V)
       Word p,*A,*B, *C,*V;
{
       Word *V1,*V2,*V3,*t,*A1,*A2,*Q,*P,k,a,ap,c,i;

Step1: /* Initialize. */
       k = MAPDEG(A);
       V1 = MAPGET(k);
       MAPDEG(V1) = 0;
       MAPCF(V1,0) = 0;
       V2 = MAPGET(k);
       MAPDEG(V2) = 0;
       MAPCF(V2,0) = 1;
       V3 = MAPGET(k);
       A1 = MAPCOPY(A);
       A2 = MAPCOPY(B);
       k = maxm(MAPDEG(A),MAPDEG(B));
       Q = MAPGET(k);
       P = MAPGET(k);

Step2: /* Compute remainder sequence. */
       while (!MAPZERO(A2)) {
	  MMAPQR(p,A1,A2,Q);
	  MMAPPROD(p,Q,V2,P);
	  MAPDIF(p,V1,P,V3);
	  t = V1;
	  V1 = V2;
	  V2 = V3;
	  V3 = t;
	  t = A1;
	  A1 = A2;
	  A2 = t; }

Step3: /* Adjust ldcf. */
       if (MAPZERO(A1)) {
	  MAPDEG(C) = 0;
	  MAPCF(C,0) = 0;
	  MAPDEG(V) = 0;
	  MAPCF(V,0) = 0; }
       else {
	  a = MAPLDCF(A1);
	  ap = MDINV(p,a);
	  k = MAPDEG(A1);
	  MAPDEG(C) = k;
	  for (i = 0; i <= k; i++) {
	     c = (ap * MAPCF(A1,i)) % p;
	     MAPCF(C,i) = c; }
	  k = MAPDEG(V1);
	  MAPDEG(V) = k;
	  for (i = 0; i <= k; i++) {
	     c = (ap * MAPCF(V1,i)) % p;
	     MAPCF(V,i) = c; } }

Step4: /* Free arrays. */
       MAPFREE(V1);
       MAPFREE(V2);
       MAPFREE(V3);
       MAPFREE(A1);
       MAPFREE(A2);
       MAPFREE(Q);
       MAPFREE(P);

Return: /* Prepare for return. */
       return;
}
