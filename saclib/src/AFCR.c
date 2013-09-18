/*======================================================================
                      Ap <- AFCR(A)

Algebraic number field element convert representation.

Inputs
  A  : in Q(alpha), represented as an element of Q[x].

Outputs
  Ap : in Q(alpha), represented as (a,Ab), where a is in Q and Ab
       is in Z[x]. A = a * Ab.
======================================================================*/
#include "saclib.h"

Word AFCR(A)
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
       IPSRP(1,A,&a,&Ab);
       Ap = LIST2(RNINV(a),Ab);

Return: /* Prepare for return. */
       return(Ap);
}
