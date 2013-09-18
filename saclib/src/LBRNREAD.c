/*======================================================================
                      B <- LBRNREAD()

Logarithmic binary rational number read.

Inputs (from the input stream)
  An element A of the ring Z[1/2] in external representation.
  The external representation of 0 is 0.
  Non-zero elements are represented in the form
    <integer> <*|/> <power of 2>
  Here, <integer> or <power of 2> may be omitted, but not both.
  If one of <integer> or <power of 2> is omitted, <*|/> is also
  omitted; otherwise, <*|/> has to be written.
    <integer>    is a possibly signed integer,
    <*|/>        is * or /,
    <power of 2> is either an unsigned integer which is a power of 2 or
                 it is an explicit power of 2, i.e. of the form
                 2^<integer>.

Outputs
  B : The internal representation of A:
      If A  = 0, B = 0.
      If A /= 0, there is a unique pair (a,k) of integers with a odd
      and A = a/2^k. In this case, B is the list (a,k), where a is an
      integer and k is a BETA-digit.

Side effects
  A logarithmic binary rational number is read from the input stream.
  Any preceding blanks are skipped.
======================================================================*/
#include "saclib.h"

Word LBRNREAD()
{
       BDigit k,n,s;
       Word A,a,B,P;
       char C;

Step1: /* Read integer. */
       A = IREAD();

Step2: /* Integer 0. */
       if (A == 0) {
         B = 0;
         goto Return; }

Step3: /* Explicit power of 2? */
       if (A == 2 || A == -2) {
         C = CREAD();
         if (C == '^') {
           a = ISIGNF(A);
           k = -IREAD();
           goto Step8; }
         else
           BKSP(); }

Step4: /* Extract power of 2. */
       k = IORD2(A);
       a = IDP2(A,k);
       k = -k;

Step5: /* Read * or /. */
       C = CREAD();
       if (C == '*')
         s = 1;
       else if (C == '/')
         s = -1;
       else {
         BKSP();
         goto Step8; }

Step6: /* Read power of 2. */
       P = IREAD();
       if (P == 2) {
         C = CREAD();
         if (C == '^')
           n = IREAD();
         else {
           n = 1;
           BKSP(); } }
       else
         n = IORD2(P);

Step7: /* Adjust exponent. */
       if (s == 1)
         n = -n;
       k = k + n;

Step8: /* Compose. */
       B = LIST2(a,k);

Return: /* Prepare for return. */
       return(B);
}
