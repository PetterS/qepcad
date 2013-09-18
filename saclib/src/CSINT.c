/*======================================================================
                      C <- CSINT(A,B)

Characteristic set intersection.

Inputs
  A,B : are characteristic sets.

Outputs
  C : the intersection of A and B.
======================================================================*/
#include "saclib.h"

Word CSINT(A,B)
       Word A,B;
{
       Word Ap,Bp,C,Cp,a,b;
       /* hide Ap,Bp,C,a,b; */

Step1: /* A and B single-precision. */
       if (A < BETA && B < BETA)
         {
         C = DAND(A,B);
         goto Return;
         }

Step2: /* A single-precision. */
       if (A < BETA)
         {
         C = DAND(A,FIRST(B));
         goto Return;
         }

Step3: /* B single-precision. */
       if (B < BETA)
         {
         C = DAND(FIRST(A),B);
         goto Return;
         }

Step4: /* General case. */
       Cp = NIL;
       Ap = A;
       Bp = B;
       do
         {
         ADV(Ap,&a,&Ap);
         ADV(Bp,&b,&Bp);
         Cp = COMP(DAND(a,b),Cp);
         }
       while (!(Ap == NIL || Bp == NIL));
       while (Cp != NIL && FIRST(Cp) == 0)
         Cp = RED(Cp);
       C = INV(Cp);
       if (C == NIL)
         C = 0;

Return: /* Prepare for return. */
       return(C);
}
