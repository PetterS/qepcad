/*=====================================================================
			  J <- LBRIREAD()

Logarithmic binary rational interval read.

Inputs (from the input stream)
  An open or one-point logarithmic binary rational interval I.
  The external representation of an open interval is
    (<left endpoint>,<right endpoint>)
  Both endpoints are external representations of logarithmic
  binary rational numbers, the left endpoint being strictly
  smaller than the right endpoint.
  The external representation of a one-point interval is
    [<point>]
  where <point> is an external representation of a logarithmic
  binary rational number.

Outputs
  J : The internal representation of I:
      If I is open, J is the list
        (<left endpoint>,<right endpoint>)
      of the internal representations of the endpoints.
      If I is a one-point interval, J is the list
        (<point>,<point>)
      where <point> is the internal representation of the
      point.

Side effect
   The interval J  is read from the input stream.
   Any preceding blanks are skipped.
======================================================================*/
#include "saclib.h"

Word LBRIREAD()
{
       Word a,b,J;
       char C;

Step1: /* Read parenthesis or bracket. */
       C = CREADB();
       if (C != '(' && C != '[')
         goto Step4;

Step2: /* Read open interval. */
       if (C == '(') {
         a = LBRNREAD();
         C = CREAD();
         if (C != ',')
           goto Step4;
         b = LBRNREAD();
         C = CREAD();
         if (C != ')')
           goto Step4;
         J = LIST2(a,b);
         goto Return; }

Step3: /* Read one-point interval. */
       if (C == '[') {
         a = LBRNREAD();
         C = CREAD();
         if (C != ']')
           goto Step4;
         J = LIST2(a,a);
         goto Return; }

Step4: /* Error. */
       FAIL("LBRNREAD","Unexpected character",C);

Return: /* Return */
       return(J);
}
