/*===========================================================================
                                B <- GICONJ(A)

Gaussian integer conjugation.  

Input
   A : a Gaussian integer.

Output
   B : The conjugate of A, a Gaussian integer.
===========================================================================*/
#include "saclib.h"

Word GICONJ(A)
       Word A;
{
       Word B;

Step1:  /* A = 0. */
        if (A == 0) {
           B = 0;
           goto Return; }

Step2:  /* A /= 0. */
        B = LIST2(FIRST(A),INEG(SECOND(A)));

Return: /* Return B. */
        return(B);
}
