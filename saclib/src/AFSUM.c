/*===========================================================================
			      c <- AFSUM(a,b)

Algebraic number field element sum.

Inputs
  a,b : in Q(alpha).

Outputs
    c : in Q(alpha), c = a + b.
===========================================================================*/
#include "saclib.h"

Word AFSUM(a,b)
       Word a,b;
{
       Word A,As,B,Bs,C,Cs,c,d,r,r1,r2,rb2,rs,s,s1,s2,sb2,ss,t,t1,t2;

Step1: /* a or b zero. */
       if (a == 0) {
	  c = b;
	  goto Return; }
       if (b == 0) {
	  c = a;
	  goto Return; }

Step2: /* Extract rational number and polynomial parts. */
       FIRST2(a,&r,&A);
       FIRST2(b,&s,&B);

Step3: /* Compute g.c.d., cofactors and least common multiple of
          denominators of rational number parts. */
       FIRST2(r,&r1,&r2);
       FIRST2(s,&s1,&s2);
       IGCDCF(r2,s2,&d,&rb2,&sb2);
       t2 = IPROD(r2,sb2);

Step4: /* Compute linear combination of polynomial parts. */
       rs = IPROD(r1,sb2);
       ss = IPROD(s1,rb2);
       As = IPIP(1,rs,A);
       Bs = IPIP(1,ss,B);
       Cs = IPSUM(1,As,Bs);

Step5: /* Compute content and primitive part of result. */
       IPSCPP(1,Cs,&s,&t1,&C);

Step6: /* Compute rational number part of c. */
       if (s < 0)
	  t1 = INEG(t1);
       t = RNRED(t1,t2);

Step7: /* Combine rational number and polynomial parts of c. */
       if (t == 0)
	  c = 0;
       else
	  c = LIST2(t,C);

Return: /* Prepare for return. */
       return(c);
}
