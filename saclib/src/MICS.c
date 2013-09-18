/*======================================================================
                      B <- MICS(A)

Matrix of integers column sort.

Inputs
  A : a matrix over Z, with nonnegative elements in first row. A is
      represented as a list of columns.

Outputs
  B : a matrix over Z. B is obtained by sorting columns of A such that
      elements of the first row are in descending order.

Remarks:
  A is modified.
======================================================================*/
#include "saclib.h"

Word MICS(A)
       Word A;
{
       Word A1,A2,Ap,App,B,a1,a2,s;
       /* hide algorithm */

Step1: /* Bubble sort columns. */
       do
         {
         Ap = A;
         s = 0;
         while (RED(Ap) != NIL)
           {
           ADV(Ap,&A1,&App);
           A2 = FIRST(App);
           a1 = FIRST(A1);
           a2 = FIRST(A2);
           if (ICOMP(a1,a2) < 0)
             {
             SFIRST(Ap,A2);
             SFIRST(App,A1);
             s = 1;
             }
           Ap = App;
           }
         }
       while (s != 0);
       B = A;

Return: /* Prepare for return. */
       return(B);
}
