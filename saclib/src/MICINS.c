/*======================================================================
                      B <- MICINS(A,V)

Matrix of integers column insertion.

Inputs
  A : an m by n matrix over Z. A is represented as a list of columns.
      The elements of the first row are sorted in descending order.
  V : an m-vector over Z, v1 < a_{1,1}.
 
Outputs
  B : an m by n+1 matrix over Z. B is obtained from A by inserting V
      after the i-th column of A, where i is the largest integer such
      that a_{1,i} >= v1.

Remarks:
  A is modified.
======================================================================*/
#include "saclib.h"

Word MICINS(A,V)
       Word A,V;
{
       Word Ap,App,B,v;
       /* hide algorithm */

Step1: /* Initialize. */
       Ap = A;
       App = RED(Ap);
       v = FIRST(V);

Step2: /* Loop. */
       while (App != NIL && ICOMP(FIRST(FIRST(App)),v) >= 0)
         {
         Ap = App;
         App = RED(App);
         }

Step3: /* Finish. */
       B = COMP(V,App);
       SRED(Ap,B);
       B = A;

Return: /* Prepare for return. */
       return(B);
}
