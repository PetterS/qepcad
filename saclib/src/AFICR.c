/*======================================================================
                      Ap <- AFICR(A)

Algebraic number field element inverse convert representation.

Inputs
  A  : in Q(alpha), represented as (a,Ab), where a is an element
       of Q and Ab is an element of Z[x].

Outputs
  Ap : in Q(alpha), represented as an element of Q[x].  Ap = a * Ab.
======================================================================*/
#include "saclib.h"

Word AFICR(A)
       Word A;
{
       Word Ab,Ap,a;

Step1: /* A equal 0. */
       if (A == 0)
         {
         Ap = 0;
         goto Return;
         }

Step2: /* A not equal 0. */
       FIRST2(A,&a,&Ab);
       Ab = RPFIP(1,Ab);
       Ap = RPRNP(1,a,Ab);

Return: /* Prepare for return. */
       return(Ap);
}
