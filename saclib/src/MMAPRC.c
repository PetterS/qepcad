/*==========================================================================
		       MMAPRC(p,A,B,C; r)

Medium modulus array polynomial resultant and cofactor.

Inputs
   p : a BETA-digit, prime.
 A,B : in Z/(p)[X].  A and B have positive degrees.
       A and B are in array representation.
   C : an array large enough to hold a polynomial of degree deg(A)-1.

Outputs
  r  : in Z/(p), the resultant of A and B.

Side effects
  C is modified so that it contains the polynomial in Z/(p)[X]
  of degree less than deg(A) such that for some D in Z/(p)[X],
  A*D + B*C = r.
==========================================================================*/
#include "saclib.h"

void MMAPRC(p,A,B,C, r_)
       Word p,*A,*B,*C, *r_;
{
       Word *A1,*A2,*Q,*P,i,n1,n2,n3,r,r2,s,*t,*v1,*v2;

Step1: /* Initialize. */
       r = 1;
       A1 = MAPCOPY(A);
       A2 = MAPCOPY(B);
       n1 = MAPDEG(A1);
       n2 = MAPDEG(A2);
       v1 = MAPFMD(0,maxm(n1,n2));
       v2 = MAPFMD(1,maxm(n1,n2));
       s = 1;
       if (n1 < n2) {
	  if (ODD(n1) && ODD(n2))
	     s = -s;
	  t = A1;
	  A1 = A2;
	  A2 = t;
	  t = v1;
	  v1 = v2;
	  v2 = t; }
       Q = MAPGET(n1);
       P = MAPGET(n1);
       
Step2: /* Loop. */
       do {
	  n1 = MAPDEG(A1);
	  MMAPQR(p,A1,A2,Q);
	  MMAPPROD(p,Q,v2,P);
	  MAPIDIF(p,v1,P);
	  if (MAPZERO(A1)) {
	     r = 0;
	     MAPASSIGN(v1,C);
	     goto Step4; }
	  n3 = MAPDEG(A1);
	  n2 = MAPDEG(A2);
	  if (ODD(n1) && ODD(n2))
	     s = -s;
	  r2 = MAPLDCF(A2);
	  for (i = 1; i <= n1 - n3; i++)
	     r = (r * r2) % p;
	  t = A1;
	  A1 = A2;
	  A2 = t;
	  t = v1;
	  v1 = v2;
	  v2 = t; }
       while (n3 != 0);

Step3: /* Finish. */
       r2 = MAPLDCF(A2);
       for (i = 1; i <= n2 - 1; i++)
	  r = (r * r2) % p;
       if (s == -1)
	  r = p - r;
       MMAPMDP(p,r,v2,C);
       r = (r * r2) % p;
       
Step4: /* Free arrays. */
       MAPFREE(A1);
       MAPFREE(A2);
       MAPFREE(v1);
       MAPFREE(v2);
       MAPFREE(Q);
       MAPFREE(P);

Return: /* Prepare for return. */
       *r_ = r;
       return;
}
