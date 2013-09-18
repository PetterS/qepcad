/*======================================================================
                      C <- IPRES(r,A,B)

Integral polynomial resultant.

Inputs
   r   : a BETA-digit, r > 0.
   A,B : in Z[x_1,...,x_r].  A and B have positive degrees in x_r.

Output
  C : in Z[x_1,...,x_{r-1}], the resultant of A and B with respect
      to x_r.

Algorithm
   The modular algorithm is used.  Degree bounds for the resultant
   are computed using ASSPR (which solves optimal assignment problems).
======================================================================*/
#include "saclib.h"

Word IPRES(r,A,B)
	BDigit r;
        Word A,B;
{
	BDigit d1,i,k,**M,m,n,p,q,rp;
        Word As,Bs,C,Cs,D,L,Mp,P,Q,d,e,f;

	BDigit j,T;

Step1: /* Compute a coefficient bound. */
        d = IPSUMN(r,A);
        e = IPSUMN(r,B);
	m = PDEG(A);
        n = PDEG(B);
        f = IPROD(IEXP(d,n),IEXP(e,m));
        f = IDPR(f,2);

Step2: /* Check for a common divisor x_i, 1 <= i <= r. */
	for (i = r; i >= 1; i--) {
           if (PDVAR(r,A,i) == 1 && PDVAR(r,B,i) == 1) {
              C = 0;
              goto Return; } }

Step3: /* Compute degree bounds. */
	D = NIL;
	k = m + n;
	for (i = r - 1; i >= 1; i--) {
	   M = SMDM(r,A,B,i);
	   Mp = AMLM(M,k,k);
	   FREEMATRIX(M,k);
	   ASSPR(Mp,&P,&d1);
	   D = COMP(d1,D); }

Step4: /* Initialize loop. */
        L = LPRIME;
        Q = 1;
        C = 0;
        rp = r - 1;

Step5: /* Compute the resultant modulo several primes and
	apply the Chinese remainder algorithm. */

        while (ICOMP(Q,f) <= 0) {
	   if (L == NIL)
	      FAIL("IPRES","Prime list exhausted");
           ADV(L,&p,&L);
           As = MPHOM(r,p,A);
	   Bs = MPHOM(r,p,B);
           if (PDEG(As) == m && PDEG(Bs) == n) {
              Cs = MPRESDB(r,p,As,Bs,D);
              q = MDHOM(p,Q);
              q = MDINV(p,q);
              C = IPCRA(Q,p,q,rp,C,Cs);
              Q = IPROD(Q,p); } }

Return: /* Return C. */
       return(C);
}
