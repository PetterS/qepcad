/*===========================================================================
			     c <- AFPROD(P,a,b)

Algebraic number field element product.

Inputs
    P : in Z[x], the minimal polynomial of an algebraic number alpha.
  a,b : in Q(alpha).

Outputs
    c : in Q(alpha), c = a * b.
===========================================================================*/
#include "saclib.h"

Word AFPROD(P,a,b)
       Word P,a,b;
{
       Word A,B,C,Cp,c,cp,n,p,r,s,t,tp,tpp,u,v;

Step1: /* a or b zero. */
       if (a == 0 || b == 0) {
	  c = 0;
	  goto Return; }

Step2: /* Decompose a and b. */
       FIRST2(a,&r,&A);
       FIRST2(b,&s,&B);

Step3: /* Multiply rational and polynomial parts. */
       tp = RNPROD(r,s);
       Cp = IPPROD(1,A,B);

Step4: /* Remainder product polynomial. */
       n = PDEG(P);
       v = 1;
       while (PDEG(Cp) >= n) {
	  IUPSR(Cp,P,&cp,&p,&Cp);
	  v = IPROD(v,p); }

Step5: /* Compute content and primitive part of remainder. */
       IPSCPP(1,Cp,&s,&u,&C);
       if (s < 0)
	  u = INEG(u);

Step6: /* Compute rational part. */
       tpp = RNRED(u,v);
       t = RNPROD(tp,tpp);

Step7: /* Compose output list. */
       c = LIST2(t,C);

Return: /* Prepare for return. */
       return(c);
}
