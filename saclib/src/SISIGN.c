/*======================================================================
                           SISIGN(I)

Software interval sign.

Inputs
  I : a software floating point interval.

Outputs
   s : I is interpreted as either an open interval or a one-point
       interval.  If all elements of I have the same sign, then
       s is that sign.  Otherwise I contains elements of every
       sign and s = NIL.
======================================================================*/
#include "saclib.h"

BDigit SISIGN(I)
       Word *I;
{
       BDigit p,s,s1,s2;

Step1: /* Left endpoint greater than 0. */
       s1 = I[1];
       if (s1 > 0) {
	 s = 1;
	 goto Return; }

Step2: /* Right endpoint. */
       p = I[2];
       s2 = I[p+4];

Step3: /* Right endpoint less than 0. */
       if (s2 < 0) {
	 s = -1;
	 goto Return; }

Step4: /* Left endpoint 0. */
       if (s1 == 0) {
	 if (s2 == 0)
	   s = 0;
         else
           s = 1;
	 goto Return; }

Step5: /* Right endpoint 0. */
       if (s2 == 0)
	 s = -1;
       else
	 s = NIL;

Return: /* return. */
       return(s);
}
