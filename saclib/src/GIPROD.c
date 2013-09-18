/*===========================================================================
                               C <- GIPROD(A,B)

Gaussian integer product.  

Inputs
  A,B : Gaussian integers.

Output
  C   : A * B, a Gaussian integer.
===========================================================================*/
#include "saclib.h"

Word GIPROD(A,B)
        Word A,B;
{
        Word A1,A2,B1,B2,C,C1,C2;

Step1: /* A or B zero. */
        if (A == 0 || B == 0) {
           C = 0;
           goto Return; }

Step2: /* Compute the parts. */
        FIRST2(A,&A1,&A2);
        FIRST2(B,&B1,&B2);
        C1 = IDIF(IPROD(A1,B1),IPROD(A2,B2));
        C2 = ISUM(IPROD(A1,B2),IPROD(B1,A2));

Step3: /* Compose the result. */
        C = LIST2(C1,C2);

Return: /* Return C. */
        return(C);
}
