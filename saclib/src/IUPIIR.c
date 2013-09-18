/*======================================================================
                      Is <- IUPIIR(A,I)

Integral univariate polynomial isolating interval refinement.  

Inputs
  A : a univariate squarefree polynomial.  
  I : a binary rational isolating interval for a root of A.  
Outputs
  Is : a binary rational subinterval of I, obtained by a single 
       application of RIB, containing the same root.
======================================================================*/
#include "saclib.h"

Word IUPIIR(A,I)
       Word A,I;
{
       Word Is;
       Word a,a1,a2,s,s2;

Step1: /* Get the endpoints of I, a1 and a2, and the bisection
          point, a. */
       FIRST2(I,&a1,&a2);
       a = RIB(a1,a2);

Step2: /* If a2 is the zero then Is = (a,a_2). */
       s2 = IUPBES(A,a2);
       if (s2 == 0)
         {
         Is = LIST2(a,a2);
         goto Return;
         }

Step3: /* Otherwise, compare the signs of A at a and a2. */
       s = IUPBES(A,a);
       if (s == s2)
         Is = LIST2(a1,a);
       else
         Is = LIST2(a,a2);

Return:
       return(Is);
}
