/*======================================================================
                      B <- SFCS(A)

Set from characteristic set.

Inputs
  A : a characteristic set.

Outputs
  B : the same set represented as an increasing list of BETA-digits.
======================================================================*/
#include "saclib.h"

Word SFCS(A)
       Word A;
{
       Word Ap,B,a,b,n,r;
       /* hide Ap,a,b,n,r; */

Step1: /* A empty. */
       if (A == 0)
         {
         B = NIL;
         goto Return;
         }

Step2: /* A single-precision. */
       if (A < BETA)
         Ap = LIST1(A);
       else
         Ap = A;

Step3: /* General case. */
       n = 0;
       B = NIL;
       do
         {
         ADV(Ap,&a,&Ap);
         b = 1;
         do
           {
           r = REM(a,2);
           a = a / 2;
           if (r != 0)
             B = COMP(n,B);
           n = n + 1;
           b = b + b;
           }
         while (!(b == BETA));
         }
       while (!(Ap == NIL));
       B = INV(B);

Return: /* Prepare for return. */
       return(B);
}
