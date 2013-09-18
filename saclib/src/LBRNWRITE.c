/*======================================================================
                      LBRNWRITE(A)

Logarithmic binary rational number write.

Inputs
  A : a logarithmic binary rational number in internal representation.
      A is either 0 or a list (a,k) where a is an odd integer and k
      is a BETA-digit. The list (a,k) represents the number a/2^k.

Outputs (to the output stream)
  Canonical external representation of A. This is the representation a
  mathematician would use. In particular, the output is
    0 if A = 0.
  Otherwise the output is of the form
    <sign> <unsigned odd integer> <*|/> <power of 2>
  where
    <sign>                 is omitted if A is positive,
    <unsigned odd integer> is omitted if |A| is a power of 2 and > 1,
    <*|/>                  is omitted if |A| is a power of 2 and > 1, or
                                      if A is an odd integer,
    <power of 2>           is omitted if A is an odd integer.
  Here,
    <sign>                 is + or -,
    <unsigned odd integer> is a positive odd integer in external form,
    <*|/>                  is * if A is an integer and / else,
    <power of 2>           is 2 or 2^<positive integer greater 1>.

Side effects
  The output is written in the output stream.
======================================================================*/
#include "saclib.h"

void LBRNWRITE(A)
       Word A;
{
       BDigit k,kp;
       Word a,ap;

Step1: /* A = 0. */
       if (A == 0) {
         AWRITE(0);
         goto Return; }

Step2: /* A = (a,k). */
       FIRST2(A,&a,&k);
       ap = IABSF(a);
       kp = absm(k);

Step3: /* Write sign. */
       if (ISIGNF(a) < 0)
         SWRITE("-");

Step4: /* Write unsigned odd integer. */
       if (ap != 1 || k >= 0)
         IWRITE(ap);

Step5: /* Write * or /. */
       if (k < 0 && ap != 1)
         SWRITE("*");
       else if (k > 0)
         SWRITE("/");

Step6: /* Write power of 2. */
       if (kp != 0) {
         SWRITE("2");
         if (kp > 1) {
           SWRITE("^");
           AWRITE(kp); } }

Return: /* Prepare for return. */
       return;
}
