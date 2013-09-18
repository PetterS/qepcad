/*======================================================================
                      t <- CSSUB(A,B)

Characteristic set subset.

Inputs
  A, B : characteristic sets.

Outputs
  t : integer, t = 1 if A is a subset of B and otherwise t = 0.
======================================================================*/
#include "saclib.h"

Word CSSUB(A,B)
       Word A,B;
{
       Word Ap,Bp,a,b,c,t;
       /* hide algorithm */

Step1: /* A single-precision. */
       if (A < BETA)
         {
         if (B < BETA)
           b = B;
         else
           b = FIRST(B);
         c = DNIMP(A,b);
         if (c == 0)
           t = 1;
         else
           t = 0;
         goto Return;
         }

Step2: /* B single-precision. */
       if (B < BETA)
         {
         t = 0;
         goto Return;
         }

Step3: /* General case. */
       Ap = A;
       Bp = B;
       do
         {
         ADV(Ap,&a,&Ap);
         ADV(Bp,&b,&Bp);
         c = DNIMP(a,b);
         if (c != 0)
           {
           t = 0;
           goto Return;
           }
         }
       while (!(Ap == NIL || Bp == NIL));
       if (Ap != NIL)
         t = 0;
       else
         t = 1;

Return: /* Prepare for return. */
       return(t);
}
