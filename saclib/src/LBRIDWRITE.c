/*======================================================================
                      LBRIDWRITE(I,n)

Logarithmic binary rational interval decimal write. 

Inputs
   I : an open or one-point interval with logarithmic
       binary rational number endpoints.  
   n : a non-negative integer.  

Side effects
   If I is an open interval, the endpoints of I are 
   approximated by n decimal digit fractions and printed, 
   using RNDDWRITE.  The left endpoint is rounded down,
   the right endpoint up.  If I is a one-point interval,
   its one point is printed using RNDWRITE, which rounds
   it to the nearest n-digit decimal fraction.
======================================================================*/
#include "saclib.h"

void LBRIDWRITE(I,n)
       Word I,n;
{
       Word a,b;

Step1: /* Convert from logarithmic representation. */
       FIRST2(I,&a,&b);
       I = LIST2(LBRNRN(a),LBRNRN(b));

Step2: /* Apply RIDWRITE. */
       RIDWRITE(I,n);

Return: /* Return. */
        return;
}
