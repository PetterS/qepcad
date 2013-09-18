/*======================================================================
                      B <- REDI(A,i)

Reductum.

Inputs
  A  : list
  i  : integer, 0 <= i <= LENGTH(A).

Outputs
  B  : the i-th reductum of A. If i=0 then B=A.
======================================================================*/
#include "saclib.h"

Word REDI(A,i)
       Word A,i;
{
       Word B,j;
       /* hide algorithm */

Step1: /* Compute. */
       B = A;
       for (j = 1; j <= i; j++)
         B = RED(B);

Return: /* Prepare for return. */
       return(B);
}
