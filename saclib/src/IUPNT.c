/*======================================================================
                      B <- IUPNT(A)

Integral univariate polynomial negative transformation.

Inputs
  A : in Z[X].

Outputs
  B : in Z[X], B(X)=A(-X).
======================================================================*/
#include "saclib.h"

Word IUPNT(A)
       Word A;
{
       Word Ap,B,a,e;
       /* hide Ap,e; */

Step1: /* Compute. */
       if (A == 0)
         {
         B = 0;
         goto Return;
         }
       B = NIL;
       Ap = A;
       do
         {
         ADV2(Ap,&e,&a,&Ap);
         if (ODD(e) == 1)
           a = INEG(a);
         B = COMP2(a,e,B);
         }
       while (!(Ap == NIL));
       B = INV(B);

Return: /* Prepare for return. */
       return(B);
}
