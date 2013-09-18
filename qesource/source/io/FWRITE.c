/*======================================================================
                      FWRITE(V,Fs)

Formula Write.

\Input
   \parm{V} is a non-null list of distinct variables.
   \parm{F} is a formula with variables in $V$, written out
            to the output stream.
======================================================================*/
#include "qepcad.h"

void FWRITE(Word V, Word Fs)
{
       Word F,Q,Q_i,f,i,r,x_i;
       /* hide i; */

Step1: /* Write the quantifier list. */
       FIRST4(Fs,&r,&f,&Q,&F);
       for (i = f + 1; i <= r; i++)
         {
         Q_i = LELTI(Q,i - f); x_i = LELTI(V,i);
         SWRITE("("); QFWR(Q_i); SWRITE(" "); VWRITE(x_i); SWRITE(")");
         }

Step2: /* Write the quantifier-free formula. */
       QFFWR(V,F);

Return: /* Prepare for return. */
       return;
}
