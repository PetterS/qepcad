/*===========================================================================
                               A <- GIFP(A1,A2)

Gaussian integer from parts.  

Inputs
   A1,A2 : Integers.

Output
   A   : The Gaussian integer A1 + A2 i.
===========================================================================*/
#include "saclib.h"

Word GIFP(A1,A2)
        Word A1,A2;
{
        Word A;

Step1: /* A = 0? */
        if (A1 == 0 && A2 == 0)
           A = 0;
        else
           A = LIST2(A1,A2);

Return: /* Return A. */
        return(A);
}

