/*======================================================================
                      A <- EXTRACT(r,F)

Extract polynomials from a quantifier--free formula.
 
\Input
  \parm{r} is a positive $\beta$--integer.
  \parm{F} is a non--constant normalized $r$--variate quantifier-free formula.

\Output
  \parm{A} is the list~$(A_1,\ldots,A_r)$ where each $A'_i$ is
           the list of all the distinct $i$--level polynomials in \v{F}. 

\SideEffect
   \parm{F} is modified in that each polynomial is assigned to
           an index.
======================================================================*/
#include "qepcad.h"

Word EXTRACT(Word r, Word F)
{
       Word A,i;
       /* hide i; */

Step1: /* Extract. */
        A = NIL; for (i = 1; i <= r; i++) A = COMP(NIL,A);
        EXTRACTS(F,A,&A); goto Return;

Return: /* Prepare for return. */
       return(A);
}
