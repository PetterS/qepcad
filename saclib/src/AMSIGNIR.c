/*======================================================================
                      AMSIGNIR(M,I,b; s,J)

Algebraic module sign, interval refinement.

Inputs
  M : the minimal integral polynomial of a real algebraic
      number alpha.
  I : an acceptable isolating interval for alpha.
  b : an element of Z[alpha].

Outputs
  s  : sign(b).
  J  : an acceptable isolating interval for alpha that is
       a subinterval of I.
======================================================================*/
#include "saclib.h"

void AMSIGNIR(M,I,b, s_,J_)

       Word M,I,b;
       Word *s_,*J_;
{
       Word s,J;
       Word bs,bsp,h,k,kp,t,tp,u,v,w;

Step1: /* b rational. */
       if (b == 0) {
          s = 0;
          J = I;
         goto Return; }
       if (PDEG(b) == 0) {
          s = ISIGNF(PLDCF(b));
          J = I;
          goto Return; }

Step2: /* alpha rational. */
       FIRST2(I,&u,&v);
       w = RNDIF(v,u);
       if (w == 0) {
          s = IUPBES(b,u);
          J = I;
          goto Return; }

Step3: /* Compute the transformed polynomial, bs, such that
          the roots of bs in (0,1) correspond to the roots 
          of b in I. */
       RNFCL2(w,&k,&kp);
       if (k == 0)
          bs = b;
       else
          bs = IUPBHT(b,k);
       if (u != 0) {
          h = RNQ(u,w);
          bs = IUPTR(bs,RNNUM(h)); }

Step4: /* Obtain an isolating interval, J, for alpha containing
          no roots of b and evaluate the sign of b at its 
          bisection point. */
       t = IUPBES(M,v);
       J = I;
       do {
          FIRST2(J,&u,&v);
          w = RIB(u,v);
          bsp = IUPTR1(PRT(bs));
          if (IUPVAR(bsp) == 0 && PORD(bsp) == 0) {
             s = IUPBES(b,w);
             goto Return; }
          bs = IUPBHT(bs,-1);
          tp = IUPBES(M,w);
          if (t * tp < 0 || t == 0) {
             u = w;
             bs = IUPTR1(bs); }
          else {
             v = w;
             t = tp; }
          J = LIST2(u,v); }
       while (1);

Return:
       *s_ = s;
       *J_ = J;
       return;
}
