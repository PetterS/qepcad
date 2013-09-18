/*===========================================================================
		       b <- IUPLB(A,k)

Integral univariate polynomial lifting bound.

Input
  A : in Z[x], deg(A) >= 3.
  k : a BETA-digit, k >= 2.

Output
  b : in Z.  If A = A_1 A_2 ... A_k is a non-trivial factorization
      of A, then at least one of the A_i's will have max norm less
      than sqrt(b/2).  The Beauzamy-Trevisan-Wang bound is used.
===========================================================================*/
#include "saclib.h"

Word IUPLB(A,k)
       Word A,k;
{
       Word N,Ns,b,c,n,np,nt,t;

Step1: /* Compute twice the square of the B-T-W bound. */
       N = IUPSWN(A);
       IROOT(N,k,&Ns,&t);
       Ns = ISUM(Ns,t);
       n = PDEG(A);
       b = IMP2(Ns,n+1);
       nt = IPROD(IPROD(n,n),n);
       IROOT(nt,4,&np,&t);
       b = RNRED(b,np);
       c = RNRED(6,5);
       b = RNPROD(c,b);
       b = RNCEIL(b);

Return: /* Prepare for return. */
       return(b);
}
