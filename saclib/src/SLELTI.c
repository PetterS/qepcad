/*======================================================================
                      SLELTI(A,i,a)

Set list element.

Inputs
  A  : non empty list.
  i  : integer, 1 <= i <= LENGTH(A).
  a  : object.

Side effects
  The list A is modified by changing the i-th element to a.
======================================================================*/
#include "saclib.h"

void SLELTI(A,i,a)
       Word A,i,a;
{
       Word Ap,j;
       /* hide algorithm */

Step1: /* Set. */
       Ap = A;
       for (j = 1; j <= i - 1; j++)
         Ap = RED(Ap);
       SFIRST(Ap,a);

Return: /* Prepare for return. */
       return;
}
