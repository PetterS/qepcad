/*===========================================================================
                                B <- GINEG(A)

Gaussian integer negation.  

Input
   A : a Gaussian integer.

Output
   B : -A, a Gaussian integer.
===========================================================================*/
#include "saclib.h"

Word GINEG(A)
       Word A;
{
       Word B;

Step1:  /* A = 0. */
        if (A == 0) {
           B = 0;
           goto Return; }

Step2:  /* A /= 0. */
        B = LIST2(INEG(FIRST(A)),INEG(SECOND(A)));

Return: /* Return B. */
        return(B);
}
