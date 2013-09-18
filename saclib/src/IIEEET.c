/*======================================================================
                             IIEEET(A; F,t,u)

Integer to IEEE double - truncation.

Inputs:
   A : integer.

Outputs:
   F : IEEE double.  If A > 0, F is the greatest IEEE-double
       that is <= A.  If A < 0, F is the smallest IEEE-double
       that is >= A.
   t : exactness flag. t = 0 if A = F, t = 1 if A /= F.
   u : If u = 0, the conversion failed because of exponent
       overflow, and F is undefined.  Otherwise u = 1.
======================================================================*/
#include "saclib.h"

void IIEEET(A, F_,t_,u_)
     Word A;
     ieee *F_;
     BDigit *t_,*u_;
{
     BDigit a,a0,a1,a2,ap,app,b,e,eb,k,kp,m0,m1,mt,n,r,s,t,u;
     Word Ap,App;
     ieee F;

Step1: /* A = 0. */
       if (A == 0) {
         s = 0;
         eb = 0;
         m1 = 0;
         m0 = 0;
         t = 0;
         goto Step8; }

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
         goto Step8; }

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

Step7: /* Overflow? Convert exponent. */
        if (e > MAXEXP) {
           u = 0;
	goto Return; }
	else {
	   u = 1;
           eb = e+BIAS-1; }

Step8: /* Construct IEEE double. */
	u = 1;
        F.rep.sign = s;
        F.rep.exp = eb;
        F.rep.mant_h = m1;
        F.rep.mant_l = m0;

Return: /* Return F, t and u. */
        *F_ = F;
        *t_ = t;
	*u_ = u;
	return;
}
