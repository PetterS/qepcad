/*======================================================================
                      B <- LINSRT(a,A)

List insertion.

Inputs
  A  : sorted list of BETA-integers ( a1,...an ), n>=0
  a  : BETA-integer.

Outputs
  B  : sorted list of BETA-integers obtained from A by inserting
       a at the proper place. If A is a null list then B = (a).
       If a < a1 then B = ( a,a1,...,an ).
       If a >= an then B = ( a1,...,an,a ).
       If ai <= a < a{i+1} then B = ( a1,...,ai,a,a{i+1},...an).
       The list A is modified.
======================================================================*/
#include "saclib.h"

Word LINSRT(a,A)
       Word a,A;
{
       Word Ap,App,As,B;
       /* hide Ap,App; */

Step1: /* Nl=0. */
       if (A == NIL)
         {
         B = LIST1(a);
         goto Return;
         }

Step2: /* a < al1. */
       if (a < FIRST(A))
         {
         B = COMP(a,A);
         goto Return;
         }

Step3: /* General case. */
       Ap = A;
       App = RED(Ap);
       while (App != NIL && a >= FIRST(App))
         {
         Ap = App;
         App = RED(Ap);
         }
       As = COMP(a,App);
       SRED(Ap,As);
       B = A;

Return: /* Prepare for return. */
       return(B);
}
