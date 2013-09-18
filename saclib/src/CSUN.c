/*======================================================================
                      C <- CSUN(A,B)

Characteristic set union.

Inputs
  A,B : characteristic sets.

Outputs
  C : the union of A and B.
======================================================================*/
#include "saclib.h"

Word CSUN(A,B)
       Word A,B;
{
       Word Ap,Bp,C,Cp,a,b;
       /* hide Ap,Bp,C,a,b; */

Step1: /* A and B single-precision. */
       if (A < BETA && B < BETA)
         {
         C = DOR(A,B);
         goto Return;
         }

Step2: /* A single-precision. */
       if (A < BETA)
         {
         ADV(B,&b,&Bp);
         C = COMP(DOR(A,b),Bp);
         goto Return;
         }

Step3: /* B single-precision. */
       if (B < BETA)
         {
         ADV(A,&a,&Ap);
         C = COMP(DOR(a,B),Ap);
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
         Cp = COMP(DOR(a,b),Cp);
         }
       while (!(Ap == NIL || Bp == NIL));
       if (Ap == NIL)
         Ap = Bp;
       C = INV(Cp);
       SRED(Cp,Ap);

Return: /* Prepare for return. */
       return(C);
}
