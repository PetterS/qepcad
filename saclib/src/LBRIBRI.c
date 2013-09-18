/*======================================================================
                      J <- LBRIBRI(I)

Logarithmic binary rational interval to binary rational interval.

Input
   I : an interval with logarithmic binary rational endpoints.

Output
   J : the same interval represented with binary rational endpoints.
======================================================================*/
#include "saclib.h"

Word LBRIBRI(I)
	Word I;
{
	Word a,b,J;

Step1: /* Convert the endpoints. */
        FIRST2(I,&a,&b);
        a = LBRNRN(a);
        b = LBRNRN(b);
        J = LIST2(a,b);

Return: /* Return J. */
        return(J);
}
