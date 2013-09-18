/*======================================================================
                      b <- SEQUAL(A,B)

Set equality.

Inputs
  A  : a list ( A1,...,Am ), m >= 0
  B  : a list ( B1,...,Bn ), n >= 0.

Outputs
  b  : an integer that has the value 1 if for each Ai there exists
       at least one Bj such that Ai = Bj, and for each Bj exists
       at least one Ai such that Bj = Ai.
       Otherwise b has the value 0.
======================================================================*/
#include "saclib.h"

Word SEQUAL(A,B)
       Word A,B;
{
       Word A1,Ap,B1,Bp,b;
       /* hide A1,Ap,B1,Bp,b; */

Step1: /* Decide. */
       b = 1;
       Ap = A;
       while (Ap != NIL)
         {
         ADV(Ap,&A1,&Ap);
         b = MEMBER(A1,B);
         if (b == 0)
           goto Return;
         }
       Bp = B;
       while (Bp != NIL)
         {
         ADV(Bp,&B1,&Bp);
         b = MEMBER(B1,A);
         if (b == 0)
           goto Return;
         }

Return: /* Prepare for return. */
       return(b);
}
