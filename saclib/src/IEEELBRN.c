/*======================================================================
                             A <- IEEELBRN(F)

IEEE to logarithmic binary rational number conversion.

Inputs
  F : a double.

Outputs
  A : a logarithmic binary rational number, A = F.
======================================================================*/
#include "saclib.h"

Word IEEELBRN(F)

        double F;
{
        unsigned m1,m0;
        int s,e;
        BDigit a0,a1,k,n;
        Word A,a;
        ieee G;

Step1: /* F = 0. */
       if (F == 0.0) {
         A = 0;
         goto Return; }

Step2: /* Decompose F. */
       G.num = F;
       s = G.rep.sign;
       m1 = G.rep.mant_h;
       m0 = G.rep.mant_l;
       e = G.rep.exp - BIAS;

Step3: /* F infinity or NaN. */
       if (e == MAXEXP1)
         FAIL("IEEELBRN","Infinity or NaN");

Step4: /* Convert mantissa to integer. */
       a0 = (m0 & BETA1);
       a1 = (m1 << 3) | (m0 >> 29);
       a = (a1 != 0 ? LIST2(a0,a1) : a0);

Step5: /* F denormalized. */
       if (e == MINEXP1) {
         k = MINEXP - PREC1;
         goto Step7; }

Step6: /* F normalized. */
       a = ISUM(a,IMP2(1,52));
       k = e - 52;

Step7: /* Compose A. */
       n = IORD2(a);
       a = IDP2(a,n);
       k = k + n;
       if (s == 1)
         a = INEG(a);
       A = LBRN(a,-k);

Return: /* Prepare for return. */
        return(A);
}
