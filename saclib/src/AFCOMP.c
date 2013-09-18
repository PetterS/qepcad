/*======================================================================
                      t <- AFCOMP(M,I,a,b)

Algebraic number field comparison.

Inputs
    M : in Z[X], the minimal polynomial of a real algebraic number alpha.
    I : an acceptable isolating interval for alpha.
 a, b : in Q(alpha).

Outputs
    t : sign(a-b).
======================================================================*/
#include "saclib.h"

Word AFCOMP(M,I,a,b)
       Word M,I,a,b;
{
       Word c,t;
       /* hide t; */

Step1: /* Determine the sign. */
       c = AFDIF(a,b);
       t = AFSIGN(M,I,c);

Return: /* Prepare for return. */
       return(t);
}
