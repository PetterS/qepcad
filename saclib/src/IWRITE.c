/*======================================================================
                      IWRITE(A)

Integer write.

Inputs
  A : an integer in internal representation.
      A is either a BETA-digit or a list of more than one BETA-digit
      which are either all non-negative or all non-positive and such
      that the last list element (= the leading BETA-digit) is not 0.

Outputs (to the output stream)
  Canonical external representation of A.
  Let <normalized digit sequence> designate any non-empty word over
  the alphabet {0,1,...,9} whose leftmost letter is not 0.
  Then the output is of the following form
  0 if A = 0,
  <normalized digit sequence>
  if A is a positive BETA-digit or a list of non-negative BETA-digits,
  -<normalized digit sequence>
  if A is a negative BETA-digit or a list of non-positive BETA-digits.

Side effects
  The output is written in the output stream.
======================================================================*/

#include "saclib.h"

void IWRITE(A)
       Word A;
{
       Word Ap,B[21],H,h,i,q;
       /* hide h,i,q; */

Step1: /* A single-precision. */
       if (A < BETA)
         {
         AWRITE(A);
         goto Return;
         }

Step2: /* Compute list of THETA-digits. */
       Ap = A;
       H = NIL;
       do
         {
         IDQR(Ap,THETA,&Ap,&h);
         H = COMP(h,H);
         }
       while (!(Ap == 0));

Step3: /* Write first THETA-digit. */
       ADV(H,&h,&H);
       AWRITE(h);

Step4: /* Write remaining digits. */
       while (H != NIL)
         {
         ADV(H,&h,&H);
         h = ABS(h);
         for (i = 1; i <= ETA; i++)
           {
           q = h / 10;
           B[i] = h - 10 * q;
           h = q;
           }
         for (i = ETA; i >= 1; i--)
           CWRITE(B[i] + '0');
         }

Return: /* Prepare for return. */
       return;
}
