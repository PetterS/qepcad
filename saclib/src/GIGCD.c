/*===========================================================================
                               C <- GIGCD(A,B)

Gaussian integer greatest common divisor.  

Inputs
  A,B : Gaussian integers.

Output
  C   : The greatest common divisor of A and B that is real
        or in the first quadrant, a Gaussian integer.
===========================================================================*/
#include "saclib.h"

Word GIGCD(A,B)
        Word A,B;
{
        Word A1,A2,A3,a,b,C,Q;
 
Step1: /* Initialize a remainder sequence. */
        A1 = A;
        A2 = B;

Step2: /* Compute remainders until zero is obtained. */
        while (A2 != 0) {
           GINQR(A1,A2,&Q,&A3);
           A1 = A2;
           A2 = A3; }
Step3: /* Set C to the real or first quadrant associate of A1. */
        FIRST2(A1,&a,&b);
        if (a <= 0 && b > 0)
           C = LIST2(b,INEG(a));
        else if (a < 0 && b <= 0)
           C = LIST2(INEG(a),INEG(b));
        else if (a >= 0 && b < 0)
           C = LIST2(INEG(b),a);
        else
           C = A1;

Return: /* Return C. */
        return(C);
}
