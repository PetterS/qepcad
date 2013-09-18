/*======================================================================
                      s <- ISIGNF(A)

Integer sign function.  

Inputs
  A : in Z.

Outputs
  s : sign(A).
======================================================================*/
#include "saclib.h"

Word ISIGNF(A)
       Word A;
{
       Word Ap,a,s;
       /* hide algorithm */

Step1: /* A single-precision. */
       if (A < BETA)
         {
         s = SIGN(A);
         goto Return;
         }

Step2: /* A multiple-precision. */
       Ap = A;
       do
         ADV(Ap,&a,&Ap);
       while (a == 0);
       s = SIGN(a);

Return: /* Prepare for return. */
       return(s);
}
