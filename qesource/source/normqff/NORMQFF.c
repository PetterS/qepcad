/*======================================================================
                      F <- NORMQFF(Fh)

Normalize Quantifier Free Formula.
 
\Input
   \parm{F^} is a quantifier-free formula.

\Output
   \parm{F} is a normalized quantifier-free formula 
            equivalent to~\v{F^}.
======================================================================*/
#include "qepcad.h"

Word NORMQFF(Word Fh)
{
       Word F;

Step1: /* Normalize the atomic formulas. */
       F = NORMAFS(Fh);

Step2: /* Remove all ``$0 = 0$'' and ``$0 \neq 0$'' if possible. */
       F = RMCAFS(F);

Step3: /* Remove all $\Leftarrow$, $\Rightarrow$, and $\Leftrightarrow$. */
       F = RMLREOP(F);

Step4: /* Remove all $\neg$. */
       F = RMNOTOP(F);

Step5: /* Remove consecutive And's, Or's. (Not a must.) */
       F = RMCAON(F);

Return: /* Prepare for return. */
       return(F);
}
