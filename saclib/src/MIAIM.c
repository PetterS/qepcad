/*======================================================================
                      B <- MIAIM(A)

Matrix of integers, adjoin identity matrix.

Inputs
  A : an m by n matrix over Z. A is represented as a list of columns.

Outputs
  B : an m+n by n matrix over Z. B is obtained by adjoining an n by n
     identity matrix to the bottom of A.

Remarks:
  A is modified.
======================================================================*/
#include "saclib.h"

Word MIAIM(A)
       Word A;
{
       Word A1,Ap,B,T,i,j,n;
       /* hide i,j,n; */

Step1: /* Compute. */
       n = LENGTH(A);
       Ap = INV(A);
       B = NIL;
       for (i = 1; i <= n; i++)
         {
         ADV(Ap,&A1,&Ap);
         T = NIL;
         for (j = 1; j <= n; j++)
           if (i == j)
             T = COMP(1,T);
           else
             T = COMP(0,T);
         A1 = CONC(A1,T);
         B = COMP(A1,B);
         }

Return: /* Prepare for return. */
       return(B);
}
