/*======================================================================
                      R <- RNREAD()

Rational number read.

Inputs (from the input stream)
  A rational number in external form.
  Let <integer N> and <integer D> be external forms of relatively prime
  integers N and D, such that D > 0.
  Then the input is of the following form
  <integer N>
  or
  <integer N>/<integer D>
  Note that no blanks are permitted immediately before and after the /.

Outputs
  R : The internal representation of the input rational number.
      R = 0     if N  = 0,
      R = (N,D) if N /= 0.

Side effects
  A rational number is read from the input stream.
  Any preceding blanks are skipped.
======================================================================*/

#include "saclib.h"

Word RNREAD()
{
       Word C,R,R1,R2;
       /* hide C,R; */

Step1: /* Read. */
       R1 = IREAD();
       C = CREAD();
       if (C == '/')
         R2 = IREAD();
       else
         {
         R2 = 1;
         BKSP();
         }
       if (R1 == 0)
         R = 0;
       else
         R = LIST2(R1,R2);

Return: /* Prepare for return. */
       return(R);
}
