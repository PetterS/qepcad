/*======================================================================
                       b <- IPLBREVAL(r,A,a)

Integral polynomial logarithmic binary rational evaluation.

Inputs
   r : a BETA-digit, > 1.
   A : in Z[x_1, ..., x_r]
   a : a logarithmic binary rational number.

Outputs                          
   b : in Z[x_1, ..., x_(r-1)], b = A[x_1, ..., x_(r-1), a] * 2^(n*p),
       where n is the degree of A, and p is the unique integer such
       that a = k / 2^p and k is odd.  When a=0 such a p does not 
       exist, in this case b is the constant coefficient of A.
======================================================================*/
#include "sac_ext.h"

Word IPLBREVAL(Word r, Word A, Word a)
{
       Word b,rp,k,p,d,i,Ap,n,c;
  
Step1: /* Special Cases. */
       if (A == 0) {
	 b = 0;
	 goto Return; }
       if (a == 0) {
	 b = PCFE(A,0);
	 goto Return; }

Step2: /* General Case. */
       Ap = A;
       rp = r - 1;
       FIRST2(a,&k,&p);  /* a = k / 2^p */
       ADV2(Ap,&d,&b,&Ap);
       n = d;
       while(Ap != NIL) {
	 ADV2(Ap,&i,&c,&Ap);
	 b = IPIP(rp,IEXP(k,d - i),b);        /* b = b * k^(d - i). */
	 if (p > 0)
	   b = IPSUM(rp,b,IPMP2(rp,c,p*(n-i))); /* b = b + c * 2^(p*(n-i)). */
	 else if (p < 0)
	   b = IPSUM(rp,IPMP2(rp,b,-p*(d-i)),c);
	 else
	   b = IPSUM(rp,b,c);
	 d = i;
       }
       
Step3: /* b = [ A(a) * 2^(p*n) / k^o ] * k^o, then divide by 2^(n*p). */
       b = IPIP(rp,IEXP(k,d),b);
       
Return: /* Prepare to return. */
       return b;
}
