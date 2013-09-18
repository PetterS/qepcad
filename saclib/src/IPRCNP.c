/*======================================================================
                      IPRCNP(A,I; sp,spp,J)

Integral polynomial real root calculation, Newton method preparation.

Inputs
  A : in Z[X], positive, primitive, squarefree, deg(A) > 0.
  I : an open interval (a1,a2) with binary rational endpoints containing
      no roots of A' and A'', but a unique root, alpha, of A.

Outputs
  sp, spp : BETA-digits, are the signs of A' and A'' on I.
  J : a subinterval (b1,b2) of I with binary rational endpoints,
      containing alpha and such that
      min(A'(b1),A'(b2)) >= (3/4) max(A'(b1),A'(b2)).
      J is a left-open and right-closed interval if b1 < b2, the one-point
      interval if b1 = b2.
======================================================================*/
#include "saclib.h"

void IPRCNP(A,I, sp_,spp_,J_)
       Word A,I, *sp_,*spp_,*J_;
{
       Word Ap,J,b,b1,b2,d,d1,d2,f,h,s,sp,spp,t;
       /* hide J,s,sp,spp,t; */

Step1: /* Initialize. */
       FIRST2(I,&b1,&b2);
       h = LIST2(1,2);

Step2: /* Compute s'. */
       sp = IUPBES(A,b2);

Step3: /* Compute s''. */
       Ap = IPDMV(1,A);
       d1 = IUPBRE(Ap,b1);
       d2 = IUPBRE(Ap,b2);
       d = RNDIF(d2,d1);
       spp = RNSIGN(d);

Step4: /* Compute fl. */
       if (sp * spp > 0)
         f = LIST2(-3,4);
       else
         f = LIST2(-4,3);

Step5: /* Test for completion. */
       d = RNPROD(f,d2);
       d = RNSUM(d1,d);
       t = RNSIGN(d);
       if (spp * t >= 0)
         goto Step7;

Step6: /* Bisect interval. */
       b = RNSUM(b1,b2);
       b = RNPROD(b,h);
       s = IUPBES(A,b);
       if (s == 0)
         {
         b1 = b;
         b2 = b;
         goto Step7;
         }
       d = IUPBRE(Ap,b);
       if (s == sp)
         {
         b2 = b;
         d2 = d;
         }
       else
         {
         b1 = b;
         d1 = d;
         }
       goto Step5;

Step7: /* Finish. */
       J = LIST2(b1,b2);

Return: /* Prepare for return. */
       *sp_ = sp;
       *spp_ = spp;
       *J_ = J;
       return;
}
