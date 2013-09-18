/*======================================================================
                      RNWRITE(R)

Rational number write.

Inputs
  R : a rational number in internal representation.
      R is either 0 or a list (N,D) where N and D are relatively prime
      integers and D > 0.

Outputs (to the output stream)
  Canonical external representation of R.
  Let <integer N> and <integer D> be the canonical external
  representations of N and D, respectively.
  Then the output is of the following form
  0                       if R  = 0,
  <integer N>             if D  = 1,
  <integer N>/<integer D> if D /= 1.

Side effects
  The output is written in the output stream.
======================================================================*/

#include "saclib.h"

void RNWRITE(R)
       Word R;
{
       Word R1,R2;
       /* hide algorithm */

Step1: /* Write. */
       if (R == 0)
         AWRITE(R);
       else
         {
         FIRST2(R,&R1,&R2);
         IWRITE(R1);
         if (R2 != 1)
           {
           CWRITE('/');
           IWRITE(R2);
           }
         }

Return: /* Prepare for return. */
       return;
}
