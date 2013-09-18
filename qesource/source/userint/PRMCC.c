/*======================================================================
                      PRMCC(; t)

Process "manually choose a cell" command.

\Output
  \parm{t} is 1 if the command is legal, 0 otherwise.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRMCC(Word *t_)
{
       Word C,c,cp,t;
       /* hide t; */

Step1: /* Read in an argument. */
       CELLRDR(GVPC,&c,&t); if (t == 0) { PCMC = 'n'; goto Return; }

Step2: /* Is it a candidate cell? */
       if ((LELTI(c,TRUTH) == UNDET) && (LELTI(c,CHILD) == NIL)) goto Step3;
       SWRITE("Error PRMCC: ");
       LWRITE(LELTI(c,INDX));
       SWRITE(" is not a candidate cell.\n");
       PCMC = 'n'; t = 0; goto Return;

Step3: /* Process. */
       PCMCC = c; PCMC = 'y'; t = 1;

Return: /* Prepare for return. */
       *t_ = t;
       return;
}
