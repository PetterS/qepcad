/*======================================================================
                      AFWRITE(A,v)

Algebraic field element write.

Inputs
  A : in Q(alpha). A is represented as (a,Ab) where a is
      in Q and Ab is in Z[x].
  v : a variable.

Side effects
  A is written to the output stream.
======================================================================*/
#include "saclib.h"

void AFWRITE(A,v)
       Word A,v;
{
       Word Ab,a;

Step1: /* A equal 0. */
       if (A == 0)
         {
         IWRITE(0);
         goto Return;
         }

Step2: /* A not equal 0. */
       FIRST2(A,&a,&Ab);
       CWRITE('(');
       RNWRITE(a);
       CWRITE(',');
       IUPWRITE(Ab,v);
       CWRITE(')');

Return: /* Prepare for return. */
       return;
}
