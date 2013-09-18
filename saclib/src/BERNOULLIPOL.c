/*======================================================================
                      A <- BERNOULLIPOL(n,L)

Bernoulli polynomial. The n-th Bernoulli polynomial is computed.

Inputs
  n : a non-negative BETA-digit.
  L : a list of the first m Bernoulli numbers, L = (B_0,...,B_m)
      where m >= n.

Outputs
  A : in Q[x], A is the n-th Bernoulli polynomial,
      A(x) = sum_{k=0}^n (n choose k) B_k x^{n-k}.

Cast
  d : (n choose k)
  r : B_k
  s : B_{n-k}
  B : sum_{j=0}^k (n choose k) B_k x^{n-k}
  C : sum_{j=0}^k (n choose k) B_{n-k} x^k
======================================================================*/
#include "saclib.h"

Word BERNOULLIPOL(n,L)

     BDigit n;
     Word L;
{
     BDigit k;
     Word A,B,C,d,e,Lp,R,r,S,s;

Step1: /* n = 0. */
       if (n == 0) {
	 A = PMON(RNINT(1),0);
	 goto Return; }

Step2: /* Lists of binomial coefficients. */
       R = L;

       Lp = L;
       S = NIL;
       for (k = 0; k <= n; k++) {
         ADV(Lp,&s,&Lp);
         S = COMP(s,S); }

Step3: /* Binomial coefficients by recursion. Exploit symmetry. */
       d = 1;

       ADV(R,&r,&R);
       B = LIST2(r,n);

       ADV(S,&s,&S);
       if (s == 0)
	 C = NIL;
       else
	 C = LIST2(0,s);

       for (k = 1; k <= (n-1)/2; k++) {
	 d = IDEQ(IDPR(d,n-k+1),k);
	 e = RNINT(d);

	 ADV(R,&r,&R);
	 if (r != 0)
	   B = COMP2(RNPROD(e,r),n-k,B);

	 ADV(S,&s,&S);
	 if (s != 0)
	   C = COMP2(k,RNPROD(e,s),C); }

       if (EVEN(n)) {
	 ADV(S,&s,&S);
	 if (s != 0) {
	   k = n/2;
	   d = IDEQ(IDPR(d,n-k+1),k);
	   e = RNINT(d);
	   C = COMP2(k,RNPROD(e,s),C); } }

Step4: /* Compose A. */
       if (C == NIL)
	 C = 0;
       A = RPSUM(1,INV(B),C);

Return: /* Prepare for return. */
       return(A);
}
