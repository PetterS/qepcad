/*======================================================================
                      L <- LEINST(A,i,a)

List element insertion.

Inputs
  A  : a list ( a1,...,an ) of objects
  i  : a BETA-integer, 0 <= i <= n
  a  : an object.

Outputs
  L  : a list obtained from A by inserting the object a
       after the i-th element of A.
       The list A is modified.
       If n=0 then L = (a,a1,...,an ).
======================================================================*/
#include "saclib.h"

Word LEINST(A,i,a)
       Word A,i,a;
{
       Word Ap,App,L,j;
       /* hide j; */

Step1: /* i=0. */
       if (i == 0)
         {
         L = COMP(a,A);
         goto Return;
         }

Step2: /* i > 0. */
       L = A;
       Ap = A;
       for (j = 2; j <= i; j++)
         Ap = RED(Ap);
       App = RED(Ap);
       App = COMP(a,App);
       SRED(Ap,App);

Return: /* Prepare for return. */
       return(L);
}
