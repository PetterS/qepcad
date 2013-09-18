/*======================================================================
                             ISEM(A; s,e,m1,m0,t)

Integer sign, exponent and mantissa.

Inputs:
   A : an integer.

Outputs:
   s, e, m1 and m0 are the sign, exponent, mantissa high-order part
   and mantissa low-order part, respectively, of what would be the
   IEEE double  produced from A by IIEEET in the absence of an
   exponent overflow test.  t is the exactness flag that would be 
   produced by IIEEET.
======================================================================*/
#include "saclib.h"

void ISEM(A, s_,e_,m1_,m0_,t_)
     Word A;
     BDigit *s_,*e_,*m1_,*m0_,*t_;
{
     BDigit a,a0,a1,a2,ap,app,b,e,eb,k,kp,m0,m1,mt,n,r,s,t;
     Word Ap,App;

Step1: /* A = 0. */
       if (A == 0) {
         s = 0;
         eb = 0;
         m1 = 0;
         m0 = 0;
         t = 0;
         goto Return; }

Step2: /* A single precision. */
       if (A < BETA) {
         if (A < 0) {
           s = 1;
           A = -A; }
         else
           s = 0;
         e = PDLOG2(A);
         k = ZETA - e;
         a2 = (A << k);
         a2 = a2 - BETA/2;
         m1 = (a2 >> 8);
         mt = (a2 & 255);
         m0 = (mt << 24);
         t = 0;
         eb = e+BIAS-1;
         goto Return; }

Step3: /* Approximate A by 0.[a2,a1,a0] * 2^e. */
       Ap = RED(A);
       App = RED(Ap);
       if (App == NIL) {
         a0 = 0;
         a1 = FIRST(A);
         a2 = FIRST(Ap);
         e = 2 * ZETA;
         r = 0; }
       else if (RED(App) == NIL) {
         a0 = FIRST(A);
         a1 = FIRST(Ap);
         a2 = FIRST(App);
         e = 3 * ZETA;
         r = 0; }
       else {
         n = 3;
         r = 0;
         Ap = A;
         do {
           App = RED(App);
           n = n + 1;
           ADV(Ap,&a,&Ap);
           if (a != 0)
             r = 1; }
         while (RED(App) != NIL);
         a0 = FIRST(Ap);
         a1 = FIRST(RED(Ap));
         a2 = FIRST(App);
         e = n * ZETA; }

Step4: /* Normalize [a2,a1,a0]. */
       if (a2 < 0) {
         s = 1;
         a2 = -a2;
         a1 = -a1;
         a0 = -a0; }
       else 
         s = 0;
       kp = PDLOG2(a2);
       k = ZETA - kp;
       ap = a0 >> kp;
       a0 = (a0 << k) & BETA1;
       r =  r | a0;
       app =  a1 >> kp;
       a1 = ((a1 << k) & BETA1) | ap;
       a2 = (a2 << k) | app;
       e = e - k;

Step5: /* Extract mantissa. */
       a2 = a2 - BETA/2;
       m1 = (a2 >> 8);
       mt = (a2 & 255);
       m0 = (mt << 24) | (a1 >> 5);
       b = a1 & 31;

Step6: /* Determine exactness flag. */
       if (r == 0 && b == 0)
         t = 0;
       else
         t = 1;

Step7: /* Convert exponent. */
       eb = e+BIAS-1;

Return: /* return. */
        *s_ = s;
	*e_ = eb;
	*m1_ = m1;
	*m0_ = m0;
        *t_ = t;
}
