/*======================================================================
                      B <- MINNCT(A)

Matrix of integers, non-negative column transformation.

Inputs
  A : an m by n matrix over Z. A is represented as a list of columns.

Outputs
  B : an m by n matrix over Z. The elements of B are obtained by taking
      the absolute value of the corresponding element of A.

Remarks:
  A is modified.
======================================================================*/
#include "saclib.h"

Word MINNCT(A)
       Word A;
{
       Word A1,Ap,B,a;
       /* hide algorithm */

Step1: /* Compute. */
       B = A;
       Ap = A;
       do
         {
         A1 = FIRST(Ap);
         a = FIRST(A1);
         if (ISIGNF(a) < 0)
           {
           A1 = VINEG(A1);
           SFIRST(Ap,A1);
           }
         Ap = RED(Ap);
         }
       while (Ap != NIL);

Return: /* Prepare for return. */
       return(B);
}
