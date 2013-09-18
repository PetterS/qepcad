/*======================================================================
                      a <- LELTI(A,i)

List element.

Inputs
  A  : non empty list
  i  : integer, 1 <= i <= LENGTH(L)

Outputs
  a  :  the i-th element of A.
======================================================================*/
#include "saclib.h"

Word LELTI(A,i)
       Word A,i;
{
       Word Ap,a,j;
       /* hide algorithm */

Step1: /* Compute. */
       Ap = A;
       for (j = 1; j <= i - 1; j++)
         Ap = RED(Ap);
       a = FIRST(Ap);

Return: /* Prepare for return. */
       return(a);
}
