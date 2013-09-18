/*===========================================================================
                                N <- GINORM(A)

Gaussian integer norm.  

Input
   A : a Gaussian integer.

Output
   N : the norm of A, an integer.
===========================================================================*/
#include "saclib.h"

Word GINORM(A)
       Word A;
{
       Word A1,A2,N1,N2,N;

Step1:  /* A = 0. */
        if (A == 0) {
           N = 0;
           goto Return; }

Step2:  /* Square the parts and add. */
        FIRST2(A,&A1,&A2);
        N1 = IPROD(A1,A1);
        N2 = IPROD(A2,A2);
        N = ISUM(N1,N2);


Return: /* Return N. */
        return(N);
}
