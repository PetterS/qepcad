/*===========================================================================
                               C <- GIDIF(A,B)

Gaussian integer difference.  

Inputs
  A,B : Gaussian integers.

Output
  C   : A - B, a Gaussian integer.
===========================================================================*/
#include "saclib.h"

Word GIDIF(A,B)
        Word A,B;
{
        Word A1,A2,B1,B2,C,C1,C2;

Step1: /* A or B zero. */
        if (A == 0) {
          C = GINEG(B);
          goto Return; }
       if (B == 0) {
          C = A;
          goto Return; }

Step2: /* Subtract the parts. */
        FIRST2(A,&A1,&A2);
        FIRST2(B,&B1,&B2);
        C1 = IDIF(A1,B1);
        C2 = IDIF(A2,B2);

Step3: /* Compose the result. */
        if (C1 == 0 && C2 == 0)
           C = 0;
        else
           C = LIST2(C1,C2);

Return: /* Return C. */
        return(C);
}
